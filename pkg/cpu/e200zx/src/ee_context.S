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
 * Context switch function for multistack on E200Z7
 * Implementation of EE_std_change_context() as described in
 * pkg/cpu/common/inc/ee_context.h
 * Author: Fabio Checconi
 */

#include <cpu/e200zx/inc/ee_regs.h>

/*
void EE_std_change_context_multi(EE_FADDR thread_addr, EE_UREG tos_index);

Pseudo code for EE_std_change_context():
     begin:
      tos_index = EE_std_thread_tos[tid+1];
      if is_not_the_current_stack(tos_index) {
          save_caller_saved_registers();
          switch_stacks(tos_index);
          restore_caller_saved_registers();
      }
      if (is_not_marked_stacked(tid)) {
          tid = EE_std_run_task_code(tid);
          goto begin;
      }
*/

	.text

	/* CW-FUNC-DEFINITION: void EE_std_change_context(EE_TID tid) */
	.global EE_std_change_context
	.type	EE_std_change_context, @function

/* void EE_std_change_context(EE_TID tid); */
EE_std_change_context:
	// r3 == tid

	/* tos_index = EE_std_thread_tos[tid+1]; */
	// r5 == tos_index
	addis	r4, 0, EE_std_thread_tos@ha
	addi	r4, r4, EE_std_thread_tos@l
	rlwinm	r5, r3, 2, 0, 29
	add	r4, r4, r5
	lwz	r5, 4(r4)

	/* if is_not_the_current_stack(tos_index) { */
	// r4 = & EE_e200z7_active_tos;
	addis	r4, 0, EE_e200z7_active_tos@ha
	addi	r4, r4, EE_e200z7_active_tos@l

	// r6 = EE_e200z7_active_tos;
	lwz	r6, 0(r4)
	cmpw	cr0, r5, r6
	beq	end_change_stacks

	/*     save_caller_saved_registers(); */
	mflr	r0
	stw	r0, -76(sp)
#ifndef	DEBUG
	stmw	r14, -72(sp)
#else
	stw	r14, -72(sp)
	stw	r15, -68(sp)
	stw	r16, -64(sp)
	stw	r17, -60(sp)
	stw	r18, -56(sp)
	stw	r19, -52(sp)
	stw	r20, -48(sp)
	stw	r21, -44(sp)
	stw	r22, -40(sp)
	stw	r23, -36(sp)
	stw	r24, -32(sp)
	stw	r25, -28(sp)
	stw	r26, -24(sp)
	stw	r27, -20(sp)
	stw	r28, -16(sp)
	stw	r29, -12(sp)
	stw	r30, -8(sp)
	stw	r31, -4(sp)
#endif
	
	/*     switch_stacks(tos_index); */
	// r7 = & EE_e200z7_system_tos[0];
	addis	r7, 0, EE_e200z7_system_tos@ha
	addi	r7, r7, EE_e200z7_system_tos@l

	// EE_e200z7_system_tos[r6] = sp;
	rlwinm	r6, r6, 2, 0, 29
	add	r6, r6, r7
	stw	sp, 0(r6)

	// EE_e200z7_active_tos = tos_index;
	stw	r5, 0(r4)

	// sp = EE_e200z7_system_tos[r5];
	rlwinm	r6, r5, 2, 0, 29
	add	r6, r6, r7
	lwz	sp, 0(r6)

#ifdef __EE_MEMORY_PROTECTION__
	/* Load application ID */
	/* The two `isync' make sure that 1. the previous register saving won't
	 * raise any exception when changing the ID, and 2. register restoring
	 * is performed in the new context */
	isync
	/* pid0 = EE_th_app[r3 + 1] */
	addis   r4, r0, (EE_th_app + 4)@ha
	addi    r4, r4, (EE_th_app + 4)@l
	slwi    r5, r3, 2
	lwzx    r0, r4, r5
	mtpid0  r0
	isync
#endif /* __EE_MEMORY_PROTECTION__ */

        /*     restore_caller_saved_registers(); */
#ifndef	DEBUG
	lmw	r14, -72(sp)
#else
	lwz	r31, -4(sp)
	lwz	r30, -8(sp)
	lwz	r29, -12(sp)
	lwz	r28, -16(sp)
	lwz	r27, -20(sp)
	lwz	r26, -24(sp)
	lwz	r25, -28(sp)
	lwz	r24, -32(sp)
	lwz	r23, -36(sp)
	lwz	r22, -40(sp)
	lwz	r21, -44(sp)
	lwz	r20, -48(sp)
	lwz	r19, -52(sp)
	lwz	r18, -56(sp)
	lwz	r17, -60(sp)
	lwz	r16, -64(sp)
	lwz	r15, -68(sp)
	lwz	r14, -72(sp)
#endif
	lwz	r0, -76(sp)
	mtlr	r0

        /* } */
end_change_stacks:

        /* if (is_not_marked_stacked(tid)) { */
	// r3 == tid
	cmpi	cr0, 0, r3, 0x0
	blt	end_run_thread

	stwu	sp, -16(sp)
	/*     tid = EE_std_run_task_code(tid); */
	mflr	r0
	stw	r0, 20(sp)
	bl	EE_std_run_task_code
	lwz	r0, 20(sp)
	mtlr	r0
	addi	sp, sp, 16

	// r3 == tid

        /*     goto begin; */
	b	EE_std_change_context

        /* } */
end_run_thread:

	blr
	
	.size	EE_std_change_context, .-EE_std_change_context
