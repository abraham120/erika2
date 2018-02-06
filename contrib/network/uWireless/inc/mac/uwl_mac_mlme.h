/** 
* @file uwl_mac_mlme.h
* @brief IEEE 802.15.4 MLME-SAP Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_mlme_h__
#define __uwl_mac_mlme_h__

#include <mac/uwl_mac_types.h>

COMPILER_INLINE 
uint8_t uwl_mac_capability_information(uint8_t alt_pan_coord, uint8_t dev_type,
				       uint8_t power_src, uint8_t rx_on_idle,
				       uint8_t security, uint8_t alloc_addr) 
{

	return 	((alt_pan_coord & 0x1) | ((dev_type & 0x1) << 1) | 
		((power_src & 0x1) << 2) | ((rx_on_idle & 0x1) << 3) |
		((security & 0x1) << 6) | ((alloc_addr & 0x1) << 7));
}
			


int8_t uwl_MLME_ASSOCIATE_request(uint8_t LogicalChannel, uint8_t ChannelPage,
				  uint8_t CoordAddrMode, uint16_t CoordPANId,
				  void *CoordAddress,
				  uint8_t CapabilityInformation,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex);

int8_t uwl_MLME_ASSOCIATE_confirm(uwl_mac_dev_addr_short_t AssocShortAddress,
				  enum uwl_mac_code_t status,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex
);

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_ASSOCIATE_indication(uwl_mac_dev_addr_extd_t DeviceAddress,
				     uint8_t CapabilityInformation,
				     uint8_t SecurityLevel, uint8_t KeyIdMode,
				     uint8_t *KeySource, uint8_t KeyIndex);

int8_t uwl_MLME_ASSOCIATE_response(uwl_mac_dev_addr_extd_t DeviceAddress,
				   uwl_mac_dev_addr_short_t AssocShortAddress,
				   enum uwl_mac_code_t status, 
				   uint8_t SecurityLevel, uint8_t KeyIdMode, 
				   uint8_t *KeySource, uint8_t KeyIndex);
#endif /* UWL_RFD_DISABLE_OPTIONAL */

int8_t uwl_MLME_DISASSOCIATE_request(uint8_t DeviceAddrMode, 
				     uint16_t DevicePANId,
				     uwl_mac_dev_addr_t DeviceAddress,
				     uint8_t DisassociateReason,
				     uint8_t TxIndirect, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex);

int8_t uwl_MLME_DISASSOCIATE_confirm(enum uwl_mac_code_t status,
				     uint8_t DeviceAddrMode,
				     uint16_t DevicePANId,
				     uwl_mac_dev_addr_t DeviceAddress);

int8_t uwl_MLME_DISASSOCIATE_indication(uwl_mac_dev_addr_extd_t DeviceAddress,
					uint8_t DisassociateReason,
					uint8_t SecurityLevel, 
					uint8_t KeyIdMode, uint8_t *KeySource,
					uint8_t KeyIndex);


int8_t uwl_MLME_BEACON_NOTIFY_indication(uint8_t BSN,
					 struct uwl_pan_des_t PANDescriptor,
					 uint8_t PendAddrSpec,
		 /*TODO: list? how?*/	 uwl_mac_dev_addr_t *AddrList, 
					 uint8_t sduLength, uint8_t *sdu);

int8_t uwl_MLME_GET_request(enum uwl_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex);
int8_t uwl_MLME_GET_confirm(enum uwl_mac_code_t status,
			    enum uwl_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex, 
			    void *PIBAttributeValue);

#ifndef UWL_DEVICE_DISABLE_OPTIONAL
int8_t uwl_MLME_GTS_request(uint8_t GTSCharacteristics, uint8_t SecurityLevel,
			    uint8_t KeyIdMode, uint8_t *KeySource,
			    uint8_t KeyIndex);

int8_t uwl_MLME_GTS_confirm(uint8_t GTSCharacteristics, 
			    enum uwl_mac_code_t status);

