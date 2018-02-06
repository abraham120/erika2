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


#include "mcu/microchip_pic32/inc/ee_mcu.h"


/* Configure button pins for digital digita inputs */
#define EE_explorer16_AD_Confict_Solve() AD1PCFG = 0x00099000;

/* enabling interrupt notifications on S3/RD6, S4/RD13, and S6/RD7 */
/* the interrupt notification cannot be enabled on S5/RA7 */
#define EE_explorer16_cn_1_int_en() CNENbits.CNEN15 = 1; CNPUEbits.CNPUE15 = 1 /* S3/RD6  */
#define EE_explorer16_cn_2_int_en() CNENbits.CNEN19 = 1; CNPUEbits.CNPUE19 = 1 /* S4/RD13 */
#define EE_explorer16_cn_3_int_en() /* S5/RA7 could not be used as interrupt source */
#define EE_explorer16_cn_4_int_en() CNENbits.CNEN16 = 1; CNPUEbits.CNPUE16 = 1	/* S6/RD7  */

/* Enable Change Notice module */
#define EE_explorer16_cn_pri() CNCON = 0x8000

/* Set Interrupt priority level=5 and Subpriority level=3 */
#define EE_explorer16_cn_pri_lev() IPC6SET = 0x00170000;

/* IRQ Handler */
#define EE_EXPLORER16_IRQ_HANDLER_NAME	_CHANGE_NOTICE_VECTOR

/* reset ADC interrupt flag disable interrupts and stop convertion */
#define EE_explorer16_int_reset()	IFS1bits.AD1IF = 0; AD1CON1bits.SAMP=1; IEC1bits.AD1IE = 0

/* AD setup for temperature acquisition */
#define EE_explorer16_temp_conf()	AD1CHS = 0x00020000  /* AN2 */

/* AD setup for potentiometer acquisition */
#define EE_explorer16_pot_conf()	AD1CHS = 0x00040000 /* AN4 */

/* Interrupt vector */
#define EE_EXPLORER16_INT_VECT	_ADC_VECTOR

/* Delay for LDC put command */
#define EE_LDC_COM_DELAY 700


/* ************************************************************************* */
/* Analog input */
/* ************************************************************************* */

#ifdef __USE_ANALOG__

#define AVDD 3.300

extern EE_UINT16 EE_analog_raw_temperature;
extern EE_UINT16 EE_analog_raw_potentiometer;

__INLINE__ void __ALWAYS_INLINE__ EE_analog_init( void ) {

	/* Reset local variables */
	EE_analog_raw_temperature = 0;
	EE_analog_raw_potentiometer = 0;
	
	/* set configuration bits as ADC input */
	AD1PCFGbits.PCFG2 = 0;	/* Disable digital input on AN2 (potentiometer) */
	AD1PCFGbits.PCFG4 = 0;	/* Disable digital input on AN4 (TC1047A temp sensor) */
	
	AD1CHSbits.CH0SA = 2;	/* channel select AN2 */

	/* ********************** */
	/* Set control register 1 */
	/* ********************** */
	AD1CON1bits.ON = 0;		/* ADC is off */
	AD1CON1bits.FORM = 0;		/* Data output is a 16-bit integer */
	AD1CON1bits.SSRC = 0b111;	/* Internal counter ends sampling and starts conversion */
	AD1CON1bits.CLRASAM =0;		/* Stop convertion when first AD is generated */
	AD1CON1bits.ASAM = 1;		/*no autosample */
	
	/* ********************** */
	/* Set control register 2 */
	/* ********************** */
	AD1CON2bits.VCFG = 0;	/* AVdd AVss */
	AD1CON2bits.BUFM = 0;	/* Buffer configured as one 16-word buffer */
	AD1CON2bits.SMPI = 0;	/* Raise interrupt after 3 sample */

	/* ********************** */
	/* Set control register 2 */
	/* ********************** */
	AD1CON3bits.SAMC = 16;	/* 16 Tad */
       	AD1CON3bits.ADCS = 3;	/* ADC convertion clock is 3 */
       	AD1CON3bits.ADRC = 0; 	/* Clock derived from Peripheral Bus Clock */

	AD1CSSL = 0x0000;	/* No inputs are scanned */
	
	IFS1bits.AD1IF = 0;	/* reset ADC interrupt flag */

	/* Configure ADC interrupt priority bits */
	IPC6bits.AD1IP = 5;	/* Priority level is 5 */
	IPC6bits.AD1IS = 3;	/* Subpriority level is 3 */

	IEC1bits.AD1IE = 1;	/* enable ADC interrupts */	  

	AD1CON1SET = 0x8000;	/* Turn on ADC module */

	AD1CON1bits.SAMP=1;	/* Start sampling the input */
} 

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_volt( void ) { return ((long)EE_analog_raw_potentiometer )*AVDD;}
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_temp( void ) { return EE_analog_raw_temperature;}

__INLINE__ void __ALWAYS_INLINE__ EE_analog_start( void ) { IEC1SET = 0x0002; AD1CON1SET = 0x0002; }
__INLINE__ void __ALWAYS_INLINE__ EE_analog_stop ( void ) { IEC1SET = 0x0000; AD1CON1CLR = 0x0002; }

#endif
/* ************************************************************************* */
