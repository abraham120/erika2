/*******************************************************************************

 File:
        ZGDriverAccessHal.h

 Description:
        Zero G Driver Access Header file to the Hardware abstraction layer.

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

#ifndef _ZGDRIVERACCESSHAL_H_
#define _ZGDRIVERACCESSHAL_H_

#include "TCPIP_Stack/ZGAccessHal.h"

/* zgHALSpiInit - used by the ZG Driver to initialize the
 * SPI driver. */
tZGVoidReturn zgHALSpiInit(tZGVoidInput);

/* zgHALSpiTxRx - used by the ZG Driver to initiate/continue an
 * SPI operation Tx or Rx as dictated by the SPI context */
tZGBool zgHALSpiTxRx(tZGVoidInput);

/* zgHALSpiProcess - used by the ZG Driver to allow the SPI
 *  driver to operate in polled mode. If the driver is not
 *  a polled driver then this macro can be left blank. */
#define ZGHAL_SPI_PROCESS()

/* zgHALEintEnable - used by the ZG Driver to enable the external
 * interrupt service from the Zero G device. */
tZGVoidReturn zgHALEintEnable(tZGVoidInput);

/* zgHALEintDisable - used by the ZG Driver to disable the external
 * interrupt service from the Zero G Device. */
tZGVoidReturn zgHALEintDisable(tZGVoidInput);

/* zgHALEintInit - used by the ZG Driver to initialize the the
 * external Interrupt service. */
tZGVoidReturn zgHALEintInit(tZGVoidInput);

/* zgHALEintProcess - used by the ZG Driver to allow the Eint
 *  driver to operate in polled mode.  If the driver is not
 *  a polled driver then this macro can be left blank. */
#define ZGHAL_EINT_PROCESS()



/*****************************************************************************/
/* ZGHAL_SPI_... macros used by the ZG Driver to access the spi driver
 *  context */
/*****************************************************************************/

/* ZGHAL_SPI_CONTEXT_SET_TX_PRE_BUF_PTR - used by the ZG Driver to add a
 * transmit Pre-buffer pointer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGDataPtr ) */
#define ZGHAL_SPI_CONTEXT_SET_TX_PRE_BUF_PTR(pTxPreambleBuffer) SpiSetTxPreBufPtr(pTxPreambleBuffer)

/* ZGHAL_SPI_CONTEXT_SET_TX_PRE_LEN - used by the ZG Driver to specify
 * length of a transmit pre-buffer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGU8 ) */
#define ZGHAL_SPI_CONTEXT_SET_TX_PRE_LEN(txPreambleLength) SpiSetTxPreLen(txPreambleLength)

/* ZGHAL_SPI_CONTEXT_SET_TX_BUF_PTR - used by the ZG Driver to add a
 * transmit main buffer pointer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGDataPtr ) */
#define ZGHAL_SPI_CONTEXT_SET_TX_BUF_PTR(pTxBuffer) SpiSetTxBufPtr(pTxBuffer)

/* ZGHAL_SPI_CONTEXT_SET_TX_ROM_BUF_PTR - used by the ZG Driver to add a
 * ROM transmit main buffer pointer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(ROM tZGDataPtr ) */
#define ZGHAL_SPI_CONTEXT_SET_TX_ROM_BUF_PTR(pTxBuffer) SpiSetTxRomBufPtr(pTxBuffer)

/* ZGHAL_SPI_CONTEXT_SET_TX_LEN - used by the ZG Driver to specify
 * length of a transmit main buffer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGU16 ) */
#define ZGHAL_SPI_CONTEXT_SET_TX_LEN(txLength) SpiSetTxBufLen(txLength)

/* ZGHAL_SPI_CONTEXT_SET_RX_PRE_BUF_PTR - used by the ZG Driver to add a
 * receive pre-buffer pointer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGDataPtr ) */
#define ZGHAL_SPI_CONTEXT_SET_RX_PRE_BUF_PTR(pRxPreambleBuffer) SpiSetRxPreBufPtr(pRxPreambleBuffer)

/* ZGHAL_SPI_CONTEXT_SET_RX_PRE_LEN - used by the ZG Driver to specify
 * how many bytes to read from the SPI to the pre-buffer. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGU8 ) */
#define ZGHAL_SPI_CONTEXT_SET_RX_PRE_LEN(rxPreambleLength) SpiSetRxPreBufLen(rxPreambleLength)

/* ZGHAL_SPI_CONTEXT_SET_RX_BUF_PTR - used by the ZG Driver to add a
 * receive main buffer pointer to the SPI context. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGDataPtr ) */
#define ZGHAL_SPI_CONTEXT_SET_RX_BUF_PTR(pRxBuffer) SpiSetRxBufPtr(pRxBuffer)

/* ZGHAL_SPI_CONTEXT_SET_RX_LEN - used by the ZG Driver to specify
 * how many bytes to read from the SPI to the main buffer. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGU16 ) */
#define ZGHAL_SPI_CONTEXT_SET_RX_LEN(rxLength) SpiSetRxBufLen(rxLength)

/* ZGHAL_SPI_CONTEXT_SET_RX_EXCESS_LEN - used by the ZG Driver to
 * specify the extra length of the rx buffer beyond the
 * desired read length. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGDataPtr ) */
#define ZGHAL_SPI_CONTEXT_SET_RX_EXCESS_LEN(excessRxLength) SpiSetRxExcessLen(excessRxLength)

/* ZGHAL_SPI_CONTEXT_SET_SUPPRESS_DONE_HANDLER_CALL - used by the ZG Driver to set a
 * boolean in the SPI context to direct the SPI driver to suppress the done handler call. */
/* DEFINITION - tZGVoidReturn FunctionName(tZGBool ) */
#define ZGHAL_SPI_CONTEXT_SET_SUPPRESS_DONE_HANDLER_CALL(suppressDoneHandlerCall) SpiSetSuppressDoneHandlerCall(suppressDoneHandlerCall)

/* ZGHAL_ZG100_HW_RESET_CALL - used by the ZG Driver to perform a hardware reset of the ZG2100 device.
 * */
/* DEFINITION - tZGBool FunctionName(tZGVoidInput ) */
#define ZGHAL_ZG100_HW_RESET_CALL() MCHPHardwareResetZG2100()

#endif /*_ZGDRIVERACCESSHAL_H_ */
