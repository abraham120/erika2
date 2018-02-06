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
; 	@file ee_startup_keil.s
; 	@brief Startup code for Keil uVision MDK-Lite.
; 	@author Giuseppe Serano
; 	@date 2011
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
#ifdef	EE_CORTEX_MX_RESET_ISR			/* Reset Handler */
	IMPORT	EE_CORTEX_MX_RESET_ISR
#endif
#ifdef EE_CORTEX_MX_NMI_ISR			/* The NMI handler */
	IMPORT	EE_CORTEX_MX_NMI_ISR
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR		/* The hard fault handler */
	IMPORT	EE_CORTEX_MX_HARD_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_MPU_FAULT_ISR		/* The MPU fault handler */
	IMPORT	EE_CORTEX_MX_MPU_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_BUS_FAULT_ISR		/* The bus fault handler */
	IMPORT	EE_CORTEX_MX_BUS_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_USAGE_FAULT_ISR		/* The usage fault handler */
	IMPORT	EE_CORTEX_MX_USAGE_FAULT_ISR
#endif
	IMPORT	EE_cortex_mx_svc_ISR		/* SVCall Handler */
	IMPORT	EE_cortex_mx_pendsv_ISR		/* PendSV Handler */
#ifdef	EE_CORTEX_MX_SYSTICK_ISR		/* SysTick Handler */
	IMPORT	EE_CORTEX_MX_SYSTICK_ISR
#endif
#ifdef EE_CORTEX_MX_DEBUG_MONITOR_ISR		/* Debug monitor handler */
	IMPORT	EE_CORTEX_MX_DEBUG_MONITOR_ISR
#endif
#ifdef EE_CORTEX_MX_SYSTICK_ISR			/* The SysTick handler */
	IMPORT	EE_CORTEX_MX_SYSTICK_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_A_ISR			/* GPIO Port A */
	IMPORT	EE_CORTEX_MX_GPIO_A_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_B_ISR			/* GPIO Port B */
	IMPORT	EE_CORTEX_MX_GPIO_B_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_C_ISR			/* GPIO Port C */
	IMPORT	EE_CORTEX_MX_GPIO_C_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_D_ISR			/* GPIO Port D */
	IMPORT	EE_CORTEX_MX_GPIO_D_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_E_ISR			/* GPIO Port E */
	IMPORT	EE_CORTEX_MX_GPIO_E_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_F_ISR			/* GPIO Port F */
	IMPORT	EE_CORTEX_MX_GPIO_F_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_G_ISR			/* GPIO Port G */
	IMPORT	EE_CORTEX_MX_GPIO_G_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_H_ISR			/* GPIO Port H */
	IMPORT	EE_CORTEX_MX_GPIO_H_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_J_ISR			/* GPIO Port J */
	IMPORT	EE_CORTEX_MX_GPIO_J_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_K_ISR			/* GPIO Port K */
	IMPORT	EE_CORTEX_MX_GPIO_K_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_L_ISR			/* GPIO Port L */
	IMPORT	EE_CORTEX_MX_GPIO_L_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_M_ISR			/* GPIO Port M */
	IMPORT	EE_CORTEX_MX_GPIO_M_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_N_ISR			/* GPIO Port N */
	IMPORT	EE_CORTEX_MX_GPIO_N_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P0_ISR			/* GPIO Port P (Summary or P0) */
	IMPORT	EE_CORTEX_MX_GPIO_P0_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P1_ISR			/* GPIO Port P1 */
	IMPORT	EE_CORTEX_MX_GPIO_P1_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P2_ISR			/* GPIO Port P2 */
	IMPORT	EE_CORTEX_MX_GPIO_P2_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P3_ISR			/* GPIO Port P3 */
	IMPORT	EE_CORTEX_MX_GPIO_P3_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P4_ISR			/* GPIO Port P4 */
	IMPORT	EE_CORTEX_MX_GPIO_P4_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P5_ISR			/* GPIO Port P5 */
	IMPORT	EE_CORTEX_MX_GPIO_P5_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P6_ISR			/* GPIO Port P6 */
	IMPORT	EE_CORTEX_MX_GPIO_P6_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P7_ISR			/* GPIO Port P7 */
	IMPORT	EE_CORTEX_MX_GPIO_P7_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q0_ISR			/* GPIO Port Q (Summary or Q0) */
	IMPORT	EE_CORTEX_MX_GPIO_Q0_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q1_ISR			/* GPIO Port Q1 */
	IMPORT	EE_CORTEX_MX_GPIO_Q1_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q2_ISR			/* GPIO Port Q2 */
	IMPORT	EE_CORTEX_MX_GPIO_Q2_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q3_ISR			/* GPIO Port Q3 */
	IMPORT	EE_CORTEX_MX_GPIO_Q3_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q4_ISR			/* GPIO Port Q4 */
	IMPORT	EE_CORTEX_MX_GPIO_Q4_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q5_ISR			/* GPIO Port Q5 */
	IMPORT	EE_CORTEX_MX_GPIO_Q5_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q6_ISR			/* GPIO Port Q6 */
	IMPORT	EE_CORTEX_MX_GPIO_Q6_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q7_ISR			/* GPIO Port Q7 */
	IMPORT	EE_CORTEX_MX_GPIO_Q7_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_R_ISR			/* GPIO Port R */
	IMPORT	EE_CORTEX_MX_GPIO_R_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_S_ISR			/* GPIO Port S */
	IMPORT	EE_CORTEX_MX_GPIO_S_ISR
