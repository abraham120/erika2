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

#include "eecfg.h"
#include <cpu/e200zx/inc/ee_regs.h>
#include <cpu/e200zx/inc/ee_cpu_asm.h>
#include <cpu/e200zx/inc/ee_ivor.h>

	.text

	ASM_REORDER_OFF

	.balign 32
	.global	EE_e200zx_system_call
	.type	EE_e200zx_system_call, @function
EE_e200zx_system_call:
	/* Interrupt-enabled state is restored from SRR1 before the actual
	 * syscall.  The syscall will disable interrupts when needed.
	 * Interrupts must be disabled again during the final critical section
	 * dealing with SRR0 and SRR1. */
	stwu    sp, -16(sp)
	mflr    r7
	stw     r7, 20(sp)
	/* Calls that should affect interrupt enabling are treated
	 * specially */
	cmpli	cr0, 0, r0, EE_ID_interrupts_last
	bgt	1f
	/* The core function is called without enabling interrupts; SRR1 is
	 * passed as an argument, and the returned value is stored in SRR1 */
	slwi    r0, r0, 2
	addis   r10, 0, EE_syscall_table@ha
	ori     r10, r10, EE_syscall_table@l
	lwzx    r10, r10, r0
	mfsrr1	r3
	mtlr    r10
	blrl
	mtsrr1	r3
	b	3f
	/* Calls that don't affect interrupt enabling */
1:
	mfsrr0  r8
	stw     r8, 8(sp)
	mfsrr1  r9
	stw     r9, 12(sp)

	cmpli	cr0, 0, r0, EE_SYSCALL_NR
	blt	1f
	/* FIXME: Error handling here (call ProtectionHook?) */
	b	2f

1:
	wrtee	r9
	slwi    r0, r0, 2
	addis   r10, 0, EE_syscall_table@ha
	ori     r10, r10, EE_syscall_table@l
	lwzx    r10, r10, r0

	mtlr    r10
	blrl

	wrteei	0
2:
	lwz     r7, 12(sp)
	mtsrr1  r7
	lwz     r8, 8(sp)
	mtsrr0  r8
3:
	lwz     r9, 20(sp)
	mtlr    r9
	addi    sp, sp, 16

	rfi
	.size	EE_e200zx_system_call, .-EE_e200zx_system_call

/*
 * EE_as_TerminateISR2(): Terminate the ISR2
 *
 *	WARNING: It must be called by the ISR2 poststub only!
 *
 *	BUG: Recovery from dead ISR2 on the stack doesn't work
 *
 *
 * void EE_as_TerminateISR2(void)
 * {
 *	if (EE_IRQ_nesting_level == 0)
 *		return;
 *	tos = &EE_as_ISR_stack[--EE_IRQ_nesting_level];
 *
 * ISR2_terminate:
 *	recover_lr_from_stack();
 *	retaddr = get_retaddr_from_stack();
 *	pop_frame_from_stack();
 *
 *	toid = EE_e200zx_get_application();
 *	to = &EE_as_Application_RAM[toid];
 *
 *	sp = get_sp();
 *	to->ISRTOS = sp;
 *	load_sp(tos->TerminationTOS);
 *
 *	if (EE_IRQ_nesting_level == 0) {
 *		load_sp(EE_e200zx_ISR_stksave.sp);
 *		load_appid(EE_e200zx_ISR_stksave.appl);
 *		EE_std_after_IRQ_schedule();
 *	} else {
 *		fromid = EE_as_ISR_ROM[tos->ISR].ApplID;
 *		tos = &EE_as_ISR_stack[EE_IRQ_nesting_level - 1];
 *		if (fromid != toid) {
 *			from = &EE_as_Application_RAM[fromid];
 *			load_appid(fromid);
 *			load_sp(from->ISRTOS);
 *		}
 *		if (tos->Terminated) {
 *			EE_IRQ_nesting_level--;
 *			jmp_to(ISR2_terminate);
 *		}
 *	}
 * }
 */

	;; r3:  toid
	;; r4:  EE_IRQ_nesting_level
	;; r6:  &EE_as_ISR_stack[EE_IRQ_nesting_level]
	;; r7:  &EE_as_Application_RAM[0]
	;; r8:  &EE_as_Application_RAM[current_application_id]
	;; r9:  EE_as_ISR_stack[EE_IRQ_nesting_level].ISR_Terminated
	;; crt:  return address
	;; r0, (r3,) r5, r10, r11:  short-lived values
	.global	EE_as_TerminateISR2
	.type	EE_as_TerminateISR2, @function
