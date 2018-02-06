/**
 * @file
 * @brief This header file declares MAC internal functions, globals, and macros.
 *
 * $Id: mac.h,v 1.1 2007/06/22 13:50:48 romano Exp $
 */
/**
 *  \author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2006, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MAC_HEADER
#define MAC_HEADER



/* === Includes ============================================================= */
#ifndef DEF_H
#include "def.h"
#endif

#include <stdbool.h>

#include "board.h"
#include "avrtypes.h"
#include "ieee_const.h"
#include "msg_types.h"
#include "bios.h"


#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

#include "data_structures.h"

/* === Externals ============================================================ */

// This define makes sure that the transmission of a beacon frame does
// properly intercept an already ongoing CSMA-CA process.  Might be
// required due to improper backoff timing or an evil device out there
// violating timings.
#define CSMA_CA_INTERCEPTION    1

/* Global data variables */
extern uint8_t          mac_FinalCapSlot;
extern uint32_t         mac_RollOverTime;
extern uint32_t         mac_SOInactiveTime;
extern bool             mac_ack_flag;
extern uint32_t         mac_battlife_latest_start;
extern bool             mac_beacon_flag;
extern uint8_t          mac_beacon_payload[];
extern uint8_t          mac_buffer[aMaxPHYPacketSize + sizeof(pd_data_ind_t)];
extern uint8_t          mac_current_channel;
extern bool             mac_i_pan_coordinator;
extern uint64_t         mac_ieee_address;
extern frame_buffer_t   *mac_message;
extern uint8_t          mac_missed_beacons;
extern uint8_t          mac_original_channel;
extern mac_state_t      mac_original_state;
extern parse_t          mac_parse_data;
extern bool             mac_phy_autoacks;
extern bool             mac_phy_autocsmaca;
extern uint8_t          mac_phy_wakeuptime;
extern mac_state_t      mac_pre_csmaca_state;
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
extern bool             mac_run_beacon_timer;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
extern uint16_t         mac_saved_panid;
extern uint8_t          mac_scan_duration;
extern mac_state_t      mac_state;
extern mac_sync_t       mac_trackBeacons;

/* MAC PIB variables */
extern uint8_t  mac_pib_macAckWaitDuration;
extern uint8_t  mac_pib_macAssociationPermit;
extern uint8_t  mac_pib_macAutoRequest;
extern uint8_t  mac_pib_macBattLifeExt;
extern uint8_t  mac_pib_macBattLifeExtPeriods;
extern uint8_t  mac_pib_macBeaconPayloadLength;
extern uint8_t  mac_pib_macBeaconOrder;
extern uint32_t mac_pib_macBeaconTxTime;
extern uint8_t  mac_pib_macBSN;
extern uint64_t mac_pib_macCoordExtendedAddress;
extern uint16_t mac_pib_macCoordShortAddress;
extern uint8_t  mac_pib_macDSN;
extern uint8_t  mac_pib_macGTSPermit;
extern uint8_t  mac_pib_macMaxCSMABackoffs;
extern uint8_t  mac_pib_macMinBE;
extern uint16_t mac_pib_macPANId;
extern uint8_t  mac_pib_macPromiscuousMode;
extern uint8_t  mac_pib_macRxOnWhenIdle;
extern uint16_t mac_pib_macShortAddress;
extern uint8_t  mac_pib_macSuperframeOrder;
extern uint16_t mac_pib_macTransactionPersistenceTime;

#if SPECIAL_PEER
extern uint8_t  mac_pib_privateCCAFailure;
extern uint8_t  mac_pib_privateDisableACK;
extern uint8_t  mac_pib_privateIllegalFrameType;
extern uint8_t  mac_pib_privateNoDataAfterAssocReq;
extern uint8_t  mac_pib_privateTransactionOverflow;
extern uint8_t  mac_pib_privateVirtualPANs;
#endif /* SPECIAL_PEER */

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* === Types ================================================================ */

/* Please declare types in data_structures.h. */

/* === Macros =============================================================== */

/** Size of FCF in octets */
#define FCF_SIZE                (2)

/**
 * Defines a mask for the frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_MASK      (0x07)

/**
 * Defines the beacon frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_BEACON    (0x00)

/**
 * Define the data frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_DATA      (0x01)

/**
 * Define the ACK frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_ACK       (0x02)

/**
 * Define the command frame type. (Table 65 IEEE 802.15.4 Specification)
 */
#define FCF_FRAMETYPE_MAC_CMD   (0x03)

