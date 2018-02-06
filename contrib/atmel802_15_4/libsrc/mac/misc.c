/**
 * @file
 * This file implements miscellaneous MAC sublayer components.  It also
 * defines all global variables of the MAC sublayer.
 *
 * $Id: misc.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

/* === Includes ============================================================ */
#ifndef DEF_H
#include "def.h"
#endif

#include <string.h>
#include "mac.h"
#include "phy.h"
#include "timer_const.h"

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */

/** IEEE address of node */
uint64_t mac_ieee_address;
/** Current state of the MAC state machine */
mac_state_t mac_state;
/** Temporarily saved MAC state */
mac_state_t mac_original_state;
/** MAC state before starting CSMA-CA */
mac_state_t mac_pre_csmaca_state;
/** Buffer to hold max length frame and corresponding properties */
uint8_t         mac_buffer[aMaxPHYPacketSize + sizeof(pd_data_ind_t)];
/** Buffer Beacon payload */
uint8_t         mac_beacon_payload[aMaxBeaconPayloadLength];
/** Current channel of node */
uint8_t         mac_current_channel;
/** Original channel of node (e.g. before starting of scan) */
uint8_t         mac_original_channel;
/** Duration for scan according 802.15.4 */
uint8_t         mac_scan_duration;
/** Type of node (i.e. coordinator or device) */
bool            mac_i_pan_coordinator;
/** Final Cap Slot of current Superframe */
uint8_t         mac_FinalCapSlot;
/** Original PAN-ID before starting of scan */
uint16_t        mac_saved_panid;
/** Global parse data */
parse_t         mac_parse_data;
/** Variable points to the frame to transmit via CSMA-CA */
frame_buffer_t  *mac_message;
/** Current mode of syncing with coordinator */
mac_sync_t      mac_trackBeacons;
/** Calculates missed Beacons during to detect loss of sync */
uint8_t         mac_missed_beacons;
/** Boolean indicates that a Beacon has been using fast processing w/o queueing messages */
bool            mac_beacon_flag;
/** Boolean indicates that an Ack has been using fast processing w/o queueing messages */
bool            mac_ack_flag;
/** Beacon order of PAN (15 for non-beaconing network) */
uint8_t         mac_beacon_order;
/** Beacon Interval in symbol time */
uint32_t        mac_RollOverTime;
/** Start of the inactive period of a Superframe in symbol time */
uint32_t        mac_SOInactiveTime;
/**
 * Latest possible time to start slotted CSMA-CA when macBattLifeExt
 * is activated.
 */
uint32_t        mac_battlife_latest_start;
bool            mac_phy_autoacks; /**< PHY currently performs auto-ack */
bool            mac_phy_autocsmaca; /**< PHY currently performs automatic CSMA-CA. */
uint8_t         mac_phy_wakeuptime; /**< Time the PHY/radio needs to wake up from sleep. */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
/**
 * Beacon timer needs to run at coordinator either for Beacon transmission or
 * (in non-beacon enabled network) for maintaining the persistence timer of pending
 * indirect frames
 */
bool            mac_run_beacon_timer;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

/* MAC PIB variables */
uint8_t  mac_pib_macAckWaitDuration;
uint8_t  mac_pib_macAssociationPermit;
uint8_t  mac_pib_macAutoRequest;
uint8_t  mac_pib_macBattLifeExt;
uint8_t  mac_pib_macBattLifeExtPeriods;
uint8_t  mac_pib_macBeaconPayloadLength;
uint8_t  mac_pib_macBeaconOrder;
uint32_t mac_pib_macBeaconTxTime;
uint8_t  mac_pib_macBSN;
uint64_t mac_pib_macCoordExtendedAddress;
uint16_t mac_pib_macCoordShortAddress;
uint8_t  mac_pib_macDSN;
uint8_t  mac_pib_macGTSPermit;
uint8_t  mac_pib_macMaxCSMABackoffs;
uint8_t  mac_pib_macMinBE;
uint16_t mac_pib_macPANId;
uint8_t  mac_pib_macPromiscuousMode;
uint8_t  mac_pib_macRxOnWhenIdle;
uint16_t mac_pib_macShortAddress;
uint8_t  mac_pib_macSuperframeOrder;
uint16_t mac_pib_macTransactionPersistenceTime;

