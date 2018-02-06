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
    @brief     UWL device test.
               This demo shows how to configure a device node in a
               ZIGBEE net. The stack si based on the uWIRELESS library.
               The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
               The demo requires a SPI connection with the MRF24J40MA/MB device. 
    @author    Dario Di Stefano
    @date      2010
*/

#include "uwl_ieee802154.h"
#include "kal/uwl_kal.h"
#include "ee.h"
#include "console_serial.h"
#include <MicoMacros.h>
/* Other libraries */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#define MAX_CHARS 128


/* This function is used to send info by serial interface. */
void myprintf(const char* format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer((EE_UINT8*)str, strlen(str));
}

/* In case of fatal error */
void die(int code)
{
	myprintf("\nError! code: %d\n", code);
	while(1);
}

/* Constant Definitions */
#define TEST_PANID          0x000A
#define TEST_COORD_ADDR     0x0001
#define TEST_CHANNEL        0x0D
#define TEST_BO             6
#define TEST_SO             6
#define TEST_DEVICE_ADDR    0x0028
#define MAX_PCK_LEN         127
#define USE_GTS             1
#define DO_NOT_USE_GTS      0
#define MSG_LEN             90

void system_timer_callback(void)
{
	CounterTick(TASK_COUNTER);
}

/* TASKs */
TASK(SEND_TASK)
{
	EE_UINT8 msg[MSG_LEN];
	/* static int sw = 0; */
	int i = 0;
	
	for (i = 0; i < MSG_LEN; i++) {
		msg[i] = i;
	}
	
	// CAP send
	myprintf("uwl_simple154_send without GTS \n");
	uwl_simple154_send(msg, MSG_LEN, TEST_COORD_ADDR, DO_NOT_USE_GTS);
	/*
	sw ^= 1;
	if (sw){
		myprintf("uwl_simple154_send without GTS \n");
		uwl_simple154_send(msg, MSG_LEN, TEST_COORD_ADDR, DO_NOT_USE_GTS);
		
	}
	else {
		myprintf("uwl_simple154_send with GTS \n");
		// GTS send
		uwl_simple154_send(msg, 10, TEST_COORD_ADDR, USE_GTS);
		
	}
	*/
}

/* Main */
int main(void)
{
	EE_INT8 retv;
	
	/* ------------ */
	/* Disable IRQ  */
	/* ------------ */
	EE_mico32_disableIRQ();
	mico32_disable_irq_mask(0xFFFFFFFF);
	
	/* ------------------- */
	/* UART configuration  */
	/* ------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
	
	
	/* ----------------- */
	/* CONSOLE */
	/* ----------------- */
	/* Serial Console configuration */
	console_descriptor_t *cons;    
	cons = console_serial_config(1, 115200, CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1);
	if (!cons)
		die(1);
	console_init(0, cons);
	if (console_open(0) < 0)
		die(2);
	myprintf("Serial console configuration...Done!\n");
	
	/* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* DEVICE init */
	/* ------------------- */
	myprintf("\nDevice init...");
	retv = uwl_simple154_init_device(TEST_DEVICE_ADDR, TEST_COORD_ADDR, TEST_PANID, TEST_CHANNEL);
	if (retv < 0)
	{
		die(retv);
	}
	else {
		myprintf("Done!\n");
	}
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MICROSECONDS_TO_TICKS(1000), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(TASK_ALARM, 1000, 2500);
	EE_timer_on();
	
	/* Forever loop: background activities (if any) should go here */
	for (;;) {

	}
	return 0;
}


