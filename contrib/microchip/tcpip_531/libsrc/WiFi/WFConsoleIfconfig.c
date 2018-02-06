/******************************************************************************

 MRF24WB0M Driver ifconfig
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFConsoleIfconfig.c
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

//============================================================================
//                                  Includes
//============================================================================
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "TCPIP_Stack/TCPIP.h"
#include "TCPIP_Stack/WFConsole.h"

#if defined( WF_CONSOLE_IFCFGUTIL )

#include "TCPIP_Stack/WFConsoleIfconfig.h"
#include "TCPIP_Stack/WFConsoleMsgs.h"
#include "TCPIP_Stack/WFConsoleMsgHandler.h"

//============================================================================
//                                  Constants
//============================================================================

//============================================================================
//                                  Globals
//============================================================================

//============================================================================
//                                  Local Function Prototypes
//============================================================================
static void IfconfigDisplayStatus(void);
static BOOL       isIPAddress(INT8 *p_string, UINT8 *p_Address);
static BOOL       isMacAddress(INT8 *p_string, UINT8 *p_Address);
#if defined(STACK_USE_DHCP_CLIENT)
static void setDHCPState(BOOL enable);
#endif
static void missingValue(void);
static void notHandledParam(UINT8 index);

void LCDDisplayIPValue(IP_ADDR IPVal)
{
#ifdef USE_LCD

    BYTE IPDigit[4];
    BYTE i;
    BYTE j;
    BYTE LCDPos=16;

    for(i = 0; i < sizeof(IP_ADDR); i++)
    {
        uitoa((WORD)IPVal.v[i], IPDigit);

        for(j = 0; j < strlen((char*)IPDigit); j++)
        {
            LCDText[LCDPos++] = IPDigit[j];
        }
        if(i == sizeof(IP_ADDR)-1)
            break;
        LCDText[LCDPos++] = '.';
    }


    if(LCDPos < 32u)
        LCDText[LCDPos] = 0;
    LCDUpdate();

#endif
}

/*****************************************************************************
 * FUNCTION: do_ifconfig_cmd
 *
 * RETURNS: None
 *
 * PARAMS:  None
 *
 * NOTES:   Responds to the user invoking ifconfig
 *****************************************************************************/
