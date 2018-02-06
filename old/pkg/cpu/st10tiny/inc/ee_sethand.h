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

;;; Author: 2000-2002 Paolo Gai
;;; CVS: $Id: ee_sethand.h,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $

; The macro is used to set up an interrupt handler routine:
; when the interrupt fires, f is called, and at return the symbol _st10_IRQ_cleanup is called.
; the called function must be reentrant; that is, it must leave the stack as it found when it started.
;
; __irq     is the irq which the handler is set to
; __f       is the name of the interrupt handler
; __cp      it is the CP register value of the handler. Into the demos, I typically used 0FC20h


@IF( @__ALLOW_NESTED_IRQ__ )
EXTERN _EE_IRQ_nesting_level:WORD
@ENDI

@IF( @__MULTI__ )
EXTERN _EE_hal_active_tos   : WORD
EXTERN _EE_st10_IRQ_user_tos : WORD
EXTERN _EE_st10_IRQ_sys_tos  : WORD
@ENDI

EXTERN _EE_aux1:WORD
EXTERN _EE_st10_IRQ_end_instance:NEAR



@*DEFINE EE_hal_set_handler(__irq, __f, __cp) @LOCAL( __irqname, __stkchange_end )

EXTERN @__f:NEAR

SectASMHandler SECTION CODE WORD PUBLIC 'ROM'

@__irqname@__irq PROC TASK INTNO=@__irq
	BCLR IEN			; disable the interrupt response.  
	NOP

	PUSH MDC			; save multiply registers
	PUSH MDL			 
	PUSH MDH
	
	MOV MDC, ZEROS			; clear MDC

	MOV _EE_aux1,R0		; save the top of the user stack

	SCXT CP,#@__cp			; change R0-R15
	NOP	

	MOV R0, _EE_aux1		; reload the top of the user stack

@IF( @__MONO__ )
@IF( @__ALLOW_NESTED_IRQ__ )
	; Add 1 to the nested interrupt counter
	SUB _EE_IRQ_nesting_level, ONES
@ENDI
@ENDI

	
@IF( @__MULTI__ )	
@IF( @__ALLOW_NESTED_IRQ__ )
	; Add 1 to the nested interrupt counter
	; Note: it is better to do this code or simply a SUB nestlevel,ONES + MOVR2, nestlevel?
	MOV R2, _EE_IRQ_nesting_level
	SUB R2, ONES
	MOV _EE_IRQ_nesting_level, R2
	CMP R2, #01h
	JMPR cc_NE, @__stkchange_end@__irq
@ENDI
	; these lines changes the stack pointers
	MOV R12, #_EE_hal_active_tos	; - get active top of stack
	MOV R12, [R12]				; - get the address of the structure containing (SP,R0)
	MOV [R12+#2d],R0			; - set the r0 value
	MOV [R12],SP				; - set the SP value

	; Reload the stack pointers
	MOV R0, _EE_st10_IRQ_user_tos
	MOV SP, _EE_st10_IRQ_sys_tos
@__stkchange_end@__irq:
@ENDI

        ; set __f return address to the cleanup handler
 	MOV R12, #_EE_st10_IRQ_end_instance
	PUSH R12

@IF( @__ALLOW_NESTED_IRQ__ )
	BSET IEN
@ENDI

    	JMP @__f
	RETV
@__irqname@__irq ENDP

SectASMHandler ENDS

@ENDD @" EE_hal_set_handler
