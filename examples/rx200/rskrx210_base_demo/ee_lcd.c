/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * Functions to control the LCD used by the RSKRX210 Starterkit
 * Author: 2012  Gianluca Franchino gianluca@evidence.eu.com
 */
#include "ee.h"
#include "ee_lcd.h"

static void EE_LCD_nib_wr(EE_UINT8, EE_UINT8);
static void EE_init_lcd_pins(void);
/*
* Note that, ee_delay works only if EE_systick is used.
* Furthermore, we consider that the EE_systick period is 1ms
*/
#define ee_delay(a) do {\
		ee_cnt = isr_count;\
		while (isr_count  < ee_cnt + a);\
		} while(0)

extern volatile unsigned int isr_count;
volatile unsigned int ee_cnt;

void EE_init_lcd_pins()
{
    /* Configure the debug LCD data pins (DLCD7-DLCD4) as outputs */
	PORTH.PDR.BIT.B0 = 1;
	PORTH.PDR.BIT.B1 = 1;
	PORTH.PDR.BIT.B2 = 1;
	PORTH.PDR.BIT.B3 = 1;
	/* Set debug LCD data pin (DLCD7-DLCD4) outputs as low */
	PORTH.PODR.BIT.B0 = 0;
	PORTH.PODR.BIT.B1 = 0;
	PORTH.PODR.BIT.B2 = 0;
	PORTH.PODR.BIT.B3 = 0;

	/* Configure the debug LCD control pin (DLCDRS) and enable pin (DLCDE)
	   as output */
	PORTJ.PDR.BIT.B1 = 1;
	PORTJ.PDR.BIT.B3 = 1;

	/* Set the debug LCD control pin (DLCDRS) and enable pin (DLCDE) as output
	   low */
	PORTJ.PODR.BIT.B1 = 0;
	PORTJ.PODR.BIT.B3 = 0;
}

/*
* Initialize the LCD module.
*/
void EE_LCD_init(void)
{
	
	EE_init_lcd_pins();

	/* Power up delay */
    ee_delay(1000);
	/* Display initialises in 8 bit mode*/ 
	EE_LCD_nib_wr(EE_CTRL_WR, 0x03);
	ee_delay(50);
	EE_LCD_nib_wr(EE_CTRL_WR, 0x03);
    ee_delay(50);
	EE_LCD_nib_wr(EE_CTRL_WR, 0x03);
	ee_delay(50);
	/* Function Set */
	EE_LCD_nib_wr(EE_CTRL_WR, 0x02);
    ee_delay(1);
	EE_LCD_nib_wr(EE_CTRL_WR, 0x02);
	EE_LCD_nib_wr(EE_CTRL_WR, (EE_LCD_DISPLAY_ON | EE_LCD_TWO_LINE ));
    ee_delay(1);
	/* Display ON/OFF control */
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_CURSOR_OFF);
    ee_delay(1);
	/* Display Clear */
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_CLEAR);
	ee_delay(25);
	/* Entry Mode Set */
	EE_LCD_wr(EE_CTRL_WR, 0x06);
    ee_delay(1);
	/* Home the cursor */
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_HOME_L1);
    ee_delay(20);
}

/*
*Clear the LCD
*/
void EE_clear_LCD(void)
{
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_CLEAR);
    ee_delay(20);
}

/*
* Display "string" starting from position.
* Note that: pos = 0 - means from first character of line 1, pos=16 
* means first character of line 2.
*/
void EE_LCD_disp(EE_UINT8 pos, const EE_UINT8 * str)
{
	static EE_UINT8 new_pos = 0xFF;

	if( new_pos != pos) {
		if(pos < EE_LCD_LINE2) {
			/*Line 1 */
		  	EE_LCD_wr(EE_CTRL_WR, ((EE_UINT8)(EE_LCD_HOME_L1 + pos)));
		}
		else {
			/*Line 2 */
		  	EE_LCD_wr(EE_CTRL_WR, ((EE_UINT8)((EE_LCD_HOME_L2 + pos ) - EE_LCD_LINE2)));
		}

        /* Delay after sending a command to the LCD */
        ee_delay(100);
		/* Set new_pos to pos */
		new_pos = pos;		
	}

	do {
		/* Write the data to the LCD */
		EE_LCD_wr(EE_DATA_WR, *str++);
        ee_delay(1);
		new_pos++;				
	} 
	while(*str);
}


/*
* This function write a character on LCD, or a send a control data to the LCD; 
* it depends on value_type: 0 (EE_CTRL_WR) -> CTRL, 1 (EE_DATA_WR) -> DATA 
*/
void EE_LCD_wr(EE_UINT8 ch_type, EE_UINT8 ch)
{
	EE_LCD_nib_wr(ch_type, (EE_UINT8)((ch & 0xF0) >> 4));
	EE_LCD_nib_wr(ch_type, (EE_UINT8)(ch & 0x0F));
}


/*
* Write a nibble to the LCD. ch_type = 0 -> CTRL nibble, 
* ch_type = 1 -> DATA nibble
*/
static void EE_LCD_nib_wr(EE_UINT8 ch_type, EE_UINT8 ch)
{
	
	if (ch_type == EE_DATA_WR) {
		PORTJ.PODR.BIT.B1 = 1;
	} else {
		PORTJ.PODR.BIT.B1 = 0;
	}
	
	/* tsu1 delay */
    ee_delay(1);
  	/* EN enable chip (HIGH) */
	PORTJ.PODR.BIT.B3 = 1;
	/* Output the data */
	PORTH.PODR.BYTE = (EE_UINT8)(ch);
	/* tw delay */	            
    ee_delay(1);
	/* Latch data by dropping E */					
	PORTJ.PODR.BIT.B3 = 0;
	
	/* th2 delay + tc delay*/				
    ee_delay(2);
}

