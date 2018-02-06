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
 * Example of use of the decrementer and the fixed-interval interrupts
 * Author: 2011 Bernardo  Dal Seno
 */

#include <ee.h>
#include <ee_irq.h>
#include "board/axiom_mpc5674fxmb/inc/ee_board.h"

DeclareTask(Task1);
DeclareTask(Task2);

void DecrIsr(void);
void FixedIntvIsr(void);

#ifdef EE_ISR_DYNAMIC_TABLE
#define ISR(f) ISR2(f)
#else
#define ISR(f) ISR2(f)
#endif /* EE_ISR_DYNAMIC_TABLE */

ISR(DecrIsr)
{
	ActivateTask(Task1);
}

ISR(FixedIntvIsr)
{
	ActivateTask(Task2);
}

#ifdef EE_ISR_DYNAMIC_TABLE
static void init_decrementer_timer(void)
{
	EE_e200z7_register_ISR(10, DecrIsr, 0);
	EE_e200z7_setup_decrementer(8000000);
}

static void init_fixed_timer(void)
{
	EE_e200z7_register_ISR(11, FixedIntvIsr, 1);
	EE_e200zx_setup_fixed_intv(64-23);
}
#else
static void init_decrementer_timer(void)
{
	EE_e200z7_setup_decrementer(8000000);
}

static void init_fixed_timer(void)
{
	EE_e200zx_setup_fixed_intv(64-23);
}
#endif /* EE_ISR_DYNAMIC_TABLE */

TASK(Task1)
{
	static unsigned char s;
	EE_led_set(1U, s);
	s = (s == 0 ? 1 : 0);
}

TASK(Task2)
{
	static unsigned char s;
	EE_led_set(2U, s);
	s = (s == 0 ? 1 : 0);
}

void main(void)
{
	EE_leds_init();
	init_decrementer_timer();
	init_fixed_timer();
	StartOS(OSDEFAULTAPPMODE);
	EE_hal_enableIRQ();
	while (1) {
		/* Background loop */
	}
}
