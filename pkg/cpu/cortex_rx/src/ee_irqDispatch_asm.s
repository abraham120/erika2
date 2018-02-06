;-------------------------------------------------------------------------------
; irqDispatch_a.asm
;
; (c) Texas Instruments 2009-2012, All rights reserved.
;

      ; Export Symbols
      .def _irqDispatch
      
      ; Import Symbols
      .ref C_irqDispatch

      ; Start
      .text
      
      
      ; Function: _irqDispatch
      .align 4
      .armfunc _irqDispatch
      .arm
      
      ; Note: This implementation is limited to the use of the first 96 interrupt priority's.
      ; Note: This implementation is for ARMv7-R (Cortex-R4) in ARM mode.

_irqDispatch: .asmfunc
      ; TI ASM Step 1:
      SUB      LR, LR, #4              ; construct the return address
      SRSDB    #31!                    ; Save LR_irq and SPSR_irq to System mode stack
      ; TI ASM Step 2:
      CPS      #31                     ; Switch to System mode
      ; TI ASM Step 3:
      PUSH     {R0-R3, R12}            ; Store AAPCS registers

   .if __TI_VFPV3D16_SUPPORT__ = 1     ; If VFPV3D16 is used
      FMRX      R12, FPSCR
      STMFD     SP!, {R12}
      FMRX      R12, FPEXC
      STMFD     SP!, {R12}
      FSTMDBD   SP!, {D0-D7}
   .endif
      
      ; TI ASM Step 5
      ; Align stack to a 64 Bit boundary
      AND      R3, SP, #4              ; Calculate Stack adjustment to 64bit boundary
      SUB      SP, SP, R3              ; Adjust System Stack
      PUSH     {R3, LR}                ; Put Stack adjustment and System Mode LR on Stack

      ; TI ASM Step 6
      BL       C_irqDispatch           ; Call Second Level IRQ Dispatcher C routine
      
      ; TI ASM Step 7
      ; Undo stack alignment
      POP      {R3, LR}                ; Get Stack adjustment and System Mode LR from Stack
      ADD      SP, SP, R3              ; Undo System Stack adjustment
      
      ; TI ASM Step 9
   .if __TI_VFPV3D16_SUPPORT__ = 1     ; If VFPV3D16 is used
      FLDMIAD   SP!, {D0-D7}
      LDMFD     SP!, {R12}
      FMXR      FPEXC, R12
      LDMFD     SP!, {R12}
      FMXR      FPSCR, R12
   .endif

      POP      {R0-R3, R12}            ; Restore AAPCS registers
      
      ; TI ASM Step 10
      RFEIA    SP!                     ; Return using RFE from System mode stack
      .endasmfunc
      
      .end
;-------------------------------------------------------------------------------
