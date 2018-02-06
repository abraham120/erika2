/******************************************************************************

 MRF24WB0M Driver Connection Profile
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFConnectionProfile.c
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

/*
*********************************************************************************************************
*                                           INCLUDES                               
*********************************************************************************************************
*/

#include "TCPIP_Stack/WFMac.h"

#if defined(WF_CS_TRIS)

/* used for assertions */
#if defined(WF_DEBUG)
    #define WF_MODULE_NUMBER    WF_MODULE_WF_CONNECTION_PROFILE
#endif


/*
*********************************************************************************************************
*                                           LOCAL DATA TYPES                               
*********************************************************************************************************
*/

/* header format for response to CP Get Element message */
typedef struct cpElementResponseStruct
{
    tMgmtMsgRxHdr  mgmtHdr;                /* normal 4-byte hdr for all mgmt responses */
    UINT8          profileId;
    UINT8          elementId;
    UINT8          elementDataLength;
    /* element data follows */
} tCPElementResponseHdr;    


/*
*********************************************************************************************************
*                                           LOCAL FUNCTION PROTOTYPES                               
*********************************************************************************************************
*/

static void LowLevel_CPSetElement(UINT8 CpId, 
                                  UINT8 elementId, 
                                  UINT8 *p_elementData, 
                                  UINT8 elementDataLength);

static void LowLevel_CPGetElement(UINT8 CpId, 
                                  UINT8 elementId, 
                                  UINT8 *p_elementData, 
                                  UINT8 elementDataLength,
                                  UINT8 dataReadAction);

/*******************************************************************************
  Function:	
    void WF_CPCreate(UINT8 *p_CpId)

  Summary:
    Creates a Connection Profile on the MRF24WB0M.

  Description:
    Requests the MRF24WB0M to create a Connection Profile (CP), assign it an ID, 
    and set all the elements to default values.  A maximum of 8 Connection 
    Profiles can exist on the MRF24WB0M (stored in FLASH).  Two CP�s can be 
    active in MRF24WB0M memory at any one time.

    NOTE: First release of this code will not support FLASH, only the two CP�s 
    in memory.

  Precondition:
    MACInit must be called first.

  Parameters:
    p_CpId -- pointer to where Connection Profile ID will be written.  If 
              function fails, the CP ID will be set to 0xff.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPCreate(UINT8 *p_CpId)
{
    UINT8  hdr[2];
 
    *p_CpId = 0xff;
    
    hdr[0] = WF_MGMT_REQUEST_TYPE;
    hdr[1] = WF_CP_CREATE_PROFILE_SUBTYPE;

    SendMgmtMsg(hdr,
                sizeof(hdr),
                NULL,            /* no data */
                0);              /* no data */
    
    /* wait for MRF24WB0M management response, read data, free response after read */
	WaitForMgmtResponseAndReadData(WF_CP_CREATE_PROFILE_SUBTYPE, 
                                   1,                             /* num data bytes to read          */
	                               MGMT_RESP_1ST_DATA_BYTE_INDEX, /* read starting at index 4        */
	                               p_CpId);                       /* write data here                 */
}    

/*******************************************************************************
  Function:	
    void WF_CPDelete(UINT8 CpId)

  Summary:
    Deletes a Connection Profile on the MRF24WB0M.

  Description:
    Deletes the specified Connection Profile.  If the Connection Profile was in 
    FLASH it will be erased from FLASH.

    NOTE: First release of this code will not support FLASH, only the two CP�s 
    in memory.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- Connection Profile to delete.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPDelete(UINT8 CpId)
{
    UINT8  hdr[2];

    hdr[0] = WF_MGMT_REQUEST_TYPE;
    hdr[1] = WF_CP_DELETE_PROFILE_SUBTYPE;
    
    SendMgmtMsg(hdr,
                sizeof(hdr),
                &CpId,           /* input data */
                1);              /* data size  */

    /* wait for mgmt response, free it after it comes in (no data needed) */
	WaitForMgmtResponse(WF_CP_DELETE_PROFILE_SUBTYPE, FREE_MGMT_BUFFER); 
}

