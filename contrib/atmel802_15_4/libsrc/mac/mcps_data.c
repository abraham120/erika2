/**
 * @file
 *
 * @brief Handles MCPS related primitives and frames
 *
 * This files handles MCPS-DATA requests from the upper layer,
 * generates data frames and initiates its transmission, and
 * processes received data frames.
 *
 * $Id: mcps_data.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#if APP_TYPE >= APP_L2 || defined (DOXYGEN)

/* === Globals ============================================================= */


/* === Prototypes ========================================================== */

static void build_data_frame(frame_buffer_t *pfbuf, mcps_data_req_t *pmdr);

/* === Implementation ====================================================== */


/*
 * Internal function to initiate mcps data confirm message.
 */
static void gen_mcps_data_conf(mcps_data_conf_t* mdc, uint8_t status, uint8_t handle)
{
   mdc->size = sizeof(mcps_data_conf_t) - sizeof(mdc->size);
   mdc->cmdcode = MCPS_DATA_CONFIRM;
   mdc->msduHandle = handle;
   mdc->status = status;
   bios_pushback_event((uint8_t *)mdc);
}

/**
 * @brief   Build the data frame for transmission. The NWK layer has supplied
 *          the parameters. We need to construct the mcps_data_req_t data type
 *          and fill it in. We also construct the FCF based on the parameters
 *          passed into us.
 *
 *          ASSUMPTION: The pointer to the data passed into the function is a
 *                      pointer to type "mcps_data_req_t".
 *
 * @param msg A pointer to the MCPS-DATA.request parameter
 */
void mcps_data_request(uint8_t *msg)
{
    mcps_data_req_t *mdr = (mcps_data_req_t *)msg;
    mcps_data_conf_t mdc;
    frame_buffer_t *fbuf;

    /* Indirect transmission only allowed for coordinator, otherwise ignore */
    if((mdr->TxOptions & INDIRECT_TRANSMISSION) && (!mac_i_pan_coordinator))
    {
        mdr->TxOptions &= ~(INDIRECT_TRANSMISSION);
    }

    if (mdr->TxOptions & INDIRECT_TRANSMISSION)
    {
        /* Now we can only be a coordinator. (See clearing of Indirect Bit above).
           mac_i_pan_coordinator is only set once we have successfully started a PAN.
           Data Requests using indirect transmission is allowed in all states after
           a network has been started, since the frame is simply put inot the queue.
           Conclusion: We do not need to check any states here. */
    }
    else
    {
        /* Data Requests for a device are accepted in all non-transient state except in MAC_W.
           All transient states (scanning in progress, waiting for responses after poll,
           or CSMA-CA states are not allowed */
        /* Data Requests for a coordinator using direct transmission are accepted
           in all non-transient state except in MAC_W.
           All transient states (scanning in progress, waiting for responses after poll,
           or CSMA-CA states are not allowed. */
        if (!((mac_state == MAC_Za) ||
              (mac_state == MAC_A) ||
              (mac_state == MAC_Tracking_Beacon) ||
              (mac_state == MAC_Ya) ||
              (mac_state == MAC_Za) ||
              (mac_state == MAC_Zp)
             ))
        {
            gen_mcps_data_conf(&mdc, (uint8_t) MAC_CHANNEL_ACCESS_FAILURE, mdr->msduHandle);
            return;
        }
    }

    /* check whether somebody requests an ACK of broadcast frames ... */
    if ((mdr->TxOptions & ACK_TRANSMISSION) &&
        (mdr->DstAddrMode == FCF_SHORT_ADDR) &&
        (mdr->DstAddr == BROADCAST))
    {
        gen_mcps_data_conf(&mdc, (uint8_t) MAC_INVALID_PARAMETER, mdr->msduHandle);
        return;
    }

    /* check whether both Src and Dst Address are not present */
    if ((mdr->SrcAddrMode == FCF_NO_ADDR) &&
        (mdr->DstAddrMode == FCF_NO_ADDR))
    {
        gen_mcps_data_conf(&mdc, (uint8_t) MAC_INVALID_PARAMETER, mdr->msduHandle);
        return;
    }

    /* check whether Src or Dst Address indicate reserved values */
    if ((mdr->SrcAddrMode == FCF_RESERVED_ADDR) ||
        (mdr->DstAddrMode == FCF_RESERVED_ADDR))
    {
        gen_mcps_data_conf(&mdc, (uint8_t) MAC_INVALID_PARAMETER, mdr->msduHandle);
        return;
    }

    /* Handle security here if called for, otherwise use the
       debug print statement. */
    if(mdr->TxOptions & SECURITY_TRANSMISSION)
    {
        gen_mcps_data_conf(&mdc, (uint8_t) MAC_UNAVAILABLE_KEY, mdr->msduHandle);
        return;
    }

    /* Handle the check for the maximum frame size that can be transmitted. */
    if (mdr->msduLength > aMaxMACFrameSize)
    {
        gen_mcps_data_conf(&mdc, (uint8_t) MAC_INVALID_PARAMETER, mdr->msduHandle);
        return;
    }

    if(mdr->TxOptions & GTS_TRANSMISSION)  // GTS not supported
    {
        gen_mcps_data_conf(&mdc, (uint8_t) MAC_INVALID_PARAMETER, mdr->msduHandle);
        return;
    }

    /* Handle Indirect transmission here if called for. */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    else if((mdr->TxOptions & INDIRECT_TRANSMISSION) && (mac_i_pan_coordinator))
    {

        fbuf = mac_buffer_request_indirect();
        // If no capacity then issue mcps_data_conf(TRANSACTION_OVERFLOW).
        if (fbuf == NULL)
        {
            gen_mcps_data_conf(&mdc, (uint8_t) MAC_TRANSACTION_OVERFLOW, mdr->msduHandle);
            return;
        }

        // If we are in non-beaconing mode and the coordinator does have pending data
        // the MAC persistence timer needs to be started, which is realized by means of
        // the beacon timer
        mac_check_persistence_timer();

        fbuf->msgtype = MCPS_MESSAGE;
        fbuf->msduHandle = mdr->msduHandle;

        // We have an indirect buffer, build the frame.
        build_data_frame(fbuf, mdr);
        return;
    }
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

    /* We are NOT GTS and NOT indirect, we need to transmit using
       CSMA_CA in the CAP (for beacon enabled) or immediately (for
       a non-beacon enabled). */
    else
    {
        fbuf = mac_buffer_request();
        if(fbuf == NULL)
        {
            gen_mcps_data_conf(&mdc, (uint8_t) MAC_TRANSACTION_OVERFLOW, mdr->msduHandle);
            return;
        }

        build_data_frame(fbuf, mdr);
        ASSERT(mac_message == NULL);
        mac_message = fbuf;
        fbuf->msgtype = MCPS_MESSAGE;
        fbuf->msduHandle = mdr->msduHandle;

        /* Start CSMA-CA using backoff and retry (direct transmission) */
        mac_csma_ca(true, true);

    }
}

