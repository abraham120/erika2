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

 /**
    @file   ee_board.h
    @brief  RX210 starter kit board header file.
    @author Gianluca Franchino
    @date   2012
  */

#ifndef __INCLUDE_RENESAS_RSKRX210_BOARD_H__
#define __INCLUDE_RENESAS_RSKRX210_BOARD_H__

#include "mcu/renesas_r5f5210x/inc/ee_mcu.h"
#include "cpu/rx200/inc/ee_utils.h"


/*
 * User Led
 */

#ifdef __USE_RSKRX120_USER_LED__

/** @brief Initialize board leds defined by mask */
__INLINE__  void EE_rskrx210_leds_init(EE_UINT8 mask)
{
	if (mask & 0x1)
		PORT1.PDR.BIT.B4 = 1;
	if (mask & 0x2)
		PORT1.PDR.BIT.B5 = 1;
	if (mask & 0x4)
		PORT1.PDR.BIT.B6 = 1;
	if (mask & 0x8)
		PORT1.PDR.BIT.B7 = 1;
}

/** @brief User leds on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_leds_on(void)
{
	PORT1.PODR.BIT.B4 = 0;
	PORT1.PODR.BIT.B5 = 0;
	PORT1.PODR.BIT.B6 = 0;
	PORT1.PODR.BIT.B7 = 0;	
}

/** @brief User leds off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_leds_off(void)
{
	PORT1.PODR.BIT.B4 = 1;
	PORT1.PODR.BIT.B5 = 1;
	PORT1.PODR.BIT.B6 = 1;
	PORT1.PODR.BIT.B7 = 1;	
}


/** @brief User leds toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_leds_toggle(void)
{
	PORT1.PODR.BIT.B4 = PORT1.PODR.BIT.B4 ^ 1;
	PORT1.PODR.BIT.B5 = PORT1.PODR.BIT.B5 ^ 1;
	PORT1.PODR.BIT.B6 = PORT1.PODR.BIT.B6 ^ 1;
	PORT1.PODR.BIT.B7 = PORT1.PODR.BIT.B7 ^ 1;
}

/** @brief User led0 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led0_on(void)
{
	PORT1.PODR.BIT.B4 = 0;
}

/** @brief User led0 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led0_off(void)
{
	PORT1.PODR.BIT.B4 = 1;
}

/** @brief User led0 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led0_toggle(void)
{
	PORT1.PODR.BIT.B4 =  PORT1.PODR.BIT.B4 ^ 1;
}

/** @brief User led1 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led1_on(void)
{
	PORT1.PODR.BIT.B5 = 0;
}

/** @brief User led1 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led1_off(void)
{
	PORT1.PODR.BIT.B5 = 1;
}

/** @brief User led1 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led1_toggle(void)
{
	PORT1.PODR.BIT.B5 =  PORT1.PODR.BIT.B5 ^ 1;
}

/** @brief User led2 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led2_on(void)
{
	PORT1.PODR.BIT.B6 = 0;
}

/** @brief User led2 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led2_off(void)
{
	PORT1.PODR.BIT.B6 = 1;
}


/** @brief User led2 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led2_toggle(void)
{
	PORT1.PODR.BIT.B6 =  PORT1.PODR.BIT.B6 ^ 1;
}

/** @brief User led3 on **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led3_on(void)
{
	PORT1.PODR.BIT.B7 = 0;
}

/** @brief User led3 off **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led3_off(void)
{
	PORT1.PODR.BIT.B7 = 1;
}

/** @brief User led3 toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_led3_toggle(void)
{
	PORT1.PODR.BIT.B7 =  PORT1.PODR.BIT.B7 ^ 1;
}

#endif /* __USE_RSKRX120_USER_LED__ */

#ifdef __USE_RSKRX120_BUTTONS__


