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
    Author:Errico Guidieri, 2012
 */

#include <ee.h>
#include "test/assert/inc/ee_assert.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;


/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter;

/*
 * Used to Test TerminateTask()
 */
void dummy_sub_function() {
    TerminateTask();
}

/*
 * Task 1
 */
TASK(Task1)
{
    ++counter;
    if (counter == 1)
    {
        /* This should return immediately.  We can check it
           by watching the values of the counters. */
        ActivateTask(Task1);
        EE_assert(2, TRUE, 1);
    }
    else if(counter==2) {
        EE_assert(4, TRUE, 3);
    }  else {
        EE_assert(5, FALSE, 1);
    }
    if(counter == 1) {
        /* CALL to dummy_sub_function */
        EE_tc_call(dummy_sub_function);
    } else {
        /* JUMP to dummy_sub_function */
        EE_tc_jump(dummy_sub_function);
    }
}

/*
 * MAIN TASK
 */
/* The loop is OK */

int main(void)
{
    EE_assert(1, TRUE, EE_ASSERT_NIL);
    StartOS(OSDEFAULTAPPMODE);
    ActivateTask(Task1);
    EE_assert(3, counter==1, 2);

    ActivateTask(Task1);
    EE_assert(5, counter==2, 4);

    EE_assert_range(0,1,5);
    result = EE_assert_last();

    /* Forever loop: background activities (if any) should go here */
    for (;;)
        ;
}

