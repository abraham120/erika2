/*
Copyright (C) 2009 -  Claudio Salvadori and Christian Nastasi
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
 *\file hv7131gp_types.h
 *
 *\date  Created on: 6-feb-2009
 *\author  Author: Claudio Salvadori and Christian Nastasi (and Bernardo Dal Seno)
 *\brief API header
 */

#ifndef _hv7131gp_types_h_
#define _hv7131gp_types_h_

/******************************************************************************/
/*                            Type Definitions                                */
/******************************************************************************/

/**
*\brief Exit status for the HV7131GP driver
* Values returned by the operative API function
* \see hv7131gp_init, hv7131gp_configure, hv7131gp_capture, hv7131gp_reg_write,
* hv7131gp_reg_read
*
*
*/
typedef enum {
	HV7131GP_SUCCESS = 0,		/**< No error */
	HV7131GP_FAILURE,		/**< Generic error */
	HV7131GP_ERR_I2C_INIT,		/**< I2C bus initialization error */
	HV7131GP_ERR_I2C_READ,		/**< I2C bus read error */
	HV7131GP_ERR_I2C_WRITE,		/**< I2C bus write error */
	HV7131GP_ERR_DEV_NOINIT,	/**< Device is not initialized */
	HV7131GP_ERR_MEM_NULL,		/**< Invalid NULL memory address */
	HV7131GP_ERR_DMA_INIT,	/**< Invalid NULL memory address */
	HV7131GP_HAL_INIT_ERR,
	HV7131GP_ERR_WRONG_PRODUCT,	/**< Camera product ID doesn't match */
	HV7131GP_ERR_DMA_SIZE,	/**< Wrong number of bytes transferred by DMA
				 * (either a bus overrun or the camera sent
				 * something wrong) */
} hv7131gp_status_t;

/**
* @brief Resolution value
*/
typedef enum {
	HV7131GP_NO_SUB  	= 0x00,		/**< 640x480 pixel resolution*/
	HV7131GP_1_4_SUB	= 0x01,		/**< 320x240 pixel resolution*/
	HV7131GP_1_16_SUB	= 0x02,		/**< 160x120 pixel resolution */
        HV7131GP_BAYER_SUB,                     /**< Raw bayer data */
} hv7131gp_R_Value_t;

/**
* @brief Time divisor
*
*/
typedef enum {
	HV7131GP_T_1	= 0x00,		/**< Divide MCLK for 1 */
	HV7131GP_T_2	= 0x01,		/**< Divide MCLK for 2 */
	HV7131GP_T_3	= 0x02,		/**< Divide MCLK for 4 */
	HV7131GP_T_4	= 0x03,		/**< Divide MCLK for 8 */
	HV7131GP_T_5	= 0x04,		/**< Divide MCLK for 16 */
	HV7131GP_T_6	= 0x05,		/**< Divide MCLK for 32 */
	HV7131GP_T_7	= 0x06,		/**< Divide MCLK for 64 */
	HV7131GP_T_8	= 0x07,		/**< Divide MCLK for 128 */
} hv7131gp_T_D_Value_t;


/**
* @brief Quality value (high level)
*/
typedef enum {
	HV7131GP_160x120_FAST  	= 0x00,	/**< 160x120 + T2 divisor*/
	HV7131GP_160x120_MEDIUM	= 0x01,	/**< 160x120 + T4 divisor*/
	HV7131GP_160x120_SLOW	= 0x02,	/**< 160x120 + T7 divisor */
} hv7131gp_Q_Value_t;


/**
 * @brief Callback type
 */
typedef void (hv7131gp_cback_t)(hv7131gp_status_t);

/**
* @name Type representation
* @{ */

//TODO: utilizzare definizione standard


/**  @} */

#endif /* _hv7131gp_types_h_ */
