/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * version 2 along with ERIKA Enerprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
#include "./define.h"
#include "./eeuart.h"

#include "./variable.h"
#include "./util.h"

extern EE_INT8 (*Rx1IsrFunction)(EE_UINT8 data);
extern EE_INT8 (*Tx1IsrFunction)(EE_UINT8 data);

extern EE_INT8 (*Rx2IsrFunction)(EE_UINT8 data);
extern EE_INT8 (*Tx2IsrFunction)(EE_UINT8 data);


/* /\************************************************************************* */
/*  UART Port 1 */
/*  *************************************************************************\/ */

//__INLINE__ void EE_UART1_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
void EE_UART1_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
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
	if (mode == CTRL_FLOW) {	// Flow Control Mode
		U1MODEbits.RTSMD = 1;
		U1MODEbits.UEN = 2;
	} else {	// Simple Mode
		U1MODEbits.RTSMD = 0;
		U1MODEbits.UEN = 0;
	}
	U1MODE |= byteformat & 0x07; // Number of bit, Parity and Stop bits

#ifdef	INT_UART1_ENABLED
	//[mck] configure INT mode
	U1STA &= 0x5FFF;			// Set Tx Interrupt source
	U1STA |= TX_INT_LAST;
	IEC0bits.U1TXIE = 0;		// Disable Tx Interrupt
	IFS0bits.U1TXIF = 0;		// Clear ISR Flag

	U1STA &= 0xFF3F;			// Set Rx Interrupt source
	U1STA |= RX_INT_SINGLE;
	IEC0bits.U1RXIE = 1;		// Enable Rx Interrupt
	IFS0bits.U1RXIF = 0;		// Clear ISR Flag

	// priority
	_U1RXIP = DPS_U1RXIP;
	_U1TXIP = DPS_U1TXIP;
#endif

	/* TX & RX interrupt modes */
	U1STA = 0;
	U1STAbits.UTXEN = 1;
}

//__INLINE__ void EE_UART1_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode)
void EE_UART1_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode)
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

//__INLINE__ EE_INT8 EE_UART1_Send(unsigned char data)
EE_INT8 EE_UART1_Send(unsigned char data)
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

//__INLINE__ EE_INT8 EE_UART1_Receive(unsigned char* data)
EE_INT8 EE_UART1_Receive(unsigned char* data)
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

//__INLINE__ void EE_UART2_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
void EE_UART2_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
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
	if (mode == CTRL_FLOW) {	// Flow Control Mode
		U2MODEbits.RTSMD = 1;
#ifdef	RS485_PORT_UART2
		U2MODEbits.UEN = 0;
#else
		U2MODEbits.UEN = 2;
#endif
	} else {	// Simple Mode
		U2MODEbits.RTSMD = 0;
		U2MODEbits.UEN = 0;
	}
	U2MODE |= byteformat & 0x07; // Number of bit, Parity and Stop bits

#ifdef	INT_UART2_ENABLED
	//[mck] configure INT mode
	U2STA &= 0x5FFF;			// Set Tx Interrupt source
	U2STA |= TX_INT_LAST;
	IEC1bits.U2TXIE = 0;		// Disable Tx Interrupt
	IFS1bits.U2TXIF = 0;		// Clear ISR Flag

	U2STA &= 0xFF3F;			// Set Rx Interrupt source
	U2STA |= RX_INT_SINGLE;
	IEC1bits.U2RXIE = 1;		// Enable Rx Interrupt
	IFS1bits.U2RXIF = 0;		// Clear ISR Flag

	// priority
	_U2RXIP = DPS_U2RXIP;
	_U2TXIP = DPS_U2TXIP;
#endif

	/* TX & RX interrupt modes */
	U2STA = 0;
	U2STAbits.UTXEN = 1;

}

//__INLINE__ void EE_UART2_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode)
void EE_UART2_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode)
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

//__INLINE__ EE_INT8 EE_UART2_Send(unsigned char data)
EE_INT8 EE_UART2_Send(unsigned char data)
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

//__INLINE__ EE_INT8 EE_UART2_Receive(unsigned char* data)
EE_INT8 EE_UART2_Receive(unsigned char* data)
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

