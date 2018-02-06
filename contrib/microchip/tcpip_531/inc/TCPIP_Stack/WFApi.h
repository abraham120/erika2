/******************************************************************************

 MRF24WB0M Driver API Interface
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFApi.h
 Dependencies:	TCP/IP Stack header files
 Processor:		PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 Compiler:		Microchip C32 v1.10b or higher
				Microchip C30 v3.22 or higher
				Microchip C18 v3.34 or higher
 Company:		Microchip Technology, Inc.

 Software License Agreement

 Copyright (C) 2002-2010 Microchip Technology Inc.  All rights reserved.

 Microchip licenses to you the right to use, modify, copy, and distribute:
 (i)  the Software when embedded on a Microchip microcontroller or digital 
      signal controller product ("Device") which is integrated into 
      Licensee's product; or
 (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
      ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device used in 
	  conjunction with a Microchip ethernet controller for the sole purpose 
	  of interfacing with the ethernet controller.

 You should refer to the license agreement accompanying this Software for 
 additional information regarding your rights and obligations.

 THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY INCIDENTAL,
 SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST
 OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS BY
 THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS
 FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON
 THE BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR
 OTHERWISE.


 Author				Date		Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KH                 27 Jan 2010 Created for MRF24WB0M
******************************************************************************/

#ifndef __WF_API_H_
#define __WF_API_H_

#include "GenericTypeDefs.h"


/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/
/*-----------------------------*/
/* WiFi Driver Version Number  */
/*-----------------------------*/
#define WF_HOST_DRIVER_VERSION_NUMBER    "2.5.2"

/* API defines */
#define WF_MAX_NUM_CHANNELS             (14)
#define WF_MAX_NUM_CONNECTION_PROFILES  (8)
#define WF_CP_LIST_LENGTH               (8)
#define WF_MAX_SSID_LENGTH              (32)
#define WF_BSSID_LENGTH                 (6)
#define WF_RETRY_FOREVER                (255)
#define WF_CHANNEL_LIST_LENGTH          (14)
#define WF_MAX_SECURITY_KEY_LENGTH      (64)
#define WF_NUM_THROTTLE_TABLE_ROWS      (4)

#define WF_MIN_NUM_CPID                 (1)
#define WF_MAX_NUM_CPID                 (8)

#define WF_NO_CPID_ACTIVE               (0)

#define WF_RTS_THRESHOLD_MAX            (2347) /* maximum RTS threshold size in bytes */

#define WF_MAX_NUM_RATES                (8)

/* Key size defines */
#define WF_MIN_WPA_PASS_PHRASE_LENGTH         (8)
#define WF_MIN_WPA_PASS_PHRASE_LENGTH         (8)
#define WF_MAX_WPA_PASS_PHRASE_LENGTH        (64)
#define WF_MAX_WPA2_PASS_PHRASE_LENGTH       (64)
#define WF_WPA_KEY_LENGTH                    (32)
#define WF_WPA2_KEY_LENGTH                   (32)

/*------------------------------------------------------------------------------*/
/* These are error codes returned in the result field of a management response. */
/*------------------------------------------------------------------------------*/
#define WF_SUCCESS                                              ((UINT16)1)
#define WF_ERROR_INVALID_SUBTYPE                                ((UINT16)2)
#define WF_ERROR_OPERATION_CANCELLED                            ((UINT16)3)
#define WF_ERROR_FRAME_END_OF_LINE_OCCURRED                     ((UINT16)4)
#define WF_ERROR_FRAME_RETRY_LIMIT_EXCEEDED                     ((UINT16)5)
#define WF_ERROR_EXPECTED_BSS_VALUE_NOT_IN_FRAME                ((UINT16)6)
#define WF_ERROR_FRAME_SIZE_EXCEEDS_BUFFER_SIZE                 ((UINT16)7)
#define WF_ERROR_FRAME_ENCRYPT_FAILED                           ((UINT16)8)
#define WF_ERROR_INVALID_PARAM                                  ((UINT16)9)
#define WF_ERROR_AUTH_REQ_ISSUED_WHILE_IN_AUTH_STATE            ((UINT16)10)
#define WF_ERROR_ASSOC_REQ_ISSUED_WHILE_IN_ASSOC_STATE          ((UINT16)11)
#define WF_ERROR_INSUFFICIENT_RESOURCES                         ((UINT16)12)
#define WF_ERROR_TIMEOUT_OCCURRED                               ((UINT16)13)
#define WF_ERROR_BAD_EXCHANGE_ENCOUNTERED_IN_FRAME_RECEPTION    ((UINT16)14)
#define WF_ERROR_AUTH_REQUEST_REFUSED                           ((UINT16)15)
#define WF_ERROR_ASSOCIATION_REQUEST_REFUSED                    ((UINT16)16)
#define WF_ERROR_PRIOR_MGMT_REQUEST_IN_PROGRESS                 ((UINT16)17)
#define WF_ERROR_NOT_IN_JOINED_STATE                            ((UINT16)18)
#define WF_ERROR_NOT_IN_ASSOCIATED_STATE                        ((UINT16)19)
#define WF_ERROR_NOT_IN_AUTHENTICATED_STATE                     ((UINT16)20)
#define WF_ERROR_SUPPLICANT_FAILED                              ((UINT16)21)
#define WF_ERROR_UNSUPPORTED_FEATURE                            ((UINT16)22)
#define WF_ERROR_REQUEST_OUT_OF_SYNC                            ((UINT16)23)
#define WF_ERROR_CP_INVALID_ELEMENT_TYPE                        ((UINT16)24)
#define WF_ERROR_CP_INVALID_PROFILE_ID                          ((UINT16)25)
#define WF_ERROR_CP_INVALID_DATA_LENGTH                         ((UINT16)26)
#define WF_ERROR_CP_INVALID_SSID_LENGTH                         ((UINT16)27)
#define WF_ERROR_CP_INVALID_SECURITY_TYPE                       ((UINT16)28)
#define WF_ERROR_CP_INVALID_SECURITY_KEY_LENGTH                 ((UINT16)29)
#define WF_ERROR_CP_INVALID_WEP_KEY_ID                          ((UINT16)30)
#define WF_ERROR_CP_INVALID_NETWORK_TYPE                        ((UINT16)31)
#define WF_ERROR_CP_INVALID_ADHOC_MODE                          ((UINT16)32)
#define WF_ERROR_CP_INVALID_SCAN_TYPE                           ((UINT16)33)
#define WF_ERROR_CP_INVALID_CP_LIST                             ((UINT16)34)
#define WF_ERROR_CP_INVALID_CHANNEL_LIST_LENGTH                 ((UINT16)35)  
#define WF_ERROR_NOT_CONNECTED                                  ((UINT16)36)
#define WF_ERROR_ALREADY_CONNECTING                             ((UINT16)37)
#define WF_ERROR_DISCONNECT_FAILED                              ((UINT16)38)
#define WF_ERROR_NO_STORED_BSS_DESCRIPTOR                       ((UINT16)39)
#define WF_ERROR_INVALID_MAX_POWER                              ((UINT16)40)

