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

/*
 * Author: 2005 Paolo Gai
 * CVS: $Id: ee_board.c,v 1.3 2007/03/16 15:20:19 nino Exp $
 */

#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"
#include "mcu/microchip_dspic/inc/ee_mcu.h"
#include "board/microchip_dspicdem11plus/inc/ee_board.h"

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

void (*EE_button_callback)(void);
EE_UINT8 EE_button_mask;

void EE_buttons_init( void(*isr_callback)(void), EE_UINT8 mask ) {
	/* set BUTTON pins as inputs */
	TRISAbits.TRISA12 = 1; 
	TRISAbits.TRISA13 = 1; 
	TRISAbits.TRISA14 = 1; 
	TRISAbits.TRISA15 = 1; 
	
	/* Enable Interrupt */
	if (isr_callback != NULL) {
		/* Clear Interrupt flags */
		IFS1bits.INT1IF = 0;
		IFS1bits.INT2IF = 0;
		IFS2bits.INT3IF = 0;
		IFS2bits.INT4IF = 0;
		
		/* Set Edge Polarity */
		INTCON2bits.INT1EP = 1;
		INTCON2bits.INT2EP = 1;
		INTCON2bits.INT3EP = 1;
		INTCON2bits.INT4EP = 1;
	
		if (mask & 0x01)
			IEC1bits.INT1IE = 1;	// S1/RA12
		if (mask & 0x02)
			IEC1bits.INT2IE = 1;	// S2/RA13
		if (mask & 0x04)
			IEC2bits.INT3IE = 1;	// S3/RA14
		if (mask & 0x08)
			IEC2bits.INT4IE = 1;	// S4/RA15
	}
	
	/* Save callback */
	EE_button_callback = isr_callback;	
} 

ISR2(_INT1Interrupt)
{
	// Execute callback function
	if (EE_button_callback != NULL) {
		EE_button_callback();
	}
		
	/* reset interrupt flag */
	IFS1bits.INT1IF = 0;           
}

ISR2(_INT2Interrupt)
{
	// Execute callback function
	if (EE_button_callback != NULL) {
		EE_button_callback();
	}
		
	/* reset interrupt flag */
	IFS1bits.INT2IF = 0;           
}

ISR2(_INT3Interrupt)
{
	// Execute callback function
	if (EE_button_callback != NULL) {
		EE_button_callback();
	}
		
	/* reset interrupt flag */
	IFS2bits.INT3IF = 0;           
}

ISR2(_INT4Interrupt)
{
	// Execute callback function
	if (EE_button_callback != NULL) {
		EE_button_callback();
	}
		
	/* reset interrupt flag */
	IFS2bits.INT4IF = 0;           
}
#endif


/* ************************************************************************* */
