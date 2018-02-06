/*******************************************************************************

ZeroG Driver Header File for the Microchip TCP/IP Stack

Copyright © 2009 Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*******************************************************************************/

/*********************************************************************
 *
 *  Finite State Machine and callbacks that are common to multiple
 *  types of networks (BSS and IBSS )
 *
 *********************************************************************
 * FileName:        ZGCommon.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGCommon.c
 * and ZGCommon.h when used in conjunction with the ZeroG ZG2100 for
 * the sole purpose of interfacing with the ZeroG ZG2100.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * EDIT BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date   		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * SG                  12/12/08
********************************************************************/

#ifndef _ZGCOMMON_H_
#define _ZGCOMMON_H_

#define kDefaultScanBssid_Byte0             0xFF
#define kDefaultScanBssid_Byte1             0xFF
#define kDefaultScanBssid_Byte2             0xFF
#define kDefaultScanBssid_Byte3             0xFF
#define kDefaultScanBssid_Byte4             0xFF
#define kDefaultScanBssid_Byte5             0xFF

#define kDefaultScanProbeDelay              (20)
#define kDefaultScanMinChanTime             (400)
#define kDefaultScanMaxChanTime             (800)
#define kDefaultNumMissedBeaconsAllowed     (100)

extern
tZGVoidReturn buildScanRequest( tZGScanReqPtr ptr );

extern
tZGVoidReturn printIPAddr( tZGVoidInput );


#endif /* _ZGCOMMON_H_ */