#endif
#ifdef EE_CORTEX_MX_UART_0_ISR			/* UART0 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_0_ISR
#endif
#ifdef EE_CORTEX_MX_UART_1_ISR			/* UART1 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_1_ISR
#endif
#ifdef EE_CORTEX_MX_UART_2_ISR			/* UART2 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_2_ISR
#endif
#ifdef EE_CORTEX_MX_UART_3_ISR			/* UART3 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_3_ISR
#endif
#ifdef EE_CORTEX_MX_UART_4_ISR			/* UART4 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_4_ISR
#endif
#ifdef EE_CORTEX_MX_UART_5_ISR			/* UART5 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_5_ISR
#endif
#ifdef EE_CORTEX_MX_UART_6_ISR			/* UART6 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_6_ISR
#endif
#ifdef EE_CORTEX_MX_UART_7_ISR			/* UART7 Rx and Tx */
	IMPORT	EE_CORTEX_MX_UART_7_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_0_ISR			/* SSI0 Rx and Tx */
	IMPORT	EE_CORTEX_MX_SSI_0_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_1_ISR			/* SSI1 Rx and Tx */
	IMPORT	EE_CORTEX_MX_SSI_1_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_2_ISR			/* SSI2 Rx and Tx */
	IMPORT	EE_CORTEX_MX_SSI_2_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_3_ISR			/* SSI3 Rx and Tx */
	IMPORT	EE_CORTEX_MX_SSI_3_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_0_ISR			/* I2C0 Master and Slave */
	IMPORT	EE_CORTEX_MX_I2C_0_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_1_ISR			/* I2C1 Master and Slave */
	IMPORT	EE_CORTEX_MX_I2C_1_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_2_ISR			/* I2C2 Master and Slave */
	IMPORT	EE_CORTEX_MX_I2C_2_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_3_ISR			/* I2C3 Master and Slave */
	IMPORT	EE_CORTEX_MX_I2C_3_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_4_ISR			/* I2C4 Master and Slave */
	IMPORT	EE_CORTEX_MX_I2C_4_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_5_ISR			/* I2C5 Master and Slave */
	IMPORT	EE_CORTEX_MX_I2C_5_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_FAULT_ISR		/* PWM Fault */
	IMPORT	EE_CORTEX_MX_PWM_0_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_0_ISR			/* PWM Generator 0  */
	IMPORT	EE_CORTEX_MX_PWM_0_0_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_1_ISR			/* PWM Generator 1 */
	IMPORT	EE_CORTEX_MX_PWM_0_1_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_2_ISR			/* PWM Generator 2 */
	IMPORT	EE_CORTEX_MX_PWM_0_2_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_3_ISR			/* PWM Generator 3 */
	IMPORT	EE_CORTEX_MX_PWM_0_3_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_FAULT_ISR		/* PWM 1 Fault */
	IMPORT	EE_CORTEX_MX_PWM_1_FAULT_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_0_ISR			/* PWM 1 Generator 0 */
	IMPORT	EE_CORTEX_MX_PWM_1_0_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_1_ISR			/* PWM 1 Generator 1 */
	IMPORT	EE_CORTEX_MX_PWM_1_1_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_2_ISR			/* PWM 1 Generator 2 */
	IMPORT	EE_CORTEX_MX_PWM_1_2_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_3_ISR			/* PWM 1 Generator 3 */
	IMPORT	EE_CORTEX_MX_PWM_1_3_ISR
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_0_ISR		/* Quadrature Encoder 0 */
	IMPORT	EE_CORTEX_MX_QUAD_ENC_0_ISR
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_1_ISR		/* Quadrature Encoder 1 */
	IMPORT	EE_CORTEX_MX_QUAD_ENC_1_ISR
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_2_ISR		/* Quadrature Encoder 2 */
	IMPORT	EE_CORTEX_MX_QUAD_ENC_2_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_0_ISR			/* ADC Sequence 0 */
	IMPORT	EE_CORTEX_MX_ADC_0_0_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_1_ISR			/* ADC Sequence 1 */
	IMPORT	EE_CORTEX_MX_ADC_0_1_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_2_ISR			/* ADC Sequence 2 */
	IMPORT	EE_CORTEX_MX_ADC_0_2_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_3_ISR			/* ADC Sequence 3 */
	IMPORT	EE_CORTEX_MX_ADC_0_3_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_0_ISR			/* ADC1 Sequence 0 */
	IMPORT	EE_CORTEX_MX_ADC_1_0_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_1_ISR			/* ADC1 Sequence 1 */
	IMPORT	EE_CORTEX_MX_ADC_1_1_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_2_ISR			/* ADC1 Sequence 2 */
	IMPORT	EE_CORTEX_MX_ADC_1_2_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_3_ISR			/* ADC1 Sequence 3 */
	IMPORT	EE_CORTEX_MX_ADC_1_3_ISR
