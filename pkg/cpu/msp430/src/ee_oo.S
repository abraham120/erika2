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
 * Functions to save and restore registers for Osek TerminateTask() on Msp430
 * Author: 2010,  Christian Grioli
 */

	.file	"ee_oo.S"
	/*Define .arch our_architecture, for now there is only msp430x1611*/	
	#ifdef __MSP430_1611__
	.arch msp430x1611
	#endif

	.text
	.p2align 1,0
	.global	EE_msp430_terminate_task
	.type	EE_msp430_terminate_task,@function
/***********************
 * Function `EE_msp430_terminate_task' 
 ***********************/
/*
 *
 *EE_msp430_terminate_task(EE_ADDR sp)
 *
 */
EE_msp430_terminate_task:
.L__FrameSize_EE_msp430_terminate_task=0x02
	mov @r15,r1
	pop r2
	pop r4
	pop r5
	pop r6
	pop r7
 	pop r8
	pop r9
	pop r10
	pop r11
	//pop r12
	//pop r13
	ret
.LfeTerminateTask:
	.size	EE_msp430_terminate_task,.LfeTerminateTask-EE_msp430_terminate_task
;; End of function 

	.p2align 1,0
	.global	EE_msp430_terminate_savestk
	.type	EE_msp430_terminate_savestk,@function
/***********************
 * Function `EE_msp430_terminate_savestk' 
 ***********************/

/**
 *EE_hal_terminate_savestk(&EE_terminate_data[t],(EE_ADDR)EE_terminate_real_th_body[t]);
 */



EE_msp430_terminate_savestk:

.L__FrameSize_EE_msp430_terminate_savestk=0x04
	//push r13
	//push r12	
	push r11
	push r10
	push r9
	push r8
	push r7
	push r6
	push r5
	push r4
	push r2
	mov r1,@r15
	call r14
/*If return, clean information*/
 	add #18,r1
	ret
.LfeSaveTask:
	.size	EE_msp430_terminate_savestk,.LfeSaveTask-EE_msp430_terminate_savestk
;; End of function 