/*
 * Internal function to build the data frame.
 */
void build_data_frame(frame_buffer_t *fbuf, mcps_data_req_t *pmdr)
{
    uint8_t index;
    bool intrabit;
    uint16_t fcf;

    /* Fill out the parameters per 7.1.1.1.1, table 27 pg. 56 */

    // Construct FCF first.
#if SPECIAL_PEER
    /*
     * When performing tests, this PIB attribute defaults to 1 (i. e. a
     * standard data frame).  If not set to 1, it is used as a
     * (supposedly illegal) frame type to fill into the frame type
     * field of the data frame's FCF.  In effect, valid (illegal)
     * values range from 4 through 7.
     */
    if (mac_pib_privateIllegalFrameType != 1)
    {
        fcf = FCF_SET_FRAMETYPE(mac_pib_privateIllegalFrameType);
    }
    else
#endif /* SPECIAL_PEER */
    {
        fcf = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_DATA);
    }

    if (pmdr->TxOptions & ACK_TRANSMISSION)
    {
        fcf |= FCF_ACK_REQUEST;
    }

    intrabit = false;
    if ((pmdr->SrcPANId == pmdr->DstPANId) &&
        (pmdr->SrcAddrMode != FCF_NO_ADDR) &&
        (pmdr->DstAddrMode != FCF_NO_ADDR))
    {
        // Set intra_pan bit.
        intrabit = true;
        fcf |= FCF_INTRA_PAN;
    }

    // set FCFs address mode byte
    fcf |= FCF_SET_SOURCE_ADDR_MODE(pmdr->SrcAddrMode);
    fcf |= (FCF_SET_DEST_ADDR_MODE(pmdr->DstAddrMode));

    index = 1;

    // Build the Frame Control Field
    fbuf->pd_data.data[index++] = fcf & 0xff;
    fbuf->pd_data.data[index++] = (fcf >> 8) & 0xff;

    // Populate the DSN.
    fbuf->pd_data.data[index] = mac_pib_macDSN++;

    index++;
    // Build the addressing fields. Destination first.
    if (pmdr->DstAddrMode != FCF_NO_ADDR)
    {
        fbuf->pd_data.data[index++] = pmdr->DstPANId;
        fbuf->pd_data.data[index++] = (pmdr->DstPANId >> 8);
        if(pmdr->DstAddrMode == FCF_LONG_ADDR)
        {
            memcpy(&fbuf->pd_data.data[index], &pmdr->DstAddr, sizeof(uint64_t));
            index += sizeof(uint64_t);
        }
        else
        {
            memcpy(&fbuf->pd_data.data[index], &pmdr->DstAddr, sizeof(uint16_t));
            index += sizeof(uint16_t);
        }
    }
    // Source PANId, if not intra-PAN && source address present
    if (!intrabit && (pmdr->SrcAddrMode != FCF_NO_ADDR))
    {
        fbuf->pd_data.data[index++] = pmdr->SrcPANId;
        fbuf->pd_data.data[index++] = (pmdr->SrcPANId >> 8);
    }
    if (pmdr->SrcAddrMode != FCF_NO_ADDR)
    {
        if (pmdr->SrcAddrMode == FCF_LONG_ADDR)
        {
            memcpy(&fbuf->pd_data.data[index], &pmdr->SrcAddr, sizeof(uint64_t));
            index += sizeof(uint64_t);
        }
        else
        {
            memcpy(&fbuf->pd_data.data[index], &pmdr->SrcAddr, sizeof(uint16_t));
            index += sizeof(uint16_t);
        }
    }
    // Set the size. Add 2 bytes for FCS.
    fbuf->pd_data.psduLength = fbuf->pd_data.data[0] =
        pmdr->msduLength + index + CRC_SIZE - sizeof(fbuf->pd_data.size);

    fbuf->pd_data.size = sizeof(fbuf->pd_data) + fbuf->pd_data.data[0];

    // Now copy the MPDU payload over.
    ASSERT(sizeof(fbuf->placeholder) - index >= pmdr->msduLength);
    memcpy(&fbuf->pd_data.data[index], &pmdr->data[1], pmdr->msduLength);
}


