/**
* @file uwl_simple154.c
* @brief Simple IEEE 802.15.4 Implementation
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @version 0.1
* @date 2009-06-22
*/
#include <net/uwl_simple154.h>
#include <util/uwl_debug.h>
#include <string.h>

struct uwl_simple154_flags_t {
	unsigned wait_confirm : 1;
	unsigned initialized : 1;
	unsigned coordinator : 1;
};

static volatile struct uwl_simple154_flags_t flags = {
	.wait_confirm = 0,
	.initialized = 0,
	.coordinator = 0
};

static int8_t mac_error;
static int8_t last_error;
static uint16_t coordinator_pan_id;
static uint16_t coordinator_address;
/* static uint8_t msdu_handle_id = 0; */
static void (*rx_callback) (int8_t, uint8_t*, uint8_t, uint16_t) = NULL;
static uint8_t rx_buffer[UWL_MAC_MAX_MSDU_SIZE];
static uwl_mac_dev_addr_short_t AssocShortAddress = 0x0020;


#define RETURN_WITH_ERROR(e) 		\
do {					\
	last_error = (e);		\
	return (e);			\
} while (0)				\

void uwl_simple154_set_rx_callback(void (*func) (int8_t, uint8_t*, uint8_t,
				   		 uint16_t))
{
	rx_callback = func;
}

int8_t uwl_simple154_get_mac_error(void)
{
	return mac_error;
}


int8_t uwl_simple154_init_coordinator(uint16_t coordinator_id, uint16_t pan_id,
				      uint8_t channel, uint8_t bo, uint8_t so)
{
	if (flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_ALREADYINIT);
	mac_error = uwl_mac_init();
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_INITMAC);
	mac_error = uwl_MLME_SET_request(UWL_MAC_SHORT_ADDRESS, 0,
					 (void *) &coordinator_id);
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_SETADDR);
	/* TODO: channel scan phase */
	flags.wait_confirm = 1;
	mac_error = uwl_MLME_START_request(pan_id, 	/* PanID */
					   channel, 	/* Logical Channel*/
					   0, 	/* Channel Page */
					   0, 	/* Srtart Time */
					   bo, 	/* BO */
					   so, 	/* SO */
					   UWL_TRUE,	/* PAN Coordinator */
					   0, 	/* Battery Life Ext */
					   UWL_FALSE,/* Coord. Realignment */
					   UWL_MAC_NULL_SECURITY_PARAMS_LIST,
					   UWL_MAC_NULL_SECURITY_PARAMS_LIST);
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_STARTMAC);
	while (flags.wait_confirm) ;
	if (last_error < 0)
		return last_error;
	flags.initialized = 1;
	flags.coordinator = 1;
	coordinator_pan_id = pan_id;
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_init_device(uint16_t device_id, uint16_t coordinator_id,
				 uint16_t pan_id, uint8_t channel)
{
	uint8_t capability;

	if (flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_ALREADYINIT);
	mac_error = uwl_mac_init();
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_INITMAC);
	capability = uwl_mac_capability_information(UWL_FALSE, /*AltPanCoord*/
						    UWL_DEVICE_FFD, /*DevType*/
						    UWL_TRUE, /*PowerSource*/
						    UWL_TRUE, /*RxOn When Idle*/
						    UWL_FALSE, /*Security*/
						    UWL_TRUE); /*Allocate Addr*/
	flags.wait_confirm = 1;
	mac_error = uwl_MLME_ASSOCIATE_request(channel,	   /* Logical Channel*/
					       0,          /* Channel Page */
					       UWL_MAC_ADDRESS_SHORT,/* mode */
					       pan_id, 	   /* CoordPanID */
					       (void*) &coordinator_id,
					       capability, /* Capability Infos*/
					       UWL_MAC_NULL_SECURITY_PARAMS_LIST
					       );
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_ASSOCIATE);
	while (flags.wait_confirm);
	if (last_error < 0)
		return last_error;

#ifdef UWL_NO_DYN_ASS
	mac_error = uwl_MLME_SET_request(UWL_MAC_SHORT_ADDRESS, 0,
             (void *) &device_id);
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_SETADDR);
#endif

	flags.initialized = 1;
	flags.coordinator = 0;
	coordinator_address = coordinator_id;
	coordinator_pan_id = pan_id;
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_send(uint8_t *data, uint8_t len, uint16_t dst_device_id,
			  uint8_t use_gts)
{
	/* TODO: current implementation is non-blocking and ignore if success */
	if (!flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTINIT);
//	if (flags.coordinator && use_gts)
//		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTSUPPORTED);
	if (!flags.coordinator)
		dst_device_id = coordinator_address;
//	flags.wait_confirm = 1;
	mac_error = uwl_MCPS_DATA_request(UWL_MAC_ADDRESS_SHORT,
					  UWL_MAC_ADDRESS_SHORT,
					  coordinator_pan_id,
					  (void *) &dst_device_id,
					  len, data,
					  0, /* msdu_handle_id, */
					  uwl_mac_set_tx_options(0, use_gts, 0),
					  UWL_MAC_NULL_SECURITY_PARAMS_LIST);
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_DATAREQ);
	/* msdu_handle_id++; */
