/* ###*B*###
* ERIKA Enterprise - a tiny RTOS for small microcontrollers
*
* Copyright (C) 2002-2008  Evidence Srl
*
* This file is part of ERIKA Enterprise.
*
* ERIKA Enterprise is free software; you can redistribute it
* and/or modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation, 
* (with a special exception described below).
*
* Linking this code statically or dynamically with other modules is
* making a combined work based on this code.  Thus, the terms and
* conditions of the GNU General Public License cover the whole
* combination.
*
* As a special exception, the copyright holders of this library give you
* permission to link this code with independent modules to produce an
* executable, regardless of the license terms of these independent
* modules, and to copy and distribute the resulting executable under
* terms of your choice, provided that you also meet, for each linked
* independent module, the terms and conditions of the license of that
* module.  An independent module is a module which is not derived from
* or based on this library.  If you modify this code, you may extend
* this exception to your version of the code, but you are not
* obligated to do so.  If you do not wish to do so, delete this
* exception statement from your version.
*
* ERIKA Enterprise is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License version 2 for more details.
*
* You should have received a copy of the GNU General Public License
* version 2 along with ERIKA Enterprise; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301 USA.
* ###*E*### */

/******************************************************************************
*  FILE		 	: e_can1.c
*  DESCRIPTION  	: enhanced CAN bus 1 configuration using dma
*  CPU TYPE     	: dsPIC33FJ256MC710
*  AUTHOR	     	: Antonio Camacho Santiago
*  PROJECT	     	: DPI2007-61527
*  COMPANY	     	: Automatic Control Department,
*  				  Technical University of Catalonia
*
*  REVISION HISTORY:
*			 VERSION: 0.1
*     		  AUTHOR: Antonio Camacho Santiago
* 				DATE: April 2010
* 			COMMENTS: Adapted from Microchip CE127_ECAN_Crosswire demo
*****************************************************************************/

#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"

// Define ECAN Message Buffers
// ECAN1MSGBUF ecan1msgBuf __attribute__((space(dma),aligned(ECAN1_MSG_BUF_LENGTH*16)));
ECAN1MSGBUF ecan1msgBuf __attribute__((space(dma)));

/* Dma Initialization for ECAN1 Transmission */
void EE_ecan1_Dma2Init(void)
{
	DMACS0=0;
	DMA2CON=0x2020;
	DMA2PAD=0x0442;	/* ECAN 1 (C1TXD) */
	DMA2CNT=0x0007;
	DMA2REQ=0x0046;	/* ECAN 1 Transmit */
	DMA2STA=  __builtin_dmaoffset(ecan1msgBuf);
	DMA2CONbits.CHEN=1;
}


/* Dma Initialization for ECAN1 Reception */
void EE_ecan1_Dma3Init(void)
{
	DMACS0=0;
	DMA3CON=0x0020;
	DMA3PAD=0x0440;	/* ECAN 1 (C1RXD) */
	DMA3CNT=0x0007;
	DMA3REQ=0x0022;	/* ECAN 1 Receive */
	DMA3STA= __builtin_dmaoffset(ecan1msgBuf);
	DMA3CONbits.CHEN=1;
}


void EE_ecan1_ClkInit(void)
{
	/* FCAN is selected to be FCY */
	/* FCAN = FCY = 40MHz */
	C1CTRL1bits.CANCKS = 0x1;

	/*
	Bit Time = (Sync Segment + Propagation Delay + Phase Segment 1 +
	+ Phase Segment 2)=20*TQ
	Phase Segment 1 = 8TQ
	Phase Segment 2 = 6Tq
	Propagation Delay = 5Tq
	Sync Segment = 1TQ
	CiCFG1<BRP> =(FCAN /(2 ×N×FBAUD))– 1
	*/

	/* Synchronization Jump Width set to 4 TQ */
	C1CFG1bits.SJW = 0x3;
	/* Baud Rate Prescaler */
	C1CFG1bits.BRP = BRP_VAL;
	/* Phase Segment 1 time is 8 TQ */
	C1CFG2bits.SEG1PH=0x7;
	/* Phase Segment 2 time is set to be programmable */
	C1CFG2bits.SEG2PHTS = 0x1;
	/* Phase Segment 2 time is 6 TQ */
	C1CFG2bits.SEG2PH = 0x5;
	/* Propagation Segment time is 5 TQ */
	C1CFG2bits.PRSEG = 0x4;
	/* Bus line is sampled three times at the sample point */
	C1CFG2bits.SAM = 0x1;
}


