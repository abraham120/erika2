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
 *  A cache of Wireless 802.11 configuration setting and access methods
 *  This cache provides tools the ability to configure the WiFi connection
 *  attributes
 *
 *********************************************************************
 * FileName:        ZGLibCfg.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGLibCfg.c
 * and ZGLibCfg.h when used in conjunction with the ZeroG ZG2100 for
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
 * SG                  12/12/08
********************************************************************/
#ifndef _ZGLIBCFG_H_
#define _ZGLIBCFG_H_

#include "HardwareProfile.h"
#include "TCPIP_Stack/TCPIP.h"
#include "TCPIPConfig.h"

#include "TCPIP_Stack/ZGDriverTypes.h"
#include "TCPIP_Stack/ZGDriverConstants.h"
#include "TCPIP_Stack/ZGDriverIfaceApp.h"


/* constant parameters used for Join Operations */
#define kJoinTimeout        ((tZGU16)(10))    /* units of beacon intervals */
/* constant parameters used for Authentication Operations */
#define kAuthTimeout        ((tZGU16)(50))    /* units of 10 msec */
/* constant parameters used for Association Operations */
#define kSleepInterval    ((tZGU16)(4)) /* units of beacon intervals */
#define kAssocTimeout    ((tZGU16)(50))    /* units of 10 msec */



/* the following represent valid 802.11 capability Info bits used by the
 * ZGAdhocMgr.c code. */
/* these are all byte[0] bits */
#define kZGAdhocMgrCapBitIbss				(0x02)
#define kZGAdhocMgrCapBitBss				(0x01)
#define kZGAdhocMgrCapBitPrivacy			(0x10)
#define kZGAdhocMgrCapBitShortPreamble		(0x20)
#define kZGAdhocMgrCapBitAllowedMask		(0x33)
#define kZGAdhocMgrCapBitCFPollable			(0x04)
#define kZGAdhocMgrCapBitCFPollReq			(0x08)


#define kZGAdHocModeString    "adhoc"
#define kZGManagedModeString  "managed"
#define kZGIdleModeString     "idle"
#define kZGEnabled            "reenable"
#define kZGDisabled           "disable"
#define kZGDHCPStart          "start"
#define kZGDHCPDrop           "drop"
#define kZGUnicast            "unicast"
#define kZGOff                "off"
#define kZGAll                "all"
#define kZGNone               "<none>"

#define kZGWepKeyOne        "[1]"
#define kZGWepKeyTwo        "[2]"
#define kZGWepKeyThree      "[3]"
#define kZGWepKeyFour       "[4]"

#define PWR_MANAGEMENT_ENABLED  0
#define PWR_MANAGEMENT_DISABLED 1
#define ENABLE_RX_MULTICAST_IN_PWR_SAVE 1
#define DISABLE_RX_MULTICAST_IN_PWR_SAVE 0

#define DHCP_ENABLED  kZGBoolTrue
#define DHCP_DISABLED kZGBoolFalse

typedef struct {
   tZGBool      enabled;
   tZGBool      rxDTIM;
   tZGBool      pending;
} tZGLibPwrParam;

typedef tZGLibPwrParam *tZGLibPwrParamPtr;

typedef struct {
    tZGU8 key[kZGWepLongLen];
} tWEP;

#if defined ( ZG_CONFIG_CONSOLE )

#define MAX_RSSI_TABLE_SZ  5
typedef struct {
  tZGU8 max;
  tZGU8 min;
} tRssiQuanta;

/* string constants that may be shared system wide */
extern ROM tRssiQuanta           g_rssiTable[];
extern ROM FAR tZGS8             *g_DomainStrings[];
extern ROM FAR tZGS8             *g_EncStrings[];
extern ROM FAR tZGS8             *g_WepAuthStrings[];

#endif /* ZG CONFIG CONSOLE */

extern ROM tZGS8                 g_SDKVersion[];

#define ZG_GET_DHCP_STATE()         g_DHCP
#define ZG_GET_SDK_VERSION()        g_SDKVersion
#define ZG_RSSI_TBL_ENTRY_MIN(x)    g_rssiTable[x].min
#define ZG_RSSI_TBL_ENTRY_MAX(x)    g_rssiTable[x].max

#ifdef  ZG_CONFIG_DHCP
#define ZG_SET_DHCP_STATE(x)     ZGLibCfgSetDHCPState(x)
#endif



