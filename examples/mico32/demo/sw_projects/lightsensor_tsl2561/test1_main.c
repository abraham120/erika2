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
    @file      test1_main.c
    @brief     Light sensor test. 
               This demo reads and prints light value.
               The demo requires a RS232 serial connection
               with a 115200 bps,8N1 configuration. 
    @author    Dario Di Stefano
    @date      2010
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Erika Mico32 interrupts */
#include <ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/* Light sensor driver */
#include "tsl2561t.h"

#define MAX_CHARS 128

/* This function is used to send info by serial interface. */
void myprintf(const char *format, ...)
{
	char str[MAX_CHARS];
	
	va_list args;
	va_start( args, format );
	vsnprintf(str, MAX_CHARS, format, args);
	va_end( args );
	EE_uart_send_buffer(str, strlen(str));
}

/* In case of fatal error */
void die(int code)
{
	myprintf("\nError! code: %d\n", code);
	while(1);
}

/* This function is used for light sensor configuration. */
int lightsensor_config(void)
{
	int ret;
	EE_lightsensor_init();
	ret = EE_lightsensor_power_on();
	if(ret!=TSL2516T_NO_ERROR)
		die(1);
	ret = EE_lightsensor_set_configuration(TSL2561T_TIMING, 0);
	if(ret!=TSL2516T_NO_ERROR)
		die(2);
	return TSL2516T_NO_ERROR;
}

/* This function is the callback function called by the timer ISR. 
 * It calls the function CounterTick used by EE for tasks periodic activation. */
void system_timer_callback(void)
{
	CounterTick(myCounter);
}

/* The Task reads light measure and sends it to PC. */
TASK(myTask)
{
	static int read_count = 0;
	uint32_t light;

	read_count++;
	EE_lightsensor_read_lux(&light);	// light = EE_lightsensor_read();
	myprintf("%d: %d\n", read_count, light);
}

/*
 * MAIN TASK
 */
int main(void)
{
	/* ------------ */
	/* Disable IRQ  */
	/* ------------ */
	EE_mico32_disableIRQ();
	
	EE_tsl2561t_board_set_int_pin();
	/* ------------------- */
	/* UART configuration */
	/* ------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);

	/* ------------------- */
	/* Light-sensor configuration */
	/* ------------------- */
	int ret = lightsensor_config();
	if (ret < 0)
		die(3);     

	/* ------------------- */
	/* Enable IRQ */
	/* ------------------- */
	EE_mico32_enableIRQ();

	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MICROSECONDS_TO_TICKS(1000), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);

	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm, 500, 500);
	EE_timer_on();

	/* Forever loop: background activities (if any) should go here */
	while(1)
		;
		
	return 0;
}