/**
 * A macro to set the frame type.
 */
#define FCF_SET_FRAMETYPE(x)            (x)

/**
 * A macro to get the frame type.
 */
#define FCF_GET_FRAMETYPE(x)            ((x) & FCF_FRAMETYPE_MASK)

/** The mask for the security enable bit of the FCF */
#define FCF_SECURITY_ENABLED    (1 << 3)

/** The mask for the frame pending bit of the FCF */
#define FCF_FRAME_PENDING       (1 << 4)

/** The mask for the ACK request bit of the FCF */
#define FCF_ACK_REQUEST         (1 << 5)

/** The mask for the intra PAN bit of the FCF */
#define FCF_INTRA_PAN           (1 << 6)

/** Address Mode: NO ADDRESS */
#define FCF_NO_ADDR             (0x00)
/** Address Mode: RESERVED */
#define FCF_RESERVED_ADDR       (0x01)
/** Address Mode: SHORT */
#define FCF_SHORT_ADDR          (0x02)
/** Address Mode: LONG */
#define FCF_LONG_ADDR           (0x03)
/** Defines the mask for the FCF address mode */
#define FCF_ADDR_MASK           (3)

/** Defines the offset of the source address */
#define FCF_SOURCE_ADDR_OFFSET  (14)

/** Defines the offset of the destination address */
#define FCF_DEST_ADDR_OFFSET    (10)

/** Macro to set the source address mode */
#define FCF_SET_SOURCE_ADDR_MODE(x)     ((x) << FCF_SOURCE_ADDR_OFFSET)
/** Macro to get the source address mode */
#define FCF_GET_SOURCE_ADDR_MODE(x)     (((x) >> FCF_SOURCE_ADDR_OFFSET) & FCF_ADDR_MASK)
/** Macro to set the destination address mode */
#define FCF_SET_DEST_ADDR_MODE(x)       ((x) << FCF_DEST_ADDR_OFFSET)
/** Macro to get the destination address mode */
#define FCF_GET_DEST_ADDR_MODE(x)       (((x) >> FCF_DEST_ADDR_OFFSET) & FCF_ADDR_MASK)

/** Battery life extention bit position */
#define BATT_LIFE_EXT_BIT_POS   (12)
/** PAN coordinator bit position */
#define PAN_COORD_BIT_POS       (14)
/** Association permit bit position */
#define ASSOC_PERMIT_BIT_POS    (15)

/** Mask of the GTS descriptor counter */
#define GTS_DESCRIPTOR_COUNTER_MASK (0x07)

/** Mask for the number of short addresses pending */
#define NUM_SHORT_PEND_ADDR(x)     ((x) & 0x07)
/** Mask for the number of long addresses pending */
#define NUM_LONG_PEND_ADDR(x)      (((x) & 0x70) >> 4)

/**
 * Defines the length of an ACK frame.
 */
#define ACK_FRAME_LEN           (0x05)

/**
 * Defines the min. length of a frame which is not an ACK
 */
#define MIN_FRAME_LEN           (0x08)

/** Size of CRC in octets */
#define CRC_SIZE                (2)

/*
 * Symbol time calculation macros.
*/
/**
 * Beacon Interval formula: \f$BI = aBaseSuperframeDuration 2^BO\f$
 * where \f$0 <= BO <= 14\f$
 */
#define MAC_CALCULATE_SYMBOL_TIME_BEACONINTERVAL(BO) ((1UL * aBaseSuperframeDuration)<<(BO))

/**
 * Superframe Duration formula: \f$BI = aBaseSuperframeDuration 2^BO\f$
 * where \f$0 <= SO <= BO\f$
 */
#define MAC_CALCULATE_SYMBOL_TIME_SUPERFRAMEDURATION(SO) ((1UL * aBaseSuperframeDuration)<<(SO))

/**
 * Scan duration formula: \f$aBaseSuperframeDuration (2^SD + 1)\f$
 * where \f$0 <= SD <= 14\f$
 */
#define MAC_CALCULATE_SYMBOL_TIME_SCANDURATION(SD) (aBaseSuperframeDuration * ((1UL<<(SD))+1))

/** Generic 16 bit broadcast address */
#define BROADCAST   (0xFFFF)

/** Unused EUI-64 address */
#define CLEAR_ADDR_64 (0ULL)

/** MAC is using long address (by now). */
#define MAC_NO_SHORT_ADDR (0xFFFE)