void EE_ecan1_Init(void)
{
	/* Request Configuration Mode */
	C1CTRL1bits.REQOP=4;
	while(C1CTRL1bits.OPMODE!=4);

	EE_ecan1_ClkInit();

	/* 6 CAN Message Buffers in DMA RAM */
	C1FCTRLbits.DMABS = 0b001; 

	/*	Filter Configuration
	ecan1WriteRxAcptFilter(int n, long identifier, unsigned int exide,
	unsigned int bufPnt,unsigned int maskSel)

	n = 0 to 15 -> Filter number

	identifier -> SID <10:0> : EID <17:0>

	exide = 0 -> Match messages with standard identifier addresses
	exide = 1 -> Match messages with extended identifier addresses

	bufPnt = 0 to 14  -> RX Buffer 0 to 14
	bufPnt = 15 -> RX FIFO Buffer

	maskSel = 0	->	Acceptance Mask 0 register contains mask
	maskSel = 1	->	Acceptance Mask 1 register contains mask
	maskSel = 2	->	Acceptance Mask 2 register contains mask
	maskSel = 3	->	No Mask Selection
	
	usage: EE_ecan1_WriteRxAcptFilter(1,0x1FFEFFFF,1,1,0);
	*/

	/*	Mask Configuration
	ecan1WriteRxAcptMask(int m, long identifierMask, unsigned int mide,
	unsigned int exide)

	m = 0 to 2 -> Mask Number

	identifier -> SID <10:0> : EID <17:0>

	mide = 0 -> Match either standard or extended address message
	if filters match
	mide = 1 -> Match only message types that correpond to 'exide'
	bit in filter

	exide = 0 -> Match messages with standard identifier addresses
	exide = 1 -> Match messages with extended identifier addresses

	usage: EE_ecan1_WriteRxAcptMask(1,0x1FFFFFFF,1,1);
	*/
	
	/* Enter Normal Mode */
	C1CTRL1bits.REQOP=0;
	while(C1CTRL1bits.OPMODE!=0);

	/* ECAN transmit/receive message control */
	C1RXFUL1=C1RXFUL2=C1RXOVF1=C1RXOVF2=0x0000;
	/* ECAN1, Buffer 0 is a Transmit Buffer */
	C1TR01CONbits.TXEN0=1;
	/* Message Buffer 0 Priority Level */
	C1TR01CONbits.TX0PRI=0b11;
}


