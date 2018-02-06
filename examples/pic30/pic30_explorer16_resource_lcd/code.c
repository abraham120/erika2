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
 * CVS: $Id: code.c,v 1.4 2007/03/15 15:39:11 nino Exp $
 */

#include "ee.h"
#include "ee_irq.h"

/*
 * Use this define to use or not the resources and obtain the race
 * condition described inside the readme.txt!!!
 */
#define WITH_RESOURCES


// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL(FNOSC_PRI);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

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
unsigned char i = 0;
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* activate thread */
	ActivateTask(HighTask);
}

TASK(LowTask)
{
	static int i=0;

	for (;;) {
#ifdef WITH_RESOURCES
		GetResource(myResource);
#endif
		EE_lcd_goto( 0, 0);
		EE_lcd_putc('0'+i);
#ifdef WITH_RESOURCES
		ReleaseResource(myResource);
#endif
		/* Increment the counter */
		i++;
		if (i == 10)
			i = 0;
	}
}

TASK(HighTask)
{
	static int j=0;

#ifdef WITH_RESOURCES
	GetResource(myResource);
#endif
	EE_lcd_goto( 0, 1);
	EE_lcd_putc('0'+j);
#ifdef WITH_RESOURCES
	ReleaseResource(myResource);
#endif
	/* Increment the counter */
	j++;
	if (j == 10)
		j = 0;
}

int main(void)
{
	/* Program Timer 1 to raise interrupts */
	T1_program();
  
	/* Clear the LCD */
	EE_lcd_init();
	EE_lcd_clear();

	/* activate the low priority task */
	ActivateTask(LowTask);
  
	/* Forever loop: Please note that since LowTask does not end
	the program will never reach this point! */
	for (;;);
	
	return 0;
}
