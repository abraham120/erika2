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

#include <ee.h>
#include <ee_irq.h>
#include "test/assert/inc/ee_assert.h"
#include "../../common/test_common.h"

#define TRUE  1U
#define FALSE 0U

/* assertion data */
#define MAX_ASSERT 15
/* Leave one position as guard */
EE_TYPEASSERTVALUE EE_assertions[MAX_ASSERT + 2];

DeclareTask(Task1);
DeclareTask(Task2);

TASK(Task1)
{
  TickType Value;
  /* 2° tick */
  IncrementCounter(Counter1); 
  /* 3° tick */
  IncrementCounter(Counter1);
  GetCounterValue(Counter1, &Value);
  /* I check that preemption happens in tasks */
  EE_assert(5, (Value == 4U), 4);
}

TASK(Task2)
{
  IncrementCounter(Counter1);
}

ISR2(isr_callback)
{
  TickType Value;
  ACK_IRQ(ISR_LOW); /* Needed by ppc */
  GetCounterValue(Counter1, &Value);
  IncrementCounter(Counter1);
  /* I check that preemption doesn't happen in IRQ */
  if(Value == 5U){
      GetCounterValue(Counter1, &Value);
      EE_assert(6, (Value == 6U), 5);
  }
}

#define NoCounter 1234

int main(int argc, char **argv)
{
  unsigned int counter;
  StatusType  s;
  TickType Value;
  TickType ElapsedValue;
#ifdef __CORTEX_MX__
  EE_system_init();
#endif
#ifdef EE_TRICORE__
  test_setup_irq(0U, isr_callback, EE_TC_1_ISR_PRI);
#endif

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  /* Setup and queue an interrupt request; StartOS() should enable IRQs, so
     the request is served */
  test_fire_irq(0U);

  StartOS(OSDEFAULTAPPMODE);

  s = GetCounterValue(NoCounter, &Value);
  EE_assert(2, (s == E_OS_ID) , 1);

  s = GetCounterValue(Counter1, &Value);
  EE_assert(3, (s == E_OK) , 2);
  EE_assert(4, (Value == 1U), 3);

  s = SetAbsAlarm(Alarm1, 3, 3);
  ActivateTask(Task1);

  IncrementCounter(Counter1);
  test_fire_irq(0U);

  /* Task 2 should be called before this */
  GetElapsedValue(Counter1, &Value, &ElapsedValue);
  EE_assert(7, (ElapsedValue == 6U), 6);

  s = GetElapsedValue(NoCounter, &Value, &ElapsedValue);
  EE_assert(8, (s == E_OS_ID), 7);

  /* I set an invalid value */
  Value = EE_counter_ROM[Counter1].maxallowedvalue + 1;
  s = GetElapsedValue(Counter1, &Value, &ElapsedValue);
  EE_assert(9, (s == E_OS_VALUE), 8);

  /* I cancel the alarm so I can control better counter increment for my last
     test */
  CancelAlarm(Alarm1);

  GetCounterValue(Counter1, &Value);

  while(Value++ <= EE_counter_ROM[Counter1].maxallowedvalue) {
    IncrementCounter(Counter1);
  }

  GetCounterValue(Counter1, &Value);

  EE_assert(10, (Value == 0U), 9);

  /* Test first counter wrap-around */
  GetCounterValue(Counter1, &Value);
  /* here Value is equal to zero */
  while(Value++ <= EE_counter_ROM[Counter1].maxallowedvalue/2) {
    IncrementCounter(Counter1);
  }
  GetCounterValue(Counter1, &Value);
  /* here Value is equal to maxallowedvalue/2=8 */
  while(Value++ <= EE_counter_ROM[Counter1].maxallowedvalue/2+4) {
    IncrementCounter(Counter1);
  }
  /* Value is equal to 4 because the timer wrap-around over 16 (max value) */
  GetCounterValue(Counter1, &Value);
  
  s = GetElapsedValue(Counter1, &Value, &ElapsedValue);
  /* Since current Value is equal to 4 and the old Value was
     maxallowedvalue/2=8, if everythings is gona be all right
     the ElapsedValue should be equal to 13 according with
     the formula of wrap-around case:
     ElapsedValue = MaxValue - (old_value - current_value) + 1 =
     = 16 -(8 - 4) + 1 = 13 */
  EE_assert(11, (Value == 13U), 10);

  /* Check set absolute alarm wrap around handling */
  s = SetAbsAlarm(Alarm1, (Value - 1), 0);
  EE_assert(12, (s == E_OK), 11);
  EE_assert(13,
    (EE_oo_counter_object_RAM[Alarm1].delta == EE_counter_ROM[Counter1].maxallowedvalue - 1U),
     12);
  CancelAlarm(Alarm1);

  /* Check set absolute alarm 'NOW' handling: that means next time counter has
     actual value*/
  s = SetAbsAlarm(Alarm1, Value, 0);
  EE_assert(14, (s == E_OK), 13);
  EE_assert(15,
   (EE_oo_counter_object_RAM[Alarm1].delta == EE_counter_ROM[Counter1].maxallowedvalue),
   14);

  EE_assert_range(0, 1, MAX_ASSERT);
  EE_assert_last();

  return 0;
}
