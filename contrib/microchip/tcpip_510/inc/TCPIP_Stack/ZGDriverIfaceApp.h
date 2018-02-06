/*******************************************************************************

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

 DO NOT DELETE THIS LEGAL NOTICE:
  2006, 2007, 2008 © ZeroG Wireless, Inc.  All Rights Reserved.
  Confidential and proprietary software of ZeroG Wireless, Inc.
  Do no copy, forward or distribute.

Author               Date       Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Zero G              Sep 2008    Initial version
KO                  31 Oct 2008 Port to PIC24F and PIC32 for TCP/IP stack v4.52

*******************************************************************************/

#ifndef _ZGDRIVERIFACEAPP_H_
#define _ZGDRIVERIFACEAPP_H_

/**************************************/
/* Compatible G2100 Firmware Versions */
/**************************************/

#define kCompatibleB2Version (0x0307)
/* B1 is no longer supported */
/* #define kCompatibleB1Version (0x0209) */
/* A1 is no longer supported */
/* #define kCompatibleA1Version (0x0109) */


/***********************************/
/* START MAC Constants             */
/***********************************/


/* these values must match precisely with the
 * subtype values used by the Zero G G2100 */

/* driver message type definitions - MANAGEMENT */
#define kZGMSGFirstMessage        ((tZGU8)1)
#define kZGMSGScan                (kZGMSGFirstMessage)
#define kZGMSGJoin                ((tZGU8)2)
#define kZGMSGAuth                ((tZGU8)3)
#define kZGMSGAssoc               ((tZGU8)4)
#define kZGMSGDisconnect          ((tZGU8)5)
#define kZGMSGDisassoc            ((tZGU8)6)
#define kZGMSGSetPwrMode          ((tZGU8)7)
#define kZGMSGPMKKey              ((tZGU8)8)
#define kZGMSGWEPMap              ((tZGU8)9)
#define kZGMSGWEPKey              ((tZGU8)10)
#define kZGMSGTempKey             ((tZGU8)11)
#define kZGMSGCalcPSK             ((tZGU8)12)
#define kZGMSGWEPKeyID            ((tZGU8)13)
#define kZGMSGConfigKeySpace      ((tZGU8)14)
#define kZGMSGSetParam            ((tZGU8)15)
#define kZGMSGGetParam            ((tZGU8)16)
#define kZGMSGAdhocConnect        ((tZGU8)17)
#define kZGMSGAdhocStart          (18)
#define kZGMSGLastMessage         (kZGMSGAdhocStart)

/* driver message type definitions - DATA */
#define kZGMSGDataStd            ((tZGU8)1)
#define kZGMSGNullDataStd        ((tZGU8)2)
/* reserved value                ((tZGU8)3) */
#define kZGMSGDataUntampered     ((tZGU8)4)
#define kZGMSGDataTestMode       ((tZGU8)6)
/* kZGMgtCnf... - constants that represent the
 * management confirm type values. Note that
 * the value for the confirm matches its
 * corresponding input message value. */
#define kZGMgtCnfScan                kZGMSGScan
#define kZGMgtCnfJoin                kZGMSGJoin
#define kZGMgtCnfAuth                kZGMSGAuth
#define kZGMgtCnfAssoc               kZGMSGAssoc
#define kZGMgtCnfDisconnect          kZGMSGDisconnect
#define kZGMgtCnfDisassoc            kZGMSGDisassoc
#define kZGMgtCnfSetPwrMode          kZGMSGSetPwrMode
#define kZGMgtCnfPMKKey              kZGMSGPMKKey
#define kZGMgtCnfWEPMap              kZGMSGWEPMap
#define kZGMgtCnfWEPKey              kZGMSGWEPKey
#define kZGMgtCnfTempKey             kZGMSGTempKey
#define kZGMgtCnfCalcPSK             kZGMSGCalcPSK
#define kZGMgtCnfWEPKeyID            kZGMSGWEPKeyID
#define kZGMgtCnfConfigKeySpace      kZGMSGConfigKeySpace
#define kZGMgtCnfSetParam            kZGMSGSetParam
#define kZGMgtCnfGetParam            kZGMSGGetParam
#define kZGMgtCnfAdhocConnect        kZGMSGAdhocConnect
#define kZGMgtCnfAdhocStart          kZGMSGAdhocStart

/* kZGMgtIndDisconnect - sent by G2100 when it receives
 *      an 802.11 deauth frame from the Access Point */
#define kZGMgtIndDisconnect          ((tZGU8)2)
/* kZGMgtIndConnStatus - sent by G2100 when connection
 *      monitoring is enabled and a connection status
 *      event has occurred.  */
#define kZGMgtIndConnStatus          ((tZGU8)4)


