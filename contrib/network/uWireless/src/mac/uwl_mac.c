/**
 * @file uwl_mac.c
 * @brief IEEE 802.15.4 MAC Layer General Part
 * @author Christian Nastasi
 * @author Daniele Alessandrelli
 * @version 0.1
 * @date 2009-06-22
 */
#include <mac/uwl_mac_internal.h>
#include <mac/uwl_mac_marshalling.h>
#include <kal/uwl_kal.h>
#include <hal/uwl_radio.h>
#include <hal/uwl_rand.h>
#include <util/uwl_debug.h>
#ifdef UWL_DEBUG_LOG
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

/******************************************************************************/
/*                          MAC Layer Private Data                            */
/******************************************************************************/
static uwl_mpdu_t rx_beacon;
static uwl_mpdu_t rx_data;
static uwl_mpdu_t rx_command;
static uwl_mpdu_t rx_ack;
static uint16_t rx_beacon_length;
static uint16_t rx_data_length;
static uint16_t rx_command_length;
static uint8_t beacon_payload_length = 0;
static uint8_t wait_ack = 0;
static uint8_t association_status = 0;
static uint8_t seq_num_ack;
static uint8_t beacon_payload[UWL_aMaxBeaconPayloadLength]
							COMPILER_ATTRIBUTE_FAR;
static struct uwl_mac_frame_t gts_queue_storage[UWL_MAC_GTS_QUEUE_SIZE]
							COMPILER_ATTRIBUTE_FAR;
static uint16_t gts_queue_rears[UWL_MAC_GTS_MAX_NUMBER];
/* NOTE: overlapping data structure for coordinator/device gts queues.*/
CQUEUE_DEFINE_EXTMEM_STATIC(uwl_mac_queue_dev_gts, struct uwl_mac_frame_t,
			    UWL_MAC_GTS_QUEUE_SIZE, gts_queue_storage);
LIST_DEFINE_EXTMEM_STATIC(uwl_mac_queue_coord_gts, struct uwl_mac_frame_t,
			  UWL_MAC_GTS_QUEUE_SIZE, gts_queue_storage);
#ifdef UWL_SUPERFRAME_CALLBACKS
static void (* on_rx_beacon_callback)(void) = NULL;
#endif

/******************************************************************************/
/*                          MAC Layer Public Data                             */
/******************************************************************************/
struct uwl_mac_flags_t uwl_mac_status = {
		.mac_initialized = 0,
		.is_pan_coordinator = 0,
		.is_coordinator = 0,
		.is_associated = 0,
		.beacon_enabled = 0,
		.track_beacon = 0,
		.sf_context = 0,
		.count_beacon_lost = 0,
		.sf_initialized = 0,
		.has_rx_beacon = 0 };
struct uwl_mac_pib_t uwl_mac_pib /*= {
 TODO: set a default values as already done for the phy_pib!
 }*/;
struct uwl_mac_gts_stat_t
		uwl_mac_gts_stat = {
				.descriptor_count = 0,
				.first_cfp_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT + 1,
				.tx_start_tslot = UWL_MAC_SUPERFRAME_FIRST_SLOT,
				.tx_length = 0,
				.rx_start_tslot = UWL_MAC_SUPERFRAME_FIRST_SLOT,
				.rx_length = 0 };

struct uwl_mac_data_request_info uwl_mac_data_req = {
		.data_req = 0,
		.addr_pan = 0,
		.addr_dev[0] = 0,
		.addr_dev[1] = 0 };

CQUEUE_DEFINE( uwl_mac_queue_cap, struct uwl_mac_frame_t,
		UWL_MAC_CAP_QUEUE_SIZE, COMPILER_ATTRIBUTE_FAR);
LIST_DEFINE( uwl_mac_list_ind, struct uwl_mac_frame_t, UWL_MAC_IND_LIST_SIZE,
		COMPILER_ATTRIBUTE_FAR);
/* TODO: used only by coordinator. */
struct uwl_gts_info_t uwl_gts_schedule[UWL_MAC_GTS_MAX_NUMBER]
COMPILER_ATTRIBUTE_FAR;

//Variable for associate request at the device, to resend association req.
struct uwl_mac_frame_t ass_req_ack_wait;
extern int16_t associate_ack_counter;
/******************************************************************************/
/*                                                                            */
/*                      MAC Layer Private Functions                           */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                          MAC General Functions                             */
/******************************************************************************/
static void set_default_mac_pib(void)
{
	/* chris: TODO: move all this literals in some defines in the
	 mac const file as already done for the default pib
	 attribute of the PHY pib */
	uwl_mac_pib.macAckWaitDuration = 54; /* TODO: apply equation!! */
	uwl_mac_pib.macAssociatedPANCoord = 0;
	uwl_mac_pib.macAutoRequest = 1;
	uwl_mac_pib.macBattLifeExt = 0;
	uwl_mac_pib.macBattLifeExtPeriods = 6; /* TODO: apply equation!! */
	UWL_MAC_EXTD_ADDR_SET(uwl_mac_pib.macCoordExtendedAddress, 0x0, 0x0);
	uwl_mac_pib.macCoordShortAddress = 0xFFFF;
	uwl_mac_pib.macDSN = uwl_rand_8bit();
	uwl_mac_pib.macMaxBE = 5;
	uwl_mac_pib.macMaxCSMABackoffs = 4;
	uwl_mac_pib.macMaxFrameTotalWaitTime = 0; /* TODO: apply equation!! */
	uwl_mac_pib.macMaxFrameRetries = 3;
	uwl_mac_pib.macMinBE = 3;
	uwl_mac_pib.macMinLIFSPeriod = 40; /* TODO: apply table!! */
	uwl_mac_pib.macMinSIFSPeriod = 12; /* TODO: apply table!! */
	uwl_mac_pib.macPANId = 0xFFFF;
	uwl_mac_pib.macResponseWaitTime = 32;
	uwl_mac_pib.macRxOnWhenIdle = 0;
	uwl_mac_pib.macSecurityEnabled = 0;
	uwl_mac_pib.macShortAddress = 0xFFFF;
	uwl_mac_pib.macSyncSymbolOffset = 0; /* TODO: apply equation!! */
	uwl_mac_pib.macTimestampSupported = 0; /* TODO: apply equation!! */
	uwl_mac_pib.macTransactionPersistenceTime = 0x01F4;
#ifndef UWL_DEVICE_DISABLE_OPTIONAL
	uwl_mac_pib.macGTSPermit = 1;
#endif /* UWL_DEVICE_DISABLE_OPTIONAL */
#ifndef UWL_RFD_DISABLE_OPTIONAL
	uwl_mac_pib.macAssociationPermit = 0;
	uwl_mac_pib.macBeaconPayload = NULL;
	uwl_mac_pib.macBeaconPayloadLenght = 0;
	uwl_mac_pib.macBeaconOrder = 15;
	uwl_mac_pib.macBeaconTxTime = 0x000000;
	uwl_mac_pib.macBSN = uwl_rand_8bit();
	uwl_mac_pib.macPromiscuousMode = 0;
	uwl_mac_pib.macSuperframeOrder = 15;
#endif /* UWL_RFD_DISABLE_OPTIONAL */
}

