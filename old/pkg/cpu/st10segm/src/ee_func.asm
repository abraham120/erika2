;;; Author: 2001 Paolo Gai
;;; CVS: $Id: ee_func.asm,v 1.2 2006/01/17 13:14:46 pj Exp $

; The thread frame:
;
; CP
; DPP2
; DPP0
; MDH
; MDL
; MDC
; PSW
; CSP
; IP
; ...
; Endcycle segment
; Endcycle offset

; The informations that the HAL stores for each thread are located at:
;
; when the thread x is active, we store:
; st10_active_tid := x (the current thread)
; st10_thread_tos[x+1] := the index of the top of the stack for thread x
; st10_tos[st10_thread_tos[x+1]] := (DPP1,R0) , the top of stack for thread x
; st10_thread_cp[x] := register bank for thread x
; hal_thread_body[x] := body function for thread x


$SEGMENTED
$CASE
REGDEF	R0-R15

ASSUME DPP3:SYSTEM

GLOBAL _EE_hal_ready2stacked
GLOBAL _EE_st10_endcycle_ready
GLOBAL _EE_st10_endcycle_stacked
GLOBAL _EE_st10_IRQ_ready
GLOBAL _EE_st10_IRQ_stacked
GLOBAL _EE_hal_stkchange

EXTERN _EE_st10_thread_end_instance:FAR
EXTERN _EE_st10_active_tid:WORD
EXTERN _EE_st10_thread_tos:WORD
EXTERN _EE_st10_tos:WORD
EXTERN _EE_hal_thread_body:WORD
EXTERN _EE_st10_thread_cp:WORD

@IF( @__ST10_OPTIMIZED__ )
@IF( @__ALLOW_NESTED_IRQ__ )
GLOBAL _EE_st10_IRQ_end_instance
EXTERN _EE_st10_optimized_IRQ_end_instance:FAR
EXTERN _EE_IRQ_nesting_level:WORD
@ENDI
@ENDI


;definition of a single code section to be rommable
ASSLEVEL_PR	SECTION CODE WORD PUBLIC 'ROM'

@IF( @__ST10_OPTIMIZED__ )
@IF( @__ALLOW_NESTED_IRQ__ )

_EE_st10_IRQ_end_instance PROC FAR

	BCLR IEN			; disable interrupts
	NOP

	; Decrement the nested interrupt counter
	EXTP #PAG _EE_IRQ_nesting_level,#1
	MOV R2, POF _EE_IRQ_nesting_level
	ADD R2, ONES
	EXTP #PAG _EE_IRQ_nesting_level,#1
	MOV POF _EE_IRQ_nesting_level, R2

	; If it is a nested interrupt, jump to the stacked interrupt!
	CMP R2, ZEROS
	JMPR cc_NE, _EE_IRQ_stacked
	JMPS SEG _EE_st10_optimized_IRQ_end_instance, SOF _EE_st10_optimized_IRQ_end_instance

