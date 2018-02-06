/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef EE_MCU_MPC5643L_ADC_H
#define EE_MCU_MPC5643L_ADC_H

#include <cpu/common/inc/ee_stdint.h>
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>

#include "BswCommon.h"

#define ADC_MODULE_NUM      0x2
#define ADC__0   0x0U   
#define ADC__1   0x1U
#define ADC_POLLING_HIT     0x2
#define ADC_POLLING_MISS    0x3
#define ADC_POLLING_ERROR   0x4

#define ADC_CH_NUM          9

#define MAX_VOLTAGE 3200	/* uVolt */
#define MIN_VOLTAGE 0		/* uVolt */

#define MAX_ADC_VALUE	0x0FFFU	/* max value sampled by the ADC */
#define MIN_ADC_VALUE	0x0000U	/* min value sampled by the ADC */

/* Watchdog Threshold for ADC0 CH0-CH1_CH2 */
#define ADC0_CH0_THRESHOLD_HIGH	0xFFFU
#define ADC0_CH0_THRESHOLD_LOW	0x200U

/* defined equal to max and min value
 * of the ADC, hence no isr for CH1
 * and CH2 */
#define ADC0_CH1_THRESHOLD_HIGH	0xFFFU
#define ADC0_CH1_THRESHOLD_LOW	0x0U

#define ADC0_CH2_THRESHOLD_HIGH	0xFFFU
#define ADC0_CH2_THRESHOLD_LOW	0x0U

/* Watchdog Threshold enable macro for ADC0 CH0-CH1_CH2 */
#define ADC0_CH0_THR_ENABLE_HIGH	0x1U
#define ADC0_CH0_THR_ENABLE_LOW		0x2U

#define ADC0_CH1_THR_ENABLE_HIGH	0x4U
#define ADC0_CH1_THR_ENABLE_LOW		0x8U

#define ADC0_CH2_THR_ENABLE_HIGH	0x10U
#define ADC0_CH2_THR_ENABLE_LOW		0x20U

/* Watchdog Threshold isr macro for ADC0 CH0-CH1_CH2 */
#define ADC0_CH0_THR_ISR_HIGH		0x1U
#define ADC0_CH0_THR_ISR_LOW		0x2U

#define ADC0_CH1_THR_ISR_HIGH		0x4U
#define ADC0_CH1_THR_ISR_LOW		0x8U

#define ADC0_CH2_THR_ISR_HIGH		0x10U
#define ADC0_CH2_THR_ISR_LOW		0x20U

/* Presampling macros */
#define PRESAMPLE_CH0	0x1
#define PRESAMPLE_CH1	0x1<<1
#define PRESAMPLE_CH2	0x1<<2
#define PRESAMPLE_CH3	0x1<<3
#define PRESAMPLE_CH4	0x1<<4
#define PRESAMPLE_CH5	0x1<<5
#define PRESAMPLE_CH6	0x1<<6
#define PRESAMPLE_CH7	0x1<<7
#define PRESAMPLE_CH8	0x1<<8
#define PRESAMPLE_CH9	0x1<<9
#define PRESAMPLE_CH10	0x1<<10
#define PRESAMPLE_CH11	0x1<<11
#define PRESAMPLE_CH12	0x1<<12
#define PRESAMPLE_CH13	0x1<<13
#define PRESAMPLE_CH14	0x1<<14
#define PRESAMPLE_CH15	0x1<<15

/* Presampling reference values */
#define PRESAMPLING_REF_LOW	0x1U
#define PRESAMPLING_REF_HIGH	0x2U

#define ADC0_BASE 0xFFE00000
#define ADC0_CWENR0 (*(volatile unsigned int *)(ADC0_BASE+0x000002E0))

StdReturnType   InitADC(void);

inline uint8 AdcPollChannel(const uint8 adcModule, const uint8 channel)
{
    uint8 result;

    if (adcModule != ADC__0 && adcModule != ADC__1) {
        /* Not allowed ADC module number */
        return ADC_POLLING_ERROR;
    }

    if (channel > ADC_CH_NUM) {
        /* Not allowed ADC channel number */
        return ADC_POLLING_ERROR;
    }

    if (adcModule == ADC__0) {
        if (ADC_0.CDR[channel].B.VALID == 1) {
            result = ADC_POLLING_HIT;
        }
        else {
            result = ADC_POLLING_MISS;
        }
    }
    else {
        if (ADC_1.CDR[channel].B.VALID == 1) {
            result = ADC_POLLING_HIT;
        }
        else {
            result = ADC_POLLING_MISS;
        }
    }

    return result;
}

#endif


