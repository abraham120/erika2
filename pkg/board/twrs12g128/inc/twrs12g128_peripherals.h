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

/** 
* \file twrs12g128_peripherals.h
* \brief Peripheral drivers for the TWRS12G128 evaluation board.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/

#ifndef __INCLUDE_S12G_DEMOBOARD_H__
#define __INCLUDE_S12G_DEMOBOARD_H__

#ifdef __TWRS12G128__

/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

#define LED_1 0x01
#define LED_2 0x02
#define LED_3 0x04
#define LED_4 0x08

/**
 * \brief		Leds initialization
*/
#define EE_leds_init() EE_twrs12g128_leds_init()

/**
 * \brief		Turn on/off the leds
*/
#define EE_leds(f) EE_twrs12g128_leds(f)

/**
 * \brief		Led 1 on
*/
#define EE_led_1_on() EE_twrs12g128_led_1_on()  

/**
 * \brief		Led 1 off
*/
#define EE_led_1_off() EE_twrs12g128_led_1_off() 

/**
 * \brief		Led 2 on
*/
#define EE_led_2_on() EE_twrs12g128_led_2_on()  

/**
 * \brief		Led 2 off
*/
#define EE_led_2_off() EE_twrs12g128_led_2_off() 

/**
 * \brief		Led 3 on
*/
#define EE_led_3_on() EE_twrs12g128_led_3_on()  

/**
 * \brief		Led 3 off
*/
#define EE_led_3_off() EE_twrs12g128_led_3_off()  

/**
 * \brief		Led 4 on
*/
#define EE_led_4_on() EE_twrs12g128_led_4_on()   

/**
 * \brief		Led 4 off
*/
#define EE_led_4_off() EE_twrs12g128_led_4_off()

/**
 * \brief		Led 1 toggle on/off
*/
#define EE_led_1_toggle() EE_twrs12g128_led_1_toggle()

/**
 * \brief		Led 2 toggle on/off
*/
#define EE_led_2_toggle() EE_twrs12g128_led_2_toggle()

/**
 * \brief		Led 3 toggle on/off
*/
#define EE_led_3_toggle() EE_twrs12g128_led_3_toggle()

/**
 * \brief		Led 4 toggle on/off
*/
#define EE_led_4_toggle() EE_twrs12g128_led_4_toggle()

/**
 * \brief		Leds on
*/
#define EE_leds_on() EE_twrs12g128_leds_on()   

/**
 * \brief		Leds off
*/
#define EE_leds_off() EE_twrs12g128_leds_off()  

/* EE_twrs12g128_leds_init: twrs12g128 red leds initialization  */
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_leds_init(void) {
	PTT = 0xF0;			//	init PTT[7:4] output
	DDRT = 0xF0;		//	PTT[7:4] output others input
}

/* EE_leds: turn on a twrs12g128 red led */
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_leds( EE_UINT8 data ) {
	PTT = ((~data) << 4);
}

__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_1_on(void)   { PTT_PTT4 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_1_off(void)  { PTT_PTT4 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_2_on(void)   { PTT_PTT5 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_2_off(void)  { PTT_PTT5 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_3_on(void)   { PTT_PTT6 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_3_off(void)  { PTT_PTT6 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_4_on(void)   { PTT_PTT7 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_4_off(void)  { PTT_PTT7 = 1; }

__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_1_toggle(void)   { PTT_PTT4 ^= 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_2_toggle(void)   { PTT_PTT5 ^= 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_3_toggle(void)   { PTT_PTT6 ^= 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_led_4_toggle(void)   { PTT_PTT7 ^= 1; }

__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_leds_on(void)    { PTT &= 0x0F; }
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_leds_off(void)   { PTT |= 0xF0; }


#endif

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

#define BUTTON_1 0x10
#define BUTTON_2 0x20
#define BUTTON_3 0x40
#define BUTTON_4 0x80

/**
 * \brief		Buttons initialization
 * \param f		Use a combination of this macros: BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4
*/
#define EE_buttons_init(f) EE_twrs12g128_buttons_init(f)

/**
 * \brief		Buttons disabled
*/
#define EE_buttons_close() EE_twrs12g128_buttons_close()

/**
 * \brief		Get the status of Button 1
*/
#define EE_button_get_B1() EE_twrs12g128_button_get_B1()

/**
 * \brief		Get the status of Button 2
*/
#define EE_button_get_B2() EE_twrs12g128_button_get_B2()

/**
 * \brief		Get the status of Button 3
*/
#define EE_button_get_B3() EE_twrs12g128_button_get_B3()

/**
 * \brief		Get the status of Button 4
*/
#define EE_button_get_B4() EE_twrs12g128_button_get_B4()

extern volatile EE_UINT8 EE_buttons_initialized;

/* EE_buttons_init: twrs12g128 buttons configuration */
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_buttons_init(EE_UINT8 bx) {
	
	if(EE_buttons_initialized == 1)
		return;
	ATDDIEN |= bx;					// enable sw input on PAD[7:4]   
	//PER0AD = 0x80;				// enable PU on PAD15 to enable COM
	PER1AD |= bx;					// enable PBSW pulls
	PPS1AD = 0x00;					// pull-ups applied
	EE_buttons_initialized = 1;
}


/* EE_buttons_close: twrs12g128 buttons disabled */
__INLINE__ void __ALWAYS_INLINE__ EE_twrs12g128_buttons_close( void ) {
	
	if(EE_buttons_initialized == 0)
		return;
	ATDDIEN &= 0x0F;				// disable sw input on PAD[7:4]   
	EE_buttons_initialized = 0;
}

/* EE_button_get_B0: get value of the button 0 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_twrs12g128_button_get_B1( void ) {
	return ( !(PT1AD & BUTTON_1) ) ? 1 : 0; 
}

/* EE_button_get_B1: get value of the button 1 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_twrs12g128_button_get_B2( void ) {
	return ( !(PT1AD & BUTTON_2) ) ? 1 : 0; 
}

/* EE_button_get_B2: get value of the button 2 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_twrs12g128_button_get_B3( void ) {
	return ( !(PT1AD & BUTTON_3) ) ? 1 : 0; 
}

/* EE_button_get_B3: get value of the button 3 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_twrs12g128_button_get_B4( void ) {
	return ( !(PT1AD & BUTTON_4) ) ? 1 : 0; 
}

#endif

#endif /* __TWRS12G128__ */

#endif /* __INCLUDE_S12G_DEMOBOARD_H__ */
