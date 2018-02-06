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

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1
#define FALSE 0

#ifdef __OO_EXTENDED_STATUS__
#define myClearEvent s = ClearEvent
#define sEqualOK (s==E_OK)
#else
#define myClearEvent ClearEvent
#define sEqualOK TRUE
#endif


/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[160];

DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);
DeclareTask(Task5);
DeclareTask(Task6);
DeclareTask(Task7);
DeclareTask(Task8);
DeclareTask(Task9);
DeclareTask(Task10);
DeclareTask(Task11);
DeclareTask(Task12);
DeclareTask(Task13);
DeclareTask(Task14);
DeclareTask(Task15);
DeclareTask(Task16);

TASK(Task1)
{
  StatusType s;

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  s = ActivateTask(Task2);
  EE_assert(2, (s==E_OK), 1);

  s = ActivateTask(Task3);
  EE_assert(3, (s==E_OK), 2);

  s = ActivateTask(Task4);
  EE_assert(4, (s==E_OK), 3);

  s = ActivateTask(Task5);
  EE_assert(5, (s==E_OK), 4);

  s = ActivateTask(Task6);
  EE_assert(6, (s==E_OK), 5);

  s = ActivateTask(Task7);
  EE_assert(7, (s==E_OK), 6);

  s = ActivateTask(Task8);
  EE_assert(8, (s==E_OK), 7);

  s = ActivateTask(Task9);
  EE_assert(9, (s==E_OK), 8);

  s = ActivateTask(Task10);
  EE_assert(10, (s==E_OK), 9);

  s = ActivateTask(Task11);
  EE_assert(11, (s==E_OK), 10);

  s = ActivateTask(Task12);
  EE_assert(12, (s==E_OK), 11);

  s = ActivateTask(Task13);
  EE_assert(13, (s==E_OK), 12);

  s = ActivateTask(Task14);
  EE_assert(14, (s==E_OK), 13);

  s = ActivateTask(Task15);
  EE_assert(15, (s==E_OK), 14);

  s = ActivateTask(Task16);
  EE_assert(16, (s==E_OK), 15);

  myClearEvent(Task1_Event1);
  EE_assert(17, sEqualOK, 16);

  myClearEvent(Task1_Event2);
  EE_assert(18, sEqualOK, 17);

  myClearEvent(Task1_Event3);
  EE_assert(19, sEqualOK, 18);

  myClearEvent(Task1_Event4);
  EE_assert(20, sEqualOK, 19);

  myClearEvent(Task1_Event5);
  EE_assert(21, sEqualOK, 20);

  myClearEvent(Task1_Event6);
  EE_assert(22, sEqualOK, 21);

  myClearEvent(Task1_Event7);
  EE_assert(23, sEqualOK, 22);

  myClearEvent(Task1_Event8);
  EE_assert(24, sEqualOK, 23);

  TerminateTask();
}

TASK(Task2)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(25, TRUE, 24);

  myClearEvent(Task2_Event1);
  EE_assert(26, sEqualOK, 25);

  myClearEvent(Task2_Event2);
  EE_assert(27, sEqualOK, 26);

  myClearEvent(Task2_Event3);
  EE_assert(28, sEqualOK, 27);

  myClearEvent(Task2_Event4);
  EE_assert(29, sEqualOK, 28);

  myClearEvent(Task2_Event5);
  EE_assert(30, sEqualOK, 29);

  myClearEvent(Task2_Event6);
  EE_assert(31, sEqualOK, 30);

  myClearEvent(Task2_Event7);
  EE_assert(32, sEqualOK, 31);

  myClearEvent(Task2_Event8);
  EE_assert(33, sEqualOK, 32);

  TerminateTask();
}

