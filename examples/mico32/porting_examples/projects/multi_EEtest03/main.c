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
 * Simple project to test IRQ private stack
 * Author: 2010,  Bernardo  Dal Seno
 * Losely based on examples/s12xs/porting_examples/multistack/EEtest4
 */


#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Lattice Timer component */
#include <MicoTimer.h>
/* Erika Mico32 interrupts */
#include <cpu/mico32/inc/ee_irq.h>


/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter1, tick_counter;

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
 * Interrupt handler for the timer
 */
void timer_interrupt(int level)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    timerc->Status = 0; /* Acknowledge the timer interrupt */
    ++tick_counter;
    ActivateTask(Task1);
}


/*
 * Low-level initialization of the timer
 */
void init_timer(void)
{
    MicoTimer_t *timerc = (MicoTimer_t *)TIMER_BASE_ADDRESS;
    /* Register handler and enable the interrupt */
    EE_mico32_register_ISR(TIMER_IRQ, timer_interrupt);
    /* Raise an interrupt every 700 clock ticks */
    timerc->Period = 700;
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
    EE_mico32_enableIRQ();
    init_timer();
    /* Wait until the fourth timer period */
    while (tick_counter < 4)
        ;
    started = 0;
    return 0;
}
