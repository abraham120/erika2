/**
 * @file
 * @brief This file contains mac related data structures, types and enums.
 *
 * $Id: data_structures.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Macros ================================================================ */

#define NO_OF_DIRECT_TX_BUFFERS             (1)

#if DEVICE_TYPE == FD1_NOGTS
// Max. no. of presented addresses in Beacon frame = No. of indirect Tx Buffers
#define ADDR_LIST_LENGTH                    (7)

#else   // device does not have direct buffers
#define ADDR_LIST_LENGTH                    (0)
#endif

/**
 * Maximal number of pending addresses in beacon frame.
 */
#define MAX_PENDING_ADDR                (7)


/* === Types ================================================================= */

/**
 * MAC state type.
 */
typedef enum
{
/*
 * IEEE 802.15.4-defined MAC states.  Rather cryptic...
 */
    MAC_W,                  /**< MAC idle ("waiting") */
    MAC_X_as,               /**< active scan proceeding */
    MAC_X_as1,              /**< intermed. state in active scan */
    MAC_X_os,               /**< orphan scan proceeding */
    MAC_X_os1,              /**< intermediate state in orphan scan */
    MAC_X_ps,               /**< passive scan proceeding */
    MAC_Ya,                 /**< active scan passed, ready for start (or associate) */
    MAC_Za,                 /**< coordinator successfully started */
    MAC_Zp,                 /**< passive scan passed, ready for associate */
    MAC_A,                  /**< device associated */
    /* keep the following states in order! */
    MAC_B,                  /**< CSMA-CA started */
    MAC_C,                  /**< CSMA_CA running and waiting for set_trx_state_conf */
    MAC_C2,                 /**< CSMA_CA running and waiting for cca_conf */
    MAC_D,                  /**< CSMA-CA completed, enable Tx */
    MAC_E,                  /**< CSMA-CA transmission in progress */
    MAC_F,                  /**< CSMA-CA transmission done, ACK requested */
    /* end keep */
    MAC_H,                  /**< POLL ACK received (explicit) - awaiting data response */
    MAC_ED,                 /**< ED scan proceeding */
    MAC_Tracking_Beacon,    /**< MAC is tracking beacons (continuously) */
    MAC_await_frame,        /**< implicit POLL - awaiting frame */
    MAC_Ya1,                /**< intermediate state 1 in start */
    MAC_X_as2,              /**< intermediate state in active scan, all channels scanned */
    MAC_Wait_Response,      /**< Wait for Association response */
} SHORTENUM mac_state_t;

typedef enum
{
/* MAC Command Frames (table 67) */
/** Command Frame Identifier for Association Request */
    ASSOCIATIONREQUEST          = (0x01),
/** Command Frame Identifier for Association Response */
    ASSOCIATIONRESPONSE,
/** Command Frame Identifier for Disassociation Notification */
    DISASSOCIATIONNOTIFICATION,
/** Command Frame Identifier for Data Request */
    DATAREQUEST,
/** Command Frame Identifier for PANID Conflict Notification */
    PANIDCONFLICTNOTIFICAION,
/** Command Frame Identifier for Orphan Notification */
    ORPHANNOTIFICATION,
/** Command Frame Identifier for Beacon Request */
    BEACONREQUEST,
/** Command Frame Identifier for Coordinator Realignment */
    COORDINATORREALIGNMENT,
/** Command Frame Identifier for GTS Request */
    GTSREQUEST,

/* These are not MAC command frames but listed here as they are needed
 * in the msgtype field of a frame_buffer_t struct. */

/** message is a directed orphan realignment command */
    ORPHANREALIGNMENT,
/** message is a beacon frame (in response to a beacon request cmd) */
    BEACON_MESSAGE,
/** message type field value for implicite poll without request */
    DATAREQUEST_IMPL_POLL,
/** message type field value for Null frame */
    NULL_FRAME,
/** message type field value for MCPS message */
    MCPS_MESSAGE,
} SHORTENUM mac_message_t;

/** MAC Address type */
typedef union
{
    uint16_t    short_address;
    uint64_t    long_address;
} address_field_t;

/** Full address, consisting of address mode, PANId, and possibly short
 *  or long address (depending on address mode).
 */
typedef struct
{
    uint8_t         address_mode;
    uint16_t        pan_id;
    address_field_t address_field;
} address_t;

