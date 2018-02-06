;;; Author 2000 paolo Gai
;;; CVS: $Id: ee_start.asm,v 1.2 2006/01/05 14:37:22 pj Exp $

; this function puts also the main task on the system stack

$NONSEGMENTED
$MODEL(TINY)
$CASE

REGDEF	R0-R15

; avoid the user stack usage :-)
ENDINSTANCE EQU 	_EE_st10_thread_end_instance

GLOBAL _EE_st10_start

EXTERN _EE_st10_thread_end_instance:NEAR
EXTERN _main:NEAR

;definition of a single code section to be rommable
ST10START_PR	SECTION CODE WORD PUBLIC 'ROM'

; this function simply clean the stack preparing it for the first task 
; that executes; R12 is the top of the user stack
_EE_st10_start PROC NEAR
    MOV WORD PTR 0FC00h,R12		; set the top of the user stack

				; remove the first pop if this function is made 
				; inline!!!
    POP R14		     	; pop the ip address pushed with this call
    POP R14		     	; pop the ip address of the final idle instruction
				; now the system stack is EMPTY!!!

    ; Now we put the main task on the system stack
    MOV R12,#0800h
    PUSH R12			; push PSW 

    MOV R12,#_main
    PUSH R12			; push _main IP

    ; Use this code if the initial CP is not FC00!!!
    ;MOV R12, #0FC00h		; we use 0FC00 CP as the main context!
    ;MOV CP,R12			; load the register set of the first thread
    ;NOP

    RETI			; and now the game starts!!! :-)
_EE_st10_start ENDP

ST10START_PR ENDS

END
