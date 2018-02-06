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
 * - DeclareTask
 * - ActivateTask
 * - TerminateTask
 * - Schedule
 *
 * Version 1
 *
 * - Task1 is activated by an ISR2 with a timer. The timer activates a
 *   christmas tree
 * - Task2 is activated by an ISR2 with the button. 
 * - each time the button is pressed the display increments
 *
 * Version 2
 *
 * - In appl.oil, set Task1 as NON preemptive
 * - Task2 is activated both by pressing the button and by Timer1
 * - the display is only updated when the christmas tree is not
 *   running, with the correct number of ISR instances
 *
 * Version 3
 *
 * - In appl.oil, set Task1 as NON preemptive
 * - Task2 prints the number of TASK ACTIVATIONS
 * - the display is only updated when the christmas tree is not
 *   running, with the number of Task instances, that are less than
 *   the ISR because some activations are lost
 *
 * Version 4
 *
 * - In appl.oil, set Task1 as NON preemptive
 * - Task2 prints the number of TASK ACTIVATIONS
 * - Same as Version 3, but the task has a chance to run in the middle
 *   of teh christmas tree, due to the Schedule() call.
 */

// V1, V2, V3, V4
#define V1

#include "ee.h"
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"

#define ONESECOND ((1 * 1000 * 1000 * 1000) / 20)
#define COUNTDOWN ONESECOND*3

/* set by the ISR */
volatile int timer_fired=0;
volatile int button_fired=0;
volatile int task2_fired=0;

DeclareTask(Task1);
DeclareTask(Task2);

void mydelay(void)
{
  int i;
  for (i=0; i<1300000; i++);
}

void ChristmasTree(void)
{
  EE_led_1_on(); mydelay(); EE_led_1_off();
  EE_led_2_on(); mydelay(); EE_led_2_off();
#ifdef V4
  Schedule();
#endif
  EE_led_3_on(); mydelay(); EE_led_3_off();
  EE_led_4_on(); mydelay(); EE_led_4_off();
}


TASK(Task1)
{
  ChristmasTree();
  TerminateTask();
}

TASK(Task2)
{
  task2_fired++;
#if defined(V1) || defined(V2)
  EE_lcd_display(button_fired&0x0f);
#else
  EE_lcd_display(task2_fired&0x0f);
#endif
  TerminateTask();
}

void ISR_Timer(void)
{
  ActivateTask(Task1);
  timer_fired++;
}

void ISR_Button(void)
{
  ActivateTask(Task2);
  button_fired++;
}

void main(void)
{
  EE_IC_clear_pending_IRQ();
  EE_timer_0_set(COUNTDOWN);
  EE_timer_0_start();

  EE_timer_1_set(COUNTDOWN/10);
  EE_timer_1_start();

  EE_button_init();

  EE_lcd_init();
  EE_leds_init(); 
  EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
#ifndef V1
  EE_IC_enable_external_IRQ(IRQ_TIMER1_MASK);
#endif
  EE_IC_enable_external_IRQ(IRQ_EXT0_MASK);

  StartOS(OSDEFAULTAPPMODE);
  for (;;);
}