/*
This function configures Acceptance Filter "n"

Inputs:
n-> Filter number [0-15]
identifier-> Bit ordering is given below
Filter Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
								|____________|_____________________|
									SID10:0           EID17:0


Filter Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
														|___________|
															SID10:0
exide -> "0" for standard identifier
		"1" for Extended identifier

bufPnt -> Message buffer to store filtered message [0-15]
maskSel -> Optinal Masking of identifier bits [0-3]
*/
void EE_ecan1_WriteRxAcptFilter(int n, long identifier, unsigned int exide,
unsigned int bufPnt,unsigned int maskSel)
{

	unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
	unsigned int *sidRegAddr,*bufPntRegAddr,*maskSelRegAddr, *fltEnRegAddr;

	C1CTRL1bits.WIN=1;

	/* Obtain the Address of CiRXFnSID, CiBUFPNTn, CiFMSKSELn and CiFEN
	* register for a given filter number "n" */
	sidRegAddr = (unsigned int *)(&C1RXF0SID + (n << 1));
	bufPntRegAddr = (unsigned int *)(&C1BUFPNT1 + (n >> 2));
	maskSelRegAddr = (unsigned int *)(&C1FMSKSEL1 + (n >> 3));
	fltEnRegAddr = (unsigned int *)(&C1FEN1);

	// Bit-filed manupulation to write to Filter identifier register
	if(exide==1) { 	// Filter Extended Identifier
		eid15_0 = (identifier & 0xFFFF);
		eid17_16= (identifier>>16) & 0x3;
		sid10_0 = (identifier>>18) & 0x7FF;

		// Write to CiRXFnSID Register
		*sidRegAddr=(((sid10_0)<<5) + 0x8) + eid17_16;
		// Write to CiRXFnEID Register
		*(sidRegAddr+1)= eid15_0;

	}else{			// Filter Standard Identifier
		sid10_0 = (identifier & 0x7FF);
		*sidRegAddr=(sid10_0)<<5;// Write to CiRXFnSID Register
		*(sidRegAddr+1)=0;		 // Write to CiRXFnEID Register
	}

	// clear nibble
	*bufPntRegAddr = (*bufPntRegAddr) & (0xFFFF - (0xF << (4 *(n & 3))));
	// Write to C1BUFPNTn Register
	*bufPntRegAddr = ((bufPnt << (4 *(n & 3))) | (*bufPntRegAddr));

	// clear 2 bits
	*maskSelRegAddr = (*maskSelRegAddr) & (0xFFFF - (0x3 << ((n & 7) * 2)));
	// Write to C1FMSKSELn Register
	*maskSelRegAddr = ((maskSel << (2 * (n & 7))) | (*maskSelRegAddr));

	// Write to C1FEN1 Register
	*fltEnRegAddr = ((0x1 << n) | (*fltEnRegAddr));

	C1CTRL1bits.WIN=0;
}


/*
This function configures Acceptance Filter Mask "m"

Inputs:
m-> Mask number [0-2]
identifier-> Bit ordering is given below
Filter Mask Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
										|____________|_____________________|
											SID10:0           EID17:0


Filter Mask Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
															|___________|
																SID10:0

mide ->  "0"  Match either standard or extended address message if filters match
		"1"  Match only message types that correpond to 'exide' bit in filter
*/
void EE_ecan1_WriteRxAcptMask(int m, long identifier, unsigned int mide,
unsigned int exide)
{
	unsigned long sid10_0=0, eid15_0=0, eid17_16=0;
	unsigned int *maskRegAddr;

	C1CTRL1bits.WIN=1;

	// Obtain the Address of CiRXMmSID register for given Mask number "m"
	maskRegAddr = (unsigned int *)(&C1RXM0SID + (m << 1));

	// Bit-filed manupulation to write to Filter Mask register
	if(exide==1)
	{ 	// Filter Extended Identifier
		eid15_0 = (identifier & 0xFFFF);
		eid17_16= (identifier>>16) & 0x3;
		sid10_0 = (identifier>>18) & 0x7FF;

		if(mide==1)
		// Write to CiRXMnSID Register
		*maskRegAddr=((sid10_0)<<5) + 0x0008 + eid17_16;
		else
		// Write to CiRXMnSID Register
		*maskRegAddr=((sid10_0)<<5) + eid17_16;
		// Write to CiRXMnEID Register
		*(maskRegAddr+1)= eid15_0;

	}
	else
	{			// Filter Standard Identifier
		sid10_0 = (identifier & 0x7FF);
		if(mide==1)
		// Write to CiRXMnSID Register
		*maskRegAddr=((sid10_0)<<5) + 0x0008;
		else
		// Write to CiRXMnSID Register
		*maskRegAddr=(sid10_0)<<5;
		// Write to CiRXMnEID Register
		*(maskRegAddr+1)=0;
	}

	C1CTRL1bits.WIN=0;
}


