/**
 * @file
 * @brief This file implements the CSMA-CA algorithm.
 *
 * $Id: csma_ca.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#include <stdlib.h>
#ifndef DEF_H
#include "def.h"
#endif

#include "phy.h"
#include "mac.h"
#include "timer_const.h"

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Defines ============================================================= */

/* Flag value to indicate (in the NR variable below) that no frame
 * retries should be performed when an ACK-requested frame did not get
 * an ACK.  Used for indirect transmissions. */
#define NO_FRAME_RETRIES (255)

/* === Globals ============================================================= */

/* Variable names match the IEEE 802.15.4 description. */
static uint8_t NB;              /* number of backoffs */
static uint8_t CW;              /* congestion window */
static uint8_t BE;              /* backoff exponent */
/* Additional variable to keep track of number of retries due to erroneous
   SDL (mixing of NB and retry count) */
static uint8_t NR;              /* number of retries */

/* In slotted operation, the length of the current transaction. */
static uint16_t transaction_length;

/* === Prototypes ========================================================== */

static void backoff(uint8_t do_rand);
static void channel_access_failure(void);
static void select_response(uint8_t statM);

/* === Implementation ====================================================== */


/**
 * \brief T_backoff timer callback
 *
 * Proceed with the CSMA-CA algorithm that has been started, once
 * the T_backoff timer has expired.
 */
void mac_t_backoff(void)
{
    plme_set_trx_state_req_t pst;

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        mac_state = mac_pre_csmaca_state;
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

    pst.size = sizeof(pst) - sizeof(pst.size);
    pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
    pst.state = PHY_RX_ON;

    bios_pushback_event((uint8_t *)&pst);

    mac_state = MAC_C;
}

/**
 * \brief PLME-SET-TRX-STATE.confirm callback
 *
 * Proceed with the CSMA-CA algorithm that has been started, once
 * a PLME-SET-TRX-STATE.confirm message has been received.
 *
 * \param phystatus The PHY status from the PLME-SET-TRX-STATE.confirm message
 */
void mac_csma_ca_do_cca(uint8_t phystatus)
{
    plme_cca_req_t pcr;
    pd_data_req_t *pdr;
    plme_set_trx_state_req_t pst;

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        mac_state = mac_pre_csmaca_state;
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

#if SPECIAL_PEER
    /*
     * Force channel access failure for test purposes.  Used in test
     * scripts to verify the correct error recovery.
     */
    if (mac_pib_privateCCAFailure == 1)
    {
        /* CCA shall be failing for testing purposes */
        channel_access_failure();
        return;
    }
#endif /* SPECIAL_PEER */

    if (mac_state == MAC_C)
    {
        if (phystatus == PHY_SUCCESS || phystatus == PHY_RX_ON)
        {
            pcr.size = sizeof(pcr) - sizeof(pcr.size);
            pcr.cmdcode = PLME_CCA_REQUEST;

            bios_pushback_event((uint8_t *)&pcr);
            mac_state = MAC_C2;
            return;
        }
        channel_access_failure();
    }
    else if (mac_state == MAC_D)
    {
        if (phystatus == PHY_SUCCESS || phystatus == PHY_TX_ON)
        {
            ASSERT(mac_message != NULL);
            if (mac_message == NULL)
            {
                /* Abort CSMA-CA here. */
                mac_state = mac_pre_csmaca_state;
                return;
            }
            pdr = (pd_data_req_t *)&mac_message->pd_data;
            pdr->cmdcode = PD_DATA_REQUEST;
            pdr->size = sizeof(*pdr) - sizeof(pdr->size) + pdr->psduLength;
            bios_pushback_event((uint8_t *)pdr);

            if ((mac_message->pd_data.data[1] & FCF_ACK_REQUEST) &&
                !mac_phy_autocsmaca)
            {
                pst.size = sizeof(pst) - sizeof(pst.size);
                pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
                pst.state = PHY_RX_ON;
                bios_pushback_event((uint8_t *)&pst);
            }

            mac_state = MAC_E;
            return;
        }
        else
        {
            pst.size = sizeof(pst) - sizeof(pst.size);
            pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
            pst.state = PHY_RX_ON;
            bios_pushback_event((uint8_t *)&pst);

            channel_access_failure();
        }
    }
    else if (mac_state == MAC_F)
    {
        /* NB: SDL 100(154) has a bug here, TRX_OFF certainly isn't
         * an 'expected result'. */
        if (phystatus == PHY_SUCCESS || phystatus == PHY_RX_ON)
        {
            /* 'expected result' */
            return;
        }
        channel_access_failure();
    }
    else if (mac_state == MAC_C2)
    {
        // ignore
        // can happen during stress tests
    }
    else
    {
        ASSERT("mac_csma_ca_do_cca() in wrong state" == 0);
    }
}


