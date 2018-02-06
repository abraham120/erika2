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

#include "cpu/mpc5xx/inc/ee_macro.h"

	.extern _start

	// User's IRQ table address
	.extern const EE_mpc5_irq_table[]
	.extern const EE_mpc5_irq_mask[]

	// Kernel scheduler addresses
	.extern EE_IRQ_end_instance

	// Stack used by IRQ handlers

#ifdef __MULTI__
	.extern EE_mpc5_hal_stkchange
#ifdef __IRQ_STACK_NEEDED__
	.extern EE_mpc5_change_to_irq_tos
	.extern EE_mpc5_change_from_irq_tos
#endif
#endif

	.extern EE_IRQ_nesting_level

	.extern EE_hal_endcycle_next_thread
#ifdef __MULTI__
	.extern	EE_hal_endcycle_next_tos
#endif

	.text

	.equ	SIVEC, 0x2FC01C
	.equ	SIMASK, 0x2FC014

	// System Reset
	. = 0x00100
	b	_start

	// Machine Check
	. = 0x00200
m_check:
	b	m_check

	// External Interrupts
	. = 0x00500
e_irq:
	stwu	sp, -88(sp)
	stw	r0, 40(sp)
	mfsrr0	r0
	stw	r0, 12(sp)
	mfsrr1	r0
	stw	r0, 16(sp)
	mflr	r0
	stw	r0, 8(sp)
	mfxer	r0
	stw	r0, 20(sp)
	mfctr	r0
	stw	r0, 24(sp)
	mfcr	r0
	stw	r0, 28(sp)
	bl	save_registers

	lis	r9, SIVEC@ha
        lbz     r11, SIVEC@l(r9)

#ifdef __ALLOW_NESTED_IRQ__
#ifndef __ENHANCED_IRQ__
	
	// Masking low level IRQ
	lis	r9, EE_mpc5_irq_mask@ha
	la	r5, EE_mpc5_irq_mask@l(r9)
	add	r5, r5, r11
	lwz	r3, 0(r5)
        lis     r9, SIMASK@ha
        la	r10, SIMASK@l(r9)
	lwz	r0, 0(r10)
	stw	r0, 32(sp)
	and	r3, r0, r3
 	stw	r3, 0(r10)		

#endif // __ENHANCED_IRQ__

	lis	r9, EE_IRQ_nesting_level@ha
	la	r10, EE_IRQ_nesting_level@l(r9)
	lwz	r5, 0(r10)
	addi	r5, r5, 1
	stw	r5, 0(r10)

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	cmpwi	r5, 1
	beql	EE_mpc5_change_to_irq_tos	
#endif
#endif

	//Enable exception
	mtspr	EIE, r0	
#else // __ALLOW_NESTED_IRQ__
	lis	r9, EE_IRQ_nesting_level@ha
	li	r5, 1
	stw	r5, EE_IRQ_nesting_level@l(r9)
	//Signaling that exception is now recoverable
	mtspr	EID, r0
#endif // __ALLOW_NESTED_IRQ__

	lis	r9, EE_mpc5_irq_table@ha
	la	r5, EE_mpc5_irq_table@l(r9)
 	add	r5, r11, r5
	lwz	r0, 0(r5)
	mtlr	r0
	blrl

	//After return restore context

#ifdef __ALLOW_NESTED_IRQ__
	mtspr	NRI, r0	//NRI
	lis	r9, EE_IRQ_nesting_level@ha
	lwz	r5, EE_IRQ_nesting_level@l(r9)
	subi	r5, r5, 1
	stw	r5, EE_IRQ_nesting_level@l(r9)

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	cmpwi	r5, 0
	beql	EE_mpc5_change_from_irq_tos
#endif
#endif

	bne	theend
#else // __ALLOW_NESTED_IRQ__
	lis	r9, EE_IRQ_nesting_level@ha
	li	r5, 0
	stw	r5, EE_IRQ_nesting_level@l(r9)
#endif // __ALLOW_NESTED_IRQ__

	bl	EE_irq_end_instance

#ifdef __MULTI__
	lis	r9, EE_hal_endcycle_next_tos@ha
	lwz	r4, EE_hal_endcycle_next_tos@l(r9)
#endif
	lis	r9, EE_hal_endcycle_next_thread@ha
	lwz	r3, EE_hal_endcycle_next_thread@l(r9)

	lis	r9, theend@ha
	la	r5, theend@l(r9)
	mtlr	r5	

	cmpwi	r3, 0

#ifdef __MULTI__

	bne	EE_mpc5_hal_ready2stacked
	beq	EE_mpc5_hal_stkchange
#else
	bne	EE_mpc5_hal_ready2stacked
	beq	theend

#endif

	// Alignment
	. = 0x00600
alig:
	b	alig

	// Program
	. = 0x00700
prg:
	b	prg

	// FP Unavailable
	. = 0x00800
fp_un:
	b	fp_un
	
	// Decrementer
	. = 0x00900
decr:
	//b	decr
	rfi

	// System Call
	. = 0x00C00
sys_c:
	b	sys_c

	// Trace
	. = 0x00D00
trac:
	b	trac

	// FP Assist
	. = 0x00E00
fp_ass:
	b	fp_ass

	// Software Emulation
	. = 0x01000
so_emul:
	b	so_emul

	// Data Breakpoint
	. = 0x01C00
d_break:
	b	d_break

	// Instruction Breakpoint
	. = 0x01D00
i_break:
	b	i_break

	// Maskable external breakpoint
	. = 0x01E00
m_ext_break:
	b	m_ext_break

	// Non-maskable external breakpoint
	. = 0x01F00
n_m_ext_break:
	b	n_m_ext_break

save_registers:
	stw	r3, 44(sp)
	stw	r4, 48(sp)
	stw	r5, 52(sp)
	stw	r6, 56(sp)
	stw	r7, 60(sp)
	stw	r8, 64(sp)
	stw	r9, 68(sp)
	stw	r10, 72(sp)
	stw	r11, 76(sp)
	stw	r12, 80(sp)
	stw	r13, 84(sp)
	blr

theend:
        lwz     r3, 44(sp)
        lwz     r4, 48(sp)
        lwz     r5, 52(sp)
        lwz     r6, 56(sp)
        lwz     r7, 60(sp)
        lwz     r8, 64(sp)
        lwz     r9, 68(sp)
        lwz     r10, 72(sp)
        lwz     r11, 76(sp)
        lwz     r12, 80(sp)
        lwz     r13, 84(sp)

#ifdef __ALLOW_NESTED_IRQ__                                                    
#ifndef __ENHANCED_IRQ__
        lwz     r0, 32(sp)
        stw     r0, 0(r10)
#endif
#endif

	lwz	r0, 28(sp)
	mtcr	r0
	lwz	r0, 24(sp)
	mtctr	r0
	lwz	r0, 20(sp)
	mtxer	r0
	lwz	r0, 8(sp)
	mtlr	r0
	//Now exception is not recoverable
	mtspr	NRI, r0
	lwz	r0, 12(sp)
	mtsrr0	r0
	lwz	r0, 16(sp)
	mtsrr1	r0
	lwz	r0, 40(sp)
	addi	sp, sp, 88
	rfi	