/*---------------------------------------------------------------------*/
/* Used for eventNotificationField bit mask in tWFCAElements structure */
/*---------------------------------------------------------------------*/
#define WF_NOTIFY_CONNECTION_ATTEMPT_SUCCESSFUL     ((UINT8)(0x01))  
#define WF_NOTIFY_CONNECTION_ATTEMPT_FAILED         ((UINT8)(0x02))  
#define WF_NOTIFY_CONNECTION_TEMPORARILY_LOST       ((UINT8)(0x04))  
#define WF_NOTIFY_CONNECTION_PERMANENTLY_LOST       ((UINT8)(0x08))  
#define WF_NOTIFY_CONNECTION_REESTABLISHED          ((UINT8)(0x10))  
#define WF_NOTIFY_ALL_EVENTS                        ((UINT8)(0x1f))

/*------------------------------------------------------------------------------------------*/
/* Multicast Filter ID's                                                                    */
/* Infrastructure can use 2,3,4,5 and AdHoc can only use 4,5.  Use 4,5 which works for both */
/*------------------------------------------------------------------------------------------*/
#define WF_MULTICAST_FILTER_1       (4) 
#define WF_MULTICAST_FILTER_2       (5)

#define WF_SCAN_ALL ((UINT8)(0xff))
/*
*********************************************************************************************************
*                                           DATA TYPES                               
*********************************************************************************************************
*/

/*----------------------------------------------------------------------------*/
/* Events that can be invoked in WF_ProcessEvent().  Note that the            */
/* connection events are optional, all other events the app must be notified. */
/*----------------------------------------------------------------------------*/
typedef enum
{
    WF_EVENT_CONNECTION_SUCCESSFUL          = 1,   /* Connection attempt to network successful            */
    WF_EVENT_CONNECTION_FAILED              = 2,   /* Connection attempt failed                           */


    WF_EVENT_CONNECTION_TEMPORARILY_LOST    = 3,   /* Connection lost; MRF24WB0M attempting to reconnect     */
    WF_EVENT_CONNECTION_PERMANENTLY_LOST    = 4,   /* Connection lost; MRF24WB0M no longer trying to connect */  
    WF_EVENT_CONNECTION_REESTABLISHED       = 5,
    
    WF_EVENT_FLASH_UPDATE_SUCCESSFUL        = 6,   /* Update to FLASH successful                          */
    WF_EVENT_FLASH_UPDATE_FAILED            = 7,   /* Update to FLASH failed                              */

 

    WF_EVENT_KEY_CALCULATION_COMPLETE       = 8,   /* Key calculation has completed                       */

    WF_EVENT_SCAN_RESULTS_READY             = 9,   /* scan results are ready                              */ 
    WF_EVENT_IE_RESULTS_READY               = 10,  /* IE data ready                                       */
    

    WF_EVENT_RX_PACKET_RECEIVED             = 11   /* Rx data packet has been received by MRF24WB0M          */
    
} tWFEvents;

typedef struct WFMacStatsStruct 
{
    /**
      Number of frames received with the Protected Frame subfield of the Frame 
      Control field set to zero and the value of dot11ExcludeUnencrypted causes 
      that frame to be discarded.
      */
    UINT32 MibWEPExcludeCtr;    
    UINT32 MibTxBytesCtr; // Total number of Tx bytes that have been transmitted

    /**
      Number of frames successfully transmitted that had the multicast bit set 
      in the destination MAC address.
      */
	UINT32 MibTxMulticastCtr;
    /**
      Number of Tx frames that failed due to the number of transmits exceeding 
      the retry count.
      */
	UINT32 MibTxFailedCtr;
	UINT32 MibTxRtryCtr; // Number of times a transmitted frame needed to be retried 
	UINT32 MibTxMultRtryCtr; // Number of times a frame was successfully transmitted after more than one retransmission.
	UINT32 MibTxSuccessCtr; // Number of Tx frames successfully transmitted.
    UINT32 MibRxDupCtr; // Number of frames received where the Sequence Control field indicates a duplicate.
	UINT32 MibRxCtsSuccCtr; // Number of CTS frames received in response to an RTS frame.
	UINT32 MibRxCtsFailCtr; // Number of times an RTS frame was not received in response to a CTS frame.
	UINT32 MibRxAckFailCtr; // Number of times an Ack was not received in response to a Tx frame.
	UINT32 MibRxBytesCtr; // Total number of Rx bytes received.
	UINT32 MibRxFragCtr; // Number of successful received frames (management or data)
	UINT32 MibRxMultCtr; // Number of frames received with the multicast bit set in the destination MAC address.
	UINT32 MibRxFCSErrCtr; // Number of frames received with an invalid Frame Checksum (FCS).

    /**
      Number of frames received where the Protected Frame subfield of the Frame Control Field is set to 
      one and the WEPOn value for the key mapped to the transmitter�s MAC address indicates the frame 
      should not have been encrypted.
      */
	UINT32 MibRxWEPUndecryptCtr;
	UINT32 MibRxFragAgedCtr; // Number of times that fragments �aged out�, or were not received in the allowable time.
	UINT32 MibRxMICFailureCtr; // Number of MIC failures that have occurred.
} tWFMacStats;


