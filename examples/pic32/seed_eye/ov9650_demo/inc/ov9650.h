/*
Copyright (C) 2009 -  Salvatore Marrapese, Claudio Salvadori and 
Christian Nastasi.
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
 *\file ov9650.h
 *
 *\date  Created on: 02-Jun-2012
 *\author  Author: Salvatore Marrapese, Claudio Salvadori,
 *                 Christian Nastasi, and Bernardo Dal Seno
 *\brief API header
 */

#ifndef _OV9650_H_
#define _OV9650_H_

#define OV9650_HSYNC_INT_MODE

#include "ov9650_types.h"
#include "ov9650_reg.h"
#include "ov9650_compiler_ee.h"
#include "ov9650_hal_ee_pic32.h"
#include "ov9650_hal_ee_board_single_128k.h"

/******************************************************************************/
/*                         Function Declarations                              */
/******************************************************************************/
/**
* @brief Init a ov9650 Camera with 10MHz master clock
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_init(void);

/******************************************************************************/
/*                         Function Declarations                              */
/******************************************************************************/
/**
* @brief Set a ov9650 resolution
*
* @param res Risolution set: OV9650_VGA, OV9650_QVGA, OV9650_QQVGA
*                            OV9650_CIF, OV9650_QCIF, OV9650_QQCIF.
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_configure_resolution(ov9650_R_Value_t res);

/**
* @brief Write a OV9650 Camera register
*
* @param reg Device register address
* @param val Register value
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_reg_write(ov9650_reg_t reg, uint8_t val);

/**
* @brief Read a OV9650 Camera register
*
* @param reg Device register address
* @param val Register value
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_reg_read(ov9650_reg_t reg, uint8_t *val);

/**
* @brief Modify some bits of a OV9650 Camera register
*
* @param reg Device register address
* @param mask Bits to change
* @param val New value for the bits in the mask
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_reg_update(ov9650_reg_t reg, uint8_t mask,
	uint8_t value);

/**
* @brief Enable colors on OV9650 Camera.
*
* \param status   A boolean indicating whether to turn colors on or off
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_configure_color(int status);

/**
* @brief Reset the camera to the starting configuration
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_init_configure(void);

/**
* @brief Configure the clock division on OV9650 Camera
*
* \param div		Divisor value
*
* \see ov9650_T_D_Value_t
*
* @return Returns \c OV9650_SUCCESS if no error occurs,
*         otherwise a specific error code.
*/
ov9650_status_t ov9650_configure_time_divisor(ov9650_T_D_Value_t div);

void ov9650_i2c_config(void);

uint16_t ov9650_get_width(void);
uint16_t ov9650_get_height(void);
uint32_t ov9650_get_size(void);

/******************************************************************************/
/*                         Inline function definitions                        */
/******************************************************************************/

/* Format Frame: Y U Y V. */
COMPILER_INLINE ov9650_status_t ov9650_capture(uint8_t *image, ov9650_cback_t *func)
{
    if (image == NULL)
        return OV9650_ERR_MEM_NULL;
    else
        return ov9650_hal_capture(image, func);
}

#endif

