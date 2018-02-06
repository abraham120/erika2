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
 * CVS: $Id: code.c,v 1.4 2007/03/16 14:21:17 nino Exp $
 */

#include "ee.h"
#include "kernel/sem/inc/ee_sem.h"

// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL(FNOSC_PRI);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

/* This example has 2 semaphores, used by the Producer and by the Consumer tasks. */

/* This semaphore is initialized automatically */
SemType P = STATICSEM(1);

/* This semaphore is initialized inside the Background Task */
SemType V;


TASK(Producer)
{
	int i;

	/* 
	Note: Please note that this task structure is different from the
	typical one-shot structure presented in other examples. This
	structure with a forever loop inside the task body is much more
	similar to the one typically used in the POSIX standard, and it
	requires that every task has a PRIVATE STACK, especially if the
	task calls blocking functions like WaitSem.
	*/
	for (;;) {
		WaitSem(&P);
    
		/* take some time to produce an item */
		for (i=0; i<10000; i++);

		/* the item has been produced! */
		EE_led_on();

		PostSem(&V); 
	} 
}

TASK(Consumer)
{
	int i;
	
	for (;;) {
		WaitSem(&V);
    
		/* take some time to consume an item */
		for (i=0; i<10000; i++);

		/* the item has been consumed! */
		EE_led_off();

		PostSem(&P); 
	} 
}

int main(void)
{
	/* Initialization of the second semaphore of the example; the first
	semaphore is initialized inside the definition */
	InitSem(V,0);
  
	/* Init the led and turn it off */
	EE_leds_init();
	EE_led_off();

	/* Activate the Producer. The consumer preempts the background task,
	executes and finally blocks waiting for the Consumer to consume
	the item produced. After the Producer Blocks, the Background task
	resumes and the ActivateTask returns. */
	ActivateTask(Producer);

	/* Activate the Consumer. The consumer is activated, preempting the
	background task. After that, the Consumer and the Producer Task
	will activate each other forever, and the background task will
	never execute again. */
	ActivateTask(Consumer);
  
	/* Forever loop: background activities (if any) should go here.
	Please note that in this example the code never reach this point... */
	for (;;);
  
	return 0;
}
