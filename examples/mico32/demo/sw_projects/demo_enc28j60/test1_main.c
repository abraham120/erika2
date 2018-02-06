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
    @brief     ENC28J60 driver function test (eth mac mii read and write, bank selection).
               User can use this demo to test if SPI communication works fine.
               The demo uses eth, mac, mii read/write and bank selection functions of the 
               ENC28J60 library.
               The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
               The demo requires a SPI bus to communicate with the device.
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
/* enc28j60 driver */
#include "enc28j60.h"

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

#define DEVICE_GPIO_BIT 1
#define device_config() 		EE_misc_gpio_write_bit_data(1, DEVICE_GPIO_BIT)
#define BANK0 0
#define BANK1 1
#define BANK2 2
#define BANK3 3

TASK(myTask1)
{
	EE_UINT8 data;
	
	/* ---------------------------------------------------------------- */
	/* BANK SELECTION */
	EE_enc28j60_bank_select(ECON1);
	myprintf("\nWrite bank: %d\n",      BANK0);
	myprintf("\nRead ECON1: %d\n",      EE_enc28j60_read_ETH_register(ECON1).Val);
	myprintf("\nRead ERXSTL:%d\n",      EE_enc28j60_read_ETH_register(ERXSTL).Val);
	myprintf("\nRead EDMADSTL:%d\n",    EE_enc28j60_read_ETH_register(EDMADSTL).Val);

	/* ---------------------------------------------------------------- */
	/* ETH */
	data = 0x09;
	EE_enc28j60_write_register(ETXNDL, data);
	myprintf("\nWrite ETXNDL:%d\n", data);
	myprintf("\nRead ETXNDL:%d\n", EE_enc28j60_read_ETH_register(ETXNDL).Val);
	EE_UINT8 mask = 0x0A; 
	EE_enc28j60_bit_field_clear_register(ETXNDL, mask); /* BFC */
	myprintf("\nBFC, ETXNDL expected:%d\n", data & ~mask);
	myprintf("\nRead ETXNDL:%d\n", EE_enc28j60_read_ETH_register(ETXNDL).Val);
	mask = 0x08;
	EE_enc28j60_bit_field_set_register(ETXNDL, mask); /* BFS */
	myprintf("\nBFS, ETXNDL expected:%d\n", data);
	myprintf("\nRead ETXNDL:%d\n", EE_enc28j60_read_ETH_register(ETXNDL).Val);
	
	/* ---------------------------------------------------------------- */
	/* BANK SELECTION */
	EE_enc28j60_bank_select(MACLCON1);
	myprintf("\nWrite bank:%d\n", BANK2);
	myprintf("\nRead ECON1:%d\n", EE_enc28j60_read_ETH_register(ECON1).Val);
	
	/* ---------------------------------------------------------------- */
	/* MAC */
	data = 0x02;
	EE_enc28j60_write_register((BYTE)MACLCON1, data);
	myprintf("\nWrite MACLCON1:%d\n", data);
	myprintf("\nRead MACLCON1:%d\n", EE_enc28j60_read_MAC_MII_register((BYTE)MACLCON1).Val);
	
	/* ---------------------------------------------------------------- */
	/* MII */
	data = 0x03;
	EE_enc28j60_write_register((BYTE)MIREGADR, data);
	myprintf("\nWrite MIREGADR:%d\n", data);
	myprintf("\nRead MIREGADR:%d\n", EE_enc28j60_read_MAC_MII_register((BYTE)MIREGADR).Val);

	/* ---------------------------------------------------------------- */
	/* PHY */
	EE_UINT32 phy_data = 0x3332;

	EE_enc28j60_write_PHY_register(PHLCON, phy_data);
	myprintf("\nWrite PHLCON:%x\n", phy_data);
	myprintf("\nRead PHLCON:%x\n", EE_enc28j60_read_PHY_register((BYTE)PHLCON).Val);
	
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
	/* SPI configuration         */
	/* -------------------------- */
	EE_net_spi_config(0);
	
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
	device_config();
	SetRelAlarm(myAlarm1, 1000, 1000);
	EE_timer_on();
	
	while(1)
	;
	
	return 0;
}









