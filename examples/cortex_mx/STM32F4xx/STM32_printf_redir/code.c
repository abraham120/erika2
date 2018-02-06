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
 * Simple demo that shows a to redirect printf() to USART.
 *
 * Author: 2013  Gianluca Franchino.
 *
 */

#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include <stdio.h>

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int _write(int fd, char *ptr, int len)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{

#ifdef __GNUC__
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
	EE_INT32 i;
   
	for (i = 0; i < len; i++) {
   	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
		USART_SendData(EVAL_COM1, (uint8_t) ptr[i]);
	/* Loop until the end of transmission */
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	}
	
	return len;
#else

	USART_SendData(EVAL_COM1, (uint8_t) ch);
	while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	
	return ch;
	
#endif
}



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

	printf("\r\nTaskOUT = %d", cnt++);

	/*Initialize Leds. */
	STM_EVAL_LEDToggle(LED3);
	STM_EVAL_LEDToggle(LED4);
	STM_EVAL_LEDToggle(LED5);
	STM_EVAL_LEDToggle(LED6);
}

USART_InitTypeDef USART_InitStructure;

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

	/*Initialize Leds. */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	/*Initialize Leds. */
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);

	/* USARTx configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM_EVAL_COMInit(COM1, &USART_InitStructure);


	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmOUT, 10, 1000);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

}

