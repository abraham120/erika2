;-----------------------------------------------------------------------------
;       This file contains the startup code
;       used by the RH850 C/C++ compiler.
;
;       Copyright 2012-2014 IAR Systems AB.
;
;       $Revision: 7503 $
;-----------------------------------------------------------------------------

;---------------------------------------------------------------;
; Naming convention of labels in this file:                     ;
;                                                               ;
;  ?xxx  - External labels only accessed from assembler.        ;
;  __xxx - External labels accessed from or defined in C.       ;
;  xxx   - Labels local to one module (note: this file contains ;
;          several modules).                                    ;
;  main  - The starting point of the user program.              ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; Defines for RAM initialization.                               ;
;                                                               ;
; To SKIP initialization of used RAM memory with 32-bit         ;
; write accesses, define the macro:                             ;
; __NORAMINIT__                                                 ;
;                                                               ;
; example: #define __NORAMINIT__                                ;
;---------------------------------------------------------------;
#define __NORAMINIT__

;---------------------------------------------------------------;
; Includes.                                                     ;
;---------------------------------------------------------------;
#include "lxx.h"
#include "cfi.h"

            CASEON

;---------------------------------------------------------------;
; Call Frame Information                                        ;
;---------------------------------------------------------------;

            CFNAMES
            CFCOMMON

            MODULE      CSTARTUP

;---------------------------------------------------------------;
; Module start.                                                 ;
;---------------------------------------------------------------;

            EXTERN      _exception_vector_table
            EXTERN      __iar_static_base$$GP
            EXTERN      __iar_static_base$$TP
            EXTERN      __iar_static_base$$EP
            PUBLIC      __iar_program_start
            PUBLIC      ??reset_vector

;---------------------------------------------------------------;
; Exclusive Control Register                                    ;
; Used as semaphore in muticore systems.                        ;
;---------------------------------------------------------------;
            
PFSSG0MEV0  DEFINE      0xFFFEEC00
PFSSG0MEV1  DEFINE      0xFFFEEC04
PFSSG0MEV2  DEFINE      0xFFFEEC08

;---------------------------------------------------------------;
; Forward declarations of segments used in this module.         ;
;---------------------------------------------------------------;

            SECTION     CSTACK1:DATA(2)
            SECTION     CSTACK2:DATA(2)
            SECTION     `Region$$Table`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$TableS`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$Table1`:DATA:REORDER:NOROOT(0)
            SECTION     `Region$$Table2`:DATA:REORDER:NOROOT(0)

            SECTION     HEAP:DATA(2)
            SECTION     `RETENTION_RAM`:DATA
            SECTION     `Region$$RamTable`:DATA
            SECTION     .sbss:DATA
            SECTION     .sconst:CONST

;---------------------------------------------------------------;
; The startup code.                                             ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(2)
            CODE
            
;---------------------------------------------------------------;
; The startup sequence contained in the final linked            ;
; application will consist of a mosaic containing               ;
; modules and segment parts defined in this file.               ;
;                                                               ;
; The only part which is required is the call to                ;
; the function "main".                                          ;
;---------------------------------------------------------------;

?BTT_cstart_begin:
__iar_program_start:
??reset_vector:
            REQUIRE     _exception_vector_table
            REQUIRE     ?cstart_call_main
            REQUIRE     ?INIT_PSW
            REQUIRE     ?INIT_STACKS

;---------------------------------------------------------------;
; Get running PE.                                               ;
;---------------------------------------------------------------;

            STSR        0, R6, 2                        ; get HTCFG0.PEID
            SHR         16, R6
            ANDI        0x7, R6, R20                    ; set core id (PE number)
       
#ifndef __NORAMINIT__       

;---------------------------------------------------------------;
; Skip RAM init if this PE is unused.                           ;
;---------------------------------------------------------------;

            CMP          2, R20
            BGT          ?wait_ram_clear_done 



