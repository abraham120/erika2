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




#include "ee.h"
#include "ee_irq.h"

#include "stm32f4xx_conf.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"

#include "STMPE811QTR.h"
#include "LCD_Touch_Calibration.h"


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


/*
 * TASK 1
 */
TASK(Task1)
{
	Calibration_Test_Dispose();

}
/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
void delay(volatile uint32_t nCount)
{
  volatile uint32_t index = 0;
  for (index = (100000 * nCount); index != 0; index--);
}

/*
 * MAIN TASK
 */
int main(void)
{

	SystemInit();
  /*Initializes Erika related stuffs*/
	EE_system_init();

	STM_EVAL_LEDInit(LED3);

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	IOE_Config();

	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();

	/* Clear the LCD */
	LCD_Clear(White);

	/* Set the LCD Text size */
	LCD_SetFont(&Font8x12);

	Lcd_Touch_Calibration();

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmTask1, 10, 50);

  /* Forever loop: background activities (if any) should go here */
	for (;;) { 
	}

}


