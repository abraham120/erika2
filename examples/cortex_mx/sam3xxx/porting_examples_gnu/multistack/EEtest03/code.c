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
 * A minimal EE demo that demonstrates how to work with the MULTISTACK mode with
 * nested interrupts.
 * In this demo two tasks are activated inside two ISRs and work with different
 * stacks.
 * With this demo you can test the ISR nesting mechanism with stack change. 
 * Author: 2011  Giuseppe Serano
 * Based on examples/s12xs/porting_examples/multistack/EEtest03
 */


#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#include "sam.h"
#include "chip.h"
#include "arduinodue.h"

#define TRUE 1

#define TIMER_TC	TC1
#define	TIMER_CHANNEL	0
#define TIMER_IRQ	TC3_IRQn
// FREQ .-> VARIANT_MCK/128/frequency
#define TIMER_FREQ	1000


/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TIMER_ISR_FIRED,
  EE_ASSERT_SYSTICK_ISR_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK2_TEN_INSTANCES,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int isr2_fired = 0;
volatile int counter = 0;

/*
 * Timer ISR2
 */
ISR2(timer_handler)
{
  // EE_timer_clear_int(EE_TIMER_ID);
  TC_GetStatus(TIMER_TC, TIMER_CHANNEL);
  isr1_fired++;
  EE_assert(EE_ASSERT_TIMER_ISR_FIRED, isr1_fired == 1, EE_ASSERT_INIT);
  // EE_timer_stop(EE_TIMER_ID);
  TC_Stop(TIMER_TC, TIMER_CHANNEL);
  ActivateTask(Task1);
  EE_systick_start();
  while (!(isr2_fired % 10));	/* Waits 1st ISR */
  while (isr2_fired % 10);	/* Waits 10th ISR */
  EE_systick_stop();
}


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
  isr2_fired++;
  if (isr2_fired == 1)
    EE_assert(
      EE_ASSERT_SYSTICK_ISR_FIRED, isr2_fired == 1, EE_ASSERT_TIMER_ISR_FIRED
    );
  ActivateTask(Task2);
}

/*
 * TASK 1
 */
TASK(Task1)
{
  task1_fired++;
  EE_assert(
    EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TASK2_TEN_INSTANCES
  );
  task1_ended++;
}

/*
 * TASK 2
 */
TASK(Task2)
{
  task2_fired++;
  if (task2_fired == 1)
    EE_assert(
      EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_SYSTICK_ISR_FIRED
    );
  else
    if (task2_fired >= 10)
      EE_assert(
        EE_ASSERT_TASK2_TEN_INSTANCES, task2_fired == 10, EE_ASSERT_TASK2_FIRED
      );
  task2_ended++;
}

/*
 * Initialize Timer
 */
void timer_init()
{
  pmc_set_writeprotect(0);
  pmc_enable_periph_clk(TIMER_IRQ);

  TC_Configure(TIMER_TC, TIMER_CHANNEL, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
  
  TC_SetRA(TIMER_TC, TIMER_CHANNEL, TIMER_FREQ/2); //50% high, 50% low
  TC_SetRC(TIMER_TC, TIMER_CHANNEL, TIMER_FREQ);
  TC_Start(TIMER_TC, TIMER_CHANNEL);
  TIMER_TC->TC_CHANNEL[TIMER_CHANNEL].TC_IER=TC_IER_CPCS;
  TIMER_TC->TC_CHANNEL[TIMER_CHANNEL].TC_IDR=~TC_IER_CPCS;
  
  NVIC_EnableIRQ(TIMER_IRQ);
}

/*
 * MAIN TASK
 */
int main(void)
{
  /*Initializes Erika related stuffs*/
  EE_system_init(); 

  EE_user_led_init();

  EE_systick_set_period(1000);
  EE_systick_enable_int();
  
  //EE_timer_init(EE_TIMER_ID, EE_TIMER_CFG);
  //EE_timer_set_period(EE_TIMER_ID, 1000);
  //EE_timer_enable_int(EE_TIMER_ID);
  timer_init();

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  //EE_timer_start(EE_TIMER_ID);
  TC_Start(TIMER_TC, TIMER_CHANNEL);

  while (task1_ended == 0);

  EE_assert(
    EE_ASSERT_TASKS_ENDED,
    task1_ended && (task2_ended == 10),
    EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {
    while (counter % 100000) counter++;
    EE_user_led_toggle();
    counter++;
  }

}
