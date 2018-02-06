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

#ifndef __INCLUDE_EEUART_H__
#define __INCLUDE_EEUART_H__

#include "ee.h"

#define CLOCK_FREQ	(40000000)      // Hz
#define INSTR_FREQ	(CLOCK_FREQ/2)	// Hz

#define BIT9		0x06
#define BIT8_ODD	0x04
#define BIT8_EVEN	0x02
#define BIT8_NO		0x00

#define BIT_STOP_1	0x00
#define BIT_STOP_2	0x01

#define CTRL_SIMPLE	0x00
#define CTRL_FLOW	0x01

#define TX_INT_SINGLE	0x8000
#define TX_INT_EMPTY	0x2000
#define TX_INT_LAST	0x0000

#define RX_INT_FULL	0x00C0
#define RX_INT_3OF4	0x0080
#define RX_INT_SINGLE	0x0040

/* /\************************************************************************* */
/*  UART Port 1 */
/*  *************************************************************************\/ */

extern EE_INT8 (*Rx1IsrFunction)(EE_UINT8 data);
extern EE_INT8 (*Tx1IsrFunction)(EE_UINT8 data);

__INLINE__ void EE_UART1_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
{
	/* Stop UART port */
	U1MODEbits.UARTEN = 0;
	
	/* Disable Interrupts */
	IEC0bits.U1RXIE = 0;
	IEC0bits.U1TXIE = 0;
	
	/* Clear Interrupt flag bits */
	IFS0bits.U1RXIF = 0;
	IFS0bits.U1TXIF = 0;
		
	/* Set IO pins */
	TRISFbits.TRISF2 = 1;	// RX Pin
	TRISFbits.TRISF3 = 0;	// TX Pin
	if (mode) {
		TRISDbits.TRISD14 = 1;	// CTS Pin
		TRISDbits.TRISD15 = 0;	// RTS Pin
	}
	
	/* baud rate */
	U1BRG  = (2500000ul / baud) - 1; // With BRGH = 0
	//U1BRG = 21 // For 115200 with Fcy = 40MHz
	
	/* Operation settings and start port */
	U1MODE = 0;
	U1MODEbits.BRGH = 0;
	U1MODEbits.UARTEN = 1;
	if (mode) {	// Flow Control Mode
		U1MODEbits.RTSMD = 1;
		U1MODEbits.UEN = 2;
	} else {	// Simple Mode
		U1MODEbits.RTSMD = 0;
		U1MODEbits.UEN = 0;	
	}
	U1MODE |= byteformat & 0x07; // Number of bit, Parity and Stop bits

	/* TX & RX interrupt modes */
	U1STA = 0;
	U1STAbits.UTXEN = 1;
}

__INLINE__ void EE_UART1_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode)
{
	Rx1IsrFunction = RxFunc;
	Tx1IsrFunction = TxFunc;
	
	if (RxFunc) {
		U1STA &= 0x5FFF;		// Set Rx Interrupt source
		U1STA |= rxmode & 0xA000;
		IEC0bits.U1RXIE = 1;		// Enable Rx Interrupt	
		IFS0bits.U1RXIF = 0;		// Clear ISR Flag
	}

	if (TxFunc) {
		U1STA &= 0xFF3F;		// Set Tx Interrupt source
		U1STA |= txmode & 0x00C0;
		IEC0bits.U1TXIE = 1;		// Enable Tx Interrupt	
		IFS0bits.U1TXIF = 0;		// Clear ISR Flag
	}	
}

__INLINE__ EE_INT8 EE_UART1_Send(unsigned char data)
{
	if (Tx1IsrFunction) {	// Interrupt mode
		//...
	} else {		// Polling mode
		//unsigned int i;
		
		while (U1STAbits.UTXBF);
		U1TXREG = data;
		while(!U1STAbits.TRMT);
		//for(i=0; i<2000; i++);	
	}
	return 0;
}

