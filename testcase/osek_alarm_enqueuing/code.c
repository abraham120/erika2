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

#include <ee.h>
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE  1U
#endif
#ifndef FALSE
#define FALSE 0U
#endif

enum EE_ASSERTION_TEST_1 {
  TEST_1_START,
  TEST_1_TICK1,
  TEST_1_ALARM1_CALLBACK1,
  TEST_1_TICK2,
  TEST_1_TICK3,
  TEST_1_ALARM1_CALLBACK2,
  TEST_1_TICK4,
  TEST_1_BEFORE_END = TEST_1_ALARM1_CALLBACK2,
  TEST_1_END        = TEST_1_TICK4,
  TEST_1_LENGTH
};

enum EE_ASSERTION_TEST_2 {
  TEST_2_START = TEST_1_LENGTH,
  TEST_2_ALARM1_CALLBACK1,
  TEST_2_ALARM2_CALLBACK1,
  TEST_2_TICK1,
  TEST_2_ALARM3_CALLBACK1,
  TEST_2_ALARM1_CALLBACK2,
  TEST_2_ALARM2_CALLBACK2,
  TEST_2_TICK2,
  TEST_2_ALARM1_QUEUE,
  TEST_2_ALARM2_QUEUE,
  TEST_2_ALARM3_QUEUE,
  TEST_2_BEFORE_END = TEST_2_ALARM2_QUEUE,
  TEST_2_END        = TEST_2_ALARM3_QUEUE,
  TEST_2_LENGTH
};

enum EE_ASSERTION_TEST_3 {
  TEST_3_START = TEST_2_LENGTH,
  TEST_3_ALARM1_CALLBACK1,
  TEST_3_ALARM2_CALLBACK1,
  TEST_3_ALARM3_CALLBACK1,
  TEST_3_TICK1,
  TEST_3_ALARM3_CALLBACK2,
  TEST_3_TICK2,
  TEST_3_ALARM2_CALLBACK2,
  TEST_3_ALARM3_CALLBACK3,
  TEST_3_TICK3,
  TEST_3_ALARM1_CALLBACK2,
  TEST_3_ALARM3_CALLBACK4,
  TEST_3_TICK4,
  TEST_3_ALARM2_QUEUE,
  TEST_3_ALARM3_QUEUE,
  TEST_3_ALARM1_QUEUE,
  TEST_3_ALARM2_DELTA,
  TEST_3_ALARM3_DELTA,
  TEST_3_ALARM1_DELTA,
  TEST_3_BEFORE_END = TEST_3_ALARM2_DELTA,
  TEST_3_END        = TEST_3_ALARM1_DELTA,
  TEST_3_LENGTH
};

enum EE_ASSERTION_TEST_4 {
  TEST_4_START = TEST_3_LENGTH,
  TEST_4_TICK1,
  TEST_4_STARTALARM1,
  TEST_4_COUNTERVALUE,
  TEST_4_ALARM1_CALLBACK1,
  TEST_4_ELAPSEDVALUE,
  TEST_4_BEFORE_END = TEST_4_ALARM1_CALLBACK1,
  TEST_4_END        = TEST_4_ELAPSEDVALUE,
  TEST_4_LENGTH
};

#define EE_ASSERTION_LENGTH TEST_4_LENGTH

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERTION_LENGTH];

DeclareTask(TestTask);

static void test1(void) {
  StatusType s;
  s = SetRelAlarm(Test1Alarm1, 2, 2);
  EE_assert(TEST_1_START, (s == E_OK), EE_ASSERT_NIL);
  s = IncrementCounter(Counter);
  EE_assert(TEST_1_TICK1, (s == E_OK), TEST_1_START);
  s = IncrementCounter(Counter);
  EE_assert(TEST_1_TICK2, (s == E_OK), TEST_1_ALARM1_CALLBACK1);
  s = IncrementCounter(Counter);
  EE_assert(TEST_1_TICK3, (s == E_OK), TEST_1_TICK2);
  s = IncrementCounter(Counter);
  EE_assert(TEST_1_TICK4, (s == E_OK), TEST_1_ALARM1_CALLBACK2);
  s = CancelAlarm(Test1Alarm1);
}

void test1_alarm1_callback(void) {
  static EE_UREG test1_alarm1_callback_hits = 0U;

  if( test1_alarm1_callback_hits == 0U ) {
    EE_assert(TEST_1_ALARM1_CALLBACK1,
      EE_counter_RAM[Counter].value == 2U,
      TEST_1_TICK1
    );
  } else if ( test1_alarm1_callback_hits == 1U ) {
    EE_assert(TEST_1_ALARM1_CALLBACK2,
      EE_counter_RAM[Counter].value == 4U,
      TEST_1_TICK3
    );
  } else {
    EE_assert(TEST_1_END, FALSE, TEST_1_BEFORE_END);
  }

  ++test1_alarm1_callback_hits;
}

