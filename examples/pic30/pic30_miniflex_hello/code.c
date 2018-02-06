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

/*
 * Author:
 * CVS: $Id: code.c,v 1.3 2007/03/15 15:33:16 nino Exp $
 */

#include "ee.h"
#include "ee_irq.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"

EE_UINT8 i;
EE_UINT8 msg[30];

EE_UINT16 light;
EE_UINT8 muted = 0;
EE_UINT16 temp;
EE_UINT16 battery;
signed int gx, gy, gz;

_CONFIG1(JTAGEN_OFF & FWDTEN_OFF)
_CONFIG2(FNOSC_PRIPLL & POSCMOD_XT)

/* Program the Timer1 peripheral to raise interrupts */
void T1_program(void)
{
	T1CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR1  = 0;		/* Clear contents of the timer register	*/
	PR1   = 0x3E80;		/* Load the Period register with the value 0x3E80
							to have a tick of 1 ms */
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

TASK(LED_BLINK)
{
	EE_led_toggle();
	
	battery = (EE_UINT16)(EE_battery_monitor_get()*1000);
	temp = (EE_UINT16)EE_temperature_get();
	gx = EE_accelerometer_getx()*1000;
	gy = EE_accelerometer_gety()*1000;
	gz = EE_accelerometer_getz()*1000;
	
	light = EE_light_get();
	
	EE_buzzer_set_freq(light*5);
	if (gz < 0)
		EE_buzzer_unmute();
	else
		EE_buzzer_mute();
}

TASK(UART_ECO)
{
	i = 0;
		while (msg[i] != '\0' && i < 30)
			EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) msg[i++] );
			
	EE_uart_write_byte( EE_UART_PORT_1, 'L');
	EE_uart_write_byte( EE_UART_PORT_1, ':');
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (light/100)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((light%100)/10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (light%10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '\n');
	EE_uart_write_byte( EE_UART_PORT_1, '\r');

	EE_uart_write_byte( EE_UART_PORT_1, 'T');
	EE_uart_write_byte( EE_UART_PORT_1, ':');
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (temp/100)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((temp%100)/10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (temp%10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '\n');
	EE_uart_write_byte( EE_UART_PORT_1, '\r');

	EE_uart_write_byte( EE_UART_PORT_1, 'B');
	EE_uart_write_byte( EE_UART_PORT_1, ':');
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (battery/1000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '.');
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((battery%1000)/100)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((battery%100)/10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (battery%10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '\n');
	EE_uart_write_byte( EE_UART_PORT_1, '\r');

	EE_uart_write_byte( EE_UART_PORT_1, 'X');
	EE_uart_write_byte( EE_UART_PORT_1, ':');
	if (gx < 0) {
		EE_uart_write_byte( EE_UART_PORT_1, '-');	
	} else
		EE_uart_write_byte( EE_UART_PORT_1, '+');	
	EE_uart_write_byte( EE_UART_PORT_1, (gx/10000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, ((gx%10000)/1000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '.');
	EE_uart_write_byte( EE_UART_PORT_1, ((gx%1000)/100)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, ((gx%100)/10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (gx%10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '\n');
	EE_uart_write_byte( EE_UART_PORT_1, '\r');

	EE_uart_write_byte( EE_UART_PORT_1, 'Y');
	EE_uart_write_byte( EE_UART_PORT_1, ':');
	if (gy < 0)
		EE_uart_write_byte( EE_UART_PORT_1, '-');	
	else
		EE_uart_write_byte( EE_UART_PORT_1, '+');	
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (gy/10000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((gy%10000)/1000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '.');
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((gy%1000)/100)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((gy%100)/10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (gy%10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '\n');
	EE_uart_write_byte( EE_UART_PORT_1, '\r');

	EE_uart_write_byte( EE_UART_PORT_1, 'Z');
	EE_uart_write_byte( EE_UART_PORT_1, ':');
	if (gz < 0)
		EE_uart_write_byte( EE_UART_PORT_1, '-');	
	else
		EE_uart_write_byte( EE_UART_PORT_1, '+');	
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (gz/10000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((gz%10000)/1000)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '.');
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((gz%1000)/100)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) ((gz%100)/10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) (gz%10)+'0' );
	EE_uart_write_byte( EE_UART_PORT_1, '\n');
	EE_uart_write_byte( EE_UART_PORT_1, '\r');
}


void uart_int_rx(EE_UINT8 data)
{
	if (U1STAbits.OERR || U1STAbits.FERR || U1STAbits.PERR) {
		if (U1STAbits.OERR)
			U1STAbits.OERR = 0;

	} else {
		EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) data);
	}
}

int main(void)
{
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Remap pins */

	//ASM_UNLOCK_LOCK_RPN();
	// Alternative way: __builtin_write_OSCCONL(OSCCON & 0xbf)
	__builtin_write_OSCCONL(OSCCON & 0xbf);

	/* Assign SPI1 input pins */
	RPINR20bits.SDI1R = 23; //SDI1 on RP23

	/* Assign SPI2 output pins */
	RPOR10bits.RP20R = 9; //SS1 on RP20
	RPOR10bits.RP21R = 8; //SCK1 on RP21
	RPOR11bits.RP22R = 7; //SDO1 on RP22

	/* Assign UART1 input pins */
	RPINR18bits.U1RXR = 25; //U1RX on RP25
	/* Assign UART1 output pins */
	RPOR12bits.RP24R = 3; //U1TX on RP24
	
	/* Assign OC1 output pin */
	RPOR4bits.RP9R = 18; //OC1 on RP9

	/* Lock pin configuration registers */
	//ASM_UNLOCK_LOCK_RPN();
	// Alternative way: __builtin_write_OSCCONL(OSCCON | 0x40)
	__builtin_write_OSCCONL(OSCCON | 0x40);


	/* Application Init */

	// Init SysLed
	EE_leds_init();

	// Init Buzzer
	EE_buzzer_init();
	
	// Init Analog
	EE_analog_init();
	EE_battery_monitor_init();
	EE_temperature_init();
	EE_accelerometer_init();
	EE_light_init();

	// Init UART Port
	EE_uart_init(EE_UART_PORT_1, 115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1, EE_UART_CTRL_SIMPLE);
	EE_uart_set_rx_callback(EE_UART_PORT_1, uart_int_rx, EE_UART_RX_INT_SINGLE);
	sprintf(msg, "Hello World from MiniFlex!\r\n");

	i = 0;
	while (msg[i] != '\0' && i < 30)
		EE_uart_write_byte( EE_UART_PORT_1, (unsigned char) msg[i++] );

	SetRelAlarm(LED_ALARM, 1000, 1000); /* Led on/off task*/
	SetRelAlarm(UART_ALARM, 1000, 1000);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

	return 0;
}
