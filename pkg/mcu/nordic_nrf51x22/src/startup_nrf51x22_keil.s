; Copyright (c) 2009 Nordic Semiconductor. All Rights Reserved.
; The information contained herein is confidential property of Nordic
; Semiconductor ASA.Terms and conditions of usage are described in detail
; in NORDIC SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
; Licensees are granted free, non-transferable use of the information. NO
; WARRANTY of ANY KIND is provided. This heading must NOT be removed from
; the file.

; Description message

; /** 
; 	@file startup_nrf51x22.s
; 	@brief Startup code for NRF51x22 under Keil, adapted for ERIKA Enterprise.
; 	@author Alessandro Biondi
; 	@date 2013
; */

;******************************************************************************

#include "eecfg.h"	/* Configurable by RT-Druid */

;******************************************************************************
;
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
#ifndef	EE_SYS_STACK_SIZE
#define	EE_SYS_STACK_SIZE	0x00000800	/* 2K bytes */
#endif

Stack_Size	EQU	EE_SYS_STACK_SIZE
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

;******************************************************************************
;
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
#ifndef	EE_SYS_HEAP_SIZE
#define	EE_SYS_HEAP_SIZE	0x00000800	/* 2K bytes */
#endif

Heap_Size	EQU	EE_SYS_HEAP_SIZE
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB
; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY

;******************************************************************************
;
; 			Extern declarations of the interrupt handlers.
;
;******************************************************************************
				
#ifdef	EE_CORTEX_MX_RESET_ISR				/* Reset Handler */
	IMPORT	EE_CORTEX_MX_RESET_ISR
#endif
#ifdef EE_CORTEX_MX_NMI_ISR					/* The NMI handler */
	IMPORT	EE_CORTEX_MX_NMI_ISR
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR			/* The hard fault handler */
	IMPORT	EE_CORTEX_MX_HARD_FAULT_ISR
#endif

	IMPORT	SVC_Handler			/* SVCall Handler */
	IMPORT	PendSV_Handler			/* PendSV Handler */
	
#ifdef	EE_CORTEX_MX_SYSTICK_ISR			/* SysTick Handler */
	IMPORT	EE_CORTEX_MX_SYSTICK_ISR
#endif
#ifdef EE_CORTEX_MX_NRF51X22_POWER_CLOCK_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_POWER_CLOCK_ISR ;POWER_CLOCK
#endif
#ifdef EE_CORTEX_MX_NRF51X22_RADIO_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_RADIO_ISR ;RADIO
#endif
#ifdef EE_CORTEX_MX_NRF51X22_UART0_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_UART0_ISR ;UART0
#endif
#ifdef EE_CORTEX_MX_NRF51X22_SPI0_TWI0_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SPI0_TWI0_ISR ;SPI0_TWI0
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_SPI1_TWI1_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SPI1_TWI1_ISR ;SPI1_TWI1
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_GPIOTE_ISR				
    IMPORT EE_CORTEX_MX_NRF51X22_GPIOTE_ISR ;GPIOTE
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_ADC_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_ADC_ISR ;ADC
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_TIMER0_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_TIMER0_ISR ;TIMER0
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_TIMER1_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_TIMER1_ISR ;TIMER1
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_TIMER2_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_TIMER2_ISR ;TIMER2
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_RTC0_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_RTC0_ISR ;RTC0
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_TEMP_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_TEMP_ISR ;TEMP
#endif						
#ifdef EE_CORTEX_MX_NRF51X22_RNG_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_RNG_ISR ;RNG
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_ECB_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_ECB_ISR ;ECB
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_CCM_AAR_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_CCM_AAR_ISR ;CCM_AAR
#endif	
#ifdef EE_CORTEX_MX_NRF51X22_WDT_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_WDT_ISR ;WDT
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_RTC1_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_RTC1_ISR ;RTC1
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_QDEC_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_QDEC_ISR ;QDEC
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_WUCOMP_COMP_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_WUCOMP_COMP_ISR ;WUCOMP_COMP
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI0_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SWI0_ISR ;SWI0
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI1_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SWI1_ISR ;SWI1
#endif							
#ifdef EE_CORTEX_MX_NRF51X22_SWI2_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SWI2_ISR ;SWI2
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI3_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SWI3_ISR ;SWI3
#endif							
#ifdef EE_CORTEX_MX_NRF51X22_SWI4_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SWI4_ISR ;SWI4
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI5_ISR
    IMPORT EE_CORTEX_MX_NRF51X22_SWI5_ISR ;SWI5
