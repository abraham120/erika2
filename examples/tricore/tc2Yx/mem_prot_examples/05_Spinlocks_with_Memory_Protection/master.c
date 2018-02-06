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

#define SHARED_START_SEC_VAR_NOINIT
#include "MemMap.h"
EE_UREG shared_slave1;
EE_UREG shared_slave2;
#define SHARED_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define ASSERT_LENGTH 40U
EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];

static int assert_count = EE_ASSERT_NIL;
void test_assert(int test)
{
  register int next_assert;
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
}

#define ERROR_LENGTH 20U
static EE_UINT32 error_counter;

static StatusType       const test_as_errors_expected[ERROR_LENGTH] = {
  E_OS_CALLEVEL, E_OS_CALLEVEL, E_OS_ID, E_OS_ID, E_OS_NESTING_DEADLOCK,
  E_OS_SPINLOCK, E_OS_SPINLOCK, E_OS_SPINLOCK, E_OS_NOFUNC,
  E_OS_INTERFERENCE_DEADLOCK, E_OS_STATE, E_OS_SPINLOCK, E_OS_ID,
  E_OS_PARAM_POINTER, E_OS_NESTING_DEADLOCK, E_OS_INTERFERENCE_DEADLOCK,
  E_OS_SPINLOCK, E_OS_MISSINGEND
};

static OSServiceIdType  const test_as_service_error_expected[ERROR_LENGTH] = {
  OSServiceId_GetSpinlock, OSServiceId_ReleaseSpinlock, OSServiceId_GetSpinlock,
  OSServiceId_ReleaseSpinlock, OSServiceId_GetSpinlock, OSServiceId_WaitEvent,
  OSServiceId_TerminateTask, OSServiceId_ChainTask, OSServiceId_ReleaseSpinlock,
  OSServiceId_GetSpinlock, OSServiceId_ReleaseSpinlock, OSId_ISR2Body,
  OSServiceId_TryToGetSpinlock, OSServiceId_TryToGetSpinlock,
  OSServiceId_TryToGetSpinlock, OSServiceId_TryToGetSpinlock,
  OSServiceId_Schedule, OSId_TaskBody
};

static EE_UREG          const test_as_param_error_expected[ERROR_LENGTH] = {
  spinlock_2, spinlock_3, EE_MAX_SPINLOCK_USER + 1U, EE_MAX_SPINLOCK_USER + 1U,
  spinlock_1, spinlock_1, spinlock_1, spinlock_1, spinlock_1, spinlock_1,
  spinlock_1, spinlock_1, EE_MAX_SPINLOCK_USER + 1U, spinlock_2, spinlock_1,
  spinlock_2, 0U, spinlock_1
};

static StatusType       test_as_errors[ERROR_LENGTH];
static OSServiceIdType  test_as_service_error[ERROR_LENGTH];
static EE_UREG          test_as_param_error[ERROR_LENGTH];

/* Fire the IRQ */
static void test_raise_irq()
{
  static EE_UREG volatile intsource;
  SRC_GPSR01.U |= EE_TC2YX_SRN_SET_REQUEST;

  EE_tc_dsync();
  intsource = SRC_GPSR01.U;
  EE_tc_isync();
}


#define TEST_WAIT 1000000U

TASK(TaskMaster)
{
  EE_UINT32 volatile    i, flag;
  StatusType            status;
  TryToGetSpinlockType  try_to_get_success;

  status = GetSpinlock(EE_MAX_SPINLOCK_USER + 1U);
  test_assert(status == E_OS_ID);
  status = ReleaseSpinlock(EE_MAX_SPINLOCK_USER + 1U);
  test_assert(status == E_OS_ID);
  status = GetSpinlock(spinlock_2);
  test_assert(status == E_OK);
  status = GetSpinlock(spinlock_1);
  test_assert(status == E_OS_NESTING_DEADLOCK);
  status = ReleaseSpinlock(spinlock_2);
  test_assert(status == E_OK);
  status = GetSpinlock(spinlock_1);
  test_assert(status == E_OK);

  status = WaitEvent(Event1);
  test_assert(status == E_OS_SPINLOCK);
  status = TerminateTask();
  test_assert(status == E_OS_SPINLOCK);
  status = ChainTask(TaskMaster2);
  test_assert(status == E_OS_SPINLOCK);

  status = GetSpinlock(spinlock_3);
  test_assert(status == E_OK);
  status = ReleaseSpinlock(spinlock_1);
  test_assert(status == E_OS_NOFUNC);
  status = ReleaseSpinlock(spinlock_3);
  test_assert(status == E_OK);

  /* raise IRQ */
  test_raise_irq();

  /* Check automatic Spinlocks Release */
  status = GetSpinlock(spinlock_3);
  test_assert(status == E_OK);
  test_assert(shared_slave1 == 1U);
  status = ReleaseSpinlock(spinlock_3);
  test_assert(status == E_OK);

  /* Release sinlock spinlock_1 */
  status = ReleaseSpinlock(spinlock_1);
  test_assert(status == E_OK);

  status = TryToGetSpinlock(EE_MAX_SPINLOCK_USER + 1U, &try_to_get_success);
  test_assert(status == E_OS_ID);
  status = TryToGetSpinlock(spinlock_2, 0U);
  test_assert(status == E_OS_PARAM_POINTER);

  status = TryToGetSpinlock(spinlock_2, &try_to_get_success);
  test_assert(status == E_OK);
  test_assert(try_to_get_success == TRYTOGETSPINLOCK_SUCCESS);

  ActivateTask(TaskMaster2);

  /* Check Automatic Release spinlocks */
  status = TryToGetSpinlock(spinlock_3, &try_to_get_success);
  test_assert(status == E_OK);
  test_assert(try_to_get_success == TRYTOGETSPINLOCK_SUCCESS);
  status = ReleaseSpinlock(spinlock_3);
  test_assert(status == E_OK);

  ActivateTask(TaskSlave2);

  {
    EE_UINT32 volatile stop = 0U;
    while (++stop < TEST_WAIT)
      ;

    test_assert(shared_slave2 == 1U);

    status = ReleaseSpinlock(spinlock_2);
    test_assert(status == E_OK);

    stop = 0U;
    while (++stop < TEST_WAIT)
      ;

    test_assert(shared_slave2 == 2U);
  }

  /* Check if the errors have been raised as expected */
  for(i=0, flag=1; (i < ERROR_LENGTH) && (flag != 0); ++i) {
    flag &= (test_as_errors[i]        == test_as_errors_expected[i]);
    flag &= (test_as_service_error[i] == test_as_service_error_expected[i]);
    flag &= (test_as_param_error[i]   == test_as_param_error_expected[i]);
  }
  test_assert(flag);

  EE_assert_range(0, 1, assert_count);

  EE_assert_last();

  /* Cleanly terminate the Task */
  TerminateTask();
}

