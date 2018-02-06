/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, TU Dortmund University, Faculty of Computer Science 12
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

/* Author: Jan C. Kleinsorge, TU Dortmund University, 2010-
 *
 */
#ifndef __INCLUDE_EE_TC179x_SCU_H__
#define __INCLUDE_EE_TC179x_SCU_H__

#include "cpu/tricore1/inc/ee_hal.h"

#ifdef __TC1796__

/* Watchdog Timer Control Register 0 */
typedef union {
    struct {
        EE_UREG ENDINIT :1;  /* End-of-initialization Control Bit */
        EE_UREG WDTLCK  :1;  /* Lock Bit to Control (WDT_CON0) */
        EE_UREG WDTHPW0 :2;  /* Hardware Password 0 */
        EE_UREG WDTHPW1 :4;  /* Hardware Password 1 */
        EE_UREG WDTPW   :8;  /* User-defineable Passwword Field (WDT_CON0) */
        EE_UREG WDTREL  :16; /* Reload Value */
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_WDT_CON0;


/* Watchdog Timer Control Register 1 */
typedef union {
    struct {
        EE_UREG _bit0  :1; 
        EE_UREG _bit1  :1; 
        EE_UREG WDTIR  :1; /* WDT Input Frequency Request Control Bit */
        EE_UREG WDTDR  :1; /* WDT Timer Disale Request Control Bit */
        EE_UREG _bit4  :1; 
        EE_UREG _bit5  :1; 
        EE_UREG _bit6  :1; 
        EE_UREG _bit7  :1; 
        EE_UREG _bit8  :1; 
        EE_UREG _bit9  :1; 
        EE_UREG _bit10 :1; 
        EE_UREG _bit11 :1; 
        EE_UREG _bit12 :1; 
        EE_UREG _bit13 :1; 
        EE_UREG _bit14 :1; 
        EE_UREG _bit15 :1; 
        EE_UREG _bit16 :1; 
        EE_UREG _bit17 :1; 
        EE_UREG _bit18 :1; 
        EE_UREG _bit19 :1; 
        EE_UREG _bit20 :1; 
        EE_UREG _bit21 :1; 
        EE_UREG _bit22 :1; 
        EE_UREG _bit23 :1; 
        EE_UREG _bit24 :1; 
        EE_UREG _bit25 :1; 
        EE_UREG _bit26 :1; 
        EE_UREG _bit27 :1; 
        EE_UREG _bit28 :1; 
        EE_UREG _bit29 :1; 
        EE_UREG _bit30 :1; 
        EE_UREG _bit31 :1; 
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_WDT_CON1;


/* Oscillator Control Register (FIXME: possibly unused) */
typedef union {
    struct {
        EE_UREG MOSC   :1;      /* Main Oscillator Test Mode */
        EE_UREG OSCR   :1;      /* Oscillator Run Status Bit */
        EE_UREG ORDRES :1;      /* Oscillator Run Detection Bit */
        EE_UREG _bit3  :1;      
        EE_UREG OGC    :1;      /* Oscillator Gain Control */
        EE_UREG _bit5  :1;
        EE_UREG _bit6  :1;
        EE_UREG _bit7  :1;
        EE_UREG _bit8  :1;
        EE_UREG _bit9  :1;
        EE_UREG _bit10 :1;
        EE_UREG _bit11 :1;
        EE_UREG _bit12 :1;
        EE_UREG _bit13 :1;
        EE_UREG _bit14 :1;
        EE_UREG _bit15 :1;
        EE_UREG _bit16 :1;
        EE_UREG _bit17 :1;
        EE_UREG _bit18 :1;
        EE_UREG _bit19 :1;
        EE_UREG _bit20 :1;
        EE_UREG _bit21 :1;
        EE_UREG _bit22 :1;
        EE_UREG _bit23 :1;
        EE_UREG _bit24 :1;
        EE_UREG _bit25 :1;
        EE_UREG _bit26 :1;
        EE_UREG _bit27 :1;
        EE_UREG _bit28 :1;
        EE_UREG _bit29 :1;
        EE_UREG _bit30 :1;
        EE_UREG _bit31 :1;       
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_OSC_CON;


/* PPL Clock Control and Status Register */
typedef union {
    struct {
        EE_UREG LOCK   :1;      /* PLL Lock Status Flag */
        EE_UREG RESLD  :1;      /* Restart Lock Detection */
        EE_UREG SYSFS  :1;      /* System Frequency select */
        EE_UREG _bit3  :1;
        EE_UREG _bit4  :1;
        EE_UREG VCOBYP :1;      /* VCO Bypass Mode Selection */
        EE_UREG VCOSEL :2;      /* VCO Range Selection */
        EE_UREG KDIV   :4;      /* PLL K-Divider Selection */
        EE_UREG _bit12 :1;
        EE_UREG PDIV   :3;      /* PLL P-Divider selection */
        EE_UREG NDIV   :7;      /* PLL N-Divider selection */
        EE_UREG _bit23 :1;
        EE_UREG OSCDISC:1;      /* Oscillator Disconnect */
        EE_UREG _bit25 :1;
        EE_UREG _bit26 :1;
        EE_UREG _bit27 :1;
        EE_UREG _bit28 :1;
        EE_UREG BYPPIN :1;      /* Bypass Pin Status Flag */
        EE_UREG _bit30 :1;
        EE_UREG _bit31 :1;
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_PLL_CLC;


#endif  /* __TC1796__ */


#endif 
