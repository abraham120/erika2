/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
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

/** 
	@file lcd-protocol.h
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
/* 
 * Author: 2006 Mauro Marinoni
 * CVS: $Id: lcd-protocol.h,v 1.1 2007/05/25 16:03:51 pj Exp $
 */

#ifndef __INCLUDE_LCD_PROTOCOL_H__
#define __INCLUDE_LCD_PROTOCOL_H__

#include "mcu/microchip_dspic/inc/ee_mcu.h"

/* /\************************************************************************* */
/*  LCD */
/*  *************************************************************************\/ */

/* 
   For Flex board, here are the data and control signal definitions
   Reset	-> RD4
   RS	-> RD5
   RW	-> RD6
   E	-> RD7
   DATA	-> RE0 - RE7   
*/

/* /\* Control signal data pins *\/ */
#define  EE_LCD_RESET	LATDbits.LATD4
#define  EE_LCD_RS	LATDbits.LATD5
#define  EE_LCD_RW	LATDbits.LATD6
#define  EE_LCD_E	LATDbits.LATD7

/* /\* Control signal pin direction *\/ */
#define  EE_LCD_RESET_TRIS	TRISDbits.TRISD4
#define  EE_LCD_RS_TRIS		TRISDbits.TRISD5
#define  EE_LCD_RW_TRIS		TRISDbits.TRISD6 
#define  EE_LCD_E_TRIS		TRISDbits.TRISD7

/* /\* Data signals and pin direction *\/ */
#define  EE_LCD_DATA      LATE           // Port for LCD data
#define  EE_LCD_DATAPORT  PORTE
#define  EE_LCD_TRISDATA  TRISE          // I/O setup for data Port


/* /\* Do an active wait of predefined duration.  *\/ */
void Delay_100us(int n)
{
	unsigned int i,j;

	for (j=0; j<n; j++) {
		for (i=0; i<1000; i++) {
			;
		}
	}
}

/* /\* Send an impulse on the enable line.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_pulse_enable( void )
{
	EE_LCD_E = 1;
	Nop();
	Nop();
	Nop();
	EE_LCD_E = 0;
}

/* /\* Send a command to the lcd.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_command( EE_UINT8 cmd )
{
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= cmd;
	EE_LCD_RW = 0;
	EE_LCD_RS = 0;
	EE_lcd_pulse_enable();
	Delay_100us(2);
}

/* /\* Initialize the display.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_init(void)
{
	// 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
	// not always required and is based on system Vdd rise rate
	Delay_100us(1000);
			
	/* Initial values */
	EE_LCD_DATA &= 0xFF00;	
	EE_LCD_RW   = 0;
	EE_LCD_RS   = 0;
	EE_LCD_E    = 0;

	/* Set pins direction */
	EE_LCD_TRISDATA &= 0xFF00;
 	EE_LCD_RW_TRIS  = 0;
	EE_LCD_RS_TRIS  = 0;
	EE_LCD_E_TRIS   = 0;

	/* Init - Step 1 */
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	Delay_100us(50);
      
	/* Init - Step 2 */
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	Delay_100us(2);

	/* Init - Step 2 */
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	Delay_100us(2);

	EE_lcd_command( 0x38 );	// Function set
	EE_lcd_command( 0x0C );	// Display on/off control, cursor blink off (0x0C)
	EE_lcd_command( 0x06 );	// Entry mode set (0x06)
}

/* /\* Send a data.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_putc( EE_INT8 data )
{
	EE_LCD_RW = 0;
	EE_LCD_RS = 1;
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= data;
	EE_lcd_pulse_enable();
	EE_LCD_RS = 0;
	Delay_100us(2);
}

/* /\* Send a data.  *\/ */
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_lcd_getc( void )
{
	EE_INT8 buf;
	
	EE_LCD_TRISDATA |= 0x00FF;
	EE_LCD_RW = 1;
	EE_LCD_RS = 1;
	EE_lcd_pulse_enable();
	Delay_100us(2);

	buf = EE_LCD_DATAPORT & 0x00FF;
	EE_LCD_RS = 0;
	EE_LCD_TRISDATA &= 0xFF00;
	return ( buf );
}

/* /\* Send a string to the display.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_puts( EE_INT8 *buf )
{
	EE_UINT8 i = 0;
	
	while (buf[i] != '\0')
		EE_lcd_putc(buf[i++]);
}

/* /\* Check if the display is busy.  *\/ */
__INLINE__ unsigned char __ALWAYS_INLINE__ EE_lcd_busy( void )
{
	EE_INT8 buf;
	
	EE_LCD_TRISDATA |= 0x00FF;
	EE_LCD_RW = 0;
	EE_LCD_RS = 1;
	EE_lcd_pulse_enable();
	Delay_100us(2);

	buf = EE_LCD_DATAPORT & 0x00FF;
	EE_LCD_RS = 0;
	EE_LCD_TRISDATA &= 0xFF00;
	return ( (buf & 0x80) ? 1 : 0 );
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_clear (void)		{ EE_lcd_command( 0x01 ); }

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_home  (void)		{ EE_lcd_command( 0x02 ); }
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_line2 (void)		{ EE_lcd_command( 0xC0 ); }

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_curs_right (void)	{ EE_lcd_command( 0x14 ); }
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_curs_left (void)	{ EE_lcd_command( 0x10 ); }
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_shift (void)		{ EE_lcd_command( 0x1C ); }

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_goto (EE_UINT8 posx, EE_UINT8 posy)
{
	EE_UINT8 tmp_pos;
	
	tmp_pos  = posy ? 0xC0 : 0x80;
	tmp_pos += 0x0F & posx;
	EE_lcd_command( tmp_pos ); 
}

/* ************************************************************************* */

#endif
