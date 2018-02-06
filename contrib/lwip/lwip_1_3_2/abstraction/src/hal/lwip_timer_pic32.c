/*
  Name: lwip_timer_mico32.c
  Copyright: Evidence Srl
  Author: Andrea Azzarà, Marco Ghibaudi
  Description: Timer library for LWIP.
*/

#include <hal/lwip_timer.h>

/* Timer configuration */
void EE_hal_lwip_timers_configuration(void)
{
	/* Set the timer to be used with the lwip */
	EE_timer_soft_init(EE_LWIP_TIMER_IN_USE, EE_LWIP_TIMER_PERIOD_MS*1000);
	EE_timer_set_callback(EE_LWIP_TIMER_IN_USE, EE_lwip_timer_tick);
	EE_timer_start(EE_LWIP_TIMER_IN_USE); 
}


