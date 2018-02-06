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
 *  The ZeroG link library header file.  This file implements a set of
 *  XMacros. Please refer to  http://www.ddj.com/cpp/184401387  or
 *  http://en.wikipedia.org/wiki/C_preprocessor .  These XMacros allow
 *  allow an application to be compiled to use function pointers, or
 *  switch/case blks. Compiling with function pointers reduces code size
 *  but requires the host MCU & toolchain to support re-entrancy - some
 *  don't.  The application program should not need to modify this file.
 *********************************************************************
 * FileName:        ZGLibIface.h
 * Dependencies:    None
 * Company:         ZeroG Wireless, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2009 ZeroG Wireless Inc.  All rights
 * reserved.
 *
 * ZeroG licenses to you the right to use, modify, copy,
 * distribute, and port the Software driver source files ZGLibIface.h
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

#ifndef _ZGLIBIFACE_H_
#define _ZGLIBIFACE_H_

  #include "HardwareProfile.h"
  #include "TCPIP_Stack/TCPIP.h"
  #include "TCPIP_Stack/ZGCustomize.h"
  #include "TCPIP_Stack/ZGModuleAccessSys.h"

#if defined (ZG_CONFIG_LIBRARY)

  #define kLibMgrCxtBufLen    128u

  #ifdef ZG_RAW_DRIVER
     /* request and confirm must be lockstep */
     #define ZG_LIB_MGMT_Q_SIZE 1u
  #else
    /* match the number of entry in the FIFO driver's queue */
    #define ZG_LIB_MGMT_Q_SIZE      kMaxMgmtQueueCnt
  #endif

  #define stringify(x)   #x
  #define stringify_val(x)   stringify(x)

  /* Conditionally compiled feature */
  #ifdef CONNECTION_LOST_FEATURE
    #define ZG_CONN_LOST_PROTO( A )    ZG_LIB_PROTO( A )
  #else
    #define ZG_CONN_LOST_PROTO( A )
  #endif

  /* ADD A NEW LIBRARY API HERE */
  #define  ZG_LIBRARY_LIST						                                \
     ZG_LIB_PROTO ( ZGLibSetDataCfrm )                                          \
     ZG_LIB_PROTO ( ZGLibScan )					                                \
     ZG_LIB_PROTO ( ZGLibSetDom )				                                \
     ZG_LIB_PROTO ( ZGLibGetChipVersion )		                                \
     ZG_LIB_PROTO ( ZGLibSetThrottleTable )	                                    \
     ZG_LIB_PROTO ( ZGLibSetMacAddr )			                                \
     ZG_LIB_PROTO ( ZGLibGetMacAddr )			                                \
     ZG_LIB_PROTO ( ZGLibInstallWEPKeys)                                        \
     ZG_LIB_PROTO ( ZGLibInstallPSK )			                                \
     ZG_LIB_PROTO ( ZGLibCalcPSK )				                                \
     ZG_LIB_PROTO ( ZGLibJoin )					                                \
     ZG_LIB_PROTO ( ZGLibAuth )					                                \
     ZG_LIB_PROTO ( ZGLibAssoc )			    	                            \
     ZG_LIB_PROTO ( ZGLibStart )				                                \
     ZG_LIB_PROTO ( ZGLibConnect )				                                \
     ZG_LIB_PROTO ( ZGLibDisconnect )			                                \
     ZG_LIB_PROTO ( ZGLibGetRadioState )                                        \
     ZG_LIB_PROTO ( ZGLibSetRadioState )                                        \
     ZG_LIB_PROTO ( ZGLibGetRTS )				                                \
     ZG_LIB_PROTO ( ZGLibSetRTS )				                                \
     ZG_CONN_LOST_PROTO( ZGLibSetConnLost )                                     \
     ZG_LIB_PROTO ( ZGLibSetPwrSaveMode )


  #ifdef ZG_NO_FUNC_PTRS

    /*********************************************/
    /* COMPLETION CALLBACK COMPATIBLITY - SWITCH */
    /*********************************************/

    /* Enumerate all the completion callback for a switch statement */
    #define ZG_COMP_FUNC( A )		        kComp_ ## A
    #define ZG_COMP_PROTO( A )		        ZG_COMP_FUNC( A ),


    #define  ENUM_ZG_COMPLETE( A )				                                \
    typedef enum {							                                    \
                    kComp_0 = 0,					                            \
                    kComp_kNULL = 0,					                        \
                    A                                                           \
                    MAX_COMP_LIST				                                \
    } tZGCompEnum;
    ENUM_ZG_COMPLETE( ZG_COMPLETE_LIST )
    typedef tZGCompEnum   tDispatchComplete;
    #undef ZG_COMP_PROTO

    /* Provide the body of the switch statement */
    /* This must be the last X-macro #undef */
    #define ZG_COMP_PROTO( A )                                                  \
    case  ZG_COMP_FUNC( A ) :                                                   \
         A (type, fourByteHeader, pBuf, len, appOpaquePtr);                     \
     break;

    #define  ZG_COMPLETE_DISPATCHER()                                           \
    void zg_comp_dispatch ( tDispatchComplete compFunc, tZGU8 type,             \
                            tZGDataPtr fourByteHeader, tZGDataPtr pBuf,         \
                            tZGU16 len, tZGVoidInput *appOpaquePtr )            \
    {                                                                           \
      switch ( compFunc )                                                       \
      {                                                                         \
        ZG_COMPLETE_LIST                                                        \
        default:                                                                \
           ZGErrorHandler((ROM FAR char*) "DispatchComp");                      \
      }                                                                         \
    }

    extern void zg_comp_dispatch ( tDispatchComplete compFunc, tZGU8 type,
                                   tZGDataPtr fourByteHeader, tZGDataPtr pBuf,
                                   tZGU16 len, tZGVoidInput *appOpaquePtr );

    #define DISPATCH_COMPLETE( A, B, C, D, E, F )	                            \
            zg_comp_dispatch ( A , B, C, D, E, F)


    /******************************************/
    /* REQUEST CALLBACK COMPATIBLITY - SWITCH */
    /******************************************/

    #define ZG_REQ_FUNC( A )			kReq_ ## A
    #define ZG_REQ_PROTO( A )			ZG_REQ_FUNC( A ),
    #define  ENUM_ZG_REQUEST( A )                                               \
    typedef enum {                                                              \
                    kReq_0=0,                                                   \
                    kReq_kNULL=0,                                               \
                    A                                                           \
                    MAX_REQ_LIST                                                \
    } tZGReqEnum;
    ENUM_ZG_REQUEST ( ZG_REQUEST_LIST )
    typedef tZGReqEnum   tDispatchRequest;
    #undef ZG_REQ_PROTO

    /* This must be the last X-Macro redefn of ZG_REQ_PROTO, since the body will
       be declared in an arbitrary C file, must likely requests.c */
    #define ZG_REQ_PROTO( A )													\
    case ZG_REQ_FUNC( A ):														\
       retValue = A ( ptrRequest, appOpaquePtr );                               \
       break;

    #define  ZG_REQUEST_DISPATCHER()                                            \
    tZGU8 zg_req_dispatch ( tDispatchRequest request,                           \
                            tZGVoidInput * const ptrRequest,                    \
                            tZGVoidInput *appOpaquePtr )                        \
    {                                                                           \
      tZGU8 retValue;                                                           \
      switch ( request )                                                        \
      {                                                                         \
        ZG_REQUEST_LIST                                                         \
        default:                                                                \
           ZGErrorHandler((ROM FAR char*) "DispatchReq");                       \
      }                                                                         \
      return( retValue );                                                       \
    }

    extern tZGU8 zg_req_dispatch ( tDispatchRequest request,
                                   tZGVoidInput * const ptrRequest,
                                   tZGVoidInput *appOpaquePtr);

    #define DISPATCH_REQUEST( A,B,C )	zg_req_dispatch ( A, B, C )


    /*********************************************/
    /* NEXT STATE CALLBACK COMPATIBLITY - SWITCH */
    /*********************************************/

    /* Enumerate all the next state callback for a switch statement */
    #define ZG_NEXT_FUNC( A )		        kNext_ ## A
    #define ZG_NEXT_PROTO( A )		        ZG_NEXT_FUNC( A ),

    #define ENUM_ZG_NEXT( A )                                                   \
    typedef enum {                                                              \
                    kNext_0 = 0,                                                \
                    kNext_kNULL = 0,                                            \
                    A                                                           \
                    MAX_NEXT_LIST                                               \
    } tZGNextEnum;

    ENUM_ZG_NEXT( ZG_NEXT_LIST )
    typedef tZGNextEnum   tDispatchNext;
    #undef ZG_NEXT_PROTO


    /* Provide the body of the switch statement */
    /* This must be the last X-macro #undef */
    #define ZG_NEXT_PROTO( A )                                                  \
    case  ZG_NEXT_FUNC( A ) :                                                   \
         retValue = A();                                                        \
     break;

    #define  ZG_NEXT_DISPATCHER()                                               \
    enum tFSMValidStates zg_next_dispatch ( tDispatchNext nextFunc )            \
    {                                                                           \
      enum tFSMValidStates retValue = kNULL;                                    \
      switch ( nextFunc )												        \
      {                                                                         \
        ZG_NEXT_LIST                                                            \
        default:                                                                \
           ZGErrorHandler((ROM FAR char*) "DispatchNext");                      \
      }																	        \
      return ( retValue );                                                      \
    }

    extern enum tFSMValidStates zg_next_dispatch ( tDispatchNext nextFunc );

    #define DISPATCH_NEXT( A )       zg_next_dispatch ( A )


  #else

    /* COMPLETION FUNC PTRS */

    #define ZG_COMP_FUNC( A )	    A
    #define  ZG_COMPLETE_DISPATCHER()
    #define DISPATCH_COMPLETE( A, B, C, D, E, F )	( *A ) ( B,C,D,E,F )

    typedef tZGVoidReturn (* tDispatchComplete) ( tZGU8 type,
                                                  tZGDataPtr fourByteHeader,
                                                  tZGDataPtr pBuf,
                                                  tZGU16 len,
                                                  tZGVoidInput *appOpaquePtr );


    /* REQUEST FUNC PTRS */

    #define ZG_REQ_FUNC( A )       A
    #define  ZG_REQUEST_DISPATCHER()
    #define DISPATCH_REQUEST( A, B, C )   ( *A  ) ( B, C )
    typedef tZGU8 (* tDispatchRequest) ( tZGVoidInput * const ptrRequest,
                                         tZGVoidInput *appOpaquePtr );



    /* NEXT FUNC PTRS */

    #define ZG_NEXT_FUNC( A )	            A
    #define  ZG_NEXT_DISPATCHER()
    #define DISPATCH_NEXT( A )        ( *A )()

    typedef enum tFSMValidStates (* tDispatchNext) ( tZGVoidInput );

  #endif



  /***************************************************************************************/
  /* ZG Library API(s) must be defined after the callbacks because of forward references */
  /***************************************************************************************/

  /* Build prototypes for ZG Lib API(s) to export */
  #define DECLARE_ZG_LIB_API( A ) A
  #define ZG_LIB_PROTO( A )	extern tZGReturnStatus A                                \
                            ( tDispatchRequest reqCall,                             \
                              tDispatchComplete compCall,                           \
                              tZGVoidInput *appOpaquePtr );

  DECLARE_ZG_LIB_API( ZG_LIBRARY_LIST )

  #undef ZG_LIB_PROTO


  #ifdef ZG_NO_FUNC_PTRS

    /* Enumerate all the library calls for a switch statement */
    #define ZG_LIB_FUNC( A )           kLib_ ## A
    #define ZG_LIB_PROTO( A )		   ZG_LIB_FUNC( A ),

    #define  ENUM_ZG_LIB( A )				                                        \
    typedef enum {	    							                                \
                    kLib_0=0,                                                       \
                    kLib_kNULL=0,                                                    \
                    A						                                        \
                    MAX_LIB_LIST                                                    \
    } tZGLibEnum;
    ENUM_ZG_LIB ( ZG_LIBRARY_LIST )
    typedef tZGLibEnum		            tDispatchZGLib;
    #undef ZG_LIB_PROTO


    /* Provide the body of the switch statement */
    /* This must be the last X-macro #undef */
    #define ZG_LIB_PROTO( A )                                                       \
    case  ZG_LIB_FUNC( A ) :                                                        \
       retValue = A ( request, complete, appOpaquePtr );                            \
       break;
    #define  ZG_LIBRARY_DISPATCHER()                                                \
    tZGReturnStatus zg_lib_dispatch ( tDispatchZGLib    api,                        \
                                      tDispatchRequest  request,                    \
                                      tDispatchComplete complete,                   \
                                      tZGVoidInput      *appOpaquePtr)              \
    {																			    \
        tZGReturnStatus retValue = kZGFailure;                                      \
        switch ( api )                                                              \
        {                                                                           \
            ZG_LIBRARY_LIST                                                         \
            default:                                                                \
                 ZGErrorHandler((ROM FAR char*) "LibAPI");                          \
        }                                                                           \
        return ( retValue );                                                        \
    }

    extern tZGReturnStatus zg_lib_dispatch ( tDispatchZGLib api,
                                             tDispatchRequest request,
                                             tDispatchComplete complete,
                                             tZGVoidInput *appOpaquePtr);

    #define DISPATCH_ZGLIB( A, B, C, D )         zg_lib_dispatch ( A, B, C, D )



  #else

    #define ZG_LIB_FUNC( A )              A
    #define ZG_LIBRARY_DISPATCHER()
    #define DISPATCH_ZGLIB( A,B,C,D )     ( *A ) ( B, C, D )

    typedef tZGReturnStatus (* tDispatchZGLib) ( tDispatchRequest request,
                                                 tDispatchComplete complete,
                                                 tZGVoidInput *appOpaquePtr);
  #endif
  /* end ZG Library API */


