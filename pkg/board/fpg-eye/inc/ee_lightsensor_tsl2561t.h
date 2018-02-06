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
	@file ee_lightsensor_tsl2561t.h
	@brief TSL2561T Light sensor driver header file (board dependent file: XP2 CAMERA BOARD). 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __EE_LIGHTSENSOR_XP2CAMERABOARD_TSL2561T__
#define __EE_LIGHTSENSOR_XP2CAMERABOARD_TSL2561T__

/* Board dependent macros */
#define EE_tsl2561t_board_set_address_gnd()
#define EE_tsl2561t_board_set_address_vdd()
#define EE_tsl2561t_board_set_address_float()
#define EE_tsl2561t_board_set_int_pin()

/* Macros for User functions (API) */  
#define EE_LIGHTSENSOR_I2C_UC CAMERA_I2C
#define EE_LIGHTSENSOR_I2C_LC camera_i2c
	
/* Functions for Mirtes compatibility */
void EE_analog_init(void);
#define EE_analogsensors_init() EE_analog_init()
EE_UINT32 EE_analog_get_light( void );
	
#endif //#ifndef __EE_LIGHTSENSOR_XP2CAMERABOARD_TSL2561T__


