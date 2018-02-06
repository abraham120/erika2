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


#include "ee_internal.h"

#include "cpu/pic30/inc/ee_irqstub.h"

/* /\************************************************************************* */
/*  Analog input */
/*  *************************************************************************\/ */

#if defined(__USE_BATTERY_MONITOR__) || defined(__USE_TEMPERATURE__) || \
	defined(__USE_LIGHT__) || defined(__USE_ACCELEROMETER__) \
	|| defined(__USE_ANALOG_IN__)
EE_UINT8 EE_adc_init = 0;
#endif

#ifdef __USE_ACCELEROMETER__
EE_UINT8 EE_accelerometer_g = 6;
#endif
/* ************************************************************************* */

#ifdef __USE_MRF24J40MA__

void (*EE_miniflex_radio_mrf24j40_callback)(void);

ISR2(_INT0Interrupt)
{
	if(IEC0bits.INT0IE && IFS0bits.INT0IF) { //if(RFIE && RFIF)
		// Execute callback function
		IFS0bits.INT0IF = 0; // clear the interrupt flag
		if (EE_miniflex_radio_mrf24j40_callback != NULL)
			EE_miniflex_radio_mrf24j40_callback();
	}
}

#endif
