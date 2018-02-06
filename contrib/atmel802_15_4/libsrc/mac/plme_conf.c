/**
 * @file
 * This file implements state transitions caused by the various
 * PLME_*.confirm messages received from the PHY.
 *
 * \brief
 * This file implements functions to handle all PLME-*.confirm primitives and
 * their corresponding handlers. This inlcudes the PLME-SET, PLME-SET-TRX-STATE,
 * and PD-DATA primitives.
 *
 * $Id: plme_conf.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
static void restart_pending_transaction(void);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

/* === Implementation ====================================================== */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
/* Checks whether a suspended transaction postponed by the
   Beacon transmissions shall be resumed */
static void restart_pending_transaction(void)
{
    // reset flag to enable csma_ca now
    mac_beacon_flag = false;

    if (mac_message->usage == BUFFER_INDIRECT)
    {
        /* Start CSMA-CA using backoff but no retry (indirect transmission) */
        mac_csma_ca(true, false);
    }
    else if (mac_message->usage == BUFFER_DIRECT)
    {
        // There was a pending transaction (e.g. Tx of Coord Realignment)
        // which needs to be finished
        switch (mac_message->msgtype)
        {
            case ORPHANREALIGNMENT:
            case COORDINATORREALIGNMENT:
                /* Start CSMA-CA using backoff and retry (direct transmission) */
                mac_csma_ca(true, true);
                break;

            case NULL_FRAME:
                /* Start CSMA-CA using backoff but no retry (similar to indirect transmission) */
                mac_csma_ca(true, false);
                break;

            default:
                ASSERT("Unexpected mac_message msgtype" == 0);
                break;
        }
    }
    else
    {
        ASSERT("Unexpected mac_message usage" == 0);
    }
}
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */



/**
 * \brief process a PLME_SET_TRX_STATE.confirm message
 *
 * \param m PLME_SET_TRX_STATE.confirm message
 */
void mac_proc_plme_set_trx_state_confirm(uint8_t *m)
{
    plme_set_trx_state_conf_t *psd = (plme_set_trx_state_conf_t *)m;

    switch (mac_state)
    {
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case MAC_ED:
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
    case MAC_X_as:
    case MAC_X_as1:
    case MAC_X_as2:
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */
    case MAC_X_ps:
    case MAC_X_os:
    case MAC_X_os1:
        mac_scan_set_trx_state_conf((plme_set_trx_state_conf_t *)psd);
        break;

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case MAC_Ya1:
        mac_start_request_set_rx_on_conf((plme_set_trx_state_conf_t *)psd);
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

    case MAC_C:
    case MAC_C2:
    case MAC_D:
    case MAC_F:
        mac_csma_ca_do_cca(psd->status);
        break;

    case MAC_W:
    case MAC_Za:
    case MAC_Zp:
    case MAC_Ya:
    case MAC_B:
    case MAC_E:
    case MAC_H:
    case MAC_A:
    case MAC_Tracking_Beacon:
    case MAC_Wait_Response:
    case MAC_await_frame:
        // ignore
        break;

    default:
        ASSERT("Unexpected PLME_SET_TRX_STATE.confirm" == 0);
        break;
    }
}

/**
 * \brief process a PLME_SET.confirm message
 *
 * \param m PLME_SET.confirm message
 */

void mac_proc_plme_set_confirm(uint8_t *m)
{
    plme_set_conf_t *psd = (plme_set_conf_t *)m;

    switch (mac_state)
    {
    case MAC_W:
        //can happen if we receive a coordinator realignment during silent join
        break;

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case MAC_ED:
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
    case MAC_X_as:
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */
    case MAC_X_ps:
    case MAC_X_os:
        mac_scan_set_conf(psd);
        break;

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case MAC_Ya:    // Standard after active scan
    case MAC_Za:    // Start once we are already running with new parameters
        ASSERT(psd->PIBAttribute == phyCurrentChannel);
        mac_start_request_set_phyCurrentChannel_conf(psd);
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

    case MAC_B:
    case MAC_A:
    case MAC_Tracking_Beacon:
        /* ignore, can happen when we get a Sync request */
    case MAC_C:
        break;

    default:
        ASSERT("Unexpected PLME_SET.confirm" == 0);
        break;
    }
}


/**
 * \brief Process a PLME_PD_DATA.confirm message
 *
 * This function processes a PLME_PD_DATA.confirm messsage.
 * If a beacon frame was sent previously the beacon transmission
 * transaction will be finalized. If an ACK frame was sent previously
 * the ACK transmission transaction will be finalized.
 *
 * \param m PLME_PD_DATA.confirm message
 */

void mac_proc_pd_data_confirm(uint8_t *m)
{
    plme_set_trx_state_req_t    pst;
    plme_set_trx_state_conf_t   psc;
    pd_data_conf_t *pdc = (pd_data_conf_t *)m;

    if ((pdc->status == PHY_SUCCESS) && (mac_beacon_flag || mac_ack_flag))
    {
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
        if ((mac_beacon_flag) && (mac_message != NULL))
        {
            restart_pending_transaction();
        }
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

        /* A Beacon or an ACK has been sent out */
        mac_beacon_flag = mac_ack_flag = false;

        // Turn the radio to PHY_RX_ON.
        pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
        pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        pst.state   = PHY_RX_ON;
        plme_set_trx_state_request_internal(&pst, &psc);
        return;
    }

    switch (mac_state)
    {
        case MAC_Ya:
            pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
            pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
            pst.state   = PHY_RX_ON;
            bios_pushback_event((uint8_t *)&pst);
            mac_state = MAC_Ya1;
            break;

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
        case MAC_X_as:
        case MAC_X_as1:
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */
        case MAC_X_os:
            mac_scan_pd_data_conf();
            break;

        case MAC_E:
            mac_csma_ca_pd_sent(m);
            break;

        case MAC_W:
        case MAC_Za:
        case MAC_A:
        case MAC_Tracking_Beacon:
        case MAC_B:
        case MAC_C:
            break;

        default:
            ASSERT("Unexpected PD-DATA.confirm" == 0);
            break;
    }
}

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
