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


#ifndef __INCLUDE_EE_MINIFLEX_DEMOBOARD_H__
#define __INCLUDE_EE_MINIFLEX_DEMOBOARD_H__

#ifdef __USE_DEMOBOARD__

/* /\************************************************************************* */
/*  Buzzer */
/*  *************************************************************************\/ */

#ifdef __USE_BUZZER__

extern EE_UINT16 buzzer_freq;
extern EE_UINT16 buzzer_ticks;
extern EE_UINT16 count;


__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_init( void )
{
  count=0;

  // Initialize Output Compare Module
  OC1CONbits.OCM = 0b000; // Disable Output Compare Module
  OC1R  = 2272; // Write the duty cycle for the first PWM pulse
  OC1RS = 2272; // Write the duty cycle for the second PWM pulse
  OC1CONbits.OCTSEL = 1;  // Select Timer 3 as output compare time base
  OC1CONbits.OCM = 0b110; // Select the Output Compare mode
  
  // Initialize and enable Timer3
  T3CONbits.TON = 0; // Disable Timer
  T3CONbits.TCS = 0; // Select internal instruction cycle clock
  T3CONbits.TGATE = 0; // Disable Gated Timer mode
  T3CONbits.TCKPS = 1; // Select 1:8 Prescaler
  TMR3 = 0x00; // Clear timer register
  PR3  = 4545; // Load the period value
  IPC2bits.T3IP = 0x01; // Set Timer 3 Interrupt Priority Level
  IFS0bits.T3IF = 0; // Clear Timer 3 Interrupt Flag
  IEC0bits.T3IE = 0; // Disable Timer 3 interrupt
  T3CONbits.TON = 0; //
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_set_freq( EE_UINT16 new_freq )
{
	buzzer_freq  = new_freq;
	if ((new_freq > 100) && (new_freq < 48000)) {
		buzzer_freq  = EE_SYS_CLOCK / (buzzer_freq << 3); // Using 1:8 prescaler
    buzzer_ticks = buzzer_freq >> 1;

    OC1R = buzzer_ticks;
    OC1RS = buzzer_ticks;
    PR3 = buzzer_freq;
    if(!T3CONbits.TON)
      T3CONbits.TON = 1; // Start Timer
  }
  else T3CONbits.TON = 0; // Start Timer
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_buzzer_get_freq( void ) {
	return buzzer_freq;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_mute( void ) {
	/* Stop Timer3 */
	T3CONbits.TON = 0;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_unmute( void ) {
	/* Clear contents of the timer register */
	TMR3 = 0;

	/* Start Timer3 */
	T3CONbits.TON = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buzzer_close( void ) {
	/* Stop Timer4 */
	T3CONbits.TON = 0;

	/* Disable Timer4 interrupts */
	IEC0bits.T3IE = 0;
}

#endif // __USE_BUZZER__

/* /\************************************************************************* */
/*  Analog inputs */
/*  *************************************************************************\/ */

/* Accelerometer Input */
#ifdef __USE_ACCELEROMETER__

#define	EE_ACCEL_G_ZERO		1.65
#define	EE_ACCEL_G_SCALE_1_5	0.8
#define	EE_ACCEL_G_SCALE_2	0.6
#define	EE_ACCEL_G_SCALE_4	0.3
#define	EE_ACCEL_G_SCALE_6	0.2

extern EE_UINT8 EE_accelerometer_g;

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_init( void )
{
	/* set configuration bit as ADC input */
 	AD1PCFGbits.PCFG10 = 0; // X Axis -> AN10/RB14
 	AD1PCFGbits.PCFG11 = 0; // Y Axis -> AN11/RB13
 	AD1PCFGbits.PCFG12 = 0; // Z Axis -> AN12/RB12

	/* Configure ADC */
	EE_analog_init();

	// Set output pins for g-select and sleep options
	TRISBbits.TRISB5 = 0;
	TRISBbits.TRISB8 = 0;   // GS1
	TRISBbits.TRISB6 = 0;   // GS2

	// Set g-selet to 6g
	LATBbits.LATB8 = 1;
	LATBbits.LATB6 = 1;
	EE_accelerometer_g = 3;

	// Disable Sleep mode
	LATBbits.LATB5 = 1;

	/* turn on ADC module */
	EE_analog_start();
}

__INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_eccelerometer_getglevel( void ) { return EE_accelerometer_g; }

__INLINE__ void __ALWAYS_INLINE__ EE_eccelerometer_setglevel( EE_UINT8 level)
{
	if (level <= 0) {
		EE_accelerometer_g = 0;
		LATBbits.LATB8 = 0;
		LATBbits.LATB6 = 0;
	} else if (level == 1) {
		EE_accelerometer_g = 1;
		LATBbits.LATB8 = 1;
		LATBbits.LATB6 = 0;
	} else if (level == 2) {
		EE_accelerometer_g = 2;
		LATBbits.LATB8 = 0;
		LATBbits.LATB6 = 1;
	} else {
		EE_accelerometer_g = 3;
		LATBbits.LATB8 = 1;
		LATBbits.LATB6 = 1;
	}
}

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_sleep( void )  { LATBbits.LATB5 = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_accelerometer_wakeup( void ) { LATBbits.LATB5 = 1; }

__INLINE__ float __ALWAYS_INLINE__ EE_accelerometer_getx( void )
{
	float adcdata;

	// Set AN10 - RB14 as input channel
	AD1CHS = 10;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = ((ADC1BUF0 * 3.3) / 1024);

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

	// Set AN11 - RB13 as input channel
	AD1CHS = 11;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = (ADC1BUF0 * 3.3) / 1024;

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

	// Set AN12 - RB12 as input channel
	AD1CHS = 12;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data and convert to volts */
	adcdata = (ADC1BUF0 * 3.3) / 1024;

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

/* ************************************************************************* */

#ifdef __USE_LIGHT__

__INLINE__ void __ALWAYS_INLINE__ EE_light_init( void )
{
	/* set configuration bit as ADC input */
 	AD1PCFGbits.PCFG9 = 0; // Temperature Sensor -> AN9/RB15

	/* Configure ADC */
	EE_analog_init();

	/* turn on ADC module */
	EE_analog_start();
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_light_get( void )
{
	EE_UINT32 adcdata;

	// Set AN9 - RB15 as input channel
	AD1CHS = 9;

	/* Start conversion */
	AD1CON1bits.SAMP = 1;

	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);

	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;

	/* Acquire data */
	adcdata = ADC1BUF0;

	/* Convert the acquired data */
	adcdata = 200 - ( adcdata * 0.464 ); // Lux - TODO: Check constants!

	/* Return conversion */
	return adcdata;
}
#endif

/* ************************************************************************* */

/* ************************************************************************* */

#endif /* __USE_DEMOBOARD__ */

#endif /* __INCLUDE_EE_MINIFLEX_DEMOBOARD_H__ */







/* ############################# BEGIN OLD STUFF ############################# */

#if 0

/* /\************************************************************************* */
/*  Includes needed by PicDemZ wirelessmodule (GF) */
/*  *************************************************************************\/ */

#if defined (__USE_PICDEMZ_WITH_INT4__) || (__USE_PICDEMZ_WITH_CN20INT__)

#include "radio_spi.h"

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
/*  PWM Output */
/*  *************************************************************************\/ */

#ifdef __USE_PWM__

#define EE_PWM_PORT1 1
#define EE_PWM_PORT2 2

#define EE_PWM_ZERO_DUTY 1500

extern EE_UINT8 t_pre_scaler;

void EE_pwm_init(EE_UINT8 chan, unsigned long int pwm_period, unsigned long int init_pw);

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

void EE_pwm_set_duty_f( EE_UINT8 chan , float duty );

__INLINE__ void __ALWAYS_INLINE__ EE_pwm_set_duty(EE_UINT8 chan, unsigned long int duty)
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

__INLINE__ void __ALWAYS_INLINE__ EE_pwm_close( EE_UINT8 chan )
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


#endif