/*******************************************************************************
  Function:	
    void WF_CPGetIds(UINT8 *p_cpIdList)

  Summary:
    Retrieves the CP ID bit mask.

  Description:
    Returns a list of all Connection Profile ID�s that have been created on the 
    MRF24WB0M.  This is not to be confused with the Connection Algorithm�s 
    connectionProfileList.  This function returns a bit mask corresponding to a 
    list of all Connection Profiles that have been created (whether they are in 
    the connectionProfileList or not).  Any Connection Profiles that have been 
    saved to FLASH will be included.  

    Note: the first release will only support two Connection Profiles in memory.
    Saving CP�s to FLASH will not be supported.

  Precondition:
    MACInit must be called first.

  Parameters:
    p_cpIdList -- pointer to value representing the bit mask where each bit 
                  index (plus 1) corresponds to a Connection Profile ID that has 
                  been created.  For example, if this value is 0x41, then 
                  Connection Profile ID�s 1 and and 4 have been created.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPGetIds(UINT8 *p_cpIdList)
{
    UINT8  hdr[2];
    
    hdr[0] = WF_MGMT_REQUEST_TYPE;
    hdr[1] = WF_CP_GET_ID_LIST_SUBTYPE;
    
    SendMgmtMsg(hdr,
                sizeof(hdr),
                NULL,
                0);
    
    /* wait for mgmt response, read data, free after read */
	WaitForMgmtResponseAndReadData(WF_CP_GET_ID_LIST_SUBTYPE, 
                                   1,                                /* num data bytes to read          */
                                   MGMT_RESP_1ST_DATA_BYTE_INDEX,    /* only used if num data bytes > 0 */
                                   p_cpIdList);                      /* only used if num data bytes > 0 */
}    

#if defined(WF_USE_GROUP_SET_GETS)
/*******************************************************************************
  Function:	
    void WF_CPSetElements(UINT8 CpId, tWFCPElements *p_elements)

  Summary:
    Writes out data for a specific connection profile element.

  Description:
    Sets all Connection Profile elements.  If the Host CPU does not have enough 
    memory to create a structure of this size then call the individual set
    functions.

  Precondition:
    MACInit must be called.

  Parameters:
    CpId -- Connectino Profile ID.
    p_elements -- Pointer to Connection Profile elements structure.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPSetElements(UINT8 CpId, tWFCPElements *p_elements)
{
    WF_ASSERT(p_elements->ssidLength <= WF_MAX_SSID_LENGTH);
    
    LowLevel_CPSetElement(CpId,                   /* CP ID                        */
                          WF_CP_ELEMENT_ALL,      /* Element ID                   */
                          (UINT8 *)p_elements,    /* pointer to element data      */
                          sizeof(tWFCPElements)); /* number of element data bytes */
}

/*******************************************************************************
  Function:	
    void WF_CPGetElements(UINT8 CpId, tWFCPElements *p_elements)

  Summary:
    Reads the Connection Profile elements for the specified ID.

  Description:
    Gets all Connection Profile elements for the specified CP ID.  If the Host 
    CPU does not have enough memory to create a structure of this size then call 
    the individual get functions.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- Connectino Profile ID.
    p_elements -- Pointer to Connection Profile elements structure.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPGetElements(UINT8 CpId, tWFCPElements *p_elements)
{
    LowLevel_CPGetElement(CpId,                   /* CP ID                        */
                          WF_CP_ELEMENT_ALL,      /* Element ID                   */
                         (UINT8 *)p_elements,     /* pointer to element data      */
                          sizeof(tWFCPElements),  /* number of element data bytes */
                          TRUE);                  /* read data and free buffer    */
}
#endif /* WF_USE_GROUP_SET_GETS */ 

#if defined(WF_USE_INDIVIDUAL_SET_GETS)
/*******************************************************************************
  Function:	
    void WF_CPSetSsid(UINT8 CpId, UINT8 *p_ssid, UINT8 *p_ssidLength)

  Summary:
    Sets the SSID for the specified Connection Profile ID.    

  Description:
    Sets the SSID and SSID Length elements in the Connection Profile.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    p_ssid -- pointer to the SSID string
    ssidLength -- number of bytes in the SSID

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPSetSsid(UINT8 CpId, UINT8 *p_ssid,  UINT8 ssidLength)
{
    WF_ASSERT(ssidLength <= WF_MAX_SSID_LENGTH);
    LowLevel_CPSetElement(CpId,                   /* CP ID                        */
                          WF_CP_ELEMENT_SSID,     /* Element ID                   */
                         (UINT8 *)p_ssid,         /* pointer to element data      */
                          ssidLength);            /* number of element data bytes */

}   
 
