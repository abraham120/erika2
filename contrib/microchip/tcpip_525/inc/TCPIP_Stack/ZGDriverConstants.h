/*******************************************************************************

 File:
        ZGDriverConstants.h

 Description:
        Zero G Driver defined Constants header file.

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

#ifndef _ZGDRIVERCONSTANTS_H_
#define _ZGDRIVERCONSTANTS_H_

/* if NULL is not already defined by the system it is defined here
 * for future use. */
#ifndef NULL
#define NULL (0)
#endif

/* Because some systems require different types for ROM vs
 * RAM memory pointers there are several NULL types below
 * that must be defined when the driver is ported. */
#define kZGDataPtrNULL  ((tZGDataPtr)NULL)
#define kZGU8PtrNULL    ((tZGU8Ptr)NULL)
#define kZGTextPtrNULL  ((tZGTextPtr)NULL)
/* The driver uses the following definitions for testing
 * boolean state. */
#define kZGBoolTrue     ((tZGBool)1u)
#define kZGBoolFalse    ((tZGBool)0u)
/* the driver uses the following definitions for testing
 * the signal state. */
#define kZGSignalExit   ((tZGSignal)0)
#define kZGSignalContinue ((tZGSignal)1)

//#define ROM rom

/* tZGReturnStatus - The return value returned by most of the
 *  Driver API functions. */
typedef enum
{
    kZGFailure = 0,
    kZGSuccess = 1
}tZGReturnStatus;


#endif /* _ZGDRIVERCONSTANTS_H_ */
