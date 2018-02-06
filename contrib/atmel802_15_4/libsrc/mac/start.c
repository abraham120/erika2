/**
 * @file
 * This file implements the MLME-START.request (MAC layer management entity)
 * entry points.
 *
 * $Id: start.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include "phy.h"

#if APP_TYPE >= APP_L2

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)

/* === Globals ============================================================= */

static mlme_start_req_t start_parms;  // Intermediate start parameters.

/* === Prototypes ========================================================== */

static bool check_start_parameter(mlme_start_req_t  *msg);

/* === Implementation ====================================================== */

/**
 * @brief This function checks the parameters of a mlme_start_req.
 *
 * @param   msg The mlme_start_req message.
 * @return  True if parameters are ok, otherwise false.
 */
bool check_start_parameter(mlme_start_req_t  *msg)
{
    bool back = false;

    /* check valid range for BO and SO */
    if ((msg->BeaconOrder <= NON_BEACON_NETWORK) &&
        ((msg->SuperframeOrder <= msg->BeaconOrder) ||
         (msg->SuperframeOrder == NON_BEACON_NETWORK)))
    {
        if (msg->CoordRealignment && mac_i_pan_coordinator)
        {
            back = true;
        }
        else if (((mac_state == MAC_Ya) && (msg->PANCoordinator)) ||
                 ((mac_state == MAC_A) && (!msg->PANCoordinator)))
        {
            back = true;
        }
    }

    return back;
}

/**
 * @brief The MLME-START.request primitive makes a request for the device to
 * start using a new superframe configuration.
 *
 * 802.15.4. Section 7.1.14.1.

   If the MLME-START.request primitive is received when macShortAddress is set
   to 0xffff, the MLME will issue the MLME-START.confirm primitive with a
   status of NO_SHORT_ADDRESS.

   On receipt of the MLME-START.request primitive,
   the MLME sets macBeaconOrder to the value of the BeaconOrder parameter. If
   macBeaconOrder is equal to 15, the MLME will also set macSuperframeOrder to
   15. In this case, this primitive configures a beaconless PAN. If
   macBeaconOrder is less than 15, the MLME will set macSuperframeOrder to the
   value of the SuperframeOrder parameter.

   When the PANCoordinator parameter is
   set to TRUE, the MLME updates macPANId with the value of the PANId parameter
   and phyCurrentChannel with the value of the LogicalChannel parameter, by
   issuing the PLME-SET.request primitive. When the PANCoordinator parameter is
   set to FALSE, the MLME ignores the PANId and LogicalChannel parameters.

   If the CoordRealignment parameter is set to TRUE, the MLME generates and
   broadcasts a coordinator realignment command containing the new PANId and
   LogicalChannel parameters.

   When the device is already transmitting beacons,
   the new superframe configuration is put into operation at the next scheduled
   beacon. If the device is not already transmitting beacons, the new superframe
   configuration is put into operation immediately.

   The address used by the
   coordinator in its beacon frames is determined by the current value of
   macShort-Address, which is set by the next higher layer before issuing this
   primitive. Also the MLME sets macBatt-LifeExt to the value of the
   BatteryLifeExtension parameter.

   The SecurityEnable parameter specifies
   whether security is to be applied to all following beacon frames. If the
   SecurityEnable parameter is set to FALSE, the MAC sublayer will set the
   security enabled subfield of the frame control field to 0 (see 7.2.1.1.2) and
   not perform any security operations on the frame. If the SecurityEnable
   parameter is set to TRUE, the MAC sublayer will set the security enabled
   subfield of the frame control field to 1 and obtain the key and security
   information, corresponding to the broadcast address, from the ACL entries in
   the MAC PIB, as described in 7.5.8.4.1. If an appropriate key could not be
   found in the ACL, the MAC sublayer will discard the frame and issue the
   MLME-START.confirm primitive with a status of UNAVAILABLE_KEY. If an
   appropriate key was found in the ACL, the MAC sublayer will use it to apply
   security to the frame, according to the security information found in the ACL
   (see 7.5.8.4). If the length of the resulting frame is longer than
   aMaxMACFrameSize, the MLME will issue the MLMESTART. confirm primitive with a
   status of FRAME_TOO_LONG. If any other error occurs during the secure
   processing of the frame, the MAC sublayer will discard the frame and issue
   the MLME-START.confirm primitive with a status of FAILED_SECURITY_CHECK.

   To transmit any beacon frame, the MLME first enables the transmitter by issuing
   the PLME-SET-TRXSTATE. request primitive with a state of TX_ON to the PHY. On
   receipt of the PLME-SET-TRX-STATE.confirm primitive with a status of either
   SUCCESS or TX_ON, the beacon frame is then transmitted by issuing the
   PDDATA.request primitive. Finally, on receipt of the PD-DATA.confirm
   primitive and if the active portion of the superframe extends beyond the
   beacon frame transmission (see 7.5.1.1), the MLME of the coordinator will
   enable the receiver by issuing the PLME-SET-TRX-STATE.request primitive with
   a state of RX_ON to the PHY. If the active portion of the superframe ends
   after the beacon frame transmission, the receiver will not be enabled.

   On completion of this procedure, the MLME responds with the MLME-START.confirm
   primitive. If the attempt to start using a new superframe configuration was
   successful, the status parameter will be set to SUCCESS. If any parameter is
   not supported or is out of range, the status parameter will be set to
   INVALID_PARAMETER.

 * @param *m The MLME_START.request message
 */

