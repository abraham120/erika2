/*
Copyright (C) 2009 -  Salvatore Marrapese, Claudio Salvadori
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
 *\file ov9650_types.h
 *
 *\date  Created on: 22-jun-2012
 *\author  Author: Salvatore Marrapese, Claudio Salvadori
 *\brief API header
 */

#ifndef _OV9650_TYPES_H_
#define _OV9650_TYPES_H_

/****************************************************************************/
/*                            Type Definitions                              */
/****************************************************************************/

/**
*\brief Exit status for the OV9650 driver
* Values returned by the operative API function
* \see ov9650_init, ov9650_configure, ov9650_capture, ov9650_reg_write,
* ov9650_reg_read
*
*
*/
typedef enum {
	OV9650_SUCCESS = 0,			/**< No error */
	OV9650_FAILURE,				/**< Generic error */
	OV9650_ERR_I2C_INIT,		/**< I2C bus initialization error */
	OV9650_ERR_I2C_READ,		/**< I2C bus read error */
	OV9650_ERR_I2C_WRITE,		/**< I2C bus write error */
	OV9650_ERR_DEV_NOINIT,		/**< Device is not initialized */
	OV9650_ERR_MEM_NULL,		/**< Invalid NULL memory address */
	OV9650_ERR_DMA_INIT,		/**< Invalid NULL memory address */
	OV9650_HAL_INIT_ERR,
	OV9650_ERR_WRONG_PRODUCT,	/**< Camera product ID doesn't match */
	OV9650_ERR_DMA_SIZE,		/**< Wrong number of bytes transferred by DMA
									* (either a bus overrun or the camera sent
									* something wrong) */
} ov9650_status_t;

/**
* @brief Resolution value
*/
typedef enum {
	OV9650_XSVGA    = 0x00,		    /**< 1280x1024 pixel resolution*/
	OV9650_VGA	    = 0x01,		    /**< 640x480 pixel resolution*/
	OV9650_QVGA     = 0x02,         /**< 320x240 pixel resolution*/
	OV9650_QQVGA    = 0x03,         /**< 160x120 pixel resolution*/
	OV9650_CIF      = 0x04,         /**< 352x288 pixel resolution*/
	OV9650_QCIF     = 0x05,         /**< 176x144 pixel resolution*/
	OV9650_QQCIF    = 0x06          /**<  88x 72 pixel resolution*/
} ov9650_R_Value_t;

/**
* @brief Time divisor
*
*/
typedef enum {
	OV9650_T_1	= 0x00,		/**< Divide MCLK for 1 */
	OV9650_T_2	= 0x01,		/**< Divide MCLK for 2 */
	OV9650_T_3	= 0x02,		/**< Divide MCLK for 4 */
	OV9650_T_4	= 0x03,		/**< Divide MCLK for 8 */
	OV9650_T_5	= 0x04,		/**< Divide MCLK for 16 */
	OV9650_T_6	= 0x05,		/**< Divide MCLK for 32 */
	OV9650_T_7	= 0x06,		/**< Divide MCLK for 64 */
} ov9650_T_D_Value_t;

/**
 * @brief Callback type
 */
typedef void (ov9650_cback_t)(ov9650_status_t);

/**
* @name Type representation
* @{ */

//TODO: utilizzare definizione standard


/**  @} */

#endif /* _ov9650_types_h_ */