#endif
#ifdef EE_CORTEX_MX_WATCHDOG_TIMER_ISR		/* Watchdog timer */
	IMPORT	EE_CORTEX_MX_WATCHDOG_TIMER_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_0_A_ISR		/* Timer 0 subtimer A */
	IMPORT	EE_CORTEX_MX_TIMER_0_A_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_0_B_ISR		/* Timer 0 subtimer B */
	IMPORT	EE_CORTEX_MX_TIMER_0_B_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_1_A_ISR		/* Timer 1 subtimer A */
	IMPORT	EE_CORTEX_MX_TIMER_1_A_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_1_B_ISR		/* Timer 1 subtimer B */
	IMPORT	EE_CORTEX_MX_TIMER_1_B_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_2_A_ISR		/* Timer 2 subtimer A */
	IMPORT	EE_CORTEX_MX_TIMER_2_A_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_2_B_ISR		/* Timer 2 subtimer B */
	IMPORT	EE_CORTEX_MX_TIMER_2_B_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_3_A_ISR		/* Timer 3 subtimer A */
	IMPORT	EE_CORTEX_MX_TIMER_3_A_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_3_B_ISR		/* Timer 3 subtimer B */
	IMPORT	EE_CORTEX_MX_TIMER_3_B_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_4_A_ISR		/* Timer 4 subtimer A */
	IMPORT	EE_CORTEX_MX_TIMER_4_A_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_4_B_ISR		/* Timer 4 subtimer B */
	IMPORT	EE_CORTEX_MX_TIMER_4_B_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_5_A_ISR		/* Timer 5 subtimer A */
	IMPORT	EE_CORTEX_MX_TIMER_5_A_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_5_B_ISR		/* Timer 5 subtimer B */
	IMPORT	EE_CORTEX_MX_TIMER_5_B_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_A_ISR		/* Wide Timer 0 subtimer A */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_0_A_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_B_ISR		/* Wide Timer 0 subtimer B */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_0_B_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_A_ISR		/* Wide Timer 1 subtimer A */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_1_A_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_B_ISR		/* Wide Timer 1 subtimer B */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_1_B_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_A_ISR		/* Wide Timer 2 subtimer A */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_2_A_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_B_ISR		/* Wide Timer 2 subtimer B */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_2_B_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_A_ISR		/* Wide Timer 3 subtimer A */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_3_A_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_B_ISR		/* Wide Timer 3 subtimer B */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_3_B_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_A_ISR		/* Wide Timer 4 subtimer A */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_4_A_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_B_ISR		/* Wide Timer 4 subtimer B */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_4_B_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_A_ISR		/* Wide Timer 5 subtimer A */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_5_A_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_B_ISR		/* Wide Timer 5 subtimer B */
	IMPORT	EE_CORTEX_MX_WIDE_TIMER_5_B_ISR
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_0_ISR		/* Analog Comparator 0 */
	IMPORT	EE_CORTEX_MX_ANALOG_CMP_0_ISR
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_1_ISR		/* Analog Comparator 1 */
	IMPORT	EE_CORTEX_MX_ANALOG_CMP_1_ISR
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_2_ISR		/* Analog Comparator 2 */
	IMPORT	EE_CORTEX_MX_ANALOG_CMP_2_ISR