/* interface constants */
#define kZGRegDomainLen                    (1)    /* number of bytes to set the Regional Domain */
#define kZGNumDefWepKeys                   (4)    /* number of WEP keys in a Slot */
#define kZGWepLongLen                     (13)    /* number of bytes in a 128 bit WEP key */
#define kZGNumContentionWindowEntries      (6)
#define kZGMinValidPassPhraseValue        (32)    /* defined in 802.11i H.4.1 */
#define kZGMaxValidPassPhraseValue       (126)    /* defined in 802.11i H.4.1 */
#define kZGMaxPhraseLen                   (63)    /* defined in 802.11i H.4.1 */
#define kZGMaxPendingTxRequests            (7)    /* maximum allowed pending Tx Requests */
#define kZGMACAddrLen                      (6)    /* the length in Bytes of a 802.11 MAC address */
#define kZGSetTxDataConfirmLen             (1)
#define kZGParamNumMissedBeaconsAllowedLen (1)
#define kZGMaxScanChannels                (14u)   /* the maximum number of channels to be scanned */
#define kZGMaxSsidLen                     (32)    /* the maximum size of an 802.11 SSID (network name) */
#define kZGMaxNumRates                     (8)    /* The maximum number of supported data rates */
#define kZGMaxScanTime                   (800)    /* the maximum allowed scan time per channel in TU's (1024 usec) */
#define kZGMaxPmkLen                      (32)    /* the exact size of a pairwise master key */
#define kZGNumStatCounters                (18)    /* the number of 32-bit stat counters that can be queried from the ZGMAC */
#define kZGMaxDataTxLen                 (2048)    /* 2KB limit on data frame */
#define kZGRxDataHdrLen                   (20)    /* length in bytes of the ZeroG Rx Data Header */
/* types of networks used in scan request */
#define kZGBssInfra        (1)    /* infrastructure only bss */
#define kZGBssAdHoc        (2)    /* Ad-hoc only Bss (ibss) */
#define kZGBssAny          (3)    /* any BSS infrastructure or independant (Ad-Hoc) */

/* Types of scan */
#define kZGScanTypeActive    (1)        /* Active Scan type indicator (uses probe requests) */
#define kZGScanTypePassive   (2)        /* Passive Scan type indicator (does not use probe requests) */

/* Types of 802.11 Authentication algorithms */
typedef enum
{
    kZGAuthAlgOpen = 0,  /* used for everything except WEP */
    kZGAuthAlgShared = 1 /* used for WEP only */
}tZGAuthAlg;

#define kZGWEPKeysNumDef    (4)

/***********************************/
/* Association Request Flags       */
/***********************************/
/* The appropriate security setting is typically acquired from
 * a successful Join Confirm Message. */
/* kAssocReqFlagWpaPsk... indicates that WPA should be used
 * as the authentication mechanism. */
#define kAssocReqFlagWpaPskTkip (0x01)
#define kAssocReqFlagWpaPskCcmp (0x02)
/* kAssocReqFlagRsnPsk... indicates that WPA2/RSN should be used
 * as the authentication mechanism. */
#define kAssocReqFlagRsnPskTkip (0x10)
#define kAssocReqFlagRsnPskCcmp (0x20)
/* kAssocReqFlagDontEchoDataRates is used to prevent the
 * G2100 from echoing the data rates list it acquired in
 * the AP's beacon/probe request frame and instead report
 * 1 and 2 mbps only.  This flag will cause some
 * AP's to fail the Association Request so it should be
 * used with extreme caution. */
#define kAssocReqFlagDontEchoDataRates (0x80)

/***********************************/
/* Tx throttle Table Definitions   */
/***********************************/

#define kZGTxThrottleTableDataRateMask       (0x80)
#define kZGTxThrottleTableDataRateTwoMbps    (0x80)
#define kZGTxThrottleTableDataRateOneMbps    (0x00)

#define kZGTxThrottleTablePowerMask          (0x7f)
/* Valid values for Tx power can range from kZGTxThrottleTableMinPower to
 * kZGTxThrottleTableMaxPower. Each step in power results in approximately
 * 1/2 dbm transmit power. */
#define kZGTxThrottleTableMinPower           (0x2c)
#define kZGTxThrottleTableMaxPower           (0x54)
#define kZGTxThrottleTableStep               (0x01)

#define kZGNumTxThrottleTableEntries         (4)
#define kZGTxThrottleTableEnableBit          (0x01)
#define kZGTxThrottleTableEnableShift        (0)

/***********************************/
/* Tx Untampered Flag Definitions  */
/***********************************/

/* If set the G2100 will use the short PHY preamble if the transmit rate is
 * greater than 1mbps. */
#define kTxUnTamperedFlagShortPreamble     (0x0001)
/* If set the G2100 must receive an 802.11 ACK frame to successfully complete the
 * transmission */
#define kTxUnTamperedFlagNeedsAck          (0x0002)
/* If set the G2100 must first receive a trigger frame prior to transmitting this frame. */
#define kTxUnTamperedFlagNeedsTrigger      (0x0004)
/* If set the G2100 will first transmit an RTS and require a CTS prior to transmitting the frame */
#define kTxUnTamperedFlagNeedsRts          (0x0008)
/* if set the G2100 will calculate a duration value and set it in the expected location.
 * It is only valid if kTxUnTamperedFlagNeedsAck is also set. */
#define kTxUnTamperedFlagNeedsDuration     (0x0010)
/* if set the G2100 will set the retry bit in the expected location if it re-transmits the frame
 * It is only valid if kTxUnTamperedFlagNeedsAck is also set */
#define kTxUnTamperedFlagSetRetryBit       (0x0020)
/* If set the G2100 will rely on the message headers txTable to determine tx data rate
 * for each transmit */
#define kTxUnTamperedFlagUseThrottleTable  (0x0040)
/* If set the G2100 will not set a backoff count between re-transmissions of the
 * same frame. */
#define kTxUnTamperedFlagZeroBackoff       (0x0080)

