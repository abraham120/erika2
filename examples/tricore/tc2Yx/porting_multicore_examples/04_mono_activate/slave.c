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

/* started: Set to 1 at the beginning of main() */
int started;

volatile int z0c_started;

/* Final result */
EE_TYPEASSERTVALUE result;

/* Assertion */
enum assertions {
  asr_init = 1,
  asr_taskz0,
  asr_taskz0b,
  asr_taskz0c,
  asr_taskz0b_end,
  asr_dim
};

EE_TYPEASSERTVALUE EE_assertions[asr_dim];

DeclareTask(TaskZ0);
DeclareTask(TaskZ0b);
DeclareTask(TaskZ0c);

TASK(TaskZ0)
{
  EE_assert(asr_taskz0, 1, asr_init);
  ActivateTask(TaskZ6);
  TerminateTask();
}

TASK(TaskZ0b)
{
  EE_assert(asr_taskz0b, 1, asr_taskz0);
  ActivateTask(TaskZ6b);
  while(0 == z0c_started) {
    /* Wait for TaskZ0c */
  }

  EE_assert(asr_taskz0b_end, 1, asr_taskz0c);
  EE_assert_range(0, 1, asr_dim - 1);
  result = EE_assert_last();
  started = 0;
}

TASK(TaskZ0c)
{
  z0c_started = 1;
  EE_assert(asr_taskz0c, 1, asr_taskz0b);
  ActivateTask(TaskZ6c);
  TerminateTask();
}

/*
 * MAIN TASK
 */
int main(void)
{
  started = 1;
  EE_assert(asr_init, 1, EE_ASSERT_NIL);
  StartOS(OSDEFAULTAPPMODE);
}
