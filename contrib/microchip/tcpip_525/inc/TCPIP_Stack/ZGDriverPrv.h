/*******************************************************************************

 File:
        ZGDriverPrv.h

 Description:
        Zero G Driver Private Header file.

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

#ifndef _ZGDRIVERPRV_H_
#define _ZGDRIVERPRV_H_


/* driver message type definitions - DATA */
#define kZGMSGDataStd           ((tZGU8)1)
#define kZGMSGNullDataStd       ((tZGU8)2)
/* reserved value               ((tZGU8)3) */
#define kZGMSGDataUntampered    ((tZGU8)4)
/* SPI message indices */
#define kZGPreambleCmdIdx           (0)
#define kZGPreambleTypeIdx          (1)
#define kZGPreambleSubTypeIdx       (2)
#define kZGPreambleSetParamIDIdx    (3)
#define kZGPreambleGetParamIDIdx    (3)
#define kZGGetParamReqSZ            (4)
#define kZGSetParamReqSZ            (2)
#define kZGDataConfirmResultIdx     (4)
#define kZGDataConfirmReqIDIdx      (3)
#define kZGMgmtConfirmResultIdx     (0)
/* SPI message type values which appear in the
 * kZGPreambleTypeIdx for each message */
#define kZGMACTypeDataReq           ((tZGU8)1)
#define kZGMACTypeMgmtReq           ((tZGU8)2)
#define kZGMACTypeTxDataConfirm     ((tZGU8)1)
#define kZGMACTypeMgmtConfirm       ((tZGU8)2)
#define kZGMACTypeRxDataIndicate    ((tZGU8)3)
#define kZGMACTypeMgmtIndicate      ((tZGU8)4)
/* buffer sizes (bytes) used on G2100 to receive packets */
/* Data packets use a single head buffer followed by the
 * required number of continue buffers to fullfill the
 * request.  Management packets only use continue buffers */
#define kZGTypeSubTypeSize (2)
#define kZGHeadBufferSize  (10)
#define kZGContinueBufferSize (232)

/* SPI direction used by MAC to COM communication */
#define kZGDirRead  (0u)
#define kZGDirWrite (1u)

#define kZGMsgPreambleLen           (3)
#define kZGPreBufLen                (8)
#define kZGReadShortThresholdLen    (4)

/* offsets and lengths in the G2100 System Information
 * block that can be read using the kZGComRegSysInfoData */
#define kZGCOMSysInfoOffsetVersionNumber    (0)
#define kZGCOMSysInfoLenVersionNumber       (2u)
#define kZGCOMSysInfoOffsetRxHeaderSize     (98)
#define kZGCOMSysInfoLenRxHeaderSize        (2)
#define kZGCOMSysInfoOffsetRxContinueSize   (100)
#define kZGCOMSysInfoLenRxContinueSize      (2)

#define kZGCOMCmdLen    (1)
#define kZGCOMStatusLen (1)
/* SPI message command values that appear in kZGPreambleCmdIdx */
#define kZGCOMCmdFifoAccess         (0x80)
#define kZGCOMCmdWtFifoWithHeadRing (kZGCOMCmdFifoAccess | 0x20)
#define kZGCOMCmdWtFifoNoHeadRing   (kZGCOMCmdFifoAccess | 0x30)
#define kZGCOMCmdRdFifo             (kZGCOMCmdFifoAccess | 0x00)
#define kZGCOMCmdRdFifoDone         (kZGCOMCmdFifoAccess | 0x50)
#define kZGCOMCmdWtFifoDone         (kZGCOMCmdFifoAccess | 0x40)
#define kZGCOMCmdReadRegister       (0x40)
#define kZGCOMCmdWriteRegister      (0x00)

/* these definitions represent register addresses
 * for the G2100 that can be read and written */
