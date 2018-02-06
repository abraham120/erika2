/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Copyright (C) 2002-2013 Errico Guidieri
 */

#include "ee.h"
#include "ee_irq.h"

volatile int led_status   = 0;
volatile int task_counter = 0;

DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

void ErrorHook ( StatusType Error ) {
  while ( 1 ) {
    ;
  }
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
#define LED_ON_TIME_DELTA 50000U
static void led_blink(enum EE_tc2x5_led_id theled)
{
  DisableAllInterrupts();
  led_status |= theled;
  EE_tc2x5_set_leds_mask(led_status);
  EnableAllInterrupts();

  EE_tc2Yx_delay(LED_ON_TIME_DELTA);

  DisableAllInterrupts();
  led_status &= ~theled;
  EE_tc2x5_set_leds_mask(led_status);
  EnableAllInterrupts();
}

TASK(Task1)
{

  while (1) {
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_1, EE_TRIBOARD_2X5_LED_ON);
    StartScheduleTableRel( SchedTab1, 100);
    WaitEvent(ButtonEvent);
    ClearEvent(ButtonEvent);
    while ( task_counter < 1 ) {
      ;
    }
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_1, EE_TRIBOARD_2X5_LED_OFF);

    StopScheduleTable( SchedTab1 );

    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_2, EE_TRIBOARD_2X5_LED_ON);
    StartScheduleTableRel( SchedTab1, 200);
    WaitEvent(ButtonEvent);
    ClearEvent(ButtonEvent);
    while ( task_counter < 2 ) {
      ;
    }
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_2, EE_TRIBOARD_2X5_LED_OFF);

    NextScheduleTable( SchedTab1, SchedTab2 );

    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_3, EE_TRIBOARD_2X5_LED_ON);
    WaitEvent(TimerEvent);
    ClearEvent(TimerEvent);
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_3, EE_TRIBOARD_2X5_LED_OFF);

    /* Wait Schedule Table 2 */
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_4, EE_TRIBOARD_2X5_LED_ON);
    while ( task_counter < 3 ) {
      ;
    }
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_4, EE_TRIBOARD_2X5_LED_OFF);
    
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_5, EE_TRIBOARD_2X5_LED_ON);
    while ( task_counter < 4 ) {
      ;
    }
    EE_tc2x5_turn_led(EE_TRIBOARD_2X5_LED_5, EE_TRIBOARD_2X5_LED_OFF);
 
    /* Restart */
    task_counter = 0;
  }
  TerminateTask();
}

TASK(Task2)
{
  led_blink(EE_TRIBOARD_2X5_LED_6);
  ++task_counter;
  TerminateTask();
}

/* MAIN */
int main( void )
{
  /* Init leds */
  EE_tc2x5_leds_init();

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
