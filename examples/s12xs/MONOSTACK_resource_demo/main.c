/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2010  Evidence Srl
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
*/ 

#include "ee.h"
#include "ee_irq.h"
#include "myapp.h"

#include "ee_s12regs.h"
#include "test/assert/inc/ee_assert.h"
#include "mcu/hs12xs/inc/ee_pit.h"
#include "mcu/hs12xs/inc/ee_sci.h"

#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

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
  	for (i=0; i<end; i++);
    
  	return;  
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
void led_blink(unsigned char theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_leds(led_status);
  EnableAllInterrupts();

  mydelay((long int)120000);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
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
  EE_led_0_on();
  for (j=0; j<10; j++) {
	mydelay((long int)10000);
	EE_sci_send_byte(SCI_0,j+'0');
	EE_sci_send_byte(SCI_0,' ');
  }
  EE_led_0_off();
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

  EE_led_1_on();
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
  EE_sci_send_byte(SCI_0,'\n');

  EE_led_1_off();
  ReleaseResource(Resource);

  TerminateTask();
}

int main(void)
{
  AppModeType startupmode;
  char *inc = "Increment mode when Task2 runs!!!";
  char *dec = "Decrement mode when Task2 runs!!!";
  char *intro = "I Love OSEK and Erika Enterprise!!!";

  EE_set_peripheral_frequency_mhz(2);
  EE_assert(1, TRUE, EE_ASSERT_NIL);		

  EE_sci_open(SCI_0,(unsigned long int)9600);
  EE_buttons_init(BUTTON_0,3);
  EE_leds_init();
  mydelay(10);
  message(intro);

  /* check if the first button is pressed or not */
  if (EE_button_get_B0()) {
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
  EE_pit0_init(99, 14, 2);
  
  while(task1_fired==0);
  EE_assert_range(0,1,3);
  EE_assert_last();
  
  for (;;);
}


void message(char* msg)
{
	//char * msg = ;
	EE_sci_send_bytes(SCI_0, msg,ALL);
	EE_sci_send_byte(SCI_0,'\n');
	return;	
}
