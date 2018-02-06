#include <ee.h>
#include "app.h"

#define APP_App2_START_SEC_CODE
#define APP_App2_START_SEC_VAR_NOINIT
#include "MemMap.h"
static char var0;
static int var1;
static volatile char state1;
static char state2;
#define APP_App2_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define APP_App2_START_SEC_DATA
#include "MemMap.h"
static int var2 = 0x374a430b;
static char var3 = 0x34;
static int err = 0;
#define APP_App2_STOP_SEC_DATA
#include "MemMap.h"

ISR2(App2Isr)
{
  /* Re-init to SR1 to 1 msec */
  EE_tc2Yx_stm_set_sr1_next_match(1000U);

  ActivateTask(TrustedTask1);
  if (state2 & 1) {
    ActivateTask(App1Task);
  }
  state2 ^= 1;
  CallMyIsrTrustedService(0);
}


TASK(App2Task)
{
  while (! (state1 & 1)) {
    /* Wait for App2Ack */
  }
  state1 = 0;
  TerminateTask();
}

TASK(App2Ack)
{
  state1 |= 1;
  TerminateTask();
}

TASK(App2HiPriTask)
{
  TerminateTask();
}

TASK(App2Init)
{
  if (err != 0) {
    err = -1;
  } else if (var3 != 0x34) {
    err = 10;
  } else if (var2 != 0x374a430b) {
    err = 11;
  } else if (var1 != 0) {
    err = 12;
  } else if (var0 != 0) {
    err = 13;
  } else {
    /* Everything is ok */
  }
  if (err != 0) {
    signal_error(err);
  }

  TerminateTask();
}
