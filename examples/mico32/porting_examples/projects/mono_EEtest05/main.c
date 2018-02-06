/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Simple project to test the TerminateTask()
 * Author: 2010,  Bernardo  Dal Seno
 * Based on examples/s12xs/porting_examples/monostack/EEtest6
 */

/* Functions that exercise the registers */
#include "dirty_regs.h"

#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Lattice Timer component */
#include <MicoTimer.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter1, counter2;

/* started: Set to 1 at the beginning of main() */
int started;

/* A register not restored correctly? */
int error;

/* Task are alive */
int task1_started, task2_started;

/* Final result */
EE_TYPEASSERTVALUE result;

/* Assertion */
EE_TYPEASSERTVALUE EE_assertions[11];



/*
 * Task 1
 */
int reclev1; /* Recursion level */

/* This recursive function contain computation before and after a recursive
 * call, so that the compiler cannot optimize by removing the call.  Also, the
 * variable `x' and `y' are alive across the call, so that registers must be
 * saved to hold them.  After 4 recursive calls, it calls TerminateTask(). */
int func1( int x )
{
    int r;
    int y = reclev1;
    ++reclev1;
    if (reclev1 < 5) {
        r = func1( x+1 );
    } else {
        r = 1;
        EE_assert(6, 1, EE_ASSERT_NIL);
    }
    if (reclev1 == 4) {
        EE_assert(7, 1, 6);
        TerminateTask();
    }
    --reclev1;
    return r + y + x;
}


void task1_body(void)
{
    EE_assert(5, counter1 == 0, 3);
    ++counter1;
    func1( 0 );
    ++counter1;
}


TASK(Task1)
{
    task1_started = 1;
    /* This should never return, because of TerminateTask() */
    error = dirty_regs(&task1_body, 72);
    task1_started = 2;
}


/*
 * Task 2
 */

void task2_body(void)
{
    ++counter2;
    EE_assert(2, task2_started == 1, EE_ASSERT_NIL);
    EE_assert(3, counter1 == 0, EE_ASSERT_NIL);
    ActivateTask(Task1);
    EE_assert(4, counter1 == 0, EE_ASSERT_NIL);
}

TASK(Task2)
{
    task2_started = 1;
    error = dirty_regs(&task2_body, 56);
    task2_started = 0;
    /* TerminateTask() is called implicitly */
}


/*
 * MAIN TASK
 */
int main(void)
{
    started = 1;
    EE_assert(1, 1, EE_ASSERT_NIL);
    StartOS(OSDEFAULTAPPMODE);
    EE_assert(8, error == 0, EE_ASSERT_NIL);
    EE_assert(9, task1_started == 1, EE_ASSERT_NIL);
    EE_assert(10, task2_started == 0, 2);
    EE_assert_range(0, 1, 10);
    result = EE_assert_last();
    started = 0;
    return 0;
}
