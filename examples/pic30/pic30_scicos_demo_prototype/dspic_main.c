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
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */


/*
 * Author: 2006 Paolo Gai
 * CVS: $Id: dspic_main.c,v 1.1 2008/02/08 14:24:09 pj Exp $
 */

#include "ee.h"
#include "ee_irq.h"

#define XNAME(x,y)  x##y
#define NAME(x,y)   XNAME(x,y)

#define XSTR(x)    #x
#define STR(x)     XSTR(x)

#define MODELNAME  STR(MODELN)
#include MODELNAME 

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

static double scicos_time; //simple time
static int dspic_time;
static double t;
static double actTime;

double get_scicos_time()
{
	return(actTime);
}

/* Program the Timer2 peripheral to raise interrupts */
void T2_program(void)
{
	T2CON = 0;		/* Stops the Timer2 and reset control reg	*/
	TMR2  = 0;		/* Clear contents of the timer register	*/
	PR2   = 0x9c40;		/* Load the Period register wit the value 0x9c40	*/
	IPC1bits.T2IP = 5;	/* Set Timer2 priority to 5		*/
	IFS0bits.T2IF = 0;	/* Clear the Timer2 interrupt status flag	*/
	IEC0bits.T2IE = 1;	/* Enable Timer2 interrupts		*/
	T2CONbits.TON = 1;	/* Start Timer2 with prescaler settings at 1:1
				  * and clock source set to the internal 
				  * instruction cycle			*/
}

/* Clear the Timer2 interrupt status flag */
void T2_clear(void)
{
	IFS0bits.T2IF = 0;
}

/* This is an ISR Type 2 which is attached to the Timer2 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T2Interrupt)
{
	/* clear the interrupt source */
	T2_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

TASK(rt_sci)
{
	actTime=t;
	NAME(MODEL,_isr)(actTime);
	t += scicos_time;
}

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T2_program();
  
	scicos_time = get_tsamp();
	dspic_time = (int) (1000*scicos_time);
	SetRelAlarm(AlarmSci, dspic_time, dspic_time);

	t = 0.0; //simulation time
  
	NAME(MODEL,_init)(); 

	// Init the debug port
	// TODO
	
	/* Forever loop: background activities (if any) should go here */
	for (;;) {}
	
	return 0;
}
