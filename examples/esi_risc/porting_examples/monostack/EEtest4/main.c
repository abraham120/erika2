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

/* Information about the timer device, such as which interrupt it is using. */
static void * timer0_device;

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

volatile int counter_taskS = 0;
volatile int counter_taskR = 0;
volatile int counter_isr = 0;

TASK(Task1)
{
	counter_taskS++;
    EE_assert(2, counter_taskS==1, 1);
    while(1)
    {
    	if(counter_isr > 10)
    	{
    		break;
    	}
    }
    timer_stop(timer0_device);

    EE_assert(4, counter_taskS==1, 3);
}

TASK(Task2)
{
	counter_taskR++;
    EE_assert(5, counter_taskR==1, 4);
}

ISR(timer0_irq_handler)
{
	counter_isr++;
	if(counter_isr==1)
	{
		ActivateTask(Task2);
		EE_assert(3, counter_isr==1, 2);
	}

	timer_irq_ack(timer0_device);
}

/*
 * MAIN TASK
*/
int main(void)
{
	int counter = 0;
	EE_assert(1, TRUE, EE_ASSERT_NIL);

	iprintf("INFO : monostack EEtest4\n");

	timer_init(&timer0_device, 0, esi_get_frequency()/100, timer0_irq_handler);
	if (timer0_device == 0)
	{
		iprintf("ERROR: Timer 0 not available.\n");
		exit(EXIT_FAILURE);
	}

	/* Enable interrupts to the CPU. */
	esi_interrupt_enable();

	ActivateTask(Task1);
	counter++;
	EE_assert(6, counter==1, 5);
	
	EE_assert_range(0,1,6);
  	if (EE_assert_last() != EE_ASSERT_YES)
  	{
		iprintf("ERROR: FAIL\n");
  	}
  	else
  	{
		iprintf("INFO : PASS\n");
  	}
  	// Forever loop: background activities (if any) should go here
	for (;;);

	return 0;
}
