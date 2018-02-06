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
 * Author: 2012 Gianluca Franchino.
 */

#include <stdio.h>
#include <string.h>

#include "ee.h"
#include "ee_irq.h"

/* OSEK COM headers*/
#include "com/ee_com.h"
#include "com/com/inc/ee_cominit.h"
#include "com/com/inc/ee_api.h"

#include "umsgtype.h"

#include "console_serial.h"

console_descriptor_t *my_console_1;
#define MY_FIRST_SERIAL 1
#define MY_FIRST_CONSOLE 0

#define CONSOLE_OUT(msg)\
	console_write(MY_FIRST_CONSOLE, (const EE_UINT8*) msg, strlen(msg))


// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							


/* insert a stub for the functions not directly supported by __FP__ */
#ifdef __FP__
__INLINE__ void __ALWAYS_INLINE__ DisableAllInterrupts(void)
{
	EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EnableAllInterrupts(void)
{
	EE_hal_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ TerminateTask(void)
{
}

#define OSDEFAULTAPPMODE 1
__INLINE__ void __ALWAYS_INLINE__ StartOS(int i)
{
}
#endif

/* A few counters incremented at each event 
 * (alarm, button press or task activation...)
 */
volatile int button_fired=4;
volatile int task1_fired=0;
volatile int task2_fired=0;
volatile int task3_fired=0;
volatile int task4_fired=0;

/* 
 * The following structure, defined in umstype.h, is used to store
 * the status of the first 4 leds of the demoboard
 */ 
led_stat st;

/* Let's remember the led status! 
 * Mutual exclusion on this variable is not included in the demo to make it
 * not too complicated; in general shared variables should be protected using
 * GetResource/ReleaseResource calls
 */
volatile unsigned int led_status = 0;

/*
 led_str is used to print the leds status on the LCD:
	* -> led on.
	_ -> led off.
 
*/
const char* leds_str[] = { 
	"____", "*___", "_*__", "**__",
	"__*_", "*_*_", "_**_", "***_",
	"___*", "*__*", "_*_*", "**_*",
	"__**", "*_**", "_***", "****"
};

/* Let's declare the tasks identifiers */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);

/* just a dummy delay */ 
#define ONEMILLION 1000
static void mydelay(void)
{
	int i,j;
	for (i=0; i<ONEMILLION*4; i++)
		for (j=0; j<1000; j++);
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
void led_blink(int theled)
{
	DisableAllInterrupts();
	led_status |= theled;
	EE_leds(led_status);
	EnableAllInterrupts();

	mydelay();

	DisableAllInterrupts();
	led_status &= ~theled;
	EE_leds(led_status);
	EnableAllInterrupts();
}



/* ************************************************** */
/* ***** Function  StartCOMExtension(void); **** */
/* ************************************************** */

StatusType StartCOMExtension (void)
{
	st.led[0] = 0;
	st.led[1] = 1;
	st.led[2] = 0;
	st.led[3] = 1;
	
	return E_OK;

}
    
/* Program the Timer1 peripheral to raise interrupts */

void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0x9c40;		/* Load the Period register wit the value 0x9c40 (1ms @ 40MIPS)	*/
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

volatile int timer_divisor = 0;

ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();
	
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * Handle button_pio interrupts.
 */
static void handle_button_interrupts(void)
{
/*
 * -If S1 is pressed, then activate Task1 (one shot).
 * -If S2 is pressed then set AlarmTask 1 to activate
 * task1 periodically every 2 seconds.
 * - If S3 is pressed then set AlarmTask 1 to activate
 * task1 periodically every 0.5 seconds.
 * -if S4 is pressed then cancel AlarmTask1.
 */
	if (EE_button_get_S1()) {
		ActivateTask(Task1);
		button_fired = 1;
	} else if (EE_button_get_S2()) {
				CancelAlarm(AlarmTask1);
				SetRelAlarm(AlarmTask1, 1000,  2000);
				button_fired = 2;
			} else if (EE_button_get_S3()) {
						CancelAlarm(AlarmTask1);
						SetRelAlarm(AlarmTask1, 500,  500);
						button_fired = 3;
					} else if (EE_button_get_S4()) {
						CancelAlarm(AlarmTask1);
						button_fired = 4;
					}
}

/* Task1: just send the leds status */
TASK(Task1)
{
	static unsigned char led_cnt = 0;
	
	task1_fired++;

	/* If it is the first task activation send the initial 
	 * value of Led_SMsg (that provided by StartCOMExtension()),
	 * else update the message value with led_cnt.
	 */
	if (task1_fired == 1) {
		SendMessage(Led_SMsg, &st);
	} else {
		st.led[0] = led_cnt & 0x1;
		st.led[1] = (led_cnt & 0x2) >> 1;
		st.led[2] = (led_cnt & 0x4) >> 2;
		st.led[3] = (led_cnt & 0x8) >> 3;
		
		SendMessage(Led_SMsg, &st);
		
		led_cnt = (led_cnt + 1) % 16;
	}
	/*Blink the 6-th led (led 5) */
	led_blink(0x20);
	
	TerminateTask();
}

/* Task2: receive and update leds status */
TASK(Task2)
{	
	led_stat rx_st;
	
	task2_fired++;
  
	ReceiveMessage(Led_RMsg, &rx_st);
		
	DisableAllInterrupts();
	led_status = rx_st.led[0] | (rx_st.led[1] << 1) |
				(rx_st.led[2] << 2) | (rx_st.led[3] << 3);
	EE_leds(led_status);
	EnableAllInterrupts();
	
	/*Blink the 7-th led (led 6) */
	led_blink(0x40);
	
	TerminateTask();
}

/*Declare a buffer for the console*/
char str[80];

/* Task3: Print the counters on the LCD and the console (UART) */
TASK(Task3)
{
	led_stat rx_st;
	EE_INT8 ret_val;
	static EE_UINT8 ok_cnt = 0, no_msg_cnt = 0, lim_cnt = 0, toggle = 0;
	
	ret_val = ReceiveMessage(Led_RMsg_Copy, &rx_st);
	
	/*Blink the 8-th led (led 7) */
	led_blink(0x80);
	
	CONSOLE_OUT("***********************************************************");
	CONSOLE_OUT("********\r\n");
	CONSOLE_OUT("ReceiveMessage(Led_RMsg_Copy, &rx_st) -> ret_val:");
	
	if (ret_val == E_COM_NOMSG) {
		sprintf(str, " E_COM_NOMSG (%d)\r\n", ret_val);
		CONSOLE_OUT(str);
		no_msg_cnt++;
		} else if (ret_val == E_COM_LIMIT) {
			sprintf(str, " E_COM_LIMIT (%d)\r\n", ret_val);
			CONSOLE_OUT(str);
			sprintf(str, "Led_RMsg_Copy: LED0=%d, LED1=%d, LED2=%d, LED3=%d\r\n",
					rx_st.led[0], rx_st.led[1], rx_st.led[2], rx_st.led[3] );
			CONSOLE_OUT(str);
			lim_cnt++;
		} else if (ret_val == E_OK) {
				sprintf(str, " E_OK (%d)\r\n", ret_val);
				CONSOLE_OUT(str);
				sprintf(str, "Led_RMsg_Copy: LED0=%d, LED1=%d, LED2=%d, LED3=%d\r\n",
						rx_st.led[0], rx_st.led[1], rx_st.led[2], rx_st.led[3] );
				CONSOLE_OUT(str);
				ok_cnt++;
			} else {
				sprintf(str, "ReceiveMessage(Led_RMsg_Copy, &rx_st) -> ret_val:\
						UNKNOW (%d)\r\n", ret_val);
				CONSOLE_OUT(str);				
			}
	
	sprintf(str, "Leds status: 0x%X\r\n", led_status);
	CONSOLE_OUT(str);
	
	sprintf(str, "MSG_SENT: %d\r\nE_OK: %d\r\nE_COM_LIMIT: %d\r\n",
		task1_fired, ok_cnt, lim_cnt);
	CONSOLE_OUT(str);
	sprintf(str, "E_COM_NOMSG: %d\r\nLast button pressed: S%d\r\n", 
		no_msg_cnt, button_fired);
	CONSOLE_OUT(str);
		CONSOLE_OUT("***********************************************************");
	CONSOLE_OUT("********\r\n\r\n\r\n");
	


	/*Print the number of message sent*/
	EE_lcd_puts(" TX: ");
	EE_lcd_putc(((task1_fired%1000)/100)+'0');
	EE_lcd_putc(((task1_fired%100)/10)+'0');
	EE_lcd_putc((task1_fired%10)+'0');
  
	/*Print the number the leds status (From led0 to led3)*/
	EE_lcd_puts(" ");
	EE_lcd_puts((char *)leds_str[led_status & 0x0F]);

	/*Print the value returned by ReceiveMessage*/
	if (ret_val == E_OK)
		EE_lcd_puts(" OK");
	else if (ret_val == E_COM_LIMIT)
		EE_lcd_puts(" FU");
		else if (ret_val == E_COM_NOMSG)
			EE_lcd_puts(" No");
			else
				EE_lcd_puts(" ?");
	
	/*Print the the statistics concerning ReceiveMessage()*/
	EE_lcd_line2();
	EE_lcd_puts(" OK: ");
	EE_lcd_putc(((ok_cnt%1000)/100)+'0');
	EE_lcd_putc(((ok_cnt%100)/10)+'0');
	EE_lcd_putc((ok_cnt%10)+'0');
  
	if (toggle) {
		EE_lcd_puts(" Fu: ");
		EE_lcd_putc(((lim_cnt%1000)/100)+'0');
		EE_lcd_putc(((lim_cnt%100)/10)+'0');
		EE_lcd_putc((lim_cnt%10)+'0');
		toggle = 0;
	} else {
		EE_lcd_puts(" No: ");
		EE_lcd_putc(((no_msg_cnt%1000)/100)+'0');
		EE_lcd_putc(((no_msg_cnt%100)/10)+'0');
		EE_lcd_putc((no_msg_cnt%10)+'0');
		toggle = 1;
	}
	
	EE_lcd_home();
	  
	TerminateTask();
}


/* TaskInit: initialize the COM support */
TASK(TaskInit)
{

	if (StartCOM(LED_DEMO_APPMODE) != E_OK) {
			EE_leds_on();
			while(1);
	}
	/*Activate Task3 periodically to print the statistics on both the LCD 
	 *	and the console (UART)
	 */
	SetRelAlarm(AlarmTask3, 1000,  500);
	
	ActivateTask(Task1);
		
	TerminateTask();
}

  
int main()
{ 
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);
	
	
	/* Init buttons S1, S2, S3 and S4. */
	EE_buttons_init(&handle_button_interrupts, 0b1111);
  
	/* Init leds */
	EE_leds_init();
	EE_demoboard_leds_init();
  
  	/* Console Init */
	my_console_1 = console_serial_config(MY_FIRST_SERIAL, 115200,
						CONSOLE_SERIAL_FLAG_BIT8_NO |
						CONSOLE_SERIAL_FLAG_BIT_STOP1);
	console_init(MY_FIRST_CONSOLE, my_console_1);
	if (console_open(MY_FIRST_CONSOLE) == -1)
		EE_led_on();
	else
		EE_led_off();
  
	/* Init LCD */
	EE_lcd_init();
	EE_lcd_clear();
  
	/* just a nice subliminal welcome message :-) */
	mydelay();
	EE_lcd_puts("I love FLEX &");
	EE_lcd_line2();
	EE_lcd_puts("ERIKA Enterprise");
	EE_lcd_home();
  
	/* Program Timer 1 to raise interrupts */
	T1_program();
	
	/* let's start the multiprogramming environment...*/
	StartOS(OSDEFAULTAPPMODE);
 
	/* now the background activities: in this case, we do nothing. */
	for (;;);
  
	return 0;
}
