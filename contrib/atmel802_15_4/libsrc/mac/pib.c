/**
 * @file
 *
 * @brief This file implements the MAC PIB attribute handling.
 *
 * $Id: pib.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#if SPECIAL_PEER
#include "private_const.h"
#endif // SPECIAL_PEER

#if APP_TYPE >= APP_L2 || defined (DOXYGEN)

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */


/* === Implementation ====================================================== */

/**
 * @brief Function to set the macPANId PIB attribute
 *
 * This function sets both, the macPANId PIB attribute inside the MAC,
 * as well as passing the information down to the hardware for
 * consideration in the address matching.
 *
 * @param panid New PANId
 */
void mac_set_panid(uint16_t panid)
{
    uint8_t         psr_buffer[sizeof(plme_set_req_t) + sizeof(uint16_t)];
    plme_set_req_t  *psr = (plme_set_req_t *)psr_buffer;
    uint8_t         *plmePIBAttributeValue = psr->data;
    plme_set_conf_t psc;

    mac_pib_macPANId = panid;
    psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint16_t);
    plmePIBAttributeValue[0] = sizeof(uint16_t);
    psr->PIBAttribute = phyPANid;
    memcpy(&plmePIBAttributeValue[1], &mac_pib_macPANId,
           sizeof(uint16_t));
    plme_set_request_internal(psr, &psc);
}

/**
 * @brief Function to set the macShortAddr PIB attribute
 *
 * This function sets both, the macShortAddr PIB attribute inside the MAC,
 * as well as passing the information down to the hardware for
 * consideration in the address matching.
 *
 * @param shortaddr New ShortAddr
 */
void mac_set_shortaddr(uint16_t shortaddr)
{
    uint8_t         psr_buffer[sizeof(plme_set_req_t) + sizeof(uint16_t)];
    plme_set_req_t  *psr = (plme_set_req_t *)psr_buffer;
    uint8_t         *plmePIBAttributeValue = psr->data;
    plme_set_conf_t psc;

    mac_pib_macShortAddress = shortaddr;
    psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) + sizeof(uint16_t);
    plmePIBAttributeValue[0] = sizeof(uint16_t);
    psr->PIBAttribute = phyShortAddr;
    memcpy(&plmePIBAttributeValue[1], &mac_pib_macShortAddress,
           sizeof(uint16_t));
    plme_set_request_internal(psr, &psc);
}


/**
 * @brief Handle an MLME-GET.request.
 *
 * The MLME-GET.request primitive requests information about a given PIB attribute.
 * This handles the MLME-GET.request, returning the internal value of
 * the respective PIB variable.
 *
 * @param m A pointer to the request structure
 */

void mlme_get_request(uint8_t *m)
{
    mlme_get_req_t  *mgr = (mlme_get_req_t *)m;
    mlme_get_conf_t *cm = (mlme_get_conf_t *) mac_buffer;

    mlme_get_request_internal(mgr, cm);

    bios_pushback_event(cm);
}

/**
 * @brief Handle an MLME-GET.request, internal form
 *
 * Internal form of an MLME-GET.request, returning the internal value
 * of the respective PIB variable.  Returns the MLME_GET.confirm
 * message in *cm.
 *
 * @param (in) msg A pointer to the request structure
 * @param (out) cm MLME-GET.confirm message
 * @return success/failure status
 */

