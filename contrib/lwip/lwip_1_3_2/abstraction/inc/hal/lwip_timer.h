/*
  Name: lwip_timer.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano, and Andrea Azzarà, Marco Ghibaudi
  Date: 29/03/10 18.23
  Description: Timer configurations functions for LWIP.
*/

#ifndef __lwip_timer_h__
#define __lwip_timer_h__

/* Compiler specification */
#include <hal/lwip_compiler.h>

#include "lwip/tcp.h"
#include <netif/etharp.h>

/* HW specification */
#if defined __LM32__
#include <hal/lwip_timer_mico32.h>
//FIXME: we moved this inclusion here but it should be probably deleted and
// moved to the specific timer_hal files
#include <system_conf.h>

#elif defined __PIC32__
#include <hal/lwip_timer_pic32.h>
#include "eth_api.h"

#elif defined __CORTEX_MX__
#include <hal/lwip_timer_cortex_mx.h>
#else			/* No timer */
#warning "No timer Specified"
#endif	/* End Selection */

/* Macros and functions for time analisys */
#define lwip_time_diff_ms(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000))
#define lwip_time_diff_us(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000000))

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_lwip_elapsed(EE_UINT32 from, EE_UINT32 to)
{
	return to - from;
}

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_lwip_get_time_stamp(void)
{
    return EE_lwip_get_core_timer_value();
}

__INLINE__ void __ALWAYS_INLINE__ EE_lwip_sleep_ms(EE_UINT32 ms)
{
	EE_UINT32 start, curr;
	EE_UINT32 cpu_freq = EE_get_peripheral_clock();
	start = EE_lwip_get_time_stamp();
	do {
		curr = EE_lwip_get_time_stamp();
	} while (EE_lwip_elapsed(start, curr) < (ms * (cpu_freq / 1000U)));
}

/* Lwip timers configuration */
#ifndef EE_LWIP_TIMER_PERIOD_MS
#define EE_LWIP_TIMER_PERIOD_MS (5U)
#endif
#define EE_LWIP_ARP_PERIOD      (ARP_TMR_INTERVAL / EE_LWIP_TIMER_PERIOD_MS)
#define EE_LWIP_TCP_FAST_PERIOD (TCP_FAST_INTERVAL / EE_LWIP_TIMER_PERIOD_MS)
#define EE_LWIP_TCP_SLOW_PERIOD (TCP_SLOW_INTERVAL / EE_LWIP_TIMER_PERIOD_MS)
#define EE_LWIP_LINK_PERIOD     (20U) /* 100 ms */
#define EE_LWIP_RX_POLLING_PERIOD  (40U) /* 200 ms */

/* Masks for `pending' in struct ee_lwip_timers */
#define EE_LWIP_TIMER_ARP       1
#define EE_LWIP_TIMER_TCP_FAST  2
#define EE_LWIP_TIMER_TCP_SLOW  4
#define EE_LWIP_TIMER_LINK      8

struct ee_lwip_timers
{
    EE_UINT16 arp_ticks;
#if LWIP_TCP
    EE_UINT16 tcp_fast_ticks;
    EE_UINT16 tcp_slow_ticks;
#endif
    EE_UINT16 link_ticks;
    /** Bit mask indicating which timer callback is to be called */
    volatile EE_UINT16 pending;
};

extern struct ee_lwip_timers EE_lwip_timers;

/* Callback used for Lwip timers */
void EE_lwip_timer_tick(void);

/* TCP timers */
#if LWIP_TCP
/** Update TCP timers, but don't modify the pending field in the struct. */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_lwip_update_tcp_timers(
    struct ee_lwip_timers *tmrs, EE_UINT16 pending)
{
    tmrs->tcp_fast_ticks += 1;
    if (tmrs->tcp_fast_ticks >= EE_LWIP_TCP_FAST_PERIOD) {
        tmrs->tcp_fast_ticks = 0;
        pending |= EE_LWIP_TIMER_TCP_FAST;
    }
    tmrs->tcp_slow_ticks += 1;
    if (tmrs->tcp_slow_ticks >= EE_LWIP_TCP_SLOW_PERIOD) {
        tmrs->tcp_slow_ticks = 0;
        pending |= EE_LWIP_TIMER_TCP_SLOW;
    }
    return pending;
}

/** Call TCP timer callbacks if needed */
__INLINE__ void __ALWAYS_INLINE__ EE_lwip_maybe_call_tcp_timers(
    EE_UINT16 pending)
{
    if (pending & EE_LWIP_TIMER_TCP_FAST)
        tcp_fasttmr();
    if (pending & EE_LWIP_TIMER_TCP_SLOW)
        tcp_slowtmr();
}
#else
#define EE_lwip_update_tcp_timers(tmrs, pending) (pending)
#define EE_lwip_maybe_call_tcp_timers(pending)
#endif /* LWIP_TCP */

