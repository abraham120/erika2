/*********************************************************************
 *
 *  Legacy Demo Code for:
 *	  - Classic HTTP server
 *    - FTP uploads of MPFS image
 *
 *********************************************************************
 * FileName:        LegacyHTTPApp.c
 * Dependencies:    TCP/IP stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date      Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * E. Wood     			4/26/08	  Moved from MainDemo.c
 ********************************************************************/
#define __LEGACYHTTPAPP_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_HTTP_SERVER)

#include "TCPIP Stack/TCPIP.h"
#include "MainDemo.h"

extern BYTE AN0String[8];

//////////////////////////////////////////////////////////////////////////////////////////
// NOTE: The following HTTP code pretains to the old HTTP server.
//       Upgrading to HTTP2 is *strongly* recommended for all new designs.
//       Custom control of HTTP2 is implemented in CustomHTTPApp.c
//////////////////////////////////////////////////////////////////////////////////////////

// CGI Command Codes
#define CGI_CMD_DIGOUT      (0)
#define CGI_CMD_LCDOUT      (1)
#define CGI_CMD_RECONFIG	(2)

// CGI Variable codes. - There could be 00h-FFh variables.
// NOTE: When specifying variables in your dynamic pages (.cgi),
//       use the hexadecimal numbering scheme and always zero pad it
//       to be exactly two characters.  Eg: "%04", "%2C"; not "%4" or "%02C"
#define VAR_LED0			(0x00)	// LED Outputs
#define VAR_LED1			(0x01)
#define VAR_LED2			(0x10)
#define VAR_LED3			(0x11)
#define VAR_LED4			(0x12)
#define VAR_LED5			(0x13)
#define VAR_LED6			(0x14)
#define VAR_LED7			(0x15)
#define VAR_ANAIN_AN0       (0x02)	// Analog Inputs (POT, temp, etc)
#define VAR_ANAIN_AN1       (0x03)
#define VAR_DIGIN0       	(0x04)	// Momentary push button inputs
#define VAR_DIGIN1       	(0x0D)
#define VAR_DIGIN2       	(0x0E)
#define VAR_DIGIN3       	(0x0F)
#define VAR_STACK_VERSION	(0x16)	// Stack constants
#define VAR_STACK_DATE		(0x17)
#define VAR_STROUT_LCD      (0x05)	// LCD Display output
#define VAR_MAC_ADDRESS     (0x06)	// Stack configuration variables
#define VAR_SERIAL_NUMBER   (0x07)
#define VAR_IP_ADDRESS      (0x08)
#define VAR_SUBNET_MASK     (0x09)
#define VAR_GATEWAY_ADDRESS (0x0A)
#define VAR_DHCP	        (0x0B)	// Use this variable when the web page is updating us
#define VAR_DHCP_TRUE       (0x0B)	// Use this variable when we are generating the web page
#define VAR_DHCP_FALSE      (0x0C)	// Use this variable when we are generating the web page


// CGI Command codes (CGI_CMD_DIGOUT).
// Should be a one digit numerical value
#define CMD_LED1			(0x0)
#define CMD_LED2			(0x1)


