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
 * Author: 2016 Nils Scharnke
 *
 * Based on ee_ccrx_multi_context.src
 */

	.globl _EE_std_change_context

	.extern _EE_rh850_thread_tos
	.extern _EE_std_run_task_code
	.extern	_EE_rh850_active_tos
	.extern	_EE_rh850_system_tos
	
	.text
  
  /* Note: Global Pointer (R4) and Text Pointer (R5) are ignored at this time. */
  /* 			 Please do not modify them in your application */
  /* TODO: Prepare initial restored Stack Frame with R4 & R5 */
	/* tos = Top of Stack */
  /* tos of Task_tid is at thread_tos[tid+1] (thread_tid[0]=normal stack) */
  /* therefore tid is incremented */
	/* R6 = tid */
_EE_std_change_context:
	ADDI 1, R6, R15   /* R15 = tid+1 */
	SHL 2, R15        /* Offset: (tid+1)*4 and get rid of "stacked mark" */ 
	MOV _EE_rh850_thread_tos, R16   /* R16 = &EE_rh850_thread_tos[0] */
	ADD R16, R15                    /* R15 = &EE_rh850_thread_tos[tid+1] */
	LD.W 0[R15], R15                /* R15 = EE_rh850_thread_tos[tid+1] = tos_index */
	
	MOV _EE_rh850_active_tos, R16   /* R16 = &EE_active_tos */
	LD.W 0[R16], R17                /* R17 = EE_active_tos */
	CMP R17, R15                    
	BE end_change_stacks
	
	/* if is_not_the_current_stack(tos_index) */
	/* save_caller_saved_registers(); */
	PUSHSP R1-R2
	PUSHSP R7-R14
  PUSHSP R25-R29
	
	MOV _EE_rh850_system_tos, R18   /* R18 = &EE_rh850_system_tos[0] */
	SHL 2, R17                      /* Offset: EE_active_tos*4 */
	ADD R18, R17                    /* R17 = &EE_rh850_system_tos[EE_active_tos] */
	ST.W R3, 0[R17]                 /* Store Stack Pointer at EE_rh850_system_tos[EE_active_tos] */
	
	ST.W R15, 0[R16]    /* EE_rh850_active_tos = tos_index */
	
	SHL 2, R15          /* Offset: tos_index*4 */
	ADD R18, R15        /* R15 = &EE_rh850_system_tos[tos_index] */
	LD.W 0[R15], R15    /* R15 = EE_rh850_system_tos[tos_index] */
	MOV R15, R3         /* SP = EE_rh850_system_tos[tos_index] */
	
  /* restore registers */
	POPSP R25-R29
  POPSP R7-R14
	POPSP R1-R2
	
end_change_stacks:
	CMP R0, R6
	BLT end_run_thread
	
  PUSHSP R31
	MOV _EE_std_run_task_code, R19
	JARL [R19], R31
  MOV R10, R6
  POPSP R31
  
	BR _EE_std_change_context
	
end_run_thread:
	JMP [LP]

	.end
