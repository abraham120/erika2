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
 * A minimal EE demo that demonstrates how to work with the MULTISTACK mode.
 * In this first demo two task are activated and work with different stacks.
 * With this demo you can test the preemption mechanism with stack change. 
 * Author: 2014  Giuseppe Serano
 * Based on examples/s12xs/porting_examples/multistack/EEtest1
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
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_FIRST_CYCLE,
  EE_ASSERT_TEN_CYCLES,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
EE_TYPEASSERTVALUE result;

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int counter = 0;
volatile int divisor = 0;

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
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_INIT);
  }

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
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

}


/*
 * MAIN TASK
 */
int main(void)
{

  EE_UINT16	curr_sp;

  EE_mcu_init();

  EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);

  /* now the background activities... */
  for (;;)
  {
    divisor++;
    if (divisor == 100) 
    {
      divisor = 0;
      counter++;
      ActivateTask(Task1);
      ActivateTask(Task2);
      if (counter == 1)
	EE_assert(EE_ASSERT_FIRST_CYCLE, counter == 1, EE_ASSERT_TASK2_FIRED);
      if (counter == 10)
	break;
    }
  }

  EE_assert(EE_ASSERT_TEN_CYCLES, counter == 10, EE_ASSERT_FIRST_CYCLE);
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TEN_CYCLES);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = EE_currentSP();
    if (curr_sp != main_sp) {
      main_sp = curr_sp;
    }

    counter = 0;
    for (;;)
    {
      divisor++;
      if (divisor == 100) 
      {
	divisor = 0;
	counter++;
	ActivateTask(Task1);
	ActivateTask(Task2);
	if (counter == 10) {
	  break;
	}
      }
    }

  }

}