#ifdef ZG_CONFIG_LIBRARY

#define MAGIC_MAC_ADDR_BYTE1            (0x00u)
#define MAGIC_MAC_ADDR_BYTE2            (0x04u)
#define MAGIC_MAC_ADDR_BYTE3            (0xA3u)
#define MAGIC_MAC_ADDR_BYTE4            (0x00u)
#define MAGIC_MAC_ADDR_BYTE5            (0x00u)
#define MAGIC_MAC_ADDR_BYTE6            (0x00u)

#define g_targetSsid            ((tZGU8*)&AppConfig.MySSID)
extern tZGU8         g_targetChannels[];
#define g_targetMACAddress      ((tZGU8*)&AppConfig.MyMACAddr)
extern tZGU8         g_targetActiveChannels;
extern tZGU8         g_targetRegDom;
extern tZGBool       g_RfEnabled;
extern tZGBool       g_DHCP;
extern tZGU16        g_Rts;
extern tZGU8         g_PMKKeyData[];
extern tWEP          g_WEPKeyData[];
extern tZGS8         g_targetPassPhrase[];
extern tZGU8         g_encType;
extern tZGU8         g_authType;
extern tZGU8         g_wepKeyIndex;
extern tZGU8         g_wepKeyLen;
extern tZGBool       g_pwrMgmtEnabled;
extern tZGBool       g_pwrRxDTIMEnabled;

extern tZGU8         g_txRate;

/* the following represent valid 802.11 capability Info bits used by the
 * Link Management code. */
/* these are all byte[0] bits */
#define kWifiMgrCapBitIbss                  (0x02)
#define kWifiMgrCapBitBss                   (0x01)
#define kWifiMgrCapBitPrivacy               (0x10)
#define kWifiMgrCapBitShortPreamble         (0x20)
#define kWifiMgrCapBitAllowedMask           (0x33)
#define kWifiMgrCapBitCFPollable            (0x04)
#define kWifiMgrCapBitCFPollReq             (0x08)

/***************************************/
/* Security Info bitfield description  */
/*  used in joinCnf.secInfo to inform  */
/* the host as to the security types   */
/* identified in the beacon Info elem  */
/***************************************/
/* WPA/RSN authentication bits */
#define kWifiMgrSecInfoAuthOther        (0x8000)
#define kWifiMgrSecInfoAuth8021X        (0x4000)
#define kWifiMgrSecInfoAuthPsk          (0x2000)
/* WPA/RSN unicast/pairwise cipher bits */
#define kWifiMgrSecInfoUnicOther        (0x1000)
#define kWifiMgrSecInfoUnicWEP104       (0x0800)
#define kWifiMgrSecInfoUnicWEP40        (0x0400)
#define kWifiMgrSecInfoUnicCcmp         (0x0200)
#define kWifiMgrSecInfoUnicTkip         (0x0100)
/* WPA/RSN group/multicast cipher bits */
#define kWifiMgrSecInfoGrpOther         (0x0010)
#define kWifiMgrSecInfoGrpWEP104        (0x0008)
#define kWifiMgrSecInfoGrpWEP40         (0x0004)
#define kWifiMgrSecInfoGrpCcmp          (0x0002)
#define kWifiMgrSecInfoGrpTkip          (0x0001)
/***************************************/
/* Security Info element Request       */
/***************************************/
#define kWifiMgrSecInfoReqWpaPskTkip    (0x01)
#define kWifiMgrSecInfoReqWpaPskCcmp    (0x02)
#define kWifiMgrSecInfoReqRsnPskTkip    (0x10)
#define kWifiMgrSecInfoReqRsnPskCcmp    (0x20)

extern tZGBool
ZGLibCfgSetDataCfrm(tZGBool bEnabled );

extern tZGVoidReturn
ZGLibCfgSetDHCPState(tZGBool dhcp);

extern tZGVoidReturn
ZGLibCfgTempDisablePwrState(tZGVoidInput);

extern tZGVoidReturn
ZGLibCfgTempRestorePwrState(tZGVoidInput);

extern tZGBool
ZGLibCfgSetPwrMgmtState(tZGBool bEnabled, tZGBool bRxDTIM );


extern tZGVoidReturn
ZGLibCfgClearAllRfChannels( tZGVoidInput );

extern tZGVoidReturn
ZGLibCfgSetAllRfChannels( tZGVoidInput );

