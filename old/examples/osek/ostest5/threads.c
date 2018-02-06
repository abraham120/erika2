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
 * Author: 2002 Paolo Gai
 * CVS: $Id: threads.c,v 1.2 2005/07/16 13:50:20 pj Exp $
 */

#include "ee.h"

void pause_and_display(int disp);

volatile int activations = 0;
volatile int callbacks = 0;

ALARMCALLBACK(mycallback)
{
  callbacks++;
}

DeclareAlarm(alarm0);
DeclareAlarm(alarm1);
DeclareAlarm(alarm2);

TASK(thread0)
{
  AlarmBaseType t;
  int x;
  
#ifdef __LEDS_USED__
  EE_led_1_on();
#endif
  
#ifdef __LCD_USED__
  pause_and_display(0x0);
#endif

  GetAlarmBase(alarm0, &t);  // should return an error

  SetRelAlarm(alarm0, 3, 3);
  SetAbsAlarm(alarm1, 2, 2);
  SetRelAlarm(alarm2, 2, 0);

  GetAlarmBase(alarm0, &t);
  
  for (x=0; x<10; x++) {
    EE_oo_counter_tick(0);
    EE_oo_counter_tick(1);
    Schedule();
  }

  SetAbsAlarm(alarm2, 14, 0);

  CancelAlarm(alarm0);
  CancelAlarm(alarm2);
  CancelAlarm(alarm1);

  SetRelAlarm(alarm0, 3, 3);
  SetAbsAlarm(alarm1, 12, 0);

  for (x=0; x<10; x++) {
    EE_oo_counter_tick(0);
    EE_oo_counter_tick(1);
    Schedule();
  }
  

#ifdef __LEDS_USED__
  EE_led_1_off();
#endif

  TerminateTask();
}



TASK(thread1)
{
#ifdef __LCD_USED__
  pause_and_display(0x1);
#endif
  activations++;
  TerminateTask();
}

#if defined(__OO_ECC1__) || defined(__OO_ECC2__)

TASK(thread2)
{
#ifdef __LCD_USED__
  pause_and_display(0x2);
#endif  
  for (;;) {
    WaitEvent(myevent);
    ClearEvent(myevent);
  }


  TerminateTask();
}

#else

TASK(thread2)
{
#ifdef __LCD_USED__
  pause_and_display(0x2);
#endif
  TerminateTask();
}

#endif


TASK(thread3)
{
#ifdef __LCD_USED__
  pause_and_display(0x3);
#endif
  TerminateTask();
}