COMPILER_INLINE
uwl_mac_dev_addr_short_t addr_to_short(enum uwl_mac_addr_mode_t mode, void *dst)
{
	uwl_mac_dev_addr_short_t addr;

	if (mode == UWL_MAC_ADDRESS_SHORT) {
		addr = *((uwl_mac_dev_addr_short_t *) dst);
	} else { /* mode == UWL_MAC_ADDRESS_EXTD */
		/* TODO: use lookup table to resolve the corresponding short */
		addr = 0x0001;
	}
	return addr;
}

COMPILER_INLINE int8_t gts_search_device(uwl_mac_dev_addr_short_t addr)
{
	int8_t i;

	for (i = 0; i < UWL_MAC_GTS_MAX_NUMBER; i++)
		if (uwl_gts_schedule[i].dev_address == addr
				&& uwl_gts_schedule[i].length != 0
				&& uwl_gts_schedule[i].direction
						== UWL_MAC_GTS_DIRECTION_IN)
			return i;
	return -1;
}

COMPILER_INLINE struct uwl_mac_frame_t *gts_queue_alloc(uint8_t gts)
{
	uint8_t i;
	struct uwl_mac_frame_t *elem;

	if (!(uwl_mac_status.is_pan_coordinator
			|| uwl_mac_status.is_coordinator)) {
		return (struct uwl_mac_frame_t *) cqueue_push(
				&uwl_mac_queue_dev_gts);
	}
	/* TODO: what should be done if uwl_mac_status.is_coordinator ?
	 Is the node both coordinator and device in such a case?
	 Double storage is required in that case!
	 */
	elem = (struct uwl_mac_frame_t *) list_insert(&uwl_mac_queue_coord_gts,
			gts_queue_rears[gts]);
	if (elem != 0)
		/* Update rears for the coordinator gts queues */
		for (i = gts; i < UWL_MAC_GTS_MAX_NUMBER; i++)
			gts_queue_rears[i]++;
	return elem;
}

/******************************************************************************/
/*                       MAC Frames Build Functions                           */
/******************************************************************************/
COMPILER_INLINE
void set_frame_control(uint8_t *fcf, uint8_t frame_type, uint8_t security,
		uint8_t frame_pending, uint8_t ack_request,
		uint8_t panid_compress, uint8_t dst_addr_mode,
		uint8_t src_addr_mode, uint8_t frame_version)
{
	fcf[0] = (panid_compress << 6) | (ack_request << 5) | (frame_pending
			<< 4) | (security << 3) | (frame_type << 0);
	fcf[1] = (src_addr_mode << 6) | (frame_version << 4) | (dst_addr_mode
			<< 2);
}