/** @brief Buttons initialization **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_buttons_pins_init(EE_UINT8 mask)
{
	if (mask & 0x1)
		PORT3.PDR.BIT.B1 = 0;
	if (mask & 0x2)
		PORT3.PDR.BIT.B3 = 0;
	if (mask & 0x4)
		PORT3.PDR.BIT.B4 = 0;
}

/** @brief Initialize board buttons ISRs as defined by mask */	
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_buttons_IRQ_init(EE_UINT8 mask)
{
	if (mask & 0x1) {
		
		MPC.PWPR.BIT.B0WI = 0;
		MPC.PWPR.BIT.PFSWE = 1;
		/*Set IRQ1 enabled on Multi-function Pin Controller*/
		MPC.P31PFS.BIT.ISEL = 1;
		MPC.PWPR.BIT.PFSWE = 0;
		MPC.PWPR.BIT.B0WI = 1;
		/*Set IRQ1 interrupt priority to level 1 */
		ICU.IPR[IR_ICU_IRQ1].BIT.IPR = 0x1;
		/*Enable IRQ1 interrupt in ICU*/
		ICU.IER[IER_ICU_IRQ1].BIT.IEN_ICU_IRQ1 = 1;
	}
	if (mask & 0x2) {
		MPC.PWPR.BIT.B0WI = 0;
		MPC.PWPR.BIT.PFSWE = 1;
		/*Set IRQ1 enabled on Multi-function Pin Controller*/
		MPC.P33PFS.BIT.ISEL = 1;
		MPC.PWPR.BIT.PFSWE = 0;
		MPC.PWPR.BIT.B0WI = 1;
		/*Set IRQ3 interrupt priority to level 1 */
		ICU.IPR[IR_ICU_IRQ3].BIT.IPR = 0x1;
		/*Enable IRQ3 interrupt in ICU*/
		ICU.IER[IER_ICU_IRQ3].BIT.IEN_ICU_IRQ3 = 1;
	}
	if (mask & 0x4) {
		MPC.PWPR.BIT.B0WI = 0;
		MPC.PWPR.BIT.PFSWE = 1;	
		MPC.P34PFS.BIT.ISEL = 1;
		MPC.PWPR.BIT.PFSWE = 0;
		MPC.PWPR.BIT.B0WI = 1;		
		/*Set IRQ4 interrupt priority to level 1 */
		ICU.IPR[IR_ICU_IRQ4].BIT.IPR = 0x1;
		/*Enable IRQ interrupt in ICU*/
		ICU.IER[IER_ICU_IRQ4].BIT.IEN_ICU_IRQ4 = 1;
	}
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_b1_not_pressed(void)
{
	 return PORT3.PIDR.BIT.B1;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_b2_not_pressed(void)
{
	 return PORT3.PIDR.BIT.B3;
}


__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_b3_not_pressed(void)
{
	 return PORT3.PIDR.BIT.B4;
}

__INLINE__ void __ALWAYS_INLINE__ EE_b1_disable_IRQ(void)
{
	 	ICU.IER[IER_ICU_IRQ1].BIT.IEN_ICU_IRQ1 = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_b1_enable_IRQ(void)
{
	 	ICU.IER[IER_ICU_IRQ1].BIT.IEN_ICU_IRQ1 = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_b2_disable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ3].BIT.IEN_ICU_IRQ3 = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_b2_enable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ3].BIT.IEN_ICU_IRQ3 = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_b3_disable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ4].BIT.IEN_ICU_IRQ4 = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_b3_enable_IRQ(void)
{
	ICU.IER[IER_ICU_IRQ4].BIT.IEN_ICU_IRQ4 = 1;
}


#endif /* __USE_RSKRX120_BUTTONS__ */

/*
 * RSKRX210 Operating freq. setup
 */

#ifdef __USE_RSKRX210_OP_FREQ_SETUP__

/** @brief Operating Frequencies setup **/
__INLINE__ void __ALWAYS_INLINE__ EE_rskrx210_op_freq_setup(void) 
{
	volatile unsigned int i;

	/* Write protect off */
	SYSTEM.PRCR.WORD = 0xA503;				
	/* Main clock oscillator wait control register       */
	/* 65536 cycles -> wait at least 2 ms  (XTAL = 20MHz ) */
	SYSTEM.MOSCWTCR.BYTE = 0x0C;			

	/* PLL wait control register 		                  */
    /* 262144 cycles -> wait at least 2.1 ms  PLL = 80MHz */
	SYSTEM.PLLWTCR.BYTE = 0x0B;				
	
	/* PLL = XTAL / 2 = 10MHz		*/												
	/* PLL * 8 = 80MHz				*/
	SYSTEM.PLLCR.WORD = 0x0701;					
	/* XTAL ON */
	SYSTEM.MOSCCR.BYTE = 0x00;				
	/* PLL ON */										
	SYSTEM.PLLCR2.BYTE = 0x00;				
	/*Wait at least 2.1 ms*/
	for(i = 0; i<500; i++){	
	}

	
	/* PCKD = PCKC = PCKB = PCKA = BCKPLL/8 = 10MHz*/
	SYSTEM.SCKCR.BIT.PCKD 	= 3;
	SYSTEM.SCKCR.BIT.PCKC 	= 3;
	SYSTEM.SCKCR.BIT.PCKB 	= 3;
	SYSTEM.SCKCR.BIT.PCKA 	= 3;
	SYSTEM.SCKCR.BIT.BCK 	= 3;
	/* BUS CLK OUT Disabled */
	SYSTEM.SCKCR.BIT.PSTOP1 = 1;
	/*ICK = PLL/2 = 40 MHz*/
	SYSTEM.SCKCR.BIT.ICK 	= 1;
	/*FCK = PLL/4 = 20 MHz*/
	SYSTEM.SCKCR.BIT.FCK 	= 2;

	while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);
	SYSTEM.OPCCR.BIT.OLPCM = 0;
	while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);

	/*Source of system clock = PLL*/
	SYSTEM.SCKCR3.WORD = 0x0400;
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;
}

