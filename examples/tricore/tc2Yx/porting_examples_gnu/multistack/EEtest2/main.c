/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2012  Evidence Srl
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

#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE 1
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int counter_isr = 0;

ISR2 (Timer_isr2) {
    /* Reset sequest flag */
    STM0_ICR.B.CMP0IR = 0U;
    ++counter_isr;
    ActivateTask(Task1);
    ActivateTask(Task2);
    if(counter_isr == 1)
        EE_assert(2, task1_fired == 0 && task2_fired == 0, 1);
    if(counter_isr == 10) {
        /* Disable STM interrupt */
        STM0_ICR.B.CMP0EN = 0U;
        /* Clear the service */
        SRC_STM0SR0.U = 0U;
    }
}

/* Task1 */
TASK(Task1)
{
    ++task1_fired;
    if(task1_fired==1)
        EE_assert(4, task1_fired==1, 3);
}

/* Task2 */
TASK(Task2)
{
    /* count the number of Task2 activations */
    ++task2_fired;
    if(task2_fired==1)
        EE_assert(3, task2_fired==1, 2);
    TerminateTask();
}
/*
 * MAIN TASK
 */

/* The loop is OK */

int main( void )
{ 
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    StartOS(OSDEFAULTAPPMODE);
    EE_tc27x_stm_set_sr0(100U, EE_ISR2_ID_Timer_isr2);

    while (counter_isr < 10)
        ;

    EE_assert(5, task1_fired==10 && task2_fired==10 , 4);

    EE_assert_range(0,1,5);

    for (;;)
        ;

    return 0;
}

