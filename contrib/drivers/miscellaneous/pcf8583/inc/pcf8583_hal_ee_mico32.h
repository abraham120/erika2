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
* @file 	pcf8583_hal_ee_mico32.h
* @brief 	pcf8583 Real-time clock driver HAL for Lattice Mico32.
* @author 	Dario Di Stefano
* @date 	2010
*/

#ifndef __PCF8583_HAL_EE_MICO32_H__
#define __PCF8583_HAL_EE_MICO32_H__

#include "pcf8583_reg.h"
#include "pcf8583_compiler.h"
#include "mcu/mico32/inc/ee_i2c.h"

#ifdef __FPG_EYE__
#include "board/fpg-eye/inc/ee_internal.h"
#include "board/fpg-eye/inc/ee_rtc_pcf8583.h"
#else	/* NO board */
#error "MRF24J40_HAL: Board specification is required!"
#endif	//#ifdef __FPG_EYE__

#ifndef __USE_I2C__
#error "PCF8583 HAL EE : The I2C module from MCU is required!"
#endif

/* Inlinde Functions */

/**
	@brief	This function initializes Mico32 i2c controller
			using default settings.
*/
COMPILER_INLINE void EE_rtc_hal_init(void)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _config)(100000, 0);
}

/**
	@brief	This function configures Mico32 i2c controller.
*/
COMPILER_INLINE void EE_rtc_hal_config(uint32_t baudrate, uint32_t settings)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _config)(baudrate, settings);
}

/**
	@brief	This function turns on RTC.
*/
COMPILER_INLINE void EE_rtc_hal_start(void)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_byte)(RTC_DEVICE_ID, RTC_CSR_ADD, RTC_ON);
}

/**
	@brief	This function turns off RTC.
*/
COMPILER_INLINE void EE_rtc_hal_shutdown(void)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_byte)(RTC_DEVICE_ID, RTC_CSR_ADD, RTC_OFF);
}

/**
	@brief	This function writes a byte using Mico32 i2c interface.
*/
COMPILER_INLINE void EE_rtc_hal_write_byte(uint8_t address, uint8_t data)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_byte)(RTC_DEVICE_ID, address, data);
}

/**
	@brief	This function writes an array of bytes using Mico32 i2c interface.
*/
COMPILER_INLINE void EE_rtc_hal_write_buffer(uint8_t address, const uint8_t *data, uint32_t len)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _send_buffer)(RTC_DEVICE_ID, address, data, len);
}

/**
	@brief	This function reads a byte using Mico32 i2c interface.
*/
COMPILER_INLINE int EE_rtc_hal_read_byte(uint8_t address)
{
    return cat3_ind(EE_, EE_RTC_I2C_LC, _receive_byte)(RTC_DEVICE_ID, address);
}

/**
	@brief	This function reads an array of bytes using Mico32 i2c interface.
*/
COMPILER_INLINE void EE_rtc_hal_read_buffer(uint8_t address, uint8_t *data, uint32_t len)
{
    cat3_ind(EE_, EE_RTC_I2C_LC, _receive_buffer)(RTC_DEVICE_ID, address, data, len);
}


#endif //__PCF8583_HAL_EE_MICO32_H__

