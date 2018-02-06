#include <ee_internal.h>
#include <ee_irq.h>
#include "error.h"

#define APP_TrustedApp_START_SEC_CODE
#define APP_TrustedApp_START_SEC_VAR_NOINIT
#include "MemMap.h"

int error_var;

void signal_error(int e)
{
  error_var = e;
  error(err_wrong_irq_tos);
}

void check_irq_tos(void)
{
  static char init;
  static EE_ADDR orig[EE_MAX_APP];
  int i;

  if (init == 0) {
    for (i = 0; i < EE_MAX_APP; ++i) {
      orig[i] = EE_tc_system_tos[EE_as_Application_ROM[i].ISRTOS].ram_tos;
    }
    init = 1;
  }
  for (i = 0; i < EE_MAX_APP; ++i) {
    if (orig[i] != EE_tc_system_tos[EE_as_Application_ROM[i].ISRTOS].ram_tos)
    {
      signal_error(i);
    }
  }
}


TASK(MainTask)
{
  EE_tc2Yx_stm_set_sr0(1000U, EE_ISR2_ID_App1Isr);
  EE_tc2Yx_stm_set_sr1(1000U, EE_ISR2_ID_App2Isr);

  ActivateTask(TrustedTask1);
  ActivateTask(App1Bkg);
  ActivateTask(App1Task);
  TerminateTask();
}

TASK(TrustedTask1)
{
  check_irq_tos();
  /* This should be a NO-OP */
  ResumeAllInterrupts();
  TerminateTask();
}

