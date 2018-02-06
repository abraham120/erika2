; ###*B*###
; ERIKA Enterprise - a tiny RTOS for small microcontrollers
;
; Copyright (C) 2002-2011  Evidence Srl
;
; This file is part of ERIKA Enterprise.
;
; ERIKA Enterprise is free software; you can redistribute it
; and/or modify it under the terms of the GNU General Public License
; version 2 as published by the Free Software Foundation, 
; (with a special exception described below).
;
; Linking this code statically or dynamically with other modules is
; making a combined work based on this code.  Thus, the terms and
; conditions of the GNU General Public License cover the whole
; combination.
;
; As a special exception, the copyright holders of this library give you
; permission to link this code with independent modules to produce an
; executable, regardless of the license terms of these independent
; modules, and to copy and distribute the resulting executable under
; terms of your choice, provided that you also meet, for each linked
; independent module, the terms and conditions of the license of that
; module.  An independent module is a module which is not derived from
; or based on this library.  If you modify this code, you may extend
; this exception to your version of the code, but you are not
; obligated to do so.  If you do not wish to do so, delete this
; exception statement from your version.
;
; ERIKA Enterprise is distributed in the hope that it will be
; useful, but WITHOUT ANY WARRANTY; without even the implied warranty
; of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License version 2 for more details.
;
; You should have received a copy of the GNU General Public License
; version 2 along with ERIKA Enterprise; if not, write to the
; Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
; Boston, MA 02110-1301 USA.
; ###*E*###
;
; /** 
; 	@file startup_stm32f4xx.s
; 	@brief Startup code for Keil uVision MDK-Lite.
; 	@author Carlo Caione
; 	@date 2012
; */
;
;******************************************************************************
#include "eecfg.h"	/* Configurable by RT-Druid */

;******************************************************************************
;
; <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
#ifndef	EE_SYS_STACK_SIZE
#define	EE_SYS_STACK_SIZE	0x00000400	/* 1K bytes */
#endif
Stack	EQU	EE_SYS_STACK_SIZE

;******************************************************************************
;
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;
;******************************************************************************
#ifndef	EE_SYS_HEAP_SIZE
#define	EE_SYS_HEAP_SIZE	0x00000400	/* 1K bytes */
#endif
Heap	EQU	EE_SYS_HEAP_SIZE

;******************************************************************************
;
; Allocate space for the stack.
;
;******************************************************************************
	AREA	STACK,	NOINIT,	READWRITE,	ALIGN=3
StackMem
	SPACE	Stack
__initial_sp
	EXPORT	__initial_sp

;******************************************************************************
;
; Allocate space for the heap.
;
;******************************************************************************
	AREA	HEAP,	NOINIT,	READWRITE,	ALIGN=3
__heap_base
HeapMem
	SPACE	Heap
__heap_limit

;******************************************************************************
;
; Indicate that the code in this file preserves 8-byte alignment of the stack.
;
;******************************************************************************
	PRESERVE8                

;******************************************************************************
;
; Place code into the reset code section.
;
;******************************************************************************
	AREA	RESET,	CODE,	READONLY
	THUMB

;******************************************************************************
;
; The vector table.
;
;******************************************************************************

/*
 * Extern declarations of the interrupt handlers.
 */
#ifdef	EE_CORTEX_MX_RESET_ISR				/* Reset Handler */
	IMPORT	EE_CORTEX_MX_RESET_ISR
#endif
#ifdef EE_CORTEX_MX_NMI_ISR					/* The NMI handler */
	IMPORT	EE_CORTEX_MX_NMI_ISR
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR			/* The hard fault handler */
	IMPORT	EE_CORTEX_MX_HARD_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_MPU_FAULT_ISR			/* The MPU fault handler */
	IMPORT	EE_CORTEX_MX_MPU_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_BUS_FAULT_ISR			/* The bus fault handler */
	IMPORT	EE_CORTEX_MX_BUS_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_USAGE_FAULT_ISR			/* The usage fault handler */
	IMPORT	EE_CORTEX_MX_USAGE_FAULT_ISR
#endif
	IMPORT	EE_cortex_mx_svc_ISR			/* SVCall Handler */
	IMPORT	EE_cortex_mx_pendsv_ISR			/* PendSV Handler */
#ifdef	EE_CORTEX_MX_SYSTICK_ISR			/* SysTick Handler */
	IMPORT	EE_CORTEX_MX_SYSTICK_ISR