/**************************************/
/* Lower Layer interfaces to ZGDriver */
/**************************************/
#ifndef ZG_RAW_DRIVER

#define ZGLibLoadConfirmBuffer( A, B, C )

#define ZGLibLoadScanBuffer( A, B, C )

/* These TWO API(s) are exported to bolt onto the ZGDriver interface */
extern tZGVoidReturn
ZGLibConfirm(tZGU8 type, tZGDataPtr fourByteHeader, tZGDataPtr pBuf, tZGU16 len);

extern tZGVoidReturn
ZGLibIndicate(tZGU8 type, tZGDataPtr fourByteHeader, tZGDataPtr pBuf, tZGU16 len);

#else

extern tZGReturnStatus
ZGLibLoadConfirmBuffer( tZGU8Ptr ptrBuf, tZGU16 length, tZGU16 offset );

tZGReturnStatus
ZGLibLoadScanBuffer( tZGU8Ptr ptrBuf, tZGU16 length, tZGU16 offset );

/* These TWO API(s) are exported to bolt onto the ZGDriver interface */
extern tZGVoidReturn
ZGLibConfirm(tZGU8 type );

extern tZGVoidReturn
ZGLibIndicate(tZGU8 type);

#endif /* RAW DRIVER */

extern tZGVoidReturn
ZGLibInitialize( tZGVoidInput );


