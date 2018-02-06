/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
	@file ee_vtable_ccs.c
	@brief Interrupt Vector Table for use with TI's Code Composer Studio.
	@author Giuseppe Serano
	@date 2011
 */

#include "ee.h"

/*
 * Extern declaration of the default handlers.
 */
extern void EE_cortex_mx_default_ISR(void);		// Default Handler
#ifdef EE_CORTEX_MX_RESET_ISR				// The reset handler
extern void EE_CORTEX_MX_RESET_ISR(void);
#else
extern void EE_cortex_mx_default_reset_ISR(void);
#endif
#ifdef EE_CORTEX_MX_NMI_ISR				// The NMI handler
extern void EE_CORTEX_MX_NMI_ISR(void);
#else
extern void EE_cortex_mx_nmi_ISR(void);
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR			// The hard fault handler
extern void EE_CORTEX_MX_HARD_FAULT_ISR(void);
#else
extern void EE_cortex_mx_hard_fault_ISR(void);
#endif
#ifdef EE_CORTEX_MX_MPU_FAULT_ISR			// The MPU fault handler
extern void EE_CORTEX_MX_MPU_FAULT_ISR(void);
#else
extern void EE_cortex_mx_mpu_fault_ISR(void);
#endif
#ifdef EE_CORTEX_MX_BUS_FAULT_ISR			// The bus fault handler
extern void EE_CORTEX_MX_BUS_FAULT_ISR(void);
#else
extern void EE_cortex_mx_bus_fault_ISR(void);
#endif
#ifdef EE_CORTEX_MX_USAGE_FAULT_ISR			// The usage fault handler
extern void EE_CORTEX_MX_USAGE_FAULT_ISR(void);
#else
extern void EE_cortex_mx_usage_fault_ISR(void);
#endif
/* Not for user: used by Erika Enterprise context switch. */
extern void EE_cortex_mx_svcall_handler(void);		// The SVCall handler
#ifdef EE_CORTEX_MX_DEBUG_MONITOR_ISR			// Debug monitor handler
extern void EE_CORTEX_MX_DEBUG_MONITOR_ISR(void);
#else
extern void EE_cortex_mx_debug_monitor_ISR(void);
#endif
/* Not for user: used by Erika Enterprise context switch. */
extern void EE_cortex_mx_pendsv_handler(void);		// The PendSV handler
#ifdef EE_CORTEX_MX_SYSTICK_ISR				// The SysTick handler
extern void EE_CORTEX_MX_SYSTICK_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_A_ISR				// GPIO Port A
extern void EE_CORTEX_MX_GPIO_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_B_ISR				// GPIO Port B
extern void EE_CORTEX_MX_GPIO_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_C_ISR				// GPIO Port C
extern void EE_CORTEX_MX_GPIO_C_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_D_ISR				// GPIO Port D
extern void EE_CORTEX_MX_GPIO_D_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_E_ISR				// GPIO Port E
extern void EE_CORTEX_MX_GPIO_E_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_F_ISR				// GPIO Port F
extern void EE_CORTEX_MX_GPIO_F_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_G_ISR				// GPIO Port G
extern void EE_CORTEX_MX_GPIO_G_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_H_ISR				// GPIO Port H
extern void EE_CORTEX_MX_GPIO_H_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_J_ISR				// GPIO Port J
extern void EE_CORTEX_MX_GPIO_J_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_K_ISR				// GPIO Port K
extern void EE_CORTEX_MX_GPIO_K_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_L_ISR				// GPIO Port L
extern void EE_CORTEX_MX_GPIO_L_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_M_ISR				// GPIO Port M
extern void EE_CORTEX_MX_GPIO_M_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_N_ISR				// GPIO Port N
extern void EE_CORTEX_MX_GPIO_N_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P0_ISR				// GPIO Port P (Summary or P0)
extern void EE_CORTEX_MX_GPIO_P0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P1_ISR				// GPIO Port P1
extern void EE_CORTEX_MX_GPIO_P1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P2_ISR				// GPIO Port P2
extern void EE_CORTEX_MX_GPIO_P2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P3_ISR				// GPIO Port P3
extern void EE_CORTEX_MX_GPIO_P3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P4_ISR				// GPIO Port P4
extern void EE_CORTEX_MX_GPIO_P4_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P5_ISR				// GPIO Port P5
extern void EE_CORTEX_MX_GPIO_P5_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P6_ISR				// GPIO Port P6
extern void EE_CORTEX_MX_GPIO_P6_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_P7_ISR				// GPIO Port P7
extern void EE_CORTEX_MX_GPIO_P7_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q0_ISR				// GPIO Port Q (Summary or Q0)
extern void EE_CORTEX_MX_GPIO_Q0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q1_ISR				// GPIO Port Q1
extern void EE_CORTEX_MX_GPIO_Q1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q2_ISR				// GPIO Port Q2
extern void EE_CORTEX_MX_GPIO_Q2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q3_ISR				// GPIO Port Q3
extern void EE_CORTEX_MX_GPIO_Q3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q4_ISR				// GPIO Port Q4
extern void EE_CORTEX_MX_GPIO_Q4_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q5_ISR				// GPIO Port Q5
extern void EE_CORTEX_MX_GPIO_Q5_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q6_ISR				// GPIO Port Q6
extern void EE_CORTEX_MX_GPIO_Q6_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_Q7_ISR				// GPIO Port Q7
extern void EE_CORTEX_MX_GPIO_Q7_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_R_ISR				// GPIO Port R
extern void EE_CORTEX_MX_GPIO_R_ISR(void);
#endif
#ifdef EE_CORTEX_MX_GPIO_S_ISR				// GPIO Port S
extern void EE_CORTEX_MX_GPIO_S_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_0_ISR				// UART0 Rx and Tx
extern void EE_CORTEX_MX_UART_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_1_ISR				// UART1 Rx and Tx
extern void EE_CORTEX_MX_UART_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_2_ISR				// UART2 Rx and Tx
extern void EE_CORTEX_MX_UART_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_3_ISR				// UART3 Rx and Tx
extern void EE_CORTEX_MX_UART_3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_4_ISR				// UART4 Rx and Tx
extern void EE_CORTEX_MX_UART_4_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_5_ISR				// UART5 Rx and Tx
extern void EE_CORTEX_MX_UART_5_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_6_ISR				// UART6 Rx and Tx
extern void EE_CORTEX_MX_UART_6_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UART_7_ISR				// UART7 Rx and Tx
extern void EE_CORTEX_MX_UART_7_ISR(void);
#endif
#ifdef EE_CORTEX_MX_SSI_0_ISR
extern void EE_CORTEX_MX_SSI_0_ISR(void);		// SSI0 Rx and Tx
#endif
#ifdef EE_CORTEX_MX_SSI_1_ISR
extern void EE_CORTEX_MX_SSI_1_ISR(void);		// SSI1 Rx and Tx
#endif
#ifdef EE_CORTEX_MX_SSI_2_ISR
extern void EE_CORTEX_MX_SSI_2_ISR(void);		// SSI2 Rx and Tx
#endif
#ifdef EE_CORTEX_MX_SSI_3_ISR
extern void EE_CORTEX_MX_SSI_3_ISR(void);		// SSI3 Rx and Tx
#endif
#ifdef EE_CORTEX_MX_I2C_0_ISR				// I2C0 Master and Slave
extern void EE_CORTEX_MX_I2C_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_I2C_1_ISR				// I2C1 Master and Slave
extern void EE_CORTEX_MX_I2C_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_I2C_2_ISR				// I2C2 Master and Slave
extern void EE_CORTEX_MX_I2C_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_I2C_3_ISR				// I2C3 Master and Slave
extern void EE_CORTEX_MX_I2C_3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_I2C_4_ISR				// I2C4 Master and Slave
extern void EE_CORTEX_MX_I2C_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_I2C_5_ISR				// I2C5 Master and Slave
extern void EE_CORTEX_MX_I2C_5_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_0_FAULT_ISR			// PWM Fault
extern void EE_CORTEX_MX_PWM_0_FAULT_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_0_0_ISR				// PWM Generator 0
extern void EE_CORTEX_MX_PWM_0_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_0_1_ISR				// PWM Generator 1
extern void EE_CORTEX_MX_PWM_0_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_0_2_ISR				// PWM Generator 2
extern void EE_CORTEX_MX_PWM_0_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_0_3_ISR				// PWM Generator 3
extern void EE_CORTEX_MX_PWM_0_3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_1_FAULT_ISR			// PWM 1 Fault
extern void EE_CORTEX_MX_PWM_1_FAULT_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_1_0_ISR				// PWM 1 Generator 0
extern void EE_CORTEX_MX_PWM_1_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_1_1_ISR				// PWM 1 Generator 1
extern void EE_CORTEX_MX_PWM_1_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_1_2_ISR				// PWM 1 Generator 2
extern void EE_CORTEX_MX_PWM_1_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PWM_1_3_ISR				// PWM 1 Generator 3
extern void EE_CORTEX_MX_PWM_1_3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_0_ISR			// Quadrature Encoder 0
extern void EE_CORTEX_MX_QUAD_ENC_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_1_ISR			// Quadrature Encoder 1
extern void EE_CORTEX_MX_QUAD_ENC_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_2_ISR			// Quadrature Encoder 2
extern void EE_CORTEX_MX_QUAD_ENC_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_0_0_ISR				// ADC Sequence 0
extern void EE_CORTEX_MX_ADC_0_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_0_1_ISR				// ADC Sequence 1
extern void EE_CORTEX_MX_ADC_0_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_0_2_ISR				// ADC Sequence 2
extern void EE_CORTEX_MX_ADC_0_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_0_3_ISR				// ADC Sequence 3
extern void EE_CORTEX_MX_ADC_0_3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_1_0_ISR				// ADC1 Sequence 0
extern void EE_CORTEX_MX_ADC_1_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_1_1_ISR				// ADC1 Sequence 1
extern void EE_CORTEX_MX_ADC_1_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_1_2_ISR				// ADC1 Sequence 2
extern void EE_CORTEX_MX_ADC_1_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ADC_1_3_ISR				// ADC1 Sequence 3
extern void EE_CORTEX_MX_ADC_1_3_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WATCHDOG_TIMER_ISR			// Watchdog timer
extern void EE_CORTEX_MX_WATCHDOG_TIMER_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_0_A_ISR			// Timer 0 subtimer A
extern void EE_CORTEX_MX_TIMER_0_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_0_B_ISR			// Timer 0 subtimer B
extern void EE_CORTEX_MX_TIMER_0_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_1_A_ISR			// Timer 1 subtimer A
extern void EE_CORTEX_MX_TIMER_1_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_1_B_ISR			// Timer 1 subtimer B
extern void EE_CORTEX_MX_TIMER_1_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_2_A_ISR			// Timer 2 subtimer A
extern void EE_CORTEX_MX_TIMER_2_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_2_B_ISR			// Timer 2 subtimer B
extern void EE_CORTEX_MX_TIMER_2_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_3_A_ISR			// Timer 3 subtimer A
extern void EE_CORTEX_MX_TIMER_3_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_3_B_ISR			// Timer 3 subtimer B
extern void EE_CORTEX_MX_TIMER_3_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_4_A_ISR			// Timer 4 subtimer A
extern void EE_CORTEX_MX_TIMER_4_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_4_B_ISR			// Timer 4 subtimer B
extern void EE_CORTEX_MX_TIMER_4_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_5_A_ISR			// Timer 5 subtimer A
extern void EE_CORTEX_MX_TIMER_5_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_TIMER_5_B_ISR			// Timer 5 subtimer B
extern void EE_CORTEX_MX_TIMER_5_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_A_ISR			// Wide Timer 0 subtimer A
extern void EE_CORTEX_MX_WIDE_TIMER_0_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_B_ISR			// Wide Timer 0 subtimer B
extern void EE_CORTEX_MX_WIDE_TIMER_0_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_A_ISR			// Wide Timer 1 subtimer A
extern void EE_CORTEX_MX_WIDE_TIMER_1_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_B_ISR			// Wide Timer 1 subtimer B
extern void EE_CORTEX_MX_WIDE_TIMER_1_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_A_ISR			// Wide Timer 2 subtimer A
extern void EE_CORTEX_MX_WIDE_TIMER_2_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_B_ISR			// Wide Timer 2 subtimer B
extern void EE_CORTEX_MX_WIDE_TIMER_2_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_A_ISR			// Wide Timer 3 subtimer A
extern void EE_CORTEX_MX_WIDE_TIMER_3_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_B_ISR			// Wide Timer 3 subtimer B
extern void EE_CORTEX_MX_WIDE_TIMER_3_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_A_ISR			// Wide Timer 4 subtimer A
extern void EE_CORTEX_MX_WIDE_TIMER_4_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_B_ISR			// Wide Timer 4 subtimer B
extern void EE_CORTEX_MX_WIDE_TIMER_4_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_A_ISR			// Wide Timer 5 subtimer A
extern void EE_CORTEX_MX_WIDE_TIMER_5_A_ISR(void);
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_B_ISR			// Wide Timer 5 subtimer B
extern void EE_CORTEX_MX_WIDE_TIMER_5_B_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_0_ISR			// Analog Comparator 0
extern void EE_CORTEX_MX_ANALOG_CMP_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_1_ISR			// Analog Comparator 1
extern void EE_CORTEX_MX_ANALOG_CMP_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_2_ISR			// Analog Comparator 2
extern void EE_CORTEX_MX_ANALOG_CMP_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_SYS_CTRL_ISR			// System Control (PLL, OSC, BO)
extern void EE_CORTEX_MX_SYS_CTRL_ISR(void);
#endif
#ifdef EE_CORTEX_MX_FLASH_CTRL_ISR			// FLASH Control
extern void EE_CORTEX_MX_FLASH_CTRL_ISR(void);
#endif
#ifdef EE_CORTEX_MX_CAN_0_ISR				// CAN0
extern void EE_CORTEX_MX_CAN_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_CAN_0_ISR				// CAN1
extern void EE_CORTEX_MX_CAN_1_ISR(void);
#endif
#ifdef EE_CORTEX_MX_CAN_2_ISR				// CAN2
extern void EE_CORTEX_MX_CAN_2_ISR(void);
#endif
#ifdef EE_CORTEX_MX_ETHERNET_ISR			// Ethernet
extern void EE_CORTEX_MX_ETHERNET_ISR(void);
#endif
#ifdef EE_CORTEX_MX_HIBERNATE_ISR			// Hibernate
extern void EE_CORTEX_MX_HIBERNATE_ISR(void);
#endif
#ifdef EE_CORTEX_MX_USB_0_ISR				// USB0
extern void EE_CORTEX_MX_USB_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR		// uDMA Software Transfer
extern void EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR(void);
#endif
#ifdef EE_CORTEX_MX_UDMA_ERR_ISR			// uDMA Error
extern void EE_CORTEX_MX_UDMA_ERR_ISR(void);
#endif
#ifdef EE_CORTEX_MX_I2S_0_ISR				// I2S0
extern void EE_CORTEX_MX_I2S_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_EXT_BUS_0_ISR			// External Bus Interface 0
extern void EE_CORTEX_MX_EXT_BUS_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_FPU_ISR				// FPU
extern void EE_CORTEX_MX_FPU_ISR(void);
#endif
#ifdef EE_CORTEX_MX_PECI_0_ISR				// PECI 0
extern void EE_CORTEX_MX_PECI_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_LCP_0_ISR				// LPC 0
extern void EE_CORTEX_MX_LCP_0_ISR(void);
#endif
#ifdef EE_CORTEX_MX_FAN_0_ISR				// Fan 0
extern void EE_CORTEX_MX_FAN_0_ISR(void);
#endif

