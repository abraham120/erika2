/*********************************************************************
 *
 *            ZG2100 registers/bits
 *
 *********************************************************************
 * FileName:        ZG2100.h
 * Description:     Include file for ZG2100 control registers
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement

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

 * Copyright © 2002-2007 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product (“Device”) which is
 *      integrated into Licensee’s product; or
 * (ii) ONLY the Software driver source files ZG2100.c and
 *      ZG2100.h ported to a non-Microchip device used in
 *      conjunction with a Microchip ethernet controller for the
 *      sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT
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

Author               Date        Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Michael Palladino   10/13/07    Original
KO                  31 Oct 2008 Port to PIC24F and PIC32 for TCP/IP stack v4.52

*******************************************************************************/

#ifndef __ZG2100_H
#define __ZG2100_H

//============================================================================
//                                  Include files
//============================================================================

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "TCPIP_Stack/ZGDriverTypes.h"
#include "TCPIP_Stack/ZGDriverAccessHal.h"
#include "TCPIP_Stack/ZGDriverIfaceHal.h"
#include "TCPIP_Stack/ZGDriverAccessApp.h"
#include "TCPIP_Stack/ZGDriverIfaceApp.h"
#include "TCPIP_Stack/ZGDriverConstants.h"
#include "TCPIP_Stack/ZGDriverPrv.h"
#include "TCPIP_Stack/ZGAccessSys.h"
#include "TCPIP_Stack/ZGDriverIfaceApp.h"
#include "TCPIP_Stack/ZGDriverAccessSys.h"



//============================================================================
//                                  RAW msg Constants
//============================================================================
// indexes where msg data starts
#define  kRawSetParamMsgStartIndex   (4)  /* start index for Raw SetParam message */
#define  kRawScanMsgStartIndex       (2)  /* start index for RAW Scan message     */
#define  kRawJoinMsgStartIndex       (2)  /* start index for RAW Join message     */
#define  kRawAuthMsgStartIndex       (2)  /* start index for RAW Auth message     */
#define  kRawAssocMsgStartIndex      (2)  /* start index for RAW Assoc message    */
#define  kRawSecKeyMsgStartIndex     (2)  /* start index for RAW Sec Key message  */
#define  kRAWSetPMKKeyStartIndex     (2)  /* start index for RAW Set PMK Key msg  */
#define  kRAWPskCalcCnfStartIndex    (2)  /* start index for received PSK Calc Cnf msg */

//============================================================================
//                                  RAW Constants
//============================================================================
#define kZGRawId0                       (0u)
#define kZGRawId1                       (1u)

// RAW0 used for Rx, RAW1 used for Tx
#define kRxPipeRAW          kZGRawId0
#define kTxPipeRAW          kZGRawId1


// Source/Destination objects on the G2100
#define kZGRawSrcDestCmdProcessor       (0x00u)   /* Cmd processor (aka G2100 MAC)                  */
#define kZGRawSrcDestManagementPool     (0x10u)   /* For 802.11 Management packets                  */
#define kZGRawSrcDestDataPool           (0x20u)   /* Data Memory pool used for tx and rx operations */
#define kZGRawSrcDestScratchPool        (0x30u)   /* Scratch object                                 */
#define kZGRawSrcDestMemory             (0x40u)   /* single level stack to save state of RAW        */
#define kZGRawSrcDestRawDataCopy        (0x70u)   /* RAW to RAW copy                                */

//typedef void (*tZGCallbackFuncPtr)(tZGU16 data);

//#define USE_TICK_TIMEOUT

extern DWORD zgGetTickDuration(DWORD initTickCnt);

extern tZGMsgQueueID driverDataQueueID, driverMgmtQueueID;

extern Boolean gHostRAWDataPacketReceived;

extern void zgMakeInitialConnection(void);
tZGVoidReturn zgEintISR(tZGVoidInput);
Boolean ZGSendRAWDataFrame(tZGU16 bufLen);

tZGU16 ZGRawMove(tZGU16 rawId, tZGU16 srcDest, Boolean rawIsDestination, tZGU16 size);
Boolean ZGRawSetIndex(tZGU16 rawId, tZGU16 index);
tZGU16 ZGRawGetIndex(tZGU16 rawId);
Boolean ZGRawGetByte(tZGU16 rawId, tZGU8 *pBuffer, tZGU16 length);
Boolean ZGRawSetByte(tZGU16 rawId, tZGU8 *pBuffer, tZGU16 length);
Boolean ZGRawSetByteROM(tZGU16 rawId, ROM tZGU8 *pBuffer, tZGU16 length);

tZGU16 ZGMACIFService(tZGVoidInput);
Boolean ZGSendRAWDataFrame(tZGU16 bufLen);
void ZGTransportRegisterRead(tZGU8  zgReg,
                             tZGU8  *pBuffer,
                             tZGU16 length);


tZGBool ZGisTxMgmtReady(tZGVoidInput);


tZGVoidReturn ZGFreeMgmtTx(tZGVoidInput);
Boolean ZGSendRAWManagementFrame(tZGU16 bufLen);



Boolean ZGRawGetMgmtRxBuffer(tZGU16 *p_numBytes);
tZGVoidReturn ZGRawFreeRxMgmtBuffer(tZGVoidInput);
tZGVoidReturn ZGSetRawRxMgmtInProgress(Boolean action);
Boolean ZGisRawRxMgmtInProgress(tZGVoidInput);

tZGReturnStatus ZGRawSendUntamperedData(tZGU8 *pReq, tZGU16 len);

#endif // __ZG2100_H

