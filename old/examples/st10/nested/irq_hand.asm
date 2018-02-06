;;; Author: 2000-2002 Paolo Gai
;;; CVS: $Id: irq_hand.asm,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $


@IF( @__ST10SEGM__ )

$SEGMENTED
$CASE

ASSUME DPP3:SYSTEM

EXTERN _EE_st10_user_stack : WORD

@ELSE

$CASE
$MODEL(TINY)
$NONSEGMENTED
$EXTEND	    
$EXTMEM

@ENDI

$INCLUDE(sethand.asm)

REGDEF	R0-R15


; thread 0
@EE_hal_set_handler(58, _my_capcom26_handler, 0FC20h)
; thread 1
@EE_hal_set_handler(57, _my_capcom25_handler, 0FCa0h)
; thread 2
@EE_hal_set_handler(56, _my_capcom24_handler, 0FCe0h)
	

GLOBAL _my_irq_init

;definition of a single code section to be rommable
IRQINIT_PR	SECTION CODE WORD PUBLIC 'ROM'


@IF( @__ST10SEGM__ )
_my_irq_init PROC FAR
@ELSE
_my_irq_init PROC NEAR
@ENDI
	OR CCM6,#00CCCh		; Capcom 26,25,24; ACCx=1 (Timer 8) CCMODx=100 (Compare Mode 0)

	; CapCom 26 thread1
	MOV CC26,#00200h	; starting time - 200h
	MOV R12, #0004Fh
	MOV CC26IC, R12		; CC26IR=0 CC26IE=1 ILVL=0011 GLVL=11

	; CapCom 25 thread2
	MOV CC25,#00180h	; starting time - 180
	MOV R12, #0004Ah
	MOV CC25IC, R12		; CC26IR=0 CC26IE=1 ILVL=0010 GLVL=10

	; CapCom 24 thread3
	MOV CC24,#00140h	; starting time - 140
	MOV R12, #00045h
	MOV CC24IC, R12		; CC26IR=0 CC26IE=1 ILVL=0001 GLVL=01

@IF( @__ST10SEGM__ )
	MOV	R3,[R0+]
	MOV	R2,[R0+]
	ATOMIC	#03h
	PUSH	R3
	PUSH	R2
	RETS
@ELSE
	RET
@ENDI
_my_irq_init ENDP

IRQINIT_PR	ENDS

END
