/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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
 * Simple demo that shows a to use to QP framework.
 * This demo implements a simple state machine that blinks the leds
 * STM32F407 Discovery board.
 *
 * Author: 2014  Gianluca Franchino.
 *
 */


#include "qp_port.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "bsp.h"

Q_DEFINE_THIS_FILE

/*..........................................................................*/
void QF_onStartup(void) {

	/*Initialize Erika related stuffs*/
	EE_system_init();
	
	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(BSP_TICKS_ms, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();
}
/*..........................................................................*/
/*void QF_onCleanup(void) {
}*/
/*..........................................................................*/


/*..........................................................................*/
void Q_onAssert(char const Q_ROM * const file, int line) {
    
	DisableAllInterrupts();
	
	for(;;);
}
/*..........................................................................*/

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* system clock tick ISR */
	QF_TICK_X(0U, (void *)0); /* process all armed time events */
}

/*..........................................................................*/
void BSP_init(void) 
{
	
	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();
	
    /* configure the LEDs and push buttons */
 	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
	
	
    if (QS_INIT((void *)0) == 0) {    /* initialize the QS software tracing */
        Q_ERROR();
    }
}


void BSP_ledOff() 
{
    STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
}


void BSP_ledOn() 
{
    STM_EVAL_LEDOn(LED3);
	STM_EVAL_LEDOn(LED4);
	STM_EVAL_LEDOn(LED5);
	STM_EVAL_LEDOn(LED6);
}


/*
 * BlinkyTask handles the l_blinky actor created in blinky.c
 */
TASK(BlinkyTask)
{

	task_function(pdata[BlinkyTask]);
	
	TerminateTask();
}
