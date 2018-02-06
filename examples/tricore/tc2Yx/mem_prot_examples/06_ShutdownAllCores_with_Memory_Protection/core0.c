#include "test.h"

EE_TYPEASSERTVALUE EE_assertions[35];

static int assert_count = EE_ASSERT_NIL;
void test_assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

#define SHARED_START_SEC_VAR_NOINIT
#include "MemMap.h"
EE_UREG volatile sync_shutdown_asserts;
EE_UREG volatile shutdown_flag;
#define SHARED_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

EE_UREG volatile core0App_startup;
EE_UREG volatile core0App_shutdown;

EE_UREG volatile error_flag;

int main ( void ) {
  StatusType status;
  StartCore(OS_CORE_ID_1, &status);
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}

TASK(TaskCore0Prio1) {
  test_assert(core0App_startup == 1);
  test_assert(core0App_shutdown == 0);
  test_assert(ActivateTask(TaskCore1Restart) == E_OS_ACCESS);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OK);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OK);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OK);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OS_LIMIT);
  test_assert(ActivateTask(TaskCore1ExtPrio2) == E_OK);
  test_assert(ActivateTask(TaskCore1ExtPrio2) == E_OS_LIMIT);
#ifdef EE_TEST_TASK_IN_EXECUTION_TERMINATION
  EE_tc2Yx_delay(1000);
#else /* EE_TEST_TASK_IN_EXECUTION_TERMINATION */
  EE_tc2Yx_delay(50);
#endif /* EE_TEST_TASK_IN_EXECUTION_TERMINATION */

  test_assert(TerminateApplication(AppCore1, RESTART) == E_OK);

  test_assert(ActivateTask(TaskCore1Restart) == E_OS_ACCESS);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OS_ACCESS);
  test_assert(ActivateTask(TaskCore1ExtPrio2) == E_OS_ACCESS);

  sync_shutdown_asserts = 1;
  while ( sync_shutdown_asserts != 0 )
    ;
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OK);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OK);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OK);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OS_LIMIT);
  test_assert(ActivateTask(TaskCore1ExtPrio2) == E_OK);
  test_assert(ActivateTask(TaskCore1ExtPrio2) == E_OS_LIMIT);
#ifdef EE_TEST_TASK_IN_EXECUTION_TERMINATION
  EE_tc2Yx_delay(1000);
#endif /* EE_TEST_TASK_IN_EXECUTION_TERMINATION */

  ShutdownAllCores(E_OK);
}

void ShutdownHook( StatusType Error )
{
  if ( GetCoreID() == OS_CORE_ID_MASTER ) {
    test_assert(GetApplicationID() == AppCore0);
    test_assert(ActivateTask(TaskCore0Prio1) == E_OS_CALLEVEL);
    test_assert(ActivateTask(TaskCore1StdPrio1) == E_OS_CALLEVEL);
    test_assert(core0App_startup == 1);
    test_assert(core0App_shutdown == 1);
    shutdown_flag |= 1U;
    while ( shutdown_flag != 3U )
      ;
    EE_assert_range(0, 1, assert_count);

    EE_assert_last();
  } else if ( GetCoreID() == OS_CORE_ID_1 ) {
    shutdown_flag |= 2U;
  }
}

void StartupHook_AppCore0( void )
{
  test_assert(GetApplicationID() == AppCore0);
  test_assert(ActivateTask(TaskCore0Prio1) == E_OS_CALLEVEL);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OS_CALLEVEL);
  ++core0App_startup;
}

void ShutdownHook_AppCore0( StatusType Error )
{
  test_assert(GetApplicationID() == AppCore0);
  test_assert(ActivateTask(TaskCore0Prio1) == E_OS_CALLEVEL);
  test_assert(ActivateTask(TaskCore1StdPrio1) == E_OS_CALLEVEL);
  ++core0App_shutdown;
}
