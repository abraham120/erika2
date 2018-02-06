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
* \file ee_pit.h
* \brief PIT driver, Erika HCS12 mcu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/

#ifdef __USE_PIT__

#ifndef __INCLUDE_FREESCALE_S12XS_PIT_H__
#define __INCLUDE_FREESCALE_S12XS_PIT_H__

/* Include a file with the registers of the s12 micro-controller */ 
#include "mcu/hs12xs/inc/ee_mcuregs.h"

extern volatile EE_UINT8 EE_pit0_initialized;

/**
 * \brief				This function is used to initialize the Periodic Interrupt timer.
 * \param pitmtld0		Value for the register PITMTLD0 (see manaul for furher info).
 * \param pitld0		Value for the register PITLD0 (see manaul for furher info).
 * \param pitld0		Interrupt priority saved in INT_CFDATA0 (see manaul for furher info).
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_pit0_init( unsigned char pitmtld0, unsigned char pitld0, unsigned char prio ) {
	if (EE_pit0_initialized==1) {
		return;
	}
	PITCFLMT      = 0x00;        /* PIT control micro timer register */
	PITFLT        = 0x00;        /* PIT force load timer register */
	PITCE         = 0x01;        /* PIT channel enable register */
	PITMUX        = 0x00;        /* PIT multiplex register */
	PITINTE       = 0x01;        /* PIT interrupt enable register */
	PITTF         = 0x01;        /* PIT time-out flag register */
	PITMTLD0      = pitmtld0;    /* PIT micro timer load reg. 0 */
	PITMTLD1      = 0x00;        /* PIT micro timer load reg. 1 */
	PITLD0        = pitld0;      /* PIT load register 0 */
	PITCNT0       = 0x00;        /* PIT count register 0 */
	PITLD1        = 0x00;        /* PIT load register 1 */
	PITCNT1       = 0x00;        /* PIT count register 1 */
	PITLD2        = 0x00;        /* PIT load register 2 */
	PITCNT2       = 0x00;        /* PIT count register 2 */
	PITLD3        = 0x00;        /* PIT load register 3 */
	PITCNT3       = 0x00;        /* PIT count register 3 */
	PITCFLMT      = 0x80;        /* PIT control micro timer register */
	  
	_asm("cli");
	INT_CFADDR = 0x7A;
	INT_CFDATA0 = prio;
	EE_pit0_initialized = 1;
}

/**
 * \brief				This function is used to close the Periodic Interrupt timer.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_pit0_close( void ) {
	PITCFLMT = 0x00;        /* PIT control micro timer register */
	EE_pit0_initialized = 0;
}

/**
 * \brief				This function is used to clear the Periodic timer Interrupt flag.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_pit0_clear_ISRflag( void ) {
	PITTF = 0x01;        
}


#endif

#endif
