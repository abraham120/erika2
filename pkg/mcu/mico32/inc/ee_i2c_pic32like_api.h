/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file ee_i2c_pic32like_api.h
	@brief I2C adapted functions for compatibility with pic32 projects. 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __INCLUDE_EEMCUMICO32_I2C_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_I2C_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 i2c driver*/ 
/* ------------------------------------------------ */

#define EE_mchp_i2c_init(uc, baud, flags) EE_hal_i2c_config((OCI2CMDev_t*)EE_BASE_ADD(uc), baud, flags)
#define EE_mchp_i2c_idle(uc) EE_hal_i2c_idle((OCI2CMDev_t*)EE_BASE_ADD(uc))
#define EE_mchp_i2c_read_byte(uc, device, address) EE_hal_i2c_read_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address)
#define EE_mchp_i2c_write_byte(uc, device, address, data) EE_hal_i2c_write_byte_polling((OCI2CMDev_t*)EE_BASE_ADD(uc), device, address, data)	

/*
	This function is used to initialize i2c controller. 
		Arguments:
			- EE_UINT8 port: I2C port number
			- EE_UINT16 baudrate: transmission rate 
			- EE_UINT16 flags: flags to configure the controller (not supported)
		Actions: 
			- Initialize i2c controller.
		Return values:
			- the return values can be:	EE_I2C_OK if no errors found,
										a negative number in case of errors.
*/	
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_init(EE_UINT8 port, EE_UINT16 baudrate, EE_UINT16 flags)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_init(EE_I2C1_NAME_UC, baudrate, flags);
	else
		ret = EE_mchp_i2c_init(EE_I2C2_NAME_UC, baudrate, flags);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_init(EE_I2C1_NAME_UC, baudrate, flags);
		#else
		ret = EE_mchp_i2c_init(EE_I2C2_NAME_UC, baudrate, flags);
		#endif
	#endif
		
	return ret;
}

/*
	This function is used to verifie the state of the i2c channel.
		Arguments:
			- EE_UINT8 port: I2C port number
		Actions: 
			- Verifie the state of the i2c channel.
		Return values:
			- the return values can be:	EE_I2C_OK if no errors found,
										a negative number in case of errors.
*/	
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_idle(EE_UINT8 port)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_idle(EE_I2C1_NAME_UC);
	else
		ret = EE_mchp_i2c_idle(EE_I2C2_NAME_UC);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_idle(EE_I2C1_NAME_UC);
		#else
		ret = EE_mchp_i2c_idle(EE_I2C2_NAME_UC);
		#endif
	#endif
		
	return ret;
}

/*
	This function is used to read a byte.
		Arguments:
			- EE_UINT8 port: I2C port number
			- EE_UINT8 device: device address
			- EE_UINT8 address: register/memory address
			- EE_UINT8 *data: pointer to a variable
		Actions: 
			- Read a byte
		Return values:
			- the return values can be:	EE_I2C_OK if no errors found,
										a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_i2c_read_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_read_byte(EE_I2C1_NAME_UC, device, address);
	else
		ret = EE_mchp_i2c_read_byte(EE_I2C2_NAME_UC, device, address);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_read_byte(EE_I2C1_NAME_UC, device, address);
		#else
		ret = EE_mchp_i2c_read_byte(EE_I2C2_NAME_UC, device, address);
		#endif
	#endif
		
	*data = (EE_UINT8)ret;
		
	return ret;

}

/*
	This function is used to read a byte.
		Arguments:
			- EE_UINT8 port: I2C port number
			- EE_UINT8 device: device address
			- EE_UINT8 address: register/memory address
			- EE_UINT8 data: character to be transmitted
		Actions: 
			- Write a byte
		Return values:
			- the return values can be:	EE_I2C_OK if no errors found,
										a negative number in case of errors.
*/
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)
{
	EE_INT8 ret;
	
	#if defined(EE_I2C1_NAME_UC) && defined(EE_I2C2_NAME_UC)
	if(port==1)
		ret = EE_mchp_i2c_write_byte(EE_I2C1_NAME_UC, device, address, data);
	else
		ret = EE_mchp_i2c_write_byte(EE_I2C2_NAME_UC, device, address, data);
	#else
		#if defined(EE_I2C1_NAME_UC)
		ret = EE_mchp_i2c_write_byte(EE_I2C1_NAME_UC, device, address, data);
		#else
		ret = EE_mchp_i2c_write_byte(EE_I2C2_NAME_UC, device, address, data);
		#endif
	#endif
		
	return ret;

}

#endif //__INCLUDE_EEMCUMICO32_I2C_PIC32LIKE_H__