/* tZGError - The set of possible error codes returned by ZGGetLastError() */
typedef enum
{
    kZGErrorNone = 0,
    kZGErrorBadInputParam,
    kZGErrorOperationInProgress,
    kZGErrorNeedConfig,
    kZGErrorFailedNetworkJoin,
    kZGErrorFailedNetworkAuth,
    kZGErrorFailedNetworkAssoc,
    kZGErrorNotConnected,
    kZGErrorSPITxError,
    kZGErrorTooManyPendingTx
}tZGError;

typedef enum
{
    kZGResultSuccess = 1,       /* Successful completion of Request. */
    kZGResultInvalidSubType,    /* Unknown Subtype in Message Header. */
    kZGResultCancelled,         /* Frame was cancelled. */
    kZGResultFrameEol,          /* Frame exceeded the programmed Time out interval */
    kZGResultFrameRetryLimit,   /* Frame exceeded the programmed Tx Retry limit. */
    kZGResultFrameNoBss,        /* Failed to deliver frame because G2100 is not associated. */
    kZGResultFrameTooBig,       /* Data Frame exceeds 802.11 maximum size requirement. */
    kZGResultFrameEncryptFailure, /* Failed to encrypt the data frame as required prior to Tx. */
    kZGResultInvalidParams,     /* One or more input parameters for a request were invalid. */
    kZGResultAlreadyAuth,       /* Authenticated with a different AP */
    kZGResultAlreadyAssoc,      /* Associated with a different AP */
    kZGResultInsufficientRsrcs, /* G2100 failed the request due to insufficient resources. */
    kZGResultTimeout,       /* Management request Timed out prior to completion */
    kZGResultBadExchange,   /* frame exchange problem with peer */
    kZGResultAuthRefused,   /* authenticating node refused our request */
    kZGResultAsocRefused,   /* associating node refused our request */
    kZGResultReqInProgress, /* only one mlme request at a time allowed */
    /* several requests first require that the Device successfully 'join' a network */
    kZGResultNotJoined,     /* operation requires that device be joined with target */
    kZGResultNotAssoc,      /* operation requires that device be associated with target */
    kZGResultNotAuth,       /* operation requires that device be authenticated with target */
    kZGResultSupplicantFailed,
    kZGResultUnsupportedFeature,
    kZGResultRequestOutOfSync /* Returned when a request is recognized but invalid given the current State of the MAC */
}tZGResultCode;

/* the following enum represents acceptable values for any .macState
 * element which appears in any of the Management Confirm (kZGMgtCnf...) data structures. */
typedef enum
{
    kZGMACStateIdle = 1,    /* The G2100 MAC is idle */
    kZGMACStateJoined,      /* The G2100 MAC is monitoring a network. */
    kZGMACStateAuth,        /* The G2100 MAC is authenticated to a network. */
    kZGMACStateAssoc,       /* The G2100 MAC is associated to a network. */
    kZGMACStateIbss         /* The G2100 MAC is associated to a ad-hoc network. */
}tZGMACState;

typedef enum
{
    /* the chip lost the connection to the AP
     * as determined by the beacon missed threshold
     * set by the host. */
    kZGConnStatusLost = 1,
    /* the chip captured a beacon from the AP
     * while in the connection lost state. */
    kZGConnStatusFound
}tZGConnStatus;

/* tZGParam - Names (ID's) of ZG MAC configurable parameters. These IDs are intended to
 * be used with ZGMACSetParam(type ..) and ZGMACGetParam(type...) */
typedef enum
{
    /* the device MAC address (6 bytes) */
    kZGParamMACAddress = 1,
    /* the device Regional Domain (1 byte) */
    kZGParamRegDomain,
    /* the RTS byte threshold 256 - 2347 (2 bytes) */
    kZGParamRTSThreshold,
    /* the long Frame Retry limit  (1 byte) */
    kZGParamLongRetryLimit,
    /* the short Frame Retry limit (1 byte) */
    kZGParamShortRetryLimit,
    /* the Tx Request lifetime in TU's 0 - 4194303 (4 bytes) */
    kZGParamTxLifeTimeTU,
    /* the Rx Frame lifetime in TU's 0 - 4194303 (4 bytes) */
    kZGParamRxLifeTimeTU,
    /* boolean 1 = on 0 = off (1 byte) */
    kZGParamSupplicantOnOff,
    /* boolean 1 = on 0 = off (1 byte) */
    kZGParamConfirmDataTxReq,
    /* represents the master state of the MAC using enumerated values (1 byte) */
    kZGParamMasterState,
    /* a bit field which enables/disables various asynchronous indications
     * from the MAC to the host (2 bytes) */
    kZGParamHostAlertBits,
    /* the number of consecutive beacons that the MAC can miss before it considers the
     * network lost (1 byte) */
    kZGParamNumMissedBeaconsAllowed,
    /* delay intervals in usec DIFS and EIFS ( 2 * 2 bytes) */
    kZGParamDifsAndEifs,
    /* max and min boundaries for Tx power (2 * 2 bytes) */
    kZGParamHostTxPower,
    /* stores a persistant destination MAC address for small Tx Requests (6 bytes) */
    kZGParamDefaultDestinationMACAddress,
    /* stores a WPA info element (IE) in 802.11 IE format.
     * Used in Assoc Request and Supplicant exchange (3 - 258 bytes) */
    kZGParamWPAInfoElement,
    /* stores a RSN info element (IE) in 802.11 IE format.
     * Used in Assoc Request and Supplicant exchange (3 - 258 bytes) */
    kZGParamRSNInfoElement,
    /* boolean to force a radio state change 1 = on 0 = off (1 byte) */
    kZGParamOnOffRadio,
    /* A MAC address used to filter received frames
     * (sizeof(tAddressFilterInput) = 8 bytes) */
    kZGParamCompareAddress,
    /* a bitfield used to filter received frames based on type and sub-type
     * (sizeof(tAddressFilterInput) = 4 bytes) */
    kZGParamSubtypeFilter,
    /* a bitfield used to control the type of frames that cause ACK responses
     * (sizeof(tAckControlInput) = 4 bytes) */
    kZGParamAckControl,
    /* the complete set of statistics counters that are maintained by the MAC */
    kZGParamStatCounters,
    /* A custom Tx Rate throttle table to be used to control tx Rate */
    kZGParamTxThrottleTable,
    /* A boolean to enable/disable use of the throttle Table and a tx rate
     * to use if the throttle table is disabled */
    kZGParamTxThrottleTableOnOff,
    /* A custom Retry contention ladder used for backoff calculation
     * prior to a Tx attempt */
    kZGParamTxContentionArray,
    /* A 2 byte representation of a version number for the ROM and Patch */
    kZGParamSystemVersion
}tZGParam;


