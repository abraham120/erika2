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
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

volatile unsigned int taskp_counter=0;
volatile unsigned int taskc_counter=0;

TASK(Producer)
{
    /* 
        Note: Please note that this task structure is different from the
        typical one-shot structure presented in other examples. This
        structure with a forever loop inside the task body is much more
        similar to the one typically used in the POSIX standard, and it
        requires that every task has a PRIVATE STACK, especially if the
        task calls blocking functions like WaitSem.
    */
    EE_assert(2, TRUE, 1);
    for (;;) {
        SetEvent(Consumer,ProducerEvent);
        WaitEvent(ConsumerEvent);
        ClearEvent(ConsumerEvent);
        ++taskp_counter;

        /* the item has been consumed! */
        if(taskp_counter == 1) {
            EE_assert(5, TRUE, 4);
        } else if (taskp_counter == 4) {
            //SetEvent(Consumer,ProducerEvent);
            break;
        }
    } 
}

TASK(Consumer)
{
    EE_assert(3, TRUE, 2);
    for (;;) {
        WaitEvent(ProducerEvent);
        ++taskc_counter;

        ClearEvent(ProducerEvent);

        /* the item has been consumed! */
        if(taskc_counter == 1)
            EE_assert(4, TRUE, 3);

        SetEvent(Producer,ConsumerEvent);

        if(taskc_counter == 1)
        {
            EE_assert(6, TRUE, 5);
        } else if (taskc_counter == 3U) {
            break;
        }
    }
}

/*
 * MAIN TASK
 */

/* The loop is OK */

int main( void )
{
    EE_assert(1, TRUE, EE_ASSERT_NIL);

    /*  Start the Kernel that Activate the Producer the Consumer and switch to Producer.
        Executes and thenfinally blocks waiting for the Consumer to consume
        the item produced. After the Producer Blocks, the Background task
        resumes and the ActivateTask returns. */
    StartOS(OSDEFAULTAPPMODE);
    EE_assert(7, ((taskc_counter == 3U) && (taskp_counter == 3U)), 6);

    EE_assert_range(0, 1, 7);
    result = EE_assert_last();

    /*  Forever loop: background activities (if any) should go here.
        Please note that in this example the code never reach this point... */
    for (;;)
        ;

    return 0;
}