/*******************************************/
/* Link Management Indicates from ZGDriver */
/*******************************************/
#define DECLARE_ZG_INDICATE_CALLBACKS( A ) A
#define ZG_REGISTER_INDICATE( A )                                                       \
   extern tZGVoidReturn A  ( tZGU8 type, tZGDataPtr fourByteHeader,                     \
                               tZGDataPtr pBuf, tZGU16 len );
DECLARE_ZG_INDICATE_CALLBACKS( ZG_INDICATE_LIST )
#undef ZG_REGISTER_INDICATE

#define ZG_INDICATE_HANDLE( A )         kHandle_ ## A
#define ZG_REGISTER_INDICATE( A )	    ZG_INDICATE_HANDLE( A ) ,

#define  ENUM_ZG_INDICATE( A )                                                          \
typedef enum {                                                                          \
                kHandle_0=0,                                                            \
                kHandle_kNULL = 0,                                                      \
                A                                                                       \
                MAX_INDICATE_LIST                                                       \
 } tZGIndicateEnum;
ENUM_ZG_INDICATE( ZG_INDICATE_LIST )
typedef tZGIndicateEnum  tDispatchZGIndicate;
#undef ZG_REGISTER_INDICATE

#define MASK_INDICATE_SIZE    (((MAX_INDICATE_LIST - kNULL) / 8) + 1)

