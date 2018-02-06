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
 * Functions to save and restore registers for Osek TerminateTask() on
 * PPCE200Z7.
 * Author: 2010,  Fabio Checconi
 */

#include <eecfg.h>
#include <cpu/e200zx/inc/ee_regs.h>

	.text

	/* CW-FUNC-DEFINITION: void EE_hal_terminate_savestk(EE_TID tid) */
	.global EE_hal_terminate_savestk
	.type	EE_hal_terminate_savestk, @function
	/* void EE_hal_terminate_savestk(EE_TID tid); */
EE_hal_terminate_savestk:
	/* r3 == tid */

	/* r4 == tid << 2 */
	rlwinm	r4, r3, 2, 0, 29

	/* r5 == EE_terminate_real_th_body[tid] */
	addis	r5, 0, EE_terminate_real_th_body@ha
	add	r5, r5, r4
	lwz	r5, EE_terminate_real_th_body@l(r5)

	/* Save the stack pointer (including space for registers) */
	/* r6 == & EE_terminate_data[tid] */
	addis	r6, 0, EE_terminate_data@ha
	add	r6, r6, r4
	mflr	r0
	stwu	sp, -96(sp)
	stw	sp, EE_terminate_data@l(r6)
	
	/* Save all callee-saved registers */
	stw	r0, 8(sp)
#ifndef	DEBUG
	stmw	r14, 12(sp)
#else
	stw	r14, 12(sp)
	stw	r15, 16(sp)
	stw	r16, 20(sp)
	stw	r17, 24(sp)
	stw	r18, 28(sp)
	stw	r19, 32(sp)
	stw	r20, 36(sp)
	stw	r21, 40(sp)
	stw	r22, 44(sp)
	stw	r23, 48(sp)
	stw	r24, 52(sp)
	stw	r25, 56(sp)
	stw	r26, 60(sp)
	stw	r27, 64(sp)
	stw	r28, 68(sp)
	stw	r29, 72(sp)
	stw	r30, 76(sp)
	stw	r31, 80(sp)
#endif

	/* Start the thread body */
	mtlr	r5
#if !defined(__EE_MEMORY_PROTECTION__)
	blrl
#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || \
		defined(__OO_ECC1__) || defined(__OO_ECC2__)
	/* The task terminated with a return:
	 * jump to notification handler EE_thread_not_terminated,
	 * which not return.
	 * needed for AS requirements (OS052, OS069, OS070, OS239)
	 */
	bl	EE_thread_not_terminated
#endif
	/* The following code SHOULD not be executed, but for
	 * conservative reason is
	 * maintained (return to caller function)
	 */
	lwz	r0, 8(sp)
	mtlr	r0
	addi	sp, sp, 96
	blr
#else /* !defined(__EE_MEMORY_PROTECTION__) */
	/* pid0 = EE_th_app[r3 + 1] */
	addis	r4, r0, (EE_th_app + 4)@ha
	addi	r4, r4, (EE_th_app + 4)@l
	slwi	r3, r3, 2
	lwzx	r0, r4, r3
	addis	r4, r0, EE_as_Application_RAM@ha
	addi	r4, r4, EE_as_Application_RAM@l
	slwi	r0, r0, 4
	add	r4, r4, r0
	lwz	r0, 4(r4)
	mtmsr	r0
	isync
	blrl
	/* Call TerminateTask(), which never returns */
	li	r0, EE_ID_TerminateTask
	sc
#endif /* else !defined(__EE_MEMORY_PROTECTION__) */
	.size	EE_hal_terminate_savestk, .-EE_hal_terminate_savestk


	/* CW-FUNC-DEFINITION: void EE_hal_terminate_task(EE_TID tid) */
	.global EE_hal_terminate_task
	.type	EE_hal_terminate_task, @function
	/* void EE_hal_terminate_task(EE_TID tid) NORETURN; */
EE_hal_terminate_task:
	/* r3 == tid */
	
	/* Restore the stack pointer */
	/* r5 == & EE_terminate_data[tid] */
	rlwinm	r4, r3, 2, 0, 29
	addis	r5, 0, EE_terminate_data@ha
	add	r5, r5, r4
	lwz	sp, EE_terminate_data@l(r5)

	/* Restore the registers and return */
	lwz	r0, 8(sp)
	mtlr	r0
#ifndef	DEBUG
	lmw	r14, 12(sp)
#else
	lwz	r31, 80(sp)
	lwz	r30, 76(sp)
	lwz	r29, 72(sp)
	lwz	r28, 68(sp)
	lwz	r27, 64(sp)
	lwz	r26, 60(sp)
	lwz	r25, 56(sp)
	lwz	r24, 52(sp)
	lwz	r23, 48(sp)
	lwz	r22, 44(sp)
	lwz	r21, 40(sp)
	lwz	r20, 36(sp)
	lwz	r19, 32(sp)
	lwz	r18, 28(sp)
	lwz	r17, 24(sp)
	lwz	r16, 20(sp)
	lwz	r15, 16(sp)
	lwz	r14, 12(sp)
#endif
	addi	sp, sp, 96
	blr
	.size	EE_hal_terminate_task, .-EE_hal_terminate_task
