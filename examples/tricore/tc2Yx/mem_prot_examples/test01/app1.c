#include "ee.h"

static volatile int EE_APPLICATION_UDATA(App1) state1;

ISR(App1Isr)
{
  /* Re-init to 1 msec */
  EE_tc2Yx_stm_set_sr1_next_match(1000U);
  if (! (state1 & 1)) {
    ActivateTask(App1Task);
  }
  state1 ^= 1;
}


TASK(App1Task)
{
  while (state1 & 1) {
    /* Wait for the next ISR invocation */
  }
  TerminateTask();
}