void do_ifconfig_cmd(void)
{
     UINT8   address[6];
     UINT8 conState, cpId;

    // if user only typed in ifconfig with no other parameters
    if (ARGC == 1u)
    {
        IfconfigDisplayStatus();
    }
#if defined(WF_CM_DEBUG)
	else if ( (ARGC == 2u) && !strcmp((char *) ARGV[1], "info") )
	{
        UINT8 i;
		tWFCMInfoFSMStats cm_stats;

		WF_CMInfoGetFSMStats(&cm_stats);
		for (i = 0; i < 12; i++)
		{
    		sprintf( (char *) g_ConsoleContext.txBuf,
            		"[%02X]: %02X%02X %02X%02X",   
					i, 
					cm_stats.byte[i*4 + 0],
					cm_stats.byte[i*4 + 1],
					cm_stats.byte[i*4 + 2],
					cm_stats.byte[i*4 + 3]
					);
    		WFConsolePrintRamStr( (char *) g_ConsoleContext.txBuf , TRUE);
		}
	}
	else if ( (ARGC == 2u) && !strcmp((char *) ARGV[1], "scan") )
	{
		WF_Scan(1); // scan, using CP 1
	}
	else if ( (ARGC == 2u) && !strcmp((char *) ARGV[1], "scanget") ) //"scangetresult"
	{
		tWFScanResult pScanResult[1];

		WF_ScanGetResult(0, pScanResult);
	}
	else if ( (ARGC == 2u) && !strcmp((char *) ARGV[1], "cpgete") ) //"cpgetelements"
	{
		tWFCPElements pCPElements[1];

		WF_CPGetElements(1, pCPElements);
	}
#endif
    // else if 2 arguments and the second arg is IP address
    else if ( (ARGC == 2u) && (isIPAddress(ARGV[1], address)) )
    {
        #if defined(STACK_USE_DHCP_CLIENT)
        if (DHCPIsEnabled(0))
        {
          WFConsolePrintRomStr(
                     "Static IP address should not be set with DHCP enabled", TRUE);
          return;
        }
        #endif

        AppConfig.MyIPAddr.v[0] = address[0];
        AppConfig.MyIPAddr.v[1] = address[1];
        AppConfig.MyIPAddr.v[2] = address[2];
        AppConfig.MyIPAddr.v[3] = address[3];

        /* Microchip DHCP client clobbers static ip on every iteration of loop, even if dhcp is turned off*/
        AppConfig.DefaultIPAddr.v[0] = address[0];
        AppConfig.DefaultIPAddr.v[1] = address[1];
        AppConfig.DefaultIPAddr.v[2] = address[2];
        AppConfig.DefaultIPAddr.v[3] = address[3];

        LCDDisplayIPValue(AppConfig.MyIPAddr);
    }
    // else if 2 args and second arg is MAC address
    else if ( (ARGC == 2u) && isMacAddress(ARGV[1], address))
    {
        /* Can only set MAC address in idle state */
        WF_CMGetConnectionState(&conState, &cpId);
        if ( conState != WF_CSTATE_NOT_CONNECTED )
        {
            WFConsolePrintRomStr("HW MAC address can only be set in idle mode", TRUE);
            return;
        }

         WF_SetMacAddress( address );
    }
	else if ( (2u <= ARGC) && (strcmppgm2ram((char *)ARGV[1], (ROM FAR char *)"netmask") == 0) )
	{
		if (ARGC != 3u)
		{
			missingValue();
			return;
		}

        #if defined(STACK_USE_DHCP_CLIENT)
        if ( DHCPIsEnabled(0) )
        {
            WFConsolePrintRomStr(
                "The Netmask should not be set with DHCP enabled", TRUE);
            return;
        }
        #endif

        if ( !isIPAddress(ARGV[2], address) )
        {
            WFConsolePrintRomStr("Invalid netmask value", TRUE);
            return;
        }

        AppConfig.MyMask.v[0] = address[0];
        AppConfig.MyMask.v[1] = address[1];
        AppConfig.MyMask.v[2] = address[2];
        AppConfig.MyMask.v[3] = address[3];

        /* Microchip DHCP client clobbers static netmask on every iteration of loop, even if dhcp is turned off*/
        AppConfig.DefaultMask.v[0] = address[0];
        AppConfig.DefaultMask.v[1] = address[1];
        AppConfig.DefaultMask.v[2] = address[2];
        AppConfig.DefaultMask.v[3] = address[3];  
	}
	else if ( (2u <= ARGC) && (strcmppgm2ram((char *)ARGV[1], (ROM FAR char *)"gateway") == 0) )
	{
		if (ARGC != 3u)
		{
			missingValue();
			return;
		}

        if ( !isIPAddress(ARGV[2], address) )
        {
            WFConsolePrintRomStr("Invalid gateway value", TRUE);
            return;
        }

        AppConfig.MyGateway.v[0] = address[0];
        AppConfig.MyGateway.v[1] = address[1];
        AppConfig.MyGateway.v[2] = address[2];
        AppConfig.MyGateway.v[3] = address[3];
	}
	else if ( (2u <= ARGC) && (strcmppgm2ram((char*)ARGV[1], "auto-dhcp") == 0) )
	{
		if (ARGC != 3u)
		{
			missingValue();
			return;
		}

        #if defined(STACK_USE_DHCP_CLIENT)
		if (strcmppgm2ram((char*)ARGV[2], "start") == 0)
		{
			setDHCPState(TRUE);
		}
		else if (strcmppgm2ram((char*)ARGV[2], "stop") == 0)
		{
			setDHCPState(FALSE);
		}
		else
		#endif
		{
			WFConsolePrintRomStr("   Invalid dhcp param", TRUE);
			return;
		}
	}
    else
    {
        notHandledParam(1);
	}
}

static void missingValue(void)
{
    WFConsolePrintRomStr(
        "Missing value after last parameter", TRUE);
}

static void notHandledParam(UINT8 index)
{
    WFConsolePrintRomStr("Param ", FALSE);
	WFConsolePrintInteger(index, 'd');
	WFConsolePrintRomStr(" not handled", TRUE);
}

/*****************************************************************************
 * FUNCTION: isIPAddress
 *
 * RETURNS: True if valid IP address, else False
 *
 * PARAMS:    p_string  -- string to check
 *          p_Address -- Array where IP values will be written
 *
 * NOTES:   Determines if the input string is a valid dot-notation IP address.
 *          If it is, then returns an array of 4 bytes for each of the values.
 *          IP address
 *****************************************************************************/

static BOOL isIPAddress(INT8 *p_string, UINT8 *p_Address)
{
    UINT8 digIndex = 0;
    UINT8 bufIndex = 0;
    UINT8 dotCount = 0;
    INT8 buf[4];
    UINT8  i;
    UINT16 tmp;

    memset(buf, 0x00, sizeof(buf));
    for (i = 0; i < strlen((char *)p_string); ++i)
    {
        // if gathering digits
        if (isdigit(p_string[i]))
        {
            // store digit in buf, fail if user has more than 3 digits
            buf[bufIndex++] = p_string[i];
            if (bufIndex > 3u)
            {
                return FALSE;
            }
        }
        // else encountered a dot
        else if (p_string[i] == (INT8)'.')
        {
            // keep track of dots and fail if we encounter too many of them
            ++dotCount;
            if (dotCount > 3u)
            {
                return FALSE;
            }

            // convert the number we just pulled from the input string, fail if not a number
            if (!ConvertASCIIUnsignedDecimalToBinary(buf, &tmp))
            {
                return FALSE;
            }
            // else a valid number
            else
            {
                // fail if greater than 255
                if ( tmp > 255u)
                {
                    return FALSE;
                }

                 p_Address[digIndex] = (UINT8) (tmp & 0xFF);

                // get ready for next number
                memset(buf, 0x00, sizeof(buf));
                bufIndex = 0;
                ++digIndex;
            }
        }
        // else got a character that is neither number nor dot
        else
        {
            return FALSE;
        }

    }

    // fail if more than 3 dots
    if (dotCount != 3u)
    {
        return FALSE;
    }

    // if made it here then make sure we have the last number
    if (buf[0] == 0)
    {
        return FALSE;
    }

    // convert last number to binary, fail if we can't
    if (!ConvertASCIIUnsignedDecimalToBinary(buf, &tmp))
    {
        return FALSE;
    }

    p_Address[digIndex] = (UINT8) (tmp & 0xFF);

    // IP digits will be in p_Address[]
    return TRUE;
}


