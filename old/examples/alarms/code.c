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
 * Author 2000-2002 Paolo Gai
 * CVS: $Id: code.c,v 1.4 2006/01/05 14:38:25 pj Exp $
 */


#include "ee.h"
#include "alarms/alarms.h"


/* Test Description:
   This test has 4 tasks with priority th1<th2<th3<th4

   This test uses:
   - Multistack
   - StartOS
   - ActivateTask into StartupHook (no preemption)
   - TerminateTask on the base level
   - Schedule with and without preemption
   - 2 alarms attached to a counter
   - 1 alarm attached to another counter
   - GetAlarmBase SetRelAlarm SetAbsAlarm CancelAlarm

   Basically, the test repeatly calls the tick function to increment
   ticks on the two counters. Only one task is used, the others are
   never activated...
*/

#include "code.h"

#ifdef __LCD_USED__
/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
#ifndef __H8__
#define LOOP_LENGHT 10000
#else
#define LOOP_LENGHT 1000
#endif
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void pause_and_display(int disp)
{
  int i=0;
  int j=0;
  
  for (i=0; i<LOOP_LENGHT; i++) {
#ifdef __LCD_USED__        
    EE_LCD_display(disp);
#endif
    for(j=0; j<10; j++) {
      /* do nothing */
    }
  }
}
#else
#define pause_and_display(x)
#endif



volatile int activations = 0;
volatile int callbacks = 0;

void mycallback(void)
{
  callbacks++;
}

void thread0(void)
{
  EE_TYPETICK t;
  int x;
  
#ifdef __LEDS_USED__
  EE_led_1_on();
#endif

#ifdef __LCD_USED__
    EE_play_note(_DO0, 10);
    EE_LCD_display(0);
#endif
    
  pause_and_display(0x0);

  EE_alarm_setrel(alarm0, 3, 3);
  EE_alarm_setabs(alarm1, 2, 2);
  EE_alarm_setrel(alarm2, 2, 0);

  EE_alarm_get(alarm0, &t);
  
  for (x=0; x<10; x++) {
    EE_counter_tick(0);
    EE_counter_tick(1);
    EE_sys_scheduler();
  }

  EE_alarm_setabs(alarm2, 14, 0);

  EE_alarm_cancel(alarm0);
  EE_alarm_cancel(alarm2);
  EE_alarm_cancel(alarm1);

  EE_alarm_setrel(alarm0, 3, 3);
  EE_alarm_setabs(alarm1, 12, 0);

  for (x=0; x<10; x++) {
    EE_counter_tick(0);
    EE_counter_tick(1);
    EE_sys_scheduler();
  }
  

#ifdef __LEDS_USED__
  EE_led_1_off();
#endif

#ifdef __LCD_USED__
    EE_LCD_clear();
#endif
}



void thread1(void)
{
  activations++;

#ifdef __LCD_USED__
    EE_LCD_display(1);
#endif
}

void main(void)
{
#ifdef __H8__
  EE_init();
#endif

#ifdef __LEDS_USED__
  EE_leds_init();
#endif

#ifdef __LCD_USED__
  EE_LCD_init();
#endif

  EE_thread_activate(0);
  EE_thread_activate(1);

  for (;;) {
    // Background activities, none in this test
#ifdef __LCD_USED__
    EE_LCD_display(-1);
#endif    
  }
}



