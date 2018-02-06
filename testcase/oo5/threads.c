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

void pause_and_display(int disp);

DeclareAlarm(alarm0);
DeclareAlarm(alarm1);
DeclareAlarm(alarm2);

TASK(thread0)
{
  AlarmBaseType t;

  EE_assert(5, 1, 50);

#ifdef __LEDS_USED__
  EE_led_1_on();
#endif
  
#ifdef __LCD_USED__
  pause_and_display(0x0);
#endif

  GetAlarmBase(alarm0, &t);  // should return an error

  EE_assert(6, 1, 5);

  SetRelAlarm(alarm0, 3, 3);
  EE_assert(7, 1, 6);

  SetAbsAlarm(alarm1, 2, 2);
  EE_assert(8, 1, 7);

  SetRelAlarm(alarm2, 2, 0);
  EE_assert(9, 1, 8);

  GetAlarmBase(alarm0, &t);
  EE_assert(10, 1, 9);


  {  // 1
    EE_oo_counter_tick(0);
    EE_assert(11, 1, 10);
    EE_oo_counter_tick(1);
    EE_assert(12, 1, 11);
    Schedule();
    EE_assert(13, 1, 12);
  }
  {  // 2  alarm 1,2
    EE_assert(14, 1, 13);
    EE_oo_counter_tick(0);
    EE_assert(15, 1, 70);
    EE_oo_counter_tick(1);
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(16, 1, 15);
#else
    EE_assert(16, 1, 51);
#endif
    Schedule();
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(17, 1, 51);
#else
    EE_assert(17, 1, 16);
#endif
  }
  {  // 3  alarm 0
    EE_assert(18, 1, 17);
    EE_oo_counter_tick(0);
    EE_assert(19, 1, 18);
    EE_oo_counter_tick(1);
    EE_assert(20, 1, 19);
    Schedule();
    EE_assert(21, 1, 60);
  }
  {  // 4  alarm 1 
    EE_assert(22, 1, 21);
    EE_oo_counter_tick(0);
    EE_assert(23, 1, 71);
    EE_oo_counter_tick(1);
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(24, 1, 23);
    //#else
    //    EE_assert(24, 1, 52);
    //#endif
    Schedule();
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    //    EE_assert(25, 1, 52);
    //#else
    EE_assert(25, 1, 24);
    //#endif
  }
  {  // 5  
    EE_assert(26, 1, 25);
    EE_oo_counter_tick(0);
    EE_assert(27, 1, 26);
    EE_oo_counter_tick(1);
    EE_assert(28, 1, 27);
    Schedule();
    EE_assert(29, 1, 28);
  }
  {  // 6  alarm 0,1,2
    EE_assert(30, 1, 29);
    EE_oo_counter_tick(0);
    EE_assert(31, 1, 72);
    EE_oo_counter_tick(1);
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(32, 1, 31);
    //#else
    //EE_assert(32, 1, 53);
    //#endif
    Schedule();
    EE_assert(33, 1, 61);
  }
  {  // 7  
    EE_assert(34, 1, 33);
    EE_oo_counter_tick(0);
    EE_assert(35, 1, 34);
    EE_oo_counter_tick(1);
    EE_assert(36, 1, 35);
    Schedule();
    EE_assert(37, 1, 36);
  }
  {  // 8  alarm 1,2 
    EE_assert(38, 1, 37);
    EE_oo_counter_tick(0);
    EE_assert(39, 1, 73);
    EE_oo_counter_tick(1);
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(40, 1, 39);
    //#else
    //    EE_assert(40, 1, 54);
    //#endif
    Schedule();
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    //    EE_assert(41, 1, 54);
    //#else
    EE_assert(41, 1, 40);
    //#endif
  }
  {  // 9  alarm 0
    EE_assert(42, 1, 41);
    EE_oo_counter_tick(0);
    EE_assert(43, 1, 42);
    EE_oo_counter_tick(1);
    EE_assert(44, 1, 43);
    Schedule();
    EE_assert(45, 1, 62);
  }
  {  // 10 alarm 1,2 
    EE_assert(46, 1, 45);
    EE_oo_counter_tick(0);
    EE_assert(47, 1, 74);
    EE_oo_counter_tick(1);
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(48, 1, 47);
    //#else
    //    EE_assert(48, 1, 55);
    //#endif
    Schedule();
    //#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    //EE_assert(49, 1, 55);
    //#else
    EE_assert(49, 1, 48);
    //#endif
  }

  EE_assert(80, 1, 49);
  SetAbsAlarm(alarm2, 14, 0);
  EE_assert(81, 1, 80);

  CancelAlarm(alarm0);
  EE_assert(82, 1, 81);
  CancelAlarm(alarm2);
  EE_assert(83, 1, 82);
  CancelAlarm(alarm1);
  EE_assert(84, 1, 83);

  SetRelAlarm(alarm0, 3, 3);
  EE_assert(85, 1, 84);
  SetAbsAlarm(alarm1, 12, 0);
  EE_assert(86, 1, 85);

  {  // 1  
    EE_oo_counter_tick(0);
    EE_assert(87, 1, 86);
    EE_oo_counter_tick(1);
    EE_assert(88, 1, 87);
    Schedule();
    EE_assert(89, 1, 88);
  }
  {  // 2  alarm 1
    EE_oo_counter_tick(0);
    EE_assert(90, 1, 75);
    EE_oo_counter_tick(1);
    EE_assert(91, 1, 90);
    Schedule();
    EE_assert(92, 1, 91);
  }
  {  // 3  alarm 0
    EE_oo_counter_tick(0);
    EE_assert(93, 1, 92);
    EE_oo_counter_tick(1);
    EE_assert(94, 1, 93);
    Schedule();
    EE_assert(95, 1, 63);
  }
  {  // 4  
    EE_oo_counter_tick(0);
    EE_assert(96, 1, 95);
    EE_oo_counter_tick(1);
    EE_assert(97, 1, 96);
    Schedule();
    EE_assert(98, 1, 97);
  }
  {  // 5  
    EE_oo_counter_tick(0);
    EE_assert(99, 1, 98);
    EE_oo_counter_tick(1);
    EE_assert(100, 1, 99);
    Schedule();
    EE_assert(101, 1, 100);
  }
  {  // 6  alarm 0
    EE_oo_counter_tick(0);
    EE_assert(102, 1, 101);
    EE_oo_counter_tick(1);
    EE_assert(103, 1, 102);
    Schedule();
    EE_assert(104, 1, 64);
  }
  {  // 7  
    EE_oo_counter_tick(0);
    EE_assert(105, 1, 104);
    EE_oo_counter_tick(1);
    EE_assert(106, 1, 105);
    Schedule();
    EE_assert(107, 1, 106);
  }
  {  // 8  
    EE_oo_counter_tick(0);
    EE_assert(108, 1, 107);
    EE_oo_counter_tick(1);
    EE_assert(109, 1, 108);
    Schedule();
    EE_assert(110, 1, 109);
  }
  {  // 9  alarm 0
    EE_oo_counter_tick(0);
    EE_assert(111, 1, 110);
    EE_oo_counter_tick(1);
    EE_assert(112, 1, 111);
    Schedule();
    EE_assert(113, 1, 65);
  }
  {  // 10  
    EE_oo_counter_tick(0);
    EE_assert(114, 1, 113);
    EE_oo_counter_tick(1);
    EE_assert(115, 1, 114);
    Schedule();
    EE_assert(116, 1, 115);
  }
  

#ifdef __LEDS_USED__
  EE_led_1_off();
#endif

  // there is no EE_assert_range here, because numbers are not
  // consecutive!
  EE_assert(0, 1, 116);

  EE_assert_last();

  TerminateTask();
}


