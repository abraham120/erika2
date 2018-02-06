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
 *  This header file allows a user to export a callback to other .C files
 *  The callbacks are wrapped with _PROTO macros, such that, the extern
 *  prototype declarations are auto generated from the _LIST.  More important
 *  the _LIST can be used to auto generate case & switch blks, when a
 *  toolchain or compiler does not support function pointers.  The
 *  ZGLibIface.h header file contains the logic for generating the
 *  switch blocks.  To accomplish this duality (switch vs func ptrs)
 *  it was necessary to create the _LIST macro
 *
 *  User may customize/add a request or complete callback in the file,
 *  the include ZGCustomize.h in their application .c file.
 *
 *********************************************************************
 * FileName:        ZGCustomize.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGCustomize.h
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

#ifndef _ZG_CUSTOMIZE_H_
#define _ZG_CUSTOMIZE_H_

#include "TCPIP_Stack/TCPIP.h"
#include "TCPIP_Stack/ZGFSMStates.h"

#ifdef ZG_CONFIG_LIBRARY

/* These are the basic callbacks for just ZGlibrary support only */
#define BASIC_NEXT_LIST
#define BASIC_INDICATE_LIST
#define BASIC_REQUEST_LIST                                                       \
        ZG_REQ_PROTO ( pwrStateRequest )                                         \
        ZG_REQ_PROTO ( dataCfrmRequest )

#define BASIC_COMPLETE_LIST                                                      \
        ZG_COMP_PROTO ( pwrStateComplete )                                       \
        ZG_COMP_PROTO ( dataCfrmComplete )


/* CLI application callbacks */
#define CLI_REQUEST_LIST
#define CLI_COMPLETE_LIST
#define CLI_NEXT_LIST
#define CLI_INDICATE_LIST

#if defined ( ZG_CONFIG_CONSOLE )

#undef  CLI_REQUEST_LIST
#define CLI_REQUEST_LIST                                                          \
        ZG_REQ_PROTO ( iwconfigSetRtsRequest )

#undef  CLI_COMPLETE_LIST
#define CLI_COMPLETE_LIST                                                         \
        ZG_COMP_PROTO ( iwconfigSetRtsComplete )                                  \
        ZG_COMP_PROTO ( iwconfigGetRtsComplete )                                  \
        ZG_COMP_PROTO ( iwconfigGetRadioComplete )                                \
        ZG_COMP_PROTO ( consoleGetVerComplete )

#endif


/* ZG Link Manager callbacks */
#define LINK_MGR_REQUEST_LIST
#define LINK_MGR_COMPLETE_LIST
#define LINK_MGR_NEXT_LIST
#define LINK_MGR_INDICATE_LIST

#if defined (ZG_CONFIG_LINKMGRII)

  #define GENERIC_REQUEST_LIST                                                     \
     ZG_REQ_PROTO ( genericSetDomRequest )                                         \
     ZG_REQ_PROTO ( genericSetMacAddrRequest )                                     \
     ZG_REQ_PROTO ( genericCalcPSKRequest )                                        \
     ZG_REQ_PROTO ( genericInstallWEPKeyRequest )                                  \
     ZG_REQ_PROTO ( genericInstallPSKRequest )                                     \
     ZG_REQ_PROTO ( genericThrottleTableRequest )

  #if !defined (ZG_CONFIG_NO_WIFIMGRII)
   #define WIFI_REQUEST_LIST                                                       \
       ZG_REQ_PROTO ( WiFiScanRequest )                                            \
       ZG_REQ_PROTO ( WiFiJoinRequest )                                            \
       ZG_REQ_PROTO ( WiFiAuthRequest )                                            \
       ZG_REQ_PROTO ( WiFiAssocRequest )                                           \
       ZG_REQ_PROTO ( WiFiDisconnRequest )                                         \
       ZG_REQ_PROTO ( WiFiConnLostRequest )
  #else
    #define WIFI_REQUEST_LIST
  #endif

  #if !defined (ZG_CONFIG_NO_ADHOCMGRII)
    #define ADHOC_REQUEST_LIST                                                     \
      ZG_REQ_PROTO ( adHocScanRequest )                                            \
      ZG_REQ_PROTO ( adHocDisconnRequest )                                         \
      ZG_REQ_PROTO ( adHocStartRequest)                                            \
      ZG_REQ_PROTO ( adHocConnRequest )
  #else
    #define ADHOC_REQUEST_LIST
  #endif

  #define API_REQUEST_LIST

  #undef  LINK_MGR_REQUEST_LIST
  #define LINK_MGR_REQUEST_LIST           GENERIC_REQUEST_LIST                     \
                                          WIFI_REQUEST_LIST                        \
                                          ADHOC_REQUEST_LIST

  #define GENERIC_COMPLETE_LIST                                                    \
        ZG_COMP_PROTO ( genericSetDomComplete )                                    \
        ZG_COMP_PROTO ( genericScanComplete )                                      \
        ZG_COMP_PROTO ( genericGetChipVerComplete )                                \
        ZG_COMP_PROTO ( genericCalcPSKComplete )                                   \
        ZG_COMP_PROTO ( genericComplete )                                          \
        ZG_COMP_PROTO ( genericGetMacAddrComplete )                                \
        ZG_COMP_PROTO ( genericSetMacAddrComplete )

  #if !defined (ZG_CONFIG_NO_ADHOCMGRII)
    #define ADHOC_COMPLETE_LIST                                                    \
        ZG_COMP_PROTO ( adHocDisconnComplete )                                     \
        ZG_COMP_PROTO ( adHocConnStartComplete )
  #else
    #define ADHOC_COMPLETE_LIST
  #endif


  #if !defined (ZG_CONFIG_NO_WIFIMGRII)
    #define WIFI_COMPLETE_LIST                                                     \
        ZG_COMP_PROTO ( WiFiJoinComplete )                                         \
        ZG_COMP_PROTO ( WiFiAuthComplete )                                         \
        ZG_COMP_PROTO ( WiFiAssocComplete )
  #else
    #define WIFI_COMPLETE_LIST
  #endif

  #define API_COMPLETE_LIST


  #undef  LINK_MGR_COMPLETE_LIST
  #define LINK_MGR_COMPLETE_LIST           GENERIC_COMPLETE_LIST                   \
                                           WIFI_COMPLETE_LIST                      \
                                           ADHOC_COMPLETE_LIST


  #define GENERIC_NEXT_LIST						                                   \
        ZG_NEXT_PROTO ( genericThrottleTableNext )                                 \
        ZG_NEXT_PROTO ( genericIdleNextState )

  #if !defined (ZG_CONFIG_NO_WIFIMGRII)
    #define WIFI_NEXT_LIST						                                   \
        ZG_NEXT_PROTO ( WiFiDomNextState )			                               \
        ZG_NEXT_PROTO ( WiFiScanNextState )                                        \
        ZG_NEXT_PROTO ( WiFiDisconnNextState )			                           \
        ZG_NEXT_PROTO ( WiFiMainConnNextState )
  #else
    #define WIFI_NEXT_LIST
  #endif

  #if !defined (ZG_CONFIG_NO_ADHOCMGRII)
    #define ADHOC_NEXT_LIST						                                   \
        ZG_NEXT_PROTO ( adHocDomNextState )			                               \
        ZG_NEXT_PROTO ( adHocScanNextState )			                           \
        ZG_NEXT_PROTO ( adHocMainConnNextState )
  #else
     #define ADHOC_NEXT_LIST
  #endif

  #undef  LINK_MGR_NEXT_LIST
  #define LINK_MGR_NEXT_LIST               GENERIC_NEXT_LIST                      \
                                           WIFI_NEXT_LIST                         \
                                           ADHOC_NEXT_LIST

  #undef  LINK_MGR_INDICATE_LIST
  #define LINK_MGR_INDICATE_LIST                                                  \
    ZG_REGISTER_INDICATE( genericIndicate )


