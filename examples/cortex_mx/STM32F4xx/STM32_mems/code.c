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
#include "stm32f4_discovery_lis302dl.h"


#define DOUBLECLICK_Z                    ((uint8_t)0x60)
#define SINGLECLICK_Z                    ((uint8_t)0x50)

/* TIM2 Autoreload and Capture Compare register values */
#define TIM_ARR                          ((uint16_t)1900)
#define TIM_CCR                          ((uint16_t)1000)

#define ABS(x)                           (x < 0) ? (-x) : x
#define MAX(a,b)                         (a < b) ? (b) : a


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

uint16_t PrescalerValue = 0;
uint8_t Buffer[6];
volatile uint32_t TimingDelay = 0;
volatile int8_t XOffset;
volatile int8_t YOffset;


volatile uint8_t SingleClickDetect = 0x00;
extern uint8_t ClickReg;

/**
  * @brief  Delay del ms.
  * @param  del The delay in ms
  * @retval None
  */
void delay(uint16_t del)
{

	TickType cnt0, cnt;
	GetCounterValue(myCounter, &cnt0);

	do {
		GetCounterValue(myCounter, &cnt);
	}
	while (cnt - cnt0 < del);
}

/**
  * @brief  Configures the TIM Peripheral.
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	/* --------------------------- System Clocks Configuration -----------------*/
	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	/* GPIOD clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/*-------------------------- GPIO Configuration ----------------------------*/
	/* GPIOD Configuration: Pins 12, 13, 14 and 15 in output push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
			GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Connect TIM4 pins to AF2 */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	/* -----------------------------------------------------------------------
	TIM4 Configuration: Output Compare Timing Mode:

	In this example TIM4 input clock (TIM4CLK) is set to 2 * APB1 clock (PCLK1),
	since APB1 prescaler is different from 1 (APB1 Prescaler = 4, see system_stm32f4xx.c file).
	  TIM4CLK = 2 * PCLK1
	  PCLK1 = HCLK / 4
	  => TIM4CLK = 2*(HCLK / 4) = HCLK/2 = SystemCoreClock/2

	To get TIM4 counter clock at 2 KHz, the prescaler is computed as follows:
	   Prescaler = (TIM4CLK / TIM1 counter clock) - 1
	   Prescaler = (168 MHz/(2 * 2 KHz)) - 1 = 41999

	To get TIM4 output clock at 1 Hz, the period (ARR)) is computed as follows:
	   ARR = (TIM4 counter clock / TIM4 output clock) - 1
		   = 1999

	TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 50%
	TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100 = 50%
	TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 50%
	TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR)* 100 = 50%

	==> TIM4_CCRx = TIM4_ARR/2 = 1000  (where x = 1, 2, 3 and 4).

	Note:
	 SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
	 Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
	 function to update SystemCoreClock variable value. Otherwise, any configuration
	 based on this variable will be incorrect.
	----------------------------------------------------------------------- */

	/* Compute the prescaler value */
	PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 2000) - 1;

	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = TIM_ARR;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* Enable TIM4 Preload register on ARR */
	TIM_ARRPreloadConfig(TIM4, ENABLE);

	/* TIM PWM1 Mode configuration: Channel */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_CCR;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	/* Output Compare PWM1 Mode configuration: Channel1 */
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_1, DISABLE);

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Output Compare PWM1 Mode configuration: Channel2 */
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_2, DISABLE);

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Output Compare PWM1 Mode configuration: Channel3 */
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_3, DISABLE);

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* Output Compare PWM1 Mode configuration: Channel4 */
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_CCxCmd(TIM4, TIM_Channel_4, DISABLE);

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

	/* TIM4 enable counter */
	TIM_Cmd(TIM4, ENABLE);
}

/**
  * @brief  Configures the accelerometer (LIS302DL).
  * @param  None
  * @retval None
  */