static void test2(void) {
  StatusType s;
  
  /* Test set-up */
  SetRelAlarm(Test2Alarm1, 1, 1);
  SetRelAlarm(Test2Alarm2, 1, 1);
  s = SetRelAlarm(Test2Alarm3, 2, 2);

  EE_assert(TEST_2_START, (s == E_OK), TEST_1_END);
  s = IncrementCounter(Counter);
  EE_assert(TEST_2_TICK1, (s == E_OK), TEST_2_START);
  s = IncrementCounter(Counter);
  EE_assert(TEST_2_TICK2, (s == E_OK), TEST_2_ALARM2_CALLBACK1);

  EE_assert(TEST_2_ALARM1_QUEUE,
    (EE_counter_RAM[Counter].first == Test2Alarm1),
    TEST_2_TICK2);
  EE_assert(TEST_2_ALARM2_QUEUE,
    (EE_alarm_RAM[Test2Alarm1].next == Test2Alarm2),
    TEST_2_ALARM1_QUEUE);
  EE_assert(TEST_2_ALARM3_QUEUE,
    (EE_alarm_RAM[Test2Alarm2].next == Test2Alarm3),
    TEST_2_ALARM2_QUEUE);

  /* Test Clean-up */
  CancelAlarm(Test2Alarm1);
  CancelAlarm(Test2Alarm2);
  CancelAlarm(Test2Alarm3);
}

void test2_alarm1_callback(void) {
  static EE_UREG test2_alarm1_callback_hits = 0U;

  if( test2_alarm1_callback_hits == 0U ) {
    EE_assert(TEST_2_ALARM1_CALLBACK1, TRUE, TEST_2_START);
  } else if ( test2_alarm1_callback_hits == 1U ) {
    EE_assert(TEST_2_ALARM1_CALLBACK2, TRUE, TEST_2_ALARM3_CALLBACK1);
  } else {
    EE_assert(TEST_2_END, FALSE, TEST_2_BEFORE_END);
  }
  ++test2_alarm1_callback_hits;
}

void test2_alarm2_callback(void) {
  static EE_UREG test2_alarm2_callback_hits = 0U;
  if( test2_alarm2_callback_hits == 0U ) {
    EE_assert(TEST_2_ALARM2_CALLBACK1, TRUE, TEST_2_ALARM1_CALLBACK1);
  } else if ( test2_alarm2_callback_hits == 1U ) {
    EE_assert(TEST_2_ALARM2_CALLBACK2, TRUE, TEST_2_ALARM1_CALLBACK2);
  } else {
    EE_assert(TEST_2_END, FALSE, TEST_2_BEFORE_END);
  }
  ++test2_alarm2_callback_hits;
}

void test2_alarm3_callback(void) {
  static EE_UREG test2_alarm3_callback_hits = 0U;
  if( test2_alarm3_callback_hits == 0U ) {
    EE_assert(TEST_2_ALARM3_CALLBACK1, TRUE, TEST_2_TICK1);
  } else {
    EE_assert(TEST_2_END, FALSE, TEST_2_BEFORE_END);
  }
  ++test2_alarm3_callback_hits;
}

static void test3(void) {
  StatusType s;
  /* Test set-up */
  SetRelAlarm(Test3Alarm1, 1, 3);
  SetRelAlarm(Test3Alarm2, 1, 2);
  s = SetRelAlarm(Test3Alarm3, 1, 1);

  EE_assert(TEST_3_START, (s == E_OK), TEST_2_END);
  s = IncrementCounter(Counter);
  EE_assert(TEST_3_TICK1, (s == E_OK), TEST_3_ALARM3_CALLBACK1);
  s = IncrementCounter(Counter);
  EE_assert(TEST_3_TICK2, (s == E_OK), TEST_3_ALARM3_CALLBACK2);
  s = IncrementCounter(Counter);
  EE_assert(TEST_3_TICK3, (s == E_OK), TEST_3_ALARM3_CALLBACK3);
  s = IncrementCounter(Counter);
  EE_assert(TEST_3_TICK4, (s == E_OK), TEST_3_ALARM3_CALLBACK4);

  EE_assert(TEST_3_ALARM2_QUEUE,
    (EE_counter_RAM[Counter].first == Test3Alarm2),
    TEST_3_TICK4);
  EE_assert(TEST_3_ALARM3_QUEUE,
    (EE_alarm_RAM[Test3Alarm2].next == Test3Alarm3),
    TEST_3_ALARM2_QUEUE);
  EE_assert(TEST_3_ALARM1_QUEUE,
    (EE_alarm_RAM[Test3Alarm3].next == Test3Alarm1),
    TEST_3_ALARM3_QUEUE);

  EE_assert(TEST_3_ALARM2_DELTA,
    (EE_alarm_RAM[Test3Alarm2].delta == 0U),
    TEST_3_ALARM1_QUEUE);
  EE_assert(TEST_3_ALARM3_DELTA,
    (EE_alarm_RAM[Test3Alarm3].delta == 0U),
    TEST_3_ALARM2_DELTA);
  EE_assert(TEST_3_ALARM1_DELTA,
    (EE_alarm_RAM[Test3Alarm1].delta == 2U),
    TEST_3_ALARM3_DELTA);

  /* Test Clean-up */
  CancelAlarm(Test3Alarm1);
  CancelAlarm(Test3Alarm2);
  CancelAlarm(Test3Alarm3);
}

