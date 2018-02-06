#ifndef __TOUCH_HAL_EE_H__
#define __TOUCH_HAL_EE_H__

#if defined __MICROCHIP_DSPIC30__

#if !defined(__FOUR_WIRES__) && !defined(__FIVE_WIRES__)
#error "Choose one between FOUR WIRES and FIVE WIRES technologies."
#endif

#if defined(__FOUR_WIRES__) && defined(__FIVE_WIRES__)
#error "Choose only ONE between FOUR WIRES and FIVE WIRES technologies."
#endif

#define CLEARBIT(BIT)		(BIT = 0)
#define SETBIT(BIT)		(BIT = 1)
#define TOGGLEBIT(BIT) 		(BIT ^= 1)

#ifdef __FOUR_WIRES__

/****************************************************************************
  4-wires
****************************************************************************/

// ADC Settings
//#ifndef ADC_TO_USE
//#define ADC_TO_USE	2
//#endif

//#if ADC_TO_USE!=1 && ADC_TO_USE!=2
//#error dsPIC33 has only two ADCs.Please change ADC_TO_USE macro.
//#endif

#define ADC_1_ONOFF		AD1CON1bits.ADON
#define ADC_1_SAMP		AD1CON1bits.SAMP
#define ADC_1_ASAM		AD1CON1bits.ASAM
#define ADC_1_FORM		AD1CON1bits.FORM
#define ADC_1_SSRC		AD1CON1bits.SSRC
#define ADC_1_AD12B		AD1CON1bits.AD12B
#define ADC_1_CON2		AD1CON2
#define ADC_1_SAMC		AD1CON3bits.SAMC
#define ADC_1_ADRC		AD1CON3bits.ADRC
#define ADC_1_ADCS		AD1CON3bits.ADCS
#define ADC_1_CONVERSION_DONE	AD1CON1bits.DONE
#define ADC_1_SELECTED_PIN 	AD1CHS0
#define ADC_1_RESULT_BUFFER	ADC1BUF0
#define ADC_1_INTERRUPT_FLAG	IFS0bits.AD1IF
#define ADC_1_INTERRUPT_ENABLE	IEC0bits.AD1IE
#define ADC_1_INTERRUPT_NAME	_ADC1Interrupt
#define ADC_1_TURN_ON		SETBIT(ADC_1_ONOFF)
#define ADC_1_TURN_OFF		CLEARBIT(ADC_1_ONOFF)
#define ADC_1_CONVERSION_RESET	CLEARBIT(ADC_1_CONVERSION_DONE)
#define ADC_1_CONVERSION_START 	CLEARBIT(ADC_1_SAMP)

#define ADC_2_ONOFF		AD2CON1bits.ADON
#define ADC_2_SAMP		AD2CON1bits.SAMP
#define ADC_2_ASAM		AD2CON1bits.ASAM
#define ADC_2_FORM		AD2CON1bits.FORM
#define ADC_2_SSRC		AD2CON1bits.SSRC
#define ADC_2_AD12B		AD2CON1bits.AD12B
#define ADC_2_CON2		AD2CON2
#define ADC_2_SAMC		AD2CON3bits.SAMC
#define ADC_2_ADRC		AD2CON3bits.ADRC
#define ADC_2_ADCS		AD2CON3bits.ADCS
#define ADC_2_CONVERSION_DONE	AD2CON1bits.DONE
#define ADC_2_SELECTED_PIN 	AD2CHS0
#define ADC_2_RESULT_BUFFER	ADC2BUF0
#define ADC_2_INTERRUPT_FLAG	IFS1bits.AD2IF
#define ADC_2_INTERRUPT_ENABLE	IEC1bits.AD2IE
#define ADC_2_INTERRUPT_NAME	_ADC2Interrupt
#define ADC_2_TURN_ON		SETBIT(ADC_2_ONOFF)
#define ADC_2_TURN_OFF		CLEARBIT(ADC_2_ONOFF)
#define ADC_2_CONVERSION_RESET	CLEARBIT(ADC_2_CONVERSION_DONE)
#define ADC_2_CONVERSION_START 	CLEARBIT(ADC_2_SAMP)

#if defined(__USE_MOTIONBOARD__)

#ifdef __USE_TOUCH__

// ADC reading pins
#define	STANDBY_PIN_1		9		// Pin Change & Low_Level_Readings & X-Coordinate Reading
#define ADC_Y_1			STANDBY_PIN_1
#define ADC_X_1			15

#define EE_1_TOUCH_BOTTOM_AD	AD1PCFGLbits.PCFG15
#define EE_1_TOUCH_BOTTOM_TRIS	TRISBbits.TRISB15
#define EE_1_TOUCH_RIGHT_AD	AD1PCFGLbits.PCFG9
#define EE_1_TOUCH_RIGHT_TRIS	TRISBbits.TRISB9
#define EE_1_TOUCH_EN_A		LATEbits.LATE1
#define EE_1_TOUCH_EN_B		LATEbits.LATE2
#define EE_1_TOUCH_EN_C		LATEbits.LATE3
#define EE_1_TOUCH_EN_A_TRIS 	TRISEbits.TRISE1
#define EE_1_TOUCH_EN_B_TRIS	TRISEbits.TRISE2
#define EE_1_TOUCH_EN_C_TRIS	TRISEbits.TRISE3