MEMS_Configure()
{
	uint8_t ctrl = 0;

	LIS302DL_InitTypeDef  LIS302DL_InitStruct;
	LIS302DL_InterruptConfigTypeDef LIS302DL_InterruptStruct;

	/* SysTick end of count event each 10ms */
	SysTick_Config(SystemCoreClock/ 100);

	/* Set configuration of LIS302DL*/
	LIS302DL_InitStruct.Power_Mode = LIS302DL_LOWPOWERMODE_ACTIVE;
	LIS302DL_InitStruct.Output_DataRate = LIS302DL_DATARATE_100;
	LIS302DL_InitStruct.Axes_Enable = LIS302DL_X_ENABLE | LIS302DL_Y_ENABLE |
			LIS302DL_Z_ENABLE;
	LIS302DL_InitStruct.Full_Scale = LIS302DL_FULLSCALE_2_3;
	LIS302DL_InitStruct.Self_Test = LIS302DL_SELFTEST_NORMAL;
	LIS302DL_Init(&LIS302DL_InitStruct);

	/* Set configuration of Internal High Pass Filter of LIS302DL*/
	LIS302DL_InterruptStruct.Latch_Request = LIS302DL_INTERRUPTREQUEST_LATCHED;
	LIS302DL_InterruptStruct.SingleClick_Axes = LIS302DL_CLICKINTERRUPT_Z_ENABLE;
	LIS302DL_InterruptStruct.DoubleClick_Axes =
			LIS302DL_DOUBLECLICKINTERRUPT_Z_ENABLE;
	LIS302DL_InterruptConfig(&LIS302DL_InterruptStruct);

	  /* Required delay for the MEMS Accelerometre:
	   * Turn-on time = 3/Output data Rate = 3/100 = 30ms
	   * */

	delay(30);

	/* Configure Interrupt control register: enable Click interrupt1 */
	ctrl = 0x07;
	LIS302DL_Write(&ctrl, LIS302DL_CTRL_REG3_ADDR, 1);

	/* Enable Interrupt generation on click/double click on Z axis */
	ctrl = 0x70;
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_CFG_REG_ADDR, 1);

	/* Configure Click Threshold on X/Y axis (10 x 0.5g) */
	ctrl = 0xAA;
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_THSY_X_REG_ADDR, 1);

	/* Configure Click Threshold on Z axis (10 x 0.5g) */
	ctrl = 0x0A;
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_THSZ_REG_ADDR, 1);

	/* Configure Time Limit */
	ctrl = 0x03;
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_TIMELIMIT_REG_ADDR, 1);

	  /* Configure Latency */
	ctrl = 0x7F;
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_LATENCY_REG_ADDR, 1);

	/* Configure Click Window */
	ctrl = 0x7F;
	LIS302DL_Write(&ctrl, LIS302DL_CLICK_WINDOW_REG_ADDR, 1);

	/* TIM configuration -------------------------------------------------------*/
	TIM_Config();

	LIS302DL_Read(Buffer, LIS302DL_OUT_X_ADDR, 6);

	XOffset = Buffer[0];
	YOffset = Buffer[2];
}


/**
  * @brief  MEMS accelerometre management of the timeout situation.
  * @param  None.
  * @retval None.
  */
uint32_t LIS302DL_TIMEOUT_UserCallback(void)
{
  /* MEMS Accelerometer Timeout error occured */
  while (1)
  {
  }
}


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


/**
 * This task acquires the mems values
 */
TASK(TaskMEMS)
{

	volatile uint8_t TempAcceleration = 0;
	uint8_t ClickReg = 0;
	uint8_t temp1, temp2 = 0;

	Buffer[0] = 0;
	Buffer[2] = 0;

	/* Disable All TIM4 Capture Compare Channels */
	TIM_CCxCmd(TIM4, TIM_Channel_1, DISABLE);
	TIM_CCxCmd(TIM4, TIM_Channel_2, DISABLE);
	TIM_CCxCmd(TIM4, TIM_Channel_3, DISABLE);
	TIM_CCxCmd(TIM4, TIM_Channel_4, DISABLE);

	LIS302DL_Read(Buffer, LIS302DL_OUT_X_ADDR, 6);
	/* Remove the offsets values from data */
	Buffer[0] -= XOffset;
	Buffer[2] -= YOffset;

	/* Update autoreload and capture compare registers value*/
	temp1 = ABS((int8_t)(Buffer[0]));
	temp2 = ABS((int8_t)(Buffer[2]));
	TempAcceleration = MAX(temp1, temp2);

	if (TempAcceleration != 0) {
		if ((int8_t)Buffer[0] < -2) {
			/* Enable TIM4 Capture Compare Channel 4 */
			TIM_CCxCmd(TIM4, TIM_Channel_4, ENABLE);
			/* Sets the TIM4 Capture Compare4 Register value */
			TIM_SetCompare4(TIM4, TIM_CCR/TempAcceleration);
		}
		if ((int8_t)Buffer[0] > 2) {
			/* Enable TIM4 Capture Compare Channel 2 */
			TIM_CCxCmd(TIM4, TIM_Channel_2, ENABLE);
			/* Sets the TIM4 Capture Compare2 Register value */
			TIM_SetCompare2(TIM4, TIM_CCR/TempAcceleration);
		}
		if ((int8_t)Buffer[2] > 2) {
			/* Enable TIM4 Capture Compare Channel 1 */
			TIM_CCxCmd(TIM4, TIM_Channel_1, ENABLE);
			/* Sets the TIM4 Capture Compare1 Register value */
			TIM_SetCompare1(TIM4, TIM_CCR/TempAcceleration);
		}
		if ((int8_t)Buffer[2] < -2) {
			/* Enable TIM4 Capture Compare Channel 3 */
			TIM_CCxCmd(TIM4, TIM_Channel_3, ENABLE);
			/* Sets the TIM4 Capture Compare3 Register value */
			TIM_SetCompare3(TIM4, TIM_CCR/TempAcceleration);
		}

		/* Time base configuration */
		TIM_SetAutoreload(TIM4,  TIM_ARR/TempAcceleration);

		/* Read click status register */
		LIS302DL_Read(&ClickReg, LIS302DL_CLICK_SRC_REG_ADDR, 1);

		if (ClickReg == SINGLECLICK_Z) {
			SingleClickDetect = 0x01;
		}
	}

	TerminateTask();

}

