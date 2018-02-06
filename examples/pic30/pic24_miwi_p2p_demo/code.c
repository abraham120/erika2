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

#include <stdio.h>

#include "ee.h"
#include "ee_irq.h"

#include "console_serial.h"

#include "ConfigApp.h"
//#include "Common\Console.h"
#include "WirelessProtocols/P2P/P2P.h"
#include "Transceivers/Transceivers.h"
#include "Common/SymbolTime.h"
#include "Transceivers/Security.h"
#include "WirelessProtocols/MCHP_API.h"

_CONFIG1(JTAGEN_OFF & FWDTEN_OFF)
_CONFIG2(FNOSC_PRIPLL & POSCMOD_XT)



#ifndef MY_FIRST_SERIAL
#define MY_FIRST_SERIAL 0
#endif

#ifndef MY_FIRST_CONSOLE
#define MY_FIRST_CONSOLE 0
#endif

#define FIRST_MINIFLEX   0x01
#define SECOND_MINIFLEX  0x02

#define CONSOLE_OUT(msg)     \
	console_write(MY_FIRST_CONSOLE, (const EE_UINT8*) msg, strlen(msg))


#if ADDITIONAL_NODE_ID_SIZE > 0
    BYTE AdditionalNodeID[ADDITIONAL_NODE_ID_SIZE] = {FIRST_MINIFLEX};
#endif

console_descriptor_t *my_console_1;
EE_UINT16 TxNum, RxNum;
EE_UINT8 myChannel = 25;

EE_UINT16 light;
EE_UINT16 temp;
EE_UINT16 battery;
EE_INT16 gx, gy, gz;


extern void PrintDec(EE_UINT8 to_print);
extern void PrintChar(EE_UINT8 to_print);

extern void mrf24j40_isr(void);


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

/*
 * radio_isr is the callback function executed when
 * the radio module issues an interrupt.
 */
void radio_isr(void)
{
	ActivateTask(TaskInt);
}

