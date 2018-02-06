/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * A minimal EE demo to test the compilation chain in MULTISTACK mode.
 * In this first demo two task are activated and share the same stack but
 * the operating system is in MULTISTACK mode.
 * Author: 2012  Gianluca Franchino
 * Based on examples/cortex_mx/lm4f232xxxx/porting_examples_keil/EEtest0
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"


#define TRUE 1

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_FIRST_CYCLE,
  EE_ASSERT_TEN_CYCLES,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int counter = 0;
volatile int divisor = 0;

/*
 * TASK 1
 */
TASK(Task1)
{
	task1_fired++;
	if (task1_fired == 1)
		EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired ==1, EE_ASSERT_INIT);
}

/*
 * TASK 2
 */
TASK(Task2)
{
	task2_fired++;
	if (task2_fired == 1)
		EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired ==1, EE_ASSERT_TASK1_FIRED);
}

/*
 * MAIN TASK
 */
int main(void)
{
	/*Initilize the operating frequencies (CPU, Peripheral etc.)*/
	/*PCKD = PCKC = PCKB = PCKA = BCKPLL/8 = 10MHz*/
	/*ICK = PLL/2 = 40 MHz*/
	/*FCK = PLL/4 = 20 MHz*/
	EE_rskrx210_op_freq_setup();
	
	EE_rskrx210_leds_init(0xF);

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	/* now the background activities... */
	for (;;) {
		divisor++;
		if (divisor == 10000) {
			divisor = 0;
			counter++;
			ActivateTask(Task1);
			ActivateTask(Task2);
			if(counter==1)
				EE_assert(EE_ASSERT_FIRST_CYCLE, counter==1, EE_ASSERT_TASK2_FIRED);
			if(counter==10)
				break;
		}
	}

	EE_assert(EE_ASSERT_TEN_CYCLES, counter==10, EE_ASSERT_FIRST_CYCLE);
	EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TEN_CYCLES);
	result = EE_assert_last();

	/* Forever loop: background activities (if any) should go here */
	for (;result == 1;) {
		while (counter % 100000) counter++;
		EE_rskrx210_leds_toggle();
		counter++;
	}

}
