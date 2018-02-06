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

#include "./define.h"
#include "./variable.h"

//-----------------------------------------------------------------------------
// Utility functions on ring buffers
//-----------------------------------------------------------------------------
unsigned char IsBufferEmpty(RingBuf * pBuf)
{
	unsigned char	result;

	if (pBuf->count == 0)
		result = DPS_TRUE;
	else
		result = DPS_FALSE;

	return result;
}

unsigned char IsBufferFull(RingBuf * pBuf)
{
	unsigned char	result;

	if (pBuf->count == pBuf->size)
		result = DPS_TRUE;
	else
		result = DPS_FALSE;

	return result;
}

int	CountBuffer(RingBuf * pBuf)
{
	return pBuf->count;
}

void PushBuffer(RingBuf * pBuf, unsigned char byte)
{
	pBuf->buffer[pBuf->head] = byte;
	pBuf->head++;
	if (pBuf->head == pBuf->size)
		pBuf->head = 0;
	pBuf->count++;
}

unsigned char PopBuffer(RingBuf * pBuf)
{
	unsigned char	data;
	//assert(pBuf->count > 0);
	data = pBuf->buffer[pBuf->tail];
	pBuf->tail++;
	if (pBuf->tail == pBuf->size)
		pBuf->tail = 0;
	pBuf->count--;

	return data;
}

unsigned char TopBuffer(RingBuf * pBuf)
{
	unsigned char	data;
	//assert(pBuf->count > 0);
	data = pBuf->buffer[pBuf->tail];

	return data;
}

//-----------------------------------------------------------------------------
// Utility functions on LED
//	Only one YELLOW LED is available for application.
//	3 GREEN LEDs are dedicated to Power status.
//-----------------------------------------------------------------------------
unsigned char	statusYellowLED = LED_OFF;
void	TurnOnYellowLED()
{
	statusYellowLED = LED_OFF;
	LATBbits.LATB14 = statusYellowLED;
}

void	TurnOffYellowLED()
{
	statusYellowLED = LED_ON;
	LATBbits.LATB14 = statusYellowLED;
}

void	ToggleYellowLED()
{
	statusYellowLED ^= 0x01;		//toggle status
	LATBbits.LATB14 = statusYellowLED;
}
