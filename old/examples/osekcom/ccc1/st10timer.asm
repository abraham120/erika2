$CASE
$EXTEND      
$EXTMEM
$MODEL(TINY)
$NONSEGMENTED

REGDEF   R0-R15

$INCLUDE(sethand.asm)

;setto la tabella degli interrupt
@EE_hal_set_handler(31, _mycapcom, 0FC20h)   

GLOBAL _start_timer1

;definition of a single code section to be rommable
TIMER_ROM   SECTION CODE WORD PUBLIC 'ROM'

;**********************************
;********** START TIMER ************
;**********************************
; utilizzo il timer 1 con prescaler impostato a 1024 modo tale da rollare ogni 3.36 sec (T1I a 0x111)
; ovvero il timer viene incrementato con una frequenza di 19.531 Khz (circa 19500 volte in un secondo) 
; voglio thread0 eseguito ogni secondo.
_start_timer1 PROC NEAR

  MOV T3, ZEROS     ; Timer T3 start from 0
  MOV T3CON, ZEROS  ; increment every 400nSec
  BSET T3R    ; setto il timer 1 a circa 19.5 KHz (incremento circa ogni 51,2 uS)

  MOV T1REL, ZEROS  ; ricarico il timer con 0
  MOV T1, ZEROS     ; il timer inizia da 0
  
  AND T01CON, #00FFh
  OR T01CON, #0700h ; setto il timer 1 a circa 19.5 KHz (incremento circa ogni 51,2 uS)

  AND CCM3, #0FFFh
  OR CCM3, #0C000h  ; Compare mode 0 (several interrupt) allocated to Capcom unit 3 Timer T1 Register 15 
  MOV CC15, #0061h  ; Definisco il primo periodo   (5 ms)
  MOV R12, #0044h   ; Group 0 priority 1
  MOV CC15IC, R12   ; Abilito le interruzioni
  
  BSET T1R
   
   RET
_start_timer1 ENDP

TIMER_ROM   ENDS
END