#endif					


;******************************************************************************
;******************         V E C T O R  T A B L E         ********************
;******************************************************************************

				
	EXPORT	EE_cortex_mx_vtable

EE_cortex_mx_vtable     
          
	DCD     __initial_sp              		/* Top of Stack */
#ifdef	EE_CORTEX_MX_RESET_ISR				/* Reset Handler */
	DCD	EE_CORTEX_MX_RESET_ISR
#else
	DCD	EE_cortex_mx_default_reset_ISR
#endif 
#ifdef EE_CORTEX_MX_NMI_ISR					/* The NMI handler */
	DCD	EE_CORTEX_MX_NMI_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR			/* The hard fault handler */
	DCD	EE_CORTEX_MX_HARD_FAULT_ISR
#else
#ifdef	__AUTOSAR_R4_0__
	DCD	EE_cortex_mx_as_hard_fault_ISR
#else	/* __AUTOSAR_R4_0__ */
	DCD	EE_cortex_mx_default_ISR
#endif	/* !__AUTOSAR_R4_0__ */
#endif
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     SVC_Handler      ; SVCall Handler 
    DCD     0                         ; Reserved
    DCD     0                         ; Reserved
    DCD     PendSV_Handler   ;PendSV Handler 
#ifdef	EE_CORTEX_MX_SYSTICK_ISR	 
	DCD	EE_CORTEX_MX_SYSTICK_ISR		
#else
	DCD	EE_cortex_mx_default_ISR
#endif

;----------------- External Interrupts --------------------------
	
	
#ifdef EE_CORTEX_MX_NRF51X22_POWER_CLOCK_ISR
    DCD      EE_CORTEX_MX_NRF51X22_POWER_CLOCK_ISR ;POWER_CLOCK
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_NRF51X22_RADIO_ISR
    DCD      EE_CORTEX_MX_NRF51X22_RADIO_ISR ;RADIO
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_NRF51X22_UART0_ISR
    DCD      EE_CORTEX_MX_NRF51X22_UART0_ISR ;UART0
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_NRF51X22_SPI0_TWI0_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SPI0_TWI0_ISR ;SPI0_TWI0
#else
	DCD	EE_cortex_mx_default_ISR
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_SPI1_TWI1_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SPI1_TWI1_ISR ;SPI1_TWI1
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
    DCD      0 ;Reserved
#ifdef EE_CORTEX_MX_NRF51X22_GPIOTE_ISR				
    DCD      EE_CORTEX_MX_NRF51X22_GPIOTE_ISR ;GPIOTE
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_ADC_ISR
    DCD      EE_CORTEX_MX_NRF51X22_ADC_ISR ;ADC
#else
	DCD	EE_cortex_mx_default_ISR
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_TIMER0_ISR
    DCD      EE_CORTEX_MX_NRF51X22_TIMER0_ISR ;TIMER0
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_TIMER1_ISR
    DCD      EE_CORTEX_MX_NRF51X22_TIMER1_ISR ;TIMER1
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_TIMER2_ISR
    DCD      EE_CORTEX_MX_NRF51X22_TIMER2_ISR ;TIMER2
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_RTC0_ISR
    DCD      EE_CORTEX_MX_NRF51X22_RTC0_ISR ;RTC0
#else
	DCD	EE_cortex_mx_default_ISR
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_TEMP_ISR
    DCD      EE_CORTEX_MX_NRF51X22_TEMP_ISR ;TEMP
