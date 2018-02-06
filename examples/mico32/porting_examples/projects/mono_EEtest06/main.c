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
 * Simple project to test static IRQ vector
 * Author: 2010,  Bernardo  Dal Seno
 */


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
volatile int counter, tick_counter;

/* started: Set to 1 at the beginning of main() */
int started;

/* Final result */
EE_TYPEASSERTVALUE result;

/* Assertion */
EE_TYPEASSERTVALUE EE_assertions[9];


/*
 * Task 1
 */
TASK(Task1)
{
    ++counter;
    if (counter == 1)
        EE_assert(3, tick_counter == 1, 2);
    else if (counter == 2)
        EE_assert(6, tick_counter == 3, 5);
}


/*
 * Interrupt handler for the timer
 */
void timer_interrupt(int level)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    timerc->Status = 0; /* Acknowledge the timer interrupt */
    ++tick_counter;
    switch (tick_counter) {
    case 1:
        EE_assert(2, counter == 0, 1);
        break;
    case 2:
        EE_assert(4, counter == 1, 3);
        break;
    case 3:
        EE_assert(5, counter == 1, 4);
        break;
    case 4:
        EE_assert(7, counter == 2, 6);
        break;
    }
    CounterTick(MainTimer);
}


/*
 * Low-level initialization of the timer
 */
void init_timer(void)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    /* Enable the interrupt */
    mico32_enable_irq(TIMER_IRQ);
    /* Raise an interrupt every 600 clock ticks */
    timerc->Period = 600;
    timerc->Control = MICO32_TIMER_CONTROL_INT_BIT_MASK |
        MICO32_TIMER_CONTROL_CONT_BIT_MASK |
        MICO32_TIMER_CONTROL_START_BIT_MASK;
}


/*
 * MAIN TASK
 */
int main(void)
{
    started = 1;
    EE_assert(1, 1, EE_ASSERT_NIL);
    SetRelAlarm(MyAlarm, 1, 2);
    EE_mico32_enableIRQ();
    init_timer();
    /* Wait until the fourth timer period */
    while (tick_counter < 4)
        ;
    EE_assert(8, counter == 2 && tick_counter == 4, 7);
    EE_assert_range(0, 1, 8);
    result = EE_assert_last();
    started = 0;
    return 0;
}
