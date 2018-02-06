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
#include "myapp.h"
#include "test/assert/inc/ee_assert.h"
#include "mcu/hs12xs/inc/ee_timer.h"

#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

volatile unsigned int ERROR_FLAG = 0;

DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int timer_fired = 0;
volatile int button_fired = 0;
volatile int dummit_counter = 0;
volatile int led_status = 0;
volatile int myErrorCounter;

/* just a dummy delay */ 
void mydelay(unsigned long int del)
{
  int i;
  for (i=0; i<del; i++);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged...
 */
void led_blink(unsigned char theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_leds(led_status);
  EnableAllInterrupts();

  mydelay((long int)125000);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
}

TASK(Task1)
{
  EventMaskType mask;
  
  task1_fired++;
  if(task1_fired==1)
  	EE_assert(2, task1_fired==1, 1);

  while (1) {
	EE_buttons_clear_ISRflag(BUTTON_0);	
	EE_buttons_enable_interrupts(BUTTON_0);	
    WaitEvent(TimerEvent|ButtonEvent);
    GetEvent(Task1, &mask);

    if (mask & TimerEvent) {
      led_blink(0x01);
      ClearEvent(TimerEvent);
    }

    if (mask & ButtonEvent) {
      led_blink(0x02);
      ClearEvent(ButtonEvent);
    }
  }
  TerminateTask();
}

TASK(Task2)
{
  /* count the number of Task2 activations */
  task2_fired++;
  if(task2_fired==1)
  	EE_assert(3, task2_fired==1, 2);	
	
  led_blink(0x04);
  TerminateTask();
}

void ErrorHook(StatusType Error)
{
  myErrorCounter++;
  ERROR_FLAG = Error;
  led_blink(0xFF);
}

/* 
 * The StartupHook in this case is used to initialize the Button and timer
 * interrupts
 */
void StartupHook(void)
{
  /* Init devices */
  EE_buttons_init(BUTTON_0,3);
  
  ///* Program Timer0 to raise interrupts */
  // ATT!!! Timer0 is configured in the StartOS using ee_utils.h
}

/* HAL StartOS: initialization routine */
int EE_s12_hal_cpu_startos(void)
{
    EE_timer_init_ms(EE_TIMER_7, 10, EE_TIMER_ISR_ON);
    EE_timer_counter_reset_enable();
    EE_timer_start();
    return 0;
}

/* MAIN */
int main(void)
{
  EE_set_peripheral_frequency_mhz(2);
  EE_assert(1, TRUE, EE_ASSERT_NIL);
  /* Serial interface */
  //EE_SCIOpenCommunication(SCI_0);

  /* Init leds */
  EE_leds_init();

  /* just a nice subliminal welcome message :-) */
  mydelay(1000);
  //message();

  StartOS(OSDEFAULTAPPMODE);
  
  while(task2_fired==0);
  EE_assert_range(0,1,3);
  result = EE_assert_last();

  /* Background activities, none in this demo! */
  while(1);
  
  return 0;
}

///* Other functions */
//void message(void)
//{
//	char * msg = "I Love OSEK and Erika Enterprise!!!";
//	EE_SCISendChars(SCI_0, msg,ALL);
//  EE_sci_send_byte(SCI_0,'\r');
//	EE_SCISendBuffer(SCI_0,'\n');
//	return;	
//}
