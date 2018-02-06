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
 * Author: 2002-2008 Paolo Gai
 */

#include "ee.h"
#include "ee_irq.h"
#include "board/axiom_mpc5674fxmb/inc/ee_board.h"

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

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile unsigned char led_status = 0;



/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

/* some other prototypes */
void mydelay(long int end);
void led_blink(unsigned char theled);



/* just a dummy delay */ 
void mydelay(long int end)
{
  	volatile long int i;
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

  mydelay((long int)300000);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_leds(led_status);
  EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;

  /* First half of the christmas tree */
  led_blink(LED_0);
  led_blink(LED_1);
  led_blink(LED_2);
  
  /* CONFIGURATION 3 and 4: we put an additional Schedule() here! */
#ifdef MYSCHEDULE
  Schedule();
#endif

  /* Second half of the christmas tree */
  /* we use led 4 5 and 6 because the board has two rows of 4 leds each */
  led_blink(LED_4);
  led_blink(LED_5);
  led_blink(LED_6);
  
  TerminateTask();
}


/* Task2: Print the counters on the JTAG UART */
TASK(Task2)
{
  static int which_led = 0;
  /* count the number of Task2 activations */
  task2_fired++;

  /* let blink leds 3 or 7 */
  if (which_led) {
    led_blink(LED_3);
    which_led = 0;
  }
  else 
  {
    led_blink(LED_7);
    which_led = 1;
  }

  TerminateTask();
}
 
static void Buttons_Interrupt(void)
{
   button_fired++;
   ActivateTask(Task2);
   EE_buttons_clear_ISRflag(BUTTON_0);
}

volatile int timer_divisor = 0;

static void Counter_Interrupt(void)
{
  timer_divisor++;

  if (timer_divisor==4000) {
    timer_divisor = 0;
    timer_fired++;
    ActivateTask(Task1);
  }

  /* reset the decrementer to fire again */
  EE_e200z7_setup_decrementer(40000);
}

static void setup_interrupts(void)
{
  EE_e200z7_register_ISR(46 + 16, Buttons_Interrupt, 1);
  EE_e200z7_register_ISR(10, Counter_Interrupt, 0);
  EE_e200z7_setup_decrementer(20000);
  EE_e200z7_enableIRQ();
}

int main(void)
{
  /* Init devices */
  EE_buttons_init(BUTTON_0,3);
  
  /* Init leds */
  EE_leds_init();
  
  setup_interrupts();
  
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  
  /* now the background activities... */
  for (;;);
  
  return 0;
}
