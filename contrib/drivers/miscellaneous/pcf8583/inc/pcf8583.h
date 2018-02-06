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
* @file 	pcf8583.h
* @brief 	PCF8583 real time clock Driver main header file.
* @author 	Dario Di Stefano 
* @date 	2010
*/

#ifndef __PCF8583_H__
#define __PCF8583_H__

#include "pcf8583_compiler.h"
#include "pcf8583_hal.h"
#include "pcf8583_reg.h"

/* Time structure */
typedef struct {
    uint8_t year, month, day, hours, minutes, seconds, hundredths;
} TTime;

/*	Operation Status		*/
#define RTC_NO_ERROR		1	//returned as positive

/**
	@brief	This function initializes Mico32 i2c interface
			using default settings.  
*/
__INLINE__ void __ALWAYS_INLINE__ EE_rtc_init(void)
{
    EE_rtc_hal_init();
}

/**
	@brief	This function initializes Mico32 i2c interface.
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_config(uint32_t baudrate, uint32_t settings)
{
    EE_rtc_hal_config(baudrate, settings);
}

/**
	@brief		This function turns on rt-clock counters. 						
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_start(void)
{
    EE_rtc_hal_start();
}

/**
	@brief		This function turns off rt-clock counters. 						
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_shutdown(void)
{
    EE_rtc_hal_shutdown();
}

/**
	@brief		This function writes a byte to RTC RAM
				using Mico32 i2c interface. 						
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_write_byte(uint8_t address, uint8_t data)
{
    EE_rtc_hal_write_byte(address, data);
}

/**
	@brief		This function writes an array of bytes to RTC RAM
				using Mico32 i2c interface. 						
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_write_buffer(uint8_t address, const uint8_t *data, uint32_t len)
{
	EE_rtc_hal_write_buffer(address, data, len);
}


/**
	@brief		This function reads a byte from RTC RAM
				using Mico32 i2c interface. 						
*/
__INLINE__ int __ALWAYS_INLINE__  EE_rtc_read_byte(uint8_t address)
{
    return EE_rtc_hal_read_byte(address);
}

/**
	@brief		This function reads an array of bytes from RTC RAM
				using Mico32 i2c interface. 						
*/
__INLINE__ void __ALWAYS_INLINE__  EE_rtc_read_buffer(uint8_t address, uint8_t *data, uint32_t len)
{
    EE_rtc_hal_read_buffer(address, data, len);
}

/**
	@brief 		This function updates rt-clock internal time.
				It sends i2c commands to: turn off the clock, write new time 
				and turn on the clock;
	@param ttw	pointer to the TTime structure with the time to be written; 
	@return		EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission\n
				EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission\n
				EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission\n
				EE_I2C_ERR_ARB_LOST if arbitration is lost\n
				RTC_NO_ERROR if no errors found (see ee_i2c.h for more info)
				
*/
int EE_rtc_write_time(const TTime *ttw);

/**
	@brief 		This function reads the rt-clock internal time. 
	@param ttr	pointer to the TTime structure to copy to 
	@return		EE_I2C_ERR_DEV_ACK if ACK is not received after slave address transmission\n
				EE_I2C_ERR_ADD_ACK if ACK is not received after memory address transmission\n
				EE_I2C_ERR_DATA_ACK if ACK is not received after data transmission\n
				EE_I2C_ERR_ARB_LOST if arbitration is lost\n
				RTC_NO_ERROR if no errors found (see ee_i2c.h for more info)				
*/
int EE_rtc_read_time(TTime *ttr); 

#endif // __PCF8583_H___