#endif
#ifdef EE_CORTEX_MX_DEBUG_MONITOR_ISR		/* Debug monitor handler */
	IMPORT	EE_CORTEX_MX_DEBUG_MONITOR_ISR
#endif
#ifdef EE_CORTEX_MX_WWDG_ISR
	IMPORT  EE_CORTEX_MX_WWDG_ISR
#endif
#ifdef EE_CORTEX_MX_PVD_ISR
	IMPORT  EE_CORTEX_MX_PVD_ISR
#endif
#ifdef EE_CORTEX_MX_TAMP_STAMP_ISR
	IMPORT  EE_CORTEX_MX_TAMP_STAMP_ISR
#endif
#ifdef EE_CORTEX_MX_RTC_WKUP_ISR
	IMPORT  EE_CORTEX_MX_RTC_WKUP_ISR
#endif
#ifdef EE_CORTEX_MX_FLASH_ISR
	IMPORT  EE_CORTEX_MX_FLASH_ISR
#endif
#ifdef EE_CORTEX_MX_RCC_ISR
	IMPORT  EE_CORTEX_MX_RCC_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI0_ISR
	IMPORT  EE_CORTEX_MX_EXTI0_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI1_ISR
	IMPORT  EE_CORTEX_MX_EXTI1_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI2_ISR
	IMPORT  EE_CORTEX_MX_EXTI2_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI3_ISR
	IMPORT  EE_CORTEX_MX_EXTI3_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI4_ISR
	IMPORT  EE_CORTEX_MX_EXTI4_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM0_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM0_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM1_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM1_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM2_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM2_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM3_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM3_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM4_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM4_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM5_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM5_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM6_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM6_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_ISR
	IMPORT  EE_CORTEX_MX_ADC_ISR
#endif
#ifdef EE_CORTEX_MX_CAN1_TX_ISR
	IMPORT  EE_CORTEX_MX_CAN1_TX_ISR
#endif
#ifdef EE_CORTEX_MX_CAN1_RX0_ISR
	IMPORT  EE_CORTEX_MX_CAN1_RX0_ISR
#endif
#ifdef EE_CORTEX_MX_CAN1_RX1_ISR
	IMPORT  EE_CORTEX_MX_CAN1_RX1_ISR
#endif
#ifdef EE_CORTEX_MX_CAN1_SCE_ISR
	IMPORT  EE_CORTEX_MX_CAN1_SCE_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI9_5_ISR
	IMPORT  EE_CORTEX_MX_EXTI9_5_ISR
#endif
#ifdef EE_CORTEX_MX_TIM1_BRK_TIM9_ISR
	IMPORT  EE_CORTEX_MX_TIM1_BRK_TIM9_ISR
#endif
#ifdef EE_CORTEX_MX_TIM1_UP_TIM10_ISR
	IMPORT  EE_CORTEX_MX_TIM1_UP_TIM10_ISR
#endif
#ifdef EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR
	IMPORT  EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR
#endif
#ifdef EE_CORTEX_MX_TIM1_CC_ISR
	IMPORT  EE_CORTEX_MX_TIM1_CC_ISR
#endif
#ifdef EE_CORTEX_MX_TIM2_ISR
	IMPORT  EE_CORTEX_MX_TIM2_ISR
#endif
#ifdef EE_CORTEX_MX_TIM3_ISR
	IMPORT  EE_CORTEX_MX_TIM3_ISR
#endif
#ifdef EE_CORTEX_MX_TIM4_ISR
	IMPORT  EE_CORTEX_MX_TIM4_ISR
#endif
#ifdef EE_CORTEX_MX_I2C1_EV_ISR
	IMPORT  EE_CORTEX_MX_I2C1_EV_ISR
#endif
#ifdef EE_CORTEX_MX_I2C1_ER_ISR
	IMPORT  EE_CORTEX_MX_I2C1_ER_ISR
#endif
#ifdef EE_CORTEX_MX_I2C2_EV_ISR
	IMPORT  EE_CORTEX_MX_I2C2_EV_ISR
#endif
#ifdef EE_CORTEX_MX_I2C2_ER_ISR
	IMPORT  EE_CORTEX_MX_I2C2_ER_ISR
#endif
#ifdef EE_CORTEX_MX_SPI1_ISR
	IMPORT  EE_CORTEX_MX_SPI1_ISR
