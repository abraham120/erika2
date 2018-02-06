/*
  Name: lwip_timer.c
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: Timer library for LWIP.
*/

#include "ee_lwip.h"

#ifdef __LWIP_TIME_DEBUG__
u32_t lwip_ts_buffer[LWIP_TS_BUFFER_SIZE];
#endif

struct ee_lwip_timers EE_lwip_timers;

/* Timer interrupt callback */
void EE_lwip_timer_tick(void)
{
    EE_UINT16 pending = EE_lwip_increment_timers(&EE_lwip_timers);
    if (pending != 0)
        ActivateTask(LwipPeriodic);
}


