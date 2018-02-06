/*******************************************************************************

 File:
        ZGDriverAccessSys.h

 Description:
        Zero G Driver Access Header file to the System Services.

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
#ifndef _ZGDRIVERACCESSSYS_H_
#define _ZGDRIVERACCESSSYS_H_


/* In this sample ZGAccessSys.h contains the prototypes for all the
 * functions used to populate the MACROS below. */
#include "TCPIP_Stack/ZGAccessSys.h"

/* ZGSYS_DRIVER_ASSERT - there are several conditions under which the
 * reference driver will issue an assert using this macro. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGU16 , tZGDataPtr) */
#define ZGSYS_DRIVER_ASSERT(tag, string) MCHPSysAssert(tag, string)

/*****************************************************************************/
/* ZGSYS_SIGNAL_... macros used by the ZG driver to manage the signal
 *  mechanism. */
/* FIXME: finish this comment */
/*****************************************************************************/

/* ZGSYS_SIGNAL_WAIT - */
/* FIXME: Finish this comment */
/* DEFINITION - */
#define ZGSYS_SIGNAL_WAIT() ((sig == kZGSignalExit)? kZGSignalContinue : kZGSignalExit)/* this application is single threaded */

/* ZGSYS_SIGNAL_SET - */
/* FIXME: Finish this comment */
/* DEFINITION - tZGVoidReturn FunctionName(tZGVoidInput) */
#define ZGSYS_SIGNAL_SET()  /* NOT USED - this application is single threaded */


#endif /*_ZGDRIVERACCESSSYS_H_ */
