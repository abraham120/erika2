/**
* @file uwl_radio.h
* @brief Abstract Radio Definition
* @author Christian Nastasi
* @version 0.1
* @date 2009-03-22
*
* This file contains the declarations of the abstract radio used by the uWireless
* modules.
*
*/
#ifndef __uwl_radio_h__
#define __uwl_radio_h__

#include <hal/uwl_compiler.h>

#define UWL_RADIO_ERR_NONE          0
#define UWL_RADIO_ERR_PHY_FAILURE   1 /**< The PHY layer issued a primitive with a failure status. */
#define UWL_RADIO_ERR_TX_WAIT       2 /**< Used for tx_status while waiting for end of transmission */

#ifdef USE_CC2420		/* Texas Instruments CC2420 */
#include <hal/uwl_radio_cc2420.h>

#elif defined USE_MRF24J40 	/* Microchip MRF24J40. */
#include <hal/uwl_radio_mrf24j40.h>
#else			/* No radio */
#error "UWL_HAL ERROR: radio type not specified!"

#endif	/* End Radio Selection */

enum uwl_phy_code_t uwl_radio_phy_get_status(void);

int8_t uwl_radio_phy_set_channel(uint8_t ch);
int8_t uwl_radio_phy_set_rx_on(void);
int8_t uwl_radio_phy_send_now(uint8_t *data, uint8_t size);

#endif /* Header Protection */
