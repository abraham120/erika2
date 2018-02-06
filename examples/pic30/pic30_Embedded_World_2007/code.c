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
 * Author: 2007 Mauro Marinoni
 * CVS: $Id: code.c,v 1.2 2007/03/19 15:04:49 nino Exp $
 */
#include "ee.h"
#include "ee_irq.h"

#include "sensors.h"

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_OFF & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							


/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0x9c40;		/* Load the Period register wit the value 0x9c40	*/
	IPC0bits.T1IP = 3;	/* Set Timer1 priority to 3		*/
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
	int  status = 0;
	
	// DEBUG (ping char)
	/* char inchar;
	LATBbits.LATB14 ^= 1;
	status = Serial_Receive(&inchar); 
	if (!status) {
		Serial_Send(inchar);
	}*/
	
	LATBbits.LATB14 = 1;
	
	status = Sensors_Acquire();
	if (!status) {
		// Plain Mode
		/*Serial_Send('<');
		Serial_Send(angle8);
		Serial_Send(angleH);
		Serial_Send(angleL);
		Serial_Send(light);
		Serial_Send(distanceH);
		Serial_Send(distanceL);
		Serial_Send('>');*/
		
		// Packet format
		Serial_Send(0x49);
		Serial_Send(light/16);
		Serial_Send(light%16);
		Serial_Send(distance/0x40);
		Serial_Send(distance%0x40);
		Serial_Send(angle/0x40);
		Serial_Send(angle%0x40);
		Serial_Send(0x46);
	}

	LATBbits.LATB14 = 0;
}

int main(void)
{
	/* Clock setup for 40MIPS */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Init led */
	EE_leds_init();

	/* Applicatio Init */
	Serial_Init();
	I2C_Init();
	// Set max distance for US sensor
	//I2C_WriteByte(0xE0,0x02,0x8A);

	/* Program a cyclic alarm which will fire after an offset of 10 counter 
	* ticks, and after that periodically every 500 ticks */
	SetRelAlarm(myAlarm, 500, 500);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

	return 0;
}