/*******************************************************************************
  Function:	
    void WF_CPGetSsid(UINT8 CpId, UINT8 *p_ssid, UINT8 *p_ssidLength)

  Summary:
    Gets the SSID for the specified Connection Profile ID.    

  Description:
    Gets the SSID and SSID Length elements in the Connection Profile.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    p_ssid -- pointer to the SSID string
    ssidLength -- number of bytes in the SSID

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPGetSsid(UINT8 CpId, UINT8 *p_ssid, UINT8 *p_ssidLength)
{
    tCPElementResponseHdr  mgmtHdr;
    
    /* Request SSID, but don't have this function read data or free response buffer.       */
    LowLevel_CPGetElement(CpId,                   /* Connection Profile ID                 */
                          WF_CP_ELEMENT_SSID,     /* Element ID                            */
                          NULL,                   /* ptr to element data (not used here    */
                          0,                      /* num data bytes to read (not used here */ 
                          FALSE);                 /* no read, leave response mounted       */
    
    /* At this point, management response is mounted and ready to be read.                 */
    /* Set raw index to 0, read normal 4 byte header plus the next 3 bytes, these will be: */
    /*   profile id             [4]                                                        */
    /*   element id             [5]                                                        */
    /*   element data length    [6]                                                        */
    RawRead(RAW_RX_ID, 0, sizeof(tCPElementResponseHdr), (UINT8 *)&mgmtHdr);

    /* extract SSID length and write to caller */
    *p_ssidLength = mgmtHdr.elementDataLength;
    
    /* copy SSID name to callers buffer */
    RawRead(RAW_RX_ID, sizeof(tCPElementResponseHdr), *p_ssidLength, p_ssid);
    
    /* free management buffer */
    DeallocateMgmtRxBuffer();
}   

/*******************************************************************************
  Function:	
    void WF_CPSetBssid(UINT8 CpId, UINT8 *p_bssid)

  Summary:
    Sets the BSSID for the specified Connection Profile ID.

  Description:
    Sets the BSSID element in a Connection Profile.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    p_bssid -- pointer to the BSSID 

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPSetBssid(UINT8 CpId, UINT8 *p_bssid)
{
    LowLevel_CPSetElement(CpId,                  /* CP ID                        */
                          WF_CP_ELEMENT_BSSID,   /* Element ID                   */
                          p_bssid,               /* pointer to element data      */
                          WF_BSSID_LENGTH);      /* number of element data bytes */
}   

/*******************************************************************************
  Function:	
    void WF_CPGetBssid(UINT8 CpId, UINT8 *p_bssid)

  Summary:
    Gets the BSSID for the specified Connection Profile ID.

  Description:
    Gets the BSSID element in a Connection Profile.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    p_bssid -- pointer to the BSSID 

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CPGetBssid(UINT8 CpId, UINT8 *p_bssid)
{
    LowLevel_CPGetElement(CpId,                  /* CP ID                             */
                          WF_CP_ELEMENT_BSSID,   /* Element ID                        */
                          p_bssid,               /* pointer to element data           */
                          WF_BSSID_LENGTH,       /* number of element data bytes      */
                          TRUE);                 /* read data, free buffer after read */
}   

/*******************************************************************************
  Function:	
    void WF_CPSetNetworkType(UINT8 CpId, UINT8 networkType)

  Summary:
    Sets the network for the specified Connection Profile ID.

  Description:
    Sets the Network Type element a Connection Profile.  Allowable values are:
    * WF_INFRASTRUCTURE
    * WF_ADHOC

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    networkType -- type of network to create (infrastructure or adhoc)

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_CPSetNetworkType(UINT8 CpId, UINT8 networkType)
{
    LowLevel_CPSetElement(CpId,                         /* CP ID                        */
                          WF_CP_ELEMENT_NETWORK_TYPE,   /* Element ID                   */
                          &networkType,                 /* pointer to element data      */
                          1);                           /* number of element data bytes */
}   

