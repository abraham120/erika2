;-----------------------------------------------------------------------------
;       This file contains the default low level initialization 
;       used by the RH850 C/C++ compiler.
;
;       Copyright 2012 IAR Systems AB.
;
;       $Revision: 7297 $
;-----------------------------------------------------------------------------

            MODULE      low_level_init

;---------------------------------------------------------------;
; A dummy "low level init" that will be used if the user        ;
; hasn not defined this function.                               ;
;---------------------------------------------------------------;

            PUBWEAK     ___low_level_init
            
            EXTERN      __cstart_low_level_init
            
            SECTION     .text:CODE:NOROOT
            
            REQUIRE     __cstart_low_level_init
            
___low_level_init:
            MOV         1, R10
            JMP         [LP]

            END

;-----------------------------------------------------------------------------