/*-------------------------------------------------------*/
/* Security Type defines                                 */
/* Used in WF_CPSet/GetSecurityType WF_CPSet/GetElements */
/*-------------------------------------------------------*/
#define WF_SECURITY_OPEN                         (0)
#define WF_SECURITY_WEP_40                       (1)
#define WF_SECURITY_WEP_104                      (2)
#define WF_SECURITY_WPA_WITH_KEY                 (3)
#define WF_SECURITY_WPA_WITH_PASS_PHRASE         (4)
#define WF_SECURITY_WPA2_WITH_KEY                (5)
#define WF_SECURITY_WPA2_WITH_PASS_PHRASE        (6)
#define WF_SECURITY_WPA_AUTO_WITH_KEY            (7)
#define WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE    (8)

/*---------------------------------------------------------------------*/
/* Network Type defines                                                */
/* Used in WF_CPSet/GetNetworkType, WF_CPSetElements, WF_CPGetElements */
/*---------------------------------------------------------------------*/
typedef enum
{
    WF_INFRASTRUCTURE = 1,
    WF_ADHOC          = 2
} tWFNetworkType;

/*--------------------------------------------------------*/
/* Ad Hoc behavior defines                                */
/* Used in WF_CPSet/GetAdhocBehavor, WF_CPSet/GetElements */
/*--------------------------------------------------------*/
typedef enum
{
    WF_ADHOC_CONNECT_THEN_START = 0,
    WF_ADHOC_CONNECT_ONLY       = 1,
    WF_ADHOC_START_ONLY         = 2
} tWFAdhocBehavior;

/*----------------------------------------------------*/
/* Scan type defines                                  */
/* Used in WF_CASet/GetScanType, WF_CASet/GetElements */
/*----------------------------------------------------*/
typedef enum
{
    WF_ACTIVE_SCAN  = 1,
    WF_PASSIVE_SCAN = 2 
} tWFScanTypes;

/*-----------------------------------------------------------------------------------------*/
/* Beacon Timeout and Deauth defines                                                       */
/* Used in WF_CASet/GetBeaconTimeoutAction, WF_CASet/GetDeauthAction, WF_CASet/GetElements */
/*-----------------------------------------------------------------------------------------*/
typedef enum
{
    WF_DO_NOT_ATTEMPT_TO_RECONNECT = 0,
    WF_ATTEMPT_TO_RECONNECT        = 1 
} tWFConnectionLossActions;

typedef enum
{
    WF_DISABLED = 0,
    WF_ENABLED  = 1
} tWFEnableDisable;

/* eventInfo defines for WF_ProcessEvent(), case WF_EVENT_CONNECTION_FAILED */
/* Also value for index 3 of WF_CONNECTION_FAILED_EVENT_SUBTYPE */
typedef enum
{
    WF_JOIN_FAILURE                         = 2,
    WF_AUTHENTICATION_FAILURE               = 3,
    WF_ASSOCIATION_FAILURE                  = 4,
    WF_WEP_HANDSHAKE_FAILURE                = 5,
    WF_PSK_CALCULATION_FAILURE              = 6,
    WF_PSK_HANDSHAKE_FAILURE                = 7,
    WF_ADHOC_JOIN_FAILURE                   = 8,
    WF_SECURITY_MISMATCH_FAILURE            = 9,
    WF_NO_SUITABLE_AP_FOUND_FAILURE         = 10,
    WF_RETRY_FOREVER_NOT_SUPPORTED_FAILURE  = 11

} tWFConnectionFailureCodes;

/* eventInfo defines for WF_ProcessEvent(), case WF_EVENT_CONNECTION_TEMPORARILY_LOST */
typedef enum
{
    WF_BEACON_TIMEOUT        = 1,
    WF_DEAUTH_RECEIVED       = 2,
    WF_DISASSOCIATE_RECEIVED = 3
} tWFConnectionLostCodes;    

/* Tx Data Rates */
typedef enum
{
    WF_ONE_MBIT_TX_RATE = 0,
    WF_TWO_MBIT_TX_RATE = 1
} tWFTxDataRates;    

/* WiFi Device Types */
typedef enum 
{
    MRF24WB0M_DEVICE = 1
} tWFDeviceTypes;    

/* Regional Domains */
typedef enum
{
    WF_DOMAIN_FCC      = 0,           /* Available Channels: 1 - 11 */
    WF_DOMAIN_IC       = 1,           /* Available Channels: 1 - 11 */
    WF_DOMAIN_ETSI     = 2,           /* Available Channels: 1 - 13 */
    WF_DOMAIN_SPAIN    = 3,           /* Available Channels: 1 - 13 */
    WF_DOMAIN_FRANCE   = 4,           /* Available Channels: 1 - 13 */
    WF_DOMAIN_JAPAN_A  = 5,           /* Available Channels: 14     */
    WF_DOMAIN_JAPAN_B  = 6            /* Available Channels: 1 - 13 */
} tWFRegDomain;

/* Power save states */
typedef enum
{
    WF_PS_HIBERNATE             = 1,
    WF_PS_PS_POLL_DTIM_ENABLED  = 2,
    WF_PS_PS_POLL_DTIM_DISABLED = 3,
    WF_PS_OFF                   = 4
} tWFPowerSaveState;    

typedef enum
{
    WF_LOW  = 0,
    WF_HIGH = 1
} tWFPinLevel;    

/*-----------------------------------------------------------------------*/
/* defines used for the p_currentCpID value in WF_CMGetConnectionState() */
/*-----------------------------------------------------------------------*/
#define WF_CURRENT_CPID_NONE    (0)
#define WF_CURRENT_CPID_LIST    (0xff)

/* Connection States */
typedef enum
{
	WF_CSTATE_NOT_CONNECTED                 = 1,
	WF_CSTATE_CONNECTION_IN_PROGRESS        = 2,
	WF_CSTATE_CONNECTED_INFRASTRUCTURE      = 3,
	WF_CSTATE_CONNECTED_ADHOC               = 4,
	WF_CSTATE_RECONNECTION_IN_PROGRESS      = 5,
	WF_CSTATE_CONNECTION_PERMANENTLY_LOST   = 6
} tWFConnectionStates;    

