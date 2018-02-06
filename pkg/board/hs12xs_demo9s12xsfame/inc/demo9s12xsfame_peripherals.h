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


#ifndef __INCLUDE_S12XS_DEMOBOARD_H__
#define __INCLUDE_S12XS_DEMOBOARD_H__

#include "mcu/hs12xs/inc/ee_mcu.h"

#ifdef __DEMO9S12XSFAME__

/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

#define LED_0 0x01
#define LED_1 0x02
#define LED_2 0x04
#define LED_3 0x08

#define EE_leds_init() EE_demo9s12xsfame_leds_init()
#define EE_leds(f) EE_demo9s12xsfame_leds(f)
#define EE_led_0_on() EE_demo9s12xsfame_led_0_on()   
#define EE_led_0_off() EE_demo9s12xsfame_led_0_off()
#define EE_led_1_on() EE_demo9s12xsfame_led_1_on()  
#define EE_led_1_off() EE_demo9s12xsfame_led_1_off() 
#define EE_led_2_on() EE_demo9s12xsfame_led_2_on()  
#define EE_led_2_off() EE_demo9s12xsfame_led_2_off() 
#define EE_led_3_on() EE_demo9s12xsfame_led_3_on()  
#define EE_led_3_off() EE_demo9s12xsfame_led_3_off()  
#define EE_leds_on() EE_demo9s12xsfame_leds_on()   
#define EE_leds_off() EE_demo9s12xsfame_leds_off()  

/* EE_demo9s12xsfame_leds_init: demo9s12xsfame red leds initialization  */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_leds_init(void) {
	
	PORTA = (unsigned char)0x00;
	DDRA = (unsigned char)0x0F;		/* configured in output mode */
}

/* EE_leds: turn on a demo9s12xsfame red led */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_leds( EE_UINT8 data ) {

	PORTA = (EE_UINT8)(data & ((EE_UINT8)0x0F));
}

