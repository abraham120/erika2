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


#ifdef __ATMEGA128__
#include "mcu/atmel_atmega128/inc/ee_avr5def.S"
#endif

#ifdef __ATMEGA1281__
#include "mcu/atmel_atmega1281/inc/ee_avr5def.S"
#endif

#ifdef __ATMEGA__
#include <avr/io.h>
#endif

.global led_1_on
led_1_on: 
			in	r18,	DDRB
			ori	r18,	0x01
			out	DDRB,	r18	; data direction = out
			ret

.global led_2_on
led_2_on: 
			in	r18,	DDRB
			ori	r18,	0x02
			out	DDRB,	r18	; data direction = out
			ret

.global led_3_on
led_3_on: 
			in	r18,	DDRB
			ori	r18,	0x04
			out	DDRB,	r18	; data direction = out
			ret

.global led_4_on
led_4_on: 
			in	r18,	DDRB
			ori	r18,	0x08
			out	DDRB,	r18	; data direction = out
			ret

.global led_5_on
led_5_on: 
			in	r18,	DDRB
			ori	r18,	0x10
			out	DDRB,	r18	; data direction = out
			ret

.global led_6_on
led_6_on: 
			in	r18,	DDRB
			ori	r18,	0x20
			out	DDRB,	r18	; data direction = out
			ret

.global led_7_on
led_7_on: 
			in	r18,	DDRB
			ori	r18,	0x40
			out	DDRB,	r18	; data direction = out
			ret

.global led_8_on
led_8_on: 
			in	r18,	DDRB
			ori	r18,	0x80
			out	DDRB,	r18	; data direction = out
			ret

.global led_1_off
led_1_off:
			in	r18,	DDRB
			andi	r18,	0xFE
			out	DDRB,	r18
			ret

.global led_2_off
led_2_off:
			in	r18,	DDRB
			andi	r18,	0xFD
			out DDRB,r18
			ret

.global led_3_off
led_3_off:
			in	r18,	DDRB
			andi	r18,	0xFB
			out	DDRB,	r18
			ret

.global led_4_off
led_4_off:
			in	r18,	DDRB
			andi	r18,	0xF7
			out	DDRB,	r18
			ret

.global led_5_off
led_5_off:
			in	r18,	DDRB
			andi	r18,	0xEF
			out	DDRB,	r18
			ret

.global led_6_off
led_6_off:
			in	r18,	DDRB
			andi	r18,	0xDF
			out	DDRB,	r18
			ret

.global led_7_off
led_7_off:
			in	r18,	DDRB
			andi	r18,	0xBF
			out	DDRB,	r18
			ret

.global led_8_off
led_8_off:
			in	r18,	DDRB
			andi	r18,	0x7F
			out	DDRB,	r18
			ret