__INLINE__ EE_INT8 EE_UART1_Receive(unsigned char* data)
{
	if (Rx1IsrFunction) {	// Interrupt mode
		//...
	} else {		// Polling mode
		if (U1STAbits.OERR) {
			U1STAbits.OERR = 0;
			return -2;
		}
	
		if (U1STAbits.URXDA) {
			*data = U1RXREG & 0x00FF;
			return 0;
		} else {
			*data = 0;
			return -1;
		}
	}
	
	return 0;
}

/* /\************************************************************************* */
/*  UART Port 2 */
/*  *************************************************************************\/ */

extern EE_INT8 (*Rx2IsrFunction)(EE_UINT8 data);
extern EE_INT8 (*Tx2IsrFunction)(EE_UINT8 data);

__INLINE__ void EE_UART2_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
{
	/* Stop UART port */
	U2MODEbits.UARTEN = 0;
	
	/* Disable Interrupts */
	IEC1bits.U2RXIE = 0;
	IEC1bits.U2TXIE = 0;
	
	/* Clear Interrupt flag bits */
	IFS1bits.U2RXIF = 0;
	IFS1bits.U2TXIF = 0;
		
	/* Set IO pins */
	TRISFbits.TRISF4 = 1;	// RX Pin
	TRISFbits.TRISF5 = 0;	// TX Pin
	if (mode) {
		TRISFbits.TRISF12 = 1;	// CTS Pin
		TRISFbits.TRISF13 = 0;	// RTS Pin
	}
	
	/* baud rate */
	U2BRG  = (2500000ul / baud) - 1; // With BRGH = 0
	//U2BRG = 21; // For 115200 with Fcy = 40MHz
	
	/* Operation settings and start port */
	U2MODE = 0;
	U2MODEbits.BRGH = 0;
	U2MODEbits.UARTEN = 1;
	if (mode) {	// Flow Control Mode
		U2MODEbits.RTSMD = 1;
		U2MODEbits.UEN = 2;
	} else {	// Simple Mode
		U2MODEbits.RTSMD = 0;
		U2MODEbits.UEN = 0;	
	}
	U2MODE |= byteformat & 0x07; // Number of bit, Parity and Stop bits

	/* TX & RX interrupt modes */
	U2STA = 0;
	U2STAbits.UTXEN = 1;
}

__INLINE__ void EE_UART2_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode)
{
	Rx2IsrFunction = RxFunc;
	Tx2IsrFunction = TxFunc;
	
	if (RxFunc) {
		U2STA &= 0x5FFF;		// Set Rx Interrupt source
		U2STA |= rxmode & 0xA000;
		IEC1bits.U2RXIE = 1;		// Enable Rx Interrupt	
		IFS1bits.U2RXIF = 0;		// Clear ISR Flag
	}

	if (TxFunc) {
		U2STA &= 0xFF3F;		// Set Tx Interrupt source
		U2STA |= txmode & 0x00C0;
		IEC1bits.U2TXIE = 1;		// Enable Tx Interrupt	
		IFS1bits.U2TXIF = 0;		// Clear ISR Flag
	}	
}

__INLINE__ EE_INT8 EE_UART2_Send(unsigned char data)
{
	if (Tx2IsrFunction) {	// Interrupt mode
		//...
	} else {		// Polling mode
		//unsigned int i;
		
		while (U2STAbits.UTXBF);
		U2TXREG = data;
		while(!U2STAbits.TRMT);
		//for(i=0; i<2000; i++);	
	}
	return 0;
}

__INLINE__ EE_INT8 EE_UART2_Receive(unsigned char* data)
{
	if (Rx2IsrFunction) {	// Interrupt mode
		//...
	} else {		// Polling mode
		if (U2STAbits.OERR) {
			U2STAbits.OERR = 0;
			return -2;
		}
	
		if (U2STAbits.URXDA) {
			*data = U2RXREG & 0x00FF;
			return 0;
		} else {
			*data = 0;
			return -1;
		}
	}
	return 0;
}

#endif
