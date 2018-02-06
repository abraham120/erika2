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

#include "ee.h"
#include "test/assert/inc/ee_assert.h"
#include "../../common/test_common.h"

/* Map OLD names on new PPC IRQ API */
#ifdef __PPCE200ZX__
#define test_setup_irq() test_setup_irq(0U, isr_callback, 1U)
#define test_fire_irq()  test_fire_irq(0U)
#endif
#ifdef EE_TRICORE__
#define test_setup_irq() test_setup_irq(0U, isr_callback, 1U)
#define test_fire_irq()  test_fire_irq(0U)
#endif

#define TRUE 1

/* Assertion data */
enum assertions {
	ASSERT_INIT = 1,
	ASSERT_CALL_STARTOS,
	ASSERT_IRQ_FIRED,
	ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[ASSERT_DIM];


void isr_callback(void)
{
	EE_assert(ASSERT_IRQ_FIRED, TRUE, ASSERT_CALL_STARTOS);
	EE_assert_range(0, 1, ASSERT_DIM - 1);
	EE_assert_last();
}

int main(void)
{
	EE_assert(ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	/* Setup and queue an interrupt request; StartOS() should enable IRQs, so
	   the request is served */
	test_setup_irq();
	test_fire_irq();
	EE_assert(ASSERT_CALL_STARTOS, TRUE, ASSERT_INIT);
	StartOS(OSDEFAULTAPPMODE);

	while (1)
		;
}

DeclareTask(Task1);

TASK(Task1)
{
}
