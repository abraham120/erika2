/** 
* @file uwl_net_mac_events.c
* @brief IEEE 802.15.4 MAC to Upper layer Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
/* TODO: this should go, eventually with a different name, in the makefile 
	 rules.
*/
//#ifndef UWL_USE_ONLY_802154_MAC	
#if !( (defined UWL_USE_ONLY_802154_MAC) || (defined UWL_USE_SIMPLE_802154) )

#include <mac/uwl_net_internal.h>

#ifdef UWL_DEBUG_LOG
#include <util/uwl_debug.h>
#include <string.h>
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif


int8_t uwl_MCPS_DATA_confirm(uint8_t msduHandle, enum uwl_mac_code_t status,
			     uint32_t Timestamp)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MCPS_DATA_indication(uint8_t SrcAddrMode, uint16_t SrcPANId,
				uwl_mac_dev_addr_t SrcAddr, uint8_t DstAddrMode,
				uint16_t DstPANId, uwl_mac_dev_addr_t DstAddr,
				uint8_t msduLength, uint8_t *msdu,
				uint8_t mpduLinkQuality, uint8_t DSN,
				uint32_t Timestamp, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MCPS_PURGE_confirm(uint8_t msduHandle, enum uwl_mac_code_t status)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}


int8_t uwl_MLME_ASSOCIATE_confirm(uwl_mac_dev_addr_short_t AssocShortAddress,
				  enum uwl_mac_code_t status,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex
)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

#ifndef UWL_RFD_DISABLE_OPTIONAL
/*int8_t uwl_MLME_ASSOCIATE_indication(uwl_mac_dev_addr_extd_t DeviceAddress,
				     uint8_t CapabilityInformation,
				     uint8_t SecurityLevel, uint8_t KeyIdMode,
				     uint8_t *KeySource, uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}*/

#endif /* UWL_RFD_DISABLE_OPTIONAL */


int8_t uwl_MLME_DISASSOCIATE_confirm(enum uwl_mac_code_t status,
				     uint8_t DeviceAddrMode,
				     uint16_t DevicePANId,
				     uwl_mac_dev_addr_t DeviceAddress)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MLME_DISASSOCIATE_indication(uwl_mac_dev_addr_extd_t DeviceAddress,
					uint8_t DisassociateReason,
					uint8_t SecurityLevel, 
					uint8_t KeyIdMode, uint8_t *KeySource,
					uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}


int8_t uwl_MLME_BEACON_NOTIFY_indication(uint8_t BSN,
					 struct uwl_pan_des_t PANDescriptor,
					 uint8_t PendAddrSpec,
		 /*TODO: list? how?*/	 uwl_mac_dev_addr_t *AddrList, 
					 uint8_t sduLength, uint8_t *sdu)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MLME_GET_confirm(enum uwl_mac_code_t status,
			    enum uwl_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex, 
			    void *PIBAttributeValue)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

#ifndef UWL_DEVICE_DISABLE_OPTIONAL
int8_t uwl_MLME_GTS_confirm(uint8_t GTSCharacteristics, 
			    enum uwl_mac_code_t status)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MLME_GTS_indication(uwl_mac_dev_addr_short_t DeviceAddress,
			       uint8_t GTSCharacteristics,
			       uint8_t SecurityLevel, uint8_t KeyIdMode,
			       uint8_t *KeySource, uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_ORPHAN_indication(uwl_mac_dev_addr_extd_t OrphanAddress,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

#endif /* UWL_RFD_DISABLE_OPTIONAL */

int8_t uwl_MLME_RESET_confirm(enum uwl_mac_code_t status)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

#ifndef UWL_DEVICE_DISABLE_OPTIONAL

int8_t uwl_MLME_RX_ENABLE_confirm(enum uwl_mac_code_t status)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

int8_t uwl_MLME_SCAN_confirm(enum uwl_mac_code_t status, uint8_t ScanType,
			     uint8_t ChannelPage, uint32_t UnscannedChannels,
/*TODO: good represent.?*/   uint16_t ResultListSize, uint8_t *EnergyDetectList,
			     struct uwl_pan_des_t *PANDescriptorList)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MLME_COMM_STATUS_indication(uint16_t PANId, uint8_t SrcAddrMode,
				       uwl_mac_dev_addr_t SrcAddr,
				       uint8_t DstAddrMode,
				       uwl_mac_dev_addr_t DstAddr,
				       enum uwl_mac_code_t status,
				       uint8_t SecurityLevel, uint8_t KeyIdMode,
				       uint8_t KeySource, uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MLME_SET_confirm(enum uwl_mac_code_t status,
			    enum uwl_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

#ifndef UWL_RFD_DISABLE_OPTIONAL

int8_t uwl_MLME_START_confirm(enum uwl_mac_code_t status)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}
#endif /* UWL_RFD_DISABLE_OPTIONAL */

int8_t uwl_MLME_SYNC_LOSS_indication(enum uwl_mac_code_t LossReason,
				     uint8_t PANId, uint8_t LogicalChannel,
				     uint8_t ChannelPage, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

int8_t uwl_MLME_POLL_confirm(enum uwl_mac_code_t status)
{
	//#ifdef UWL_DEBUG_LOG
	//char s[100];
	//char s1[30];
	//uwl_debug_sprint_maccode(status, s1);
	//sprintf(s, "SET_confirm(%s, a=%u)", s1, PIBAttribute);
	//uwl_debug_print(s);
	//#endif
	return 1;
}

#endif /* ! (UWL_USE_ONLY_802154_MAC || UWL_USE_SIMPLE_802154) */
