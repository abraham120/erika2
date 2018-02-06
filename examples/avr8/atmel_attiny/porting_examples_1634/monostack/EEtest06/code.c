/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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
 *  A minimal EE demo that demostrates how the Erika BCC1 mode works.
 * This demo can be used to test Erika BCC1 files compilation, kernel start
 * procedure (StartOS(...)) and task termination (EE_s12xs_terminate_task(:::)).
 * Author: 2014  Giuseppe Serano
 * Based on examples/s12xs/porting_examples/monostack/EEtest6
 */


#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#include <avr/io.h>

#ifndef	F_CPU
/*! \brief Define default CPU frequency, if this is not already defined. */
#define	F_CPU	1000000UL
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Functions */
int func5(void)
{
	TerminateTask();
	return 1;
}

int func4(void)
{
	return func5();
}

int func3(void)
{
	return func4();
}


int func2(void)
{
	return func3();
}

int func1(void)
{
	return func2();
}

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int counter = 0;

/* Stack Pointers */
volatile EE_UINT16 task2_sp = 0x0000U;
volatile EE_UINT16 task1_sp = 0x0000U;
volatile EE_UINT16 main_sp = 0x0000U;

EE_UINT16 EE_currentSP( void ) {
#if	0
  __asm__ __volatile__(
    /* r24:r25 = SP */
    "in	r24, 0x3D\n"	/* SPL -> r24 */
    "in	r25, 0x3E\n"	/* SPH -> r25 */
    ::
  );
#else	/* 0 */
  return _SFR_IO16(_SFR_IO_ADDR(SP));
#endif	/* 0 */
}

/*
 * Timer ISR2
 */
ISR2(EE_AVR8_TIMER0_COMPA_ISR)
{

  EE_timer_0_stop();

  isr1_fired++;

  ActivateTask(Task2);

  EE_timer_init0(0x7FU);

  EE_timer_0_start();

}

/*
 * TASK 1
 */
TASK(Task1)
{

  EE_UINT16	curr_sp;

  curr_sp = EE_currentSP();
  if (curr_sp != task1_sp) {
    task1_sp = curr_sp;
  }

  task1_fired++;
  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TASK2_FIRED);
  }

#if	0	/* Forgetfulness Test!!! */
  TerminateTask();
  task1_ended++;
#endif	/* 0 */

}

/*
 * TASK 2
 */
TASK(Task2)
{

  EE_UINT16	curr_sp;

  curr_sp = EE_currentSP();
  if (curr_sp != task2_sp) {
    task2_sp = curr_sp;
  }

  task2_fired++;
  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_INIT);
  }

  ActivateTask(Task1);

  func1();

  task2_ended++;

}

/*
 * MAIN TASK
 */
int main(void)
{

  EE_UINT16	curr_sp;

  EE_mcu_init();

  EE_timer_init0(0x7FU);

  EE_timer_0_start();

  EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);

  StartOS(OSDEFAULTAPPMODE);

  EE_assert(
    EE_ASSERT_TASKS_ENDED, !task1_ended && !task2_ended, EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = EE_currentSP();
    if (curr_sp != main_sp) {
      main_sp = curr_sp;
    }

    counter++;

  }

}