/*
 * Linker variable that marks the top of the stack.
 */
extern unsigned long __STACK_TOP;

/*
 * The vector table.  Note that the proper constructs must be placed on this to
 * ensure that it ends up at physical address 0x0000.0000 or at the start of
 * the program if located at a start address other than 0.
 */
#pragma DATA_SECTION(EE_cortex_mx_vtable, ".intvecs")
void (* const EE_cortex_mx_vtable[])(void) =
{
    (void (*)(void))((unsigned long)&__STACK_TOP),
					// The initial stack pointer
#ifdef EE_CORTEX_MX_RESET_ISR		// The reset handler
    EE_CORTEX_MX_RESET_ISR,
#else
    EE_cortex_mx_default_reset_ISR,
#endif
#ifdef EE_CORTEX_MX_NMI_ISR		// The NMI handler
    EE_CORTEX_MX_NMI_ISR,
#else
    EE_cortex_mx_nmi_ISR,
#endif
#ifdef EE_CORTEX_MX_HARD_FAULT_ISR	// The hard fault handler
    EE_CORTEX_MX_HARD_FAULT_ISR,
#else
    EE_cortex_mx_hard_fault_ISR,
#endif
#ifdef EE_CORTEX_MX_MPU_FAULT_ISR	// The MPU fault handler
    EE_CORTEX_MX_MPU_FAULT_ISR,
#else
    EE_cortex_mx_mpu_fault_ISR,
#endif
#ifdef EE_CORTEX_MX_BUS_FAULT_ISR	// The bus fault handler
    EE_CORTEX_MX_BUS_FAULT_ISR,
#else
    EE_cortex_mx_bus_fault_ISR,
#endif
#ifdef EE_CORTEX_MX_USAGE_FAULT_ISR	// The usage fault handler
    EE_CORTEX_MX_USAGE_FAULT_ISR,
#else
    EE_cortex_mx_usage_fault_ISR,
#endif
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    /* Not for user: used by Erika Enterprise context switch. */
    EE_cortex_mx_svcall_handler,	// The SVCall handler
#ifdef EE_CORTEX_MX_DEBUG_MONITOR_ISR	// Debug monitor handler
    EE_CORTEX_MX_DEBUG_MONITOR_ISR,
#else
    EE_cortex_mx_debug_monitor_ISR,
#endif
    0,					// Reserved
    /* Not for user: used by Erika Enterprise context switch. */
    EE_cortex_mx_pendsv_handler,	// The PendSV handler
#ifdef EE_CORTEX_MX_SYSTICK_ISR		// The SysTick handler
    EE_CORTEX_MX_SYSTICK_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_A_ISR		// GPIO Port A
    EE_CORTEX_MX_GPIO_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_B_ISR		// GPIO Port B
    EE_CORTEX_MX_GPIO_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_C_ISR		// GPIO Port C
    EE_CORTEX_MX_GPIO_C_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_D_ISR		// GPIO Port D
    EE_CORTEX_MX_GPIO_D_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_E_ISR		// GPIO Port E
    EE_CORTEX_MX_GPIO_E_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_0_ISR		// UART0 Rx and Tx
    EE_CORTEX_MX_UART_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_1_ISR		// UART1 Rx and Tx
    EE_CORTEX_MX_UART_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_SSI_0_ISR		// SSI0 Rx and Tx
    EE_CORTEX_MX_SSI_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_I2C_0_ISR		// I2C0 Master and Slave
    EE_CORTEX_MX_I2C_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_0_FAULT_ISR	// PWM Fault
    EE_CORTEX_MX_PWM_0_FAULT_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_0_0_ISR		// PWM Generator 0
    EE_CORTEX_MX_PWM_0_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_0_1_ISR		// PWM Generator 1
    EE_CORTEX_MX_PWM_0_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_0_2_ISR		// PWM Generator 2
    EE_CORTEX_MX_PWM_0_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_0_ISR	// Quadrature Encoder 0
    EE_CORTEX_MX_QUAD_ENC_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_0_0_ISR		// ADC Sequence 0
    EE_CORTEX_MX_ADC_0_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_0_1_ISR		// ADC Sequence 1
    EE_CORTEX_MX_ADC_0_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_0_2_ISR		// ADC Sequence 2
    EE_CORTEX_MX_ADC_0_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_0_3_ISR		// ADC Sequence 3
    EE_CORTEX_MX_ADC_0_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WATCHDOG_TIMER_ISR	// Watchdog timer
    EE_CORTEX_MX_WATCHDOG_TIMER_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_0_A_ISR	// Timer 0 subtimer A
    EE_CORTEX_MX_TIMER_0_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_0_B_ISR	// Timer 0 subtimer B
    EE_CORTEX_MX_TIMER_0_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_1_A_ISR	// Timer 1 subtimer A
    EE_CORTEX_MX_TIMER_1_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_1_B_ISR	// Timer 1 subtimer B
    EE_CORTEX_MX_TIMER_1_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_2_A_ISR	// Timer 2 subtimer A
    EE_CORTEX_MX_TIMER_2_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_2_B_ISR	// Timer 2 subtimer B
    EE_CORTEX_MX_TIMER_2_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_0_ISR	// Analog Comparator 0
    EE_CORTEX_MX_ANALOG_CMP_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_1_ISR	// Analog Comparator 1
    EE_CORTEX_MX_ANALOG_CMP_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ANALOG_CMP_2_ISR	// Analog Comparator 2
    EE_CORTEX_MX_ANALOG_CMP_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_SYS_CTRL_ISR	// System Control (PLL, OSC, BO)
    EE_CORTEX_MX_SYS_CTRL_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_FLASH_CTRL_ISR	// FLASH Control
    EE_CORTEX_MX_FLASH_CTRL_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_F_ISR		// GPIO Port F
    EE_CORTEX_MX_GPIO_F_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_G_ISR		// GPIO Port G
    EE_CORTEX_MX_GPIO_G_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_H_ISR		// GPIO Port H
    EE_CORTEX_MX_GPIO_H_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_2_ISR		// UART2 Rx and Tx
    EE_CORTEX_MX_UART_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_SSI_1_ISR		// SSI1 Rx and Tx
    EE_CORTEX_MX_SSI_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_3_A_ISR	// Timer 3 subtimer A
    EE_CORTEX_MX_TIMER_3_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_3_B_ISR	// Timer 3 subtimer B
    EE_CORTEX_MX_TIMER_3_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_I2C_1_ISR		// I2C1 Master and Slave
    EE_CORTEX_MX_I2C_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_1_ISR	// Quadrature Encoder 1
    EE_CORTEX_MX_QUAD_ENC_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_CAN_0_ISR		// CAN0
    EE_CORTEX_MX_CAN_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_CAN_1_ISR		// CAN1
    EE_CORTEX_MX_CAN_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_CAN_2_ISR		// CAN2
    EE_CORTEX_MX_CAN_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ETHERNET_ISR	// Ethernet
    EE_CORTEX_MX_ETHERNET_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_HIBERNATE_ISR	// Hibernate
    EE_CORTEX_MX_HIBERNATE_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_USB_0_ISR		// USB0
    EE_CORTEX_MX_USB_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_0_3_ISR		// PWM Generator 3
    EE_CORTEX_MX_PWM_0_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR	// uDMA Software Transfer
    EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UDMA_ERR_ISR	// uDMA Error
    EE_CORTEX_MX_UDMA_ERR_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_1_0_ISR		// ADC1 Sequence 0
    EE_CORTEX_MX_ADC_1_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_1_1_ISR		// ADC1 Sequence 1
    EE_CORTEX_MX_ADC_1_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_1_2_ISR		// ADC1 Sequence 2
    EE_CORTEX_MX_ADC_1_2_ISR
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_ADC_1_3_ISR		// ADC1 Sequence 3
    EE_CORTEX_MX_ADC_1_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_I2S_0_ISR		// I2S0
    EE_CORTEX_MX_I2S_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_EXT_BUS_0_ISR	// External Bus Interface 0
    EE_CORTEX_MX_EXT_BUS_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_J_ISR		// GPIO Port J
    EE_CORTEX_MX_GPIO_J_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_K_ISR		// GPIO Port K
    EE_CORTEX_MX_GPIO_K_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_L_ISR		// GPIO Port L
    EE_CORTEX_MX_GPIO_L_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_SSI_2_ISR		// SSI2 Rx and Tx
    EE_CORTEX_MX_SSI_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_SSI_3_ISR		// SSI3 Rx and Tx
    EE_CORTEX_MX_SSI_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_3_ISR		// UART3 Rx and Tx
    EE_CORTEX_MX_UART_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_4_ISR		// UART4 Rx and Tx
    EE_CORTEX_MX_UART_4_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_5_ISR		// UART5 Rx and Tx
    EE_CORTEX_MX_UART_5_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_6_ISR		// UART6 Rx and Tx
    EE_CORTEX_MX_UART_6_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_UART_7_ISR		// UART7 Rx and Tx
    EE_CORTEX_MX_UART_7_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
#ifdef EE_CORTEX_MX_I2C_2_ISR		// I2C2 Master and Slave
    EE_CORTEX_MX_I2C_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_I2C_3_ISR		// I2C3 Master and Slave
    EE_CORTEX_MX_I2C_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_4_A_ISR	// Timer 4 subtimer A
    EE_CORTEX_MX_TIMER_4_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_4_B_ISR	// Timer 4 subtimer B
    EE_CORTEX_MX_TIMER_4_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
#ifdef EE_CORTEX_MX_TIMER_5_A_ISR	// Timer 5 subtimer A
    EE_CORTEX_MX_TIMER_5_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_TIMER_5_B_ISR	// Timer 5 subtimer B
    EE_CORTEX_MX_TIMER_5_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_A_ISR	// Wide Timer 0 subtimer A
    EE_CORTEX_MX_WIDE_TIMER_0_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_0_B_ISR	// Wide Timer 0 subtimer B
    EE_CORTEX_MX_WIDE_TIMER_0_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_A_ISR	// Wide Timer 1 subtimer A
    EE_CORTEX_MX_WIDE_TIMER_1_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_1_B_ISR	// Wide Timer 1 subtimer B
    EE_CORTEX_MX_WIDE_TIMER_1_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_A_ISR	// Wide Timer 2 subtimer A
    EE_CORTEX_MX_WIDE_TIMER_2_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_2_B_ISR	// Wide Timer 2 subtimer B
    EE_CORTEX_MX_WIDE_TIMER_2_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_A_ISR	// Wide Timer 3 subtimer A
    EE_CORTEX_MX_WIDE_TIMER_3_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_3_B_ISR	// Wide Timer 3 subtimer B
    EE_CORTEX_MX_WIDE_TIMER_3_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_A_ISR	// Wide Timer 4 subtimer A
    EE_CORTEX_MX_WIDE_TIMER_4_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_4_B_ISR	// Wide Timer 4 subtimer B
    EE_CORTEX_MX_WIDE_TIMER_4_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_A_ISR	// Wide Timer 5 subtimer A
    EE_CORTEX_MX_WIDE_TIMER_5_A_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_WIDE_TIMER_5_B_ISR	// Wide Timer 5 subtimer B
    EE_CORTEX_MX_WIDE_TIMER_5_B_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_FPU_ISR		// FPU
    EE_CORTEX_MX_FPU_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PECI_0_ISR		// PECI 0
    EE_CORTEX_MX_PECI_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_LCP_0_ISR		// LPC 0
    EE_CORTEX_MX_LCP_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_I2C_4_ISR		// I2C4 Master and Slave
    EE_CORTEX_MX_I2C_4_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_I2C_5_ISR		// I2C5 Master and Slave
    EE_CORTEX_MX_I2C_5_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_M_ISR		// GPIO Port M
    EE_CORTEX_MX_GPIO_M_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_N_ISR		// GPIO Port N
    EE_CORTEX_MX_GPIO_N_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_QUAD_ENC_2_ISR	// Quadrature Encoder 2
    EE_CORTEX_MX_QUAD_ENC_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_FAN_0_ISR		// Fan 0
    EE_CORTEX_MX_FAN_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
    0,					// Reserved
#ifdef EE_CORTEX_MX_GPIO_P0_ISR		// GPIO Port P (Summary or P0)
    EE_CORTEX_MX_GPIO_P0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P1_ISR		// GPIO Port P1
    EE_CORTEX_MX_GPIO_P1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P2_ISR		// GPIO Port P2
    EE_CORTEX_MX_GPIO_P2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P3_ISR		// GPIO Port P3
    EE_CORTEX_MX_GPIO_P3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P4_ISR		// GPIO Port P4
    EE_CORTEX_MX_GPIO_P4_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P5_ISR		// GPIO Port P5
    EE_CORTEX_MX_GPIO_P5_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P6_ISR		// GPIO Port P6
    EE_CORTEX_MX_GPIO_P6_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_P7_ISR		// GPIO Port P7
    EE_CORTEX_MX_GPIO_P7_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q0_ISR		// GPIO Port Q (Summary or Q0)
    EE_CORTEX_MX_GPIO_Q0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q1_ISR		// GPIO Port Q1
    EE_CORTEX_MX_GPIO_Q1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q2_ISR		// GPIO Port Q2
    EE_CORTEX_MX_GPIO_Q2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q3_ISR		// GPIO Port Q3
    EE_CORTEX_MX_GPIO_Q3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q4_ISR		// GPIO Port Q4
    EE_CORTEX_MX_GPIO_Q4_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q5_ISR		// GPIO Port Q5
    EE_CORTEX_MX_GPIO_Q5_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q6_ISR		// GPIO Port Q6
    EE_CORTEX_MX_GPIO_Q6_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_Q7_ISR		// GPIO Port Q7
    EE_CORTEX_MX_GPIO_Q7_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_R_ISR		// GPIO Port R
    EE_CORTEX_MX_GPIO_R_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_GPIO_S_ISR		// GPIO Port S
    EE_CORTEX_MX_GPIO_S_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_1_0_ISR		// PWM 1 Generator 0
    EE_CORTEX_MX_PWM_1_0_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_1_1_ISR		// PWM 1 Generator 1
    EE_CORTEX_MX_PWM_1_1_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_1_2_ISR		// PWM 1 Generator 2
    EE_CORTEX_MX_PWM_1_2_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_1_3_ISR		// PWM 1 Generator 3
    EE_CORTEX_MX_PWM_1_3_ISR,
#else
    EE_cortex_mx_default_ISR,
#endif
#ifdef EE_CORTEX_MX_PWM_1_FAULT_ISR	// PWM 1 Fault
    EE_CORTEX_MX_PWM_1_FAULT_ISR
#else
    EE_cortex_mx_default_ISR
#endif
};
