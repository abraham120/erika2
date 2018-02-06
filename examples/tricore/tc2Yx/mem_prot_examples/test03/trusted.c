#include "ee.h"
#include "ee_internal.h"
#include "app.h"
#include "trusted.h"

/* flag1 is allocated in the OS segment */
static volatile int flag1;

#define APP_TrustedApp_START_SEC_VAR_NOINIT
#define APP_TrustedApp_START_SEC_CODE
#include "MemMap.h"

struct trusted_params
{
  EE_INT32 arg0;
  EE_INT32 res;
};

int error;
EE_UREG gvar;
/* just to not make the compiler optimize some code and warning because wrote
   and not used */
static EE_UREG volatile x;

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

/* User inteface */
EE_INT32 CallMyTaskTrustedService(EE_INT32 arg)
{
  struct trusted_params str;
  StatusType s;
  str.arg0 = arg;
  s = CallTrustedFunction(EE_ID_TRUSTED_MyTaskTrustedService, &str);
  if (s != E_OK) {
    str.res = -1;
    signal_error( -1 );
  }
  return str.res;
}
 
/* User inteface */
EE_INT32 CallMyIsrTrustedService(EE_INT32 arg)
{
  struct trusted_params str;
  StatusType s;
  str.arg0 = arg;
  s = CallTrustedFunction(EE_ID_TRUSTED_MyIsrTrustedService, &str);
  if (s != E_OK) {
    str.res = -1;
  }
  return str.res;
}
 
StatusType TRUSTED_MyTaskTrustedService(TrustedFunctionIndexType index,
  TrustedFunctionParameterRefType ref)
{
  /* Privileged function */
  x = EE_tc_get_ICR().reg;
  flag1 = 0;
  while (flag1 == 0) {
    /* Wait for MyIsrTrustedService */
  }
  /* Again, a privileged function */
  x = EE_tc_get_ICR().reg;
  /* Launch a non-trusted, high-priority task */
  ActivateTask(App2HiPriTask);
  /* Again, a privileged function */
  x = EE_tc_get_ICR().reg;
  return E_OK;
}

StatusType TRUSTED_MyIsrTrustedService(TrustedFunctionIndexType index,
  TrustedFunctionParameterRefType ref)
{
  /* Privileged function */
  x = EE_tc_get_ICR().reg;
  flag1 = 1;
  return E_OK;
}

TASK(TrustedTask1)
{
  check_irq_tos();
  TerminateTask();
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

TASK(ErrorTask)
{
  DisableAllInterrupts();
  while (1) {
    /* Do nothing, just keep the system busy */
    EE_tc_debug();
  }
}