/** Beacon Payload type */
typedef struct mac_beacon_payload_tag
{
    uint16_t        superframe_spec;
    uint8_t         gts_spec;
    uint8_t         pending_addr_spec;
    uint16_t        pending_addr_list_short[MAX_PENDING_ADDR];
    uint64_t        pending_addr_list_long[MAX_PENDING_ADDR];
    uint8_t         payload[aMaxBeaconPayloadLength];
} mac_beacon_payload_t;

/** Data Payload type */
typedef struct mac_data_payload_tag
{
    uint8_t         payload[aMaxMACFrameSize];
} mac_data_payload_t;

/** Association Request type */
typedef struct mac_assoc_req_tag
{
    uint8_t         capability_info;
} mac_assoc_req_t;

/** Association Response type */
typedef struct mac_assoc_response_tag
{
    uint16_t        short_addr;
    uint8_t         assoc_status;
} mac_assoc_response_t;

/** Disassociation Request type */
typedef struct mac_disassoc_req_tag
{
    uint8_t         disassoc_reason;
} mac_disassoc_req_t;

/** Coordinator Realignment type */
typedef struct mac_coord_realign_tag
{
    uint16_t        pan_id;
    uint16_t        coord_short_addr;
    uint8_t         logical_channel;
    uint16_t        short_addr;
} mac_coord_realign_t;

/** General Command frame payload type */
typedef union
{
    mac_beacon_payload_t    beacon_data;
    mac_data_payload_t      data;
    mac_assoc_req_t         assoc_req_data;
    mac_assoc_response_t    assoc_response_data;
    mac_disassoc_req_t      disassoc_req_data;
    mac_coord_realign_t     coord_realign_data;
} frame_payload_t;

/*
 * This structure is used to form a table of offsets into the frame
 * (mostly into the MHR of the frame), indexed by the addressing bits
 * of the FCF.
 *
 * Possible values for each field are indicated in the per-field
 * comments. Offset 0 means this field is not present (as offset 0
 * into the frame would point to the FCF).
 */
typedef struct
{
    /* offset of destination PANId within frame */
    uint8_t dest_panid: 3;      /* 0 or 3 */
    /* offset of destination address (short or long) within frame */
    uint8_t dest_addr:  4;      /* 0 or 5 */
    /* offset of source PANId within frame */
    uint8_t src_panid: 4;       /* 0, 3, 7, or 13 */
    /* offset of source address (short or long) within frame */
    uint8_t src_addr:  4;       /* 0, 5, 7, 9, 13, or 15 */
    /* offset of MAC payload within frame */
    uint8_t payload: 5;         /* 0, 3, 7, 9, 11, 13, 15, 17, 21, or 23 */
} mhr_offset_t;

typedef struct parse_tag
{
    uint16_t        fcf;
    uint8_t         frame_type;
    uint8_t         frame_length;
    uint8_t         security_enable;
    uint8_t         sequence_number;
    uint8_t         dest_addr_mode;
    uint16_t        dest_panid;
    address_field_t dest_addr;
    uint8_t         src_addr_mode;
    uint16_t        src_panid;
    address_field_t src_addr;
    uint8_t         mac_command;
    uint8_t         ppduLinkQuality;
    uint32_t        timestamp;
    uint8_t         payload_index;
    uint8_t         payload_length;
    frame_payload_t payload_data;
    mhr_offset_t    mhro;
} parse_t;

typedef struct frame_buffer_tag frame_buffer_t;
struct frame_buffer_tag{
    uint8_t usage;                          // buffer status
    frame_buffer_t *next_buf;               // pointer to next buffer in single linked list
    mac_message_t msgtype;                  // message type; used to select response on failure
    uint8_t msduHandle;                     // MSDU handle
    uint16_t transactiontime;               // MAC Transaction Persistence time left
    pd_data_req_t pd_data;                  // PD-DATA.request message structure
    uint8_t placeholder[aMaxPHYPacketSize]; // it will hold the data of the pd_data member
};

/**
 * Device sync type.
 */
typedef enum
{
    SYNC_NEVER              = (0x00), /* Do not track beacons */
    SYNC_ONCE               = (0x01), /* Track the next beacon */
    SYNC_CONTINUOUSLY       = (0x02)  /* Track beacons continuously */
} SHORTENUM mac_sync_t;

/**
 * Buffer usage type.
 */
