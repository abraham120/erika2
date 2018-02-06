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
 * version 2 along with ERIKA Enerprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/**
    Author: Antonio Camacho Santiago, 2010, 
            Automatic Control Department,
            Technical University of Catalonia.
    Author: Dario Di Stefano, 2011, 
            Evidence Srl
*/

/*
 * Description: Two boards are needed to communicate via CAN bus
 *              This board implements the CAN receiver code.
 *              TaskReceive is activated inside the CAN interrupt handler (ISR2 type),
 *              only when message identifier match id=3.
 *              The code inside the task toggles the orange led and send strings using
 *              the UART serial interface.
 *              4 different filters allows different RAM variables:
 *                - rx_ecan1message1 for id=1
 *                - rx_ecan1message2 for id=2
 *                - rx_ecan1message3 for id=3 (Activates TaskReceive)
 *                - rx_ecan1message4 for id=99
*/


#include "ee.h"
#include "ee_irq.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"
#include "string.h"
#include "stdio.h"
#include <stdarg.h>


_FOSCSEL(FNOSC_PRIPLL);          // Primary (XT, HS, EC) Oscillator with PLL
_FOSC(OSCIOFNC_ON & POSCMD_XT);  // OSC2 Pin Function: OSC2 is Clock Output
                                 // Primary Oscillator Mode: XT Crystal
_FWDT(FWDTEN_OFF);               // Watchdog Timer Enabled/disabled by user software
_FGS(GCP_OFF);                   // Disable Code Protection


// CAN Messages in RAM
ee_ecan_mID rx_ecan1message1; //RX message for id=1
ee_ecan_mID rx_ecan1message2; //RX message for id=2
ee_ecan_mID rx_ecan1message3; //RX message for id=3
ee_ecan_mID rx_ecan1message4; //RX message for id=99
ee_ecan_mID tx_ecan1message;  //TX Transmission message

/**
 *  Function: T1_program(void)
 *  Description: This function enables Timer1 to raise interrupts.
 */
void T1_program(void)
{
	T1CON = 0;          /* Stops the Timer1 and reset control register */
	TMR1  = 0;          /* Clear contents of the timer register	*/
	PR1   = 0x9c40;     /* Load the Period register with the value of 1ms */
	IPC0bits.T1IP = 5;  /* Set Timer1 priority to 1. Higher values set higher
	                     * priorities */
	IFS0bits.T1IF = 0;  /* Clear the Timer1 interrupt status flag */
	IEC0bits.T1IE = 1;  /* Enable Timer1 interrupts	*/
	T1CONbits.TON = 1;  /* Start Timer1 with prescaler settings at 1:1 and
	                     * clock source set to the internal instruction cycle*/
}

/**
 *  Function: T1_clear(void)
 *  Description: This function clears Timer1 interrupt status flag.
 */
void T1_clear(void)
{
	IFS0bits.T1IF = 0;
}


/** This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
  * The ISR simply calls CounterTick to implement the timing reference. 
  */
