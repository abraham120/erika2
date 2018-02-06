$CASE
$EXTEND	    
$EXTMEM
$MODEL(TINY)
$NONSEGMENTED

REGDEF	R0-R15

$INCLUDE(sethand.asm)

;setto la tabella degli interrupt
@EE_hal_set_handler(31, _mycapcom_sx, 0FC20h)	
@EE_hal_set_handler(30, _mycapcom_rx_queued, 0FC20h)	

GLOBAL _start_timer1

;definition of a single code section to be rommable
TIMER_ROM	SECTION CODE WORD PUBLIC 'ROM'

;**********************************
;********** START TIMER ************
;**********************************
; utilizzo il timer 1 con prescaler impostato a 1024 modo tale da rollare ogni 3.36 sec (T1I a 0x111)
; ovvero il timer viene incrementato con una frequenza di 19.531 Khz (circa 19500 volte in un secondo) 
; voglio thread0 eseguito ogni secondo.
_start_timer1 PROC NEAR

	MOV T1REL, ZEROS		;ricarico il timer con 0
	MOV T1, ZEROS			;il timer inizia da 0
	
	AND T01CON, #00FFh
	OR T01CON, #4700h		;setto il timer 1 a circa 19.5 KHz (incremento circa ogni 51,2 uS)

	AND CCM3, #0FFFh
	OR CCM3, #0C000h	;Compare mode 0 (several interrupt) allocated to Capcom unit 3 Timer T1 Register 15 
	MOV CC15, #00C3h	;Definisco il primo periodo	(10 ms per il sender)
	MOV R12, #0048h	;Group 0 priority 2
	MOV CC15IC, R12	; Abilito le interruzioni
	
	AND CCM3, #0F0FFh
	OR CCM3, #0C00h	;Compare mode 0 (several interrupt) allocated to Capcom unit 3 Timer T1 Register 14 
	MOV CC14, #0124h	;Definisco il primo periodo	(15 ms)
	MOV R12, #0044h	;Group 0 priority 1
	MOV CC14IC, R12	; Abilito le interruzioni
	
	RET
_start_timer1 ENDP

TIMER_ROM	ENDS
END