uint8_t mlme_get_request_internal(mlme_get_req_t *msg, mlme_get_conf_t *cm)
{
    plme_get_req_t  pgr;
    uint8_t         pgc_buffer[sizeof(plme_get_conf_t) +
                               PHY_MAX_GETCONF_SIZE];
    plme_get_conf_t *pgc = (plme_get_conf_t *)pgc_buffer;
    uint8_t         *PIBAttributeValue = cm->data;

    cm->cmdcode      = MLME_GET_CONFIRM;
    cm->PIBAttribute = msg->PIBAttribute;
    cm->status       = MAC_SUCCESS;

    switch (msg->PIBAttribute)
    {
        case macAckWaitDuration:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macAckWaitDuration,
                   sizeof(uint8_t));
            break;

        case macAssociationPermit:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            PIBAttributeValue[1] = mac_pib_macAssociationPermit;
            break;

        case macAutoRequest:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            PIBAttributeValue[1] = mac_pib_macAutoRequest;
            break;

        case macBattLifeExt:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            PIBAttributeValue[1] = mac_pib_macBattLifeExt;
            break;

        case macBattLifeExtPeriods:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macBattLifeExtPeriods,
                   sizeof(uint8_t));
            break;

        case macBeaconPayload:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) +
                mac_pib_macBeaconPayloadLength;
            PIBAttributeValue[0] = mac_pib_macBeaconPayloadLength;
            memcpy(&PIBAttributeValue[1], mac_beacon_payload,
                   mac_pib_macBeaconPayloadLength);
            break;

        case macBeaconPayloadLength:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macBeaconPayloadLength,
                   sizeof(uint8_t));
            break;

        case macBeaconOrder:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macBeaconOrder,
                   sizeof(uint8_t));
            break;

        case macBeaconTxTime:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint32_t);
            PIBAttributeValue[0] = sizeof(uint32_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macBeaconTxTime,
                   sizeof(uint32_t));
            break;

        case macBSN:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macBSN,
                   sizeof(uint8_t));
            break;

        case macCoordExtendedAddress:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint64_t);
            PIBAttributeValue[0] = sizeof(uint64_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macCoordExtendedAddress,
                   sizeof(uint64_t));
            break;

        case macCoordShortAddress:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint16_t);
            PIBAttributeValue[0] = sizeof(uint16_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macCoordShortAddress,
                   sizeof(uint16_t));
            break;

        case macDSN:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macDSN,
                   sizeof(uint8_t));
            break;

        case macGTSPermit:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            PIBAttributeValue[1] = mac_pib_macGTSPermit;
            break;

        case macMaxCSMABackoffs:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macMaxCSMABackoffs,
                   sizeof(uint8_t));
            break;

        case macMinBE:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macMinBE,
                   sizeof(uint8_t));
            break;

        case macPANId:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint16_t);
            PIBAttributeValue[0] = sizeof(uint16_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macPANId,
                   sizeof(uint16_t));
            break;

        case macPromiscuousMode:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macPromiscuousMode,
                   sizeof(uint8_t));
            break;

        case macRxOnWhenIdle:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macRxOnWhenIdle,
                   sizeof(uint8_t));
            break;

        case macShortAddress:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint16_t);
            PIBAttributeValue[0] = sizeof(uint16_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macShortAddress,
                   sizeof(uint16_t));
            break;

        case macSuperframeOrder:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            PIBAttributeValue[0] = sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macSuperframeOrder,
                   sizeof(uint8_t));
            break;

        case macTransactionPersistenceTime:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint16_t);
            PIBAttributeValue[0] = sizeof(uint16_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_macTransactionPersistenceTime,
                   sizeof(uint16_t));
            break;

        default:
            /*
             * If not recognized by MAC, try the PHY.
             */
            pgr.size = sizeof(plme_get_req_t) - sizeof(pgr.size);
            pgr.cmdcode = PLME_GET_REQUEST;
            pgr.PIBAttribute = msg->PIBAttribute;
            if (plme_get_request_internal(&pgr, pgc) == PHY_SUCCESS)
            {
                cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + pgc->data[0];
                memcpy(PIBAttributeValue, pgc->data, pgc->data[0] + sizeof(uint8_t));
            }
            else
            {
                cm->status = MAC_UNSUPPORTED_ATTRIBUTE;
            }
            break;

