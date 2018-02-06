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
	@file ee_oo.S
	@brief Functions to save and restore registers for Osek TerminateTask() on Mico32
	@author Bernardo  Dal Seno
	@date 2010
*/  

#include <cpu/mico32/inc/ee_asm_util.h>

	.text

	.global EE_hal_terminate_savestk
	.type	EE_hal_terminate_savestk, @function
/* void EE_hal_terminate_savestk(EE_TID tid); */
EE_hal_terminate_savestk:
	// r1 == tid

	// r4 == tid << 2
	sli	r4, r1, 2

	// r3 == EE_terminate_real_th_body[tid]
	LOAD_ADDR r3, EE_terminate_real_th_body
	add	r3, r3, r4
	lw	r3, (r3+0)

	/* Save the stack pointer (including space for registers) */
	// r2 == & EE_terminate_data[tid]
	LOAD_ADDR r2, EE_terminate_data
	add	r2, r2, r4
	addi	sp, sp, -72
	sw	(r2+0), sp
	
	/* Save all callee-saved registers */
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

	/* Start the thread body */
	call	r3

	/* The task terminated with a return: do the usual cleanup */
	lw	ra, (sp+4)
	addi	sp, sp, 72
	ret
	
	.size	EE_hal_terminate_savestk, .-EE_hal_terminate_savestk

	
	.global EE_hal_terminate_task
	.type	EE_hal_terminate_task, @function
	/* void EE_hal_terminate_task(EE_TID tid) NORETURN; */
EE_hal_terminate_task:
	// r1 == tid
	
	/* Restore the stack pointer */
	// r2 == & EE_terminate_data[tid]
	sli	r4, r1, 2
	LOAD_ADDR r2, EE_terminate_data
	add	r2, r2, r4
	lw	sp, (r2+0)

	/* Restore the registers and return */
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
	
	.size	EE_hal_terminate_task, .-EE_hal_terminate_task
