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
* \file ee_board.h
* \brief Drivers for the TWRS12G128 evaluation board.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/

/** 
* \mainpage Erika support for the TWRS12G128 evaluation board.
*
* \section intro_sec This documentation describes the functions, the macros and the variables of the 
* Erika support for the TWRS12G128 evaluation board. For further info see the examples and the demos.
*/

#ifndef __INCLUDE_S12G_BOARD_H__
#define __INCLUDE_S12G_BOARD_H__

#include "mcu/hs12xs/inc/ee_mcu.h"

/**
 * \brief		Setup clock module for PLL Engaged using External XTAL
 * This function automatically calls EE_set_peripheral_frequency_mhz(8).
 * For 8MHz XTAL - 
 * VCOCLK - 64MHz, Core Clk - 16MHz, Bus Clk - 8MHz
*/
__INLINE__ void __ALWAYS_INLINE__ EE_set_clock_8MHz(void){

	CPMUSYNR = 0x01;					// fVCO = 32MHz
	CPMUREFDIV = 0x80;				// OSC input is 8MHz
	CPMUPOSTDIV = 0x01;				// core clk - 16MHz, bus clk - 8MHz
	
	CPMUOSC_OSCE = 1;					// enable ext OSC
	while(!CPMUFLG_UPOSC || !CPMUFLG_LOCK);
											// wait for ext osc to stabilize and pll to lock
	CPMUFLG = 0xFF;					// clear CMPMU int flags - not needed but good practice
	EE_set_peripheral_frequency_mhz(8);
}

/* /\************************************************************************* */
/* Check if the DemoBoard has been selected */
/* /\************************************************************************* */

#ifdef __TWRS12G128__
#include "board\twrs12g128\inc\twrs12g128_peripherals.h"
#endif /* __TWRS12G128__ */

/* ************************************************************************* */
#endif