// I/O States
#define STANDBY_1_CONFIGURATION		\
					(SETBIT(EE_1_TOUCH_EN_A), \
					 SETBIT(EE_1_TOUCH_EN_B), \
					 CLEARBIT(EE_1_TOUCH_EN_C))
					 
#define X_POS_1_CONFIGURATION		\
					(CLEARBIT(EE_1_TOUCH_EN_A), \
					 SETBIT(EE_1_TOUCH_EN_B), \
					 SETBIT(EE_1_TOUCH_EN_C))
					 
#define Y_POS_1_CONFIGURATION		\
					(SETBIT(EE_1_TOUCH_EN_A), \
					 CLEARBIT(EE_1_TOUCH_EN_B), \
					 CLEARBIT(EE_1_TOUCH_EN_C))

#endif // __USE_TOUCH__

#elif defined(__USE_DOUBLETOUCHBOARD__)

#ifdef __USE_TOUCH__

// ADC reading pins
// STANDBY = Y = RIGHT
#define STANDBY_PIN_1		23		// Pin Change & Low_Level_Readings & X-Coordinate Reading
#define ADC_Y_1			STANDBY_PIN_1
// X = BOTTOM
#define ADC_X_1			22

#define EE_1_TOUCH_BOTTOM_AD	AD1PCFGHbits.PCFG22
#define EE_1_TOUCH_BOTTOM_TRIS	TRISAbits.TRISA6
#define EE_1_TOUCH_RIGHT_AD	AD1PCFGHbits.PCFG23
#define EE_1_TOUCH_RIGHT_TRIS	TRISAbits.TRISA7
#define EE_1_TOUCH_EN_A		LATEbits.LATE2
#define EE_1_TOUCH_EN_A_TRIS 	TRISEbits.TRISE2
#define EE_1_TOUCH_EN_B		LATGbits.LATG12
#define EE_1_TOUCH_EN_B_TRIS	TRISGbits.TRISG12
#define EE_1_TOUCH_EN_C		LATEbits.LATE1
#define EE_1_TOUCH_EN_C_TRIS	TRISEbits.TRISE1

// I/O States
#define STANDBY_1_CONFIGURATION		\
					(SETBIT(EE_1_TOUCH_EN_A), \
					 SETBIT(EE_1_TOUCH_EN_B), \
					 CLEARBIT(EE_1_TOUCH_EN_C))
					 
#define X_POS_1_CONFIGURATION		\
					(CLEARBIT(EE_1_TOUCH_EN_A), \
					 SETBIT(EE_1_TOUCH_EN_B), \
					 SETBIT(EE_1_TOUCH_EN_C))
					 
#define Y_POS_1_CONFIGURATION		\
					(SETBIT(EE_1_TOUCH_EN_A), \
					 CLEARBIT(EE_1_TOUCH_EN_B), \
					 CLEARBIT(EE_1_TOUCH_EN_C))

#endif // __USE_TOUCH__

#ifdef __USE_TOUCH_2__

// ADC reading pins
// STANDBY = Y = RIGHT
#define STANDBY_PIN_2		10		// Pin Change & Low_Level_Readings & X-Coordinate Reading
#define ADC_Y_2			STANDBY_PIN_2
// X = BOTTOM
#define ADC_X_2			8

#define EE_2_TOUCH_BOTTOM_AD	AD2PCFGLbits.PCFG8
#define EE_2_TOUCH_BOTTOM_TRIS	TRISBbits.TRISB8
#define EE_2_TOUCH_RIGHT_AD	AD2PCFGLbits.PCFG10
#define EE_2_TOUCH_RIGHT_TRIS	TRISBbits.TRISB10
#define EE_2_TOUCH_EN_A		LATFbits.LATF5
#define EE_2_TOUCH_EN_A_TRIS 	TRISFbits.TRISF5
#define EE_2_TOUCH_EN_B		LATDbits.LATD15
#define EE_2_TOUCH_EN_B_TRIS	TRISDbits.TRISD15
#define EE_2_TOUCH_EN_C		LATBbits.LATB15
#define EE_2_TOUCH_EN_C_TRIS	TRISBbits.TRISB15
// I/O States
#define STANDBY_2_CONFIGURATION	(SETBIT(EE_2_TOUCH_EN_A), SETBIT(EE_2_TOUCH_EN_B), CLEARBIT(EE_2_TOUCH_EN_C))
#define X_POS_2_CONFIGURATION	(CLEARBIT(EE_2_TOUCH_EN_A), SETBIT(EE_2_TOUCH_EN_B), SETBIT(EE_2_TOUCH_EN_C))
#define Y_POS_2_CONFIGURATION	(SETBIT(EE_2_TOUCH_EN_A), CLEARBIT(EE_2_TOUCH_EN_B), CLEARBIT(EE_2_TOUCH_EN_C))

#endif // __USE_TOUCH_2__

#else

#error "No board specified. Choose among MOTIONBOARD and DOUBLETOUCH board."

#endif

#endif // __FOUR_WIRES__

#ifdef __FIVE_WIRES__
#error There_s no support for five wires device ^_^ Enjoy.
#endif // __FIVE_WIRES__

#endif // __MICROCHIP_DSPIC30__

#endif // __touch_hal_ee_h__