/* eventInfo define for WF_ProcessEvent() when no additional info is supplied */
#define WF_NO_ADDITIONAL_INFO       ((UINT16)0xffff)

/*-----------------------------*/
/* Connection Profile Elements */
/*-----------------------------*/

// Connection profile elements structure
typedef struct WFCPElementsStruct
{
    /** 
      SSID, which must be less than or equal to 32 characters.  Set to all 0�s 
      if not being used.  If ssidLength is 0 this field is ignored.  If SSID is 
      not defined then the MRF24WB0M, when using this profile to connect, will 
      scan all channels within its regional domain.

      Default: SSID not used. 
      */
    UINT8  ssid[WF_MAX_SSID_LENGTH];
    /**
      Basic Service Set Identifier, always 6 bytes.  This is the 48-bit MAC of 
      the SSID.  It is an optional field that can be used to specify a specific 
      SSID if more than one AP exists with the same SSID.  This field can also 
      be used in lieu of the SSID.  

      Set each byte to 0xFF if BSSID is not going to be used.
      Default: BSSID not used (all FF�s)
      */
    UINT8  bssid[WF_BSSID_LENGTH];
    /**
      Number of ASCII bytes in ssid.  Set to 0 is SSID is not going to be used.

      Default: 0
      */
    UINT8  ssidLength;
    /**
      Designates the desired security level for the connection.  Choices are:
      <table>
        WF_SECURITY_OPEN                        No security encryption used.
        WF_SECURITY_WEP_40                      Use WEP security.  
                                                WEP key, using four 5-byte keys will be provided in securityKey.
                                                 Note that only open authentication is supported for WEP.
        WF_SECURITY_WEP_104                     Use WEP security.  
                                                 WEP key, using four 13-byte keys will be provided in securityKey.
                                                 Note that only open authentication is supported for WEP.
        WF_SECURITY_WPA_WITH_KEY                Use WPA security.  
                                                 Binary PSK (Pre-shared Key) key will be provided in securityKey.
        WF_SECURITY_WPA_WITH_PASS_PHRASE        Use WPA security.  
                                                 ASCII WPA passphrase will be provided in securityKey and, 
                                                 after a call to WF_CMConnect(), the MRF24WB0M will calculate 
                                                 the PSK key (which can take up to 30 seconds).
        WF_SECURITY_WPA2_WITH_KEY               Use WPA-2 security.  
                                                 Binary WPA-2 key will be provided in securityKey.
        WF_SECURITY_WPA2_WITH_PASSPHRASE        Use WPA-2 security.
                                                 ASCII WPA-2 passphrase will be provided in securityKey and, 
                                                 after a call to WF_CMConnect(), the MRF24WB0M will calculate 
                                                 the PSK key (which can take up to 30 seconds).
        WF_SECURITY_WPA_AUTO_WITH_KEY           Same as WF_SECURITY_WPA_WITH_KEY or WF_SECURITY_WPA2_WITH_KEY 
                                                 except connection manager will connect to the AP using highest 
                                                 level security the AP supports (WPA or WPA2).
        WF_SECURITY_WPA_AUTO_WITH_PASSPHRASE    Same as WF_SECURITY_WPA_WITH_PASS_PHRASE or 
                                                 WF_SECURITY_WPA2_WITH_PASS_PHRASE except connection manager 
                                                 will connect to the AP using highest level security the AP 
                                                 supports (WPA or WPA2).
      </table>
      Default: WF_SECURITY_OPEN
      */
    UINT8  securityType;
    /**
      Set to NULL if securityType is WF_SECURITY_OPEN.  If securityKeyLength is 0 
      this field is ignored.
      <table>
        WEP Keys        If using WEP this field must contain 4 keys.  Each key must be 
                         either 5 bytes in length (if securityType is WF_SECURITY_WEP_40) 
                         or 13 bytes in length  (if securityType is WF_SECURITY_WEP_104).  
                         The keys must be contiguous within this field.  For example, if 
                         using 5 bytes keys the first key starts at index 0, the second 
                         key at index 5, the third key at index 10, and the last key at 
                         index 15.  Unused keys should be set to all 0�s.
        WPA/WPA2 Keys   If using WPA or WPA2 you can provide the actual binary key or 
                         ASCII passphrase used to generate a key.  [64 byte array covers 
                         all cases of keys or passphrases].  If using this field for a 
                         security passphrase the MRF24WB0M will need to calculate the 
                         binary key after the call to WF_CMConnect() � this can add about 
                         30 seconds to the connection time.
      </table>
      Default: No security key defined
      */
    UINT8  securityKey[WF_MAX_SECURITY_KEY_LENGTH];
    /**
      Number of bytes used in the securityKey.  Set to 0 if securityType is WF_SECURITY_OPEN.
      <table>
        WEP Keys        If securityType is WF_SECURITY_WEP_40 or WF_SECURITY_WEP_104 
                         then this field is the length of the four WEP keys.

                         Range is  
                         20 if securityType is WF_SECURITY_WEP_40 (four 5-byte keys),
                         52 if securityType is WF_SECURITY_WEP_104 (four 13-byte keys)
        WPA/WPA2 Keys   If securityType is one of the WPA or WPA2 choices then this 
                         field is the number of bytes in the binary key or the 
                         passphrase, whichever is being used.

      </table>
      Default: 0
      */
    UINT8  securityKeyLength;
    /**
      This field is only used if securityType is WF_SECURITY_WEP.  This field 
      designates which of the four WEP keys defined in securityKey to use when 
      connecting to a WiFi network.  The range is 0 thru 3, with the default
      being 0.
      */
    UINT8  wepDefaultKeyId;
    /**
      WF_INFRASTRUCTURE  or WF_ADHOC

      Default: WF_INFRASTRUCTURE  
      */
    UINT8  networkType;
    /**
      Only applicable if networkType is WF_ADHOC.  Configures Adhoc behavior.  Choices are:
      <table>
        WF_ADHOC_CONNECT_THEN_START     Attempt to connect to existing network.  
                                         If that fails, then start a network.
        WF_ADHOC_CONNECT_ONLY           Connect only to an existing network.  
                                         Do not start a network.
        WF_ADHOC_START_ONLY             Only start a network.
      </table>
      Default: WF_ADHOC_CONNECT_THEN_START
      */
    UINT8  adHocBehavior;
} tWFCPElements;

