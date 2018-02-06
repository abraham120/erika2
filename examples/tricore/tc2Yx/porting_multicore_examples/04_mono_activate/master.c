/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Simple project to test interprocessor activations
 * Author: 2011  Bernardo  Dal Seno
 */

#include <ee.h>
#include <ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter, tick_counter;

/* started: Set to 1 at the beginning of main() */
int started;

/* Final result */
EE_TYPEASSERTVALUE result;

volatile int z6b_started;

/* Assertion */
enum assertions {
  asr_init = 1,
  asr_startz0,
  asr_taskz6,
  asr_taskz6b,
  asr_taskz6c,
  asr_dim
};
EE_TYPEASSERTVALUE EE_assertions[asr_dim];

DeclareTask(TaskZ6);
DeclareTask(TaskZ6b);
DeclareTask(TaskZ6c);


TASK(TaskZ6)
{
  EE_assert(asr_taskz6, 1, asr_startz0);
  ActivateTask(TaskZ0b);
  while (0 == z6b_started) {
    /* Wait for TaskZ6b */
  }
  TerminateTask();
}


TASK(TaskZ6b)
{
  z6b_started = 1;
  EE_assert(asr_taskz6b, 1, asr_taskz6);
  ActivateTask(TaskZ0c);
  TerminateTask();
}


TASK(TaskZ6c)
{
  EE_assert(asr_taskz6c, 1, asr_taskz6b);
  EE_assert_range(0, 1, asr_dim - 1);
  result = EE_assert_last();
  started = 0;
}



/*
 * MAIN TASK
 */
int main(void)
{
  StatusType core1_status;
  started = 1;
  EE_assert(asr_init, 1, EE_ASSERT_NIL);
  EE_assert(asr_startz0, 1, asr_init);
  StartCore(OS_CORE_ID_1,&core1_status);
  StartOS(OSDEFAULTAPPMODE);
}
