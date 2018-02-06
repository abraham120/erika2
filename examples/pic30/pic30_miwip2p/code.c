/*
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */

/*
 * File: code.c
 * Author: Gianluca Franchino (Abbreviation GF).
 * Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
 * Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
 * Date: 03/20/2009.
 */


#include "ee.h"
#include "ee_irq.h"

#include "P2PDefs.h"
#include "MRF24J40.h"
#include "P2P.h"
#include "SymbolTime.h"

#include "console_serial.h"


// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystal
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);



extern void int_service(void);
extern void PrintChar(EE_UINT8 to_print);


console_descriptor_t *console_des;

EE_UINT8 myChannel = CHANNEL_25;

/*******************************************************************/
// the following two variable arrays are the data to be transmitted
// in this demo. They are bit map of English word "HELLO" and "P2P"
// respectively.
/*******************************************************************/
const unsigned char Hello[100] =
{
    0xB2,0x20,0xB2,0x20,0xB2,0xB2,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0x20,
    0xB2,0xB2,0x20,0x0D,0x0A,0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,
    0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x0D,0x0A,0xB2,0xB2,0xB2,0x20,0xB2,
    0xB2,0xB2,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,0x0D,0x0A,
    0xB2,0x20,0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0xB2,0x20,0x20,0xB2,
    0x20,0x20,0xB2,0x0D,0x0A,0xB2,0x20,0xB2,0x20,0xB2,0xB2,0xB2,0x20,0xB2,0xB2,
    0xB2,0xB2,0xB2,0xB2,0x20,0xB2,0xB2,0x20,0x0D,0x0A
};
const unsigned char P2P[65] =
{
    0xB2,0xB2,0xB2,0x20,0xB2,0xB2,0xB2,0x20,0xB2,0xB2,0xB2,0x0D,0x0A,
    0xB2,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0xB2,0x20,0xB2,0x0D,0x0A,
    0xB2,0xB2,0xB2,0x20,0xB2,0xB2,0xB2,0x20,0xB2,0xB2,0xB2,0x0D,0x0A,
    0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0x20,0xB2,0x20,0x20,0x0D,0x0A,
    0xB2,0x20,0x20,0x20,0xB2,0xB2,0xB2,0x20,0xB2,0x20,0x20,0x0D,0x0A
};

void T1_clear(void);

EE_UINT16 now_count = 0;

/*
 * This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
	/* count the interrupts for button debounce operations */
	now_count++;
}


/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0xFFFF;		/* Load the Period register with the value 0xffff	*/
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

#define DEBOUNCE_TIME 200 /* DEBOUNCE time is 200 ms */

EE_UINT8 msg_flag = 0, flag  = 1;
EE_UINT16 last_press_time[3] = {0, 0, 0};

/*
 * my_button is the callback function executed when
 * a button is pressed
 */
void my_button(void)
{
	EE_INT16 press_diff;

	if (EE_button_get_S1() == 1) {
		press_diff = now_count - last_press_time[0];
		last_press_time[0] = now_count;

		if (press_diff < 0)
			press_diff += 0xFFFF;
		if (press_diff >= DEBOUNCE_TIME)
			msg_flag = (msg_flag + 1) % 2;
	} else
		if(EE_button_get_S2() == 1) {

			press_diff = now_count - last_press_time[1];
			last_press_time[1] = now_count;

			if (press_diff < 0)
				press_diff += 0xFFFF;
			if (press_diff >= DEBOUNCE_TIME)
				ActivateTask(TaskSend);

		} else {
			if(EE_button_get_S3() == 1) {

				press_diff = now_count - last_press_time[2];
				last_press_time[2] = now_count;
				if (press_diff < 0)
					press_diff += 0xFFFF;
				if (press_diff >= DEBOUNCE_TIME) {
					if(flag) {
						flag = 0;
						SetRelAlarm(AlarmSend, 50, 250);
					} else {
						flag = 1;
						CancelAlarm(AlarmSend);
					}
				}
			}
		}
}

/*
 * radio_isr is the callback function executed when
 * the radio module issues an interrupt.
 */
void radio_isr(void)
{
	ActivateTask(TaskInt);
}

/*
 * This function initializes the flex board
 * in order to manage buttons and leds of the demo board.
 * Furthermore, it initializes the radio module.
 */
void flex_demoboard_init()
{
	/* Initialize buttons 1, 2 and 3 */
	EE_buttons_init(&my_button, 0x07);

	/* Initialize leds */
	EE_demoboard_leds_init();

	/* Initialize radio module */
	EE_picdemz_init(&radio_isr);

}

