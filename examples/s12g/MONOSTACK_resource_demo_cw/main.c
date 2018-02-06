/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011  Evidence Srl
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
	Author: Dario Di Stefano, 2011
*/ 

#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"
#include "mcu/hs12xs/inc/ee_timer.h"
#include "mcu/hs12xs/inc/ee_sci.h"

#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;
volatile unsigned char led_status = 0;
volatile int mycounter=0;

/* just a dummy delay */ 
void mydelay(long int end)
{
	long int i;
	for (i=0; i<end; i++)
		;
}

TASK(Task1)
{
	unsigned char j;

	task1_fired++;
	if(task1_fired==1)
	EE_assert(3, task1_fired==1, 2);

	/* Lock the resource */
	GetResource(Resource);

	/* do a long loop, printing the numbers from 0 to 9 */
	EE_led_1_on();
	for (j=0; j<10; j++) {
		mydelay((long int)10000);
		EE_sci_send_byte(SCI_0,j+'0');
		EE_sci_send_byte(SCI_0,' ');
	}
	EE_led_1_off();
	EE_sci_send_byte(SCI_0,'\r');
	EE_sci_send_byte(SCI_0,'\n');

	/* Release the lock */
	ReleaseResource(Resource);

	TerminateTask();
}


/* High Priority Task.
 * This task simply decrements the counter depending on the current
 * applicationmode, and prints it using printf.
 */
TASK(Task2)
{
	int i;
	AppModeType currentmode;
	char * msg = "My Counter: ";
	unsigned char byte = 0;
  
	task2_fired++;
	if(task2_fired==1)
		EE_assert(2, task2_fired==1, 1);
  
	/* get the current application mode */
	currentmode = GetActiveApplicationMode();
  
	GetResource(Resource);

	EE_led_2_on();
	mydelay((long int)100000);
  
	/* decrement or increment the counter depending on the application mode */
	if ( currentmode==ModeIncrement )
		mycounter++;
	else
		mycounter--;
  
	EE_sci_send_bytes(SCI_0, msg,ALL);
	byte = ((mycounter%1000)/100)+'0';
	EE_sci_send_byte(SCI_0,byte);
	byte = ((mycounter%100)/10)+'0';
	EE_sci_send_byte(SCI_0,byte);
	byte = (mycounter%10)+'0';
	EE_sci_send_byte(SCI_0,byte);
	EE_sci_send_byte(SCI_0,'\r');
	EE_sci_send_byte(SCI_0,'\n');

	EE_led_2_off();
	ReleaseResource(Resource);

	TerminateTask();
}

void message(char* msg) {
	EE_sci_send_bytes(SCI_0, msg, ALL);
	EE_sci_send_byte(SCI_0,'\r');
	EE_sci_send_byte(SCI_0,'\n');
}

void board_init(void) {
	EE_set_clock_8MHz();
	PER0AD = 0x80;	// enable PU on PAD15 to enable COM
}

int main(void)
{
	int err;
	AppModeType startupmode;
	char *inc = "Increment mode when Task2 runs!!!";
	char *dec = "Decrement mode when Task2 runs!!!";
	char *intro = "I Love OSEK and Erika Enterprise!!!";

	board_init();
	EE_buttons_init(BUTTON_1);
	EE_leds_init();
	
	/* First assertion */
	EE_assert(1, TRUE, EE_ASSERT_NIL);

	err = EE_sci_open(SCI_0,(unsigned long int)9600);
	mydelay(10);
	message(intro);

	/* check if the first button is pressed or not */
	if (EE_button_get_B1()) {
		/* the button is not pressed */
		startupmode = ModeIncrement;
		message(inc);
	}
	else {
		/* the button is pressed */
		startupmode = ModeDecrement;
		mycounter = 1000;
		message(dec);
  }

	StartOS(startupmode);
	
	/* Program Timer 1 to raise interrupts */
	err = EE_timer_init_ms(EE_TIMER_7, 50, EE_TIMER_ISR_ON);
	EE_timer_start();

	while(task1_fired==0)
		;
	
	EE_assert_range(0,1,3);
	result = EE_assert_last();

	/* now the background activities... */
	while(1)
		;
}

