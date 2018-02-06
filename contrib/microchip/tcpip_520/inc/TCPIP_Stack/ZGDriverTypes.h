/*******************************************************************************

 File:
        ZGDriverTypes.h

 Description:
        Zero G Driver defined Types header file.

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

#ifndef _ZGDRIVERTYPES_H_
#define _ZGDRIVERTYPES_H_
/*********************************/
/* Basic data types and pointers */
/*********************************/
#define tZGS8       signed char
#define tZGS8Ptr    signed char*
#define tZGU8       unsigned char
#define tZGU8Ptr    unsigned char*
#define tZGS16      signed short
#define tZGS16Ptr   signed short*
#define tZGU16      unsigned short
#define tZGU16Ptr   unsigned short*
#define tZGU32      unsigned long
#define tZGU32Ptr   unsigned long*

#if defined(__18CXX)
 typedef enum _BOOL { FALSE = 0, TRUE } BOOL;   // Undefined size
 typedef BOOL Boolean;
#else
 typedef unsigned short Boolean;
#endif

/*============================================================================*/
/* basic constants                                                            */
/*============================================================================*/

// microchip compiler treats void as a data type (16 bit pointer)
// and that causes problems when NULL is passed to a function for
// an argument that is a function pointer or a ROM pointer (24 bit pointer)
#if !defined(__18CXX)
#undef NULL
#define NULL        ((void *)0)
#endif

#if defined(__18CXX)
#undef true
#define true        (TRUE)
#undef false
#define false       (FALSE)
#else
#undef true
#define true        ((Boolean)1u)
#undef false
#define false       ((Boolean)0u)
#endif

/********************************************/
/* endian conversion macros for 16-bit ints */
/********************************************/
/* NOTE: the G2100 uses the big-endian format for all multi-byte
 *  integers that pass between the G2100 and the host. These
 *  macros should be setup to reflect the endianness of the host. */
/* Host to Zero G long */
#define HTOZGL(a) (((a & 0x000000ff)<<24) | ((a & 0x0000ff00)<<8) | ((a & 0x00ff0000)>>8) | ((a & 0xff000000)>>24))
#define ZGTOHL(a) HTOZGL(a)
/* Host to Zero G short */
#define HSTOZGS(a) (((a)<<8) | ((a)>>8))
#define ZGSTOHS(a) HSTOZGS(a)

/**********************************/
/* Custom data types and pointers */
/**********************************/

/* tZGDataPtr - some CPU's require a special
 *  type to reference pointers to RAM/DATA.
 *  The ZG Driver uses this type for such
 *  references. */
#define tZGDataPtr tZGU8Ptr

/* tZGTextPtr - is used for pointers to ROM
 *  constants such as assert strings */
#define tZGTextPtr ROM char *

/* tZGBool - This type is used internally
 *  by the ZGDriver to store system state
 *  that is boolean in nature (1 or 0).
 *  None of the tests in the Driver rely
 *  on the value of kZGBoolTrue being '1'
 *  or kZGBoolFalse being '0'. The developer
 *  is free to configure this to any
 *  desired value */
#define tZGBool tZGU8

/* types used for function prototypes. Some
 * compilers prefer that functions with no parameters
 * be defined with an empty parameter list instead of
 * 'void'.  In that case the Developer should define
 * tZGVoidInput as empty space.   */
#define tZGVoidReturn void
#define tZGVoidInput  void

#define tZGVolatile   volatile


#define tZGMsgQueueID tZGU16 /* tRen32MsgQueueID */
#define tZGMsgQueueIDPtr tZGU16Ptr

#define tZGMessage tZGDataPtr /* tRen32MsgPtr */
#define tZGSignal tZGU8

#define tZGConst const


#endif /*_ZGDRIVERTYPES_H_ */
