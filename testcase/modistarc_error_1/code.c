/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
#include "test/assert/inc/ee_assert.h"

#define TRUE 1

#ifdef __OO_EXTENDED_STATUS__
#define S_equal s =
#define S_ok    s == E_OK &&
#else
#define S_equal
#define S_ok
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[32];

DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);

TASK(Task1)
{
  StatusType s;

  EE_assert(7, (TRUE), 6);

  s = ActivateTask(Task2);
  EE_assert(27, (s==E_OK), 26);

  TerminateTask();
}

int task2_i = 0;
TASK(Task2)
{
  StatusType s;
  TickType Tick;

  EE_assert(16, TRUE, 15);

  s = GetAlarm(Alarm1, &Tick);
  EE_assert(18, (s==E_OS_NOFUNC), 17);

  TerminateTask();
}

void StartupHook(void)
{
  EE_assert(1, (TRUE), -1);
  ActivateTask(Task1);
  EE_assert(2, (TRUE), 1);
}

int precounter=0;
void PreTaskHook(void)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  TaskType TaskID;
  TaskStateType TaskState;

  switch (precounter) {
  case 0:

    EE_assert(3, (TRUE), 2);
    
    GetTaskID(&TaskID);
    EE_assert(4, (TaskID==Task1), 3);

    S_equal GetTaskState(Task1, &TaskState);
    EE_assert(5, (S_ok TaskState==RUNNING), 4);

    S_equal GetTaskState(Task2, &TaskState);
    EE_assert(6, (S_ok TaskState==SUSPENDED), 5);
    
    break;
  case 1:
    EE_assert(12, (TRUE), 11);
    
    GetTaskID(&TaskID);
    EE_assert(13, (TaskID==Task2), 12);

    S_equal GetTaskState(Task1, &TaskState);
    EE_assert(14, (S_ok TaskState==READY), 13);

    S_equal GetTaskState(Task2, &TaskState);
    EE_assert(15, (S_ok TaskState==RUNNING), 14);
    
    break;
  case 2:
    EE_assert(23, (TRUE), 22);
    
    GetTaskID(&TaskID);
    EE_assert(24, (TaskID==Task1), 23);

    S_equal GetTaskState(Task1, &TaskState);
    EE_assert(25, (S_ok TaskState==RUNNING), 24);

    S_equal GetTaskState(Task2, &TaskState);
    EE_assert(26, (S_ok TaskState==SUSPENDED), 25);
    
    break;
  default:
    EE_assert(0,0,0);
    break;
  }
  precounter++;
}

int postcounter=0;
void PostTaskHook(void)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  TaskType TaskID;
  TaskStateType TaskState;

  switch (postcounter) {
  case 0:
    EE_assert(8, (TRUE), 7);
    
    GetTaskID(&TaskID);
    EE_assert(9, (TaskID==Task1), 8);

    S_equal GetTaskState(Task1, &TaskState);
    EE_assert(10, (S_ok TaskState==RUNNING), 9);

    S_equal GetTaskState(Task2, &TaskState);
    EE_assert(11, (S_ok TaskState==READY), 10);

    break;
  case 1:
    EE_assert(19, (TRUE), 18);
    
    GetTaskID(&TaskID);
    EE_assert(20, (TaskID==Task2), 19);

    S_equal GetTaskState(Task1, &TaskState);
    EE_assert(21, (S_ok TaskState==READY), 20);

    S_equal GetTaskState(Task2, &TaskState);
    EE_assert(22, (S_ok TaskState==RUNNING), 21);
    break;
  case 2:
    EE_assert(28, (TRUE), 27);
    
    GetTaskID(&TaskID);
    EE_assert(29, (TaskID==Task1), 28);

    S_equal GetTaskState(Task1, &TaskState);
    EE_assert(30, (S_ok TaskState==RUNNING), 29);

    S_equal GetTaskState(Task2, &TaskState);
    EE_assert(31, (S_ok TaskState==SUSPENDED),30);

    break;
  default:
    EE_assert(0,0,0);
    break;
  }
  postcounter++;
}

void ErrorHook(StatusType Error)
{
  /* This trick will filter the first error generated in StartupHook */
  if ( Error != E_OS_CALLEVEL ) {
    EE_assert(17, TRUE, 16);
  }
}

int main(int argc, char **argv)
{
#if defined(__ARM7GNU__) && defined(__JANUS__)
  EE_janus_IRQ_enable_EIC();
#endif

#if defined(__CORTEX_MX__)
  /*Initializes Erika related stuffs*/
  EE_system_init();
#endif

  StartOS(OSDEFAULTAPPMODE);

  EE_assert_range(0,1,31);
  EE_assert_last();

  return 0;
}

#ifdef __JANUS__
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}
#endif
