/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2009-2011  Evidence Srl
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
	Author: Dario Di Stefano, 2011
*/ 

#include "ee.h"
#include "cpu/hs12xs/inc/ee_irqstub.h"
#include "test/assert/inc/ee_assert.h"
#include "ee_s12regs.h" 
#include "mcu/hs12xs/inc/ee_sci.h"

#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[10];

/* Final result */
EE_TYPEASSERTVALUE result;

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);

volatile int task1_fired=0;
volatile int task2_fired=0;

/* Task1 */
TASK(Task1)
{
	task1_fired++;
	/* Lock the resource */
	GetResource(Resource);
	EE_assert(3, task1_fired==1, 2);
	ActivateTask(Task2);
	EE_assert(4, task1_fired==1, 3);
	/* Release the lock */
	ReleaseResource(Resource);
}

/* Task2 */
TASK(Task2)
{
	task2_fired++;
	EE_assert(5, task2_fired==1, 4);
	GetResource(Resource);
	EE_assert(6, task1_fired==1, 5);
	ReleaseResource(Resource);
}

int main(void)
{
	EE_set_peripheral_frequency_mhz(8);
	
	_asm("cli");
	EE_assert(1, TRUE, EE_ASSERT_NIL);

	StartOS(OSDEFAULTAPPMODE);

	/* Initialize SCI0 */
	EE_sci_open(SCI_0, (unsigned long int)9600);
	SCI0CR2 = 0x8C; /* enable SCI0 IRQ */

	while(task2_fired<1)
		;
	EE_assert_range(0,1,6);
	result = EE_assert_last();

	while(1)
		;

	return 0;
}