#endif  /* LINK MGII defined */


/* Build aggregated lists - glue together all the conditional compiled pieces together */
#define ZG_REQUEST_LIST             \
        BASIC_REQUEST_LIST          \
        CLI_REQUEST_LIST            \
		API_REQUEST_LIST    \
        LINK_MGR_REQUEST_LIST

#define ZG_COMPLETE_LIST            \
        BASIC_COMPLETE_LIST         \
        CLI_COMPLETE_LIST           \
		API_COMPLETE_LIST   \
        LINK_MGR_COMPLETE_LIST

#define ZG_NEXT_LIST                \
        BASIC_NEXT_LIST             \
        CLI_NEXT_LIST               \
        LINK_MGR_NEXT_LIST

#define ZG_INDICATE_LIST            \
        BASIC_INDICATE_LIST         \
        CLI_INDICATE_LIST           \
        LINK_MGR_INDICATE_LIST


  /*********************************/
  /* DO NOT MODIFY BELOW THIS LINE */
  /*********************************/

  /* Build prototypes for callback funcs to export */
  #define DECLARE_ZG_REQUEST_CALLBACKS( A ) A
  #define ZG_REQ_PROTO( A )	extern tZGU8 A                                  \
                                ( tZGVoidInput * const ptrRequest,          \
                                  tZGVoidInput *appOpaquePtr );
  DECLARE_ZG_REQUEST_CALLBACKS( ZG_REQUEST_LIST )
  #undef ZG_REQ_PROTO


  #define DECLARE_ZG_COMPLETE_CALLBACKS( A )    A
  #define ZG_COMP_PROTO( A )                                                \
  extern tZGVoidReturn A (tZGU8 type, tZGDataPtr fourByteHeader,            \
                            tZGDataPtr pBuf, tZGU16 len,                    \
                            tZGVoidInput *appOpaquePtr);
  DECLARE_ZG_COMPLETE_CALLBACKS( ZG_COMPLETE_LIST )
  #undef ZG_COMP_PROTO

  #define DECLARE_ZG_NEXT_CALLBACKS( A )            A
  #define ZG_NEXT_PROTO( A )  extern enum tFSMValidStates A ( tZGVoidInput );
  DECLARE_ZG_NEXT_CALLBACKS( ZG_NEXT_LIST )
  #undef ZG_NEXT_PROTO

  #define DECLARE_ZG_INDICATE_CALLBACKS( A ) A
  #define ZG_REGISTER_INDICATE( A )                                         \
     extern tZGVoidReturn A  ( tZGU8 type, tZGDataPtr fourByteHeader,       \
                               tZGDataPtr pBuf, tZGU16 len );
  DECLARE_ZG_INDICATE_CALLBACKS( ZG_INDICATE_LIST )
  #undef ZG_REGISTER_INDICATE


#endif /*ZG_CONFIG_LIBRARY */

#endif /* _ZG_CUSTOMIZE_H_ */
