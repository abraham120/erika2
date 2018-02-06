/*******************************************************************************

 File:
        ZGAccessSys.h

 Description:
        Microchip Access Header file to the System Services.
      Used by the ZGDriverAccessSys.h file.

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
#ifndef _ZG_ACCESSSYS_H_
#define _ZG_ACCESSSYS_H_

  #include "HardwareProfile.h"
  #include "TCPIP_Stack/TCPIP.h"
  #include "TCPIPConfig.h"

#if defined( STACK_USE_UART )
  #define ZG_PUTRSUART(x)     putrsUART(x)
  #define ZG_PUTSUART(x)      putsUART(x)
#else
  #define ZG_PUTRSUART(x)
  #define ZG_PUTSUART(x)
#endif

extern tZGVoidReturn MCHPSysAssert(tZGU16 tag, tZGTextPtr string);

#endif /* _ZG_ACCESSSYS_H_ */
