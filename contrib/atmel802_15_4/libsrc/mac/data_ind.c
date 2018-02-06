/**
 * @file
 *
 * @brief This file implements incoming frame handling in the MAC.
 *
 * This file handles parsing of incoming frames from the PHY. The frames are
 * parsed in two passes, whereas the first pass is initiated by the PHY and
 * handles all time critical task necessary to initiate ACk transmission.
 * The second pass handles the further filtering of the frames and calls the
 * corresponding actions within the MAC. As long as the second pass of a valid
 * frame is not finished, no further frame can be processed.
 *
 * $Id: data_ind.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include "timer_const.h"

#if APP_TYPE >= APP_L2 || defined (DOXYGEN)

/* === Globals ============================================================= */

/*
 * Dispatch table to compute MHR and payload offsets.
 *
 * Index is (intra_pan << 4) | (src_addr_mode << 2) | (dest_addr_mode).
 *
 * Invalid entries will get auto-initialized to all 0's, and we use
 * the payload index of 0 to detect an invalid combination of
 * addressing modes.
 */
#define MHR_INDEX(intra_pan, src_mode, dest_mode) \
        (((intra_pan) << 4) | ((src_mode) << 2) | (dest_mode))

FLASH_DECLARE(static mhr_offset_t mhr_offsets[32]) =
{
    /* intra_pan,  src_addr_mode,  dest_addr_mode */
    [MHR_INDEX(0,    FCF_NO_ADDR,    FCF_NO_ADDR)] = { 0, 0, 0, 0, 3 }, /* ACK frames only */
    [MHR_INDEX(0,    FCF_NO_ADDR, FCF_SHORT_ADDR)] = { 3, 5, 0, 0, 7 },
    [MHR_INDEX(0,    FCF_NO_ADDR,  FCF_LONG_ADDR)] = { 3, 5, 0, 0, 13 },
    [MHR_INDEX(0, FCF_SHORT_ADDR,    FCF_NO_ADDR)] = { 0, 0, 3, 5, 7 },
    [MHR_INDEX(0,  FCF_LONG_ADDR,    FCF_NO_ADDR)] = { 0, 0, 3, 5, 13 },
    [MHR_INDEX(0, FCF_SHORT_ADDR, FCF_SHORT_ADDR)] = { 3, 5, 7, 9, 11 },
    [MHR_INDEX(0,  FCF_LONG_ADDR, FCF_SHORT_ADDR)] = { 3, 5, 7, 9, 17 },
    [MHR_INDEX(0, FCF_SHORT_ADDR,  FCF_LONG_ADDR)] = { 3, 5, 13, 15, 17 },
    [MHR_INDEX(0,  FCF_LONG_ADDR,  FCF_LONG_ADDR)] = { 3, 5, 13, 15, 23 },
    [MHR_INDEX(1,    FCF_NO_ADDR,    FCF_NO_ADDR)] = { 0, 0, 0, 0, 3 }, /* ACK frames only */
    [MHR_INDEX(1,    FCF_NO_ADDR, FCF_SHORT_ADDR)] = { 3, 5, 0, 0, 7 },
    [MHR_INDEX(1,    FCF_NO_ADDR,  FCF_LONG_ADDR)] = { 3, 5, 0, 0, 13 },
    [MHR_INDEX(1, FCF_SHORT_ADDR,    FCF_NO_ADDR)] = { 0, 0, 3, 5, 7 },
    [MHR_INDEX(1,  FCF_LONG_ADDR,    FCF_NO_ADDR)] = { 0, 0, 3, 5, 13 },
    /* intra_pan = 1 and both addresses present: src_panid == dst_panid */
    [MHR_INDEX(1, FCF_SHORT_ADDR, FCF_SHORT_ADDR)] = { 3, 5, 3, 7, 9 },
    [MHR_INDEX(1,  FCF_LONG_ADDR, FCF_SHORT_ADDR)] = { 3, 5, 3, 7, 15 },
    [MHR_INDEX(1, FCF_SHORT_ADDR,  FCF_LONG_ADDR)] = { 3, 5, 3, 13, 15 },
    [MHR_INDEX(1,  FCF_LONG_ADDR,  FCF_LONG_ADDR)] = { 3, 5, 3, 13, 21 },
};

/* === Prototypes ========================================================== */
static void init_parse_buffer(void);

/* === Implementation ====================================================== */

