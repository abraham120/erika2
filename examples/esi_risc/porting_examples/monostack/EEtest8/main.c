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
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Information about the timer0 device, such as which interrupt it is using. */
static void * timer0_device;

static void mydelay(int end);

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* A few counters incremented at each event 
 */
volatile int timer_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;

/* just a dummy delay */ 
static void mydelay(int end)
{
  	int i;
  	for (i=0; i<end; i++)
  	{
  		asm("nop");
  	}
    
  	return;  
}

TASK(Task1)
{
	timer_stop(timer0_device);

	task1_fired++;
  	
	/* Lock the resource */
  	GetResource(Resource);
  	EE_assert(3, task1_fired==1, 2);
  	ActivateTask(Task2);
  	EE_assert(4, task1_fired==1, 3);
  	//led_on(LED_0 | LED_1);
	mydelay(2000);
  	//led_off(LED_0 | LED_1);
  
  	/* Release the lock */
  	ReleaseResource(Resource);
	
  	//TerminateTask();
}


TASK(Task2)
{
  	task2_fired++;
  	EE_assert(5, task2_fired==1, 4);
  	GetResource(Resource);
  	EE_assert(6, task1_fired==1, 5);
  	//led_on(LED_2 | LED_3);
	mydelay(1000);
  	//led_off(LED_2 | LED_3);

  	ReleaseResource(Resource);
  	
	//TerminateTask();
}


ISR(timer0_irq_handler)
{
	timer_irq_ack(timer0_device);

	timer_divisor++;
	if (timer_divisor == 100) {
		timer_divisor = 0;
		timer_fired++;
		EE_assert(2, timer_fired==1, 1);
        ActivateTask(Task1);
	}

}

int main(void)
{
	iprintf("INFO : monostack EEtest8 - resource access test\n");

	EE_assert(1, TRUE, EE_ASSERT_NIL);
	
	/* Init leds */
	//EE_leds_init();
	
	mydelay(10);
   
  	StartOS(OSDEFAULTAPPMODE);

	timer_init(&timer0_device, 0, esi_get_frequency()/1000, timer0_irq_handler);
	if (timer0_device == 0)
	{
		iprintf("ERROR: Timer 0 not available.\n");
		exit(EXIT_FAILURE);
	}
	/* Enable interrupts to the CPU. */
	esi_interrupt_enable();
  
  	while(task2_fired<1);

  	EE_assert_range(0,1,6);
	if (EE_assert_last() != EE_ASSERT_YES)
	{
		iprintf("ERROR : FAIL\n");
	}
	else
	{
		iprintf("INFO : PASS\n");
	}
  
  	return 0;
}