#if SPECIAL_PEER
/**
 * Private MAC PIB variables, only valid for testing purposes
 */
uint8_t  mac_pib_privateCCAFailure;
uint8_t  mac_pib_privateDisableACK;
uint8_t  mac_pib_privateIllegalFrameType;
uint8_t  mac_pib_privateNoDataAfterAssocReq;
uint8_t  mac_pib_privateTransactionOverflow;
uint8_t  mac_pib_privateVirtualPANs;
#endif /* SPECIAL_PEER */


/* === Prototypes ========================================================== */

static void do_init_pib(void);
static void reset_globals(void);

/* === Implementation ====================================================== */

void reset_globals(void)
{
    mac_original_state = MAC_W;
    mac_pre_csmaca_state = MAC_W;

    mac_current_channel = 0;
    mac_original_channel = 0;
    mac_scan_duration = 0;
    mac_i_pan_coordinator = false;
    mac_FinalCapSlot = FINAL_CAP_SLOT_DEFAULT;
    mac_saved_panid = 0;
    mac_message = NULL;
    mac_trackBeacons = SYNC_NEVER;
    mac_missed_beacons = 0;
    mac_beacon_flag = false;
    mac_ack_flag = false;
    mac_beacon_order = 0;
    mac_RollOverTime = 0;
    mac_SOInactiveTime = 0;
    mac_battlife_latest_start = 0;

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
    mac_run_beacon_timer = false;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */
}

/**
 * \brief Initialize the MAC sublayer.
 *
 * \param ieee_addr The 64-bit extended IEEE (MAC) address of this device.
 */

void mac_init(uint64_t ieee_addr)
{
    /*
     * The MAC (or IEEE) 64-bit address is a constant wrt. the MAC
     * from the standard's point of view, named aExtendedAddress.
     * As this cannot be a compile-time constant, it needs to be
     * initialized once, and passed down to the PHY layer as well
     * for the hardware address recognition logic (if present).
     */
    mac_ieee_address = ieee_addr;
    (void)mac_reset(true);
}

/**
 * \brief Reset of MAC helper Variables and transition to idle state
 *
 * This function sets the MAC to idle state and resets
 * MAC helping flags
 */
void mac_idle_trans(void)
{
    plme_set_trx_state_req_t pst;

    mac_state = MAC_W;
    // Turn the radio off;`
    pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
    pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
    pst.state   = PHY_TRX_OFF;
    bios_pushback_event((uint8_t *)&pst);
}



/**
 * \brief Internal MAC reset
 *
 * This is the heart of the MLME_RESET functionality.
 *
 * \param init_pib Boolean indicates whether PIB attributes shall be initialized or not.
 * \return success/failure status
 */

