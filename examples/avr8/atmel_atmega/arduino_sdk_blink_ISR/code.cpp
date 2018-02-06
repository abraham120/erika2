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
#include "Arduino.h"
#include "Timer1.h"

#define	TIMER1_US	1000000U

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;


/*
 * ISR2 MUST BE C SYMBOL
 */
extern "C" {

/* Timer1 ISR2 */
ISR2(timer1_handler)
{
	resetTimer1();

	ActivateTask(TaskL1);
}

};	/* extern "C" */

void loop(void)
{
	;
}

void setup(void)
{
	// initialize the digital pin as an output.
	pinMode(led, OUTPUT);
}

int main(void)
{
	EE_mcu_init();

	init();

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();

	/* Prepare Timer1 to send notifications every ALARMS_GCD_US. */
	startTimer1(TIMER1_US);


	for (;;) {
		loop();
		if (serialEventRun) serialEventRun();
	}

	return 0;

}
