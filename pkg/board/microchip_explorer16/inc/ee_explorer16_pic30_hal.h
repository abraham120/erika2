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
 * Author: 2011 Riccardo Schiavi
 * 
 */


#include "mcu/microchip_dspic/inc/ee_mcu.h"


/* Set AN23 as digital output */
#define EE_explorer16_AD_Confict_Solve() AD1PCFGHbits.PCFG23 = 1

/* enabling interrupt notifications on */
/* S3/RD6, S4/RD13, S4/RA7, and S6/RD7 */
#define EE_explorer16_cn_1_int_en()	CNEN1bits.CN15IE = 1	/* S3/RD6 */
#define EE_explorer16_cn_2_int_en()	CNEN2bits.CN19IE = 1	/* S4/RD13 */
#define EE_explorer16_cn_3_int_en()	CNEN2bits.CN23IE = 1	/* S5/RA7 */
#define EE_explorer16_cn_4_int_en()	CNEN2bits.CN16IE = 1	/* S6/RD7 */

/* Enable Change Notice module */
#define EE_explorer16_cn_pri()

/* Set Interrupt priority level and Subpriority level */
#define EE_explorer16_cn_pri_lev()

/* IRQ Handler  */
#define EE_EXPLORER16_IRQ_HANDLER_NAME	_CNInterrupt

/* reset ADC interrupt flag  */
#define EE_explorer16_int_reset()	IFS0bits.AD1IF = 0

/* AD setup for temperature acquisition */
#define EE_explorer16_temp_conf()	AD1CHS0 = 0x0005

/* AD setup for potentiometer acquisition */
#define EE_explorer16_pot_conf()	AD1CHS0 = 0x0004

/* Interrupt vector */
#define EE_EXPLORER16_INT_VECT		_ADC1Interrupt

/* Delay for LDC put command */
#define EE_LDC_COM_DELAY 200


/* ************************************************************************* */
/* Analog input */
/* ************************************************************************* */

#ifdef __USE_ANALOG__

#define AVDD 3300

extern EE_UINT16 EE_analog_raw_temperature;
extern EE_UINT16 EE_analog_raw_potentiometer;

__INLINE__ void __ALWAYS_INLINE__ EE_analog_init( void ) {
	
	/* Reset local variables */
	EE_analog_raw_temperature = 0;
	EE_analog_raw_potentiometer = 0;
	
	/* set configuration bits as ADC input */ 		
 	AD1PCFGLbits.PCFG4 = 0;         /* Temp Sensor  -> AN4/RB4 */
	AD1PCFGLbits.PCFG5 = 0;         /* Potentiometer -> AN5/RB5 */
 
	/* Set control register 1 */
	/* 12-bit, unsigned integer format, autoconvert, autosampling */
	AD1CON1 = 0x04E4;
	
	/* Set control register 2 */
	/* Vref = AVcc/AVdd, Scan Inputs */
	AD1CON2 = 0x0000;
	
	/* Set Samples and bit conversion time */
	/* AS = 16 Tad, Tad = 32 Tcy */
	AD1CON3 = 0x1020;
        	
	/* set channel scanning here for AN4 and AN5 */
	AD1CSSL = 0x0000;
	
	/* channel select AN4 and AN5 */
	AD1CHS0 = 0x0004;
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* enable ADC interrupts, disable this interrupt if the DMA is enabled */	  
	IEC0bits.AD1IE = 1;       

	/* turn on ADC module */
	AD1CON1bits.ADON = 1;          	
} 

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_volt( void ) { return ((long)EE_analog_raw_potentiometer * AVDD) >> 12;  }
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_temp( void ) { return EE_analog_raw_temperature >> 2; }

__INLINE__ void __ALWAYS_INLINE__ EE_analog_start( void ) { IEC0bits.AD1IE = 1; AD1CON1bits.ADON = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_analog_stop ( void ) { IEC0bits.AD1IE = 0; AD1CON1bits.ADON = 0; }

#endif
/* ************************************************************************* */


