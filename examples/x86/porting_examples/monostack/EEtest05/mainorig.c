/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2010  Evidence Srl
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
  *	Author: 2014 Martin Hoffmann, FAU Erlangen
  */

#include "stdlib.h"
#include <math.h>
#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

volatile int counter_task1 = 0;
volatile int counter_task2 = 0;
volatile int counter_isr = 0;



#define TEST_IRQ 42

ISR(TEST_IRQ) {
    (void)ctx;
    ActivateTask(Task1);
    counter_isr++;
    printf("----------Test ISR (irq %d), cnt: %d----------\n", vector, counter_isr);


    EE_lapic_send_eoi();
}

TASK(Task1)
{
    counter_task1++;

    printf("\tTask1 activated. cnt: %d\n", counter_task1);
    printf("\tTask1 finished.\n");
}

TASK(Task2)
{
    counter_task2++;
    printf("\t\tTask2 activated. cnt: %d, triggering IRQ\n", counter_task2);
    EE_lapic_trigger(TEST_IRQ);
    printf("\t\tTask2 finished.\n");
}


/*
 * MAIN TASK
*/
int main(void)
{

    EE_uart_init(COM1);
    EE_uart_puts(COM1, "Starting ERIKA");

    EE_hal_enableIRQ(); // enable interrupt

	ActivateTask(Task2);


    EE_hal_shutdown_system();
    __builtin_unreachable();
}

