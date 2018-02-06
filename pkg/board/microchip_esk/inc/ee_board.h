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
 * Author: 2014 Angelo Compagnucci <angelo.compagnucci@gmail.com>
 * 
 */

#ifndef __INCLUDE_MICROCHIP_esk_BOARD_H__
#define __INCLUDE_MICROCHIP_esk_BOARD_H__


#if defined __PIC32__
#include "board/microchip_esk/inc/ee_esk_pic32_hal.h"
#else
#error "Unsupported pic on esk board"
#endif


/* ************************************************************************* */
/* Buttons */
/* ************************************************************************* */

#ifdef __USE_BUTTONS__

extern void (*EE_button_callback)(void);
extern EE_UINT8 EE_button_mask;

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init( void(*isr_callback)(void), EE_UINT8 mask ) {
	/* set BUTTON pins (S0/RD6-S1/RD7-S2/RD13) as inputs */
	TRISDbits.TRISD6  = 1;
	TRISDbits.TRISD7  = 1;
	TRISDbits.TRISD13 = 1;

	/* Solve conflict againd AD module */
 	EE_esk_AD_Confict_Solve();

	/* Enable Interrupt */
	if (isr_callback != NULL) {
	  /* Enable Change Notice module */
	  EE_esk_cn_pri();

	  if (mask & 0x01)
	    EE_esk_cn_1_int_en();	/* S0/RD6 */
	  if (mask & 0x02)
	    EE_esk_cn_2_int_en();	/* S1/RD7 */
	  if (mask & 0x04)
	    EE_esk_cn_4_int_en();	/* S2/RD13 */

	  /* Set interrupt priority Level and Sublevel */
	  EE_esk_cn_pri_lev();

	  IFS1bits.CNIF = 1;
	  IEC1bits.CNIE = 1;
	}

	/* Save callback */
	EE_button_callback = isr_callback;	
} 

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S1( void ) {
	if (PORTDbits.RD6)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S2( void ) {
	if (PORTDbits.RD7)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S3( void ) {
	if (PORTDbits.RD13)
		return 0;
	else
		return 1;
}

#endif


/* ************************************************************************* */
/*  LEDs */
/* ************************************************************************* */

#ifdef __USE_LEDS__

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {
  /* set LEDs (D0-D2) drive state low */
  LATD &= 0xFFF8; 
  /* set LED pins (D0-D2) as outputs */
  TRISD &= 0xFFF8;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)   { LATD |= 0x0007; }
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)  { LATD &= 0xFFF8; }

__INLINE__ void __ALWAYS_INLINE__ EE_leds( EE_UINT8 data )  { LATD &= 0xFFF8; LATD |= data; }

__INLINE__ void __ALWAYS_INLINE__ EE_led_0_on(void)   { LATDbits.LATD0 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_off(void)  { LATDbits.LATD0 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)   { LATDbits.LATD1 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void)  { LATDbits.LATD1 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void)   { LATDbits.LATD2 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void)  { LATDbits.LATD2 = 0; }

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_led_is_on(EE_UINT8 led)   { return PORTD & (1 << led); }

#endif

#endif
