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
 * CVS: $Id: threads.c,v 1.1 2005/07/17 13:10:52 pj Exp $
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

/* the events */
DeclareEvent(myevent);

void pause_and_display(int disp);

TASK(thread0)
{
  EE_assert(8, 1, 7);

#ifdef __LEDS_USED__
  EE_led_1_on();
#endif

  pause_and_display(0x0);

  SetEvent(thread3, myevent);
  // preemption!

  EE_assert(16, 1, 15);

  pause_and_display(0x0);
  ActivateTask(thread2);

  pause_and_display(0x0);

#ifdef __LEDS_USED__
  EE_led_1_off();
#endif

  EE_assert_range(0, 1, 26);

  EE_assert_last();

  TerminateTask();
}

volatile int myerror=0;
TASK(thread1)
{
  EventMaskType m;

  EE_assert(7, 1, 6);

#ifdef __LEDS_USED__
  EE_led_2_on();
#endif

  pause_and_display(0x1);

  WaitEvent(myevent);
  //block

  EE_assert(21, 1, 20);

  pause_and_display(0x1);

  GetEvent(thread1, &m);

  EE_assert(22, 1, 21);

  if (m & myevent) {
    EE_assert(23, 1, 22);
    ClearEvent(myevent);
    EE_assert(24, 1, 23);
  }

  GetEvent(thread1, &m);

  EE_assert(25, 1, 24);

  if (m) {
    EE_assert(0, 0, 0);
    myerror++;
  }

  EE_assert(26, 1, 25);

  WaitEvent(myevent);

#ifdef __LEDS_USED__
  EE_led_2_off();
#endif

  TerminateTask();
}

TASK(thread2)
{
  EventMaskType m;

  EE_assert(17, 1, 16);

#ifdef __LEDS_USED__
  EE_led_3_on();
#endif

  pause_and_display(0x2);

  SetEvent(thread1, myevent);

  EE_assert(18, 1, 17);
  
  GetEvent(thread1, &m);

  EE_assert(19, 1, 18);

  if (m != myevent) {
    EE_assert(0, 0, 0);
    myerror++;
  }

#ifdef __LEDS_USED__
  EE_led_3_off();
#endif

  EE_assert(20, 1, 19);

  TerminateTask();
}

TASK(thread3)
{
  EventMaskType m;

  EE_assert(6, 1, 5);

#ifdef __LEDS_USED__
  EE_led_4_on();
#endif

  pause_and_display(0x3);

  WaitEvent(myevent);
  //block

  EE_assert(9, 1, 8);

  pause_and_display(0x3);

  GetEvent(thread3, &m);

  EE_assert(10, 1, 9);

  if (m & myevent) {
    EE_assert(11, 1, 10);
    ClearEvent(myevent);
    EE_assert(12, 1, 11);
  }

  EE_assert(13, 1, 12);

  GetEvent(thread3, &m);

  EE_assert(14, 1, 13);


  if (m) {
    EE_assert(0, 0, 0);
    myerror++;
  }

  EE_assert(15, 1, 14);

  WaitEvent(myevent);

  EE_assert(0, 0, 0);

#ifdef __LEDS_USED__
  EE_led_4_off();
#endif

  TerminateTask();
}
