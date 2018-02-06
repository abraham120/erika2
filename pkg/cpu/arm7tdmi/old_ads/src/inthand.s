;;; Author: 2001-2002 Alessandro Colantonio
;;; CVS: $Id: inthand.s,v 1.2 2006/01/24 10:22:22 pj Exp $

	
	;; common symbols (it must be included _before_ cfg_ads.s)
	GET symbols.s
	
	;; system config
	GET cfg_ads.s

	
	
;;
;; Imported symbols
;;

	;; user's handlers addresses
	[ TIMER_0_USED
	IMPORT EE_timer0_handler_addr
	]

	[ TIMER_1_USED
	IMPORT EE_timer1_handler_addr
	]
	
	[ EXT0_USED
	IMPORT EE_ext0_handler_addr
	]

	;; WARNING!!!
	;; Because ADS does not accept a symbol that has the 
	;; prefix '__' and it does not accept FP as a valid 
	;; symbol, all the scheduler choice symbols are modified 
	;; adding the '_SCHED' suffix
	
	;; kernel scheduler addresses 
	IMPORT	EE_IRQ_end_instance

	
	;; Angel modules addresses
	[ DEBUG
	IMPORT	Angel_IRQ_addr
	IMPORT	Angel_SWI_addr
	]

	;; stack used by IRQ handlers
	[ IRQ_STACK_NEEDED:LAND:MULTI
	IMPORT EE_arm7_IRQ_tos
	]
		
	;; see start.s in current directory
	IMPORT EE_real_system_start
	
		
;;
;; Exported symbols
;;
	;; hardware and software interrupts handlers
	EXPORT	EE_IRQ_handler
	EXPORT	EE_SWI_handler

	

;;
;; Code area
;;
	AREA	data, DATA, READWRITE

;; this variable is used by arm7_change_to_irq_tos and
;; arm7_change_from_irq_tos to store the current thread TOS
	[ IRQ_STACK_NEEDED:LAND:MULTI
EE_arm7_temp_tos
	DCD	0x00000000	; sys
	DCD	0x00000000	; irq
	]

;; interrupt handlers nesting
	[ ALLOW_NESTED_IRQ
EE_IRQ_nesting_level
	DCD	0x00000000	; it must be 0!!!
	]


	
				
	
	AREA	text, CODE, READONLY

	;; kernel code is in ARM-mode
	CODE32
	
	;; Address of the IRQ controller for the Samsung KS32C50100.
	;; NOTE: it is in the text segment (ROM?) because it cannot
	;;       be an immediate operand and it is constant
INTPND	DCD	0x03ff4004


		
	[ IRQ_STACK_NEEDED:LAND:MULTI
		
;; 
;; This code is called when we have to change from the thread stack to
;; the IRQ stack. Note that this routine is called when the CPU is in
;; IRQ_mode and it is not important to return in this mode...
;; R2 MUST NOT BE MODIFIED!
;; 
EE_arm7_change_to_irq_tos
	MOV	r3, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, r3

	LDR	r0, =EE_arm7_temp_tos
	STMIA	r0!, {sp}
	
	LDR	r1, =EE_arm7_IRQ_tos
	LDMIA	r1!, {sp}

	MOV	r3, #Mode_IRQ:OR:I_bit
 	MSR	cpsr_c, r3
	
	STMIA	r0, {sp}
	LDMIA	r1, {sp}

	MOV	pc, lr


	
;; 
;; This code is called when we have to change from the IRQ stack to
;; the thread stack. Note that we don't have to save the IRQ TOS 
;; because the IRQ stack is empty. Note also that this routine is 
;; called when the CPU is in SYS_mode and it _must_ return in this 
;; mode when it ends...
;;
EE_arm7_change_from_irq_tos
	LDR	r0, =EE_arm7_temp_tos
	LDMIA	r0!, {sp}

	MOV	r3, #Mode_IRQ:OR:I_bit
 	MSR	cpsr_c, r3
	
	LDMIA	r0, {sp}
	
	MOV	r3, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, r3

	MOV	pc, lr

	] ; IRQ_STACK_NEEDED:LAND:MULTI

	
		
;;
;; Hardware interrupts handler
;;
EE_IRQ_handler	
	;; NOTE: interrupts are disabled

	;; save LR_irq, PSR of the preempted thread and work registers
	;; that are not preserved across function calls -- that can be
	;; overwritten if another interrupt occurs while the current
	;; one is being processed
	STMFD	sp!, {r0-r3,r12,lr}
	MRS	r0, spsr
	STMFD	sp, {r0, lr}^	;; thread return address and cpsr
	NOP
	SUB	sp, sp, #8	; ARM7 "bug"
	

	;; R0 contains the IRQ number
	LDR	r1, INTPND	; get address of the IRQ status reg 
	LDR	r0, [r1]	; read the status reg byte


 	;;
	;; TIMER0 handler
	;;
	[ TIMER_0_USED
	TST	r0, #0x0400
	BEQ	timer0used_end
	
	;; clear interrupt source (*INTPND |= 0x0400)
	ORR	r0, r0, #0x0400
	STR	r0, [r1]
	[ TIME_SUPPORT
 	ADD	sp, sp, #8	; do not restore spsr and lr_sys...
 	LDMFD	sp!, {r0-r3,r12,lr}
	SUBS	pc, lr, #4
	|
	LDR	r2, =EE_timer0_handler_addr
	B	realjumptohandler
	] ; TIME_SUPPORT

timer0used_end
	] ; TIMER_0_USED


	;;	
	;; TIMER1 handler
	;;
	[ TIMER_1_USED
	TST	r0, #0x0800
	BEQ	timer1used_end
	
	;; clear interrupt source (*INTPND |= 0x0800)
	ORR	r0, r0, #0x0800
	STR	r0, [r1]
	LDR	r2, =EE_timer1_handler_addr
	B	realjumptohandler
timer1used_end
	] ; TIMER_1_USED



	;;
	;; EXT0 handler
	;;
	[ EXT0_USED
	TST	r0, #0x0001
	BEQ	ext0used_end

	;; clear interrupt source (*INTPND |= 0x0001)
	ORR	r0, r0, #0x0001
	STR	r0, [r1]
	LDR	r2, =EE_ext0_handler_addr
	B	realjumptohandler
ext0used_end
	] ; EXT0_USED



	;;
	;; Detect Angel Monitor requests
	;;
