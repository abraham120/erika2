/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2010  Evidence Srl
 * Copyright (C) 2010       Pebble Bay Consulting Ltd.
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
    Author: 2009-2010 Dario Di Stefano
    Updates:2010-2011 Steve Langstaff, Pebble Bay Consulting Ltd.
*/

#include "ee.h"
#include "cpu/esi_risc/inc/ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#include <stdio.h>
#include <stdlib.h>
#include <esirisc/esirisc.h>

#define TRUE 1

/* Information about the timer0 device, such as which interrupt it is using. */
static void * timer0_device;

/* Information about the timer1 device, such as which interrupt it is using. */
static void *timer1_device;

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

volatile int isr_low_fired = 0;
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int timer_fired = 0;
volatile int finished = 0;

extern int get_sp(void);


/* This is a high priority task that is activated by the low priority ISR
 * It should be scheduled AFTER the ISRs have finished
 */
TASK(Task1)
{
	iprintf("INFO :%s: START: sp=0x%x\n", __FUNCTION__, get_sp());
	  task1_fired++;
	   if(task1_fired==1)
	  	EE_assert(4, task1_fired==1, 3);
	iprintf("INFO :%s: END\n", __FUNCTION__);
}

/* This is a high priority task that is activated by the high priority ISR
 * It should be scheduled AFTER the Task1 has finished
 */
TASK(Task2)
{
	iprintf("INFO :%s: START: sp=0x%x\n", __FUNCTION__, get_sp());
	  task2_fired++;
		if(task2_fired==1)
	  	EE_assert(5, task2_fired==1, 4);
	iprintf("INFO :%s: END\n", __FUNCTION__);
}

/*
 * This is the low priority ISR that waits for a number of high priority ISRs
 * to execute
 */
ISR(timer1_irq_handler)
{
	iprintf("INFO :  %s: START: sp=0x%x\n", __FUNCTION__, get_sp());

	timer_irq_ack(timer1_device);
	timer_stop(timer1_device);

	esi_interrupt_enable();

	++isr_low_fired;

	EE_assert(2, isr_low_fired==1, 1);

	ActivateTask(Task1);
	while(1)
    	if(finished != 0)
    		break;
	iprintf("INFO :  %s: END\n", __FUNCTION__);

}

/*
 * This is the high priority interrupt handler which should interrupt the low
 * priority one above
 */
ISR(timer0_irq_handler)
{
	if (isr_low_fired != 0)
	{
		iprintf("INFO :    %s: START: sp=0x%x\n", __FUNCTION__, get_sp());

		timer_fired++;
		ActivateTask(Task2);
		if(timer_fired==1)
		{
			EE_assert(3, timer_fired==1, 2);
		}
		if(timer_fired==10)
		{
			finished = 1;
		    timer_stop(timer0_device);
		}
		iprintf("INFO :    %s: END\n", __FUNCTION__);
	}
	timer_irq_ack(timer0_device);
}



/*
 * MAIN TASK
*/
int main(void)
{
	EE_assert(1, TRUE, EE_ASSERT_NIL);

	iprintf("INFO : monostack EEtest5 - nested ISRs\n");

	/* This test uses two timers, 0 and 1, with timer 0 needing to interrupt
	 * at a rate of at least 20 x timer 1
	 * Be careful - if the interrupt rate of timer 1 is too high it may
	 * interrupt itself!
	 */
	timer_init(&timer0_device, 0, esi_get_frequency()/100, timer0_irq_handler);
	if (timer0_device == 0)
	{
		iprintf("ERROR: Timer 0 not available.\n");
		exit(EXIT_FAILURE);
	}
	timer_init(&timer1_device, 1, esi_get_frequency()/5,   timer1_irq_handler);
	if (timer1_device == 0)
	{
		iprintf("ERROR: Timer 1 not available.\n");
		exit(EXIT_FAILURE);
	}
	/* Enable interrupts to the CPU. */
	esi_interrupt_enable();

	while(finished == 0)
	{
		//spin
	}

	EE_assert_range(0,1,5);
  	if (EE_assert_last() != EE_ASSERT_YES)
  	{
		iprintf("ERROR : FAIL\n");
  	}
  	else
  	{
		iprintf("INFO : PASS\n");
  	}

	// Forever loop: background activities (if any) should go here
	for (;;);

	return 0;
}