EE_as_TerminateISR2:
	wrteei	0		; Disable interrupts for this syscall
	addis	r3, 0, EE_IRQ_nesting_level@ha
	ori	r3, r3, EE_IRQ_nesting_level@l
	lwz	r4, (r3)			# r4 <= EE_IRQ_nesting_level
	cmpli	cr0, 0, r4, 0
	beq	5f

	addi	r4, r4, -1			# EE_IRQ_nesting_level--
	stw	r4, (r3)

	addis	r5, 0, EE_as_ISR_stack@ha
	ori	r5, r5, EE_as_ISR_stack@l	# r5 <= EE_as_ISR_stack

	mr	r6, r4
	slwi	r6, r6, 3
	add	r6, r6, r5			# r6 <= tos

ISR2_terminate:
	lwz	r0, 20(sp)	; Recover LR saved by the syscall
	mtlr	r0
	lwz	r0, 8(sp)	; Recover the return address of the syscall
	mtctr	r0
	addi	sp, sp, 16	; Remove the frame of syscall

	mfpid0	r3				# r3 <= toid
	addis	r7, 0, EE_as_Application_RAM@ha
	ori	r7, r7, EE_as_Application_RAM@l
	mr	r8, r3
	slwi	r8, r8, 4
	add	r8, r7, r8			# r8 <= to
	stw	sp, (r8)			# to->ISRTOS <= sp

#if 0 /* Arbitrary TerminateIsr() not supported */
	lwz	sp, (r6)			# sp <= tos->TerminationTOS
#endif

	cmpli	cr0, 0, r4, 0
	bne	1f

	addis	r3, 0, EE_e200zx_ISR_stksave@ha
	ori	r3, r3, EE_e200zx_ISR_stksave@l
	lwz	sp, (r3)			# EE_e200zx_ISR_stksave.sp
	lwz	r0, 4(r3)			# EE_e200zx_ISR_stksave.appl
	isync
	mtpid0	r0
	isync
#if 0 /* Done by EE_e200z7_irq */
	bl	EE_e200zx_after_IRQ_schedule
#endif
	bctr			; Return to the ISR wrapper
1:
	addis	r11, 0, EE_as_ISR_ROM@ha
	ori	r11, r11, EE_as_ISR_ROM@l
	addi	r6, r6, -8			# tos--
	lwz	r9, 4(r6)			# r9 <= tos->ISR_Terminated
	mr	r8, r9
	andi.	r8, r8, 0xffff			# r8 <= ISR id
	slwi	r8, r8, 2
	lwzx	r8, r11, r8			# r8 <= fromid

	cmpl	cr0, r8, r3
	beq	3f
	mr	r10, r8
	slwi	r10, r10, 4
	add	r10, r7, r10			# r10 <= from
	isync
	mtpid0	r8				# load_appid(fromid)
	isync
	lwz	sp, (r10)			# load_sp(from->ISRTOS)
2:
	srwi	r9, r9, 16			# r9 <= Terminated
	cmpli	cr0, 0, r9, 0
	bne	5f
3:
	bctr			; Return to the ISR wrapper
4:
	addi	r4, r4, -1			# EE_IRQ_nesting_level--
	stw	r4, (r3)
	b	ISR2_terminate
5:
	blr
	.size	EE_as_TerminateISR2, .-EE_as_TerminateISR2


	.data
	.balign 4
	.global EE_e200zx_ISR_stksave
	.type	EE_e200zx_ISR_stksave, @object
EE_e200zx_ISR_stksave:
	.space	8
	.size	EE_e200zx_ISR_stksave, .-EE_e200zx_ISR_stksave
