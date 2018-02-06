/******************************************************************************

 MRF24WB0M Driver Power Save functions
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFPowerSave.c
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
#if defined(WF_CS_TRIS) && defined(WF_USE_POWER_SAVE_FUNCTIONS)


/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/

/* used for assertions */
#if defined(WF_DEBUG)
    #define WF_MODULE_NUMBER   WF_MODULE_WF_POWER_SAVE
#endif

#define REG_ENABLE_LOW_POWER_MASK   ((UINT16)(0x01))

/*
*********************************************************************************************************
*                                           LOCAL DATA TYPES                               
*********************************************************************************************************
*/

/* Enumeration of valid values for WFSetPowerSaveMode() */
typedef enum
{
    PS_POLL_ENABLED = 0,    /* power save mode enabled  */
    PS_POLL_DISABLED        /* power save mode disabled */ 
} tWFPsPwrMode;

typedef struct pwrModeRequestStruct
{
    UINT8 mode;
    UINT8 wake;
    UINT8 rcvDtims;
    UINT8 reserved;            /* pad byte */
} tWFPwrModeReq;


/*
*********************************************************************************************************
*                                           LOCAL GLOBAL VARIABLES                              
*********************************************************************************************************
*/

static UINT8 g_powerSaveState = WF_PS_OFF;
static BOOL  g_psPollActive   = FALSE;     

/*
*********************************************************************************************************
*                                           LOCAL FUNCTION PROTOTYPES                          
*********************************************************************************************************
*/

static void SendPowerModeMsg(tWFPwrModeReq *p_powerMode);
static void SetPowerSaveState(UINT8 powerSaveState);


/*******************************************************************************
  Function:	
    void WFConfigureLowPowerMode(UINT8 action)

  Summary:
    Driver function to configure PS Poll mode.

  Description:
    This function is only used by the driver, not the application.  This
    function, other than at initialization, is only used when the application
    has enabled PS-Poll mode.  This function is used to temporarily deactivate 
    PS-Poll mode when there is mgmt or data message tx/rx and then, when message 
    activity has ceased, to again activate PS-Poll mode. 

  Precondition:
  	MACInit must be called first.

  Parameters:
    action - Can be either:
             * WF_LOW_POWER_MODE_ON
             * WF_LOW_POWER_MODE_OFF

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WFConfigureLowPowerMode(UINT8 action)
{
    UINT16 lowPowerStatusRegValue;

    /*-----------------------------------------*/
    /* if activating PS-Poll mode on MRF24WB0M */
    /*-----------------------------------------*/
    if (action == WF_LOW_POWER_MODE_ON)
    {
        Write16BitWFRegister(WF_PSPOLL_H_REG, REG_ENABLE_LOW_POWER_MASK);
        g_psPollActive = TRUE;           
    }        
    /*---------------------------------------------------------------------------------------------*/    
    /* else deactivating PS-Poll mode on MRF24WB0M (taking it out of low-power mode and waking it up) */
    /*---------------------------------------------------------------------------------------------*/
    else /* action == WF_LOW_POWER_MODE_OFF */
    {
        Write16BitWFRegister(WF_PSPOLL_H_REG, 0x00);      
        g_psPollActive = FALSE;                 

        /* poll the response bit that indicates when the MRF24WB0M has come out of low power mode */
        do
        {
            /* set the index register to the register we wish to read (kWFCOMRegLoPwrStatusReg) */
            Write16BitWFRegister(WF_INDEX_ADDR_REG, WF_LOW_POWER_STATUS_REG);
            lowPowerStatusRegValue = Read16BitWFRegister(WF_INDEX_DATA_REG);

        } while (lowPowerStatusRegValue & REG_ENABLE_LOW_POWER_MASK);
    }    
}

