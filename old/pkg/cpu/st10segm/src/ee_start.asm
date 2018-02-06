;;; Author: 2000 Paolo Gai
;;; CVS: $Id: ee_start.asm,v 1.2 2006/01/05 14:37:22 pj Exp $

; this function puts also the main task on the system stack

$SEGMENTED
$CASE
REGDEF	R0-R15

ASSUME DPP3:SYSTEM

GLOBAL _EE_st10_start

EXTERN _EE_st10_thread_end_instance:FAR
EXTERN _main:FAR

; avoid the user stack usage :-)
ENDINSTANCE EQU	_EE_st10_thread_end_instance


;definition of a single code section to be rommable
ST10START_PR	SECTION CODE WORD PUBLIC 'ROM'

; this function simply clean the stack preparing it for the first task 
; that executes; R12 is the top of the user stack
_EE_st10_start PROC FAR
	;MOV WORD PTR 0FC00h,R12		; set the top of the user stack
	MOV R0, R12			; set the top of the user stack
	MOV DPP1, R13

	; Now we put the main task on the system stack

	; activate the new body! (MDL = new TOS)
	MOV R13,#0800h
	PUSH R13			; PSW of the activated task
	MOV R13, #SEG _main
	PUSH R13			; CSP
	MOV R13, #SOF _main
	PUSH R13			; IP

	RETI			; and now the game starts!!! :-)
_EE_st10_start ENDP

ST10START_PR ENDS

END





