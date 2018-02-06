
/**
 * $Id: usr_mlme_scan_conf.c,v 1.1 2007/06/22 13:50:48 romano Exp $
 * @file
 * generated code for user callback function
 * - Generator: -C
 *
 */
/**
 *   uthor
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
#include "board.h"
#ifndef DEF_H
#include "def.h"
#endif
#include "ee_confMac.h"

#ifdef PANCOORDINATOR
extern coord_status_t c_status;
void usr_mlme_scan_conf(uint8_t status, uint8_t ScanType, uint32_t UnscannedChannels, uint8_t ResultListSize, uint8_t *data, uint8_t data_length)
{
    if ( c_status.state == PEND_INITIAL_SCAN_C )
    {
        /* We don't care about the confirm of the scan request because the scan */
        /* request just puts the MAC into the correct state for a pancoord. */
        mac_start_pan();
    }
    return;
}
#elif DEVICE
extern device_status_t d_status;
extern void mac_associate(void);
extern void mac_scan(void);
void usr_mlme_scan_conf(uint8_t status, uint8_t ScanType,
                        uint32_t UnscannedChannels, uint8_t ResultListSize,
                        uint8_t *data, uint8_t data_length)
{
    bool scan_success = false;

    if ((status == MAC_SUCCESS) && (d_status.state == PEND_SCAN_D))
    {
        /* there should only be one PAN descriptor */
        if (ResultListSize == 1)
        {
            scan_success = true;
            wpan_pandescriptor_t *pandesc = (wpan_pandescriptor_t *)data;

            /* save information from the PAN Descriptor */
            d_status.coord_address_mode = pandesc->CoordAddrMode;
            d_status.coord_address = pandesc->CoordAddress;
            d_status.pan_id = pandesc->CoordPANId;
            d_status.logical_channel = pandesc->LogicalChannel;

            /* associate to the PAN coordinator */
            mac_associate();
        }
    }

    if (!scan_success)
    {
        /* no success, scan again */
        mac_scan();
    }

    return;
}
#else
void usr_mlme_scan_conf(uint8_t status, uint8_t ScanType,
                        uint32_t UnscannedChannels, uint8_t ResultListSize,
                        uint8_t *data, uint8_t data_length)
			{
			}			
#endif




