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
 * Simple project to test activation from an ISR with multistack
 * Author: 2010 Fabio Checconi
 * Based on examples/mico32/porting_examples/projects/mono_EEtest02
 */


#include <ee.h>
#include <ee_irq.h>

/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter1, counter2, tick_counter;

/* started: Set to 1 at the beginning of main() */
int started;

/*
 * Task 1
 */
TASK(Task1)
{
    ++counter1;
}

/*
 * Task 2
 */
TASK(Task2)
{
    ++counter2;
}

/*
 * Interrupt handler for the timer
 */
void timer_interrupt(void)
{
    ++tick_counter;
    ActivateTask(Task1);
    ActivateTask(Task2);
}

/*
 * Low-level initialization of the timer
 */
void init_timer(void)
{
    EE_e200z7_register_ISR(10, timer_interrupt, 0);
    EE_e200z7_setup_decrementer(1000000);
    EE_e200z7_enableIRQ();
}

/*
 * MAIN TASK
 */
int main(void)
{
    started = 1;
    init_timer();
    /* Wait until the third timer period */
    while (tick_counter < 3)
        ;
    started = 0;
    return 0;
}
