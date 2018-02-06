#include <stdio.h>
#include "string.h"

#include "ee.h"
#include "cpu/pic30/inc/ee_irqstub.h"

#include "touch.h"
#include "console_serial.h"

_FWDT(FWDTEN_OFF);      /* Watchdog Timer Enabled/disabled by user software */
_FGS(GCP_OFF);          /* Disable Code Protection */
_FOSCSEL(FNOSC_PRIPLL); /* Primary (XT, HS, EC) Oscillator without PLL */
_FOSC(OSCIOFNC_ON & POSCMD_XT); /* OSC2 Pin Function: OSC2 is Clock Output
                                 * Primary Oscillator Mode: XT Crystanl */

//#define TOUCH_TEST_RAW
//#define TOUCH_TEST_UNSIGNED
#define TOUCH_TEST_SIGNED

#define TOUCH_CHANNEL 0
#define TOUCH_X_RANGE 240
#define TOUCH_Y_RANGE 180

/* Console variables and defines */
char str[40];
console_descriptor_t *my_console_1;
#define MY_FIRST_SERIAL 1
#define MY_FIRST_CONSOLE 0

static tune_raw_t tune;

/******************************************************************************/
/*                          Function Definitions                              */
/******************************************************************************/
static void timer_set(void)
{
	/* TIMER 1  */
	T1CON = 0;		/* Stops the Timer1 and reset control reg */
	TMR1 = 0;		/* Clear contents of the timer register	*/
	PR1 = 0x9C40;		/* Load the Period register -> 1ms @ 40MHz */
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 5 */
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag */
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts */
	T1CONbits.TON = 1;	/* Start Timer1 without prescaler */
}
/******************************************************************************/
/*                                  TASKs                                     */
/******************************************************************************/
TASK(TASK_SEND)
{
	EE_INT16 x,y;

#ifdef TOUCH_TEST_RAW
	touch_1_poll_raw_position(TOUCH_X_AXIS, &x);
	touch_1_poll_raw_position(TOUCH_Y_AXIS, &y);
	sprintf(str,"x:%5d y:%5d [RAW]\n",x,y);
#endif

#ifdef TOUCH_TEST_UNSIGNED
	touch_1_poll_u_position(TOUCH_X_AXIS, &x);
	touch_1_poll_u_position(TOUCH_Y_AXIS, &y);
	sprintf(str,"x:%5d y:%5d [UNSIGNED]\n",x,y);
#endif

#ifdef TOUCH_TEST_SIGNED
	touch_1_poll_s_position(TOUCH_X_AXIS, &x);
	touch_1_poll_s_position(TOUCH_Y_AXIS, &y);
	sprintf(str,"x:%5d y:%5d [SIGNED]\n",x,y);
#endif

	console_write(MY_FIRST_CONSOLE, (unsigned char*)str, strlen(str));
}

/******************************************************************************/
/*                                   MAIN                                     */
/******************************************************************************/
int main(void)
{	
	/* Clock setup for 40 MHz */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	while (OSCCONbits.LOCK != 1) ;

	/* Init basic components */	
	timer_set();		
	EE_leds_init();
	EE_daughter_leds_init();
	EE_switch_init();
	EE_buttons_init(NULL, NULL);

	/* Application Init */
	my_console_1 = console_serial_config(MY_FIRST_SERIAL, 115200,
						CONSOLE_SERIAL_FLAG_BIT8_NO |
						CONSOLE_SERIAL_FLAG_BIT_STOP1);
	console_init(MY_FIRST_CONSOLE, my_console_1);
	if (console_open(MY_FIRST_CONSOLE) == -1)
		EE_led_on();
	else
		EE_led_off();

	//touch_read_mode = [POLLING|BLOCKING]|[RAW_FORMAT|SIGNED_FORMAT|UNSIGNED_FORMAT];

	// Nice hard coding for touch calibration.
	tune.xt1 = 2893;
	tune.yt1 = 1420;
	tune.xt2 = 1864;
	tune.yt2 = 2260;
	tune.xt3 = 834;
	tune.yt3 = 579;
	touch_1_set_dimension(TOUCH_X_AXIS, TOUCH_X_RANGE);
	touch_1_set_dimension(TOUCH_Y_AXIS, TOUCH_Y_RANGE);
	touch_1_raw_init();
	touch_1_tune(&tune);
	touch_1_start();

	SetRelAlarm(Alarm_Send, 200, 200);

	// Forever loop: background activities (if any) should go here
	for (;;);
}

/******************************************************************************/
/*                                     ISRs                                   */
/******************************************************************************/
ISR2(_T1Interrupt)
{
	IFS0bits.T1IF = 0;
	CounterTick(DUMMY_COUNTER);
}

