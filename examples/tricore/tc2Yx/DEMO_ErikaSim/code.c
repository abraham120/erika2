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
 * Author: Evidence Srl in collaboration with Lauterbach
 */

#include "ee.h"

#define LED_ON	1
#define LED_OFF	0

/* Dummy shared variable used by ALL tasks */
unsigned char dummy_shared_variable = 0;

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int task3_fired=0;
volatile int task4_fired=0;
volatile int task5_fired=0;
volatile int task6_fired=0;
volatile int task7_fired=0;

/* Added for a finest debugger (run-time) tuning */
static int tunable_delay = 500000;

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);
DeclareTask(Task5);
DeclareTask(Task6);
DeclareTask(Task7);

/* Event declaration */
DeclareEvent(TimerEvent);

/* some other prototypes */
void led_blink(unsigned char theled);

static void led_on(void)
{
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_8, EE_TRIBOARD_2X5_LED_ON);
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_4, EE_TRIBOARD_2X5_LED_OFF);
}

static void led_off(void)
{
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_8, EE_TRIBOARD_2X5_LED_OFF);
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_4, EE_TRIBOARD_2X5_LED_ON);
}

void led_blink(enum EE_tc2x5_led_id theled)
{
  DisableAllInterrupts();
  EE_tc2x5_turn_led(theled, EE_TRIBOARD_2X5_LED_ON);
  EnableAllInterrupts();

  EE_tc2Yx_delay(tunable_delay);

  DisableAllInterrupts();
  EE_tc2x5_turn_led(theled, EE_TRIBOARD_2X5_LED_OFF);
  EnableAllInterrupts();
}

/* Task1: just call the ChristmasTree */
TASK(Task1)
{
  task1_fired++;

  /* First half of the christmas tree */
  led_blink(EE_TRIBOARD_2X5_LED_1);
  led_blink(EE_TRIBOARD_2X5_LED_2);
  led_blink(EE_TRIBOARD_2X5_LED_3);

  /* Second half of the christmas tree */
  led_blink(EE_TRIBOARD_2X5_LED_5);
  led_blink(EE_TRIBOARD_2X5_LED_6);
  led_blink(EE_TRIBOARD_2X5_LED_7);
  
  TerminateTask();
}


/* Task2: blink led3 and led7 */
TASK(Task2)
{
  static int which_led = 0;

  task2_fired++;

  /* First click: led_3 on led_7 off */
  if (which_led) {
    led_on();
    which_led = 0;
  }
  else 
  {
    /* Second click: led_3 off led_7 on */
    led_off();
    which_led = 1;
  }

  TerminateTask();
}

TASK(Task3)
{
  task3_fired++;

  /* Lock the resource */
  GetResource(Resource);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 3;

  /* Release the lock */
  ReleaseResource(Resource);

  /* Lock the resource */
  GetResource(Resource3);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 6;

  /* Release the lock */
  ReleaseResource(Resource3);

  /* Lock the resource */
  GetResource(Resource2);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 12;

  /* Release the lock */
  ReleaseResource(Resource2);
  
  TerminateTask();
}

TASK(Task4)
{
  task4_fired++;

  /* Lock the resource */
  GetResource(Resource);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 4;

  /* Release the lock */
  ReleaseResource(Resource);

  /* Lock the resource */
  GetResource(Resource3);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 8;

  /* Release the lock */
  ReleaseResource(Resource3);
  
  TerminateTask();
}

TASK(Task5)
{
  task5_fired++;

  /* Lock the resource */
  GetResource(Resource);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 5;

  /* Release the lock */
  ReleaseResource(Resource);
  
  TerminateTask();
}

TASK(Task6)
{
  EventMaskType mask;
  
  while (1) {
    WaitEvent(TimerEvent);
    GetEvent(Task6, &mask);

    if (mask & TimerEvent) {
      ClearEvent(TimerEvent);
    }

    /* Lock the resource */
    GetResource(Resource2);

    /* Write to a dummy shared variable */
    dummy_shared_variable = 24;

    /* Release the lock */
    ReleaseResource(Resource2);
  }

  TerminateTask();
}

TASK(Task7)
{
  /* Lock the resource */
  GetResource(Resource3);

  /* Write to a dummy shared variable */
  dummy_shared_variable = 7;

  /* Release the lock */
  ReleaseResource(Resource3);

  TerminateTask();
}
 
ISR2(Buttons_Interrupt)
{
  button_fired++;
  ActivateTask(Task2);

   /* arm an alarm that will activate Task7 */
  SetRelAlarm(AlarmTask2,750,0);

  EE_tc2x5_button_irq_clear_request();
}

volatile int timer_divisor = 0;

/* EG: This could have been done better with system timer and alarms.
       In any case why mix just one alarm timer_divisor with 
       ActivateTask ? */
ISR2(Counter_Interrupt)
{
  /* Re-enable next TICK, Next Interrupt after another 1 ms */
  EE_tc2Yx_stm_set_sr0_next_match(1000);

  IncrementCounter(Counter1);

  timer_divisor++;

  if (timer_divisor == 1) {
    ActivateTask(Task3);
  }
  else if (timer_divisor == 100) {
    ActivateTask(Task4);
  }
  else if (timer_divisor == 200) {
    ActivateTask(Task5);
  }
  else if (timer_divisor==300) {
    timer_divisor = 0;
    timer_fired++;
    ActivateTask(Task1);
  }
  else {
    /* Dummy empty else statement */
  }
}

int main(void)
{
  /* Init IRQ button */
  EE_tc2x5_button_irq_init(EE_ISR2_ID_Buttons_Interrupt);
  /* Init leds */
  EE_tc2x5_leds_init();
  /* Initialize Timer for the Counter (One interrupt every 1 ms) */
  EE_tc2Yx_stm_set_sr0(1000, (EE_TYPEISR2PRIO)EE_ISR2_ID_Counter_Interrupt);
  
  /* setup_interrupts(); EG: No dynamic Table
      for TriCore only REAL OSEK support */
  
  /* let's start the multiprogramming environment...*/
  StartOS(OSDEFAULTAPPMODE);
  /* StartOs Never Return */

  return 0;
}
