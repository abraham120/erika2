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
 * Author: 2006 Paolo Gai
 * CVS: $Id: code.c,v 1.10 2007/03/16 10:45:20 nino Exp $
 */

#include "ee.h"
#include "ee_irq.h"

/* Oscillator selectione register set on internal Fast RC oscillator (7.86 Mhz nominal). */
_FOSCSEL(FNOSC_FRC);
/* Oscillator configuration register set with clock switch enabled & clock monitoring disabled (FCKSM_CSECMD),
 * OSC2 pin as GPIO (OSCIOFNC_ON) and
 * primary oscillator disabled (not external oscillator/clock source in the board) */
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
/* Watchdog Timer disabled */
_FWDT(FWDTEN_OFF);

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0xffff;		/* Load the Period register wit the value 0xffff	*/
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
				* and clock source set to the internal
				* instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}

/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

TASK(myTask)
{
	EE_sys_led_toggle();
}

int main(void)
{
	/* Program Timer 1 to raise interrupts */
	T1_program();
  
	/* Init led */
	EE_leds_init();

	/* Program a cyclic alarm which will fire after an offset of 10 counter 
	* ticks, and after that periodically every 20 ticks */
	SetRelAlarm(myAlarm, 10, 20);
  
	/* A task can be activated directly by using ActivateTask */
	ActivateTask(myTask);
  
	/* Forever loop: background activities (if any) should go here */
	for (;;);
  
	return 0;
}
