/**
 * @file
 *
 * @brief MAC level API.
 *
 * $Id: api_mac.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include "phy.h"
#include "mac.h"
#include "timer_const.h"
#include "wpan_mac.h"

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */

void wpan_init(void)
{
#if APP_TYPE >= APP_L0
    bios_init();
#endif

#if APP_TYPE >= APP_L1
    phy_init();
#endif

#if APP_TYPE >= APP_L2
    mac_init(bios_get_ieee_addr());
#endif
    return;
}

#if APP_TYPE >= APP_L1 || defined(DOXYGEN)
bool wpan_task(void)
{
    uint8_t *event;
    bool processed_event = false;
    event = bios_popfront_event();
    if (event != NULL)
    {
        processed_event = true;
        bios_dispatch_event(event);
    }
    bios_timer_handler();

    return (processed_event);
}


bool wpan_start_timer(const uint8_t tid, const uint32_t duration)
{
    uint8_t timer_id = tid + T_LAST + 1;

    if (tid < 254 - T_LAST)
    {
        return (bios_starttimer(timer_id, duration));
    }
    return false;
}

bool wpan_stop_timer(const uint8_t tid)
{
    uint8_t timer_id = tid + T_LAST + 1;

    if (tid < 254 - T_LAST)
    {
        return(bios_stoptimer(timer_id));
    }
    return false;
}
#endif

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)
// MAC level API

bool wpan_mcps_data_request(const wpan_mcpsdata_addr_t *addrInfo,
    const uint8_t msduHandle,
    const uint8_t TxOptions, const uint8_t * msdu, const uint8_t msduLength)
{
    uint8_t buffer[MAX_MESSAGE_SIZE];
    mcps_data_req_t *datamsg = (mcps_data_req_t *)buffer;

    // Check data length.
    size_t max_length = msduLength;
    if (max_length > aMaxMACFrameSize)
    {
        max_length = aMaxMACFrameSize;
    }

    datamsg->cmdcode = MCPS_DATA_REQUEST;
    datamsg->SrcAddrMode = addrInfo->SrcAddrMode;
    datamsg->SrcPANId = addrInfo->SrcPANId;
    datamsg->SrcAddr = addrInfo->SrcAddr;
    datamsg->DstAddrMode = addrInfo->DstAddrMode;
    datamsg->DstPANId = addrInfo->DstPANId;
    datamsg->DstAddr = addrInfo->DstAddr;
    datamsg->msduHandle = msduHandle;
    datamsg->TxOptions = TxOptions;
    datamsg->data[0] = datamsg->msduLength = max_length;

    memcpy((void *)&datamsg->data[1], msdu, max_length);

    datamsg->size = sizeof(mcps_data_req_t) - sizeof(datamsg->size) + max_length;

    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)datamsg));
    }
    else
    {
        return false;
    }
}

bool wpan_mcps_purge_request(const uint8_t msduHandle)
{
    mcps_purge_req_t purge;
    purge.cmdcode = MCPS_PURGE_REQUEST;
    purge.msduHandle = msduHandle;
    purge.size = sizeof(mcps_purge_req_t) - sizeof(purge.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&purge));
    }
    else
    {
        return false;
    }
}

bool wpan_mlme_associate_request(const uint8_t LogicalChannel,
    const uint8_t CoordAddrMode, const uint16_t CoordPANId,
    const uint64_t CoordAddress, const uint8_t CapabilityInformation,
    const bool SecurityEnable)
{
    // Associate to the PAN coordinator.
    mlme_associate_req_t associate;
    associate.cmdcode = MLME_ASSOCIATE_REQUEST;
    associate.LogicalChannel = LogicalChannel;
    associate.CoordAddrMode = CoordAddrMode;
    associate.CoordPANId = CoordPANId;
    associate.CoordAddress = CoordAddress;
    associate.CapabilityInformation = CapabilityInformation;
    associate.SecurityEnable = SecurityEnable;
    associate.size = sizeof(mlme_associate_req_t) - sizeof(associate.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&associate));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_associate_response(const uint64_t DeviceAddress,
    const uint16_t assoc_ShortAddress, const uint8_t status,
    const bool SecurityEnable)
{
    mlme_associate_resp_t response;
    response.cmdcode = MLME_ASSOCIATE_RESPONSE;
    response.DeviceAddress = DeviceAddress;
    response.AssocShortAddress = assoc_ShortAddress;
    response.status = status;
    response.SecurityEnable = SecurityEnable;
    response.size = sizeof(mlme_associate_resp_t) - sizeof(response.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&response));
    }
    else
    {
        return false;
    }
}