/**
 * \brief parse an MPDU
 *
 * This function parses an MPDU, and leaves the parse result in
 * mac_parse_data.
 *
 * Parsing is done in two passes.
 *
 * Pass 1 parses just the MHR fields, and in case of a MAC cmd enough
 * of the payload to decide whether this is going to be a data request
 * so the pending bit needs to be set, and then issues an ACK
 * transmission if needed.  This is supposed to be called as timely as
 * possible from within the PHY layer.
 *
 * Pass 2 then completes parsing.
 *
 * \param pdi the PLME-DATA.indication message to parse
 * \param pass_no the pass number
 * \return bool true if frame OK, or false if frame is invalid or 2nd pass not yet done
 */
bool mac_parse_MPDU(pd_data_ind_t *pdi, uint8_t pass_no)
{
    uint8_t     payload_index;
    uint8_t     temp_byte, i;
    uint16_t    fcf;
    uint8_t     framelen;
    uint8_t     *framep;
    static bool parser_busy = false;

    if (pass_no == 1)
    {
        if (parser_busy)
        {
            return false;
        }

        framelen  = pdi->data[0];
        framep = (uint8_t *)&pdi->data[1];

        /* Catch invalid frame lengths. */
        if (!((framelen == ACK_FRAME_LEN) || (framelen >= MIN_FRAME_LEN)))
        {
            return false;
        }

        parser_busy = true;
        init_parse_buffer();

        mac_parse_data.fcf = fcf = framep[0] | (framep[1] << 8);
        if (fcf & FCF_SECURITY_ENABLED)
        {
            /* We cannot handle that. */
            parser_busy = false;
            return false;
        }
        mac_parse_data.frame_type = FCF_GET_FRAMETYPE(fcf);

        temp_byte = (fcf & FCF_INTRA_PAN)? 1: 0;
        mac_parse_data.dest_addr_mode = FCF_GET_DEST_ADDR_MODE(fcf);
        mac_parse_data.src_addr_mode = FCF_GET_SOURCE_ADDR_MODE(fcf);

        PGM_READ_BLOCK(&mac_parse_data.mhro,
                       mhr_offsets + MHR_INDEX(temp_byte,
                                               mac_parse_data.src_addr_mode,
                                               mac_parse_data.dest_addr_mode),
                       sizeof(mhr_offset_t));

        /* Initial pass over the MPDU. */
        if (mac_parse_data.mhro.payload == 0)
        {
            // Invalid addressing mode
            parser_busy = false;
            return false;
        }
        payload_index = mac_parse_data.mhro.payload;

        if (framelen < payload_index + FCF_SIZE) /* account for FCS */
        {
            // Frame too short
            parser_busy = false;
            return false;
        }

        // Now are frames are valid and can be processed further
        // Copy and evaluate destination address
        if (mac_parse_data.mhro.dest_panid)
        {
            memcpy(&mac_parse_data.dest_panid,
                   framep + mac_parse_data.mhro.dest_panid,
                   sizeof(uint16_t));

            if ((mac_pib_macPANId != BROADCAST) &&
                (mac_parse_data.dest_panid != BROADCAST) &&
                (mac_parse_data.dest_panid != mac_pib_macPANId))
                /* not our frame, discard */
                {
                    parser_busy = false;
                    return false;
                }
        }
        if (mac_parse_data.mhro.dest_addr == 0)
        {
            /*
             * No destination address present.  Only accept the frame
             * if it is either a beacon or an ack frame, or if we are
             * the PAN coordinator.
             */
            if(mac_i_pan_coordinator ||
               (mac_parse_data.frame_type == FCF_FRAMETYPE_BEACON) ||
               (mac_parse_data.frame_type == FCF_FRAMETYPE_ACK))
            {
                /* frame OK, continue */
            }
            else
            {
                /* discard */
                parser_busy = false;
                return false;
            }
        }
        else
        {
            if (mac_parse_data.dest_addr_mode == FCF_SHORT_ADDR)
            {
                memcpy(&mac_parse_data.dest_addr,
                       framep + mac_parse_data.mhro.dest_addr,
                       sizeof(uint16_t));

                if ((mac_parse_data.dest_addr.short_address != BROADCAST) &&
                    (mac_parse_data.dest_addr.short_address != mac_pib_macShortAddress))
                {
                /* not our frame, discard */
                    parser_busy = false;
                    return false;
                }

#if SPECIAL_PEER
                // No production code
                // Required for Test Script parser
                // Short address is contained in long address
                // so we need to clear the remaining octets
                memset((uint8_t *)&mac_parse_data.dest_addr + sizeof(uint16_t),
                       0,
                       sizeof(uint64_t) - sizeof(uint16_t));
#endif /* SPECIAL_PEER */

            }
            else
            {
                memcpy(&mac_parse_data.dest_addr,
                       framep + mac_parse_data.mhro.dest_addr,
                       sizeof(uint64_t));

                if (mac_parse_data.dest_addr.long_address != mac_ieee_address)
                {
                    /* not our frame, discard */
                    parser_busy = false;
                    return false;
                }
            }
        }

        // Get the sequence number
        mac_parse_data.sequence_number = framep[2];

        if (mac_parse_data.frame_type == FCF_FRAMETYPE_MAC_CMD)
        {
            mac_parse_data.mac_command = framep[payload_index++];
        }

        if (mac_parse_data.fcf & FCF_ACK_REQUEST)
        {
            /* We might need to ACK this frame. */
            if (mac_parse_data.frame_type == FCF_FRAMETYPE_MAC_CMD)
            {
                /*
                 * For a data request, we always set the pending bit,
                 * so we can quickly ack the request without further
                 * delays.
                 * For all other commands, the pending bit will be
                 * clear.
                 */
                mac_send_ack(mac_parse_data.mac_command == DATAREQUEST);
            }
            else if (mac_parse_data.frame_type == FCF_FRAMETYPE_DATA)
            {
                mac_send_ack(false);
            }
        }
        mac_parse_data.payload_index = payload_index;

        return true;
    }
    else if(pass_no == 2)
    {
        /* Second pass, continue parsing. */
        framelen  = pdi->data[0];
        framep = (uint8_t *)&pdi->data[1];

        payload_index = mac_parse_data.payload_index;
        mac_parse_data.frame_length = framelen;

        memset(&mac_parse_data.payload_data, 0, sizeof mac_parse_data.payload_data);

        fcf = mac_parse_data.fcf;

        // Copy over source addresses
        if (mac_parse_data.mhro.src_panid)
        {
            memcpy(&mac_parse_data.src_panid,
                   framep + mac_parse_data.mhro.src_panid,
                   sizeof(uint16_t));
        }
        if (mac_parse_data.mhro.src_addr)
        {
            if (mac_parse_data.src_addr_mode == FCF_SHORT_ADDR)
            {
                memcpy(&mac_parse_data.src_addr,
                       framep + mac_parse_data.mhro.src_addr,
                       sizeof(uint16_t));

#if SPECIAL_PEER
                // No production code
                // Required for Test Script parser
                // Short address is contained in long address
                // so we need to clear the remaining octets
                memset((uint8_t *)&mac_parse_data.src_addr + sizeof(uint16_t),
                       0,
                       sizeof(uint64_t) - sizeof(uint16_t));
#endif /* SPECIAL_PEER */

            }
            else
            {
                memcpy(&mac_parse_data.src_addr,
                       framep + mac_parse_data.mhro.src_addr,
                       sizeof(uint64_t));
            }
        }

        mac_parse_data.timestamp = pdi->timestamp;
        mac_parse_data.ppduLinkQuality = pdi->ppduLinkQuality;
        mac_parse_data.security_enable = false;

        switch (mac_parse_data.frame_type)
        {
        case FCF_FRAMETYPE_BEACON:
            // Get the Superframe specification
            memcpy(&mac_parse_data.payload_data.beacon_data.superframe_spec,
                   &framep[payload_index],
                   sizeof(uint16_t));
            payload_index += sizeof(uint16_t);

            // Get the GTS specification
            mac_parse_data.payload_data.beacon_data.gts_spec = framep[payload_index++];

            // If the GTS specification descriptor count is > 0, then
            // increase the index by the correct GTS field octet number
            // GTS directions and GTS address list will not be parsed
            temp_byte = (mac_parse_data.payload_data.beacon_data.gts_spec & GTS_DESCRIPTOR_COUNTER_MASK);
            if (temp_byte > 0)
            {
                // 1 octet GTS diresctions + GTS address list
                payload_index += 1 + temp_byte;
            }

            // Get the Pending address specification
            mac_parse_data.payload_data.beacon_data.pending_addr_spec = framep[payload_index++];

            // If the Pending address specification indicates that the number of
            // short or long addresses is > 0, then get the short and/or long addresses
            temp_byte = NUM_SHORT_PEND_ADDR(mac_parse_data.payload_data.beacon_data.pending_addr_spec);
            if (temp_byte > 0)
            {
                ASSERT(sizeof(mac_parse_data.payload_data.beacon_data.pending_addr_list_short) >=
                       temp_byte * sizeof(uint16_t));
                memcpy(mac_parse_data.payload_data.beacon_data.pending_addr_list_short,
                       &framep[payload_index],
                       (temp_byte * sizeof(uint16_t)));
                payload_index += (temp_byte * sizeof(uint16_t));
            }
            temp_byte = NUM_LONG_PEND_ADDR(mac_parse_data.payload_data.beacon_data.pending_addr_spec);
            if (temp_byte > 0)
            {
                ASSERT(sizeof(mac_parse_data.payload_data.beacon_data.pending_addr_list_long) >=
                       temp_byte * sizeof(uint64_t));
                memcpy(mac_parse_data.payload_data.beacon_data.pending_addr_list_long,
                       &framep[payload_index],
                       (temp_byte * sizeof(uint64_t)));
                payload_index += (temp_byte * sizeof(uint64_t));
            }

            // Is there a beacon payload ?
            if (framelen > payload_index - CRC_SIZE)
            {
                i = framelen - payload_index - CRC_SIZE;

                ASSERT(sizeof(mac_parse_data.payload_data.beacon_data.payload) >= i);
                mac_parse_data.payload_length = i;
                memcpy(mac_parse_data.payload_data.beacon_data.payload,
                       &framep[payload_index],
                       i);
            }
            else
            {
                mac_parse_data.payload_length = 0;
            }
            break;

        case FCF_FRAMETYPE_DATA:
            if (framelen > payload_index - CRC_SIZE)
            {
                mac_parse_data.payload_length = framelen - payload_index - CRC_SIZE;

                // in case we get a frame with a corrupted payload length
                if (mac_parse_data.payload_length >= aMaxMACFrameSize)
                {
                    mac_parse_data.payload_length = aMaxMACFrameSize;
                }

                ASSERT(sizeof( mac_parse_data.payload_data.data.payload ) >=
                       mac_parse_data.payload_length );
                memcpy(mac_parse_data.payload_data.data.payload,
                       &framep[payload_index],
                       mac_parse_data.payload_length);
            }
            else
            {
                mac_parse_data.payload_length = 0;
            }
            break;

        case FCF_FRAMETYPE_ACK:
            /*
             * Nothing to be done here, macDSN will be compared in
             * mac_process_ack_frame(), and CRC has been checked
             * elsewhere.
             */
            break;

        case FCF_FRAMETYPE_MAC_CMD:
            /*
             * We leave the SDL path here.
             *
             * SDL would normally complete parsing the command, then
             * fall back to the caller, which would eventually notice
             * that an ACK needs to be sent (76(154), p. 328).  Upon
             * that, it would walk a lot of state transitions until it
             * could eventually transmit the ACK frame.  This is very
             * likely to happen way too late to be in time for an ACK
             * frame, and it's somewhat funny why that part of SDL
             * would actually go all that way down as all other ACK
             * frames are pushed out onto the queue really quickly,
             * without taking care to await all the response message
             * ping-pong first.
             */

            switch (mac_parse_data.mac_command)
            {
            case ASSOCIATIONREQUEST:
                mac_parse_data.payload_data.assoc_req_data.capability_info = framep[payload_index++];
                break;

            case ASSOCIATIONRESPONSE:
                memcpy(&mac_parse_data.payload_data.assoc_response_data.short_addr,
                       &framep[payload_index],
                       sizeof(uint16_t));
                payload_index += sizeof(uint16_t);
                mac_parse_data.payload_data.assoc_response_data.assoc_status =
                    framep[payload_index];
                break;

            case DISASSOCIATIONNOTIFICATION:
                mac_parse_data.payload_data.disassoc_req_data.disassoc_reason = framep[payload_index++];
                break;

            case COORDINATORREALIGNMENT:
                memcpy(&mac_parse_data.payload_data.coord_realign_data.pan_id,
                       &framep[payload_index],
                       sizeof(uint16_t));
                payload_index += sizeof(uint16_t);

                memcpy(&mac_parse_data.payload_data.coord_realign_data.coord_short_addr,
                       &framep[payload_index],
                       sizeof(uint16_t));
                payload_index += sizeof(uint16_t);

                mac_parse_data.payload_data.coord_realign_data.logical_channel = framep[payload_index++];

                memcpy(&mac_parse_data.payload_data.coord_realign_data.short_addr,
                       &framep[payload_index],
                       sizeof(uint16_t));
                payload_index += sizeof(uint16_t);
                break;

            case ORPHANNOTIFICATION:
            case DATAREQUEST:
            case BEACONREQUEST:
                // Fall through in this case and do nothing
                break;


            default:
                // Unsupported MAC command in parse_MPDU
                parser_busy = false;
                return false;
            }
            break;

        default:
            // Illegal frame type
            parser_busy = false;
            return false;
        }
        return true;
    }
    else if(pass_no == 3)
    {
        parser_busy = false;
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * \brief Processes a PD_DATA.indication message
 *
 * \param msg PD_DATA.indication message
 */

void mac_proc_pd_data_ind(uint8_t *msg)
{
    pd_data_ind_t *pdi = (pd_data_ind_t *)msg;

    // Parse the incoming frame
    if(!mac_parse_MPDU(pdi, 2))
    {
        return;
    }

    switch (mac_state)          /* Number of SDL diagram: */
    {
        case MAC_X_as:              /* 30(154) */
        case MAC_X_ps:              /* 35(154) */
            if (mac_parse_data.frame_type == FCF_FRAMETYPE_BEACON)
            {
                mac_process_beacon_frame();
            }
            break;

        case MAC_X_as2:
            /* ignore incoming frame, we are waiting for TRX_OFF */
            break;

        case MAC_X_os:              /* 42(154) */
            if (mac_parse_data.frame_type == FCF_FRAMETYPE_MAC_CMD &&
                mac_parse_data.mac_command == COORDINATORREALIGNMENT)
            {
                if (mac_parse_data.dest_addr_mode == FCF_LONG_ADDR)
                {
                    // received coordinator realignment frame specifically for us
                    bios_stoptimer(T_scan_duration);
                    // we are in the middle of orphan scan
                    mac_process_coord_realign(true);
                }
                else
                {
                    // received coordinator realignment frame for entire PAN
                    // in the middle of an orphan scan
                    mac_process_coord_realign(false);
                }
            }
            break;

        case MAC_Za:                /* 58(154) */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
            switch (mac_parse_data.frame_type)
            {
                case FCF_FRAMETYPE_MAC_CMD:
                {
                    switch (mac_parse_data.mac_command)
                    {
                    case ASSOCIATIONREQUEST:
                        mac_process_associate_request();
                        break;

                    case DISASSOCIATIONNOTIFICATION:
                        mac_process_disassociate_notification();
                        break;

                    case DATAREQUEST:
                        mac_process_data_request();
                        break;

                    case PANIDCONFLICTNOTIFICAION:
                        break;

                    case ORPHANNOTIFICATION:
                        mac_process_orphan_notification();
                        break;

                    case BEACONREQUEST:
                        mac_process_beacon_request();
                        break;

                    case COORDINATORREALIGNMENT:
                        break;

                    default:
                        PRINT("Unsupported MAC command in MAC_Za: %d.",
                              mac_parse_data.mac_command);
                        break;
                    }
                }
                break;

                case FCF_FRAMETYPE_DATA:
                    mac_process_data_frame();
                    break;

                case FCF_FRAMETYPE_ACK:
                    break;
            }
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
            break;

        case MAC_Tracking_Beacon:   /* 66(154) */
        case MAC_A:                 /* 75(154) */
            /* Is it a Beacon of our Coordinator? */
            switch (mac_parse_data.frame_type)
            {
                case FCF_FRAMETYPE_BEACON:
                    if ((mac_parse_data.src_panid == mac_pib_macPANId) &&
                        (((mac_parse_data.src_addr_mode == FCF_SHORT_ADDR) &&
                          (mac_parse_data.src_addr.short_address == mac_pib_macCoordShortAddress)) ||
                         ((mac_parse_data.src_addr_mode == FCF_LONG_ADDR) &&
                          (mac_parse_data.src_addr.long_address == mac_pib_macCoordExtendedAddress)))
                       )
                    {
                        mac_pib_macBeaconTxTime = pdi->timestamp;

                        if (mac_trackBeacons == SYNC_CONTINUOUSLY)
                        {
                            bios_stoptimer(T_btp);
                            /* To support rx_enable, a DEVICE must have a means to know how
                                many symbols before the next beacon will happen.
                            */
                            bool t_start_res = false;
                            uint32_t temp_time = 0;

                            mac_missed_beacons = 0;
                            while (!t_start_res)
                            {
                                temp_time = bios_add_time(mac_pib_macBeaconTxTime, mac_RollOverTime);
                                temp_time = bios_sub_time(temp_time, mac_phy_wakeuptime);
                                t_start_res = bios_start_absolute_timer(T_btp, temp_time);
                                if (!t_start_res)
                                {
                                    // in case we have been too slow...
                                    mac_pib_macBeaconTxTime = bios_add_time(mac_pib_macBeaconTxTime, mac_RollOverTime);
                                }
                            }
                            // Process a received beacon.
                            mac_process_beacon_frame();
                        }
                        else if(mac_trackBeacons == SYNC_ONCE)
                        {
                            mac_process_beacon_frame();
                            mac_trackBeacons = SYNC_NEVER; // Do this after processing the beacon.
                        }
                    }
                    break;

                case FCF_FRAMETYPE_MAC_CMD:
                    switch (mac_parse_data.mac_command)
                    {
                        case DISASSOCIATIONNOTIFICATION:
                            mac_process_disassociate_notification();
                            // Device needs to scan for networks again
                            // got into idle mode and reset Variables
                            mac_idle_trans();
                            break;

                        case COORDINATORREALIGNMENT:
                            if (mac_parse_data.dest_addr_mode == FCF_SHORT_ADDR)
                            {
                                // received coordinator realignment frame for entire PAN
                                // in the middle of an orphan scan
                                mac_process_coord_realign(false);
                            }
                            else
                            {
                                // received coordinator realignment frame specifically for us
                                // although orphan scan is not in progress
                                bios_stoptimer(T_scan_duration);
                                // do nothing more
                            }
                            break;
                    }
                    break;

                case FCF_FRAMETYPE_DATA:
                    mac_process_data_frame();
                    break;

                default:
                    break;
            }
            break;

        case MAC_F:                 /* 101(154) */
            if (mac_parse_data.frame_type == FCF_FRAMETYPE_ACK)
            {
                ASSERT(mac_message != NULL);
                if (mac_message == NULL)
                {
                    break;
                }
                /* compare DSN */
                if (mac_message->pd_data.data[3] == pdi->data[3])
                {
                    mac_process_ack_frame((mac_parse_data.fcf & FCF_FRAME_PENDING) != 0);
                }
            }
            break;

        case MAC_H:                 /* 112(154) */
            mac_process_data_response();
            // Note: mac_state has changed to previous state now

            switch (mac_parse_data.frame_type)
            {
                case FCF_FRAMETYPE_MAC_CMD:
                {
                    switch (mac_parse_data.mac_command)
                    {
                    case ASSOCIATIONREQUEST:
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
                        mac_process_associate_request();
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
                        break;

                    case DISASSOCIATIONNOTIFICATION:
                        mac_process_disassociate_notification();
                        if(mac_i_pan_coordinator)
                        {
                            mac_state = MAC_Za;
                        }
                        else
                        {
                            // Device needs to scan for networks again
                            // go into idle mode and reset variables
                            mac_idle_trans();
                        }
                        break;

                    case DATAREQUEST:
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
                        mac_process_data_request();
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
                        break;

                    case PANIDCONFLICTNOTIFICAION:
                        break;

                    case ORPHANNOTIFICATION:
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
                        mac_process_orphan_notification();
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
                        break;

                    case BEACONREQUEST:
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
                        mac_process_beacon_request();
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
                        break;

                    case COORDINATORREALIGNMENT:
                            if (mac_parse_data.dest_addr_mode == FCF_SHORT_ADDR)
                        {
                            // received coordinator realignment frame for entire PAN
                            // in the middle of an orphan scan
                            mac_process_coord_realign(false);
                        }
                        else
                        {
                            // received coordinator realignment frame specifically for us
                            // although orphan scan is not in progress
                            bios_stoptimer(T_scan_duration);
                            // do nothing more
                        }
                        break;

                    default:
                        PRINT("Unsupported MAC_CMD in state MAC_H in mac_proc_pd_data_ind:%d",
                              mac_parse_data.mac_command);
                        break;
                    }
                }
                break;

                case FCF_FRAMETYPE_DATA:
                    bios_stoptimer(T_MaxFrameResponseTime);
                    if(mac_trackBeacons == SYNC_CONTINUOUSLY)
                    {
                        mac_state = MAC_Tracking_Beacon;
                    }
                    else
                    {
                        mac_state = MAC_A;
                    }
                    mac_process_data_frame();
                break;
            }
            break;

        case MAC_await_frame:       /* 119(154) */
            switch (mac_parse_data.frame_type)
            {
                case FCF_FRAMETYPE_DATA:
                    bios_stoptimer(T_MaxFrameResponseTime);
                    if(mac_trackBeacons == SYNC_CONTINUOUSLY)
                    {
                        mac_state = MAC_Tracking_Beacon;
                    }
                    else
                    {
                        mac_state = MAC_A;
                    }
                    mac_process_data_frame();
                    break;

                case FCF_FRAMETYPE_MAC_CMD:
                    bios_stoptimer(T_AssocResponseTime);
                    switch (mac_parse_data.mac_command)
                    {
                        case ASSOCIATIONRESPONSE:
                            mac_process_associate_response();
                            break;

                        case DISASSOCIATIONNOTIFICATION:
                            mac_process_disassociate_notification();
                            if(mac_i_pan_coordinator)
                            {
                                mac_state = MAC_Za;
                            }
                            else
                            {
                                // Device needs to scan for networks again
                                // go into idle mode and reset variables
                                mac_idle_trans();
                            }
                            break;

                        case COORDINATORREALIGNMENT:
                            if (mac_parse_data.dest_addr_mode == FCF_SHORT_ADDR)
                            {
                                // received coordinator realignment frame for entire PAN
                                // in the middle of an orphan scan
                                mac_process_coord_realign(false);
                            }
                            else
                            {
                                // received coordinator realignment frame specifically for us
                                // although orphan scan is not in progress
                                bios_stoptimer(T_scan_duration);
                                // do nothing more
                            }
                            break;
                    }
                    break;
            }
            break;

        case MAC_ED:
            /*
             * Ignore all frames received while performing ED measurement,
             * or while performing CCA.
             */
        case MAC_Wait_Response:
            /*
             * Ignore all frames received while in this state.
             */
        case MAC_B:
        case MAC_C:
        case MAC_C2:
        case MAC_D:
        case MAC_E:
            /* Ignore all frames during CSMA-CA */
        case MAC_W:
            /* ignore, can happen if we receive a Disassociation Notification frame from Coord */
        case MAC_Ya1:
        case MAC_Ya:
            /* ignore, can happen if the association procedure is not successful */
            break;

        default:
            ASSERT("Unexpected PD_DATA.indication." == 0);
            break;
    }
    mac_parse_MPDU(pdi, 3);
}

void init_parse_buffer(void)
{
#if DEBUG >= 2
    /*
     * (ACK) Timing does not matter here, without compiler
     * optimization, all bets are off anyway.
     *
     * Clear out the entire parse buffer, as humans might care about
     * getting a ``beautiful view'', including blanking all fields
     * that won't be used at all (like the upper 6 bytes of an address
     * field when there's only a short address in effect).
     *
     * Machines don't care about that, so we don't waste our time when
     * we are interested in fast timing (DEBUG < 2).  Keep in mind
     * that @ F_CPU = 8 MHz, the memset() below takes 185 us which is
     * about the entire time that is available (on 2.4 GHz PHYs) to
     * send out the ACK (192 us).
     */
    memset(&mac_parse_data, 0, sizeof(mac_parse_data));

    mac_parse_data.frame_type = 0xFF;   // FF hex is an invalid frame type
    mac_parse_data.dest_addr_mode = 0xFF;
    mac_parse_data.src_addr_mode = 0xFF;
    mac_parse_data.mac_command = 0xFF;
#else  /* DEBUG < 2, i.e. optimize */
    mac_parse_data.payload_length = 0;
    mac_parse_data.src_panid = 0;
    mac_parse_data.dest_panid = 0;
#endif /* DEBUG >= 2 */
}

#endif /* APP_TYPE >= APP_L2 || defined (DOXYGEN) */

/* EOF */