COMPILER_INLINE
uint8_t set_addressing_fields(uint8_t *af, enum uwl_mac_addr_mode_t dst_mode,
		uint16_t dst_panid, void *dst_addr,
		enum uwl_mac_addr_mode_t src_mode, uint16_t src_panid,
		void *src_addr, uint8_t panid_compression)
{
	uint8_t offset = 0;

	if (dst_mode == UWL_MAC_ADDRESS_SHORT) {

		/*FIXME: problem with this instruction, solved by explicitly decompose
		* the uint16_t in 2 uint8_t
		* memcpy(af+offset, &dst_panid, sizeof(uint16_t));
		*/
		// af[offset] = (uint8_t) (dst_panid & 0xFF);
		// af[offset+1] = (uint8_t)(dst_panid >> 8);
		hton(af+offset, (uint8_t *)&dst_panid, UWL_MAC_MPDU_PANID_SIZE);
		offset += UWL_MAC_MPDU_PANID_SIZE;
		hton(af+offset, (uint8_t *)dst_addr, UWL_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_SHORT_SIZE;
		
	} else if (dst_mode == UWL_MAC_ADDRESS_EXTD) {
	
		hton(af + offset, (uint8_t *)&dst_panid, UWL_MAC_MPDU_PANID_SIZE);
		offset += UWL_MAC_MPDU_PANID_SIZE;
		hton(af + offset, (uint8_t *)dst_addr, UWL_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_EXTD_SIZE;
	
	}

	if (src_mode == UWL_MAC_ADDRESS_SHORT) {

		if (panid_compression == 0) {
			hton(af + offset, (uint8_t *)&src_panid, UWL_MAC_MPDU_PANID_SIZE);
			offset += UWL_MAC_MPDU_PANID_SIZE;
		}
		hton(af + offset, (uint8_t *)src_addr, UWL_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_SHORT_SIZE;
		
	} else if (src_mode == UWL_MAC_ADDRESS_EXTD) {
	
		if (panid_compression == 0) {
			hton(af + offset, (uint8_t *)&src_panid, UWL_MAC_MPDU_PANID_SIZE);
			offset += UWL_MAC_MPDU_PANID_SIZE;
		}
		hton(af + offset, (uint8_t *)src_addr, UWL_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_EXTD_SIZE;
		
	}
	return offset;
}

COMPILER_INLINE
uint8_t set_command_header(struct uwl_mac_frame_t *cmd, uint8_t security,
		uint8_t pending_frame, uint8_t ack_request,
		uint8_t panid_compress, uint8_t dst_addr_mode,
		uint8_t src_addr_mode, uint8_t frame_version,
		enum uwl_mac_addr_mode_t dst_mode, uint16_t dst_panid,
		void *dst_addr, enum uwl_mac_addr_mode_t src_mode,
		void * src_addr, uint16_t src_panid,
		enum uwl_mac_cmd_type_t cmd_type)
{
	uint8_t s;

	/* Build the mpdu header (MHR) */

	memset(cmd->mpdu, 0x0, sizeof(uwl_mpdu_t));

	set_frame_control(UWL_MAC_MPDU_FRAME_CONTROL(cmd->mpdu),
			UWL_MAC_TYPE_COMMAND, security,/* TODO: Use security infos (sec_level, etc.) */
			pending_frame, /* TODO: Use Pending List flag */
			ack_request, panid_compress, dst_addr_mode,
			src_addr_mode, frame_version);

	seq_num_ack = uwl_mac_pib.macDSN;
	*(UWL_MAC_MPDU_SEQ_NUMBER(cmd->mpdu)) = uwl_mac_pib.macDSN++;

	s = set_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(cmd->mpdu),
			dst_mode, dst_panid, dst_addr, src_mode, src_panid,
			src_addr, panid_compress);
	/* TODO: think to security infos? */

	(UWL_MAC_MPDU_COMMAND_FRAME_IDENTIFIER(cmd->mpdu, s))[0] = cmd_type;

	return s;

}

COMPILER_INLINE
uint8_t get_addressing_fields(uint8_t *af, enum uwl_mac_addr_mode_t dst_mode,
		uint16_t *dst_panid, void *dst_addr,
		enum uwl_mac_addr_mode_t src_mode, uint16_t *src_panid,
		void *src_addr, uint8_t panid_compression)
{
	uint8_t offset = 0;

	if (dst_mode == UWL_MAC_ADDRESS_SHORT) {
	
		if (dst_panid != NULL)
			ntoh((uint8_t *)dst_panid, af + offset, UWL_MAC_MPDU_PANID_SIZE);
		offset += UWL_MAC_MPDU_PANID_SIZE;
		if (dst_addr != NULL)
			ntoh((uint8_t *)dst_addr, af + offset, UWL_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_SHORT_SIZE;
		
	} else if (dst_mode == UWL_MAC_ADDRESS_EXTD) {
	
		if (dst_panid != NULL)
			ntoh((uint8_t *)dst_panid, af + offset, UWL_MAC_MPDU_PANID_SIZE);
		offset += UWL_MAC_MPDU_PANID_SIZE;
		if (dst_addr != NULL)
			ntoh((uint8_t *)dst_addr, af + offset, UWL_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_EXTD_SIZE;
		
	}

	if (src_mode == UWL_MAC_ADDRESS_SHORT) {
	
		if (panid_compression == 0) {
			if (src_panid != NULL)
				ntoh((uint8_t *)src_panid, af + offset, UWL_MAC_MPDU_PANID_SIZE);
			offset += UWL_MAC_MPDU_PANID_SIZE;
		}
		if (src_addr != NULL)
			ntoh((uint8_t *)src_addr, af + offset, UWL_MAC_MPDU_ADDRESS_SHORT_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_SHORT_SIZE;
		
	} else if (src_mode == UWL_MAC_ADDRESS_EXTD) {
	
		if (panid_compression == 0) {
			if (src_panid != NULL)
				ntoh((uint8_t *)src_panid, af + offset, UWL_MAC_MPDU_PANID_SIZE);
			offset += UWL_MAC_MPDU_PANID_SIZE;
		}
		if (src_addr != NULL)
			ntoh((uint8_t *)src_addr, af + offset, UWL_MAC_MPDU_ADDRESS_EXTD_SIZE);
		offset += UWL_MAC_MPDU_ADDRESS_EXTD_SIZE;
		
	}

	return offset;
}

COMPILER_INLINE
uint8_t set_superframe_specification(uint8_t *ss, uint8_t bo, uint8_t so,
		uint8_t final_cap_slot, uint8_t ble, uint8_t pan_coord,
		uint8_t assoc_permit)
{
	ss[0] = (bo << 0) | (so << 4);
	ss[1] = (final_cap_slot << 0) | (ble) << 4 | (pan_coord << 6)
			| (assoc_permit << 7);
	return UWL_MAC_MPDU_SUPERFRAME_SPEC_SIZE;
}

COMPILER_INLINE uint8_t set_pending_address_fields(uint8_t *pf)
{
	UWL_MAC_PENDING_ADDR_SPEC_SET_EMPTY(pf);
	/*
	 UWL_MAC_PENDING_ADDR_SPEC_SET_SHORTS(pf, 0);
	 UWL_MAC_PENDING_ADDR_SPEC_SET_EXTDS(pf, 0);
	 */
	return 1;
}

COMPILER_INLINE uint8_t set_beacon_payload(uint8_t *bp)
{
	uint8_t len;

	uwl_kal_mutex_wait(MAC_MUTEX);
	if (beacon_payload_length > 0)
		memcpy(bp, beacon_payload, beacon_payload_length);
	len = beacon_payload_length;
	uwl_kal_mutex_signal(MAC_MUTEX);
	return len;
}

static uint8_t filtering_condition(uint8_t *fctrl, uint16_t dst_panid,
		void *dst_addr, uint16_t src_panid)
{
	/* 3rd frame filter:  */
	/* TODO: check Frame Version invalid!! */
	if (UWL_MAC_FCTL_GET_FRAME_TYPE(fctrl) == UWL_MAC_TYPE_BEACON) {
		if (uwl_mac_pib.macPANId != UWL_MAC_PANID_BROADCAST
				&& src_panid != uwl_mac_pib.macPANId)
			return 0;
	} else {
		if (dst_panid != UWL_MAC_PANID_BROADCAST && dst_panid
				!= uwl_mac_pib.macPANId)
			return 0;
	}
	if ((UWL_MAC_FCTL_GET_FRAME_TYPE(fctrl) == UWL_MAC_TYPE_DATA
			|| UWL_MAC_FCTL_GET_FRAME_TYPE(fctrl)
					== UWL_MAC_TYPE_COMMAND)
			&& UWL_MAC_FCTL_GET_DST_ADDR_MODE(fctrl)
					== UWL_MAC_ADDRESS_NONE
			&& UWL_MAC_FCTL_GET_SRC_ADDR_MODE(fctrl)
					!= UWL_MAC_ADDRESS_NONE) {
		if (uwl_mac_status.is_pan_coordinator == UWL_FALSE || src_panid
				!= uwl_mac_pib.macPANId)
			return 0;
	}
	if (UWL_MAC_FCTL_GET_DST_ADDR_MODE(fctrl) == UWL_MAC_ADDRESS_SHORT) {
		if ((*((uwl_mac_dev_addr_short_t*) dst_addr)
				!= uwl_mac_pib.macShortAddress)
				&& (*((uwl_mac_dev_addr_short_t*) dst_addr)
						!= UWL_MAC_SHORT_ADDRESS_BROADCAST))
			return 0;
	} else if (UWL_MAC_FCTL_GET_DST_ADDR_MODE(fctrl)
			== UWL_MAC_ADDRESS_EXTD) {
		if (!UWL_MAC_EXTD_ADDR_COMPARE_IMM(
				(uwl_mac_dev_addr_extd_ptr_t) dst_addr,
				UWL_aExtendedAddress_high,
				UWL_aExtendedAddress_low))
			return 0;
	}
	return 1;
}

/******************************************************************************/
/*                              MAC Layer TASKs                               */
/******************************************************************************/
UWL_KAL_TASK_ASYNC(MAC_PROCESS_RX_BEACON, 25);
UWL_KAL_TASK_ASYNC(MAC_PROCESS_RX_DATA, 20);
UWL_KAL_TASK_ASYNC(MAC_PROCESS_RX_COMMAND, 20);

/* IMPORTANT NOTE:
 * The mutexes that might be used in the context of possible PHY tasks,
 * that call the MAC notification functions, MUST be declared in the
 * file "mac/uwl_mac_mutexes.h" as body of the macro
 * UWL_PHY_IMPORT_MAC_MUTEXES().
 */
UWL_KAL_MUTEX( MAC_RX_BEACON_MUTEX, MAC_PROCESS_RX_BEACON);
UWL_KAL_MUTEX( MAC_RX_DATA_MUTEX, MAC_PROCESS_RX_DATA);
UWL_KAL_MUTEX( MAC_RX_COMMAND_MUTEX, MAC_PROCESS_RX_COMMAND);

static void process_rx_beacon(void)
{
	uint8_t s;
	uint8_t *bcn;
	uint16_t s_pan = 0;
	uwl_mac_dev_addr_extd_t s_a;

	if (uwl_kal_mutex_wait(MAC_RX_BEACON_MUTEX) < 0)
		return; /* TODO: manage error? */
	/* NOTE: Src Address is supposed to exist. NO Dst Address.
	 Assuming a pre-check in the dispatcher ? */
	bcn = UWL_MAC_MPDU_FRAME_CONTROL(rx_beacon);
	s = get_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(rx_beacon),
			UWL_MAC_ADDRESS_NONE, NULL, NULL,
			UWL_MAC_FCTL_GET_SRC_ADDR_MODE(bcn), &s_pan,
			(void *) s_a, 0);
	/* Note that the dst_pan_id (arg.2) is ignored in case of beacon.*/
	if (!filtering_condition(bcn, 0, NULL, s_pan)) {
		/* Drop the frame! */
		uwl_kal_mutex_signal(MAC_RX_BEACON_MUTEX);/*TODO:manage error?*/
		return;
	}
	bcn = UWL_MAC_MPDU_MAC_PAYLOAD(rx_beacon, s);
	uwl_mac_pib.macBeaconOrder = UWL_MAC_SF_SPEC_GET_BO(bcn);
	uwl_mac_pib.macSuperframeOrder = UWL_MAC_SF_SPEC_GET_SO(bcn);
	uwl_mac_gts_set_cap_end(UWL_MAC_SF_SPEC_GET_LAST_CAP_TSLOT(bcn));
	/*TODO: Use the BLE fiels w.r.t the std */
	uwl_mac_pib.macAssociationPermit
			= UWL_MAC_SF_SPEC_GET_ASSOC_PERMIT(bcn);
	/* TODO: read BO and SO and update the PIB!! */
	bcn += UWL_MAC_MPDU_SUPERFRAME_SPEC_SIZE;
	bcn += uwl_mac_gts_get_gts_fields(bcn);
	bcn += UWL_MAC_MPDU_PENDING_ADDR_SPEC_SIZE;
	/* TODO: compute FCS , use auto gen? */
	// consider 2 bytes in the following formula
	beacon_payload_length = rx_beacon_length - (bcn - rx_beacon);
	if (beacon_payload_length > 0)
		memcpy(beacon_payload, bcn, beacon_payload_length);
	if (uwl_kal_mutex_signal(MAC_RX_BEACON_MUTEX) < 0)
		return; /* TODO: manage error? */
	uwl_mac_superframe_resync();
#ifdef UWL_SUPERFRAME_CALLBACKS
	if (on_rx_beacon_callback)
		on_rx_beacon_callback();
#endif
}

static void process_rx_data(void)
{
	uint8_t s, len;
	uint8_t *data;
	uint16_t s_pan = 0, d_pan = 0;
	uwl_mac_dev_addr_extd_t s_a, d_a;

	if (uwl_kal_mutex_wait(MAC_RX_DATA_MUTEX) < 0)
		return; /* TODO: manage error? */
	data = UWL_MAC_MPDU_FRAME_CONTROL(rx_data);
	s = get_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(rx_data),
			UWL_MAC_FCTL_GET_DST_ADDR_MODE(data), &d_pan,
			(void *) d_a, UWL_MAC_FCTL_GET_SRC_ADDR_MODE(data),
			&s_pan, (void *) s_a, UWL_MAC_FCTL_GET_PANID_COMPRESS(
					data));
	if (!filtering_condition(data, d_pan, (void*) d_a, s_pan)) {
		uwl_kal_mutex_signal(MAC_RX_DATA_MUTEX);/*TODO:manage error?*/
		return;
	}
	if (UWL_MAC_FCTL_GET_PANID_COMPRESS(data))
		s_pan = d_pan;
	len = rx_data_length - UWL_MAC_MPDU_FRAME_CONTROL_SIZE
			- UWL_MAC_MPDU_SEQ_NUMBER_SIZE - s;
	uwl_MCPS_DATA_indication(UWL_MAC_FCTL_GET_SRC_ADDR_MODE(data), s_pan,
			(void *) s_a, UWL_MAC_FCTL_GET_DST_ADDR_MODE(data),
			d_pan, (void *) d_a, len, UWL_MAC_MPDU_MAC_PAYLOAD(
					rx_data, s),
			0 /*TODO: mpduLinkQuality*/, *(UWL_MAC_MPDU_SEQ_NUMBER(
					rx_data))/*CHECK!*/,
			0 /*TODO: timestamp!! */,
			UWL_MAC_NULL_SECURITY_PARAMS_LIST);
	if (uwl_kal_mutex_signal(MAC_RX_DATA_MUTEX) < 0)
		return; /* TODO: manage error? */
}

static void process_rx_command(void)
{
	uint8_t s, i;
	uint8_t *cmd;
	uint16_t s_pan = 0, d_pan = 0;
	uwl_mac_dev_addr_extd_t s_a, d_a;
	uint8_t cap_inf;
	enum uwl_mac_code_t status;

	uwl_debug_print("process_rx_command()");
	if (uwl_kal_mutex_wait(MAC_RX_COMMAND_MUTEX) < 0)
		return; /* TODO: manage error? */
	cmd = UWL_MAC_MPDU_FRAME_CONTROL(rx_command);

	s = get_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(rx_command),
			UWL_MAC_FCTL_GET_DST_ADDR_MODE(cmd), &d_pan,
			(void *) d_a, UWL_MAC_FCTL_GET_SRC_ADDR_MODE(cmd),
			&s_pan, (void *) s_a, UWL_MAC_FCTL_GET_PANID_COMPRESS(
					cmd));

	/* Moved to the callback in order to speed-up the ack reply */
//	if (UWL_MAC_FCTL_GET_ACK_REQUEST(cmd)) {
//		cmd = UWL_MAC_MPDU_SEQ_NUMBER(rx_command);
//		uwl_mac_ack_frame(cmd); //rx_command
//	}

	if (UWL_MAC_FCTL_GET_PANID_COMPRESS(cmd))
		s_pan = d_pan;

	cmd = UWL_MAC_MPDU_MAC_COMMAND_FIELDS(rx_command, s);

	switch (UWL_MAC_MPDU_GET_COMMAND_FRAME_ID(cmd)) {
	case UWL_MAC_CMD_ASSOCIATION_REQUEST:
		cmd = UWL_MAC_MPDU_MAC_COMMAND_FIELDS(rx_command, (s + 1));
		cap_inf = UWL_MAC_MPDU_GET_CAPABILITY_INFORMATION(cmd);

		i = uwl_MLME_ASSOCIATE_indication((void *) s_a, cap_inf, 0,
				*(UWL_MAC_MPDU_SEQ_NUMBER(rx_command)), 0, 0);
		break;
	case UWL_MAC_CMD_DATA_REQUEST:
		uwl_mac_data_req.addr_pan = d_pan;
		memcpy(uwl_mac_data_req.addr_dev, s_a,
				UWL_MAC_MPDU_ADDRESS_EXTD_SIZE);
		uwl_mac_data_req.data_req = 1;
		uwl_debug_print("proc_rx_command(): UWL_MAC_CMD_DATA_REQUEST");
		break;
	case UWL_MAC_CMD_ASSOCIATION_RESPONSE:
		association_status = 0;
		cmd = UWL_MAC_MPDU_SHORT_ADDRESS(rx_command, s);
		uwl_mac_pib.macShortAddress = *cmd;
		cmd = UWL_MAC_MPDU_ASSOCIATION_STATUS(rx_command, s);
		status = UWL_MAC_MPDU_GET_STATUS(cmd);
		uwl_MLME_ASSOCIATE_confirm(uwl_mac_pib.macShortAddress, status,
				0, 0, NULL, 0);
		break;
	default:
		break;
	}

	if (uwl_kal_mutex_signal(MAC_RX_COMMAND_MUTEX) < 0)
		return; /* TODO: manage error? */
}

static void process_rx_ack(void)
{
	uint8_t *ack;
	uint8_t *seq_num;

	ack = UWL_MAC_MPDU_FRAME_CONTROL(rx_ack);
	seq_num = UWL_MAC_MPDU_SEQ_NUMBER(ack);
	if (wait_ack == 1 && UWL_MAC_MPDU_GET_SEQ_NUMBER(seq_num)
			== seq_num_ack && association_status == 1) {
		uwl_mac_data_request_cmd();
	}
}

COMPILER_INLINE int8_t init_rx_tasks(void)
{
	int retv;

	retv = uwl_kal_init(0);
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_PROCESS_RX_BEACON, process_rx_beacon);
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_PROCESS_RX_DATA, process_rx_data);
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_PROCESS_RX_COMMAND, process_rx_command);
	if (retv < 0)
		return retv;
	return 1;
}

