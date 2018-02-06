/*******************************************************************************

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

#ifndef _ZGDRIVERIFACEHAL_H_
#define _ZGDRIVERIFACEHAL_H_

/*****************************************************************************
 * FUNCTION: zgDriverEintHandler
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      N/A
 *
 *
 *  NOTES: This function must be called once, each time an external interrupt
 *      is received from the ZeroG device.   The ZG Driver will schedule any
 *      subsequent SPI communication to process the interrupt.
 *****************************************************************************/
tZGVoidReturn zgDriverEintHandler(tZGVoidInput);

/*****************************************************************************
 * FUNCTION: zgDriverSpiTxRxDoneHandler
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      N/A
 *
 *
 *  NOTES: This function must be called once, each time the SPI driver
 *      completes an SPI operation.  The ZG Driver will, upon receiving this
 *      function call, schedule a new SPI operation to the driver if one
 *      is pending.
 *****************************************************************************/
tZGVoidReturn zgDriverSpiTxRxDoneHandler(tZGVoidInput);

#endif /*_ZGDRIVERIFACEHAL_H_ */
