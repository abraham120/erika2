/**
 * @file
 *
 * @brief   This file processes a received Beacon frame. This happens either
 *          scan where the PAN Descriptor list is filled, or while the device
 *          is tracking beacon frames. In the latter case the device checks
 *          whether the coordinator does have pending data and initiates
 *          the transmission of a data request frame if required.
 *
 * $Id: process_beacon_frame.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include "phy.h"
#include "mac.h"

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */


/* === Prototypes ========================================================== */


/* === Implementation ====================================================== */

/**
 * @brief Processes a received beacon frame
 *
 * This routine processes a received beacon frame.
 * When the system is scanning it records pan descriptor information
 * contained in the beacon. These pan descriptors will be reported to the
 * next higher layer via MLME_SCAN.confirm.
 * Also this routine constructs the MLME_Beacon_notification_indication.
 * Additionally when a device is synced with the coordinator, it tracks beacon
 * frames, checks whether the coordinator does have pending data and will initiate
 * the transmission of a data request frame.
 * The routine uses global "parse_data" structure.
 * The PAN descriptors are stored in the mlme_scan_conf_t structure.
 */
void mac_process_beacon_frame(void)
{
    uint8_t i, numaddrshort, numaddrlong;
    uint16_t beacon_length;
    bool matchflag;
    mlme_beacon_notify_ind_t *mbni;
    wpan_pandescriptor_t *pand_long_start_p, pand_long;
    mlme_scan_conf_t *msc = (mlme_scan_conf_t *)mac_buffer;
    frame_buffer_t *fbuf;

    if (!mac_i_pan_coordinator)
    {
        mac_pib_macBeaconOrder = GET_BEACON_ORDER(mac_parse_data.payload_data.beacon_data.superframe_spec);
        mac_pib_macSuperframeOrder = GET_SUPERFRAME_ORDER(mac_parse_data.payload_data.beacon_data.superframe_spec);
        mac_FinalCapSlot = GET_FINAL_CAP(mac_parse_data.payload_data.beacon_data.superframe_spec);
        mac_RollOverTime = MAC_CALCULATE_SYMBOL_TIME_BEACONINTERVAL(mac_pib_macBeaconOrder);
        mac_SOInactiveTime = MAC_CALCULATE_SYMBOL_TIME_SUPERFRAMEDURATION(mac_pib_macSuperframeOrder);
    }

    /* In a beacon-enabled network with the batterylife extension
     * enabled, compute the first backoff slot boundary after the
     * end of the beacon's IFS. */
    if ((mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
        && mac_pib_macBattLifeExt)
    {
        /* Lengths that are given in octets: */
        beacon_length = mac_parse_data.frame_length + PHY_OVERHEAD;
        /* Convert to symbols. */
        beacon_length *= SYMBOLS_PER_OCTET;
        /* Compute space needed for IFS, and add it. */
        if (mac_parse_data.frame_length <= aMaxSIFSFrameSize)
        {
            beacon_length += aMinSIFSPeriod;
        }
        else
        {
            beacon_length += aMinLIFSPeriod;
        }
        /* Round up to backoff slot boundary. */
        beacon_length = (beacon_length + aUnitBackoffPeriod - 1) /
            aUnitBackoffPeriod;
        beacon_length *= aUnitBackoffPeriod;
        /* Slotted CSMA-CA with macBattLifeExt must start within
         * the first macBattLifeExtPeriods backoff slots of the CAP. */
        beacon_length += mac_pib_macBattLifeExtPeriods * aUnitBackoffPeriod;
        /* Compute absolute time. */
        mac_battlife_latest_start = mac_parse_data.timestamp + beacon_length;
    }

    // scan result
    pand_long_start_p = (wpan_pandescriptor_t *)&msc->data[1];

    // Arrange the beacon data received from parse into a pan descriptor
    // structure style
    pand_long.CoordAddrMode = mac_parse_data.src_addr_mode;

    pand_long.CoordPANId         = mac_parse_data.src_panid;
    pand_long.CoordAddress       = mac_parse_data.src_addr.long_address;
    if (pand_long.CoordAddrMode == FCF_SHORT_ADDR)
    {
        // Blank out the upper address bytes, so in case we've got a short address,
        // the comparison below will behave deterministically.
        memset(((uint8_t *)&pand_long.CoordAddress) + sizeof(uint16_t), 0,
               sizeof(uint64_t) - sizeof(uint16_t));
    }
    pand_long.LogicalChannel  = mac_current_channel;
    pand_long.SuperframeSpec  = mac_parse_data.payload_data.beacon_data.superframe_spec;
    pand_long.LinkQuality     = mac_parse_data.ppduLinkQuality;
    pand_long.TimeStamp       = mac_parse_data.timestamp;
    pand_long.SecurityUse     = false;
    pand_long.ACLEntry        = MAC_NOACLENTRYFOUND;
    pand_long.SecurityFailure = false;

    matchflag = false;

    // We are scanning
    if ((mac_state == MAC_X_as) || (mac_state == MAC_X_ps))
    {
        // We now can compare the beacon frame data with the contents of our
        // pan descriptor storage and determine if we save the pan descriptor data.
        // A PAN is considered the same as an existing one if all, the PAN Id, the
        // coordinator address mode, the coordinator address, and the Logical Channel
        // compare equal.
        for(i=0; i<msc->ResultListSize; i++, pand_long_start_p++)
        {
            if ((pand_long.CoordPANId == pand_long_start_p->CoordPANId)
                && (pand_long.CoordAddrMode == pand_long_start_p->CoordAddrMode)
                && (pand_long.CoordAddress == pand_long_start_p->CoordAddress)
                && (pand_long.LogicalChannel == pand_long_start_p->LogicalChannel))
            {
                // Beacon of our own PAN
                matchflag = true;
                break;
            }
        }
    }

    /* If the pan descriptor is not in our list, and there is space left,
       put it into the list. */
    if((!matchflag) && (msc->ResultListSize < MAX_PANDESCRIPTORS))
    {
        memcpy(pand_long_start_p, &pand_long, sizeof(pand_long));
        msc->ResultListSize++;
    }

    numaddrshort = NUM_SHORT_PEND_ADDR(mac_parse_data.payload_data.beacon_data.pending_addr_spec);
    numaddrlong = NUM_LONG_PEND_ADDR(mac_parse_data.payload_data.beacon_data.pending_addr_spec);

    // In all cases (pan or device) if the payload is not equal to zero
    // or macAutoRequest is false, then we have to generate a MLME_BEACON_NOTIFY.indication.
    if((mac_parse_data.payload_length > 0) || (mac_pib_macAutoRequest == false))
    {
        uint8_t index;

        fbuf = mac_buffer_request();
        ASSERT(fbuf != NULL);
        if(fbuf == NULL)
        {
            return;
        }

        mbni = (mlme_beacon_notify_ind_t *)&fbuf->placeholder[0];

        // Build up the beacon notify indication structure.
        mbni->size           = sizeof(mlme_beacon_notify_ind_t) - sizeof(mbni->size);
        mbni->cmdcode        = MLME_BEACON_NOTIFY_INDICATION;
        mbni->BSN            = mac_parse_data.sequence_number;
        mbni->PANDescriptor  = pand_long;
        mbni->PendAddrSpec   = mac_parse_data.payload_data.beacon_data.pending_addr_spec;

        index = 1;
        if (numaddrshort > 0)
        {
            memcpy(&(mbni->data[index]),
                   mac_parse_data.payload_data.beacon_data.pending_addr_list_short,
                   numaddrshort * sizeof(uint16_t));
            index += numaddrshort * sizeof(uint16_t);
        }
        if (numaddrlong > 0)
        {
            memcpy(&(mbni->data[index]),
                   mac_parse_data.payload_data.beacon_data.pending_addr_list_long,
                   numaddrlong * sizeof(uint64_t));
            index += numaddrlong * sizeof(uint64_t);
        }

        mbni->data[index++] = mac_parse_data.payload_length;

        memcpy(&(mbni->data[index]),
               mac_parse_data.payload_data.beacon_data.payload,
               mac_parse_data.payload_length);
        index += mac_parse_data.payload_length;

        mbni->data[0] = index - 1;
        mbni->size += mbni->data[0];
        bios_pushback_event(mbni);

        mac_buffer_free(fbuf);
    }

    /*
     * If we are tracking beacons due to a previous mlme_sync_request then
     * we have to examine the pending address list of the beacon to see if the
     * PAN coordinator has data for us.
     */
    if(((mac_trackBeacons == SYNC_CONTINUOUSLY) || (mac_trackBeacons == SYNC_ONCE)) &&
       (mac_pib_macAutoRequest == true))
    {
        // PAN-ID and CoordAddress does not have to be checked here, since when we are
        // synced with the coordinator we will only get beacon frames passed from data_ind.c
        // if those conditions are fulfilled

        // Compare our address to the addresses in the address list field
        // of the beacon frame.
        for(i=0; i<numaddrshort; i++)
        {
            // Our short address matches an address in the beacon address list.
            if((memcmp(&mac_parse_data.payload_data.beacon_data.pending_addr_list_short[i],
                       &mac_pib_macShortAddress, sizeof(mac_pib_macShortAddress)) == 0))
            {
                // Request pending data from coordinator (implicit poll)
                // use own short address
                mac_build_data_req_cmd(false, false);
                return;
            }
        }

        for(i=0; i<numaddrlong; i++)
        {
            // Our long address matches an address in the beacon address list.
            if((memcmp( &mac_parse_data.payload_data.beacon_data.pending_addr_list_long[i],
                        &mac_ieee_address, sizeof(mac_ieee_address)) == 0))
            {
                // Request pending data from coordinator (implicit poll)
                // use own long address
                mac_build_data_req_cmd(false, true);
                return;
            }
        }
    }
}

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
