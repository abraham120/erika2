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
#include "ee.h"
#include "shared.h"

#define ASSERT_LENGTH 20U
EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];

static int assert_count = EE_ASSERT_NIL;

void EE_COMPILER_SECTION("ee_mcglobalt") test_assert ( int test )
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


EE_BIT volatile master_app_startup_flag;
EE_BIT volatile master_app_shutdown_flag;

#define SHARED_START_SEC_VAR_NOINIT
#include "MemMap.h"
EE_BIT volatile slave2_app_startup_flag;
EE_BIT volatile slave2_app_shutdown_flag;
#define SHARED_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

TASK(TaskMaster)
{
  /* First start Slave2 to give him more time to Shutdown indipendetly or
     give less time to TaskSlave1 to really start */
  ActivateTask( TaskSlave2 );

  ActivateTask( TaskSlave1 );

  /* Choice an error to check is value in other cores */
  ShutdownAllCores( E_OK );
}

ISR( STM0_isr2 ) {
  EE_tc2Yx_stm_set_sr0_next_match( EE_CPU_CLOCK / 1000U );
}

void StartupHook_MasterApplication( void )
{
  ++master_app_startup_flag;
}

void ShutdownHook_MasterApplication( StatusType Error )
{
  test_assert( Error == E_OK );
  ++master_app_shutdown_flag;
}

void StartupHook( void )
{
  CoreIdType current_core = GetCoreID();

  if( current_core == OS_CORE_ID_MASTER )
  {
    test_assert( master_app_startup_flag == 0U );
  } else if ( current_core == OS_CORE_ID_2 ) {
    test_assert( slave2_app_startup_flag == 0U );
  }
}

void ShutdownHook( StatusType Error )
{
  static EE_BIT slave1_shutdown, slave2_shutdown;

  CoreIdType current_core = GetCoreID();

if ( current_core == OS_CORE_ID_2 )
{
  test_assert( Error == E_OS_STATE );
} else {
  test_assert( Error == E_OK );
}
  if( current_core == OS_CORE_ID_MASTER )
  {
    test_assert( master_app_shutdown_flag == 1U );
    while( (slave1_shutdown && slave2_shutdown) == 0U)
      ;

    EE_assert_range(0U, 1U, assert_count);

    EE_assert_last();
 
  } else if  ( current_core == OS_CORE_ID_1 ) {
    slave1_shutdown = 1;
  } else if ( current_core == OS_CORE_ID_2 ) {
    test_assert( slave2_app_shutdown_flag == 1U );
    slave2_shutdown = 1;
  }
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType status;


  EE_tc2Yx_stm_set_sr0( EE_CPU_CLOCK / 1000U, EE_ISR2_ID_STM0_isr2);

  StartCore(OS_CORE_ID_1, &status);
  StartCore(OS_CORE_ID_2, &status);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