/*****************************************************************************
 * FUNCTION: isMacAddress
 *
 * RETURNS: True if valid MAC address, else False
 *
 * PARAMS:    p_string  -- string to check
 *          p_Address -- Array where MAC values will be written
 *
 * NOTES:   Determines if the input string is a valid MAC address.
 *          If it is, then returns an array of 6 bytes for each of the values.
 *          MAC address must be in hex in the format xx:xx:xx:xx:xx:xx
 *****************************************************************************/
static BOOL isMacAddress(INT8 *p_string, UINT8 *p_Address)
{
    UINT8 i;
    UINT16 tmp;

    if (strlen((char *)p_string) != 17u)
    {
        return FALSE;
    }

    // ensure the ':' is in the right place, and if so, set them to 0
    for (i = 2; i < 17u; i += 3)
    {
        if (p_string[i] == (INT8)':')
        {
            p_string[i] = '\0';
        }
        else
        {
            return FALSE;
        }
    }

    // now extract each hex number string
    for (i = 0; i < 6u;  ++i)
    {
        if (!ConvertASCIIHexToBinary(&p_string[i * 3], &tmp))
        {
            return FALSE;
        }

        p_Address[i] = (UINT8) (tmp & 0xFF);

    }

    return TRUE;
}

/*****************************************************************************
 * FUNCTION: IfconfigDisplayStatus
 *
 * RETURNS: None
 *
 * PARAMS:    None
 *
 * NOTES:   Responds to the user invoking ifconfig with no parameters
 *****************************************************************************/
static void IfconfigDisplayStatus(void)
{
    sprintf( (char *) g_ConsoleContext.txBuf,
              "\tIP addr:  %d.%d.%d.%d",   AppConfig.MyIPAddr.v[0],
                                           AppConfig.MyIPAddr.v[1],
                                           AppConfig.MyIPAddr.v[2],
                                           AppConfig.MyIPAddr.v[3] );
    WFConsolePrintRamStr( (char *) g_ConsoleContext.txBuf , TRUE);


    sprintf( (char *) g_ConsoleContext.txBuf,
             "\tMAC addr: %02X:%02X:%02X:%02X:%02X:%02X",   AppConfig.MyMACAddr.v[0],
                                                            AppConfig.MyMACAddr.v[1],
                                                            AppConfig.MyMACAddr.v[2],
                                                            AppConfig.MyMACAddr.v[3],
                                                            AppConfig.MyMACAddr.v[4],
                                                            AppConfig.MyMACAddr.v[5]);
    WFConsolePrintRamStr( (char *) g_ConsoleContext.txBuf , TRUE);



    sprintf( (char *) g_ConsoleContext.txBuf,
              "\tNetmask:  %d.%d.%d.%d",   AppConfig.MyMask.v[0],
                                           AppConfig.MyMask.v[1],
                                           AppConfig.MyMask.v[2],
                                           AppConfig.MyMask.v[3] );
    WFConsolePrintRamStr( (char *) g_ConsoleContext.txBuf , TRUE);


    sprintf( (char *) g_ConsoleContext.txBuf,
              "\tGateway:  %d.%d.%d.%d",   AppConfig.MyGateway.v[0],
                                           AppConfig.MyGateway.v[1],
                                           AppConfig.MyGateway.v[2],
                                           AppConfig.MyGateway.v[3] );
    WFConsolePrintRamStr( (char *) g_ConsoleContext.txBuf , TRUE);

    #if defined(STACK_USE_DHCP_CLIENT)
    if ( DHCPIsEnabled(0) )
       WFConsolePrintRomStr("\tDHCP:     Started", TRUE);
    else
       WFConsolePrintRomStr("\tDHCP:     Stopped", TRUE);
    #endif
}

#if defined(STACK_USE_DHCP_CLIENT)
/*****************************************************************************
 * FUNCTION: setDHCPState
 *
 * RETURNS: None
 *
 * PARAMS:  enable -- a boolean indicating whether to enable DHCP or not
 *
 * NOTES:   Enable or disable DHCP operation
 *****************************************************************************/
static void setDHCPState(BOOL enable)
{
    if ( enable )
    {
        AppConfig.Flags.bIsDHCPEnabled = TRUE;
        DHCPEnable(0);
    }
    else
    {
        AppConfig.Flags.bIsDHCPEnabled = FALSE;
        DHCPDisable(0);
    }
}
#endif

#endif /* WF_CONSOLE_IFCFGUTIL */