;---------------------------------------------------------------;
; Mark done and wait until all PEs have finished FRAM init.     ;
;---------------------------------------------------------------;

            MOV         PFSSG0MEV2, R9                  ; set lock
?ram_clear_lock_loop:
            SET1        0, 0[R9]
            BZ          ?ram_clear_lock_done
            SNOOZE
            BR          ?ram_clear_lock_loop

?ram_clear_lock_done:
            MOV         PFSSG0MEV1, R7                  ; inc semaphore
            LD.W        0[R7], R8
            ADD         1, R8
            ST.W        R8, 0[R7]      
            CLR1        0, 0[R9]                        ; clear lock
?wait_ram_clear_loop:
            LD.W        0[R7], R8
            CMP         2, R8
            BZ          ?wait_ram_clear_done            ; all done?
            SNOOZE
            BR          ?wait_ram_clear_loop
?wait_ram_clear_done:



#endif
;---------------------------------------------------------------;
; Set up the global pointers.                                   ;
;---------------------------------------------------------------;

            MOV         __iar_static_base$$GP, GP
            MOV         __iar_static_base$$TP, TP

;---------------------------------------------------------------;
; Initialize the saddr base pointers.                           ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            PUBLIC      ?INIT_SADDR_BASE

?INIT_SADDR_BASE:
            ;RTMODEL     "__reg_ep", "saddr"
            MOV         __iar_static_base$$EP, EP

;---------------------------------------------------------------;
; Initialize co-processors                      ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            PUBLIC      ?INIT_PSW

?INIT_PSW:  STSR        5, R6, 0                        ; get PSW
            MOV         0x00070000, R7
            OR          R7, R6                          ; PSW.CU0 = 1, PSW.CU1 = 1, PSW.CU2 = 1
            ; Attempt to enable coprocessors. If they don't exist,
            ; this should not causes any problems. 
            ; The apropriate bits in PSW will simply remain fixed to zero.
            LDSR        R6, 5, 0                        ; set PSW

;---------------------------------------------------------------;
; Stack initializations.                                        ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            PUBLIC      ?INIT_STACKS

?INIT_STACKS:

;---------------------------------------------------------------;
; Set the stacks for all PEs.                                   ;
;---------------------------------------------------------------;

            CMP         1, R20
            BZ          ?stack_PE1
            CMP         2, R20
            BZ          ?stack_PE2
?not_used_PE:
            SNOOZE
            BR          ?not_used_PE
?stack_PE1:
            MOV         SFE CSTACK1, SP
            MOV         SP,R6
            MOV         SFB CSTACK1, R7
?stack_PE_loop1:                          ;Clear stack for PE1
            ST.W        R0, 0[R6]
            ADD         4,r6
            CMP         R7,R6
            BC          ?stack_PE_loop1
            BR __cstart_low_level_init
?stack_PE2:
            MOV         SFE CSTACK2, SP
            MOV         SP,R6
            MOV         SFB CSTACK2, R7
?stack_PE_loop2:                          ;Clear stack for PE2
            ST.W        R0, 0[R6]
            ADD         4,r6
            CMP         R7,R6
            BC          ?stack_PE_loop2


