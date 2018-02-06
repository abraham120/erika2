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


/*
 * Demo project to test pwm driver.
 * TaskL1, TaskL2 and TaskL3 are actived by alarms controlled by 2 pwm.
 * Every tasks switch on a led.
 * Author: 2013  Giuseppe Serano
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#ifndef	F_CPU
/*! \brief Define default CPU frequency, if this is not already defined. */
#define	F_CPU	2000000UL
#endif


/* Led */
volatile EE_UREG led = 0U;

/* Alarms */
volatile EE_UREG a1 = 0U;
volatile EE_UREG a2 = 0U;
volatile EE_UREG a3 = 0U;

/* PWMs */
volatile EE_UREG p1 = 0U;
volatile EE_UREG p2 = 0U;

/* Ducty-Cycles */
volatile EE_UREG d1 = 0x64U;	/* 100% */
volatile EE_UREG d2 = 0x00U;	/* 0% */

/*
 * PWM Channel 0 D Call-Back
 */
void EE_Pwm_Channel_0_D_CallBack(void)
{
	CounterTick(Counter400us);
}

/*
 * PWM Channel 0 E Call-Back
 */
void EE_Pwm_Channel_0_E_CallBack(void)
{
	CounterTick(Counter1ms);
}

void EE_Gpio_Channel_A_1_CallBack(void)
{
	if (a1 == 0x00U) {
		SetRelAlarm(AlarmL1, 1000U, 1000U);
		a1 = 0x01U;
	}
	else {
		CancelAlarm(AlarmL1);
		a1 = 0x00U;
	}
}

void EE_Gpio_Channel_A_2_CallBack(void)
{
	if (a2 == 0x00U) {
		SetRelAlarm(AlarmL2, 2000U, 2000U);
		a2 = 0x01U;
	}
	else {
		CancelAlarm(AlarmL2);
		a2 = 0x00U;
	}
}

void EE_Gpio_Channel_A_3_CallBack(void)
{
	if (a3 == 0x00U) {
		SetRelAlarm(AlarmL3, 1000U, 1000U);
		a3 = 0x01U;
	}
	else {
		CancelAlarm(AlarmL3);
		a3 = 0x00U;
	}
}

void EE_Gpio_Channel_A_4_CallBack(void)
{
	if (p1 == 0x00U) {
		/* 400us @ 2MHz - Duty 50% */
		EE_Pwm_SetPeriodAndDuty(
		  EE_PWM_CHANNEL_D_0, EE_MCU_US_2_TICKS(400U, F_CPU), d1
		);
		p1 = 0x01U;
	}
	else {
		EE_Pwm_SetOutputToIdle(EE_PWM_CHANNEL_D_0);
		p1 = 0x00U;
	}
}

void EE_Gpio_Channel_A_5_CallBack(void)
{
	if (p2 == 0x00U) {
		/* 1ms @ 2MHz - Duty 50% */
		EE_Pwm_SetPeriodAndDuty(
		  EE_PWM_CHANNEL_E_0, EE_MCU_MS_2_TICKS(1U, F_CPU), d2
		);
		p2 = 0x01U;
	}
	else {
		EE_Pwm_SetOutputToIdle(EE_PWM_CHANNEL_E_0);
		p2 = 0x00U;
	}
}

void EE_Gpio_Channel_A_6_CallBack(void)
{
	if ( d1 == 0x00U ) {
		d1 = 0x64U;
	}
	else {
		d1 -= 0x0AU;
	}
	EE_Pwm_SetDutyCycle(EE_PWM_CHANNEL_D_0, d1);
}

void EE_Gpio_Channel_A_7_CallBack(void)
{
	if ( d2 == 0x64U ) {
		d2 = 0x00U;
	}
	else {
		d2 += 0x0AU;
	}
	EE_Pwm_SetDutyCycle(EE_PWM_CHANNEL_E_0, d2);
}

TASK(TaskL1)
{
	EE_TYPEGPIOVALUE	Value;
	EE_Gpio_FlipChannel( EE_GPIO_CHANNEL_C_1, &Value);
}

TASK(TaskL2)
{
	EE_TYPEGPIOVALUE	Value;
	EE_Gpio_ReadChannel( EE_GPIO_CHANNEL_C_2, &Value);
	if (Value == EE_HIGH) {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_C_2, EE_LOW);
	}
	else {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_C_2, EE_HIGH);
	}
}

TASK(TaskL3)
{
	if ( led == 0U ) {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_C_3, EE_LOW);
		led = 1U;
	}
	else {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_C_3, EE_HIGH);
		led = 0U;
	}
}

int main(void) {

	EE_Mcu_Init(EE_MCU_FLAG_DEFAULT);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_C_0,
	  ( EE_GPIO_FLAG_DIR_OUT | EE_GPIO_FLAG_LVL_HIGH ),
	  EE_NULL_PTR
	);
	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_C_1,
	  ( EE_GPIO_FLAG_DIR_OUT | EE_GPIO_FLAG_LVL_HIGH ),
	  EE_NULL_PTR
	);
	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_C_2,
	  ( EE_GPIO_FLAG_DIR_OUT | EE_GPIO_FLAG_LVL_HIGH ),
	  EE_NULL_PTR
	);
	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_C_3,
	  ( EE_GPIO_FLAG_DIR_OUT | EE_GPIO_FLAG_LVL_HIGH ),
	  EE_NULL_PTR
	);
	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_C_7,
	  ( EE_GPIO_FLAG_DIR_OUT | EE_GPIO_FLAG_LVL_HIGH ),
	  EE_NULL_PTR
	);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_1,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_1_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_1);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_2,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_2_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_2);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_3,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_3_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_3);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_4,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_4_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_4);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_5,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_5_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_5);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_6,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_6_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_6);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_A_7,
	  ( 
	    EE_GPIO_FLAG_DIR_IN		|
	    EE_GPIO_FLAG_PULL_UP	|
	    EE_GPIO_FLAG_FALL_EDGE
	  ),
	  EE_Gpio_Channel_A_7_CallBack
	);

	EE_Gpio_EnableNotification(EE_GPIO_CHANNEL_A_7);

	EE_Gpio_Init( EE_GPIO_CHANNEL_D_0, EE_GPIO_FLAG_DIR_OUT, EE_NULL_PTR );

	EE_Pwm_Init(
	  EE_PWM_CHANNEL_D_0, EE_PWM_FLAG_POL_HIGH, EE_Pwm_Channel_0_D_CallBack
	);

	EE_Pwm_EnableNotification(EE_PWM_CHANNEL_D_0, EE_PWM_RISING_EDGE);

	EE_Gpio_Init(
	  EE_GPIO_CHANNEL_E_3,
	  ( EE_GPIO_FLAG_DIR_OUT | EE_GPIO_FLAG_LVL_HIGH ),
	  EE_NULL_PTR
	);

	EE_Pwm_Init(
	  EE_PWM_CHANNEL_E_0,
	  ( EE_PWM_FLAG_POL_HIGH | EE_PWM_FLAG_IDLE_HIGH),
	  EE_Pwm_Channel_0_E_CallBack
	);

	EE_Pwm_EnableNotification(EE_PWM_CHANNEL_E_0, EE_PWM_RISING_EDGE);

	for (;;) {
		if ( led == 0U ) {
			EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_C_0, EE_LOW);
		}
		else {
			EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_C_0, EE_HIGH);
		}
	}

	EE_Mcu_DeInit(EE_MCU_FLAG_DEFAULT);

}