void test3_alarm1_callback(void) {
  static EE_UREG test3_alarm1_callback_hits = 0U;

  if( test3_alarm1_callback_hits == 0U ) {
    EE_assert(TEST_3_ALARM1_CALLBACK1, TRUE, TEST_3_START);
  } else if ( test3_alarm1_callback_hits == 1U ) {
    EE_assert(TEST_3_ALARM1_CALLBACK2, TRUE, TEST_3_TICK3);
  } else {
    EE_assert(TEST_3_END, FALSE, TEST_3_BEFORE_END);
  }
  ++test3_alarm1_callback_hits;
}

void test3_alarm2_callback(void) {
  static EE_UREG test3_alarm2_callback_hits = 0U;
  if( test3_alarm2_callback_hits == 0U ) {
    EE_assert(TEST_3_ALARM2_CALLBACK1, TRUE, TEST_3_ALARM1_CALLBACK1);
  } else if ( test3_alarm2_callback_hits == 1U ) {
    EE_assert(TEST_3_ALARM2_CALLBACK2, TRUE, TEST_3_TICK2);
  } else {
    EE_assert(TEST_3_END, FALSE, TEST_3_BEFORE_END);
  }
  ++test3_alarm2_callback_hits;
}

void test3_alarm3_callback(void) {
  static EE_UREG test3_alarm3_callback_hits = 0U;
  if( test3_alarm3_callback_hits == 0U ) {
    EE_assert(TEST_3_ALARM3_CALLBACK1, TRUE, TEST_3_ALARM2_CALLBACK1);
  } else if ( test3_alarm3_callback_hits == 1U ) {
    EE_assert(TEST_3_ALARM3_CALLBACK2, TRUE, TEST_3_TICK1);
  } else if ( test3_alarm3_callback_hits == 2U ) {
    EE_assert(TEST_3_ALARM3_CALLBACK3, TRUE, TEST_3_ALARM2_CALLBACK2);
  } else if ( test3_alarm3_callback_hits == 3U ) {
    EE_assert(TEST_3_ALARM3_CALLBACK4, TRUE, TEST_3_ALARM1_CALLBACK2);
  } else {
    EE_assert(TEST_3_END, FALSE, TEST_3_BEFORE_END);
  }
  ++test3_alarm3_callback_hits;
}

static void test4(void) {
  StatusType s;
  TickType counter_value;
  EE_UREG i;
  EE_UREG ticks_to_wrap_around;

  EE_assert(TEST_4_START, TRUE, TEST_3_END);
  s = IncrementCounter(Counter);
  EE_assert(TEST_4_TICK1, (s == E_OK), TEST_4_START);
  s = SetAbsAlarm(Test4Alarm1, 0, 0);
  EE_assert(TEST_4_STARTALARM1, (s == E_OK), TEST_4_TICK1);
  s = GetCounterValue(Counter, &counter_value);
  EE_assert(TEST_4_COUNTERVALUE, (s == E_OK), TEST_4_STARTALARM1);

  ticks_to_wrap_around = EE_counter_ROM[Counter].maxallowedvalue - counter_value
    + 1U;

  for (i = 0U; i < ticks_to_wrap_around; ++i) {
    IncrementCounter(Counter);
  }
  /* Un po' tirato per i capelli ma è una prova che voglio fare: usare la stessa
     variable per Value e ElapsedValue */
  s = GetElapsedValue(Counter, &counter_value, &counter_value);
  EE_assert(TEST_4_ELAPSEDVALUE, (counter_value == ticks_to_wrap_around),
      TEST_4_ALARM1_CALLBACK1);

}

void test4_alarm1_callback(void) {
  static EE_UREG test4_alarm1_callback_hits = 0U;
  if( test4_alarm1_callback_hits == 0U ) {
    EE_assert(TEST_4_ALARM1_CALLBACK1, TRUE, TEST_4_COUNTERVALUE);
  } else {
    EE_assert(TEST_4_END, TRUE, TEST_4_BEFORE_END);
  }
  ++test4_alarm1_callback_hits;
}

TASK(TestTask)
{
  test1();
  test2();
  test3();
  test4();

  TerminateTask();
}

int main(int argc, char *argv[])
{
  StartOS(OSDEFAULTAPPMODE);

  EE_assert_range(0, 1, (EE_ASSERTION_LENGTH - 1U));

  EE_assert_last();

  return 0;
}
