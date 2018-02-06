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

EE_TYPEASSERTVALUE EE_SHARED_UDATA EE_assertions[ASSERT_LENGTH];

static int assert_count = EE_ASSERT_NIL;
void EE_COMPILER_SECTION("ee_mcglobalt") test_assert(int test)
{
  register int next_assert;
  EE_tc_spin_in(EE_SPINLOCK_CORE0);
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, assert_count);
  assert_count = next_assert;
  EE_tc_spin_out(EE_SPINLOCK_CORE0);
}

static EE_UINT8 volatile cores;

#ifndef TEST_ERROR_CONF
#define CORES_MASK 7U
static const AppModeType test_os_application_mode[] = {DONOTCARE, DONOTCARE,
  DONOTCARE};
#else /* TEST_ERROR_CONF */
#define CORES_MASK 3U
#ifndef TEST_SLAVE1_APPMODE
#define TEST_SLAVE1_APPMODE OSDEFAULTAPPMODE
#endif
static const AppModeType test_os_application_mode[] = {OSDEFAULTAPPMODE,
  TEST_SLAVE1_APPMODE};
#endif /* TEST_ERROR_CONF */


TASK(TaskMaster)
{
  StatusType start_core_status;
  StartCore(OS_CORE_ID_1, &start_core_status);
  test_assert(start_core_status == E_OS_ACCESS);
  StartNonAutosarCore(OS_CORE_ID_1, &start_core_status);
  test_assert(start_core_status == E_OS_STATE);

  /* Checking cores is sure because imposed synchronization first scheduling */
  test_assert(cores == CORES_MASK);
  test_assert(GetActiveApplicationMode() == OSDEFAULTAPPMODE);

  EE_assert_range(0, 1, assert_count); 

  EE_assert_last();
}

void StartupHook( void ) {
  /* With this trick I can check if all the three cores enter here only once */
  cores += ( 1U << GetCoreID() );
  if ( cores == CORES_MASK) {
    extern AppModeType volatile EE_as_os_application_mode[];
    register EE_UINT32 i;
    register EE_BIT donotcare_test = 1;
    for ( i=0; i < GetNumberOfActivatedCores(); ++i ) {
      donotcare_test &= (EE_as_os_application_mode[i] ==
        test_os_application_mode[i]);
    }
    test_assert(donotcare_test);
  }
}

void ShutdownHook( StatusType Error ) {
  /* I will not test shutdown procedure here */
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType start_core_status;
#ifndef TEST_ERROR_CONF
  test_assert(GetCoreID() == OS_CORE_ID_MASTER);
  test_assert(GetNumberOfActivatedCores() == 1);

  StartCore(OS_CORE_ID_1, &start_core_status);
  test_assert(start_core_status == E_OK);
  test_assert(GetNumberOfActivatedCores() == 2);

  StartCore((CoreIdType)4, &start_core_status);
  test_assert(start_core_status == E_OS_ID);

  StartCore(OS_CORE_ID_2, &start_core_status);
  test_assert(start_core_status == E_OK);
  test_assert(GetNumberOfActivatedCores() == 3);

  StartNonAutosarCore((CoreIdType)4, &start_core_status);
  test_assert(start_core_status == E_OS_ID);

  StartCore(OS_CORE_ID_MASTER, &start_core_status);
  test_assert(start_core_status == E_OS_STATE);

  StartNonAutosarCore(OS_CORE_ID_1, &start_core_status);
  test_assert(start_core_status == E_OS_STATE);


  StartOS(DONOTCARE);
#else /*  TEST_ERROR_CONF */
  test_assert(GetCoreID() == OS_CORE_ID_MASTER);
  test_assert(GetNumberOfActivatedCores() == 1);

  StartCore(OS_CORE_ID_1, &start_core_status);
  test_assert(start_core_status == E_OK);
  test_assert(GetNumberOfActivatedCores() == 2);

  StartCore(4, &start_core_status);
  test_assert(start_core_status == E_OS_ID);

  StartNonAutosarCore(OS_CORE_ID_2, &start_core_status);
  test_assert(start_core_status == E_OK);
  test_assert(GetNumberOfActivatedCores() == 2);

  StartNonAutosarCore(4, &start_core_status);
  test_assert(start_core_status == E_OS_ID);

  StartNonAutosarCore(OS_CORE_ID_2, &start_core_status);
  test_assert(start_core_status == E_OS_STATE);
  StartOS(OSDEFAULTAPPMODE);
#endif /* TEST_ERROR_CONF */
}