;;; useless...
;;	[ DEBUG
;;	TST	r0, #0x00C0	; COM1 RX/TX (debugging port...)
;;	]

 	ADD	sp, sp, #8	; do not restore spsr and lr_sys...
 	LDMFD	sp!, {r0-r3,r12,lr}

	[ DEBUG
	;; push a "void content" and R0 (work register)
 	STR	r0, [sp, #-8]!

	;; get the Angel address and push it into the "void location"
 	LDR	r0, =Angel_IRQ_addr
	LDR	r0, [r0]
 	STR	r0, [sp, #4]

	;; restore the work register R0 and jump to Angel
 	LDMFD	sp!, {r0,pc}
	
	|
	
	;; 
	;; if it isn't a known request, simply return 
	;;
	
	;; clear all pending interrupt requests
	STMFD	sp!, {r0,r1}
	LDR	r1, INTPND
	MOV	r0, #0xFFFFFFFF
	STR	r0, [r1] 
	LDMFD	sp!, {r0,r1}

	;; return
	SUBS	pc, lr, #4
	] ; DEBUG



	;;
	;; Jump to the correct handler
	;;
realjumptohandler
	[ ALLOW_NESTED_IRQ

	;; increase the nesting level
	LDR	r0, =EE_IRQ_nesting_level
	LDR	r1, [r0]
	ADD	r1, r1, #1
	STR	r1, [r0]
	
	[ IRQ_STACK_NEEDED:LAND:MULTI
	;; if this is the first handler instance then we have to
	;; change stack
	CMP	r1, #1
	BLEQ	EE_arm7_change_to_irq_tos
	]
	
	;; now we can re-enable interrupts and switch to SYS mode
 	MOV	r0, #Mode_SYS
 	MSR	cpsr_c, r0
	
	|
	
	;; now we can switch to SYS mode
 	MOV	r0, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, r0
	
	] ; ALLOW_NESTED_IRQ

	
	;; 
	;; jump to the correct handler
	;; 
	MOV	lr, pc
	LDR	pc, [r2]

	
	[ ALLOW_NESTED_IRQ
	;; we can disable interrupts
 	MOV	r0, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, r0

	;; decrease the nesting level
	LDR	r0, =EE_IRQ_nesting_level
	LDR	r1, [r0]
	SUB	r1, r1, #1
	STR	r1, [r0]

	;; is this the first handler instance?
	CMP	r1, #0
	
	[ IRQ_STACK_NEEDED:LAND:MULTI
	;; if this is the first handler instance then we have to
	;; change stack
	BLEQ	EE_arm7_change_from_irq_tos
	]
		
	;; call the scheduler only if this is the first instance
	BLEQ	EE_IRQ_end_instance

	| ; ALLOW_NESTED_IRQ

	;; call the scheduler only if this is the first instance
	BL	EE_IRQ_end_instance
	
	] ; ALLOW_NESTED_IRQ

	;; switch to IRQ mode and disable _only_ IRQ, _not_ FIQ
 	MOV	r0, #Mode_IRQ:OR:I_bit
 	MSR	cpsr_c, r0
	
	;; restore IRQ-handler working registers and return from IRQ
	LDMFD	sp, {r0, lr}^	; cpsr and lr of preempted thread
	MSR	spsr_cf, r0
	ADD	sp, sp, #8	; ARM7 "bug"
	LDMFD	sp!, {r0-r3,r12,lr}
	SUBS	pc, lr, #4
	

		
;;
;; Software interrupts handler
;;

EE_SWI_handler
	STMFD	sp!, {r4}
	LDR	r4, [lr, #-4]	; calculate address if SWI instruction
	BIC	r4, r4, #0xff000000 ; mask off bits
	CMP	r4, #0		; is a system start request?
	LDMFD	sp!, {r4}
	BEQ	EE_real_system_start

	[ DEBUG

	;; push a "void content" and R0 (work register)
 	STR	r0, [sp, #-8]!

	;; get the Angel address and push it into the "void location"
 	LDR	r0, =Angel_SWI_addr
	LDR	r0, [r0]
 	STR	r0, [sp, #4]

	;; restore the work register R0 and jump to Angel
 	LDMFD	sp!, {r0,pc}
	
	|
	
	;; 
	;; if it isn't a known request, simply return 
	;;
	
	;; return
	MOVS	pc, lr
	
	] ; DEBUG

	
	END