/**
 * This task notifies the results coming from mems sensor
 * through the board's leds.
 */
TASK(TaskNotify)
{
	uint8_t ClickReg = 0;

	if (SingleClickDetect != 0) {
      delay(50);
      /* Read click status register */
		LIS302DL_Read(&ClickReg, LIS302DL_CLICK_SRC_REG_ADDR, 1);

		if (ClickReg == DOUBLECLICK_Z) {
			/* Enable TIM4 Capture Compare Channel 1 */
			TIM_CCxCmd(TIM4, TIM_Channel_1, ENABLE);
			/* Sets the TIM4 Capture Compare1 Register value */
			TIM_SetCompare1(TIM4, TIM_CCR/12);
			/* Enable TIM4 Capture Compare Channel 2 */
			TIM_CCxCmd(TIM4, TIM_Channel_2, ENABLE);
			/* Sets the TIM4 Capture Compare2 Register value */
			TIM_SetCompare2(TIM4, TIM_CCR/12);
			/* Enable TIM4 Capture Compare Channel 3 */
			TIM_CCxCmd(TIM4, TIM_Channel_3, ENABLE);
			/* Sets the TIM4 Capture Compare3 Register value */
			TIM_SetCompare3(TIM4, TIM_CCR/12);
			/* Enable TIM4 Capture Compare Channel 4 */
			TIM_CCxCmd(TIM4, TIM_Channel_4, ENABLE);
			/* Sets the TIM4 Capture Compare4 Register value */
			TIM_SetCompare4(TIM4, TIM_CCR/12);

			/* Time base configuration */
			TIM_SetAutoreload(TIM4, TIM_ARR/12);
			delay(200);

			/* Clear the click status register by reading it */
			LIS302DL_Read(&ClickReg, LIS302DL_CLICK_SRC_REG_ADDR, 1);

			/* Reset the single click detect */
			SingleClickDetect = 0x00;
		} else {
			/* Disable TIM4 Capture Compare Channel 1/3 */
			TIM_CCxCmd(TIM4, TIM_Channel_1, DISABLE);
			TIM_CCxCmd(TIM4, TIM_Channel_3, DISABLE);

			/* Enable TIM4 Capture Compare Channel 2 */
			TIM_CCxCmd(TIM4, TIM_Channel_2, ENABLE);
			/* Sets the TIM4 Capture Compare2 Register value */
			TIM_SetCompare2(TIM4, TIM_CCR/12);

			/* Enable TIM4 Capture Compare Channel 4 */
			TIM_CCxCmd(TIM4, TIM_Channel_4, ENABLE);
			/* Sets the TIM4 Capture Compare4 Register value */
			TIM_SetCompare4(TIM4, TIM_CCR/12);

			/* Time base configuration */
			TIM_SetAutoreload(TIM4, TIM_ARR/12);
			delay(200);
			SingleClickDetect = 0;
		}
	}

	TerminateTask();

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

	MEMS_Configure();

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmMEMS, 100, 50);
	SetRelAlarm(AlarmNotify, 100, 100);

	StartOS(OSDEFAULTAPPMODE);
	/* Forever loop: background activities (if any) should go here */
	for (;;);

}