int8_t uwl_MLME_GTS_indication(uwl_mac_dev_addr_short_t DeviceAddress,
			       uint8_t GTSCharacteristics,
			       uint8_t SecurityLevel, uint8_t KeyIdMode,
			       uint8_t *KeySource, uint8_t KeyIndex);
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_ORPHAN_indication(uwl_mac_dev_addr_extd_t OrphanAddress,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex);

int8_t uwl_MLME_ORPHAN_response(uwl_mac_dev_addr_extd_t OrphanAddress,
				uwl_mac_dev_addr_short_t ShortAddress,
				uint8_t AssociatedMember, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex);
#endif /* UWL_RFD_DISABLE_OPTIONAL */

int8_t uwl_MLME_RESET_request(uint8_t SetDefaultPIB);
int8_t uwl_MLME_RESET_confirm(enum uwl_mac_code_t status);

#ifndef UWL_DEVICE_DISABLE_OPTIONAL
int8_t uwl_MLME_RX_ENABLE_request(uint8_t DeferPermit, uint32_t RxOnTime,
				  uint32_t RxOnDuration);

int8_t uwl_MLME_RX_ENABLE_confirm(enum uwl_mac_code_t status);
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

int8_t uwl_MLME_SCAN_request(uint8_t ScanType, uint32_t ScanChannels,
			     uint8_t ScanDuration, uint8_t ChannelPage,
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex);

int8_t uwl_MLME_SCAN_confirm(enum uwl_mac_code_t status, uint8_t ScanType,
			     uint8_t ChannelPage, uint32_t UnscannedChannels,
/*TODO: good represent.?*/   uint16_t ResultListSize, uint8_t *EnergyDetectList,
			     struct uwl_pan_des_t *PANDescriptorList);

int8_t uwl_MLME_COMM_STATUS_indication(uint16_t PANId, uint8_t SrcAddrMode,
				       uwl_mac_dev_addr_t SrcAddr,
				       uint8_t DstAddrMode,
				       uwl_mac_dev_addr_t DstAddr,
				       enum uwl_mac_code_t status,
				       uint8_t SecurityLevel, uint8_t KeyIdMode,
				       uint8_t KeySource, uint8_t KeyIndex);

int8_t uwl_MLME_SET_request(enum uwl_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex,
                            void *PIBAttributeValue);

int8_t uwl_MLME_SET_confirm(enum uwl_mac_code_t status,
			    enum uwl_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex);

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_START_request(uint16_t PANId, uint8_t LogicalChannel,
			      uint8_t ChannelPage, uint32_t StartTime,
			      uint8_t BeaconOrder, uint8_t SuperframeOrder,
			      uint8_t PANCoordinator, 
			      uint8_t BatteryLifeExtension,
			      uint8_t CoordRealignment,
			      uint8_t CoordRealignSecurityLevel,
			      uint8_t CoordRealignKeyIdMode,
			      uint8_t *CoordRealignKeySource,
			      uint8_t CoordRealignKeyIndex,
			      uint8_t BeaconSecurityLevel,
			      uint8_t BeaconKeyIdMode,
			      uint8_t *BeaconKeySource,
			      uint8_t BeaconKeyIndex);

int8_t uwl_MLME_START_confirm(enum uwl_mac_code_t status);
#endif /* UWL_RFD_DISABLE_OPTIONAL */

#ifndef UWL_DEVICE_DISABLE_OPTIONAL
int8_t uwl_MLME_SYNC_request(uint8_t LogicalChannel, uint8_t ChannelPage,
			     uint8_t TrackBeacon);
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

int8_t uwl_MLME_SYNC_LOSS_indication(enum uwl_mac_code_t LossReason,
				     uint8_t PANId, uint8_t LogicalChannel,
				     uint8_t ChannelPage, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex);

int8_t uwl_MLME_POLL_request(uint8_t CoordAddrMode, uint16_t CoordPANId,
			     uwl_mac_dev_addr_t CoordAddress, 
			     uint8_t SecurityLevel, uint8_t KeyIdMode,
			     uint8_t *KeySource, uint8_t KeyIndex);

int8_t uwl_MLME_POLL_confirm(enum uwl_mac_code_t status);

#endif /* Header Protection */