/******************************************************************************/
/*                                                                            */
/*                       MAC Layer Public Functions                           */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*                          MAC General Functions                             */
/******************************************************************************/
int8_t uwl_mac_init(void)
{
	int8_t retv = 1;

#ifdef UWL_DEBUG
	if (uwl_debug_init() < 0)
	return -UWL_MAC_ERR_DEBUG_INIT;
#endif
	uwl_mac_status.mac_initialized = 0;
	uwl_mac_status.is_pan_coordinator = 0;
	uwl_mac_status.is_coordinator = 0;
	uwl_mac_status.is_associated = 0;
	uwl_mac_status.beacon_enabled = 0;
	uwl_mac_status.sf_initialized = 0;
	uwl_mac_status.sf_context = 0;
	uwl_rand_init();
	retv = uwl_phy_init();
	if (retv < 0)
		return retv;
	set_default_mac_pib();
	cqueue_clear(&uwl_mac_queue_cap);
	cqueue_clear(&uwl_mac_queue_dev_gts);
	list_clear(&uwl_mac_queue_coord_gts);
	list_clear(&uwl_mac_list_ind);
	memset(gts_queue_rears, 0, sizeof(uint16_t) * UWL_MAC_GTS_MAX_NUMBER);
	retv = init_rx_tasks();
	if (retv < 0)
		return retv;

	retv = uwl_mac_superframe_init();
	if (retv < 0)
		return retv;
	retv = uwl_mac_gts_init();
	if (retv < 0)
		return retv;

	//return -UWL_MAC_INIT_ERROR;
	uwl_mac_status.mac_initialized = 1;
	return 1;
}

