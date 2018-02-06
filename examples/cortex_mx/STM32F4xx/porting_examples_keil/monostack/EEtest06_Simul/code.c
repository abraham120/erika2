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

/*
 * A minimal EE demo that demostrates how the Erika BCC1 mode works.
 * This demo can be used to test Erika BCC1 files compilation, kernel start
 * procedure (StartOS(...)) and task termination (EE_s12xs_terminate_task(:::)).
 * Author: 2012 Carlo Caione
 * Based on examples\cortex_mx\lpc12xx\porting_examples\monostack\EEtest6
 */


#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#ifdef	__SIMUL__
#define	LEDn	0x04U

typedef enum 
{
  LED4 = 0,
  LED3 = 1,
  LED5 = 2,
  LED6 = 3
} Led_TypeDef;

volatile unsigned int leds[LEDn];

void STM_EVAL_LEDInit(unsigned int led) {
  if ( led < LEDn ) {
    leds[led] = 0;
  }
}

void STM_EVAL_LEDToggle(int led) {
  if ( led < LEDn ) {
    if (leds[led] == 0) {
      leds[led] = 1;
    }
    else {
      leds[led] = 0;
    }
  }
}

#else
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#endif

#ifndef	TRUE
#define	TRUE	0x01U
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Functions */
int func5(void)
{
	TerminateTask();
	return 1;
}

int func4(void)
{
	return func5();
}

int func3(void)
{
	return func4();
}


int func2(void)
{
	return func3();
}

int func1(void)
{
	return func2();
}

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int counter = 0;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{

  isr1_fired++;

  ActivateTask(Task2);

}

/*
 * TASK 1
 */
TASK(Task1)
{

  task1_fired++;
  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TASK2_FIRED);
  }

  STM_EVAL_LEDToggle(LED3);

  /* TerminateTask(); -> Forgetfulness Test!!!	*/
  /* task1_ended++;				*/

}

/*
 * TASK 2
 */
TASK(Task2)
{

  task2_fired++;
  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_INIT);
  }

  ActivateTask(Task1);

  func1();

  task2_ended++;

}

/*
 * MAIN TASK
 */
int main(void)
{
#ifndef	__SIMUL__
  SystemInit();
#endif

  /*Initializes Erika related stuffs*/
  /* EE_system_init(); -> Done inside StartOS() */

  STM_EVAL_LEDInit(LED3);

  EE_systick_set_period(1000000);
  EE_systick_enable_int();

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  StartOS(OSDEFAULTAPPMODE);

  EE_assert(
    EE_ASSERT_TASKS_ENDED, !task1_ended && !task2_ended, EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  if (result == 1) {
    EE_systick_start();
  }

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    counter++;

  }

}
