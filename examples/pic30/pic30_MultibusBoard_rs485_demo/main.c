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

//#include "ee.h"
//#include "ee_irq.h"

#include "define.h"
#include "eeuart.h"
#include "variable.h"
#include "driver.h"

//#include "./util.h"

// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);

// optional callback functions for UART1/UART2
EE_INT8 (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
EE_INT8 (*Tx1IsrFunction)(EE_UINT8 data) = NULL;

EE_INT8 (*Rx2IsrFunction)(EE_UINT8 data) = NULL;
EE_INT8 (*Tx2IsrFunction)(EE_UINT8 data) = NULL;


int main(void)
{
	/* Clock setup for 40MIPS */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;

	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);

	/* Program Timer 1 to raise interrupts */
	T1_program();

	/* Init led */
	EE_leds_init();

	/* Application Init */
	//[mck]
	InitVariables();

	//[mck] org
	//EE_UART1_Init(115200, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);
	EE_UART1_Init(9600, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);
#ifdef	RS485_PORT_UART2
	EE_UART2_Init(9600, BIT8_NO | BIT_STOP_1, CTRL_FLOW);
#else
	EE_UART2_Init(9600, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);
#endif

	/* Program a cyclic alarm which will fire after an offset of 10 counter
	* ticks, and after that periodically every 500 ticks */
	//SetRelAlarm(AlarmSend, 500, 500);
	//SetRelAlarm(AlarmReceive, 500, 500);
	//SetRelAlarm(AlarmDebug, 500, 500);

	// For RS485 Half-duplex communication mode test
#ifdef	RS485_PORT_UART2
#ifdef	RS485_UART2_SENDER
	PORTFbits.RF12 = 0;
	PORTFbits.RF13 = 1;				//TXEN

	/* Program a cyclic alarm which will fire after an offset of 10 counter
	* ticks, and after that periodically every 500 ticks */
	SetRelAlarm(AlarmSend, 500, 500);
#else
	PORTFbits.RF12 = 0;
	PORTFbits.RF13 = 0;				//TXEN

	/* Program a cyclic alarm which will fire after an offset of 10 counter
	* ticks, and after that periodically every 500 ticks */
	//SetRelAlarm(AlarmReceive, 500, 500);
	ActivateTask(TaskDebug);
#endif
#endif

	/* Forever loop: background activities (if any) should go here */
	for (;;);

	return 0;
}
