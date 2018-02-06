
/**
 * $Id: usr_mlme_comm_status_ind.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
extern association_entry_t association_table[MAX_ENTRIES];

void usr_mlme_comm_status_ind(wpan_commstatus_addr_t *pAddrInfo, uint8_t status)
{
uint16_t assoc_idx = NO_ENTRY;

    if (pAddrInfo->PANId == PANID) /* if it is our PAN */
    {
        if (pAddrInfo->DstAddrMode == WPAN_ADDRMODE_SHORT)
        {
            assoc_idx = pAddrInfo->DstAddr;
        }
        else if (pAddrInfo->DstAddrMode == WPAN_ADDRMODE_LONG)
        {
            assoc_idx = search_association_entry(pAddrInfo->DstAddr);
        }

        if ((status == MAC_SUCCESS) && (assoc_idx < MAX_ENTRIES))
        {
            association_table[assoc_idx].associated = true;
        }
    }
}

#elif DEVICE
void usr_mlme_comm_status_ind(wpan_commstatus_addr_t *pAddrInfo, uint8_t status)
{
}
#else
void usr_mlme_comm_status_ind(wpan_commstatus_addr_t *pAddrInfo, uint8_t status)
{
}
#endif

