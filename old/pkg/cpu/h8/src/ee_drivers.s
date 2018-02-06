;;; Author: 2002 Davide Cantini
;;; CVS: $Id: ee_drivers.s,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $

	.section .text
        
	.global _rom_func0		
	.global _rom_func1
	.global _rom_func2
	.global _rom_func3
	 
.ifdef __MOTOR_A_FP_USED__	
	.global _EE_motorA_action	
	.align 1 	
    _EE_motorA_action: 
	mov	#0xF000, r1  ; device register         
	bld	#1, r0l
	bst	#7, @r1
	bld	#0, r0l
	bst	#6, @r1
	rts
.endif

.ifdef __MOTOR_A_PWM_USED__	
	.global __motorA_reg
	.align 1 
    __motorA_reg:    
	mov	#0xF000, r1  ; device register         
	bld	#1, r0l
	bst	#7, @r1
	bld	#0, r0l
	bst	#6, @r1
	rts
.endif
	
.ifdef __MOTOR_B_FP_USED__	
	.global _EE_motorB_action	
	.align 1
    _EE_motorB_action:
	mov	#0xF000, r1  ; device register         
	bld	#1, r0l
	bst	#5, @r1
	bld	#0, r0l
	bst	#4, @r1
	rts
.endif


.ifdef __MOTOR_C_FP_USED__	
	.global _EE_motorC_action	
	.align 1	
    _EE_motorC_action:
	mov	#0xF000, r1  ; device register         
	bld	#1, r0l
	bst	#1, @r1
	bld	#0, r0l
	bst	#0, @r1	          
	rts
.endif

.ifdef __MOTOR_C_PWM_USED__	
	.global __motorC_reg
	.align 1	
    __motorC_reg:
	mov	#0xF000, r1  ; device register         
	bld	#1, r0l
	bst	#1, @r1
	bld	#0, r0l
	bst	#0, @r1	          
	rts
.endif


	

;;; utility function

_rom_func0:
	    	push    r6
    		jsr     @r0
    		mov.w   r6,r0
    		pop     r6
    		rts

	        
_rom_func1:
                push    r6
                mov.w   r1,r6
                jsr     @r0
                mov.w   r6,r0
                pop     r6
                rts

	       
_rom_func2:
		push    r6
    		push    r2
    		mov.w   r1,r6
    		jsr     @r0
    		adds    #2,r7
    		mov.w   r6,r0
    		pop     r6
    		rts
	       
_rom_func3:
    		push    r6
    		mov.w   @(4,r7),r3
    		push    r3
    		push    r2
    		mov.w   r1,r6
    		jsr     @r0
    		adds    #2,r7
    		adds    #2,r7
    		mov.w   r6,r0
    		pop     r6
    		rts
		
