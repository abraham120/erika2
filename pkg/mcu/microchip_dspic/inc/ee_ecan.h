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
 *  FILE		 	: e_can1.h
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

#ifndef _ECAN_DEF_H
#define _ECAN_DEF_H

#define ECAN1_MSG_BUF_LENGTH 	8

#define EE_BAUDRATE_eCAN1 50000L
//#define EE_BAUDRATE_eCAN1 100000L
//#define EE_BAUDRATE_eCAN1 250000L
//#define EE_BAUDRATE_eCAN1 500000L
//#define EE_BAUDRATE_eCAN1 1000000L

//#define EE_BAUDRATE_eCAN2 1000000L

#define CAN_MSG_DATA	0x01 // message type
#define CAN_MSG_RTR		0x02 // data or RTR
#define CAN_FRAME_EXT	0x03 // Frame type
#define CAN_FRAME_STD	0x04 // extended or standard

/* message structure in RAM */
typedef struct{
	/* keep track of the buffer status */
	unsigned char buffer_status;
	/* RTR message or data message */
	unsigned char message_type;
	/* frame type extended or standard */
	unsigned char frame_type;
	/* buffer being used to reference the message */
	unsigned char buffer;
	/* 29 bit id max of 0x1FFF FFFF
	*  11 bit id max of 0x7FF */
	unsigned long id;
	/* message data */
	unsigned char data[8];
	/* received message data length */
	unsigned char data_length;
}ee_ecan_mID;



/* CAN Baud Rate Configuration 		*/
#define FCAN  	40000000L
#ifdef EE_BAUDRATE_eCAN1
	#define BITRATE1 EE_BAUDRATE_eCAN1
#else
	#define BITRATE1 50000L//100000//50000// 1000000
	#warning By default: CAN 1 baudrate set to 50kbps
#endif
#define NTQ 	20L		// 20 Time Quanta in a Bit Time

#define BRP_VAL		(((FCAN/BITRATE1)/(2*NTQ))-1)

/* CAN Message Buffer Configuration */
typedef unsigned int ECAN1MSGBUF [ECAN1_MSG_BUF_LENGTH][8];
extern ECAN1MSGBUF  ecan1msgBuf __attribute__((space(dma)));

void EE_ecan1_Dma2Init(void);
void EE_ecan1_Dma3Init(void);
void EE_ecan1_ClkInit(void);
void EE_ecan1_Init(void);
void EE_ecan1_WriteRxAcptFilter(int n, long identifier, unsigned int exide, unsigned int bufPnt,unsigned int maskSel);
void EE_ecan1_WriteRxAcptMask(int m, long identifier, unsigned int mide, unsigned int exide);
void EE_ecan1_WriteTxMsgBufId(unsigned int buf, long txIdentifier, unsigned int ide, unsigned int remoteTransmit);
void EE_ecan1_WriteTxMsgBufData(unsigned int buf, unsigned int dataLength, unsigned int data1, unsigned int data2, unsigned int data3, unsigned int data4);
void EE_ecan1_DisableRXFilter(int n);
void EE_ecan1_WriteMessage(void);
void EE_ecan1_Rx(ee_ecan_mID *message);
void EE_ecan1_ClearIntrFlags(void);
void EE_ecan1_Config(void);
void EE_ecan1_Initialize(void);
void EE_ecan1_SendMessage(ee_ecan_mID *M2S);

#define EE_ECAN1_NULL_CBK ((EE_ISR_callback)0)
void EE_ecan1_set_ISR_callback(EE_ISR_callback isr_cbk);
 
#endif
