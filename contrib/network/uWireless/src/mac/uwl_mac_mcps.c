/**
* @file uwl_mac_mcps.c
* @brief IEEE 802.15.4 MCPS-SAP Implementation
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#include <mac/uwl_mac_internal.h>
#include <util/uwl_debug.h>
#ifdef UWL_DEBUG_LOG
//#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/* TODO: what is the meaning of the msduHandle? */

int8_t uwl_MCPS_DATA_request(uint8_t SrcAddrMode, uint8_t DstAddrMode,
			     uint16_t DstPANId, void *DstAddr,
			     uint8_t msduLength, uint8_t *msdu,
			     uint8_t msduHandle, uint8_t TxOptions,
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex)
{
	if (SrcAddrMode == UWL_MAC_ADDRESS_NONE &&
	    DstAddrMode == UWL_MAC_ADDRESS_NONE) {
		uwl_MCPS_DATA_confirm(msduHandle, UWL_MAC_INVALID_ADDRESS, 0);
		return UWL_MAC_ERR_NONE;
	} else if (SrcAddrMode != UWL_MAC_ADDRESS_SHORT &&
		   SrcAddrMode != UWL_MAC_ADDRESS_EXTD) {
		uwl_MCPS_DATA_confirm(msduHandle, UWL_MAC_INVALID_PARAMETER, 0);
		return UWL_MAC_ERR_NONE;
	} else if (DstAddrMode != UWL_MAC_ADDRESS_SHORT &&
		   DstAddrMode != UWL_MAC_ADDRESS_EXTD) {
		uwl_MCPS_DATA_confirm(msduHandle, UWL_MAC_INVALID_PARAMETER, 0);
		return UWL_MAC_ERR_NONE;
	}
	if (msduLength > UWL_aMaxMACPayloadSize) {
		uwl_MCPS_DATA_confirm(msduHandle, UWL_MAC_INVALID_PARAMETER, 0);
		return UWL_MAC_ERR_NONE;
	}
	if (SecurityLevel != 0) {
		return -UWL_MAC_ERR_STANDARD_UNSUPPORTED;
		/* TODO: security levels management! */
	}
	/* TODO: check other params!*/
	/* TODO: check ret value?*/
	uwl_mac_perform_data_request(SrcAddrMode, DstAddrMode, DstPANId,
				     DstAddr, msduLength, msdu, msduHandle,
				     TxOptions/*, SecurityLevel, KeyIdMode,
				     KeySource, KeyIndex*/);

	return UWL_MAC_ERR_NONE;
}
