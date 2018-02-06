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


#ifndef __INCLUDE_EE_FLEX_DEMOBOARD_H__
#define __INCLUDE_EE_FLEX_DEMOBOARD_H__

#ifdef __USE_DEMOBOARD__

/* /\************************************************************************* */
/*  Includes needed by PicDemZ wirelessmodule (GF) */
/*  *************************************************************************\/ */

#if defined (__USE_PICDEMZ_WITH_INT4__) || (__USE_PICDEMZ_WITH_CN20INT__)

#include "radio_spi.h"

#endif


/* /\************************************************************************* */
/*  LEDs */
/*  *************************************************************************\/ */

#ifdef __USE_LEDS__

#define EE_demoboard_leds_init() EE_daughter_leds_init()

__INLINE__ void __ALWAYS_INLINE__ EE_daughter_leds_init(void) {
	/* set LEDs drive state low */
	LATF  &= 0xFFF0;
	LATD  &= 0xF0FF;

	/* set LEDs pin as output */
	TRISF &= 0xFFF0;
	TRISD &= 0xF0FF;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds( EE_UINT8 data ) {
	LATF &= 0xFFF0;
	LATD &= 0xF0FF;

	LATF |= (data & 0x0F);
	LATD |= (data & 0xF0) << 4;
}


__INLINE__ void __ALWAYS_INLINE__ EE_led_0_init(void)   { LATFbits.LATF0  = 0; TRISFbits.TRISF0  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_init(void)   { LATFbits.LATF1  = 0; TRISFbits.TRISF1  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_init(void)   { LATFbits.LATF2  = 0; TRISFbits.TRISF2  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_init(void)   { LATFbits.LATF3  = 0; TRISFbits.TRISF3  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_init(void)   { LATDbits.LATD8  = 0; TRISDbits.TRISD8  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_init(void)   { LATDbits.LATD9  = 0; TRISDbits.TRISD9  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_init(void)   { LATDbits.LATD10  = 0; TRISDbits.TRISD10  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_init(void)   { LATDbits.LATD11  = 0; TRISDbits.TRISD11  = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_led_0_on(void)   { LATFbits.LATF0  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_off(void)  { LATFbits.LATF0  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)   { LATFbits.LATF1  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void)  { LATFbits.LATF1  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void)   { LATFbits.LATF2  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void)  { LATFbits.LATF2  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void)   { LATFbits.LATF3  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void)  { LATFbits.LATF3  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void)   { LATDbits.LATD8  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void)  { LATDbits.LATD8  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_on(void)   { LATDbits.LATD9  = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_off(void)  { LATDbits.LATD9  = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_on(void)   { LATDbits.LATD10 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_off(void)  { LATDbits.LATD10 = 0; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_on(void)   { LATDbits.LATD11 = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_off(void)  { LATDbits.LATD11 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)   { LATD  |= 0x0F00; LATF  |= 0x000F; }
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)  { LATD  &= 0xF0FF; LATF  &= 0xFFF0; }

#define EE_LED_0 1
#define EE_LED_1 2
#define EE_LED_2 3
#define EE_LED_3 4
#define EE_LED_4 5
#define EE_LED_5 6
#define EE_LED_6 7
#define EE_LED_7 8

__INLINE__ void __ALWAYS_INLINE__ EE_led_init(int led_id) 
{
    switch(led_id){
	case EE_SYS_LED:
	  EE_led_sys_init();
	  break;
	case EE_LED_0:
	  EE_led_0_init();
	  break;
	case EE_LED_1:
	  EE_led_1_init();
	  break;
	case EE_LED_2:
	  EE_led_2_init();
	  break;
	case EE_LED_3:
	  EE_led_3_init();
	  break;
	case EE_LED_4:
	  EE_led_4_init();
	  break;
	case EE_LED_5:
	  EE_led_5_init();
	  break;
	case EE_LED_6:
	  EE_led_6_init();
	  break;
	case EE_LED_7:
	  EE_led_7_init();
	  break;
    }
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_write(int led_id, EE_INT8 value) 
{
    switch(led_id){
	case EE_SYS_LED:
	  if(value)
	    EE_led_sys_on();
	  else
	    EE_led_sys_off();
	  break;
	case EE_LED_0:
	  if(value)
	    EE_led_0_on();
	  else
	    EE_led_0_off();
	  break;
	case EE_LED_1:
	  if(value)
	    EE_led_1_on();
	  else
	    EE_led_1_off();
	  break;
	case EE_LED_2:
	  if(value)
	    EE_led_2_on();
	  else
	    EE_led_2_off();
	  break;
	case EE_LED_3:
	  if(value)
	    EE_led_3_on();
	  else
	    EE_led_3_off();
	  break;
	case EE_LED_4:
	  if(value)
	    EE_led_4_on();
	  else
	    EE_led_4_off();
	  break;
	case EE_LED_5:
	  if(value)
	    EE_led_5_on();
	  else
	    EE_led_5_off();
	  break;
	case EE_LED_6:
	  if(value)
	    EE_led_6_on();
	  else
	    EE_led_6_off();
	  break;
	case EE_LED_7:
	  if(value)
	    EE_led_7_on();
	  else
	    EE_led_7_off();
	  break;

    }
}


#endif

/* /\************************************************************************* */
/*  Buttons */
/*  *************************************************************************\/ */

#ifdef __USE_BUTTONS__

extern void (*EE_button_callback)(void);

union  cn_st{
	EE_UINT8 status;
	struct a_bits
	{
		EE_UINT8 s1: 1;
		EE_UINT8 s2: 1;
		EE_UINT8 s3: 1;
		EE_UINT8 s4: 1;
	}bits;
};

extern EE_UINT8 EE_button_mask;
extern union cn_st cn_st_old;

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init( void(*isr_callback)(void), EE_UINT8 mask ) {
	/* set BUTTON pins as inputs */
	TRISDbits.TRISD4  = 1;
	TRISDbits.TRISD5  = 1;
	TRISDbits.TRISD6  = 1;
	TRISDbits.TRISD15 = 1;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		if (mask & 0x01) {
			CNEN1bits.CN13IE = 1;	// S1/RD4
			//cn_st_old.bits.s1 = PORTDbits.RD4;
		}
		if (mask & 0x02) {
			CNEN1bits.CN14IE = 1;	// S2/RD5
			//cn_st_old.bits.s2 = PORTDbits.RD5;
		}
		if (mask & 0x04) {
			CNEN1bits.CN15IE = 1;	// S3/RD6
			//cn_st_old.bits.s3 = PORTDbits.RD6;
		}
		if (mask & 0x08) {
			CNEN2bits.CN21IE = 1;	// S4/RD15
			//cn_st_old.bits.s4 = PORTDbits.RD15;
		}
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE = 1;
	}

	/* Save callback */
	EE_button_callback = isr_callback;
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S1( void ) {
	if (PORTDbits.RD4)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S2( void ) {
	if (PORTDbits.RD5)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S3( void ) {
	if (PORTDbits.RD6)
		return 0;
	else
		return 1;
}
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_button_get_S4( void ) {
	if (PORTDbits.RD15)
		return 0;
	else
		return 1;
}

/******************************************************************************/
/*                  Common APIs for Model Based Suite                         */
/******************************************************************************/

#define EE_BUTTON_S1 0
#define EE_BUTTON_S2 1
#define EE_BUTTON_S3 2
#define EE_BUTTON_S4 3

__INLINE__ void __ALWAYS_INLINE__ EE_button_S1_init(void(*isr_callback)(void))
{

	/* set BUTTON pins as inputs */
	TRISDbits.TRISD4  = 1;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		CNEN1bits.CN13IE = 1;	// S1/RD4
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE = 1;
		/* Save callback */
		EE_button_callback = isr_callback;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_button_S2_init(void(*isr_callback)(void))
{

	/* set BUTTON pins as inputs */
	TRISDbits.TRISD5  = 1;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		CNEN1bits.CN14IE = 1;	// S2/RD5
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE = 1;
		/* Save callback */
		EE_button_callback = isr_callback;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_button_S3_init(void(*isr_callback)(void))
{

	/* set BUTTON pins as inputs */
	TRISDbits.TRISD6  = 1;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		CNEN1bits.CN15IE = 1;	// S3/RD6
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE = 1;
		/* Save callback */
		EE_button_callback = isr_callback;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_button_S4_init(void(*isr_callback)(void))
{

	/* set BUTTON pins as inputs */
	TRISDbits.TRISD15  = 1;

	/* Enable Interrupt */
	if (isr_callback != NULL) {
		CNEN2bits.CN21IE = 1;	// S4/RD15
		IFS1bits.CNIF = 0;
		IEC1bits.CNIE = 1;
		/* Save callback */
		EE_button_callback = isr_callback;
	}
}


__INLINE__ void __ALWAYS_INLINE__ EE_button_init( int button_id, void(*isr_callback)(void) )
{
    switch(button_id){
	case EE_BUTTON_S1:
	  EE_button_S1_init(isr_callback);
	  break;
	case EE_BUTTON_S2:
	  EE_button_S2_init(isr_callback);
	  break;
	case EE_BUTTON_S3:
	  EE_button_S3_init(isr_callback);
	  break;
	case EE_BUTTON_S4:
	  EE_button_S4_init(isr_callback);
	  break;
    }
}

__INLINE__ void __ALWAYS_INLINE__ EE_button_read( int button_id, EE_INT8* value)
{
    switch(button_id){
	case EE_BUTTON_S1:
	  *value = EE_button_get_S1();
	  break;
	case EE_BUTTON_S2:
	  *value = EE_button_get_S2();
	  break;
	case EE_BUTTON_S3:
	  *value = EE_button_get_S3();
	  break;
	case EE_BUTTON_S4:
	  *value = EE_button_get_S4();
	  break;
    }
}


/* TODO:
   1- Write APIs doc
   2- Do we need pre-condition check on the orther of calls? i.e. the init MUST
      be done before any call to control and read.
   3- Do we want to keep this "safe" version of the API that checking all 
      the function params? We can have a "faster" version with no check. We can
      choose at compilation time with defines.
*/
#if 0
enum {
	EE_BUTTON_MODE = 0,
	EE_BUTTON_ATTRIBUTES
};

enum {
	EE_BUTTON_RAW = 0,
	EE_BUTTON_LATCHED,
	EE_BUTTON_DEBOUNCED,
	EE_BUTTON_MODE_VALUES
};

enum {
	EE_BUTTON_ERR_UNIMPLEMENTED = 1,
	EE_BUTTON_ERR_BAD_ID,
};

__INLINE__ EE_INT8  EE_button_init(EE_UINT8 id, void(*callback)(void)) 
{
	/* TODO: provide logic for callback registration for each button */
	if (id > 4)
		return -EE_BUTTON_ERR_BAD_ID;
	if (callback != NULL)
		return -EE_BUTTON_ERR_UNIMPLEMENTED;
	EE_buttons_init(NULL, 0);
	return 1;
}

__INLINE__ EE_INT8 EE_button_control(EE_UINT8 id, EE_UINT8 attribute, 
				     EE_UINT8 value) 
{
	/* TODO: provide parsing of attributes */
	if (id > 4)
		return -EE_BUTTON_ERR_BAD_ID;
	switch (attribute) {
	case EE_BUTTON_MODE :
		if (value != EE_BUTTON_RAW)
			return -EE_BUTTON_ERR_UNIMPLEMENTED;
		break;
	default:
		return -EE_BUTTON_ERR_UNIMPLEMENTED;
	}
	return 1;
}

__INLINE__ EE_INT8 EE_button_read(EE_UINT8 id, EE_UINT8 *value) 
{
	switch (id) {
	case 0 :
		*value = EE_button_get_S1();
		break;
	case 1 :
		*value = EE_button_get_S2();
		break;
	case 2 :
		*value = EE_button_get_S3();
		break;
	case 3 :
		*value = EE_button_get_S4();
		break;
	default :
		return -EE_BUTTON_ERR_BAD_ID;
	}
	return 1;
}

enum {
	EE_LED_ERR_UNIMPLEMENTED = 1,
	EE_LED_ERR_BAD_ID,
	EE_LED_ERR_BAD_VALUE,
};

__INLINE__ EE_INT8  EE_led_init(EE_UINT8 id) 
{
	if (id > 4)
	switch (id) {
	case 0 :
		TRISFbits.TRISF0 = 0;
		break;
	case 1 :
		TRISFbits.TRISF1 = 0;
		break;
	case 2 :
		TRISFbits.TRISF2 = 0;
		break;
	case 3 :
		TRISFbits.TRISF3 = 0;
		break;
	case 4 :
		TRISDbits.TRISD8 = 0;
		break;
	case 5 :
		TRISDbits.TRISD9 = 0;
		break;
	case 6 :
		TRISDbits.TRISD10 = 0;
		break;
	case 7 :
		TRISDbits.TRISD11 = 0;
		break;
	default :
		return -EE_LED_ERR_BAD_ID;
	}
	return 1;
}

__INLINE__ EE_INT8  EE_led_write(EE_UINT8 id, EE_UINT8 value) 
{
	if (value > 1)
		return -EE_LED_ERR_BAD_VALUE;
	switch (id) {
	case 0 :
		LATFbits.LATF0 = value;
		break;
	case 1 :
		LATFbits.LATF1 = value;
		break;
	case 2 :
		LATFbits.LATF2 = value;
		break;
	case 3 :
		LATFbits.LATF3 = value;
		break;
	case 4 :
		LATDbits.LATD8 = value;
		break;
	case 5 :
		LATDbits.LATD9 = value;
		break;
	case 6 :
		LATDbits.LATD10 = value;
		break;
	case 7 :
		LATDbits.LATD11 = value;
		break;
	default :
		return -EE_LED_ERR_BAD_ID;
	}
	return 1;
}
#endif
#endif

//Start GF
/* /\************************************************************************* */
/*  PICDEM Z RF*/
/*  *************************************************************************\/ */

#if defined (__USE_PICDEMZ_WITH_INT4__) || (__USE_PICDEMZ_WITH_CN20INT__)

extern void (*EE_picdemz_callback)(void);

__INLINE__ void __ALWAYS_INLINE__ EE_picdemz_init( void(*isr_callback)(void)) {


	/* set the pins that control the radio module */
	TRISGbits.TRISG0 = 0; //PHY_RESETn_TRIS = 0;
	LATGbits.LATG0 = 0; //PHY_RESETn = 0; Reset the radio
	TRISGbits.TRISG9 = 0; // PHY_CS_TRIS = 0;
	LATGbits.LATG9 = 1; //PHY_CS = 1;
	TRISGbits.TRISG12 = 0; //PHY_WAKE_TRIS = 0;
	LATGbits.LATG12 = 1; //PHY_WAKE = 1;

	/* Initialize the spi peripheral */
	dsPIC33F_radio_spi_init(1); /* Initialize SPI2 */

#ifdef __USE_PICDEMZ_WITH_INT4__
		/* initialize INT4 interrupt */
	IFS3bits.INT4IF = 0; //RFIF = 0;
	IEC3bits.INT4IE = 1; //RFIE = 1;
#else
	/* initialize CN20 interrupt */
	CNEN2bits.CN20IE =1; //RFIEC20 = 1; INT on CN20
	IFS1bits.CNIF = 0; //RFIF = 0;
	IEC1bits.CNIE = 1; //RFIE = 1;
	TRISDbits.TRISD14 = 1; // set CN20 pin as input
#endif
	/* link the callback */
	EE_picdemz_callback = isr_callback;

}

#endif
//End GF

/* /\************************************************************************* */
/*  LCD */
/*  *************************************************************************\/ */

#ifdef __USE_LCD__

#ifndef FCY
#define FCY  40000000
#endif
#include <libpic30.h> /* to use: __delay_us and __delay_ms */

/*
   For Explorer 16 board, here are the data and control signal definitions
   RS -> RB10
   E   -> RB9
   RW -> N.C.
   DATA -> RA0 - RA7
*/

/* /\* Control signal data pins *\/ */
#define  EE_LCD_RS		LATBbits.LATB10	// LCD RS signal
#define  EE_LCD_E		LATBbits.LATB9	// LCD Enable signal
// fra
#define  EE_LCD_VLCD		LATBbits.LATB8	// LCD Voltage control
#define  EE_LCD_BRIGHTNESS	LATBbits.LATB11	// LCD Brightness control

/* /\* Control signal pin direction *\/ */
#define  EE_LCD_RS_TRIS		TRISBbits.TRISB10
#define  EE_LCD_E_TRIS		TRISBbits.TRISB9
// fra
#define  EE_LCD_VLCD_TRIS	TRISBbits.TRISB8
#define  EE_LCD_BRIGHTNESS_TRIS	TRISBbits.TRISB11

/* /\* Data signals and pin direction *\/ */
#define  EE_LCD_DATA		LATA           // Port for LCD data
#define  EE_LCD_DATAPORT	PORTA
#define  EE_LCD_TRISDATA	TRISA          // I/O setup for data Port

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
	EE_LCD_RS = 0;  // fra
	EE_lcd_pulse_enable();
	__delay_us(500);
}

/* /\* Switch on or off the back illumination  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_brightness( EE_UINT8 btns_status )
{
	EE_LCD_BRIGHTNESS = btns_status & 1;
}

/* /\* Switch on or off the display  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_switch( EE_UINT8 lcd_status )
{
	EE_LCD_VLCD = lcd_status & 1;
}

/* /\* Initialize the display.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_init(void) {
	// 15mS delay after Vdd reaches nnVdc before proceeding with LCD initialization
	// not alwEE_LCD_VLCDays required and is based on system Vdd rise rate
	// Todo!!!
	EE_LCD_VLCD_TRIS	= 0;
	EE_LCD_BRIGHTNESS_TRIS	= 0;
	EE_LCD_VLCD       = 1;
	EE_LCD_BRIGHTNESS = 1;

	/* Use pin as digital IO */
 	AD1PCFGLbits.PCFG9  = 0;
 	AD1PCFGLbits.PCFG10 = 0;

	/* Initial values */
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_RS   = 0;
	EE_LCD_E    = 0;

	/* Set pins direction */
	EE_LCD_TRISDATA &= 0xFF00;
	EE_LCD_RS_TRIS  = 0;
	EE_LCD_E_TRIS   = 0;
	__delay_ms(50);

	// Init - Step 1
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	__delay_us(500);

	// Init - Step 2
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	__delay_us(500);

	// Init - Step 3
	EE_LCD_DATA &= 0xFF00;
	EE_LCD_DATA |= 0x0038;
	EE_lcd_pulse_enable();
	__delay_us(500);

	EE_lcd_command( 0x38 );	// Function set
	EE_lcd_command( 0x0C );	// Display on/off control, cursor blink off (0x0C)
	EE_lcd_command( 0x06 );	// Entry mode set (0x06)
}

/* /\* Send a data.  *\/ */
void EE_lcd_putc( unsigned char data );

/* /\* Send a string to the display.  *\/ */
__INLINE__ void __ALWAYS_INLINE__ EE_lcd_puts( char *buf )
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
	EE_LCD_RS = 1;
	EE_lcd_pulse_enable();
	//__delay_us(200);
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

#endif


/* /\************************************************************************* */
/*  Analog inputs */
/*  *************************************************************************\/ */

#if defined(__USE_ANALOG_SENSORS__) || defined(__USE_TRIMMER__) || defined(__USE_ACCELEROMETER__) || defined(__USE_ADC__)

#define AVDD 3.3
#define VREF 3.3

extern EE_UINT8 ee_adc_init_flag;

__INLINE__ void __ALWAYS_INLINE__ EE_analog_init( void )
{
	/* Check if the ADC is initialized */
	if (ee_adc_init_flag != 0) return;

	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* set ALL configuration bits as ADC input */
 	AD1PCFGLbits.PCFG12 = 0;         // Temp Sensor -> AN12/RB12
 	AD1PCFGLbits.PCFG13 = 0;         // Light Sensor -> AN13/RB13
 	AD1PCFGLbits.PCFG15 = 0;         // Trimmer        -> AN15/RB15
 	AD1PCFGHbits.PCFG16 = 0;         // Accelerometer X Axis -> AN16/RC1
 	AD1PCFGHbits.PCFG17 = 0;         // Accelerometer Y Axis -> AN17/RC2
 	AD1PCFGHbits.PCFG18 = 0;         // Accelerometer Z Axis -> AN18/RC3
 	AD1PCFGHbits.PCFG19 = 0;         // ADC Aux 1    -> AN19/RC4
 	AD1PCFGHbits.PCFG20 = 0;         // ADC Aux 2    -> AN20/RE8
 	AD1PCFGHbits.PCFG21 = 0;         // ADC Aux 3    -> AN21/RE9

	/* Set control register 1 */
	/* 12-bit, unsigned integer format, autosampling */
	AD1CON1 = 0x04E0;

	/* Set control register 2 */
	/* Vref = AVcc/AVdd, Scan Inputs */
	AD1CON2 = 0x0000;

	/* Set Samples and bit conversion time */
	/* AS = 31 Tad, Tad = 64 Tcy = 1.6us  */
	AD1CON3 = 0x1F3F; //** Last PATCH xxx

	/* disable channel scanning here */
	AD1CSSL = 0x0000;

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* disable ADC interrupts */
	IEC0bits.AD1IE = 0;

	/* turn on ADC module */
	AD1CON1bits.ADON = 1;

	/* set ADC as configured */
	ee_adc_init_flag = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_analog_close( void )
{
	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* set ADC as unconfigured */
	ee_adc_init_flag = 0;
}

#endif

/* ADC Aux Input */
#ifdef __USE_ADC__

#define ADC_GP1      EE_ADC_AN1
#define ADC_GP2      EE_ADC_AN2
#define ADC_GP3      EE_ADC_AN3
#define EE_ADC_AN1   EE_ADC_PIN19 /* ADC_GP1 */
#define EE_ADC_AN2   EE_ADC_PIN20 /* ADC_GP2 */
#define EE_ADC_AN3   EE_ADC_PIN21 /* ADC_GP3 */
  
__INLINE__ void __ALWAYS_INLINE__ EE_adcin_init( void ) { EE_analog_init(); }

__INLINE__ float __ALWAYS_INLINE__ EE_adcin_get_volt( EE_UINT8 channel )
{
	float adcdata;

	switch (channel) {
		case 1: // Set AN19 - RC4 as input channel
			AD1CHS0 = 19;
			break;
		case 2: // Set AN20 - RE8 as input channel
			AD1CHS0 = 20;
			break;
		case 3: // Set AN21 - RE9 as input channel
			AD1CHS0 = 21;
			break;
		default: // Set to channel 1 as default
			AD1CHS0 = 19;
			break;
	}

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Return conversion */
	return (adcdata * VREF) / 4096;
}
#endif

/* Trimmer Input */
#ifdef __USE_TRIMMER__
__INLINE__ void __ALWAYS_INLINE__ EE_trimmer_init( void ) { EE_analog_init(); }

__INLINE__ float __ALWAYS_INLINE__ EE_trimmer_get_volt( void )
{
	float adcdata;

	// Set AN15 - RB15 as input channel
	AD1CHS0 = 15;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Return conversion */
	return (adcdata * VREF) / 4096;
}
#endif

/* Sensors Input */
#ifdef __USE_ANALOG_SENSORS__

// Thermal constants for the Voltage-Temperature conversion (fra)
#define THERM_A 0.0004132
#define THERM_B 0.000320135

__INLINE__ void __ALWAYS_INLINE__ EE_analogsensors_init( void ) { EE_analog_init(); }

__INLINE__ float __ALWAYS_INLINE__ EE_analog_get_temperature( void )
{
	float adcdata;

	// Set AN12 - RB12 as input channel
	AD1CHS0 = 12;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	// Conversion (fra)
	float r_therm, T_K, T_C;

	r_therm = 1 / (4096.0/adcdata - 1.0);

	// T_K = 1.0 / (THERM_A + THERM_B * log(r_therm));
	T_K = 1.0 / (THERM_A + THERM_B * ((r_therm-1) + 9.8) );
	T_C = T_K - 273.15;

	/* Return conversion */
	return T_C;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_analog_get_light( void )
{
	EE_UINT32 adcdata;

	// Set AN13 - RB13 as input channel
	AD1CHS0 = 13;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Convert the acquired data */
	adcdata = 200 - ( adcdata * 0.116 ); // lux

	/* Return conversion */
	return adcdata;
}
#endif

/* Accelerometer Input */
#ifdef __USE_ACCELEROMETER__

#define	EE_ACCEL_G_ZERO		1.65
#define	EE_ACCEL_G_SCALE_1_5	0.8
#define	EE_ACCEL_G_SCALE_2	0.6
#define	EE_ACCEL_G_SCALE_4	0.3
#define	EE_ACCEL_G_SCALE_6	0.2

extern EE_UINT8 EE_accelerometer_g;

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_sleep( void )  { LATDbits.LATD3 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_wakeup( void ) { LATDbits.LATD3 = 1; }

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_accelerometer_getglevel( void ) { return EE_accelerometer_g; }

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_setglevel( EE_UINT8 level)
{
	if (level <= 0) {
		EE_accelerometer_g = 0;
		LATGbits.LATG15 = 0;
	  LATCbits.LATC13 = 0;
	} else if (level == 1) {
		EE_accelerometer_g = 1;
		LATGbits.LATG15 = 1;
    LATCbits.LATC13 = 0;
	} else if (level == 2) {
		EE_accelerometer_g = 2;
  	LATGbits.LATG15 = 0;
  	LATCbits.LATC13 = 1;
	} else {
		EE_accelerometer_g = 3;
  	LATGbits.LATG15 = 1;
  	LATCbits.LATC13 = 1;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_config( void )
{
	// Set output pins for g-select and sleep options
	TRISDbits.TRISD3  = 0;
	TRISGbits.TRISG15 = 0;   // GS1
	TRISCbits.TRISC13 = 0;   // GS2

	// Set g-selet to 6g
	EE_accelerometer_setglevel(0);

	// Disable Sleep mode
	EE_accelerometer_wakeup();
}

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_init( void )
{
	EE_analog_init();

	// Set output pins for g-select and sleep options
	EE_accelerometer_config();
}

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_getx( void )
{
	float adcdata;

	// Set AN16 - RB16 as input channel
	AD1CHS0 = 16;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = ((ADC1BUF0 * 3.3) / 4096);

	/* Return conversion */
	adcdata -= EE_ACCEL_G_ZERO;
	switch (EE_accelerometer_g) {
		case 0:
			adcdata /= EE_ACCEL_G_SCALE_1_5;
			break;
		case 1:
			adcdata /= EE_ACCEL_G_SCALE_2;
			break;
		case 2:
			adcdata /= EE_ACCEL_G_SCALE_4;
			break;
		case 3:
			adcdata /= EE_ACCEL_G_SCALE_6;
			break;
	}

	return adcdata;
}

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_gety( void )
{
	float adcdata;

	// Set AN17 - RB17 as input channel
	AD1CHS0 = 17;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = (ADC1BUF0 * 3.3) / 4096;

	/* Return conversion */
	adcdata -= EE_ACCEL_G_ZERO;
	switch (EE_accelerometer_g) {
		case 0:
			adcdata /= EE_ACCEL_G_SCALE_1_5;
			break;
		case 1:
			adcdata /= EE_ACCEL_G_SCALE_2;
			break;
		case 2:
			adcdata /= EE_ACCEL_G_SCALE_4;
			break;
		case 3:
			adcdata /= EE_ACCEL_G_SCALE_6;
			break;
	}
	return adcdata;
}

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_getz( void )
{
	float adcdata;

	// Set AN18 - RB18 as input channel
	AD1CHS0 = 18;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = (ADC1BUF0 * 3.3) / 4096;

	/* Return conversion */
	adcdata -= EE_ACCEL_G_ZERO;
	switch (EE_accelerometer_g) {
		case 0:
			adcdata /= EE_ACCEL_G_SCALE_1_5;
			break;
		case 1:
			adcdata /= EE_ACCEL_G_SCALE_2;
			break;
		case 2:
			adcdata /= EE_ACCEL_G_SCALE_4;
			break;
		case 3:
			adcdata /= EE_ACCEL_G_SCALE_6;
			break;
	}
	return adcdata; // TODO!!!
}

#endif

/* /\************************************************************************* */
/*  Buzzer */
/*  *************************************************************************\/ */

#ifdef __USE_BUZZER__

#define EE_BUZZER_MAX_FREQ 20000UL
#define EE_BUZZER_MIN_FREQ 100UL

extern EE_UINT32 buzzer_freq;

void EE_buzzer_start(EE_UINT32 freq);
void EE_buzzer_stop(void);
void EE_buzzer_init(void);

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_set_freq( EE_UINT16 new_freq )
{
	EE_buzzer_start(new_freq);
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_buzzer_get_freq( void ) {
	return buzzer_freq;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_mute( void ) {
	EE_buzzer_stop();
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_unmute( void ) {
	EE_buzzer_start(buzzer_freq);
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_close( void ) {
	EE_buzzer_stop();
}

#endif

/* /\************************************************************************* */
/*  PWM Output */
/*  *************************************************************************\/ */

#ifdef __USE_PWM__

#define EE_PWM_PORT1 1
#define EE_PWM_PORT2 2

#define EE_PWM_ZERO_DUTY 1500

extern EE_UINT8 t_pre_scaler;

void EE_ocpwm_init(EE_UINT8 chan, unsigned long int pwm_period, unsigned long int init_pw);

//__INLINE__ void __ALWAYS_INLINE__ EE_pwm_set_duty_f( EE_UINT8 chan , float duty )
//{
//	/* The computed duty cycle*/
//	float duty_out ;
//
//	/* Get period from Timer2 period register PR2 */
//	EE_UINT16 period = PR2;
//
//	if (duty <= 0.0)
//		duty_out = 0; //** for negative values assume zero
//	else if(duty >= 1.0)
//		duty_out = 1; //** for exessive values assume one
//	else
//		duty_out = duty; //** for the correct values ...
//
//	// Computer register valure
//	switch (chan) {
//		case EE_PWM_PORT1:
//			OC8RS = duty_out * (period+1);
//			break;
//		case EE_PWM_PORT2:
//			OC7RS = duty_out * (period+1);
//			break;
//	}
//}

void EE_ocpwm_set_duty_f( EE_UINT8 chan , float duty );

__INLINE__ void __ALWAYS_INLINE__ EE_ocpwm_set_duty(EE_UINT8 chan, unsigned long int duty)
{
  duty = ( (duty * 40) >> t_pre_scaler ) - 1;  /* Compute the Current PulseWidth  to set */

	if(	duty > PR2) return;

  switch(chan)
  {
    case EE_PWM_PORT1:
			OC8RS = (unsigned int)duty; /* Load OCRS: current pwm duty cycle */
    	break;
    case EE_PWM_PORT2:
			OC3RS = (unsigned int)duty; /* Load OCRS: current pwm duty cycle */
    	break;
  }

  return;
}

__INLINE__ void __ALWAYS_INLINE__ EE_ocpwm_close( EE_UINT8 chan )
{
	switch (chan) {
		case EE_PWM_PORT1:	/** Close PWM1 **/
			OC8RS  = 0;
			OC8CON = 0;
			break;

		case EE_PWM_PORT2: /** Close PWM2 **/
			OC3RS  = 0;
			OC3CON = 0;
			break;
	}
}

#endif // __USE_PWM__

/* /\************************************************************************* */
/*  DAC */
/*  *************************************************************************\/ */

#ifdef __USE_DAC__

#define EE_DAC_I2C_KCLOCK		100

#define EE_DAC_GENERAL_CALL_RESET	0x06
#define EE_DAC_GENERAL_CALL_WAKEUP	0x09

#define EE_DAC_PD_NORMAL		0x00
#define EE_DAC_PD_1K			0x01
#define EE_DAC_PD_100K			0x10
#define EE_DAC_PD_500K			0x11

#define EE_DAC_SAVE_EEPROM		0x00
#define EE_DAC_NOSAVE_EEPROM		0x02

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_dac_general_call( EE_UINT8 second )
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed
	while(I2C1CONbits.SEN);

	// Write Slave address and set master for transmission  (R/W bit should be 0)
	I2C1TRN = 0x00;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write command
	I2C1TRN = 0x06;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */

	// Wait till Stop sequence is completed
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return 0;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_dac_fast_write( EE_UINT16 data, EE_UINT8 port, EE_UINT8 power)
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed
	while(I2C1CONbits.SEN);

	// Write address
	I2C1TRN = 0xC0 + ( port*2 & 0x02 );
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write first byte
	I2C1TRN = ((data / 256) & 0x0F) + (power << 4);
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till data is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write second byte
	I2C1TRN = data % 256;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till data is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */

	// Wait till Stop sequence is completed
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return 0;
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_dac_write( EE_UINT16 data, EE_UINT8 port, EE_UINT8 power, EE_UINT8 save)
{
	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Transmit a Start condition
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	// Wait till Start sequence is completed
	while(I2C1CONbits.SEN);

	// Write address
	I2C1TRN = 0xC0 + ( port*2 & 0x02 );
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write first byte
	I2C1TRN = 0x40 + ( save & 0x20 ) + power*2;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till data is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write second byte
	I2C1TRN = data / 16;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// Write third byte
	I2C1TRN = (data % 16) << 4;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -1;

	// Wait till address is transmitted
	while(I2C1STATbits.TBF);

	// Test for ACK condition received
	while(I2C1STATbits.ACKSTAT);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	// send STOP condition
	I2C1CONbits.PEN = 1;	/* initiate Stop on SDA and SCL pins */

	// Wait till Stop sequence is completed
	while(I2C1CONbits.PEN);

	// Ensure I2C module is idle
	while(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

	return 0;
}

extern volatile int ee_flexdmb_dac_init;
__INLINE__ void __ALWAYS_INLINE__ EE_dac_init( void )
{
	if(ee_flexdmb_dac_init==0){
		/* Configre SCL/SDA pin as open-drain */
		ODCGbits.ODCG2 = 1;
		ODCGbits.ODCG3 = 1;

		/* Clear Address and mask */
		I2C1ADD = 0;
		I2C1MSK = 0;

		/* Set baudrate */
		I2C1BRG = (40000ul / EE_DAC_I2C_KCLOCK) - 37;	// With Fcy = 40MHz !!!
		//I2C1BRG = 363;

		/* Configure I2C port */
		I2C1CON = 0;
		I2C1CONbits.ACKDT  = 1;
		I2C1CONbits.DISSLW = 1;

		/* Start I2C port */
		I2C1CONbits.I2CEN = 1;

		EE_dac_general_call(EE_DAC_GENERAL_CALL_RESET);
		ee_flexdmb_dac_init = 1;
	}
}

#endif

/* /\************************************************************************* */
/*  Motor PWM - TODO!!! */
/*  *************************************************************************\/ */

#ifdef __USE_PWM_MOTOR__

__INLINE__ void __ALWAYS_INLINE__ EE_motor_init( void ) {

}

#endif

/* /\************************************************************************* */
/*  Encoder */
/*  *************************************************************************\/ */

#ifdef __USE_ENCODER__

#define EE_ENCODER_HW 		0
#define EE_ENCODER_SW 		1
#define EE_ENCODER_SW_PINA	PORTDbits.RD7                           // CN16
#define EE_ENCODER_SW_PINB	PORTCbits.RC4                           // digital input
#define QEI_TICK_PER_REV	500
#define	QEI_MAX_CNT_PER_REV	0xffff
#define	SWENC_MAX_CNT_PER_REV	0xffff

extern const EE_UINT16 ee_enc_poscnts_offset;

/*
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_encoder_ISR_cbk(EE_UINT16 dir, EE_UINT16 posl, EE_UINT32 posh, EE_INT8* runflag)
{
	if(dir==1 && posl==0) {
		if (posh == 0x7FFFFFFF) // 2147483647
			*runflag = 1;
		return posh+1;
	}
	else if(dir==0 && posl==0xFFFF) {
		if (posh == 0x80000000) // -2147483648
			*runflag = -1;
		return posh-1;
	}
	else {
		*runflag = 0;
		return posh;
	}
}
*/
__INLINE__ EE_INT16 __ALWAYS_INLINE__ EE_encoder_ISR_cbk(EE_UINT16 dir, EE_UINT16 posl, EE_UINT16 threshold, EE_INT8* runflag)
{
	// to do: support for posh if needed
	if(dir==1 && posl==threshold) {
		*runflag = 1;
		return 1;
	}
	else if(dir==0 && posl==(threshold-1)) {
		*runflag = -1;
		return -1;
	}
	else {
		*runflag = 0;
		return 0;
	}
}

void EE_sw_encoder_callback(void);
extern EE_UINT16 ee_encsw_encdir;		// Count direction: 1 if +, 0 if -
//extern EE_UINT32 ee_encsw_poscnts_h;
extern EE_UINT16 ee_encsw_poscnts;
extern EE_INT16 ee_encsw_swapped;
extern EE_INT16 ee_encsw_maxcnt;
extern EE_INT8 ee_encsw_over_under_flow;

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_SW_init(EE_UINT8 swap_on_off, EE_UINT8 irq_on_off)
{
	if(swap_on_off)
		ee_encsw_swapped = 1;
	else
		ee_encsw_swapped = 0;
	ee_encsw_maxcnt = SWENC_MAX_CNT_PER_REV;
	
	/** Reset position counter */
	ee_encsw_poscnts = 0;
	ee_encsw_encdir = 0;
	//ee_encsw_poscnts_h = 0;
	
	IEC1bits.CNIE = 0;      // Disable interrupts on CN16
	OC8CON = 0;				// Disable OC8 module
	TRISDbits.TRISD7  = 1; 	// CN16/D7 input
	AD1PCFGHbits.PCFG19 = 1; // digital input
	TRISCbits.TRISC4  = 1; 	// C4 input
    CNPU1 = 0;              // Disable all CN pull ups
    CNEN1 = 0;           	// Disable all
	CNEN2 = 0x01;           // Enable interrupts for CN16
    IFS1bits.CNIF = 0;      // Clear interrupt flag
    IEC1bits.CNIE = irq_on_off;      // Enable interrupts on CN16
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_SW_close(void)
{
	IEC1bits.CNIE = 0;      // Disable interrupts on CN16
	CNEN2 = 0;           	// Disable CN16
}

__INLINE__ EE_INT16 __ALWAYS_INLINE__ EE_encoder_SW_get_ticks(void)
{
	return ee_encsw_poscnts;
}
/*
__INLINE__ EE_INT32 __ALWAYS_INLINE__ EE_encoder_SW_get_ticks_32(void)
{
	return ((EE_INT32)ee_encsw_poscnts_h)*65535 + (EE_INT32)ee_encsw_poscnts;
}

__INLINE__ float __ALWAYS_INLINE__ EE_encoder_SW_get_ticks_f(void)
{
	return (float)((EE_INT32)ee_encsw_poscnts_h)*65535.0 + (float)ee_encsw_poscnts;
}

__INLINE__ float __ALWAYS_INLINE__ EE_encoder_SW_get_position(float sw_gain)
{
	return EE_encoder_SW_get_ticks_f() * sw_gain; 
}
*/
__INLINE__ float __ALWAYS_INLINE__ EE_encoder_SW_get_flag(void)
{
	return (float)ee_encsw_over_under_flow;
}

//extern EE_UINT32 ee_enchw_poscnts_h;
extern EE_INT8 ee_enchw_over_under_flow;

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_init(EE_UINT8 swap_on_off, EE_UINT8 irq_on_off)
{
	/* Reset counter */
	//ee_enchw_poscnts_h = 0;
	
	/* Default value */
	QEICON = 0;
	
	/* set encoder bits as digital input */
 	AD1PCFGLbits.PCFG3 = 1;
 	AD1PCFGLbits.PCFG4 = 1;
 	AD1PCFGLbits.PCFG5 = 1;
 	AD2PCFGLbits.PCFG3 = 1;
 	AD2PCFGLbits.PCFG4 = 1;
 	AD2PCFGLbits.PCFG5 = 1;

	// Swap channels
	QEICONbits.SWPAB = swap_on_off;
	// Count error interrupts disabled
	DFLTCONbits.CEID = 1;
	// Interrupts
		// Interrupts
	IPC14bits.QEIIP = 5;
	IFS3bits.QEIIF = 0;
	IEC3bits.QEIIE = irq_on_off;
	// Reset position counter
	POSCNT = ee_enc_poscnts_offset;
	// Set bound value
	MAXCNT = QEI_MAX_CNT_PER_REV;
	// X4 mode with position counter reset by MAXCNT
	QEICONbits.QEIM = 7;
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_close(void)
{
	// Disable QEI Module
	QEICONbits.QEIM = 0;
}

__INLINE__ EE_INT16 __ALWAYS_INLINE__ EE_encoder_get_ticks(void)
{
	return POSCNT + ee_enc_poscnts_offset;
}
/*
__INLINE__ EE_INT32 __ALWAYS_INLINE__ EE_encoder_get_ticks_32(void)
{
	return ((EE_INT32)ee_enchw_poscnts_h)*65535 + (EE_INT32)POSCNT;
}

__INLINE__ float __ALWAYS_INLINE__ EE_encoder_get_ticks_f(void)
{
	return (float)((EE_INT32)ee_enchw_poscnts_h)*65535.0 + (float)POSCNT;
}

__INLINE__ float __ALWAYS_INLINE__ EE_encoder_get_position(float hw_gain)
{
	return EE_encoder_get_ticks_f() * hw_gain; 
}
*/
__INLINE__ float __ALWAYS_INLINE__ EE_encoder_get_flag(void)
{
	return (float)ee_enchw_over_under_flow;
}

__INLINE__ void __ALWAYS_INLINE__ EE_encoder_set_IRQ(EE_UINT8 irq_on_off)
{
	IEC3bits.QEIIE = irq_on_off;
}

extern void (*QEI_cbk)(void);
__INLINE__ void __ALWAYS_INLINE__ EE_encoder_set_ISR_callback(void (*qei_cbk)(void))
{
	QEI_cbk = qei_cbk;
}

#endif


/* ************************************************************************* */
/* InfraRed - TODO!!! */
/* ************************************************************************* */

#ifdef __USE_IR__

__INLINE__ void __ALWAYS_INLINE__ EE_ir_init( void ) {

}

#endif

/* ************************************************************************* */
/* USB Communication - TODO!!! */
/* ************************************************************************* */

#if defined __USE_USB__
void EE_usb_init(void);
EE_INT16 EE_usb_write(EE_UINT8 *buf, EE_UINT16 len);
EE_INT16 EE_usb_read(EE_UINT8 *buf, EE_UINT16 len);
#endif

/* ************************************************************************* */

/* ************************************************************************* */

#endif

#endif
