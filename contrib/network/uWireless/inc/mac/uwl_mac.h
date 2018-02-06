/** 
* @file uwl_mac.h
* @brief IEEE 802.15.4 MAC Layer Public Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_h__
#define __uwl_mac_h__

#include <mac/uwl_mac_const.h>
#include <mac/uwl_mac_types.h>	
#include <mac/uwl_mac_mcps.h>
#include <mac/uwl_mac_mlme.h>

#define UWL_MAC_EXTD_ADDR_SET(address, high, low) 	\
do {							\
	(address)[0] = (low);				\
	(address)[1] = (high);				\
} while (0)						\


#define UWL_MAC_EXTD_ADDR_GET(address, high, low) 	\
do {							\
	(low) = (address)[0];				\
	(high) = (address)[1];				\
} while (0)						\


#define UWL_MAC_EXTD_ADDR_COMPARE(address1, address2) 	\
	(((address1)[0] == (address2)[0]) && ((address1)[1] == (address2)[1]))

#define UWL_MAC_EXTD_ADDR_COMPARE_IMM(address, high, low) 	\
	(((address)[0] == (low) && ((address)[1] == (high))))


#define UWL_MAC_MPDU_FRAME_CONTROL(mpdu) 		(mpdu)
#define UWL_MAC_MPDU_SEQ_NUMBER(mpdu) 			((mpdu) + 2)
#define UWL_MAC_MPDU_ADDRESSING_FIELDS(mpdu) 		((mpdu) + 3)
#define UWL_MAC_MPDU_AUX_SECURITY_HEADER(mpdu, offset) 	((mpdu) + 3 + (offset))
#define UWL_MAC_MPDU_MAC_PAYLOAD(mpdu, offset) 		((mpdu) + 3 + (offset))
#define UWL_MAC_MPDU_MAC_FCS(mpdu, offset) 		((mpdu) + 3 + (offset))

#define UWL_MAC_MPDU_COMMAND_FRAME_IDENTIFIER(mpdu, offset)	((mpdu) + 3 + (offset))
#define UWL_MAC_MPDU_CAPABILITY_INFORMATION(mpdu, offset)	((mpdu) + 4 + (offset))
#define UWL_MAC_MPDU_SHORT_ADDRESS(mpdu, offset)	((mpdu) + 4 + (offset))
#define UWL_MAC_MPDU_ASSOCIATION_STATUS(mpdu, offset)	((mpdu) + 6 + (offset))
#define UWL_MAC_MPDU_MAC_COMMAND_FIELDS(mpdu, offset) 		((mpdu) + 3 + (offset))

#define UWL_MAC_MPDU_GET_SEQ_NUMBER(mpdu)	(*(mpdu))
#define UWL_MAC_MPDU_GET_COMMAND_FRAME_ID(cmd)	(*(cmd))
#define UWL_MAC_MPDU_GET_CAPABILITY_INFORMATION(cmd)	(*(cmd))
#define UWL_MAC_MPDU_GET_SHORT_ADDRESS(cmd)	(*(cmd))
#define UWL_MAC_MPDU_GET_STATUS(cmd)	(*(cmd))

#define UWL_MAC_FCTL_GET_FRAME_TYPE(fcf) 	((*(fcf)) & 0x07)
#define UWL_MAC_FCTL_GET_SECURITY(fcf) 		(((*(fcf)) >> 3) & 0x01)
#define UWL_MAC_FCTL_GET_FRAME_PENDING(fcf) 	(((*(fcf)) >> 4) & 0x01)
#define UWL_MAC_FCTL_GET_ACK_REQUEST(fcf) 	(((*(fcf)) >> 5) & 0x01)
#define UWL_MAC_FCTL_GET_PANID_COMPRESS(fcf) 	(((*(fcf)) >> 6) & 0x01)
#define UWL_MAC_FCTL_GET_DST_ADDR_MODE(fcf)	((((fcf)[1]) >> 2) & 0x03)
#define UWL_MAC_FCTL_GET_FRAME_VERSION(fcf)	((((fcf)[1]) >> 4) & 0x03)
#define UWL_MAC_FCTL_GET_SRC_ADDR_MODE(fcf)	((((fcf)[1]) >> 6) & 0x03)

#define UWL_MAC_SF_SPEC_GET_BO(ss)		((*(ss)) & 0x0F)
#define UWL_MAC_SF_SPEC_GET_SO(ss)		((*(ss)) >> 4)
#define UWL_MAC_SF_SPEC_GET_LAST_CAP_TSLOT(ss)	(((ss)[1]) & 0x0F)
#define UWL_MAC_SF_SPEC_GET_BLE(ss)		((((ss)[1]) >> 4) & 0x03)
#define UWL_MAC_SF_SPEC_GET_PAN_COORD(ss)	((((ss)[1]) >> 6) & 0x01)
#define UWL_MAC_SF_SPEC_GET_ASSOC_PERMIT(ss)	((((ss)[1]) >> 7) & 0x01)


/*
#define UWL_MAC_MPDU_SF_SPECIFICATION(mpdu, offset) 	((mpdu) + 3 + (offset))
#define UWL_MAC_MPDU_GTS_FIELDS(mpdu, offset) 		((mpdu) + 5 + (offset))
#define UWL_MAC_MPDU_PENDING_ADDRESSES(mpdu, offset) 	((mpdu) + 6 + (offset))
#define UWL_MAC_MPDU_BEACON_PAYLOAD(mpdu, offset) 	((mpdu) + 7 + (offset))
*/

