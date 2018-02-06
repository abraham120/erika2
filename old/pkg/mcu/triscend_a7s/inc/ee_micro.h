/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/*
 * Author: Marko Bertogna
 * CVS: $Id: ee_micro.h,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#ifndef __INCLUDE_TRISCEND_MICRO_H__
#define __INCLUDE_TRISCEND_MICRO_H__

#include "cpu/arm7tdmi/inc/ee_cpu.h"
#include _PROJECT_HEADER	//per definizioni di SEVEN_SEG_LED_REG e SWINP

/*
 **********************************************************
 *  Control Register Base Address Definitions
 **********************************************************
 */
 
#define MSS_BASE    0xd1010000
#define SYS_BASE    0xd1010100
#define INT_BASE    0xd1010200
#define REMAP_BASE  0xd1010400
#define TIMER_BASE  0xd1010500
#define WD_BASE     0xd1010600
#define CFG_BASE    0xd1010700
#define DMA_BASE    0xd1010800
#define UART_BASE   0xd1010900
#define BPU_BASE    0xd1010a00
#define PU_BASE     0xd1011100


/*
 **********************************************************
 * Memory Subsystem Unit Definition
 **********************************************************
 */


#define MSS_CONFIG_REG          ((volatile EE_ADDR)(MSS_BASE + 0x00))
#define MSS_TIM_CTRL_REG        ((volatile EE_ADDR)(MSS_BASE + 0x04))
#define MSS_SDR_MODE_REG        ((volatile EE_ADDR)(MSS_BASE + 0x08))
#define MSS_SDR_CTRL_REG        ((volatile EE_ADDR)(MSS_BASE + 0x0c))
#define MSS_STATUS_REG          ((volatile EE_ADDR)(MSS_BASE + 0x10))
#define MSS_STATUS_CLEAR_REG    ((volatile EE_ADDR)(MSS_BASE + 0x14))



/*
 **********************************************************
 *  Clock Control Definition
 **********************************************************
 */
 
#define SYS_CLOCK_CONTROL_REG      		((volatile EE_ADDR)(SYS_BASE + 0x00))
#define SYS_PLL_STATUS_REG      		((volatile EE_ADDR)(SYS_BASE + 0x04))
#define SYS_PLL_STATUS_CLEAR_REG 		((volatile EE_ADDR)(SYS_BASE + 0x08))

#define A7HAL_XCLK_FREQ  40000000    /* Default value for the external clock */
#define A7HAL_XTAL_FREQ  32768       /* Default value for PLL clock */
#define A7HAL_RING_FREQ  20000000    /* Default value for RING oscillator */

#define PLL_DIV_VALUE		((*SYS_CLOCK_CONTROL_REG >> 8) & 0xfff)
#define PLL_SCALE_VALUE		((*SYS_CLOCK_CONTROL_REG >> 24) & 0x1f)


/*
 **********************************************************
 *  System Control Registers
 **********************************************************
 */

#define SYS_RESET_CONTROL_REG    		((volatile EE_ADDR)(SYS_BASE + 0x0c))
#define SYS_POWER_CONTROL_REG    		((volatile EE_ADDR)(SYS_BASE + 0x10))

#define REMAP_PAUSE_REG  			((volatile EE_ADDR)(REMAP_BASE + 0x00))
#define REMAP_IDENTIFICATION_REG 		((volatile EE_ADDR)(REMAP_BASE + 0x10))
#define REMAP_REVISION_REG  			((volatile EE_ADDR)(REMAP_BASE + 0x14))
#define REMAP_CLEAR_RESET_MAP_REG		((volatile EE_ADDR)(REMAP_BASE + 0x20))
#define REMAP_RESET_STATUS_REG 			((volatile EE_ADDR)(REMAP_BASE + 0x30))
#define REMAP_RESET_STATUS_CLEAR_REG		((volatile EE_ADDR)(REMAP_BASE + 0x34))
#define REMAP_PIN_STATUS_REG  			((volatile EE_ADDR)(REMAP_BASE + 0x38))
#define REMAP_PIN_STATUS_CLEAR_REG  		((volatile EE_ADDR)(REMAP_BASE + 0x3c))
#define REMAP_ALIAS_ENABLE_REG    		((volatile EE_ADDR)(REMAP_BASE + 0x40))
#define REMAP_SRAM_CONFIG_REG    		((volatile EE_ADDR)(REMAP_BASE + 0x44))
#define REMAP_SRAM_BASE_ADR_REG  		((volatile EE_ADDR)(REMAP_BASE + 0x48))
#define REMAP_ACC_PROTECT_REG    		((volatile EE_ADDR)(REMAP_BASE + 0x4c))




/*
 **********************************************************
 *  Configuration Unit Definition
 **********************************************************
 */

#define CFG_CONFIG_CONTROL_REG		((volatile EE_ADDR)(CFG_BASE + 0x00))
#define CFG_CONFIG_TIMING_REG      	((volatile EE_ADDR)(CFG_BASE + 0x04))
#define CFG_IO_RECOVER_REG      	((volatile EE_ADDR)(CFG_BASE + 0x08))
#define CFG_CONFIG_PROTECT_REG 		((volatile EE_ADDR)(CFG_BASE + 0x0c))


/*
 ***********************************************************
 * DMA Unit Definition
 ***********************************************************
 */


