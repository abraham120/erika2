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
 * This example shows the following primitives:
 *
 * - GetActiveApplicationMode
 * - ReleaseResource
 * - GetResource
 *
 * The application starts in a different application mode depending on
 * the dip switch number 1 value
 *
 * The application is composed by two tasks:
 *
 * ledTask is a "long" low priority task that almost completely
 * executes in critical section. The task is activated by a timer.
 *
 * LCDTask is a high priority task, that increment/decrement a counter
 * depending on the application mode. it is executed in critical
 * section, and it is activated by the button.
 *
 * The behavior of the application shows that LCDTask have to wait for
 * LedTask to complete its critical section before being able to
 * execute.
 */

#include "ee.h"
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"

#define ONESECOND ((1 * 1000 * 1000 * 1000) / 20)
#define COUNTDOWN ONESECOND*3

volatile int task_fired=0;

void mydelay(void)
{
  int i;
  for (i=0; i<1300000; i++);
}

void ChristmasTree(void)
{
  EE_led_1_on(); mydelay(); EE_led_1_off();
  EE_led_2_on(); mydelay(); EE_led_2_off();
  EE_led_3_on(); mydelay(); EE_led_3_off();
  EE_led_4_on(); mydelay(); EE_led_4_off();
}


TASK(LedTask)
{
  GetResource(Resource);
  ChristmasTree();
  ReleaseResource(Resource);
  TerminateTask();
}

TASK(LCDTask)
{
  GetResource(Resource);

  if (GetActiveApplicationMode() == ModeIncrement)
    task_fired++;
  else
    task_fired--;

  EE_lcd_display(task_fired&0x0f);

  ReleaseResource(Resource);

  TerminateTask();
}

void ISR_Timer(void)
{
  ActivateTask(LedTask);
}

void ISR_Button(void)
{
  ActivateTask(LCDTask);
}

void main(void)
{
  AppModeType startupmode;

  EE_IC_clear_pending_IRQ();
  EE_timer_0_set(COUNTDOWN);
  EE_timer_0_start();

  EE_button_init();

  EE_lcd_init();
  EE_leds_init(); 
  EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
  EE_IC_enable_external_IRQ(IRQ_EXT0_MASK);


  if (EE_dip_switch_get() & 0x1)
    startupmode = ModeIncrement;
  else
    startupmode = ModeDecrement;

  StartOS(startupmode);
    
  for (;;);
}