/*********************************************************************
 * Function:        void HTTPExecCmd(BYTE** argv, BYTE argc)
 *
 * PreCondition:    None
 *
 * Input:           argv        - List of arguments
 *                  argc        - Argument count.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a "callback" from HTTPServer
 *                  task.  Whenever a remote node performs
 *                  interactive task on page that was served,
 *                  HTTPServer calls this functions with action
 *                  arguments info.
 *                  Main application should interpret this argument
 *                  and act accordingly.
 *
 *                  Following is the format of argv:
 *                  If HTTP action was : thank.htm?name=Joe&age=25
 *                      argv[0] => thank.htm
 *                      argv[1] => name
 *                      argv[2] => Joe
 *                      argv[3] => age
 *                      argv[4] => 25
 *
 *                  Use argv[0] as a command identifier and rests
 *                  of the items as command arguments.
 *
 * Note:            THIS FUNCTION IS DEPRECATED BY HTTP2
 ********************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////
// NOTE: The following HTTP code pretains to the old HTTP server.
//       Upgrading to HTTP2 is *strongly* recommended for all new designs.
//       Custom control of HTTP2 is implemented in CustomHTTPApp.c
//////////////////////////////////////////////////////////////////////////////////////////
ROM char COMMANDS_OK_PAGE[] = "INDEX.CGI";
ROM char CONFIG_UPDATE_PAGE[] = "CONFIG.CGI";
ROM char CMD_UNKNOWN_PAGE[] = "INDEX.CGI";

// Copy string with NULL termination.
#define COMMANDS_OK_PAGE_LEN  	(sizeof(COMMANDS_OK_PAGE))
#define CONFIG_UPDATE_PAGE_LEN  (sizeof(CONFIG_UPDATE_PAGE))
#define CMD_UNKNOWN_PAGE_LEN    (sizeof(CMD_UNKNOWN_PAGE))
void HTTPExecCmd(BYTE** argv, BYTE argc)
{
    BYTE command;
    BYTE var;
#if defined(ENABLE_REMOTE_CONFIG)
	DWORD_VAL dwVal;
    BYTE CurrentArg;
    WORD_VAL TmpWord;
#endif
    /*
     * Design your pages such that they contain command code
     * as a one character numerical value.
     * Being a one character numerical value greatly simplifies
     * the job.
     */
    command = argv[0][0] - '0';

    /*
     * Find out the cgi file name and interpret parameters
     * accordingly
     */
    switch(command)
    {
    case CGI_CMD_DIGOUT:	// ACTION=0
        /*
         * Identify the parameters.
         * Compare it in upper case format.
         */
        var = argv[1][0] - '0';

        switch(var)
        {
        case CMD_LED1:	// NAME=0
            // Toggle LED.
            LED1_IO ^= 1;
            break;

        case CMD_LED2:	// NAME=1
            // Toggle LED.
            LED2_IO ^= 1;
            break;
         }

         memcpypgm2ram((void*)argv[0], (ROM void*)COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);
         break;
#if defined(USE_LCD)
    case CGI_CMD_LCDOUT:	// ACTION=1
		if(argc > 2u)	// Text provided in argv[2]
		{
			// Convert %20 to spaces, and other URL transformations
			UnencodeURL(argv[2]);

			// Write 32 received characters or less to LCDText
			if(strlen((char*)argv[2]) < 32u)
			{
				memset(LCDText, ' ', 32);
				strcpy((char*)LCDText, (char*)argv[2]);
			}
			else
			{
				memcpy(LCDText, (void*)argv[2], 32);
			}

			// Write LCDText to the LCD
			LCDUpdate();
		}
		else			// No text provided
		{
			LCDErase();
		}
		memcpypgm2ram((void*)argv[0], (ROM void*)COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);
        break;
#endif
#if defined(ENABLE_REMOTE_CONFIG)
// Possibly useful code for remotely reconfiguring the board through 
// HTTP
	case CGI_CMD_RECONFIG:	// ACTION=2
		// Loop through all variables that we've been given
		CurrentArg = 1;
		while(argc > CurrentArg)
		{
			// Get the variable identifier (HTML "name"), and 
			// increment to the variable's value
			TmpWord.v[1] = argv[CurrentArg][0];
			TmpWord.v[0] = argv[CurrentArg++][1];
	        var = hexatob(TmpWord);
	        
	        // Make sure the variable's value exists
	        if(CurrentArg >= argc)
	        	break;
	        
	        // Take action with this variable/value
	        switch(var)
	        {
	        case VAR_IP_ADDRESS:
	        case VAR_SUBNET_MASK:
	        case VAR_GATEWAY_ADDRESS:
	        	{
		        	// Convert the returned value to the 4 octect 
		        	// binary representation
			        if(!StringToIPAddress(argv[CurrentArg], (IP_ADDR*)&dwVal))
			        	break;

					// Reconfigure the App to use the new values
			        if(var == VAR_IP_ADDRESS)
			        {
				        // Cause the IP address to be rebroadcast
				        // through Announce.c or the RS232 port since
				        // we now have a new IP address
				        if(dwVal.Val != *(DWORD*)&AppConfig.MyIPAddr)
					        DHCPBindCount++;
					    
					    // Set the new address
			        	memcpy((void*)&AppConfig.MyIPAddr, (void*)&dwVal, sizeof(AppConfig.MyIPAddr));
			        }
			        else if(var == VAR_SUBNET_MASK)
			        	memcpy((void*)&AppConfig.MyMask, (void*)&dwVal, sizeof(AppConfig.MyMask));
			        else if(var == VAR_GATEWAY_ADDRESS)
			        	memcpy((void*)&AppConfig.MyGateway, (void*)&dwVal, sizeof(AppConfig.MyGateway));
		        }
	            break;
	
	        case VAR_DHCP:
	        	if(AppConfig.Flags.bIsDHCPEnabled)
	        	{
		        	if(!(argv[CurrentArg][0]-'0'))
		        	{
		        		AppConfig.Flags.bIsDHCPEnabled = FALSE;
		        	}
		        }
		        else
	        	{
		        	if(argv[CurrentArg][0]-'0')
		        	{
						AppConfig.MyIPAddr.Val = 0x00000000ul;
		        		AppConfig.Flags.bIsDHCPEnabled = TRUE;
				        AppConfig.Flags.bInConfigMode = TRUE;
			        	DHCPInit(0);
		        	}
		        }
	            break;
	    	}

			// Advance to the next variable (if present)
			CurrentArg++;	
        }
		
		// Save any changes to non-volatile memory
      	SaveAppConfig(&AppConfig);


		// Return the same CONFIG.CGI file as a result.
        memcpypgm2ram((void*)argv[0],
             (ROM void*)CONFIG_UPDATE_PAGE, CONFIG_UPDATE_PAGE_LEN);
		break;
#endif	// #if defined(ENABLE_REMOTE_CONFIG)

    default:
		memcpypgm2ram((void*)argv[0], (ROM void*)COMMANDS_OK_PAGE, COMMANDS_OK_PAGE_LEN);
        break;
    }

}


