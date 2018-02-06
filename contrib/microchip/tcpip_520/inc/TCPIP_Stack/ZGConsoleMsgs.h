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
 *  Messages exchanged between PC and Host Bridge.  Used by PC app and Host Bridge app.
 *  Module for ZGHostBridge library
 *	 - Describes the UART messages exchanged between the PC and Host Bridge
 *	 -Reference: None
 *
 *********************************************************************
 * FileName:        ZGConsoleMsgs.h
 * Dependencies:    None
 * Processor:       PC
 * Compiler:        Visual Studio 2008, Visual C++ 2008
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2008 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files uart.c
 * and uart.h when used in conjunction with the ZeroG ZG2100 for
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
 * SAG            		12/12/08    Ported from eval SDK
********************************************************************/

#ifndef __ZGCONSOLEMSGS_H
#define __ZGCONSOLEMSGS_H

#ifdef __cplusplus
 extern "C" {
#endif

//----------------------------------------------------------------------------
//                                 Defines
//----------------------------------------------------------------------------

// !!! These defines MUST match the g_consoleCmd structure  !!!
enum validConsoleCmds
{
    HELP_MSG = 0,                   // only used by humans
    GET_ZG2100_VERSION_MSG,
    RESET_HOST,
    CLEAR_SCREEN_MSG,
    IFCONFIG_MSG,
    IWCONFIG_MSG,
    IWPRIV_MSG,
    INVALID_CMD = 0xFF
};


#define kZGMaxTokensPerCmd          (16)  /* max tokens, including cmd and parameters */
#define kConsoleMaxMsgSize	        (80)


//----------------------------------------------------------------------------
//                                 Typedefs
//----------------------------------------------------------------------------

// structure definition to define all ASCII messages
typedef struct msg_struct
{
    ROM tZGS8   *p_cmdName;       // pointer to cmd name
    ROM tZGS8   *p_cmdHelp;       // pointer to cmd help string
    tZGU8   maxTokens;            // max tokens for this command
} tZGCmd;

// parsed version numbers put in this structure
typedef struct version_struct
{
    tZGU8 major;
    tZGU8 minor;
    tZGU8 revision;
} tZGVersion;


//----------------------------------------------------------------------------
//                                 External Globals
//----------------------------------------------------------------------------
extern  const tZGCmd    g_consoleCmd[];
extern  const tZGU8     g_numCmds;


//----------------------------------------------------------------------------
//                                 Function Prototypes
//----------------------------------------------------------------------------
tZGVoidReturn   TokenizeCmdLine(tZGS8 *p_line);
tZGU8           GetCmdId(tZGVoidInput);
tZGVoidReturn   Output_Monitor_Hdr(tZGVoidInput);
tZGBool         ConvertASCIIHexToBinary(tZGS8 *p_ascii, tZGU16 *p_binary);
tZGBool         ConvertASCIIUnsignedDecimalToBinary(tZGS8 *p_ascii, tZGU16 *p_binary);
tZGBool         ConvertASCIISignedDecimalToBinary(tZGS8 *p_ascii, tZGS16 *p_binary);
tZGU8           HexToBin(tZGU8 hexChar);
tZGVoidReturn   ZGConsoleSetMsgFlag(tZGVoidInput);



#ifdef __cplusplus
 }
#endif


#endif /* __ZGCONSOLEMSGS_H */
