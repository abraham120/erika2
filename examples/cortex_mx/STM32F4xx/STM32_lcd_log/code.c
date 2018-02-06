/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Simple demo that shows how to use LCD log library.
 *
 * Author: 2013  Gianluca Franchino.
 *
 */

#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "lcd_log.h"

#include <stdio.h>


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


TASK(TaskOUT)
{
	static int cnt = 0;

	LCD_UsrLog("\r\nTaskOUT = %d", cnt++);

}


int main(void)
{


	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();
	
	/*Initialize the LCD*/
	STM32f4_Discovery_LCD_Init();
	LCD_LOG_Init();
	LCD_LOG_SetHeader("Hi ... Erika is running!");
	LCD_LOG_SetFooter("Erika RTOS LCD log Demo");
	LCD_UsrLog("\r\nTest-> Log Initialized!");
	LCD_DbgLog("\r\nTest-> DBG message!");
	LCD_ErrLog("\r\nTest-> ERR message!");

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmOUT, 10, 1000);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

}

