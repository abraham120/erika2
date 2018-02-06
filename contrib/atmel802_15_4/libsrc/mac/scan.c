/**
 * \file
 * This file implements the MLME_SCAN primitives.
 *
 * \brief
 * This file implements functions to handle all MLME-SCAN primitives and the
 * corresponding scan algorithm. This includes ED, Active, Passive and Orphan
 * scan. All required timers and frames (beacon request and orphan
 * notification frames) are assembled and their transmission is initiated.
 *
 * $Id: scan.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

static void scan_proceed(uint8_t scan_type);

/* === Implementation ====================================================== */

/**
 * \brief proceed with a scan request
 *
 * Increment the current channel.  See if it belongs to the list of
 * channels to scan.  If so, start scanning.  If all channels done,
 * send out the MLME_SCAN.confirm message.
 *
 * \param scan_type The type of the scan operation to proceed with
 */
void scan_proceed(uint8_t scan_type)
{
    mlme_scan_conf_t *msc = (mlme_scan_conf_t *)mac_buffer;
    plme_set_trx_state_req_t pst;
    uint8_t psr_buf[sizeof(plme_set_req_t) + 1];
    plme_set_req_t *psr = (plme_set_req_t *)psr_buf;

    /* Loop over all channels the MAC has been requested to scan */
    for (; mac_current_channel <= MAX_CHANNEL; mac_current_channel++)
    {
        if ((scan_type == MLME_SCAN_TYPE_PASSIVE)
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
            || (scan_type == MLME_SCAN_TYPE_ACTIVE)
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */
            )
        {
            /*
             * For active (FFDs only) or passive scans, bail out if we
             * reached our maximum number of PANDescriptors that could
             * be stored.  That way, the upper layer will get the
             * correct set of unscanned channels returned, so it can
             * continue scanning if desired.
             */
            if (msc->ResultListSize >= MAX_PANDESCRIPTORS)
            {
                break;
            }
        }
        else if (scan_type == MLME_SCAN_TYPE_ORPHAN)
        {
            /*
             * In an orphan scan, terminate if any coordinator
             * realignment packet has been received.
             */
            if (msc->ResultListSize != 0)
            {
                break;
            }
        }

        if ((msc->UnscannedChannels & (1UL << mac_current_channel)) != 0)
        {
            psr->size         = sizeof(plme_set_req_t) - sizeof(psr->size) + 1;
            psr->cmdcode      = PLME_SET_REQUEST;
            psr->PIBAttribute = phyCurrentChannel;
            psr->data[0]      = 1;
            psr->data[1]      = mac_current_channel;
            bios_pushback_event((uint8_t *)psr);
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
            if (scan_type == MLME_SCAN_TYPE_ACTIVE)
            {
                mac_state = MAC_X_as;
            }
            else
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */
            if (scan_type == MLME_SCAN_TYPE_PASSIVE)
            {
                mac_state = MAC_X_ps;
            }
            else if (scan_type == MLME_SCAN_TYPE_ORPHAN)
            {
                mac_state = MAC_X_os;
            }
            return;
        }
    }
    /* All channels were scanned. The confirm needs to be prepared */
    pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
    pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
    pst.state   = PHY_TRX_OFF;
    bios_pushback_event((uint8_t *)&pst);

    switch (scan_type)
    {
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case MLME_SCAN_TYPE_ED:
        msc->status = MAC_SUCCESS;
        /* Convert number of ED levels to size of octet string. */
        msc->data[0] = msc->ResultListSize;
        bios_pushback_event((uint8_t *)msc);

        // go into idle mode and reset Variables
        mac_idle_trans();
        mac_current_channel = mac_original_channel;
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
    case MLME_SCAN_TYPE_ACTIVE:
        mac_state = MAC_X_as2;
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */

    case MLME_SCAN_TYPE_ORPHAN:
        if (msc->ResultListSize > 0)
        {
            msc->status = MAC_SUCCESS;
        }
        else
        {
            msc->status = MAC_NO_BEACON;
        }
        /* Orphan scan does not return any list. */
        msc->ResultListSize = 0;

        bios_pushback_event((uint8_t *)msc);

        mac_state = mac_original_state;
        mac_current_channel = mac_original_channel;
        break;

    case MLME_SCAN_TYPE_PASSIVE:
        if (msc->ResultListSize > 0)
        {
            /* Convert number of PAN descriptors to size of octet string. */
            msc->data[0] = msc->ResultListSize * sizeof(wpan_pandescriptor_t);
            msc->size += msc->data[0];
            msc->status = MAC_SUCCESS;
        }
        else
        {
            msc->status = MAC_NO_BEACON;
        }

        /* Restore macPANId after passive scan completed. */
        mac_set_panid(mac_saved_panid);
        bios_pushback_event((uint8_t *)msc);

        mac_state = mac_original_state == MAC_W? MAC_Zp: mac_original_state;
        mac_current_channel = mac_original_channel;
        break;
    }
}

