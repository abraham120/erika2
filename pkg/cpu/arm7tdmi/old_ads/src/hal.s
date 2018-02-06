;;; Author: 2001-2002 Alessandro Colantonio
;;; CVS: $Id: hal.s,v 1.3 2006/01/24 10:22:22 pj Exp $


	;; common symbols (it must be included _before_ cfg_ads.s)
	GET symbols.s
	
	;; system config
	GET cfg_ads.s


	EXPORT	EE_arm7_hal_ready2stacked
	EXPORT	EE_arm7_hal_endcycle_stacked
	EXPORT	EE_arm7_hal_endcycle_ready
	EXPORT	EE_arm7_hal_IRQ_ready
	EXPORT	EE_arm7_enableIRQ
	EXPORT	EE_arm7_disableIRQ
	[ MULTI
	EXPORT  EE_arm7_hal_stkchange
	]

	;; system TOS
	[ MULTI
	IMPORT	EE_arm7_system_tos
	IMPORT	EE_arm7_active_tos
	]
	
	;; WARNING!!!
	;; Because ADS does not accept a symbol that has the 
	;; prefix '__' and it does not accept FP as a valid 
	;; symbol, all the scheduler choice symbols are modified 
	;; adding the '_SCHED' suffix
	
	;; kernel scheduler addresses 
	IMPORT	EE_thread_end_instance

	




	AREA	data, DATA, READWRITE
	
;; This variable contains the address of the new preempter thread,
;; when the preemption check is done at the end of a thread.
;;
;; NOTE: This variable is modified when a thread ends (before
;;       EE_thread_end_instance()) and its content is read when
;;       EE_thread_end_instance() ends; during this period it is
;;       important to disable interrupts in order to avoid nested
;;       EE_thread_end_instance() calls.


EE_hal_endcycle_next_thread
	DCD	0x00000000

;;
;; This variable contains the index of the new preempter thread TOS.
;;
	[ MULTI
EE_hal_endcycle_next_tos
	DCD	0x00000000
	]

	
	
		
	AREA	text, CODE, READONLY

	;;  kernel code is in ARM-mode
	CODE32

	
;; 
;; This code is called when we have to change the thread stack
;; NOTE: r1 *MUST* contain tos_index, while r0 (the thread address)
;; will be unchanged!!!
;;
	[ MULTI
EE_arm7_change_tos
	;; if tos_index == arm7_active_tos then we do not have to
	;; switch stack
	LDR	r2, =EE_arm7_active_tos
	LDR	r3, [r2]

	CMP	r3, r1
	MOVEQ	pc, lr


	;; Before changing the stack, we have to save the registers
	;; that could be modified (i.e. all the registers that should
	;; be preserved through function calls). Note that if there is
	;; not the stack change, the system will behave like the
	;; monostack version of the kernel
 	STMFD	sp!, {r4-r11}
	
	;;
	;; Save current TOS
	;;
	LDR	r2, =EE_arm7_system_tos ; r2 = arm7_system_tos
	ADD	r3, r2, r3, LSL#3 ; r3 = & arm7_system_tos[arm7_active_tos].SYS_tos

	;; arm7_system_tos[arm7_active_tos].SYS_tos = sp_SYS
	STMIA	r3!, {sp}

	;; arm7_system_tos[arm7_active_tos].IRQ_tos = sp_IRQ
	MOV	r2, #Mode_IRQ:OR:I_bit
 	MSR	cpsr_c, r2
	STMIA	r3, {sp}	
	MOV	r2, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, r2

	
	;;
	;; New current TOS
	;;
	LDR	r2, =EE_arm7_system_tos ; r2 = arm7_system_tos
	ADD	r3, r2, r1, LSL#3 ; r3 = & arm7_system_tos[tos_index].SYS_tos

	;; sp_SYS = arm7_system_tos[tos_index].SYS_tos
	LDMIA	r3!, {sp}
	
	;; sp_IRQ = arm7_system_tos[tos_index].IRQ_tos
	MOV	r2, #Mode_IRQ:OR:I_bit
 	MSR	cpsr_c, r2
	LDMIA	r3, {sp}
	MOV	r2, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, r2

	;;
	;; Update arm7_active_tos (= tos_index)
	;;
	LDR	r2, =EE_arm7_active_tos
	STR	r1, [r2]

	;; Here we have to restore the registers saved before the
	;; stack previous change. If this is the first time we use the
	;; current stack, restoring is useless... (see also inithal.c
	;; into the directories erika/tests/arm7xxxx)
 	LDMFD	sp!, {r4-r11}
	
	MOV	pc, lr
	] ; MULTI

	


	
;;
;; MONO:  void arm7_hal_ready2stacked(ADDR thread_addr)
;; MULTI: void arm7_hal_ready2stacked(ADDR thread_addr, WORD tos_index)
;;
;; Typically called into a generic primitive to implement preemption.
;;
EE_arm7_hal_ready2stacked
	;;
	;; THE CODE IS THE SAME OF arm7_hal_IRQ_ready()!!! 
	;;


		
