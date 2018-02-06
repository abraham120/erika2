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
 * Demo project to test alarms.
 * TaskL1, TaskL2 and TaskL3 are actived by alarms controlled by timers.
 * Every tasks switch on a led.
 * Author: 2013  Giuseppe Serano
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#include <avr/io.h>

#ifndef	F_CPU
/*! \brief Define default CPU frequency, if this is not already defined. */
#define	F_CPU	2000000UL
#endif

/** Utility Macro that convert an amount of ms in number of ticks of a given
    frequency **/
#define MILLISECONDS_TO_TICKS(X_MS, REF_FREQ_HZ)                            \
    ((X_MS) * ((REF_FREQ_HZ) / 1000UL))

/** Utility Macro that convert an amount of us in number of ticks of a given
    frequency **/
#define MICROSECONDS_TO_TICKS(X_MICROSECS, REF_FREQ_HZ)                     \
    (((X_MICROSECS) / 1000UL)?                                              \
        (MILLISECONDS_TO_TICKS(((X_MICROSECS) / 1000UL), (REF_FREQ_HZ))):   \
        (MILLISECONDS_TO_TICKS((X_MICROSECS), (REF_FREQ_HZ)) / 1000UL))

#ifndef	TRUE
#define	TRUE	0x01U
#endif

/* Leds */
volatile EE_UREG l0 = 0U, l1 = 0U, l2 = 0U, l3 = 0U;
volatile counter = 0;

void EE_timer1_init()
{
	/* Set up Timer/Counter 0 with three Compare Match interrupts. */
	TCC0.CTRLB = TC_WGMODE_NORMAL_gc;
	TCC0.INTCTRLA = (uint8_t) TC_OVFINTLVL_HI_gc;
	TCC0.PER = MICROSECONDS_TO_TICKS(320U, F_CPU);
}

void EE_timer1_start()
{
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc; /* Run at maximum speed. */
}

void EE_timer1_stop()
{
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
}

void EE_timer2_init()
{
	/* Set up Timer/Counter 0 with three Compare Match interrupts. */
	TCC1.CTRLB = TC_WGMODE_NORMAL_gc;
	TCC1.INTCTRLA = (uint8_t) TC_OVFINTLVL_HI_gc;
	TCC1.PER = MILLISECONDS_TO_TICKS(1U, F_CPU);
}

void EE_timer2_start()
{
	TCC1.CTRLA = TC_CLKSEL_DIV1_gc; /* Run at maximum speed. */
}

void EE_timer2_stop()
{
	TCC1.CTRLA = TC_CLKSEL_OFF_gc;
}

/*
 * Timer1 ISR2
 */
ISR2(timer1_handler)
{
	CounterTick(Counter320us);
}

/*
 * Timer2 ISR2
 */
ISR2(timer2_handler)
{
	CounterTick(Counter1ms);
}

TASK(TaskL1)
{
	EE_TYPEGPIOVALUE	Value;
	EE_Gpio_ReadChannel( EE_GPIO_CHANNEL_B_1, &Value);
	if (Value == EE_HIGH) {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_B_1, EE_LOW);
	}
	else {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_B_1, EE_HIGH);
	}
};

TASK(TaskL2)
{
	EE_TYPEGPIOVALUE	Value;
	EE_Gpio_FlipChannel( EE_GPIO_CHANNEL_B_2, &Value);
};

TASK(TaskL3)
{
	if (l3 == 0U) {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_B_3, EE_LOW);
		l3 = 1U;
	}
	else {
		EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_B_3, EE_HIGH);
		l3 = 0U;
	}
};

int main(void) {

	EE_Mcu_Init(EE_MCU_FLAG_DEFAULT);

	EE_Gpio_Init(EE_GPIO_CHANNEL_B_0, EE_GPIO_FLAG_DIR_OUT, EE_NULL_PTR);
	EE_Gpio_Init(EE_GPIO_CHANNEL_B_1, EE_GPIO_FLAG_DIR_OUT, EE_NULL_PTR);
	EE_Gpio_Init(EE_GPIO_CHANNEL_B_2, EE_GPIO_FLAG_DIR_OUT, EE_NULL_PTR);
	EE_Gpio_Init(EE_GPIO_CHANNEL_B_3, EE_GPIO_FLAG_DIR_OUT, EE_NULL_PTR);

	EE_timer1_init();	/* 320us @ 2MHz */
	EE_timer2_init();	/*   1ms @ 2MHz */

	EE_timer1_start();
	EE_timer2_start();

	SetRelAlarm(AlarmL1, 500U, 500U);
	SetRelAlarm(AlarmL2,1000U,1000U);
	SetRelAlarm(AlarmL3, 300U, 300U);

	for (;;) {
		while (counter % 1000) counter++;
		counter++;
		if ( l0 == 0U ) {
			EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_B_0, EE_LOW);
			l0 = 1U;
		}
		else {
			EE_Gpio_WriteChannel( EE_GPIO_CHANNEL_B_0, EE_HIGH);
			l0 = 0U;
		}
	}

	EE_Mcu_DeInit(EE_MCU_FLAG_DEFAULT);

}
