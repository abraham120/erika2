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

#include "ee_internal.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE 1
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[11];

/* Final result */
EE_TYPEASSERTVALUE result;

/* To check task changes */
#define STACKS_SIZE 256U/sizeof(EE_STACK_T)
extern EE_UINT32 __USTACK_BEGIN[];
extern EE_UINT32 __USTACK[];

volatile int counter_task1 = 0;
volatile int counter_task2 = 0;
volatile int counter_isr1 = 0;
volatile int counter_isr2    = 0;
volatile EE_ADDR sp_isr1 = 0;


ISR2 (STM0_isr2) {
    /* Disable STM interrupt (use it just once) */
    STM0_ICR.B.CMP0EN = 0U;
    /* Reset sequest flag (just to be clean) */
    STM0_ICR.B.CMP0IR = 0U;
    /* Clear the service */
    SRC_STM0SR0.U = 0U;
    
    sp_isr1 = EE_tc_get_SP();
    
    EE_tc27x_stm_set_sr1(10U, EE_ISR2_ID_STM1_isr2);
    while(TRUE)
        if(counter_isr2)
            break;
    ++counter_isr1;
    ActivateTask(Task1);

    EE_assert(5, counter_task1 == 0 && counter_task2 == 0, 4);
    EE_assert(6, (EE_tc_IRQ_tos.SYS_tos - STACKS_SIZE) < sp_isr1 && sp_isr1 <= EE_tc_IRQ_tos.SYS_tos, 5);
}

ISR2 (STM1_isr2) {
    EE_ADDR sp_isr2;
    /* Disable STM interrupt (use it just once) */
    STM0_ICR.B.CMP1EN = 0U;
    /* Reset sequest flag (just to be clean) */
    STM0_ICR.B.CMP1IR = 0U;
    /* Clear the service */
    SRC_STM0SR1.U = 0U;

    sp_isr2 = EE_tc_get_SP();
    ++counter_isr2;
    ActivateTask(Task2);

    EE_assert(2, counter_task1 == 0 && counter_task2 == 0, 1);
    EE_assert(3, (EE_tc_IRQ_tos.SYS_tos - STACKS_SIZE) < sp_isr2 && sp_isr2 <= EE_tc_IRQ_tos.SYS_tos, 2);
    EE_assert(4, sp_isr2 <= sp_isr1, 3);
}

/* Task1 */
TASK(Task1)
{
    ++counter_task1;
    if(counter_task1 == 1) {
        EE_ADDR sp_task1 = EE_tc_get_SP();
        EE_assert(8, (EE_tc_system_tos[1].ram_tos - STACKS_SIZE) < sp_task1 && sp_task1 <= EE_tc_system_tos[1].ram_tos, 7);
    }
    TerminateTask();
}

/* Task2 */
TASK(Task2)
{
    /* count the number of Task2 activations */
    ++counter_task2;
    if(counter_task2 == 1) {
        EE_ADDR sp_task2 = EE_tc_get_SP();
        EE_assert(7, (EE_tc_system_tos[2].ram_tos - STACKS_SIZE) < sp_task2 && sp_task2 <= EE_tc_system_tos[2].ram_tos, 6);
    }
    TerminateTask();
}  
  

/*
 * MAIN TASK
 */

/* The loop is OK */

int main( void )
{
    EE_ADDR sp_system;
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    StartOS(OSDEFAULTAPPMODE);

    EE_tc27x_stm_set_sr0(10U, EE_ISR2_ID_STM0_isr2);

    while (counter_isr2 == 0U)
        ;
    sp_system = EE_tc_get_SP();
    EE_assert(9, (counter_task1 == (counter_task2 == (counter_isr2 == (counter_isr1 == 1)))), 8);
    EE_assert(10, (EE_ADDR)__USTACK_BEGIN < sp_system && sp_system <= (EE_ADDR)__USTACK, 9);

    EE_assert_range(0,1,10);

    /* now the background activities... */
    for (;;)
        ;

    return 0;
}

