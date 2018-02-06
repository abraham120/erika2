/*
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */

#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"
#include "mcu/microchip_dspic/inc/ee_mcu.h"
#include "common/eeuart.h"

/* /\************************************************************************* */
/*  UART Port 1 */
/*  *************************************************************************\/ */

EE_INT8 (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
EE_INT8 (*Tx1IsrFunction)(EE_UINT8 data) = NULL;

ISR2(_U1RXInterrupt)
{
	// Execute callback function
	if (Rx1IsrFunction != NULL) {
		Rx1IsrFunction(0x00);
	}
		
	/* reset RX interrupt flag */
	IFS0bits.U1RXIF = 0;           
}

ISR2(_U1TXInterrupt)
{
	// Execute callback function
	if (Tx1IsrFunction != NULL) {
		Tx1IsrFunction(0x00);
	}
		
	/* reset TX interrupt flag */
	IFS0bits.U1TXIF = 0;           
}

/* /\************************************************************************* */
/*  UART Port 2 */
/*  *************************************************************************\/ */

EE_INT8 (*Rx2IsrFunction)(EE_UINT8 data) = NULL;
EE_INT8 (*Tx2IsrFunction)(EE_UINT8 data) = NULL;

ISR2(_U2RXInterrupt)
{
	// Execute callback function
	if (Rx2IsrFunction != NULL) {
		Rx2IsrFunction(0x00);
	}
		
	/* reset RX interrupt flag */
	IFS1bits.U2RXIF = 0;           
}

ISR2(_U2TXInterrupt)
{
	// Execute callback function
	if (Tx2IsrFunction != NULL) {
		Tx2IsrFunction(0x00);
	}
		
	/* reset TX interrupt flag */
	IFS1bits.U2TXIF = 0;           
}