/**
 * @brief Processes a received data frame.
 *
 * This function will process a received data frame. The result will be a
 * MAC to Stack MLME_data_indication call.
 */
void mac_process_data_frame(void)
{
    mcps_data_ind_t         *mdi = (mcps_data_ind_t *)mac_buffer;

    mdi->ACLEntry = MAC_NOACLENTRYFOUND;
    // Build the MLME_Data_indication parameters
    mdi->SrcAddrMode = mac_parse_data.src_addr_mode;
    mdi->SrcPANId = mac_parse_data.src_panid;
    mdi->SrcAddr = mac_parse_data.src_addr.long_address;
    mdi->DstAddrMode = mac_parse_data.dest_addr_mode;
    mdi->DstPANId = mac_parse_data.dest_panid;
    mdi->DstAddr = mac_parse_data.dest_addr.long_address;
    mdi->mpduLinkQuality = mac_parse_data.ppduLinkQuality;
    mdi->SecurityUse = false;
    mdi->msduLength = mac_parse_data.payload_length;
    mdi->data[0] = mdi->msduLength;

    ASSERT( (aMaxPHYPacketSize + sizeof(pd_data_ind_t)) - sizeof(mcps_data_ind_t) >= mdi->msduLength );
    memcpy(&mdi->data[1], &mac_parse_data.payload_data.data.payload[0],  mdi->msduLength);

    // Send a data indication to the stack only if it contains payload to avoid null frame noise
    if (mdi->msduLength > 0)
    {
        mdi->size    = sizeof(mcps_data_ind_t) - sizeof(mdi->size)+ (mdi->msduLength);
        mdi->cmdcode = MCPS_DATA_INDICATION;
        bios_pushback_event((uint8_t *) mdi);
    }

    // Check and see if the frame pending bit was set on the received data frame
    // Only valid if we are not coordinator
    if ((!mac_i_pan_coordinator) && (mac_parse_data.fcf & FCF_FRAME_PENDING))
    {
        // Build command frame due to implicit poll request
        mac_build_data_req_cmd(false, false);
    }
}


#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)

/**
 * @brief Processes an MCPS-PURGE.request primitive.
 *
 *        The MCPS-PURGE.request primitive allows the next higher layer
 *        to purge an MSDU from the transaction queue.
 *        On receipt of the MCPS-PURGE.request primitive, the MAC sublayer
 *        attempts to find in its transaction queue the MSDU indicated by the
 *        msduHandle parameter. If an MSDU matching the given handle is found,
 *        the MSDU is discarded from the transaction queue, and the MAC
 *        sublayer issues the MCPSPURGE. confirm primitive with a status of
 *        SUCCESS. If an MSDU matching the given handle is not found, the MAC
 *        sublayer issues the MCPS-PURGE.confirm primitive with a status of
 *        INVALID_HANDLE.
 *
 * @param msg A pointer to the MCPS-PURGE.request parameter
 */
void mcps_purge_request(uint8_t *msg)
{
    mcps_purge_req_t *mpr = (mcps_purge_req_t *)msg;
    mcps_purge_conf_t mpc;

    // Remove the requested buffer if it is still in the queue.
    mpc.size = sizeof(mcps_purge_conf_t) - sizeof(mpc.size);
    mpc.cmdcode = MCPS_PURGE_CONFIRM;
    mpc.msduHandle = mpr->msduHandle;
    mpc.status = mac_buffer_purge(mpr->msduHandle) ? MAC_SUCCESS : MAC_INVALID_HANDLE;
    bios_pushback_event((uint8_t *)&mpc);
}

#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

#endif /* APP_TYPE >= APP_L2 || defined (DOXYGEN)*/

/* EOF */
