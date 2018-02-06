;;; Author: 2002 Davide Cantini
;;; CVS: $Id: ee_hal.s,v 1.6 2006/01/24 10:45:29 pj Exp $
 
	

	.equ ccr_init, 0x00	; inter.enabled(I=0),bit6=0
	.equ ccr_IRQinit, 0x40  ; I=0,bit6=1

;; Note for monostack:
;; when a thread starts its bit6 ccr initial value must be the same of
;; of the thread that activated it: could be 0 or 1. If a thread
;; is activeted by a driver its bit6 value must be 1 (ccr_IRQinit).

.ifdef __MULTI__	
        .extern _EE_h8_active_stack_id
	.extern _EE_h8_thread_stack_id
	.extern _EE_h8_sp
	
	.macro M_swap_stack         
         ;; r0=tid of new thread (NIL=-1 for main);
	 ;; each element of vector h8_thread_stack_id is 1 byte;
	 ;; so we obtain r1=h8_thread_stack_id[r0+1] just with this mov:
	 
	 mov.b	@(_EE_h8_thread_stack_id+1,r0), r1l
         mov.b  @_EE_h8_active_stack_id, r2l
	 cmp.b	r1l, r2l
	 beq	lMss\@	
	 mov.b  #0, r2h
	 add.w  r2, r2
	 mov.w	sp, @(_EE_h8_sp, r2)          ; h8_sp[h8_active_thread_id]=sp
	 mov.b  r1l, @_EE_h8_active_stack_id  ; h8_active_stack_id=h8_thread_stack_id[r0+1]
	 mov.b  #0, r1h
	 add.w  r1, r1
	 mov	@(_EE_h8_sp, r1), sp          ; sp=h8_sp[h8_active_stack_id];
lMss\@:
	.endm
.endif

	.macro M_start_thread
	
	;;; end_instance
	mov.w #_EE_thread_end_instance, r1

;;; we have to look better at this!
         push r1	    ;; when thread executes RTS this is the return address

	 ;; calculate new thread body address giving TID 
         ; r0 contains TID of the thread. we want r0 to contain body address
	 ; => r0 = hal_thread_body[r0] = @(_hal_thread_body, r0*2)
	 ; Note that r0*2 is needed since each vector element is 2 byte long
	 add     r0, r0          ; r0=r0*2
	 mov.w	@(_EE_hal_thread_body, r0), r0
	 push	r0	;; push IP of new thread	
	 rts		;; pop IP and start new thread
	
	.endm		
	
;;; ****************
;;; context handling
;;; ****************
	.section .data
	.global  _EE_IRQ_nesting_level
	
	.section .text
	.global _EE_h8_hal_ready2stacked	
	.global _EE_h8_hal_endcycle_ready
	.global _EE_h8_hal_endcycle_stacked
	.global _EE_h8_hal_IRQ_ready
	.global _EE_h8_hal_IRQ_stacked
.ifdef __MULTI__
	.global _EE_h8_hal_stkchange
.endif	

;;; ****************
;;; utility function
;;; ****************
		
	.align 1
_EE_h8_hal_ready2stacked:
	stc	ccr, r1h	; must be loaded into upper byte
	push	r1		; save ccr of preempted task
	;; save registers
	push	r4
	push	r5
	;; r6 will be pushed by new thread => not saved here.
	;; r3-r0 don't need to be saved (gcc non fa alcuna ipotesi
	;; sul valore di questi registri dopo una chiamata a funzione)
	
.ifdef __MULTI__
	push	r6
	mov.w	#0, r1
	push    r1		; short context (only r6-r4)
        M_swap_stack
.endif
	
	ldc     #ccr_init, ccr	; ccr new thread (bit6=0) 	
	M_start_thread	


	.align 1
_EE_h8_hal_endcycle_ready:
	mov	r6, sp
	
.ifdef __MULTI__
	adds	#2, sp		; remove r6 from stack of ending stack
        M_swap_stack
.else
	pop	r6		; it will be pushed by new threa	
.endif	

;;; ***************************************************************************
;;; NOTE: with multistack hal bit6 of ccr is not used. Instead of it, it
;;; ***** is used a word pushed on the stack just after the context:
;;; ***** if that value is 0 it means short context is saved (r6-r4);
;;; ***** if that value is 0x4000 it means full context saved (r6-r0).
;;; ***** Value 0x4000 is used so that the code can be the same for multi
;;; ***** and mono stack when we test bit 6 of r1h (see hal_endcycle_stacked)
;;; ***************************************************************************
	andc	#ccr_IRQinit,ccr; bit6 must be the same of preempted task
	M_start_thread


        .align 1
_EE_h8_hal_endcycle_stacked:	
	mov	r6, sp

.ifdef __MULTI__
	adds	#2, sp		; remove r6 from stack of ending stack
        M_swap_stack
	pop	r1		; more over we test r1h, both for mono and multi
.endif
	
	;; resume context
	pop	r6
	pop	r5
	pop	r4
	;; now, only if ending thread has bit6=1 then r3-r0 must
	;; be resumed too.
.ifdef __MULTI__
.else
	stc	ccr, r1h
.endif
	btst	#6, r1h		; if bit6=0 then Z=1
	beq	lecs		; if Z=1 jumps to lecs
	pop	r3
	pop	r2
	pop	r1
	pop	r0
lecs:
	rte			; pops ccr,ip and preempted task restarts

	
.ifdef __MULTI__
	.align 1
_EE_h8_hal_stkchange:
;;; save context of blocking thread
	;; save ccr
	stc	ccr, r1h
	push	r1
	;; save registers
	push	r4
	push	r5
	push	r6
	;; save lenght of context just saved (short context)
	mov	#0, r1
	push	r1
;;; load context of new thread
	M_swap_stack
	;; pop lenght of new thread context
	pop	r1
	;; pop short context
	pop	r6
	pop	r5
	pop	r4
	;; check if full context is saved and eventually pop it
	btst	#6, r1h
	beq	lstk
	pop	r3
	pop	r2
	pop	r1
	pop	r0
lstk:
	rte	
.endif

	
	.align 1
_EE_h8_hal_IRQ_stacked:
;;; ********************************************************************************
;;; NOTE: this function is the same for mono and multi stack just after we supposed
;;; ***** that every handler uses the stack of the thread that it interrupted.
;;; ***** (remember that actually semaphores cannot be used into a handler)
;;; ***** In practice it means that there is no an IRQ stack.
;;; ***** So t parameter is ignored in multistack hal too.
;;; ********************************************************************************
	;; clear EE_IRQ_nesting_level
	mov	#0, r0                             
	mov	r0, @_EE_IRQ_nesting_level	 
	;; resume context of the interrupted task

	mov	r6, sp
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r1
	pop	r0
	rte			; pops ccr, ip and restarts interrupted task
	

        .align 1
_EE_h8_hal_IRQ_ready:

	;; clear EE_IRQ_nesting_level
	mov	#0, r1			
	mov	r1, @_EE_IRQ_nesting_level	
	;; 

	mov	r6, sp
	
.ifdef __MULTI__
	mov	#0x4000, r1
	push	r1
        M_swap_stack
.else
	pop	r6		; it will be pushed by new thread
.endif

	ldc	#ccr_IRQinit, ccr    ;; ccr new thread (bit6=1)
	M_start_thread		
