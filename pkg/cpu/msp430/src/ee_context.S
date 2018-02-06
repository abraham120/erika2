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
 * Context switch function for multistack on Msp430
 * Implementation of EE_std_change_context() as described in
 * pkg/cpu/common/inc/ee_context.h
 * Author: 2010,  Christian Grioli
 */


	.file	"ee_context.S"

	/*Define .arch our_architecture, for now there is only msp430x1611*/	
	#ifdef __MSP430_1611__
	.arch msp430x1611
	#endif

	.text
	.p2align 1,0
	.global EE_std_change_context
	.type	EE_std_change_context, @function



/***********************
 * Function `EE_st_change_context' 
 ***********************/
/* void EE_std_change_context(EE_TID tid); */
EE_std_change_context:
.L__FrameSize_EE_std_change_context=0x02
/*r15 tid*/
	/*TID+1*/
	mov r15,r14
	/*For security, delete info of is stacked*/
	and #0x7fff, r14
	inc r14
	/*Shift TID value because works with int(2byte)*/
	rla r14
	/*r13=EE_std_thread_tos[tid+1]
	* r13=tos_index*/
	mov EE_std_thread_tos(r14),r13

	/* if is_not_the_current_stack(tos_index) {*/
	cmp r13,&EE_msp430_active_tos
	jeq  _end_change_stacks/*If equal jump*/

	/*     save_caller_saved_registers(); */
	push r11
	push r10
	push r9
	push r8
	push r7
	push r6
	push r5
	push r4
	push r2

/*     switch_stacks(tos_index); */
	mov &EE_msp430_active_tos,r12
	// EE_msp430_system_tos[EE_msp430_active_tos] = sp
	/*Shift TID value because works with address(2byte)*/
	rla r12	
	mov r1,EE_msp430_system_tos(r12)

	// EE_msp430_active_tos = tos_index;
	mov r13,&EE_msp430_active_tos
	
	
// sp = EE_msp430_system_tos[tos_index];
/*Shift TID value because works with address(2byte)*/
	rla r13
	mov EE_msp430_system_tos(r13),r1
	/*     restore_caller_saved_registers(); */
	pop r2
	pop r4
	pop r5
	pop r6
	pop r7
	pop r8
	pop r9
	pop r10
	pop r11
     /* } */
_end_change_stacks:
/* if (is_not_marked_stacked(tid)) { */

	cmp #0,r15 /* r15 <0*/
	jl _end_run_thread
	/*     tid = EE_std_run_task_code(tid); */

	/*In r15 I have the parameter(current TID)*/
	call #EE_std_run_task_code
	/*In r15 I have the result ( TID )*/
	jmp EE_std_change_context
     /* } */
_end_run_thread:

	ret
	
LfechangeCont:
	.size	EE_std_change_context, .LfechangeCont-EE_std_change_context
;;
