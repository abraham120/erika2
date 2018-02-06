;;; Author: 2000-2002 Paolo Gai
;;; CVS: $Id: ee_hal_optimized.asm,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $

$NONSEGMENTED
$MODEL(TINY)
$CASE

REGDEF	R0-R15

ENDINSTANCE EQU 	_EE_st10_thread_end_instance

EXTERN _EE_st10_thread_end_instance:NEAR

GLOBAL _EE_st10_endcycle_ready
GLOBAL _EE_st10_ready2stacked
GLOBAL _EE_st10_IRQ_ready 

EXTERN _EE_aux1:WORD

@IF( @__MONO__)
EXTERN _EE_aux2:WORD
@ENDI




@IF( @__ALLOW_NESTED_IRQ__ )
GLOBAL _EE_st10_IRQ_end_instance
EXTERN _EE_st10_optimized_IRQ_end_instance:NEAR
EXTERN _EE_IRQ_nesting_level:WORD
@ENDI

@IF( @__MULTI__)
GLOBAL _EE_st10_stkchange
GLOBAL _EE_st10_IRQ_stacked
GLOBAL _EE_st10_endcycle_stacked

EXTERN _EE_st10_active_tos:WORD
EXTERN _EE_st10_thread_end_instance:NEAR
@ENDI


;definition of a single code section to be rommable
ASSLEVEL_PR	SECTION CODE WORD PUBLIC 'ROM'

; --------------------------------------------------------
; --------------------------------------------------------
; Common part
; --------------------------------------------------------
; --------------------------------------------------------


@IF( @__ALLOW_NESTED_IRQ__ )

_EE_st10_IRQ_end_instance PROC NEAR

	BCLR IEN			; disable interrupts
	NOP

	; Decrement the nested interrupt counter
	MOV R2, _EE_IRQ_nesting_level
	ADD R2, ONES			 ; subtract 1
	MOV _EE_IRQ_nesting_level, R2

	; If it is a nested interrupt, jump to the stacked interrupt!
	CMP R2, ZEROS
	JMPA cc_EQ, _EE_st10_optimized_IRQ_end_instance 

	; execute the stacked ointerrupt

	POP CP				; reload R0-R15

	POP MDH				; reload multiply registers
	POP MDL
	POP MDC

	RETI				; and wake up the thread!!!
_EE_st10_IRQ_end_instance ENDP

@ENDI


@IF( @__MONO__)

; --------------------------------------------------------
; --------------------------------------------------------
; MONO
; --------------------------------------------------------
; --------------------------------------------------------

; - This function is called when a new thread is activated, and the new thread preempts
;   the running thread.
; - The function saves the context and call the activated thread body.
; R12 -> new CP to load
; R13 -> IP of the thread to activate
_EE_st10_ready2stacked	PROC	NEAR
	MOV _EE_aux1, R12			; save the new CP...
	MOV _EE_aux2, R13			; save the IP...

					; remove the first pop if the function is
					; inline!!!

	POP R13				; get the return address of the running task

	MOV R12, PSW			; save PSW
	PUSH R12
	PUSH R13			; save return address (IP)

	PUSH MDC			; save/multiply registers
	PUSH MDL
	PUSH MDH

	;SCXT CP,[R12]			
	MOV R12,_EE_aux1			; reload the CP saved before
	MOV _EE_aux1,R0			; save the user stack pointer
	
	PUSH CP				; change R0-R15
	MOV CP,R12
	NOP

	MOV R0,_EE_aux1			; reload the user stack pointer

	MOV R13, #ENDINSTANCE		; killer function
	PUSH R13

	MOV R13,#0800h
	PUSH R13			; PSW of the activated task

	MOV R13,_EE_aux2		; load the IP of the activated task
	PUSH R13		

	RETI
_EE_st10_ready2stacked	ENDP

; - This function is called in an interrupt handler to activate a thread.
; - the function assumes that the system stack is clean (the interrupt handler must not have
;   pushed any word on the stack).
; - the function build another stack frame and executes it.
; R12 -> new CP to load
; R13 -> IP of the thread to activate
_EE_st10_IRQ_ready PROC NEAR
    	MOV _EE_aux2, R13		; save the IP...

					; remove the first pop if the function is
					; inline!!!
	POP R13				; remove the call to this function

	MOV _EE_aux1,R0			; save the user stack pointer
	MOV CP,R12			; change R0-R15
	NOP

	MOV R0,_EE_aux1			; reload the user stack pointer

	MOV R13, #ENDINSTANCE		; killer function
	PUSH R13

	MOV R13,#0800h
	PUSH R13			; PSW of the activated task

	MOV R13,_EE_aux2		; load the IP of the activated task
	PUSH R13		

	RETI