int8_t uwl_mac_get_beacon_payload(uint8_t *data, uint8_t len)
{
	/* NOTE: mutex condition is guaranteed due to
	 * task activation mechanism and the following flag */
	if (!uwl_mac_status.has_rx_beacon)
		return -100; //TODO: add error code
	if (beacon_payload_length == 0)
		return 0;
	if (len > beacon_payload_length)
		len = beacon_payload_length;
	memcpy(data, beacon_payload, len);
	return (int8_t) len;
}

int8_t uwl_mac_set_beacon_payload(uint8_t *data, uint8_t len)
{
	if (len > UWL_aMaxBeaconPayloadLength)
		return -UWL_MAC_ERR_INVALID_LENGTH;
	uwl_kal_mutex_wait(MAC_MUTEX);
	if (len > 0)
		memcpy(beacon_payload, data, len);
	beacon_payload_length = len;
	uwl_kal_mutex_signal(MAC_MUTEX);
	return UWL_MAC_ERR_NONE;
}

int8_t uwl_mac_jammer_cap(uint8_t *data, uint8_t len)
{
#ifdef UWL_HAS_JAMMER
	if (uwl_mac_status.sf_context != UWL_MAC_SF_CAP || len == 0)
	return -1; /* TODO: write appropriate error code */
	if (len > UWL_aMaxMACPayloadSize)
	len = UWL_aMaxMACPayloadSize;
	uwl_radio_phy_send_now((EE_UINT8 *)data, len);
	return 1;
#else
	return -1; /* TODO: write appropriate error code */
#endif
}

int8_t uwl_mac_set_on_rx_beacon_callback(void(* func)(void))
{
#ifdef UWL_SUPERFRAME_CALLBACKS
	on_rx_beacon_callback = func;
	return UWL_MAC_ERR_NONE;
#else
	return -UWL_MAC_ERR_SUPERFRAME_CALLBACKS_DISABLED;
#endif
}

/******************************************************************************/
/*                  MAC GTS queue 'protected' Functions                       */
/******************************************************************************/
void uwl_gts_queue_flush(uint8_t gts)
{
	struct uwl_mac_frame_t *fr;
	uint8_t i;
	uint16_t cnt;

	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		/* TODO: FIXME: CURRENT POLICY: DON'T FLUSH*/
		return;
		fr = (struct uwl_mac_frame_t *) list_pop_front(
				&uwl_mac_queue_coord_gts);
		cnt = 0;
		/* TODO: FIXME: rewrite!!! */
		while (fr != 0 && cnt < gts_queue_rears[gts]) {
			uwl_MCPS_DATA_confirm(fr->msdu_handle,
					UWL_MAC_INVALID_GTS, 0);
			fr = (struct uwl_mac_frame_t *) list_pop_front(
					&uwl_mac_queue_coord_gts);
			cnt++;
			/* Update rears for the coordinator gts queues */
			for (i = gts; i < UWL_MAC_GTS_MAX_NUMBER; i++)
				gts_queue_rears[i]--;
		}
	} else {
		fr = (struct uwl_mac_frame_t*) cqueue_pop(
				&uwl_mac_queue_dev_gts);
		while (fr != 0) {
			uwl_MCPS_DATA_confirm(fr->msdu_handle,
					UWL_MAC_INVALID_GTS, 0);
			fr = (struct uwl_mac_frame_t *) cqueue_pop(
					&uwl_mac_queue_dev_gts);
		}
	}
}

uint8_t uwl_gts_queue_is_empty(uint8_t gts)
{
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		if (gts == 0)
			return (gts_queue_rears[gts] == 0);
		return (gts_queue_rears[gts] == gts_queue_rears[gts - 1]);
	} else {
		return cqueue_is_empty(&uwl_mac_queue_dev_gts);
	}
}

struct uwl_mac_frame_t *uwl_gts_queue_extract(uint8_t gts)
{
	uint8_t i;

	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		if (gts == 0) {
			if (gts_queue_rears[gts] == 0)
				return 0;
		} else {
			if (gts_queue_rears[gts] == gts_queue_rears[gts - 1])
				return 0;
		}
		/* Update rears for the coordinator gts queues */
		for (i = gts; i < UWL_MAC_GTS_MAX_NUMBER; i++)
			gts_queue_rears[i]--;
		if (gts == 0)
			return (struct uwl_mac_frame_t*) list_pop_front(
					&uwl_mac_queue_coord_gts);
		else
			return (struct uwl_mac_frame_t*) list_extract(
					&uwl_mac_queue_coord_gts,
					gts_queue_rears[gts - 1]);
	} else {
		return (struct uwl_mac_frame_t*) cqueue_pop(
				&uwl_mac_queue_dev_gts);
	}
}