extern tZGBool
ZGLibCfgSetRfChannelList(tZGU8Ptr channelList, tZGU8 size);

extern tZGVoidReturn
ZGLibCfgSetSSID(tZGS8* pSsid, tZGU8 len);

extern tZGVoidReturn
ZGLibCfgSetMacAddress(tZGU8Ptr pMac);

extern tZGVoidReturn
ZGLibCfgSetWEPKey(tZGU8Ptr wep, tZGU8 index, tZGU8 keyLen);

extern tZGVoidReturn
ZGLibCfgSetWpaPSK(tZGU8Ptr psk);

extern tZGVoidReturn
ZGLibCfgSetWpaPassPhrase(tZGS8Ptr userFriendlyStr, tZGU8 length);


/* String routines are optional for the console application */
#if defined ( ZG_CONFIG_CONSOLE )

#define ZG_GET_CUR_AUTH_STR()       g_WepAuthStrings[ g_authType ]
#define ZG_GET_AUTH_STRING(x)       g_WepAuthStrings[x]

#define ZG_GET_CUR_ENC_STR()        g_EncStrings[ g_encType ]
#define ZG_GET_ENC_STRING(x)        g_EncStrings[x]

#define ZG_GET_DOM_STRING(x)        g_DomainStrings[x]
#define ZG_GET_CUR_DOM_STR()        g_DomainStrings[ g_targetRegDom ]

#endif


/* TX DATA CONFIRMATIONS FOR TX PKT SENDS */
#define ZG_SET_DATA_CFRM(x)        ZGLibCfgSetDataCfrm(x)
#define ZG_GET_DATA_CFRM()         g_dataConfirmation


/* POWER MANAGEMENT */
#define ZG_RESTORE_PWR_MGMT()      ZGLibCfgTempRestorePwrState()
#define ZG_DISABLE_PWR_MGMT()      ZGLibCfgTempDisablePwrState()
#define ZG_IS_PWR_MGMT_ENABLED()   g_pwrMgmtEnabled
#define ZG_SET_PWR_MGMT(x)         ZGLibCfgSetPwrMgmtState(x, g_pwrRxDTIMEnabled)
#define ZG_IS_DTIM_ENABLED()       g_pwrRxDTIMEnabled
#define ZG_SET_DTIM(x)             ZGLibCfgSetPwrMgmtState(g_pwrMgmtEnabled, x)


/* MAC ADDRESS */
#define ZG_GET_MAC_ADDR()           g_targetMACAddress
#define ZG_SET_MAC_ADDR(x)          ZGLibCfgSetMacAddress(x)
#define ZG_MAC_ADDR_BYTE(x)         g_targetMACAddress[x]


/* SSID */
#define ZG_SSID_LEN()               strlen( (char*) g_targetSsid)
#define ZG_GET_SSID()               g_targetSsid
#define ZG_SET_SSID(x,y)            ZGLibCfgSetSSID(x,y)


/* CHANNELS */
#define ZG_SET_CHANNEL_LIST(x,y)    ZGLibCfgSetRfChannelList(x,y)
#define ZG_GET_ACTIVE_CHANNELS()    g_targetActiveChannels
#define ZG_GET_CHANNELS_LIST()      g_targetChannels
#define ZG_CHANNEL(x)               g_targetChannels[x]
#define ZG_SET_ALL_CHANNELS()       ZGLibCfgSetAllRfChannels()
#define ZG_CLEAR_ALL_CHANNELS()     ZGLibCfgClearAllRfChannels()


/* DOMAIN */
#define ZG_SET_DOM(x)				g_targetRegDom = x
#define ZG_GET_DOM()                g_targetRegDom


/* ENCRYPTION MODE */
#define ZG_SET_ENC_TYPE(x)          g_encType = x
#define ZG_GET_ENC_TYPE()           g_encType


/* VARIOUS */
#define ZG_GET_RADIO_STATE()        g_RfEnabled
#define ZG_SET_RADIO_STATE(x)       g_RfEnabled = x
#define ZG_GET_RTS()                g_Rts
#define ZG_SET_RTS(x)               g_Rts = x
#define ZG_GET_TXRATE()             g_txRate
#define ZG_SET_TXRATE(x)            g_txRate = x