_EE_st10_IRQ_ready ENDP


; - This function is called when a task has finished an instance, and a new ready thread 
;   (maybe the same) is scheduled
; - Since we are at the end of an instance, the context doesn't need to be saved
;   however, we have to pop the IP pushed with the CALL that jums here, and activate the thread...
; R12 -> new CP to load
; R13 -> IP of the thread to activate

; WARNING: this function can be called only by internal_thread_endinstance because
; it have to clean the user stack!
_EE_st10_endcycle_ready PROC NEAR
	POP R9				; pop the IP pushed with the previous call

	MOV _EE_aux2, R13		; save the IP...
	MOV _EE_aux1, R0		; save the user stack pointer

	MOV CP,R12			; change R0-R15
	NOP

	MOV R0, _EE_aux1		; reload the user stack pointer

	MOV R13, #ENDINSTANCE		; killer function
	PUSH R13

	MOV R13,#0800h
	PUSH R13			; PSW of the activated task

	MOV R13,_EE_aux2		; load the IP of the activated task
	PUSH R13		

	RETI
_EE_st10_endcycle_ready ENDP

@ENDI
; End mono



@IF( @__MULTI__)

; --------------------------------------------------------
; --------------------------------------------------------
; MULTI
; --------------------------------------------------------
; --------------------------------------------------------