/******************************************************************************/
/*                       MAC Frames Build Functions                           */
/******************************************************************************/
/* chris: TODO: Split this function in more the one */
void uwl_mac_perform_data_request(enum uwl_mac_addr_mode_t src_mode,
		enum uwl_mac_addr_mode_t dst_mode, uint16_t dst_panid,
		void *dst_addr, uint8_t len, uint8_t *payload, uint8_t handle,
		uint8_t tx_opt /*,
 uint8_t sec_lev, uint8_t key_id_mode,
 uint8_t *key_src, uint8_t key_idx */)
{
	uint8_t s;
	//char str[1000];
	struct
	{
		unsigned compress :1;
		unsigned version :1;
	} flag;
	struct uwl_mac_frame_t *frame;
	uwl_mac_dev_addr_extd_t e_addr;
	int8_t gts_idx = 0;

	uwl_debug_print("DATA REQ TX :");
	if (UWL_MAC_TX_OPTION_GTS(tx_opt) == UWL_TRUE) {
		if (uwl_mac_status.is_pan_coordinator
				|| uwl_mac_status.is_coordinator) {
			gts_idx = gts_search_device(addr_to_short(dst_mode,
					dst_addr));
			//sprintf(str, "---> SEND GTS: Q=%u GTS=%d ADR=0x%X",
			//	list_get_size(&uwl_mac_queue_coord_gts), gts_idx,
			//	addr_to_short(dst_mode, dst_addr));
			//uwl_debug_print(str);
			//sprintf(str, "---> schedule: [ (%X,%u,%u) (%X,%u,%u) (%X,%u,%u) (%X,%u,%u)"
			//		"	(%X,%u,%u) (%X,%u,%u) (%X,%u,%u) ]",
			//			uwl_gts_schedule[0].dev_address,
			//			uwl_gts_schedule[0].length,
			//			uwl_gts_schedule[0].direction,
			//			uwl_gts_schedule[1].dev_address,
			//			uwl_gts_schedule[1].length,
			//			uwl_gts_schedule[1].direction,
			//			uwl_gts_schedule[2].dev_address,
			//			uwl_gts_schedule[2].length,
			//			uwl_gts_schedule[2].direction,
			//			uwl_gts_schedule[3].dev_address,
			//			uwl_gts_schedule[3].length,
			//			uwl_gts_schedule[3].direction,
			//			uwl_gts_schedule[4].dev_address,
			//			uwl_gts_schedule[4].length,
			//			uwl_gts_schedule[4].direction,
			//			uwl_gts_schedule[5].dev_address,
			//			uwl_gts_schedule[5].length,
			//			uwl_gts_schedule[5].direction,
			//			uwl_gts_schedule[6].dev_address,
			//			uwl_gts_schedule[6].length,
			//			uwl_gts_schedule[6].direction
			//			);
			//uwl_debug_print(str);

			if (gts_idx < 0) {
				uwl_MCPS_DATA_confirm(handle,
						UWL_MAC_INVALID_GTS, 0);
				uwl_debug_print("--->        Invalid GTS");
				return;
			}
		}
		if (!uwl_mac_superframe_check_gts(len, (uint8_t) gts_idx)) {
			//uwl_debug_print("DEVICE:  GTS CHECK FAIL ");
			uwl_MCPS_DATA_confirm(handle, UWL_MAC_INVALID_GTS, 0);
			uwl_debug_print("--->        Invalid CHECK");
			return;
		}

		uwl_kal_mutex_wait(MAC_GTS_SEND_MUTEX);
		/* Store in the GTS queue! */
		frame = gts_queue_alloc((uint8_t) gts_idx);
		if (frame == 0) {
			//uwl_debug_print("DEVICE:  GTS QUEUE FULL!!! ");
			/* TODO: we have to choose a well formed reply
			 for the indication primitive (status=??) */
			uwl_MCPS_DATA_confirm(handle, UWL_MAC_INVALID_GTS, 0);
			uwl_debug_print("--->        Invalid ALLOC");
			return;
		}
		//sprintf(str, "---> SEND OK: Q = %u", list_get_size(&uwl_mac_queue_coord_gts));
		//uwl_debug_print(str);
	} else { /* Store in the CSMA-CA queue */
		//uwl_debug_print("DEVICE:  CSMA QUEUE FULL!!! ");
		uwl_kal_mutex_wait(MAC_SEND_MUTEX);
		frame = (struct uwl_mac_frame_t*) cqueue_push(
				&uwl_mac_queue_cap);
		if (frame == 0) {
			/* TODO: we have to choose a well formed reply
			 for the indication primitive (status=??) */
			uwl_kal_mutex_signal(MAC_SEND_MUTEX);
			uwl_MCPS_DATA_confirm(handle,
					UWL_MAC_CHANNEL_ACCESS_FAILURE, 0);
			return;
		}
	}
	frame->msdu_handle = handle;
	/* Build the mpdu header (MHR) */
	memset(frame->mpdu, 0x0, sizeof(uwl_mpdu_t));
	flag.compress = (src_mode != UWL_MAC_ADDRESS_NONE && dst_mode
			!= UWL_MAC_ADDRESS_NONE && dst_panid
			== uwl_mac_pib.macPANId) ? 1 : 0;
	flag.version = (/*TODO: if has security set (sec_level?) &&*/
	len > UWL_aMaxMACSafePayloadSize) ? 1 : 0;
	set_frame_control(UWL_MAC_MPDU_FRAME_CONTROL(frame->mpdu),
			UWL_MAC_TYPE_DATA, 0,/* TODO: Use security infos (sec_level, etc.) */
			0, /* TODO: Use Pending List flag */
			UWL_MAC_TX_OPTION_ACK(tx_opt), flag.compress, dst_mode,
			src_mode, flag.version);
	*(UWL_MAC_MPDU_SEQ_NUMBER(frame->mpdu)) = uwl_mac_pib.macDSN++;
	if (src_mode == UWL_MAC_ADDRESS_EXTD
			|| (src_mode == UWL_MAC_ADDRESS_SHORT
					&& (uwl_mac_pib.macShortAddress
							== UWL_MAC_SHORT_ADDRESS_USE_EXTD
							|| uwl_mac_pib.macShortAddress
									== UWL_MAC_SHORT_ADDRESS_INVALID))){

		UWL_MAC_EXTD_ADDR_SET(e_addr, UWL_aExtendedAddress_high,
				UWL_aExtendedAddress_low);
		s = set_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(frame->mpdu),
				dst_mode, dst_panid, dst_addr, UWL_MAC_ADDRESS_EXTD,
				uwl_mac_pib.macPANId, (void *) e_addr, flag.compress);
	}
	else {
		/* TODO: can be short_none??? */
		s = set_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(frame->mpdu),
			dst_mode, dst_panid, dst_addr, UWL_MAC_ADDRESS_SHORT,
			uwl_mac_pib.macPANId, (void *) &(uwl_mac_pib.macShortAddress), flag.compress);
	}
	/* TODO: think to security infos? */
	/* Store the msdu (Mac Payload) */
	memcpy(UWL_MAC_MPDU_MAC_PAYLOAD(frame->mpdu, s), payload, len);
	/* TODO: compute FCS , use auto gen? */
	//*((uint16_t *) UWL_MAC_MPDU_MAC_FCS(bcn, s)) = 0;

	frame->mpdu_size = UWL_MAC_MPDU_FRAME_CONTROL_SIZE
			+ UWL_MAC_MPDU_SEQ_NUMBER_SIZE + s + len /* +
	 sizeof(uint16_t) */;
	if (UWL_MAC_TX_OPTION_GTS(tx_opt) == UWL_TRUE)
		uwl_mac_superframe_gts_wakeup(gts_idx);
	uwl_debug_print("--->       OK (in TX Queue)");

	/* Free the blocked resources*/
	if (UWL_MAC_TX_OPTION_GTS(tx_opt) == UWL_TRUE) {
		uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
	} else {
		uwl_kal_mutex_signal(MAC_SEND_MUTEX);
	}
}

