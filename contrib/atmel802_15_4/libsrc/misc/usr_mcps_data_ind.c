
/**
 * $Id: usr_mcps_data_ind.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include "ee.h"
#include "board.h"
#include "bios.h"
#include "phy.h"

#ifdef PANCOORDINATOR
extern coord_status_t c_status;
extern association_entry_t association_table[MAX_ENTRIES];

uint8_t ledevice=0;
uint16_t myoldcnt=0;
uint32_t myoldticks=0;
uint16_t mynewcnt=0;
uint32_t MyTicks=0;
uint32_t Dticks=0;
int32_t delay=0;
EE_UINT8  msdu_uart[5]={0,0,0,0,0};
EE_INT8  msdu_uartLength = 5;
#ifdef PANCOORDINATOR
extern bool StartNet;
extern receiver_st rec_st;
#endif
uint32_t Gstart;
uint32_t Gend;
uint32_t Gticks;

/*
uint32_t calc_delay(uint32_t ticks, uint32_t start, uint32_t end)
{
	uint32_t r;
	if (ticks > 0)
		r = ((ticks-1)<<16) + (0x10000 - start) + end;
	else
		r = end - start;
	Gstart = start;
	Gticks = ticks;
	Gend = end;
	if (r > 0x1000000)
		r = 0xffffffff;
	return r;
}

*/

void usr_mcps_data_ind(wpan_mcpsdata_addr_t *addrInfo, uint8_t mpduLinkQuality, uint8_t SecurityUse, uint8_t ACLEntry, uint8_t msduLength, uint8_t *msdu)
{
    /* Determine if the indication comes from a device,
     * that has previously associated.
     */
    cli();
    if (addrInfo->SrcAddrMode == WPAN_ADDRMODE_SHORT
        && association_table[(uint8_t)addrInfo->SrcAddr].associated)
    {
	
	ledevice = msdu[8];
	PORTE = ledevice;
	switch(ledevice){
		case 0xFB:
			msdu_uart[4]=1;
			break;
		case 0xF7:
			msdu_uart[4]=2;
			break;
		case 0xFE:
			msdu_uart[4]=3;
			break;
		case 0xFD:
			msdu_uart[4]=4;
			break;
		defualt:
			break;
	}
			
	myoldcnt = ((uint16_t) msdu[1])| (((uint16_t) msdu[2]) << 8);
	myoldticks = ((uint32_t) msdu[3])| (((uint32_t) msdu[4]) << 8)|
		((uint32_t) msdu[5] << 16)| (((uint32_t) msdu[6]) << 24);
	mynewcnt = EE_timer_3_get();
	Dticks = MyTicks - myoldticks;
	if (Dticks > 0)
		delay = ((Dticks-1)<<16) + (0x10000 - myoldcnt) + mynewcnt;
	else
		delay = mynewcnt - myoldcnt;
	memcpy(msdu_uart, &delay, 4);
	EE_uart_init();	
        EE_uartSend(msdu_uart, msdu_uartLength);
	PORTE = 0xFF;
	rec_st.state=RX_END_COORD;
	}
	sei();
    return;
}

#elif DEVICE
extern device_status_t d_status;
void usr_mcps_data_ind(wpan_mcpsdata_addr_t *addrInfo,
                       uint8_t mpduLinkQuality, uint8_t SecurityUse,
                       uint8_t ACLEntry, uint8_t msduLength, uint8_t *msdu)
{
    if ((d_status.state == RUN_D) && (addrInfo->DstPANId == d_status.pan_id))
    {
	    
	   	    
        /* Data packet contains LED information. */
        PORTE = ~((uint8_t)*msdu);
    }
}
#else
void usr_mcps_data_ind(wpan_mcpsdata_addr_t *addrInfo,
                       uint8_t mpduLinkQuality, uint8_t SecurityUse,
                       uint8_t ACLEntry, uint8_t msduLength, uint8_t *msdu)
		       {
		       }
#endif

