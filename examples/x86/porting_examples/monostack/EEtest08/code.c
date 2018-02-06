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
  EE_ASSERT_TIMER_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK1_GETRES,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK2_GETRES,
  EE_ASSERT_TASK2_RELRES,
  EE_ASSERT_TASK1_RELRES,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int counter = 0;


#define TEST_IRQ 42

void EE_pit_handler(void) {
  isr1_fired++;

  printf("----------Timer ISR, cnt: %d----------\n", isr1_fired);

  if (isr1_fired == 1) {
    EE_assert(EE_ASSERT_TIMER_FIRED, isr1_fired == 1, EE_ASSERT_INIT);
  }

  ActivateTask(Task1);
}

TASK(Task1)
{
  task1_fired++;

  printf("\tTask1 started. cnt: %d, getting resource\n", task1_fired);


  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TIMER_FIRED);
  }


  GetResource(Resource);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_GETRES, task1_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

  printf("\tTask1 Activating Task2\n");

  ActivateTask(Task2);

  printf("\tTask1: ReleaseResource\n");
  ReleaseResource(Resource);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_RELRES, task1_fired == 1, EE_ASSERT_TASK2_RELRES);
  }

  task1_ended++;

}

TASK(Task2)
{
  task2_fired++;

  printf("\t\tTask2 started. cnt: %d\n", task2_fired);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_GETRES);
  }

  printf("\t\tTask2 GetResource\n");
  GetResource(Resource);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_GETRES, task2_fired == 1, EE_ASSERT_TASK2_FIRED);
  }

  printf("\t\tTask2 ReleaseResource\n");
  ReleaseResource(Resource);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_RELRES, task2_fired == 1, EE_ASSERT_TASK2_GETRES);
  }

  task2_ended++;
  printf("\t\tTask2 finished.\n");

}


/*
 * MAIN TASK
*/
int main(void)
{

    printf("Starting ERIKA\n");

    EE_pit_init();
    EE_pit_set_periodic(20); // slow down to 20 Hz

    EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);

    EE_hal_enableIRQ(); // enable interrupt

    while(!(task1_ended && task2_ended));

    EE_assert(
      EE_ASSERT_TASKS_ENDED, task1_ended && task2_ended, EE_ASSERT_TASK1_RELRES
    );
    EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
    result = EE_assert_last();

    if(result == EE_ASSERT_YES) {
      printf("TEST SUCCESSFUL FINISHED!\n");
    } else {
      for(int i = 0; i < EE_ASSERT_DIM; i++) {
        printf("ASSERT %d : %d\n", i, EE_assertions[i]);
      }
      printf("TEST FAILED!\n");
    }



    printf("Shutdown\n");
    EE_hal_shutdown_system();
    __builtin_unreachable();
}