__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_0_on(void)   { PORTA |= 0x01; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_0_off(void)  { PORTA &= 0xFE; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_1_on(void)   { PORTA |= 0x02; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_1_off(void)  { PORTA &= 0xFD; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_2_on(void)   { PORTA |= 0x04; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_2_off(void)  { PORTA &= 0xFB; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_3_on(void)   { PORTA |= 0x08; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_led_3_off(void)  { PORTA &= 0xF7; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_leds_on(void)   { PORTA |= 0x0F; }
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_leds_off(void)  { PORTA &= 0xF0; }


#endif

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

#define BUTTON_0 0
#define BUTTON_1 1

#define EE_buttons_init(f,g) EE_demo9s12xsfame_buttons_init(f,g)
#define EE_buttons_close EE_demo9s12xsfame_buttons_close()
#define EE_buttons_disable_interrupts(f) EE_demo9s12xsfame_buttons_disable_interrupts(f)
#define EE_buttons_enable_interrupts(f) EE_demo9s12xsfame_buttons_enable_interrupts(f)
#define EE_buttons_clear_ISRflag(f) EE_demo9s12xsfame_buttons_clear_ISRflag(f)
#define EE_button_get_B0() EE_demo9s12xsfame_button_get_B0()
#define EE_button_get_B1() EE_demo9s12xsfame_button_get_B1()

extern volatile EE_UINT8 EE_buttons_initialized;

/* EE_buttons_init: demo9s12xsfame buttons configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_buttons_init( EE_UINT8 bx, EE_UINT8 prio ) {
	
	if(EE_buttons_initialized == 1)
		return;
	DDRP = (unsigned char)0x00;		/* configured in input mode */
	PIEP = (EE_UINT8)(bx+1);
	_asm("cli");
	INT_CFADDR = 0x8E;
	INT_CFDATA0 = prio;
	EE_buttons_initialized = 1;
}


/* EE_buttons_close: demo9s12xsfame buttons configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_buttons_close( void ) {
	
	if(EE_buttons_initialized == 0)
		return;
	PIEP = 0x00;
	EE_buttons_initialized = 0;
}

/* EE_demo9s12xsfame_buttons_disable_interrupts: demo9s12xsfame buttons configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_buttons_disable_interrupts( EE_UINT8 bx ) {
	EE_UINT8 x;
		x = (EE_UINT8)((EE_UINT8)1<<bx);
	x = (EE_UINT8)(~x);
	PIEP &= x;
}

/* EE_demo9s12xsfame_buttons_enable_interrupts: demo9s12xsfame buttons configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_buttons_enable_interrupts( EE_UINT8 bx ) {
	EE_UINT8 x;
		x = (EE_UINT8)((EE_UINT8)1<<bx);
	PIFP |= x;
  	PIEP |= x;
}

/* EE_demo9s12xsfame_buttons_enable_interrupts: demo9s12xsfame buttons configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_buttons_clear_ISRflag( EE_UINT8 bx ) {
	EE_UINT8 x;
		x = (EE_UINT8)((EE_UINT8)1<<bx);
	PIFP |= x;
}

/* EE_button_get_B0: get value of the button 0 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_demo9s12xsfame_button_get_B0( void ) {
	
	if (!(PTP&0x01))
		return 1;
	else
		return 0;
}

/* EE_button_get_B1: get value of the button 1 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_demo9s12xsfame_button_get_B1( void ) {
	
	if (!(PTP&0x02))
		return 1;
	else
		return 0;
}

#endif


/* /\************************************************************************* */
/*  Analog inputs */
/*  *************************************************************************\/ */

#if defined(__USE_POTENTIOMETER__) || defined(__USE_ADC__) || defined(__USE_LIGHT_SENSOR__)

#define EE_adc_init(f,g) EE_demo9s12xsfame_adc_init(f,g)
#define EE_adc_convert() EE_demo9s12xsfame_adc_convert()
#define EE_adc_getvalue(f) EE_demo9s12xsfame_adc_getvalue(f)
#define EE_adc_close() EE_demo9s12xsfame_adc_close()
#define EE_analog_get_light() EE_demo9s12xsfame_analog_get_light()
#define EE_analog_get_pot() EE_demo9s12xsfame_analog_get_pot()

#define AVDD 3.3
#define VREF 3.3
#define ATDRES_8BIT 0
#define ATDRES_10BIT 1
#define ATDRES_12BIT 2

extern volatile EE_UINT8 EE_adc_init;

/* EE_adc_init: ADC module configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_adc_init( unsigned char res, unsigned char numconvseq )
{
	/* Check if the ADC is initialized */
	if (EE_adc_init != 0) return;
	
	if(numconvseq >= 16)
		numconvseq = 0;

	/* Configures the ATD peripheral */
	ATD0CTL1 = (unsigned char)(0x10 + (res<<5));  /* 8 bit data resolution */
	ATD0CTL3 = (unsigned char)(0x03 + ((numconvseq & 0x0F)<<3));	/* Right justified data, 2 conversion sequence and non-FIFO mode */
	ATD0CTL4 = 0xE0; /* fBUS=2MHz, fATDCLK = 1 MHz (PRESCLAER = 0) Select 24 Sample Time */
	EE_adc_init = 1; /* set ADC as configured */
}

/* EE_adc_convert: to start conversion */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_adc_convert( void )
{
	ATD0CTL5 = 0x10; 
	while(!(ATD0STAT0 & 0x80));   
}

/* EE_adc_getvalue: to get a new sample of the channel adcch */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_demo9s12xsfame_adc_getvalue( unsigned int adcch )
{
	unsigned int val = 0;
	EE_demo9s12xsfame_adc_convert();
	val = *((&ATD0DR0)+adcch);
	return val>>8;  
}

/* EE_adc_close: close the ADC module */
__INLINE__ void __ALWAYS_INLINE__ EE_demo9s12xsfame_adc_close( void )
{
	/* set ADC as unconfigured */
	EE_adc_init = 0;
}

/* EE_analog_get_light: Get a new measure from the light sensor */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_demo9s12xsfame_analog_get_light( void )
{
	EE_adc_convert();
	/* Return conversion */
	return EE_demo9s12xsfame_adc_getvalue(1);
}

/* EE_analog_get_pot: Get a new measure from the potentiometer */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_demo9s12xsfame_analog_get_pot( void )
{
	EE_adc_convert();
	/* Return conversion */
	return EE_demo9s12xsfame_adc_getvalue(0);
	
}
#endif


#endif
#endif
