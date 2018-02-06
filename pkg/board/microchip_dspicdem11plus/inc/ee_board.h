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
 * Author: 2006 Mauro Marinoni
 * CVS: $Id: ee_board.h,v 1.5 2007/03/19 15:01:28 nino Exp $
 */

#ifndef __INCLUDE_MICROCHIP_DSPICDEM11PLUS_BOARD_H__
#define __INCLUDE_MICROCHIP_DSPICDEM11PLUS_BOARD_H__

#include "mcu/microchip_dspic/inc/ee_mcu.h"

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

extern void (*EE_button_callback)(void);
extern EE_UINT8 EE_button_mask;

void EE_buttons_init( void(*isr_callback)(void), EE_UINT8 mask );

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S1( void ) {
	if (PORTAbits.RA12)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S2( void ) {
	if (PORTAbits.RA13)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S3( void ) {
	if (PORTAbits.RA14)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S4( void ) {
	if (PORTAbits.RA15)
		return 0;
	else
		return 1;
}

#endif


/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {
	/* set LEDs (D1-D4/RD0-RD3) drive state low */
	LATD |= 0x000F; 
	/* set LED pins (D1-D4/RD0-RD3) as outputs */
	TRISD &= 0xFFF0; 
}
__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)   { LATD |= 0x000F; }
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)  { LATD &= 0xFFF0; }

__INLINE__ void __ALWAYS_INLINE__ EE_leds( EE_UINT8 data )  {
	LATDbits.LATD0 = (data & 0x01) ? 0 : 1;
	LATDbits.LATD1 = (data & 0x02) ? 0 : 1;
	LATDbits.LATD2 = (data & 0x04) ? 0 : 1;
	LATDbits.LATD3 = (data & 0x08) ? 0 : 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_on(void)   { LATDbits.LATD0 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_off(void)  { LATDbits.LATD0 = 1; }

__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)   { LATDbits.LATD0 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void)  { LATDbits.LATD0 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void)   { LATDbits.LATD1 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void)  { LATDbits.LATD1 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void)   { LATDbits.LATD2 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void)  { LATDbits.LATD2 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void)   { LATDbits.LATD3 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void)  { LATDbits.LATD3 = 1; }

#endif


/* /\************************************************************************* */
/*  SPI init */
/*  *************************************************************************\/ */

#if defined(__USE_ANALOG__) || defined(__USE_LCD__)

__INLINE__ void __ALWAYS_INLINE__ EE_spi2_init( void ) {
	
	/* Reset SPI2 port status register */
	SPI2STAT = 0;
	
	/* Master Clk = Fcy/8, Data on rising edge */
	SPI2CON = 0x003A;
	
	/* turn on SPI2 module */
	SPI2STATbits.SPIEN = 1;          	
}

/* Send a character using the SPI port */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_spi2_send( EE_UINT8 data )
{
	while(SPI2STATbits.SPITBF);
	SPI2BUF = data;
	while(!SPI2STATbits.SPIRBF);
	
	return SPI2BUF;
}

#endif


/* /\************************************************************************* */
/*  LCD */
/*  *************************************************************************\/ */

#ifdef __USE_LCD__

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_init(void) {

	EE_UINT16 i;
	for (i=0;i>10000;i++);
	
	/* Configure CS pins */
	TRISGbits.TRISG9 = 0;
	LATGbits.LATG9   = 1;

	/* Config SPI port */
	EE_spi2_init();
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_lcd_command( EE_UINT8 cmd )
{
	EE_UINT8 res;
	
	LATGbits.LATG9   = 0;
	res = EE_spi2_send( cmd );
	LATGbits.LATG9   = 1;
	
	return res;
}

/* General Commands */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_Reset( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x80 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_Home( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x81 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_HomeClear( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x82 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_Scroll( EE_UINT8 lines )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xA3 );
	EE_spi2_send( lines & 0x1F );
	LATGbits.LATG9   = 1;
}

/* Character Commands */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrPos( EE_UINT8 col, EE_UINT8 row )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xC5 );
	EE_spi2_send( col & 0x1F );
	EE_spi2_send( row & 0x03 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrPosInc( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x8E );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtChr( EE_UINT8 chr, EE_UINT8 col, EE_UINT8 row )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xE6 );
	EE_spi2_send( chr & 0x7F );
	EE_spi2_send( col & 0x1F );
	EE_spi2_send( row & 0x03 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtChrInc( EE_UINT8 chr, EE_UINT8 col, EE_UINT8 row )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xE7 );
	EE_spi2_send( chr & 0x7F );
	EE_spi2_send( col & 0x1F );
	EE_spi2_send( row & 0x03 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtChrNext( EE_UINT8 chr )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xA8 );
	EE_spi2_send( chr & 0x7F );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrClearRow( EE_UINT8 row )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xA9 );
	EE_spi2_send( row & 0x03 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrClearEOL( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x8A );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrCursorOff( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x8B );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrCursorOn( void )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0x8C );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ChrCursorBlink( EE_UINT8 tick )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xAD );
	EE_spi2_send( tick & 0x07 );
	LATGbits.LATG9   = 1;
}

/* Pixel Commands */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_PixPos( EE_UINT8 posx, EE_UINT8 posy )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xD7 );
	EE_spi2_send( posx & 0x7F );
	EE_spi2_send( posy & 0x1F );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_PixOn( EE_UINT8 posx, EE_UINT8 posy )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xD8 );
	EE_spi2_send( posx & 0x7F );
	EE_spi2_send( posy & 0x1F );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_PixOff( EE_UINT8 posx, EE_UINT8 posy )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xD9 );
	EE_spi2_send( posx & 0x7F );
	EE_spi2_send( posy & 0x1F );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_PixLine( EE_UINT8 posx, EE_UINT8 posy )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xDA );
	EE_spi2_send( posx & 0x7F );
	EE_spi2_send( posy & 0x1F );
	LATGbits.LATG9   = 1;
}

/* Column Commands */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_ColPos( EE_UINT8 col, EE_UINT8 row )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xDB );
	EE_spi2_send( col & 0x7F );
	EE_spi2_send( row & 0x03 );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtColNext( EE_UINT8 data )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xBC );
	EE_spi2_send( data );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtColNextOR( EE_UINT8 data )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xBD );
	EE_spi2_send( data );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtColNextAND( EE_UINT8 data )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xBE );
	EE_spi2_send( data );
	LATGbits.LATG9   = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_lcd_WrtColNextXOR( EE_UINT8 data )
{
	LATGbits.LATG9   = 0;
	EE_spi2_send( 0xBF );
	EE_spi2_send( data );
	LATGbits.LATG9   = 1;
}

#define EE_lcd_putc	EE_lcd_WrtChrNext
#define EE_lcd_home	EE_lcd_Home
#define EE_lcd_goto	EE_lcd_ChrPos
#define EE_lcd_clear	EE_lcd_HomeClear

#endif



/* ************************************************************************* */

#endif