#else
	DCD	EE_cortex_mx_default_ISR
#endif						
#ifdef EE_CORTEX_MX_NRF51X22_RNG_ISR
    DCD      EE_CORTEX_MX_NRF51X22_RNG_ISR ;RNG
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_ECB_ISR
    DCD      EE_CORTEX_MX_NRF51X22_ECB_ISR ;ECB
#else
	DCD	EE_cortex_mx_default_ISR
#endif				
#ifdef EE_CORTEX_MX_NRF51X22_CCM_AAR_ISR
    DCD      EE_CORTEX_MX_NRF51X22_CCM_AAR_ISR ;CCM_AAR
#else
	DCD	EE_cortex_mx_default_ISR
#endif	
#ifdef EE_CORTEX_MX_NRF51X22_WDT_ISR
    DCD      EE_CORTEX_MX_NRF51X22_WDT_ISR ;WDT
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_RTC1_ISR
    DCD      EE_CORTEX_MX_NRF51X22_RTC1_ISR ;RTC1
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_QDEC_ISR
    DCD      EE_CORTEX_MX_NRF51X22_QDEC_ISR ;QDEC
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_WUCOMP_COMP_ISR
    DCD      EE_CORTEX_MX_NRF51X22_WUCOMP_COMP_ISR ;WUCOMP_COMP
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI0_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SWI0_ISR ;SWI0
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI1_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SWI1_ISR ;SWI1
#else
	DCD	EE_cortex_mx_default_ISR
#endif							
#ifdef EE_CORTEX_MX_NRF51X22_SWI2_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SWI2_ISR ;SWI2
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI3_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SWI3_ISR ;SWI3
#else
	DCD	EE_cortex_mx_default_ISR
#endif							
#ifdef EE_CORTEX_MX_NRF51X22_SWI4_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SWI4_ISR ;SWI4
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
#ifdef EE_CORTEX_MX_NRF51X22_SWI5_ISR
    DCD      EE_CORTEX_MX_NRF51X22_SWI5_ISR ;SWI5
#else
	DCD	EE_cortex_mx_default_ISR
#endif					
    DCD      0 ;Reserved
    DCD      0 ;Reserved
    DCD      0 ;Reserved
    DCD      0 ;Reserved
    DCD      0 ;Reserved
    DCD      0 ;Reserved


;__Vectors_End

;__Vectors_Size  EQU     __Vectors_End - __Vectors

;******************************************************************************
;******************************************************************************

    AREA    |.text|, CODE, READONLY

; Reset Handler

NRF_POWER_RAMON_ADDRESS           EQU   0x40000524  ; NRF_POWER->RAMON address
NRF_POWER_RAMON_RAMxON_ONMODE_Msk EQU   0xF         ; All RAM blocks on in onmode bit mask

EE_cortex_mx_default_reset_ISR   PROC
                EXPORT  EE_cortex_mx_default_reset_ISR             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =NRF_POWER_RAMON_ADDRESS
                LDR     R2, [R0]
                MOVS    R1, #NRF_POWER_RAMON_RAMxON_ONMODE_Msk
                ORRS    R2, R2, R1
                STR     R2, [R0]
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

;******************************************************************************
;
; This is the code that gets called when the processor receives a HARD FAULT
; exception.
;
;******************************************************************************
#ifdef	__AUTOSAR_R4_0__
EE_cortex_mx_as_hard_fault_ISR
#ifdef	DEBUG
	BKPT	#0x00
#endif	/* DEBUG */
	B	EE_cortex_mx_as_hard_fault_ISR
#endif	/* __AUTOSAR_R4_0__ */

;******************************************************************************
;
; This is the code that gets called when the processor receives an unexpected
; interrupt.  This simply enters an infinite loop, preserving the system state
; for examination by a debugger.
;
;******************************************************************************
EE_cortex_mx_default_ISR
#ifdef	DEBUG
	BKPT	#0x00
#endif	/* DEBUG */
	B	EE_cortex_mx_default_ISR

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, = Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem + Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END