/* ECAN Transmit Message Buffer Configuration

Inputs:
buf	-> Transmit Buffer Number

txIdentifier ->

Extended Identifier (29-bits) : 0b000f ffff ffff ffff ffff ffff ffff ffff
									|____________|_____________________|
											SID10:0           EID17:0



Standard Identifier (11-bits) : 0b0000 0000 0000 0000 0000 0fff ffff ffff
															|___________|
																SID10:0

Standard Message Format:
											Word0 : 0b000f ffff ffff ffff
														|____________|||___
															SID10:0   SRR   IDE

											Word1 : 0b0000 0000 0000 0000
														|____________|
															EID17:6

											Word2 : 0b0000 00f0 0000 ffff
													|_____||	  	 |__|
													EID5:0 RTR   	  DLC



Extended Message Format:
											Word0 : 0b000f ffff ffff ffff
														|____________|||___
															SID10:0   SRR   IDE

											Word1 : 0b0000 ffff ffff ffff
														|____________|
															EID17:6

											Word2 : 0bffff fff0 0000 ffff
													|_____||	  	 |__|
													EID5:0 RTR   	  DLC

ide -> "0"  Message will transmit standard identifier
	"1"  Message will transmit extended identifier



remoteTransmit -> "0" Message transmitted is a normal message
				"1" Message transmitted is a remote message

				Standard Message Format:
											Word0 : 0b000f ffff ffff ff1f
														|____________|||___
															SID10:0   SRR   IDE

											Word1 : 0b0000 0000 0000 0000
														|____________|
															EID17:6

											Word2 : 0b0000 0010 0000 ffff
													|_____||	  	 |__|
													EID5:0 RTR   	  DLC



				Extended Message Format:
											Word0 : 0b000f ffff ffff ff1f
														|____________|||___
															SID10:0   SRR   IDE

											Word1 : 0b0000 ffff ffff ffff
														|____________|
															EID17:6

											Word2 : 0bffff ff10 0000 ffff
													|_____||	  	 |__|
													EID5:0 RTR   	  DLC
*/
void EE_ecan1_WriteTxMsgBufId(unsigned int buf, long txIdentifier,
unsigned int ide, unsigned int remoteTransmit)
{
	unsigned long word0=0, word1=0, word2=0;
	unsigned long sid10_0=0, eid5_0=0, eid17_6=0;

	if(ide)
	{
		eid5_0  = (txIdentifier & 0x3F);
		eid17_6 = (txIdentifier>>6) & 0xFFF;
		sid10_0 = (txIdentifier>>18) & 0x7FF;
		word1 = eid17_6;
	}
	else
	{
		sid10_0 = (txIdentifier & 0x7FF);
	}

	if(remoteTransmit==1) { 	// Transmit Remote Frame

		word0 = ((sid10_0 << 2) | ide | 0x2);
		word2 = ((eid5_0 << 10)| 0x0200);}

	else {

		word0 = ((sid10_0 << 2) | ide);
		word2 = (eid5_0 << 10);
	}

	/* Obtain the Address of Transmit Buffer in DMA RAM
* for a given Transmit Buffer number */

	if(ide)
	ecan1msgBuf[buf][0] = (word0 | 0x0002);
	else
	ecan1msgBuf[buf][0] = word0;

	ecan1msgBuf[buf][1] = word1;
	ecan1msgBuf[buf][2] = word2;
}


/* ECAN Transmit Data

Inputs :
buf -> Transmit Buffer Number

dataLength -> Length of Data in Bytes to be transmitted

data1/data2/data3/data4 ->  Transmit Data Bytes
*/
void EE_ecan1_WriteTxMsgBufData(unsigned int buf, unsigned int dataLength,
unsigned int data1, unsigned int data2, unsigned int data3,
unsigned int data4)
{
	ecan1msgBuf[buf][2] = ((ecan1msgBuf[buf][2] & 0xFFF0) + dataLength) ;
	ecan1msgBuf[buf][3] = data1;
	ecan1msgBuf[buf][4] = data2;
	ecan1msgBuf[buf][5] = data3;
	ecan1msgBuf[buf][6] = data4;
}


