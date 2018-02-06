;;; Author:	 2000-2002 Paolo Gai
;;; CVS: $Id: handst10.asm,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $


$CASE
$EXTEND	    
$EXTMEM
$MODEL(TINY)
$NONSEGMENTED

REGDEF	R0-R15

$INCLUDE(sethand.asm)

; thread 0
@EE_hal_set_handler(58, _my_capcom26_handler, 0FC20h)
; thread 1
@EE_hal_set_handler(57, _my_capcom25_handler, 0FC20h)
; thread 2
@EE_hal_set_handler(56, _my_capcom24_handler, 0FC20h)
	

GLOBAL _st10_irq_init

;definition of a single code section to be rommable
IRQINIT_PR	SECTION CODE WORD PUBLIC 'ROM'


_st10_irq_init PROC NEAR
	OR CCM6,#00CCCh		; Capcom 26,25,24; ACCx=1 (Timer 8) CCMODx=100 (Compare Mode 0)

	; CapCom 26 thread1
	MOV CC26,#00100h	; starting time - 256
;	MOV CC26,#08500h	; starting time - near the wraparound
;	MOV CC26,#0FC00h	; starting time - near 0
	MOV R12, #0004Bh
	MOV CC26IC, R12		; CC26IR=0 CC26IE=1 ILVL=0010 GLVL=11

	; CapCom 25 thread2
	MOV CC25,#00100h	; starting time - 256
;	MOV CC25,#08500h	; starting time - near the wraparound
;	MOV CC25,#0FC00h	; starting time - near 0
	MOV R12, #0004Ah
	MOV CC25IC, R12		; CC26IR=0 CC26IE=1 ILVL=0010 GLVL=10

	; CapCom 24 thread3
	MOV CC24,#00100h	; starting time - 256
;	MOV CC24,#08500h	; starting time - near the wraparound
;	MOV CC24,#0FC00h	; starting time - near 0
	MOV R12, #00049h
	MOV CC24IC, R12		; CC26IR=0 CC26IE=1 ILVL=0010 GLVL=01

	RET
_st10_irq_init ENDP

IRQINIT_PR	ENDS

END

























1
