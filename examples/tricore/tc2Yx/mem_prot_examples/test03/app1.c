#include <ee.h>
#include "app.h"

#define APP_App1_START_SEC_CODE
#define APP_App1_START_SEC_VAR_NOINIT
#include "MemMap.h"
static volatile int state1;

#define APP_App1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define APP_App1_START_SEC_DATA
#include "MemMap.h"
static volatile int counter1 = 110100;
char err1 = 0x13;
#define APP_App1_STOP_SEC_DATA
#include "MemMap.h"

ISR2(App1Isr)
{
  /* Re-init Sr0 to 1 msec */
  EE_tc2Yx_stm_set_sr0_next_match(1000U);

  if (! (state1 & 1)) {
    ActivateTask(App2Task);
  } else {
    ActivateTask(App2Ack);
  }
  state1 ^= 1;
}

TASK(App1Init)
{
  if (err1 != 0x13) {
    err1 = -1;
  } else if (state1 != 0) {
    err1 = 1;
  } else if (counter1 != 110100) {
    err1 = 2;
  } else {
    err1 = 0;
  }
  if (err1 != 0) {
    signal_error(err1);
  }
}

TASK(App1Task)
{
  while (state1 & 1) {
    /* Wait for the next ISR invocation */
  }
  CallMyTaskTrustedService(0);
  TerminateTask();
}

TASK(App1Ack)
{
}

TASK(App1Bkg)
{
  while (1) {
    counter1 += 1;
  }
}