/**
 * \brief PLME-CCA.confirm callback
 *
 * Proceed with the CSMA-CA algorithm that has been started, once a
 * PLME-CCA.confirm message has been received.
 *
 * \param m PLME_CCA.confirm message
 */
void mac_csma_ca_cca_done(uint8_t *m)
{
    plme_cca_conf_t *pec = (plme_cca_conf_t *)m;
    plme_set_trx_state_req_t pst;

    uint8_t chan_stat = pec->status;

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        mac_state = mac_pre_csmaca_state;
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

    if (mac_message == NULL)
    {
        /* Abort CSMA-CA here. */
        mac_state = mac_pre_csmaca_state;
        return;
    }

    if (chan_stat == PHY_IDLE)
    {
        if ( (mac_pib_macBeaconOrder == NON_BEACON_NETWORK) || (--CW == 0) )
        {
            /*
             * Unslotted CSMA-CA, or slotted CSMA-CA and congestion
             * window exhausted.
             */
            pst.size = sizeof(pst) - sizeof(pst.size);
            pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
            pst.state = PHY_TX_ON;
            bios_pushback_event((uint8_t *)&pst);
            mac_state = MAC_D;
        }
        else
        {
            /* Slotted CSMA-CA, next attempt inside congestion window. */
            backoff(false);
        }
    }
    else
    {
        /*
         * Channel busy, start over.
         */
        if (++NB > mac_pib_macMaxCSMABackoffs)
        {
            /* CSMA-CA failed */
            channel_access_failure();
        }
        else
        {
            if (BE != aMaxBE)
            {
                BE++;
            }
            CW = 2;
            backoff(true);
        }
    }
}

/**
 * \brief PD-DATA.confirm callback
 *
 * Proceed with the CSMA-CA algorithm that has been started, once
 * a PD-DATA.confirm message has been received.
 *
 * \param m Pointer to PD-DATA.confirm message
 */
