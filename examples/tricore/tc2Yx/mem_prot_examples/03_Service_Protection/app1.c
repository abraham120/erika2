#include "test.h"

TASK(TaskApp1Prio1)
{
  ApplicationStateType    application_state;
  EventMaskType           events;

  /* Service Protection diasbled Interrupts  */
  DisableAllInterrupts();
  test_assert(test_service_protection(E_OS_DISABLEDINT));
  test_assert(GetApplicationState(App1, &application_state) == E_OS_DISABLEDINT);
  EnableAllInterrupts();

  SuspendOSInterrupts();
  test_assert(test_service_protection(E_OS_DISABLEDINT));
  test_assert(GetApplicationState(App2, &application_state) == E_OS_DISABLEDINT);
  SuspendAllInterrupts();
  ResumeOSInterrupts();
  test_assert(test_service_protection(E_OS_DISABLEDINT));
  test_assert(GetApplicationState(App3, &application_state) == E_OS_DISABLEDINT);
  ResumeAllInterrupts();

  test_assert(CheckObjectAccess(App1, OBJECT_TASK, TaskApp2Prio2) == NO_ACCESS);
  test_assert(CheckObjectAccess(App1, OBJECT_TASK, TaskApp3Prio1) == NO_ACCESS);
  test_assert(CheckObjectAccess(App1, OBJECT_TASK, TaskApp3Prio2) == ACCESS);

  test_assert(CheckObjectAccess(App1, OBJECT_RESOURCE, RES_SCHEDULER) == ACCESS);
  test_assert(CheckObjectAccess(App1, OBJECT_COUNTER, CounterApp3) == NO_ACCESS);
  test_assert(CheckObjectAccess(App1, OBJECT_ALARM, AlarmApp3) == ACCESS);
  test_assert(CheckObjectAccess(App1, OBJECT_SCHEDULETABLE, ScheduleTableApp3) == NO_ACCESS);

  test_assert(ActivateTask(TaskApp2Prio2) == E_OS_ACCESS);
  test_assert(ActivateTask(TaskApp3Prio2) == E_OK);
  test_assert(SetRelAlarm(AlarmApp3, 1, 0) == E_OK);
  test_assert(TerminateApplication(App3, RESTART) == E_OK);
  test_assert(WaitEvent(EventApp1Prio1) == E_OK);
  test_assert(GetEvent(TaskApp1Prio1, &events) == E_OK);
  test_assert(EventApp1Prio1 == events);
  test_assert(ClearEvent(EventApp1Prio1) == E_OK);

  ShutdownOS(E_OK);
  TerminateTask();
}