void mlme_start_request(uint8_t *m)
{
    mlme_start_req_t  *msg = (mlme_start_req_t *)m;
    mlme_start_conf_t msc;
    uint8_t local_buf[sizeof(plme_set_req_t) + 1];
    plme_set_req_t    *psr = (plme_set_req_t *) local_buf;
    plme_set_conf_t   psc;

    uint8_t old_BO;

    // Copy start params into a global variable structure
    memcpy(&start_parms, msg, sizeof(start_parms));

    // Begin start command.
    if (mac_pib_macShortAddress == BROADCAST)
    {
        msc.size    = sizeof(mlme_start_conf_t) - sizeof(msc.size);
        msc.cmdcode = MLME_START_CONFIRM;
        msc.status  = MAC_NO_SHORT_ADDRESS;
        bios_pushback_event((uint8_t *) &msc);
        return;
    }

    if (check_start_parameter(msg))
    {
        old_BO = mac_pib_macBeaconOrder;
        mac_pib_macBeaconOrder = msg->BeaconOrder;
        mac_pib_macSuperframeOrder = msg->SuperframeOrder;

        // Calculate symbol times according to the new superframe configuration
        if (mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
        {
            mac_RollOverTime = MAC_CALCULATE_SYMBOL_TIME_BEACONINTERVAL(mac_pib_macBeaconOrder);
            mac_SOInactiveTime = MAC_CALCULATE_SYMBOL_TIME_SUPERFRAMEDURATION(mac_pib_macSuperframeOrder);
            mac_pib_macBattLifeExt = start_parms.BatteryLifeExtension;
        }
        else
        {
            /*
            * There are no beacons, but the T_beacon timer gets
            * started anyway, in order to perform maintenance on
            * expired transactions.  The original 802.15.4 standard
            * forgot to specify the time to apply in a non
            * beacon-enabled network.  According to the 802.15.4b
            * draft, the same timing is applied for that purpose as
            * it would for a beacon interval of 0.
            *
            * The code in mac_t_beacon() takes care to only ever send
            * out an actual beacon frame for beacon-enabled networks.
            */
            mac_RollOverTime = MAC_CALCULATE_SYMBOL_TIME_BEACONINTERVAL(0);
            mac_pib_macSuperframeOrder = mac_pib_macBeaconOrder;
        }

        if (msg->CoordRealignment)
        {
            /* return success, because this is all we can do here */
            msc.size    = sizeof(mlme_start_conf_t) - sizeof(msc.size);
            msc.cmdcode = MLME_START_CONFIRM;

            /* First inform our devices of the configuration change */
            if (mac_tx_coord_realignment_command(COORDINATORREALIGNMENT,
                                                 NULL,
                                                 msg->PANId,
                                                 msg->LogicalChannel))
            {
                /* Update the parameters of the existing PAN */
                mac_set_panid(msg->PANId);
                mac_current_channel = msg->LogicalChannel;

                /* 802.15.4 2006: If CSMA-CA fails for the Coordinator Realignment Command nothing should
                   be changed for the MAC */

                msc.status  = MAC_SUCCESS;

                if ((old_BO == NON_BEACON_NETWORK) && (mac_pib_macBeaconOrder  < NON_BEACON_NETWORK))
                {
                    mac_start_beacon_timer();
                }
            }
            else
            {
                msc.status  = MAC_INVALID_PARAMETER;
            }
            bios_pushback_event((uint8_t *) &msc);
        }
        else
        {
            // Start a new PAN either as Coordinator or Router
            mac_set_panid(msg->PANId);
            mac_i_pan_coordinator = msg->PANCoordinator != 0;
            mac_current_channel = msg->LogicalChannel;

            psr->size         = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint8_t);
            psr->cmdcode      = PLME_SET_REQUEST;
            psr->data[0]      = sizeof(uint8_t);

            if (mac_phy_autoacks)
            {
                psr->PIBAttribute = phyPANcoord;
                psr->data[1] = true;
                plme_set_request_internal(psr, &psc);
                ASSERT(psc.status == PHY_SUCCESS);
            }

            // If we are the PAN coordinator, tell the PHY to set the channel
            psr->PIBAttribute = phyCurrentChannel;
            psr->data[1]      = mac_current_channel;
            bios_pushback_event((uint8_t *)psr);
        }

    }
    else
    {
        msc.size    = sizeof(mlme_start_conf_t) - sizeof(msc.size);
        msc.cmdcode = MLME_START_CONFIRM;
        msc.status  = MAC_INVALID_PARAMETER;
        bios_pushback_event((uint8_t *) &msc);
    }
}

