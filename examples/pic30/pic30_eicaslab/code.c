/*
 * Author: 2006 Paolo Gai
 * CVS: $Id: code.c,v 1.1 2008/10/06 21:22:57 pj Exp $
 */

#include "ee.h"
#include "ee_irq.h"
#include <stdio.h>


// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

// the time reference
double t;

/* Program the Timer2 peripheral to raise interrupts */
void T2_program(void)
{
	T2CON = 0;		/* Stops the Timer2 and reset control reg	*/
	TMR2  = 0;		/* Clear contents of the timer register	*/
	PR2   = 0x9c40;		/* 1ms @ 40Mhz */
//	PR2   = 0x07D0;		/* 1ms @ 2MHz */
	IPC1bits.T2IP = 5;	/* Set Timer2 priority to 5		*/
	IFS0bits.T2IF = 0;	/* Clear the Timer2 interrupt status flag	*/
	IEC0bits.T2IE = 1;	/* Enable Timer2 interrupts		*/
	T2CONbits.TON = 1;	/* Start Timer2 with prescaler settings at 1:1
				  * and clock source set to the internal 
				  * instruction cycle			*/
}

/* Clear the Timer2 interrupt status flag */
void T2_clear(void)
{
	IFS0bits.T2IF = 0;
}


/* LCD update functions
 * -------------------------------------------------------------
 */

#ifdef __USE_LCD__

/* defined in contrib/scicos/src/pic20/flex_dmb_lcd.c */
volatile float scicos_lcd_value1 = 0.0;
volatile float scicos_lcd_value2 = 0.0;
volatile int scicos_lcd_used = 0;

static char lcd_buf[17];

/*
* Output syntax: n:smmmmmmmmEsaa
* where:	n is the input number (0/1);
*	s is the signum (-/+);
*	mmmmmmmm is the mantissa (max 8 chars);
*	aaa is the exponent (max 3 chars).
*/
static void write_buf(float data)
{
	/* Conversion routine */
	//** WARNING: 
	//**          Two lines = 7.5 ms !
	//** To DO: find a faster sprintf()
	sprintf(lcd_buf,"%+.6E ",(double)data);
}

void update_lcd(void)
{
	static float oldvalue1 = 1.0; // something different from 0
	static float oldvalue2 = 1.0; // something different from 0
	float newvalue1;
	float newvalue2;

	if (!scicos_lcd_used)
		return;

	/* check if we have to update the LCD */
	EE_pic30_disableIRQ();
	newvalue1 = scicos_lcd_value1;
	newvalue2 = scicos_lcd_value2;	
	EE_pic30_enableIRQ();

	/* stop if the data are the same */
	if (newvalue1 == oldvalue1 && newvalue2 == oldvalue2)
		return;
 
	/* save the new values */
	oldvalue1 = newvalue1;
	oldvalue2 = newvalue2;

	/* Write 1st value on LCD */
	EE_lcd_puts("1:");
	write_buf(newvalue1);
	EE_lcd_puts(lcd_buf);
	
	/* Move to second line */
	EE_lcd_line2();
	
	/* Write 2nd value on LCD */
	EE_lcd_puts("2:");
	write_buf(newvalue2);
	EE_lcd_puts(lcd_buf);	

	/* Reset position for the next iteration */
	EE_lcd_home();
}

#endif



/* This is an ISR Type 2 which is attached to the Timer2 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T2Interrupt)
{
	/* clear the interrupt source */
	T2_clear();

	/* Increment the current time */
	t += 0.001; // 1 ms

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


#ifdef __USE_LCD__
TASK(rt_LCD)
{
	update_lcd();
}
#endif

/* EICAS Initialization sequence prototype */
void EICAS_Init();

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 80;// 78 old value---check!
	
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

#ifdef __USE_LCD__
	/* Init LCD */
	EE_lcd_init();
	
	/* Clean LCD */
	EE_lcd_clear();
#endif

	t = 0.0; //simulation time

	EICAS_Init();
  
	/* Program Timer 1 to raise interrupts */
	T2_program();

	StartOS(OSDEFAULTAPPMODE);

	/* Forever loop: background activities (if any) should go here */
	for (;;);
	
	return 0;
}
