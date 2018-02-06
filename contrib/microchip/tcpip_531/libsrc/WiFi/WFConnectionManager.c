/******************************************************************************

 MRF24WB0M Driver Connection Manager
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFConnectionManager.c
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
    #define WF_MODULE_NUMBER    WF_MODULE_WF_CONNECTION_MANAGER
#endif


/*
*********************************************************************************************************
*                                           LOCAL GLOBAL VARIABLES                               
*********************************************************************************************************
*/

static BOOL g_LogicalConnection = FALSE;


/*******************************************************************************
  Function:	
    void WF_CMConnect(UINT8 CpId)

  Summary:
    Commands the MRF24WB0M to start a connection.

  Description:
    Directs the Connection Manager to scan for and connect to a WiFi network.
    This function does not wait until the connection attempt is successful, but 
    returns immediately.  See WF_ProcessEvent for events that can occur as a 
    result of a connection attempt being successful or not.

    Note that if the Connection Profile being used has WPA or WPA2 security
    enabled and is using a passphrase, the connection manager will first 
    calculate the PSK key, and then start the connection process.  The key 
    calculation can take up to 30 seconds.

  Precondition:
    MACInit must be called first.

  Parameters:
    CpId -- If this value is equal to an existing Connection Profile�s ID than 
            only that Connection Profile will be used to attempt a connection to 
            a WiFi network.  
            If this value is set to WF_CM_CONNECT_USING_LIST then the 
            connectionProfileList will be used to connect, starting with the 
            first Connection Profile in the list.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CMConnect(UINT8 CpId)
{
    UINT8  hdrBuf[4];

    /* Write out header portion of msg (which is whole msg, there is no data) */
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;    /* indicate this is a mgmt msg     */
    hdrBuf[1] = WF_CM_CONNECT_SUBYTPE;   /* mgmt request subtype            */  
    hdrBuf[2] = CpId;
    hdrBuf[3] = 0;   

    SendMgmtMsg(hdrBuf,
                sizeof(hdrBuf),
                NULL,
                0);
   
    /* wait for mgmt response, free after it comes in, don't need data bytes */
    WaitForMgmtResponse(WF_CM_CONNECT_SUBYTPE, FREE_MGMT_BUFFER);
}

/*******************************************************************************
  Function:	
    void WF_CMDisconnect(void)

  Summary:
    Commands the MRF24WB0M to close any open connections and/or to cease
    attempting to connect.

  Description:
    Directs the Connection Manager to close any open connection or connection 
    attempt in progress.  No further attempts to connect are taken until 
    WF_CMConnect() is called.  Generates the event 
    WF_EVENT_CONNECTION_PERMANENTLY_LOST when the connection is successfully
    terminated.
    
  Precondition:
    MACInit must be called.

  Parameters:
    None.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CMDisconnect(void)
{
    UINT8  hdrBuf[2];

    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;
    hdrBuf[1] = WF_CM_DISCONNECT_SUBYTPE;

    SendMgmtMsg(hdrBuf,
                sizeof(hdrBuf),
                NULL,
                0);
 
    /* wait for mgmt response, free after it comes in, don't need data bytes */
    WaitForMgmtResponse(WF_CM_DISCONNECT_SUBYTPE, FREE_MGMT_BUFFER);

    /* set state to no connection */
    SetLogicalConnectionState(FALSE);
}    
    
/*******************************************************************************
  Function:	
    void WF_CMGetConnectionState(UINT8 *p_state, UINT8 *p_currentCpId)

  Summary:
    Returns the current connection state.

  Description:

  Precondition:
    MACInit must be called first.

  Parameters:
    p_state -- Pointer to location where connection state will be written
    p_currentCpId -- Pointer to location of current connection profile ID that
                     is being queried.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void WF_CMGetConnectionState(UINT8 *p_state, UINT8 *p_currentCpId)
{
    UINT8  hdrBuf[2];
    UINT8  msgData[2];
    
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;
    hdrBuf[1] = WF_CM_GET_CONNECTION_STATUS_SUBYTPE;

    SendMgmtMsg(hdrBuf,
                sizeof(hdrBuf),
                NULL,
                0);
 
    /* wait for mgmt response, read data, free after read */
	WaitForMgmtResponseAndReadData(WF_CM_GET_CONNECTION_STATUS_SUBYTPE, 
                                   sizeof(msgData),                  /* num data bytes to read          */
                                   MGMT_RESP_1ST_DATA_BYTE_INDEX,    /* only used if num data bytes > 0 */
                                   msgData);                         /* only used if num data bytes > 0 */
    
    *p_state       = msgData[0];        /* connection state */
    *p_currentCpId = msgData[1];        /* current CpId     */
    
    if ((*p_state == WF_CSTATE_NOT_CONNECTED) || (*p_state == WF_CSTATE_CONNECTION_PERMANENTLY_LOST))
    {
        SetLogicalConnectionState(FALSE);
    }
    else
    {
        SetLogicalConnectionState(TRUE);
    }        
}  

/*******************************************************************************
  Function:	
    BOOL WFisConnected()

  Summary:
    Query the connection status of the MRF24WB0M.

  Description:
    Determine the fine granularity status of the connection state of the
    MRF24WB0M.

  Precondition:
    MACInit must be called first.

  Parameters:
    None.

  Returns:
    TRUE if the MRF24WB0M is either connected or attempting to connect.
    FALSE for all other conditions.
  	
  Remarks:
    None.
  *****************************************************************************/
BOOL WFisConnected()
{
    return g_LogicalConnection;   
}      

/*******************************************************************************
  Function:	
    void SetLogicalConnectionState(BOOL state)

  Summary:
    Sets the logical connection state.

  Description:
    Logically, if the MRF24WB0M is either connected or trying to connect, then
    it is "connected".  For all other scenarios, the MRF24WB0M is "not
    connected".

  Precondition:
    MACInit must be called first.

  Parameters:
    state -- Current logical connection state of the MRF24WB0M.

  Returns:
    None.
  	
  Remarks:
    None.
  *****************************************************************************/
void SetLogicalConnectionState(BOOL state)
{
    g_LogicalConnection = state;
}

#endif /* WF_CS_TRIS */
