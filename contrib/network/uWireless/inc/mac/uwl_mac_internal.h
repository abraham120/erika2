/**
* @file uwl_mac_internal.h
* @brief IEEE 802.15.4 MAC Layer Internals
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_internal_h__
#define __uwl_mac_internal_h__

#include <mac/uwl_mac.h>
#include <hal/uwl_radio.h>
#include <phy/uwl_phy.h>
#include <util/uwl_memory.h>

#define UWL_aBaseSlotDuration_btick	  3  /**< UWL_aBaseSlotDuration /
						  UWL_aUnitBackoffPeriod */
#define UWL_aBaseSuperframeDuration_btick 48 /**< UWL_aBaseSuperframeDuration /
						  UWL_aUnitBackoffPeriod */
#define UWL_aTurnaroundTime_btick	1 /**< ceiling( UWL_aTurnaroundTime /
						UWL_aUnitBackoffPeriod ) */
#define UWL_MAC_LIFS_PERIOD		2 /**< 	macMinLIFSPeriod /
						UWL_aUnitBackoffPeriod */
#define UWL_MAC_SIFS_PERIOD		1 /**<  Greater than macMinSIFSPeriod /
						UWL_aUnitBackoffPeriod */

#define UWL_MAC_GET_BI(bo) ((1UL << (bo)) * UWL_aBaseSuperframeDuration_btick)
#define UWL_MAC_GET_SD(so) ((1UL << (so)) * UWL_aBaseSuperframeDuration_btick)
#define UWL_MAC_GET_TS(so) ((1UL << (so)) * UWL_aBaseSlotDuration_btick)

#define UWL_MAC_GTS_SET_SCHEDULE(sched, slot, len, dir) 	\
	((sched) = ((sched) & 					\
		   (~(((0x1 << (len)) - 1) << (slot)) | 	\
		   (((0x1 << (len)) - 1) * (dir)) << (slot)) 	\

#define UWL_MAC_GTS_GET_SCHEDULE(sched, pos) (((sched) >> (pos)) & 0x1)

enum uwl_mac_state_id_t {
	UWL_MAC_SF_OFF 	= 0,	/**< Superframe is not present. */
	UWL_MAC_SF_CAP 	= 1,	/**< Stack in Contention Access Period. */
	UWL_MAC_SF_CFP	= 2,	/**< Stack in Collision Free Period. */
	UWL_MAC_SF_IDLE	= 3, 	/**< Stack in Idle Period. */
};

struct uwl_mac_flags_t {
	unsigned mac_initialized : 1;
	unsigned is_pan_coordinator : 1;
	unsigned is_coordinator : 1;
	unsigned is_associated : 1;
	unsigned beacon_enabled : 1;
	unsigned track_beacon : 1;
	unsigned sf_context : 2;
	unsigned count_beacon_lost : 4;
	unsigned sf_initialized : 1;
	unsigned has_rx_beacon : 1;
};

struct uwl_mac_gts_stat_t {
	unsigned descriptor_count : 3; // TODO: maybe is useless!!!
	unsigned first_cfp_tslot : 5;
	unsigned tx_start_tslot : 4;
	unsigned tx_length : 4;
	unsigned rx_start_tslot : 4;
	unsigned rx_length : 4;
};

struct uwl_mac_data_request_info {
	unsigned data_req : 1;
	uint16_t addr_pan;
	uwl_mac_dev_addr_extd_t addr_dev;
};

struct uwl_mac_associate_retry_t {
	uint8_t capability;
};

extern struct uwl_mac_pib_t uwl_mac_pib;
extern struct uwl_mac_flags_t uwl_mac_status;
extern struct uwl_mac_gts_stat_t uwl_mac_gts_stat;
extern cqueue_t uwl_mac_queue_cap;
//extern cqueue_t uwl_mac_queue_dev_gts;
//extern list_t uwl_mac_queue_coord_gts;
extern struct uwl_gts_info_t uwl_gts_schedule[UWL_MAC_GTS_MAX_NUMBER];
extern struct uwl_mac_data_request_info uwl_mac_data_req;
extern struct list_t uwl_mac_list_ind;
extern struct uwl_mac_associate_retry_t uwl_mac_associate_retry;

uint8_t uwl_mac_create_beacon(uwl_mpdu_ptr_t beacon);
void uwl_mac_parse_received_mpdu(uint8_t *psdu, uint8_t len);
void uwl_mac_perform_data_request(enum uwl_mac_addr_mode_t src_mode,
				  enum uwl_mac_addr_mode_t dst_mode,
				  uint16_t dst_panid, void *dst_addr,
				  uint8_t len, uint8_t *payload,
				  uint8_t handle, uint8_t tx_opt /*,
				  uint8_t sec_lev, uint8_t key_id_mode,
				  uint8_t *key_src, uint8_t key_idx */);

int8_t uwl_mac_gts_init(void);
uint8_t uwl_mac_gts_set_gts_fields(uint8_t *gf);
uint8_t uwl_mac_gts_get_gts_fields(uint8_t *gf);
void uwl_mac_association_request_cmd(enum uwl_mac_addr_mode_t dst_mode,
										uint16_t dst_panid,
										void *dst_addr,
										uint8_t cap_inform);
void uwl_mac_association_response_cmd(void *dst_addr,
		 uwl_mac_dev_addr_short_t assoc_short_address,
		 uint8_t status);
void uwl_mac_ack_frame(uint8_t *seq_num);
void uwl_mac_data_request_cmd(void);

COMPILER_INLINE void uwl_mac_gts_set_cap_end(uint8_t last_cap_tslot)
{
	uwl_mac_gts_stat.first_cfp_tslot = last_cap_tslot + 1;
}

COMPILER_INLINE uint8_t uwl_mac_gts_get_cap_end(void)
{
	return uwl_mac_gts_stat.first_cfp_tslot - 1;
}

COMPILER_INLINE uint8_t uwl_mac_gts_get_cap_size(void)
{
	return uwl_mac_gts_stat.first_cfp_tslot;
}


int8_t uwl_mac_superframe_init(void);
int8_t uwl_mac_csma_unslotted_init(void);
void uwl_mac_superframe_start(uint32_t offset);
void uwl_mac_superframe_stop(void);
void uwl_mac_superframe_resync(void);
void uwl_mac_superframe_gts_wakeup(uint8_t gts_idx);
uint8_t uwl_mac_superframe_check_gts(uint8_t lenght, uint8_t gts_idx);
struct uwl_gts_info_t *uwl_mac_gts_get_first(void);
struct uwl_gts_info_t *uwl_mac_gts_get_next(void);
void uwl_gts_queue_flush(uint8_t gts_idx);
uint8_t uwl_gts_queue_is_empty(uint8_t gts_idx);
struct uwl_mac_frame_t *uwl_gts_queue_extract(uint8_t gts_idx);


#endif /* Header Protection */
