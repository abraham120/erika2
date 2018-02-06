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
 * Author: 2006 Paolo Gai
 * CVS: $Id: code.c,v 1.12 2007/03/15 15:37:02 nino Exp $
 */

#include "ee.h"
#include "ee_irq.h"

// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL(FNOSC_PRI);
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

unsigned char kitt_i = 0;
unsigned char kitt_seq = 0;
unsigned char kitt_seq_n[4] = { 0, 14, 22, 28 }; // 14, 8, 6
unsigned char kitt_seqs[28] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x2,
				0x0f, 0x1e, 0x3c, 0x78, 0xf0, 0xe1, 0xc3, 0x87, 
				0x81, 0x42, 0x24, 0x18, 0x24, 0x42 };
TASK(TaskKitt)
{
	/* Set LEDs new status */
	EE_leds(kitt_seqs[kitt_i++]);
	
	/* Loop sequence if finished */
	if ( (kitt_i >= kitt_seq_n[ kitt_seq + 1 ]) || (kitt_i < kitt_seq_n[ kitt_seq ]) )
		kitt_i = kitt_seq_n[ kitt_seq ];
}

TASK(TaskFlash)
{
	static unsigned char my_button_status = 0;
	
	/* Change LEDs sequence if button S6 is pressen */
	if (EE_button_get_S6()) {
		if (my_button_status == 0) {
			kitt_seq++;
			if (kitt_seq > 2)
				kitt_seq = 0;
			kitt_i = kitt_seq_n[ kitt_seq ];
			my_button_status = 1;
		}
	} else {
		my_button_status = 0;
	}
}

TASK(TaskLCD)
{
	unsigned int volt=1;
	unsigned int deg=1;
	
	/* Acquire voltage and temperature values */
	volt = EE_analog_get_volt();
	deg  = EE_analog_get_temp();

	/* Show results on LCD */
	EE_lcd_line2();
	
	EE_lcd_putc((volt/1000)+'0');
	EE_lcd_putc('.');
	EE_lcd_putc(((volt%1000)/100)+'0');
	EE_lcd_putc(((volt%100)/10)+'0');
	EE_lcd_putc((volt%10)+'0');
	EE_lcd_putc('V');
	EE_lcd_putc(' ');
	EE_lcd_putc(' ');

	EE_lcd_goto( 10, 1 );
	
	if ((deg > 1000) || (deg < 0)) {
		EE_lcd_putc(' ');
		EE_lcd_putc('-');
		EE_lcd_putc('-');
		EE_lcd_putc('-');
		EE_lcd_putc('-');
	} else {
		EE_lcd_putc(((deg%1000)/100)+'0');
		EE_lcd_putc(((deg%100)/10)+'0');
		EE_lcd_putc('.');
		EE_lcd_putc((deg%10)+'0');
		EE_lcd_putc(0xDF);
		EE_lcd_putc('C');
	}
	
	EE_lcd_home();
	
	EE_lcd_putc('E');
	EE_lcd_putc('r');
	EE_lcd_putc('i');
	EE_lcd_putc('k');
	EE_lcd_putc('a');
	EE_lcd_putc(' ');
	EE_lcd_putc('E');
	EE_lcd_putc('n');
	EE_lcd_putc('t');
	EE_lcd_putc('e');
	EE_lcd_putc('r');
	EE_lcd_putc('p');
	EE_lcd_putc('r');
	EE_lcd_putc('i');
	EE_lcd_putc('s');
	EE_lcd_putc('e');
}

void my_button(void)
{
	/* Light up alla LEDs */
	if (EE_button_get_S3() == 1)
		EE_leds_on();
}

int main(void)
{
	/* Program Timer 1 to raise interrupts */
	T1_program();
  
	/* Init devices */
	EE_buttons_init(&my_button, 0x01);
  
	/* Init leds */
	EE_leds_init();
  
	/* Init LCD */
	EE_lcd_init();
	EE_lcd_clear();

	/* Init analog sensors */
	EE_analog_init();
  
	/* Program cyclic alarms which will fire after an initial offset, and after that periodically */
	SetRelAlarm(AlarmFlash, 10,  1);
	SetRelAlarm(AlarmKitt,  10, 10);
	SetRelAlarm(AlarmLCD,   10, 50);

	 /* Forever loop: background activities (if any) should go here */
	for (;;);
	
	return 0;
}