/*-------------------------------*/
/* Connection Algorithm Elements */
/*-------------------------------*/
typedef struct WFCAElementsStruct
{
    /**
      This parameter is only used when PS Poll mode is enabled.  See 
      WF_PsPollEnable().  Number of 100ms intervals between instances when the 
      MRF24WB0M wakes up to received buffered messages from the network.  Range
      is from 1 (100ms) to 6553.5 sec (~109 min).

      Note that the 802.11 standard defines the listen interval in terms of 
      Beacon Periods, which are typically 100ms.  If the MRF24WB0M is communicating 
      to a network with a network that has Beacon Periods that is not 100ms it 
      will round up (or down) as needed to match the actual Beacon Period as 
      closely as possible.

      Important Note: If the listenInterval is modified while connected to a 
      network the MRF24WB0M will automatically reconnect to the network with the 
      new Beacon Period value.  This may cause a temporary loss of data packets.
      */
    UINT16  listenInterval;
    /**
      WF_ACTIVE_SCAN (Probe Requests sent out) or WF_PASSIVE_SCAN (listen only)

      Default: WF_ACTIVE_SCAN
      */
    UINT8   scanType;
    /**
      Specifies RSSI restrictions when connecting.  This field is only used if:
      1.  The Connection Profile has not defined a SSID or BSSID, or  
      2.  An SSID is defined in the Connection Profile and multiple AP�s are discovered with the same SSID.
    
      <table>
        0       Connect to the first network found
        1-254   Only connect to a network if the RSSI is greater than or equal to the specified value.
        255     Connect to the highest RSSI found (default)
      </table>
      */
    UINT8   rssi;
    /**
      <b>Note: Connection Profile lists are not yet supported.  This array should be set to all FF�s.</b>
      */
    UINT8   connectionProfileList[WF_CP_LIST_LENGTH];
    /**
      This field is used to specify the number of retries for the single 
      connection profile before taking the connection lost action.

      Range 1 to 254 or WF_RETRY_FOREVER (255)

      Default is 3
      */
    UINT8   listRetryCount;
    /**
      There are several connection-related events that can occur.  The Host has 
      the option to be notified (or not) when some of these events occur.  This 
      field controls event notification for connection-related events.
      <table>
        Bit 7   Bit 6   Bit 5   Bit 4   Bit 3   Bit 2   Bit 1   Bit 0
        -----   -----   -----   -----   -----   -----   -----   -----
        Not     Not     Not     Event   Event   Event   Event   Event
         used    used    used    E       D       C       B       A
      </table>
      The defines for each bit are shown below.
      <table>
        Event Code  #define
        ----------  -------
        A           WF_NOTIFY_CONNECTION_ATTEMPT_SUCCESSFUL  
        B           WF_NOTIFY_CONNECTION_ATTEMPT_FAILED
        C           WF_NOTIFY_CONNECTION_TEMPORARILY_LOST
        D           WF_NOTIFY_CONNECTION_PERMANENTLY_LOST
        E           WF_NOTIFY_CONNECTION_REESTABLISHED
      </table>
      If a bit is set, then the host will be notified if the associated event 
      occurs.  If the bit is not set then the host will not be notified if the 
      associated event occurs.   A #define, WF_NOTIFY_ALL_EVENTS, exists as a 
      shortcut to allow notification for all events. 

      Note that if an event is not in the above bit mask the application will 
      always be notified of the event via the call to WF_ProcessEvent().

      Default: WF_NOTIFY_ALL_EVENTS
      */
    UINT8   eventNotificationAction;
    /**
      Specifies the action the Connection Manager should take if a Connection is 
      lost due to a Beacon Timeout.  
      If this field is set to WF_ATTEMPT_TO_RECONNECT then the number of attempts 
      is limited to the value in listRetryCount.

      Choices are:
      WF_ATTEMPT_TO_RECONNECT or WF_DO_NOT_ATTEMPT_TO_RECONNECT

      Default: WF_ATTEMPT_TO_RECONNECT
      */
    UINT8   beaconTimeoutAction;
    /**
      Designates what action the Connection Manager should take if it receives a 
      Deauthentication message from the AP.  

      If this field is set to WF_ATTEMPT_TO_RECONNECT then the number of attempts 
      is limited to the value in listRetryCount.

      Choices are:
      WF_ATTEMPT_TO_RECONNECT or WF_DO_NOT_ATTEMPT_TO_RECONNECT

      Default: WF_ATTEMPT_TO_RECONNECT
      */
    UINT8   deauthAction;
    /**
      List of one or more channels that the MRF24WB0M should utilize when 
      connecting or scanning.  If numChannelsInList is set to 0 then this 
      parameter should be set to NULL.

      Default: All valid channels for the regional domain of the MRF24WB0M (set 
      at manufacturing).
    */
    UINT8   channelList[WF_CHANNEL_LIST_LENGTH];
    /**
      Number of channels in channelList.  If set to 0 then the MRF24WB0M will 
      populate the list with all valid channels for the regional domain.

      Default: The number of valid channels for the regional domain of the 
      MRF24WB0M (set at manufacturing).
      */
    UINT8   numChannelsInList;
    /**
      Specifies the number of beacons that can be missed before the action 
      described in beaconTimeoutAction is taken.

      <table>
        0       * Not monitor the beacon timeout condition
                 * Will not indicate this condition to Host
        1-255   Beacons missed before disconnect event occurs and beaconTimeoutAction 
                 occurs.  If enabled, host will receive an event message indicating 
                 connection temporarily or permanently lost, and if retrying, a 
                 connection successful event.
      </table>
      Default: 0 (no monitoring or notification of beacon timeout)
      */
    UINT8   beaconTimeout;
    /**
      The number of times to scan a channel while attempting to find a particular 
      access point.

      Default: 1
      */
    UINT8   scanCount;
    UINT8   pad1; 
    /**
      The minimum time (in milliseconds) the connection manager will wait for a 
      probe response after sending a probe request.  If no probe responses are 
      received in minChannelTime then the connection manager will go on to the 
      next channel, if any are left to scan, or quit.

      Default: 200ms
      */
    UINT16  minChannelTime;
    /**
      If a probe response is received within minChannelTime then the connection 
      manager will continue to collect any additional probe responses up to 
      maxChannelTime before going to the next channel in the channelList.  Units 
      are in milliseconds.

      Default: 400ms
      */
    UINT16  maxChannelTime;
    /**
      The number of microseconds to delay before transmitting a probe request 
      following the channel change event.

      Default: 20us
    */
    UINT16  probeDelay;
} tWFCAElements;