typedef struct
{
    tZGU16    value;
    tZGU8     idx;
    tZGU8     reserved;
}tZGMACSubtypeFilterInput;

typedef enum
{
    kZGSubtypeFilterIndexManagement= 0,
    kZGSubtypeFilterIndexControl,
    kZGSubtypeFilterIndexData
}tZGSubtypeFilterIndex;

typedef enum
{
    kZGMasterState80211 = 1,    /* default State G2100 MAC is active in layer. */
    kZGMasterStatePropreitary = 2
}tZGMasterStates;

/* Set of regulatory domains one of which must be assigned
 * to the ZG MAC on initialization */
typedef enum
{
    kZGRegDomainFCC = 0,         /* Available Channels: 1 - 11 */
    kZGRegDomainIC,              /* Available Channels: 1 - 11 */
    kZGRegDomainETSI,            /* Available Channels: 1 - 13 */
    kZGRegDomainSpain,           /* Available Channels: 1 - 13 */
    kZGRegDomainFrance,          /* Available Channels: 1 - 13 */
    kZGRegDomainJapanA,          /* Available Channels: 14     */
    kZGRegDomainJapanB           /* Available Channels: 1 - 13 */
}tZGRegDomain;

/* Optional Enumeration of acceptable Channel values for Join Request. */
typedef enum
{
    kZGRFChannelOne = 1,
    kZGRFChannelTwo,
    kZGRFChannelThree,
    kZGRFChannelFour,
    kZGRFChannelFive,
    kZGRFChannelSix,
    kZGRFChannelSeven,
    kZGRFChannelEight,
    kZGRFChannelNine,
    kZGRFChannelTen,
    kZGRFChannelEleven,
    kZGRFChannelTwelve,
    kZGRFChannelThirteen,
    kZGRFChannelFourteen
}tZGRFChannel;

/* Enumeration of valid values for SetParameter: kZGParamOnOffRadio */
typedef enum
{
    kZGRFStateOff = 0, /* Force the Radio Off */
    kZGRFStateOn  = 1   /* Force the Radio On. */
}tZGRFState;

/* Enumeration of valid values for ZGSetPowerSaveMode() */
typedef enum
{
    kZGPsPwrModeSave = 0,
    kZGPsPwrModeActive
}tZGPsPwrMode;

typedef enum
{
    kZGRFRateOneMbps = 2,
    kZGRFRateTwoMbps = 4
}tZGRFRate;

/* Enumeration of valid values for WEP key lengths */
typedef enum
{
     kZGWEPKeyLenShort = 5,
    kZGWEPKeyLenLong   = 13
}tZGWEPKeyLen;

/* Enumeration of valid values for Security key storage slots used
 * in  ZGSetPMKKey() and ZGSetWEPKey() */
typedef enum
{
    tZGSecKeySlotPmk0 = 0,
    tZGSecKeySlotPmk1,
    tZGSecKeySlotPmk2,
    tZGSecKeySlotWEPDef
}tZGSecKeySlot;

typedef enum
{
    kKeyTypeNone = 0,
    kKeyTypeWep,
    kKeyTypePsk,
    kKeyTypeCalcPsk
}tZGEncryptType;

/*Wep Devkey enumerations */
typedef enum
{
 tZGWepKeyOne = 0,
 tZGWepKeyTwo,
 tZGWepKeyThree,
 tZGWepKeyFour
}tZGWepDevID;


/***********************************/
/* END MAC Constants               */
/* ...                             */
/* START Data Structure Definition */
/***********************************/

typedef struct
{
    tZGU8 mode;
    tZGU8 wake;
    tZGU8 rcvDtims;
    tZGU8 reserved;            /* pad byte */
}tZGPwrModeReq;

typedef tZGPwrModeReq *tZGPwrModeReqPtr;

#define kZGPwrModeReqSZ (4)

