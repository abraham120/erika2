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
#ifndef __INCLUDE_EE_TC179x_STM_H__
#define __INCLUDE_EE_TC179x_STM_H__

#include "cpu/tricore1/inc/ee_hal.h"

#ifdef __TC1796__

/* System Timer Clock Control Regsister */
typedef union {
    struct {
        EE_UREG DISR   :1;  /* Module Disable Request */
        EE_UREG DISS   :1;  /* Module Disable Status */
        EE_UREG SPEN   :1;  /* Module Suspend Enable for OCDS */
        EE_UREG EDIS   :1;  /* External Request Disable */
        EE_UREG SBWE   :1;  /* Module Suspend Bit Write Enable for OCDS */
        EE_UREG FSOE   :1;  /* Fast Switch Off Enable */
        EE_UREG _bit6  :1;
        EE_UREG _bit7  :1;
        EE_UREG RMC    :3;  /* Clock Divider in Run Mode */
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
} __ALIGNED__(4) EE_STM_CLC;


/* System Timer Interrupt Control Register */
typedef union {
    struct {
        EE_UREG CMP0EN :1; /* CMP0 Interrupt Enable Control */
        EE_UREG CMP0IR :1; /* CMP0 Interrupt Request Flag */
        EE_UREG CMP0OS :1; /* CMP0 Interrupt Output Selection */
        EE_UREG _bit3  :1;
        EE_UREG CMP1EN :1; /* CMP1 Interrupt Enable Control */
        EE_UREG CMP1IR :1; /* CMP1 Interrupt Request Flag */
        EE_UREG CMP1OS :1; /* CMP1 Interrupt Output Selection */
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
} __ALIGNED__(4) EE_STM_ICR;


/* System Timer Compare Match Control Register */
typedef union {
    struct {
        EE_UREG MSIZE0  :5;     /* Compare Register Size for CMP0 */
        EE_UREG _bit5   :1;
        EE_UREG _bit6   :1;
        EE_UREG _bit7   :1;
        EE_UREG MSTART0 :5;     /* Compare Register Start for CMP0 */
        EE_UREG _bit13  :1;
        EE_UREG _bit14  :1;
        EE_UREG _bit15  :1;
        EE_UREG MSIZE1  :5;     /* Compare Register Size for CMP1 */
        EE_UREG _bit21  :1;
        EE_UREG _bit22  :1;
        EE_UREG _bit23  :1;
        EE_UREG MSTART1 :5;     /* Compare Register Start for CMP1 */
        EE_UREG _bit29  :1;
        EE_UREG _bit30  :1;
        EE_UREG _bit31  :1;
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_STM_CMCON;



/* System timer Interrupt Set/Reset Register */
typedef union {
    struct {
        EE_UREG CMP0IRR  :1; /* Reset Compare Register CMP0 Interrupt Flag */
        EE_UREG CMP0IRS  :1; /* Set Compare Register CMP0 Interrupt Flag */
        EE_UREG CMP1IRR  :1; /* Reset Compare Register CMP1 Interrupt Flag */
        EE_UREG CMP1IRS  :1; /* Set Compare Register CMP1 Interrupt Flag */
        EE_UREG _bit4    :1;
        EE_UREG _bit5    :1;
        EE_UREG _bit6    :1;
        EE_UREG _bit7    :1;
        EE_UREG _bit8    :1;
        EE_UREG _bit9    :1;
        EE_UREG _bit10   :1;
        EE_UREG _bit11   :1;
        EE_UREG _bit12   :1;
        EE_UREG _bit13   :1;
        EE_UREG _bit14   :1;
        EE_UREG _bit15   :1;
        EE_UREG _bit16   :1;
        EE_UREG _bit17   :1;
        EE_UREG _bit18   :1;
        EE_UREG _bit19   :1;
        EE_UREG _bit20   :1;
        EE_UREG _bit21   :1;
        EE_UREG _bit22   :1;
        EE_UREG _bit23   :1;
        EE_UREG _bit24   :1;
        EE_UREG _bit25   :1;
        EE_UREG _bit26   :1;
        EE_UREG _bit27   :1;
        EE_UREG _bit28   :1;
        EE_UREG _bit29   :1;
        EE_UREG _bit30   :1;
        EE_UREG _bit31   :1;
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_STM_ISRR;


/* System Timer Service Request Control Register 0 */
typedef union {
    struct {
        EE_UREG SRPN   :8;      /* Service Request Priority Numner */
        EE_UREG _bit8  :1;
        EE_UREG _bit9  :1;
        EE_UREG TOS    :1;      /* Type of Service Control */
        EE_UREG _bit11 :1;
        EE_UREG SRE    :1;      /* Service Request Enable */
        EE_UREG SRR    :1;      /* Service Request Flag */
        EE_UREG CLRR   :1;      /* Request Clear Bit */
        EE_UREG SETR   :1;      /* Request Set Bit */
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
} __ALIGNED__(4) EE_STM_SRC0;


/* System Timer Service Request Control Register 1 */
typedef EE_STM_SRC0 EE_STM_SRC1;


/* System Timer Compare Register 0 */
typedef union {
    struct {
        EE_UREG CMPVAL: 32;     /* Compare Value */
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_STM_CMP0;


/* System Timer Compare Register 1 */
typedef EE_STM_CMP0 EE_STM_CMP1;


/* System Timer/Capture Register 0 */
typedef union {
    EE_UREG bits_0_31;
    EE_UREG reg;
} __ALIGNED__(4) EE_STM_TIM0;

/* System Timer/Capture Register 6 */
typedef union {
    EE_UREG bits_32_55;
    EE_UREG reg;
} __ALIGNED__(4) EE_STM_TIM6;

/* System Timer Capture Register */
typedef EE_STM_TIM6 EE_STM_CAP;


#else

#error Other MCU not supported.

#endif


/* Initializes the STM (STM freq == SYS freq) */
void EE_tc179x_stm_init(void);

/* Programs an STM compare register to trigger an IRQ after n ticks
 * and enabled the compare register.  
 *
 * If iv == 0, then the correponding service request node is left
 * unprogrammed. */
void EE_tc179x_stm_cmp0_init(EE_UINT8 iv, EE_UINT32 match);

/* Sets the compare register */
void EE_tc179x_stm_set_cmp0(EE_UINT32 match);

/* Returns the number of STM ticks per microsecond. */
EE_UINT32 EE_tc179x_stm_ticks_per_usec(void);


#endif 