#define UWL_MAC_GTS_SPEC_SET_EMPTY(gts_spec) 				\
	(*(gts_spec) = 0)						\

#define UWL_MAC_GTS_SPEC_SET_DESCRIPTOR_COUNT(gts_spec, cnt) 		\
	(*(gts_spec) = (*(gts_spec) & 0xF8) | ((cnt) & 0x07))		\

#define UWL_MAC_GTS_SPEC_SET_PERMIT(gts_spec, permit) 			\
	(*(gts_spec) = (*(gts_spec) & 0x7F) | ((permit)) << 7)		\

#define UWL_MAC_GTS_DIRECTION_SET(gts_dirs, id, val) 			   \
	(*(gts_dirs) = (*(gts_dirs) & (~(0x1 << (id))))	| ((val)) << (id)) \


#define UWL_MAC_GTS_SPEC_GET_DESCRIPTOR_COUNT(gts_spec) \
	(*(gts_spec) & 0x07)				\

#define UWL_MAC_GTS_SPEC_GET_PERMIT(gts_spec) 		\
	((*(gts_spec)) >> 7)				\

#define UWL_MAC_GTS_DIRECTION_GET(gts_dirs, id) 	\
	((*(gts_dirs) >> (id)) & 0x1) 			\

#define UWL_MAC_GTS_DES_GET_ADDRESS(gts_des) 		\
	(((uint8_t *)(gts_des))[0] + 			\
	(((uint16_t)((uint8_t *)(gts_des))[1]) << 8))	\


#define UWL_MAC_GTS_DES_GET_LENGTH(gts_des) 		\
	(((gts_des)[2]) >> 4)				\

#define UWL_MAC_GTS_DES_GET_START_SLOT(gts_des) 	\
	(((gts_des)[2]) & 0x0F)				\



#define UWL_MAC_PENDING_ADDR_SPEC_SET_EMPTY(pend_spec)			\
	(*(pend_spec) = 0)						\

#define UWL_MAC_PENDING_ADDR_SPEC_SET_SHORTS(pend_spec, cnt) 		\
	(*(pend_spec) = (*(pend_spec) & 0xF8) | ((cnt) & 0x07))		\

#define UWL_MAC_PENDING_ADDR_SPEC_SET_EXTDS(pend_spec, cnt) 		\
	(*(pend_spec) = (*(pend_spec) & 0x8F) | (((cnt) & 0x07) << 4))	\


int8_t uwl_mac_init(void); 

int8_t uwl_mac_gts_db_clean(void);

int8_t uwl_mac_gts_db_add(uwl_mac_dev_addr_short_t dev_addr, 
			  uint8_t len, uint8_t dir);

#ifndef CSMA_UNSLOTTED
int8_t uwl_mac_set_beacon_payload(uint8_t *data, uint8_t len);

int8_t uwl_mac_get_beacon_payload(uint8_t *data, uint8_t len);

int8_t uwl_mac_set_before_beacon_callback(void (* func)(void)); 

int8_t uwl_mac_set_on_beacon_callback(void (* func)(void));

int8_t uwl_mac_set_on_rx_beacon_callback(void (* func)(void));
#endif

int8_t uwl_mac_jammer_cap(uint8_t *data, uint8_t len);

uint8_t uwl_mac_is_tx_gts_allocated(void);

#endif /* Header Protection */
