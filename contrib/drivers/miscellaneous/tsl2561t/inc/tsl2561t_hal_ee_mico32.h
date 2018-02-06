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
	@file 	tsl2561t_hal_ee_mico32.h
	@brief 	TSL2561T Light Sensor Driver for Lattice Mico32
			This file is part of the TSL2561T Light Sensor Driver
			developed at Retis Lab, Scuola Superiore Sant'Anna. Pisa (Italy).
			Copyright (C) 2002-2008   Retis Lab.
			Please contact: Matteo Petracca, Marco Ghibaudi.
	@author	Dario Di Stefano
	@date 	2010-04-26
*/

#ifndef __TSL2561T_HAL_EE_MICO32_H__
#define __TSL2561T_HAL_EE_MICO32_H__

#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include <cpu/mico32/inc/ee_irq.h>
#include "mcu/mico32/inc/ee_i2c.h"
#include "MicoUtils.h"

#ifdef __FPG_EYE__
#include "board/fpg-eye/inc/ee_internal.h"
#include "board/fpg-eye/inc/ee_lightsensor_tsl2561t.h"
#else	/* NO board */
#error "TSL2561T_HAL: Board specification is required!"
#endif	//#ifdef __FPG_EYE__

#ifndef __USE_I2C__
#error "TSL2561T HAL EE : The I2C module from MCU is required!"
#endif

#ifndef TSL2561T_I2C_CLK
#define TSL2561T_I2C_CLK	400		//KHz
#endif

#ifndef TSL2561T_I2C_FLAGS
#define TSL2561T_I2C_FLAGS	0x0		//No special settings.
#endif

/* Driver macros */
// #define TLS2561_DEVICE_ID		(0x49<<1)
// #define TLS2561_COMMAND_BIT     (0x80)
// #define TLS2561_CLEAR_INT       (0x40)
// #define TLS2561_WORD_PROT       (0x20)
// #define TLS2561_BLOCK_PROT      (0x10)
// #define TLS2561_WORD_COMMAND(x) (TLS2561_COMMAND_BIT | TLS2561_WORD_PROT | (x))
// #define TLS2561_BLOCK_COMMAND(x) (TLS2561_COMMAND_BIT | TLS2561_BLOCK_PROT | (x))
// #define TLS2561_BYTE_COMMAND(x) (TLS2561_COMMAND_BIT | (x))
// #define TLS2561_REG_CONTROL     (0x0)
// #define TLS2561_REG_DATA0LOW    (0xC)
// #define TLS2561_REG_DATA0HIGH   (0xD)
// #define TLS2561_REG_DATA0       (TLS2561_REG_DATA0LOW)
// #define TLS2561_REG_DATA1LOW    (0xE)
// #define TLS2561_REG_DATA1HIGH   (0xF)
// #define TLS2561_REG_DATA1       (TLS2561_REG_DATA1LOW)
// #define TLS2561_POWER_UP       	(0x03)
// #define TLS2561_POWER_DOWN		(0x00)

/* Macros for User functions (API) */  
#define DECLARE_FUNC_I2C_LIGHTSENSOR(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_i2c_config(int baudrate, int settings){ \
	return cat3(EE_, lc, _config)(baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_write_byte(EE_UINT8 device_id, EE_UINT8 address, EE_UINT8 data){ \
	return cat3(EE_, lc, _send_byte)(device_id, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_write_buffer(EE_UINT8 device_id, EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _send_buffer)(device_id, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_read_byte(EE_UINT8 device_id, EE_UINT8 address){ \
	return cat3(EE_, lc, _receive_byte)(device_id, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_lightsensor_read_buffer(EE_UINT8 device_id, EE_UINT8 address, EE_UINT8 *data, int len){ \
	return cat3(EE_, lc, _receive_buffer)(device_id, address, data, len); }
	
/**
	@brief 	API to configure and to use Mico32 i2c interface.		
*/	
DECLARE_FUNC_I2C_LIGHTSENSOR(EE_LIGHTSENSOR_I2C_UC, EE_LIGHTSENSOR_I2C_LC)

/******************************************************************************/
/*				Inlinde Functions 			      */
/******************************************************************************/

/**
	@brief 	This function sets the slave ADDRESS to DEVICE_ADDRESS_GND.		
*/	
COMPILER_INLINE void tsl2561t_hal_set_ADDRESS_gnd(void){ 
	EE_tsl2561t_board_set_address_gnd();
}

/**
	@brief 	This function sets the slave ADDRESS to DEVICE_ADDRESS_VDD.		
*/
COMPILER_INLINE void tsl2561t_hal_set_ADDRESS_vdd(void){ 
	EE_tsl2561t_board_set_address_vdd();
}

/**
	@brief 	This function sets the slave ADDRESS to DEVICE_ADDRESS_FLOAT.		
*/
COMPILER_INLINE void tsl2561t_hal_set_ADDRESS_float(void){
	EE_tsl2561t_board_set_address_float();
}

/**
	@brief 	This function sets INT pin (not supported, see ee_lightsensor_tsl2561t.h).		
*/
COMPILER_INLINE void tsl2561t_hal_set_INT_pin(void){
	EE_tsl2561t_board_set_int_pin();
}

/**
	@brief 	This function writes on a tsl2561t register.		
*/
COMPILER_INLINE void tsl2561t_write_register(EE_UINT8 device_address, EE_UINT8 reg, EE_UINT8 value) {
	EE_lightsensor_write_byte(device_address, reg, value);	
}

/**
	@brief 	This function reads a tsl2561t register.		
*/
COMPILER_INLINE void tsl2561t_read_register(EE_UINT8 device_address, EE_UINT8 reg , 
		EE_UINT8 * value) {

	*value = EE_lightsensor_read_byte(device_address, reg);		
}

/**
	@brief 	This function reads an array of bytes from tsl2561t memory.		
*/
COMPILER_INLINE void tsl2561t_read_buffer(EE_UINT8 device_address, EE_UINT8 reg , 
		EE_UINT8 *data, int len) {
		
	EE_lightsensor_read_buffer(device_address, reg, data, len);
}

/**
	@brief 	This function writes an array of bytes to tsl2561t memory.		
*/
COMPILER_INLINE void tsl2561t_write_buffer(EE_UINT8 device_address, EE_UINT8 reg , 
		EE_UINT8 *data, int len) {
		
	EE_lightsensor_write_buffer(device_address, reg, data, len);
}

/**
	@brief 	This function swaps a 32-bits variable for endianness change.		
*/
COMPILER_INLINE EE_UINT32 tsl2561t_swap_32(EE_UINT32 le_val){
	EE_UINT32 be_val;
	EE_UINT8 *p8 = (EE_UINT8*)&le_val;
	EE_UINT8 *q8 = (EE_UINT8*)&be_val;
	
	q8[0] = p8[3];
	q8[1] = p8[2];
	q8[2] = p8[1];
	q8[3] = p8[0];
	
	return be_val;
}

/**
	@brief 	This function swaps a 16-bits variable for endianness change.		
*/
COMPILER_INLINE EE_UINT16 tsl2561t_swap_16(EE_UINT16 le_val){
	EE_UINT16 be_val;
	EE_UINT8 *p8 = (EE_UINT8*)&le_val;
	EE_UINT8 *q8 = (EE_UINT8*)&be_val;
	
	q8[0] = p8[1];
	q8[1] = p8[0];
	
	return be_val;
}

/**
	@brief 	This function initializes Mico32 i2c controller.		
*/
EE_UINT8 tsl2561t_hal_i2c_init(void);

#endif //__TSL2561T_HAL_EE_MICO32_H__

