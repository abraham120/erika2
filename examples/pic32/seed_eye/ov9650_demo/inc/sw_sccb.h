/*
Copyright (C) 2012 -  Salvatore Marrapese
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/**
 *\file sw_sccb.h
 *
 *\date  Created on: 10-jun-2012
 *\author  Author: Marrapese Salvatore
 *\brief API header
 */

#ifndef _SW_SCCB_H_
#define _SW_SCCB_H_

#include "util.h"
#include "ee.h"
#include "../../../../pkg/cpu/common/inc/ee_stdint.h"

#define SW_SCCB_T_2()			EE_delay_us(10)
#define SW_SCCB_T()				SW_SCCB_T_2(); SW_SCCB_T_2()
#define SW_SCCB_T_SKEW()		asm volatile (	"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t"\
									"nop\n\t")
/* Pin Define */
#define SW_SCCB_PIN_OUT			0
#define SW_SCCB_PIN_IN			1
#define SW_SCCB_PIN_HIGH		1
#define SW_SCCB_PIN_LOW			0

#define SW_SCCB_SDA_DIR			TRISFbits.TRISF2
#define SW_SCCB_SDA_VAL			LATFbits.LATF2
#define SW_SCCB_SDA				PORTFbits.RF2
#define SW_SCCB_SCL_DIR			TRISFbits.TRISF8
#define SW_SCCB_SCL_VAL			LATFbits.LATF8

#define SW_SCCB_SUCCESS			0


/**
* @brief Init the pin for sccb bus
*/
void sw_sccb_init(void);

/**
* @brief Read a unsigned 8 bit value on sccb bus
*
* @param id Device identifier
* @param reg Register address
* @param *val Register value
*
* @return Returns \c SW_SCCB_SUCCESS if no error occurs.
*/
uint8_t sw_sccb_read(uint8_t id, uint8_t reg, uint8_t* val);

/**
* @brief Write a unsigned 8 bit value on sccb bus
*
* @param id Device identifier
* @param reg Register address
* @param *val Value to put into Register
*
* @return Returns \c SW_SCCB_SUCCESS if no error occurs.
*/
uint8_t sw_sccb_write(uint8_t id, uint8_t reg, uint8_t val);

#endif