/* This must be the last X-macro #undef */
#define ZG_REGISTER_INDICATE( A )                                                       \
  case  ZG_INDICATE_HANDLE( A ) :                                                       \
        A ( type, fourByteHeader, pBuf, len );                                          \
       break;

#define  ZG_INDICATE_DISPATCHER()                                                       \
tZGVoidReturn zg_indicate_dispatch  ( tDispatchZGIndicate  indicate,                    \
                                      tZGU8 type,                                       \
                                      tZGDataPtr fourByteHeader,                        \
                                      tZGDataPtr pBuf,                                  \
                                      tZGU16 len )                                      \
{                                                                                       \
    switch ( indicate )                                                                 \
    {                                                                                   \
       ZG_INDICATE_LIST													                \
       default:                                                                         \
          ZGErrorHandler((ROM FAR char*)"Indicate");                                    \
    }                                                                                   \
}

tZGVoidReturn zg_indicate_dispatch ( tDispatchZGIndicate indicate,
                                            tZGU8 type,
                                            tZGDataPtr fourByteHeader,
                                            tZGDataPtr pBuf,
                                            tZGU16 len );

#define DISPATCH_INDICATE( A, B, C, D, E ) zg_indicate_dispatch ( A, B, C, D, E )

extern tZGBool ZGLibEnableIndicate( tDispatchZGIndicate handle, tZGBool bEnable );
/* End Indicate */


