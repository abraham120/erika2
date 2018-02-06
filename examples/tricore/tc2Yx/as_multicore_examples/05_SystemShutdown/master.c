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
/* I need some internal to keep the things easy */
#include "ee_internal.h"

#define ASSERT_LENGTH 20U
EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];

static int assert_count = EE_ASSERT_NIL;
void EE_COMPILER_SECTION("ee_mcglobalt") test_assert (int test )
{
  register int next_assert;
  /* Shared I need critical section I reuse CORE 0 Spinlock */
  EE_TYPESPIN spinlock_id = EE_as_core_spinlocks[OS_CORE_ID_MASTER];
  EE_hal_spin_in( spinlock_id );
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
  EE_hal_spin_out( spinlock_id );
}

TASK(TaskMaster)
{
  /* Test Unordered spinlocks */
  StatusType status = GetSpinlock( spinlock_1 );
  test_assert( status == E_OK );
  status = GetSpinlock( spinlock_2 );
  test_assert( status == E_OS_NESTING_DEADLOCK );
  status = ReleaseSpinlock( spinlock_1 );
  test_assert( status == E_OK );

  /* First start Slave2 to give him more time to Shutdown indipendetly or
     give less time to TaskSlave1 to really start */
  ActivateTask( TaskSlave2 );

  ActivateTask( TaskSlave1 );

/* Check Error Parameter ( check slave2 code/comments for more infos) */
#ifdef EE_SHUTDOWN_ALL_CORES_FROM_CORE2
  TerminateTask();
#else /* EE_SHUTDOWN_ALL_CORES_FROM_CORE2 */
  /* Choice an error to check is value in other cores */
  ShutdownAllCores( E_OS_STATE );
#endif /* EE_SHUTDOWN_ALL_CORES_FROM_CORE2 */
}

void ShutdownHook( StatusType Error )
{
  static EE_BIT volatile shutdown_flag_core0;
  static EE_BIT volatile shutdown_flag_core2;
  static EE_BIT volatile shutdown_flag_core1;

  CoreIdType current_core = GetCoreID();

/* Check Error Parameter ( check slave2 code/comments for more infos) */
#ifdef EE_SHUTDOWN_ALL_CORES_FROM_CORE2
    test_assert( Error == E_OS_ID );
#else /* EE_SHUTDOWN_ALL_CORES_FROM_CORE2 */
    test_assert( Error == E_OS_STATE );
#endif /* EE_SHUTDOWN_ALL_CORES_FROM_CORE2 */

  if( current_core == OS_CORE_ID_2 )
  {
#ifndef EE_SHUTDOWN_ALL_CORES_FROM_CORE2
    if ( (shutdown_flag_core0 != 0U) || (shutdown_flag_core1 != 0U) )
      test_assert( FALSE );
#endif /* !EE_SHUTDOWN_ALL_CORES_FROM_CORE2 */

    /* Check automatic spinlock release */
#ifdef EE_QUEUEING_SPINLOCKS
    test_assert(
      EE_TC_LOCK_WHAT_MEANS_LOCKED( EE_hal_spinlock_status[spinlock_2] ) !=
        EE_hal_spinlock_value[spinlock_2][OS_CORE_ID_2] );
#else /* EE_QUEUEING_SPINLOCKS */
    test_assert( EE_hal_spinlock_status[spinlock_2] == 0U );
#endif /* EE_QUEUEING_SPINLOCKS */

    test_assert( EE_as_spinlocks_locker_core[spinlock_2] ==
      INVALID_CORE_ID );

    shutdown_flag_core2 = 1U;
  } else if ( current_core == OS_CORE_ID_1 ) {

    shutdown_flag_core1 = 1U;
  } else if ( current_core == OS_CORE_ID_MASTER ) {

    shutdown_flag_core0 = 1U;
    while ( (shutdown_flag_core1 && shutdown_flag_core2) == 0U )
      ; /* wait all other cores */

    EE_assert_range(0U, 1U, assert_count);

    EE_assert_last();
  } else {
    /* Unknown core ID */
    test_assert( FALSE );
  }
}

void PreTaskHook( void )
{
  /* Nothing TODO here */
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