#if SPECIAL_PEER
        /* The following PIB attributes are privately used for special test scenarios and
           are not part of the product code path */
        case macPrivateCCAFailure:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_privateCCAFailure,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;

        case macPrivateDisableACK:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_privateDisableACK,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;

        case macPrivateIeeeAddress:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint64_t);
            memcpy(&PIBAttributeValue[1], &mac_ieee_address, sizeof(uint64_t));
            cm->data[0] = sizeof(uint64_t);
            break;

        case macPrivateIllegalFrameType:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_privateIllegalFrameType,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;

        case macPrivateMACState:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_state,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;

        case macPrivateNoDataAfterAssocReq:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_privateNoDataAfterAssocReq,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;

        case macPrivateTransactionOverflow:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_privateTransactionOverflow,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;

        case macPrivateVirtualPANs:
            cm->size = sizeof(mlme_get_conf_t) - sizeof(cm->size) + sizeof(uint8_t);
            memcpy(&PIBAttributeValue[1], &mac_pib_privateVirtualPANs,
                   sizeof(uint8_t));
            cm->data[0] = sizeof(uint8_t);
            break;
#endif /* SPECIAL_PEER */
    }

    return cm->status;
}

/**
 * @brief Handle an MLME-SET.request
 *
 * This handles the MLME-SET.request. The MLME-SET.request primitive attempts to write
 * the given value to the indicated PIB attribute.
 * The respective internal PIB variable is set, and
 * the lower layer is informed about the change as well.
 *
 * @param m A pointer to the request structure
 */

void mlme_set_request(uint8_t *m)
{
    mlme_set_req_t  *msr = (mlme_set_req_t *)m;
    mlme_set_conf_t cm;

    (void)mlme_set_request_internal(msr, &cm);

    bios_pushback_event(&cm);
}

/**
 * @brief Handle an MLME-SET.request, internal form
 *
 * This is the internal form of an MLME-SET.request.  The respective
 * internal PIB variable is set, and if needed, the lower layer is
 * informed about the change as well. The resulting message is passed
 * back in *cm.
 *
 * @param (in) msg A pointer to the request structure
 * @@param (out) cm MLME-SET.confirm message
 * @return success/failure status
 */

