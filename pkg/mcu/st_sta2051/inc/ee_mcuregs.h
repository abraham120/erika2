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
 * Author: 2006 Paolo Gai
 * CVS: $Id: ee_mcuregs.h,v 1.1 2006/10/19 09:51:44 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_cpu.h"

#ifndef __INCLUDE_MCU_ST_STA2051_MCUREGS__
#define __INCLUDE_MCU_ST_STA2051_MCUREGS__



#define RCCU_BASE    0xA0000000	

/* 
 * RCCU 
 */
#define CLKCTL      ((volatile EE_ADDR)(RCCU_BASE + 0x0000))
#define CLK_FLAG    ((volatile EE_ADDR)(RCCU_BASE + 0x0008))
#define PLLCONF     ((volatile EE_ADDR)(RCCU_BASE + 0x0018))
#define PH_CLOCK_EN ((volatile EE_ADDR)(RCCU_BASE + 0x001C))
#define SYSMODE     ((volatile EE_ADDR)(RCCU_BASE + 0x0020))




/*
 * CPM Register Map 
 */
#define CPUDIV   ((volatile EE_ADDR)(RCCU_BASE + 0x0040))
#define APBDIV   ((volatile EE_ADDR)(RCCU_BASE + 0x0044))
#define PH_RST   ((volatile EE_ADDR)(RCCU_BASE + 0x0048))
#define PLL2CTL  ((volatile EE_ADDR)(RCCU_BASE + 0x004c))
#define BOOTCONF ((volatile EE_ADDR)(RCCU_BASE + 0x0050)) /* bit 1-0= 00flash 01ram */
#define PWRCTRL  ((volatile EE_ADDR)(RCCU_BASE + 0x0054))







/*
 * Enhanced Interrupt Controller
 */
#define EIC_ADDR	0xFFFFFC00

/* Interrupt Control Register */
#define ICR		((volatile EE_ADDR)(EIC_ADDR + 0x00))
#define ICR_IRQ_EN	((volatile EE_ADDR)(1 << 0))
#define ICR_FIQ_EN	((volatile EE_ADDR)(1 << 1))

/* Current Interrupt Channel Register (readonly) */
#define CICR		((volatile EE_ADDR)(EIC_ADDR + 0x04))

/* Current Interrupt Priority Register (readonly) */
#define CIPR		((volatile EE_ADDR)(EIC_ADDR + 0x08))

/* Interrupt Vector Register */
#define IVR		((volatile EE_ADDR)(EIC_ADDR + 0x18))

/* Fast Interrupt Register */
#define FIR		((volatile EE_ADDR)(EIC_ADDR + 0x1C))

/* Normal Interrupt Registers */
#define IER		((volatile EE_ADDR)(EIC_ADDR + 0x20)) /* enable */
#define IPR		((volatile EE_ADDR)(EIC_ADDR + 0x40)) /* pending */
#define SIR		((volatile EE_ADDR)(EIC_ADDR + 0x60)) /* SIV and SIPL array */





/*
 * Timers
 */

/* Timer 0 */
#define T0_ADDR	0xE0009000
#define T0_ICAR		((volatile EE_ADDR)(T0_ADDR + 0x00))
#define T0_ICBR		((volatile EE_ADDR)(T0_ADDR + 0x04))
#define T0_OCAR		((volatile EE_ADDR)(T0_ADDR + 0x08))
#define T0_OCBR		((volatile EE_ADDR)(T0_ADDR + 0x0c))
#define T0_CNTR		((volatile EE_ADDR)(T0_ADDR + 0x10))
#define T0_CR1 		((volatile EE_ADDR)(T0_ADDR + 0x14))
#define T0_CR2 		((volatile EE_ADDR)(T0_ADDR + 0x18))
#define T0_SR  		((volatile EE_ADDR)(T0_ADDR + 0x1c))

/* Timer 1 */
#define T1_ADDR	0xE000A000
#define T1_ICAR		((volatile EE_ADDR)(T1_ADDR + 0x00))
#define T1_ICBR		((volatile EE_ADDR)(T1_ADDR + 0x04))
#define T1_OCAR		((volatile EE_ADDR)(T1_ADDR + 0x08))
#define T1_OCBR		((volatile EE_ADDR)(T1_ADDR + 0x0c))
#define T1_CNTR		((volatile EE_ADDR)(T1_ADDR + 0x10))
#define T1_CR1 		((volatile EE_ADDR)(T1_ADDR + 0x14))
#define T1_CR2 		((volatile EE_ADDR)(T1_ADDR + 0x18))
#define T1_SR  		((volatile EE_ADDR)(T1_ADDR + 0x1c))

/* Timer 2 */
#define T2_ADDR	0xE000B000
#define T2_ICAR		((volatile EE_ADDR)(T2_ADDR + 0x00))
#define T2_ICBR		((volatile EE_ADDR)(T2_ADDR + 0x04))
#define T2_OCAR		((volatile EE_ADDR)(T2_ADDR + 0x08))
#define T2_OCBR		((volatile EE_ADDR)(T2_ADDR + 0x0c))
#define T2_CNTR		((volatile EE_ADDR)(T2_ADDR + 0x10))
#define T2_CR1 		((volatile EE_ADDR)(T2_ADDR + 0x14))
#define T2_CR2 		((volatile EE_ADDR)(T2_ADDR + 0x18))
#define T2_SR  		((volatile EE_ADDR)(T2_ADDR + 0x1c))

/* Timer 3 */
#define T3_ADDR	0xE000C000
#define T3_ICAR		((volatile EE_ADDR)(T3_ADDR + 0x00))
#define T3_ICBR		((volatile EE_ADDR)(T3_ADDR + 0x04))
#define T3_OCAR		((volatile EE_ADDR)(T3_ADDR + 0x08))
#define T3_OCBR		((volatile EE_ADDR)(T3_ADDR + 0x0c))
#define T3_CNTR		((volatile EE_ADDR)(T3_ADDR + 0x10))
#define T3_CR1 		((volatile EE_ADDR)(T3_ADDR + 0x14))
#define T3_CR2 		((volatile EE_ADDR)(T3_ADDR + 0x18))
#define T3_SR  		((volatile EE_ADDR)(T3_ADDR + 0x1c))

/* timer bit masks */
#define CR1_EN          0x8000
#define CR1_PWMI        0x4000
#define CR1_FOLVB       0x0800
#define CR1_FOLVA       0x0400
#define CR1_OLVLB       0x0200
#define CR1_OLVLA       0x0100
#define CR1_OCBE        0x0080
#define CR1_OCAE        0x0040
#define CR1_OPM         0x0020
#define CR1_PWM         0x0010
#define CR1_IEDGB       0x0008
#define CR1_IEDGA       0x0004
#define CR1_EXEDG       0x0002
#define CR1_ECKEN       0x0001

#define CR2_ICAIE       0x8000
#define CR2_OCAIE       0x4000
#define CR2_TOE         0x2000
#define CR2_ICBIE       0x1000
#define CR2_OCBIE       0x0800

#define SR_ICFA         0x8000
#define SR_OCFA         0x4000
#define SR_TOF          0x2000
#define SR_ICFB         0x1000
#define SR_OCFB         0x0800







#endif
