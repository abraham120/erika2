/**
 * @file msg_const.h
 * @brief This file defines all message constants.
 *
 * $Id: msg_const.h,v 1.1 2007/06/22 13:50:48 romano Exp $
 *
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

#ifndef msg_const_h
#define msg_const_h

/* === Includes ============================================================== */
#include <stdbool.h>
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */

/** the event payload can be max 255 bytes, 1 byte goes as length byte
 * for octetstring and 1 byte as command code
*/
#define MAX_OCTETSTRING_SIZE (253)

/**  max. size of message queue */
#define MAX_MESSAGE_SIZE  (255)

/** this type contains the service primitives of the PHY-, MAC- and Network-layer
 * as well the command-interface primitives
*/
enum msg_code
{
    MLME_ASSOCIATE_REQUEST              = (0x01),
    MLME_ASSOCIATE_RESPONSE             = (0x02),

    MCPS_DATA_REQUEST                   = (0x03),
    MCPS_PURGE_REQUEST                  = (0x04),

    MLME_DISASSOCIATE_REQUEST           = (0x05),
    MLME_SET_REQUEST                    = (0x06),
    MLME_ORPHAN_RESPONSE                = (0x07),
    MLME_GET_REQUEST                    = (0x08),
    MLME_RESET_REQUEST                  = (0x09),
    MLME_RX_ENABLE_REQUEST              = (0x0A),
    MLME_SCAN_REQUEST                   = (0x0B),
    MLME_GTS_REQUEST                    = (0x0C),
    MLME_START_REQUEST                  = (0x0D),
    MLME_POLL_REQUEST                   = (0x0E),
    MLME_SYNC_REQUEST                   = (0x0F),

    MCPS_DATA_CONFIRM                   = (0x10),
    MCPS_DATA_INDICATION                = (0x11),
    MCPS_PURGE_CONFIRM                  = (0x12),

    MLME_ASSOCIATE_INDICATION           = (0x13),
    MLME_ASSOCIATE_CONFIRM              = (0x14),
    MLME_DISASSOCIATE_INDICATION        = (0x15),
    MLME_DISASSOCIATE_CONFIRM           = (0x16),
    MLME_BEACON_NOTIFY_INDICATION       = (0x17),
    MLME_GTS_INDICATION                 = (0x18),
    MLME_GTS_CONFIRM                    = (0x19),
    MLME_ORPHAN_INDICATION              = (0x1A),
    MLME_SCAN_CONFIRM                   = (0x1B),
    MLME_COMM_STATUS_INDICATION         = (0x1C),
    MLME_SYNC_LOSS_INDICATION           = (0x1D),
    MLME_GET_CONFIRM                    = (0x1E),
    MLME_SET_CONFIRM                    = (0x1F),
    MLME_RESET_CONFIRM                  = (0x20),
    MLME_RX_ENABLE_CONFIRM              = (0x21),
    MLME_START_CONFIRM                  = (0x22),
    MLME_POLL_CONFIRM                   = (0x23),

    PD_DATA_REQUEST                     = (0x30),
    PD_DATA_CONFIRM                     = (0x31),
    PD_DATA_INDICATION                  = (0x32),

    PLME_CCA_REQUEST                    = (0x33),
    PLME_CCA_CONFIRM                    = (0x34),
    PLME_ED_REQUEST                     = (0x35),
    PLME_ED_CONFIRM                     = (0x36),
    PLME_GET_REQUEST                    = (0x37),
    PLME_GET_CONFIRM                    = (0x38),
    PLME_SET_TRX_STATE_REQUEST          = (0x39),
    PLME_SET_TRX_STATE_CONFIRM          = (0x3A),
    PLME_SET_REQUEST                    = (0x3B),
    PLME_SET_CONFIRM                    = (0x3C),

    NLDE_DATA_REQUEST                   = (0x40),
    NLDE_DATA_CONFIRM                   = (0x41),
    NLDE_DATA_INDICATION                = (0x42),

    NLME_NETWORK_DISCOVERY_REQUEST      = (0x43),
    NLME_NETWORK_DISCOVERY_CONFIRM      = (0x44),
    NLME_NETWORK_FORMATION_REQUEST      = (0x45),
    NLME_NETWORK_FORMATION_CONFIRM      = (0x46),
    NLME_PERMIT_JOINING_REQUEST         = (0x47),
    NLME_PERMIT_JOINING_CONFIRM         = (0x48),
    NLME_START_ROUTER_REQUEST           = (0x49),
    NLME_START_ROUTER_CONFIRM           = (0x4A),
    NLME_JOIN_REQUEST                   = (0x4B),
    NLME_JOIN_INDICATION                = (0x4C),
    NLME_JOIN_CONFIRM                   = (0x4D),
    NLME_DIRECT_JOIN_REQUEST            = (0x4E),
    NLME_DIRECT_JOIN_CONFIRM            = (0x4F),
    NLME_LEAVE_REQUEST                  = (0x50),
    NLME_LEAVE_INDICATION               = (0x51),
    NLME_LEAVE_CONFIRM                  = (0x52),
    NLME_RESET_REQUEST                  = (0x53),
    NLME_RESET_CONFIRM                  = (0x54),
    NLME_SYNC_REQUEST                   = (0x55),
    NLME_SYNC_CONFIRM                   = (0x56),
    NLME_GET_REQUEST                    = (0x57),
    NLME_GET_CONFIRM                    = (0x58),
    NLME_SET_REQUEST                    = (0x59),
    NLME_SET_CONFIRM                    = (0x5A),

