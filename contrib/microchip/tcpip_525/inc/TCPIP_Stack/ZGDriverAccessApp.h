/*******************************************************************************

 File:
        ZGDriverAccessApp.h

 Description:
        Zero G Driver Application Access Definition Header file.

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

 DO NOT DELETE THIS LEGAL NOTICE:
  2006, 2007, 2008 © ZeroG Wireless, Inc.  All Rights Reserved.
  Confidential and proprietary software of ZeroG Wireless, Inc.
  Do no copy, forward or distribute.

Author               Date       Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Zero G              Sep 2008    Initial version
KO                  31 Oct 2008 Port to PIC24F and PIC32 for TCP/IP stack v4.52

*******************************************************************************/

#ifndef _ZGDRIVERACCESSAPP_H_
#define _ZGDRIVERACCESSAPP_H_

#include "TCPIP_Stack/ZGDriverTypes.h"
#include "TCPIP_Stack/ZGDriverConstants.h"
#include "TCPIP_Stack/ZGAccessApp.h"
#include "TCPIP_Stack/ZGLibIface.h"


/* ZGAPP_HANDLE_MGMTCONFIRM - used by the ZG Driver to pass management confirm
 * messages to the application.
 * type - identifies the type of Management Confirm message. Must be one of kZGMgtCnf...
 *          found in ZGDriverIfaceApp.h.
 */

/* ZGAPP_HANDLE_MGMTINDICATE - used by the ZG Driver to pass management indicate
 * announcements to the application. */

#if defined ( ZG_CONFIG_LIBRARY )

#define ZGAPP_HANDLE_MGMTCONFIRM(type)         ZGLibConfirm((tZGU8)type)
#define ZGAPP_HANDLE_MGMTINDICATE(type)        ZGLibIndicate((tZGU8)type)

#else

#define ZGAPP_HANDLE_MGMTCONFIRM(type)
#define ZGAPP_HANDLE_MGMTINDICATE(type)

#endif

#endif /*_ZGDRIVERACCESSAPP_H_ */

