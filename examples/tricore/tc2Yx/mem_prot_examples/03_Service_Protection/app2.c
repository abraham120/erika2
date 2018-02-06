#include "test.h"

TASK(TaskApp2Prio2)
{
  EventMaskType           events;

  SuspendAllInterrupts();
  SuspendOSInterrupts();
  test_assert(test_service_protection(E_OS_DISABLEDINT));
  ResumeOSInterrupts();
  test_assert(test_service_protection(E_OS_DISABLEDINT));
  ResumeAllInterrupts();

  test_assert(IncrementCounter(CounterApp3) == E_OS_ACCESS);
  test_assert(ActivateTask(TaskApp3Prio1) == E_OS_ACCESS);
  test_assert(TerminateApplication(App3, RESTART) == E_OS_ACCESS);
  /* It shall be ignored */
  ShutdownOS(E_OS_STATE);

  test_assert(StartScheduleTableAbs(ScheduleTableApp3, 0) == E_OK);
  test_assert(ActivateTask(TaskApp3Prio2) == E_OK);
  test_assert(WaitEvent(EventApp2Prio2) == E_OK);
  test_assert(GetEvent(TaskApp2Prio2, &events) == E_OK);
  test_assert(EventApp2Prio2 == events);
  test_assert(ClearEvent(EventApp2Prio2) == E_OK);


  TerminateTask();
}