TASK(TaskMaster2) {
  StatusType status;
  TryToGetSpinlockType  try_to_get_success;

  status = TryToGetSpinlock(spinlock_1, &try_to_get_success);
  test_assert(status == E_OS_NESTING_DEADLOCK);
  status = TryToGetSpinlock(spinlock_2, &try_to_get_success);
  test_assert(status == E_OS_INTERFERENCE_DEADLOCK);
  status = TryToGetSpinlock(spinlock_3, &try_to_get_success);
  test_assert(status == E_OK);
  test_assert(try_to_get_success == TRYTOGETSPINLOCK_SUCCESS);
  /* Check Schedule */
  status = Schedule();
  test_assert(status == E_OS_SPINLOCK);
  /* Check automatic Spinlocks Release */
}

ISR(isr_spin) {
  StatusType status;
  status = GetSpinlock(spinlock_1);
  test_assert(status == E_OS_INTERFERENCE_DEADLOCK);
  status = ReleaseSpinlock(spinlock_1);
  test_assert(status == E_OS_STATE);
  /* Check That The Spinlock Work */
  status = GetSpinlock(spinlock_3);
  test_assert(status == E_OK);
  ActivateTask(TaskSlave1);
  {
    EE_UINT32 volatile stop = 0U;
    while (++stop < TEST_WAIT)
      ;
  }
  test_assert(shared_slave1 == 0U);
  /* Check automatic Spinlocks Release */
}

void StartupHook( void ) {
  /*  THIS IS AN ORRIBLE HACK */
  /* Work around to let shared code be visible to untrusted OSApplications too */
  if ( GetCoreID() > OS_CORE_ID_MASTER ) {
    EE_UREG mask = EE_tc_get_csfr(EE_CPU_REG_DPRE_1);
    EE_tc_set_csfr(EE_CPU_REG_DPRE_1, mask | EE_BIT(7))
    mask = EE_tc_get_csfr(EE_CPU_REG_DPWE_1);
    EE_tc_set_csfr(EE_CPU_REG_DPWE_1, mask | EE_BIT(7))
  }
}

void ErrorHook( StatusType Error ) {
  OSServiceIdType service_id = OSErrorGetServiceId();
  test_as_errors[error_counter]   = Error;
  test_as_service_error[error_counter] = service_id;
  if(GetCoreID() != OS_CORE_ID_MASTER ) {
    /* This Should not never happen */
    EE_tc_debug();
  }
  switch (service_id) {
    case OSServiceId_GetSpinlock :
      test_as_param_error[error_counter] = OSError_GetSpinlock_SpinlockId();
      break;
    case OSServiceId_ReleaseSpinlock :
      test_as_param_error[error_counter] = OSError_ReleaseSpinlock_SpinlockId();
      break;
    case OSServiceId_TryToGetSpinlock :
      test_as_param_error[error_counter] = OSError_TryToGetSpinlock_SpinlockId();
      /* TODO_: I should add check for second param */
      break;
    case OSId_ISR2Body:
    case OSId_TaskBody:
    case OSServiceId_Schedule:
    case OSServiceId_WaitEvent:
    case OSServiceId_ChainTask:
    case OSServiceId_TerminateTask:
      /* I don't care of parameters */
    break;
    default:
      /* This should never happened */
      EE_tc_debug();
  }
  ++error_counter;
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType status;

  /* Enable and assign entry (priority) in INTTAB TOS is cpu0 */
  SRC_GPSR01.U = EE_TC2YX_SRN_ENABLE | EE_TC2YX_SRN_PRIORITY(
    EE_ISR2_ID_isr_spin);

  StartCore(OS_CORE_ID_1, &status);
  StartCore(OS_CORE_ID_2, &status);

  /* Errors: detected by service protection */
  status = GetSpinlock(spinlock_2);
  test_assert(status == E_OS_CALLEVEL );
  status = ReleaseSpinlock(2);
  test_assert(status == E_OS_CALLEVEL);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