#endif
#ifdef EE_CORTEX_MX_SPI2_ISR
	IMPORT  EE_CORTEX_MX_SPI2_ISR
#endif
#ifdef EE_CORTEX_MX_USART1_ISR
	IMPORT  EE_CORTEX_MX_USART1_ISR
#endif
#ifdef EE_CORTEX_MX_USART2_ISR
	IMPORT  EE_CORTEX_MX_USART2_ISR
#endif
#ifdef EE_CORTEX_MX_USART3_ISR
	IMPORT  EE_CORTEX_MX_USART3_ISR
#endif
#ifdef EE_CORTEX_MX_EXTI15_10_ISR
	IMPORT  EE_CORTEX_MX_EXTI15_10_ISR
#endif
#ifdef EE_CORTEX_MX_RTC_ALARM_ISR
	IMPORT  EE_CORTEX_MX_RTC_ALARM_ISR
#endif
#ifdef EE_CORTEX_MX_OTG_FS_WKUP_ISR
	IMPORT  EE_CORTEX_MX_OTG_FS_WKUP_ISR
#endif
#ifdef EE_CORTEX_MX_TIM8_BRK_TIM12_ISR
	IMPORT  EE_CORTEX_MX_TIM8_BRK_TIM12_ISR
#endif
#ifdef EE_CORTEX_MX_TIM8_UP_TIM13_ISR
	IMPORT  EE_CORTEX_MX_TIM8_UP_TIM13_ISR
#endif
#ifdef EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR
	IMPORT  EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR
#endif
#ifdef EE_CORTEX_MX_TIM8_CC_ISR
	IMPORT  EE_CORTEX_MX_TIM8_CC_ISR
#endif
#ifdef EE_CORTEX_MX_DMA1_STREAM7_ISR
	IMPORT  EE_CORTEX_MX_DMA1_STREAM7_ISR
#endif
#ifdef EE_CORTEX_MX_FSMC_ISR
	IMPORT  EE_CORTEX_MX_FSMC_ISR
#endif
#ifdef EE_CORTEX_MX_SDIO_ISR
	IMPORT  EE_CORTEX_MX_SDIO_ISR
#endif
#ifdef EE_CORTEX_MX_TIM5_ISR
	IMPORT  EE_CORTEX_MX_TIM5_ISR
#endif
#ifdef EE_CORTEX_MX_SPI3_ISR
	IMPORT  EE_CORTEX_MX_SPI3_ISR
#endif
#ifdef EE_CORTEX_MX_UART4_ISR
	IMPORT  EE_CORTEX_MX_UART4_ISR
#endif
#ifdef EE_CORTEX_MX_UART5_ISR
	IMPORT  EE_CORTEX_MX_UART5_ISR
#endif
#ifdef EE_CORTEX_MX_TIM6_DAC_ISR
	IMPORT  EE_CORTEX_MX_TIM6_DAC_ISR
#endif
#ifdef EE_CORTEX_MX_TIM7_ISR
	IMPORT  EE_CORTEX_MX_TIM7_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM0_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM0_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM1_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM1_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM2_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM2_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM3_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM3_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM4_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM4_ISR
#endif
#ifdef EE_CORTEX_MX_ETH_ISR
	IMPORT  EE_CORTEX_MX_ETH_ISR
#endif
#ifdef EE_CORTEX_MX_ETH_WKUP_ISR
	IMPORT  EE_CORTEX_MX_ETH_WKUP_ISR
#endif
#ifdef EE_CORTEX_MX_CAN2_TX_ISR
	IMPORT  EE_CORTEX_MX_CAN2_TX_ISR
#endif
#ifdef EE_CORTEX_MX_CAN2_RX0_ISR
	IMPORT  EE_CORTEX_MX_CAN2_RX0_ISR
#endif
#ifdef EE_CORTEX_MX_CAN2_RX1_ISR
	IMPORT  EE_CORTEX_MX_CAN2_RX1_ISR
#endif
#ifdef EE_CORTEX_MX_CAN2_SCE_ISR
	IMPORT  EE_CORTEX_MX_CAN2_SCE_ISR
#endif
#ifdef EE_CORTEX_MX_OTG_FS_ISR
	IMPORT  EE_CORTEX_MX_OTG_FS_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM5_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM5_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM6_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM6_ISR