/*
 **********************************************************
 * UART Definition
 **********************************************************
 */
  
 
 /*
 ******************************************************************************
 * Breakpoint Unit Definition
 ******************************************************************************
 */


/*
 ******************************************************************************
 * Protection Unit Registers (PU_BASE)
 ******************************************************************************
 */
 
  
/*
 **********************************************************
 * Debug Unit Definition
 **********************************************************
 */



/*
 **********************************************************
 * Interrupt Control Unit Definition
 **********************************************************
 */

#define INT_IRQ_STATUS_REG          ((volatile EE_ADDR)(INT_BASE + 0x00))  // read only
#define INT_IRQ_RAW_STATUS_REG      ((volatile EE_ADDR)(INT_BASE + 0x04))  // read only
#define INT_IRQ_ENABLE_REG          ((volatile EE_ADDR)(INT_BASE + 0x08))  // read/write
#define INT_IRQ_ENABLE_CLEAR_REG    ((volatile EE_ADDR)(INT_BASE + 0x0c))  // write only
#define INT_IRQ_SOFT_REG            ((volatile EE_ADDR)(INT_BASE + 0x10))  // write only
#define INT_FIQ_STATUS_REG          ((volatile EE_ADDR)(INT_BASE + 0x100)) // read only
#define INT_FIQ_RAW_STATUS_REG      ((volatile EE_ADDR)(INT_BASE + 0x104)) // read only
#define INT_FIQ_ENABLE_REG          ((volatile EE_ADDR)(INT_BASE + 0x108)) // read/write
#define INT_FIQ_ENABLE_CLEAR_REG    ((volatile EE_ADDR)(INT_BASE + 0x10c)) // write only
#define INT_IRQ_STEER_REG           ((volatile EE_ADDR)(INT_BASE + 0x110)) // write only

/*#define IRQ_STATUS_RESET_VALUE      0x00000000
#define IRQ_RAW_STATUS_RESET_VALUE  0x00000000
#define IRQ_ENABLE_RESET_VALUE      0x00000000
#define FIQ_STATUS_RESET_VALUE      0x00000000
#define FIQ_RAW_STATUS_RESET_VALUE  0x00000000
#define FIQ_ENABLE_RESET_VALUE      0x00000000
*/
#define FIQ_BIT              0
#define IRQ_SOFTWARE_BIT     1
#define IRQ_SERIAL_0_BIT     2
#define IRQ_TIMER_0_BIT      3
#define IRQ_TIMER_1_BIT      4
#define IRQ_SERIAL_1_BIT     5
#define IRQ_WATCHDOG_BIT     6
#define IRQ_DMA_0_BIT        7
#define IRQ_DMA_1_BIT        8
#define IRQ_DMA_2_BIT        9
#define IRQ_DMA_3_BIT       10
#define IRQ_CSL_USER_0_BIT  11
#define IRQ_CSL_USER_1_BIT  12
#define IRQ_CSL_USER_2_BIT  13
#define IRQ_JTAG_BIT        14
#define IRQ_BREAKPOINT_BIT  15


/*
 **********************************************************
 * Timer Unit Definition
 **********************************************************
 */

#define TIMER0_LOAD_REG  	((volatile EE_ADDR)(TIMER_BASE + 0x00))
#define TIMER1_LOAD_REG  	((volatile EE_ADDR)(TIMER_BASE + 0x20))
#define TIMER0_VALUE_REG 	((volatile EE_ADDR)(TIMER_BASE + 0x04))
#define TIMER1_VALUE_REG 	((volatile EE_ADDR)(TIMER_BASE + 0x24))
#define TIMER0_CONTROL_REG 	((volatile EE_ADDR)(TIMER_BASE + 0x08))
#define TIMER1_CONTROL_REG 	((volatile EE_ADDR)(TIMER_BASE + 0x28))
#define TIMER0_CLEAR_REG  	((volatile EE_ADDR)(TIMER_BASE + 0x0c))
#define TIMER1_CLEAR_REG  	((volatile EE_ADDR)(TIMER_BASE + 0x2c))


/*
 **********************************************************
 * Watchdog Unit Definition
 **********************************************************
 */


#define WATCHDOG_CONTROL_REG		((volatile EE_ADDR)(WD_BASE + 0x00))
#define WATCHDOG_TIMEOUT_VAL_REG	((volatile EE_ADDR)(WD_BASE + 0x04))
#define WATCHDOG_CURRENT_VAL_REG	((volatile EE_ADDR)(WD_BASE + 0x08))
#define WATCHDOG_CLEAR_REG		((volatile EE_ADDR)(WD_BASE + 0x0c))


/*
 **********************************************************
 * LED Unit Definition
 **********************************************************
 */

#ifdef __LED_USED__				//occorre includere FCP project header per SEVEN_SEG_LED_REG

#define LED_REG ((volatile EE_ADDR)(SEVEN_SEG_LED_REG))

extern EE_UREG EE_LED_numeric_display[16];	//Association number <-> segments

#endif /* __LED_USED__ */



/*
 **********************************************************
 * DIP Switch Definition
 ***********************************************************
 */

#ifdef __DIP_SWITCH_USED__		//occorre includere FCP project header per SWINP_REG

#define DIP_REG ((volatile EE_ADDR)(SWINP_REG))

#endif /* __DIP_SWITCH_USED__ */


//TODO: uart (dma, mpu)	- altre #define da triscend_a7s.h


#endif /* __INCLUDE_ARM7GNU_MICRO_H__ */


