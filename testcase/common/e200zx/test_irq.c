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
 * IRQ functions used in test cases for PPC e200zX
 * Author: 2011 Bernardo  Dal Seno
 */

#include <ee_irq.h>
#include "../test_common.h"
#include "cpu/e200zx/inc/ee_mcu_regs.h"

/* EXTRA Software IRQ support. I'll provide support only for software IRQ
   from o to 5 because software because software IRQ 6 and 7 are used in
   MPC5668 (Fado) for dual-core communication
   (look at mcu/freescale_mpc5668/inc/ee_dual.h).
*/

#define E200ZX_SOFT_IRQ_NUM  6

#ifdef EE_ISR_DYNAMIC_TABLE
static SoftIRQHandler soft_irq_handlers[E200ZX_SOFT_IRQ_NUM];

#define DEFINE_SOFT_IRQ_WRAPPER(IRQ)\
static void handler_wrapper_isr##IRQ(void) \
{ \
	SoftIRQHandler real_handler = soft_irq_handlers[(IRQ)]; \
	ACK_IRQ(IRQ); /* Ack the IRQ */ \
	if(real_handler != NULL) { /* check if the real handler is null */ \
		real_handler(); /* call the real handler */ \
	} \
}

#define SOFT_IRQ_WRAPPER(IRQ) handler_wrapper_isr##IRQ

DEFINE_SOFT_IRQ_WRAPPER(0)
DEFINE_SOFT_IRQ_WRAPPER(1)
DEFINE_SOFT_IRQ_WRAPPER(2)
DEFINE_SOFT_IRQ_WRAPPER(3)
DEFINE_SOFT_IRQ_WRAPPER(4)
DEFINE_SOFT_IRQ_WRAPPER(5)

static SoftIRQHandler soft_irq_wrappers[] = {
	SOFT_IRQ_WRAPPER(0),
	SOFT_IRQ_WRAPPER(1),
	SOFT_IRQ_WRAPPER(2),
	SOFT_IRQ_WRAPPER(3),
	SOFT_IRQ_WRAPPER(4),
	SOFT_IRQ_WRAPPER(5)
};

void test_setup_irq(unsigned int irq, SoftIRQHandler handler,
		unsigned int priority)
{
	if((irq > 5U) || (priority > 15U))
		return;

	soft_irq_handlers[irq] = handler;
	EE_e200z7_register_ISR(EE_E200ZX_MAX_CPU_EXCP + irq, soft_irq_wrappers[irq],
		priority);
}
#endif /* EE_ISR_DYNAMIC_TABLE */

void test_fire_irq(unsigned int irq)
{
	if(irq > 5U)
		return;
#if defined (EE_MPC5777C) || defined (EE_SPC574K)
	INTC_SSCIR(irq) = 2;
#else
	INTC.SSCIR[irq].R = 2;
#endif
	EE_e200zx_mbar();
}