/*-------------------*/
/* Tx Throttle Table */
/*-------------------*/
typedef struct WFThrottleTableStruct
{
    UINT8  dataRate[WF_NUM_THROTTLE_TABLE_ROWS];  // WF_ONE_MBIT_TX_RATE or WF_TWO_MBIT_TX_RATE
    INT8   txPower[WF_NUM_THROTTLE_TABLE_ROWS];   // -10dB to +10dB
} tWFThrottleTable;

/*--------------------------*/
/* used in WF_GetDeviceInfo */
/*--------------------------*/
typedef struct tWFDeviceInfoStruct
{
    UINT8  deviceType;    /* MRF24WB0M_DEVICE_TYPE  */
    UINT8  romVersion;    /* ROM version number     */
    UINT8  patchVersion;  /* Patch version number   */
} tWFDeviceInfo;

/*--------------*/
/* Scan Results */
/*--------------*/
typedef struct
{
    UINT8      bssid[WF_BSSID_LENGTH]; // Network BSSID value
    UINT8      ssid[WF_MAX_SSID_LENGTH]; // Network SSID value

    /**
      Access point configuration
      <table>
        Bit 7       Bit 6       Bit 5       Bit 4       Bit 3       Bit 2       Bit 1       Bit 0
        -----       -----       -----       -----       -----       -----       -----       -----
        WPA2        WPA         Preamble    Privacy     Reserved    Reserved    Reserved    IE
      </table>
      
      <table>
      IE        1 if AP broadcasting one or more Information Elements, else 0
      Privacy   0 : AP is open (no security)
                 1: AP using security,  if neither WPA and WPA2 set then security is WEP.
      Preamble  0: AP transmitting with short preamble
                 1: AP transmitting with long preamble
      WPA       Only valid if Privacy is 1.
                 0: AP does not support WPA
                 1: AP supports WPA
      WPA2      Only valid if Privacy is 1.
                 0: AP does not support WPA2
                 1: AP supports WPA2
      </table>
      */
    UINT8      apConfig;
    UINT8      reserved;
    UINT16     beaconPeriod; // Network beacon interval          
    UINT16     atimWindow; // Only valid if bssType = WF_INFRASTRUCTURE

    /**
      List of Network basic rates.  Each rate has the following format:
      
	  Bit 7
      * 0 � rate is not part of the basic rates set
      * 1 � rate is part of the basic rates set

	  Bits 6:0 
      Multiple of 500kbps giving the supported rate.  For example, a value of 2 
      (2 * 500kbps) indicates that 1mbps is a supported rate.  A value of 4 in 
      this field indicates a 2mbps rate (4 * 500kbps).
      */
    UINT8      basicRateSet[WF_MAX_NUM_RATES]; 
    UINT8      rssi; // Signal strength of received frame beacon or probe response
    UINT8      numRates; // Number of valid rates in basicRates
    UINT8      DtimPeriod; // Part of TIM element
    UINT8      bssType; // WF_INFRASTRUCTURE or WF_ADHOC
    UINT8      channel; // Channel number
    UINT8      ssidLen; // Number of valid characters in ssid

} tWFScanResult; 

#if defined(WF_CM_DEBUG)
typedef struct
{
    UINT8     byte[12*4];  // Currently, CM has 12 states; 4-byte for each state info entry.
} tWFCMInfoFSMStats;
#endif

/*------------------------*/
/* if asserts are enabled */
/*------------------------*/
#if defined(WF_DEBUG)

    /*---------------------------------------------------------*/    
    /* Module numbers that will be used in the WF_ASSERT macro */
    /*---------------------------------------------------------*/
    typedef enum 
    {
        WF_MODULE_MAIN_DEMO                  = 0,   /* MainDemo.c               */
        WF_MODULE_WF_CONFIG                  = 1,   /* WF_Config.c              */
        WF_MODULE_WF_EINT                    = 2,   /* WF_Eint.c                */
        WF_MODULE_WF_SPI                     = 3,   /* WF_Spi.c                 */
        WF_MODULE_WF_MAC                     = 4,   /* WFMac.c                  */
        WF_MODULE_WF_PARAM_MSG               = 5,   /* WFParamMsg.c             */
        WF_MODULE_WF_CONNECTION_PROFILE      = 6,   /* WFConnectionProfile.c    */
        WF_MODULE_WF_CONNECTION_ALGORITHM    = 7,   /* WFConnectionAlgorithm.c  */
        WF_MODULE_WF_CONNECTION_MANAGER      = 8,   /* WFConnectionManager.c    */
        WF_MODULE_WF_DRIVER_COM              = 9,   /* WFDriverCom.c            */
        WF_MODULE_WF_INIT                    = 10,  /* WFInit.c                 */
        WF_MODULE_WF_DRIVER_RAW              = 11,  /* WFDriverRaw.c            */
        WF_MODULE_WF_MGMT_MSG                = 12,  /* WFMgmtMsg.c              */
        WF_MODULE_MGMT_MSG_TEST              = 13,  /* WFMgmtMsgTest.c          */
        WF_MODULE_WF_TX_POWER                = 14,  /* WFTxPower.c              */
        WF_MODULE_WF_POWER_SAVE              = 15,  /* WFPowerSave.c            */
        WF_MODULE_EVENT_HANDLER              = 16,  /* WFEventHandler.c         */
        WF_MODULE_WF_SCAN                    = 17,  /* WFScan.c                 */
        WF_MODULE_WF_DATA_TX_RX              = 18,  /* WFDataTxRx               */
        
        WF_MODULE_IPERF_APP                  = 100, /* IperfApp.c               */
        WF_MODULE_HOST_BRIDGE                = 101, /* WFHostBridge.c           */
        WF_MODULE_WF_IPERF_CLIENT            = 102, /* WF_iperfClient.c         */
        WF_MODULE_WF_IPERF_SERVER            = 103, /* WF_iperfServer.c         */
        WF_MODULE_WF_IPERF_COMMON            = 104  /* WF_iperfCommon.c         */
        
    } tWFModuleNumber;    
    
    
    void WF_AssertionFailed(UINT8 moduleNumber, UINT16 lineNumber);
    
    #define WF_ASSERT(expr)                                 \
       if (!(expr))                                         \
       {                                                    \
           WF_AssertionFailed(WF_MODULE_NUMBER, __LINE__);  \
       }