void EE_ecan1_DisableRXFilter(int n)
{
	/* n -> Filter number [0-15] */
	unsigned int *fltEnRegAddr;
	C1CTRL1bits.WIN=1;
	fltEnRegAddr = (unsigned int *)(&C1FEN1);
	*fltEnRegAddr = (*fltEnRegAddr) & (0xFFFF - (0x1 << n));
	C1CTRL1bits.WIN=0;

}

#if 0
/* ECAN1 buffer loaded with Identifiers and Data */
void EE_ecan1_WriteMessage(void){

	/* Writing the message for Transmission
ecan1WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide,
unsigned int remoteTransmit);
ecan1WriteTxMsgBufData(unsigned int buf, unsigned int dataLength,
unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4);

buf -> Transmit Buffer number

txIdentifier -> SID<10:0> : EID<17:0>

ide = 0 -> Message will transmit standard identifier
ide = 1 -> Message will transmit extended identifier

remoteTransmit = 0 -> Normal message
remoteTransmit = 1 -> Message will request remote transmission

dataLength -> Data length can be from 0 to 8 bytes

data1, data2, data3, data4 -> Data words (2 bytes) each

*/

	EE_ecan1_WriteTxMsgBufId(0,0x1FFEFFFF,1,0);
	EE_ecan1_WriteTxMsgBufData(0,8,0x1111,0x2222,0x3333,0x4444);

}
#endif

/******************************************************************************
*
*    Function:			rxECAN1
*    Description:       moves the message from the DMA memory to RAM
*
*    Arguments:			*message: a pointer to the message structure in RAM
*						that will store the message.
*	 Author:            Jatinder Gharoo
*
*
******************************************************************************/
void EE_ecan1_Rx(ee_ecan_mID *message)
{
	unsigned int ide=0;
	unsigned int srr=0;
	unsigned long id=0;

	/*
	Standard Message Format:
	Word0 : 0bUUUx xxxx xxxx xxxx
				|____________|||
					SID10:0   SRR IDE(bit 0)
	Word1 : 0bUUUU xxxx xxxx xxxx
					|____________|
						EID17:6
	Word2 : 0bxxxx xxx0 UUU0 xxxx
			|_____||	     |__|
			EID5:0 RTR   	  DLC
	word3-word6: data bytes
	word7: filter hit code bits

	Substitute Remote Request Bit
	SRR->	"0"	 Normal Message
			"1"  Message will request remote transmission

	Extended  Identifier Bit
	IDE-> 	"0"  Message will transmit standard identifier
			"1"  Message will transmit extended identifier

	Remote Transmission Request Bit
	RTR-> 	"0"  Message transmitted is a normal message
			"1"  Message transmitted is a remote message
	*/
	/* read word 0 to see the message type */
	ide=ecan1msgBuf[message->buffer][0] & 0x0001;
	srr=ecan1msgBuf[message->buffer][0] & 0x0002;

	/* check to see what type of message it is */
	/* message is standard identifier */
	if(ide==0)
	{
		message->id=(ecan1msgBuf[message->buffer][0] & 0x1FFC) >> 2;
		message->frame_type=CAN_FRAME_STD;
	}
	/* mesage is extended identifier */
	else
	{
		id=ecan1msgBuf[message->buffer][0] & 0x1FFC;
		message->id=id << 16;
		id=ecan1msgBuf[message->buffer][1] & 0x0FFF;
		message->id=message->id+(id << 6);
		id=(ecan1msgBuf[message->buffer][2] & 0xFC00) >> 10;
		message->id=message->id+id;
		message->frame_type=CAN_FRAME_EXT;
	}
	/* check to see what type of message it is */
	/* RTR message */
	if(srr==1)
	{
		message->message_type=CAN_MSG_RTR;
	}
	/* normal message */
	else
	{
		message->message_type=CAN_MSG_DATA;
		message->data[0]=(unsigned char)ecan1msgBuf[message->buffer][3];
		message->data[1]=(unsigned char)((ecan1msgBuf[message->buffer][3] & 0xFF00) >> 8);
		message->data[2]=(unsigned char)ecan1msgBuf[message->buffer][4];
		message->data[3]=(unsigned char)((ecan1msgBuf[message->buffer][4] & 0xFF00) >> 8);
		message->data[4]=(unsigned char)ecan1msgBuf[message->buffer][5];
		message->data[5]=(unsigned char)((ecan1msgBuf[message->buffer][5] & 0xFF00) >> 8);
		message->data[6]=(unsigned char)ecan1msgBuf[message->buffer][6];
		message->data[7]=(unsigned char)((ecan1msgBuf[message->buffer][6] & 0xFF00) >> 8);
		message->data_length=(unsigned char)(ecan1msgBuf[message->buffer][2] & 0x000F);
	}
}


