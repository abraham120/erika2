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
 * Exception entry points and hardware setup for the e200zX CPUs.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#include <cpu/e200zx/inc/ee_regs.h>
#include <cpu/e200zx/inc/ee_cpu_asm.h>
#include <cpu/e200zx/inc/ee_ivor.h>

	.text

	ASM_REORDER_OFF

	/* CW-FUNC-DEFINITION: void save_registers(void) */
	.type	save_registers, @function
save_registers:
	stw	r0, 12(sp)	/* LR, copied by the `vector' macro */
	stw	r3, 20(sp)
	stw	r4, 24(sp)
	stw	r5, 28(sp)
	stw	r6, 32(sp)
	stw	r7, 36(sp)
	stw	r8, 40(sp)
	stw	r9, 44(sp)
	stw	r10, 48(sp)
	stw	r11, 52(sp)
	stw	r12, 56(sp)

	mfspr	r0, srr0
	stw	r0, 60(sp)
	mfspr	r0, srr1
	stw	r0, 64(sp)
	mfcr	r0
	stw	r0, 68(sp)
	mfspr	r0, ctr
	stw	r0, 72(sp)
	mfspr	r0, xer
	stw	r0, 76(sp)

	blr
	.size	save_registers, .-save_registers


	/* CW-FUNC-DEFINITION: void restore_all_return(void) */
	.type	restore_all_return, @function
restore_all_return:
	lwz	r0, 76(sp)
	mtspr	xer, r0
	lwz	r0, 72(sp)
	mtspr	ctr, r0
	lwz	r0, 68(sp)
	mtcr	r0
	lwz	r0, 64(sp)
	mtspr	srr1, r0
	lwz	r0, 60(sp)
	mtspr	srr0, r0

	lwz	r12, 56(sp)
	lwz	r11, 52(sp)
	lwz	r10, 48(sp)
	lwz	r9, 44(sp)
	lwz	r8, 40(sp)
	lwz	r7, 36(sp)
	lwz	r6, 32(sp)
	lwz	r5, 28(sp)
	lwz	r4, 24(sp)
	lwz	r3, 20(sp)
	lwz	r0, 12(sp)
	mtspr	lr, r0
	lwz	r0, 8(sp)
	addi	sp, sp, 80
	rfi

	.size	restore_all_return, .-restore_all_return


/*
 * this belongs to the mcu code; we'd need a way to let the mcu code
 * define a couple of macros for us...
 */
#include <cpu/e200zx/inc/ee_mcu_regs_asm.h>

#ifndef EE_ISR_EXTERNAL_TABLE
	/* CW-FUNC-DEFINITION:  void EE_e200zx_external_input_handler(void) */
	.global EE_e200zx_external_input_handler
	.type	EE_e200zx_external_input_handler, @function
EE_e200zx_external_input_handler:
	handler_prologue
	addis	r3, 0, INTC_IACKR_ADDR@ha	/* ack the interrupt */
	lwz	r0, INTC_IACKR_ADDR@l(r3)

	srawi	r3, r0, 2		/* calculate the irq number */
	addi	r3, r3, EE_E200ZX_MAX_CPU_EXCP

	bl	EE_e200z7_irq		/* handle the interrupt */

	/* The EOI is issued by EE_e200z7_irq() */

	handler_epilogue
	.size	EE_e200zx_external_input_handler, .-EE_e200zx_external_input_handler


	/* CW-FUNC-DEFINITION: void EE_e200zx_decrementer_handler(void) */
	.global EE_e200zx_decrementer_handler
	.type	EE_e200zx_decrementer_handler, @function
EE_e200zx_decrementer_handler:
	handler_prologue
	addis	r0, 0, (1 << TSR_DIS)@h
#ifdef	EE_GNU__
	mtspr	SPRG_TSR, r0
#else
	mtspr	tsr, r0
#endif
	li	r3, 10
	bl	EE_e200z7_irq
	handler_epilogue
	.size	EE_e200zx_decrementer_handler, .-EE_e200zx_decrementer_handler


	/* CW-FUNC-DEFINITION: void EE_e200zx_fixed_intv_handler(void) */
	.global EE_e200zx_fixed_intv_handler
	.type	EE_e200zx_fixed_intv_handler, @function
EE_e200zx_fixed_intv_handler:
	handler_prologue
	addis	r0, 0, (1 << TSR_FIS)@h
#ifdef	EE_GNU__
	mtspr	SPRG_TSR, r0
#else
	mtspr	tsr, r0
#endif
	li	r3, 11
	bl	EE_e200z7_irq
	handler_epilogue
	.size	EE_e200zx_fixed_intv_handler, .-EE_e200zx_fixed_intv_handler
#endif /* !EE_ISR_EXTERNAL_TABLE */

	/* CW-FUNC-DEFINITION: void cpu_setup(void) */
	.global	cpu_setup
	.type	cpu_setup, @function
cpu_setup:
#if E200ZX_CPU_HAS_TB
	li	r0, 0
	mtspr	SPRG_TBL_W, r0
	mtspr	SPRG_TBH_W, r0
	mtspr	SPRG_TBL_W, r0

	/* Enable time base */
	mfspr	r3, SPRG_HID0
	ori	r3, r3, 1 << HID0_TBEN
	mtspr	SPRG_HID0, r3
#endif /* E200ZX_CPU_HAS_TB */
#ifndef EE_ISR_EXTERNAL_TABLE
	b	ivor_setup
#endif /* !EE_ISR_EXTERNAL_TABLE */
	.size	cpu_setup, .-cpu_setup



#ifdef	EE_GNU__
	.section .boot, "ax", @progbits
  	.align 8
#else
	text_section(.boot)
#endif



	/* CW-FUNC-DEFINITION: void sram_setup(void) */
	.global	sram_setup
	.type	sram_setup, @function
sram_setup:
#ifndef __E200ZX_EXECUTE_FROM_RAM__
	addis	r8, 0, isram_base@ha
	addi	r8, r8, isram_base@l
	addis	r9, 0, isram_len@ha
	addi	r9, r9, isram_len@l
	srawi	r9, r9, (0x4)
	mtctr	r9
	li	r31, 0
	li	r30, 0
	li	r29, 0
	li	r28, 0
1:
	/* ECC SRAM must be initialized with 64-bit writes, hence stmw;
	 * 16-btye alignment should work always */
#ifndef	DEBUG
	stmw	r28, 0(r8)
#else
	stw	r28, 0(r8)
	stw	r29, 4(r8)
	stw	r30, 8(r8)
	stw	r31, 12(r8)
#endif
	addi	r8, r8, 16
	bdnz	1b
#endif /*!__E200ZX_EXECUTE_FROM_RAM__ */
	blr
	.size	sram_setup, .-sram_setup