#define kZGCOMRegHostInt            (0x01) /* 8-bit register containing 1st level interrupt bits. */
#define kZGCOMRegHostIntMask        (0x02) /* 8-bit register containing 1st level interrupt mask. */
#define kZGCOMRegSysInfoData        (0x21) /* 8-bit register to read System Information data window. */
#define kZGCOMRegRAW0Ctrl0          (0x25)
#define kZGCOMRegRAW0Ctrl1          (0x26)
#define kZGCOMRegRAW0Index          (0x27)
#define kZGCOMRegRAW0Status         (0x28)
#define kZGCOMRegRAW1Ctrl0          (0x29)
#define kZGCOMRegRAW1Ctrl1          (0x2a)
#define kZGCOMRegSysInfoIndex       (0x2b) /* 16-bit register used to change the offset inside the sys info window. */
#define kZGCOMRegSysInfoStatus      (0x2c) /* 16-bit register used to test the satus of the sys info window. */
#define kZGCOMRegHostInt2           (0x2d) /* 16-bit register containing 2nd level interrupt bits */
#define kZGCOMRegHostInt2Mask       (0x2e) /* 16-bit register containing 2nd level interrupt mask. */
#define kZGCOMRegFifo0ByteCnt       (0x33) /* 16-bit register containing bytes ready to read on Fifo 0 */
#define kZGCOMRegFifo1ByteCnt       (0x35) /* 16-bit register containing bytes ready to read on Fifo 1 */
#define kZGCOMRegWrtFifo0ByteCnt    (0x2f) /* 16-bit register containing available write size for fifo 0 */
#define kZGCOMRegLoPwrCtrlReg       (0x3d) /* 16-bit register used to control low power mode on the G2100 */
#define kZGCOMRegIndexAddrReg       (0x3e) /* 16-bit register to move the data window */
#define kZGCOMRegIndexDataReg       (0x3f) /* 16-bit register to read the address in the kZGCOMRegIndexAddrReg */
/* these definitions represent register byte lengths
 * for the registers above */
#define kZGCOMRegHostIntLen         (1)
#define kZGCOMRegHostIntMaskLen     (1)
#define kZGCOMRegSysInfoDataLen     (1)
#define kZGCOMRegHostInt2Len        (2)
#define kZGCOMRegRAW1Ctrl1Len       (2)
#define kZGCOMRegRAW0Ctrl1Len       (2)
#define kZGCOMRegSysInfoIndexLen    (2)
#define kZGCOMRegSysInfoStatusLen   (2)
#define kZGCOMRegHostInt2MaskLen    (2)
#define kZGCOMRegFifo1ByteCntLen    (2)
#define kZGCOMRegFifo0ByteCntLen    (2)
#define kZGCOMRegWrtFifo0ByteCntLen (2)
#define kZGCOMRegLoPwrCtrlRegLen    (2)
#define kZGCOMRegIndexAddrRegLen    (2)
#define kZGCOMRegIndexDataRegLen    (2)
/* these definitions represent register addresses
 * for the G2100 that can be accessed via the
 * kZGCOMRegIndexAddrReg */
#define kZGCOMRegAnalogStatusReg    (0x2a) /* 16-bit read only register providing hardware status bits */
#define kZGCOMRegConfigCtrl0Reg     (0x2e) /* 16-bit register used to initiate Hard reset */
#define kZGCOMRegLoPwrStatusReg     (0x3e) /* 16-bit register read to determine when low power is done */
/* kZGCOMRegFifoByteCntMask - indicates the bits in the
 *  fifo byte count registers that represent the
 *  actual count. */
#define kZGCOMRegFifoByteCntMask    (0x0fff)
/* kZGCOMRegNotInResetMask - this bit is in the first byte
 * of the kZGCOMRegAnalogStatusReg. It is used to determine
 * when the G2100 is in reset.  0 - the chip is in reset
 * 1 - the chip is NOT in reset. */
#define kZGCOMRegNotInResetMask     ((tZGU16)(0x1000))
/* kZGCOMRegEnableLoPwrMask - this value masks the bit(s) that
 * are used by the Host to enable/disable low power mode on
 * the G2100.  This mask should be applied to register
 * kZGCOMRegLoPwrCtrlReg which is an indirect register that
 * is accessed via kZGCOMRegIndexAddrReg */
#define kZGCOMRegEnableLoPwrMask    (0x01)

/* these definitions represent individual interrupt
 *  bits for the 8-bit host interrupt register
 *  kZGCOMRegHostInt and kZGCOMRegHostIntMask */
#define kZGCOMRegHostIntMaskInt2        (0x01u)
#define kZGCOMRegHostIntMaskFifo1Thresh (0x80)
#define kZGCOMRegHostIntMaskFifo0Thresh (0x40u)
#define kZGCOMRegHostIntMaskRAW1Intr0   (0x04)
#define kZGCOMRegHostIntMaskRAW0Intr0   (0x02)
#define kZGCOMRegHostIntMaskAllInt      (0xff)
#define kZGCOMRegHost2IntMaskAllInt     (0xffff)
/* these definitions are used in calls to enable and
 * disable interrupt bits. */
