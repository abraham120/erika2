/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011  Evidence Srl
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
    Author: Errico Guidieri, 2012
  */

#include <time.h>
#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE 1
#endif /* TRUE */

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

volatile int counter_task = 0;
volatile int counter_isr = 0;

ISR2 (Timer_isr2) {
    /* Disable STM interrupt (use it just once) */
    STM0_ICR.B.CMP0EN = 0U;
    /* Reset sequest flag (just to be clean) */
    STM0_ICR.B.CMP0IR = 0U;
    /* Clear the service */
    SRC_STM0SR0.U = 0U;

    ActivateTask(Task1);
    EE_assert(3, counter_task == 0, 2);
    ++counter_isr;
    EE_assert(4, counter_isr == 1, 3);
}

TASK(Task1)
{
    ++counter_task;
    EE_assert(5, counter_task==1, 4);
    /* Without TerminateTask I test the EE_thread_not_terminated */
}

static void EE_tc27x_stm_timer_init() {
    unsigned int compare_value;
    unsigned int size_of_compare;

    /* Compare configuration. __clocks_per_sec is set in start-up code */
    compare_value   = (unsigned int)(__clocks_per_sec / 1000U);
    /* Adjust the size of the mask */
    size_of_compare = 31U - __clz (compare_value);

    STM0_CMCON.B.MSTART0 = 0U;
    STM0_CMCON.B.MSIZE0  = size_of_compare;
    STM0_CMP0.U          = compare_value;

    /* Enable STM Service Request Source
       Compare Register 0 (ICR.CMP0OS default
       value) */
    STM0_ICR.B.CMP0EN = 1U;
    
    /*
     *  STM0 service Request 0 configuration
     * (serviced by core 0)
     *
     * [0..7] SRPN = GPT12_T2_INTERRUPT_NR
     * [10] Service Request enable
     */
    SRC_STM0SR0.U = (1 << 10U) | EE_ISR2_ID_Timer_isr2;
}

/* The loop is OK */
EE_DO_PRAGMA(warning 557)

int main(void)
{
    EE_assert(1, TRUE, EE_ASSERT_NIL);
    StartOS(OSDEFAULTAPPMODE);
    EE_assert(2, TRUE, 1);
    /* I configure the timer after StartOS, so I can immediatly handle ISR  */
    EE_tc27x_stm_timer_init();
    while(counter_task < 1)
        ;   
    EE_assert_range(0,1,5);
    result = EE_assert_last();
    /* Forever loop: background activities (if any) should go here */
    for (;;)
    ;
}

