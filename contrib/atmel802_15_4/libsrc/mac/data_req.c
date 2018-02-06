/**
 * @file
 *
 * @brief This file implements generation and reception of data request frames.
 *
 * $Id: data_req.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */

/* === Macros =============================================================== */

#define FRAME_CONTROL_0         (0x00)      // Position of frame control 0

/* === Prototypes ========================================================== */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
static frame_buffer_t *null_data_frame(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

/* === Implementation ====================================================== */

/**
 * @brief Builds a data request command frame.
 *
 * This function will build a data request command frame and transmit it.
 *
 *
 * @param Bool expl_poll Data request due to explicit MLME-POLL.request
 * @param Bool forceOwnLongAddr Forces the usage of the Extended Address as Source Address
 *
 * @return Bool that indicates whether the data request command frame has created
 *
 */
bool mac_build_data_req_cmd(bool expl_poll, bool forceOwnLongAddr)
{
    uint8_t                     index;
    frame_buffer_t              *fbuf;
    uint16_t                    fcf;

    if (mac_message != NULL)
    {
        return false;
    }

    /* Call buffer request to get a buffer pointer. */
    fbuf = mac_buffer_request();
    if (fbuf == NULL)
    {
        return false;
    }

    // Long address need to be used if we do not have a short address
    // of if we are forced to use the long address
    // (e.g. in case the coordinator indicates pending data for us using our long address)
    if (
        (mac_pib_macShortAddress == BROADCAST) ||
        (mac_pib_macShortAddress == MAC_NO_SHORT_ADDR) ||
        forceOwnLongAddr
       )
    {
        fcf = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_MAC_CMD) |
            FCF_SET_SOURCE_ADDR_MODE(FCF_LONG_ADDR);
    }
    else
    {
        fcf = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_MAC_CMD) |
            FCF_SET_SOURCE_ADDR_MODE(FCF_SHORT_ADDR);
    }

    fcf = fcf | FCF_ACK_REQUEST;

    index = 1;

    // Build the Frame Control Field
    fbuf->pd_data.data[index++] = fcf & 0xFF;
    fbuf->pd_data.data[index++] = (fcf >> 8) & 0xFF;

    // Build the sequence number
    fbuf->pd_data.data[index++] = mac_pib_macDSN++;

    // No destination address info.

    // Build the source address info.
    // Build the Source PAN ID
    memcpy(&fbuf->pd_data.data[index], &mac_pib_macPANId, sizeof(uint16_t));
    index += sizeof(uint16_t);

    // Build the Source address
    if ((mac_pib_macShortAddress == BROADCAST) ||
        (mac_pib_macShortAddress == MAC_NO_SHORT_ADDR) ||
         forceOwnLongAddr)
    {
        memcpy(&fbuf->pd_data.data[index], &mac_ieee_address, sizeof(uint64_t));
        index += sizeof(uint64_t);
    }
    else
    {
        memcpy(&fbuf->pd_data.data[index], &mac_pib_macShortAddress, sizeof(uint16_t));
        index += sizeof(uint16_t);
    }

    // Build the command frame id
    fbuf->pd_data.data[index++] = DATAREQUEST;

    // If this data request cmd frame was initiated by a device due to a set frame pending bit
    // (without an explicit MLME_poll_request), set msgtye to DATAREQUEST_IMPL_POLL.
    // If this data request cmd frame was initiated by a MLME_poll_request,
    // set msgtype to DATAREQUEST.
    if (expl_poll)
    {
        fbuf->msgtype = DATAREQUEST;
    }
    else
    {
        fbuf->msgtype = DATAREQUEST_IMPL_POLL;
    }

    /* begin MFR */
    index += CRC_SIZE - sizeof(fbuf->pd_data.size);
    fbuf->pd_data.data[0] = fbuf->pd_data.psduLength = index;
    /* end MFR */

    ASSERT(mac_message == NULL);
    mac_message = fbuf;

    /* Start CSMA-CA using backoff and retry (direct transmission) */
    mac_csma_ca(true, true);

    return true;
}



#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
/*
 * Constructs a null data frame
 *
 * Can return NULL pointer if not successful
 */