#endif
#ifdef EE_CORTEX_MX_DMA2_STREAM7_ISR
	IMPORT  EE_CORTEX_MX_DMA2_STREAM7_ISR
#endif
#ifdef EE_CORTEX_MX_USART6_ISR
	IMPORT  EE_CORTEX_MX_USART6_ISR
#endif
#ifdef EE_CORTEX_MX_I2C3_EV_ISR
	IMPORT  EE_CORTEX_MX_I2C3_EV_ISR
#endif
#ifdef EE_CORTEX_MX_I2C3_ER_ISR
	IMPORT  EE_CORTEX_MX_I2C3_ER_ISR
#endif
#ifdef EE_CORTEX_MX_I2C3_ER_ISR
	IMPORT  EE_CORTEX_MX_I2C3_ER_ISR
#endif
#ifdef EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR
	IMPORT  EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR
#endif
#ifdef EE_CORTEX_MX_OTG_HS_EP1_IN_ISR
	IMPORT  EE_CORTEX_MX_OTG_HS_EP1_IN_ISR
#endif
#ifdef EE_CORTEX_MX_OTG_HS_WKUP_ISR
	IMPORT  EE_CORTEX_MX_OTG_HS_WKUP_ISR
#endif
#ifdef EE_CORTEX_MX_OTG_HS_ISR
	IMPORT  EE_CORTEX_MX_OTG_HS_ISR
#endif
#ifdef EE_CORTEX_MX_DCMI_ISR
	IMPORT  EE_CORTEX_MX_DCMI_ISR
#endif
#ifdef EE_CORTEX_MX_CRYP_ISR
	IMPORT  EE_CORTEX_MX_CRYP_ISR
#endif
#ifdef EE_CORTEX_MX_HASH_RNG_ISR
	IMPORT  EE_CORTEX_MX_HASH_RNG_ISR
#endif
#ifdef EE_CORTEX_MX_FPU_ISR
	IMPORT  EE_CORTEX_MX_FPU_ISR
#endif

; Interrupt Vectors Table.
	EXPORT	EE_cortex_mx_vtable
EE_cortex_mx_vtable
	DCD	StackMem + Stack					; Top of Stack
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
#ifdef EE_CORTEX_MX_MPU_FAULT_ISR			/* The MPU fault handler */
	DCD	EE_CORTEX_MX_MPU_FAULT_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_BUS_FAULT_ISR			/* The bus fault handler */
	DCD	EE_CORTEX_MX_BUS_FAULT_ISR
#else
#ifdef	__AUTOSAR_R4_0__
	DCD	EE_cortex_mx_as_bus_fault_ISR
#else	/* __AUTOSAR_R4_0__ */
	DCD	EE_cortex_mx_default_ISR
#endif	/* !__AUTOSAR_R4_0__ */
#endif
#ifdef EE_CORTEX_MX_USAGE_FAULT_ISR			/* The usage fault handler */
	DCD	EE_CORTEX_MX_USAGE_FAULT_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
    DCD     0                          		; Reserved
    DCD     0                          		; Reserved
    DCD     0                          		; Reserved
    DCD     0                          		; Reserved
	DCD	EE_cortex_mx_svc_ISR					; SVCall Handler
#ifdef EE_CORTEX_MX_DEBUG_MONITOR_ISR		/* Debug monitor handler */
	DCD	EE_CORTEX_MX_DEBUG_MONITOR_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
    DCD     0                          		; Reserved
	DCD	EE_cortex_mx_pendsv_ISR				; PendSV Handler