/* completely describes the details of a BSS (access point) */
/* This structure is used as a single entry in a Scan result */
typedef struct
{
    tZGU8        bssid[kZGMACAddrLen]; /* network BSSID value */
    tZGS8        ssid[kZGMaxSsidLen];   /* network SSID value */
    tZGU8        capInfo[2];            /* capability info bits */
    tZGU16       beaconPeriod;          /* network Beacon interval */
    tZGU16       atimWindow; /* only valid if .bssType == Ibss */
    tZGU8        basicRateSet[kZGMaxNumRates]; /* list of network basic rates */
    tZGU8        rssi;            /* signal strength of rx'd
                                  * frame beacon, probe resp */
    tZGU8        numRates;        /* num entries in basicRateSet */
    tZGU8        DtimPeriod;      /* (part of TIM element) */
    tZGU8        bssType;           /* ad-hoc or infrastructure. */
    tZGU8        channel;        /* phy param set */
    tZGU8        ssidLen;       /* number of bytes in ssid */
} tZGBssDesc; /* 58 bytes */

typedef tZGBssDesc *tZGBssDescPtr;

/* use #define size to represent the number of bytes in the structure
 * because not all compilers have an appropriate calculation when using sizeof() */
#define kZGBssDescSZ (58)

/* Represents the input parameters required to
 * conduct a Scan operation */
typedef struct
{
    tZGU16         probeDelay;           /* the number of usec to delay before transmitting a probe
                                          * request following the channel change event */
    tZGU16         minChannelTime;       /* the minimum time to spend on each channel in units
                                          * of TU (1024 usec) */
    tZGU16         maxChannelTime;       /* the maximum time to spend on each channel in units
                                          * of TU (1024 usec) */
    tZGU8          bssid[kZGMACAddrLen]; /* limits the scan to a specific Bss or Broadcast
                                          * (FF:FF:FF:FF:FF:FF) */
    tZGU8          bss;                  /* limits the type of networks to include in scan results.
                                          * Can be one of; kBssInfra kBssAdHoc kBssAny*/
    tZGU8          snType;               /* one of kZGMACSnTypeActive or kZGMACSnTypePassive where
                                          * active indicates the use of Probe Request frames */
    tZGU8          ssidLen;              /* num chars in ssid */
    tZGU8         chnlLen;               /* num channels to scan */
    tZGS8         ssid[kZGMaxSsidLen];   /* limits the scan to a specific Service Set (SSID) or
                                          * broadcast ("\0") */
    tZGU8        channelList[kZGMaxScanChannels]; /* zero terminated list of channels
                                                   * to scan */
} tZGScanReq; /* 62 bytes */

typedef tZGScanReq *tZGScanReqPtr;

/* use #define size to represent the number of bytes in the structure
 * because not all compilers have an appropriate calculation when using sizeof() */
#define kZGScanReqSZ    (62)

/* The structure used to return the scan results back to the host system */
typedef struct
{
    tZGU8    result;        /* the result of the scan */
    tZGU8    macState;      /* current state of the on-chip MAC */
    tZGU8    lastChnl;      /* the last channel scanned */
    tZGU8    numBssDesc;    /* The number of tZGMACBssDesc objects that
                             * immediately follows this structure in memory */
} tZGScanResult; /* 4 bytes */

typedef tZGScanResult *tZGScanResultPtr;

#define kZGScanResultSZ    (4)

typedef struct
{
    tZGU16 to;     /* the join timeout in units of beacon intervals. If the STA
                    * cannot successfully Rx a beacon or probe response from the
                    * specified network within this time frame the operation will
                    * fail. */
    tZGU16 beaconPeriod;         /* beacon period in units of TU's (1024 usec) */
    tZGU8 bssid[kZGMACAddrLen];  /* the bssid of the target */
    tZGU8 channel;               /* the 2.4 GHz channel alias values 1 thru 15 */
    tZGU8 ssidLen;               /* num valid bytes in ssid */
    tZGS8 ssid[kZGMaxSsidLen];   /* the ssid of the target */
} tZGJoinReq;

typedef tZGJoinReq *tZGJoinReqPtr;

#define kZGJoinReqSZ (6 + kZGMACAddrLen + kZGMaxSsidLen)

typedef struct
{
    tZGU8 result;   /* one of tZGResultCode enum values. */
    tZGU8 macState; /* one of tZGMACState enum values. */
    tZGU16 capInfo; /* capability info bits received in Beacon. */
    tZGU16 securityInfo[2]; /* security information for network. */
} tZGJoinCnf;

typedef tZGJoinCnf *tZGJoinCnfPtr;

#define kZGJoinCnfSZ (8)

typedef struct
{
    tZGU8     addr[kZGMACAddrLen];    /* the BSSID of the network with which to authenticate */
    tZGU16     to;                    /* authentication timeout in 10's of msec */
    tZGU8     alg;                    /* auth algorithm; open or shared key */
    tZGU8    reserved;                /* pad byte */
} tZGAuthReq;

typedef tZGAuthReq *tZGAuthReqPtr;

#define kZGAuthReqSZ (4 + kZGMACAddrLen)

