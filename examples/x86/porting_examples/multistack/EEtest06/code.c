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
 * A minimal EE demo that demonstrates how to work with the MULTISTACK mode and
 * semaphores.
 * In this demo is shown that a task can be interrupted with a call to
 * ready2stacked (with an activation of a high priority task) and resumed with a
 * call to stkchange (if the high priority task is blocked on a shared
 * resource).
 * Author: 2014  Giuseppe Serano
 * Based on examples/s12xs/porting_examples/multistack/EEtest6
 */

/*
 *	Author: 2014 Martin Hoffmann, FAU Erlangen
 */

#include "ee.h"
#include "kernel/sem/inc/ee_sem.h"
#include "test/assert/inc/ee_assert.h"

/* This semaphore is initialized inside the Background Task */
SemType V;

/* Counters */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_POST,
  EE_ASSERT_TASK2_ENDED,
  EE_ASSERT_TASK1_ENDED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;


#define	TASK1_CYCLES	10000

TASK(Task1)
{
  volatile int i;

  task1_fired++;

  printf("Task1 activating Task2, act: %d\n", task1_fired);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_INIT);
  }

  ActivateTask(Task2);

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_POST, task1_fired == 1, EE_ASSERT_TASK2_FIRED);
  }

  /* take some time to produce an item */
  for (i = 0; i < TASK1_CYCLES; i++);

  /* the item has been produced! */
  printf("Task1, before PostSem V\n");

  PostSem(&V);

  printf("Task1, after PostSem V\n");

  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_ENDED, task1_fired == 1, EE_ASSERT_TASK2_ENDED);
  }

  task1_ended++;

}



#define	TASK2_CYCLES	TASK1_CYCLES
/*
 * TASK 2
 */
TASK(Task2)
{
  volatile int i;

  task2_fired++;

  printf("\tTask 2 activated, act: %d\n", task2_fired);

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_TASK1_FIRED);
  }

  printf("\tTask 2 before WaitSem V\n");

  WaitSem(&V);

  for (i = 0; i < TASK2_CYCLES; i++);

  printf("\tTask 2 after WaitSem V\n");

  if (task2_fired == 1) {
    EE_assert(EE_ASSERT_TASK2_ENDED, task2_fired == 1, EE_ASSERT_TASK1_POST);
  }

  task2_ended++;
}

/*
 * MAIN TASK
*/
int main(void)
{

  printf("Starting ERIKA\n");

  EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);

  InitSem(V, 0);

  ActivateTask(Task1);

  EE_assert(
    EE_ASSERT_TASKS_ENDED, task1_ended && task2_ended, EE_ASSERT_TASK1_ENDED
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

  printf("Shutdown ERIKA\n");
  EE_hal_shutdown_system();
  __builtin_unreachable();
}

