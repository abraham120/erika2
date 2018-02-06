#include <ee.h>
#include <ee_irq.h>
#include "error.h"

#define APP_App2_START_SEC_CODE
#define APP_App2_START_SEC_VAR_NOINIT
#include "MemMap.h"

static volatile char state1;
static char state2;
static volatile char state3;

ISR2(App2Isr)
{
  /* Re-init Sr1 to 1 msec */
  EE_tc2Yx_stm_set_sr1_next_match(1000U);
  ActivateTask(TrustedTask1);
  if (state2 & 1) {
    ActivateTask(App1Task);
  }
  state2 ^= 1;
  state3 = 1;
}


TASK(App2Task)
{
  SuspendAllInterrupts();
  state3 = 0;
  EE_tc2Yx_delay(1000U);
  if (state3 != 0) {
    /* Error: state3 has changed with interrupts disabled */
    error(err_suspend_irq_fail);
  }
  /* Check nesting of suspend/resume */
  SuspendAllInterrupts();
  ResumeAllInterrupts();
  if (state3 != 0) {
    /* Error: state3 has changed with interrupts disabled */
    error(err_resume_irq_early_fail);
  }
  ResumeAllInterrupts();
  /* Interrupts are enabled: pending IRQs should be served before
   * reading state3 in the next instruction */
  if (state3 == 0) {
    /* Error: state3 hasn't changed yet */
    error(err_resume_irq_fail);
  }
  while (! (state1 & 1)) {
    /* Wait for App2Ack */
  }
  state1 = 0;
  TerminateTask();
}

TASK(App2Ack)
{
  state1 |= 1;
  /* This should be a NO-OP */
  EnableAllInterrupts();
  TerminateTask();
}