#define kZGCOMIntDisable ((tZGU8)0)
#define kZGCOMIntEnable  ((tZGU8)1)

/* tZGRdWtContext - The read write context is used by the
 * MAC layer to submit a fifo operation to the COM layer. */
typedef struct
{
    tZGU16 len;
    tZGU8  dir;
}tZGRdWtContext;

/* tZGMacContext - Used by the MAC layer to manage State information */
typedef struct
{
    tZGBool bMgmtRxMsgReady;     /* true when ZG chip has mgmt msg ready for host to read */
    tZGBool bMgmtTxMsgReady;     /* true when mgmt Tx msg is ready to be sent to chip */
    tZGBool bDataTrafficEnabled; /* set to true when the driver allows data requests to occur */
    tZGBool bComIdle;
    tZGU8   pendingMgmtConfirm;  /* management confirm msg that should be received next */
}tZGMacContext;

/* tComContext - Used by the COM layer to manage State information */
typedef struct
{
    tZGU16 versionNumber; /* the G2100 version number read from the sys info block */
    tZGU8 regBuf[4]; /* buffer used to read/write registers */
    tZGU8 spiCmdBuf[kZGCOMCmdLen]; /* buffer used to write a spi command */
    tZGU8 statusBuf[kZGCOMStatusLen]; /* buffer used to read the g2100 status */
    tZGU8 state; /* state machine state */
    tZGBool bInitDevice; /* control variable set true during device init. */
    tZGBool bRdWtReady; /* control variable that indicates whether there is an operation pending */
    tZGVolatile tZGBool bIntServiceReq; /* control variable that indicates whether an interrupt needs servicing */
    tZGBool bLowPowerModeActive; /* control variable that indicates whether Power save Poll is active. */
    tZGBool bLowPowerModeDesired;  /* control veriable that indicates whether Power save Poll is desired. */
}tComContext;

/* tZGDriverContext - convenient storage for all the State information for
 * the ZGDriver. */
typedef struct
{
    tZGRdWtContext  rdWt;
    tZGMacContext   mac;
    tComContext     com;
}tZGDriverContext;

extern tZGDriverContext gblDriverContext;
/* macros used to access Driver State variables */
#define RWCXT (gblDriverContext.rdWt)
#define MACCXT (gblDriverContext.mac)
#define COMCXT (gblDriverContext.com)

/* ZGPrvMacInit - called by ZGInit to initialize the ZGMAC
 * layer. */
extern tZGVoidReturn ZGPrvMacInit(tZGVoidInput);
/* ZGPrvComInit - called by ZGPrvMacInit to initialize the ZGCOM
 * layer. */
extern tZGVoidReturn ZGPrvComInit(tZGVoidInput);
/* ZGPrvMacOpComplete - called by COM layer to notify MAC layer
 * when a submitted rd/write operation has completed. */
extern tZGVoidReturn ZGPrvMacOpComplete(tZGVoidInput);
/* ZGPrvMacReadReady - called by the COM layer to notify the
 * MAC layer when a submitted */
extern tZGVoidReturn ZGPrvMacReadReady(tZGVoidInput);
/* ZGPrvComFifoOperation - called by the MAC layer to initiate
 * a FIFO operation in the COM layer. */
extern tZGVoidReturn ZGPrvComFifoOperation(tZGVoidInput);
/* ZGPrvComStateMachine - called by the MAC layer to give
 * the COM layer an opportunity to run. */
extern tZGVoidReturn ZGPrvComStateMachine(tZGVoidInput);
/* ZGPrvComSetLowPowerMode - called by the MAC layer to
 * invoke the desired behavior by the COM layer for
 * controlling low power mode on the G2100. */
extern tZGVoidReturn ZGPrvComSetLowPowerMode(tZGBool bEnable);

extern tZGU16 Read16BitZGRegister(tZGU8 regId);
extern tZGVoidReturn Write16BitZGRegister(tZGU8 regId, tZGU16 value);
extern tZGU8 Read8BitZGRegister(tZGU8 regId);
extern tZGVoidReturn Write8BitZGRegister(tZGU8 regId, tZGU8 value);
extern tZGVoidReturn WriteZGArray(tZGU8 regId, tZGU8 *pBuf, tZGU16 length);
extern tZGVoidReturn WriteZGROMArray(tZGU8 regId, ROM tZGU8 *pBuf, tZGU16 length);
extern tZGVoidReturn ReadZGArray(tZGU8  regId, tZGU8 *pBuf, tZGU16 length);

#endif /*_ZGDRIVERPRV_H_ */