int activations = 0;
TASK(thread1)
{
  switch (activations) {
  case 0:
    EE_assert(60, 1, 20); break;
  case 1:
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
    EE_assert(61, 1, 32); break;
#else
    EE_assert(61, 1, 32); break;
#endif
  case 2:
    EE_assert(62, 1, 44); break;
  case 3:
    EE_assert(63, 1, 94); break;
  case 4:
    EE_assert(64, 1, 103); break;
  case 5:
    EE_assert(65, 1, 112); break;
  default:
    EE_assert(0, 0, 0); break;
  }

#ifdef __LCD_USED__
  pause_and_display(0x1);
#endif
  activations++;
  TerminateTask();
}

#if defined(__OO_ECC1__) || defined(__OO_ECC2__)

TASK(thread2)
{
  { // 2
    EE_assert(50, 1, 4);
    WaitEvent(myevent);
    ClearEvent(myevent);
  }
  { // 4
    EE_assert(51, 1, 16);
    WaitEvent(myevent);
    ClearEvent(myevent);
  }
  EE_assert(0, 0, 0);
  /*
  { // 6
    EE_assert(52, 1, 24);
    WaitEvent(myevent);
    ClearEvent(myevent);
  }
  { // 8
    EE_assert(53, 1, 32);
    WaitEvent(myevent);
    ClearEvent(myevent);
  }
  { // 10
    EE_assert(54, 1, 40);
    WaitEvent(myevent);
    ClearEvent(myevent);
  }
  { // should never go out of this wait...
    EE_assert(55, 1, 48);
    WaitEvent(myevent);
    EE_assert(0, 0, 0);
  }
  */
  TerminateTask();
}

#else
TASK(thread2)
{
  EE_assert(50, 1, 4);
  TerminateTask();
}

int callback2_count = 1;
ALARMCALLBACK(mycallback2)
{
  switch (callback2_count) {
  case 1:
    EE_assert(51, 1, 15); break;
  case 2:
    EE_assert(52, 1, 23); break;
  case 3:
    EE_assert(53, 1, 31); break;
  case 4:
    EE_assert(54, 1, 39); break;
  case 5:
    EE_assert(55, 1, 47); break;
  default:
    EE_assert(0, 0, 0); break;
  }

  callback2_count++;
}

#endif

int callback1_count = 0;
ALARMCALLBACK(mycallback)
{
  switch (callback1_count) {
  case 0:
    EE_assert(70, 1, 14); break;
  case 1:
    EE_assert(71, 1, 22); break;
  case 2:
    EE_assert(72, 1, 30); break;
  case 3:
    EE_assert(73, 1, 38); break;
  case 4:
    EE_assert(74, 1, 46); break;
  case 5:
    EE_assert(75, 1, -1); break;
  default:
    EE_assert(0, 0, 0); break;
  }

  callback1_count++;
}

TASK(thread3)
{
#ifdef __LCD_USED__
  pause_and_display(0x3);
#endif
  TerminateTask();
}