/**
 * \brief Send a beacon request or orphan notification command frame
 *
 * Construct an MPDU containing either a beacon request or an orphan notification
 * command and send it
 *
 * \param beacon_req True if a beacon request command frame shall be sent,
 *        otherwise (false) an orphan notification command frame will be sent.
 * \return True is the frame transmission has been initiated, or false if not
 */
bool send_scan_cmd(bool beacon_req)
{
    uint8_t         i;
    uint16_t        fcf;
    frame_buffer_t *fbuf;

    if ((fbuf = mac_buffer_request()) == NULL)
    {
        return false;
    }

    i = 1;

    /* begin MHR */
    /* FCF */
    if (beacon_req)
    {
        fcf = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_MAC_CMD) |
            FCF_SET_DEST_ADDR_MODE(FCF_SHORT_ADDR) |
            FCF_SET_SOURCE_ADDR_MODE(FCF_NO_ADDR);
    }
    else
    {
        fcf = FCF_SET_FRAMETYPE(FCF_FRAMETYPE_MAC_CMD) |
            FCF_SET_DEST_ADDR_MODE(FCF_SHORT_ADDR) |
            FCF_SET_SOURCE_ADDR_MODE(FCF_LONG_ADDR);
    }

    fbuf->pd_data.data[i++] = fcf & 0xff;
    fbuf->pd_data.data[i++] = (fcf >> 8) & 0xff;

    /* sequence number */
    fbuf->pd_data.data[i++] = mac_pib_macDSN;

    /* dst PANid */
    fbuf->pd_data.data[i++] = BROADCAST & 0xff;
    fbuf->pd_data.data[i++] = (BROADCAST >> 8) & 0xff;

    /* dst address */
    fbuf->pd_data.data[i++] = BROADCAST & 0xff;
    fbuf->pd_data.data[i++] = (BROADCAST >> 8) & 0xff;

    if (!beacon_req)
    {
        // Orphan notification contains more
        /* src PANid */
        fbuf->pd_data.data[i++] = BROADCAST & 0xff;
        fbuf->pd_data.data[i++] = (BROADCAST >> 8) & 0xff;

        /* src address */
        memcpy(&fbuf->pd_data.data[i], &mac_ieee_address, sizeof(uint64_t));
        i += sizeof(uint64_t);
    }
    /* end MHR */

    /* begin MAC payload */
    /* command frame identifier */
    if (beacon_req)
    {
        fbuf->pd_data.data[i++] = fbuf->msgtype = BEACONREQUEST;
    }
    else
    {
        fbuf->pd_data.data[i++] = fbuf->msgtype = ORPHANNOTIFICATION;
    }
    /* end MAC payload */

    /* begin MFR */
    i += CRC_SIZE - sizeof(fbuf->pd_data.size);
    fbuf->pd_data.data[0] = fbuf->pd_data.psduLength = i;
    /* end MFR */

    fbuf->pd_data.size = sizeof(pd_data_req_t) - sizeof(fbuf->pd_data.size) + i;
    fbuf->pd_data.cmdcode = PD_DATA_REQUEST;
    bios_pushback_event((uint8_t *)&fbuf->pd_data);

    mac_buffer_free(fbuf);

    return true;
}


/**
 * \brief Handles confirm after setting of TRX state during scan
 *
 * After a TRX state change has been requested to the PHY the corresponding
 * confirm is evaluated and scannning continues accordingly.
 *
 * \param *psd The Status of the Request to set the PHY state.
 */