/** Max beacon Order in beacon-enabled network */
#define BEACON_NETWORK_MAX_BO   (14)

/** BO value for nonbeacon-enabled network */
#define NON_BEACON_NETWORK      (15)

/** MCPS-DATA.request TxOption: ACKTRANSMISSION */
#define ACK_TRANSMISSION         (0x01)
/** MCPS-DATA.request TxOption: GTSTRANSMISSION */
#define GTS_TRANSMISSION         (0x02)
/** MCPS-DATA.request TxOption: INDIRECTTRANSMISSION */
#define INDIRECT_TRANSMISSION    (0x04)
/** MCPS-DATA.request TxOption: SECURITYTRANSMISSION */
#define SECURITY_TRANSMISSION    (0x08)

/** Extract the superframe order from the Superframe Spec. */
#define GET_SUPERFRAME_ORDER(spec) (((spec) & 0x00F0) >> 4)

/** Extract the beacon order from the Superframe Spec. */
#define GET_BEACON_ORDER(spec)     ((spec) & 0x000F)

/** Extract the final CAP slot from Superframe Spec. */
#define GET_FINAL_CAP(spec)        (((spec) & 0x0F00) >> 8)

/**
 * Active/passive scan: implementation-defined maximum number of
 * PANDescriptors that can be stored.
 *
 * This macro evaluates to 5.
 */
#define MAX_PANDESCRIPTORS ((sizeof(mac_buffer) - sizeof(mlme_scan_conf_t)) \
                            / sizeof(wpan_pandescriptor_t))

/**
 * Offset of the destination address within an association response
 * command frame.  Used in order to obtain the DstAddress of a
 * MLME-COMM-STATUS.indication generated for an association response,
 * so the (64-bit) DstAddress doesn't need to be duplicated in
 * frame_buffer_t.
 */
#define ASSOC_RESP_DSTADDR_OFFSET       (5)

/**
 * Offset of the destination address within an directed (i. e.
 * non-broadcast) coordinator realignment command frame.  Used in
 * order to obtain the DstAddress of a MLME-COMM-STATUS.indication
 * generated for an orphan response, so the (64-bit) DstAddress
 * doesn't need to be duplicated in frame_buffer_t.
 */
#define COORD_REALIGN_DSTADDR_OFFSET    (5)

/**
 * Final CAP slot in standard superframe without GTS
 */
#define FINAL_CAP_SLOT_DEFAULT          (0x0F)

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/** \defgroup MAC MAC internal functions
 *
 * This module describes all MAC internal functions.
 *
 */
/*@{*/

/* MAC-internal functions -- please keep them alphabetically sorted. */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_build_beacon_frame(bool tx_directly);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
bool            mac_build_data_req_cmd(bool expl_poll, bool forceOwnLongAddr);
void            mac_create_beacon(void);
void            mac_csma_ca(uint8_t init_nb, uint8_t init_nr);
void            mac_csma_ca_cca_done(uint8_t *m);
void            mac_csma_ca_do_cca(uint8_t phystatus);
void            mac_csma_ca_pd_sent(uint8_t *m);
void            mac_idle_trans(void);
void            mac_init(uint64_t ieee_addr);
void            mac_mlme_comm_status(uint8_t srcAddrMode, uint64_t *srcAddr,
                                     uint8_t dstAddrMode, uint64_t *dstAddr, uint8_t status);
