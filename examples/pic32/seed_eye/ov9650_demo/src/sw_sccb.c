
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
 *\file sw_sccb.c
 *
 *\date  Created on: 10-jun-2012
 *\author  Author: Marrapese Salvatore
 *\brief API header
 */

#include "../inc/sw_sccb.h"

/* *** Private functions *** */

void sw_sccb_start(void)
{
	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_T();
	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T();
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T();
}

void sw_sccb_stop(void)
{
	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T();
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_T();
 	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_T();
}

void sw_sccb_byte_tx(uint8_t num, uint8_t val)
{
	uint8_t i;

	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T_SKEW();
	SW_SCCB_T_SKEW();
	SW_SCCB_T_SKEW();
	for(i = 0; i < num; i++) {
		if(val & 0x80) {
			SW_SCCB_SDA_VAL	= SW_SCCB_PIN_HIGH;
		} else  {
			SW_SCCB_SDA_VAL	= SW_SCCB_PIN_LOW;
		}
		SW_SCCB_T_2();
		SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
		SW_SCCB_T();
		SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
		SW_SCCB_T_2();
		val = val << 1;
	}
	SW_SCCB_T_2();
	/* ACK (not used in sccb) */
	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T_SKEW();

	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_T();
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T();
}

void sw_sccb_byte_rx(uint8_t num, uint8_t* val)
{
	uint8_t i;

	SW_SCCB_SDA_DIR = SW_SCCB_PIN_IN;
	SW_SCCB_T();

	for(i = 0; i < num; i++) {
		*val = *val << 1;
		SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
		SW_SCCB_T_2();
		if(SW_SCCB_SDA) {
			*val |= 1;
		} else {
		}
		SW_SCCB_T_2();
		SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
		SW_SCCB_T();
	}
	/* ACK (not used in sccb) */
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_T();
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_LOW;
	SW_SCCB_T();

	SW_SCCB_SDA_DIR	= SW_SCCB_PIN_OUT;
	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_LOW;
}

void sw_sccb_init(void)
{
	SW_SCCB_SDA_DIR	= SW_SCCB_PIN_OUT;
	SW_SCCB_SDA_VAL	= SW_SCCB_PIN_HIGH;
	SW_SCCB_SCL_DIR	= SW_SCCB_PIN_OUT;
	SW_SCCB_SCL_VAL	= SW_SCCB_PIN_HIGH;
}

uint8_t sw_sccb_read(uint8_t id, uint8_t reg, uint8_t* val)
{
	sw_sccb_start();
	sw_sccb_byte_tx(8, id);
	sw_sccb_byte_tx(8, reg);
	sw_sccb_stop();
	sw_sccb_start();
	sw_sccb_byte_tx(8, id + 1);
	sw_sccb_byte_rx(8, val);
	sw_sccb_stop();

	return SW_SCCB_SUCCESS;
}

uint8_t sw_sccb_write(uint8_t id, uint8_t reg, uint8_t val)
{
	sw_sccb_start();
	sw_sccb_byte_tx(8, id);
	sw_sccb_byte_tx(8, reg);
	sw_sccb_byte_tx(8, val);
	sw_sccb_stop();

	return SW_SCCB_SUCCESS;
}

