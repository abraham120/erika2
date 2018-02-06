/******************************************************************************

 MRF24WB0M Driver Initialization
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WF_Init.c
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
 KH                 27 Jan 2010 Updated for MRF24WB0M
******************************************************************************/

/*
*********************************************************************************************************
*                                           INCLUDES                               
*********************************************************************************************************
*/

#include "TCPIP_Stack/TCPIP.h"
#include "TCPIP_Stack/WFMac.h"

#if defined(WF_CS_TRIS)


/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/

/* used for assertions */
#if defined(WF_DEBUG)
    #define WF_MODULE_NUMBER    WF_MODULE_WF_INIT
#endif

#define EXPECTED_MRF24WB0M_VERSION_NUMBER      (2)

/* This MAC address is the default MAC address used in TCPIPConfig.h.  If the */
/* user leaves this MAC address unchanged then the WiFi Driver will get the   */
/* unique MAC address from the MRF24WB0M and have the stack use it.           */
#define MCHP_DEFAULT_MAC_ADDRESS_BYTE_1     (0x00)
#define MCHP_DEFAULT_MAC_ADDRESS_BYTE_2     (0x04)
#define MCHP_DEFAULT_MAC_ADDRESS_BYTE_3     (0xa3)
#define MCHP_DEFAULT_MAC_ADDRESS_BYTE_4     (0x00)
#define MCHP_DEFAULT_MAC_ADDRESS_BYTE_5     (0x00)
#define MCHP_DEFAULT_MAC_ADDRESS_BYTE_6     (0x00)


/*
*********************************************************************************************************
*                                           LOCAL GLOBAL VARIABLES                               
*********************************************************************************************************
*/

/* This MAC address is the default MAC address used in TCPIPConfig.h.  If the */
/* user leaves this MAC address unchanged then the WiFi Driver will get the  */
/* unique MAC address from the MRF24WB0M and have the stack use it.              */
static const UINT8 MchpDefaultMacAddress[WF_MAC_ADDRESS_LENGTH] = {0x00u, 0x04u, 0xA3u, 0x00u, 0x00u, 0x00u};


/*
*********************************************************************************************************
*                                           LOCAL FUNCTION PROTOTYPES                              
*********************************************************************************************************
*/

static void WF_LibInitialize(void);


/*****************************************************************************
 * FUNCTION: WF_Init
 *
 * RETURNS: None
 *
 * PARAMS:
 *      N/A.
 *
 *
 *  NOTES: This function must be called once prior to calling any other WF...
 *          functions.  This function initializes the Wifi Driver internal State.
 *          It also verifies functionality of the lower level SPI driver and
 *          connected hardware.
 *****************************************************************************/
void WF_Init(void)
{
    UINT8  version;

    /* initialize WiFi drivers, reset MRF24WB0M */
    WFHardwareInit();

    RawInit();

    WFGetMRF24WB0MVersion(&version);
    WF_ASSERT(version >= EXPECTED_MRF24WB0M_VERSION_NUMBER);
  
    WFEnableMRF24WB0MMode();
  
    /* send init messages to MRF24WB0M */
    WF_LibInitialize();
}


extern void WFMgmtMessageTest();
/*****************************************************************************
 * FUNCTION: WF_LibInitialize
 *
 * RETURNS:  None
 *
 * PARAMS:   None
 *
 *  NOTES:   Performs initialization which is specific to the Microchip Demo code.
 *****************************************************************************/
static void WF_LibInitialize()
{
    
    /* Disable Tx Data confirms (from the MRF24WB0M) */
    WF_SetTxDataConfirm(WF_DISABLED);

#if defined(WF_USE_POWER_SAVE_FUNCTIONS)    
    /* Disable power management */
    WF_PsPollDisable();
#endif

    /* if the user has left the default MAC address in TCPIPConfig.h unchanged then use */
    /* the unique MRF24WB0M MAC address so prevent multiple devices from having the same   */
    /* MAC address.                                                                     */
    if ( memcmp((void *)AppConfig.MyMACAddr.v, (void *)MchpDefaultMacAddress, WF_MAC_ADDRESS_LENGTH) == 0)
    {
        /* get the MRF24WB0M MAC address and overwrite the MAC in AppConfig */
        WF_GetMacAddress((UINT8 *)AppConfig.MyMACAddr.v);
    }
    /* else presume the user has a unique MAC address of their own that they wish to use */    
    else
    {
        // set MAC address with user-supplied MAC */
        WF_SetMacAddress((UINT8 *)AppConfig.MyMACAddr.v);
    }    
    
    #ifdef WF_CONFIG_DHCP
    WF_SET_DHCP_STATE(DHCP_ENABLED);
    #endif
}



#endif /* WF_CS_TRIS */