void mac_scan_set_trx_state_conf(plme_set_trx_state_conf_t *psd)
{
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
    mlme_scan_conf_t *msc = (mlme_scan_conf_t *)mac_buffer;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    plme_ed_req_t per;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
    uint32_t tmr;

    switch (mac_state)
    {
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
        case MAC_ED:
            if ((psd->status == PHY_RX_ON) || (psd->status == PHY_SUCCESS))
            {
                per.size    = sizeof(plme_ed_req_t) - sizeof(per.size);
                per.cmdcode = PLME_ED_REQUEST;
                bios_pushback_event((uint8_t *)&per);

                tmr = MAC_CALCULATE_SYMBOL_TIME_SCANDURATION(mac_scan_duration);
                if (!bios_starttimer(T_scan_duration, tmr))
                {
                    // scan duration timer could not be started so we call the function directly
                    // this will basically shorten scanning without having really scanned
                    mac_t_scan_duration();
                }
            }
            else
            {
                /* Did not work, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ED);
            }
            break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
        case MAC_X_as:
            if ((psd->status == PHY_TX_ON) || (psd->status == PHY_SUCCESS))
            {
                // send an beacon request command
                if(!send_scan_cmd(true))
                {
                    // beacon request could not be transmitted since there is no buffer available
                    // stop scanning
                    // we call the function usually called by the scan duration timer
                    // to pretend scanning has finished
                    mac_t_scan_duration();
                }
            }
            else
            {
                /* Did not work, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ACTIVE);
            }
            break;

        case MAC_X_as1:
            if ((psd->status == PHY_RX_ON) || (psd->status == PHY_SUCCESS))
            {
                tmr = MAC_CALCULATE_SYMBOL_TIME_SCANDURATION(mac_scan_duration);
                /* Wait for any response. */
                mac_state = MAC_X_as;
                if (!bios_starttimer(T_scan_duration, tmr))
                {
                    // scan duration timer could not be started so we call the function directly
                    // this will basically shorten scanning without having really scanned
                    mac_t_scan_duration();
                }
            }
            else
            {
                /* Did not work, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ACTIVE);
            }
            break;

        case MAC_X_as2:
            /* we are done with scanning */
            mac_current_channel = mac_original_channel;
            mac_state = mac_original_state == MAC_W? MAC_Ya: mac_original_state;
            if (msc->ResultListSize > 0)
            {
                /* Convert number of PAN descriptors to size of octet string. */
                msc->data[0] = msc->ResultListSize * sizeof(wpan_pandescriptor_t);
                msc->size += msc->data[0];
                msc->status = MAC_SUCCESS;
            }
            else
            {
                msc->status = MAC_NO_BEACON;
            }
            mac_set_panid(mac_saved_panid);
            bios_pushback_event((uint8_t *)msc);
            break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */

        case MAC_X_ps:
            if ((psd->status == PHY_RX_ON) || (psd->status == PHY_SUCCESS))
            {
                tmr = MAC_CALCULATE_SYMBOL_TIME_SCANDURATION(mac_scan_duration);
                if (!bios_starttimer(T_scan_duration, tmr))
                {
                    // scan duration timer could not be started so we call the function directly
                    // this will basically shorten scanning without having really scanned
                    mac_t_scan_duration();
                }
            }
            else
            {
                /* Did not work, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_PASSIVE);
            }
            break;

        case MAC_X_os:
            if ((psd->status == PHY_TX_ON) || (psd->status == PHY_SUCCESS))
            {
                // send an orphan notification command
                if (!send_scan_cmd(false))
                {
                    // beacon request could not be transmitted since there is no buffer available
                    // stop scanning
                    // we call the function usually called by the scan duration timer
                    // to pretend scanning has finished
                    mac_t_scan_duration();
                }
            }
            else
            {
                /* Did not work, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ORPHAN);
            }
            break;

         case MAC_X_os1:
            if ((psd->status == PHY_RX_ON) || (psd->status == PHY_SUCCESS))
            {
                /* Wait for any response. */
                mac_state = MAC_X_os;
                if (!bios_starttimer(T_scan_duration, aResponseWaitTime))
                {
                    // scan duration timer could not be started so we call the function directly
                    // this will basically shorten scanning without having really scanned
                    mac_t_scan_duration();
                }
            }
            else
            {
                /* Did not work, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ORPHAN);
            }
            break;

        default:
            ASSERT("mac_scan_set_trx_state_conf in unexpected MAC state." == 0);
            break;
    }
}


/**
 * \brief Handles confirm after setting of PIB attributes during scan
 *
 * After a PIB attribute change has been requested to the PHY the corresponding
 * confirm is evaluated and scannning continues accordingly.
 *
 * \param *psd The Status of the Request to change a PIB attribute.
 */
void mac_scan_set_conf(plme_set_conf_t *psd)
{
    plme_set_trx_state_req_t pst;

    switch (mac_state)
    {

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
        case MAC_ED:
            if (psd->PIBAttribute != phyCurrentChannel)
            {
                /* 'unexpected result, but possible' */
                break;
            }
            if (psd->status == PHY_SUCCESS)
            {
                pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
                pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
                pst.state   = PHY_RX_ON;
                bios_pushback_event((uint8_t *)&pst);
            }
            else
            {
                /* Channel not supported, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ED);
            }
            break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
        case MAC_X_as:
            if (psd->PIBAttribute != phyCurrentChannel)
            {
                /* 'unexpected result, but possible' */
                break;
            }
            if (psd->status == PHY_SUCCESS)
            {
                pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
                pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
                pst.state   = PHY_TX_ON;
                bios_pushback_event((uint8_t *)&pst);
            }
            else
            {
                /* Channel not supported, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ACTIVE);
            }
            break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */

        case MAC_X_ps:
            if (psd->PIBAttribute != phyCurrentChannel)
            {
                /* 'unexpected result, but possible' */
                break;
            }
            if (psd->status == PHY_SUCCESS)
            {
                pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
                pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
                pst.state   = PHY_RX_ON;
                bios_pushback_event((uint8_t *)&pst);
            }
            else
            {
                /* Channel not supported, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_PASSIVE);
            }
            break;

        case MAC_X_os:
            if (psd->PIBAttribute != phyCurrentChannel)
            {
                /* 'unexpected result, but possible' */
                break;
            }
            if (psd->status == PHY_SUCCESS)
            {
                pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
                pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
                pst.state   = PHY_TX_ON;
                bios_pushback_event((uint8_t *)&pst);
            }
            else
            {
                /* Channel not supported, continue. */
                mac_current_channel++;
                scan_proceed(MLME_SCAN_TYPE_ORPHAN);
            }
            break;

        default:
            ASSERT("mac_scan_set_conf in unexpected MAC state." == 0);
            break;
    }
}


/**
 * \brief Handles PD_DATA.confirm after the request to transmit a frame during scan
 *
 * After the transmission of a beacon request or orphan notification frame has
 * been requested, the corresponding PD-DATA.confirm is evaluated and scannning
 * continues accordingly.
 */
void mac_scan_pd_data_conf(void)
{
    plme_set_trx_state_req_t    pst;

    switch (mac_state)
    {

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
        case MAC_X_as:
            mac_pib_macDSN++;
            pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
            pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
            pst.state   = PHY_RX_ON;
            bios_pushback_event((uint8_t *)&pst);
            mac_state = MAC_X_as1;
            break;
        case MAC_X_as1:
            /* ignore this, because T_scan_duration triggered and we had to */
            /* proceed with scanning */
            break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */

        case MAC_X_os:
            mac_pib_macDSN++;
            pst.size    = sizeof(plme_set_trx_state_req_t) - sizeof(pst.size);
            pst.cmdcode = PLME_SET_TRX_STATE_REQUEST;
            pst.state   = PHY_RX_ON;
            bios_pushback_event((uint8_t *)&pst);
            mac_state = MAC_X_os1;
            break;

        default:
            ASSERT("mac_scan_set_conf in unexpected MAC state." == 0);
            break;
    }
}


#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
/**
 * \brief process a PLME_ED.confirm message
 *
 * \param m PLME_ED.confirm message
 */

void mac_proc_plme_ed_confirm(uint8_t *m)
{
    plme_ed_conf_t *pec = (plme_ed_conf_t *)m;
    mlme_scan_conf_t *msc = (mlme_scan_conf_t *)mac_buffer;
    uint8_t n_eds, enerlev;
    plme_ed_req_t per;

    switch (mac_state)
    {
        case MAC_ED:
            if (pec->status == PHY_SUCCESS)
            {
                /* ED measurements are done continuously on channel
                   until scan timer expires;
                   Accumulate max. measurement on this channel */
                n_eds = msc->ResultListSize + 1;
                enerlev = msc->data[n_eds];
                if (pec->EnergyLevel > enerlev)
                    msc->data[n_eds] = pec->EnergyLevel;
            }
            per.size    = sizeof(plme_ed_req_t) - sizeof(per.size);
            per.cmdcode = PLME_ED_REQUEST;
            bios_pushback_event((uint8_t *)&per);
            break;

        default:
            /* result to be ignored */
            break;
    }
}
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */


/**
 * \brief MAC scan timer callback
 */
void mac_t_scan_duration(void)
{
    mlme_scan_conf_t *msc = (mlme_scan_conf_t *)mac_buffer;
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    uint8_t n_eds;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

    switch (mac_state)
    {
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    case MAC_ED:
        n_eds = msc->ResultListSize;
        n_eds++;
        msc->ResultListSize = n_eds;
        msc->size++;
        msc->data[n_eds + 1] = 0;
        msc->UnscannedChannels &= ~(1UL << mac_current_channel);
        scan_proceed(MLME_SCAN_TYPE_ED);
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
    case MAC_X_as:
        msc->UnscannedChannels &= ~(1UL << mac_current_channel);
        scan_proceed(MLME_SCAN_TYPE_ACTIVE);
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */

    case MAC_X_ps:
        msc->UnscannedChannels &= ~(1UL << mac_current_channel);
        scan_proceed(MLME_SCAN_TYPE_PASSIVE);
        break;

    case MAC_X_os:
        msc->UnscannedChannels &= ~(1UL << mac_current_channel);
        scan_proceed(MLME_SCAN_TYPE_ORPHAN);
        break;

    default:
        /* These MAC states are not supposed to happen here. */
        ASSERT("Scan duration timer expired in unexpected MAC state." == 0);
        break;
    }
}


/**
 * @brief The MLME-SCAN.request primitive makes a request for a nore to
 * start a scan procedure.
 *
 * 802.15.4. Section 7.1.11.1.

   The MLME-SCAN.request primitive is used to initiate a channel scan over a
   given list of channels. A device can use a channel scan to measure the energy
   on the channel, search for the coordinator with which it associated, or
   search for all coordinators transmitting beacon frames within the POS of the
   scanning device.

   The MLME-SCAN.request primitive is generated by the next higher layer and
   issued to its MLME to initiate a channel scan to search for activity within
   the POS of the device. This primitive can be used to perform an ED scan to
   determine channel usage, an active or passive scan to locate beacon frames
   containing any PAN identifier, or an orphan scan to locate a PAN to which
   the device is currently associated.

   ED or active scans can be performed before an FFD starts operation as a
   PAN coordinator. Active or passive scans can be performed prior to selecting
   a PAN for association. Orphan scans can be performed to attempt to locate a
   specific coordinator with which communication has been lost.

   All devices shall be capable of performing passive scans and orphan scans;
   ED scans and active scans are optional for an RFD.

   When the MLME receives the MLME-SCAN.request primitive, it initiates a scan
   in all channels specified in the ScanChannels parameter. The MLME suspends
   all beacon transmissions for the duration of the scan. During a scan, the
   MAC sublayer only accepts frames received over the PHY data service that are
   relevant to the scan being performed (see 7.5.2.1).

   An ED scan allows a device to obtain a measure of the peak energy in each
   requested channel. The ED scan is performed on each channel by the MLME’s
   repeatedly issuing the PLME-ED.request primitive to the PHY until
   [aBaseSuperframeDuration * (2n + 1)] symbols, where n is the value of the
   ScanDuration parameter, have elapsed. The MLME notes the maximum energy
   measurement and moves on to the next channel in the channel list. A device
   will be able to store between one and an implementation-specified maximum
   number of channel ED measurements. The ED scan terminates when the number
   of channel ED measurements stored equals this implementation-specified
   maximum or when every channel specified in the channel list has been scanned.

   An active scan is used by an FFD to locate all coordinators transmitting
   beacon frames within its POS. The active scan is performed on each channel
   by the MLME’s first sending a beacon request command (see 7.3.2.4). The MLME
   then enables the receiver and records the information contained in each
   received beacon in a PAN descriptor structure (see Table 41 in 7.1.5.1.1).
   A device will be able to store between one and an implementation-specified
   maximum number of PAN descriptors. The active scan on a particular channel
   terminates when the number of PAN descriptors stored equals this
   implementation-specified maximum or when [aBaseSuperframeDuration * (2n + 1)]
   symbols, where n is the value of the ScanDuration parameter, have elapsed.
   If the latter condition has been satisfied, the channel is considered to
   have been scanned. Where possible, the scan is repeated on each channel and
   terminates when the number of PAN descriptors stored equals the
   implementation-specified maximum or when every channel in the set of
   available channels has been scanned.

   A passive scan, like an active scan, is used to locate all coordinators
   transmitting beacon frames within the POS of the scanning device; the
   difference is that the passive scan is a receive-only operation and does not
   transmit the beacon request command. The passive scan is performed on each
   channel by the MLME’s enabling its receiver and recording the information
   contained in each received beacon in a PAN descriptor structure
   (see Table 41 in 7.1.5.1.1). A device will be able to store between one and
   an implementation-specified maximum number of PAN descriptors. The passive
   scan on a particular channel terminates when the number of PAN descriptors
   stored equals this implementation-specified maximum or when
   [aBaseSuperframeDuration * (2n + 1)] symbols, where n is the value of the
   ScanDuration parameter, have elapsed. If the latter condition has been
   satisfied, the channel is considered to have been scanned. Where possible,
   the scan is repeated on each channel and terminates when the number of PAN
   descriptors stored equals the implementation-specified maximum or when
   every channel in the set of available channels has been scanned.

   An orphan scan is used to locate the coordinator with which the scanning
   device had previously associated. The orphan scan is performed on each
   channel by the MLME first sending an orphan notification command
   (see 7.3.2.3). The MLME then enables its receiver for at most
   aResponseWaitTime symbols. If the device receives a coordinator realignment
   command within this time, the MLME will disable its receiver. Otherwise, the
   scan is repeated on the next channel in the channel list. The scan
   terminates when the device receives a coordinator realignment command
   (see 7.3.2.5) or when every channel in the set of available channels has
   been scanned.

   The results of an ED scan are recorded in a list of ED values and reported
   to the next higher layer through the MLME-SCAN.confirm primitive with a
   status of SUCCESS. The results of an active or passive scan are recorded
   in a set of PAN descriptor values and reported to the next higher layer
   through the MLME-SCAN.confirm primitive. If no beacons were found, the
   MLME-SCAN.confirm primitive will contain a null set of PAN descriptor
   values and a status of NO_BEACON. Otherwise, the MLME-SCAN.confirm primitive
   will contain the set of PANDescriptor values found, a list of unscanned
   channels, and a status of SUCCESS.

   The results of an orphan scan are reported to the next higher layer through
   the MLME-SCAN.confirm primitive. If successful, the MLME-SCAN.confirm
   primitive will contain a status of SUCCESS. If the device did not receive a
   coordinator realignment command, the MLME-SCAN.confirm primitive will contain
   a status of NO_BEACON. In either case, the PANDescriptorList and
   EnergyDetectList parameters of the MLMESCAN.confirm primitive are null.

   If any parameter in the MLME-SCAN.request primitive is not supported or is
   out of range, the MAC sublayer will issue the MLME-SCAN.confirm primitive
   with a status of INVALID_PARAMETER.

 * @param m The MLME_SCAN.request message
 */

void mlme_scan_request(uint8_t *m)
{
    mlme_scan_req_t *msg = (mlme_scan_req_t *)m;
    mlme_scan_conf_t *msc = (mlme_scan_conf_t *)mac_buffer;

    msc->size = sizeof(mlme_scan_conf_t) - sizeof(msc->size);
    msc->cmdcode = MLME_SCAN_CONFIRM;
    msc->ScanType = msg->ScanType;
    msc->UnscannedChannels = msg->ScanChannels;
    msc->ResultListSize = 0;
    msc->data[0] = 0;           /* null result string */

    switch (mac_state)
    {
        /* Ignore scan request while scanning. */
        case MAC_ED:
        case MAC_X_as:
        case MAC_X_as1:
        case MAC_X_as2:
        case MAC_X_ps:
        case MAC_X_os:
        case MAC_X_os1:
            return;

        /* Return invalid parameters during transient states */
        // All CSMA-CA states
        case MAC_B:
        case MAC_C:
        case MAC_C2:
        case MAC_D:
        case MAC_E:
        case MAC_F:
        // All other transient states
        case MAC_await_frame:
        case MAC_H:
        case MAC_Wait_Response:
            msc->status = MAC_INVALID_PARAMETER;
            bios_pushback_event((uint8_t *)msc);
            return;

        default:
            /* Go on. */
            break;
    }

    /*
     * Verify parameters.  According to IEEE 802.15.4,
     * phyChannelsSupported must not be monitored, instead the
     * INVALID_PARAMETER response from the PHY when trying to set the
     * channel is examined.
     *
     * Note that we rely on the partial mlme_scan_conf_t being in
     * static mac_buffer memory to preserve its contents between the
     * various scan steps.
     */
    if (msg->ScanDuration > BEACON_NETWORK_MAX_BO)
    {
        msc->status = MAC_INVALID_PARAMETER;
        bios_pushback_event((uint8_t *)msc);
        return;
    }

    mac_original_state = mac_state;
    mac_original_channel = mac_current_channel;
    mac_scan_duration = msg->ScanDuration;
    switch (msc->ScanType)
    {
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
        /*
         * ED and active scans are optional for an RFD.
         */
    case MLME_SCAN_TYPE_ED:
        mac_current_channel = 0;
        msc->data[1] = 0;       /* first channel's accumulated energy level */
        mac_state = MAC_ED;
        scan_proceed(MLME_SCAN_TYPE_ED);
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC
    case MLME_SCAN_TYPE_ACTIVE:
        mac_current_channel = 0;
        /*
          Before commencing an active scan, the MAC sublayer shall
          store the value of macPANId and then set it to 0xffff for
          the duration of the scan. This enables the receive filter to
          accept all beacons rather than just the beacons from its
          current PAN (see 7.5.6.2). On completion of the scan, the
          MAC sublayer shall restore the value of macPANId to the
          value stored before the scan began.
         */
        mac_saved_panid = mac_pib_macPANId;
        mac_set_panid(0xffff);
        scan_proceed(MLME_SCAN_TYPE_ACTIVE);
        break;
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || DEVICE_TYPE == FD2_ACTSC */

    case MLME_SCAN_TYPE_PASSIVE:
        mac_current_channel = 0;
        /*
          Before commencing a passive scan, the MAC sublayer shall
          store the value of macPANId and then set it to 0xffff for
          the duration of the scan. This enables the receive filter to
          accept all beacons rather than just the beacons from its
          current PAN (see 7.5.6.2). On completion of the scan, the
          MAC sublayer shall restore the value of macPANId to the
          value stored before the scan began.
         */
        mac_saved_panid = mac_pib_macPANId;
        mac_set_panid(0xffff);
        scan_proceed(MLME_SCAN_TYPE_PASSIVE);
        break;

    case MLME_SCAN_TYPE_ORPHAN:
        // check whether there is any transaction ongoing that needs to be terminated
        if (mac_message != NULL)
        {
            mac_buffer_free(mac_message);
            mac_message = NULL;
        }
        mac_current_channel = 0;
        scan_proceed(MLME_SCAN_TYPE_ORPHAN);
        break;

    default:
        msc->status = MAC_INVALID_PARAMETER;
        bios_pushback_event((uint8_t *)msc);
        break;
    }
}

#endif /* APP_TYPE >= APP_L2 || defined(DOXYGEN) */

/* EOF */
