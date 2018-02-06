#include <ee.h>
#include <ee_irq.h>

static volatile int EE_APPLICATION_UDATA(App1) state1;
static volatile int EE_APPLICATION_IDATA(App1) counter1 = 110100;
char EE_APPLICATION_IDATA(App1) err1 = 0x13;

ISR(App1Isr)
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
    ActivateTask(ErrorTask);
  }
}

TASK(App1Task)
{
  while (state1 & 1) {
    /* Wait for the next ISR invocation */
  }
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