void mac_csma_ca_pd_sent(uint8_t *m)
{
    plme_set_trx_state_req_t pst;
    uint8_t psrbuf[sizeof(plme_set_req_t) + sizeof(uint8_t)];
    plme_set_req_t *psr = (plme_set_req_t *)psrbuf;
    plme_set_conf_t psc;
    bool ack_req;

    ASSERT(mac_message != 0);
    ack_req = (mac_message->pd_data.data[1] & FCF_ACK_REQUEST) != 0;

    if (mac_phy_autocsmaca)
    {
        pd_data_conf_t *pdc = (pd_data_conf_t *)m;
        /*
         * As the hardware runs automatic CSMA-CA, the currently
         * requested transaction has finished at this point,
         * somehow.  Examine the status, generate the respective
         * response, and finish the internal CSMA-CA.
         */
        switch (pdc->status)
        {
        case PHY_SUCCESS:
            if (ack_req)
            {
                mac_state = MAC_F;
                mac_process_ack_frame(false);
            }
            else
            {
                select_response(MAC_SUCCESS);
            }
            break;

        case PHY_SUCCESS_DATA_PENDING:
            if (ack_req)
            {
                mac_state = MAC_F;
                mac_process_ack_frame(true);
            }
            else
            {
                select_response(MAC_SUCCESS);
            }
            break;

        case MAC_CHANNEL_ACCESS_FAILURE:
            channel_access_failure();
            break;

        case MAC_NO_ACK:
            select_response(MAC_NO_ACK);
            break;

        default:
            ASSERT("Invalid pdc->status in Auto-CSMA-CA completion." == 0);
            channel_access_failure();
            break;
        }

        pst.size = sizeof(pst) - sizeof(pst.size);
        pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        pst.state = PHY_RX_ON;
        bios_pushback_event((uint8_t *)&pst);

        return;
    }

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        mac_state = mac_pre_csmaca_state;
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

    if (ack_req)
    {
        /*
         * When running on a PHY that performs automatic ACKs but
         * no automatic CSMA-CA, turn them off here so the
         * received ACK frames will be announced.
         */
        if (mac_phy_autoacks)
        {
            psr->PIBAttribute = phyAutoACK;
            psr->data[1] = false;
            plme_set_request_internal(psr, &psc);
            ASSERT(psc.status == PHY_SUCCESS);
        }

        mac_state = MAC_F;

        if (!bios_starttimer(T_AckWait, mac_pib_macAckWaitDuration))
        {
            // ACK timer could not be started, call immediate actions
            mac_t_ackwait();
        }
    }
    else
    {
        pst.size = sizeof(pst) - sizeof(pst.size);
        pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        pst.state = PHY_RX_ON;
        bios_pushback_event((uint8_t *)&pst);

        select_response(MAC_SUCCESS);
    }
}

/**
 * \brief This implements the CSMA-CA algorithm
 *
 * This function is called from outside with init_nb == true.  The
 * CSMA-CA algorithm itself can recursively call it with init_nb ==
 * false.
 *
 * The init_nr parameter decides whether the frame retry algorithm is
 * to be used or not.  It is true for direct frames and false for
 * indirect frames, as the latter are not being retried.
 *
 * \param init_nb True for initial call
 * \param init_nr True to activate frame retry algorithm
 */
void mac_csma_ca(uint8_t init_nb, uint8_t init_nr)
{
    plme_set_trx_state_req_t pst;

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

    if (init_nb)
    {
        NB = 0;
        mac_pre_csmaca_state = mac_state;
        mac_state = MAC_B;

        /* In slotted operation, calculate the number of symbols
         * required for the current transaction to complete. */
        if (mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
        {
            /* Lengths that are given in octets: */
            transaction_length = mac_message->pd_data.psduLength +
                PHY_OVERHEAD;
            if (mac_message->pd_data.data[1] & FCF_ACK_REQUEST)
            {
                /* Ensure there is room for the ACK. */
                transaction_length += ACK_FRAME_LEN + PHY_OVERHEAD;
            }
            /* Convert to symbols. */
            transaction_length *= SYMBOLS_PER_OCTET;
            /* Add lengths that are given in symbols. */
            if (mac_message->pd_data.data[1] & FCF_ACK_REQUEST)
            {
                /* Space needed until ACK is sent. */
                transaction_length += aUnitBackoffPeriod;
            }
            /* Compute space needed for IFS, and add it. */
            if (mac_message->pd_data.psduLength <= aMaxSIFSFrameSize)
            {
                transaction_length += aMinSIFSPeriod;
            }
            else
            {
                transaction_length += aMinLIFSPeriod;
            }
        }

        // Do the initialization of the retry counter only when this function is initially called
        if (init_nr)
        {
            /* do honour retry mechanism for direct frames */
            NR = 0;
        }
        else
        {
            /* do not honour retry mechanism for indirect frames, do only send once */
            NR = NO_FRAME_RETRIES;
        }
    }
    CW = 2;
    BE = mac_pib_macMinBE;
    if (mac_pib_macBattLifeExt && (BE > 2))
    {
        BE = 2;
    }

    if (mac_phy_autocsmaca)
    {
        uint8_t         psr_buffer[sizeof(plme_set_req_t) + sizeof(uint8_t)];
        plme_set_req_t  *psr = (plme_set_req_t *)psr_buffer;
        plme_set_conf_t psc;

        /*
         * If our PHY can perform automatic CSMA-CA, go ahead, and
         * fire off a PD-DATA.request right away.
         */
        // Set up the CSMA-CA parameters in the PHY first.
        psr->size = sizeof(*psr) - sizeof(psr->size) + sizeof(uint8_t);
        psr->PIBAttribute = phyMaxFrameRetries;
        psr->data[0] = sizeof(uint8_t);
        psr->data[1] = init_nr? aMaxFrameRetries: 0;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);

        psr->PIBAttribute = phyMinBE;
        psr->data[1] = BE;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);

        psr->PIBAttribute = phyMaxCSMABackoffs;
        psr->data[1] = mac_pib_macMaxCSMABackoffs;
        ASSERT(psc.status == PHY_SUCCESS);

        pst.size = sizeof(pst) - sizeof(pst.size);
        pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        pst.state = PHY_TX_ON;
        bios_pushback_event((uint8_t *)&pst);
        mac_state = MAC_D;
    }
    else
    {
        backoff(true);
    }
}