/*********************************************************************
 * Function:        WORD HTTPGetVar(BYTE var, WORD ref, BYTE* val)
 *
 * PreCondition:    None
 *
 * Input:           var         - Variable Identifier
 *                  ref         - Current callback reference with
 *                                respect to 'var' variable.
 *                  val         - Buffer for value storage.
 *
 * Output:          Variable reference as required by application.
 *
 * Side Effects:    None
 *
 * Overview:        This is a callback function from HTTPServer() to
 *                  main application.
 *                  Whenever a variable substitution is required
 *                  on any html pages, HTTPServer calls this function
 *                  8-bit variable identifier, variable reference,
 *                  which indicates whether this is a first call or
 *                  not.  Application should return one character
 *                  at a time as a variable value.
 *
 * Note:            Since this function only allows one character
 *                  to be returned at a time as part of variable
 *                  value, HTTPServer() calls this function
 *                  multiple times until main application indicates
 *                  that there is no more value left for this
 *                  variable.
 *                  On begining, HTTPGetVar() is called with
 *                  ref = HTTP_START_OF_VAR to indicate that
 *                  this is a first call.  Application should
 *                  use this reference to start the variable value
 *                  extraction and return updated reference.  If
 *                  there is no more values left for this variable
 *                  application should send HTTP_END_OF_VAR.  If
 *                  there are any bytes to send, application should
 *                  return other than HTTP_START_OF_VAR and
 *                  HTTP_END_OF_VAR reference.
 *
 *                  THIS FUNCTION IS DEPRECATED BY HTTP2
 ********************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////
// NOTE: The following HTTP code pretains to the old HTTP server.
//       Upgrading to HTTP2 is *strongly* recommended for all new designs.
//       Custom control of HTTP2 is implemented in CustomHTTPApp.c
//////////////////////////////////////////////////////////////////////////////////////////
WORD HTTPGetVar(BYTE var, WORD ref, BYTE* val)
{
	// Temporary variables designated for storage of a whole return 
	// result to simplify logic needed since one byte must be returned
	// at a time.
	static BYTE VarString[25];
#if defined(ENABLE_REMOTE_CONFIG)
	static BYTE VarStringLen;
	BYTE *VarStringPtr;

	BYTE i;
	BYTE *DataSource;
#endif
	
	// Identify variable
    switch(var)
    {
    case VAR_LED0:
        *val = LED0_IO ? '1':'0';
        break;
    case VAR_LED1:
        *val = LED1_IO ? '1':'0';
        break;
    case VAR_LED2:
        *val = LED2_IO ? '1':'0';
        break;
    case VAR_LED3:
        *val = LED3_IO ? '1':'0';
        break;
    case VAR_LED4:
        *val = LED4_IO ? '1':'0';
        break;
    case VAR_LED5:
        *val = LED5_IO ? '1':'0';
        break;
    case VAR_LED6:
        *val = LED6_IO ? '1':'0';
        break;
    case VAR_LED7:
        *val = LED7_IO ? '1':'0';
        break;

    case VAR_ANAIN_AN0:
        *val = AN0String[(BYTE)ref];
        if(AN0String[(BYTE)ref] == '\0')
            return HTTP_END_OF_VAR;
		else if(AN0String[(BYTE)++ref] == '\0' )
            return HTTP_END_OF_VAR;
        return ref;
//    case VAR_ANAIN_AN1:
//        *val = AN1String[(BYTE)ref];
//        if(AN1String[(BYTE)ref] == '\0')
//            return HTTP_END_OF_VAR;
//		else if(AN1String[(BYTE)++ref] == '\0' )
//            return HTTP_END_OF_VAR;
//        return ref;

    case VAR_DIGIN0:
        *val = BUTTON0_IO ? '1':'0';
        break;
    case VAR_DIGIN1:
        *val = BUTTON1_IO ? '1':'0';
        break;
    case VAR_DIGIN2:
        *val = BUTTON2_IO ? '1':'0';
        break;
    case VAR_DIGIN3:
        *val = BUTTON3_IO ? '1':'0';
        break;

	case VAR_STACK_VERSION:
        if(ref == HTTP_START_OF_VAR)
		{
			strncpypgm2ram((char*)VarString, (ROM char*)TCPIP_STACK_VERSION, sizeof(VarString));
		}
        *val = VarString[(BYTE)ref];
        if(VarString[(BYTE)ref] == '\0')
            return HTTP_END_OF_VAR;
		else if(VarString[(BYTE)++ref] == '\0' )
            return HTTP_END_OF_VAR;
        return ref;
	case VAR_STACK_DATE:
        if(ref == HTTP_START_OF_VAR)
		{
			strncpypgm2ram((char*)VarString, (ROM char*)(__DATE__ " " __TIME__), sizeof(VarString));
		}
        *val = VarString[(BYTE)ref];
        if(VarString[(BYTE)ref] == '\0')
            return HTTP_END_OF_VAR;
		else if(VarString[(BYTE)++ref] == '\0' )
            return HTTP_END_OF_VAR;
        return ref;

#if defined(ENABLE_REMOTE_CONFIG)
    case VAR_MAC_ADDRESS:
        if ( ref == HTTP_START_OF_VAR )
        {
            VarStringLen = 2*6+5;	// 17 bytes: 2 for each of the 6 address bytes + 5 octet spacers

	        // Format the entire string
            i = 0;
            VarStringPtr = VarString;
            while(1)
            {
	            *VarStringPtr++ = btohexa_high(AppConfig.MyMACAddr.v[i]);
	            *VarStringPtr++ = btohexa_low(AppConfig.MyMACAddr.v[i]);
	            if(++i == 6)
	            	break;
	            *VarStringPtr++ = '-';
	        }
        }

		// Send one byte back to the calling function (the HTTP Server)
		*val = VarString[(BYTE)ref];
		
        if ( (BYTE)++ref == VarStringLen )
            return HTTP_END_OF_VAR;

        return ref;
    		
    case VAR_IP_ADDRESS:
    case VAR_SUBNET_MASK:
    case VAR_GATEWAY_ADDRESS:
    	// Check if ref == 0 meaning that the first character of this 
    	// variable needs to be returned
        if ( ref == HTTP_START_OF_VAR )
        {
	        // Decide which 4 variable bytes to send back
	        if(var == VAR_IP_ADDRESS)
		    	DataSource = (BYTE*)&AppConfig.MyIPAddr;
		    else if(var == VAR_SUBNET_MASK)
		    	DataSource = (BYTE*)&AppConfig.MyMask;
		    else if(var == VAR_GATEWAY_ADDRESS)
		    	DataSource = (BYTE*)&AppConfig.MyGateway;
	        
	        // Format the entire string
	        VarStringPtr = VarString;
	        i = 0;
	        while(1)
	        {
		        uitoa((WORD)*DataSource++, VarStringPtr);
		        VarStringPtr += strlen(VarStringPtr);
		        if(++i == 4)
		        	break;
		        *VarStringPtr++ = '.';
		    }
		    VarStringLen = strlen(VarString);
        }

		// Send one byte back to the calling function (the HTTP Server)
		*val = VarString[(BYTE)ref];
		
		// If this is the last byte to be returned, return 
		// HTTP_END_OF_VAR so the HTTP server won't keep calling this 
		// application callback function
        if ( (BYTE)++ref == VarStringLen )
            return HTTP_END_OF_VAR;

        return ref;
    	
    case VAR_DHCP_TRUE:
    case VAR_DHCP_FALSE:
    	// Check if ref == 0 meaning that the first character of this 
    	// variable needs to be returned
        if ( ref == HTTP_START_OF_VAR )
        {
	        if((var == VAR_DHCP_TRUE) ^ AppConfig.Flags.bIsDHCPEnabled)
	        	return HTTP_END_OF_VAR;

            VarStringLen = 7;
			memcpypgm2ram(VarString, (ROM void *)"checked", 7);
        }

		*val = VarString[(BYTE)ref];
		
        if ( (BYTE)++ref == VarStringLen )
            return HTTP_END_OF_VAR;

        return ref;
#endif	// #if defined(ENABLE_REMOTE_CONFIG)
    }

    return HTTP_END_OF_VAR;
}
#endif	// #if defined(STACK_USE_HTTP_SERVER)

//#endif



#if defined(STACK_USE_FTP_SERVER)

#include "TCPIP Stack/TCPIP.h"

//////////////////////////////////////////////////////////////////////////////////////////
// NOTE: The following FTP code is deprecated.
//       If your application has upgraded to HTTP2, you can upload MPFS 
//       images directly through the MPFS2.exe utility without using FTP.
//       This upload will occur over HTTP, and therefore FTP is unnecessary.
//////////////////////////////////////////////////////////////////////////////////////////
ROM char FTP_USER_NAME[]    = "admin";
ROM char FTP_USER_PASS[]    = "microchip";
#undef FTP_USER_NAME_LEN
#define FTP_USER_NAME_LEN   (sizeof(FTP_USER_NAME)-1)
#define FTP_USER_PASS_LEN   (sizeof(FTP_USER_PASS)-1)

BOOL FTPVerify(BYTE *login, BYTE *password)
{
    if ( !memcmppgm2ram(login, (ROM void*)FTP_USER_NAME, FTP_USER_NAME_LEN) )
    {
        if ( !memcmppgm2ram(password, (ROM void*)FTP_USER_PASS, FTP_USER_PASS_LEN) )
            return TRUE;
    }
    return FALSE;
}
#endif	// #if defined(STACK_USE_FTP_SERVER)
