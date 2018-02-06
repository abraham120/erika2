/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Simple test for spinlocks and shared memory
 * Author: 2011 Francesco Esposito
 */

#include "support.h"

/* My shared data */
#ifdef __MSRP__

#ifdef USE_PRAGMAS
#pragma section EE_SHARED_NOTINIT_BEGIN
#pragma section EE_SHARED_FAST_NOTINIT_BEGIN
volatile int shared_data[SHARED_LONG_LEN];
#pragma section EE_SHARED_END
#pragma section EE_SHARED_FAST_OR_SLOW_END
#else
volatile int EE_SHARED_UDATA shared_data[SHARED_LONG_LEN];
#endif
#else
volatile int shared_data[SHARED_LONG_LEN];
#endif

/* Shared variable */
int shared_data_local[SHARED_LONG_LEN];

DeclareTask(TaskZ6_1);
DeclareTask(TaskZ6_2);
DeclareTask(TaskZ6_3);
DeclareTask(TaskZ6_4);

/* First task */
TASK(TaskZ6_1)
{
	delay(MEDIUM_DELAY);
	/* Write shared_data_local */
	set_shared_value(1,shared_data_local);

	ActivateTask(TaskZ6_2);
	TerminateTask();
}

/* Second task */
TASK(TaskZ6_2)
{
	int check_res;
	delay(SMALL_DELAY);

	/* Check shared_data_local */
	check_res = check_shared_value(1,shared_data_local);

	/* Exec concurrently with disturbing task */
	lock_var();
	delay(LARGE_DELAY);
	set_shared_value(2,shared_data);
	unlock_var();

	delay(MEDIUM_DELAY);

	/* If previous check is ok activate TaskZ6_3 */
	if (check_res == 1)
		ActivateTask(TaskZ6_3);
	/* If check is not ok the task activation chain terminates here */

	TerminateTask();
}

/* Third Task */
TASK(TaskZ6_3)
{
	int check_res;
	delay(LARGE_DELAY);
	/* 
	* Check shared_data. This is a syncronous read so
	* spinlock or resource use is unnecessary,
	* the variable is always checked after it is written
	*/
	check_res = check_shared_value(2,shared_data);
	
	ActivateTask(TaskZ6_1);
	TerminateTask();
}

/* Third Task */
TASK(TaskZ6_4)
{
	/* Activate disturbing task */
	/* It may reside in Z0 or Z6 according with OIL definition */
	delay(MEDIUM_DELAY);
	ActivateTask(disturbing_task);
}

/*
 * Interrupt handler for the decrementer timer
 */
#ifdef EE_ISR_DYNAMIC_TABLE
static void timer_interrupt(void)
{
	ActivateTask(TaskZ6_4);
}

static void init_decrementer_timer(void)
{
	EE_e200z7_register_ISR(10, timer_interrupt, 1);
	EE_e200z7_setup_decrementer(26000000);
}
#else /* EE_ISR_DYNAMIC_TABLE */
#include <ee_irq.h>

/* Declare ISR handler */
void timer_interrupt(void);

ISR2_INT(timer_interrupt)
{
	ActivateTask(TaskZ6_4);
}

static void init_decrementer_timer(void)
{
	EE_e200z7_setup_decrementer(26000000);
}
#endif /* EE_ISR_DYNAMIC_TABLE */

/*
 * MAIN TASK
 */
int main(void)
{
	/* System start-up */
	sys_start_up();

	/* Init decrementer */
	init_decrementer_timer();

	/* Start Operating System */
	StartOS(OSDEFAULTAPPMODE);

	while(1)
	;

	return 0;
}
