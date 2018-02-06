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

/******************************************************************************/
/*																			  */
/* File:																	  */
/*		ZGConsole.h										    				  */
/*																			  */
/* Description:																  */
/*		Header file implenting the console user interface.		              */
/*																			  */
/* DO NOT DELETE THIS LEGAL NOTICE:											  */
/*  2008 © ZeroG Wireless, Inc.  All Rights Reserved.					      */
/*  Confidential and proprietary software of ZeroG Wireless, Inc.			  */
/*  Do no copy, forward or distribute.										  */
/*																			  */
/******************************************************************************/

#ifndef _ZGCONSOLE_H_
#define _ZGCONSOLE_H_

#include "TCPIP_Stack/TCPIP.h"
#include "TCPIP_Stack/ZGConsoleMsgHandler.h"


#if defined (ZG_CONFIG_CONSOLE)
  #if defined(__18CXX)
  #pragma varlocate 4 g_ConsoleContext
  #endif

  extern tConsoleContext g_ConsoleContext;
#endif

#define ARGC           g_ConsoleContext.argc
#define ARGV           g_ConsoleContext.argv

typedef enum
{
    kZGConsoleReqNone = 0,
    kZGConsoleReqPing
} tZGConsoleReq;

#if defined ( ZG_CONFIG_CONSOLE )

    extern tZGVoidReturn ZGConsoleInit(ROM tZGU8 **p_cmdStrings, tZGU8 numCmdStrings);
    extern tZGVoidReturn ZGConsoleProcess(tZGVoidInput);
    extern tZGVoidReturn ZGConsoleReqClear(tZGVoidInput);
    extern tZGVoidReturn ZGConsoleProcess(tZGVoidInput);
    extern tZGBool ZGConsoleIsConsoleMsgReceived(tZGVoidInput);
    extern tZGVoidReturn ZGConsoleReleaseConsoleMsg(tZGVoidInput);
    extern tZGS8 ** ZGConsoleGetCmdLineTokens(tZGU8 *p_argc);
    extern tZGVoidReturn ZGConsoleSetMsgFlag(tZGVoidInput);

#else

    #define ZGConsoleInit()
    #define ZGConsoleProcess()
    #define ZGConsoleReqClear()

#endif

#endif /* _ZGCONSOLE_H_ */