/*******************************************************************************
  Function:	
    void WF_CPGetNetworkType(UINT8 CpId, UINT8 networkType)

  Summary:
    Gets the network for the specified Connection Profile ID.

  Description:
    Gets the Network Type element a Connection Profile.  Allowable values are:
    * WF_INFRASTRUCTURE
    * WF_ADHOC

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    networkType -- type of network to create (infrastructure or adhoc)

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/ 
void WF_CPGetNetworkType(UINT8 CpId, UINT8 *p_networkType)
{
    LowLevel_CPGetElement(CpId,                       /* conn. profile ID       */
                          WF_CP_ELEMENT_NETWORK_TYPE, /* element ID             */
                          p_networkType,              /* element data pointer   */
                          1,                          /* read one byte          */
                          TRUE);                      /* read data, free buffer */
}

/*******************************************************************************
  Function:	
    void WF_CPSetSecurity(UINT8 CpId, 
                          UINT8 securityType,
                          UINT8 wepKeyIndex,
                          UINT8 *p_securityKey,
                          UINT8 securityKeyLength)

  Summary:
    Sets the security for the specified Connection Profile.

  Description:
    Configures security for a Connection Profile.

    <table>
    Security                                Key         Length
    --------                                ---         ------
    WF_SECURITY_OPEN                        N/A         N/A
    WF_SECURITY_WEP_40                      hex         4, 5 byte keys
    WF_SECURITY_WEP_104                     hex         4, 13 byte keys
    WF_SECURITY_WPA_WITH_KEY                hex         32 bytes
    WF_SECURITY_WPA_WITH_PASS_PHRASE        ascii       8-63 ascii characters
    WF_SECURITY_WPA2_WITH_KEY               hex         32 bytes
    WF_SECURITY_WPA2_WITH_PASS_PHRASE       ascii       8-63 ascii characters
    WF_SECURITY_WPA_AUTO_WITH_KEY           hex         32 bytes
    WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE   ascii       8-63 ascii characters
    </table>

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    securityType -- value corresponding to the security type desired.
    wepKeyIndex -- 0 thru 3 (only used if security type is WF_SECURITY_WEP_40 or
                   WF_SECURITY_WEP_104)
    p_securityKey -- binary key or passphrase (not used if security is 
                     WF_SECURITY_OPEN)
    securityKeyLength -- number of bytes in p_securityKey (not used if security
                         is WF_SECURITY_OPEN)

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_CPSetSecurity(UINT8 CpId, 
                      UINT8 securityType,
                      UINT8 wepKeyIndex,
                      UINT8 *p_securityKey,
                      UINT8 securityKeyLength)
{
    UINT8  hdrBuf[7];
    UINT8  *p_key;

    /* Write out header portion of msg */
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;           /* indicate this is a mgmt msg     */
    hdrBuf[1] = WF_CP_SET_ELEMENT_SUBTYPE;      /* mgmt request subtype            */     
    hdrBuf[2] = CpId;                           /* Connection Profile ID           */
    hdrBuf[3] = WF_CP_ELEMENT_SECURITY;         /* Element ID                      */
    
    /* Next to header bytes are really part of data, but need to put them in header      */
    /* bytes in order to prepend to security key                                         */
    hdrBuf[5] = securityType;                   
    hdrBuf[6] = wepKeyIndex;                     
    
    /* if security is open (no key) */
    if (securityType == WF_SECURITY_OPEN)
    {
        hdrBuf[4]         = 2;      /* Only data is security type and wep index */ 
        p_key             = NULL;   
        securityKeyLength = 0;    

    } 
    /* else security is selected, so need to send key */   
    else
    {
        hdrBuf[4] = 2 + securityKeyLength;  /* data is security type + wep index + key */
        p_key     = p_securityKey;       
    }    
    
    SendMgmtMsg(hdrBuf,              /* msg header which includes the security type and WEP index)    */
                sizeof(hdrBuf),      /* msg header length                                             */
                p_key,               /* msg data (security key), can be NULL                          */
                securityKeyLength);  /* msg data length (will be 0 if p_securityKey is NULL)          */
    
    /* wait for mgmt response, free after it comes in, don't need data bytes */
    WaitForMgmtResponse(WF_CP_SET_ELEMENT_SUBTYPE, FREE_MGMT_BUFFER);
}   

