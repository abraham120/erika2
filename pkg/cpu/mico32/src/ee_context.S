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
	@file ee_context.S
	@brief Context switch function for multistack on Mico32 
	Implementation of EE_std_change_context() as described in
	pkg/cpu/common/inc/ee_context.h
	@author Bernardo  Dal Seno
	@date 2010
*/ 

/*
void EE_std_change_context_multi(EE_THREAD_PTR thread_addr, EE_UREG tos_index);

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

#include <cpu/mico32/inc/ee_asm_util.h>

	
	.text

	.global EE_std_change_context
	.type	EE_std_change_context, @function
/* void EE_std_change_context(EE_TID tid); */
EE_std_change_context:
	// r1 == tid

	/* tos_index = EE_std_thread_tos[tid+1]; */
	// r2 == tos_index
	sli	r2, r1, 2	// This gets rid of the `stacked' mark
	LOAD_ADDR r3, EE_std_thread_tos
	add	r2, r3, r2
	lw	r2, (r2 + 4)

	/* if is_not_the_current_stack(tos_index) { */
	// r3 = & EE_mico32_active_tos;
	LOAD_ADDR r3, EE_mico32_active_tos
	// r4 = EE_mico32_active_tos;
	lw	r4, (r3+0)
	be	r2, r4, _end_change_stacks

	/*     save_caller_saved_registers(); */
	sw	(sp+-68), ra
	sw	(sp+-64), r27
	sw	(sp+-60), r26
	sw	(sp+-56), r25
	sw	(sp+-52), r24
	sw	(sp+-48), r23
	sw	(sp+-44), r22
	sw	(sp+-40), r21
	sw	(sp+-36), r20
	sw	(sp+-32), r19
	sw	(sp+-28), r18
	sw	(sp+-24), r17
	sw	(sp+-20), r16
	sw	(sp+-16), r15
	sw	(sp+-12), r14
	sw	(sp+-8), r13
	sw	(sp+-4), r12
	sw	(sp+0), r11
	// addi	sp, sp, -72	; Not useful if interrupts are disabled
	
	/*     switch_stacks(tos_index); */
	// r5 = & EE_mico32_system_tos[0];
	LOAD_ADDR r5, EE_mico32_system_tos
	// EE_mico32_system_tos[r4] = sp;
	sli	r4, r4, 2
	add	r4, r5, r4
	sw	(r4+0), sp
	// EE_mico32_active_tos = tos_index;
	sw	(r3+0), r2
	// sp = EE_mico32_system_tos[r2];
	sli	r2, r2, 2
	add	r2, r5, r2
	lw	sp, (r2+0)

        /*     restore_caller_saved_registers(); */
	// addi sp, sp, 72	; Not useful if interrupts are disabled
	lw	ra, (sp+-68)
	lw	r27, (sp+-64)
	lw	r26, (sp+-60)
	lw	r25, (sp+-56)
	lw	r24, (sp+-52)
	lw	r23, (sp+-48)
	lw	r22, (sp+-44)
	lw	r21, (sp+-40)
	lw	r20, (sp+-36)
	lw	r19, (sp+-32)
	lw	r18, (sp+-28)
	lw	r17, (sp+-24)
	lw	r16, (sp+-20)
	lw	r15, (sp+-16)
	lw	r14, (sp+-12)
	lw	r13, (sp+-8)
	lw	r12, (sp+-4)
	lw	r11, (sp+0)
	
        /* } */
_end_change_stacks:
	
        /* if (is_not_marked_stacked(tid)) { */
	// r1 == tid
	bg	r0, r1, _end_run_thread

	/*     tid = EE_std_run_task_code(tid); */
	addi	sp, sp, -4
	sw	(sp+4), ra
	calli	EE_std_run_task_code
	// r1 == tid
	lw	ra, (sp+4)
	addi	sp, sp, 4
	
        /*     goto begin; */
	bi	EE_std_change_context

        /* } */
_end_run_thread:

	ret
	
	.size	EE_std_change_context, .-EE_std_change_context
