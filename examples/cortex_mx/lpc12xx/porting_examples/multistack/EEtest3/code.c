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
 * Author: 2011  Gianluca Franchino
 *               Giuseppe Serano
 * Based on examples/s12xs/porting_examples/multistack/EEtest3
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
  EE_ASSERT_ST_ISR_FIRED,
  EE_ASSERT_TMR_ISR_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK2_TEN_INSTANCES,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile unsigned int task1_fired=0;
volatile unsigned int task2_fired=0;
volatile unsigned int timer_fired;
volatile unsigned int timer_divisor = 0;
volatile unsigned long sys_tick_cnt;

volatile unsigned int flag_end = 0;

/*
 * Timer0 (CT16B0) ISR
 */
ISR2(TIMER16_0_IRQHandler)
{
  if (TIM16_GetIntStatusReg (LPC_CT16B0) & TIM16_INT_MR0) {
    TIM16_ClearIntPendingBit(LPC_CT16B0, TIM16_INT_MR0);
    timer_divisor++;
    if (timer_divisor == 100) {
      timer_divisor = 0;
      timer_fired++;
      if (timer_fired == 1)
	EE_assert(
	  EE_ASSERT_TMR_ISR_FIRED, timer_fired == 1, EE_ASSERT_ST_ISR_FIRED
	);
      ActivateTask(Task2);
      //SysTick->CTRL = SysTick->CTRL & 0xFFFFFFFD;

      if(timer_fired==10) {		/*Disable SysTick interrupt*/
	//SysTick->CTRL = SysTick->CTRL & 0xFFFFFFFD
	flag_end = 1;
      }
    }
  }

}

/*
 * SysTick ISR2
 */
ISR2(SysTick_Handler)
{
  if (!flag_end) {
    TIM16_Cmd(LPC_CT16B0, ENABLE);

    ActivateTask(Task1);
  }

  sys_tick_cnt++;
  if (sys_tick_cnt == 1)
    EE_assert(EE_ASSERT_ST_ISR_FIRED, sys_tick_cnt == 1, EE_ASSERT_INIT);
  
  while(!flag_end); 
  TIM16_Cmd(LPC_CT16B0, DISABLE);
}

TIM16_InitTypeDef TIM16_mode;
TIM16_MATCHTypeDef TIM16_MATCH_mode;

/*
 * Initialize Timer0 (CT16B0)
 */
void timer_init()
{
  /* 
   *Considering prescaler 1 and clock of 6 MHz -> 0.167 usec/tick
   * So to obtain 1 ms we need 6000 ticks = 0x1770.
   */

  /* Initialize timer16B0, prescale count time of 100uS */
  TIM16_mode.PrescaleOption = TIM16_PRESCALE_USVAL;
  TIM16_mode.PrescaleValue = 100;
  
  TIM16_MATCH_mode.MatchValue = 0x1000;
  TIM16_MATCH_mode.IntOnMatch = TRUE;
  TIM16_MATCH_mode.ResetOnMatch = TRUE;
  TIM16_MATCH_mode.StopOnMatch = FALSE;
  
  TIM16_ConfigMatch(LPC_CT16B0, &TIM16_MATCH_mode);
  TIM16_StructInit(TIM16_TIMER_MODE, &TIM16_mode);
  TIM16_Init(LPC_CT16B0, TIM16_TIMER_MODE, &TIM16_mode);
  
  
  /* preemption = 1, sub-priority = 1 */
  //NVIC_SetPriority(TIMER_16_0_IRQn, ((0x01<<3)|0x01)); 
  NVIC_SetPriority(TIMER_16_0_IRQn,0);
  /* Enable interrupt for timer */
  NVIC_EnableIRQ(TIMER_16_0_IRQn);

}

/*
 * DELAY
 */
void mydelay(unsigned long tick)
{
  unsigned long cnt;
  cnt = sys_tick_cnt;

  while ((sys_tick_cnt - cnt) < tick);
}

/*
 * SysTick INITIALIZATION
 */
void sys_tick_init(void)
{
  /* Generate systemtick interrupt each 1 ms   */
  SysTick_Config(SystemCoreClock/1000 - 1); 
  /* Priority SysTick = 00*/
  NVIC_SetPriority(SysTick_IRQn, 1);
}

/*
 * LED INITIALIZATION
 */
void led_init(void) 
{
  IOCON_PIO_CFG_Type PIO_mode;
  
  IOCON_StructInit(&PIO_mode);
  
  PIO_mode.type = IOCON_PIO_0_7;
  IOCON_SetFunc(&PIO_mode);
  GPIO_SetDir(LPC_GPIO0, 7, 1);
  GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
}

/*
 * LED Blink
 */
void led_blink(void) 
{
  if ( GPIO_GetPinValue(LPC_GPIO0, 7) )
    GPIO_SetLowLevel(LPC_GPIO0, 7, 1);
  else
    GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
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
  led_blink();
}

/*
 * TASK 2
 */
TASK(Task2)
{
  static int led_off_cnt = 0;
  static int led_on_cnt = 0;
  
  /* count the number of Task2 activations */
  task2_fired++;
  if (task2_fired == 1)
    EE_assert(
      EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_ST_ISR_FIRED
    );
  else
    if (task2_fired >= 10)
      EE_assert(
        EE_ASSERT_TASK2_TEN_INSTANCES, task2_fired == 10, EE_ASSERT_TASK2_FIRED
      );
  
  /* Count the number of times the led is on and off */
  if (GPIO_GetPinValue(LPC_GPIO0, 7)) 
    led_on_cnt++;
  else 
    led_off_cnt++;
}

/*
 * MAIN TASK
 */
int main(void)
{
  /*Setup the microcontroller system:
    -System Clock Setup;
    -PLL setup
    -Whatchdog setup (Default Watchdog = disabled)
    
    The system (core) clock frequency (CF):  CF= Fin * M / (2P);
    For Fin<15 P=4 and M=2
    If your board mounts a 12MHz cristal oscillator, i.e. Fin=12MHz,
    then the default system clock frequency is CF = 12 MHz * M / (2P)= 6MHZ.

    See "system_LPC12xx.c" in <lpc12cc_cmsis_driver_library> 
    for further informations.
    To modify the system setup, use functions provided by 
    "lpc12xx_sysctrl.c" in <lpc12cc_cmsis_driver_library>
  */
  SystemInit();

  /*Initializes Erika related stuffs*/
  EE_system_init(); 

  /*Initialize the systemtick*/
  sys_tick_init();

  /*Initialize Timer0 (CT16B0) */
  timer_init();

  led_init();

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  mydelay(100);

  EE_assert(
    EE_ASSERT_TASKS_ENDED,
    task1_fired && (task2_fired == 10),
    EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;;)
  {
    ;
  }

}
