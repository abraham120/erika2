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
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>
#include "FasterLoop.h"
#include "adc.h"
#include "pwm.h"
#include "CanDrv.h"

volatile uint32 Result;	/* Expressed as ADC measure */
uint32 FinalResult;	/* Expressed in uVolt */

/* RTOS macro to declare ISR1 customized routines */
void TRIGGER_isr_handler(void);

ISR1(TRIGGER_isr_handler)
{
    /* Loop here till ADC0 ch0 is ready to be read */
    while (AdcPollChannel(ADC__0, 0) != ADC_POLLING_HIT)
        ;

    /*
     * Read data from ADC0 ch0 
     * notice that once you read this data
     * the VALID bit (ADC_0.CDR[0].B.VALID) becomes NOT_VALID (becomes 0)
     */
    Result = ADC_0.CDR[0].B.CDATA;

    FinalResult = (uint16) ((MAX_VOLTAGE)*Result/MAX_ADC_VALUE);

	if(FinalResult > MAX_VOLTAGE/2) {
		/* If the input voltage is greater then MAX_VOLTAGE/2
		 * reduces PWM0A to 25% by moving falling edge back
		 */
		PWM0_A0_load_new_falling_edge((uint16)(PWM_MODULO));
		PWM0_A1_load_new_falling_edge((uint16)(MIN_ADC_VALUE));
	}
	else {
		/* If the input voltage is less then MAX_VOLTAGE/2
		 * increments PWM0A to 75% by moving falling edge ahead
		 */
		PWM0_A0_load_new_falling_edge((uint16)(PWMA_FALLING_EDGE));
		PWM0_A1_load_new_falling_edge((uint16)(PWMA_FALLING_EDGE));
	}

	/* update PWM0A falling edge position based on ADC0 ch0 input value  */
	FLEXPWM_0.MCTRL.B.LDOK = PWM0_A0_LOAD | PWM0_A1_LOAD | PWM0_A2_LOAD;

	CTU_0.CTUCR.B.GRE  = 1;		/* CTU General Reload Enable */

	CTU_0.CTUIFR.B.T0_I = 0x1; 	/* Trigger 0 ISR flag clear */
}