#endif
#ifdef EE_CORTEX_MX_SYS_CTRL_ISR		/* System Control (PLL, OSC, BO) */
	IMPORT	EE_CORTEX_MX_SYS_CTRL_ISR
#endif
#ifdef EE_CORTEX_MX_FLASH_CTRL_ISR		/* FLASH Control */
	IMPORT	EE_CORTEX_MX_FLASH_CTRL_ISR
#endif
#ifdef EE_CORTEX_MX_CAN_0_ISR			/* CAN0 */
	IMPORT	EE_CORTEX_MX_CAN_0_ISR
#endif
#ifdef EE_CORTEX_MX_CAN_0_ISR			/* CAN1 */
	IMPORT	EE_CORTEX_MX_CAN_1_ISR
#endif
#ifdef EE_CORTEX_MX_CAN_2_ISR			/* CAN2 */
	IMPORT	EE_CORTEX_MX_CAN_2_ISR
#endif
#ifdef EE_CORTEX_MX_ETHERNET_ISR		/* Ethernet */
	IMPORT	EE_CORTEX_MX_ETHERNET_ISR
#endif
#ifdef EE_CORTEX_MX_HIBERNATE_ISR		/* Hibernate */
	IMPORT	EE_CORTEX_MX_HIBERNATE_ISR
#endif
#ifdef EE_CORTEX_MX_USB_0_ISR			/* USB0 */
	IMPORT	EE_CORTEX_MX_USB_0_ISR
#endif
#ifdef EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR	/* uDMA Software Transfer */
	IMPORT	EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR
#endif
#ifdef EE_CORTEX_MX_UDMA_ERR_ISR		/* uDMA Error */
	IMPORT	EE_CORTEX_MX_UDMA_ERR_ISR
#endif
#ifdef EE_CORTEX_MX_I2S_0_ISR			/* I2S0 */
	IMPORT	EE_CORTEX_MX_I2S_0_ISR
#endif
#ifdef EE_CORTEX_MX_EXT_BUS_0_ISR		/* External Bus Interface 0 */
	IMPORT	EE_CORTEX_MX_EXT_BUS_0_ISR
#endif
#ifdef EE_CORTEX_MX_FPU_ISR			/* FPU */
	IMPORT	EE_CORTEX_MX_FPU_ISR
#endif
#ifdef EE_CORTEX_MX_PECI_0_ISR			/* PECI 0 */
	IMPORT	EE_CORTEX_MX_PECI_0_ISR
#endif
#ifdef EE_CORTEX_MX_LCP_0_ISR			/* LPC 0 */
	IMPORT	EE_CORTEX_MX_LCP_0_ISR
#endif
#ifdef EE_CORTEX_MX_FAN_0_ISR			/* Fan 0 */
	IMPORT	EE_CORTEX_MX_FAN_0_ISR
#endif

; Interrupt Vectors Table.
	EXPORT	EE_cortex_mx_vtable
