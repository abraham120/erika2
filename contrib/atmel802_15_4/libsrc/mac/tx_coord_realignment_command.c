/**
 * @file
 * @brief This file implements the coordinator realignment command.
 *
 * $Id: tx_coord_realignment_command.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

/* === Implementation ====================================================== */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
/**
 * @brief Send a coordinator realignment command frame
 *
 * This is called either in response to the reception of an orphan
 * notification command from a device (cmd_type = ORPHANREALIGNMENT),
 * or gratuitously whenever the PAN parameters are about to be changed
 * (cmd_type = COORDINATORREALIGNMENT).  In the first case, the
 * paramater mor contains a pointer to the respective
 * MLME-ORPHAN.response message, while in the latter case this
 * parameter is unused, and can be passed as NULL.
 *
 * @param   cmd_type determines directed or broadcast mode
 * @param   mor pointer to mlme_orphan_resp_t message for directed mode
 * @param   new_panid contains the new PAN-ID in case we do a network realignment
 * @param   new_channel contains the new channel in case we do a network realignment
 * @return  success status, false if no buffer is available
 */
bool mac_tx_coord_realignment_command(mac_message_t cmd_type,
                                      mlme_orphan_resp_t *mor,
                                      uint16_t new_panid,
                                      uint8_t new_channel)
{
    uint8_t             index;
    uint16_t            fcf;
    frame_buffer_t      *fbuf;

    // Check if there is already a transaction ongoing
    if (mac_message != NULL)
    {
        return false;
    }

    fbuf = mac_buffer_request();
    if (fbuf == NULL)
    {
        return false;
    }

    index = 1;
    // FCF
    if (cmd_type == ORPHANREALIGNMENT)
    {
        // Coordinator realignment in response to an orphan
        // notification cmd received from a device.  This is always
        // sent to a 64-bit device address, and the device is
        // requested to acknowledge the reception.
        fcf = FCF_SET_SOURCE_ADDR_MODE(FCF_LONG_ADDR) |
            FCF_SET_DEST_ADDR_MODE(FCF_LONG_ADDR) |
            FCF_SET_FRAMETYPE(FCF_FRAMETYPE_MAC_CMD) |
            FCF_ACK_REQUEST;
    }
    else
    {
        // Coordinator realignment gratuitously sent when the PAN
        // configuration changes.  This is sent to the (16-bit)
        // broadcast address.
        fcf = FCF_SET_SOURCE_ADDR_MODE(FCF_LONG_ADDR) |
            FCF_SET_DEST_ADDR_MODE(FCF_SHORT_ADDR) |
            FCF_SET_FRAMETYPE(FCF_FRAMETYPE_MAC_CMD);
    }

    fbuf->pd_data.data[index++] = fcf & 0xff;
    fbuf->pd_data.data[index++] = (fcf >> 8) & 0xff;

    // Insert the DSN
    fbuf->pd_data.data[index++] = mac_pib_macDSN++;

    // Insert the destination PAN ID broadcast
    fbuf->pd_data.data[index++] = (uint8_t) BROADCAST;
    fbuf->pd_data.data[index++] = (BROADCAST >> 8);


    // coord realignment
    if (cmd_type == ORPHANREALIGNMENT)
    {
        // Insert the destination addr
        memcpy(&fbuf->pd_data.data[index], &mor->OrphanAddress, sizeof(uint64_t));
        index += sizeof(uint64_t);
    }
    else
    {
        // Insert the broadcast addr
        fbuf->pd_data.data[index++] = (uint8_t) BROADCAST;
        fbuf->pd_data.data[index++] = (BROADCAST >> 8);

    }

    // Insert the source Pan ID
    fbuf->pd_data.data[index++] = mac_pib_macPANId;
    fbuf->pd_data.data[index++] = (mac_pib_macPANId >> 8);

    // Insert the source address
    memcpy(&fbuf->pd_data.data[index], &mac_ieee_address, sizeof(uint64_t));
    index += sizeof(uint64_t);

    // Insert command frame identifier
    fbuf->pd_data.data[index++] = COORDINATORREALIGNMENT;

    // Insert PAN identifier
    fbuf->pd_data.data[index++] = new_panid;
    fbuf->pd_data.data[index++] = (new_panid >> 8);

    // Insert coordinator short address
    fbuf->pd_data.data[index++] = mac_pib_macShortAddress;
    fbuf->pd_data.data[index++] = (mac_pib_macShortAddress >> 8);

    // Insert the logical channel
    fbuf->pd_data.data[index++] = new_channel;

    // Insert the device's short address, or 0xFFFF if this is a
    // gratuitous realigment.
    if (cmd_type == ORPHANREALIGNMENT)
    {
        fbuf->pd_data.data[index++] = mor->ShortAddress;
        fbuf->pd_data.data[index++] = (mor->ShortAddress >> 8);
    }
    else
    {
        fbuf->pd_data.data[index++] = (uint8_t) BROADCAST;
        fbuf->pd_data.data[index++] = (BROADCAST >> 8);
    }

    /* begin MFR */
    index += CRC_SIZE - sizeof(fbuf->pd_data.size);
    /* end MFR */

    fbuf->pd_data.cmdcode = PD_DATA_REQUEST;
    fbuf->pd_data.data[0] = fbuf->pd_data.psduLength = index;
    fbuf->pd_data.size = sizeof(pd_data_req_t) - sizeof(fbuf->pd_data.size) +
        index;

    fbuf->msgtype = cmd_type;

    ASSERT(mac_message == NULL);
    mac_message = fbuf;

    /* Start CSMA-CA using backoff and retry (direct transmission) */
    mac_csma_ca(true, true);

    return true;
}

#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