uint8_t mac_reset(uint8_t init_pib)
{
    plme_set_trx_state_req_t    pstsr;
    plme_set_trx_state_conf_t   pstsc;
    union
    {
        uint8_t psrbuf[sizeof(plme_set_req_t) + sizeof(uint64_t)];
        uint8_t pgcbuf[sizeof(plme_get_conf_t) + sizeof(uint8_t)];
    }
    local_buf;
    plme_set_req_t *psr = (plme_set_req_t *)&local_buf;
    plme_set_conf_t psc;
    plme_get_req_t pgr;
    plme_get_conf_t *pgc = (plme_get_conf_t *)&local_buf;
    uint8_t status;
    uint8_t i;

    reset_globals();
    mac_buffer_flush();         // Initialize the transmit frame buffer

    pstsr.size = sizeof(pstsr) - sizeof(pstsr.size);
    pstsr.cmdcode = PLME_SET_TRX_STATE_REQUEST;
    pstsr.state = PHY_FORCE_TRX_OFF;

    status = MAC_DISABLE_TRX_FAILURE;
    /*
     * Try to wait until the trx reached TRX_OFF.  Don't try
     * infinitely though, rather return a MAC_DISABLE_TRX_FAILURE upon
     * complete failure.
     */
    for (i = 0; i < 255; i++)
    {
        plme_set_trx_state_request_internal(&pstsr, &pstsc);
        if ((pstsc.status == PHY_SUCCESS) || (pstsc.status == PHY_TRX_OFF))
        {
            status = MAC_SUCCESS;
            break;
        }
    }

    /* Kills all timers. */
    bios_timer_init();

    if (init_pib)
    {
        do_init_pib();
    }

    // go into idle mode and reset Variables
    mac_idle_trans();

    phy_reset_internal();

    /*
     * Push the MAC view of certain PIB attributes down to the PHY.
     * There is no need to worry whether the respective PHY doesn't
     * support all of these, the goal is only to ensure the MAC and
     * the PHY view about these are the same.  For that reason, all
     * the status returned is simply ignored.
     */
    // Set the IEEE address.
    psr->cmdcode = PLME_SET_REQUEST;
    psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint64_t);
    psr->data[0] = sizeof(uint64_t);
    psr->PIBAttribute = phyIEEEaddr;
    memcpy(&psr->data[1], &mac_ieee_address, sizeof(mac_ieee_address));
    plme_set_request_internal(psr, &psc);

    // Set short address.
    psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint16_t);
    psr->data[0] = sizeof(uint16_t);
    psr->PIBAttribute = phyShortAddr;
    memcpy(&psr->data[1], &mac_pib_macShortAddress, sizeof(mac_pib_macShortAddress));
    plme_set_request_internal(psr, &psc);

    // Set the panid.
    // psr->size and psr->data[0] just remain the same here.
    psr->PIBAttribute = phyPANid;
    memcpy(&psr->data[1], &mac_pib_macPANId, sizeof(mac_pib_macPANId));
    plme_set_request_internal(psr, &psc);

    // Determine the time our PHY/radio needs to wake up.
    pgr.size = sizeof(plme_get_req_t) - sizeof(pgr.size);
    pgr.PIBAttribute = phyWakeupTime;
    plme_get_request_internal(&pgr, pgc);
    ASSERT(pgc->status == PHY_SUCCESS);
    mac_phy_wakeuptime = pgc->data[1];

    /*
     * Try turning on some of the more advanced features in the PHY.
     * When successful, adjust our state about the PHY features.
     */
    // Automatic ACKs.
    psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint8_t);
    psr->data[0] = sizeof(uint8_t);
    psr->PIBAttribute = phyAutoACK;
    psr->data[1] = true;
    plme_set_request_internal(psr, &psc);
    if (psc.status == PHY_SUCCESS)
    {
        mac_phy_autoacks = true;
        // If automatic ACKs are supported, phyPANcoord must be supported, too.
        psr->PIBAttribute = phyPANcoord;
        psr->data[1] = false;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
        // phySetPending is mandatory as well here.
        psr->PIBAttribute = phySetPending;
        psr->data[1] = false;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
    }
    else
    {
        mac_phy_autoacks = false;
    }
    // Generate CRC for transmitted packets.  This one is pretty mandatory.
    psr->PIBAttribute = phyGenerateCRC;
    psr->data[1] = true;
    plme_set_request_internal(psr, &psc);
    ASSERT(psc.status == PHY_SUCCESS);
    // Check CRC on received packets.  Also mandatory.
    psr->PIBAttribute = phyCheckCRC;
    psr->data[1] = true;
    plme_set_request_internal(psr, &psc);
    ASSERT(psc.status == PHY_SUCCESS);

    // Automatic CSMA-CA.
    psr->PIBAttribute = phyAutoCSMACA;
    psr->data[1] = true;
    plme_set_request_internal(psr, &psc);
    if (psc.status == PHY_SUCCESS)
    {
        mac_phy_autocsmaca = true;
        // If automatic CSMA-CA is supported, phyMaxFrameRetries,
        // phyMaxCSMABackoffs, and phyMinBE must be supported, too.
        psr->PIBAttribute = phyMaxFrameRetries;
        psr->data[1] = aMaxFrameRetries;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
        psr->PIBAttribute = phyMaxCSMABackoffs;
        psr->data[1] = mac_pib_macMaxCSMABackoffs;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
        psr->PIBAttribute = phyMinBE;
        psr->data[1] = mac_pib_macMinBE;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
    }
    else
    {
        mac_phy_autocsmaca = false;
    }

    return status;
}