; - This function is called when a context of a thread have to be saved
; - The function saves the context and the stack pointers
; R12 -> address of the old stacks
; R13 -> address of the new stacks
; R12 have to be saved because I want to modify only R0 and the parameters...
_EE_st10_stkchange PROC NEAR
; CONTEXT_SAVE
	MOV [R12+#2d],R0		; save the user stack pointer; R0 is free


	POP R12				; get the return address of the running task

	MOV R0, PSW			; save PSW on the old stack
	PUSH R0

	PUSH R12			; save return address
	MOV R12, _EE_aux1			; get the old R12 value

	PUSH MDC			; save/multiply registers
	PUSH MDL
	PUSH MDH

	PUSH CP				; push the old CP; now the system stack os ok.

	MOV [R12],SP			; save the system stack pointer
					; now the context of the old task is saved

; CONTEXT_LOAD
	MOV _EE_st10_active_tos, R13       ; set the active stack

	MOV SP,[R13]			; load the new system stack pointer

	; THERE MUST BE AN INSTRUCTION HERE (because we just loaded SP and then R12 is pushed!
	MOV R0,[R13+#2d]		; new user stack tos

	POP R12				; new CP value

	MOV [R12],R0			; set the R0 in the new context
					; this setting may be eliminated only if R0 is not modified by other
					; functions...

	MOV CP, R12
	NOP

	POP MDH				; reload multiply registers
	POP MDL
	POP MDC

	RETI				; and wake up the new thread!!!
_EE_st10_stkchange ENDP

; - This function is called when a context of a thread have to be saved
; - The function saves the context and the stack pointers
; R12 -> address of the old stacks
; R13 -> address of the new stacks
; R14 -> new thread CP
; R15 -> new body
_EE_st10_ready2stacked PROC NEAR
; CONTEXT_SAVE
	MOV [R12+#2d],R0		; save the user stack pointer; R0 is free

	MOV _EE_aux1, R12			; save the value of the current tos

	POP R12				; get the return address of the running task

	MOV R0, PSW			; save PSW on the old stack
	PUSH R0

	PUSH R12			; save return address
	MOV R12, _EE_aux1			; get the old R12 value

	PUSH MDC			; save/multiply registers
	PUSH MDL
	PUSH MDH

	PUSH CP				; push the old CP; now the system stack os ok.

	MOV [R12],SP			; save the system stack pointer
					; now the context of the old task is saved

; CONTEXT_ACTIVATE
	MOV _EE_st10_active_tos, R13       ; set the active stack

	MOV SP,[R13]			; load the new system stack pointer

	MOV R13,[R13+#2d]		; load the new user stack pointer
	MOV [R14],R13			; into the new R0 :-)

	MOV [R14+#2d],R15		; load the body function into R1

	MOV CP,R14			; the new CP
	NOP

	MOV R13, #ENDINSTANCE		; killer function
	PUSH R13

	MOV R13,#0800h
	PUSH R13			; PSW of the activated task

	PUSH R1				; IP of the new thread

	RETI				; and wake up the new thread!!!
_EE_st10_ready2stacked ENDP


; - This function is called at the end of an interrupt handler
; - The stack of the interrupt routine is supposed clean
; - The function executes the task that is saved at the top of the stack
; R12 -> address of the new stacks
_EE_st10_IRQ_stacked PROC NEAR
; Note that the context have not to be saved, because it is always restored
; clean by the interrupt handler!!! also the registers can be left dirty!!!

; CONTEXT_LOAD
	MOV _EE_st10_active_tos, R12       ; set the active stack

	MOV SP,[R12]			; load the new system stack pointer

	MOV R0,[R12+#2d]  		; take the new user tos
	
	POP R1				; take the new CP
	MOV [R1], R0			; set the new R0 to the correct value

	MOV CP, R1			; set R0-R15
	NOP

	POP MDH				; reload multiply registers
	POP MDL
	POP MDC

	RETI				; and wake up the new thread!!!
_EE_st10_IRQ_stacked ENDP

; - This function is called when a context of a thread have to be saved
; - The function saves the context and the stack pointers
; R12 -> address of the new stacks
; R13 -> new thread CP
; R14 -> new body
_EE_st10_IRQ_ready PROC NEAR
; similar to CONTEXT_ACTIVATE
	MOV _EE_st10_active_tos, R12       ; set the active stack

	MOV SP,[R12]			; load the new system stack pointer

	MOV R12,[R12+#2d]		; load the new user stack pointer
	MOV [R13],R12			; into the new R0 :-)

	MOV [R13+#2d],R14		; load the body function into R1

	MOV CP,R13			; the new CP
	NOP

	MOV R13, #ENDINSTANCE		; killer function
	PUSH R13

	MOV R13,#0800h
	PUSH R13			; PSW of the activated task

	PUSH R1				; IP of the new thread

	RETI				; and wake up the new thread!!!
_EE_st10_IRQ_ready ENDP

; - THIS FUNCTION IS CALLED WITH A CALL INSTRUCTION
; - This function is called at the endcycle
; - The stack of the routine is supposed clean
; - The stack pointers have to be saved
; - The function executes the task that is saved at the top of the stack passed as parameter
; R12 -> address of the old stacks
; R13 -> address of the new stacks
_EE_st10_endcycle_stacked PROC NEAR
; we have to save only the stack pointers, but not the MDH, MDC, and so on!!!
	MOV [R12+#2d],R0		; save the user stack pointer; R0 is free

	POP R1				; get the return address of the running task

	MOV [R12],SP			; save the system stack pointer
					; now the context of the old task is saved

; CONTEXT_LOAD
	MOV _EE_st10_active_tos, R13       ; set the active stack

	MOV SP,[R13]			; load the new system stack pointer

	MOV R0,[R13+#2d]  		; take the new user tos
	
	POP R1				; take the new CP
	MOV [R1], R0			; set the new R0 to the correct value

	MOV CP, R1			; set R0-R15
	NOP

	POP MDH				; reload multiply registers
	POP MDL
	POP MDC

	RETI				; and wake up the new thread!!!
_EE_st10_endcycle_stacked ENDP

; - THIS FUNCTION IS CALLED WITH A CALL INSTRUCTION
; - This function is called at the endcycle
; - The stack of the routine is supposed clean
; - The stack pointers have to be saved
; - The function creates the stack frame and executes the task passed as parameter
; R12 -> address of the old stacks
; R13 -> address of the new stacks
; R14 -> new thread CP
; R15 -> new body
_EE_st10_endcycle_ready PROC NEAR
; we have to save only the stack pointers, but not the MDH, MDC, and so on!!!
	MOV [R12+#2d],R0		; save the user stack pointer; R0 is free

	POP R1				; get the return address of the running task

	MOV [R12],SP			; save the system stack pointer
					; now the context of the old task is saved
; similar to CONTEXT_ACTIVATE
	MOV _EE_st10_active_tos, R13       ; set the active stack

	MOV SP,[R13]			; load the new system stack pointer

	MOV R13,[R13+#2d]		; load the new user stack pointer
	MOV [R14],R13			; into the new R0 :-)

	MOV [R14+#2d],R15		; load the body function into R1

	MOV CP,R14			; the new CP
	NOP

	MOV R14, #ENDINSTANCE		; killer function
	PUSH R14

	MOV R14,#0800h
	PUSH R14			; PSW of the activated task

	PUSH R1				; IP of the new thread

	RETI				; and wake up the new thread!!!
_EE_st10_endcycle_ready ENDP

@ENDI
; End Multi


ASSLEVEL_PR ENDS

END
