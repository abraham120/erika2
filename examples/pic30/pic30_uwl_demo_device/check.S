;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                TRAP MANAGER            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Trap Adress Name
.global __OscillatorFail
.global __AddressError
.global __StackError
.global __MathError
.global __DMACError

.global _guessedBadPCLow
.global _guessedBadPCHigh

.section .bss
_guessedBadPCLow: .space 2
_guessedBadPCHigh: .space 2

.section .text

;-------------------------------------------------------------------------------
; OSCILLATOR FAILURE
; - TODO
;-------------------------------------------------------------------------------
__OscillatorFail:
StayTrappedOscillatorFail:                     ;Stay in this routine
        bra     StayTrappedOscillatorFail


;-------------------------------------------------------------------------------
; ADDRESS ERROR
; - Extract the last ProgramCounter in _guessedBadPCLow _guessedBadPCHigh
; - Wait here for debugging
;-------------------------------------------------------------------------------
__AddressError:
        mov     #_guessedBadPCHigh, w1
        pop     [w1--]                  ;Pop the Program Counter from the stack.
        pop     [w1++]                  ;NOTE: PC (PCH and PCL) is stacked
        bclr    [w1], #7                ; with the SRL byte and IPL3 bit from
        inc     w1, w1                  ; CORCON. So we need just the 24-bit
        clr.b   [w1]                    ; PCH:PCL information from the stack
        mov     #_guessedBadPCLow, w1  	;Decrement that value by 2.
        mov     #2, w2                  ;Store the 24-bit result into 2x16-bit 
        subr    w2, [w1], [w1++]        ; words in RAM at- guessedBadPCHigh:Low.
        clr     w2
        subbr   w2, [w1], [w1]
        bclr    INTCON1, #3       	;Clear the trap flag.
StayTrappedAddrErr:                     ;Stay in this routine.
        bra     StayTrappedAddrErr 	;View the variables guessedBadPCHigh:Low
        retfie


;-------------------------------------------------------------------------------
; STACK ERROR
; - TODO
;-------------------------------------------------------------------------------
__StackError:
StayTrappedStackError:                     ;Stay in this routine
        bra     StayTrappedStackError

;-------------------------------------------------------------------------------
; MATHEMATIC ERROR
; - TODO
;-------------------------------------------------------------------------------
__MathError:
StayTrappedMathError:                     ;Stay in this routine
        bra     StayTrappedMathError

;-------------------------------------------------------------------------------
; DMA CHANNEL ERROR
; - TODO
;-------------------------------------------------------------------------------
__DMACError:
StayTrappedDMACError:                     ;Stay in this routine
        bra     StayTrappedDMACError


