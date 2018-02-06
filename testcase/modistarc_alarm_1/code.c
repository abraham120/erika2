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

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[18];

DeclareTask(Task1);
DeclareTask(Task2);

#define NoAlarm 1234

TASK(Task1)
{
  StatusType s;
  TickType Tick;
  AlarmBaseType AlarmBase;

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  s = GetAlarmBase(NoAlarm, &AlarmBase);
  EE_assert(2, (s==E_OS_ID), 1);

  s = GetAlarm(NoAlarm, &Tick);
  EE_assert(3, (s==E_OS_ID), 2);

  s = GetAlarmBase(Alarm1, &AlarmBase);
  EE_assert(4, (s==E_OK), 3);

  s = SetRelAlarm(NoAlarm, 0, 0);
  EE_assert(5, (s==E_OS_ID), 4);

  s = SetRelAlarm(Alarm1, -1, 0);
  EE_assert(6, (s==E_OS_VALUE), 5);

  s = SetRelAlarm(Alarm1, AlarmBase.maxallowedvalue+1, 0);
  EE_assert(7, (s==E_OS_VALUE), 6);

  s = SetRelAlarm(Alarm1, 1, AlarmBase.mincycle-1);
  EE_assert(8, (s==E_OS_VALUE), 7);

  s = SetRelAlarm(Alarm1, 1, AlarmBase.maxallowedvalue+1);
  EE_assert(9, (s==E_OS_VALUE), 8);

  s = SetAbsAlarm(NoAlarm, 0, 0);
  EE_assert(10, (s==E_OS_ID), 9);

  s = SetAbsAlarm(Alarm1, -1, 0);
  EE_assert(11, (s==E_OS_VALUE), 10);

  s = SetAbsAlarm(Alarm1, AlarmBase.maxallowedvalue+1, 0);
  EE_assert(12, (s==E_OS_VALUE), 11);

  s = SetAbsAlarm(Alarm1, 0, AlarmBase.mincycle-1);
  EE_assert(13, (s==E_OS_VALUE), 12);

  s = SetAbsAlarm(Alarm1, 0, AlarmBase.maxallowedvalue+1);
  EE_assert(14, (s==E_OS_VALUE), 13);

  s = CancelAlarm(NoAlarm);
  EE_assert(15, (s==E_OS_ID), 14);

  /*AS OS304: If in a call to SetRelAlarm() the parameter “increment” is set to
    zero, the service shall return E_OS_VALUE in standard and extended status.
  */
  s = SetRelAlarm(Alarm1, 0, AlarmBase.mincycle);
  EE_assert(16, (s==E_OS_VALUE), 15);

  s = CancelAlarm(Alarm1);
  EE_assert(17, (s==E_OS_NOFUNC), 16);

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

  EE_assert_range(0,1,17);
  EE_assert_last();

  return 0;
}

#ifdef __JANUS__
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}
#endif

