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
 * CVS: $Id: code.c,v 1.6 2008/06/19 08:29:59 francesco Exp $
 */

#include "ee.h"
#include "ee_irq.h"

// Primary (XT, HS, EC) Oscillator with PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							


volatile EE_UINT16 i;
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
unsigned char info_seq = 0;
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
	static unsigned char my_button_status_1 = 0;
	static unsigned char my_button_status_2 = 0;
	
	/* Change LEDs sequence if button S1 is pressen */
	if (EE_button_get_S1()) {
		if (my_button_status_1 == 0) {
			kitt_seq++;
			if (kitt_seq > 2)
				kitt_seq = 0;
			kitt_i = kitt_seq_n[ kitt_seq ];
			my_button_status_1 = 1;
		}
	} else {
		my_button_status_1 = 0;
	}		

	/* Change visualized data if button S2 is pressen */
	if (EE_button_get_S2()) {
		if (my_button_status_2 == 0) {
			info_seq++;
			if (info_seq > 3)
				info_seq = 0;
			my_button_status_2 = 1;
			EE_lcd_clear();
		}
	} else {
		my_button_status_2 = 0;
	}			
}

TASK(TaskLCD)
{
	float volt=1;
	unsigned int millivolt=1000;
	unsigned int deg=1;
	unsigned int light=1;
	float x_level=1.0;
	float y_level=1.0;
	float z_level=1.0;
	signed int x_acc_int=1;
	signed int y_acc_int=1;
	signed int z_acc_int=1;
	
	/* Acquire voltage and temperature values */
	volt = EE_trimmer_get_volt();
	deg  = EE_analog_get_temperature();
	light = EE_analog_get_light();
	
	millivolt = volt * 1000;
	
	/* Show results on LCD */
	switch(info_seq){
		case 0:
			
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
			
			EE_lcd_line2();
			EE_lcd_putc((millivolt/1000)+'0');
			EE_lcd_putc('.');
			EE_lcd_putc(((millivolt%1000)/100)+'0');
			EE_lcd_putc(((millivolt%100)/10)+'0');
			EE_lcd_putc((millivolt%10)+'0');
			EE_lcd_putc('V');
		
			EE_lcd_goto( 10, 1 );
	
			if ((deg > 100) || (deg < 0)) {
				EE_lcd_putc(' ');
				EE_lcd_putc('-');
				EE_lcd_putc('-');
				EE_lcd_putc('-');
				EE_lcd_putc('-'); 
			} else {
				EE_lcd_putc( (((int)deg%100)/10)+'0' );
				EE_lcd_putc( ((int)deg%10)+'0' );
				EE_lcd_putc('.');
				EE_lcd_putc( ((int)(deg*10))%10+'0' );
				EE_lcd_putc(0xDF);
				EE_lcd_putc('C');
			}
			EE_lcd_home();
			
		break;
		
		case 1:
			
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
			
			EE_lcd_line2();
			EE_lcd_putc((millivolt/1000)+'0');
			EE_lcd_putc('.');
			EE_lcd_putc(((millivolt%1000)/100)+'0');
			EE_lcd_putc(((millivolt%100)/10)+'0');
			EE_lcd_putc((millivolt%10)+'0');
			EE_lcd_putc('V');
		
			EE_lcd_goto( 10, 1 );
	
			if ((light > 1000) || (light < 0)) {
				EE_lcd_putc(' ');
				EE_lcd_putc('-');
				EE_lcd_putc('-');
				EE_lcd_putc('-');
				EE_lcd_putc('-'); 
			} else {
				EE_lcd_putc(((light%1000)/100)+'0');
				EE_lcd_putc(((light%100)/10)+'0');
				EE_lcd_putc((light%10)+'0');
				EE_lcd_putc('l');
				EE_lcd_putc('u');
				EE_lcd_putc('x');
			}
			EE_lcd_home();	
		
		break;
		
		case 2:
			
			x_level = EE_accelerometer_getx()*100;
			
			x_acc_int = x_level;	
			
			EE_lcd_putc('X');
			EE_lcd_putc('=');
			if(x_level<0) {
				EE_lcd_putc('-');
				x_acc_int=-x_acc_int;}
			else EE_lcd_putc('+');
			EE_lcd_putc(((x_acc_int%1000)/100)+'0');
			EE_lcd_putc('.');
			EE_lcd_putc(((x_acc_int%100)/10)+'0');
			EE_lcd_putc((x_acc_int%10)+'0');
			
			y_level = EE_accelerometer_gety()*100;
			
			y_acc_int = y_level;
			//EE_lcd_home();
			EE_lcd_goto( 9, 0 );
			EE_lcd_putc('Y');
			EE_lcd_putc('=');
			if(y_level<0) {
				EE_lcd_putc('-');
				y_acc_int=-y_acc_int;}
			else EE_lcd_putc('+');
			EE_lcd_putc(((y_acc_int%1000)/100)+'0');
			EE_lcd_putc('.');
			EE_lcd_putc(((y_acc_int%100)/10)+'0');
			EE_lcd_putc((y_acc_int%10)+'0');
			
			z_level = EE_accelerometer_getz()*100;
			
			z_acc_int = z_level;
			//EE_lcd_home();
			EE_lcd_line2();
			EE_lcd_putc('Z');
			EE_lcd_putc('=');
			if(z_level<0) {
				EE_lcd_putc('-');
				z_acc_int=-z_acc_int;}
			else EE_lcd_putc('+');
			EE_lcd_putc(((z_acc_int%1000)/100)+'0');
			EE_lcd_putc('.');
			EE_lcd_putc(((z_acc_int%100)/10)+'0');
			EE_lcd_putc((z_acc_int%10)+'0');
			EE_lcd_home();	
			
		break;
		
		case 3:
			
			EE_trimmer_get_volt();
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
			
			EE_lcd_line2();
			EE_lcd_putc('P');
			EE_lcd_putc('o');
			EE_lcd_putc('t');
			EE_lcd_putc(' ');
			EE_lcd_putc((millivolt/1000)+'0');
			EE_lcd_putc('.');
			EE_lcd_putc(((millivolt%1000)/100)+'0');
			EE_lcd_putc(((millivolt%100)/10)+'0');
			EE_lcd_putc((millivolt%10)+'0');
			EE_lcd_putc('V');
			
			EE_lcd_home();	
			break;

	}
}


void my_button(void)
{
	/* Light up alla LEDs */
	if (EE_button_get_S3() == 1)
		EE_leds_on();
}

int main(void)
{
	/* Clock setup */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1);
	
	/* Program Timer 1 to raise interrupts */
	T1_program();
	
	/* Init devices */
	EE_buttons_init(&my_button, 0x04);
  
	/* Init leds */
	EE_leds_init();
	EE_demoboard_leds_init();
	
	/* Init LCD */
	EE_lcd_init();
	EE_lcd_clear();
	
	EE_accelerometer_init();
	EE_accelerometer_wakeup();
	EE_accelerometer_setglevel(0);	// set the level to 1.5 g*/
	/* Init analog sensors */
	EE_analog_init();

	/* Program cyclic alarms which will fire after an initial offset, and after that periodically */
	SetRelAlarm(AlarmFlash, 10,  10);
	SetRelAlarm(AlarmKitt,  10, 100);
	SetRelAlarm(AlarmLCD,   10, 500);


	 /* Forever loop: background activities (if any) should go here */
	for (;;);
	
	return 0;
}
