#include "test.h"

TASK(TaskApp3Prio1)
{
  test_assert(test_service_protection(E_OS_ACCESS));
  test_assert(AllowAccess() == E_OK);
  test_assert(ActivateTask(TaskApp3Prio2) == E_OK);
  TerminateTask();
}

TASK(TaskApp3Prio2)
{
/*#define APP_App3_START_SEC_VAR_NOINIT
#include "MemMap.h" */
  static unsigned int count;
/*#define APP_App3_STOP_SEC_VAR_NOINIT
#include "MemMap.h"*/

  ++count;
  if ( count == 1U ) {
    test_assert(ActivateTask(TaskApp2Prio2) == E_OK);
    TerminateTask();
    error();
  } else if ( count == 2U ){
    test_assert(ActivateTask(TaskApp2Prio2) == E_OS_LIMIT);
    IncrementCounter(CounterApp3);
    TerminateTask();
    error();
  } else if ( count == 3U ) {
    IncrementCounter(CounterApp3);
    error();
  } else {
    error();
  }
  TerminateTask();
}
