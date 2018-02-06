/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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
 * Author: 2005 Antonio Romano
 * 	   2014 Giuseppe Serano
 */

#ifndef __INCLUDE_STK_BOARD_H__
#define __INCLUDE_STK_BOARD_H__


#ifdef __ATMEGA128__
#include "mcu/atmel_atmega128/inc/ee_mcu.h"
#endif

#ifdef __ATMEGA1281__
#include "mcu/atmel_atmega1281/inc/ee_mcu.h"
#endif

#ifdef __ATMEGA__
#include "mcu/atmel_atmega/inc/ee_mcu.h"
#endif

/*************************************************************************
 Button
 *************************************************************************/

/* the button is connected to EXT0 */

#ifdef __BUTTON_USED__

/* Initialize the EXT0 interrupt source (button)  */
__INLINE__ void EE_button_init(void)
{
    
}

#endif




/*************************************************************************
 LEDs
 *************************************************************************/


#ifdef __LEDS_USED__

/* On stk500, the LEDs are connected through IO Port B */

__INLINE__ void EE_led_4_on(void) {
led_4_on();
}

__INLINE__ void EE_led_8_on(void) {
led_8_on();
}

__INLINE__ void EE_led_3_on(void) {
led_3_on();
}
__INLINE__ void EE_led_2_on(void) {
led_2_on();
}
__INLINE__ void EE_led_1_on(void) {
led_1_on();
}

__INLINE__ void EE_led_5_on(void) {
led_5_on();
}

__INLINE__ void EE_led_6_on(void) {
led_6_on();
}
__INLINE__ void EE_led_7_on(void) {
led_7_on();
}





__INLINE__ void EE_led_5_off(void) {
led_5_off();
}
__INLINE__ void EE_led_6_off(void) {
led_6_off();
}
__INLINE__ void EE_led_7_off(void) {
led_7_off();
}


__INLINE__ void EE_led_4_off(void) {
led_4_off();
}
__INLINE__ void EE_led_3_off(void) {
led_3_off();
}
__INLINE__ void EE_led_2_off(void) {
led_2_off();
}
__INLINE__ void EE_led_1_off(void) {
led_1_off();
}

__INLINE__ void EE_led_8_off(void) {
led_8_off();
}
__INLINE__ void EE_leds_init(void) {}

#endif /* __LEDS_USED__ */



#endif