/*
 * This task sends a message through the MiWi P2P stack.
 */
TASK(TaskSend)
{
	EE_INT16 i;


	FlushTx();

	if( msg_flag ) {
		for(i = 0; i < 100; i++)
			{
				WriteData(Hello[i]);
			}

			BroadcastPacket(myPANID, FALSE, FALSE);
	} else {
		for(i = 0; i < 65; i++)
		    {
		        WriteData(P2P[i]);
		    }

		    UnicastConnection(0, FALSE, TRUE);

	}

}

EE_INT16 tog=0;

/*
 * This task prints out on the console a message received through the MiWi P2P
 * stack.
 */
TASK(TaskRec)
{
	EE_INT16 i;

	GetResource(S1);
	console_write(MY_FIRST_CONSOLE, (EE_UINT8*) "\r\nReceived Packet ",
			strlen("\r\nReceived Packet "));
	ReleaseResource(S1);

    #ifdef ENABLE_SECURITY
         if( rxFrame.flags.bits.security )
         {
        	 GetResource(S1);
             console_write(MY_FIRST_CONSOLE, (EE_UINT8*) "Secured ", strlen("Secured "));
             ReleaseResource(S1);
         }
     #endif
     #ifndef TARGET_SMALL
         if( rxFrame.flags.bits.broadcast )
         {
        	 GetResource(S1);
             console_write(MY_FIRST_CONSOLE, (EE_UINT8*) "Broadcast with RSSI ",
            		 strlen("Broadcast with RSSI "));
             ReleaseResource(S1);
         }
         else
         {
        	 GetResource(S1);
        	 console_write(MY_FIRST_CONSOLE, (EE_UINT8*) "Unicast with RSSI ",
        			 strlen("Broadcast with RSSI "));
        	 ReleaseResource(S1);
         }
         PrintChar(rxFrame.PacketRSSI);
         GetResource(S1);
         console_write(MY_FIRST_CONSOLE, (EE_UINT8*) " from ", strlen(" from "));
         ReleaseResource(S1);
         for(i = 0; i < 8; i++)
         {
             PrintChar(rxFrame.SourceLongAddress[7-i]);
         }
     #endif
         GetResource(S1);
         console_write(MY_FIRST_CONSOLE, (EE_UINT8*) ": \r\n", strlen(": \r\n"));
         console_write(MY_FIRST_CONSOLE, rxFrame.PayLoad,rxFrame.PayLoadSize);
         ReleaseResource(S1);

     /* Toggle LED1 to indicate receiving a packet. */
     if( !tog ) {
    	 EE_led_1_on();
    	 tog=1;
     } else {
    	 EE_led_1_off();
    	 tog=0;
     }

     DiscardPacket();
}

/*
 * This task is activated when an interrupt is issued by the radio transceiver.
 */

TASK(TaskInt)
{
	int_service();
}

/*
 * This task checks for a message arriving, and if it is so, it activates
 * TaskRec.
 */
TASK(TaskMiWiOP)
{
	if( ReceivedPacket() )
			ActivateTask(TaskRec);
}


/*
 * Application main function
 */
int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	EE_INT16 i;

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Initialize the board */
	flex_demoboard_init();

	/* Initialize the console */
	console_des = console_serial_config(MY_FIRST_SERIAL, 115200,
						CONSOLE_SERIAL_FLAG_BIT8_NO |
						CONSOLE_SERIAL_FLAG_BIT_STOP1);
	console_init(MY_FIRST_CONSOLE, console_des);
	console_open(MY_FIRST_CONSOLE);

	console_write(MY_FIRST_CONSOLE, (EE_UINT8*) "\r\nStarting P2P Demo...",
					strlen("\r\nStarting P2P Demo..."));


	/* Switch off all leds */
	EE_led_0_off();

	/* MiWi-P2P initialization */
	P2PInit();

	SetChannel(myChannel);

	EnableNewConnection();

	i = CreateNewConnection(2);

	#ifdef ENABLE_DUMP
	DumpConnection(i);
	#endif

	/* Turn on LED 0 to indicate P2P connection established */
	EE_led_0_on();

	/*
	* This alarm activates, every 5 ms, the TaskMiWiOP task which
	* manages the MiWi-P2P protocol.
	*/
	SetRelAlarm(AlarmProt, 5, 5);

	/* Forever loop: background activities (if any) should go here */
	for (;;) {
	}

	return 0;
}
