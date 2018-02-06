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
 * A minimal EE demo that demostrates how the nesting of the interrupts works.
 * This demo can be used to test nesting mechanism.
 * Author: 2012 Carlo Caione
 * Based on examples\cortex_mx\lpc12xx\porting_examples\monostack\EEtest5
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"
#include "ee_irq.h"
#include "mcu/nordic_nrf51x22/inc/ee_timer.h"

#include "nrf.h"
#include "nrf_gpio.h"
#include "boards.h"

#ifndef	TRUE
#define	TRUE	0x01U
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TIMER_ISR_FIRED,
  EE_ASSERT_SYSTICK_ISR_FIRED,
  EE_ASSERT_TASK1_ENDED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK2_ENDED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
EE_TYPEASSERTVALUE result;

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int isr2_fired = 0;
volatile int counter = 0;

/* Stack Pointers */
volatile EE_UREG main_sp = 0;
volatile EE_UREG isr1_sp = 0;
volatile EE_UREG isr2_sp = 0;
volatile EE_UREG task1_sp = 0;
volatile EE_UREG task2_sp = 0;

/* Used for led toggling */
uint8_t output_state = 0;

/*
 * Timer2 handler
 */

void timer_handler()
{

  EE_UREG curr_sp;
  
  curr_sp = __current_sp();
  if (curr_sp != isr1_sp) {
    isr1_sp = curr_sp;
  }

  isr1_fired++;
  if (isr1_fired == 1) {
    EE_assert(EE_ASSERT_TIMER_ISR_FIRED, isr1_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

  EE_timer_stop(EE_TIMER_2);

  EE_timer_start(EE_TIMER_1);
  while (!(isr2_fired % 10));	/* Waits 1st ISR */
  while (isr2_fired % 10);	/* Waits 10th ISR */
  EE_timer_stop(EE_TIMER_1);

}

/*
 * SysTick handler (Timer1)
 */
void systick_handler()
{

  EE_UREG curr_sp;
  
  curr_sp = __current_sp();
  if (curr_sp != isr2_sp) {
    isr2_sp = curr_sp;
  }

  isr2_fired++;
  if (isr2_fired == 1) {
    EE_assert(
      EE_ASSERT_SYSTICK_ISR_FIRED, isr2_fired == 1, EE_ASSERT_TIMER_ISR_FIRED
    );
  }

  ActivateTask(Task2);

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
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_INIT);
  }

  EE_timer_start(EE_TIMER_2);
  while (task1_fired != isr1_fired);

  task1_ended++;
  if (task1_ended == 1) {
    EE_assert(
      EE_ASSERT_TASK1_ENDED, task1_ended == 1, EE_ASSERT_SYSTICK_ISR_FIRED
    );
  }

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
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_ENDED);
  }

  task2_ended++;
  if (task2_ended == 1) {
    EE_assert(EE_ASSERT_TASK2_ENDED, task2_ended == 1, EE_ASSERT_TASK2_FIRED);
  }

}

/*
 * MAIN TASK
 */
int main(void)
{

  EE_UREG curr_sp;
  int i;

  /* Start 16 MHz crystal oscillator */
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  NRF_CLOCK->TASKS_HFCLKSTART = 1;

  /* Wait for the external oscillator to start up */
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) 
  {
  }	
  
  /*Initializes Erika related stuffs*/
  EE_system_init(); 
  
  EE_timer_hard_init(EE_TIMER_2, 100000, EE_TIMER_PS32, EE_TIMER_BITMODE_16);
  EE_timer_set_callback(EE_TIMER_2,timer_handler);

  /* Configure LED-pins as outputs */
  nrf_gpio_range_cfg_output(LED_START, LED_STOP);
  
  EE_timer_hard_init(EE_TIMER_1, 100000, EE_TIMER_PS16, EE_TIMER_BITMODE_16);
  EE_timer_set_callback(EE_TIMER_1,systick_handler);
  
  EE_cortex_mx_enableIRQ();
  
  for(i=0;i<EE_ASSERT_DIM;i++)
	EE_assertions[i]=EE_ASSERT_INITVALUE;
  
  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  ActivateTask(Task1);

  EE_assert(
    EE_ASSERT_TASKS_ENDED, task1_ended && task2_ended, EE_ASSERT_TASK2_ENDED
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

    while (counter % 10000) counter++;
	
    /* LED Toggle */
	nrf_gpio_port_write(LED_PORT, 1 << (output_state + LED_OFFSET));
	output_state = (output_state + 1) & BLINKY_STATE_MASK;
	
    ActivateTask(Task1);
    counter++;

  }

}