/**
 * \brief Initialize MAC PIBs
 *
 * Initialize all MAC PIBs to their defaults as stated by 802.15.4.
 *
 */

void do_init_pib(void)
{

    mac_pib_macAckWaitDuration = macAckWaitDuration_def;
    mac_pib_macAssociationPermit = macAssociationPermit_def;
    mac_pib_macAutoRequest = macAutoRequest_def;
    mac_pib_macBattLifeExt = macBattLifeExt_def;
    mac_pib_macBattLifeExtPeriods = macBattLifeExtPeriods_def;
    mac_pib_macBeaconPayloadLength = macBeaconPayloadLength_def;
    mac_pib_macBeaconOrder = macBeaconOrder_def;
    mac_pib_macBeaconTxTime = macBeaconTxTime_def;
    mac_pib_macBSN = (uint8_t)rand();
    mac_pib_macCoordExtendedAddress = CLEAR_ADDR_64;
    mac_pib_macCoordShortAddress = macCoordShortAddress_def;
    mac_pib_macDSN = (uint8_t)rand();
    mac_pib_macGTSPermit = macGTSPermit_def;
    mac_pib_macMaxCSMABackoffs = macMaxCSMABackoffs_def;
    mac_pib_macMinBE = macMinBE_def;
    mac_pib_macPANId = macPANId_def;
    mac_pib_macPromiscuousMode = macPromiscuousMode_def;
    mac_pib_macRxOnWhenIdle = macRxOnWhenIdle_def;
    mac_pib_macShortAddress = macShortAddress_def;
    mac_pib_macSuperframeOrder = macSuperframeOrder_def;
    mac_pib_macTransactionPersistenceTime = macTransactionPersistenceTime_def;
#if SPECIAL_PEER
    mac_pib_privateCCAFailure = 0;
    mac_pib_privateDisableACK = 0;
    mac_pib_privateIllegalFrameType = 1;
    mac_pib_privateNoDataAfterAssocReq = 0;
    mac_pib_privateTransactionOverflow = 0;
    mac_pib_privateVirtualPANs = 0;
#endif /* SPECIAL_PEER */
}


/**
 * \brief send an ACK frame
 *
 * This routine constructs an ACK frame MPDU, and sends it to the PHY.
 *
 * \param set_pending whether to set the "frame pending" FCF bit
 */
void mac_send_ack(bool set_pending)
{
    /*
     * Just allocate enough space to hold one ACK frame.
     */
    uint8_t ack_buffer[sizeof(frame_buffer_t) - aMaxPHYPacketSize + ACK_FRAME_LEN];
    frame_buffer_t              *ackbuf = (frame_buffer_t *)ack_buffer;
    plme_set_trx_state_req_t    pst;
    plme_set_trx_state_conf_t   psc;
    pd_data_conf_t              pdc;
    uint8_t                     index;
    uint16_t                    tmp16;

#if SPECIAL_PEER
    if (mac_pib_privateDisableACK == 0xff)
    {
        return;
    }
    else if (mac_pib_privateDisableACK > 0)
    {
        mac_pib_privateDisableACK--;
        return;
    }
#endif /* SPECIAL_PEER */

    /* do not ACK frames during CSMA-CA */
    if ((mac_state >= MAC_B) && (mac_state <= MAC_F))
    {
        return;
    }

    if (!mac_phy_autoacks)
    {
        /* AutoACK is OFF --> send ACK frame */

        index = 1;
        ackbuf->pd_data.size = sizeof(pd_data_req_t) - sizeof(ackbuf->pd_data.size) + ACK_FRAME_LEN;
        ackbuf->pd_data.cmdcode = PD_DATA_REQUEST;

        // Build the Frame control field
        tmp16 = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_ACK);

        if (set_pending)
        {
            tmp16 = tmp16 | FCF_FRAME_PENDING;
        }

        ackbuf->pd_data.data[index++] = tmp16 & 0xff;
        ackbuf->pd_data.data[index++] = (tmp16 >> 8) & 0xff;

        // Build the sequence number
        ackbuf->pd_data.data[index] = mac_parse_data.sequence_number;

        ackbuf->pd_data.data[0] = ackbuf->pd_data.psduLength = ACK_FRAME_LEN;

        mac_ack_flag = true;

        // Send the frame over the air
        pst.size = sizeof(pst) - sizeof(pst.size);
        pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        pst.state = PHY_TX_ON;

        // we need to wait until we are ready to Tx
        do
        {
            plme_set_trx_state_request_internal(&pst, &psc);
        } while ((psc.status != PHY_SUCCESS) && (psc.status != PHY_TX_ON));

        // Check whether the ACK could be transmitted
        if (pd_data_request_internal(&ackbuf->pd_data, &pdc))
        {
            // frame could not be tx'ed
            mac_ack_flag = false;
        }
    }
}