EE_cortex_mx_vtable
	DCD	StackMem + Stack		; Top of Stack
#ifdef	EE_CORTEX_MX_RESET_ISR			/* Reset Handler */
	DCD	EE_CORTEX_MX_RESET_ISR
#else
	DCD	EE_cortex_mx_default_reset_ISR
#endif
#ifdef EE_CORTEX_MX_NMI_ISR			/* The NMI handler */
	DCD	EE_CORTEX_MX_NMI_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR		/* The hard fault handler */
	DCD	EE_CORTEX_MX_HARD_FAULT_ISR
#else
#ifdef	__AUTOSAR_R4_0__
	DCD	EE_cortex_mx_as_hard_fault_ISR
#else	/* __AUTOSAR_R4_0__ */
	DCD	EE_cortex_mx_default_ISR
#endif	/* !__AUTOSAR_R4_0__ */
#endif
#ifdef EE_CORTEX_MX_MPU_FAULT_ISR		/* The MPU fault handler */
	DCD	EE_CORTEX_MX_MPU_FAULT_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_BUS_FAULT_ISR		/* The bus fault handler */
	DCD	EE_CORTEX_MX_BUS_FAULT_ISR
#else
#ifdef	__AUTOSAR_R4_0__
	DCD	EE_cortex_mx_as_bus_fault_ISR
#else	/* __AUTOSAR_R4_0__ */
	DCD	EE_cortex_mx_default_ISR
#endif	/* !__AUTOSAR_R4_0__ */
#endif
#ifdef EE_CORTEX_MX_USAGE_FAULT_ISR		/* The usage fault handler */
	DCD	EE_CORTEX_MX_USAGE_FAULT_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
; Not for user: used by Erika Enterprise context switch.
	DCD	EE_cortex_mx_svc_ISR		; SVCall Handler
#ifdef EE_CORTEX_MX_DEBUG_MONITOR_ISR		/* Debug monitor handler */
	DCD	EE_CORTEX_MX_DEBUG_MONITOR_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
	DCD	0				; Reserved
; Not for user: used by Erika Enterptise context switch.
	DCD	EE_cortex_mx_pendsv_ISR		; PendSV Handler
