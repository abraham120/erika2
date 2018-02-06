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
/*		ZGModuleAccessSys.h													  */
/*																			  */
/* Description:																  */
/*		Zero G Module Access Header file to the System Services.			  */
/*																			  */
/* DO NOT DELETE THIS LEGAL NOTICE:											  */
/*  2006, 2007 © ZeroG Wireless, Inc.  All Rights Reserved.					  */
/*  Confidential and proprietary software of ZeroG Wireless, Inc.			  */
/*  Do no copy, forward or distribute.										  */
/*																			  */
/******************************************************************************/
#ifndef _ZGMODULEACCESSSYS_H_
#define _ZGMODULEACCESSSYS_H_

/* Use the same set of access functions as driver does.
 * Particularly, buffer management functions such as
 * ZGSYS_READBUF_GET() and ZGSYS_READBUF_CLEAN()
 */
#include "TCPIPConfig.h"

#include "TCPIP_Stack/ZGDriverTypes.h"
#include "TCPIP_Stack/ZGDriverConstants.h"
#include "TCPIP_Stack/ZGAccessSys.h"

#define ZGSYS_MODULE_GET_MSEC_TICK_COUNT  TickGet

#define ZGSYS_UART_INIT(port,rate,flag)
#if defined( STACK_USE_UART )
	#define ZGSYS_UART_PUTC(port,c)          	putcUART(c)
	#define ZGSYS_UART_GETC()            		ReadUART()
	#define ZGSYS_UART_GETC_COUNT()      		DataRdyUART()
#else
	#define ZGSYS_UART_PUTC(port,c)
	#define ZGSYS_UART_GETC()            		(0)
	#define ZGSYS_UART_GETC_COUNT()      		(0)
#endif

#endif /*_ZGMODULEACCESSSYS_H_ */
