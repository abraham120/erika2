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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_ic_fiqstub.S,v 1.1 2004/11/18 11:19:31 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"

//
// Code area
//
	
	.text

	// kernel code is in ARM-mode
	.arm
	
	// Address of the IRQ controller for the Samsung KS32C50100.
	// NOTE: it is in the text segment (ROM?) because it cannot
	//       be an immediate operand and it is constant


		

/* ------------------------------------------------------------------------
 * FIQ Macro
 * ------------------------------------------------------------------------
 *
 * This macro must be used to define the FIQ Handler.
 * Note that there must be ONLY one FIQ macro, and that
 * macro have to be put at address 0x0000001C, in a way that the
 * first instruction that can be called after a FIQ instructions
 * is also the first instruction of this macro.
 *
 * Think at a FIQ handler like an ISR Level 1 Handler.
 * 
 * Features of this FIQ macro include:
 * - No support for any kind of interrupt nesting
 * - The ISR C routine runs in FIQ mode into the FIQ stack
 * - No EE Functions can be called from this handler
 */

// GCC!!!
.macro EE_FIQ_HANDLER_STUB

.extern EE_INTOSET_FIQ
.extern EE_IC_EXTIRQ_vector	

        // The FIQ handler works as follows:
	//
	// - The banked registers R8-R10 are used to save the registers R0-R3
	//   without accessing the memory.
	// - R11 is used to store
	// - R12 is not saved (it is banked automatically by the FIQ mode)
	// - SPSR is not saved (there is no interrupt nesting)

	// Save the contents of the R0-R2 registers
	MOV	r8, r0
	MOV	r9, r1
	MOV	r10, r2

	// Save r3 and lr_fiq on the stack
 	STMFD	sp!, {r3, lr}

	// R0, R1, R2, R3 are free

	LDR	r1, EE_INTOSET_FIQ
	LDR	r2, [r1]	// read the IRQ highest priority FIQ

	// R0, R3 are free
	// R1 contains EE_INTOSET_IRQ
	// R2 contains the offset used for the vectors

	MOV	r0, r2, lsr #2
	// R0 contains the bit in INTPND to be cleared
	
	SUB	r1, r1, #0x2C    // R1 now contains INTPND
	MOV	r3, #1
	MOV	r0, r3, lsl r0

	// R0 contains the mask to be applied to INTPND
	// R1 contains INTPND
	// R2 contains the offset used for the vectors
	// R3 is free
	
	// clear interrupt source (*INTPND = r2)
	STR	r0, [r1]

	LDR	r0, =EE_IC_EXTIRQ_vector
	LDR	r0, [r0, r2]
		
	// call the handler
	mov	lr,pc
	mov	pc,r0

	// R0 contains the address of the IRQ handler
	// R1, R2, R3 are free

	// Restore r3 and lr_fiq on the stack 	
	LDMFD	sp!, {r3, lr}	

	// Save the contents of the R0-R2 registers
	MOV     r2, r10
	MOV     r1, r9
	MOV	r0, r8

	SUBS	pc, lr, #4

EE_INTOSET_FIQ:	.word	0x03ff4030


	.endm

	/* there is no .end directive, this file is included! */


	
