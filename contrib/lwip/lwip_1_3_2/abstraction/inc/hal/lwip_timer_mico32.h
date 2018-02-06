/*
  Name: lwip_timer_mico32.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Mico32 Timer functions for LWIP.
*/

#ifndef __lwip_timer_mico32_h__
#define __lwip_timer_mico32_h__

#include <hal/lwip_compiler.h>
#include "mcu/mico32/inc/ee_timer.h"

#define EE_get_peripheral_clock() CPU_FREQUENCY
 
__INLINE__ void __ALWAYS_INLINE__  EE_hal_lwip_maybe_call_link_tmr(void)
{}
 
__INLINE__ u32_t __ALWAYS_INLINE__ EE_lwip_get_core_timer_value(void)
{
	u32_t time_val;
	EE_freetimer_get_value(&time_val);
	return time_val;
}
/* Function used for timer configuration */
void EE_hal_lwip_timers_configuration(void);

#ifdef __LWIP_TIME_DEBUG__
__INLINE__ u32_t __ALWAYS_INLINE__ EE_hal_lwip_read_timer(void)
{
    return EE_lwip_get_core_timer_value();
}
#endif

#endif /* Header Protection */
