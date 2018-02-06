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
#define MODULE_ID   (11)

#include "BswCommon.h"
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>
#include "adc.h"
#include "eecfg.h"
#include <ee.h>

void WD_isr_handler(void);

/* Threashold overcome isr handler: it only manages the fault coming from CH0 */
ISR2(WD_isr_handler)
{
	/* ADC0: hight threashold fault on CH0 */
	//ADC0_WTISR = 0x00000002;
	ADC_0.WTISR.B.WDG0H = 1U;

	//ADC0_AWORR0 = 0x00000002;
	ADC_0.AWORR0.B.AWOR_CH0 = 1U;

	/* Adjust threshold for ADC0: uncomment if required */
	//ADC_0.THRHLR0.B.THRH = 0x000007FF;
	//ADC_0.THRHLR0.B.THRL = 0x00000000;

	/* switch LED2 on to warn about the watchdog
	 * threshold exception on CH0 */
	//SIU.GPDO[52].R = 0;
}

