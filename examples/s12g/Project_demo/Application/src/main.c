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
#include "mcu/hs12xs/inc/ee_timer.h"
#include "mcu/hs12xs/inc/ee_sci.h"
#include "inc/application.h"

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int timer_divisor = 0;
volatile unsigned char led_status = 0;

/* just a dummy delay */
void mydelay(long int end)
{
	long int i;
	for (i=0; i<end; i++)
		;
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 *
 * Note: led_blink is called both from Task1 and Task2. To avoid race
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the
 * critical section is -really- small. An example of critical section using
 * resources can be found in the osek_resource example.
 */

volatile long int mydelay_par = 60000;
void led_blink(unsigned char theled)
{
	DisableAllInterrupts();
	led_status |= theled;
	EE_leds(led_status);
	EnableAllInterrupts();

	mydelay(mydelay_par);

	DisableAllInterrupts();
	led_status &= ~theled;
	EE_leds(led_status);
	EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
	StatusType res;
	task1_fired++;

	/* First half of the christmas tree */
	led_blink(LED_1);
	led_blink(LED_2);
	/* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
	res = Schedule();
#endif
	/* Second half of the christmas tree */
	led_blink(LED_3);

	res = TerminateTask();
}

/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
	char *msg_tmr =  "ISR_Timer: ";
	char *msg_tsk1 = "Task_1: ";
	char *msg_btn =  "Button_1: ";
	char *msg_tsk2 = "Task_2: ";
	unsigned char byte = 0;
	int res;
	StatusType Res;

	/* count the number of Task2 activations */
	task2_fired++;
	
	/* Toggle LED4 */
	EE_led_4_toggle();

	/* prints a report
	* Note: after the first printf in main(), then only this task uses printf
	* In this way we avoid raceconditions in the usage of stdout.
	*/
	res = EE_sci_send_bytes(SCI_0, msg_tmr,ALL);
	byte = ((timer_fired%1000)/100)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = ((timer_fired%100)/10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = (timer_fired%10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	res = EE_sci_send_byte(SCI_0,' ');

	res = EE_sci_send_bytes(SCI_0, msg_tsk1,ALL);
	byte = ((task1_fired%1000)/100)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = ((task1_fired%100)/10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = (task1_fired%10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	res = EE_sci_send_byte(SCI_0,' ');

	res = EE_sci_send_bytes(SCI_0, msg_btn,ALL);
	byte = ((button_fired%1000)/100)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = ((button_fired%100)/10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = (button_fired%10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	res = EE_sci_send_byte(SCI_0,' ');

	res = EE_sci_send_bytes(SCI_0, msg_tsk2,ALL);
	byte = ((task2_fired%1000)/100)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = ((task2_fired%100)/10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);
	byte = (task2_fired%10)+'0';
	res = EE_sci_send_byte(SCI_0,byte);

	res = EE_sci_send_byte(SCI_0,'\r');
	res = EE_sci_send_byte(SCI_0,'\n');

	Res = TerminateTask();
}

void message(void)
{
	int res;
	char * msg = "I Love OSEK and Erika Enterprise!!!";
	res = EE_sci_send_bytes(SCI_0, msg,ALL);
	res = EE_sci_send_byte(SCI_0,'\r');
	res = EE_sci_send_byte(SCI_0,'\n');
}

void board_init(void)
{
	EE_set_clock_8MHz();
	PER0AD = 0x80;	// enable PU on PAD15 to enable COM
}

// MAIN function
int main()
{
	StatusType Res;
	int err;
	
	board_init();
	
	/* Init leds */
	EE_leds_init();
	
		/* Init devices */
	EE_buttons_init(BUTTON_1);
	
	/* Serial interface */
	err = EE_sci_open(SCI_0, (unsigned long int)9600);
	mydelay(10);
	message();
	
	/* let's start the multiprogramming environment...*/
	Res = StartOS(OSDEFAULTAPPMODE);
	
	/* Program Timer 1 to raise interrupts */
	err = EE_timer_init_ms(EE_TIMER_0, 100, EE_TIMER_ISR_ON);
	#ifdef __FP__
	SetRelAlarm(SystemAlarm, 1, 30);
	#endif
	EE_timer_start();

	/* now the background activities... */
	while(1)
		;
	return 0;
}

