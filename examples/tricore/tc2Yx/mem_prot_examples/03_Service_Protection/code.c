#include "test.h"

EE_TYPEASSERTVALUE EE_assertions[EE_MAX_ASSERTIONS];
unsigned int assert_count = EE_ASSERT_NIL;

void test_assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

int test_service_protection( StatusType Error )
{
  /* Volatile to follow it better with debugger */
  int volatile            flag = 1;
  TickType                ticks;
  TickType                elapsed;
  AlarmBaseType           info;
  TaskType                task_id;
  TaskStateType           task_state;
  EventMaskType           event_mask;
  ScheduleTableStatusType sched_table_status;

  flag &= (ActivateTask(TaskApp2Prio2) == Error);
  flag &= (ActivateTask(TaskApp3Prio1) == Error);
  flag &= (ActivateTask(TaskApp3Prio2) == Error);
  flag &= (GetTaskID(&task_id) == Error);
  flag &= (GetTaskState(TaskApp2Prio2, &task_state) == Error);
  flag &= (SetRelAlarm(AlarmApp3, 1, 0) == Error);
  flag &= (SetAbsAlarm(AlarmApp3, 0, 0) == Error);
  flag &= (SetAbsAlarm(AlarmApp3, 0, 0) == Error);
  flag &= (GetISRID() == INVALID_ISR);
  flag &= (GetAlarm(AlarmApp3, &ticks)  == Error);
  flag &= (GetAlarmBase(AlarmApp3, &info)  == Error);
  flag &= (CancelAlarm(AlarmApp3)  == Error);
  flag &= (IncrementCounter(CounterApp3) == Error);
  flag &= (GetCounterValue(CounterApp3, &ticks) == Error);
  flag &= (GetElapsedValue(CounterApp3, &ticks, &elapsed) == Error);
  flag &= (StartScheduleTableAbs(ScheduleTableApp3, 0) == Error);
  flag &= (StartScheduleTableRel(ScheduleTableApp3, 0) == Error);
  flag &= (StopScheduleTable(ScheduleTableApp3) == Error);
  flag &= (NextScheduleTable(ScheduleTableApp3, ScheduleTableApp3) == Error);
  flag &= (GetScheduleTableStatus(ScheduleTableApp3, &sched_table_status) == Error);
  flag &= (WaitEvent(EventApp1Prio1) == Error);
  flag &= (GetEvent(TaskApp1Prio1, &event_mask) == Error);
  flag &= (ClearEvent(EventApp1Prio1) == Error);
  flag &= (GetResource(RES_SCHEDULER) == Error);
  flag &= (ReleaseResource(RES_SCHEDULER) == Error);
  flag &= (Schedule() == Error);
  flag &= (ChainTask(TaskApp3Prio1) == Error);
  flag &= (TerminateTask() == Error);
  flag &= (AllowAccess() == E_OS_CALLEVEL);
  flag &= (TerminateApplication(App1, RESTART) == Error);
  flag &= (CheckObjectAccess(App1, OBJECT_TASK, TaskApp2Prio2) == NO_ACCESS);
  flag &= (CheckObjectOwnership(OBJECT_TASK, TaskApp2Prio2)  == INVALID_OSAPPLICATION);
  flag &= (CheckTaskMemoryAccess(TaskApp1Prio1, &ticks, sizeof(ticks)) == NO_ACCESS);
  flag &= (CheckISRMemoryAccess(INVALID_ISR, &elapsed, sizeof(elapsed)) == NO_ACCESS);

  return flag;
}

void ShutdownHook( StatusType error ) {
  ApplicationStateType    application_state;

  test_assert(test_service_protection(E_OS_CALLEVEL));
  GetApplicationState(App1, &application_state);
  test_assert(application_state == APPLICATION_ACCESSIBLE);
  //GetApplicationState(App2ID, &application_state);
  //GetApplicationState(App3ID, &application_state);

  EE_assert_range(0, 1, assert_count); 
  EE_assert_last();
}

int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
