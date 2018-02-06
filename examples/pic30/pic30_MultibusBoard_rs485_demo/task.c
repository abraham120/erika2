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
 
#include "ee.h"
#include "define.h"
#include "eeuart.h"
#include "variable.h"
#include "driver.h"
#include "util.h"

//=========================================================================
TASK(TaskDebug)
{
	RingBuf *		pBufSrc;
	RingBuf *		pBufDst;
	unsigned char	count, byte;

	while (1) {
		// check if data available from RF
		//	then, move it to SerialTXBuf and enable TX INT
		pBufSrc = &UART1RXBuf;
		pBufDst = &UART2TXBuf;
		ENTER_CRITICAL_SECTION();
		count = CountBuffer(pBufSrc);
		EXIT_CRITICAL_SECTION();
		if (count >= DPS_MSG_SIZE) {
			// move data to SerialTXBuf
			ENTER_CRITICAL_SECTION();
			do {
				byte = PopBuffer(pBufSrc);
				if (IsBufferFull(pBufDst) == DPS_FALSE)
					PushBuffer(pBufDst, byte);
				else {
					//ERROR: buffer full
				}
			} while (IsBufferEmpty(pBufSrc) == DPS_FALSE);
			EXIT_CRITICAL_SECTION();

			if (UART2TX_INT_Enabled == DPS_FALSE)
			{
				ENTER_CRITICAL_SECTION();
				//enable UART2 TX INT to send the data via Serial Port
				IEC1bits.U2TXIE = 1;		// Enable Tx Interrupt
				// set the flag
				UART2TX_INT_Enabled = DPS_TRUE;
				EXIT_CRITICAL_SECTION();
			}
		}

		// check if data available from Serial Port
		//	then, move it to RFTXBuf and enable TX INT
		pBufSrc = &UART2RXBuf;
		pBufDst = &UART1TXBuf;
		ENTER_CRITICAL_SECTION();
		count = CountBuffer(pBufSrc);
		EXIT_CRITICAL_SECTION();
		if (count >= DPS_MSG_SIZE) {
			// move data to SerialTXBuf
			ENTER_CRITICAL_SECTION();
			do {
				byte = PopBuffer(pBufSrc);
				if (IsBufferFull(pBufDst) == DPS_FALSE)
					PushBuffer(pBufDst, byte);
				else {
					//ERROR: buffer full
				}
			} while (IsBufferEmpty(pBufSrc) == DPS_FALSE);
			EXIT_CRITICAL_SECTION();

			if (UART1TX_INT_Enabled == DPS_FALSE)
			{
				ENTER_CRITICAL_SECTION();
				//enable UART1 TX INT to send the data via RF
				IEC0bits.U1TXIE = 1;		// Enable Tx Interrupt
				// set the flag
				UART1TX_INT_Enabled = DPS_TRUE;
				EXIT_CRITICAL_SECTION();
			}
		}
	}	// while (1)
}

/* Send a character using the UART2 port
 */
TASK(TaskSend)
{
	// toggle LED
	LATBbits.LATB14 ^= 1;

	EE_UART2_Send('<');
	EE_UART2_Send('H');
	EE_UART2_Send('>');
}
