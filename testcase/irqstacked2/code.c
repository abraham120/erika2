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
 * Author: 2003 Paolo Gai
 * CVS: $Id: code.c,v 1.7 2006/01/05 14:35:52 pj Exp $
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#ifdef __EVALUATOR7T__
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"
#endif

EE_TYPEASSERTVALUE EE_assertions[8];

#define TRUE 1

#ifdef __ARM7GNU__
#ifdef __TRISCENDA7S__
void init_drivers(void);		//definito in initdrvs.c
#endif
#endif

EE_SEM mysem = {0,EE_NIL,EE_NIL};

void myhandler(void)
{
  EE_assert(3, TRUE, 2);
  EE_thread_activate(1);
  EE_timer_1_stop();
}

void thread0(void)
{
  int i;

  EE_assert(2, TRUE, 1);

  for (i =0; i< 100000; i++) {}

  EE_assert(5, TRUE, 4);

  EE_sem_post(&mysem);

  EE_assert(7, TRUE, 6);

}

void thread1(void)
{
  EE_assert(4, TRUE, 3);

  EE_sem_wait(&mysem);

  EE_assert(6, TRUE, 5);

}


void thread2(void) {}
void thread3(void) {}


void main(void)
{
#ifdef __EVALUATOR7T__
  EE_IC_clear_pending_IRQ();
  EE_IC_enable_external_IRQ(IRQ_TIMER1_MASK);
  EE_timer_1_set(10000);
  EE_timer_1_start();
#endif

#ifdef __TRISCENDA7S__
  init_drivers();
  EE_timer_1_set(0xf000);
  EE_timer_1_start();
#endif

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  EE_thread_activate(0);

  EE_assert_range(0,1,7);
  EE_assert_last();
  
  for (;;) {}
}
