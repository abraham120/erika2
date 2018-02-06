/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2010  Evidence Srl
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
  *	Author: 2014 Martin Hoffmann, FAU Erlangen
  */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

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



void delay(unsigned int d) {
   unsigned int i;
   for (i = 0; i<d; i++) {
      asm volatile("nop");
      asm volatile("nop");
   }
}


TASK(Task1)
{
  task1_fired++;
  printf("\tTask1 started. cnt: %d\n", task1_fired);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_INIT);
  }

  printf("\tTask1 finished.\n");
}

TASK(Task2)
{
  task2_fired++;
  printf("\t\tTask2 started. cnt: %d\n", task2_fired);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

  printf("\t\tTask2 finished.\n");
}


/*
 * MAIN TASK
*/
int main(void)
{

  EE_uart_init(COM1);
  printf("Starting ERIKA\n");

  EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);
  EE_hal_enableIRQ(); // enable interrupt

  /* now the background activities... */
  for (;;)
  {
    divisor++;
    if (divisor == 10000)
    {
      divisor = 0;
      counter++;
      ActivateTask(Task1);
      ActivateTask(Task2);
      if (counter == 1) {
	    EE_assert(EE_ASSERT_FIRST_CYCLE, counter == 1, EE_ASSERT_TASK2_FIRED);
      }
      if (counter == 10) {
	    break;
      }
    }
  }

  EE_assert(EE_ASSERT_TEN_CYCLES, counter == 10, EE_ASSERT_FIRST_CYCLE);
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TEN_CYCLES);
  result = EE_assert_last();

  if(result == EE_ASSERT_YES) {
    printf("TEST SUCCESSFUL FINISHED!\n");
  } else {
    for(int i = 0; i < EE_ASSERT_DIM; i++) {
      printf("ASSERT %d : %d\n", i, EE_assertions[i]);
    }
    printf("TEST FAILED!\n");
  }


  printf("Shutdown ERIKA\n");
  EE_hal_shutdown_system();
  __builtin_unreachable();
}

