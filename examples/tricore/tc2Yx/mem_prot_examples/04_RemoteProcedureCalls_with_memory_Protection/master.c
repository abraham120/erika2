/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#include "shared.h"

#define ASSERT_LENGTH 45U
EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];

static int assert_count = EE_ASSERT_NIL;
void test_assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

#define ERROR_LENGTH 10U
static EE_UINT32 error_counter;

static OSServiceIdType  const test_as_service_error_expected[ERROR_LENGTH] = {
  OSServiceId_ActivateTask, OSServiceId_SetRelAlarm
};

static StatusType       const test_as_errors_expected[ERROR_LENGTH] = {
  E_OS_LIMIT, E_OS_STATE
};

static EE_UREG          const test_as_param_error_expected[ERROR_LENGTH] = {
  TaskSlave1, AlarmSlave2
};

static StatusType       test_as_errors[ERROR_LENGTH];
static OSServiceIdType  test_as_service_error[ERROR_LENGTH];
static EE_UREG          test_as_param_error[ERROR_LENGTH];

#define TEST_WAIT 50000

TASK(TaskMaster)
{
  EE_UREG volatile        stop;
  TickType                ticks, elapsed;
  EE_UREG                 i, flag;
  AlarmBaseType           info;
  TaskStateType           task_state;
  StatusType              status;
  ApplicationStateType    application_state;
  ScheduleTableStatusType sched_table_status;

  status = ActivateTask(TaskSlave1);
  test_assert(status == E_OK);
  status = ActivateTask(TaskSlave1);
  test_assert(status == E_OS_LIMIT);
  for( stop = 0; stop < TEST_WAIT; ++stop )
    ;
  status = EE_oo_GetTaskState(TaskSlave1, &task_state);
  test_assert(status == E_OK);
  test_assert(task_state == WAITING);
  status = SetEvent(TaskSlave1, EventSlave1);
  test_assert(status == E_OK);
  for( stop = 0; stop < TEST_WAIT; ++stop )
    ;
  status = EE_oo_GetTaskState(TaskSlave1, &task_state);
  test_assert(status == E_OK);
  test_assert(task_state == SUSPENDED);

  status = ActivateTask(TaskSlave1);
  test_assert(status == E_OK);
  status = SetAbsAlarm(AlarmSlave2, 1, 0);
  test_assert(status == E_OK);
  status = SetRelAlarm(AlarmSlave2, 1, 0);
  test_assert(status == E_OS_STATE);
  status = GetAlarm(AlarmSlave2, &ticks);
  test_assert(status == E_OK);
  test_assert(ticks == 1);
  ticks = 0;
  status = ActivateTask(TaskSlave2);
  test_assert(status == E_OK);
  for( stop = 0; stop < TEST_WAIT; ++stop )
    ;
  status = GetCounterValue(CounterSlave2, &ticks);
  test_assert(status == E_OK);
  test_assert(ticks == 1);
  status = ActivateTask(TaskSlave2);
  test_assert(status == E_OK);
  for( stop = 0; stop < TEST_WAIT; ++stop )
    ;
  status = GetElapsedValue(CounterSlave2, &ticks, &elapsed);
  test_assert(status == E_OK);
  test_assert(elapsed == 1);
  status = GetCounterValue(CounterSlave2, &ticks);
  test_assert(status == E_OK);
  test_assert(ticks == 0);

  status = GetAlarmBase(AlarmSlave2, &info);
  test_assert(status == E_OK);
  test_assert(info.maxallowedvalue == 1U );
  test_assert(info.ticksperbase == 1U );
#ifdef __OO_EXTENDED_STATUS__
  test_assert(info.mincycle == 1U );
#endif /* __OO_EXTENDED_STATUS__ */

  status = ActivateTask(TaskSlave1);
  status = StartScheduleTableAbs(ScheduleTableSlave2, 0);
  test_assert(status == E_OK);
  status = GetScheduleTableStatus(ScheduleTableSlave2, &sched_table_status);
  test_assert(status == E_OK);
  test_assert(sched_table_status == SCHEDULETABLE_RUNNING);
  status = ActivateTask(TaskSlave2);
  for( stop = 0; stop < TEST_WAIT; ++stop )
    ;
  status = EE_oo_GetTaskState(TaskSlave1, &task_state);
  test_assert(status == E_OK);
  test_assert(task_state == SUSPENDED);
  status = GetScheduleTableStatus(ScheduleTableSlave2, &sched_table_status);
  test_assert(sched_table_status == SCHEDULETABLE_STOPPED);
  status = StartScheduleTableRel(ScheduleTableSlave2, 1);
  test_assert(status == E_OK);
  status = GetScheduleTableStatus(ScheduleTableSlave2, &sched_table_status);
  test_assert(sched_table_status == SCHEDULETABLE_RUNNING);
  status = StopScheduleTable(ScheduleTableSlave2);
  test_assert(status == E_OK);
  status = GetScheduleTableStatus(ScheduleTableSlave2, &sched_table_status);
  test_assert(sched_table_status == SCHEDULETABLE_STOPPED);

  status = GetApplicationState(Core1App, &application_state);
  test_assert(status == E_OK);
  test_assert(application_state == APPLICATION_ACCESSIBLE);
  status = GetApplicationState(Core2App, &application_state);
  test_assert(application_state == APPLICATION_ACCESSIBLE);
  status = TerminateApplication(Core1App, RESTART);
  test_assert(status == E_OK);
  status = TerminateApplication(Core2App, NO_RESTART);
  status = GetApplicationState(Core1App, &application_state);
  test_assert(application_state == APPLICATION_RESTARTING);
  status = GetApplicationState(Core2App, &application_state);
  test_assert(application_state == APPLICATION_TERMINATED);

  /* Check if the errors have been raised as expected */
  for( i=0U, flag=1U; (i < ERROR_LENGTH) && (flag != 0U); ++i )
  {
    flag &= (test_as_errors[i]        == test_as_errors_expected[i]);
    flag &= (test_as_service_error[i] == test_as_service_error_expected[i]);
    flag &= (test_as_param_error[i]   == test_as_param_error_expected[i]);
  }
  test_assert(flag);

  EE_assert_range(0U, 1U, assert_count);

  EE_assert_last();

  /* Cleanly terminate the Task */
  TerminateTask();
}

void ErrorHook( StatusType Error ) {
  OSServiceIdType const service_id = OSErrorGetServiceId();
  CoreIdType      const core_id    = GetCoreID();

  if( core_id != OS_CORE_ID_MASTER )
  {
    /* This should never happened */
    EE_tc_debug();
  }

  test_as_service_error[error_counter]  = service_id;
  test_as_errors[error_counter]         = Error;
  /* Trick to get the first parameter independently from service
     (IT MUST NOT BE USED IN PRODUCTION CODE) */
  test_as_param_error[error_counter]    = EE_oo_get_errorhook_data()->param1.
    value_param;

  ++error_counter;
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType status;

  StartCore(OS_CORE_ID_1, &status);
  StartCore(OS_CORE_ID_2, &status);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