ISR2(_T1Interrupt)
{
	/* clear the interrupt source */
	T1_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/**
 *  Function: print_string(char *str)
 *  Description: This function sends a string using UART.
 */
void print_string(char *str)
{
	int len, i;
	len = strlen(str);
	for(i=0; i<len; i++)
		EE_uart_write_byte(EE_UART_PORT_1, str[i]);
}

/** 
 *  TaskReceive: When id=3, CAN interrupt callback activates 
 *  this task to toggle the led 
 */
TASK(TaskReceive)
{
	char str[32];
	
	/* Toggle orange led */
	LATBbits.LATB14 ^= 1;
	
	/* Print the received message */
	sprintf(str,"received message: %c%c%c%c%c%c%c%c\n", rx_ecan1message3.data[0],
	                                                    rx_ecan1message3.data[1],
	                                                    rx_ecan1message3.data[2],
	                                                    rx_ecan1message3.data[3],
	                                                    rx_ecan1message3.data[4],
	                                                    rx_ecan1message3.data[5],
	                                                    rx_ecan1message3.data[6],
	                                                    rx_ecan1message3.data[7]);
	print_string(str);
}

/**
 *  Function: eCAN1_cbk(void)
 *  Description: See below
 */
void eCAN1_cbk(void);

/** 
 *  Function: eCAN1_init(void)
 *  Description: This function initializes CAN controller and configures the RX filters.
 */
void eCAN1_init(void)
{
	/* Initialize enhanced CAN bus number 1 */
	EE_ecan1_Initialize(); 
	EE_ecan1_WriteRxAcptMask(0x0,0x1FFFFFFF, 0,0x1);
	EE_ecan1_WriteRxAcptFilter(0x0,1,0x1,0x1,0x0);  //id=1 to buffer 1
	EE_ecan1_WriteRxAcptFilter(0x1,2,0x1,0x2,0x0);  //id=2 to buffer 2
	EE_ecan1_WriteRxAcptFilter(0x2,3,0x1,0x3,0x0);  //id=3 to buffer 3
	EE_ecan1_WriteRxAcptFilter(0x3,99,0x1,0x4,0x0); //id=99 to buffer 4
	EE_ecan1_set_ISR_callback(&eCAN1_cbk);
}

/** 
 * Main entry point. This code initializes software and hardware,
 * fire alarms, and implement background activities 
 */
int main(void)
{
	/* Clock setup for 40MIPS */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Init led */
	EE_leds_init();
	/* Program Timer 1 to raise interrupts */
	T1_program();
	/* UART1 Init */
	EE_uart_init(EE_UART_PORT_1, 57600, EE_UART_BIT_STOP_1 | EE_UART_BIT8_NO, EE_UART_CTRL_SIMPLE);
	/* Configure enhanced CAN 1 */
	eCAN1_init();

	/* Forever loop: background activities (if any) should go here */
	while(1)
		;

	return 0;
}

/**
 *  Function: eCAN1_cbk(void)
 *  Description: CAN bus 1 Interrupt callback, ISR2 type.
 */
void eCAN1_cbk(void)
{
	static int ecan1_cbk_counter = 0;
	ecan1_cbk_counter++;
	
	/* Transmission interrupt (nothing to be done but clear flag) */
	if(C1INTFbits.TBIF)
		C1INTFbits.TBIF = 0;

	/*Reception interrupt, different code for different filtered id's */
	if(C1INTFbits.RBIF) {

		//Filter 1(id=ID_PLANT): Sensor to controller message
		if(C1RXFUL1bits.RXFUL1==1) {
			/* Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message1.buffer=1;
			C1RXFUL1bits.RXFUL1=0;
			EE_ecan1_Rx(&rx_ecan1message1);
			C1INTFbits.RBIF = 0;
			/* Custom code for incoming id=1 goes here */
			/* .. */
		}

		//Filter 2(id=ID_PLANT+1): Controller to Actuator message
		if(C1RXFUL1bits.RXFUL2==1) {
			/*Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message2.buffer=2;
			C1RXFUL1bits.RXFUL2=0;
			EE_ecan1_Rx(&rx_ecan1message2);
			C1INTFbits.RBIF = 0;
			/* Custom code for incoming id=2 goes here */
			/* .. */
		}

		//Filter 3(id=ID_PLANT+2): Controller updated reference (supervision)
		if(C1RXFUL1bits.RXFUL3==1) {
			/*Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message3.buffer=3;
			C1RXFUL1bits.RXFUL3=0;
			EE_ecan1_Rx(&rx_ecan1message3);
			C1INTFbits.RBIF = 0;
			/* Custom code for incoming id=3 goes here */
			ActivateTask(TaskReceive);
		}

		//Filter 4(id=99): Reserved for future improvements
		if(C1RXFUL1bits.RXFUL4==1) {
			/* Tells rxECAN1 the buffer to pass from DMA to RAM */
			rx_ecan1message4.buffer=4;
			C1RXFUL1bits.RXFUL4=0;
			EE_ecan1_Rx(&rx_ecan1message4);
			C1INTFbits.RBIF = 0;
			/* Custom code for incoming id=99 goes here */
			/* .. */
		}

	}
}
