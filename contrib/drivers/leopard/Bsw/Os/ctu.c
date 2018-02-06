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

#include "ctu.h"
#include "AdcCfg.h"

#define MODULE_ID   (16)

void InitCTU(void)
{
    uint8 i=0U;

	/* FE: Clear CTUIFR */
	CTU_0.CTUIFR.R = 0x05FF;

	/* Enable input */
	CTU_0.TGSISR.R              = 0x0400; /* Enable PWM A0 rising edge trigger; I1_RE*/

	/* Compare registers */
	CTU_0.TCR[0].R              = 0x0000; /* For triggering dual conversion on ADC0-CH0 and ADC1-CH0 
	//				       * determines delay between external trigger and triggering ADC sequence */

	/* High value just to prevent from comparator matching */
	//CTU_0.TCR[1].R              = 0xFFFF;
	//CTU_0.TCR[2].R              = 0xFFFF;
	//CTU_0.TCR[3].R              = 0xFFFF;
	//CTU_0.TCR[4].R              = 0xFFFF;
	//CTU_0.TCR[5].R              = 0xFFFF;
	//CTU_0.TCR[6].R              = 0xFFFF;
	//CTU_0.TCR[7].R              = 0xFFFF;

    for (i=1; i<CHANNEL_TO_SAMPLE; i++) {
        CTU_0.TCR[i].R = 0xFFFF;
    }

	/* Counter */
	CTU_0.TGSCCR.R              = CTU_COUNTER_VALUE;
	CTU_0.TGSCRR.R              = 0x0000;
	CTU_0.TGSCR.R               = 0x0000;

	/* Enable triggers */
	CTU_0.THCR1.R               = 0x00000061; /* Enable Triger 0 and set to ADC */

	/* Set ADC messages */
	//CTU_0.CLR[0].R              = SAMPLE_CH0_CMD;  /* Command 0 - first command in command sequence,  
	//					* single conversion mode on ADC0-CH0,
    //						* issue interrupt after conversion */

	//CTU_0.CLR[1].R              = SAMPLE_CH1_CMD;
	//CTU_0.CLR[2].R              = SAMPLE_CH2_CMD;
	//CTU_0.CLR[3].R              = SAMPLE_CH3_CMD;
	//CTU_0.CLR[4].R              = SAMPLE_CH4_CMD;
	//CTU_0.CLR[5].R              = SAMPLE_CH5_CMD;
	//CTU_0.CLR[6].R              = SAMPLE_CH6_CMD;
    //CTU_0.CLR[7].R              = SAMPLE_CH7_CMD;
    // Use the following if you need to raise the ADC_I interrupt
    // immediately after the acquisition from channel 7. This also
    // requires that the user defines the isr handler.
	//CTU_0.CLR[7].R              = SAMPLE_CH7_CMD | RAISE_INT_CMD;

    for (i=0; i<COMMAND_NUMBER; i++) {
        CTU_0.CLR[i].R = (uint16)adcConfContainer[0].adcCommandConfigPtr[i];
    }

	/* Enable isr for Trigger 0 occurrence */
	CTU_0.CTUIR.B.T0_I  = 0x1;

	CTU_0.CTUCR.R       = 0x0003; /* General reload and TGS input selection reload */
}

