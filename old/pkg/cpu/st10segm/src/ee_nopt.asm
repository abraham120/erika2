;;; Author: 2001 Paolo Gai
;;; CVS: $Id: ee_nopt.asm,v 1.2 2006/01/17 13:14:46 pj Exp $

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

EXTERN _EE_st10_endcycle_ready:FAR
EXTERN _EE_st10_endcycle_stacked:FAR
EXTERN _EE_st10_IRQ_ready:FAR
EXTERN _EE_st10_IRQ_stacked:FAR


GLOBAL _EE_st10_thread_end_instance
GLOBAL _EE_st10_IRQ_end_instance

EXTERN _EE_st10_active_tid:WORD
EXTERN _EE_st10_thread_tos:WORD
EXTERN _EE_st10_tos:WORD
EXTERN _EE_hal_thread_body:WORD
EXTERN _EE_st10_thread_cp:WORD

EXTERN @THREAD_ENDINSTANCE:FAR
EXTERN @IRQ_ENDINSTANCE:FAR

@IF( @__ALLOW_NESTED_IRQ__ )
EXTERN _EE_IRQ_nesting_level:WORD
@ENDI

EXTERN _EE_aux1:WORD
EXTERN _EE_aux2:WORD

;definition of a single code section to be rommable
ASSLEVEL_PR	SECTION CODE WORD PUBLIC 'ROM'

_EE_st10_thread_end_instance PROC FAR
	BCLR IEN
	NOP
	
	; A thread has just finished. Call the thread endinstance function
	MOV	R8,#SOF _1
	MOV	[-R0],R8
	MOV	R8,#SEG _1
	MOV	[-R0],R8
	JMPS	SEG @THREAD_ENDINSTANCE, @THREAD_ENDINSTANCE
_1:
	; depending on which path the endinstance executed, we have to:
	; - execute the stacked thread
	; - execute a ready thread
	; - aux4 is used to contain the body function. It is 0 if the stacked 
	;   thread should be executed
	EXTP	#PAG _EE_aux1,#01h
	CMP ZEROS, POF _EE_aux1
	JMPR cc_Z, EE_thendinstance_stacked 

	; -----------------------------------------------------------------
	; If we are here, 
	; hal_endcycle_ready was called. t is the new thread to execute
	; aux1 != 0
	; aux2 = t

	EXTP	#PAG _EE_aux2,#01h
	MOV	R12,POF _EE_aux2
	; R12 contains the t value
	JMPS SEG _EE_st10_endcycle_ready, SOF _EE_st10_endcycle_ready

	; -----------------------------------------------------------------
EE_thendinstance_stacked:
	; If we are here, 
	; hal_endcycle_stacked was called. t is the new thread to execute
	; aux1 = 0
	; aux2 = t

	EXTP	#PAG _EE_aux2,#01h
	MOV	R12,POF _EE_aux2
	; R12 contains the t value
	JMPS SEG _EE_st10_endcycle_stacked, SOF _EE_st10_endcycle_stacked
_EE_st10_thread_end_instance ENDP


_EE_st10_IRQ_end_instance PROC FAR
@IF( @__ALLOW_NESTED_IRQ__ )
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
	JMPR cc_EQ, EE_irqendinstance_normal

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

EE_irqendinstance_normal:

@ENDI

	; A thread has just finished. Call the thread endinstance function
	MOV	R8,#SOF _2
	MOV	[-R0],R8
	MOV	R8,#SEG _2
	MOV	[-R0],R8
	JMPS	SEG @IRQ_ENDINSTANCE, @IRQ_ENDINSTANCE
_2:
	; depending on which path the endinstance executed, we have to:
	; - execute the stacked thread
	; - execute a ready thread
	; - aux4 is used to contain the body function. It is 0 if the stacked 
	;   thread should be executed
	EXTP	#PAG _EE_aux1,#01h
	CMP ZEROS, POF _EE_aux1
	JMPR cc_Z, EE_irqendinstance_stacked 

	; -----------------------------------------------------------------
	; If we are here, 
	; hal_IRQ_ready was called. t is the new thread to execute
	; aux1 != 0
	; aux2 = t
	EXTP	#PAG _EE_aux2,#01h
	MOV	R12,POF _EE_aux2
	; R12 and MDL should contain the t value
	MOV MDL, R12
	EXTERN _EE_st10_IRQ_ready:FAR
	JMPS SEG _EE_st10_IRQ_ready, SOF _EE_st10_IRQ_ready

	; -----------------------------------------------------------------
EE_irqendinstance_stacked:
	; If we are here, 
	; hal_IRQ_stacked was called. t is the new thread to execute
	; aux1 = 0
	; aux2 = t

	; - This function is called at the end of an interrupt handler
	; - The stack of the interrupt routine is supposed clean
	; - The function executes the task that is saved at the top of the stack
	EXTP	#PAG _EE_aux2,#01h
	MOV	R12,POF _EE_aux2
	; R12 contains the t value
	EXTERN _EE_st10_IRQ_stacked:FAR
	JMPS SEG _EE_st10_IRQ_stacked, SOF _EE_st10_IRQ_stacked
_EE_st10_IRQ_end_instance ENDP

ASSLEVEL_PR ENDS

END