/**
 * @brief   Call back function from PHY after a channel switch
 *
 * This function will be called from PHY after a channel switch has
 * been requested during the start process. If the channel was set
 * properly, plme_set_conf will return PHY_SUCCESS.
 *
 * @param   *psd    The status of the PLME request to set a specific channel.
 */
void mac_start_request_set_phyCurrentChannel_conf(plme_set_conf_t *psd)
{
    plme_set_trx_state_req_t psx;
    mlme_start_conf_t msc;

    if (psd->status == PHY_SUCCESS)
    {
        // We must now put the radio into receive mode
        psx.size    = sizeof(plme_set_trx_state_req_t) - sizeof(psx.size);
        psx.cmdcode = PLME_SET_TRX_STATE_REQUEST;
        psx.state   = PHY_RX_ON;
        bios_pushback_event((uint8_t *)&psx);
        mac_state = MAC_Ya1;
    }
    else
    {
        msc.size    = sizeof(mlme_start_conf_t) - sizeof(msc.size);
        msc.cmdcode = MLME_START_CONFIRM;
        msc.status  = MAC_INVALID_PARAMETER;
        bios_pushback_event((uint8_t *)&msc);
        mac_state = MAC_Ya;
    }

}


/**
 * @brief   Start beacon timer
 *
 * Start beacon timer with appropriate parameters.  This is normally
 * called during MLME-START.request processing for beacon-enabled
 * networks, but can be called repeatedly in non beacon-enabled
 * networks while indirect buffers are pending, in order to ensure
 * indirect buffers will be properly expired.
 */
