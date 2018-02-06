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
	@file 	tsl2561t_hal_ee_mico32.c
	@brief 	TSL2561T Light Sensor Driver for Lattice Mico32.
			This file is part of the TSL2561T Light Sensor Driver
			developed at Retis Lab, Scuola Superiore Sant'Anna. Pisa (Italy).
			Copyright (C) 2002-2008   Retis Lab.
			Please contact: Matteo Petracca, Marco Ghibaudi.
	@author Dario Di Stefano
	@date 	2010-04-26
*/

#include "tsl2561t.h"
#include "tsl2561t_hal_ee_mico32.h"

/* This function initializes Mico32 i2c controller. */
EE_UINT8 tsl2561t_hal_i2c_init(void) {

	if( EE_lightsensor_i2c_config(TSL2561T_I2C_CLK*1000, TSL2561T_I2C_FLAGS) == EE_I2C_OK )	
		return TSL2516T_NO_ERROR;
	return -TSL2516T_I2C_INIT_ERROR;
}

/* Functions used by Mirtes for Mico32 based devices */
void EE_analog_init(void)
{
	tsl2561t_init(SELECT_ADDRESS_VDD);
	tsl2561t_power_on(DEVICE_ADDRESS_VDD);
	tsl2561t_set_configuration(DEVICE_ADDRESS_VDD, TSL2561T_TIMING, 0); 
}

EE_UINT32 EE_analog_get_light( void )
{
	uint32_t lux;
	tsl2561t_read_lux(DEVICE_ADDRESS_VDD, &lux);
	return lux;
}
