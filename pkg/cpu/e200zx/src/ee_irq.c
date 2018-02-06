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
 * Derived from the mico32 code.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#include <ee_internal.h>
#include "cpu/e200zx/inc/ee_irq_internal.h"
#include "cpu/e200zx/inc/ee_mcu_regs.h"

#ifdef EE_ISR_DYNAMIC_TABLE
/*
    Only with Dynamic ISR TAble the EE_e200z7_register_ISR method is defined
    and the Software ISR Table declared.
 */
/* Software Isr Table */
static EE_e200z7_ISR_handler EE_e200z7_ISR_table[EE_E200ZX_MAX_CPU_EXCP_C
	+ EE_E200ZX_MAX_EXT_IRQ];

void EE_e200z7_register_ISR(EE_UINT16 level, EE_e200z7_ISR_handler fun, EE_UINT8 pri)
{
	/*EE_UINT8 proc;*/
	EE_FREG intst = EE_e200z7_suspendIRQ();

	EE_e200z7_ISR_table[level] = fun;

	/* Set priority for external interrupts */
	if (level >= EE_E200ZX_MAX_CPU_EXCP_C) {
	        #if 0
		proc = EE_E200ZX_INTC_CURRPROC;
		#endif
		SET_INT_PRIO(level, pri);
	}

	EE_e200z7_resumeIRQ(intst);
}

/*
    The "complete" interrupt dispatcher EE_e200z7_irq is needed for handling
    dynamic ISR table.
 */
void EE_e200z7_irq(EE_UREG level)
{
	EE_e200z7_ISR_handler fh;
	EE_ORTI_runningisr2_type ortiold;

	EE_increment_IRQ_nesting_level();
	fh = EE_e200z7_ISR_table[level];
	if (fh != (EE_e200z7_ISR_handler)0) {
		ortiold = EE_ORTI_get_runningisr2();
		EE_ORTI_set_runningisr2(EE_ORTI_build_isr2id(fh));
		/* eventually call ISR handler in a new stack (it need nesting level) */
		EE_e200zx_call_ISR(fh, EE_IRQ_nesting_level);
		EE_ORTI_set_runningisr2(ortiold);
	}

	/* ISR2 instance clean-up as requested by AS */
	EE_std_end_IRQ_post_stub();

	/* Pop priority for external interrupts */
	if (level >= EE_E200ZX_MAX_CPU_EXCP_C) {
		/* Look at reference manual:
			 9.4.3.1.2 End-of-Interrupt Exception Handler NOTE
		*/
		EE_e200zx_mbar();
		INTC_EOIR.R = 0U;
	}
	EE_decrement_IRQ_nesting_level();
	if (!EE_is_inside_ISR_call()) {
		/*
		 * Outer nesting level: call the scheduler.  If we have
		 * also type-ISR1 interrupts, the scheduler should be
		 * called only for type-ISR2 interrupts.
		 * WTF?  It doesn't work, does it?
		 */
		EE_std_after_IRQ_schedule();
	}
}

#else /* EE_ISR_DYNAMIC_TABLE */

extern EE_e200z7_ISR_handler EE_e200z7_ISR_table[EE_E200ZX_MAX_CPU_EXCP_C
	+ EE_E200ZX_MAX_EXT_IRQ];

/* Simplified interrupt dispatcher used with static ISR table. */
void EE_e200z7_irq(EE_UREG level)
{
  EE_e200z7_ISR_handler f;
  f = EE_e200z7_ISR_table[level];
  if (f != (EE_e200z7_ISR_handler)0) {
    f();
  }
}
#endif /* EE_ISR_DYNAMIC_TABLE */

#ifdef __EE_MEMORY_PROTECTION__
/*
 * Expansion of the inline function in the common layer.  We have asm
 * post-IRQ stubs that need to call it.
 */
void EE_e200zx_after_IRQ_schedule(void);
void EE_e200zx_after_IRQ_schedule(void)
{
	EE_std_after_IRQ_schedule();
}
#endif /*__EE_MEMORY_PROTECTION__ */