typedef enum
{
    BUFFER_EMPTY = 0xFF,   // 0xFF means the buffer id free
    BUFFER_DIRECT = 1,     // Buffer is active for a direct xfer
    BUFFER_INDIRECT = 2    // Buffer is active for indirect xfer
}SHORTENUM buffer_id_type_t;

#if DEBUG > 0
/* === Intra-State union ==================================================== */

typedef union
{
    /* === PD-SAP messages ================================================== */

    pd_data_req_t               pd_data_req_u;
    pd_data_conf_t              pd_data_conf_u;
    pd_data_ind_t               pd_data_ind_u;

    /* === PLME-SAP messages ================================================ */

    plme_cca_req_t              plme_cca_req_u;
    plme_cca_conf_t             plme_cca_conf_u;
    plme_ed_req_t               plme_ed_req_u;
    plme_ed_conf_t              plme_ed_conf_u;
    plme_get_req_t              plme_get_req_u;
    plme_get_conf_t             plme_get_conf_u;
    plme_set_req_t              plme_set_req_u;
    plme_set_conf_t             plme_set_conf_u;
    plme_set_trx_state_req_t    plme_set_trx_state_req_u;
    plme_set_trx_state_conf_t   plme_set_trx_state_conf_u;


    /* === MCPS-SAP messages ================================================ */

    mcps_data_req_t             mcps_data_req_u;
    mcps_data_conf_t            mcps_data_conf_u;
    mcps_data_ind_t             mcps_data_ind_u;
    mcps_purge_req_t            mcps_purge_req_u;
    mcps_purge_conf_t           mcps_purge_conf_u;

    /* === MLME-SAP messages ================================================ */

    mlme_associate_req_t        mlme_associate_req_u;
    mlme_associate_ind_t        mlme_associate_ind_u;
    mlme_associate_resp_t       mlme_associate_resp_u;
    mlme_associate_conf_t       mlme_associate_conf_u;
    mlme_disassociate_req_t     mlme_disassociate_req_u;
    mlme_disassociate_ind_t     mlme_disassociate_ind_u;
    mlme_disassociate_conf_t    mlme_disassociate_conf_u;
    mlme_beacon_notify_ind_t    mlme_beacon_notify_ind_u;
    mlme_gts_req_t              mlme_gts_req_u;
    mlme_gts_conf_t             mlme_gts_conf_u;
    mlme_gts_ind_t              mlme_gts_ind_u;
    mlme_orphan_ind_t           mlme_orphan_ind_u;
    mlme_orphan_resp_t          mlme_orphan_resp_u;
    mlme_reset_req_t            mlme_reset_req_u;
    mlme_reset_conf_t           mlme_reset_conf_u;
    mlme_get_req_t              mlme_get_req_u;
    mlme_get_conf_t             mlme_get_conf_u;
    mlme_set_req_t              mlme_set_req_u;
    mlme_set_conf_t             mlme_set_conf_u;
    mlme_rx_enable_req_t        mlme_rx_enable_req_u;
    mlme_rx_enable_conf_t       mlme_rx_enable_conf_u;
    mlme_scan_req_t             mlme_scan_req_u;
    mlme_scan_conf_t            mlme_scan_conf_u;
    mlme_comm_status_ind_t      mlme_comm_status_ind_u;
    mlme_start_req_t            mlme_start_req_u;
    mlme_start_conf_t           mlme_start_conf_u;
    mlme_sync_req_t             mlme_sync_req_u;
    mlme_sync_loss_ind_t        mlme_sync_loss_ind_u;
    mlme_poll_req_t             mlme_poll_req_u;
    mlme_poll_conf_t            mlme_poll_conf_u;


    /* === SCRIPT-SNIFFER messages ================================================ */
    sniffer_frame_ind_t         sniffer_frame_ind_u;
    sniffer_set_channel_req_t   sniffer_set_channel_req_u;
    sniffer_set_channel_conf_t  sniffer_set_channel_conf_u;
    sniffer_start_req_t         sniffer_start_req_u;
    sniffer_start_conf_t        sniffer_start_conf_u;
    sniffer_stop_req_t          sniffer_stop_req_u;
    sniffer_stop_conf_t         sniffer_stop_conf_u;
    sniffer_set_frmfilter_req_t     sniffer_set_frmfilter_req_u;
    sniffer_set_frmfilter_conf_t    sniffer_set_frmfilter_conf_u;
} isu_t;

#endif /* DEBUG */

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DATA_STRUCTURES_H*/
/* EOF */
