;;; Author: 2001-2002 Alessandro Colantonio
;;; CVS: $Id: start.s,v 1.2 2006/01/05 14:37:22 pj Exp $

	;; common symbols (it must be included _before_ cfg_ads.s)
	GET symbols.s
	
	;; system config
	GET cfg_ads.s

	
		
;;
;; System "bootstrap"
;;
	IMPORT main		; main thread
	IMPORT EE_install_handlers	; SWI and IRQ handler installer


	
	AREA text, CODE, READONLY

;; 
;; ENTRY POINT
;;
	;; initialization code is in ARM-mode
	CODE32


	;; bootstrap
	ENTRY
|_start|
	;; IRQ & SWI handlers installation */
 	BL	EE_install_handlers

	;; NOTE: with gcc, the system starts in User-mode. Because we
	;; have to work in System-mode, we use an SWI to assure the
	;; wanted privilege level.
	swi	0x0
	b	.		; useless, but...
	


	
		
	EXPORT EE_real_system_start
EE_real_system_start
	;;
	;; Stack pointer "set up" 
	;;
	
	;; Supervisor mode (SWI) stack pointer
 	MOV	r0, #Mode_SVC:OR:I_bit:OR:F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__SVC_STACK_ADDRESS

 	;; IRQ mode stack pointer
 	MOV	r0, #Mode_IRQ:OR:I_bit:OR:F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__IRQ_STACK_ADDRESS

	;; System mode stack pointer
	;; note: now we can enable the interrupts
 	MOV	r0, #Mode_SYS
 	MSR	cpsr_c, r0
 	LDR	sp, =__SYS_STACK_ADDRESS

	;;
	;; NOTE: now we are in SYS-mode! 
	;;

	;; main() thread "activation".
	;; We are in System-mode and ARM-mode.
  	B	main

	
	END
	