/*****************************/
/*  Library Queue Structure  */
/*****************************/
typedef struct
{
    tDispatchComplete      completeCallback;
    void*                  opaquePtr;
    tZGU8                  request[kLibMgrCxtBufLen];
    tZGU16                 len;
    tZGU8                  type;
    tZGU8                  info;
    tZGU8                  reqLen;
}tZGLibCall;

#include "TCPIP_Stack/ZGDriverIfaceApp.h"

/*
 * This function schedules a management request to be sent to G2100.
 *
 * Refer to table 1 in section 2.6 of "G2100 Programmer's Guide".
 * The corresponding SPI message has its "type" field set to kZGMACTypeMgmtReq (2).
*/
extern tZGReturnStatus
ZGLibManagementRequest (
    tZGU16             appMgmtValueLen,     /* Length of the additional info, to be filled by appPrepareCallback(), */
                                            /* that holds the payload portion of request/response.                  */
    tZGU8              appMgmtSubType,      /* This corresponds to the SPI message "subtype" field.                 */
                                            /* E.g., kZGMSGGetParam or kZGMSGSetParam.                              */
    tZGParam           appMgmtParamName,    /* This corresponds to the next field right after the "subtype" field.  */
                                            /* For kZGMSGSetParam, this is the "ParamID" field in Figure 38 of      */
                                            /* "G2100 Programmer's Guide".                                          */
                                            /* Valid values for kZGMSGGetParam/kZGMSGSetParam are enumerated        */
                                            /* and defined in tZGParam.                                             */
    tDispatchRequest   appPrepareCallback,  /* Callback function to prepare the payload portion of the request.     */
    tDispatchComplete  appDoneCallback,     /* Callback function to be called when G2100 completes this             */
                                            /* management request.                                                  */
    tZGVoidInput      *appOpaquePtr         /* A pointer to application's private data area.                        */
);

#else

#define ZGLibGetRadioState( A, B, C )       kZGFailure
#define ZGLibGetRTS( A, B, C )              kZGFailure
#define ZGLibSetRTS( A, B, C )              kZGFailure

#endif

#endif /*_ZGLIBIFACE_H */