uint8_t uwl_mac_create_beacon(uwl_mpdu_ptr_t bcn)
{
	uint8_t s;
	uwl_mac_dev_addr_extd_t e_addr;

	memset(bcn, 0x0, sizeof(uwl_mpdu_t));
	set_frame_control(UWL_MAC_MPDU_FRAME_CONTROL(bcn), UWL_MAC_TYPE_BEACON,
			uwl_mac_pib.macSecurityEnabled, 0, /* TODO: Use Pending List flag */
			0, 0, /* Zeros and ignored in case of Beacon */
			UWL_MAC_ADDRESS_NONE, UWL_MAC_ADDRESS_SHORT,
			uwl_mac_pib.macSecurityEnabled /*TODO: check std*/);
	*(UWL_MAC_MPDU_SEQ_NUMBER(bcn)) = uwl_mac_pib.macBSN++;
	if (uwl_mac_pib.macShortAddress == UWL_MAC_SHORT_ADDRESS_USE_EXTD) {
		UWL_MAC_EXTD_ADDR_SET(e_addr, UWL_MAC_DEVICE_EXTD_ADDRESS_HIGH,
				UWL_MAC_DEVICE_EXTD_ADDRESS_LOW);
		s = set_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(bcn),
				UWL_MAC_ADDRESS_NONE, 0, NULL,
				UWL_MAC_ADDRESS_EXTD, uwl_mac_pib.macPANId,
				(void*) e_addr, 0);
	} else {
		s = set_addressing_fields(UWL_MAC_MPDU_ADDRESSING_FIELDS(bcn),
				UWL_MAC_ADDRESS_NONE, 0, NULL,
				UWL_MAC_ADDRESS_SHORT, uwl_mac_pib.macPANId,
				(void*) &(uwl_mac_pib.macShortAddress), 0);
	}
	/* TODO: think to security infos? */
	s += set_superframe_specification(UWL_MAC_MPDU_MAC_PAYLOAD(bcn, s),
			uwl_mac_pib.macBeaconOrder,
			uwl_mac_pib.macSuperframeOrder,
			uwl_mac_gts_get_cap_end(), 0, /*TODO: Use w.r.t the std */
			uwl_mac_status.is_pan_coordinator,
			uwl_mac_pib.macAssociationPermit);
	s += uwl_mac_gts_set_gts_fields(UWL_MAC_MPDU_MAC_PAYLOAD(bcn, s));
	s += set_pending_address_fields(UWL_MAC_MPDU_MAC_PAYLOAD(bcn, s));
	s += set_beacon_payload(UWL_MAC_MPDU_MAC_PAYLOAD(bcn, s));
	/* TODO: compute FCS , use auto gen? */
	//*((uint16_t *) UWL_MAC_MPDU_MAC_FCS(bcn, s)) = 0;
	//s += UWL_MAC_MPDU_MHR_BASE_SIZE + UWL_MAC_MPDU_MFR_SIZE;
	s += UWL_MAC_MPDU_MHR_BASE_SIZE;
	return s;
}

/*create association request cmd */

void uwl_mac_association_request_cmd(enum uwl_mac_addr_mode_t dst_mode,
		uint16_t dst_panid, void *dst_addr, uint8_t cap_inform)
{
	uint8_t s;
	uwl_mac_dev_addr_extd_t e_addr;
	struct uwl_mac_frame_t *cmd_ass_req;

	uwl_kal_mutex_wait(MAC_SEND_MUTEX);
	cmd_ass_req = (struct uwl_mac_frame_t*) cqueue_push(&uwl_mac_queue_cap);
	if (cmd_ass_req == 0) {
		/* TODO: we have to choose a well formed reply
		 for the indication primitive (status=??) */
		uwl_kal_mutex_signal(MAC_SEND_MUTEX);
		return;
	}

	UWL_MAC_EXTD_ADDR_SET(e_addr, UWL_aExtendedAddress_high,
			UWL_aExtendedAddress_low);

	s = set_command_header(cmd_ass_req, 0, 0, 1, 0, dst_mode,
			UWL_MAC_ADDRESS_EXTD, 0, dst_mode, dst_panid, dst_addr,
			UWL_MAC_ADDRESS_EXTD, (void *) e_addr, UWL_MAC_PANID_BROADCAST,
			UWL_MAC_CMD_ASSOCIATION_REQUEST);

	(UWL_MAC_MPDU_CAPABILITY_INFORMATION(cmd_ass_req->mpdu, s))[0]
			= cap_inform;

	cmd_ass_req->mpdu_size = UWL_MAC_MPDU_FRAME_CONTROL_SIZE
			+ UWL_MAC_MPDU_SEQ_NUMBER_SIZE + s
			+ UWL_MAC_COMMAND_FRAME_IDENTIFIER_SIZE
			+ UWL_MAC_CAPABILITY_INFORMATION_SIZE/* +
	 sizeof(uint16_t) */;

	wait_ack = 1;
	association_status = 1;

	uwl_kal_mutex_signal(MAC_SEND_MUTEX);
}

/* create association response */

void uwl_mac_association_response_cmd(void *dst_addr,
		uwl_mac_dev_addr_short_t assoc_short_address, uint8_t status)
{
	uint8_t s;

	struct uwl_mac_frame_t *cmd_ass_res;

	uwl_kal_mutex_wait(MAC_SEND_MUTEX);
	cmd_ass_res = (struct uwl_mac_frame_t*) list_push_front(
			&uwl_mac_list_ind);

	if (cmd_ass_res == 0) {
		/* TODO: we have to choose a well formed reply
		 for the indication primitive (status=??) */
		uwl_kal_mutex_signal(MAC_SEND_MUTEX);
		return;
	}

	s = set_command_header(cmd_ass_res, //struct uwl_mac_frame_t *cmd
			0, //uint8_t security
			0, //uint8_t pending_frame
			1, //uint8_t ack_request
			1, //uint8_t panid_compress
			UWL_MAC_ADDRESS_EXTD, //uint8_t dst_addr_mode
			UWL_MAC_ADDRESS_SHORT, //uint8_t src_addr_mode
			0, //uint8_t frame_version
			UWL_MAC_ADDRESS_EXTD, //enum uwl_mac_addr_mode_t dst_mode
			uwl_mac_pib.macPANId, //uint16_t dst_panid
			dst_addr, //void *dst_addr
			UWL_MAC_ADDRESS_SHORT, //enum uwl_mac_addr_mode_t src_mode
			(void*) &(uwl_mac_pib.macShortAddress), //void * src_addr
			UWL_MAC_ADDRESS_NONE, //uint16_t src_panid
			UWL_MAC_CMD_ASSOCIATION_RESPONSE //enum uwl_mac_cmd_type_t cmd_type
			);

	(UWL_MAC_MPDU_SHORT_ADDRESS(cmd_ass_res->mpdu, s))[0]
			= assoc_short_address;

	(UWL_MAC_MPDU_ASSOCIATION_STATUS(cmd_ass_res->mpdu, s))[0] = status;

	cmd_ass_res->mpdu_size = UWL_MAC_MPDU_FRAME_CONTROL_SIZE
			+ UWL_MAC_MPDU_SEQ_NUMBER_SIZE + s
			+ UWL_MAC_COMMAND_FRAME_IDENTIFIER_SIZE
			+ UWL_MAC_SHORT_ADDRESS_SIZE
			+ UWL_MAC_ASSOCIATION_STATUS_SIZE/* +
	 sizeof(uint16_t) */;

	uwl_kal_mutex_signal(MAC_SEND_MUTEX);
}

