/*
  Name:		lwip_timer_cortex_mx.h
  Copyright:	Evidence Srl
  Author:	Giuseppe Serano
  Date:		2012
  Description:	Cortex-MX Timer functions for LWIP.
*/

#ifndef __lwip_timer_cortex_mx_h__
#define __lwip_timer_cortex_mx_h__

#ifndef MILLISECONDS_TO_TICKS
#error lwip for cortex need MILLISECONDS_TO_TICKS macro!
#endif

#include <hal/lwip_compiler.h>

#define EE_get_peripheral_clock() EE_CPU_CLOCK

#define EE_hal_lwip_maybe_call_link_tmr() ((void)0)
 
__INLINE__ u32_t __ALWAYS_INLINE__ EE_lwip_get_core_timer_value(void)
{
  return EE_systick_get_value();
}

#define	EE_hal_lwip_timers_configuration()	((void)0)

#ifdef __LWIP_TIME_DEBUG__
__INLINE__ u32_t __ALWAYS_INLINE__ EE_hal_lwip_read_timer(void)
{
  return EE_lwip_get_core_timer_value();
}
#endif

#endif /* Header Protection */
