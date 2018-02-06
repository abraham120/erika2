; ###*B*###
; ERIKA Enterprise - a tiny RTOS for small microcontrollers
;
; Copyright (C) 2002-2011  Evidence Srl
;
; This file is part of ERIKA Enterprise.
;
; ERIKA Enterprise is free software; you can redistribute it
; and/or modify it under the terms of the GNU General Public License
; version 2 as published by the Free Software Foundation, 
; (with a special exception described below).
;
; Linking this code statically or dynamically with other modules is
; making a combined work based on this code.  Thus, the terms and
; conditions of the GNU General Public License cover the whole
; combination.
;
; As a special exception, the copyright holders of this library give you
; permission to link this code with independent modules to produce an
; executable, regardless of the license terms of these independent
; modules, and to copy and distribute the resulting executable under
; terms of your choice, provided that you also meet, for each linked
; independent module, the terms and conditions of the license of that
; module.  An independent module is a module which is not derived from
; or based on this library.  If you modify this code, you may extend
; this exception to your version of the code, but you are not
; obligated to do so.  If you do not wish to do so, delete this
; exception statement from your version.
;
; ERIKA Enterprise is distributed in the hope that it will be
; useful, but WITHOUT ANY WARRANTY; without even the implied warranty
; of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License version 2 for more details.
;
; You should have received a copy of the GNU General Public License
; version 2 along with ERIKA Enterprise; if not, write to the
; Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
; Boston, MA 02110-1301 USA.
; ###*E*###

;
;	@file ee_ccs_oo.S
;	@brief Functions to save and restore registers for Osek TerminateTask()
;	       on Cortex_mX
;	@author Gianluca Franchino
;	@author Giuseppe Serano
;	@date 2011
; @author Christoph Kreuzberger
; @date 2014
;

;*******************************************************************************
;                         PUBLIC FUNCTIONS
;*******************************************************************************
	; Functions declared in this file 
	.global	EE_hal_terminate_savestk	; void EE_hal_terminate_savestk(EE_TID tid)
	.global	EE_hal_terminate_task		; NORETURN void EE_hal_terminate_task(EE_TID tid);

;*******************************************************************************
;                         EXTERNAL DATA
;*******************************************************************************

	.global	EE_terminate_real_th_body
	.global	EE_terminate_data
	.global	EE_thread_not_terminated

;*******************************************************************************
;                              CODE SECTION
;******************************************************************************
	.text

_EPSR_T_BIT_VAL			.word	001000000h	; Value to set the T-bit in EPSR (always Thumb mode)

_EE_terminate_real_th_body_addr	.word	EE_terminate_real_th_body
_EE_terminate_data_addr		.word	EE_terminate_data
_EE_thread_not_terminated_addr	.word	EE_thread_not_terminated

	;void EE_hal_terminate_savestk(EE_TID tid);
EE_hal_terminate_savestk:
	; Save all callee-saved registers
	; R0-R3 and R12 are scratch registers, R13 ->(MSP), R14 ->(LR), R15 -> (PC)
	PUSH	{R4-R11}			; Store R4, R5, R6, R7 onto stack 
	PUSH	{LR}			; Store link register (return address)
  fstmdbd sp!,         {d0-d15}
  mrs     r4,          spsr
  fmrx    r5,          fpscr
  stmfd   sp!,         {r4,r5}
	;R0 == tid
	LSLS	R0, R0, #2		; R0 = tid << 2
	LDR	R1, _EE_terminate_real_th_body_addr	; R1 == EE_terminate_real_th_body[tid]
	ADD	R1, R1, R0
	LDR	R1, [R1]
	; Save the stack pointer (including space for registers)
	; R2 == & EE_terminate_data[tid]
	LDR	R2, _EE_terminate_data_addr
	ADD	R2, R2, R0
	MOV	R3, SP			; Get the stack pointer
	STR	R3, [R2]		; Save stack pointer

	;Start the thread body
	BLX	R1

	; The task terminated with a return: do the usual cleanup
	LDR	R0, _EE_thread_not_terminated_addr
	BLX	R0


	BX	LR			; Return

	;void EE_hal_terminate_task(EE_TID tid) NORETURN; */
EE_hal_terminate_task:
	; R0 == tid

	; Restore the stack pointer
	; R1 == & EE_terminate_data[tid]
	LSLS	R0, R0, #2		; R0 = tid << 2	
	LDR	R1, _EE_terminate_data_addr	; R1 == & EE_terminate_data[tid]
	ADD	R1, R1, R0
	LDR	R2, [R1]
	MOV	SP, R2


  LDMFD   SP!,         {R4,R5}
  FLDMIAD SP!,         {D0-D15}
  FMXR    FPSCR,       R5
  MSR     SPSR_CF,     R4
  
	POP	{R3}			; Get link register from stack
	MOV	LR, R3			; Restore the link register
	; Restore R8, R9, R10, R11 from stack
	POP	{R4-R11}

	BX	LR			; Return

	.end
