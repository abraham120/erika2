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
 * Another minimal EE demo that demonstrates how to work with the MULTISTACK
 * mode.
 * In this demo two task are activated inside an ISR and work with different
 * stacks.
 * With this demo you can test the preemption mechanism with stack change
 * starting from an interrupt.
 * Author: 2012 Carlo Caione
 * Based on examples\cortex_mx\lpc12xx\porting_examples\multistack\EEtest2
 */

#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

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
  EE_ASSERT_TIMER_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_END,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int isr1_fired = 0;
volatile int counter = 0;

/* Stack Pointers */
volatile EE_UREG main_sp = 0;
volatile EE_UREG isr1_sp = 0;
volatile EE_UREG task1_sp = 0;
volatile EE_UREG task2_sp = 0;

/* Used for led toggling */
uint8_t output_state = 0;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{

  EE_UREG curr_sp;
  
  /* Clear Interrupt */
  NRF_TIMER1->EVENTS_COMPARE[0] = 0;

  curr_sp = __current_sp();
  if (curr_sp != isr1_sp) {
    isr1_sp = curr_sp;
  }

  ActivateTask(Task1);
  ActivateTask(Task2);

  isr1_fired++;
  if (isr1_fired==1) {
    EE_assert(EE_ASSERT_TIMER_FIRED, isr1_fired == 1, EE_ASSERT_INIT);
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
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TASK2_FIRED);
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
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TIMER_FIRED);
  }

}

/*
 * Initialize Timer1 (used as systick)
 */
void timer1_init()
{
  NRF_TIMER1->MODE 			= TIMER_MODE_MODE_Timer; 		 // Set the timer in Timer Mode
  NRF_TIMER1->PRESCALER		= 0;
  NRF_TIMER1->BITMODE 		= TIMER_BITMODE_BITMODE_16Bit;  // 16-bit mode

  NRF_TIMER1->TASKS_CLEAR 	= 1;         			      // clear the task first to be usable for later
  
  NRF_TIMER1->CC[0] 		= 100000;
  NRF_TIMER1->INTENSET 		= (TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos);
  //NRF_TIMER1->SHORTS = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);

  NVIC_ClearPendingIRQ(TIMER1_IRQn);
  //NVIC_SetPriority(TIMER1_IRQn, 2);
  NVIC_EnableIRQ(TIMER1_IRQn);
  
  __enable_irq();

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

  /* Configure LED-pins as outputs */
  nrf_gpio_range_cfg_output(LED_START, LED_STOP);
  
  for(i=0;i<EE_ASSERT_DIM;i++)
	EE_assertions[i]=EE_ASSERT_INITVALUE;

  timer1_init();
  NRF_TIMER1->TASKS_START = 1;

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  while (isr1_fired < 10);

  EE_assert(
    EE_ASSERT_END,
    (task1_fired >= 10) && (task2_fired >= 10),
    EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_END);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = __current_sp();
    if (curr_sp != main_sp) {
      main_sp = curr_sp;
    }

    while (counter % 100000) counter++;
	
    /* LED Toggle */
    nrf_gpio_port_write(LED_PORT, 1 << (output_state + LED_OFFSET));
    output_state = (output_state + 1) & BLINKY_STATE_MASK;
	
    counter++;

  }

}

