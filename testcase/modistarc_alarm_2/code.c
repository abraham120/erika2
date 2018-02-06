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
#define FALSE 0

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[18];

DeclareTask(Task1);
DeclareTask(Task2);

TASK(Task1)
{
  StatusType s;
  AlarmBaseType AlarmBase;
  TickType Tick;

  EE_assert(1, TRUE, EE_ASSERT_NIL);

#ifdef __OO_EXTENDED_STATUS__
  s = GetAlarmBase(Alarm1, &AlarmBase);
  EE_assert(2, (s==E_OK), 1);
#else
  GetAlarmBase(Alarm1, &AlarmBase);
  EE_assert(2, TRUE, 1);
#endif

  s = GetAlarm(Alarm1, &Tick);
  EE_assert(3, (s==E_OS_NOFUNC), 2);

  s = CancelAlarm(Alarm1);
  EE_assert(4, (s==E_OS_NOFUNC), 3);

  // initializealarmcounter (actually not provided by our interface
  EE_assert(5, TRUE, 4);

  s = SetAbsAlarm(Alarm1,1,1);
  EE_assert(6, (s==E_OK), 5);

  s = SetAbsAlarm(Alarm1, 3, 0);
  EE_assert(7, (s==E_OS_STATE), 6);

#ifdef __OO_EXTENDED_STATUS__
  s =   IncrementCounter(Counter1);
  EE_assert(9, (s==E_OK), 8);
#else
  IncrementCounter(Counter1);
  EE_assert(9, (TRUE), 8);
#endif

#ifdef __OO_EXTENDED_STATUS__
  s = IncrementCounter(Counter1);
  EE_assert(11, (s==E_OK), 10);
#else
  IncrementCounter(Counter1);
  EE_assert(11, (TRUE), 10);
#endif
  
  s = CancelAlarm(Alarm1);
  EE_assert(12, (s==E_OK), 11);

  s = SetRelAlarm(Alarm1, 1, 0);
  EE_assert(13, (s==E_OK), 12);

  s = SetRelAlarm(Alarm1, 2, 0);
  EE_assert(14, (s==E_OS_STATE), 13);

  s = GetAlarm(Alarm1, &Tick);
  EE_assert(15, (s==E_OK && Tick==1), 14);

#ifdef __OO_EXTENDED_STATUS__
  s = IncrementCounter(Counter1);
  EE_assert(17, (s==E_OK), 16);
#else
  IncrementCounter(Counter1);
  EE_assert(17, (TRUE), 16);
#endif

  TerminateTask();
}

int task2_i = 0;
TASK(Task2)
{
  switch (task2_i) {
  case 0:
    EE_assert(8, TRUE, 7);
    break;
  case 1:
    EE_assert(10, TRUE, 9);
    break;
  case 2:
    EE_assert(16, TRUE, 15);
    break;
  default:
    EE_assert(0, 0, 0);
  }

  task2_i++;

  TerminateTask();
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

  EE_assert_range(0,1, 17);
  EE_assert_last();

  return 0;
}

#ifdef __JANUS__
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}
#endif
