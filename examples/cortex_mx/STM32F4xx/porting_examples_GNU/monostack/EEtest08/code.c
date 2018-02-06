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
 * A minimal EE demo to test the scheduler behaviour in presence of shared
 * resources.
 * Author: 2012 Carlo Caione
 * Based on examples\cortex_mx\lpc12xx\porting_examples\monostack\EEtest8
 */

#include "ee.h"
#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef	TRUE
#define	TRUE	0x01U
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TIMER_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK1_GETRES,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK2_GETRES,
  EE_ASSERT_TASK1_RELRES,
  EE_ASSERT_TASK2_RELRES,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile int timer_fired = 0;
volatile int timer_divisor = 0;
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int counter = 0;

/* Stack Pointers */
volatile EE_UREG main_sp = 0;
volatile EE_UREG isr1_sp = 0;
volatile EE_UREG task1_sp = 0;
volatile EE_UREG task2_sp = 0;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{

  EE_UREG curr_sp;

  curr_sp = __current_sp();
  if (curr_sp != isr1_sp) {
    isr1_sp = curr_sp;
  }

  isr1_fired++;

  timer_divisor++;
  if (timer_divisor == 2000)
  {

    timer_divisor = 0;
    timer_fired++;
    if (timer_fired == 1) {
      EE_assert(EE_ASSERT_TIMER_FIRED, timer_fired == 1, EE_ASSERT_INIT);
    }

    ActivateTask(Task1);

  }

}

/*
 * TASK 1
 */
TASK(Task1)
{

  EE_UREG curr_sp;

  curr_sp = __current_sp();
  if (curr_sp != task1_sp) {
    task1_sp = curr_sp;
  }

  task1_fired++;
  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TIMER_FIRED);
    EE_assert(EE_ASSERT_TASK1_GETRES, task1_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

  GetResource(Resource);

  ActivateTask(Task2);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_RELRES, task1_fired == 1, EE_ASSERT_TASK1_GETRES);
  }

  ReleaseResource(Resource);

  task1_ended++;
  TerminateTask();

}

/*
 * TASK 2
 */
TASK(Task2)
{

  EE_UREG curr_sp;

  curr_sp = __current_sp();
  if (curr_sp != task2_sp) {
    task2_sp = curr_sp;
  }

  task2_fired++;
  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_RELRES);
    EE_assert(EE_ASSERT_TASK2_GETRES, task2_fired == 1, EE_ASSERT_TASK2_FIRED);
  }

  GetResource(Resource);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_RELRES, task2_fired == 1, EE_ASSERT_TASK2_GETRES);
  }

  ReleaseResource(Resource);

  STM_EVAL_LEDToggle(LED3);

  task2_ended++;
  TerminateTask();

}

/*
 * MAIN TASK
 */
int main(void)
{

  EE_UREG curr_sp;

  SystemInit();
  /*Initializes Erika related stuffs*/
  EE_system_init();

  STM_EVAL_LEDInit(LED3);

  EE_systick_set_period(1000);
  EE_systick_enable_int();
  EE_systick_start();

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  StartOS(OSDEFAULTAPPMODE);

  while(!(task1_ended && task2_ended));


  EE_assert(
    EE_ASSERT_TASKS_ENDED, task1_ended && task2_ended, EE_ASSERT_TASK2_RELRES
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = __current_sp();
    if (curr_sp != main_sp) {
      main_sp = curr_sp;
    }

    counter++;

  }

}