typedef struct
{
    tZGU8 addr[kZGMACAddrLen];  /* addr of the AP that will receive the assoc frame */
    tZGU8 channel;              /* channel 1-14 only required for re-association */
    tZGU8 flags;                /* The most significant bit is used to control the
                                 * data rates reported in the associaton request. The
                                 * remaining bits are security selection bits to instruct construction
                                 * of a security IE */
    tZGU16    to;               /* association timeout in 10's of msec */
    tZGU8 capInfo[2];           /* the capabilities of this station. They must
                                 * coincide with what the AP publishes in its beacon */
    tZGU16 listenIntval;        /* the number of beacons that may pass between
                                 * listen attempts by this Station. Indicates to
                                 * the AP how how much resources may be required to
                                 * buffer for this station while its sleeps */
    tZGU16 elemLen;             /* length of additional elements to be included in
                                 * the assoc frame that immediately follows this
                                 * data structure */
} tZGAssocReq;

typedef tZGAssocReq *tZGAssocReqPtr;

#define kZGAssocReqSZ (10 + kZGMACAddrLen)

typedef struct
{
    tZGU8 result;   /* one of tZGResultCode enum values. */
    tZGU8 macState; /* one of tZGMACState enum values. */
    /* the reason code, if any, provided by the peer Station in the
     * assocation response frame */
    tZGU16 reasonCode;
    /* the capability info provided in the association response frame */
    tZGU8 capInfo[2];
    /* the association ID provided in the association response frame */
    tZGU16 aid;
    /* the length in bytes of optional elements which may follow this structure in memory */
    tZGU16 elemLen;
} tZGAssocCnf;

typedef tZGAssocCnf *tZGAssocCnfPtr;

#define kZGAssocCnfSZ (10)

typedef struct
{
    tZGU8    channel;                   /* DS param set */
    tZGU8     ssidLen;                  /* num valid bytes in ssid */
    tZGU8     dataRateLen;              /* num valid data rates */
    tZGU8     reserved;                  /* padding byte */
    tZGU16    beaconPrd;                 /* units of TU */
    tZGU8     capInfo[2];                /* Cap Info must equal 0x3200 | 0x2200 | 0x1200 | 0x0200 */
    tZGU8     dataRates[kZGMaxNumRates]; /* the set of data rates published in the beacon. */
    tZGS8     ssid[kZGMaxSsidLen];      /* string name for Station */
} tZGAdhocStartReq;    /* 48 bytes */

typedef tZGAdhocStartReq *tZGAdhocStartReqPtr;

#define kZGAdhocStartReqSZ (48)

typedef struct
{
    tZGU16 timeout;                /* the timeout in units of beacon intervals. If the STA
                                    * cannot successfully connect to the adhoc network
                                    * within the specified timeout the device will fail the
                                    * request. */
    tZGU16 beaconPrd;              /* beacon period in units of TU's (1024 usec) */
    tZGU8 bssid[kZGMACAddrLen];    /* the bssid of the target */
    tZGU8 channel;                 /* the 2.4 GHz channel alias values 1 thru 15 */
    tZGU8 ssidLen;                 /* num valid bytes in ssid */
    tZGS8 ssid[kZGMaxSsidLen];     /* the ssid of the target */
} tZGAdhocConnectReq;

typedef tZGAdhocConnectReq *tZGAdhocConnectReqPtr;

#define kZGAdhocConnectReqSZ (44)

/* Represents the input parameters required to
 * conduct a Network Disconnect operation */
typedef struct
{
    tZGU16 reasonCode;      /* specifies the reason for transmitting the
                             * deauthentication and is included in the Deauth frame
                             * that gets sent to the AP. */
    tZGU8    disconnect;    /* boolean if non-zero the MAC will enter into the
                             * Idle State upon completion of the request, otherwise
                             * the MAC will enter into the Joined State and
                             * continue monitoring network beacons.*/
    tZGU8    txFrame;       /* boolean if non-zero the MAC will transmit a deauth
                             * frame to the network. */
} tZGDisconnectReq; /* 4 bytes */

typedef tZGDisconnectReq *tZGDisconnectReqPtr;

#define kZGDisconnectReqSZ    (4)

/* Represents the input parameters required to
 * conduct a Network Data Transmit operation */
typedef struct
{
    tZGU8     reqID;    /* unique identifier returned in the Tx Data Confirm message. */
    tZGU8    reserved;          /* 1-byte reserved for driver use */
    tZGU8    da[kZGMACAddrLen]; /* The destination MAC address for the frame. */
    /* the data to be transmitted as the payload immed
     * follows this structure in memory. */
} tZGTxDataReq;

typedef tZGTxDataReq *tZGTxDataReqPtr;

#define kZGTxDataReqSZ    (8)

typedef struct
{
    tZGU8     reqID;        /* A unique identifier that will be returned as
                             * an element of the tZGMACTxDataCnf structure
                             * that applies to a specific request. */
    tZGU8    numRetransmits;
    tZGU16     flags;        /* various bit options that dictate transmit parameters */
    tZGU8    txTable[4];
} tZGTxUntamperedFrameReq;

typedef tZGTxUntamperedFrameReq *tZGTxUntamperedFrameReqPtr;

#define kZGTxUntamperedFrameReqSZ (4 + 4)

/* The purpose of this data structure is to indicate that a peer Station or AP
 * has sent a 802.11 DATA frame to this device. */
typedef struct
{
    tZGU16        rssi;                      /* the value of the G1000 RSSI when the data frame was received */
    tZGU8         dstAddr[kZGMACAddrLen];    /* MAC Address to which the data frame was directed. */
    tZGU8         srcAddr[kZGMACAddrLen];    /* MAC Address of the Station that sent the Data frame. */
    tZGU32        arrivalTime;               /* the value of the 32-bit G1000 system clock when the frame arrived */
    tZGU16        dataLen;                   /* the length in bytes of the payload which immediately follows this data structure */
} tZGRxDataInd; /* 20 bytes */

