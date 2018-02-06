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

	.macro LOAD_DIRTY_VALUE reg, value
	andi	\reg, r2, 0xffff	/* Low word from r2 */
	orhi	\reg, \reg, \value	/* Hi word from value */
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
#define STACK_DIRT 0xAA1c
#define RA_DIRT 0xAA1d

	.macro GET_REG_FROM_DIRT dest src
	sri	\dest, \src, 16
	andi	\dest, \dest, 0xff
	.endm

	
	/* void dirty_regs( void (*func)(void), short base_dirt ); */
	
	.global dirty_regs
	.type	dirty_regs, @function
dirty_regs:
	/* Save registers */
	addi	sp, sp, -72
	/* r28 is sp; r29 is ra; r30 is ea; r31 is ba */
	sw	(sp+4), ra
        sw      (sp+8), r27
        sw      (sp+12), r26
        sw      (sp+16), r25
        sw      (sp+20), r24
        sw      (sp+24), r23
        sw      (sp+28), r22
        sw      (sp+32), r21
        sw      (sp+36), r20
        sw      (sp+40), r19
        sw      (sp+44), r18
        sw      (sp+48), r17
        sw      (sp+52), r16
        sw      (sp+56), r15
        sw      (sp+60), r14
        sw      (sp+64), r13
        sw      (sp+68), r12
        sw      (sp+72), r11

	/* Dirty the stack and reserve 1 location at (sp+8) */
	LOAD_DIRTY_VALUE r3, STACK_DIRT
	addi	sp, sp, -8
	sw	(sp+4), r3

	/* Dirty al registers */
	LOAD_DIRTY_VALUE r2, R2_DIRT
        LOAD_DIRTY_VALUE r3, R3_DIRT
        LOAD_DIRTY_VALUE r4, R4_DIRT
        LOAD_DIRTY_VALUE r5, R5_DIRT
        LOAD_DIRTY_VALUE r6, R6_DIRT
        LOAD_DIRTY_VALUE r7, R7_DIRT
        LOAD_DIRTY_VALUE r8, R8_DIRT
        LOAD_DIRTY_VALUE r9, R9_DIRT
        LOAD_DIRTY_VALUE r10, R10_DIRT
        LOAD_DIRTY_VALUE r11, R11_DIRT
        LOAD_DIRTY_VALUE r12, R12_DIRT
        LOAD_DIRTY_VALUE r13, R13_DIRT
        LOAD_DIRTY_VALUE r14, R14_DIRT
        LOAD_DIRTY_VALUE r15, R15_DIRT
        LOAD_DIRTY_VALUE r16, R16_DIRT
        LOAD_DIRTY_VALUE r17, R17_DIRT
        LOAD_DIRTY_VALUE r18, R18_DIRT
        LOAD_DIRTY_VALUE r19, R19_DIRT
        LOAD_DIRTY_VALUE r20, R20_DIRT
        LOAD_DIRTY_VALUE r21, R21_DIRT
        LOAD_DIRTY_VALUE r22, R22_DIRT
        LOAD_DIRTY_VALUE r23, R23_DIRT
        LOAD_DIRTY_VALUE r24, R24_DIRT
        LOAD_DIRTY_VALUE r25, R25_DIRT
        LOAD_DIRTY_VALUE r26, R26_DIRT
        LOAD_DIRTY_VALUE r27, R27_DIRT
	LOAD_DIRTY_VALUE ra, RA_DIRT

	be	r1, r0, .L_check_forever
	/* Call the function */
	sw	(sp+8), r2
	call	r1
	lw	r2, (sp+8)
	/* Check callee-saved registers */
	calli	.L_check_callee_saved_regs
	/* If the call returns, everything is okay */
	mvi	r1, 0

.L_restore_and_return:
	addi	sp, sp, 8
	lw	ra, (sp+4)
        lw      r27, (sp+8)
        lw      r26, (sp+12)
        lw      r25, (sp+16)
        lw      r24, (sp+20)
        lw      r23, (sp+24)
        lw      r22, (sp+28)
        lw      r21, (sp+32)
        lw      r20, (sp+36)
        lw      r19, (sp+40)
        lw      r18, (sp+44)
        lw      r17, (sp+48)
        lw      r16, (sp+52)
        lw      r15, (sp+56)
        lw      r14, (sp+60)
        lw      r13, (sp+64)
        lw      r12, (sp+68)
        lw      r11, (sp+72)
	addi	sp, sp, 72
	ret

	/* Continuously check the registers for changes. Jump to
	 * .L_reg_wrong if a register changes */
.L_check_forever:
	LOAD_DIRTY_VALUE r1, RA_DIRT
	bne	r1, ra, .L_reg_wrong
	calli	.L_check_callee_saved_regs
        LOAD_DIRTY_VALUE r1, R2_DIRT
        bne     r1, r2, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R3_DIRT
        bne     r1, r3, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R4_DIRT
        bne     r1, r4, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R5_DIRT
        bne     r1, r5, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R6_DIRT
        bne     r1, r6, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R7_DIRT
        bne     r1, r7, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R8_DIRT
        bne     r1, r8, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R9_DIRT
        bne     r1, r9, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R10_DIRT
        be     r1, r10, .L_check_forever
	
.L_reg_wrong:
	GET_REG_FROM_DIRT r1, r1
	bi	.L_restore_and_return

	/* Check callee-saved registers (except ra; ra is just dirtied).
	 * In case of error jump to .L_reg_wrong; if everything is ok, return */
.L_check_callee_saved_regs:
	sw	(sp+8), ra
	LOAD_DIRTY_VALUE ra, RA_DIRT
        LOAD_DIRTY_VALUE r1, R11_DIRT
        bne     r1, r11, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R12_DIRT
        bne     r1, r12, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R13_DIRT
        bne     r1, r13, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R14_DIRT
        bne     r1, r14, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R15_DIRT
        bne     r1, r15, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R16_DIRT
        bne     r1, r16, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R17_DIRT
        bne     r1, r17, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R18_DIRT
        bne     r1, r18, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R19_DIRT
        bne     r1, r19, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R20_DIRT
        bne     r1, r20, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R21_DIRT
        bne     r1, r21, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R22_DIRT
        bne     r1, r22, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R23_DIRT
        bne     r1, r23, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R24_DIRT
        bne     r1, r24, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R25_DIRT
        bne     r1, r25, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R26_DIRT
        bne     r1, r26, .L_reg_wrong
        LOAD_DIRTY_VALUE r1, R27_DIRT
        bne     r1, r27, .L_reg_wrong
	LOAD_DIRTY_VALUE r1, STACK_DIRT
	lw	r2, (sp+4)
	bne	r1, r2, .L_reg_wrong
	/* Restore r2 */
	LOAD_DIRTY_VALUE r2, R2_DIRT
	/* Home-made RET that doesn't use ra */
	lw	r1, (sp+8)
	b	r1
	
	.size	dirty_regs, .-dirty_regs
	