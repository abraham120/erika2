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
 *  Easy Config implementation functions.
 *
 *********************************************************************
 * FileName:        ZGEasyConfig.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGEasyConfig.c
 * and ZGEasyConfig.h when used in conjunction with the ZeroG ZG2100 for
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
 * ZEROG BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
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
 * SCC                  09/24/09
********************************************************************/

#ifndef _ZGEASYCONFIG_H_
#define _ZGEASYCONFIG_H_

#include "HardwareProfile.h"
#include "TCPIP_Stack/TCPIP.h"
#include "TCPIPConfig.h"

#include "TCPIP_Stack/ZGDriverTypes.h"

typedef enum {                                          \
    net_infra = 0,                                      \
    net_adhoc,                                          \
    net_max                                             \
} tZGAppNetType;

typedef enum {                                          \
    sec_open = 0,                                       \
    sec_wpa_passphrase,                                 \
    sec_wpa_pskcalc,                                    \
    sec_wep64,                                          \
    sec_wep128,                                         \
    sec_max                                             \
} tZGAppSecurityType;

typedef enum {                                          \
    cfg_stopped = 0,                                    \
    cfg_wait_idle_complete,                             \
    cfg_max                                             \
} tZDynamicConfigStates;

typedef struct {
    BYTE isWifiNeedToConfigure;
    BYTE isWifiDoneConfigure;
    char ssid[33];  /* 32 for ssid and one for term character */
    tZGAppNetType type;  /* Net type infrastructure vs adhoc */
    tZGAppSecurityType security;
    BYTE  defaultWepKey;
    BYTE key[65];
    tZDynamicConfigStates cfg_state;
} tZGEasyConfigCtx;

extern tZGEasyConfigCtx g_easyConfigCtx;
#define CFGCXT	(g_easyConfigCtx)

/* Easy Config Public Functions */
tZGVoidReturn ZGEasyConfigInit(void);
tZGVoidReturn ZGEasyConfigMgr(void);

extern tZGVoidReturn
ZGUserScanMgr(tZGVoidInput);

extern
tZGVoidReturn  buildScanList(tZGBssDescPtr ptr);

tZGBool
startDynamicScan();

extern
tZGVoidReturn  DisplayScanList();

/* Macros */
#define ZG_WEP_KEY_INVALID     0xff

#if !defined (ZG_CONFIG_NO_WIFIMGRII)
#define  ZG_SCAN          WiFiScanRequest
#elif !defined (ZG_CONFIG_NO_ADHOCMGRII)
#define  ZG_SCAN          adHocScanRequest
#endif

#define ZG_START_EASY_CONFIG()   CFGCXT.isWifiNeedToConfigure = 1;
#endif /* _ZGEASYCONFIG_H_ */
