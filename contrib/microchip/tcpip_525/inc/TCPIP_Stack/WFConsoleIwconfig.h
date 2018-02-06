/******************************************************************************

 MRF24W10C Driver iwconfig
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24W10C WiFi controller
  -Reference: MRF24W10C Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFConsoleIwconfig.h
 Dependencies:	TCP/IP Stack header files
 Processor:		PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 Compiler:		Microchip C32 v1.10b or higher
				Microchip C30 v3.22 or higher
				Microchip C18 v3.34 or higher
 Company:		Microchip Technology, Inc.

 Software License Agreement

 Copyright (C) 2002-2010 Microchip Technology Inc.  All rights reserved.

 Microchip licenses to you the right to use, modify, copy, and distribute:
 (i)  the Software when embedded on a Microchip microcontroller or digital 
      signal controller product ("Device") which is integrated into 
      Licensee's product; or
 (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
      ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device used in 
	  conjunction with a Microchip ethernet controller for the sole purpose 
	  of interfacing with the ethernet controller.

 You should refer to the license agreement accompanying this Software for 
 additional information regarding your rights and obligations.

 THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY INCIDENTAL,
 SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST
 OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS BY
 THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS
 FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON
 THE BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR
 OTHERWISE.


 Author				Date		Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KH                 27 Jan 2010 Updated for MRF24WB0M
******************************************************************************/

#ifndef __WFCONSOLE_IWCONFIG_H
#define __WFCONSOLE_IWCONFIG_H

//============================================================================
//                                  Globals
//============================================================================

typedef struct
{
	UINT8 powerSaveState;	// power save state

	UINT8 cpId; 	// ID of a connection profle that is created by this
					// iwconfig cmd
	UINT8 connState;	// connection state
	BOOL	isIdle;		// true if connState is WF_CSTATE_NOT_CONNECTED
} tWFIwconfigCb;	// iwconfig control block

extern tWFIwconfigCb iwconfigCb;

//============================================================================
//                                  Function Prototypes
//============================================================================
extern void do_iwconfig_cmd(void);

//============================================================================
//                                  Function Prototypes (used by iwpriv)
//============================================================================
extern BOOL iwconfigSetCb(void);

#endif /* __WFCONSOLE_IWCONFIG_H */