/*******************************************************************************
  Function:	
    void WF_PsPollEnable(BOOL rxDtim)

  Summary:
    Enables PS Poll mode.

  Description:
    Enables PS Poll mode.  PS-Poll (Power-Save Poll) is a mode allowing for 
    longer battery life.  The MRF24WB0M coordinates with the Access Point to go 
    to sleep and wake up at periodic intervals to check for data messages, which 
    the Access Point will buffer.  The listenInterval in the Connection 
    Algorithm defines the sleep interval.  By default, PS-Poll mode is disabled.

    When PS Poll is enabled, the WF Host Driver will automatically force the 
    MRF24WB0M to wake up each time the Host sends Tx data or a control message 
    to the MRF24WB0M.  When the Host message transaction is complete the 
    MRF24WB0M driver will automatically re-enable PS Poll mode.

    When the application is likely to experience a high volume of data traffic 
    then PS-Poll mode should be disabled for two reasons:
    1. No power savings will be realized in the presence of heavy data traffic.
    2. Performance will be impacted adversely as the WiFi Host Driver 
        continually activates and deactivates PS-Poll mode via SPI messages.

  Precondition:
  	MACInit must be called first.

  Parameters:
    rxDtim -- TRUE if MRF24WB0M should wake up periodically and check for
              buffered broadcast messages, else FALSE

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_PsPollEnable(BOOL rxDtim)
{
    tWFPwrModeReq   pwrModeReq;
    
    /* fill in request structure and send message to MRF24WB0M */
    pwrModeReq.mode     = PS_POLL_ENABLED;
    pwrModeReq.wake     = 0;
    pwrModeReq.rcvDtims = rxDtim;
    SendPowerModeMsg(&pwrModeReq);
    
    if (rxDtim == TRUE)
    {
        SetPowerSaveState(WF_PS_PS_POLL_DTIM_ENABLED);
    }    
    else
    {
        SetPowerSaveState(WF_PS_PS_POLL_DTIM_DISABLED);
    }    
    
    WFConfigureLowPowerMode(WF_LOW_POWER_MODE_ON);
}

/*******************************************************************************
  Function:	
    void WF_PsPollDisable(void)

  Summary:
    Disables PS-Poll mode.

  Description:
    Disables PS Poll mode.  The MRF24WB0M will stay active and not go sleep.

  Precondition:
  	MACInit must be called first.

  Parameters:
    None.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_PsPollDisable(void)
{
   tWFPwrModeReq   pwrModeReq;
    
    pwrModeReq.mode     = PS_POLL_DISABLED;
    pwrModeReq.wake     = 1;
    pwrModeReq.rcvDtims = 1;
    SendPowerModeMsg(&pwrModeReq);

    SetPowerSaveState(WF_PS_OFF);
    WFConfigureLowPowerMode(WF_LOW_POWER_MODE_OFF);    
}   

/*******************************************************************************
  Function:	
    void WF_GetPowerSaveState(UINT8 *p_powerSaveState)

  Summary:
    Returns current power-save state.

  Description:
    Returns the current MRF24WB0M power save state.

    <table>
    Value                       Definition
    -----                       ----------
    WF_PS_HIBERNATE             MRF24WB0M in hibernate state
    WF_PS_PS_POLL_DTIM_ENABLED  MRF24WB0M in PS-Poll mode with DTIM enabled
    WF_PS_PS_POLL_DTIM_DISABLED MRF24WB0M in PS-Poll mode with DTIM disabled
    WF_PS_POLL_OFF              MRF24WB0M is not in any power-save state
    </table>

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_powerSaveState -- pointer to where power state is written

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_GetPowerSaveState(UINT8 *p_powerSaveState)
{
    *p_powerSaveState = g_powerSaveState;
}  

/*******************************************************************************
  Function:	
    BOOL WFisPsPollEnabled(void)

  Summary:
    Determines if application has enable PS-Poll mode.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    None.

  Returns:
  	TRUE if application has enabled PS-Poll mode, else returns FALSE
  	
  Remarks:
  	None.
  *****************************************************************************/
BOOL WFisPsPollEnabled(void)
{
    if ((g_powerSaveState == WF_PS_PS_POLL_DTIM_ENABLED) || (g_powerSaveState == WF_PS_PS_POLL_DTIM_DISABLED)) 
    {
        return TRUE;
    }    
    else
    {
        return FALSE;
    }    
}    

/*******************************************************************************
  Function:	
    BOOL WFIsPsPollActive(void)

  Summary: Determine if PS Poll is currently active.

  Description:
    This function is only called when PS-Poll mode has been enabled by the 
    application.  When transmitting or receiving data or mgmt messages the 
    driver will temporarily disable PS-Poll.  This function is used by the 
    driver to determine if PS-Poll is active or has been temporarily disabled. 

  Precondition:
  	MACInit must be called first.

  Parameters:
    None.

  Returns:
  	TRUE if driver has enabled PS-Poll, else FALSE
  	
  Remarks:
  	None.
  *****************************************************************************/
