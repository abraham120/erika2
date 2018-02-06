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

#include "adc.h"
#include "AdcCfg.h"

#define MODULE_ID   (12)

static void ADC0_CH0_WD_Threshold_set(void)
{
	unsigned int old_value = ADC_0.THRHLR0.B.THRL;

	ADC_0.THRHLR0.B.THRL = old_value | ADC0_CH0_THRESHOLD_LOW;
	old_value = ADC_0.THRHLR0.B.THRH;
	ADC_0.THRHLR0.B.THRH = old_value | ADC0_CH0_THRESHOLD_HIGH;
}

static void ADC0_CH1_WD_Threshold_set(void)
{
	unsigned int old_value = ADC_0.THRHLR1.B.THRL;

	ADC_0.THRHLR1.B.THRL = old_value | ADC0_CH1_THRESHOLD_LOW;
	old_value = ADC_0.THRHLR1.B.THRH;
	ADC_0.THRHLR1.B.THRH = old_value | ADC0_CH1_THRESHOLD_HIGH;
}

static void ADC0_CH2_WD_Threshold_set(void)
{
	unsigned int old_value = ADC_0.THRHLR2.B.THRL;

	ADC_0.THRHLR2.B.THRL = old_value | ADC0_CH2_THRESHOLD_LOW;
	old_value = ADC_0.THRHLR2.B.THRH;
	ADC_0.THRHLR2.B.THRH = old_value | ADC0_CH2_THRESHOLD_HIGH;
}

static void ADC0_WD_enable_threshold(void)
{
	ADC0_CWENR0 = ADC0_CH0_THR_ENABLE_HIGH | ADC0_CH0_THR_ENABLE_LOW | \
		ADC0_CH1_THR_ENABLE_HIGH | ADC0_CH1_THR_ENABLE_LOW | \
		ADC0_CH2_THR_ENABLE_HIGH | ADC0_CH2_THR_ENABLE_LOW;
}

static void ADC0_WD_set_threshold_isr(void)
{
	ADC_0.WTIMR.R = ADC0_CH0_THR_ISR_HIGH | ADC0_CH0_THR_ISR_LOW | \
		ADC0_CH1_THR_ISR_HIGH | ADC0_CH1_THR_ISR_LOW | \
		ADC0_CH2_THR_ISR_HIGH | ADC0_CH2_THR_ISR_LOW;
}

static void ADC0_set_presampled_channels(unsigned int list_of_channels)
{
	ADC_0.PSR0.R = list_of_channels;
}

static void ADC0_bypass_sampling_phase(void)
{
	ADC_0.PSCR.B.PRECONV  = 0x1U;
}

static void ADC0_set_presampling_ref_value(unsigned int presampling_value)
{
	ADC_0.PSCR.B.PREVAL0 = presampling_value;
}

static StdReturnType InitADCInternal(const uint8 channel)
{
    /* Return code from SSD pFlashErase function. */
    unsigned int returnCode = STD_OK;

    if (channel == ADC__0) {
        if (adcConfContainer[channel].peripheralFreq == ADC_HALF_SYS_FREQ) {
            /* 
             * enable result overwriting,
             * enable CTU triggered injected conversion,
             * peripheral clock = half of system clock
             */
	        ADC_0.MCR.R	= 0x80020000;
            ADC_0.CTR[0].R = 0x00008606;
        }
        else {
            /* 
             * enable result overwriting,
             * enable CTU triggered injected conversion,
             * peripheral clock = system clock
             */
            ADC_0.MCR.R	= 0x80020100;
            ADC_0.CTR[0].R = 0x00008606;
        }
    }
    else {
        if (adcConfContainer[channel].peripheralFreq == ADC_HALF_SYS_FREQ) {
            /* 
             * enable result overwriting,
             * enable CTU triggered injected conversion,
             * peripheral clock = half of system clock
             */
	        ADC_1.MCR.R	= 0x80020000;
            ADC_1.CTR[0].R = 0x00008606;
        }
        else {
            /* 
             * enable result overwriting,
             * enable CTU triggered injected conversion,
             * peripheral clock = system clock
             */
            ADC_1.MCR.R	= 0x80020100;
            ADC_1.CTR[0].R = 0x00008606;
        }
    }

    return STD_OK;
}
/*
uint16 u8Result1[8];
static StdReturnType ReadADC1(uint8 u8GroupOfChannels)
{
    
    unsigned int returnCode = STD_OK;
    uint8 i=0U;
    for (i=0; i<u8GroupOfChannels; i++) { 
    	u8Result1[i] = ADC_0.CDR[i].B.CDATA;
    }
    
    return STD_OK;
}
static StdReturnType GetEndADC1(uint8 u8GetEOCMask)
{
    
    unsigned int returnCode = STD_OK;
    while (ADC0.CEOCFR0.R&u8GetEOCMask);
    
    return STD_OK;
}

uint16 u8Result2[8];
static StdReturnType ReadADC2(uint8 u8GroupOfChannels)
{
    
    unsigned int returnCode = STD_OK;
    uint8 i=0U;
    for (i=0; i<u8GroupOfChannels; i++) { 
    	u8Result2[i] = ADC_1.CDR[i].B.CDATA;
    }
    
    return STD_OK;
}/**/
StdReturnType InitADC(void)
{
    /* Return code from SSD pFlashErase function. */
    unsigned int returnCode = STD_OK;

    uint8 i=0U;

    for (i=0; i<ADC_MODULE_NUM; i++) {
        if (adcConfContainer[i].peripheralEn == ADC_ENABLED) {
            returnCode = InitADCInternal(i);
        }
    }

	/* Enable presampling for a set of given channels */
	//ADC0_set_presampled_channels(PRESAMPLE_CH0 | PRESAMPLE_CH1 | PRESAMPLE_CH2);

	/* Bypass sampling phase if required.
	 * If uncommented the sampled input is the 
	 * presampling voltage reference value */
	//ADC0_bypass_sampling_phase();

	/* Set the presampled reference value: HIGH or LOW */
	//ADC0_set_presampling_ref_value(PRESAMPLING_REF_LOW);

	//------------------------
	// ADC 0 Watchdog for ADC0 CH0,1,2
	//------------------------
	//ADC0_CH0_WD_Threshold_set();
	//ADC0_CH1_WD_Threshold_set();
	//ADC0_CH2_WD_Threshold_set();

	/* Set isr on threshold watchdog */
	//ADC0_WD_set_threshold_isr();

	/* Enable threshold watchdog */
	//ADC0_WD_enable_threshold();

    return STD_OK;
}