#ifdef	EE_CORTEX_MX_SYSTICK_ISR		/* SysTick Handler */
	DCD	EE_CORTEX_MX_SYSTICK_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_A_ISR			/* GPIO Port A */
	DCD	EE_CORTEX_MX_GPIO_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_B_ISR			/* GPIO Port B */
	DCD	EE_CORTEX_MX_GPIO_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_C_ISR			/* GPIO Port C */
	DCD	EE_CORTEX_MX_GPIO_C_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_D_ISR			/* GPIO Port D */
	DCD	EE_CORTEX_MX_GPIO_D_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_E_ISR			/* GPIO Port E */
	DCD	EE_CORTEX_MX_GPIO_E_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_0_ISR			/* UART0 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_1_ISR			/* UART1 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_0_ISR			/* SSI0 Rx and Tx */
	DCD	EE_CORTEX_MX_SSI_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_0_ISR			/* I2C0 Master and Slave */
	DCD	EE_CORTEX_MX_I2C_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_FAULT_ISR		/* PWM Fault */
	DCD	EE_CORTEX_MX_PWM_0_FAULT_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_0_ISR			/* PWM Generator 0 */
	DCD	EE_CORTEX_MX_PWM_0_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_1_ISR			/* PWM Generator 1 */
	DCD	EE_CORTEX_MX_PWM_0_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_2_ISR			/* PWM Generator 2 */
	DCD	EE_CORTEX_MX_PWM_0_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_0_ISR		/* Quadrature Encoder 0 */
	DCD	EE_CORTEX_MX_QUAD_ENC_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_0_ISR			/* ADC Sequence 0 */
	DCD	EE_CORTEX_MX_ADC_0_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_1_ISR			/* ADC Sequence 1 */
	DCD	EE_CORTEX_MX_ADC_0_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_2_ISR			/* ADC Sequence 2 */
	DCD	EE_CORTEX_MX_ADC_0_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_0_3_ISR			/* ADC Sequence 3 */
	DCD	EE_CORTEX_MX_ADC_0_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WATCHDOG_TIMER_ISR		/* Watchdog timer */
	DCD	EE_CORTEX_MX_WATCHDOG_TIMER_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_0_A_ISR		/* Timer 0 subtimer A */
	DCD	EE_CORTEX_MX_TIMER_0_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_0_B_ISR		/* Timer 0 subtimer B */
	DCD	EE_CORTEX_MX_TIMER_0_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_1_A_ISR		/* Timer 1 subtimer A */
	DCD	EE_CORTEX_MX_TIMER_1_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_1_B_ISR		/* Timer 1 subtimer B */
	DCD	EE_CORTEX_MX_TIMER_1_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_2_A_ISR		/* Timer 2 subtimer A */
	DCD	EE_CORTEX_MX_TIMER_2_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_2_B_ISR		/* Timer 2 subtimer B */
	DCD	EE_CORTEX_MX_TIMER_2_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_0_ISR		/* Analog Comparator 0 */
	DCD	EE_CORTEX_MX_ANALOG_CMP_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_1_ISR		/* Analog Comparator 1 */
	DCD	EE_CORTEX_MX_ANALOG_CMP_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_2_ISR		/* Analog Comparator 2 */
	DCD	EE_CORTEX_MX_ANALOG_CMP_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_SYS_CTRL_ISR		/* System Control (PLL, OSC, BO) */
	DCD	EE_CORTEX_MX_SYS_CTRL_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_FLASH_CTRL_ISR		/* FLASH Control */
	DCD	EE_CORTEX_MX_FLASH_CTRL_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_F_ISR			/* GPIO Port F */
	DCD	EE_CORTEX_MX_GPIO_F_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_G_ISR			/* GPIO Port G */
	DCD	EE_CORTEX_MX_GPIO_G_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_H_ISR			/* GPIO Port H */
	DCD	EE_CORTEX_MX_GPIO_H_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_2_ISR			/* UART2 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_1_ISR			/* SSI1 Rx and Tx */
	DCD	EE_CORTEX_MX_SSI_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_3_A_ISR		/* Timer 3 subtimer A */
	DCD	EE_CORTEX_MX_TIMER_3_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_3_B_ISR		/* Timer 3 subtimer B */
	DCD	EE_CORTEX_MX_TIMER_3_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_1_ISR			/* I2C1 Master and Slave */
	DCD	EE_CORTEX_MX_I2C_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_1_ISR		/* Quadrature Encoder 1 */
	DCD	EE_CORTEX_MX_QUAD_ENC_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_CAN_0_ISR			/* CAN0 */
	DCD	EE_CORTEX_MX_CAN_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_CAN_1_ISR			/* CAN1 */
	DCD	EE_CORTEX_MX_CAN_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_CAN_2_ISR			/* CAN2 */
	DCD	EE_CORTEX_MX_CAN_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ETHERNET_ISR		/* Ethernet */
	DCD	EE_CORTEX_MX_ETHERNET_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_HIBERNATE_ISR		/* Hibernate */
	DCD	EE_CORTEX_MX_HIBERNATE_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_USB_0_ISR			/* USB0 */
	DCD	EE_CORTEX_MX_USB_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_0_3_ISR			/* PWM Generator 3 */
	DCD	EE_CORTEX_MX_PWM_0_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR	/* uDMA Software Transfer */
	DCD	EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UDMA_ERR_ISR		/* uDMA Error */
	DCD	EE_CORTEX_MX_UDMA_ERR_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_0_ISR			/* ADC1 Sequence 0 */
	DCD	EE_CORTEX_MX_ADC_1_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_1_ISR			/* ADC1 Sequence 1 */
	DCD	EE_CORTEX_MX_ADC_1_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_2_ISR			/* ADC1 Sequence 2 */
	DCD	EE_CORTEX_MX_ADC_1_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_ADC_1_3_ISR			/* ADC1 Sequence 3 */
	DCD	EE_CORTEX_MX_ADC_1_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_I2S_0_ISR			/* I2S0 */
	DCD	EE_CORTEX_MX_I2S_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_EXT_BUS_0_ISR		/* External Bus Interface 0 */
	DCD	EE_CORTEX_MX_EXT_BUS_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_J_ISR			/* GPIO Port J */
	DCD	EE_CORTEX_MX_GPIO_J_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_K_ISR			/* GPIO Port K */
	DCD	EE_CORTEX_MX_GPIO_K_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_L_ISR			/* GPIO Port L */
	DCD	EE_CORTEX_MX_GPIO_L_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_2_ISR			/* SSI2 Rx and Tx */
	DCD	EE_CORTEX_MX_SSI_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_SSI_3_ISR			/* SSI3 Rx and Tx */
	DCD	EE_CORTEX_MX_SSI_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_3_ISR			/* UART3 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_4_ISR			/* UART4 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_5_ISR			/* UART5 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_6_ISR			/* UART6 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_6_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_UART_7_ISR			/* UART7 Rx and Tx */
	DCD	EE_CORTEX_MX_UART_7_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