bool            mac_parse_MPDU(pd_data_ind_t *pdi, uint8_t pass_no);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_persistence_buf_expired(frame_buffer_t *);
void            mac_process_orphan_notification(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_process_ack_frame(bool has_pending_bit);
void            mac_process_associate_request(void);
void            mac_process_associate_response(void);
void            mac_process_beacon_frame(void);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_process_beacon_request(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_process_coord_realign(bool orphan);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_process_data_request(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_process_data_response(void);
void            mac_process_data_frame(void);
void            mac_process_disassociate_notification(void);
uint8_t         mac_reset(uint8_t init_pib);
void            mac_scan_pd_data_conf(void);
void            mac_scan_set_conf(plme_set_conf_t *psd);
void            mac_scan_set_trx_state_conf(plme_set_trx_state_conf_t *psd);
void            mac_send_ack(bool set_pending);
void            mac_set_panid(uint16_t panid);
void            mac_set_shortaddr(uint16_t shortaddr);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_start_beacon_timer(void);
void            mac_start_request_set_phyCurrentChannel_conf(plme_set_conf_t *psd);
void            mac_start_request_set_rx_on_conf(plme_set_trx_state_conf_t *psd);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_sync_loss(uint8_t loss_reason);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
bool            mac_tx_coord_realignment_command(mac_message_t cmd_type,
                                                 mlme_orphan_resp_t *buf,
                                                 uint16_t new_panid,
                                                 uint8_t new_channel);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */



/* MAC-internal Buffer functions */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
uint8_t         mac_buffer_add_pending(uint8_t *pending_addr_spec);
bool            mac_buffer_decrement_persistence(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_buffer_flush(void);
void            mac_buffer_free(frame_buffer_t *buf);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
bool mac_buffer_purge(uint8_t msdu_handle);
frame_buffer_t *mac_buffer_report_long_indirect(uint64_t extended_addr, uint8_t *count);
frame_buffer_t *mac_buffer_report_short_indirect(uint16_t short_addr, uint8_t *count);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
frame_buffer_t *mac_buffer_request(void);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
frame_buffer_t *mac_buffer_request_indirect(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */


/* timer callbacks */
void            mac_t_ackwait(void);
void            mac_t_assocresponsetime(void);
void            mac_t_backoff(void);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_t_beacon(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_t_maxframeresponsetime(void);
void            mac_t_missed_beacons(void);
void            mac_t_scan_duration(void);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_t_so_inactive(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_t_response_wait(void);
void            mac_t_rx_enable_duration_expired(void);
void            mac_t_rx_enable_duration_start(void);
void            mac_t_tracking_beacons(void);

/* PHY layer callback functions */
void            mac_proc_pd_data_confirm(uint8_t *pdc);
void            mac_proc_pd_data_ind(uint8_t *msg);

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mac_proc_plme_ed_confirm(uint8_t *pec);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mac_proc_plme_set_confirm(uint8_t *psd);
void            mac_proc_plme_set_trx_state_confirm(uint8_t *psd);

/* 802.15.4 MAC layer entries */
void            mcps_data_request(uint8_t *msg);
void            mcps_purge_request(uint8_t *msg);

void            mlme_get_request(uint8_t *msg);
void            mlme_reset_request(uint8_t *msg);
void            mlme_scan_request(uint8_t *msg);
void            mlme_set_request(uint8_t *msg);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mlme_start_request(uint8_t *msg);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mlme_associate_request(uint8_t *m);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mlme_associate_response(uint8_t *m);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mlme_disassociate_request(uint8_t *m);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
void            mlme_orphan_response(uint8_t *m);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
void            mlme_poll_request(uint8_t *m);
void            mlme_rx_enable_request(uint8_t *m);
void            mlme_sync_request(uint8_t *m);

void            mcps_data_conf(uint8_t *m);
void            mcps_data_ind(uint8_t *m);
void            mcps_purge_conf(uint8_t *m);
void            mlme_associate_conf(uint8_t *m);
void            mlme_associate_ind(uint8_t *m);
void            mlme_beacon_notify_ind(uint8_t *m);
void            mlme_comm_status_ind(uint8_t *m);
void            mlme_disassociate_conf(uint8_t *m);
void            mlme_disassociate_ind(uint8_t *m);
void            mlme_get_conf(uint8_t *m);
void            mlme_orphan_ind(uint8_t *m);
void            mlme_poll_conf(uint8_t *m);
void            mlme_reset_conf(uint8_t *m);
void            mlme_rx_enable_conf(uint8_t *m);
void            mlme_scan_conf(uint8_t *m);
void            mlme_set_conf(uint8_t *m);
void            mlme_start_conf(uint8_t *m);
void            mlme_sync_loss_ind(uint8_t *m);


/* Internal form of MLME-{GET,SET}.request handling. */
uint8_t         mlme_get_request_internal(mlme_get_req_t *msg, mlme_get_conf_t *cm);
uint8_t         mlme_set_request_internal(mlme_set_req_t *msg, mlme_set_conf_t *cm);


#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
/**
 * @brief Checks whether the Persistence timer needs to be started
 *
 * If the network is non-beaconing and the coordinator does have pending data
 * the MAC persistence timer needs to be started, which is realized by means of
 * the beacon timer
 */

static inline void mac_check_persistence_timer(void)
{
    if ((mac_pib_macBeaconOrder == NON_BEACON_NETWORK) && (!mac_run_beacon_timer))
    {
        mac_run_beacon_timer = true;
        mac_start_beacon_timer();
    }
}
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

/*@}*/

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MAC_HEADER */
/* EOF */