/*******************************************************************************
  Function:	
    void WF_CPGetSecurity(UINT8 CpId, 
                          UINT8 securityType,
                          UINT8 wepKeyIndex,
                          UINT8 *p_securityKey,
                          UINT8 securityKeyLength)

  Summary:
    Gets the security for the specified Connection Profile.

  Description:
    Configures security for a Connection Profile.

    <table>
    Security                                Key         Length
    --------                                ---         ------
    WF_SECURITY_OPEN                        N/A         N/A
    WF_SECURITY_WEP_40                      hex         4, 5 byte keys
    WF_SECURITY_WEP_104                     hex         4, 13 byte keys
    WF_SECURITY_WPA_WITH_KEY                hex         32 bytes
    WF_SECURITY_WPA_WITH_PASS_PHRASE        ascii       8-63 ascii characters
    WF_SECURITY_WPA2_WITH_KEY               hex         32 bytes
    WF_SECURITY_WPA2_WITH_PASS_PHRASE       ascii       8-63 ascii characters
    WF_SECURITY_WPA_AUTO_WITH_KEY           hex         32 bytes
    WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE   ascii       8-63 ascii characters
    </table>

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    securityType -- value corresponding to the security type desired.
    wepKeyIndex -- 0 thru 3 (only used if security type is WF_SECURITY_WEP_40 or
                   WF_SECURITY_WEP_104)
    p_securityKey -- binary key or passphrase (not used if security is 
                     WF_SECURITY_OPEN)
    securityKeyLength -- number of bytes in p_securityKey (not used if security
                         is WF_SECURITY_OPEN)

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_CPGetSecurity(UINT8 CpId, 
                      UINT8 *p_securityType,
                      UINT8 *p_wepKeyIndex,
                      UINT8 *p_securityKey,
                      UINT8 *p_securityKeyLength)
{
    tCPElementResponseHdr mgmtHdr;
    UINT8 keyLength;
    
    /* send request, wait for mgmt response, do not read and do not free up response buffer */
     LowLevel_CPGetElement(CpId,
                           WF_CP_ELEMENT_SECURITY,        /* Element ID      */
                           NULL,                          /* do not read     */
                           0,                             /* do not read     */
                           FALSE);                        /* do not read, do not free mgmt buffer */

    /* at this point, management response is mounted and ready to be read */  

        /* At this point, management response is mounted and ready to be read.                 */
    /* Set raw index to 0, read normal 4 byte header plus the next 3 bytes, these will be: */
    /*   profile id             [4]                                                        */
    /*   element id             [5]                                                        */
    /*   element data length    [6]                                                        */
    RawRead(RAW_RX_ID, 0, sizeof(tCPElementResponseHdr), (UINT8 *)&mgmtHdr);
    
    RawRead(RAW_RX_ID,                          /* raw Id                     */
            sizeof(tCPElementResponseHdr) + 0,  /* index of security type [7] */
            1,                                  /* read one byte              */
            p_securityType);                    /* copy that byte here        */

    RawRead(RAW_RX_ID,                          /* raw Id                     */
            sizeof(tCPElementResponseHdr) + 1 , /* index of WEP key index [8] */
            1,                                  /* read one byte              */
            p_wepKeyIndex);                     /* copy that byte here        */

    /* determine security key length and read if it is present */
    keyLength = mgmtHdr.elementDataLength - 2;
    if (keyLength > 0)
    {
        *p_securityKeyLength = keyLength;
        
        RawRead(RAW_RX_ID,                          /* raw Id                  */
                sizeof(tCPElementResponseHdr) + 2,  /* index of first key byte */
                keyLength,                          /* number of bytes to read */
                p_securityKey);                     /* copy bytes here         */
        
    }
    /* no security key, so set key length param to 0 */
    else
    {
        *p_securityKeyLength = 0;
    }       
    
    /* free management buffer */
    DeallocateMgmtRxBuffer();
 
}    