void mac_start_beacon_timer(void)
{
    uint32_t    temp_time = 0;
    bool        t_start_res = false;

    mac_pib_macBeaconTxTime = bios_gettime();

    while (!t_start_res)
    {
        temp_time = bios_add_time(mac_pib_macBeaconTxTime, mac_RollOverTime);
        t_start_res = bios_start_absolute_timer(T_beacon, temp_time);
    }

    // Should we be transmitting beacons ?
    if (mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
    {
        mac_build_beacon_frame(true);
    }
}


/**
 * @brief   Call back function from PHY after a state change into RX_ON
 *
 * This function will be called from PHY after a state change into RX_ON has
 * been requested during the start process. If the state chanke was successful,
 * plme_set_trx_state_conf will return PHY_SUCCESS.
 *
 * @param   *psd The Status of the Request to set the PHY into RX_ON state.
 */
void mac_start_request_set_rx_on_conf(plme_set_trx_state_conf_t *psd)
{
    mlme_start_conf_t msc;


    if ((psd->status == PHY_SUCCESS) || (psd->status == PHY_RX_ON))
    {
        msc.size    = sizeof(mlme_start_conf_t) - sizeof(msc.size);
        msc.cmdcode = MLME_START_CONFIRM;
        msc.status  = MAC_SUCCESS;
        bios_pushback_event((uint8_t *) &msc);
        mac_state = MAC_Za;

        mac_start_beacon_timer();
    }
    else
    {
        msc.size    = sizeof(mlme_start_conf_t) - sizeof(msc.size);
        msc.cmdcode = MLME_START_CONFIRM;
        msc.status  = MAC_INVALID_PARAMETER;
        bios_pushback_event((uint8_t *) &msc);
        mac_state = MAC_Ya;
    }

}


/**
 * @brief   Beacon Timer handler
 *
 *          Call back function once the Beacon timer has expired.
 *          This function both initiates transmission of the next Beacon frame
 *          and checks for frames with expired persistence timer.
 */
void mac_t_beacon(void)
{
    if (mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
    {
        /* If CSMA-CA has already been started it needs to be intercepted */
        if ((mac_state >= MAC_B) && (mac_state <= MAC_F) )
        {
            plme_set_trx_state_conf_t   psc;
            plme_set_trx_state_req_t    psr;

            // Turn the radio to PHY_TRX_OFF.
            psr.size    = sizeof(plme_set_trx_state_req_t) - sizeof(psr.size);
            psr.cmdcode = PLME_SET_TRX_STATE_REQUEST;
            psr.state   = PHY_FORCE_TRX_OFF;
            do
            {
                plme_set_trx_state_request_internal(&psr, &psc);
            } while (psc.status != PHY_SUCCESS);

            /* We do not care for any pending ACKs once we have to Tx Beacon */
            mac_ack_flag = false;

            mac_state = mac_pre_csmaca_state;

            if (mac_message->usage == BUFFER_DIRECT)
            {
                // Direct frames need to be removed from the direct buffer list
                mac_buffer_free(mac_message);
            }
            mac_message = NULL;
        }
    }

    switch (mac_state)
    {
        case MAC_ED:
        case MAC_X_as:
        case MAC_X_as1:
        case MAC_X_ps:
        case MAC_X_os:
        case MAC_X_os1:
            break;
        default:
            if (mac_pib_macBeaconOrder < NON_BEACON_NETWORK)
            {
                mac_build_beacon_frame(true);
            }
            break;
    }

    /*
     * Watch out for frames that already expired.  Remember that we
     * can turn off beacon timers next time iff we are in non
     * beacon-enabled mode, and there are no more indirect
     * transmissions pending.
     */
    mac_run_beacon_timer = mac_buffer_decrement_persistence() ||
        mac_pib_macBeaconOrder < NON_BEACON_NETWORK;

    if (mac_run_beacon_timer)
    {
        bool t_start_res = false;
        uint32_t temp_time = bios_add_time(mac_pib_macBeaconTxTime, mac_RollOverTime);

        while (!t_start_res)
        {
            temp_time = bios_add_time(temp_time, mac_RollOverTime);
            t_start_res = bios_start_absolute_timer(T_beacon, temp_time);
        }
        // Update the PIB attribute.
        mac_pib_macBeaconTxTime = bios_sub_time(temp_time, mac_RollOverTime);

        /* Start Superframe timer here (only for coordinator or router) */
        if ((mac_pib_macBeaconOrder < NON_BEACON_NETWORK) &&
            (mac_pib_macSuperframeOrder < mac_pib_macBeaconOrder))
        {
            bios_starttimer(T_superframe, mac_SOInactiveTime);
        }
    }
}

/**
 * @brief   Superframe Timer handler
 *
 *          Call back function once the Superframe timer has expired.
 *          This function is called once the inactive portion of a superframe
 *          shall be entered.
 */
void mac_t_so_inactive(void)
{
    plme_set_trx_state_req_t psx;

    psx.size    = sizeof(plme_set_trx_state_req_t) - sizeof(psx.size);
    psx.cmdcode = PLME_SET_TRX_STATE_REQUEST;
    psx.state   = PHY_TRX_OFF;
    bios_pushback_event((uint8_t *)&psx);
}

#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

#endif /* APP_TYPE >= APP_L2 */

/* EOF */
