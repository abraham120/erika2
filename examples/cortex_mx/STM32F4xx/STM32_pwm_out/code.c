/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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

#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t CCR1_Val = 333;
uint16_t CCR2_Val = 249;
uint16_t CCR3_Val = 166;
uint16_t CCR4_Val = 83;
uint16_t PrescalerValue = 0;


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/**
  * @brief  Configure and enable the PWM Ouput Channels.
  * @param  None
  * @retval None
  */
void PWM_Config_and_En(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* GPIOC and GPIOB clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);

	/* GPIOC Configuration: TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* GPIOB Configuration:  TIM3 CH3 (PB0) and TIM3 CH4 (PB1) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Connect TIM3 pins to AF2 */
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM3);


	  /* -----------------------------------------------------------------------
	    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles.

	    In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1),
	    since APB1 prescaler is different from 1.
	      TIM3CLK = 2 * PCLK1
	      PCLK1 = HCLK / 4
	      => TIM3CLK = HCLK / 2 = SystemCoreClock /2

	    To get TIM3 counter clock at 28 MHz, the prescaler is computed as follows:
	       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
	       Prescaler = ((SystemCoreClock /2) /28 MHz) - 1

	    To get TIM3 output clock at 30 KHz, the period (ARR)) is computed as follows:
	       ARR = (TIM3 counter clock / TIM3 output clock) - 1
	           = 665

	    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
	    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
	    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%

	    Note:
	     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
	     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
	     function to update SystemCoreClock variable value. Otherwise, any configuration
	     based on this variable will be incorrect.
	  ----------------------------------------------------------------------- */

	  /* Compute the prescaler value */
	  PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 28000000) - 1;

	  /* Time base configuration */
	  TIM_TimeBaseStructure.TIM_Period = 665;
	  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	  /* PWM1 Mode configuration: Channel1 */
	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  /* PWM1 Mode configuration: Channel2 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	  TIM_OC2Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  /* PWM1 Mode configuration: Channel3 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

	  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  /* PWM1 Mode configuration: Channel4 */
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

	  TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

	  TIM_ARRPreloadConfig(TIM3, ENABLE);

	  /* TIM3 enable counter */
	  TIM_Cmd(TIM3, ENABLE);
}

/**
 * This task blinks led 4.
 */
TASK(TaskLedBlink)
{
	STM_EVAL_LEDToggle(LED4);
}



int main(void)
{
	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	STM_EVAL_LEDInit(LED4);

	PWM_Config_and_En();

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmLedBlink, 10, 500);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

}

