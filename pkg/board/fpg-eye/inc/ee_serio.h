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
 
/** 
	@file ee_serio.h
	@brief Driver for the parallel/serial IO components of the FPGA+Camera board.
	@author Bernardo  Dal Seno
	@date 2010
*/


#ifndef __INCLUDE_FPGA_CAMERA_BOARD_SERIO_H__
#define __INCLUDE_FPGA_CAMERA_BOARD_SERIO_H__

#define EE_LED_COUNT 10

#define EE_TRANSISTOR_DRAM      0
#define EE_TRANSISTOR_LCD       1
#define EE_TRANSISTOR_FLASH     2
#define EE_TRANSISTOR_SRAM      3
#define EE_TRANSISTOR_CAMERA    4
#define EE_TRANSISTOR_SWITCHES  5
#define EE_TRANSISTOR_EXT_SPI   6

#include "ee_serio_internal.h"

/* Leds */

#ifdef __USE_LEDS__

/**
	@brief			This function turns on a led of the XP2-CAMERA board. 
	@param n		ID number of the led
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_led_on(EE_UREG n)
{
    if (n == EE_SERIO_SYSTEM_LED)
        EE_serio_system_led_on();
    else
        EE_serio_write(EE_serio_get_data_out() | EE_SERIO_LED_MASK(n));
}

/**
	@brief			This function turns off a led of the XP2-CAMERA board. 
	@param n		ID number of the led
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_led_off(EE_UREG n)
{
    if (n == EE_SERIO_SYSTEM_LED)
        EE_serio_system_led_off();
    else
        EE_serio_write(EE_serio_get_data_out() & ~EE_SERIO_LED_MASK(n));
}

/**
	@brief			This function toggles a led of the XP2-CAMERA board. 
	@param n		ID number of the led
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_led_toggle(EE_UREG n)
{
    if (n == EE_SERIO_SYSTEM_LED)
        EE_serio_system_led_toggle();
    else
        EE_serio_write(EE_serio_get_data_out() ^ EE_SERIO_LED_MASK(n));
}

/**
	@brief			This function sets the state of the leds of the XP2-CAMERA board.
	@param state	Bitmap of the new led state
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_led_set_all(EE_UINT32 state)
{
    EE_UINT32 old = EE_serio_get_data_out();
    EE_serio_write((old & ~EE_SERIO_ALL_LEDS) | (state & EE_SERIO_ALL_LEDS));
    EE_serio_system_led_set(state & (1 << EE_SERIO_SYSTEM_LED));
}

/**
	@brief			This function gets the state of the leds of the XP2-CAMERA board.
	@return 		the state of the leds
*/	
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_led_get_all(void)
{
    EE_UINT32 state = EE_serio_get_data_out() & EE_SERIO_ALL_LEDS;
    if (EE_serio_system_led_get())
        state |= (1 << EE_SERIO_SYSTEM_LED);
    return state;
}

/**
	@brief			This function turns off all the leds of the XP2-CAMERA board.
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_led_all_off(void)
{
    EE_led_set_all(0);
    EE_serio_system_led_off();
}

/**
	@brief			This function turns on all the leds of the XP2-CAMERA board.
*/	
__INLINE__ void __ALWAYS_INLINE__ EE_led_all_on(void)
{
    EE_led_set_all(EE_SERIO_ALL_LEDS);
    EE_serio_system_led_on();
}

/**
	@brief			This function toggles all the leds of the XP2-CAMERA board.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_led_all_toggle(void)
{
    EE_serio_write(EE_serio_get_data_out() ^ EE_SERIO_ALL_LEDS);
    EE_serio_system_led_toggle();
}

/**
	@brief			This function initializes the led driver and turns off all the leds.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_led_init(void)
{
    EE_led_all_off();
}

#endif /* __USE_LEDS__ */


/* Switches & button */

#ifdef __USE_SWITCHES__
/**
	@brief			This function reads all the switches of the XP2-CAMERA board.
	@return			the state of the switches
*/
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_switch_read_all(void)
{
    return EE_serio_read();
}

/**
	@brief			This function reads a particular switch of the XP2-CAMERA board.
	@param n 		the number of the switch to read			
	@return			the status of the switches
*/
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_switch_read(EE_UREG n)
{
    return (EE_serio_read() & EE_SERIO_SWITCH_MASK(n)) != 0;
}

#endif /* __USE_SWITCHES__ */


/* Transistors */

#ifdef __USE_TRANSISTORS__

/* Note: Transistors are controlled with negative logic, with the exception of the
 *  one powering the switch array. */

/**
	@brief			This function turns on a transistor of the XP2-CAMERA board.
	@param n 		the number of the transistor to turn on			
*/
__INLINE__ void __ALWAYS_INLINE__ EE_transistor_on(EE_UREG n)
{
    if (n != EE_TRANSISTOR_SWITCHES)
        EE_serio_write(EE_serio_get_data_out() & ~EE_SERIO_TRANSISTOR_MASK(n));
    else
        EE_serio_write(EE_serio_get_data_out() | EE_SERIO_TRANSISTOR_MASK(n));
}

/**
	@brief			This function turns off a transistor of the XP2-CAMERA board.
	@param n 		the number of the transistor to turn off			
*/
__INLINE__ void __ALWAYS_INLINE__ EE_transistor_off(EE_UREG n)
{
    if (n != EE_TRANSISTOR_SWITCHES)
        EE_serio_write(EE_serio_get_data_out() | EE_SERIO_TRANSISTOR_MASK(n));
    else
        EE_serio_write(EE_serio_get_data_out() & ~EE_SERIO_TRANSISTOR_MASK(n));
}

/**
	@brief			This function reads a transistor state of the XP2-CAMERA board.
	@param n 		the number of the transistor to read	
	@return			the state of the transistor	
*/
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_transistor_read(EE_UREG n)
{
    unsigned sw;
    sw = EE_serio_get_data_out() & EE_SERIO_TRANSISTOR_MASK(n);
    if (n != EE_TRANSISTOR_SWITCHES)
        return sw == 0;
    else
        return sw == 1;
}

/**
	@brief			This function turns on all the transistors of the XP2-CAMERA board.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_transistor_all_on(void)
{
    EE_serio_write((EE_serio_get_data_out() & ~EE_SERIO_ALL_TRANSISTORS)
        | EE_SERIO_TRANSISTOR_MASK(EE_TRANSISTOR_SWITCHES));
}

/**
	@brief			This function turns off all the transistors of the XP2-CAMERA board.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_transistor_all_off(void)
{
    EE_serio_write((EE_serio_get_data_out() | EE_SERIO_ALL_TRANSISTORS)
        & ~EE_SERIO_TRANSISTOR_MASK(EE_TRANSISTOR_SWITCHES));
}

#endif /* __USE_TRANSISTORS__ */

#endif /* __INCLUDE_FPGA_CAMERA_BOARD_SERIO_H__ */
