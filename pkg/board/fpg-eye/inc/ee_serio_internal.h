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
	@file ee_serio_internal.h
	@brief Driver for the parallel/serial IO components of the FPGA+Camera board (private parts).
	@author Bernardo  Dal Seno
	@date 2010
*/

#ifndef __INCLUDE_FPGA_CAMERA_BOARD_SERIO_INTERNAL_H__
#define __INCLUDE_FPGA_CAMERA_BOARD_SERIO_INTERNAL_H__

#include <ee.h>
#include <mcu/mico32/inc/ee_gpio.h>
#include <system_conf.h>

/* Common stuff */
#ifdef SERPARIO_BASE_ADDRESS

typedef struct
{
    /* Register to read state of switches and button (RO) */
    volatile EE_UINT32 data_in;
    /* Register to control leds & transistors (R/W) */
    volatile EE_UINT32 data_out;
    /* Status register (R/W) */
    volatile EE_UINT32 status;
} SerParIO_t;

static SerParIO_t * const serpario = (SerParIO_t *)SERPARIO_BASE_ADDRESS;


/**
	@brief			This function reads the status of switches and button.
	@return			the status of switches and button (data_in register).	
*/
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_serio_read(void)
{
    return serpario->data_in;
}

/**
	@brief			This function writes data_out, the register to control leds & transistors.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_serio_write(EE_UINT32 data)
{
    serpario->data_out = data;
}

/**
	@brief			This function reads data_out, the register to control leds & transistors.
	@return			the status of leds & transistors (data_out register).
*/
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_serio_get_data_out(void)
{
    return serpario->data_out;
}

#define EE_SERIO_SYSTEM_LED 9
#define EE_SERIO_LED_COUNT (EE_LED_COUNT - 1)
#define EE_SERIO_ALL_LEDS ((1 << EE_SERIO_LED_COUNT) - 1)
#define EE_SERIO_LED_MASK(n) (1 << (n))

#define EE_SERIO_SWITCH_MASK(n) (1 << (n))

#define EE_SERIO_TRANSISTOR_MASK(n) (1 << ((n) + EE_SERIO_LED_COUNT))
#define EE_SERIO_ALL_TRANSISTORS (0x7f << EE_SERIO_LED_COUNT)
#else
#error Unsopported platform: no parallel/serial component found
#endif /* SERPARIO_BASE_ADDRESS */


/* Leds */

#ifdef __USE_LEDS__

#define EE_SERIO_GPIO_LED_BIT  0
#define EE_SERIO_GPIO_LED_MASK 1

/**
	@brief			This function controls the system led.
	@param s		desired status for the system led.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_set(EE_UREG s)
{
    EE_misc_gpio_write_bit_data(s, EE_SERIO_GPIO_LED_BIT);
}

/**
	@brief			This function reads the status of the system led.
	@return			1 if the system led is on, else 0.
*/
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_serio_system_led_get(void)
{
    return EE_misc_gpio_read_data_out() & EE_SERIO_GPIO_LED_MASK;
}

/**
	@brief			This function turns on the system led.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_on(void)
{
    EE_serio_system_led_set(1);
}

/**
	@brief			This function turns off the system led.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_off(void)
{
    EE_serio_system_led_set(0);
}

/**
	@brief			This function toggles the system led.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_serio_system_led_toggle(void)
{
    EE_serio_system_led_set (! EE_serio_system_led_get());
}


#endif /* __USE_LEDS__ */


#endif /* __INCLUDE_FPGA_CAMERA_BOARD_SERIO_INTERNAL_H__ */
