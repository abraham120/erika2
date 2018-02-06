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
 * A minimal EE demo that demostrates how to create two TASKs with different
 * priorities.
 * This demo can be used to test the preemption mechanism.
 * In this case Task2 preempts Task1.
 * Author: 2011  Gianluca Franchino
 *               Giuseppe Serano
 * Based on examples/s12xs/porting_examples/monostack/EEtest3
 */

#include "ee.h"
#include "lpc12xx_libcfg_default.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_ISR_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile int counter_taskS = 0;
volatile int counter_taskR = 0;
volatile int counter_isr = 0;

/*
 * SysTick ISR2
 */
ISR2(SysTick_Handler)
{
  counter_isr++;
  if (counter_isr == 1) {
    EE_assert(EE_ASSERT_ISR_FIRED, counter_isr == 1, EE_ASSERT_TASK1_FIRED);
    ActivateTask(Task2);
  }

  if (!(counter_isr % 500)) {
    if ( GPIO_GetPinValue(LPC_GPIO0, 7) )
      GPIO_SetLowLevel(LPC_GPIO0, 7, 1);
    else
      GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
  }
}

/*
 * TASK 1
 */
TASK(Task1)
{
  counter_taskS++;
  EE_assert(EE_ASSERT_TASK1_FIRED, counter_taskS == 1, EE_ASSERT_INIT);
  while(1)
    if (counter_taskR > 0)
      break;
  //NVIC_DisableIRQ(SysTick_IRQn);
  __disable_interrupt();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  counter_taskR++;
  EE_assert(EE_ASSERT_TASK2_FIRED, counter_taskR == 1, EE_ASSERT_ISR_FIRED);
}

/*
 * INTERRUPT INITIALIZATION
 */
void interrupt_init()
{
  /* Generate systemtick interrupt each 1 ms   */
  SysTick_Config(SystemCoreClock/1000 - 1); 
  __enable_interrupt();
}

/*
 * MAIN TASK
 */
int main(void)
{

  /*Initializes Erika related stuffs*/
  EE_system_init(); 

  IOCON_PIO_CFG_Type PIO_mode;

  /* Set interrupt vectors read from flash*/
  SYS_SetMemMap(SYS_USERFLASHMODE);

  /*Initialize the IO system*/
  SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_GPIO2, ENABLE);
  IOCON_StructInit(&PIO_mode);
  PIO_mode.type = IOCON_PIO_0_7;
  IOCON_SetFunc(&PIO_mode); 
  GPIO_SetDir(LPC_GPIO0, 7, 1);
  GPIO_SetHighLevel(LPC_GPIO0, 7, 0);

  interrupt_init();

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  ActivateTask(Task1);

  EE_assert(
    EE_ASSERT_TASKS_ENDED, counter_taskR && counter_taskS, EE_ASSERT_TASK2_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();
  
  /* Forever loop: background activities (if any) should go here */
  for (;;)
  {
    ;
  }

}