#ifdef	EE_CORTEX_MX_SYSTICK_ISR			/* SysTick Handler */
	DCD	EE_CORTEX_MX_SYSTICK_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_WWDG_ISR		
	DCD	EE_CORTEX_MX_WWDG_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_PVD_ISR		
	DCD	EE_CORTEX_MX_PVD_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TAMP_STAMP_ISR		
	DCD	EE_CORTEX_MX_TAMP_STAMP_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_RTC_WKUP_ISR		
	DCD	EE_CORTEX_MX_RTC_WKUP_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_FLASH_ISR		
	DCD	EE_CORTEX_MX_FLASH_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_RCC_ISR		
	DCD	EE_CORTEX_MX_RCC_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI0_ISR		
	DCD	EE_CORTEX_MX_EXTI0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI1_ISR		
	DCD	EE_CORTEX_MX_EXTI1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI2_ISR		
	DCD	EE_CORTEX_MX_EXTI2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI3_ISR		
	DCD	EE_CORTEX_MX_EXTI3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI4_ISR		
	DCD	EE_CORTEX_MX_EXTI4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM0_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM1_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM2_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM3_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM4_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM5_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM6_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM6_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_ADC_ISR		
	DCD	EE_CORTEX_MX_ADC_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN1_TX_ISR		
	DCD	EE_CORTEX_MX_CAN1_TX_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN1_RX0_ISR		
	DCD	EE_CORTEX_MX_CAN1_RX0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN1_RX1_ISR		
	DCD	EE_CORTEX_MX_CAN1_RX1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN1_SCE_ISR		
	DCD	EE_CORTEX_MX_CAN1_SCE_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI9_5_ISR		
	DCD	EE_CORTEX_MX_EXTI9_5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM1_BRK_TIM9_ISR		
	DCD	EE_CORTEX_MX_TIM1_BRK_TIM9_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM1_UP_TIM10_ISR		
	DCD	EE_CORTEX_MX_TIM1_UP_TIM10_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR		
	DCD	EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM1_CC_ISR		
	DCD	EE_CORTEX_MX_TIM1_CC_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM2_ISR		
	DCD	EE_CORTEX_MX_TIM2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM3_ISR		
	DCD	EE_CORTEX_MX_TIM3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM4_ISR		
	DCD	EE_CORTEX_MX_TIM4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_I2C1_EV_ISR		
	DCD	EE_CORTEX_MX_I2C1_EV_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_I2C1_ER_ISR		
	DCD	EE_CORTEX_MX_I2C1_ER_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_I2C2_EV_ISR		
	DCD	EE_CORTEX_MX_I2C2_EV_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_I2C2_ER_ISR		
	DCD	EE_CORTEX_MX_I2C2_ER_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_SPI1_ISR		
	DCD	EE_CORTEX_MX_SPI1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_SPI2_ISR		
	DCD	EE_CORTEX_MX_SPI2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_USART1_ISR		
	DCD	EE_CORTEX_MX_USART1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_USART2_ISR		
	DCD	EE_CORTEX_MX_USART2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_USART3_ISR		
	DCD	EE_CORTEX_MX_USART3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_EXTI15_10_ISR		
	DCD	EE_CORTEX_MX_EXTI15_10_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_RTC_ALARM_ISR		
	DCD	EE_CORTEX_MX_RTC_ALARM_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_OTG_FS_WKUP_ISR		
	DCD	EE_CORTEX_MX_OTG_FS_WKUP_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM8_BRK_TIM12_ISR		
	DCD	EE_CORTEX_MX_TIM8_BRK_TIM12_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM8_UP_TIM13_ISR		
	DCD	EE_CORTEX_MX_TIM8_UP_TIM13_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR		
	DCD	EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM8_CC_ISR		
	DCD	EE_CORTEX_MX_TIM8_CC_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA1_STREAM7_ISR		
	DCD	EE_CORTEX_MX_DMA1_STREAM7_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_FSMC_ISR		
	DCD	EE_CORTEX_MX_FSMC_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_SDIO_ISR		
	DCD	EE_CORTEX_MX_SDIO_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM5_ISR		
	DCD	EE_CORTEX_MX_TIM5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_SPI3_ISR		
	DCD	EE_CORTEX_MX_SPI3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_UART4_ISR		
	DCD	EE_CORTEX_MX_UART4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_UART5_ISR		
	DCD	EE_CORTEX_MX_UART5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM6_DAC_ISR		
	DCD	EE_CORTEX_MX_TIM6_DAC_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_TIM7_ISR		
	DCD	EE_CORTEX_MX_TIM7_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA2_STREAM0_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA2_STREAM1_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA2_STREAM2_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA2_STREAM3_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_DMA2_STREAM4_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_ETH_ISR		
	DCD	EE_CORTEX_MX_ETH_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_ETH_WKUP_ISR		
	DCD	EE_CORTEX_MX_ETH_WKUP_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN2_TX_ISR		
	DCD	EE_CORTEX_MX_CAN2_TX_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN2_RX0_ISR		
	DCD	EE_CORTEX_MX_CAN2_RX0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN2_RX1_ISR		
	DCD	EE_CORTEX_MX_CAN2_RX1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_CAN2_SCE_ISR		
	DCD	EE_CORTEX_MX_CAN2_SCE_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef	EE_CORTEX_MX_OTG_FS_ISR		
	DCD	EE_CORTEX_MX_OTG_FS_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif 
