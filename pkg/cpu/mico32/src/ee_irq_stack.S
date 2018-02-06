/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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

/** 
	@file ee_irq_stack.S
	@brief Stack switch for ISRs on Mico32. 
	Implementation of EE_mico32_call_ISR_new_stack() as described in
	pkg/cpu/mico32/inc/ee_irq_internal.h
	@author Bernardo  Dal Seno
	@date 2009-2010
*/  

#include <cpu/mico32/inc/ee_irq_asm.h>

	
        .section        .bss
	.global	EE_mico32_tmp_tos
	.type	EE_mico32_tmp_tos, @object
	.balign	4
EE_mico32_tmp_tos:
        .space  4
	.size	EE_mico32_tmp_tos, .-EE_mico32_tmp_tos

	
	.text

/* 
void EE_mico32_call_ISR_new_stack(
    int irq_level, EE_mico32_ISR_handler fun, int nesting_level)
{
    if (nesting_level == 1)
        change_stacks();
    EE_std_enableIRQ_nested(); // Enable IRQ if nesting is allowed
    fun();
    EE_std_disableIRQ_nested(); // Disable IRQ if nesting is allowed
    if (nesting_level == 1)
        change_stacks_back();
}
*/

	.global EE_mico32_call_ISR_new_stack
	.type	EE_mico32_call_ISR_new_stack, @function
/* void EE_mico32_call_ISR_new_stack(
    int irq_level, EE_mico32_ISR_handler fun, int nesting_level); */
EE_mico32_call_ISR_new_stack:
	// r1 == irq_level
	// r2 == fun
	// r3 == nesting_level
	addi	sp, sp, -8
	sw	(sp + 4), ra

	/* if (nesting_level == 1) */
	SKIP_IF_NESTED_REG r3, r4, .L_skip_change
        /*     change_stacks(); */
	sw	(sp + 8), r11
	LOAD_ADDR r11, EE_mico32_tmp_tos
	sw	(r11 + 0), sp
	LOAD_ADDR r5, EE_mico32_IRQ_tos
	lw	sp, (r5 + 0)
.L_skip_change:
	/* EE_std_enableIRQ_nested(); */
	ENABLE_NESTED_IRQ
	/* fun(); */
	call	r2
	/* EE_std_disableIRQ_nested(); */
	DISABLE_NESTED_IRQ
	/* if (nesting_level == 1) */
	SKIP_IF_NESTED r3, r3, .L_skip_change_back
	/*     change_stacks_back(); */
	lw	sp, (r11 + 0)
	lw	r11, (sp + 8)
.L_skip_change_back:
	lw	ra, (sp + 4)
	addi	sp, sp, 8
	ret
	
	.size	EE_mico32_call_ISR_new_stack, .-EE_mico32_call_ISR_new_stack