static frame_buffer_t *null_data_frame(void)
{
    frame_buffer_t  *buf_ptr;
    uint16_t fcf;
    bool use_long_addr;
    uint8_t index = 1;

    buf_ptr = mac_buffer_request();
    if (buf_ptr == NULL)
    {
        return NULL;
    }

    // Reply to frame just parsed so that DST fields are taken from SRC fields of received frame
    use_long_addr = (mac_parse_data.src_addr_mode == FCF_LONG_ADDR);

    /* begin MHR */
    /* FCF */
    fcf = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_DATA);
    if (use_long_addr)
    {
        fcf |= FCF_SET_DEST_ADDR_MODE(FCF_LONG_ADDR);
    }
    else
    {
        fcf |= FCF_SET_DEST_ADDR_MODE(FCF_SHORT_ADDR);
    }

    buf_ptr->pd_data.data[index++] = fcf & 0xFF;
    buf_ptr->pd_data.data[index++] = (fcf >> 8) & 0xFF;

    /* sequence number */
    buf_ptr->pd_data.data[index++] = mac_pib_macDSN++;

    /* dst PANid is set from src PANid of received frame */
    buf_ptr->pd_data.data[index++] = mac_parse_data.src_panid & 0xFF;
    buf_ptr->pd_data.data[index++] = (mac_parse_data.src_panid >> 8) & 0xFF;

    /* dst address is set from src address of received frame */
    if (use_long_addr)
    {
        memcpy(&buf_ptr->pd_data.data[index], &(mac_parse_data.src_addr.long_address), sizeof(uint64_t));
        index += sizeof(uint64_t);
    }
    else
    {
        buf_ptr->pd_data.data[index++] = mac_parse_data.src_addr.short_address & 0xFF;
        buf_ptr->pd_data.data[index++] = (mac_parse_data.src_addr.short_address >> 8) & 0xFF;
    }
    /* end MHR */

    /* no src addressing information */
    /* no data payload, this is a null packet */

    /* begin MFR */
    index += CRC_SIZE - sizeof(buf_ptr->pd_data.size);
    buf_ptr->pd_data.data[0] = buf_ptr->pd_data.psduLength = index;
    /* end MFR */

    buf_ptr->pd_data.size = sizeof(pd_data_req_t) - sizeof(buf_ptr->pd_data.size) + index;
    buf_ptr->pd_data.cmdcode = PD_DATA_REQUEST;
    buf_ptr->msgtype = NULL_FRAME;

    return buf_ptr;
}


/**
 * @brief Processes a received Data Request Command frame
 *
 * This function processes a received Data Request Command frame at the coordinator,
 * searches for pending indirect data frames for the originator and initiates the frame transmission
 * of the data frames via CSMA-CA.
 *
 */
void mac_process_data_request(void)
{
    frame_buffer_t  *buf_ptr = NULL;
    uint8_t         count;

    // If we are not the PAN coordinator, then ignore data requests
    if (!mac_i_pan_coordinator)
    {
        return;
    }

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        mac_buffer_free(mac_message);
        mac_message = NULL;
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

    // Find out if we should be looking for a short or long address
    switch (mac_parse_data.src_addr_mode)
    {
    case FCF_SHORT_ADDR:
        // look for pending data for this short address
        buf_ptr = mac_buffer_report_short_indirect(mac_parse_data.src_addr.short_address, &count);
        if (buf_ptr == NULL)
        {
            if ((buf_ptr = null_data_frame()) == NULL)
                break;
        }
        if (count > 1)
        {
            buf_ptr->placeholder[FRAME_CONTROL_0] |= FCF_FRAME_PENDING;
        }
        ASSERT(mac_message == NULL);
        mac_message = buf_ptr;
        /* Start CSMA-CA using backoff but no retry (indirect transmission) */
        mac_csma_ca(true, false);
        break;

    case FCF_LONG_ADDR:
        // look for pending data for this long address
        buf_ptr = mac_buffer_report_long_indirect(mac_parse_data.src_addr.long_address, &count);
        if (buf_ptr == NULL)
        {
            if ((buf_ptr = null_data_frame()) == NULL)
                break;
        }
        if (count > 1)
        {
            buf_ptr->placeholder[FRAME_CONTROL_0] |= FCF_FRAME_PENDING;
        }
        ASSERT(mac_message == NULL);
        mac_message = buf_ptr;
        /* Start CSMA-CA using backoff but no retry (indirect transmission) */
        mac_csma_ca(true, false);
        break;

    default:
        break;
    }
}
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */


#endif /* APP_TYPE >= APP_L2 */

/* EOF */
