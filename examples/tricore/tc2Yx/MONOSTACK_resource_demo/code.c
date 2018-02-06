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

/* Let's declare the tasks identifiers */
DeclareTask(HighTask);
DeclareTask(LowTask);

volatile int timer_fired;
volatile int button_fired;
volatile int taskhigh_fired;
volatile int tasklow_fired;
volatile int mycounter=0;

#define LED_ON_TIME_DELTA 200000U
static void blink_led(enum EE_tc2x5_led_id led_id) {
  /* do something long */
  EE_tc2x5_turn_led(led_id,EE_TRIBOARD_2X5_LED_ON);
  EE_tc2Yx_delay(LED_ON_TIME_DELTA);
  EE_tc2x5_turn_led(led_id,EE_TRIBOARD_2X5_LED_OFF);
}

/*
 * This is the Low priority task.
 * When the task runs, it locks a resource for a -long- time, preventing 
 * HighTask to preempt.
 */
TASK(LowTask)
{
  ++tasklow_fired;

  /* Lock the resource */
  GetResource(Resource);
  blink_led(EE_TRIBOARD_2X5_LED_1);
  blink_led(EE_TRIBOARD_2X5_LED_2);
  blink_led(EE_TRIBOARD_2X5_LED_3);
  blink_led(EE_TRIBOARD_2X5_LED_4);
  blink_led(EE_TRIBOARD_2X5_LED_5);
  blink_led(EE_TRIBOARD_2X5_LED_6);
  blink_led(EE_TRIBOARD_2X5_LED_7);
  
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
  AppModeType currentmode;
  
  ++taskhigh_fired;

  /* get the current application mode */
  currentmode = GetActiveApplicationMode();
  
  GetResource(Resource);
  
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_8, EE_TRIBOARD_2X5_LED_ON);
  EE_tc2Yx_delay(LED_ON_TIME_DELTA / 2U);
  
  /* decrement or increment the counter depending on the application mode */
  if ( currentmode == ModeIncrement )
    ++mycounter;
  else
    --mycounter;
  
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_8, EE_TRIBOARD_2X5_LED_OFF);
  ReleaseResource(Resource);

  TerminateTask();
}

ISR2(button_handler)
{
    EE_tc2x5_button_irq_clear_request();
    ++button_fired;
    ActivateTask(HighTask);
}

int main( void ) {
  AppModeType startupmode;

  /* check if the first button is pressed or not */
  if (EE_tc2x5_read_button()) {
    /* the button is not pressed */
    startupmode = ModeIncrement;
  } else {
    /* the button is pressed */
    startupmode = ModeDecrement;
    mycounter = 1000;
  }

  /* Init IRQ button */
  EE_tc2x5_button_irq_init(EE_ISR2_ID_button_handler);

  /* Init leds */
  EE_tc2x5_leds_init();
  EE_tc2x5_leds_on();

  StartOS(startupmode);

  return 0;
}
