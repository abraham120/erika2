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

/*
 * Asm functions that dirty all registers and check for unexepcted changes
 * Author: 2010,  Bernardo  Dal Seno
 */

load_dirty_value: .macro reg,value
	mr	reg, r4
	andi.	reg, reg, 0xffff
	oris	reg, reg, value
	.endm

check_dirty_value: .macro reg, value
	load_dirty_value r0, value
	cmplw	cr0, r0, reg
	bne     reg_wrong
	.endm

#define R2_DIRT 0xAA02
#define R3_DIRT 0xAA03
#define R4_DIRT 0xAA04
#define R5_DIRT 0xAA05
#define R6_DIRT 0xAA06
#define R7_DIRT 0xAA07
#define R8_DIRT 0xAA08
#define R9_DIRT 0xAA09
#define R10_DIRT 0xAA0a
#define R11_DIRT 0xAA0b
#define R12_DIRT 0xAA0c
#define R13_DIRT 0xAA0d
#define R14_DIRT 0xAA0e
#define R15_DIRT 0xAA0f
#define R16_DIRT 0xAA10
#define R17_DIRT 0xAA11
#define R18_DIRT 0xAA12
#define R19_DIRT 0xAA13
#define R20_DIRT 0xAA14
#define R21_DIRT 0xAA15
#define R22_DIRT 0xAA16
#define R23_DIRT 0xAA17
#define R24_DIRT 0xAA18
#define R25_DIRT 0xAA19
#define R26_DIRT 0xAA1a
#define R27_DIRT 0xAA1b
#define R28_DIRT 0xAA1c
#define R29_DIRT 0xAA1d
#define R30_DIRT 0xAA1e
#define R31_DIRT 0xAA1f
#define STACK_DIRT 0xAA20

	/* void dirty_regs( void (*func)(void), short base_dirt ); */
	
	.global dirty_regs
	.type	dirty_regs, @function
dirty_regs:
	/* Save registers */
	/* r1 is sp, r2 and r13 contain sdata addresses */
	mfspr	r0, 8
	stwu	sp, -96(sp)
	stw	r0, 12(sp)
#ifndef	DEBUG
	stmw	r14, 24(sp)
#else
	stw	r14, 24(sp)
	stw	r15, 28(sp)
	stw	r16, 32(sp)
	stw	r17, 36(sp)
	stw	r18, 40(sp)
	stw	r19, 44(sp)
	stw	r20, 48(sp)
	stw	r21, 52(sp)
	stw	r22, 56(sp)
	stw	r23, 60(sp)
	stw	r24, 64(sp)
	stw	r25, 68(sp)
	stw	r26, 72(sp)
	stw	r27, 76(sp)
	stw	r28, 80(sp)
	stw	r29, 84(sp)
	stw	r30, 88(sp)
	stw	r31, 92(sp)
#endif

	/* Dirty the stack. */
	load_dirty_value r0, STACK_DIRT
	stw	r0, 8(sp)

	/* Dirty all registers */
	load_dirty_value r4, R4_DIRT
	load_dirty_value r5, R5_DIRT
	load_dirty_value r6, R6_DIRT
	load_dirty_value r7, R7_DIRT
	load_dirty_value r8, R8_DIRT
	load_dirty_value r9, R9_DIRT
	load_dirty_value r10, R10_DIRT
	load_dirty_value r11, R11_DIRT
	load_dirty_value r12, R12_DIRT
	load_dirty_value r14, R14_DIRT
	load_dirty_value r15, R15_DIRT
	load_dirty_value r16, R16_DIRT
	load_dirty_value r17, R17_DIRT
	load_dirty_value r18, R18_DIRT
	load_dirty_value r19, R19_DIRT
	load_dirty_value r20, R20_DIRT
	load_dirty_value r21, R21_DIRT
	load_dirty_value r22, R22_DIRT
	load_dirty_value r23, R23_DIRT
	load_dirty_value r24, R24_DIRT
	load_dirty_value r25, R25_DIRT
	load_dirty_value r26, R26_DIRT
	load_dirty_value r27, R27_DIRT
	load_dirty_value r28, R28_DIRT
	load_dirty_value r29, R29_DIRT
	load_dirty_value r30, R30_DIRT
	load_dirty_value r31, R31_DIRT

	/* Test for zero; "cmpwi cr0, r3, 0" doesn't work in VLE */
	and.	r3, r3, r3
	beq	check_forever

	/* Call the function */
	stw	r4, 16(sp)
	mtspr	8, r3
	blrl
	lwz	r4, 16(sp)

	/* Check callee-saved registers */
	bl	check_callee_saved_regs

	/* If the call returns, everything is okay */
	li	r3, 0

restore_and_return:
	lwz	r0, 12(sp)
	mtspr	8, r0
#ifndef	DEBUG
	lmw	r14, 24(sp)
#else
	lwz	r14, 24(sp)
	lwz	r15, 28(sp)
	lwz	r16, 32(sp)
	lwz	r17, 36(sp)
	lwz	r18, 40(sp)
	lwz	r19, 44(sp)
	lwz	r20, 48(sp)
	lwz	r21, 52(sp)
	lwz	r22, 56(sp)
	lwz	r23, 60(sp)
	lwz	r24, 64(sp)
	lwz	r25, 68(sp)
	lwz	r26, 72(sp)
	lwz	r27, 76(sp)
	lwz	r28, 80(sp)
	lwz	r29, 84(sp)
	lwz	r30, 88(sp)
	lwz	r31, 92(sp)
#endif
	addi	sp, sp, 96

	blr

	/* Continuously check the registers for changes. Jump to
	 * reg_wrong if a register changes */
check_forever:
	check_dirty_value r4, R4_DIRT
	check_dirty_value r5, R5_DIRT
	check_dirty_value r6, R6_DIRT
	check_dirty_value r7, R7_DIRT
	check_dirty_value r8, R8_DIRT
	check_dirty_value r9, R9_DIRT
	check_dirty_value r10, R10_DIRT
	check_dirty_value r11, R11_DIRT
	load_dirty_value r0, R12_DIRT
	cmplw	cr0, r0, r12
	beq	check_forever
	
reg_wrong:
	li	r3, -1
	b	restore_and_return

	/* Check callee-saved registers (except ra; ra is just dirtied).
	 * In case of error jump to .L_reg_wrong; if everything is ok, return */
check_callee_saved_regs:
	check_dirty_value r14, R14_DIRT
	check_dirty_value r15, R15_DIRT
	check_dirty_value r16, R16_DIRT
	check_dirty_value r17, R17_DIRT
	check_dirty_value r18, R18_DIRT
	check_dirty_value r19, R19_DIRT
	check_dirty_value r20, R20_DIRT
	check_dirty_value r21, R21_DIRT
	check_dirty_value r22, R22_DIRT
	check_dirty_value r23, R23_DIRT
	check_dirty_value r24, R24_DIRT
	check_dirty_value r25, R25_DIRT
	check_dirty_value r26, R26_DIRT
	check_dirty_value r27, R27_DIRT
	check_dirty_value r28, R28_DIRT
	check_dirty_value r29, R29_DIRT
	check_dirty_value r30, R30_DIRT
	check_dirty_value r31, R31_DIRT

	load_dirty_value r0, STACK_DIRT
	lwz	r3, 8(sp)
	cmplw	cr0, r0, r3
	bne	reg_wrong

	blr

	.size	dirty_regs, .-dirty_regs
