;;; Author: 2002 Davide Cantini
;;; CVS: $Id: ee_handstub.s,v 1.3 2006/01/24 10:45:29 pj Exp $
			
;;; This file will be included by a ".s" user file. In that file the user
;;; will call M_set_handler for each handler that he want to install.

.macro M_set_handler handler,ext=_stub
	.section .text
	.align 1
	.global _\handler\ext
    			
_\handler\ext:
	;; don't need to disable interrupt: I=1 by Hw.
	adds	#2, r7		; remove dispatcher return ip
	pop	r6		; it will be pushed by handler
	;; save context
	push	r0
	push	r1
	push	r2
	push	r3
	push	r4
	push	r5
	;; set EE_IRQ_nesting_level to 1
	mov 	#1, r1
	mov	r1, @_EE_IRQ_nesting_level

	;; calls real handler

	jsr	@_\handler

	jmp	@_EE_IRQ_end_instance		
	
.endm	

	

	
