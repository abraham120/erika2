/*************************************************************************
*
* Project: ERIKA Enterprise and Open-ZB 
*          ZigBee compliant network stack for ERIKA Enterprise
*
* Coordinators:
*   Giuseppe Lipari     <lipari@sssup.it>
*   Eduardo Tovar       <emt@dei.isep.ipp.pt>
*   Mario Alves         <mjs@isep.ipp.pt>
*
* Authors:
*   Andre Cunha            <andreribeirocunha@gmail.com>
*   Mangesh Chitnis        <m.chitnis@sssup.it>
*   Antonio Romano         <a.romano@sssup.it>
*   Ricardo Severino       <rars@isep.ipp.pt>
*   Paolo Pagano           <p.pagano@sssup.it>
*   Christian Nastasi      <nastasichr@gmail.com>
*
* ReTiS Lab (CEIIC, Scuola Superiore S.Anna - Pisa - Italy)
* IPP-Hurray (Polytechnique Institute of Porto - Portugal)
*
* http://retis.sssup.it
* http://www.hurray.isep.ipp.pt
*
*************************************************************************
*
* Copyright (C) 2008 Andre Cunha, Mangesh Chitnis 
*                    Antonio Romano, Ricardo Severino
*                    Paolo Pagano, Christian Nastasi
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*************************************************************************
*
* CVS: 
*
* $Id: hal_interrupts.c,v 1.21 2008/07/30 16:48:08 chris Exp $
* $Log: hal_interrupts.c,v $
* Revision 1.21  2008/07/30 16:48:08  chris
* Use precompiler define (optional) to specify radio channels
*
* Revision 1.20  2008/07/17 17:37:51  francesco
* Scicos update
*
* Revision 1.19  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.18  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

#include "hal/hal_interrupts.h"
#include "common/console.h"

//Mac.c
extern EE_UINT8 backoff_count;
extern EE_UINT16 timer2_count;

/* Program the Timer2 peripheral to raise interrupts at 320 microseconds*/
void T2_program(void)
{
	T2CON = 0;		/* Stops the Timer1 and reset control reg	*/
	TMR2  = 0;		/* Clear contents of the timer register	*/
	//40MHZ
	PR2   = 0x3200;		/* Load the Period register wit the value ...)*/
	//20MHz
	//PR2 = 0x1600;
	//8MHz
	//PR2 = 0x0A00;

	IPC1bits.T2IP = 5;	/* Set Timer1 priority to 5		*/
	IFS0bits.T2IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC0bits.T2IE = 1;	/* Enable Timer1 interrupts		*/
	T2CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1
				* and clock source set to the internal 
				* instruction cycle			*/
}

/* Clear the Timer1 interrupt status flag */
void T2_clear(void)
{
	IFS0bits.T2IF = 0;
}


void hardware_init()
{
	/*set the I/O pins as all digital */
	//AD1PCFGH = 0xFFFF;
	//AD1PCFGL = 0xFFFF;

    /* Set the I/O pins direction */
	TRIS_RESETn = 0;
	TRIS_VREG_EN = 0;
	TRIS_FIFO = 1;
	TRIS_FIFOP = 1;
	TRIS_CSn = 0;
	TRIS_CCA = 1;
	TRIS_SFD = 1;
	/*Initialize INT0 linked to FIFOP pin*/
	INT1_config();
	
	#ifndef __USE_DEMOBOARD__
	INT0_config();	
	#else
	INT4_config();
	#endif
	hal_console_init(CONSOLE_PORT);
	hal_radio_spi_init(RADIO_SPI2);	
	
	///hal_radio_init();
	
	if (hal_radio_init() != 0) {
		hal_console_out_str("\n\r+ERROR INITIALIZING THE RADIO!");
		
	}
	else {
		hal_console_out_str("\n\r+Radio initialized correctly!");
		
	}
	
//		
	
	#ifndef OPENZB_CHANNEL
	#define OPENZB_CHANNEL 26
	#endif
	
	#ifndef DEVICE_TYPE_COORDINATOR
		hal_set_channel(OPENZB_CHANNEL);	
		hal_set_rx();
	#endif
		//TODO  //EE_UINT8 LogicalChannel,EE_UINT8 CoordAddrMode,EE_UINT16 CoordPANId,EE_UINT32 CoordAddress[],EE_UINT8 CapabilityInformation,EE_UINT8 SecurityEnable)
		//MLME_ASSOCIATE_request(26,0,0x1234,0,0,0);
	
}


/* This is an ISR Type 2 which is attached to the Timer 1 peripheral IRQ pin
 * The ISR simply calls CounterTick to implement the timing reference
 */
ISR2(_T2Interrupt)
{
					
	/* clear the interrupt source */
	T2_clear();

	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/* 
 * This is an ISR Type 2  - SFD.
 */

ISR2 (_INT1Interrupt)
{
	IFS1bits.INT1IF = 0;
	
	backoff_count=0;
	timer2_count = TMR2;
	
	return;
	
}	
/* 
 * This is an ISR Type 2 which is attached to the INT0 IRQ.
 * The ISR controls the EasyBee FIFO status and actives TaskAcquire.
 */
#ifndef __USE_DEMOBOARD__
ISR2 (_INT0Interrupt)
{
	IFS0bits.INT0IF = 0;
	
	ActivateTask(ReadDispatcher);
	
	return;
}

#else

ISR2 (_INT4Interrupt)
{
	IFS3bits.INT4IF = 0;

	ActivateTask(ReadDispatcher);
	
	return;
}

#endif


#ifndef __USE_DEMOBOARD__


void INT0_config(void)
{
	IFS0bits.INT0IF = 0;/* clear the interrupt flag */
	IPC0bits.INT0IP = 0b001; /* set int0 priority to 1 */
	INTCON2bits.INT0EP = 0; /* set interrupt on rising edge */
	IEC0bits.INT0IE = 1; /* enable the interrupt */
}
#else

void INT4_config(void)
{
	IFS3bits.INT4IF = 0;/* clear the interrupt flag */
	IPC13bits.INT4IP = 0b001; /* set int0 priority to 1 */
	INTCON2bits.INT4EP = 0; /* set interrupt on rising edge */
	IEC3bits.INT4IE = 1; /* enable the interrupt */
}

#endif


void INT1_config(void)
{

	IFS1bits.INT1IF = 0;/* clear the interrupt flag */
	IPC5bits.INT1IP = 0b001; /* set int0 priority to 1 */
	INTCON2bits.INT1EP = 0; /* set interrupt on rising edge */
	IEC1bits.INT1IE = 1; /* enable the interrupt */

}