/* create ack frame */

void uwl_mac_ack_frame(uint8_t *seq_num)
{
	uwl_mpdu_t ack;
	uint8_t s;

	set_frame_control(ack, UWL_MAC_TYPE_ACK, 0, 0, 0, 0, 0, 0, 0);

	*(UWL_MAC_MPDU_SEQ_NUMBER(ack)) = UWL_MAC_MPDU_GET_SEQ_NUMBER(seq_num);

	s = UWL_MAC_MPDU_FRAME_CONTROL_SIZE + UWL_MAC_MPDU_SEQ_NUMBER_SIZE/* +
	 sizeof(uint16_t) */;

	uwl_radio_store_ack(ack, s);
	uwl_radio_send_ack();
}

void uwl_mac_data_request_cmd(void)
{
	uint8_t s;
	struct uwl_mac_frame_t *data_req;
	uwl_mac_dev_addr_extd_t e_addr;

	uwl_kal_mutex_wait(MAC_SEND_MUTEX);

	associate_ack_counter = -255;
	data_req = (struct uwl_mac_frame_t*) cqueue_push(&uwl_mac_queue_cap);
	if (data_req == 0) {
		/* TODO: we have to choose a well formed reply
		 for the indication primitive (status=??) */
		uwl_kal_mutex_signal(MAC_SEND_MUTEX);
		return;
	}

	UWL_MAC_EXTD_ADDR_SET(e_addr, UWL_aExtendedAddress_high,
			UWL_aExtendedAddress_low);

	s = set_command_header(data_req, //struct uwl_mac_frame_t *cmd
			0, //uint8_t security
			0, //uint8_t pending_frame
			1, //uint8_t ack_request
			1, //uint8_t panid_compress
			UWL_MAC_ADDRESS_SHORT, //uint8_t dst_addr_mode
			UWL_MAC_ADDRESS_EXTD, //uint8_t src_addr_mode
			0, //uint8_t frame_version
			UWL_MAC_ADDRESS_SHORT, //enum uwl_mac_addr_mode_t dst_mode
			uwl_mac_pib.macPANId, //uint16_t dst_panid uwl_mac_pib.macPANId
			&uwl_mac_pib.macCoordShortAddress, //void *dst_addr
			UWL_MAC_ADDRESS_EXTD, //enum uwl_mac_addr_mode_t src_mode
			(void *) e_addr, //void * src_addr
			UWL_MAC_ADDRESS_NONE, //uint16_t src_panid
			UWL_MAC_CMD_DATA_REQUEST //enum uwl_mac_cmd_type_t cmd_type
			);

	data_req->mpdu_size = UWL_MAC_MPDU_FRAME_CONTROL_SIZE
			+ UWL_MAC_MPDU_SEQ_NUMBER_SIZE + s
			+ UWL_MAC_COMMAND_FRAME_IDENTIFIER_SIZE/* +
	 sizeof(uint16_t) */;

	wait_ack = 0;

	uwl_kal_mutex_signal(MAC_SEND_MUTEX);

}

/******************************************************************************/
/*                       MAC MPDU Parsing Functions                           */
/******************************************************************************/
#ifdef __JUST_MEASURE_FOR_PAPER__
#include "daq_time.h"
#endif
void uwl_mac_parse_received_mpdu(uint8_t *psdu, uint8_t len)
{
#ifdef UWL_DEBUG_LOG
	char str[100];
#endif
	/* 1st frame filter: FCS */
	/* TODO: Checksum is done by the transceiver, fix this!!! */
	/* 2nd frame filter: promiscuous mode */
	if (uwl_mac_pib.macPromiscuousMode == UWL_TRUE)
		return; /* TODO: pass the frame to the upper layer! (see std) */
	/* TODO: perform some discarding action depending on the context :
	 What if I am coordinator? */

	/* Moved from process_rx_command in order to speed up the ack reply */
	if (UWL_MAC_FCTL_GET_ACK_REQUEST(psdu)) {
		uwl_mac_ack_frame(UWL_MAC_MPDU_SEQ_NUMBER(psdu)); //rx_command
	}

	switch (UWL_MAC_FCTL_GET_FRAME_TYPE(psdu)) {
	case UWL_MAC_TYPE_BEACON:
		if (uwl_mac_status.is_pan_coordinator
				|| uwl_mac_status.is_coordinator)
			return; /* TODO: check if this is correct w.r.t std */
		/* TODO: make an extra compare, to see if Frame Control Field
		 is valid for a beacon, no_dest address, a_src address*/
		if (uwl_kal_mutex_wait(MAC_RX_BEACON_MUTEX) < 0)
			return; /* TODO: manage error? */
		memcpy(rx_beacon, psdu, len);
		rx_beacon_length = len;
		uwl_kal_activate(MAC_PROCESS_RX_BEACON);
		if (uwl_kal_mutex_signal(MAC_RX_BEACON_MUTEX) < 0)
			return; /* TODO: manage error? */
		break;
	case UWL_MAC_TYPE_DATA:
#ifdef __JUST_MEASURE_FOR_PAPER__
daq_time_start(1); // FIXME: this is just for AVR time measurement!
#endif
		if (uwl_kal_mutex_wait(MAC_RX_DATA_MUTEX) < 0)
			return; /* TODO: manage error? */
		memcpy(rx_data, psdu, len);
		rx_data_length = len;
		uwl_kal_activate(MAC_PROCESS_RX_DATA);
		if (uwl_kal_mutex_signal(MAC_RX_DATA_MUTEX) < 0)
			return; /* TODO: manage error? */
		break;
	case UWL_MAC_TYPE_COMMAND:
		#ifdef UWL_DEBUG_LOG
		sprintf(str, "uwl_mac_parse_received_mpdu(*p=%p,len=%u)",
			 psdu, len);
		uwl_debug_print(str);
		#endif
		if (uwl_kal_mutex_wait(MAC_RX_COMMAND_MUTEX) < 0)
			return; /* TODO: manage error? */
		memcpy(rx_command, psdu, len);
		rx_command_length = len;
		uwl_kal_activate(MAC_PROCESS_RX_COMMAND);
		if (uwl_kal_mutex_signal(MAC_RX_COMMAND_MUTEX) < 0)
			return; /* TODO: manage error? */
		break;
	case UWL_MAC_TYPE_ACK:
		memcpy(rx_ack, psdu, len);
		process_rx_ack();

		break;
	default:
		break;
	}
}

uint8_t uwl_mac_is_tx_gts_allocated(void) {
	return uwl_mac_gts_stat.tx_length;
}
