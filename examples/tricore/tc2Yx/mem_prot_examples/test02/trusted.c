#include <ee.h>
#include <ee_internal.h>

int EE_APPLICATION_UDATA(TrustedApp) error;

void signal_error(int e)
{
  error = e;
  ActivateTask(ErrorTask);
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
    if (orig[i] != EE_tc_system_tos[EE_as_Application_ROM[i].ISRTOS].ram_tos) {
      signal_error(i);
    }
  }
}


TASK(MainTask)
{
  EE_tc2Yx_stm_set_sr0(1000U, EE_ISR2_ID_App1Isr);
  EE_tc2Yx_stm_set_sr1(1000U, EE_ISR2_ID_App2Isr);

  ActivateTask(TrustedTask1);
  ActivateTask(App1Init);
  ActivateTask(App2Init);
  ActivateTask(App1Bkg);
  TerminateTask();
}

TASK(TrustedTask1)
{
  check_irq_tos();
  TerminateTask();
}


ISR2(TrustedIsr)
{
  /* Re-init to 1 msec */
  EE_tc2Yx_stm_set_sr0_next_match(1000U);

  ActivateTask(TrustedTask1);
}

TASK(ErrorTask)
{
  DisableAllInterrupts();
  while (1) {
    /* Do nothing, just keep the system busy */
  }
}
