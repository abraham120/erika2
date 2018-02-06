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
#include "board/freescale_xpc564xl/inc/ee_board.h"

/* Let's declare the tasks identifiers */
DeclareTask(HighTask);
DeclareTask(LowTask);

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



/*
 * This is the Low priority task.
 * When the task runs, it locks a resource for a -long- time, preventing 
 * HighTask to preempt.
 */

TASK(LowTask)
{
  tasklow_fired++;

  /* Lock the resource */
  GetResource(Resource);

  /* do something long */
  EE_led_1_on();
  mydelay((long int)3000000);
  EE_led_1_off();
  EE_led_2_on();
  mydelay((long int)3000000);
  EE_led_2_off();
  EE_led_3_on();
  mydelay((long int)3000000);
  EE_led_3_off();
  
  /* Release the lock */
  ReleaseResource(Resource);
  
  TerminateTask();
}


/* High Priority Task.
 * This task simply decrements the counter depending on the current 
 * applicationmode, and prints it using printf.
 */
TASK(HighTask)
{
  int i;
  AppModeType currentmode;
  
  taskhigh_fired++;

  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  GetResource(Resource);

  EE_led_0_on();
  mydelay((long int)2000000);
  
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

  if (timer_divisor==4000) {
    timer_divisor = 0;
    timer_fired++;
    ActivateTask(LowTask);
  }

  /* reset the decrementer to fire again */
  EE_e200z7_setup_decrementer(40000);
}

static void Buttons_Interrupt(void)
{
  button_fired++;
  ActivateTask(HighTask);
  EE_buttons_clear_ISRflag(BUTTON_0);
}

static void setup_interrupts(void)
{
  EE_e200z7_register_ISR(41 + 16, Buttons_Interrupt, 1);
  EE_e200z7_register_ISR(10, Counter_Interrupt, 0);
  EE_e200z7_setup_decrementer(20000);
  EE_e200z7_enableIRQ();
}

int main(void)
{

  AppModeType startupmode;

  /* Init HW: PLLs, clock (120 Mhz), clear error flags, etc */
  InitHW();

  EE_buttons_init();
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
