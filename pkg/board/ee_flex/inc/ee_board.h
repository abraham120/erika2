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
 * Author: 2006 Mauro Marinoni
 * CVS: $Id: ee_board.h,v 1.27 2008/08/29 11:21:08 francesco Exp $
 */

#ifndef __INCLUDE_EE_FLEX_BOARD_H__
#define __INCLUDE_EE_FLEX_BOARD_H__

#include "mcu/microchip_dspic/inc/ee_mcu.h"

/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

#define EE_SYS_LED 0

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {
	/* set LED (LEDSYS/RB14) drive state low */
	LATBbits.LATB14 = 0;
	/* set LED pin (LEDSYS/RB14) as output */
	TRISBbits.TRISB14 = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_sys_init(void)  { EE_leds_init(); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_sys_on(void)   { LATBbits.LATB14 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_sys_off(void)  { LATBbits.LATB14 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_led_on(void)   { LATBbits.LATB14 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_off(void)  { LATBbits.LATB14 = 0; }

#endif

/* ######################################################## */

/* ************************************************************************* */
/* USB Communication - TODO!!! */
/* ************************************************************************* */

//#if defined __USE_USB__
//void EE_usb_init(void);
//EE_INT16 EE_usb_write(EE_UINT8 *buf, EE_UINT16 len);
//EE_INT16 EE_usb_read(EE_UINT8 *buf, EE_UINT16 len);
//#endif

#ifdef __USE_USB__
       #ifndef __USE_DEMOBOARD__
             #ifndef __USE_MOTIONBOARD__
                     #define __USE_MOTIONBOARD__
             #endif
       #endif
#endif // __USE_USB__


/* /\************************************************************************* */
/* Check if the Flex DemoBoard has been selected */
/* /\************************************************************************* */

#ifdef __USE_DEMOBOARD__
#include "board/ee_flex/inc/ee_flex_demoboard.h"
#endif // __USE_DEMOBOARD__


/* /\************************************************************************* */
/* Check if the Flex MotionBoard has been selected */
/* /\************************************************************************* */

#ifdef __USE_MOTIONBOARD__
#include "board/ee_flex/inc/ee_flex_motionboard.h"
#endif // __USE_MOTIONBOARD__




/* ************************************************************************* */
#endif