TASK(Task3)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(34, TRUE, 33);

  myClearEvent(Task3_Event1);
  EE_assert(35, sEqualOK, 34);

  myClearEvent(Task3_Event2);
  EE_assert(36, sEqualOK, 35);

  myClearEvent(Task3_Event3);
  EE_assert(37, sEqualOK, 36);

  myClearEvent(Task3_Event4);
  EE_assert(38, sEqualOK, 37);

  myClearEvent(Task3_Event5);
  EE_assert(39, sEqualOK, 38);

  myClearEvent(Task3_Event6);
  EE_assert(40, sEqualOK, 39);

  myClearEvent(Task3_Event7);
  EE_assert(41, sEqualOK, 40);

  myClearEvent(Task3_Event8);
  EE_assert(42, sEqualOK, 41);

  TerminateTask();
}

TASK(Task4)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(43, TRUE, 42);

  myClearEvent(Task4_Event1);
  EE_assert(44, sEqualOK, 43);

  myClearEvent(Task4_Event2);
  EE_assert(45, sEqualOK, 44);

  myClearEvent(Task4_Event3);
  EE_assert(46, sEqualOK, 45);

  myClearEvent(Task4_Event4);
  EE_assert(47, sEqualOK, 46);

  myClearEvent(Task4_Event5);
  EE_assert(48, sEqualOK, 47);

  myClearEvent(Task4_Event6);
  EE_assert(49, sEqualOK, 48);

  myClearEvent(Task4_Event7);
  EE_assert(50, sEqualOK, 49);

  myClearEvent(Task4_Event8);
  EE_assert(51, sEqualOK, 50);

  TerminateTask();
}

TASK(Task5)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(52, TRUE, 51);

  myClearEvent(Task5_Event1);
  EE_assert(53, sEqualOK, 52);

  myClearEvent(Task5_Event2);
  EE_assert(54, sEqualOK, 53);

  myClearEvent(Task5_Event3);
  EE_assert(55, sEqualOK, 54);

  myClearEvent(Task5_Event4);
  EE_assert(56, sEqualOK, 55);

  myClearEvent(Task5_Event5);
  EE_assert(57, sEqualOK, 56);

  myClearEvent(Task5_Event6);
  EE_assert(58, sEqualOK, 57);

  myClearEvent(Task5_Event7);
  EE_assert(59, sEqualOK, 58);

  myClearEvent(Task5_Event8);
  EE_assert(60, sEqualOK, 59);

  TerminateTask();
}

TASK(Task6)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(61, TRUE, 60);

  myClearEvent(Task6_Event1);
  EE_assert(62, sEqualOK, 61);

  myClearEvent(Task6_Event2);
  EE_assert(63, sEqualOK, 62);

  myClearEvent(Task6_Event3);
  EE_assert(64, sEqualOK, 63);

  myClearEvent(Task6_Event4);
  EE_assert(65, sEqualOK, 64);

  myClearEvent(Task6_Event5);
  EE_assert(66, sEqualOK, 65);

  myClearEvent(Task6_Event6);
  EE_assert(67, sEqualOK, 66);

  myClearEvent(Task6_Event7);
  EE_assert(68, sEqualOK, 67);

  myClearEvent(Task6_Event8);
  EE_assert(69, sEqualOK, 68);

  TerminateTask();
}

TASK(Task7)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(70, TRUE, 69);

  myClearEvent(Task7_Event1);
  EE_assert(71, sEqualOK, 70);

  myClearEvent(Task7_Event2);
  EE_assert(72, sEqualOK, 71);

  myClearEvent(Task7_Event3);
  EE_assert(73, sEqualOK, 72);

  myClearEvent(Task7_Event4);
  EE_assert(74, sEqualOK, 73);

  myClearEvent(Task7_Event5);
  EE_assert(75, sEqualOK, 74);

  myClearEvent(Task7_Event6);
  EE_assert(76, sEqualOK, 75);

  myClearEvent(Task7_Event7);
  EE_assert(77, sEqualOK, 76);

  myClearEvent(Task7_Event8);
  EE_assert(78, sEqualOK, 77);

  TerminateTask();
}