;---------------------------------------------------------------;
; If hardware must be initialized from C or if watch dog timer  ;
; must be handled or if the segment init should not be          ;
; performed it can now be done in `__low_level_init'.           ;
;---------------------------------------------------------------;
; Call the user function __low_level_init, if defined.          ;
; It is the responsibility of __low_level_init to require       ;
; __cstart_low_level_init in order to be called by cstartup.    ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

            PUBLIC      __cstart_low_level_init
            EXTERN      ___low_level_init

__cstart_low_level_init:
            MOV         R20, R6
            CALL_FUNC   ___low_level_init, LP, R1
            ANDI        0xFF, R10, R10
            BZ          ?no_seg_init
				
;---------------------------------------------------------------;
; Init heap memory.                                             ;
;---------------------------------------------------------------;

            CMP         1, R20
            BZ          ?heap_init_end
            MOV         SFE HEAP, R6
            MOV         SP,R6
            MOV         SFB HEAP, R7
            BR          ?heap_init_loop_test
?heap_init_loop:                          
            ST.W        R0, 0[R6]
            ADD         4,r6
?heap_init_loop_test:                          
            CMP         R6,R7
            BC          ?heap_init_end
?heap_init_end:
						
;---------------------------------------------------------------;
; Segment initialization code. Copy initialized ROMmed code to  ;
; RAM and ?seg_clear uninitialized variables.                   ;
;---------------------------------------------------------------;

            PUBLIC      __cstart_data_init
            EXTERN      ___iar_data_init2
__cstart_data_init:
            CMP         2, R20
            BZ          ?data_init_PE2
?data_init_PE1:
        MOV         SFE(`Region$$TableS`),r7
        MOV         SFB(`Region$$TableS`),r6
        CALL_FUNC   ___iar_data_init2, LP, R1
            MOV         SFE(`Region$$Table`),r7
            MOV         SFB(`Region$$Table`),r6
            CALL_FUNC   ___iar_data_init2, LP, R1
            MOV         SFE(`Region$$Table1`),r7
            MOV         SFB(`Region$$Table1`),r6
            CALL_FUNC   ___iar_data_init2, LP, R1
            BR ?no_seg_init
?data_init_PE2:
        MOV         SFE(`Region$$TableS`),r7
        MOV         SFB(`Region$$TableS`),r6
        CALL_FUNC   ___iar_data_init2, LP, R1
            MOV         SFE(`Region$$Table2`),r7
            MOV         SFB(`Region$$Table2`),r6
            CALL_FUNC   ___iar_data_init2, LP, R1


;---------------------------------------------------------------;
; Destination label when skipping data initialization.          ;
;---------------------------------------------------------------;

?no_seg_init:

;---------------------------------------------------------------;
; Module start.                                                 ;
;---------------------------------------------------------------;

#if 0
            EXTERN      _vector_table
            PUBLIC      ?INIT_PIC

;---------------------------------------------------------------;
; Calculate code distance (PIC only).                           ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

?INIT_PIC:
            RTMODEL     "__code_model", "pic"
            JARL        ref_point, R7
ref_point:  MOV         ref_point, R8
            SUB         R8, R7
            ;; Expands to correct store instruction/sequence.
            STORE_M     R7, ?CODE_DISTANCE, R8
            ;; Note: R7 (the value of ?CODE_DISTANCE) is used below!

;---------------------------------------------------------------;
; The distance the code has been moved when using position      ;
; independent code.                                             ;
;---------------------------------------------------------------;

            SECTION     LIBRARY_N:DATA:NOROOT(2)

?CODE_DISTANCE:
            REQUIRE     ?INIT_PIC
            RTMODEL     "__code_model", "pic"
            DS          4
#endif

            EXTERN      ?CODE_DISTANCE
            PUBLIC      ?cstart_call_main
            PUBLIC      ___iar_init_callt
            PUBLIC      ___iar_init_syscall
            PUBLIC      ___iar_init_interrupt
            PUBLIC      ___iar_init_hvcall
            PUBLIC      ?cstart_call_ctors
            PUBLIC      __iar_cstart_call_ctors
            PUBLIC      ?BTT_cstart_end
            PUBLIC      __exit
            PUBLIC      ?BTT_exit_begin
            PUBLIC      ___cstart_call_dtors
            PUBLIC      ___cstart_closeall
            PUBLIC      ?BTT_exit_end

;---------------------------------------------------------------;
; Initialize the CALLT base pointers.                           ;
;---------------------------------------------------------------;

            SECTION     .table.callt:CONST
            SECTION     .text:CODE:NOROOT(1)


            ;; The Call table base pointer
___iar_init_callt:
            EXTERN      _callt_vector_table
            REQUIRE     _callt_vector_table
            
            MOV         SFB .table.callt, R8
#if __CODE_MODEL__ == __CODE_MODEL_PIC__
            REQUIRE     ?CODE_DISTANCE

            ;; Add the value of ?CODE_DISTANCE calculated above
            ADD         R7, R8
#endif
            LDSR        R8, 20          ; CTBP

;---------------------------------------------------------------;
; Initialize the SYSCALL base pointers.                         ;
;---------------------------------------------------------------;

            SECTION     `.table.syscall`:CONST
            SECTION     .text:CODE:NOROOT(1)

            ;; The syscall table base pointer
___iar_init_syscall:
            EXTERN      _syscall_vector_table
            REQUIRE     _syscall_vector_table
            
            MOV         SFB .table.syscall, R8
#if __CODE_MODEL__ == __CODE_MODEL_PIC__
            REQUIRE     ?CODE_DISTANCE

            ;; Add the value of ?CODE_DISTANCE calculated above
            ADD         R7, R8
#endif
            LDSR        R8,12,1          ; SCBP

            MOV         (SIZEOF .table.syscall) - 4, R8
            SHR         2, R8
            LDSR        R8,11,1          ; SCCFG

;---------------------------------------------------------------;
; Initialize the HVCALL base pointers.                          ;
;---------------------------------------------------------------;

            SECTION     `.table.hvcall`:CONST
            SECTION     .text:CODE:NOROOT(1)

            ;; The syscall table base pointer
___iar_init_hvcall:
            EXTERN      _hvcall_vector_table
            REQUIRE     _hvcall_vector_table
            
            MOV         SFB .table.hvcall, R8
#if __CODE_MODEL__ == __CODE_MODEL_PIC__
            REQUIRE     ?CODE_DISTANCE

            ;; Add the value of ?CODE_DISTANCE calculated above
            ADD         R7, R8
#endif
            LDSR        R8,14,1          ; HVCBP

            MOV         (SIZEOF .table.hvcall) - 4, R8
            SHR         2, R8
            LDSR        R8,13,1          ; HVCCFG.SIZE

;---------------------------------------------------------------;
; Initialize the INTBP base pointer.                            ;
;---------------------------------------------------------------;

            SECTION     `.table.interrupt_core_1`:CONST
            SECTION     `.table.interrupt_core_2`:CONST
            SECTION     .text:CODE:NOROOT(1)

            ;; The syscall table base pointer
___iar_init_interrupt:
            EXTERN      _interrupt_vector_table_core_1
            REQUIRE     _interrupt_vector_table_core_1

            CMP         1, R20
            BNZ         ?int_PE1
            MOV         _interrupt_vector_table_core_1, R8
?int_PE1:
            EXTERN      _interrupt_vector_table_core_2
            REQUIRE     _interrupt_vector_table_core_2

            CMP         2, R20
            BNZ         ?int_PE2
            MOV         _interrupt_vector_table_core_2, R8
?int_PE2:

            
#if __CODE_MODEL__ == __CODE_MODEL_PIC__
            REQUIRE     ?CODE_DISTANCE

            ;; Add the value of ?CODE_DISTANCE calculated above
            ADD         R7, R8
#endif
            LDSR        R8,4,1            ; INTBP


;---------------------------------------------------------------;
; Check if wait (PE2+) or continue (PE1).                       ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
            
            PUBLIC      ?CHECK_PE

;---------------------------------------------------------------;
; Check if PE1.                                                 ;
;---------------------------------------------------------------;
            
?CHECK_PE   CMP         1, R20
            BZ          ?continue_init
  
;---------------------------------------------------------------;
; All, but PE1, waits here for PE1 to finalize init.            ;
;---------------------------------------------------------------;
            
?wait_init_done:
            MOV         PFSSG0MEV0, R7                  ; check semaphore
            LD.W        0[R7], R8
            CMP         1, R8
            BE          ?init_done_PE1
            SNOOZE
            BR          ?wait_init_done
  
?continue_init:

;---------------------------------------------------------------;
; Only PE1 do all the rest.                                     ;
;---------------------------------------------------------------;

;---------------------------------------------------------------;
; This segment part is required by the compiler when it is      ;
; necessary to call constructors of global objects.             ;
;---------------------------------------------------------------;

            SECTION     SHT$$PREINIT_ARRAY:CONST:NOROOT(2)
            SECTION     SHT$$INIT_ARRAY:CONST:NOROOT(2)
            SECTION     .text:CODE:NOROOT(1)

            EXTERN      ___call_ctors

?cstart_call_ctors:
__iar_cstart_call_ctors:
            MOV         SFB SHT$$PREINIT_ARRAY, R6
            MOV         SFE SHT$$INIT_ARRAY, R7

            CALL_FUNC   ___call_ctors, LP, R8

;---------------------------------------------------------------;
; Call C main() with no parameters.                             ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

            EXTERN      _main
            EXTERN      _exit
            REQUIRE     __cstart_data_init

?cstart_call_main:
;---------------------------------------------------------------;
; PE1 init has finished.                                        ;
;---------------------------------------------------------------;

            MOV         1, R8
            MOV         PFSSG0MEV0, R7                  ; releae PE1 semaphore
            ST.W        R8, 0[R7]           
?init_done_PE1:


            CALL_FUNC   _main, LP, R6

;---------------------------------------------------------------;
; If we come here we have returned from main with a 'return'    ;
; statement, not with a call to exit() or abort().              ;
; In this case we must call exit() here for a nice ending.      ;
; Note: The return value of main() is the argument to exit().   ;
;---------------------------------------------------------------;

            MOV         R10, R6
            CALL_FUNC   _exit, LP, R7

;---------------------------------------------------------------;
; We should never come here, but just in case.                  ;
;---------------------------------------------------------------;

            MOV         ___exit, LP
            JMP         [LP]

?BTT_cstart_end:

;---------------------------------------------------------------;
; _exit code                                                    ;
;                                                               ;
; Call destructors (if required), then fall through to __exit.  ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)

?BTT_exit_begin:
__exit:
            REQUIRE     ?exit_restore2
            
;---------------------------------------------------------------;
; If any of the two pieces of code "__cstart_call_dtors"        ;
; or "__cstart_closeall" is called we need to save the          ;
; argument to "_exit".  However, since we never will            ;
; from this function we can use a permanent register            ;
; rather than storing the value on the stack.                   ;
;---------------------------------------------------------------;

            SECTION     .text:CODE:NOROOT(1)
?exit_save:
            REQUIRE     ?exit_restore

            MOV         R10, R29

            SECTION     .text:CODE:NOROOT(1)
            
            EXTERN      ___call_dtors
            REQUIRE     ?exit_save

            ;; This label is required by "__record_needed_destruction".

___cstart_call_dtors:
            CALL_FUNC   ___call_dtors, LP, R1


            ;; A new module is needed so that a non-terminal-IO program
            ;; doesn't include this, which requires __putchar.

            SECTION     .text:CODE:NOROOT(1)

            ;; When stdio is used, the following piece of code is
            ;; required by the _Closreg macro.

            REQUIRE     ?exit_save

            ;; This label is required by _Closreg

___cstart_closeall:
            EXTERN      __Close_all
            CALL_FUNC   __Close_all, LP, R1

            SECTION     .text:CODE:NOROOT(1)
            
            PUBLIC      ___cstart_clearlocks
            EXTERN      ___iar_clearlocks

            REQUIRE     ?exit_save

___cstart_clearlocks:
            CALL_FUNC   ___iar_clearlocks, LP, R1

            ;; Restore the argument previously stored by the "save" section
            ;; above.

            SECTION     .text:CODE:NOROOT(1)

?exit_restore:
            REQUIRE     ?exit_restore2
            MOV         R29, R10

            SECTION     .text:CODE:NOROOT(1)

            EXTERN      ___exit
?exit_restore2:
            MOV         R10, R6
            MOV         ___exit, LP
            JMP         [LP]

?BTT_exit_end:

            END

;-----------------------------------------------------------------------------
