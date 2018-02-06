/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 2001-2002 Alessandro Colantonio
 *         2002- Paolo Gai
 *
 * CVS: $Id: ee_hal_thumb.S,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"

	.global	EE_arm7_enableIRQ
	.global EE_arm7_end_nested_primitive
	.global EE_arm7_begin_nested_primitive
	.global	EE_arm7_disableIRQ

	
	.text

	//  kernel code is in ARM-mode
	CODE32

//
// void EE_arm7_enableIRQ(void)
//
// Enable interrupts. Tipically called by thumb functions.
//
	.type	EE_arm7_enableIRQ, #function
EE_arm7_enableIRQ:		
	//
	// NOTE:
	// 1) only flag field of CPSR can be set with immediate value,
	//    so we have to use two asm instruction;
	// 2) preserving flag field is useless. (I hope ;)
	//
	MRS	r0, cpsr
	BIC	r0, r0, #I_bit
	MSR	cpsr_c, r0
#ifdef __unibo_mparm__
	MOV	pc, lr
#else
	BX	lr
#endif

	.size	EE_arm7_enableIRQ, . - EE_arm7_enableIRQ

	
	
//
// void EE_arm7_disableIRQ(void)
//
// Disable interrupts. Tipically called by thumb functions.
//
	.type	EE_arm7_disableIRQ, #function
EE_arm7_disableIRQ:	
	MRS	r0, cpsr
	ORR	r0, r0, #I_bit
	MSR	cpsr_c, r0
#ifdef __unibo_mparm__
	MOV	pc, lr
#else
	BX	lr
#endif
	.size	EE_arm7_disableIRQ, . - EE_arm7_disableIRQ
	

//
// void EE_arm7_end_nested_primitive(EE_FREG f)
//
// Enable interrupts (can be nested). Tipically called by thumb functions.
//
	.type	EE_arm7_end_nested_primitive, #function
EE_arm7_end_nested_primitive:	
	//
	// NOTE:
	// 1) only flag field of CPSR can be set with immediate value,
	//    so we have to use two asm instruction;
	// 2) preserving flag field is useless. (I hope ;)
	//
	MSR	cpsr_c, r0
#ifdef __unibo_mparm__
	MOV	pc, lr
#else
	BX	lr
#endif

	.size	EE_arm7_end_nested_primitive, . - EE_arm7_end_nested_primitive

	
	
//
// EE_FREG EE_arm7_begin_nested_primitive(void)
//
// Disable interrupts (can be nested). Tipically called by thumb functions.
//
	.type	EE_arm7_begin_nested_primitive, #function
EE_arm7_begin_nested_primitive:	
	MRS	r0, cpsr
	MOV	r1, r0	
	ORR	r1, r1, #I_bit
	MSR	cpsr_c, r1
#ifdef __unibo_mparm__
	MOV	pc, lr
#else
	BX	lr
#endif

	.size	EE_arm7_begin_nested_primitive, . - EE_arm7_begin_nested_primitive

	.end