#ifdef EE_CORTEX_MX_I2C_2_ISR			/* I2C2 Master and Slave */
	DCD	EE_CORTEX_MX_I2C_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_3_ISR			/* I2C3 Master and Slave */
	DCD	EE_CORTEX_MX_I2C_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_4_A_ISR		/* Timer 4 subtimer A */
	DCD	EE_CORTEX_MX_TIMER_4_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_4_B_ISR		/* Timer 4 subtimer B */
	DCD	EE_CORTEX_MX_TIMER_4_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
	DCD	0				; Reserved
#ifdef EE_CORTEX_MX_TIMER_5_A_ISR		/* Timer 5 subtimer A */
	DCD	EE_CORTEX_MX_TIMER_5_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_TIMER_5_B_ISR		/* Timer 5 subtimer B */
	DCD	EE_CORTEX_MX_TIMER_5_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_A_ISR		/* Wide Timer 0 subtimer A */
	DCD	EE_CORTEX_MX_WIDE_TIMER_0_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_B_ISR		/* Wide Timer 0 subtimer B */
	DCD	EE_CORTEX_MX_WIDE_TIMER_0_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_A_ISR		/* Wide Timer 1 subtimer A */
	DCD	EE_CORTEX_MX_WIDE_TIMER_1_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_B_ISR		/* Wide Timer 1 subtimer B */
	DCD	EE_CORTEX_MX_WIDE_TIMER_1_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_A_ISR		/* Wide Timer 2 subtimer A */
	DCD	EE_CORTEX_MX_WIDE_TIMER_2_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_B_ISR		/* Wide Timer 2 subtimer B */
	DCD	EE_CORTEX_MX_WIDE_TIMER_2_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_A_ISR		/* Wide Timer 3 subtimer A */
	DCD	EE_CORTEX_MX_WIDE_TIMER_3_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_B_ISR		/* Wide Timer 3 subtimer B */
	DCD	EE_CORTEX_MX_WIDE_TIMER_3_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_A_ISR		/* Wide Timer 4 subtimer A */
	DCD	EE_CORTEX_MX_WIDE_TIMER_4_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_B_ISR		/* Wide Timer 4 subtimer B */
	DCD	EE_CORTEX_MX_WIDE_TIMER_4_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_A_ISR		/* Wide Timer 5 subtimer A */
	DCD	EE_CORTEX_MX_WIDE_TIMER_5_A_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_B_ISR		/* Wide Timer 5 subtimer B */
	DCD	EE_CORTEX_MX_WIDE_TIMER_5_B_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_FPU_ISR			/* FPU */
	DCD	EE_CORTEX_MX_FPU_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PECI_0_ISR			/* PECI 0 */
	DCD	EE_CORTEX_MX_PECI_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_LCP_0_ISR			/* LPC 0 */
	DCD	EE_CORTEX_MX_LCP_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_4_ISR			/* I2C4 Master and Slave */
	DCD	EE_CORTEX_MX_I2C_4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_I2C_5_ISR			/* I2C5 Master and Slave */
	DCD	EE_CORTEX_MX_I2C_5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_M_ISR			/* GPIO Port M */
	DCD	EE_CORTEX_MX_GPIO_M_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_N_ISR			/* GPIO Port N */
	DCD	EE_CORTEX_MX_GPIO_N_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_2_ISR		/* Quadrature Encoder 2 */
	DCD	EE_CORTEX_MX_QUAD_ENC_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_FAN_0_ISR			/* Fan 0 */
	DCD	EE_CORTEX_MX_FAN_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
	DCD	0				; Reserved
