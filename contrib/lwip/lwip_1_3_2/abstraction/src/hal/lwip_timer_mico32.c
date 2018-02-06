/*
  Name: lwip_timer_mico32.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Timer library for LWIP.
*/

#include <hal/lwip_timer.h>
#include <MicoMacros.h>

/* Timer configuration */
void EE_hal_lwip_timers_configuration(void)
{
	 /* Set up the timer for polling and timeouts */
    EE_timer_uwl_init(MILLISECONDS_TO_TICKS(EE_LWIP_TIMER_PERIOD_MS),
        MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
    EE_timer_uwl_set_ISR_callback(EE_lwip_timer_tick);
    EE_timer_uwl_on();
}


