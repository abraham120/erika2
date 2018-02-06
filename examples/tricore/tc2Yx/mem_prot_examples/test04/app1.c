#include <ee_internal.h>
#include <ee_irq.h>
#include "error.h"

#define APP_App1_START_SEC_CODE

#define APP_App1_START_SEC_VAR_NOINIT
#include "MemMap.h"
static volatile int state1;
static volatile int state2;
static volatile int state3;
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
  state2 = 1;
  state3 = 1;
}

TASK(App1Task)
{
  DisableAllInterrupts();
  state2 = 0;
  /* Simulate the calling of an API in the ORTI tracer */
  EE_ORTI_set_service_in(EE_SERVICETRACE_GETRESOURCE);
  EE_tc2Yx_delay(1000U);
  EE_ORTI_set_service_out(EE_SERVICETRACE_GETRESOURCE);
  if (state2 != 0) {
    /* Error: state2 has changed while interrupts were disabled */
    error(err_disable_irq_fail);
  }
  EnableAllInterrupts();
  /* Interrupts are enabled: pending IRQ should be served before reading
   * state2 in the next instruction */
  if (state2 == 0) {
    /* Error: no interrupt though we have enabled interrupts */
    error(err_enable_irq_fail);
  }
  TerminateTask();
}

TASK(App1Bkg)
{
  while (1) {
    counter1 += 1;
  }
}
