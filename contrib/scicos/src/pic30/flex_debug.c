/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
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
	@file flex_debug.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

__INLINE__ void __ALWAYS_INLINE__ EE_debugs_on(void)  { LATB |= 0x003C; }
__INLINE__ void __ALWAYS_INLINE__ EE_debugs_off(void) { LATB &= 0xFFC3; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_1_on(void)  { LATBbits.LATB2 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_1_off(void) { LATBbits.LATB2 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_2_on(void)  { LATBbits.LATB3 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_2_off(void) { LATBbits.LATB3 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_3_on(void)  { LATBbits.LATB4 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_3_off(void) { LATBbits.LATB4 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_debug_4_on(void)  { LATBbits.LATB5 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_debug_4_off(void) { LATBbits.LATB5 = 0; }

void debug_init(scicos_block *block)
{
	/* set LEDs state low */
	LATBbits.LATB2 = 0; 
	LATBbits.LATB3 = 0; 
	LATBbits.LATB4 = 0; 
	LATBbits.LATB5 = 0; 
	
	/* set LEDs pins as outputs */
	TRISBbits.TRISB2 = 0; 
	TRISBbits.TRISB3 = 0; 
	TRISBbits.TRISB4 = 0; 
	TRISBbits.TRISB5 = 0; 
}
