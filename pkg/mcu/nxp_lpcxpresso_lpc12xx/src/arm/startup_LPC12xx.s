;/*****************************************************************************
; * @file:    startup_LPC12xx.s
; * @purpose: CMSIS Cortex-M0 Core Device Startup File 
; *           for the NXP LPC12xx Device Series 
; * @version: V1.0
; * @date:    25. Nov. 2008
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; * Copyright (C) 2008 ARM Limited. All rights reserved.
; * ARM Limited (ARM) is supplying this software for use with Cortex-M0 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; *****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WAKEUP_IRQHandler         ; 16+ 0: Wakeup PIO0.0
                DCD     WAKEUP_IRQHandler         ; 16+ 1: Wakeup PIO0.1
                DCD     WAKEUP_IRQHandler         ; 16+ 2: Wakeup PIO0.2
                DCD     WAKEUP_IRQHandler         ; 16+ 3: Wakeup PIO0.3
                DCD     WAKEUP_IRQHandler         ; 16+ 4: Wakeup PIO0.4
                DCD     WAKEUP_IRQHandler         ; 16+ 5: Wakeup PIO0.5
                DCD     WAKEUP_IRQHandler         ; 16+ 6: Wakeup PIO0.6
                DCD     WAKEUP_IRQHandler         ; 16+ 7: Wakeup PIO0.7
                DCD     WAKEUP_IRQHandler         ; 16+ 8: Wakeup PIO0.8
                DCD     WAKEUP_IRQHandler         ; 16+ 9: Wakeup PIO0.9
                DCD     WAKEUP_IRQHandler         ; 16+10: Wakeup PIO0.10
                DCD     WAKEUP_IRQHandler         ; 16+11: Wakeup PIO0.11
                DCD     I2C_IRQHandler            ; 16+12: I2C
                DCD     TIMER16_0_IRQHandler      ; 16+13: 16-bit Timer0
                DCD     TIMER16_1_IRQHandler      ; 16+14: 16-bit Timer1
                DCD     TIMER32_0_IRQHandler      ; 16+15: 32-bit Timer0
                DCD     TIMER32_1_IRQHandler      ; 16+16: 32-bit Timer1
                DCD     SSP_IRQHandler            ; 16+17: SSP
                DCD     UART0_IRQHandler          ; 16+18: UART0                
                DCD     UART1_IRQHandler          ; 16+19: UART1
                DCD     COMP_IRQHandler           ; 16+20: Comparator                
                DCD     ADC_IRQHandler            ; 16+21: A/D Converter
                DCD     WDT_IRQHandler            ; 16+22: Watchdog timer                
                DCD     BOD_IRQHandler            ; 16+23: Brown Out Detect
				DCD		0						  ; reserved
                DCD     PIOINT0_IRQHandler        ; 16+25: PIO INT0
                DCD     PIOINT1_IRQHandler        ; 16+26: PIO INT1
                DCD     PIOINT2_IRQHandler        ; 16+27: PIO INT2
				DCD		0						  ; reserved
                DCD     DMA_IRQHandler            ; 16+29: DMA
                DCD     RTC_IRQHandler            ; 16+30: RTC                                                                                                                 

                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
#ifdef __EE_DEF_SYS_INIT__				
                LDR     R0, =SystemInit		
                BLX     R0
#endif						
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)                

; now, under COMMON NMI.c and NMI.h, a real NMI handler is created if NMI is enabled 
; for particular peripheral.
;NMI_Handler     PROC
;                EXPORT  NMI_Handler               [WEAK]
;                B       .
;                ENDP                
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP				
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  NMI_Handler               [WEAK]
                EXPORT  WAKEUP_IRQHandler         [WEAK]
                EXPORT  I2C_IRQHandler            [WEAK]
                EXPORT  TIMER16_0_IRQHandler      [WEAK]
                EXPORT  TIMER16_1_IRQHandler      [WEAK]
                EXPORT  TIMER32_0_IRQHandler      [WEAK]
                EXPORT  TIMER32_1_IRQHandler      [WEAK]
                EXPORT  SSP_IRQHandler            [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]

                EXPORT  COMP_IRQHandler           [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT	PIOINT0_IRQHandler        [WEAK]
                EXPORT	PIOINT1_IRQHandler        [WEAK]
                EXPORT  PIOINT2_IRQHandler        [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]

NMI_Handler
WAKEUP_IRQHandler
I2C_IRQHandler
TIMER16_0_IRQHandler
TIMER16_1_IRQHandler
TIMER32_0_IRQHandler
TIMER32_1_IRQHandler
SSP_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
COMP_IRQHandler
ADC_IRQHandler
WDT_IRQHandler
BOD_IRQHandler
PIOINT0_IRQHandler  
PIOINT1_IRQHandler 
PIOINT2_IRQHandler
DMA_IRQHandler
RTC_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
