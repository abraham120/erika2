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

;;; Author: 2001 Paolo Gai
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

EXTERN _EE_st10_active_tid : WORD
EXTERN _EE_st10_thread_tos : WORD
EXTERN _EE_st10_tos        : WORD
EXTERN _EE_st10_IRQ_end_instance:FAR
EXTERN _EE_st10_IRQ_tos    :FAR

@*DEFINE EE_hal_set_handler(__irq, __f, __cp) @LOCAL( __irqname, __stkchange_end )

EXTERN @__f             : FAR

SectASMHandler SECTION CODE WORD PUBLIC 'ROM'

@__irqname@__irq PROC TASK INTNO=@__irq
	BCLR IEN			; disable the interrupt response.  
	NOP

	SUB R0,#06H			; save R1 to preserve its value. 
	MOV [-R0],R1 
	ADD R0,#08H      	 

	POP R1				;take IP of the process interrupt.
	MOV [-R0],R1   			;load IP in the user stack.
	POP R1				;take CSP of the process interrupt. 
	MOV [-R0],R1			;load CSP in the user stack.
	POP R1				;take PSW of the process interrupt.		     
	MOV [-R0],R1			;load PSW in the user stack.

	MOV R1,[R0+#-2d]	        ;load the original R1
	                                 
	; now in the user stack there is ip+csp+psw
	; R0-R15 have the correct values
	; the system stack is clean

	PUSH R1				; save R1 in the system stack
	MOV R1,MDC	  		; save MDC
	MOV [-R0],R1
	MOV R1,MDL			; save MDL
	MOV [-R0],R1
	MOV R1,MDH			; save MDH
	MOV [-R0],R1
	MOV R1,DPP0			; save DPP0
	MOV [-R0],R1
	MOV R1,DPP2			; save DPP2
	MOV [-R0],R1
	MOV R1,CP			; save CP
	MOV [-R0],R1

	MOV MDL, R0			; save the current tos

	POP R1

	MOV CP,	#@__cp
	NOP

	MOV R0, MDL			; reload the current tos


@IF( @__ALLOW_NESTED_IRQ__ )
	; Add 1 to the nested interrupt counter
	EXTP #PAG _EE_IRQ_nesting_level,#1
	MOV R2, POF _EE_IRQ_nesting_level
	SUB R2, ONES
	EXTP #PAG _EE_IRQ_nesting_level,#1
	MOV POF _EE_IRQ_nesting_level, R2
	CMP R2, #01h
	JMPR cc_NE, @__stkchange_end@__irq
@ENDI
	; these lines changes the stack pointers
	EXTP #PAG _EE_st10_active_tid,#1
	MOV R8, POF _EE_st10_active_tid	  ; R8 = st10_active_tid

	SHL R8,#1d
	ADD R8,#POF _EE_st10_thread_tos+2d
	EXTP #PAG _EE_st10_thread_tos,#1
	MOV R8,[R8]			  ; R8 = st10_thread_tos[st10_active_tid+1]

	SHL R8,#2d
	ADD R8,#POF _EE_st10_tos 	          ; R8 contains the address in the st10_tos table

	EXTP #PAG _EE_st10_tos,#1
	MOV [R8],R0			  ; save the current R0 into the TOS

	; Reload the stack pointers
	EXTP #PAG _EE_st10_IRQ_tos, #2
	MOV R0, POF _EE_st10_IRQ_tos
	MOV R1, POF _EE_st10_IRQ_tos+2d
	MOV DPP1, R1
@__stkchange_end@__irq:

	MOV MDC, ZEROS

	; Push return address and CSP in the user stack	
	MOV R12, #SOF _EE_st10_IRQ_end_instance
	MOV [-R0],R12
	MOV R12, #SEG _EE_st10_IRQ_end_instance
	MOV [-R0],R12

@IF( @__ALLOW_NESTED_IRQ__ )
	BSET IEN
@ENDI

	JMPS SEG @__f, SOF @__f
	RETV
@__irqname@__irq ENDP

SectASMHandler ENDS

@ENDD @" hal_set_handler
