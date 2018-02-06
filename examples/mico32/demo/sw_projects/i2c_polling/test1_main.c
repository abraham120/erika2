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
    @brief     I2C polling test.
               This demo shows how to use I2C driver for Lattice Mico32 device.
               I2C driver supports only polling and blocking mode. 
               In this demo is shown how to use I2C driver functions to 
               develop a new device driver (RTC PCF8583 in this example).
               In case of error the application turns off the system led.
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

/* ----------------- */
/* My device driver */
int device_write(void);
int device_read(void);
int device_print(void); 
/* Global variables used by driver */
struct myStruct {
  char year, month, day, hours, minutes, seconds;
};
EE_UINT8 rx_data[16];
EE_UINT8 tx_data[16];
struct myStruct TimeToWrite, TimeRead;
EE_UINT8 retvalue;
/* ----------------- */

/*
 * Task 1
 */
TASK(myTask)
{
	int ret;
	
	ret = device_read();

	if(ret == EE_I2C_OK)
	{
		ret = device_print(); 
		if(ret<0)
		{
			myprintf("rtc_display: ERROR!\n");
			EE_led_off(EE_SERIO_SYSTEM_LED);
			while(1);
		}
	}
	else
	{
		myprintf("rtc_read: ERROR!\n");
		EE_led_off(EE_SERIO_SYSTEM_LED);
		while(1);
	}
	
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
	/* I2C configuration         */
	/* -------------------------- */
	EE_rtc_i2c_config(100000, 0);
	
	/* ------------------- */
	/* Kernel timer configuration */
	/* ------------------- */
	EE_timer_set_ISR_callback(system_timer_callback);
	EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	EE_led_init();
	int ret = device_write();
	if(ret == EE_I2C_OK)
	{
		EE_led_on(EE_SERIO_SYSTEM_LED);
		SetRelAlarm(myAlarm, 1000, 1000);
		EE_timer_on();
	}
	else
	{
		EE_led_off(EE_SERIO_SYSTEM_LED);
		die(0);
	}
		
	while(1)
		;
	return 0;
}

/* ------------------------------------------------------- */
/* Device driver functions                                 */
/* ------------------------------------------------------- */

int device_write(void) {
	EE_UINT8 device = 0xA0;
	EE_UINT8 address;
	
	TimeToWrite.year    = 7;    			// 2007 (offset from 2000)
	TimeToWrite.month   = 12;
	TimeToWrite.day     = 31;
	TimeToWrite.hours   = 23;
	TimeToWrite.minutes = 59;
	TimeToWrite.seconds = 40;

	address = 0;							// address in memory
	tx_data[0] = 0x80;
	tx_data[1] = 0;
	tx_data[2] = ((TimeToWrite.seconds/10)<<4) + (TimeToWrite.seconds%10);
	tx_data[3] = ((TimeToWrite.minutes/10)<<4) + (TimeToWrite.minutes%10);
	tx_data[4] = ((TimeToWrite.hours/10)<<4) + (TimeToWrite.hours%10);
	tx_data[5] = ((TimeToWrite.year%4)<<6) + ((TimeToWrite.day/10)<<4) +(TimeToWrite.day%10);
	tx_data[6] = ((TimeToWrite.month/10)<<4) + (TimeToWrite.month%10);
	retvalue = EE_rtc_i2c_send_buffer(device, address, tx_data, 7);	

	if(retvalue!= EE_I2C_OK) 
	{
		EE_uart_send_buffer(&retvalue,1);
		die(1);
	}

	address = 0x10;							// address in memory
	tx_data[0] = TimeToWrite.year;			// data to be written
	retvalue = EE_rtc_i2c_send_byte(device, address, tx_data[0]);	
	if(retvalue!= EE_I2C_OK)
	{
		EE_uart_send_buffer(&retvalue,1);
		die(2);
	}

	address = 0;							// address in memory
	tx_data[0] = 0;							// data to be written
	retvalue = EE_rtc_i2c_send_byte(device, address, tx_data[0]);	
	if(retvalue!= EE_I2C_OK)
	{
		EE_uart_send_buffer(&retvalue,1);	
		die(3);
	}

	return 0;
}

