/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#include "WdDrv.h"

#define SWT_TIMEOUT_4SEC    0x03D09000U  // 4 sec watchdog timeout
#define SWT_TIMEOUT_2SEC    0x01E84800U  // 2 sec watchdog timeout
#define SWT_TIMEOUT_1SEC    0x00F42400U  // 1 sec watchdog timeout
#define SWT_TIMEOUT_100MSEC 0x00186A00U  // 100 msec watchdog timeout
#define SWT_TIMEOUT_10MSEC  0x00027100U  // 10 msec watchdog timeout
#define SWT_TIMEOUT_4MSEC   0x0000FA00U  // 4 msec watchdog timeout
#define SWT_TIMEOUT_2MSEC   0x00007D00U  // 2 msec watchdog timeout
#define SWT_TIMEOUT_1MSEC   0x00003E80U  // 1 msec watchdog timeout

// Watchdog initialization
void InitWatchdog(void)
{
    // This register is read only if either the SWT_CR[HLK]
    // or SWT_CR[SLK] bits are set
    // But they are set both to 0 by DisableWatchdog() function.
    // Hence This reguister can be written
	SWT.TO.R = 0x0F42400;	// 1 sec
}

// Enable Watchdog
void EnableWatchdog(void) 
{
    SWT.SR.R = 0x0000c520; // key
    SWT.SR.R = 0x0000d928; // key

    // Enable WEN (WEN = 1)
    // Fixed Service Sequence (KEY = 0)
    SWT.CR.R = 0xFF00017B;
}

// Service Watchdog to prevent it triggres a reset
void ServiceWatchdog(void)
{
	uint16_t temp16;
	
	if(SWT.CR.B.KEY == 0)
	{
        // Use Fixed Service Sequence: 0xA602 followed by 0xB480
		SWT.SR.B.WSC  = 0xA602;
		SWT.SR.B.WSC  = 0xB480;
	}
	else if(SWT.CR.B.KEY == 1)
	{
        // This statement is used if KEY is set to 1 in EnableWatchdog()
		temp16 = (uint16_t)SWT.SK.B.SERVICEKEY;
		SWT.SR.B.WSC = (uint16_t)((17*temp16) + 3);
 
		temp16 = (uint16_t)SWT.SK.B.SERVICEKEY;
		SWT.SR.B.WSC = (uint16_t)((17*temp16) + 3);
	}
}