/*---------------------------*/
/* else asserts are disabled */
/*---------------------------*/
#else 
    #define WF_ASSERT(expr)
#endif  /* WF_DEBUG */


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES                               
*********************************************************************************************************
*/

/*--------------------------*/
/* Initialization Functions */
/*--------------------------*/
void WF_Init(void);

/*-------------------*/
/* Version functions */
/*-------------------*/
void WF_GetDeviceInfo(tWFDeviceInfo *p_deviceInfo);

/*----------------------------*/
/* WF Driver process function */
/*----------------------------*/
void WFProcess(void);


/*---------------------------------------*/
/* WF Driver External Interrupt function */
/* Must be called when:                  */
/*  1) External interrupt is enabled AND */
/*  2) EXINT line is asserted (low)      */
/*---------------------------------------*/
void WFEintISR(void);

/*-----------------------*/
/* MAC Address Functions */
/*-----------------------*/
void WF_SetMacAddress(UINT8 *p_mac);       
void WF_GetMacAddress(UINT8 *p_mac);


/*------------------------------*/
/* Connection Profile Functions */
/*------------------------------*/
void WF_CPCreate(UINT8 *p_CpId);
void WF_CPDelete(UINT8 CpId);
void WF_CPGetIds(UINT8 *cpIdList);

#if defined(WF_USE_GROUP_SET_GETS)
void WF_CPSetElements(UINT8 CpId, tWFCPElements *p_elements);
void WF_CPGetElements(UINT8 CpId, tWFCPElements *p_elements);
#endif

#if defined(WF_USE_INDIVIDUAL_SET_GETS)
    void WF_CPSetSsid(UINT8 CpId, UINT8 *p_ssid,  UINT8 ssidLength);
    void WF_CPGetSsid(UINT8 CpId, UINT8 *p_ssid, UINT8 *p_ssidLength);
    void WF_CPSetBssid(UINT8 CpId, UINT8 *p_bssid);
    void WF_CPGetBssid(UINT8 CpId, UINT8 *p_bssid);
    void WF_CPSetSecurity(UINT8 CpId, 
                          UINT8 securityType,
                          UINT8 wepKeyIndex,
                          UINT8 *p_securityKey,
                          UINT8 securityKeyLength);
    void WF_CPGetSecurity(UINT8 CpId, 
                          UINT8 *p_securityType,
                          UINT8 *p_wepKeyIndex,
                          UINT8 *p_securityKey,
                          UINT8 *p_securityKeyLength);
    void WF_CPSetDefaultWepKeyIndex(UINT8 CpId, UINT8 defaultWepKeyIndex);
    void WF_CPGetDefaultWepKeyIndex(UINT8 CpId, UINT8 *p_defaultWepKeyIndex);
    void WF_CPSetNetworkType(UINT8 CpId, UINT8 networkType);
    void WF_CPGetNetworkType(UINT8 CpId, UINT8 *p_networkType);
    void WF_CPSetAdHocBehavior(UINT8 CpId, UINT8 adHocBehavior);
    void WF_CPGetAdHocBehavior(UINT8 CpId, UINT8 *p_adHocBehavior);
    
#endif /* WF_USE_INDIVIDUAL_SET_GETS */

/*--------------------------------*/
/* Connection Algorithm Functions */
/*--------------------------------*/
#if defined(WF_USE_GROUP_SET_GETS)
void WF_CASetElements(tWFCAElements *p_elements);
void WF_CAGetElements(tWFCAElements *p_elements);
#endif

#if defined(WF_USE_INDIVIDUAL_SET_GETS)
    void WF_CASetScanType(UINT8 scanType);
    void WF_CAGetScanType(UINT8 *p_scanType);
    void WF_CASetRssi(UINT8 rssi);
    void WF_CAGetRssi(UINT8 *p_rssi);
    void WF_CASetConnectionProfileList(UINT8 cpList[WF_CP_LIST_LENGTH]);
    void WF_CAGetConnectionProfileList(UINT8 cpList[WF_CP_LIST_LENGTH]);
    void WF_CASetListRetryCount(UINT8 listRetryCount);
    void WF_CAGetListRetryCount(UINT8 *p_listRetryCount);
    void WF_CASetEventNotificationAction(UINT8 eventNotificationAction);
    void WF_CAGetEventNotificationAction(UINT8 *p_eventNotificationAction);
    void WF_CASetBeaconTimeoutAction(UINT8 beaconTimeoutAction);
    void WF_CAGetBeaconTimeoutAction(UINT8 *p_beaconTimeoutAction);
    void WF_CASetDeauthAction(UINT8 deauthAction);
    void WF_CAGetDeauthAction(UINT8 *p_deauthAction);
    void WF_CASetChannelList(UINT8 *p_channelList, UINT8 numChannels);
    void WF_CAGetChannelList(UINT8 *p_channelList, UINT8 *p_numChannels);
    void WF_CASetListenInterval(UINT16 listenInterval);
    void WF_CAGetListenInterval(UINT16 *p_listenInterval);
    void WF_CASetBeaconTimeout(UINT8 beaconTimeout);
    void WF_CAGetBeaconTimeout(UINT8 *p_beaconTimeout);
    void WF_CASetScanCount(UINT8 scanCount);
    void WF_CAGetScanCount(UINT8 *p_scanCount);
    void WF_CASetMinChannelTime(UINT16 minChannelTime);
    void WF_CAGetMinChannelTime(UINT16 *p_minChannelTime);
    void WF_CASetMaxChannelTime(UINT16 minChannelTime);
    void WF_CAGetMaxChannelTime(UINT16 *p_minChannelTime);
    void WF_CASetProbeDelay(UINT16 probeDelay);
    void WF_CAGetProbeDelay(UINT16 *p_probeDelay);