BOOL WFIsPsPollActive(void)
{
    return g_psPollActive;
}    

/*******************************************************************************
  Function:	
    void EnsureWFisAwake()

  Summary:
    If PS-Poll is active or the MRF24WB0M is asleep, ensure that it is woken up.

  Description:
    Called by the WiFi driver when it needs to transmit or receive a data or 
    mgmt message. If the application has enabled PS-Poll mode and the WiFi 
    driver has activated PS-Poll mode then this function will deactivate PS-Poll
    mode and wake up the MRF24WB0M.

  Precondition:
  	MACInit must be called first.

  Parameters:
    None.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void EnsureWFisAwake()
{
    /* if the application desires the MRF24WB0M to be in PS-Poll mode (PS-Poll with DTIM enabled or disabled */
    if ((g_powerSaveState == WF_PS_PS_POLL_DTIM_ENABLED) || (g_powerSaveState == WF_PS_PS_POLL_DTIM_DISABLED)) 
    {
        /* if the WF driver has activated PS-Poll */
        if (g_psPollActive == TRUE)
        {
            /* wake up MRF24WB0M */
            WFConfigureLowPowerMode(WF_LOW_POWER_MODE_OFF);
        }    
    }
}        
            
/*******************************************************************************
  Function:	
    void WF_HibernateEnable()

  Summary:
    Puts the MRF24WB0M into hibernate mode.

  Description:
    Enables Hibernate mode on the MRF24WB0M, which effectively turns off the 
    device for maximum power savings.  

    MRF24WB0M state is not maintained when it transitions to hibernate mode.  
    To remove the MRF24WB0M from hibernate mode call WF_Init().

  Precondition:
  	MACInit must be called first.

  Parameters:
    None.

  Returns:
  	None.
  	
  Remarks:
  	Note that because the MRF24WB0M does not save state, there will be a
    disconnect between the TCP/IP stack and the MRF24B0M state.  If it is
    desired by the application to use hibernate, additional measures must be
    taken to save application state.  Then the host should be reset.  This will
    ensure a clean connection between MRF24WB0M and TCP/IP stack

    Future versions of the stack might have the ability to save stack context
    as well, ensuring a clean wake up for the MRF24WB0M without needing a host
    reset.
  *****************************************************************************/
void WF_HibernateEnable()
{
    WF_SetCE_N(WF_HIGH);   /* set XCEN33 pin high, which puts MRF24WB0M in hibernate mode */

    SetPowerSaveState(WF_PS_HIBERNATE);
}

/*******************************************************************************
  Function:	
    static void SendPowerModeMsg(tWFPwrModeReq *p_powerMode)

  Summary:
    Send power mode management message to the MRF24WB0M.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_powerMode -- pointer to tWFPwrModeReq structure to send to MRF24WB0M.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
static void SendPowerModeMsg(tWFPwrModeReq *p_powerMode)
{
    UINT8 hdr[2];
    
    hdr[0] = WF_MGMT_REQUEST_TYPE;
    hdr[1] = WF_SET_POWER_MODE_SUBTYPE;

    SendMgmtMsg(hdr,
                sizeof(hdr),
               (UINT8 *)p_powerMode,
               sizeof(tWFPwrModeReq));

    /* wait for mgmt response, free buffer after it comes in (no data to read) */
	WaitForMgmtResponse(WF_SET_POWER_MODE_SUBTYPE, FREE_MGMT_BUFFER);
    
}    

/*******************************************************************************
  Function:	
    static void SetPowerSaveState(UINT8 powerSaveState)

  Summary:
    Sets the desired power save state of the MRF24WB0M.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    powerSaveState -- value of the power save state desired.

    <table>
    Value                       Definition
    -----                       ----------
    WF_PS_HIBERNATE             MRF24WB0M in hibernate state
    WF_PS_PS_POLL_DTIM_ENABLED  MRF24WB0M in PS-Poll mode with DTIM enabled
    WF_PS_PS_POLL_DTIM_DISABLED MRF24WB0M in PS-Poll mode with DTIM disabled
    WF_PS_POLL_OFF              MRF24WB0M is not in any power-save state
    </table>

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
static void SetPowerSaveState(UINT8 powerSaveState)
{
    g_powerSaveState = powerSaveState;
}    
#endif /* WF_CS_TRIS && WF_USE_POWER_SAVE_FUNCTIONS */