int device_read(void)
{
	EE_UINT8 device = 0xA0;
	EE_UINT8 address;
	char yearmod4;
	char byteRead;

	address = 2;											// address in memory
	retvalue = EE_rtc_i2c_receive_buffer(device, address, rx_data, 5);	
	if(retvalue!= EE_I2C_OK)
	{
		EE_uart_send_buffer(&retvalue,1);
		die(4);
	}

	byteRead = rx_data[0];		// read seconds byte
	TimeRead.seconds = (byteRead >> 4)*10 + (byteRead & 0x0F); // transform seconds
	byteRead = rx_data[1];     	// read minutes byte
	TimeRead.minutes = (byteRead >> 4)*10 + (byteRead & 0x0F); // transform minutes
	byteRead = rx_data[2];     	// read hours byte
	TimeRead.hours = (byteRead >> 4)*10 + (byteRead & 0x0F); // transform hours
	byteRead = rx_data[3];     	// read year/day byte
	TimeRead.day = ((byteRead & 0b00110000) >> 4)*10 + (byteRead & 0x0F); // transform day
	yearmod4 = (byteRead & 0b11000000) >> 6;   // get year mod 4 from RTC
	byteRead = rx_data[4];     	// read weekday/month byte
	TimeRead.month = ((byteRead & 0b00010000) >> 4)*10 + (byteRead & 0x0F); // transform month

	address = 0x10;				// address in memory

	rx_data[0] = EE_rtc_i2c_receive_byte(device, address);	
	retvalue = rx_data[0];
	if(retvalue < 0)
	{
		EE_uart_send_buffer(&retvalue,1);
		die(5);
	}

	byteRead = rx_data[0];  		// read year
	if (yearmod4 != byteRead % 4 )  // check if year is incremented in RTC
	{	// in this case the new value should be written to RTC RAM at address 16(0x10)
		byteRead++;  
		address = 0x10;				// address in memory
		tx_data[0] = byteRead;		// data to be written
		retvalue = EE_rtc_i2c_send_byte(device, address, tx_data[0]);	
		if(retvalue!= EE_I2C_OK)
		{
			EE_uart_send_buffer(&retvalue,1);
			die(6);
		}
		
	}
	TimeRead.year = byteRead;

	return 0;
}

int device_print(void) 
{
	int ret1, ret2;

	// output values to USART
	tx_data[0] = (TimeRead.day / 10) + 48;
	tx_data[1] = (TimeRead.day % 10) + 48;
	tx_data[2] = '/';
	tx_data[3] = (TimeRead.month / 10) + 48;
	tx_data[4] = (TimeRead.month % 10) + 48;
	tx_data[5] = '/';
	tx_data[6] = ((TimeRead.year % 100) / 10) + 48;
	tx_data[7] = (TimeRead.year % 10)  + 48;
	tx_data[8] = ' ';
	ret1 = EE_uart_send_buffer(tx_data,9);
	if(ret1 < 0) return ret1;

	tx_data[0] = (TimeRead.hours / 10) + 48;
	tx_data[1] = (TimeRead.hours % 10) + 48;
	tx_data[2] = ':';
	tx_data[3] = (TimeRead.minutes / 10) + 48;
	tx_data[4] = (TimeRead.minutes % 10) + 48;
	tx_data[5] = ':';
	tx_data[6] = (TimeRead.seconds / 10) + 48;
	tx_data[7] = (TimeRead.seconds % 10) + 48;
	tx_data[8] = '\n';
	ret2 = EE_uart_send_buffer(tx_data,9);
	if(ret2 < 0) return ret2;

	return ret1+ret2;
}




