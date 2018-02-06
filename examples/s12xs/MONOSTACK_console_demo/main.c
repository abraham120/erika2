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
#include "console_serial.h"
#include "ee_s12regs.h"
#include "test/assert/inc/ee_assert.h"
#include "mcu/hs12xs/inc/ee_pit.h"

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

console_descriptor_t *my_console_1;

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

  mydelay((long int)60000);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;
  if(task1_fired==1)
  	EE_assert(3, task1_fired==1, 2);	
  
  /* First half of the christmas tree */
  led_blink(LED_0);
  led_blink(LED_1);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  	Schedule();
#endif

  /* Second half of the christmas tree */
  led_blink(LED_2);
  
  TerminateTask();
}

/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  static int which_led = 0;
  char *msg_tmr =  "Tmr: ";
  char *msg_tsk1 = "T_1: ";
  char *msg_btn =  "Btn: ";
  char *msg_tsk2 = "T_2: ";
  unsigned char byte = 0;
  
  /* count the number of Task2 activations */
  task2_fired++;
  
  if(task2_fired==1)
  	EE_assert(2, task2_fired==1, 1);

  /* let blink leds 6 or 7 */
  if (which_led) 
  {
	led_status &= (~LED_3);
    EE_led_3_off();
    which_led = 0;
  }
  else 
  {
	led_status |= LED_3;
	EE_led_3_on();
    which_led = 1;
  }

  /* prints a report
   * Note: after the first printf in main(), then only this task uses printf
   * In this way we avoid raceconditions in the usage of stdout.
   */
  console_write(MY_FIRST_CONSOLE,msg_tmr,6);
  byte = ((timer_fired%1000)/100)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = ((timer_fired%100)/10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = (timer_fired%10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);

  console_write(MY_FIRST_CONSOLE,msg_tsk1,6);
  byte = ((task1_fired%1000)/100)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = ((task1_fired%100)/10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = (task1_fired%10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  
  console_write(MY_FIRST_CONSOLE,msg_btn,6);
  byte = ((button_fired%1000)/100)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = ((button_fired%100)/10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = (button_fired%10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  
  console_write(MY_FIRST_CONSOLE,msg_tsk2,6);
  byte = ((task2_fired%1000)/100)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = ((task2_fired%100)/10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = (task2_fired%10)+'0';
  console_write(MY_FIRST_CONSOLE,&byte,1);
  byte = '\n';
  console_write(MY_FIRST_CONSOLE,&byte,1);

  TerminateTask();
}

// MAIN function 
int main()
{ 
  EE_set_peripheral_frequency_mhz(2);
  EE_assert(1, TRUE, EE_ASSERT_NIL);
  ///* Program Timer 1 to raise interrupts */
  EE_pit0_init(99, 14, 2);
  /* Init devices */
  EE_buttons_init(BUTTON_0,3);
  /* Init leds */
  EE_leds_init();

  mydelay(10);
  
  /* Application Init */
  my_console_1 = console_serial_config(MY_FIRST_SERIAL, 9600,0);
  console_init(MY_FIRST_CONSOLE, my_console_1);
  if (console_open(MY_FIRST_CONSOLE) == -1)
	  EE_leds_on();
  else
	  EE_leds_off();
  message();
  
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  while(task1_fired==0);
  EE_assert_range(0,1,3);
  EE_assert_last();
  
  /* now the background activities... */
  while(1);
  return 0;
}

int message(void)
{
	unsigned char byte;
	char* msg = "I Love OSEK and Erika Enterprise!!!     ";
	console_write(MY_FIRST_CONSOLE,msg,36);
	byte = '\n';
	return console_write(MY_FIRST_CONSOLE,&byte,1);
}