TASK(Task8)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(79, TRUE, 78);

  myClearEvent(Task8_Event1);
  EE_assert(80, sEqualOK, 79);

  myClearEvent(Task8_Event2);
  EE_assert(81, sEqualOK, 80);

  myClearEvent(Task8_Event3);
  EE_assert(82, sEqualOK, 81);

  myClearEvent(Task8_Event4);
  EE_assert(83, sEqualOK, 82);

  myClearEvent(Task8_Event5);
  EE_assert(84, sEqualOK, 83);

  myClearEvent(Task8_Event6);
  EE_assert(85, sEqualOK, 84);

  myClearEvent(Task8_Event7);
  EE_assert(86, sEqualOK, 85);

  myClearEvent(Task8_Event8);
  EE_assert(87, sEqualOK, 86);

  TerminateTask();
}

TASK(Task9)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(88, TRUE, 87);

  myClearEvent(Task9_Event1);
  EE_assert(89, sEqualOK, 88);

  myClearEvent(Task9_Event2);
  EE_assert(90, sEqualOK, 89);

  myClearEvent(Task9_Event3);
  EE_assert(91, sEqualOK, 90);

  myClearEvent(Task9_Event4);
  EE_assert(92, sEqualOK, 91);

  myClearEvent(Task9_Event5);
  EE_assert(93, sEqualOK, 92);

  myClearEvent(Task9_Event6);
  EE_assert(94, sEqualOK, 93);

  myClearEvent(Task9_Event7);
  EE_assert(95, sEqualOK, 94);

  myClearEvent(Task9_Event8);
  EE_assert(96, sEqualOK, 95);

  TerminateTask();
}

TASK(Task10)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(97, TRUE, 96);

  myClearEvent(Task10_Event1);
  EE_assert(98, sEqualOK, 97);

  myClearEvent(Task10_Event2);
  EE_assert(99, sEqualOK, 98);

  myClearEvent(Task10_Event3);
  EE_assert(100, sEqualOK, 99);

  myClearEvent(Task10_Event4);
  EE_assert(101, sEqualOK, 100);

  myClearEvent(Task10_Event5);
  EE_assert(102, sEqualOK, 101);

  myClearEvent(Task10_Event6);
  EE_assert(103, sEqualOK, 102);

  myClearEvent(Task10_Event7);
  EE_assert(104, sEqualOK, 103);

  myClearEvent(Task10_Event8);
  EE_assert(105, sEqualOK, 104);

  TerminateTask();
}

TASK(Task11)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(106, TRUE, 105);

  myClearEvent(Task11_Event1);
  EE_assert(107, sEqualOK, 106);

  myClearEvent(Task11_Event2);
  EE_assert(108, sEqualOK, 107);

  myClearEvent(Task11_Event3);
  EE_assert(109, sEqualOK, 108);

  myClearEvent(Task11_Event4);
  EE_assert(110, sEqualOK, 109);

  myClearEvent(Task11_Event5);
  EE_assert(111, sEqualOK, 110);

  myClearEvent(Task11_Event6);
  EE_assert(112, sEqualOK, 111);

  myClearEvent(Task11_Event7);
  EE_assert(113, sEqualOK, 112);

  myClearEvent(Task11_Event8);
  EE_assert(114, sEqualOK, 113);

  TerminateTask();
}

TASK(Task12)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(115, TRUE, 114);

  myClearEvent(Task12_Event1);
  EE_assert(116, sEqualOK, 115);

  myClearEvent(Task12_Event2);
  EE_assert(117, sEqualOK, 116);

  myClearEvent(Task12_Event3);
  EE_assert(118, sEqualOK, 117);

  myClearEvent(Task12_Event4);
  EE_assert(119, sEqualOK, 118);

  myClearEvent(Task12_Event5);
  EE_assert(120, sEqualOK, 119);

  myClearEvent(Task12_Event6);
  EE_assert(121, sEqualOK, 120);

  myClearEvent(Task12_Event7);
  EE_assert(122, sEqualOK, 121);

  myClearEvent(Task12_Event8);
  EE_assert(123, sEqualOK, 122);

  TerminateTask();
}