_EE_IRQ_stacked:
	; execute the stacked interrupt

	MOV R8,[R0]			  ; Pop CP without increment
	MOV CP, R8
	NOP

	; now the registers have the same form as when the function was called
	; since we already used the CP value, we can simply discard it
	ADD R0, #2d			  ; Pop CP increment

	PUSH R8
	MOV R8,[R0+]
	MOV DPP2,R8			  ; load DPP2
	MOV R8,[R0+]
	MOV DPP0,R8			  ; load DPP0	
	MOV R8,[R0+]
	MOV MDH,R8			  ; load MDH
	MOV R8,[R0+]
	MOV MDL,R8			  ; load MDL
	MOV R8,[R0+]
	MOV MDC,R8			  ; load MDC
	POP R8

        ;Jump to the process to active
        MOV [-R0],R2  			  ; save R2 into the user stack
	MOV R2,[R0+#02h]		     
	PUSH R2				  ; save PSW
	MOV R2,[R0+#04h]   
	PUSH R2				  ; save CSP
	MOV R2,[R0+#06h] 
	PUSH R2				  ; save IP
	MOV R2,[R0+]       		  ; get  R2 back
	ADD R0,#06h	       
	RETI				  ; return
_EE_st10_IRQ_end_instance ENDP

@ENDI
@ENDI


; _st10_endcycle_ready (see in the middle _hal_ready2stacked)
; _st10_IRQ_ready      (see in the middle _hal_ready2stacked)
; This function is called at the end of an instance of a task.
; when it is called, the stack frame of the ending task is clean,
; and we can use all the Rx registers...
; THIS FUNCTION IS CALLED WITH A JMP
; The stack pointers have to be saved
; The function creates the stack frame and executes the task passed as parameter
; R12 contains the TID of the new thread

; - This function is called when a thread is activated; the current context is
;   saved and a new frame is created on the correct stack.
; R12 contains the TID of the new thread
_EE_hal_ready2stacked PROC FAR
	; save the current thread frame
	PUSH R8
					  ; IP + CSP were saved with the CALLS to this function
	MOV R8,PSW			  ; save PSW
	MOV [-R0],R8
	MOV R8,MDC			  ; save MDC
	MOV [-R0],R8
	MOV R8,MDL			  ; save MDL
	MOV [-R0],R8
	MOV R8,MDH			  ; save MDH
	MOV [-R0],R8
	MOV R8,DPP0			  ; save DPP0
	MOV [-R0],R8
	MOV R8,DPP2			  ; save DPP2
	MOV [-R0],R8
	MOV R8,CP			  ; save CP
	MOV [-R0],R8

	POP R8				  ; revert R8 

	; at this time R0-R15 have the correct values, and the context is built
	; correctly into the user stack. Now we have to change the registers using CP

	; change the CP to a new value, so we can arrange something
	; since MDC, MDH and MDL has been saved, we use them as temp registers
	MOV MDH,R8			  ; save R8, R12 into temp registers
_EE_st10_endcycle_ready:
        MOV MDL,R12

	; save the current R0 into the _st10_stack_tos data structure
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

_EE_st10_IRQ_ready:
	; the function hal_IRQ_ready should pass MDL = R12 = new tid!!!
	; get the new values for CP, DPP1, R0...
	EXTP #PAG _EE_st10_active_tid,#1
	MOV POF _EE_st10_active_tid,R12	  ; set the new _st10_active_tid value

	MOV R8,R12			  ; compute the address of the new R0 and new DPP1
	SHL R8,#1d
	ADD R8,#POF _EE_st10_thread_tos+2d
	EXTP #PAG _EE_st10_thread_tos,#1
	MOV R8,[R8]			  ; R8 = st10_thread_tos[st10_active_tid+1]

	SHL R8,#2d
	ADD R8,#POF _EE_st10_tos  	          ; R8 contains the address in the st10_tos table

	EXTP #PAG _EE_st10_tos,#2
	MOV R12,[R8+#2d]		  ; load new DPP1
	MOV R8,[R8]			  ; load new R0
	PUSH R8			  	  ; save R0 on the system stack

	MOV R8,MDL			  ; compute the address of the new CP (R12 was saved into MDL!)
	SHL R8,#1d
	ADD R8,#POF _EE_st10_thread_cp
	EXTP #PAG _EE_st10_thread_cp,#1	  ; push the CP value 
	MOV R8,[R8]
	PUSH R8

	MOV R8,MDH			  ; revert R8
	MOV MDH,R12			  ; save DPP1 in a temp register
	MOV R12,MDL			  ; revert R12

	; now the old context is saved, MDH= new R0, MDC= new DPP1, MDL=new TOS, new CP is on the stack

	POP CP				  ; change the registers R0-R15!!!

	; all the registers can be considered "empty"!!!

	MOV DPP1, MDH			  ; set the new DPP1
	POP R0				  ; set the new R0

	MOV R1, ZEROS
	MOV MDC, R1			  ; reset MDC
	MOV DPP0, R1			  ; reset DPP0
	MOV DPP2, R1			  ; reset DDP2

	; save the endcycle function
	MOV R8,#SOF _EE_st10_thread_end_instance
	MOV [-R0],R8
	MOV R8,#SEG _EE_st10_thread_end_instance
	MOV [-R0],R8

	; activate the new body! (MDL = new TOS)
	MOV R13,#0800h
	PUSH R13			; PSW of the activated task

	MOV R2, MDL
	SHL R2,#2d
	ADD R2,#POF _EE_hal_thread_body

	EXTP #PAG _EE_hal_thread_body,#4
	MOV R13, [R2+#2d]
	PUSH R13			; CSP

	MOV R13, [R2]
	PUSH R13			; IP

	RETI				; and wake up the new thread!!!
_EE_hal_ready2stacked ENDP

; _st10_endcycle_stacked  (see in the middle _hal_ready2stacked)
; _st10_endcycle_ready    (see in the middle _hal_ready2stacked)
; - THIS FUNCTION IS CALLED WITH A CALL INSTRUCTION
; - This function is called at the endcycle
; - The stack of the routine is supposed clean
; - The stack pointers have to be saved
; - The function executes the task that is saved at the top of the stack passed as parameter


; - This function is called when we need to switch from a frame to another frame that is already
;   saved
; R12 contains the TID of the new thread
_EE_hal_stkchange PROC FAR
	; save the current thread frame
	PUSH R8
					  ; IP + CSP were saved with the CALLS to this function
	MOV R8,PSW			  ; save PSW
	MOV [-R0],R8
	MOV R8,MDC			  ; save MDC
	MOV [-R0],R8
	MOV R8,MDL			  ; save MDL
	MOV [-R0],R8
	MOV R8,MDH			  ; save MDH
	MOV [-R0],R8
	MOV R8,DPP0			  ; save DPP0
	MOV [-R0],R8
	MOV R8,DPP2			  ; save DPP2
	MOV [-R0],R8
	MOV R8,CP			  ; save CP
	MOV [-R0],R8

	POP R8				  ; revert R8 

	; at this time R0-R15 have the correct values, and the context is built
	; correctly into the user stack. Now we have to change the registers using CP

	; prepare the system to switch to the new context
	; since MDC, MDH and MDL has been saved, we use them as temp registers
	MOV MDH,R8			  ; save R8 and R12 into the user stack
_EE_st10_endcycle_stacked:
        MOV MDL,R12

	; save the current R0 into the _st10_stack_tos data structure
	EXTP #PAG _EE_st10_active_tid,#1
	MOV R8, POF _EE_st10_active_tid	  ; R8 = st10_active_tid

	SHL R8,#1d
	ADD R8,#POF _EE_st10_thread_tos+2d
	EXTP #PAG _EE_st10_thread_tos,#1
	MOV R8,[R8]			  ; R8 = st10_thread_tos[st10_active_tid+1]

	SHL R8,#2d
	ADD R8,#POF _EE_st10_tos	  	  ; R12 contains the address in the st10_tos table

	EXTP #PAG _EE_st10_tos,#1
	MOV [R8],R0			  ; save the current R0 into the TOS

_EE_st10_IRQ_stacked:
	; get the new values for CP, DPP1, R0...
	EXTP #PAG _EE_st10_active_tid,#1
	MOV POF _EE_st10_active_tid,R12	  ; set the new _st10_active_tid value

	MOV R8,R12			  ; compute the address of the new R0 and new DPP1
	SHL R8,#1d
	ADD R8,#POF _EE_st10_thread_tos+2d
	EXTP #PAG _EE_st10_thread_tos,#1
	MOV R8,[R8]			  ; R8 = st10_thread_tos[st10_active_tid+1]

	SHL R8,#2d
	ADD R8,#POF _EE_st10_tos	  	  ; R8 contains the address in the st10_tos table

	EXTP #PAG _EE_st10_tos,#2
	MOV R12,[R8+#2d]		  ; load new DPP1
	MOV R8,[R8]			  ; load new R0
	PUSH R8				  ; save R0 in a temporary register

	EXTP R12,#1			  ; push the CP value (that is currently on the top of the user stack!)
	MOV R8,[R8]
	PUSH R8

	MOV R8, MDH			  ; revert R8
	MOV MDH,R12			  ; save DPP1 in a temp register
	MOV R12,MDL			  ; revert R12

	; now the registers have the same form as when the function was called

	POP CP				  ; change the registers R0-R15!!!

	; at this time R0-R15 are saved, the new registers are as they were
	; when the task was preempted
	MOV DPP1, MDH			  ; load the segment of the user stack

	POP R0

	PUSH R8
	MOV R8,[R0+]			  ; exclude CP, already loaded
	MOV R8,[R0+]
	MOV DPP2,R8			  ; load DPP2
	MOV R8,[R0+]
	MOV DPP0,R8			  ; load DPP0	
	MOV R8,[R0+]
	MOV MDH,R8			  ; load MDH
	MOV R8,[R0+]
	MOV MDL,R8			  ; load MDL
	MOV R8,[R0+]
	MOV MDC,R8			  ; load MDC
	POP R8

        ;Jump to the process to active
        MOV [-R0],R2  			  ; save R2 into the user stack
	MOV R2,[R0+#02h]		     
	PUSH R2				  ; save PSW
	MOV R2,[R0+#04h]   
	PUSH R2				  ; save CSP
	MOV R2,[R0+#06h] 
	PUSH R2				  ; save IP
	MOV R2,[R0+]       		  ; get  R2 back
	ADD R0,#06h	       
	RETI				  ; return
_EE_hal_stkchange ENDP			  

ASSLEVEL_PR ENDS

END
