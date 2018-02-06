/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * A minimal EE demo that demonstrates how to work with the MULTISTACK mode and
 * semaphores.
 * In this demo is shown that a task can be interrupted with a call to
 * ready2stacked (with an activation of a high priority task) and resumed with a
 * call to stkchange (if the high priority task is blocked on a shared
 * resource).
 * Author: 2012 Carlo Caione
 * Based on examples\cortex_mx\lpc12xx\porting_examples\multistack\EEtest6
 */


#include "ee.h"
#include "test/assert/inc/ee_assert.h"
#include "kernel/sem/inc/ee_sem.h"

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

void STM_EVAL_LEDOff(int led) {
  if ( led < LEDn ) {
    leds[led] = 0;
  }
}

void STM_EVAL_LEDOn(int led) {
  if ( led < LEDn ) {
    leds[led] = 1;
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
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_POST,
  EE_ASSERT_TASK2_ENDED,
  EE_ASSERT_TASK1_ENDED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* This semaphore is initialized inside the Background Task */
SemType V;

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int counter = 0;

/*
 * TASK 1
 */
TASK(Task1)
{

  int i;

  task1_fired++;
  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_INIT);
  }

  STM_EVAL_LEDOn(LED3);

  ActivateTask(Task2);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_POST, task1_fired == 1, EE_ASSERT_TASK2_FIRED);
  }

  for (i = 0; i < 100000; i++) {
    ;
  }

  PostSem(&V);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_ENDED, task1_fired == 1, EE_ASSERT_TASK2_ENDED);
  }
  task1_ended++;

}

/*
 * TASK 2
 */
TASK(Task2)
{

  int i;

  task2_fired++;
  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

  WaitSem(&V);

  for (i = 0; i < 100000; i++) {
    ;
  }

  STM_EVAL_LEDOff(LED3);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_ENDED, task2_fired == 1, EE_ASSERT_TASK1_POST);
  }
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
  EE_system_init(); 

  STM_EVAL_LEDInit(LED3);

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  /* Initialization of the second semaphore of the example;
   * the first semaphore is initialized inside the definition */
  InitSem(V, 0);

  ActivateTask(Task1);

  EE_assert(
    EE_ASSERT_TASKS_ENDED, task1_ended && task2_ended, EE_ASSERT_TASK1_ENDED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    while (counter % 10000) counter++;
    ActivateTask(Task1);
    counter++;

  }

}

