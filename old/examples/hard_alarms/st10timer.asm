$CASE
$EXTEND      
$EXTMEM
$MODEL(TINY)
$NONSEGMENTED

REGDEF   R0-R15

$INCLUDE(sethand.asm)

;setto la tabella degli interrupt
@EE_hal_set_handler(16, _EE_altimer0, 0FC20h)   
@EE_hal_set_handler(17, _EE_altimer1, 0FC20h)   

GLOBAL _start_timer0

;definition of a single code section to be rommable
TIMER_ROM   SECTION CODE WORD PUBLIC 'ROM'

;**********************************
;********** START TIMER ************
;**********************************
; utilizzo il timer 1 con prescaler impostato a 1024 modo tale da rollare ogni 3.36 sec (T1I a 0x111)
; ovvero il timer viene incrementato con una frequenza di 19.531 Khz (circa 19500 volte in un secondo) 
; voglio thread0 eseguito ogni secondo.
_start_timer0 PROC NEAR

  MOV T0REL, ZEROS    ; ricarico il timer con 0
  MOV T0, ZEROS       ; Timer T0 start from 0
  MOV T01CON, #0FF07h ; increment every 51.2 uSec
  
  AND CCM0, #0FF00h
  OR CCM0, #0044h     ; Several interrupt allocated to Capcom 0 and 1
  MOV CC0IC, #0008h    ; Capcom 0, interrupt enabled on priority level 4
  MOV CC1IC, #0008h    ; Capcom 1, interrupt enabled on priority level 4
  
  BSET T0R
 
   RET
_start_timer0 ENDP

TIMER_ROM   ENDS
END

