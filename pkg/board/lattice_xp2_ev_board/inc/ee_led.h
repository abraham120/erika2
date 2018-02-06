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
 * Support for LEDs on the Lattice standard XP2 evalutation board
 * Author: 2010,  Bernardo  Dal Seno
 */

#ifndef __INCLUDE_LATTICE_XP2_EVBOARD_LED_H__
#define __INCLUDE_LATTICE_XP2_EVBOARD_LED_H__

#include <mcu/mico32/inc/ee_gpio.h>
#include <system_conf.h>

/* 8 leds */

__INLINE__ void __ALWAYS_INLINE__ EE_led_set_all(EE_INT32 state)
{
    EE_led_write_data(~state);
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_all_off(void)
{
    EE_led_set_all(0);
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_all_on(void)
{
    EE_led_set_all(~0);
}

__INLINE__ void  __ALWAYS_INLINE__ EE_led_init(void)
{
    EE_led_all_off();
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_on(EE_UREG n)
{
    EE_led_write_bit_data(0,n);
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_off(EE_UREG n)
{
    EE_led_write_bit_data(1,n);
}

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_led_get(EE_UREG n)
{
    return ! (EE_led_read_data_out() & (1 << n));
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_toggle(EE_UREG n)
{
    if (EE_led_get(n))
        EE_led_off(n);
    else
        EE_led_on(n);
}


/* 7-segment led */

#define DISP_DASH       16

__INLINE__ void  __ALWAYS_INLINE__ EE_led_init_display(void)
{
    EE_num_led_write_data(~0);
}

/**
 * @param num  A number between 0 and 15, or DISP_DASH
 */
void EE_led_display(EE_UREG num);

#endif /* __INCLUDE_LATTICE_XP2_EVBOARD_LED_H__ */