;;
;; MONO:  void arm7_hal_IRQ_ready(ADDR thread_add)
;; MULTI: void arm7_hal_IRQ_ready(ADDR thread_add, WORD tos_index)
;;
;; Called at the end of an IRQ handler instance, when we have to 
;; activate a new thread.
;;
EE_arm7_hal_IRQ_ready
	;; we have to save LR into the stack (APCS standard)
 	STMFD	sp!, {lr}

EE_begin_of_arm7_hal_IRQ_ready
	[ MULTI
	;; (eventually) switch to the TOS of the new thread
	BL	EE_arm7_change_tos
	]
	
	;;
	;; Before calling the new thread we have to enable interrupts. 
	;; Note that only arithmetic flag field of CPSR can be set
	;; with immediate value (we use LR because we saved its content)
	;;
	MOV	lr, #Mode_SYS
 	MSR	cpsr_c, lr

	;; jump to the preempter thread (r0 = first parameter)
	MOV	lr, pc
	BX	r0

	;; NOTE: we have to disable interrupts here before calling
	;; EE_thread_end_instance() because it is a primitive
	MOV	lr, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, lr
	
	;; call the scheduler 
	BL	EE_thread_end_instance

	;; note that interrupts are disabled yet
	
	;;
	;; if hal_endcycle_next_thread == 0
	;;   then wake up the preempted thread
	;;   (arm7_hal_endcycle_stacked executed)
	;;
	;; if hal_endcycle_next_thread != 0
	;;   then activate a new thread
	;;   (arm7_hal_endcycle_ready executed)
	;;
	[ MULTI
	LDR	r2, =EE_hal_endcycle_next_tos
	LDR	r1, [r2]
	]
	
	LDR	r2, =EE_hal_endcycle_next_thread
	LDR	r0, [r2]

	CMP	r0, #0
	BNE	EE_begin_of_arm7_hal_IRQ_ready

	;; (eventually) switch to the TOS of the preempted thread
	[ MULTI
	BL	EE_arm7_change_tos
	]
	
	;; Keep interrupts disabled !!!
	;; we always return into a primitive or into an IRQ handler...
	MOV	lr, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, lr
	
	;;
	;; return to the interrupted thread
	;;
	LDMFD	sp!, {lr}
	BX	lr
		

	[ MULTI
;;; 
;;; MONO:  not defined
;;; MULTI: void arm7_hal_stkchange(ADDR thread_addr, WORD tos_index)
;;;
;;; Typically called into a generic primitive to implement a blocking
;;; synchronization primitive.
;;; 
EE_arm7_hal_stkchange
	;; we have to save LR into the stack (APCS standard)
 	STMFD	sp!, {lr}

	MOV	r1, r0
	;; note that R1 must be equal to the new context...

	;; switch to the TOS of the new thread
	BL	EE_arm7_change_tos

	;; now the stack is changed, and we need to return to the caller

	;; Keep interrupts disabled !!!
	;; we always return into a primitive or into an IRQ handler...
	MOV	lr, #Mode_SYS:OR:I_bit
 	MSR	cpsr_c, lr
	
	;; 
	;; return to the interrupted thread
	;; 
	LDMFD	sp!, {lr}
	BX	lr
	]		


	
;;
;; void arm7_hal_endcycle_stacked(WORD tos_index)
;;
;; Typically called at the end of a thread instance. 
;;
EE_arm7_hal_endcycle_stacked
	;;
	;; store the new TOS in hal_endcycle_next_tos
	;;
	[ MULTI
	LDR	r1, =EE_hal_endcycle_next_tos
	STR	r0, [r1]
	]
	
	;; store 0 in hal_endcycle_next_thread to say that we do not
	;; have to activate a new thread but we have to wake up the
	;; preempted thread
	MOV	r0, #0
	LDR	r1, =EE_hal_endcycle_next_thread
	STR	r0, [r1]
	
	;; return to EE_thread_end_instance()
	MOV	pc, lr


	
;;
;; void arm7_hal_endcycle_ready(ADDR thread_addr, WORD tos_index)
;;
;; Typically called at the end of a thread instance. 
;;
EE_arm7_hal_endcycle_ready
	;;
	;; store the new TOS in hal_endcycle_next_tos
	;;
	[ MULTI
	LDR	r2, =EE_hal_endcycle_next_tos
	STR	r1, [r2]
	]
	
	;; store the new thread address in hal_endcycle_next_thread
	LDR	r2, =EE_hal_endcycle_next_thread
	STR	r0, [r2]

	;; return to EE_thread_end_instance()
	MOV	pc, lr
	


	
;;
;; void hal_enableIRQ(void)
;;
;; Enable interrupts. Tipically called by thumb functions.
;;
EE_arm7_enableIRQ	
	;;
	;; NOTE:
	;; 1) only flag field of CPSR can be set with immediate value,
	;;    so we have to use two asm instruction;
	;; 2) preserving flag field is useless. (I hope ;)
	;;
	MRS	r0, cpsr
	BIC	r0, r0, #I_bit
	MSR	cpsr_c, r0
	BX	lr


	
;;
;; void hal_disableIRQ(void)
;;
;; Disable interrupts. Tipically called by thumb functions.
;;
EE_arm7_disableIRQ
	MRS	r0, cpsr
	ORR	r0, r0, #I_bit
	MSR	cpsr_c, r0
	BX	lr



	
	END