#ifdef EE_CORTEX_MX_GPIO_P0_ISR			/* GPIO Port P (Summary or P0) */
	DCD	EE_CORTEX_MX_GPIO_P0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P1_ISR			/* GPIO Port P1 */
	DCD	EE_CORTEX_MX_GPIO_P1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P2_ISR			/* GPIO Port P2 */
	DCD	EE_CORTEX_MX_GPIO_P2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P3_ISR			/* GPIO Port P3 */
	DCD	EE_CORTEX_MX_GPIO_P3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P4_ISR			/* GPIO Port P4 */
	DCD	EE_CORTEX_MX_GPIO_P4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P5_ISR			/* GPIO Port P5 */
	DCD	EE_CORTEX_MX_GPIO_P5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P6_ISR			/* GPIO Port P6 */
	DCD	EE_CORTEX_MX_GPIO_P6_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_P7_ISR			/* GPIO Port P7 */
	DCD	EE_CORTEX_MX_GPIO_P7_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q0_ISR			/* GPIO Port Q (Summary or Q0) */
	DCD	EE_CORTEX_MX_GPIO_Q0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q1_ISR			/* GPIO Port Q1 */
	DCD	EE_CORTEX_MX_GPIO_Q1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q2_ISR			/* GPIO Port Q2 */
	DCD	EE_CORTEX_MX_GPIO_Q2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q3_ISR			/* GPIO Port Q3 */
	DCD	EE_CORTEX_MX_GPIO_Q3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q4_ISR			/* GPIO Port Q4 */
	DCD	EE_CORTEX_MX_GPIO_Q4_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q5_ISR			/* GPIO Port Q5 */
	DCD	EE_CORTEX_MX_GPIO_Q5_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q6_ISR			/* GPIO Port Q6 */
	DCD	EE_CORTEX_MX_GPIO_Q6_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_Q7_ISR			/* GPIO Port Q7 */
	DCD	EE_CORTEX_MX_GPIO_Q7_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_R_ISR			/* GPIO Port R */
	DCD	EE_CORTEX_MX_GPIO_R_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_GPIO_S_ISR			/* GPIO Port S */
	DCD	EE_CORTEX_MX_GPIO_S_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_0_ISR			/* PWM 1 Generator 0 */
	DCD	EE_CORTEX_MX_PWM_1_0_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_1_ISR			/* PWM 1 Generator 1 */
	DCD	EE_CORTEX_MX_PWM_1_1_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_2_ISR			/* PWM 1 Generator 2 */
	DCD	EE_CORTEX_MX_PWM_1_2_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_3_ISR			/* PWM 1 Generator 3 */
	DCD	EE_CORTEX_MX_PWM_1_3_ISR
#else
	DCD	EE_cortex_mx_default_ISR
#endif
#ifdef EE_CORTEX_MX_PWM_1_FAULT_ISR		/* PWM 1 Fault */
	DCD	EE_CORTEX_MX_PWM_1_FAULT_ISR
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
	IMPORT	__main

    IF	{CPU} = "Cortex-M4.fp"
	LDR	R0, =0xE000ED88		; Enable CP10, CP11
	LDR	R1, [R0]
	ORR	R1, R1, #(0xF << 20)
	STR	R1, [R0]
    ENDIF

	B	__main

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
    IF	:DEF:	__MICROLIB
	EXPORT	__heap_base
	EXPORT	__heap_limit
    ELSE
	IMPORT	__use_two_region_memory
	EXPORT	__user_initial_stackheap
__user_initial_stackheap
	LDR	R0, =HeapMem
	LDR	R1, =(StackMem + Stack)
	LDR	R2, =(HeapMem + Heap)
	LDR	R3, =StackMem
	BX	LR
    ENDIF

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