int board_init(void)
{
	__builtin_write_OSCCONL(OSCCON & 0xbf);

	/* Assign UART1 input pins */
	RPINR18bits.U1RXR = 25; //U1RX on RP25
	/* Assign UART1 output pins */
	RPOR12bits.RP24R = 3; //U1TX on RP24

	/* Lock pin configuration registers */

	//__builtin_write_OSCCONL(OSCCON | 0x40);


	EE_miniflex_radio_init(&radio_isr);

	EE_leds_init();

	EE_analog_init();
	EE_battery_monitor_init();
	EE_temperature_init();
	EE_accelerometer_init();
	EE_light_init();


	return 0;
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




TASK(TaskMiWiOP)
{
	if(  MiApp_MessageAvailable() )
				ActivateTask(TaskRec);
}

TASK(TaskInt)
{
	mrf24j40_isr();
}

TASK(TaskRec)
{

	char str[100];
	EE_UINT8 i;

	GetResource(S0);
	CONSOLE_OUT("\r\n");
	ReleaseResource(S0);

	#ifdef ENABLE_SECURITY
	if( rxMessage.flags.bits.secEn ) {
		GetResource(S0);
		CONSOLE_OUT("\r\nSecured ");
		ReleaseResource(S0);
	}

	#endif
	#ifndef TARGET_SMALL
	if( rxMessage.flags.bits.broadcast ) {
		GetResource(S0);
		CONSOLE_OUT("\r\nBroadcast with RSSI ");
		ReleaseResource(S0);
	} else {
		GetResource(S0);
		CONSOLE_OUT("\r\nUnicast with RSSI ");
		ReleaseResource(S0);
	}
	GetResource(S0);
	PrintChar(rxMessage.PacketRSSI);
	ReleaseResource(S0);

	if( rxMessage.flags.bits.srcPrsnt ) {
		GetResource(S0);
		CONSOLE_OUT(" from ");
		ReleaseResource(S0);

		if( rxMessage.flags.bits.altSrcAddr ) {
			GetResource(S0);
			PrintChar(rxMessage.SourceAddress[1]);
			PrintChar(rxMessage.SourceAddress[0]);
			ReleaseResource(S0);
		} else {
			for(i = 0; i < MY_ADDRESS_LENGTH; i++) {
				GetResource(S0);
				PrintChar(rxMessage.SourceAddress[MY_ADDRESS_LENGTH-1-i]);
				ReleaseResource(S0);
			}
		}
	}
	#endif
	sprintf(str,"\r\nTxNum: %u\r\nRxNum: %u", TxNum, ++RxNum );

	GetResource(S0);
	CONSOLE_OUT(str);
	ReleaseResource(S0);


	if (rxMessage.Payload[0] == 0xAA
			&& rxMessage.Payload[1] == 0xFF
			&& rxMessage.Payload[2] == 0xAA && rxMessage.PayloadSize >= 15) {

		GetResource(S0);
		CONSOLE_OUT("\r\nData from remote MinFlex: ");
		ReleaseResource(S0);

		sprintf(str,"\r\nLight: %d [Lux]", ((EE_UINT16)(rxMessage.Payload[3]) << 8)
				+ rxMessage.Payload[4] );

		GetResource(S0);
		CONSOLE_OUT(str);
		ReleaseResource(S0);

		sprintf(str,"\r\nTemp: %d [C degrees]", ((EE_UINT16)(rxMessage.Payload[5]) << 8)
				+ rxMessage.Payload[6] );
		GetResource(S0);
		CONSOLE_OUT(str);
		ReleaseResource(S0);

		sprintf(str,"\r\nBattery: %2.2f [Volts]",
				(double)(((EE_UINT16)(rxMessage.Payload[7]) << 8)
				+ rxMessage.Payload[8]) / 1000.0 );
		GetResource(S0);
		CONSOLE_OUT(str);
		ReleaseResource(S0);

		sprintf(str,"\r\ng_x: %2.2f [#g]",
				(double)(((EE_INT16)(rxMessage.Payload[9] << 8)
				+ rxMessage.Payload[10]) / 1000.0 ) );
		GetResource(S0);
		CONSOLE_OUT(str);
		ReleaseResource(S0);

		sprintf(str,"\r\ng_y: %2.2f [#g]",
				(double)(((EE_INT16)(rxMessage.Payload[11] << 8)
						+ rxMessage.Payload[12]) / 1000.0 ) );
		GetResource(S0);
		CONSOLE_OUT(str);
		ReleaseResource(S0);

		sprintf(str,"\r\ng_z: %2.2f[#g]",
				(double)(((EE_INT16)(rxMessage.Payload[13] << 8)
						+ rxMessage.Payload[14]) / 1000.0 ) );
		GetResource(S0);
		CONSOLE_OUT(str);
		CONSOLE_OUT("\r\n");
		ReleaseResource(S0);

	} else {

		GetResource(S0);
		CONSOLE_OUT("\r\nReceived Packet: ");
		console_write(MY_FIRST_CONSOLE, rxMessage.Payload,
				rxMessage.PayloadSize);
		CONSOLE_OUT("\r\n");
		ReleaseResource(S0);
	}

    MiApp_DiscardMessage();

}

EE_UINT8 first_msg = 1;

TASK (TaskSend)
{

	char str[100];
	EE_UINT8 i;

	if (first_msg) {
		sprintf(str, "\r\nHello! Miniflex powered by Erika is ready ...");
		first_msg = 0;
	} else {
		/* the first three bytes indicates a packet with sensor data */
		str[0] = 0xAA;
		str[1] = 0xFF;
		str[2] = 0xAA;

		GetResource(S1);
		str[3] = (EE_UINT8) (light >> 8);
		str[4] = (EE_UINT8) (light);
		str[5] = (EE_UINT8) (temp >> 8);
		str[6] = (EE_UINT8) (temp);
		str[7] = (EE_UINT8) (battery >> 8);
		str[8] = (EE_UINT8) (battery);
		str[9] = (EE_UINT8) (gx >> 8);
		str[10] = (EE_UINT8) (gx);
		str[11] = (EE_UINT8) (gy >> 8);
		str[12] = (EE_UINT8) (gy);
		str[13] = (EE_UINT8) (gz >> 8);
		str[14] = (EE_UINT8) (gz);
		ReleaseResource(S1);


	}
	MiApp_FlushTx();

	i = 0;
	if (first_msg) {
		while (str[i] != '\0')
			MiApp_WriteData(str[i++]);
	} else {
		while(i < 15)
			MiApp_WriteData(str[i++]);

	}

	if (!MiApp_BroadcastPacket(FALSE)) {
		GetResource(S0);
		CONSOLE_OUT("\r\nTX ERROR");
		ReleaseResource(S0);
	}

	EE_led_toggle();

	++TxNum;

}


TASK(TaskSensRead)
{
	GetResource(S1);
	light = EE_light_get();
	temp = (EE_UINT16)EE_temperature_get();
	battery = (EE_UINT16)(EE_battery_monitor_get()*1000);
	gx = EE_accelerometer_getx()*1000;
	gy = EE_accelerometer_gety()*1000;
	gz = EE_accelerometer_getz()*1000;
	ReleaseResource(S1);

}

int main(void)
{

	EE_UINT8 i = 0;

	char str[80];

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Application Init */

	board_init();

	my_console_1 = console_serial_config(MY_FIRST_SERIAL, 115200,
						CONSOLE_SERIAL_FLAG_BIT8_NO |
						CONSOLE_SERIAL_FLAG_BIT_STOP1);
	console_init(MY_FIRST_CONSOLE, my_console_1);
	console_open(MY_FIRST_CONSOLE);

	EE_led_sys_off();

    /*********************************************************************/
    /* Which protocol to use depends on the configuration in ConfigApp.h */
    /*********************************************************************/

	CONSOLE_OUT("\r\nStarting MiniFlex and Erika Enterprise Demo");
	CONSOLE_OUT("\r\nMiWi(TM) P2P Stack ...");
    MiApp_ProtocolInit();

    if( MiApp_SetChannel(myChannel) == FALSE )
    {
    	CONSOLE_OUT("\r\nSelection of channel ");
        PrintDec(myChannel);
        CONSOLE_OUT(" is not supported in current condition.\r\n");

        return 0;
    }

    /*******************************************************************/
    // Function MiApp_ConnectionMode defines the connection mode. The
    // possible connection modes are:
    //  ENABLE_ALL_CONN:    Enable all kinds of connection
    //  ENABLE_PREV_CONN:   Only allow connection already exists in
    //                      connection table
    //  ENABL_ACTIVE_SCAN_RSP:  Allow response to Active scan
    //  DISABLE_ALL_CONN:   Disable all connections.
    /*******************************************************************/
    MiApp_ConnectionMode(ENABLE_ALL_CONN);


    /*******************************************************************/
    // Function MiApp_EstablishConnection try to establish a new connection
    // with peer device.
    // The first parameter is the index to the active scan result, which is
    //      acquired by discovery process (active scan). If the value of the
    //      index is 0xFF, try to establish a connection with any peer.
    // The second parameter is the mode to establish connection, either direct
    //      or indirect. Direct mode means connection within the radio range;
    //      Indirect mode means connection may or may not in the radio range.
    /*******************************************************************/
    #ifdef ENABLE_HAND_SHAKE
        while( (i = MiApp_EstablishConnection(0xFF, CONN_MODE_DIRECT)) == 0xFF );
    #endif

	sprintf(str, "\r\nConnected Peer on Channel %d", myChannel);
	CONSOLE_OUT(str);//Printf(str);

    /*******************************************************************/
    // Function DumpConnection is used to print out the content of the
    //  Connection Entry on the hyperterminal. It may be useful in
    //  the debugging phase.
    // The only parameter of this function is the index of the
    //  Connection Entry. The value of 0xFF means to print out all
    //  valid Connection Entry; otherwise, the Connection Entry
    //  of the input index will be printed out.
    /*******************************************************************/
	#define EANABLE_DUMP

    #ifdef ENABLE_DUMP
        DumpConnection(i);
    #endif

    EE_led_sys_on();

	SetRelAlarm(AlarmProt, 50, 50);
	SetRelAlarm(AlarmSens, 250, 250);
	SetRelAlarm(AlarmSend, 500, 500);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

	return 0;
}
