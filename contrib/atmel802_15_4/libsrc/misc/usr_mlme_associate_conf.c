
/**
 * $Id: usr_mlme_associate_conf.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
void usr_mlme_associate_conf( uint16_t AssocShortAddress, uint8_t status)
{
}

#elif DEVICE
extern device_status_t d_status;
extern void mac_associate(void);
void usr_mlme_associate_conf( uint16_t AssocShortAddress, uint8_t status)
{
    if ((status == MAC_SUCCESS) && (d_status.state == PEND_ASSOCIATE_D))
    {
        /* save the device short address */
        d_status.device_short_address = AssocShortAddress;

        /* mark that association is complete */
        SET_STATE( RUN_D );

        /* turn all LEDs off after successfull association */
        PORTE = 0xFF;
    }
    else
    {
        /* somethig went wrong, try  association again */
        mac_associate();
    }

    return;
}
#else
void usr_mlme_associate_conf( uint16_t AssocShortAddress, uint8_t status)
{
}
#endif


