/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.  ERIKA Enterprise is free software;
 * you can redistribute it and/or modify it under the terms of the
 * GPLv2 + Linking Exception license (contained in the file `ee/LICENSE').
 *
 * ERIKA Enterprise is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the license for more details.
 *
 * ###*E*### */

/*
 * Example of timing measurment with ORTI support
 * Author: 2011 Bernardo  Dal Seno
 */

#include <ee.h>
#include <ee_irq.h>

static int runcount;

/* Function declations */
DeclareTask(Task0);
DeclareTask(Task1);
DeclareTask(Task2);
void t1body(void);


static void DecrIsr(void)
{
	ActivateTask(Task1);
}

static void FixedIntvIsr(void)
{
	ActivateTask(Task2);
}

static void init_decrementer_timer(void)
{
	void App1Isr(void);
	EE_e200z7_register_ISR(10, DecrIsr, 0);
	EE_e200z7_setup_decrementer(500000);
}

static void init_fixed_timer(void)
{
	void App2Isr(void);
	EE_e200z7_register_ISR(11, FixedIntvIsr, 1);
	EE_e200zx_setup_fixed_intv(64-15);
}


/* just a dummy delay */ 
static void mydelay(int end)
{
	volatile int i;
	for (i = 0; i < end; i++)
		;
	return;	 
}


TASK(Task0)
{
	ActivateTask(Task1);
	runcount = 2;
	ActivateTask(Task2);
}


TASK(Task1)
{
	t1body();
}

void t1body(void)
{
	mydelay(150);
	runcount = 1;
	mydelay(350);
	TerminateTask();
}


TASK(Task2)
{
	/* count the number of Task2 activations */
	static t2runcount;
	++t2runcount;
	mydelay(100);
	TerminateTask();
}


int main(void)
{
	init_decrementer_timer();
	init_fixed_timer();
	StartOS(OSDEFAULTAPPMODE);
	EE_hal_enableIRQ();
	while (1) {
		/* Background loop */
	}
}
