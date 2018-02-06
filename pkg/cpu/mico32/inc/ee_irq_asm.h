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
	@file ee_irq_asm.h
	@brief Assembly macros for IRQs on Lattice Mico32
	@author Bernardo  Dal Seno
	@date 2010
*/  

#ifndef __INCLUDE_MICO32_IRQ_ASM_H__
#define __INCLUDE_MICO32_IRQ_ASM_H__

#include <cpu/mico32/inc/ee_asm_util.h>

#ifdef __ALLOW_NESTED_IRQ__
	.macro  SKIP_IF_NESTED_REG nest_lev, tmp_reg, skip_lab
	addi	\tmp_reg, \nest_lev, -1
	bne	\tmp_reg, r0, skip_lab
	.endm

	.macro  SKIP_IF_NESTED nest_reg, tmp_reg, skip_lab
        LOAD_ADDR \nest_reg, EE_IRQ_nesting_level
	lw	\nest_reg, (\nest_reg + 0)
	addi	\tmp_reg, \nest_reg, -1
	bne	\tmp_reg, r0, skip_lab
	.endm

	.macro	ENABLE_NESTED_IRQ
#error ENABLE_NESTED_IRQ: Not implemented
	.endm

	.macro	DISABLE_NESTED_IRQ
#error DISABLE_NESTED_IRQ: Not implemented
	.endm
#else	
	.macro  SKIP_IF_NESTED_REG nest_lev, tmp_reg, skip_lab
	/* Never nested, never skip */
	.endm
	
	.macro  SKIP_IF_NESTED nest_reg, tmp_reg, skip_lab
	/* Never nested, never skip */
	.endm
	
	.macro	ENABLE_NESTED_IRQ
	.endm

	.macro	DISABLE_NESTED_IRQ
	.endm
#endif

#endif /*  __INCLUDE_MICO32_IRQ_ASM_H__ */