uint8_t mlme_set_request_internal(mlme_set_req_t *msg, mlme_set_conf_t *cm)
{
    uint8_t         *PIBAttributeValue = msg->data;
    plme_set_req_t  *psr = (plme_set_req_t *) mac_buffer;
    uint8_t         *plmePIBAttributeValue = psr->data;
    plme_set_conf_t psc;

    psr->cmdcode    = PLME_SET_REQUEST;

    cm->size         = sizeof(mlme_set_conf_t) - sizeof(cm->size);
    cm->cmdcode      = MLME_SET_CONFIRM;
    cm->PIBAttribute = msg->PIBAttribute;
    cm->status       = MAC_SUCCESS;

    switch (msg->PIBAttribute)
    {
        case macAckWaitDuration:
            memcpy(&mac_pib_macAckWaitDuration, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macAssociationPermit:
            mac_pib_macAssociationPermit = PIBAttributeValue[1];
            break;

        case macAutoRequest:
            mac_pib_macAutoRequest = PIBAttributeValue[1];
            break;

        case macBattLifeExt:
            mac_pib_macBattLifeExt = PIBAttributeValue[1];
            break;

        case macBattLifeExtPeriods:
            memcpy(&mac_pib_macBattLifeExtPeriods, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macBeaconPayload:
            memcpy(mac_beacon_payload, &PIBAttributeValue[1],
                   mac_pib_macBeaconPayloadLength);
            break;

        case macBeaconPayloadLength:
            if (PIBAttributeValue[1] > aMaxBeaconPayloadLength)
            {
                cm->status = MAC_INVALID_PARAMETER;
                break;
            }
            memcpy(&mac_pib_macBeaconPayloadLength, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macBeaconOrder:
            memcpy(&mac_pib_macBeaconOrder, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macBeaconTxTime:
            memcpy(&mac_pib_macBeaconTxTime, &PIBAttributeValue[1],
                   sizeof(uint32_t));
            break;

        case macBSN:
            memcpy(&mac_pib_macBSN, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macCoordExtendedAddress:
            memcpy(&mac_pib_macCoordExtendedAddress, &PIBAttributeValue[1],
                   sizeof(uint64_t));
            break;

        case macCoordShortAddress:
            memcpy(&mac_pib_macCoordShortAddress, &PIBAttributeValue[1],
                   sizeof(uint16_t));
            break;

        case macDSN:
            memcpy(&mac_pib_macDSN, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macGTSPermit:
            memcpy(&mac_pib_macGTSPermit, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macMaxCSMABackoffs:
            memcpy(&mac_pib_macMaxCSMABackoffs, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macMinBE:
            memcpy(&mac_pib_macMinBE, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macPANId:
            mac_set_panid(*(uint16_t *)&PIBAttributeValue[1]);
            break;

        case macPromiscuousMode:
            memcpy(&mac_pib_macPromiscuousMode, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macRxOnWhenIdle:
            memcpy(&mac_pib_macRxOnWhenIdle, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macShortAddress:
            mac_set_shortaddr(*(uint16_t *)&PIBAttributeValue[1]);
            break;

        case macSuperframeOrder:
            if (PIBAttributeValue[1] > mac_pib_macBeaconOrder)
            {
                cm->status = MAC_INVALID_PARAMETER;
            }
            else
            {
                memcpy(&mac_pib_macSuperframeOrder, &PIBAttributeValue[1],
                       sizeof(uint8_t));
            }
            break;

        case macTransactionPersistenceTime:
            memcpy(&mac_pib_macTransactionPersistenceTime, &PIBAttributeValue[1],
                   sizeof(uint16_t));
            break;

        default:
            /*
             * If not recognized by MAC, try the PHY.
             */
            psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) +
                PIBAttributeValue[0];
            psr->PIBAttribute = msg->PIBAttribute;
            memcpy(plmePIBAttributeValue, PIBAttributeValue,
                   PIBAttributeValue[0] + sizeof(uint8_t));
            if (plme_set_request_internal(psr, &psc) != PHY_SUCCESS)
            {
                cm->status = MAC_UNSUPPORTED_ATTRIBUTE;
            }
            else if (msg->PIBAttribute == phyAutoACK)
            {
                /*
                 * PHY succeeded in enabling auto-ACK, keep a copy of
                 * that value.
                 */
                mac_phy_autoacks = PIBAttributeValue[1];
            }
            break;

#if SPECIAL_PEER
        /* The following PIB attributes are privately used for special test scenarios and
           are not part of the product code path */
        case macPrivateCCAFailure:
            memcpy(&mac_pib_privateCCAFailure, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macPrivateDisableACK:
            memcpy(&mac_pib_privateDisableACK, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macPrivateIeeeAddress:
            memcpy(&mac_ieee_address, &PIBAttributeValue[1], sizeof(uint64_t));
            /* Notify the PHY as well. */
            psr->data[0] = sizeof(uint64_t);
            memcpy(&psr->data[1], &mac_ieee_address, sizeof(mac_ieee_address));
            psr->size = sizeof(plme_set_req_t) - sizeof(psr->size) +
                sizeof(mac_ieee_address);
            psr->PIBAttribute = phyIEEEaddr;
            plme_set_request_internal(psr, &psc);
            break;

        case macPrivateIllegalFrameType:
            memcpy(&mac_pib_privateIllegalFrameType, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macPrivateNoDataAfterAssocReq:
            memcpy(&mac_pib_privateNoDataAfterAssocReq, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macPrivateTransactionOverflow:
            memcpy(&mac_pib_privateTransactionOverflow, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;

        case macPrivateVirtualPANs:
            memcpy(&mac_pib_privateVirtualPANs, &PIBAttributeValue[1],
                   sizeof(uint8_t));
            break;
#endif /* SPECIAL_PEER */
    }

    return cm->status;
}

#endif /* APP_TYPE >= APP_L2 || defined (DOXYGEN) */

/* EOF */