bool wpan_mlme_disassociate_request(const uint64_t DeviceAddress,
    const uint8_t DisassociateReason, const bool SecurityEnable)
{
    mlme_disassociate_req_t disassociate;
    disassociate.cmdcode = MLME_DISASSOCIATE_REQUEST;
    disassociate.DeviceAddress = DeviceAddress;
    disassociate.DisassociateReason = DisassociateReason;
    disassociate.SecurityEnable = SecurityEnable;
    disassociate.size = sizeof(mlme_disassociate_req_t) - sizeof(disassociate.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&disassociate));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_gts_request(const uint8_t GTSCharacteristics,
    const bool SecurityEnable)
{
    mlme_gts_req_t gts;
    gts.cmdcode = MLME_GTS_REQUEST;
    gts.GTSCharacteristics = GTSCharacteristics;
    gts.SecurityEnable = SecurityEnable;
    gts.size = sizeof(mlme_gts_req_t) - sizeof(gts.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&gts));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_orphan_response(const uint64_t OrphanAddress,
    const uint16_t ShortAddress, const bool AssociatedMember,
    const bool SecurityEnable)
{
    mlme_orphan_resp_t response;
    response.cmdcode = MLME_ORPHAN_RESPONSE;
    response.OrphanAddress = OrphanAddress;
    response.ShortAddress = ShortAddress;
    response.AssociatedMember = AssociatedMember;
    response.SecurityEnable = SecurityEnable;
    response.size = sizeof(mlme_orphan_resp_t) - sizeof(response.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&response));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_reset_request(const bool SetDefaultPib)
{
    // Reset MAC.
    mlme_reset_req_t reset;
    reset.cmdcode = MLME_RESET_REQUEST;
    reset.SetDefaultPIB = SetDefaultPib;
    reset.size = sizeof(mlme_reset_req_t) - sizeof(reset.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&reset));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_get_request(const uint8_t PIBAttribute)
{
    mlme_get_req_t get;
    get.cmdcode = MLME_GET_REQUEST;
    get.PIBAttribute = PIBAttribute;
    get.size = sizeof(mlme_get_req_t) - sizeof(get.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&get));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_set_request(const uint8_t PIBAttribute,
    const void *PIBAttributeValue, const size_t PIBAttributeValueSize)
{
    uint8_t buffer[MAX_MESSAGE_SIZE];
    mlme_set_req_t *set = (mlme_set_req_t *)buffer;
    set->cmdcode = MLME_SET_REQUEST;
    set->PIBAttribute = PIBAttribute;
    set->data[0] = PIBAttributeValueSize;
    memcpy((void *)&set->data[1], PIBAttributeValue, PIBAttributeValueSize);
    set->size = sizeof(mlme_set_req_t) - sizeof(set->size)
        + PIBAttributeValueSize;
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)set));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_rx_enable_request(const bool DeferPermit,
    const uint32_t RxOnTime, const uint32_t RxOnDuration)
{
    mlme_rx_enable_req_t rxenable;
    rxenable.cmdcode = MLME_RX_ENABLE_REQUEST;
    rxenable.DeferPermit = DeferPermit;
    rxenable.RxOnTime = RxOnTime;
    rxenable.RxOnDuration = RxOnDuration;
    rxenable.size = sizeof(mlme_rx_enable_req_t) - sizeof(rxenable.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&rxenable));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_scan_request(const uint8_t ScanType,
    const uint32_t ScanChannels, const uint8_t ScanDuration)
{
    mlme_scan_req_t scan;
    scan.cmdcode = MLME_SCAN_REQUEST;
    scan.ScanType = ScanType;
    scan.ScanChannels = ScanChannels;
    scan.ScanDuration = ScanDuration;
    scan.size = sizeof(mlme_scan_req_t) - sizeof(scan.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&scan));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_start_request(const uint16_t PANId,
    const uint8_t LogicalChannel, const uint8_t BeaconOrder,
    const uint8_t SuperframeOrder, const bool PANCoordinator,
    const bool BatteryLifeExtension, const bool CoordRealignment,
    const bool SecurityEnable)
{
    mlme_start_req_t start;
    start.cmdcode = MLME_START_REQUEST;
    start.PANId = PANId;
    start.LogicalChannel = LogicalChannel;
    start.BeaconOrder = BeaconOrder;
    start.SuperframeOrder = SuperframeOrder;
    start.PANCoordinator = PANCoordinator;
    start.BatteryLifeExtension = BatteryLifeExtension;
    start.CoordRealignment = CoordRealignment;
    start.SecurityEnable = SecurityEnable;
    start.size = sizeof(mlme_start_req_t) - sizeof(start.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&start));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_sync_request(const uint8_t LogicalChannel,
    const bool TrackBeacon)
{
    mlme_sync_req_t sync;
    sync.cmdcode = MLME_SYNC_REQUEST;
    sync.LogicalChannel = LogicalChannel;
    sync.TrackBeacon = TrackBeacon;
    sync.size = sizeof(mlme_sync_req_t) - sizeof(sync.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&sync));
    }
    else
    {
        return false;
    }
}


bool wpan_mlme_poll_request(const uint8_t CoordAddrMode,
    const uint16_t CoordPANId, const uint64_t CoordAddress,
    const bool SecurityEnable)
{
    mlme_poll_req_t poll;
    poll.cmdcode = MLME_POLL_REQUEST;
    poll.CoordAddrMode = CoordAddrMode;
    poll.CoordPANId = CoordPANId;
    poll.CoordAddress = CoordAddress;
    poll.SecurityEnable = SecurityEnable;
    poll.size = sizeof(mlme_poll_req_t) - sizeof(poll.size);
    if (!bios_queue_full())
    {
        return(bios_pushback_event((void *)&poll));
    }
    else
    {
        return false;
    }
}

#endif // APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* EOF */
