/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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

EE_UINT8 l1, l2, l3;

/*
 * Timer 0 ISR2
 */
ISR2(irq_t0_type2)
{
	EE_timer_0_stop();
	CounterTick(Counter1ms);
	EE_timer_init0(123);	/*   1ms @ 7.86MHz */
	EE_timer_0_start();
}

/*
 * Timer 2 ISR2
 */
ISR2(irq_t2_type2)
{
	EE_timer_2_stop();
	CounterTick(Counter320us);
	EE_timer_init2(314);	/* 320us @ 7.86MHz */
	EE_timer_2_start();
}

TASK(TaskL1) {
	l1 = l1 ? 0 : 1;
	if (l1) {
		EE_led_1_on();
	}
	else {
		EE_led_1_off();
	}
};

TASK(TaskL2) {
	l2 = l2 ? 0 : 1;
	if (l2) {
		EE_led_2_on();
	}
	else {
		EE_led_2_off();
	}
};

TASK(TaskL3) {
	l3 = l3 ? 0 : 1;
	if (l3) {
		EE_led_3_on();
	}
	else {
		EE_led_3_off();
	}
};

int main(void)
{
	EE_mcu_init();

	EE_timer_init0(123);	/*   1ms @ 7.86MHz */
	EE_timer_0_start();

	EE_timer_init2(314);	/* 320us @ 7.86MHz */
	EE_timer_2_start();

	SetRelAlarm(AlarmL1, 500, 500);
	SetRelAlarm(AlarmL2,1000,1000);
	SetRelAlarm(AlarmL3, 300, 300);

	for (;;);
}
