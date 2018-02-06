/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
  * Author: 2014 Angelo Compagnucci <angelo.compagnucci@gmail.com>
  * 
  */

#include <ee.h>
#include "cpu/pic32/inc/ee_irqstub.h"
#include "mcu/microchip_pic32/inc/ee_timer.h"


/*  Initial Configuration (fuse bits)
 *
 *  Main Clock       -> SYSCLK = Crystal_Freq / FPLLIDIV * FPLLMUL / FPLLODIV
 *  Peripheral Clock -> PBCLK  = SYSCLK / FPBDIV
*/
#pragma config POSCMOD = HS
#pragma config FNOSC = PRIPLL
#pragma config FPLLMUL = MUL_20		/* PLL Multiplier */
#pragma config FPLLIDIV = DIV_2	 	/* PLL Input Divider */
#pragma config FPLLODIV = DIV_1  	/* PLL Output Divider */
#pragma config FWDTEN = OFF		/* Watchdog Off */
#pragma config FPBDIV = DIV_2		/* SYSCLK = 80MHz, PBCLK = 40MHz */


/* ************************************************************************** */
/*                                  Macros                                    */
/* ************************************************************************** */

/* Timer definitions	*/
#define TICK_PERIOD 	20000


/* ************************************************************************** */
/*                               Functions                                    */
/* ************************************************************************** */

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}


/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
void T1_cbk(void)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	EE_timer_soft_init(EE_TIMER_1,30000);
	EE_timer_set_callback(EE_TIMER_1,&T1_cbk);
	EE_timer_start(EE_TIMER_1);
}



/* ************************************************************************** */
/*                               Tasks                                	      */
/* ************************************************************************** */
TASK(TaskLed1)
{
	if (EE_led_is_on(0)){
		EE_led_0_off();
	} else {
		EE_led_0_on();
	}
}

TASK(TaskLed2)
{
	if (EE_led_is_on(1)){
		EE_led_1_off();
	} else {
		EE_led_1_on();
	}
}

TASK(TaskLed3)
{
	if (EE_led_is_on(2)){
		EE_led_2_off();
	} else {
		EE_led_2_on();
	}
}


void my_button(void)
{
	/* Light up all LEDs */
	if (EE_button_get_S1() == 1)
		EE_leds_on();
}



/* ************************************************************************** */
/*                                  MAIN                                      */
/* ************************************************************************** */
int main(void)
{
	/* */
	EE_system_init();

	/* Init leds */
	EE_leds_init();

	/* Init devices */
	EE_buttons_init(&my_button, 0x01);

	/* Program Timer 1 to raise interrupts */
	T1_program();
  
	/* Program cyclic alarms which will fire after an initial offset, and after that periodically */
	SetRelAlarm(AlarmLed1, 1, 10);
	SetRelAlarm(AlarmLed2, 3, 10);
	SetRelAlarm(AlarmLed3, 6, 10);

	 /* Forever loop: background activities (if any) should go here */
	for (;;);
	
	return 0;
}
