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
 * This example shows the following task related primitives:
 *
 * SetEvent, ClearEvent, WaitEvent, SetRelAlarm
 *
 * This demo shows the usage of alarm and event primitives
 *
 * Task1 is an extended task that waits for two events:
 * - a timer event (action: led number 2)
 * - a button event (action: led number 3)
 *
 * The timer event is set by a periodic alarm notification.
 *
 * The button event is set explicitly inside the button interrupt handler.
 *
 * The button interrupt handler in turns sets a relative one-shot
 * alarm that activates task 2, that simply lights on led 1.
 *
 * If a breakpoint is set to ErrorHook, and the button is pressed
 * twice (rapidly), the system will call ErrorHook with an error
 * E_OS_STATE, because of the SetAlarm inside the interrupt handler.
 */

#include "ee.h"
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"

/*
 * "my" LED and LCD functions.
 * The Evaluator7T board maps both LED and LCD functions on the same
 * IO register. In this test, we call them with interrupt disabled to
 * avoid race conditions that typically lights up some spurious led.
 */

void my_led_1_on(void)
{ EE_arm7_disableIRQ(); EE_led_1_on(); EE_arm7_enableIRQ(); }

void my_led_2_on(void)
{ EE_arm7_disableIRQ(); EE_led_2_on(); EE_arm7_enableIRQ(); }

void my_led_3_on(void)
{ EE_arm7_disableIRQ(); EE_led_3_on(); EE_arm7_enableIRQ(); }

void my_led_4_on(void)
{ EE_arm7_disableIRQ(); EE_led_4_on(); EE_arm7_enableIRQ(); }

void my_led_1_off(void)
{ EE_arm7_disableIRQ(); EE_led_1_off(); EE_arm7_enableIRQ(); }

void my_led_2_off(void)
{ EE_arm7_disableIRQ(); EE_led_2_off(); EE_arm7_enableIRQ(); }

void my_led_3_off(void)
{ EE_arm7_disableIRQ(); EE_led_3_off(); EE_arm7_enableIRQ(); }

void my_led_4_off(void)
{ EE_arm7_disableIRQ(); EE_led_4_off(); EE_arm7_enableIRQ(); }

void my_lcd_display(int d)
{ EE_arm7_disableIRQ(); EE_lcd_display(d); EE_arm7_enableIRQ(); }









#define ONESECOND ((1 * 1000 * 1000 * 1000) / 20)
#define COUNTDOWN ONESECOND/4

volatile int timer_fired=0;

DeclareTask(Task1);
DeclareTask(Task2);
DeclareEvent(TimerEvent);
DeclareEvent(ButtonEvent);

void mydelay(void)
{
  int i;
  for (i=0; i<1300000; i++);
}




TASK(Task1)
{
  EventMaskType mask;

  while (1) {
    WaitEvent(TimerEvent|ButtonEvent);
    GetEvent(Task1, &mask);

    if (mask & TimerEvent) {
      my_led_2_on(); mydelay(); my_led_2_off();
      ClearEvent(TimerEvent);
    }

    if (mask & ButtonEvent) {
      my_led_3_on(); mydelay(); my_led_3_off();
      ClearEvent(ButtonEvent);
    }
  }
  TerminateTask();
}

TASK(Task2)
{
  my_led_1_on(); mydelay(); my_led_1_off();
  TerminateTask();
}

void ISR_Timer(void)
{
  timer_fired++;
  my_lcd_display(timer_fired&0x0f);

  EE_oo_counter_tick(Counter1);
}

void ISR_Button(void)
{
  SetRelAlarm(AlarmTask2, 5, 0);
  SetEvent(Task1, ButtonEvent);
}

int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
}

void main(void)
{
  EE_IC_clear_pending_IRQ();
  EE_timer_0_set(COUNTDOWN);
  EE_timer_0_start();

  EE_button_init();

  EE_lcd_init();
  EE_leds_init(); 
  EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
  EE_IC_enable_external_IRQ(IRQ_EXT0_MASK);

  StartOS(OSDEFAULTAPPMODE);
  for (;;);
}
