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
 * Author: 2011  Gianluca Franchino
 *               Giuseppe Serano
 * Based on examples/s12xs/porting_examples/monostack/EEtest5
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
  EE_ASSERT_TMR_ISR_FIRED,
  EE_ASSERT_ST_ISR_FIRED,
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
volatile int counter0 = 0; 
volatile int timer_divisor =0;
volatile int timer_fired =0;

/*
 * Timer0 (CT16B0) ISR2
 */
ISR2(TIMER16_0_IRQHandler)
{
  if (TIM16_GetIntStatusReg (LPC_CT16B0) & TIM16_INT_MR0) {
    TIM16_ClearIntPendingBit(LPC_CT16B0, TIM16_INT_MR0);
    counter0++;
    if (counter0 == 1) {
      EE_assert(EE_ASSERT_TMR_ISR_FIRED, counter0 == 1, EE_ASSERT_TASK1_FIRED);
      while(1)
        if(timer_fired > 2)
	  break;
    }
  }
}

/*
 * SysTick ISR2
 */
ISR2(SysTick_Handler)
{
  /* clear the interrupt source */
  timer_divisor++;
  if (timer_divisor == 200) {
    timer_divisor = 0;
    timer_fired++;
    if (timer_fired == 1) {
      EE_assert(
        EE_ASSERT_ST_ISR_FIRED, timer_fired == 1, EE_ASSERT_TMR_ISR_FIRED
      );
      ActivateTask(Task2);
    }
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
    if(timer_fired > 2)
      break;
  GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
}

/*
 * TASK 2
 */
TASK(Task2)
{
  counter_taskR++;
  EE_assert(EE_ASSERT_TASK2_FIRED, counter_taskR == 1, EE_ASSERT_ST_ISR_FIRED);
  NVIC_DisableIRQ(TIMER_16_0_IRQn);
}

/*
 * INTERRUPT INITIALIZATION
 */
void interrupt_init()
{
  /*
  NVIC_SetPriority(TIMER_16_0_IRQn,1); 
  NVIC_EnableIRQ(TIMER_16_0_IRQn);
  */
  /* preemption = 1, sub-priority = 1 */
  NVIC_SetPriority(TIMER_16_0_IRQn, ((0x01<<3)|0x01)); 
  /* Enable interrupt for timer */
  NVIC_EnableIRQ(TIMER_16_0_IRQn);
  __enable_interrupt();
}

TIM16_InitTypeDef TIM16_mode;
TIM16_MATCHTypeDef TIM16_MATCH_mode;

/*
 * Initialize Timer0 (CT16B0)
 */
void timer_init()
{
  /* 
   * Considering prescaler 1 and clock of 2 MHz -> 0.5 usec/tick
   * So to obtain 1 ms we need 2000 ticks = 0x7D0.
   */
  TIM16_MATCH_mode.MatchValue = 0x07D0;
  TIM16_MATCH_mode.IntOnMatch = TRUE;
  TIM16_MATCH_mode.ResetOnMatch = TRUE;
  TIM16_MATCH_mode.StopOnMatch = FALSE;

  TIM16_ConfigMatch(LPC_CT16B0, &TIM16_MATCH_mode);
  TIM16_StructInit(TIM16_TIMER_MODE, &TIM16_mode);
  TIM16_Init(LPC_CT16B0, TIM16_TIMER_MODE, &TIM16_mode);
  TIM16_Cmd(LPC_CT16B0, ENABLE);
}

/*
 * MAIN TASK
 */
int main(void)
{

  /*Initializes Erika related stuffs*/
  EE_system_init(); 

  IOCON_PIO_CFG_Type PIO_mode;
  

  /* Generate systemtick interrupt each 1 ms   */
  SysTick_Config(SystemCoreClock/1000 - 1); 
  /* Priority SysTick = 00*/
  NVIC_SetPriority(SysTick_IRQn, 0);

  SystemInit();

  /*Initialize the IO system*/
  SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_GPIO2, ENABLE);
  IOCON_StructInit(&PIO_mode);
  PIO_mode.type = IOCON_PIO_0_7;
  IOCON_SetFunc(&PIO_mode); 
  GPIO_SetDir(LPC_GPIO0, 7, 1);
  GPIO_SetHighLevel(LPC_GPIO0, 7, 0);

  timer_init();
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
