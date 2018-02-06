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
 * Simple project to test interprocessor events
 * Author: 2011  Bernardo  Dal Seno
 */

#include "shared.h"

EE_TYPEASSERTVALUE EE_SHARED_UDATA EE_assertions[asr_dim];
volatile int EE_SHARED_UDATA send_event;
int EE_SHARED_UDATA result;

DeclareTask(TaskZ6);

TASK(TaskZ6)
{
  EE_assert(asr_setevent1, 1, asr_taskz0bkg);
  SetEvent(TaskZ0Main, Event1);
  while (0 == send_event) {
    /* Wait for the ack of the other task */
  }
  send_event = 0;
  EE_assert(asr_setevent2, 1, asr_ackevent1);
  SetEvent(TaskZ0Main, Event2);
  while (0 == send_event) {
    /* Wait for the ack of the other task */
  }
  send_event = 0;
  EE_assert(asr_setevent2b, 1, asr_ackevent2);
  SetEvent(TaskZ0Main, Event2);
  TerminateTask();
}

/*
 * MAIN TASK
 */
int main(void)
{
  StatusType start_core_status;
  EE_assert(asr_init, 1, EE_ASSERT_NIL);
  /* Start Z0 from RAM */
  StartCore(OS_CORE_ID_1, &start_core_status);
  EE_assert(asr_core1_start, (start_core_status == E_OK), asr_init);
  EE_assert(asr_startz6, 1 , asr_core1_start);
  StartOS(OSDEFAULTAPPMODE);
}
