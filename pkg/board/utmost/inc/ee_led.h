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
 * Support for LEDs on the UTMOST board.
 * Author: 2010,  Christian Grioli
 */


#ifndef __INCLUDE_UTMOST_BOARD_LED_H__
#define __INCLUDE_UTMOST_BOARD_LED_H__

#define LED_0 0x20

#define LED_1 0x40

#define LED_2 0x80

#define ALL_LEDS 0xE0

#define N_LED_0 0xDF

#define N_LED_1 0xBF

#define N_LED_2 0x7F

#define N_ALL_LEDS 0x0




__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {
	P4DIR|=0xE0;
	P4OUT=ALL_LEDS;
}
__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)   { P4OUT &=N_ALL_LEDS; }
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)  { P4OUT |= ALL_LEDS; }

__INLINE__ void __ALWAYS_INLINE__ EE_leds( EE_UINT8 data )  {
	P4OUT=data;
	}
 

__INLINE__ void __ALWAYS_INLINE__ EE_led_0_on(void)   { P4OUT &= N_LED_0;  }
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_off(void)  { P4OUT |= LED_0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)   { P4OUT &= N_LED_1;  }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void)  { P4OUT |= LED_1;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void)   { P4OUT &= N_LED_2;  }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void)  {P4OUT |= LED_2;}

__INLINE__ void __ALWAYS_INLINE__ EE_led_0_toggle(void)  { P4OUT^=LED_0;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_toggle(void)   { P4OUT^= LED_1;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_toggle(void)  {P4OUT^= LED_2;}
__INLINE__ void __ALWAYS_INLINE__ EE_leds_toggle(void)  {P4OUT^=ALL_LEDS;}



#endif