typedef tZGRxDataInd *tZGRxDataIndPtr;

#define kZGRxDataIndSZ    (20)

/* The purpose of this data structure is to indicate that a frame was
 * successfully received while in promiscuous mode; a mode whereby
 * all frames are forwarded to the host */
typedef struct
{
    tZGU16            rssi;         /* the value of the G1000 RSSI when the data frame was received */
    tZGU32            arrivalTime;  /* the value of the 32-bit G1000 system clock when the frame arrived */
    tZGU16            dataLen;      /* the length in bytes of the payload which immediately follows this data structure */
} tZGRxDataPromiscInd;

typedef tZGRxDataPromiscInd *tZGRxDataPromiscIndPtr;

#define kZGRxDataPromiscIndSz (8)

typedef struct
{
    tZGU8 slot;
    tZGU8 ssidLen;
    tZGU8 ssid[kZGMaxSsidLen];
    tZGU8 keyData[kZGMaxPmkLen];
} tZGPMKKeyReq;

typedef tZGPMKKeyReq *tZGPMKKeyReqPtr;

#define kZGPMKKeyReqSZ (2 + kZGMaxSsidLen + kZGMaxPmkLen)

typedef struct
{
    tZGU8        slot;                  /* slot index */
    tZGU8        keyLen;                /* one of kWepShortLen or kWepLongLen */
    tZGU8        defID;                 /* the default wep key ID. One of 0 -> 3 */
    tZGU8         ssidLen;              /* num valid bytes in ssid */
    tZGU8         ssid[kZGMaxSsidLen];  /* string name for Network */
    tZGU8        key[kZGNumDefWepKeys][kZGWepLongLen]; /* wep key data for 4 default keys */
} tZGWEPKeyReq;

typedef tZGWEPKeyReq *tZGWEPKeyReqPtr;

#define kZGWEPKeyReqSZ (4 + kZGMaxSsidLen + kZGNumDefWepKeys*kZGWepLongLen)

/* (Host MCU -> Zero G chip) to confirm a PRE-SHARED KEY CALCULATE REQUEST */
typedef struct
{
    tZGU8 configBits;                    /* used to dictate MAC behavior following the calculation */
    tZGU8 phraseLen;                     /* number of valid bytes in passphrase */
    tZGU8 ssidLen;                       /* number of valid bytes in ssid */
    tZGU8 reserved;                      /* alignment byte */
    tZGS8 ssid[kZGMaxSsidLen];           /* the string of characters representing the ssid */
    tZGS8 passPhrase[kZGMaxPhraseLen+1]; /* the string of characters representing the pass phrase */
} tZGPskCalcReq;

typedef tZGPskCalcReq *tZGPskCalcReqPtr;

#define kZGPskCalcReqSZ    (4 + kZGMaxSsidLen + kZGMaxPhraseLen + 1) /* 100 bytes */

/* (Zero G chip -> Host MCU) to confirm a PRE-SHARED KEY CALCULATE REQUEST */
typedef struct
{
    tZGU8 result;                    /* one of kZGMACResult... indicating success or other */
    tZGU8 macState;                 /* current State of the on-chip MAC */
    tZGU8 keyReturned;               /* 1 if psk contains key data, 0 otherwise */
    tZGU8 reserved;                 /* pad byte */
    tZGU8 psk[kZGMaxPmkLen];         /* the psk bytes */
} tZGPskCalcCnf;

typedef tZGPskCalcCnf *tZGPskCalcCnfPtr;

#define kZGPskCalcCnfSZ    (4 + kZGMaxPmkLen) /* 36 bytes */


/* (Zero G chip -> Host MCU) to confirm a MAC GET-PARAMETER REQUEST */
typedef struct
{
    tZGU8 result;        /* one of kZGMACResult... indicating success or other */
    tZGU8 macState;      /* state of the MAC */
    tZGU8 dataLen;       /* number of bytes of data following this structure */
    tZGU8 reserved;      /* pad byte */
    /* data specific to the request immediately follows this object in memory */
} tZGGetMACParamCnf;

typedef tZGGetMACParamCnf *tZGGetMACParamCnfPtr;

#define kZGGetMACParamCnfSZ (4)

/***************************************/
/* END Data Structure Definition       */
/* ...                                 */
/* START Interface function Prototypes */
/***************************************/

extern tZGError ZGGetLastError(tZGVoidInput);

extern tZGReturnStatus ZGReset(tZGVoidInput);

extern tZGReturnStatus ZGSignalDriver(tZGVoidInput);

/*****************************************************************************
 * FUNCTION: ZGInit
 *
 * RETURNS: kZGSuccess or kZGFailure
 *
 * PARAMS:
 *
 *    NOTES: This function must be called once prior to calling any other ZG...
 *            functions.  This function initializes the ZG Driver internal State.
 *            It also verifies functionality of the lower level SPI driver and
 *            connected hardware.
 *****************************************************************************/
extern tZGReturnStatus ZGInit(tZGVoidInput);

