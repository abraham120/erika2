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
#include "test/assert/inc/ee_assert.h"

#include <stdio.h>
#include <stdlib.h>

extern int get_sp(void);

#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__
__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void)
{
  EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void)
{
  EE_hal_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void)
{
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i)
{
}
#endif


/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int task1_fired=0;
volatile int task2_fired=0;
volatile long int divisor = 0;
volatile int dummit_counter=0;

#define	DELAY_TIME	10000L

/* just a dummy delay */ 
void mydelay(long int end)
{
  	long int i;
  	for (i=0; i<end; i++)
  	{
  		asm("nop");
  	}
    
  	return;  
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 */
void led_blink(unsigned char theled)
{
	EE_leds_on(theled);
	mydelay((long int)DELAY_TIME);
	EE_leds_off(theled);
}


TASK(Task1)
{
	iprintf("INFO :%s: sp=0x%x\n", __FUNCTION__, get_sp());
  task1_fired++;
  if(task1_fired==1)
  	EE_assert(2, task1_fired==1, 1);
  led_blink(LED_0);
  led_blink(LED_1);
  led_blink(LED_2);
  TerminateTask();
}


TASK(Task2)
{
  static int which_led = 0;
	iprintf("INFO :%s: sp=0x%x\n", __FUNCTION__, get_sp());
  /* count the number of Task2 activations */
  task2_fired++;
  if(task2_fired==1)
  	EE_assert(3, task2_fired==1, 2);
  if (which_led) 
  {
    EE_leds_off(LED_3);
    which_led = 0;
  }
  else 
  {
	EE_leds_on(LED_3);
    which_led = 1;
  }
  TerminateTask();
}

// MAIN function 
int main()
{ 
	int counter=0;
	EE_assert(1, TRUE, EE_ASSERT_NIL);
	
	iprintf("INFO : multistack EEtest0 - single shared stack\n");

	EE_leds_init();

	mydelay(DELAY_TIME);

	/* let's start the multiprogramming environment...*/
	StartOS(OSDEFAULTAPPMODE);
  
  /* now the background activities... */
	for (;;)
	{
		divisor++;
		if (divisor == DELAY_TIME * 10)
		{
			divisor = 0;
			counter++;
			ActivateTask(Task1);
			ActivateTask(Task2);
			if (counter == 1)
				EE_assert(4, counter == 1, 3);
			if (counter == 10)
				break;
		}
	}

	EE_assert_range(0, 1, 4);
	if (EE_assert_last() != EE_ASSERT_YES)
	{
		iprintf("ERROR: FAIL\n");
	}
	else
	{
		iprintf("INFO : PASS\n");
	}
	return 0;
}

