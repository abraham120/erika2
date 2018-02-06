/*
  Name: lwip_timer_mico32.h
  Copyright: Evidence Srl
  Author: Andrea Azzarà, Marco Ghibaudi
  Date: 29/03/10 18.23
  Description: Mico32 Timer functions for LWIP.
*/

#ifndef __lwip_timer_pic32_h__
#define __lwip_timer_pic32_h__

#include <hal/lwip_compiler.h>
#include "mcu/microchip_pic32/inc/ee_timer.h"
#include "eth_api.h"

#ifndef EE_LWIP_TIMER_IN_USE	
#define EE_LWIP_TIMER_IN_USE	EE_TIMER_2
#endif

#define EE_lwip_get_core_timer_value() EE_pic32_get_core_timer_value()

__INLINE__ void __ALWAYS_INLINE__  EE_hal_lwip_maybe_call_link_tmr(void)
{
	EE_eth_link_check();
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
