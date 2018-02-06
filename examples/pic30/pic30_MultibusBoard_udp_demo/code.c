/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * code.c
 */

#include "ee.h"
#include "ee_irq.h"
#include "flex_udp.h"

// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL( FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT( FWDTEN_OFF);
// Disable Code Protection
_FGS( GCP_OFF);

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void) {
	T1CON = 0; /* Stops the Timer1 and reset control reg	*/
	TMR1 = 0; /* Clear contents of the timer register	*/
	PR1 = 0x9C40; /* Load the Period register wit the value 0xffff	*/
	IPC0bits.T1IP = 5; /* Set Timer1 priority to 1		*/
	IFS0bits.T1IF = 0; /* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T1IE = 1; /* Enable Timer1 interrupts		*/
	T1CONbits.TON = 1; /* Start Timer1 with prescaler settings at 1:1
	 * and clock source set to the internal
	 * instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T1_clear(void) {
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

BYTE myUDP_rx[UDP_PKG_LEN];	// buffer for UDP reception
BYTE myUDP_tx[UDP_PKG_LEN];	// buffer for UDP transmission

void UDP_config(void)
{
    int i = 0;
    //TRISAbits.TRISA14=0;
   	UDP_flex_port 			= 9760;				// FLEX SERVER PORT NUMBER
    UDP_pc_port 			= 9761;				// PC SERVER PORT NUMBER
    UDP_remote.IPAddr.v[0]	= 192;				// dest_address byte 1
    UDP_remote.IPAddr.v[1]	= 168;				// dest_address byte 2
    UDP_remote.IPAddr.v[2]	= 0;				// dest_address byte 3
    UDP_remote.IPAddr.v[3]	= 1;				// dest_address byte 4
    UDP_remote.MACAddr.v[0] = 0;	// 0x00;
    UDP_remote.MACAddr.v[1] = 0;	// 0x1E;
    UDP_remote.MACAddr.v[2] = 0;	// 0x33;
    UDP_remote.MACAddr.v[3] = 0;	// 0xC9;
    UDP_remote.MACAddr.v[4] = 0;	// 0xD6;
    UDP_remote.MACAddr.v[5] = 0;	// 0xAA;

    //UDP_buf_size 			= block->ipar[0];	// Number of elements in the rx buffer.
    for(i=0;i<UDP_PKG_LEN;i++)
    {
		myUDP_rx[i] = 0;
		myUDP_tx[i] = 0;
    }
}

int UDP_receive(void)
{
	if(UDP_Buffer_Getmsg(&UDP_rx_buffer, myUDP_rx, UDP_BUF_SIZE))
		return 1;
	else
		return -1;
}

int UDP_send(void)
{
    return UDP_Buffer_Putmsg(&UDP_tx_buffer, myUDP_tx, UDP_BUF_SIZE);
}

#define FLEX_LED_CONFIG()	TRISBbits.TRISB14 = 0;
#define FLEX_LED_ON_OFF()	LATBbits.LATB14 ^= 1;
#define FLEX_LED_ON()		LATBbits.LATB14 = 1;
#define FLEX_LED_OFF()		LATBbits.LATB14 = 0;


int main(void) {
	/* Clock setup for 40 MHz */
	CLKDIVbits.DOZEN = 0;
	CLKDIVbits.PLLPRE = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV = 78;
	while (OSCCONbits.LOCK != 1)
		;

	/* FLEX Led */
	FLEX_LED_CONFIG();
	FLEX_LED_OFF();

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* myTask */
	FLEX_LED_ON();
	SetRelAlarm(myAlarm, 1000, 1000);

	/* UDP task */
	UDP_config();
	ActivateTask(UDP_TASK);

	/* Forever loop: background activities (if any) should go here */
	for (;;)
		;
	return 0;
}

TASK(myTask) {
	int i;
	FLEX_LED_ON_OFF();
	UDP_send();
	if(UDP_receive() >= 0)
		for(i=0; i<UDP_PKG_LEN; i++)
		   	myUDP_tx[i] = myUDP_rx[i];
}
