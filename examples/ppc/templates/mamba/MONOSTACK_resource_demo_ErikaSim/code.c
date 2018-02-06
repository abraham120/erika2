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

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int timer_fired;
volatile int button_fired;
volatile int taskhigh_fired;
volatile int tasklow_fired;

/* some prototypes... */
void mydelay(long int end);

volatile int mycounter=0;

/* just a dummy delay */ 
void mydelay(long int end)
{
  volatile long i;
  for (i=0; i<end; i++);
  return;  
}

/* Added for a finest debugger (run-time) tuning */
int tunable_delay = 50000;

/*
 * This is the Low priority task.
 * When the task runs, it locks a resource for a -long- time, preventing 
 * HighTask to preempt.
 */

TASK(Task1)
{
  tasklow_fired++;

  /* Lock the resource */
  GetResource(Resource);

  /* do something long */
  EE_led_1_on();
  mydelay((long int)tunable_delay);
  EE_led_1_off();
  EE_led_2_on();
  mydelay((long int)tunable_delay);
  EE_led_2_off();
  EE_led_3_on();
  mydelay((long int)tunable_delay);
  EE_led_3_off();
  EE_led_4_on();
  mydelay((long int)tunable_delay);
  EE_led_4_off();
  EE_led_5_on();
  mydelay((long int)tunable_delay);
  EE_led_5_off();
  EE_led_6_on();
  mydelay((long int)tunable_delay);
  EE_led_6_off();
  EE_led_7_on();
  mydelay((long int)tunable_delay);
  EE_led_7_off();
  
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
  AppModeType currentmode;
  
  taskhigh_fired++;

  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  GetResource(Resource);

  EE_led_0_on();
  mydelay((long int)tunable_delay);
  
  /* decrement or increment the counter depending on the application mode */
  if ( currentmode==ModeIncrement )
    mycounter++;
  else
    mycounter--;
  
  EE_led_0_off();
  ReleaseResource(Resource);

  TerminateTask();
}

volatile int timer_divisor = 0;

static void Counter_Interrupt(void)
{
  timer_divisor++;

  if (timer_divisor==100) {
    timer_divisor = 0;
    timer_fired++;
    ActivateTask(Task1);
  }

  /* reset the decrementer to fire again */
  EE_e200z7_setup_decrementer(2000);
}

static void Buttons_Interrupt(void)
{
  button_fired++;
  ActivateTask(Task2);
  EE_buttons_clear_ISRflag(BUTTON_0);
}

static void setup_interrupts(void)
{
  EE_e200z7_register_ISR(46 + 16, Buttons_Interrupt, 1);
  EE_e200z7_register_ISR(10, Counter_Interrupt, 0);
  EE_e200z7_setup_decrementer(2000);
  EE_e200z7_enableIRQ();
}

int main(void)
{

  AppModeType startupmode;

  EE_buttons_init(BUTTON_0,3);
  EE_leds_init();
  EE_leds(0);

  /* check if the first button is pressed or not */
  if (!EE_button_get_B0()) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
  }
  else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
  }

  setup_interrupts();
  StartOS(startupmode);
 
  for (;;);
}