void EE_ecan1_ClearIntrFlags(void){
	/* Clear Interrupt Flags */
	IFS2bits.C1IF = 0;
	IFS1bits.DMA2IF = 0;
	IFS2bits.DMA3IF = 0;
	C1INTFbits.TBIF = 0;
	C1INTFbits.RBIF = 0;
}


//------------------------------------------------------------------------------
//    DMA and CAN interrupt handlers
//------------------------------------------------------------------------------

ISR2(_DMA2Interrupt)
{
	IFS1bits.DMA2IF = 0;          // Clear the DMA2 Interrupt Flag;
}


ISR2(_DMA3Interrupt)
{
	IFS2bits.DMA3IF = 0;          // Clear the DMA4 Interrupt Flag;
}

/* Callback function called by driver handlers  */
EE_ISR_callback ee_ecan1_ISR_cbk;

void EE_ecan1_set_ISR_callback(EE_ISR_callback isr_cbk)
{
	ee_ecan1_ISR_cbk = isr_cbk;
}

/* CAN bus 1 Interrupt, ISR2 type */
ISR2(_C1Interrupt)
{
	IFS2bits.C1IF = 0; // clear interrupt flag
	
	if(ee_ecan1_ISR_cbk != EE_ECAN1_NULL_CBK)
		ee_ecan1_ISR_cbk();
}

//------------------------------------------------------------------------------
//    API for users
//------------------------------------------------------------------------------

void EE_ecan1_Initialize()
{
	/* Clear Interrupt Flags */
	EE_ecan1_ClearIntrFlags();

	/* ECAN1 Initialisation
	Configure DMA Channel 0 for ECAN1 Transmit
	Configure DMA Channel 2 for ECAN1 Receive */
	EE_ecan1_Init();
	EE_ecan1_Dma2Init();
	EE_ecan1_Dma3Init();

	/* Enable ECAN1 Interrupt */
	IEC2bits.C1IE = 1;
	C1INTEbits.TBIE = 1;
	C1INTEbits.RBIE = 1;
}


void EE_ecan1_SendMessage(ee_ecan_mID *M2S)
{
	EE_ecan1_WriteTxMsgBufId((*M2S).buffer,(*M2S).id,(*M2S).frame_type,(*M2S).message_type);

	EE_ecan1_WriteTxMsgBufData((*M2S).buffer,
	(*M2S).data_length,
	((*M2S).data[1]<<8) + (*M2S).data[0],
	((*M2S).data[3]<<8) + (*M2S).data[2],
	((*M2S).data[5]<<8) + (*M2S).data[4],
	((*M2S).data[7]<<8) + (*M2S).data[6]);
	C1TR01CONbits.TXREQ0=1;
}