unsigned char	byteRcvd;		// for debugging in MPLAB IDE
ISR2(_U1RXInterrupt)
{
	/* reset RX interrupt flag */
	IFS0bits.U1RXIF = 0;

	// Execute callback function, if exists
	/*
	if (Rx1IsrFunction != NULL) {
		Rx1IsrFunction(0x00);
	}
	*/

	//[mck] read the data and put it into the buffer
	// check for receive errors
	if (U1STAbits.FERR == 1)
	{
		// frame error
	}
	// clear the overrun error to keep UART receiving
	else if (U1STAbits.OERR == 1)
	{
		// overrun error
		U1STAbits.OERR = 0;
	}
	else {
		// no error
		RingBuf	*pBuf = &UART1RXBuf;
		if(U1STAbits.URXDA == 1)		// data available in RX register
		{
			byteRcvd = U1RXREG;
			// check if the buffer is full
			if (IsBufferFull(pBuf) == DPS_FALSE)
			{
				PushBuffer(pBuf, byteRcvd);
			}
			else
			{
				// Error!!!
				//	a byte in data register will be lost
			}
		}
	}
}

//
// UART1 - RF
//	TX Interrupt Service Routine
//
unsigned char	byteSent;		// for debugging in MPLAB IDE
ISR2(_U1TXInterrupt)
{
	/* reset TX interrupt flag */
	IFS0bits.U1TXIF = 0;

	// Execute callback function
	/*
	if (Tx1IsrFunction != NULL) {
		Tx1IsrFunction(0x00);
	}
	*/

	// check if RF TX buffer has data
	RingBuf	*pBuf = &UART1TXBuf;
	{
		// check if the buffer is empty
		if (IsBufferEmpty(pBuf) == DPS_FALSE)
		// No. Send out the byte on top.
		{
			//if (U1STAbits.TRMT == 1)	// Do not check this!
										// TRMT shows status of TSR, not TXREG.
			{
				byteSent = PopBuffer(pBuf);
				U1TXREG = byteSent;
			}
		}
		else
		{
			// something's wrong
			//	put a dummy byte to TX Data register to keep UART TX INT invoked
			U1TXREG = 0;
		}

		if (IsBufferEmpty(pBuf) == DPS_TRUE) {
		// Yes. Disable TX INT.
		//	Will be re-enabled by application when there comes data to be sent via wireless.
			IEC0bits.U1TXIE = 0;	// disable TX INT
			UART1TX_INT_Enabled = DPS_FALSE;
		}
	}
}

//
// UART2 - Serial port
//	RX Interrupt Service Routine
//
ISR2(_U2RXInterrupt)
{
	/* reset RX interrupt flag */
	IFS1bits.U2RXIF = 0;

	// Execute callback function
	/*
	if (Rx2IsrFunction != NULL) {
		Rx2IsrFunction(0x00);
	}
	*/

	// my code here
	// check for receive errors
	if (U2STAbits.FERR == 1)
	{
		// frame error
	}
	// clear the overrun error to keep UART receiving
	else if (U2STAbits.OERR == 1)
	{
		// overrun error
		U2STAbits.OERR = 0;
	}
	else {
		RingBuf	*pBuf = &UART2RXBuf;
		// no error
		if(U2STAbits.URXDA == 1)		// data available in RX register
		{
			byteRcvd = U2RXREG;
			// check if the buffer is full
			if (IsBufferFull(pBuf) == DPS_FALSE)
			{
				PushBuffer(pBuf, byteRcvd);
			}
			else
			{
				// Error!!!
				//	a byte in data register will be lost
			}
		}
	}

	// enable Serial TX INT
	//	-> moved to TaskDebug

}

//
// UART2 - Serial port
//	TX Interrupt Service Routine
//
ISR2(_U2TXInterrupt)
{
	/* reset TX interrupt flag */
	IFS1bits.U2TXIF = 0;

	// Execute callback function
	/*
	if (Tx2IsrFunction != NULL) {
		Tx2IsrFunction(0x00);
	}
	*/

	// check if Serial TX buffer has data
	RingBuf	*pBuf = &UART2TXBuf;
	{
		// check if the buffer is empty
		if (IsBufferEmpty(pBuf) == DPS_FALSE)
		// No. Send out the byte on top.
		{
			//if (U2STAbits.TRMT == 1)		//
			{
				byteSent = PopBuffer(pBuf);
				U2TXREG = byteSent;
			}
		}
		else
		{
			// something's wrong
			//	put a dummy byte to TX Data register to keep UART TX INT invoked
			U2TXREG = 0;
		}

		if (IsBufferEmpty(pBuf) == DPS_TRUE) {
		// Yes. Disable TX INT.
		//	Will be re-enabled by application when there comes data to be sent via wireless.
			IEC1bits.U2TXIE = 0;	// disable TX INT
			UART2TX_INT_Enabled = DPS_FALSE;
		}
	}

}

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	//PR1   = 0x9c40;		/* Load the Period register wit the value 0xffff	*/
	PR1   = 0xFFFF;		/* Load the Period register wit the value 0xffff	*/
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
				* and clock source set to the internal
				* instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}

/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}