#ifdef	EE_CORTEX_MX_DMA2_STREAM5_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif   
#ifdef	EE_CORTEX_MX_DMA2_STREAM6_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM6_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif   
#ifdef	EE_CORTEX_MX_DMA2_STREAM7_ISR		
	DCD	EE_CORTEX_MX_DMA2_STREAM7_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif  
#ifdef	EE_CORTEX_MX_USART6_ISR		
	DCD	EE_CORTEX_MX_USART6_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif  
#ifdef	EE_CORTEX_MX_I2C3_EV_ISR		
	DCD	EE_CORTEX_MX_I2C3_EV_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif  
#ifdef	EE_CORTEX_MX_I2C3_ER_ISR		
	DCD	EE_CORTEX_MX_I2C3_ER_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif  
#ifdef	EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR		
	DCD	EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif   
#ifdef	EE_CORTEX_MX_OTG_HS_EP1_IN_ISR		
	DCD	EE_CORTEX_MX_OTG_HS_EP1_IN_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif 
#ifdef	EE_CORTEX_MX_OTG_HS_WKUP_ISR		
	DCD	EE_CORTEX_MX_OTG_HS_WKUP_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif   
#ifdef	EE_CORTEX_MX_OTG_HS_ISR		
	DCD	EE_CORTEX_MX_OTG_HS_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif  
#ifdef	EE_CORTEX_MX_DCMI_ISR		
	DCD	EE_CORTEX_MX_DCMI_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif 
#ifdef	EE_CORTEX_MX_CRYP_ISR		
	DCD	EE_CORTEX_MX_CRYP_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif  
#ifdef	EE_CORTEX_MX_HASH_RNG_ISR		
	DCD	EE_CORTEX_MX_HASH_RNG_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif     
#ifdef	EE_CORTEX_MX_FPU_M4_ISR		
	DCD	EE_CORTEX_MX_FPU_M4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif                                                             
                                                                         

;******************************************************************************
;
; This is the code that gets called when the processor first starts execution
; following a reset event.
;
;******************************************************************************
	EXPORT	EE_cortex_mx_default_reset_ISR
EE_cortex_mx_default_reset_ISR
	;
	; Call the C library enty point that handles startup.  This will copy
	; the .data section initializers from flash to SRAM and zero fill the
	; .bss section.
	;
    IMPORT  __main

    ;FPU settings
    LDR     R0, =0xE000ED88           ; Enable CP10,CP11
    LDR     R1,[R0]
    ORR     R1,R1,#(0xF << 20)
    STR     R1,[R0]

    
    LDR     R0, =__main
    BX      R0

;******************************************************************************
;
; This is the code that gets called when the processor receives a BUS FAULT
; exception.
;
;******************************************************************************
#ifdef	__AUTOSAR_R4_0__
EE_cortex_mx_as_bus_fault_ISR
#ifdef	DEBUG
	BKPT	#0x00
#endif	/* DEBUG */
	B	EE_cortex_mx_as_bus_fault_ISR
#endif	/* __AUTOSAR_R4_0__ */

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

;******************************************************************************
;
; Make sure the end of this section is aligned.
;
;******************************************************************************
	ALIGN

;******************************************************************************
;
; Some code in the normal code section for initializing the heap and stack.
;
;******************************************************************************
	AREA	|.text|, CODE, READONLY

;******************************************************************************
;
; The function expected of the C library startup code for defining the stack
; and heap memory locations.  For the C library version of the startup code,
; provide this function so that the C library initialization code can find out
; the location of the stack and heap.
;
;******************************************************************************

;	IF	:DEF: __MICROLIB
#ifdef __MICROLIB
	EXPORT	__heap_base
	EXPORT	__heap_limit
#else
;    	ELSE

	IMPORT	__use_two_region_memory
	EXPORT	__user_initial_stackheap
__user_initial_stackheap
	LDR	R0, =HeapMem
	LDR	R1, =(StackMem + Stack)
	LDR	R2, =(HeapMem + Heap)
	LDR	R3, =StackMem
	BX	LR

#endif
;******************************************************************************
;
; Make sure the end of this section is aligned.
;
;******************************************************************************
	ALIGN


;******************************************************************************
;
; Tell the assembler that we're done.
;
;******************************************************************************
	END
