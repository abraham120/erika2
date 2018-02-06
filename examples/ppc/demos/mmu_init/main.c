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
 * Example of the static initialization of the MMU in the crt0.
 * Author: 2011 Bernardo  Dal Seno
 */


#include <ee.h>
#include <ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

#ifdef EE_ISR_DYNAMIC_TABLE
#define ISR(f) ISR2(f)
#else
#define ISR(f) ISR2_INT(f)
#endif

/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter, tick_counter;

/* started: Set to 1 at the beginning of main() */
int started;

/* Final result */
EE_TYPEASSERTVALUE result;

/* Assertion */
EE_TYPEASSERTVALUE EE_assertions[9];

#ifdef __VLE__
#define USE_VLE_FLAG EE_E200ZX_MMU_FLAG_VLE
#else
#define USE_VLE_FLAG EE_E200ZX_MMU_FLAG_FLE
#endif

const EE_MMU_ENTRY_T EE_e200zx_mmu_entries[] = {
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_1M,
		0xfff00000U | EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD,
		0xfff00000U | EE_E200ZX_MMU_PROT_SRWX },
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_16M,
		0x00000000U | EE_E200ZX_MMU_FLAG_CE | USE_VLE_FLAG,
		0x00000000U | EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SX
		| EE_E200ZX_MMU_PROT_UR | EE_E200ZX_MMU_PROT_UX },
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_1M,
		0xc3f00000U | EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD,
		0xc3f00000U | EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SW },
	{ EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_64K,
		0x40000000U | EE_E200ZX_MMU_FLAG_CE | USE_VLE_FLAG,
		0x40000000U | EE_E200ZX_MMU_PROT_SRWX },
	/* Invalid entries to erase any default entries */
	{ 0, 0, 0 },
	{ 0, 0, 0 }
};
const unsigned EE_e200zx_mmu_num_entries =
	sizeof(EE_e200zx_mmu_entries) / sizeof(EE_e200zx_mmu_entries[0]);

DeclareTask(Task1);


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
ISR(timer_interrupt)
{
	++tick_counter;
	if (tick_counter & 1)
		ActivateTask(Task1);
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
}


/*
 * Low-level initialization of the timer
 */
#ifdef EE_ISR_DYNAMIC_TABLE
static void init_timer(void)
{
	EE_e200z7_register_ISR(10, timer_interrupt, 0);
	EE_e200z7_setup_decrementer(500000);
}
#else
static void init_timer(void)
{
	EE_e200z7_setup_decrementer(500000);
}
#endif

extern void system_call(void);


/*
 * MAIN TASK
 */
int main(void)
{
	started = 1;
	EE_assert(1, 1, EE_ASSERT_NIL);
	EE_e200z7_enableIRQ();
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
