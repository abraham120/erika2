/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010  Evidence Srl
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
 
/** 
    @file      main.c
    @brief     UWL coordinator test.
               This demo shows how to configure a coordinator node in a
               ZIGBEE net. The stack si based on the uWIRELESS library.
               The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
               The demo requires a SPI connection with the MRF24J40MA/MB device. 
    @author    Dario Di Stefano
    @date      2010
*/

#include "ee.h"
#include "uwl_ieee802154.h"
#include "kal/uwl_kal.h"
#include <MicoMacros.h>
/* Other libraries */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_CHARS 128

/* This function is used to send info by serial interface. */
void myprintf(const char *format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

/* Constants */
#define TEST_PANID          0x000A
#define TEST_COORD_ADDR     0x0001
#define TEST_CHANNEL        0x0D
#define TEST_BO             6
#define TEST_SO             6
#define MAX_PCK_LEN         127
#define USE_GTS             1
#define DO_NOT_USE_GTS      0

/* Global variables */
static EE_UINT8 last_msg[MAX_PCK_LEN];
static EE_UINT8 last_msg_len = 0;
static EE_UINT16 last_sender = 0;

/* RX callback */
void rx_callback(EE_INT8 err, EE_UINT8* msg, EE_UINT8 len, EE_UINT16 addr)
{
	int i = 0;
	
	myprintf("rx_cbk!\n err: %d, len: %d, addr: %d\n", err, len, addr);
	if (len > MAX_PCK_LEN)
		len = MAX_PCK_LEN;
	for (i = 0; i < len; i++) {
		last_msg[i] = msg[i];
		myprintf("msg[%d]:0x%02x  ", i, msg[i]);
	}
	myprintf("\n");
	last_msg_len = len;
	last_sender = addr;
	ActivateTask(myTask);
}

/* myTask */
TASK(myTask)
{
	uwl_simple154_send(last_msg, last_msg_len, last_sender, DO_NOT_USE_GTS);
}

/* Main */
int main(void)
{
	/* ------------------- */
	/* Disable IRQ         */
	/* ------------------- */
	EE_mico32_disableIRQ();

	/* -------------------------- */
	/* Uart configuration         */
	/* -------------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK); // polling, blocking mode  

	/* ---------- */
	/* Enable IRQ */
	/* ---------- */
	EE_mico32_enableIRQ();
	
	/* -------------------------- */
	/* Coordinator initialization */
	/* -------------------------- */
	int ret;
	uwl_simple154_init_coordinator(	TEST_COORD_ADDR, TEST_PANID,
									TEST_CHANNEL, TEST_BO, TEST_SO);
	uwl_simple154_set_rx_callback(&rx_callback);
	ret = uwl_simple154_gts_add(0x0022, 2, 0);
	myprintf("0x0022 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0023, 2, 0);
	myprintf("0x0023 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0024, 2, 0);
	myprintf("0x0024 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0025, 2, 0);
	myprintf("0x0025 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0026, 2, 0);
	myprintf("0x0026 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0027, 2, 0);
	myprintf("0x0027 ret: %d!\n", ret);
	ret = uwl_simple154_gts_add(0x0028, 2, 0);
	myprintf("0x0028 ret: %d!\n", ret);
	myprintf("Init coordinator...Done!\n");
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	while(1)
		;
	
	return 0;
}


