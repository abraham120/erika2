/**
 * @file
 *
 * @brief This file processes an ACK frame, and proceeds with the MAC operation
 *
 * $Id: process_ack_frame.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include "timer_const.h"

#if APP_TYPE >= APP_L2 || defined (DOXYGEN)

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */

/**
 * \brief Process received an ACK frame
 *
 * This funciton processes an received ACK frame and finishes last pending
 * transaction. According to the frame type that has previously been sent the
 * corresponding actionsa are taken and the MAC returns to its standard state.
 *
 * \param has_pending_bit Bool indicates the pending bit was set in the ACK frame
 */
void mac_process_ack_frame(bool has_pending_bit)
{
    // union to save memory
    union
    {
        plme_set_trx_state_req_t pst;
        mlme_disassociate_conf_t mdc;
        mlme_poll_conf_t mpc;
        mcps_data_conf_t mcps;
        plme_set_conf_t psc;
    } u;

    uint8_t psrbuf[sizeof(plme_set_req_t) + sizeof(uint8_t)];
    plme_set_req_t *psr = (plme_set_req_t *)psrbuf;

    ASSERT(mac_state == MAC_F);
    ASSERT(mac_message != NULL);

    if (!mac_phy_autocsmaca)
    {
        bios_stoptimer(T_AckWait);
    }

    /*
     * When running on a PHY that performs automatic ACKs but no
     * automatic CSMA-CA, turn them on again here as we saw our ACK
     * frame, and can continue in fully automatic mode.
     */
    if (mac_phy_autoacks && !mac_phy_autocsmaca)
    {
        psr->PIBAttribute = phyAutoACK;
        psr->data[1] = true;
        plme_set_request_internal(psr, &u.psc);
        ASSERT(u.psc.status == PHY_SUCCESS);
    }

    /* See SDL 103(154) */
    switch (mac_message->msgtype)
    {
    case MCPS_MESSAGE:
        u.mcps.size = sizeof(u.mcps) - sizeof(u.mcps.size);
        u.mcps.cmdcode = MCPS_DATA_CONFIRM;
        u.mcps.status = MAC_SUCCESS;
        u.mcps.msduHandle = mac_message->msduHandle;
        bios_pushback_event((uint8_t *)&u.mcps);
        /* FALLTHROUGH */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case NULL_FRAME:
        mac_buffer_free(mac_message);
        mac_message = NULL;
        mac_state = mac_pre_csmaca_state;
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

    case DISASSOCIATIONNOTIFICATION:
        if (!mac_i_pan_coordinator)
        {
            mac_set_shortaddr(macShortAddress_def);
            mac_set_panid(macPANId_def);
            mac_idle_trans();
        }
        else
        {
            mac_state = mac_pre_csmaca_state;
        }

        u.mdc.size = sizeof(mlme_disassociate_conf_t) - sizeof(u.mdc.size);
        u.mdc.cmdcode = MLME_DISASSOCIATE_CONFIRM;
        u.mdc.status = MAC_SUCCESS;
        bios_pushback_event((uint8_t *)&u.mdc);

        mac_buffer_free(mac_message);
        mac_message = NULL;
        break;

    case ASSOCIATIONREQUEST:
#if SPECIAL_PEER
        /* For purely testing purposes the coordinator may be set into a state
           where it will never repond with an Assoc Response frame */
        if (mac_pib_privateNoDataAfterAssocReq >= 1)
        {
            // Private PIB is set to suppress the transmission of a Data Request frame
            mac_buffer_free(mac_message);
            mac_message = NULL;
            mac_state = mac_pre_csmaca_state;
            break;
        }
#endif /* SPECIAL_PEER */
        mac_buffer_free(mac_message);
        mac_message = NULL;
        mac_state = MAC_Wait_Response;
        if (!bios_starttimer(T_ResponseWaitTime, aResponseWaitTime))
        {
            mac_t_response_wait();
        }
        break;

    case DATAREQUEST_IMPL_POLL:      /* implicit poll without request */
        bios_stoptimer(T_ResponseWaitTime);
        mac_state = MAC_await_frame;
        if (!bios_starttimer(T_MaxFrameResponseTime, aMaxFrameResponseTime))
        {
            mac_t_maxframeresponsetime();
        }
        mac_buffer_free(mac_message);
        mac_message = NULL;
        break;

    case DATAREQUEST:               /* explicit poll caused my MLME-POLL.request */
        /* MLME-POLL.request completed */
        mac_buffer_free(mac_message);
        mac_message = NULL;

        if (!has_pending_bit)
        {
            u.mpc.size = sizeof(u.mpc) - sizeof(u.mpc.size);
            u.mpc.cmdcode = MLME_POLL_CONFIRM;
            u.mpc.status = MAC_NO_DATA;
            bios_pushback_event((uint8_t *)&u.mpc);
            mac_state = mac_pre_csmaca_state;
            return;
        }

        mac_state = MAC_H;
        if (!bios_starttimer(T_MaxFrameResponseTime, aMaxFrameResponseTime))
        {
            mac_t_maxframeresponsetime();
        }
        break;

    case ASSOCIATIONRESPONSE:
    case ORPHANREALIGNMENT:
        // Offset of DST address is the same for both cases
        mac_mlme_comm_status(FCF_LONG_ADDR, &mac_ieee_address, FCF_LONG_ADDR,
                             (uint64_t *)&mac_message->placeholder[ASSOC_RESP_DSTADDR_OFFSET],
                             MAC_SUCCESS);
        mac_buffer_free(mac_message);
        mac_message = NULL;
        mac_state = mac_pre_csmaca_state;
        break;

    default:
        ASSERT("Unknown message type in mac_process_ack_frame()." == 0);
        return;
    }
}

#endif /* APP_TYPE >= APP_L2 || defined (DOXYGEN) */

/* EOF */