#endif /*__USE_RSKRX210_OP_FREQ_SETUP__*/

/*
 * User Led
 */

#ifdef __USE_RSKRX120_LCD__ 

#define EE_LCD_LINE1 0
#define EE_LCD_LINE2 16
#define EE_DATA_WR 1
#define EE_CTRL_WR 0
	

/* LCD minimal commands. For other commands see the datasheet*/
#define EE_LCD_CLEAR        0x01
#define EE_LCD_HOME_L1      0x80    
#define EE_LCD_HOME_L2      0xC0
#define EE_LCD_DISPLAY_ON	0x04
#define EE_LCD_TWO_LINE		0x08
#define EE_LCD_CURSOR_OFF	0x0C
#define EE_LCD_CURSOR_ON	0x0E
#define EE_LCD_CLEAR		0x01
#define EE_LCD_HOME_L1		0x80
#define EE_LCD_HOME_L2		0xC0


/*
* Write a nibble to the LCD. ch_type = 0 -> CTRL nibble, 
* ch_type = 1 -> DATA nibble
*/
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_nib_wr(EE_UINT8 ch_type, EE_UINT8 ch)
{
	
	if (ch_type == EE_DATA_WR) {
		PORTJ.PODR.BIT.B1 = 1;
	} else {
		PORTJ.PODR.BIT.B1 = 0;
	}
	
	/* tsu1 delay */
    EE_delay_us(1e6);
  	/* EN enable chip (HIGH) */
	PORTJ.PODR.BIT.B3 = 1;
	/* Output the data */
	PORTH.PODR.BYTE = (EE_UINT8)(ch);
	/* tw delay */	            
    EE_delay_us(1e6);
	/* Latch data by dropping E */					
	PORTJ.PODR.BIT.B3 = 0;
	
	/* th2 delay + tc delay*/				
    EE_delay_us(2e6);
}

/*
* This function write a character on LCD, or a send a control data to the LCD; 
* it depends on value_type: 0 (EE_CTRL_WR) -> CTRL, 1 (EE_DATA_WR) -> DATA 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_wr(EE_UINT8 ch_type, EE_UINT8 ch)
{
	EE_LCD_nib_wr(ch_type, (EE_UINT8)((ch & 0xF0) >> 4));
	EE_LCD_nib_wr(ch_type, (EE_UINT8)(ch & 0x0F));
}

__INLINE__ void __ALWAYS_INLINE__ EE_init_lcd_pins()
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
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_init(void)
{
	
	EE_init_lcd_pins();

	/* Power up delay */
    EE_delay_us(1e6);
	/* Display initialises in 8 bit mode*/ 
	EE_LCD_nib_wr(EE_CTRL_WR, 0x03);
	EE_delay_us(50e3);
	EE_LCD_nib_wr(EE_CTRL_WR, 0x03);
    EE_delay_us(50e3);
	EE_LCD_nib_wr(EE_CTRL_WR, 0x03);
	EE_delay_us(50e3);
	/* Function Set */
	EE_LCD_nib_wr(EE_CTRL_WR, 0x02);
    EE_delay_us(1e3);
	EE_LCD_nib_wr(EE_CTRL_WR, 0x02);
	EE_LCD_nib_wr(EE_CTRL_WR, (EE_LCD_DISPLAY_ON | EE_LCD_TWO_LINE ));
    EE_delay_us(1e3);
	/* Display ON/OFF control */
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_CURSOR_OFF);
    EE_delay_us(1e3);
	/* Display Clear */
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_CLEAR);
	EE_delay_us(25e3);
	/* Entry Mode Set */
	EE_LCD_wr(EE_CTRL_WR, 0x06);
    EE_delay_us(1e3);
	/* Home the cursor */
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_HOME_L1);
    EE_delay_us(20e3);
}

/*
*Clear the LCD
*/
__INLINE__ void __ALWAYS_INLINE__ EE_clear_LCD(void)
{
	EE_LCD_wr(EE_CTRL_WR, EE_LCD_CLEAR);
    EE_delay_us(20e3);
}

/*
* Display "string" starting from position.
* Note that: pos = 0 - means from first character of line 1, pos=16 
* means first character of line 2.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_disp(EE_UINT8 pos, 
												const EE_UINT8 * str)
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
        EE_delay_us(100e3);
		/* Set new_pos to pos */
		new_pos = pos;		
	}

	do {
		/* Write the data to the LCD */
		EE_LCD_wr(EE_DATA_WR, *str++);
        EE_delay_us(1e3);
		new_pos++;				
	} 
	while(*str);
}


#endif /*__USE_RSKRX120_LCD__*/

#endif /*__INCLUDE_RENESAS_RSKRX210_BOARD_H__ */
