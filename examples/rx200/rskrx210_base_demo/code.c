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
 * Simple project to blink the leds with different frequencies!
 * Author: 2012  Gianluca Franchino gianluca@evidence.eu.com
 */

#include "ee.h"
#include "ee_irq.h"
//#include "ee_lcd.h"

/* Enable all leds*/
#define LED_INIT_MASK 0xF 
/*Enable all buttons*/
#define BUTTON_INIT_MASK 0x7


volatile EE_UINT32 task_toggle_count = 0, isr_count = 1;
volatile EE_UINT8  irq1_cnt = 0, irq3_cnt = 0, irq4_cnt = 0;
EE_UINT8 leds_status_cnt = 0, leds_cnt = 0;

/*
*Not that isr_count is also used by ee_delay() macro in ee_lcd.c
*/
#pragma interrupt (cmia0_handler)
ISR2(cmia0_handler)
{
	isr_count++;
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


#pragma interrupt (irq1_handler)
ISR2(irq1_handler)
{
	EE_b1_disable_IRQ();
	SetRelAlarm(AlarmDeb1, 200, 0);
	irq1_cnt++;
}

#pragma interrupt (irq3_handler)
ISR2(irq3_handler)
{
	EE_b2_disable_IRQ();
	SetRelAlarm(AlarmDeb2, 200, 0);
	irq3_cnt++;
}

#pragma interrupt (irq4_handler)
ISR2(irq4_handler)
{
	EE_b3_disable_IRQ();
	SetRelAlarm(AlarmDeb3, 200, 0);
	irq4_cnt++;
}


/*
 * TaskLeds
 */
TASK(TaskLeds)
{
	if (!leds_status_cnt) {
		leds_cnt = leds_cnt % 4;
		if (leds_cnt == 0) {
			EE_rskrx210_led0_toggle();
		} else if (leds_cnt == 1) {
			EE_rskrx210_led1_toggle();
		} else if (leds_cnt == 2) {
			EE_rskrx210_led2_toggle();
		} else if (leds_cnt == 3) {
			EE_rskrx210_led3_toggle();
		}
		leds_cnt++;
	} else {
		EE_rskrx210_leds_toggle();
		task_toggle_count++;
	}

}

/*
 * TaskDebounce1
 */
TASK(TaskDebounce1)
{
	if (!EE_b1_not_pressed()) {
		CancelAlarm(AlarmLeds);
		SetRelAlarm(AlarmLeds, 500, 500);
	}
	EE_b1_enable_IRQ();
}

/*
 * TaskDebounce2
 */
TASK(TaskDebounce2)
{
	if (!EE_b2_not_pressed()) {
		CancelAlarm(AlarmLeds);
		SetRelAlarm(AlarmLeds, 500, 125);
	}
	EE_b2_enable_IRQ();
}

EE_UINT8 taskdeb3cnt=0;
EE_UINT8 taskdeb3cnt_if=0;

/*
 * TaskDebounce3
 */
TASK(TaskDebounce3)
{
	if (!EE_b3_not_pressed()) {
		taskdeb3cnt_if++;
		if (!leds_status_cnt) {
			EE_rskrx210_leds_off();
			leds_status_cnt = 1;
		} else {
			EE_rskrx210_leds_off();
			leds_status_cnt = 0 ;
			leds_cnt = 0;
		}
	}
	taskdeb3cnt++;
	EE_b3_enable_IRQ();
}

/*
 * TaskLCD
 */
TASK(TaskLCD)
{
	static EE_UINT8 lcd_cnt = 0;

	if (lcd_cnt == 0) {
		EE_LCD_disp(EE_LCD_LINE1, "Renesas ");
		EE_LCD_disp(EE_LCD_LINE2, " RX210  ");
		lcd_cnt = 1;
	} else if (lcd_cnt == 1) {
		EE_LCD_disp(EE_LCD_LINE1, "  and   ");
		EE_LCD_disp(EE_LCD_LINE2, " Erika  ");
		lcd_cnt = 2;
	} else if (lcd_cnt == 2) {
		EE_LCD_disp(EE_LCD_LINE1, "  Just  ");
		EE_LCD_disp(EE_LCD_LINE2, "Married!");
		lcd_cnt = 0;
	}
}



/*
 * Main function
 */
int main(void)
{
	/*Initilize the operating frequencies (CPU, Peripheral etc.)*/
	/*PCKD = PCKC = PCKB = PCKA = BCKPLL/8 = 10MHz*/
	/*ICK = PLL/2 = 40 MHz*/
	/*FCK = PLL/4 = 20 MHz*/
	EE_rskrx210_op_freq_setup();
	
	/*
	* Initialize the system tick
	* Note: now it is initialized to generate an IRQ every 1ms.
	*/
	EE_systick_start();
	/*Set 1 ms tick: match value 0xC, prescaler =0x8C -> PCLK/64*/
	EE_systick_set_period(0x0C, 0x8C);
	EE_systick_enable_int();
	
	/*Initialize the Leds*/
	EE_rskrx210_leds_init(LED_INIT_MASK);
	/*Initialize the buttons*/
	EE_rskrx210_buttons_IRQ_init(BUTTON_INIT_MASK);
	/*Initialize the LCD Module*/
	EE_LCD_init();

	SetRelAlarm(AlarmLeds, 500, 250);
	SetRelAlarm(AlarmLCD, 500, 1000);
	
  /* Forever loop: background activities (if any) should go here */
	for (;;) {}

}