/**
 * @brief Reset the MAC layer
 * The MLME-RESET.request primitive allows the next higher layer to request that the MLME performs a
    reset operation (according to the standard, section 7.9.1)
 * @param msg the MLME_RESET.request message
 */

void mlme_reset_request(uint8_t *m)
{
    mlme_reset_req_t *msg = (mlme_reset_req_t *)m;
    mlme_reset_conf_t mrc;

    mrc.status = mac_reset(msg->SetDefaultPIB);
    mrc.cmdcode = MLME_RESET_CONFIRM;
    mrc.size = sizeof(mlme_reset_conf_t) - sizeof(mrc.size);

    bios_pushback_event((uint8_t *)&mrc);
}



/**
 * @brief Creates a Communication Status Indication message to the upper layer
 *
 * @param srcAddrMode Address mode of transmitting device
 *        srcAddr Address of transmitting device
 *        dstAddrMode Address mode of receiving device
 *        dstAddr Address of receiving device
 *        status Status of the last operation
 *
 */
void mac_mlme_comm_status(uint8_t srcAddrMode,
                          uint64_t *srcAddr,
                          uint8_t dstAddrMode,
                          uint64_t *dstAddr,
                          uint8_t status)
{
    mlme_comm_status_ind_t csi;

    csi.size = sizeof(mlme_comm_status_ind_t) - sizeof(csi.size);
    csi.cmdcode = MLME_COMM_STATUS_INDICATION;
    csi.PANId = mac_pib_macPANId;
    csi.SrcAddrMode = srcAddrMode;
    memcpy(&csi.SrcAddr, srcAddr, sizeof(uint64_t));
    csi.DstAddrMode = dstAddrMode;
    memcpy(&csi.DstAddr, dstAddr, sizeof(uint64_t));
    csi.status = status;

    bios_pushback_event(&csi);
}



/**
 * @brief generate notification for expired transaction
 *
 * @param msg Pointer to buffer that just expired
 */
void mac_persistence_buf_expired(frame_buffer_t *msg)
{

    switch (msg->msgtype)
    {
        case ASSOCIATIONRESPONSE:
            mac_mlme_comm_status(FCF_LONG_ADDR, &mac_ieee_address, FCF_LONG_ADDR,
                                 (uint64_t *)&msg->placeholder[ASSOC_RESP_DSTADDR_OFFSET],
                                 MAC_TRANSACTION_EXPIRED);
            break;

        case DISASSOCIATIONNOTIFICATION:
            {
                mlme_disassociate_conf_t dac;
                dac.size = sizeof(mlme_disassociate_conf_t) - sizeof(dac.size);
                dac.cmdcode = MLME_DISASSOCIATE_CONFIRM;
                dac.status = MAC_TRANSACTION_EXPIRED;
                bios_pushback_event(&dac);
            }
            break;

        case MCPS_MESSAGE:
            {
                mcps_data_conf_t mdc;
                mdc.size = sizeof(mcps_data_conf_t) - sizeof(mdc.size);
                mdc.cmdcode = MCPS_DATA_CONFIRM;
                mdc.msduHandle = msg->msduHandle;
                mdc.status = MAC_TRANSACTION_EXPIRED;
                bios_pushback_event(&mdc);
            }
            break;

        default:
            // Nothing to be done here
            break;
    }
}

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