#endif /* WF_USE_INDIVIDUAL_SET_GETS */

/*--------------------------------*/
/* Connection Manager Functions   */
/*--------------------------------*/
void WF_CMConnect(UINT8 CpId);
void WF_CMDisconnect(void);
void WF_CMGetConnectionState(UINT8 *p_state, UINT8 *p_currentCpId);

/*----------------------------*/
/* Tx Power Control Functions */
/*----------------------------*/
#if defined(WF_USE_TX_POWER_CONTROL_FUNCTIONS)
void WF_ThrottleTableSet(tWFThrottleTable *p_table);
void WF_ThrottleTableGet(tWFThrottleTable *p_table);
void WF_ThrottleTableEnable(void);
void WF_ThrottleTableDisable(UINT8 txPower);
void WF_ThrottleTableGetState(BOOL *p_state, UINT8 *p_bitRate);
void WF_TxPowerSetMinMax(INT8 minTxPower, INT8 maxTxPower);
void WF_TxPowerGetMinMax(INT8 *p_minTxPower, INT8 *p_maxTxPower);
void WF_TxPowerGetFactoryMax(INT8 *p_factoryMaxTxPower);
#endif

/*----------------------------*/
/* Power Management Functions */
/*----------------------------*/
#if defined(WF_USE_POWER_SAVE_FUNCTIONS)
    void WF_PsPollDisable(void);
    void WF_PsPollEnable(BOOL rxDtim);
    void WF_GetPowerSaveState(UINT8 *p_powerSaveState);
    void WF_HibernateEnable(void);
#endif

/*-------------------------*/
/* RTS Threshold Functions */
/*-------------------------*/
void WF_SetRtsThreshold(UINT16 rtsThreshold);
void WF_GetRtsThreshold(UINT16 *p_rtsThreshold);

/*---------------------------*/
/* Regional Domain Functions */
/*---------------------------*/
void WF_SetRegionalDomain(UINT8 regionalDomain);     /* see tWFRegDomain enumerated types */
void WF_GetRegionalDomain(UINT8 *p_regionalDomain);  /* see tWFRegDomain enumerated types */

/*---------------------*/
/* Multicast Functions */
/*---------------------*/
#if defined(WF_USE_MULTICAST_FUNCTIONS)
    void WF_SetMultiCastFilter(UINT8 multicastFilterId, UINT8 multicastAddress[6]);
    void WF_GetMultiCastFilter(UINT8 multicastFilterId, UINT8 multicastAddress[6]);
#endif 

/* MAC Stats */
void WF_GetMacStats(tWFMacStats *p_macStats);

/*----------------*/
/* Scan Functions */
/*----------------*/
#if defined(WF_USE_SCAN_FUNCTIONS)
void WF_Scan(UINT8 CpId);
void WF_ScanGetResult(UINT8         listIndex, 
                      tWFScanResult *p_scanResult);
#endif /* WF_SCAN_FUNCTIONS */

/*------------------------------*/
/* External Interrupt Functions */
/*------------------------------*/
void WF_EintInit(void);
void WF_EintEnable(void);
void WF_EintDisable(void);
BOOL WF_EintIsDisabled(void);
void WFEintHandler(void); 
/* WF_EintIsPending - used by the WF Driver to test for whether */
/* external interrupts are pending.  The pending case is not something */
/* that should normally happen.  It says we have the interrupt line */
/* asserted but the WF_EINT_IF bit is not set, thus, no interrupt generated */
BOOL WF_EintIsPending(void);

/*---------------*/
/* SPI Functions */
/*---------------*/
void     WF_SpiInit(void);
void     WF_SpiEnableChipSelect(void);
void     WF_SpiDisableChipSelect(void);
void     WFSpiTxRx(UINT8   *p_txBuf, 
                   UINT16  txLen, 
                   UINT8   *p_rxBuf,
                   UINT16  rxLen);

#if defined (__18CXX) 
void WFSpiTxRx_Rom(ROM UINT8 *p_txBuf, 
                   UINT16    txLen, 
                   UINT8     *p_rxBuf,
                   UINT16    rxLen);
#endif /* __18CXX */



#if defined(WF_USE_DATA_TX_RX_FUNCTIONS)
/*------------*/
/* Data Tx/Rx */
/*------------*/
void WF_TxDataAllocateBuffer(UINT16 txDataPacketLength);
void WF_TxDataWrite(UINT8  *p_txData, 
                    UINT16  length,
                    UINT16  startIndex);
void WF_TxDataSendPacket(UINT16 length);                      
void WF_RxDataReadPacket(UINT8  *p_rxData,
                         UINT16 length,
                         UINT16 startIndex);
void WF_RxDataDeallocateBuffer(void);
#endif

/*--------------------------*/
/* Event Handling Functions */
/*--------------------------*/
/*******************************************************************************
  Function:	
    void WF_ProcessEvent(UINT8 event,
                         UINT16 eventInfo);

  Summary:
    Process events from the MRF24WB0M

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    event -- The event that occurred
    eventInfo -- Additional information about the event.  This is not applicable 
                 to all events.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_ProcessEvent(UINT8 event, UINT16 eventInfo);

#if defined(WF_CM_DEBUG)
/*--------------------------*/
/* CM Info Functions        */
/*--------------------------*/
void WF_CMInfoGetFSMStats(tWFCMInfoFSMStats *p_info);
#endif

#endif /* __WF_API_H_ */



