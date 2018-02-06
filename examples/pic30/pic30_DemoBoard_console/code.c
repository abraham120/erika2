/*
 * Author:
 * CVS: $Id: code.c,v 1.3 2007/03/15 15:33:16 nino Exp $
 */

#include "ee.h"
#include "ee_irq.h"

#include "console_serial.h"

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0xffff;		/* Load the Period register wit the value 0xffff	*/
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
				* and clock source set to the internal
				* instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}

/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

char * mymessage = "ErikaConsole\r\n";
console_descriptor_t *my_console_1;
#define MY_FIRST_SERIAL 1
#define MY_FIRST_CONSOLE 0

TASK(TaskSend)
{
	static char j = 0;

	console_write(MY_FIRST_CONSOLE, mymessage, strlen(mymessage));
	if ((j++)%2)
		EE_leds_on();
	else
		EE_leds_off();
}

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Init leds */
	EE_leds_init();
	EE_demoboard_leds_init();

	/* Applicatio Init */
	my_console_1 = console_serial_config(MY_FIRST_SERIAL, 115200,
						CONSOLE_SERIAL_FLAG_BIT8_NO |
						CONSOLE_SERIAL_FLAG_BIT_STOP1);
	console_init(MY_FIRST_CONSOLE, my_console_1);
	if (console_open(MY_FIRST_CONSOLE) == -1)
		EE_led_on();
	else
		EE_led_off();


	/* Program cyclic alarms which will fire after an initial offset, and after that periodically */
	SetRelAlarm(AlarmSend, 500, 500);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

	return 0;
}
