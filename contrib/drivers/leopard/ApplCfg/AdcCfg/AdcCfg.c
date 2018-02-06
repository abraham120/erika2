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

#include "BswCommon.h"
#include "AdcCfg.h"
#include "adc.h"
#include "ctu.h"

#define MODULE_ID   (33)

void AdcOffsetEval ();
void AdcSelfTest ();

const AdcCommand adcCommandConfig[COMMAND_NUMBER] = {
    //                          command
    /* 0-th command*/          SAMPLE_CH0_CMD,
    /* 1-th command*/          SAMPLE_CH1_CMD,
    /* 2-th command*/          SAMPLE_CH2_CMD,
    /* 3-th command*/          SAMPLE_CH3_CMD,
    /* 4-th command*/          SAMPLE_CH4_CMD,
    /* 5-th command*/          SAMPLE_CH5_CMD,
    /* 6-th command*/          SAMPLE_CH6_CMD,
    /* 7-th command*/          SAMPLE_CH7_CMD,
    /* If you want to raise an isr at the end of ADC command sequence */
    /* 7-th command*/          // SAMPLE_CH7_CMD | RAISE_INT_CMD
    // ...
    /* 7-th command*/          DUMMY_CMD
};

const AdcConfType adcConfContainer[] = {
    ///                 ADC                     Peripheral                  list of
    //                  enabled/disabled        frequency                   ADC commands
    /* ADC_0 */         {ADC_ENABLED,           ADC_HALF_SYS_FREQ,          adcCommandConfig},
    /* ADC_1 */         {ADC_DISABLED,          DO_NOT_CARE,                NULL}
};
/// Evaluating offset value to subtract by acquisition value 
/// if the value is over a calibration level a warning and/or an alarm could be occur
/// the best value is 0, of course, but an electrical noise could be occur.
/// a suggestion is acquiring a enough number of sample and then computing an avarage value 
void AdcOffsetEval (void)
{
	
/*	if(AdcPollChannel(ADC__0,7)==ADC_POLLING_HIT){
				u16Result[0] = ADC_0.CDR[1].B.CDATA;
				u16Result[1] = ADC_0.CDR[2].B.CDATA;
				u16Result[2] = ADC_0.CDR[3].B.CDATA;
				u16Result[3] = ADC_0.CDR[4].B.CDATA;
				
		}/**/	
};
/// Testing good functionality of ADC peripheral  
/// if the value is over a calibration level a warning and/or an alarm could be occur	
void AdcSelfTest (void)
{
		
};