    CMDIF_REGWR_REQUEST                 = (0x81),
    CMDIF_REGRD_REQUEST                 = (0x82),
    CMDIF_BITWR_REQUEST                 = (0x83),
    CMDIF_BITRD_REQUEST                 = (0x84),
    CMDIF_FRAMEUP_REQUEST               = (0x85),
    CMDIF_FRAMEDN_REQUEST               = (0x86),
    CMDIF_SRAMUP_REQUEST                = (0x87),
    CMDIF_SRAMDN_REQUEST                = (0x88),
    CMDIF_ECHO_REQUEST                  = (0x89),
    CMDIF_MEMTEST_REQUEST               = (0x8A),
    CMDIF_PINSET_REQUEST                = (0x8B),
    CMDIF_PINGET_REQUEST                = (0x8C),
    CMDIF_SET_ROUTE_REQUEST             = (0x8D),
    CMDIF_GET_ROUTE_REQUEST             = (0x8E),

    CMDIF_REGWR_CONFIRM                 = (0x91),
    CMDIF_REGRD_CONFIRM                 = (0x92),
    CMDIF_BITWR_CONFIRM                 = (0x93),
    CMDIF_BITRD_CONFIRM                 = (0x94),
    CMDIF_FRAMEUP_CONFIRM               = (0x95),
    CMDIF_FRAMEDN_CONFIRM               = (0x96),
    CMDIF_SRAMUP_CONFIRM                = (0x97),
    CMDIF_SRAMDN_CONFIRM                = (0x98),
    CMDIF_ECHO_CONFIRM                  = (0x99),
    CMDIF_MEMTEST_CONFIRM               = (0x9A),
    CMDIF_PINSET_CONFIRM                = (0x9B),
    CMDIF_PINGET_CONFIRM                = (0x9C),
    CMDIF_SET_ROUTE_CONFIRM             = (0x9D),
    CMDIF_GET_ROUTE_CONFIRM             = (0x9E),

    CMDIF_ECHO_INDICATION               = (0x9F),

    TIMER_EXPIRED_INDICATION            = (0xA0),

    CMDIF_TIMERSTART_REQUEST            = (0xA1),
    CMDIF_TIMERSTOP_REQUEST             = (0xA2),

    TRX_INTERRUPT_INDICATION            = (0xA3),

    CMDIF_BOOTLOAD_REQUEST              = (0xA4),

    CMDIF_VERSION_REQUEST               = (0xA5),
    CMDIF_VERSION_CONFIRM               = (0xA6),

    CMDIF_VALIDATION_REQUEST            = (0xA7),
    CMDIF_VALIDATION_CONFIRM            = (0xA8),
    CMDIF_VALIDATION_INDICATION         = (0xA9),

    CMDIF_TIMERSTART_CONFIRM            = (0xB1),
    CMDIF_TIMERSTOP_CONFIRM             = (0xB2),

    SNIFFER_FRAME_INDICATION            = (0xC0),
    SNIFFER_SET_CHANNEL_REQUEST         = (0xC1),
    SNIFFER_START_REQUEST               = (0xC2),
    SNIFFER_STOP_REQUEST                = (0xC3),
    SNIFFER_ACK_REQUEST                 = (0xC4),
    SNIFFER_SET_CHANNEL_CONFIRM         = (0xC5),
    SNIFFER_START_CONFIRM               = (0xC6),
    SNIFFER_STOP_CONFIRM                = (0xC7),
    SNIFFER_ACK_CONFIRM                 = (0xC8),
    SNIFFER_SET_FRMFILTER_REQUEST       = (0xC9),
    SNIFFER_SET_FRMFILTER_CONFIRM       = (0xCA),
} SHORTENUM;

/* bump this when extending the list! */
#define LAST_MESSAGE                     SNIFFER_SET_FRMFILTER_CONFIRM

/** confirm message code: success */
#define CNF_SUCCESS     (0)
/** confirm message code: failure */
#define CNF_FAILED      (1)

/* === Prototypes ============================================================
*/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*msg_const_h*/
/* EOF */