//	while (flags.wait_confirm) ;
//	if (last_error < 0)
//		return last_error;
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_gts_clear(void)
{
	if (!flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTINIT);
	if (!flags.coordinator)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_GTS_NOTCOORDINATOR);
	mac_error = uwl_mac_gts_db_clean();
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_GTS_MANIPULATION);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_gts_add(uint16_t device_id, uint8_t length, uint8_t dir)
{
	if (!flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTINIT);
	if (!flags.coordinator)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_GTS_NOTCOORDINATOR);
	mac_error = uwl_mac_gts_db_add(device_id, length, dir);
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_GTS_MANIPULATION);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_set_beacon_payload(uint8_t *data, uint8_t len)
{
	if (!flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTINIT);
	if (!flags.coordinator)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_GTS_NOTCOORDINATOR);
	mac_error = uwl_mac_set_beacon_payload(data, len);
	if (mac_error < 0)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_INVALID_LENGTH);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_get_beacon_payload(uint8_t *data, uint8_t len)
{
	int8_t real_len;

	if (!flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTINIT);
	real_len = uwl_mac_get_beacon_payload(data, len);
	if (real_len < 0) {
		mac_error = real_len;
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_INVALID_LENGTH);
	}
	return real_len;
}

int8_t uwl_simple154_set_on_beacon_callback(void (* func)(void))
{
	mac_error = uwl_mac_set_on_beacon_callback(func);
	if (mac_error < 0)
		RETURN_WITH_ERROR(
			UWL_SIMPLE154_ERR_SUPERFRAME_CALLBACKS_DISABLED);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_set_on_rx_beacon_callback(void (* func)(void))
{
	mac_error = uwl_mac_set_on_rx_beacon_callback(func);
	if (mac_error < 0)
		RETURN_WITH_ERROR(
			UWL_SIMPLE154_ERR_SUPERFRAME_CALLBACKS_DISABLED);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_set_before_beacon_callback(void (* func)(void))
{
	mac_error = uwl_mac_set_before_beacon_callback(func);
	if (mac_error < 0)
		RETURN_WITH_ERROR(
			UWL_SIMPLE154_ERR_SUPERFRAME_CALLBACKS_DISABLED);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

int8_t uwl_simple154_jam_cap(uint8_t *data, uint8_t len)
{
	if (!flags.initialized)
		RETURN_WITH_ERROR(-UWL_SIMPLE154_ERR_NOTINIT);
	mac_error = uwl_mac_jammer_cap(data, len);
	if (mac_error < 0)
		RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_INVALID_JAMMER);
	RETURN_WITH_ERROR(UWL_SIMPLE154_ERR_NONE);
}

/******************************************************************************/
/*                     MAC EVENTS (confirm, indication)                       */
/******************************************************************************/
int8_t uwl_MCPS_DATA_confirm(uint8_t msduHandle, enum uwl_mac_code_t status,
			     uint32_t Timestamp)
{
	/*
	#ifdef UWL_DEBUG_LOG
	char s[100];
	char s1[40];
	if (status == UWL_MAC_INVALID_GTS)
		return 1;
	uwl_debug_sprint_maccode(status, s1);
	sprintf(s, "MCPS_DATA_confirm(%d, %s,...)", msduHandle, s1);
	uwl_debug_print(s);
	#endif
	*/
	if (status != UWL_MAC_SUCCESS)
		last_error = -UWL_SIMPLE154_ERR_DATACONFIRM;
	flags.wait_confirm = 0;
	return 1;
}

int8_t uwl_MCPS_DATA_indication(uint8_t SrcAddrMode, uint16_t SrcPANId,
				void *SrcAddr, uint8_t DstAddrMode,
				uint16_t DstPANId, void *DstAddr,
				uint8_t msduLength, uint8_t *msdu,
				uint8_t mpduLinkQuality, uint8_t DSN,
				uint32_t Timestamp, uint8_t SecurityLevel,
				uint8_t KeyIdMode, uint8_t *KeySource,
				uint8_t KeyIndex)
{
	uint16_t src;
	/* NOTE: the rx_buffer could be a local buffer! */

	/* TODO: solve mutex problem on test_packet due to race condition! */
	if (rx_callback != NULL && msduLength <= UWL_MAC_MAX_MSDU_SIZE) {
		memset(rx_buffer, 0x00, UWL_MAC_MAX_MSDU_SIZE);
		memcpy(rx_buffer, msdu, msduLength);
		if (SrcAddrMode == UWL_MAC_ADDRESS_SHORT)
			memcpy(&src, SrcAddr, sizeof(uint16_t));
		else
			src = 0xFFFE;
		rx_callback(UWL_SIMPLE154_ERR_NONE, rx_buffer, msduLength, src);
	}
	return 1;
}

int8_t uwl_MCPS_PURGE_confirm(uint8_t msduHandle, enum uwl_mac_code_t status)
{
	return 1;
}


int8_t uwl_MLME_ASSOCIATE_confirm(uwl_mac_dev_addr_short_t AssocShortAddress,
				  enum uwl_mac_code_t status,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	if (status != UWL_MAC_SUCCESS)
		last_error = -UWL_SIMPLE154_ERR_ASSOCIATE;
	flags.wait_confirm = 0;
	return 1;
}

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_ASSOCIATE_indication(uwl_mac_dev_addr_extd_t DeviceAddress,
				     uint8_t CapabilityInformation,
				     uint8_t SecurityLevel, uint8_t KeyIdMode,
				     uint8_t *KeySource, uint8_t KeyIndex)
{

	AssocShortAddress++;
//#ifdef UWL_DEBUG_LOG
//char str[100];
//sprintf(str, "uwl_MLME_ASSOCIATE_indication(..)");
//uwl_debug_print(str);
//#endif
	uwl_MLME_ASSOCIATE_response(DeviceAddress,
					   AssocShortAddress,
					   UWL_MAC_SUCCESS,
					   SecurityLevel, KeyIdMode,
					   KeySource, KeyIndex);

	return 1;
}

#endif /* UWL_RFD_DISABLE_OPTIONAL */


int8_t uwl_MLME_DISASSOCIATE_confirm(enum uwl_mac_code_t status,
				     uint8_t DeviceAddrMode,
				     uint16_t DevicePANId,
				     uwl_mac_dev_addr_t DeviceAddress)
{
	return 1;
}

/*int8_t uwl_MLME_DISASSOCIATE_indication(uwl_mac_dev_addr_extd_t DeviceAddress,
					uint8_t DisassociateReason,
					uint8_t SecurityLevel,
					uint8_t KeyIdMode, uint8_t *KeySource,
					uint8_t KeyIndex)
{
	return 1;
}*/


int8_t uwl_MLME_BEACON_NOTIFY_indication(uint8_t BSN,
					 struct uwl_pan_des_t PANDescriptor,
					 uint8_t PendAddrSpec,
		 /*TODO: list? how?*/	 uwl_mac_dev_addr_t *AddrList,
					 uint8_t sduLength, uint8_t *sdu)
{
	return 1;
}

int8_t uwl_MLME_GET_confirm(enum uwl_mac_code_t status,
			    enum uwl_mac_pib_id_t PIBAttribute,
	/*TODO: enough?*/   uint16_t PIBAttributeIndex,
			    void *PIBAttributeValue)
{
	return 1;
}

#ifndef UWL_DEVICE_DISABLE_OPTIONAL
int8_t uwl_MLME_GTS_confirm(uint8_t GTSCharacteristics,
			    enum uwl_mac_code_t status)
{
	return 1;
}

int8_t uwl_MLME_GTS_indication(uwl_mac_dev_addr_short_t DeviceAddress,
			       uint8_t GTSCharacteristics,
			       uint8_t SecurityLevel, uint8_t KeyIdMode,
			       uint8_t *KeySource, uint8_t KeyIndex)
{
	return 1;
}
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_ORPHAN_indication(uwl_mac_dev_addr_extd_t OrphanAddress,
				  uint8_t SecurityLevel, uint8_t KeyIdMode,
				  uint8_t *KeySource, uint8_t KeyIndex)
{
	return 1;
}

#endif /* UWL_RFD_DISABLE_OPTIONAL */

int8_t uwl_MLME_RESET_confirm(enum uwl_mac_code_t status)
{
	return 1;
}

#ifndef UWL_DEVICE_DISABLE_OPTIONAL

int8_t uwl_MLME_RX_ENABLE_confirm(enum uwl_mac_code_t status)
{
	return 1;
}
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */

int8_t uwl_MLME_SCAN_confirm(enum uwl_mac_code_t status, uint8_t ScanType,
			     uint8_t ChannelPage, uint32_t UnscannedChannels,
/*TODO: good represent.?*/   uint16_t ResultListSize, uint8_t *EnergyDetectList,
			     struct uwl_pan_des_t *PANDescriptorList)
{
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
	return 1;
}

int8_t uwl_MLME_SET_confirm(enum uwl_mac_code_t status,
			    enum uwl_mac_pib_id_t PIBAttribute,
        /*TODO: enough?*/   uint16_t PIBAttributeIndex)
{
	flags.wait_confirm = 0;
	return 1;
}

#ifndef UWL_RFD_DISABLE_OPTIONAL
int8_t uwl_MLME_START_confirm(enum uwl_mac_code_t status)
{
	if (status != UWL_MAC_SUCCESS)
		last_error = -UWL_SIMPLE154_ERR_STARTMAC;
	flags.wait_confirm = 0;
	return 1;
}
#endif /* UWL_RFD_DISABLE_OPTIONAL */

int8_t uwl_MLME_SYNC_LOSS_indication(enum uwl_mac_code_t LossReason,
				     uint8_t PANId, uint8_t LogicalChannel,
				     uint8_t ChannelPage, uint8_t SecurityLevel,
				     uint8_t KeyIdMode, uint8_t *KeySource,
				     uint8_t KeyIndex)
{
	return 1;
}

int8_t uwl_MLME_POLL_confirm(enum uwl_mac_code_t status)
{
	return 1;
}
