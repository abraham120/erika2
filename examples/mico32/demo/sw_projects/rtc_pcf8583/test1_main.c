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
    @brief     RTC PCF8583 driver test.
               This demo shows how to use RTC PCF8583 driver written for
               Lattice Mico32 device.
               The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
               The demo requires a I2C connection with the RTC PCF8583 device.
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
/* Other libraries */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/* RTC driver */
#include "pcf8583.h"


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

/* In case of fatal error */
void die(int code)
{
	myprintf("\nError! code: %d\n", code);
	while(1);
}

int rtc_display_time(TTime *TimeRead);

TASK(myTask)
{
	int ret;
	TTime now;
	    
	ret = EE_rtc_read_time(&now);
	if(ret == RTC_NO_ERROR)
	{
		myprintf("Time:\n");
		ret = rtc_display_time(&now); 
		if(ret<0)
			die(1);
	}
	else
		die(2);
}

void system_timer_callback(void)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/*
 * MAIN TASK
 */
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
	
	/* -------------------------- */
	/* RTC configuration         */
	/* -------------------------- */
	int ret;
	TTime tt;
	/* I2C configuration */
	EE_rtc_config(100000, 0);
	/* Write Time in RTC */
	tt.year    = 10;    // 2010 (offset from 2000)
	tt.month   = 4;
	tt.day     = 1;
	tt.hours   = 10;
	tt.minutes = 43;
	tt.seconds = 0;
	tt.hundredths = 0;
	ret = EE_rtc_write_time(&tt);
	if(ret != RTC_NO_ERROR)
		die(3);
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	SetRelAlarm(myAlarm, 1000, 500);
	EE_timer_on();

	while(1)
		;
		
	return 0;
}

/* ------------------------------------------------------- */
/* Other RTC functions                                     */
/* ------------------------------------------------------- */

int rtc_display_time(TTime *TimeRead) 
{
	EE_UINT8 txt[12];
	int ret1, ret2;

	// output values to USART
	txt[0] = (TimeRead->day / 10) + 48;
	txt[1] = (TimeRead->day % 10) + 48;
	txt[2] = '/';
	txt[3] = (TimeRead->month / 10) + 48;
	txt[4] = (TimeRead->month % 10) + 48;
	txt[5] = '/';
	txt[6] = ((TimeRead->year % 100) / 10) + 48;
	txt[7] = (TimeRead->year % 10)  + 48;
	txt[8] = ' ';
	ret1 = EE_uart_send_buffer(txt,9);
	if(ret1 < 0) return ret1;

	txt[0] = (TimeRead->hours / 10) + 48;
	txt[1] = (TimeRead->hours % 10) + 48;
	txt[2] = ':';
	txt[3] = (TimeRead->minutes / 10) + 48;
	txt[4] = (TimeRead->minutes % 10) + 48;
	txt[5] = ':';
	txt[6] = (TimeRead->seconds / 10) + 48;
	txt[7] = (TimeRead->seconds % 10) + 48;
	txt[8] = ':';
	txt[9] = (TimeRead->hundredths / 10) + 48;
	txt[10] = (TimeRead->hundredths % 10) + 48;;
	txt[11] = '\n';
	ret2 = EE_uart_send_buffer(txt,12);
	if(ret2 < 0) return ret2;

	return ret1+ret2;
}





