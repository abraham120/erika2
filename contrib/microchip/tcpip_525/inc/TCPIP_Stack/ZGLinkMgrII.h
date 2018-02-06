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
 *  A daemon like task that directs calls to the ZG Library using a selected
 *  state machine table.   This daemon is agnostic to how the table
 *  is built.  The daemon will select it's next state using a runtime
 *  next_callback or a statically ( in the table ) defined next_callback.
 *
 *********************************************************************
 * FileName:        ZGLinkMgrII.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGLinkMgrII.c
 * and ZGLinkMgrII.h when used in conjunction with the ZeroG ZG2100 for
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
#ifndef _ZGLINKMGRII_H_
#define _ZGLINKMGRII_H_

#include "HardwareProfile.h"
#include "TCPIP_Stack/TCPIP.h"
#include "TCPIPConfig.h"

#include "TCPIP_Stack/ZGDriverTypes.h"
#include "TCPIP_Stack/ZGDriverConstants.h"
#include "TCPIP_Stack/ZGDriverIfaceApp.h"
#include "TCPIP_Stack/ZGLibIface.h"
#include "TCPIP_Stack/ZGLibCfg.h"

typedef enum
{

#if !defined (ZG_CONFIG_NO_WIFIMGRII)
    kZGLMNetworkModeInfrastructure,
#endif

#if !defined (ZG_CONFIG_NO_ADHOCMGRII)
    kZGLMNetworkModeAdhoc,
#endif

    kZGLMNetworkModeIdle

} tZGLMNetworkMode;


#if defined(ZG_CONFIG_LINKMGRII)

#include "TCPIP_Stack/ZGFSMStates.h"

#define FSM_STATE( A , B , C, D, E, F )   \
  { ZG_LIB_FUNC( A ), ZG_REQ_FUNC( B ), ZG_COMP_FUNC( C ), ZG_NEXT_FUNC( D ), E, F }


typedef struct __state {
  tDispatchZGLib                zg_library_func;
  tDispatchRequest              request_func;
  tDispatchComplete             complete_func;
  tDispatchNext                 next_state_func;
  enum tFSMValidStates          next_success;
  enum tFSMValidStates          next_fail;
} tFSMState;

typedef struct {
   tZGLMNetworkMode             currentMode;
   enum tFSMValidStates         currentState;
   enum tFSMStateStatus         stateStatus;
   tZGBool                      bSilent;
} tFSM;

typedef struct {
  tFSM                   FSM;
  ROM tFSMState*   FSMSelector;

  tZGLMNetworkMode nextMode;

  tZGBssDesc      bssDesc;
  tZGU32          selectedBSS;
  tZGBool         bRetryBSSConnect;
  tZGU8           nRetryBSSConnect;
  tZGU8           nScanRetryState;
  tZGU8           nJoinRetryState;
  tZGU8           nAssocRetryState;
  tZGU8           nAuthRetryState;
  tZGU8           patchVersion;
  tZGU8           romVersion;
  tZGU8           capInfo[2];
  tZGU16          securityInfo[2];
  tZGBool         bConnLost;
  tZGBool         bConnFound;
  tZGBool         bConnected;

} tZGLinkMgrCtx;

extern tZGLinkMgrCtx g_linkMgrCtx;
#define APPCXT	(g_linkMgrCtx)


#define ZG_SET_MODE(x)      ZGLinkMgrSetMode(x)
#define ZG_GET_MODE()       ZGLinkMgrGetMode()
#define ZG_SETNEXT_MODE(x)  ZGLinkMgrSetNextMode(x)
#define ZG_GETNEXT_MODE()   ZGLinkMgrGetNextMode()
#define ZG_IS_CONNECTED()   ZGLinkMgrIsConnected()


extern tZGVoidReturn
ZGLinkMgrInit( tZGVoidInput );

extern tZGVoidReturn
ZGLinkMgr( tZGVoidInput );

extern tZGLMNetworkMode
ZGLinkMgrGetMode( tZGVoidInput );

extern tZGVoidReturn
ZGLinkMgrSetMode( tZGLMNetworkMode mode );

extern tZGVoidReturn
ZGLinkMgrSetNextMode( tZGLMNetworkMode mode );

extern tZGLMNetworkMode
ZGLinkMgrGetNextMode( tZGVoidInput );

extern tZGBool
ZGLinkMgrIsConnected( tZGVoidInput );


#else

#define ZG_SET_MODE(x)
#define ZG_GET_MODE()       kZGLMNetworkModeIdle
#define ZG_SETNEXT_MODE(x)
#define ZG_GETNEXT_MODE()
#define ZG_IS_CONNECTED()   kZGBoolFalse

#endif

#endif /* _ZGLINKMGRII_H_ */
