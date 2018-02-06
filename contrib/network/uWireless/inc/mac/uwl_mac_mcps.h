/** 
* @file uwl_mac_mcps.h
* @brief IEEE 802.15.4 MCPS-SAP Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_mcps_h__
#define __uwl_mac_mcps_h__

#include <mac/uwl_mac_types.h>

COMPILER_INLINE 
uint8_t uwl_mac_set_tx_options(uint8_t ack, uint8_t use_gts, uint8_t indirect)
{
	return (ack & 0x1) | ((use_gts & 0x1) << 1) | ((indirect & 0x1) << 2);
}

#define UWL_MAC_TX_OPTION_ACK(opt)	((opt) & 0x01)
#define UWL_MAC_TX_OPTION_GTS(opt)	(((opt) >> 1) & 0x01)
#define UWL_MAC_TX_OPTION_INDIRECT(opt)	(((opt) >> 2) & 0x01)

int8_t uwl_MCPS_DATA_request(uint8_t SrcAddrMode, uint8_t DstAddrMode,
			     uint16_t DstPANId, void *DstAddr,
			     uint8_t msduLength, uint8_t *msdu,
			     uint8_t msduHandle, uint8_t TxOptions,
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex);

int8_t uwl_MCPS_DATA_confirm(uint8_t msduHandle, enum uwl_mac_code_t status,
			     uint32_t Timestamp);

int8_t uwl_MCPS_DATA_indication(uint8_t SrcAddrMode, uint16_t SrcPANId,
				void *SrcAddr, uint8_t DstAddrMode,
				uint16_t DstPANId, void *DstAddr,
				uint8_t msduLength, uint8_t *msdu,
				uint8_t mpduLinkQuality, uint8_t DSN,
				uint32_t Timestamp, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex);

#ifdef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MCPS_PURGE_request(uint8_t msduHandle);

int8_t uwl_MCPS_PURGE_confirm(uint8_t msduHandle, enum uwl_mac_code_t status);
#endif /* UWL_RFD_NO_OPTIONAL */

#endif /* Header Protection */