/**
 * @brief Increment timer ticks and update the pending status.
 * This function must be called with interrupts disabled.
 * @return the new pending status
 */
__INLINE__ EE_UINT16 EE_lwip_increment_timers(struct ee_lwip_timers *tmrs)
{
    /* Keep a copy of pending, which is volatile */
    EE_UINT16 pending = tmrs->pending;
    /* ARP timer */
    tmrs->arp_ticks += 1;
    if (tmrs->arp_ticks >= EE_LWIP_ARP_PERIOD) {
        tmrs->arp_ticks = 0;
        pending |= EE_LWIP_TIMER_ARP;
    }
    /* TCP timer */
    pending = EE_lwip_update_tcp_timers(tmrs, pending);
    /* LINK timer */
    tmrs->link_ticks += 1;
    if (tmrs->link_ticks >= EE_LWIP_LINK_PERIOD) {
        tmrs->link_ticks = 0;
        pending |= EE_LWIP_TIMER_LINK;
    }
    /* store flags */
    tmrs->pending = pending;
    return pending;
}

/** Call ARP timer callback if needed */
__INLINE__ void __ALWAYS_INLINE__ EE_lwip_maybe_call_arp_timer(
    EE_UINT16 pending)
{
    if (pending & EE_LWIP_TIMER_ARP)
        etharp_tmr();
}

/** Call LINK timer callback if needed */
__INLINE__ void __ALWAYS_INLINE__ EE_lwip_maybe_call_link_check(
    EE_UINT16 pending)
{
    if (pending & EE_LWIP_TIMER_LINK)
        EE_hal_lwip_maybe_call_link_tmr();
}

/* Function used for Lwip timers configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_lwip_timers_configuration(void)
{
	EE_hal_lwip_timers_configuration();
}

/* Time analisys for debug */
#ifdef __LWIP_TIME_DEBUG__
enum{	
	LWIP_START_ETH_OUT,
	LWIP_START_LOWLEV_OUT, 
	LWIP_START_UDP_SEND, 
	LWIP_START_LOWLEV_INIT,
	LWIP_START_LOWLEV_INPUT,
	LWIP_START_ETH_INIT,
	LWIP_START_ETH_INPUT,
	LWIP_START_UDP_INPUT,
	LWIP_START_UDP_RX_CBK,
	LWIP_START_UDP_SEND_IPROUTE,
	LWIP_START_LOWLEV_INIT_TRANSFER,
	LWIP_START_LOWLEV_WRITE,
	LWIP_START_LOWLEV_SIGNAL,
	LWIP_START_UDP_CHECKSUM,
	LWIP_START_IP_OUTPUT,
	
	LWIP_END_ETH_OUT,
	LWIP_END_LOWLEV_OUT,
	LWIP_END_UDP_SEND,
	LWIP_END_LOWLEV_INIT,
	LWIP_END_LOWLEV_INPUT,
	LWIP_END_ETH_INPUT,
	LWIP_END_ETH_INIT,
	LWIP_END_UDP_INPUT,
	LWIP_END_UDP_RX_CBK,
	LWIP_END_UDP_SEND_IPROUTE,
	LWIP_END_LOWLEV_INIT_TRANSFER,
	LWIP_END_LOWLEV_WRITE,
	LWIP_END_LOWLEV_SIGNAL,
	LWIP_END_UDP_CHECKSUM,
	LWIP_END_IP_OUTPUT,
	LWIP_END_IP_BEFORE_NETIF_OUTPUT,
	
	LWIP_TS_BUFFER_SIZE };
	
extern u32_t lwip_ts_buffer[LWIP_TS_BUFFER_SIZE];

__INLINE__ void __ALWAYS_INLINE__ EE_lwip_write_timestamp(u32_t id)
{
	lwip_ts_buffer[id] = EE_hal_lwip_read_timer();
}

__INLINE__ u32_t __ALWAYS_INLINE__ EE_lwip_read_timestamp(u32_t id)
{
	return lwip_ts_buffer[id];
}

__INLINE__ void __ALWAYS_INLINE__ EE_lwip_reset_timestamp(void)
{
	int i;
	for(i=0; i<LWIP_TS_BUFFER_SIZE; i++)
		lwip_ts_buffer[i] = 0;
}

#else	

#define EE_lwip_write_timestamp(id)
#define EE_lwip_read_timestamp(id)	-1
#define EE_lwip_reset_timestamp()

#endif	// __LWIP_TIME_DEBUG__

#endif /* Header Protection */