/*******************************************************************************
  Function:	
    void WF_CPSetDefaultWepKeyIndex(UINT8 CpId, UINT8 defaultWepKeyIndex)

  Summary:
    Selects one of the 4 WEP keys to use.

  Description:
    Only applicable if the Connection Profile security type is either 
    WF_SECURITY_WEP_40 or WF_SECURITY_WEP_104.  Selects which of the four WEP 
    keys to use.

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    defaultWepKeyIndex -- index of WEP key to use (0 - 3)

  Returns:
  	None.
  	
  Remarks:
  	Note that only key 0 amongst AP manufacturers is typically used.  Using any
    of the other three keys may be unpredictable from brand to brand.
  *****************************************************************************/
void WF_CPSetDefaultWepKeyIndex(UINT8 CpId, UINT8 defaultWepKeyIndex)
{
    LowLevel_CPSetElement(CpId,                          /* CP ID                        */
                          WF_CP_ELEMENT_WEP_KEY_INDEX,   /* Element ID                   */
                          &defaultWepKeyIndex,            /* pointer to element data      */
                          1);                            /* number of element data bytes */
}  

/*******************************************************************************
  Function:	
    void WF_CPGetDefaultWepKeyIndex(UINT8 CpId, UINT8 *p_defaultWepKeyIndex)

  Summary:
    Gets the value of the active WEP keys to use.

  Description:
    Only applicable if the Connection Profile security type is either 
    WF_SECURITY_WEP_40 or WF_SECURITY_WEP_104.  Selects which of the four WEP 
    keys to use.

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    p_defaultWepKeyIndex -- pointer to index of WEP key to use (0 - 3)

  Returns:
  	None.
  	
  Remarks:
  	Note that only key 0 amongst AP manufacturers is typically used.  Using any
    of the other three keys may be unpredictable from brand to brand.
  *****************************************************************************/
void WF_CPGetDefaultWepKeyIndex(UINT8 CpId, UINT8 *p_defaultWepKeyIndex)
{
    LowLevel_CPGetElement(CpId,                        /* conn. profile ID       */
                          WF_CP_ELEMENT_WEP_KEY_INDEX, /* element ID             */
                          p_defaultWepKeyIndex,        /* element data pointer   */
                          1,                           /* read one byte          */
                          TRUE);                       /* read data, free buffer */
}
  
/*******************************************************************************
  Function:	
    void WF_CPSetAdHocBehavior(UINT8 CpId, UINT8 adHocBehavior)

  Summary:
    Selects the desired Ad Hoc behavior

  Description:
    Sets the AdHoc behavior within a Connection Profile.  Allowable values are:
    * WF_ADHOC_CONNECT_THEN_START
    * WF_ADHOC_CONNECT_ONLY
    * WF_ADHOC_START_ONLY

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    adHocBehavior -- value of the adhoc behavior for this connection profile.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_CPSetAdHocBehavior(UINT8 CpId, UINT8 adHocBehavior)
{
    LowLevel_CPSetElement(CpId,                          /* CP ID                        */
                          WF_CP_ELEMENT_ADHOC_BEHAVIOR,  /* Element ID                   */
                          &adHocBehavior,                /* pointer to element data      */
                          1);                            /* number of element data bytes */
}    

/*******************************************************************************
  Function:	
    void WF_CPGetAdHocBehavior(UINT8 CpId, UINT8 *p_adHocBehavior)

  Summary:
    Gets the desired Ad Hoc behavior

  Description:
    Gets the AdHoc behavior within a Connection Profile.  Allowable values are:
    * WF_ADHOC_CONNECT_THEN_START
    * WF_ADHOC_CONNECT_ONLY
    * WF_ADHOC_START_ONLY

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    adHocBehavior -- pointer to location of the adhoc behavior value for this 
                     connection profile.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_CPGetAdHocBehavior(UINT8 CpId, UINT8 *p_adHocBehavior)
{
    LowLevel_CPGetElement(CpId,                         /* conn. profile ID       */
                          WF_CP_ELEMENT_ADHOC_BEHAVIOR, /* element ID             */
                          p_adHocBehavior,              /* element data pointer   */
                          1,                            /* read one byte          */
                          TRUE);                        /* read data, free buffer */
}    
#endif /* WF_USE_INDIVIDUAL_SET_GETS */

