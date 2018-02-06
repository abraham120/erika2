/**
 * @file
 * This file implements the beacon frame generation
 *
 * @brief
 * This file implements the proper building of beacon frames and initiates
 * beacon transmission directly (for beacon-enabled PANs) or via CSMA-CA
 * after reception of a beacon request frame in a nonbeacon-enabled PAN.
 *
 * $Id: beacon.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include <string.h>
#include "mac.h"
#include "phy.h"
#ifndef DEF_H
#include "def.h"
#endif

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)

static uint8_t beacon_buffer[aMaxPHYPacketSize + sizeof(pd_data_ind_t)];

#if SPECIAL_PEER
static uint8_t vpanNo;
#endif  /* SPECIAL_PEER */

/* === Prototypes ========================================================== */


/* === Implementation ====================================================== */

/**
 * @brief Build a beacon frame
 *
 *  Build_Beacon_Frame is called from the MAC_BEACON_TX_TIME_routine within the
 *  MAC_Event_Interrupt. The purpose of this routine is to build the beacon frame
 *  in a buffer and transmit it via the PHY. The transmission can be done directly
 *  or via CSMA-CA dependent upon the caller.
 *
 * @param   tx_directly
 *          Transmit the beacon immediately. If false transmit it using CSMA-CA.
 **/

void mac_build_beacon_frame(bool tx_directly)
{
    plme_set_trx_state_req_t    psr;
    uint8_t                     index;
    uint16_t                    superframe_spec, fcf;
    plme_set_trx_state_conf_t   psc;
    pd_data_conf_t              pdc;
    frame_buffer_t              *fbuf;

    if (tx_directly)
    {
        // use special beacon buffer
        fbuf = (frame_buffer_t*)&beacon_buffer;
    }
    else
    {
        // use generic direct frame buffer
        fbuf = mac_buffer_request();
        if (fbuf == NULL)
        {
            return;
        }
    }
    index = 1;

    // FCF
    if (mac_pib_macShortAddress == MAC_NO_SHORT_ADDR)
    {
        fcf = FCF_SET_SOURCE_ADDR_MODE(FCF_LONG_ADDR) |
            FCF_SET_FRAMETYPE(FCF_FRAMETYPE_BEACON);
    }
    else
    {
        fcf = FCF_SET_SOURCE_ADDR_MODE(FCF_SHORT_ADDR) |
            FCF_SET_FRAMETYPE(FCF_FRAMETYPE_BEACON);
    }
    fbuf->pd_data.data[index++] = fcf & 0xFF;
    fbuf->pd_data.data[index++] = (fcf >> 8) & 0xFF;

    // Build the beacon sequence number field
    fbuf->pd_data.data[index++] = mac_pib_macBSN;
    mac_pib_macBSN++;

    // Build the address fields. For a beacon frame, only source info
#if SPECIAL_PEER
    if (mac_pib_privateVirtualPANs > 0)
    {
        // This changes the PAN-ID of subsequent beacon frames to simulate virtual PANs
        // for testing purposes
        fbuf->pd_data.data[index++] = mac_pib_macPANId + vpanNo;
        vpanNo++;
        vpanNo = vpanNo % mac_pib_privateVirtualPANs;
    }
    else
#endif /* SPECIAL_PEER */
    {
        fbuf->pd_data.data[index++] = mac_pib_macPANId;
    }
    fbuf->pd_data.data[index++] = (mac_pib_macPANId >> 8);

    if (mac_pib_macShortAddress == MAC_NO_SHORT_ADDR)
    {
        memcpy(&fbuf->pd_data.data[index], &mac_ieee_address, sizeof(uint64_t));
        index += sizeof(uint64_t);
    }
    else
    {
        memcpy(&fbuf->pd_data.data[index], &mac_pib_macShortAddress, sizeof(uint16_t));
        index += sizeof(uint16_t);
    }

    // Build the superframe specification field
    superframe_spec = mac_pib_macBeaconOrder;
    superframe_spec |= (mac_pib_macSuperframeOrder << 4);
    superframe_spec |= (mac_FinalCapSlot << 8);
    if (mac_pib_macBattLifeExt)
    {
        superframe_spec |= (1U << BATT_LIFE_EXT_BIT_POS);
    }
    if (mac_i_pan_coordinator)
    {
        superframe_spec |= (1U << PAN_COORD_BIT_POS);
    }
    if (mac_pib_macAssociationPermit)
    {
        superframe_spec |= (1U << ASSOC_PERMIT_BIT_POS);
    }
    memcpy(&fbuf->pd_data.data[index], &superframe_spec, sizeof(uint16_t));
    index += sizeof(uint16_t);

    // Build the (empty) GTS fields
    fbuf->pd_data.data[index++] = 0;

    // Build the Pending address field
    index += mac_buffer_add_pending(&fbuf->pd_data.data[index]);

    // Build the beacon payload if existant
    if (mac_pib_macBeaconPayloadLength > 0 )
    {
        memcpy(&fbuf->pd_data.data[index], mac_beacon_payload, mac_pib_macBeaconPayloadLength);
        index += mac_pib_macBeaconPayloadLength;
    }

    /* begin MFR */
    index += CRC_SIZE - sizeof(fbuf->pd_data.size);
    fbuf->pd_data.data[0] = fbuf->pd_data.psduLength = index;
    /* end MFR */

    fbuf->pd_data.size = sizeof(pd_data_req_t) - sizeof(fbuf->pd_data.size) + index;

    if (tx_directly)
    {
        mac_beacon_flag = true;

        // Turn the radio to TX_ON.
        psr.size    = sizeof(plme_set_trx_state_req_t) - sizeof(psr.size);
        psr.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        psr.state   = PHY_TX_ON;
        // we need to wait until are ready to Tx
        do
        {
            plme_set_trx_state_request_internal(&psr, &psc);
        } while ( !((psc.status == PHY_SUCCESS) || (psc.status == PHY_TX_ON)) );
        fbuf->pd_data.cmdcode    = PD_DATA_REQUEST;

        // Check whether the beacon could be transmitted
        if (pd_data_request_internal(&fbuf->pd_data, &pdc))
        {
            // frame could not be tx'ed
            mac_beacon_flag = false;
        }
    }
    else
    {
        fbuf->msgtype = BEACON_MESSAGE;
        mac_message = fbuf;
        /* Start CSMA-CA using backoff and retry (direct transmission) */
        mac_csma_ca(true, true);
    }
}



/**
 * @brief Process a beacon request frame
 *
 *  This function is called in case a beacon request frame has been received by
 *  a coordinator. In a nonbeacon-enabled PAN the generation of a beacon frame
 *  using CSMA-CA is initiated. In a beacon-enabled PAN no extra beacon frame
 *  will be transmitted apart from the standard beacon frames.
 *
 * @param
 */
void mac_process_beacon_request(void)
{
    // If we are already transmitting beacons, ignore this beacon request
    if (!((mac_i_pan_coordinator) && (mac_pib_macBeaconOrder < NON_BEACON_NETWORK)))
    {
        // Build a beacon frame and transmit it using CSMA-CA
        mac_build_beacon_frame(false);
    }
}

#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
