/** 
* @file phy_types.h
* @brief IEEE 802.15.4 PHY Types
* @author Christian Nastasi
* @date 2009-03-22
*/
#ifndef __uwl_phy_types_h__
#define __uwl_phy_types_h__

#include <hal/uwl_compiler.h>
#include <phy/uwl_phy_const.h>

/** 
* @brief IEEE 802.15.4 PHY PAN Information Base
*
* \todo Some member can be optimized due to their representation. Check the
* 	standard at the section and table PHY PIB attributes.
* \todo Some value (from CURRENT_PAGE_INIT to 
*	SYMBOLS_PER_OCTET_INIT) cannot change at runtime unless there 
*	is a change in the transceiver (is this correct?). Can we optimize
*	the code making some of the elements as either const (flash) or define?
*/
struct uwl_phy_pib_t {
	uint8_t 	phyCurrentChannel;
	uint32_t	phyChannelsSupported[UWL_PHY_CHANNEL_PAGES];
	uint8_t 	phyTransmitPower;
	uint8_t		phyCCAMode;
	uint8_t 	phyCurrentPage;
	uint16_t	phyMaxFrameDuration;
	uint8_t		phySHRDuration;
	float 		phySymbolsPerOctet;
};

/** 
* @brief PHY PIB Attributes IDs.
*
* \todo Make a reference to the std where is defined the PHY PIB attribute list.
*/
enum uwl_phy_pib_id_t {
	UWL_PHY_CURRENT_CHANNEL		= 0x00,
	UWL_PHY_CHANNEL_SUPPORTED	= 0x01,
	UWL_PHY_TRANSMIT_POWER		= 0x02,
	UWL_PHY_CCA_MODE		= 0x03,
	UWL_PHY_CURRENT_PAGE		= 0x04,
	UWL_PHY_MAX_FRAME_DURATION	= 0x05,
	UWL_PHY_SHR_DURATION		= 0x06,
	UWL_PHY_SYMBOLS_PER_OCTET	= 0x07,
};

/** 
* @brief PHY status and state code.
*
* \todo Make a reference to the std where is defined the PHY enumeration list.
*/
enum uwl_phy_code_t {
	UWL_PHY_BUSY 			= 0x00,
	UWL_PHY_BUSY_RX 		= 0x01,
	UWL_PHY_BUSY_TX 		= 0x02,
	UWL_PHY_FORCE_TRX_OFF 		= 0x03,
	UWL_PHY_IDLE 			= 0x04,
	UWL_PHY_INVALID_PARAMETER 	= 0x05,
	UWL_PHY_RX_ON 			= 0x06,
	UWL_PHY_SUCCESS 		= 0x07,
	UWL_PHY_TRX_OFF 		= 0x08,
	UWL_PHY_TX_ON 			= 0x09,
	UWL_PHY_UNSUPPORTED_ATTRIBUTE 	= 0x0A,
	UWL_PHY_READ_ONLY 		= 0x0B
};


#endif /* Header Protection */