/**
 * \brief perform backoff timer calculations
 *
 * \param do_rand random backoff is to be performed
 */
static void backoff(uint8_t do_rand)
{
    uint32_t symbols_elapsed_since_beacon;
    uint32_t tm;
    uint32_t next_backoff_periods;
    uint32_t next_backoff_symbols;
    uint32_t cap_period;
    uint32_t now_tm;
    uint32_t backoff_tm = (uint32_t)0;


    if (do_rand)
    {
        /*
         * macMinBE is 3, aMaxBE is 5, aUnitBackoffPeriod is 20.  With
         * 2**5 - 1, there are at most 31 * 20 = 620 symbols to wait.
         * This is too much for a fast timer.
         */
        backoff_tm = (unsigned)(rand() & ((1 << BE) - 1)) * aUnitBackoffPeriod;
    }

    // Do slotted CSMA-CA if: beaconing AND associated AND not sending an Association Request frame.
    if ((mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
        && (mac_pib_macShortAddress != BROADCAST)
        && (mac_message->msgtype != ASSOCIATIONREQUEST))
    {
        // Calculate the number of symbols in the CAP.
        if (!mac_i_pan_coordinator)
        {
            // Calculate mac_RollOverTime if a device.
            mac_RollOverTime = MAC_CALCULATE_SYMBOL_TIME_BEACONINTERVAL(mac_pib_macBeaconOrder);
        }

        // Number of symbols elapsed since beacon.
        now_tm = bios_gettime();
        while ((symbols_elapsed_since_beacon = bios_sub_time(now_tm, mac_pib_macBeaconTxTime)) >
               mac_RollOverTime)
        {
            // we have not heard the last beacon, fix it!
            mac_pib_macBeaconTxTime = bios_add_time(mac_pib_macBeaconTxTime, mac_RollOverTime);
        }

        // Add some fuzz factor to compensate for the following
        // calculations, plus the subsequent CCA.  The calculations
        // add up to some 200 us (about 12 symbols), and the CCA
        // period itself is another 12 symbols.
        symbols_elapsed_since_beacon = bios_add_time(symbols_elapsed_since_beacon, 24);

        // Calculate next backoff boundary (in backoff periods).
        next_backoff_periods = (symbols_elapsed_since_beacon / (uint32_t)aUnitBackoffPeriod) + 1;

        // Convert next backoff boundary to symbols.
        next_backoff_symbols = next_backoff_periods * (uint32_t)aUnitBackoffPeriod;

        // Now add in the random backoffs to do.
        tm = bios_add_time(backoff_tm, next_backoff_symbols);

        // aNumSuperframeSlots == 16
        cap_period = (mac_SOInactiveTime / aNumSuperframeSlots) * (mac_FinalCapSlot + 1);

        {
            // Check if we need to span superframes.
            if (bios_add_time(transaction_length, tm) > bios_add_time(cap_period, mac_pib_macBeaconTxTime))
            {
                /*
                 * The target is to have the timer go off sometime shortly
                 * after the next beacon was transmitted.
                 */
                tm = bios_add_time(mac_pib_macBeaconTxTime, aMinLIFSPeriod);
                tm = bios_add_time(tm, mac_RollOverTime);
                tm = bios_add_time(tm, aMaxPHYPacketSize * SYMBOLS_PER_OCTET);
                while (!bios_start_absolute_timer(T_backoff, tm))
                {
                    // we could not start a timer, because it would not trigger on the next slot boundery
                    // therefore take the next slot
                    tm = bios_add_time(tm, aUnitBackoffPeriod);
                }
                return;
            }
        }

        // Start timer.
        while (!bios_start_absolute_timer(T_backoff, bios_add_time(tm, mac_pib_macBeaconTxTime)))
        {
            // A timer could not be started, because it would not
            // trigger on the computed slot boundary.  Therefore take
            // the next slot.
            tm = bios_add_time(tm, aUnitBackoffPeriod);
        }
    }
    else
    {
        if (backoff_tm == 0)
        {
            //if timeout is zero -> trigger timer immediatelly
            mac_t_backoff();
        }
        else
        {
            if (!bios_starttimer(T_backoff, backoff_tm))
            {
                // Backoff timer could not be started, call immediate actions
                mac_t_backoff();
            }
        }
    }
}

/**
 * \brief T_AckWait timer callback
 *
 * Notify about the missed ack frame.
 */
void mac_t_ackwait(void)
{
    uint8_t psrbuf[sizeof(plme_set_req_t) + sizeof(uint8_t)];
    plme_set_req_t *psr = (plme_set_req_t *)psrbuf;
    plme_set_conf_t psc;

#if CSMA_CA_INTERCEPTION
    if (mac_beacon_flag)
    {
        mac_state = mac_pre_csmaca_state;
        return;
    }
#endif  // CSMA_CA_INTERCEPTION

    if (mac_state == MAC_F)
    {
        /*
         * When running on a PHY that performs automatic ACKs, turn them
         * on again here as we saw our ACK frame, and can continue in
         * fully automatic mode.
         */
        if (mac_phy_autoacks)
        {
            psr->PIBAttribute = phyAutoACK;
            psr->data[1] = true;
            plme_set_request_internal(psr, &psc);
            ASSERT(psc.status == PHY_SUCCESS);
        }

        if (NR == NO_FRAME_RETRIES)
        {
            /* Indirect transmission, no retries. */
            // All indirect frames except NULL_FRAMES need to stay in the queue.
            if (mac_message->msgtype == NULL_FRAME)
            {
                mac_buffer_free(mac_message);
            }

            // release mac_message since the indirect frame is not retried, so the
            // pending transaction is finished if the ACK timer expires
            mac_message = NULL;
            mac_state = mac_pre_csmaca_state;
        }
        else
        {
            if (++NR > aMaxFrameRetries)
            {
                select_response(MAC_NO_ACK);
            }
            else
            {
                /* Restart CSMA-CA */
                mac_state = MAC_B;
                mac_csma_ca(false, true);
            }
        }
    }
}


/**
 * \brief Handle Channel Access Failure
 *
 * Perform appropriate action in case of Channel Access Failure for direct and indirect frames
 */
static void channel_access_failure(void)
{
    /* indirect frame */
    if (NR == NO_FRAME_RETRIES)
    {
        /* Indirect transmission, no retries. */
        // All indirect frames except NULL_FRAMES need to stay in the queue.
        if (mac_message->msgtype == NULL_FRAME)
        {
            mac_buffer_free(mac_message);
        }
        // release mac_message since the indirect frame is not retried, so the
        // pending transaction is finished if the ACK timer expires
        mac_message = NULL;
        mac_state = mac_pre_csmaca_state;
    }
    else
    {
        /* direct frame */
        select_response(MAC_CHANNEL_ACCESS_FAILURE);
    }
}

/**
 * \brief select a response based on the type of the pending message
 *
 * This implements the SDL's select_response procedure, except statM
 * is not a global but a parameter, and also the response is queued up
 * within the procedure.
 *
 * Changes MAC state back to what it has been before starting CSMA-CA.
 *
 * \param statM the MAC response code
 */
static void select_response(uint8_t statM)
{
    /*
     * Union u is used to reduce the stack space consumption, as only
     * one of these messages is needed at a time, depending on the
     * mac_message we are responding to.
     */
    union
    {
        mlme_associate_conf_t masc;
        mlme_disassociate_conf_t mdc;
        mlme_poll_conf_t mpc;
        mcps_data_conf_t mcps;
    } u;

    switch (mac_message->msgtype)
    {
    case ASSOCIATIONREQUEST:
        u.masc.size = sizeof(u.masc) - sizeof(u.masc.size);
        u.masc.cmdcode = MLME_ASSOCIATE_CONFIRM;
        u.masc.status = statM;
        /*
         * This short address will only be used if the association
         * attempt was unsuccessful.  7.1.3.4.1 mandates it to be
         * 0xffff in that case.  On a successful association, the
         * actual value will be filled in based on the response to the
         * data request obtained from the coordinator.
         */
        u.masc.AssocShortAddress = BROADCAST;
        bios_pushback_event((uint8_t *)&u.masc);
        break;

    case ORPHANREALIGNMENT:
        /* coord realignment was sent out as result of an orphan scan */
    case ASSOCIATIONRESPONSE:
        mac_mlme_comm_status(FCF_LONG_ADDR, &mac_ieee_address, FCF_LONG_ADDR,
                             (uint64_t *)&mac_message->placeholder[ASSOC_RESP_DSTADDR_OFFSET],
                             statM);
        break;

    case DISASSOCIATIONNOTIFICATION:
        u.mdc.size = sizeof(u.mdc) - sizeof(u.mdc.size);
        u.mdc.cmdcode = MLME_DISASSOCIATE_CONFIRM;
        u.mdc.status = statM;
        bios_pushback_event((uint8_t *)&u.mdc);
        break;

    case DATAREQUEST:
        u.mpc.size = sizeof(u.mpc) - sizeof(u.mpc.size);
        u.mpc.cmdcode = MLME_POLL_CONFIRM;
        u.mpc.status = statM;
        bios_pushback_event((uint8_t *)&u.mpc);
        break;

    case MCPS_MESSAGE:
        u.mcps.size = sizeof(u.mcps) - sizeof(u.mcps.size);
        u.mcps.cmdcode = MCPS_DATA_CONFIRM;
        u.mcps.status = statM;
        u.mcps.msduHandle = mac_message->msduHandle;
        bios_pushback_event((uint8_t *)&u.mcps);
        break;

    case DATAREQUEST_IMPL_POLL:
    case NULL_FRAME:
    case BEACON_MESSAGE:
        /* Nothing to do here. */
        break;

    case COORDINATORREALIGNMENT:
        /* coord realignment was sent out, now switch to the right channel */
        {
            uint8_t         psr_buffer[sizeof(plme_set_req_t) + sizeof(uint8_t)];
            plme_set_req_t  *psr = (plme_set_req_t *)psr_buffer;
            plme_set_conf_t psc;

            psr->size         = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint8_t);
            psr->cmdcode      = PLME_SET_REQUEST;
            psr->PIBAttribute = phyCurrentChannel;
            psr->data[0]      = sizeof(uint8_t);
            psr->data[1]      = mac_current_channel;

            (void)plme_set_request_internal(psr, &psc);
        }
        break;

    default:
        ASSERT("Unexpected mac_message->msgtype in select_response()" == 0);
        break;
    }
    mac_state = mac_pre_csmaca_state;
    mac_buffer_free(mac_message);
    mac_message = NULL;
}


#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