/* WEP methods */
#define ZG_GET_WEPKEY(x)            g_WEPKeyData[x].key
#define ZG_GET_WEP_ACTIVE_KEY()     g_WEPKeyData[g_wepKeyIndex].key
#define ZG_GET_WEP_ACTIVE_INDEX()   g_wepKeyIndex
#define ZG_SET_WEP_ACTIVE_INDEX(x)  g_wepKeyIndex = x
#define ZG_GET_WEP_KEY_LEN()        g_wepKeyLen
#define ZG_SET_WEP_KEY_LONG(x,y)    ZGLibCfgSetWEPKey(x, y, kZGWEPKeyLenLong)
#define ZG_SET_WEP_KEY_SHORT(x,y)   ZGLibCfgSetWEPKey(x, y, kZGWEPKeyLenShort)
#define ZG_SET_AUTH_TYPE(x)         g_authType = x
#define ZG_GET_AUTH_TYPE()          g_authType


/*WPA methods */
#define ZG_GET_WPAPSK()             g_PMKKeyData
#define ZG_SET_WPAPSK(x)            ZGLibCfgSetWpaPSK(x)
#define ZG_SET_WPA_PASSPHRASE(x,y)  ZGLibCfgSetWpaPassPhrase(x,y)
#define ZG_GET_WPA_PASSPHRASE()     g_targetPassPhrase
#define ZG_GET_PASSPHRASE_LEN()     strlen( (char *)g_targetPassPhrase)


#else // ZG_CONFIG_LIBRARY

/* POWER MANAGEMENT */
#define ZG_RESTORE_PWR_MGMT()
#define ZG_DISABLE_PWR_MGMT()
#define ZG_IS_PWR_MGMT_ENABLED()    kZGBoolFalse
#define ZG_SET_PWR_MGMT(x)
#define ZG_IS_DTIM_ENABLED()        kZGBoolFalse
#define ZG_SET_DTIM(x)
#define ZG_GET_MAC_ADDR()           0x000000000000
#define ZG_SET_MAC_ADDR(x)
#define ZG_MAC_ADDR_BYTE(x)
#define ZG_SSID_LEN()
#define ZG_GET_SSID()               "ERROR NO LINK MGR"
#define ZG_SET_SSID(x,y)
#define ZG_SET_CHANNEL_LIST(x,y)    kZGBoolTrue
#define ZG_GET_ACTIVE_CHANNELS()    1
#define ZG_GET_CHANNELS_LIST()      {0}
#define ZG_CHANNEL(x)               0
#define ZG_SET_ALL_CHANNELS()
#define ZG_CLEAR_ALL_CHANNELS()

#define ZG_GET_DOM()                kZGRegDomainFCC


/* String routines are optional for the console application */
#if defined ( ZG_CONFIG_CONSOLE )

#define ZG_GET_DOM_STRING(x)        "none"
#define ZG_GET_CUR_DOM_STR()        "none"
#define ZG_GET_CUR_ENC_STR()        NULL
#define ZG_GET_ENC_STRING(x)        NULL
#define ZG_GET_CUR_AUTH_STR()       NULL
#define ZG_GET_AUTH_STRING(x)       NULL

#endif


#define ZG_SET_ENC_TYPE(x)
#define ZG_GET_ENC_TYPE()           kKeyTypeNone
#define ZG_GET_RADIO_STATE()        kZGBoolTrue
#define ZG_SET_RADIO_STATE(x)
#define ZG_GET_RTS()                0
#define ZG_SET_RTS(x)
#define ZG_GET_WEPKEY(x)            0
#define ZG_GET_WEP_ACTIVE_KEY()     0
#define ZG_GET_WEP_ACTIVE_INDEX()   0
#define ZG_SET_WEP_ACTIVE_INDEX(x)
#define ZG_GET_WEP_KEY_LEN()        1
#define ZG_SET_WEP_KEY_LONG(x,y)
#define ZG_SET_WEP_KEY_SHORT(x,y)
#define ZG_SET_AUTH_TYPE(x)
#define ZG_GET_AUTH_TYPE()          kZGAuthAlgOpen
#define ZG_GET_WPAPSK()             0
#define ZG_SET_WPAPSK(x)
#define ZG_SET_WPA_PASSPHRASE(x,y)
#define ZG_GET_WPA_PASSPHRASE()     NULL
#define ZG_GET_PASSPHRASE_LEN()     0

#endif

#endif /*_ZGLIBCFG_H */
