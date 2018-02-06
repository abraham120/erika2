/**
 * @file phy.h
 * @brief RI-EDF PHY Layer Public Interface
 * @author Christian Nastasi
 * @date 2009-03-22
 *
 * This file is the entry point for the IEEE 802.15.4 PHY primitives.
 */

#ifndef __iedf_phy_h__
#define __iedf_phy_h__

#include <util/iedf_debug.h>
#include <util/iedf_memory.h>
#include <hal/iedf_rand.h>
#include <hal/iedf_compiler.h>
#include <kal/iedf_kal.h>
#include "hal/iedf_radio.h"
#include "mac/iedf.h"

#define IEDF_PHY_ERROR_NONE             0
#define IEDF_PHY_ERROR_INIT             1
#define IEDF_PHY_ERROR_SEND             2

enum iedf_phy_code_t {
	IEDF_PHY_BUSY 					= 0x00,
	IEDF_PHY_BUSY_RX 				= 0x01,
	IEDF_PHY_BUSY_TX 				= 0x02,
	IEDF_PHY_FORCE_TRX_OFF 			= 0x03,
	IEDF_PHY_IDLE 					= 0x04,
	IEDF_PHY_INVALID_PARAMETER 		= 0x05,
	IEDF_PHY_RX_ON 					= 0x06,
	IEDF_PHY_SUCCESS 				= 0x07,
	IEDF_PHY_TRX_OFF 				= 0x08,
	IEDF_PHY_TX_ON 					= 0x09,
	IEDF_PHY_UNSUPPORTED_ATTRIBUTE 	= 0x0A,
	IEDF_PHY_READ_ONLY 				= 0x0B
};

/**
* @brief Initializes the physical layer.
*
* This routine returns 0 if everything goes well, -1 otherwise.
*
* @param[in] chr The channel to tune in.
*/
int8_t iedf_phy_init(uint8_t ch);

/**
* @brief Send a message to the physical layer.
*
* @param[in] *psdu Pointer to physical data unit.
* @param[in] psduLen Length of the psdu
*/
int8_t iedf_phy_send(uint8_t *psdu, uint8_t psduLen);

/**
* @brief Set the state of the radio.
*
* @param[in] state The new state.
*/
int8_t iedf_phy_set_status(enum iedf_phy_code_t state);

/**
* @brief Returns the state of the radio.
*
*/
enum iedf_phy_code_t iedf_phy_get_status(void);


uint8_t iedf_phy_get_cca(void);

#endif
