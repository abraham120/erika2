/*
  Name:		lwip_timer_cortex_mx.c
  Copyright:	Evidence Srl
  Author:	Errico Guidieri
  		Giuseppe Serano
  Date:		2012
  Description:	Timer library for LWIP.
*/

#include <hal/lwip_timer.h>

TASK(LwipTimer)
{
  GetResource(LwipMutex);

  EE_lwip_timer_tick();

  ReleaseResource(LwipMutex);
}
