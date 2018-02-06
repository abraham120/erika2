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


/* Set the real clock frequency */
#define EE_UART_INSTRUCTION_CLOCK	7860000UL

#include "ee.h"

#include "console_serial.h"

char * mymessage = "ErikaConsole\r\n";
console_descriptor_t *my_console_1;
#define MY_FIRST_SERIAL 0
#define MY_FIRST_CONSOLE 0

/*
 * Timer 1 ISR2
 */
ISR2(irq_1_f__type1)
{
	EE_timer_1_stop();
	CounterTick(myCounter);
	EE_timer_init1(0xFFFF);
	EE_timer_1_start();
}

EE_UINT8 l2;

TASK(TaskSend) {
	l2 = l2 ? 0 : 1;
	if (l2)
		EE_led_2_on();
	else
		EE_led_2_off();

	console_write(MY_FIRST_CONSOLE, mymessage, strlen(mymessage));
};

int main(void) {
	EE_mcu_init();

	EE_timer_init1(0xFFFF);
	EE_timer_1_start();

	/* Application Init */
	my_console_1 = console_serial_config(MY_FIRST_SERIAL, 9600, 0x06);
	console_init(MY_FIRST_CONSOLE, my_console_1);

	SetRelAlarm(AlarmSend,1,1);
	if (console_open(MY_FIRST_CONSOLE) == -1)
		EE_led_3_on();
	else
		EE_led_3_off();

	for (;;);
}
