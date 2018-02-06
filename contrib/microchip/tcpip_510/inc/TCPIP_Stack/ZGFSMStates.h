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
 *  This header file defines all possible states referenced in FSM tables
 *  defined in ZGWiFiMgrII.c, ZGAdhocMgrII.c, etc.  This header file
 *  eliminates a cross dependency between other .h files, and subsequent forward
 *  references that may or may not port well, based on the host MCU toolchain.
 *
 *********************************************************************
 * FileName:        ZGFSMStates.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGFSMStates.h
 * when used in conjunction with the ZeroG ZG2100 for
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
 * SG                  12/12/08
********************************************************************/

#ifndef _ZGFSMSTATES_H_
#define _ZGFSMSTATES_H_

/* Different C runtime libraries seem to define NULL differently ways.  */
/* And the toolchains seem to expand NULL before or after macro expansions MACRO(A) */
/* So far I have seen null defined these ways (proprietary & standardized): */
/*  #define NULL             */
/*  #define NULL (0)         */
/*  #define NULL 0           */
/*  #define NULL (void *) 0  */
/*  #define NULL '\0'        */
/* To decouple these different definitions NULL from the link manager & link library code */
/* one definition of kNULL is used throughout the code.   The side effect is that each FSM   */
/* table burns one entry with doing nothing.   If you want to reduce the ROM (FSM table) code size, you could */
/* attempt to useone system definition of NULL, and the one that seems to universally work with ZGLib and LinkMgr is */
/* #define NULL 0 .   The use of kNULL is a tradeoff for portability and reduces issues with macro expansion */

enum tFSMValidStates
{
    kNULL=0,
    kSTIdle,
    kSTGetChipVersion,
    kSTEnThrottleTable,
    kSTSetConnLostCondition,
    kSTSetMacAddr,
    kSTGetMacAddr,
    kSTSetRegDom,
    kSTCalcPSK,
    kSTInstallWEPKey,
    kSTInstallPSK,
    kSTScan,
    kSTStart,
    kSTConnect,
    kSTJoin,
    kSTAuth,
    kSTAssoc,
    kSTMaintainConnect,
    kSTDisconnect,

    /* End of Valid States */
    ZG_MAX_STATES

};

enum tFSMStateStatus
{
    kFAILURE=0,
    kSUCCESS,
    kPENDING,
    kRETRY
};


#endif /* _ZGFSMSTATES_H_ */
