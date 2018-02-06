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
 * Author: Gianluca Franchino. 2013
 * Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
 * Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
 *
 */
#include "ee.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "cc2420.h"
#include "lcd_log.h"

#include <stdio.h>


GPIO_InitTypeDef  GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

#define SENDER_ADDR 0x0000
#define RECEIVER_ADDR 0x0001
#define RADIO_CHANNEL 19

#define PACKET_SIZE 100

#define MY_PACKET_SIZE 8

#define BOARD_0


//EE_UINT8 rx_msg[PACKET_SIZE];
char rx_msg[PACKET_SIZE];
char str[80];

#ifdef BOARD_0
EE_UINT8 my_packet[] ={'E','R','I','K','A',' ', 'B','0'};
#else
EE_UINT8 my_packet[] ={'E','R','I','K','A',' ', 'B','1'};
#endif

EE_INT16 len;
EE_UINT8 lqi, rssi;

EE_UINT16 n_msg_sent = 0;
EE_UINT16 n_msg_rec = 0;

#ifdef USE_LCD_LOG

void console_init()
{
	/*Initialize the LCD*/
	STM32f4_Discovery_LCD_Init();
	LCD_LOG_Init();
	LCD_LOG_SetHeader("Powered by Erika RTOS");
	LCD_LOG_SetFooter("Erika RTOS CC2420 Aloha Demo");
}

#else /* USE_LCD_LOG */

USART_InitTypeDef USART_InitStructure;

void console_init()
{
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
}

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls _write() */
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

#endif /* USE_LCD_LOG*/


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* counconsole_init()t the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}


/* Store a message into radio buffer and send it using aloha algorithm */
EE_INT8 radio_aloha_send(EE_UINT8 *msg, EE_UINT8 msg_len)
{
	GetResource(RADIO_MUTEX);
	cc2420_store_msg(msg, msg_len);
	cc2420_set_tx();
	/* Wait until the transmission has finished. */
	while (cc2420_get_status() & 0x08);

	/* If a tx underflow has occurred fix the problem and return -1.*/
	if (cc2420_get_status() & 0x20) {
		CC2420_TX_FIFO_FLUSH();
		ReleaseResource(RADIO_MUTEX);
		return -1;
	}
	ReleaseResource(RADIO_MUTEX);
	return 0;
}

EE_UINT8 buf[127];

/* Function "called" by the radio interrupt when receiving a packet */
EE_INT8 rx_data()
{
	int i = 0;

	GetResource(RADIO_MUTEX);
	len = cc2420_get_fifo_msg(buf);
	ReleaseResource(RADIO_MUTEX);

	if (len < 2)
		return -1;
	/* Length does not consider the first byte (which is length itself) so
	 * add it! */
	len += 1;

	/* The last two bytes in the buffer are the RSSI value
	* and the CRC value respectively. They are not part
	* of the message (payload), then we can discard them.
	* For further information see the CC2420 datasheet
	*/

	/* check the CRC bit, if the packet is corrupted return
	 * Note: CRC bit = 0 -> msg corrupted!
	 */
	if (!(buf[len - 1] & 0x80))
			return -2;

	lqi = buf[len - 1] & 0x7F;
	rssi= 255 - buf[len - 2];

	/* remove the FCS/LQI, RSSI, and length from the length */
	len -= 3;

	for (i = 0; i < len; i++) {
		rx_msg[i] = buf[i+1];
	}


	return len;
}

static void radio_rx_callback()
{
	ActivateTask(TaskReceiver);
}
/*
 * This Task sends the message "msg" every time it is activated
 */
TASK(TaskSender)
{
	if (radio_aloha_send(my_packet, MY_PACKET_SIZE ) == -1) {
		GetResource(CONSOLE_MUTEX);
		printf("\r\nradio_aloha_send() ERROR!!!!");
		ReleaseResource(CONSOLE_MUTEX);
	} else {
		n_msg_sent++;
		GetResource(CONSOLE_MUTEX);
		printf("\r\nNumber of msg sent = %u", n_msg_sent);
		ReleaseResource(CONSOLE_MUTEX);
#ifndef USE_LCD_LOG
		STM_EVAL_LEDToggle(LED5);
#endif
	}

}


TASK(TaskReceiver)
{
	EE_INT8 rx_ret;

	rx_ret = rx_data();

	if (rx_ret == -1) {
		GetResource(CONSOLE_MUTEX);
		printf("\r\nrx_data() MSG length ERROR!!!");
		ReleaseResource(CONSOLE_MUTEX);
	} else if (rx_ret == -2) {
		GetResource(CONSOLE_MUTEX);
		printf("\r\nrx_data() MSG Corrupted!!!");
		ReleaseResource(CONSOLE_MUTEX);
	} else {
		n_msg_rec++;
		GetResource(CONSOLE_MUTEX);
		printf(str, "\r\nNumber of msg received = %u", n_msg_rec);
		ReleaseResource(CONSOLE_MUTEX);
		rx_msg[rx_ret]='\0';
		GetResource(CONSOLE_MUTEX);
		printf("\r\nMessage Received: %s", (char*) rx_msg);
		ReleaseResource(CONSOLE_MUTEX);
#ifndef USE_LCD_LOG
		STM_EVAL_LEDToggle(LED3);
#endif
	}

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

#ifndef USE_LCD_LOG
	/*Initialize Leds. */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED5);
#endif

	/*
	 * Initialize the console.
	 */
	console_init();
	printf("\r\nConsole initialized!");

	/* Initialize the radio */
	if (cc2420_radio_init(CC2420_SPI_PORT_2) < 0 ) {
		printf("\r\nRadio initialization error!");
		while(1);
	}
	/* Set the function to be called when receiving a packet */
	cc2420_set_rx_callback(radio_rx_callback);
	cc2420_set_channel(RADIO_CHANNEL);
	cc2420_set_rx();

	printf("\r\nRadio initialization OK!");

	/*
	 * Program a cyclic alarm which will fire after an offset of 10 counter
	 * ticks, and after that periodically every 100 ticks.
	 * Please note that 1 tick = 1 ms
	 */
	SetRelAlarm(AlarmSender, 3000, 500);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

}