/*****************************************************************************
 * FUNCTION: ZGMACIFScan
 *
 * RETURNS: kZGMACSuccess or kZGMACFailure
 *
 * PARAMS:
 *        None
 *
 *    NOTES: Invokes a Scan operation by the ZeroG chip.  The caller supplies
 *        input parameters with the tZGMACScanReq.  The memory used to hold the
 *        tZGMACScanReq will be used to transfer the information to the ZeroG
 *        chip.  This function will return after the transmission has completed.
 *        If the transmission completed successfully the function will return
 *        kZGMACSuccess. Otherwise it will return kZGMACFailure.  The Scan
 *        results will be returned by the ZeroG chip and can be recovered with a
 *        call to ZGMACIFReceive().
 *****************************************************************************/
extern tZGReturnStatus ZGScan(tZGVoidInput);

extern tZGReturnStatus ZGJoin(tZGVoidInput);

extern tZGReturnStatus ZGAuth(tZGVoidInput);

extern tZGReturnStatus ZGAssoc(tZGVoidInput);

extern tZGReturnStatus ZGAdhocStart(tZGVoidInput);

extern tZGReturnStatus ZGAdhocConnect(tZGVoidInput);

extern tZGReturnStatus ZGDisconnect(tZGVoidInput);

extern tZGReturnStatus ZGGetParam(tZGParam type);

/* tZGParam type - identifies the parameter whose value will be set
 * pBuf - points to the data containing the new value for the parameter
 * len - the number of bytes that should be taken from pBuf and written
 *         to the chip. */
extern tZGReturnStatus ZGSetParam(tZGParam type, tZGU16 len);

/*****************************************************************************
 * FUNCTION: ZGMACIFSetPMKKey
 *
 * RETURNS: kZGMACSuccess or kZGMACFailure
 *
 * PARAMS: None
 *
 *
 *    NOTES: Used to Set a Pairwise Master Key (PMK) that can be used by
 *        the Zero G chip to establish a security association.  The key data
 *        is expected to be exactly 32 bytes long.  The ssid is between 0 and
 *        32 bytes long.
 *****************************************************************************/
extern tZGReturnStatus ZGSetPMKKey(tZGVoidInput);

extern tZGReturnStatus ZGSetWEPKeys(tZGVoidInput);

/*****************************************************************************
 * FUNCTION: ZGMACIFSetPowerSaveMode
 *
 * RETURNS: kZGMACSuccess or kZGMACFailure
 *
 * PARAMS:
 *        tZGMACPsPwrMode mode - The desired power save mode to use on the ZG
 *            chip.
 *
 *
 *    NOTES: 802.11 chipsets have 2 well known operational power modes.  Active
 *        power mode is defined as the radio always on either transmitting or
 *        receiving, meaning that when it isn't transmitting then it is trying
 *        to receive.  Power save mode is defined as operating with the radio
 *        turned off when there is nothing to transmit and only turning the
 *        radio receiver on when required.  The power save mode is a mode that
 *        requires interaction with an Access Point.  The access point is
 *        notified via a packet from the Station that it is entering into
 *        power save mode. As a result the access point is required to buffer
 *        any packets that are destined for the Station until the Station
 *        announces that it is ready to once again receive packets.  The duration
 *        that a Station is allowed to remain in this mode is limited and is
 *        typically 10 times the beacon interval of the Access point.  If the
 *        host is expecting packets from the network it should operate in Active
 *        mode.  If however power saving is critical and packets are not expected
 *        then the host should consider operating in power save mode.  Due to
 *        the nature of Access points not all behaving the same, there is the
 *        possibility that an Access point will invalidate a Stations connection
 *        if it has not heard from the Station over a given time period. For this
 *        reason power save mode should be used with caution.
 *****************************************************************************/
extern tZGReturnStatus ZGSetPowerSaveMode(tZGPwrModeReqPtr pReq);


/*****************************************************************************
 * FUNCTION: ZGCalcPSK
 *
 * RETURNS: kZGSuccess or kZGFailure
 *
 * PARAMS:
 *          None
 *
 *    NOTES: With the advent of WPA and WPA2 802.11 connections are made secure
 *           using schemes that can require a Pre-shared key.  This key is
 *           calculated using the SSID network name combined with a secret
 *           passphrase that is user readable.  These two strings are used as
 *           input into a computationally expensive calculation which generates
 *           a 32 byte key.  The ZG chip is able to perform this calcuation
 *           when given the SSID and passphrase. ZGMACIFCalcPSK provides the
 *           interface for Host software to request such a calculation.  Be
 *           warned that the ZG chip can require 60 seconds or more to complete
 *           the calculation. Following successful completion of the calculation
 *           the host can then submit the PSK using the ZGMACIFSetPMKKey function.
 *****************************************************************************/
extern tZGReturnStatus ZGCalcPSK(tZGVoidInput);

extern tZGReturnStatus SendManagementMsg(tZGU16 len, tZGU8 type, tZGU8 info);

extern tZGReturnStatus ZGDataSendUntampered(tZGTxUntamperedFrameReqPtr pReq, tZGU16 len);

extern tZGVoidReturn ZGProcess(tZGVoidInput);

extern tZGU16 ZGGetNumWriteBytes(tZGU16 testLimit);

extern tZGU16 ZGGetTCBSize(void);

/***************************************/
/* END Interface function Prototypes   */
/***************************************/

#endif /*_ZGDRIVERIFACEAPP_H_ */