/*******************************************************************************
  Function:	
    static void LowLevel_CPSetElement(UINT8 CpId, 
                                  UINT8 elementId, 
                                  UINT8 *p_elementData, 
                                  UINT8 elementDataLength)

  Summary:
    Set an element of the connection profile on the MRF24WB0M.

  Description:
    All Connection Profile 'Set Element' functions call this function to 
    construct the management message.  The caller must fix up any endian issues 
    prior to calling this function.

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    elementId -- element that is being set
    p_elementData -- pointer to element data
    elementDataLength -- number of bytes pointed to by p_elementData

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
static void LowLevel_CPSetElement(UINT8 CpId, 
                                  UINT8 elementId, 
                                  UINT8 *p_elementData, 
                                  UINT8 elementDataLength)
{
    UINT8  hdrBuf[5];
    
    /* Write out header portion of msg */
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;       /* indicate this is a mgmt msg     */
    hdrBuf[1] = WF_CP_SET_ELEMENT_SUBTYPE;  /* mgmt request subtype            */     
    hdrBuf[2] = CpId;                       /* Connection Profile ID           */
    hdrBuf[3] = elementId;                  /* Element ID                      */
    hdrBuf[4] = elementDataLength;          /* number of bytes of element data */
    
    SendMgmtMsg(hdrBuf,              /* msg header        */
                sizeof(hdrBuf),      /* msg header length */
                p_elementData,       /* msg data          */
                elementDataLength);  /* msg data length   */
    
    /* wait for mgmt response, free after it comes in, don't need data bytes */
    WaitForMgmtResponse(WF_CP_SET_ELEMENT_SUBTYPE, FREE_MGMT_BUFFER);

}    

/*******************************************************************************
  Function:	
    static void LowLevel_CPGetElement(UINT8 CpId, 
                                      UINT8 elementId, 
                                      UINT8 *p_elementData, 
                                      UINT8 elementDataLength,
                                      UINT8 dataReadAction)

  Summary:
    Get an element of the connection profile on the MRF24WB0M.

  Description:
    All Connection Profile 'Get Element' functions call this function to 
    construct the management message.  The caller must fix up any endian issues 
    prior to calling this function.

  Precondition:
  	MACInit must be called first.

  Parameters:
    CpId -- Connection Profile ID
    elementId -- element that is being read
    p_elementData -- pointer to where element data will be written
    elementDataLength -- number of element data bytes that will be read
    dataReadAction -- if TRUE then read data per paramters and free mgmt 
                      response buffer. If FALSE then return after response 
                      received, do not read any data as the caller will do that, 
                      and don't free buffer, as caller will do that as well.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
static void LowLevel_CPGetElement(UINT8 CpId, 
                                    UINT8 elementId, 
                                    UINT8 *p_elementData, 
                                    UINT8 elementDataLength,
                                    UINT8 dataReadAction)    /* TRUE or FALSE */
{
    UINT8  hdrBuf[4];
      
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;          /* indicate this is a mgmt msg     */
    hdrBuf[1] = WF_CP_GET_ELEMENT_SUBTYPE;  /* mgmt request subtype            */     
    hdrBuf[2] = CpId;                       /* Connection Profile ID           */
    hdrBuf[3] = elementId;                  /* Element ID                      */

    SendMgmtMsg(hdrBuf,              /* msg header        */
                sizeof(hdrBuf),      /* msg header length */
                NULL,                /* msg data          */
                0);                  /* msg data length   */
  
    if (dataReadAction == (UINT8)TRUE)
    {
        /* wait for mgmt response, read desired data, and then free response buffer */
    	WaitForMgmtResponseAndReadData(WF_CP_GET_ELEMENT_SUBTYPE, 
                                       elementDataLength,                   /* num data bytes to read                */
                                       sizeof(tCPElementResponseHdr),       /* index of first byte of element data   */
                                       p_elementData);                      /* where to write element data           */
    }
    else
    {
        /* wait for mgmt response, don't read any data bytes, do not release mgmt buffer */
        WaitForMgmtResponse(WF_CP_GET_ELEMENT_SUBTYPE, DO_NOT_FREE_MGMT_BUFFER);
    }                   	                             
}
    

#endif /* WF_CS_TRIS */