TASK(Task13)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(124, TRUE, 123);

  myClearEvent(Task13_Event1);
  EE_assert(125, sEqualOK, 124);

  myClearEvent(Task13_Event2);
  EE_assert(126, sEqualOK, 125);

  myClearEvent(Task13_Event3);
  EE_assert(127, sEqualOK, 126);

  myClearEvent(Task13_Event4);
  EE_assert(128, sEqualOK, 127);

  myClearEvent(Task13_Event5);
  EE_assert(129, sEqualOK, 128);

  myClearEvent(Task13_Event6);
  EE_assert(130, sEqualOK, 129);

  myClearEvent(Task13_Event7);
  EE_assert(131, sEqualOK, 130);

  myClearEvent(Task13_Event8);
  EE_assert(132, sEqualOK, 131);

  TerminateTask();
}

TASK(Task14)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(133, TRUE, 132);

  myClearEvent(Task14_Event1);
  EE_assert(134, sEqualOK, 133);

  myClearEvent(Task14_Event2);
  EE_assert(135, sEqualOK, 134);

  myClearEvent(Task14_Event3);
  EE_assert(136, sEqualOK, 135);

  myClearEvent(Task14_Event4);
  EE_assert(137, sEqualOK, 136);

  myClearEvent(Task14_Event5);
  EE_assert(138, sEqualOK, 137);

  myClearEvent(Task14_Event6);
  EE_assert(139, sEqualOK, 138);

  myClearEvent(Task14_Event7);
  EE_assert(140, sEqualOK, 139);

  myClearEvent(Task14_Event8);
  EE_assert(141, sEqualOK, 140);

  TerminateTask();
}

TASK(Task15)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(142, TRUE, 141);

  myClearEvent(Task15_Event1);
  EE_assert(143, sEqualOK, 142);

  myClearEvent(Task15_Event2);
  EE_assert(144, sEqualOK, 143);

  myClearEvent(Task15_Event3);
  EE_assert(145, sEqualOK, 144);

  myClearEvent(Task15_Event4);
  EE_assert(146, sEqualOK, 145);

  myClearEvent(Task15_Event5);
  EE_assert(147, sEqualOK, 146);

  myClearEvent(Task15_Event6);
  EE_assert(148, sEqualOK, 147);

  myClearEvent(Task15_Event7);
  EE_assert(149, sEqualOK, 148);

  myClearEvent(Task15_Event8);
  EE_assert(150, sEqualOK, 149);

  TerminateTask();
}

TASK(Task16)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif

  EE_assert(151, TRUE, 150);

  myClearEvent(Task16_Event1);
  EE_assert(152, sEqualOK, 151);

  myClearEvent(Task16_Event2);
  EE_assert(153, sEqualOK, 152);

  myClearEvent(Task16_Event3);
  EE_assert(154, sEqualOK, 153);

  myClearEvent(Task16_Event4);
  EE_assert(155, sEqualOK, 154);

  myClearEvent(Task16_Event5);
  EE_assert(156, sEqualOK, 155);

  myClearEvent(Task16_Event6);
  EE_assert(157, sEqualOK, 156);

  myClearEvent(Task16_Event7);
  EE_assert(158, sEqualOK, 157);

  myClearEvent(Task16_Event8);
  EE_assert(159, sEqualOK, 158);

  TerminateTask();
}

#ifndef __OO_AUTOSTART_TASK__
void StartupHook(void)
{
  ActivateTask(Task1);
}
#endif

int main(int argc, char **argv)
{
#if defined(__ARM7GNU__) && defined(__JANUS__)
  EE_janus_IRQ_enable_EIC();
#endif

#if defined(__CORTEX_MX__)
  /*Initializes Erika related stuffs*/
  EE_system_init();
#endif

  StartOS(OSDEFAULTAPPMODE);

  EE_assert_range(0,1,159);
  EE_assert_last();

  return 0;
}

#ifdef __JANUS__
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}
#endif
