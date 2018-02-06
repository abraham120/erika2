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
    @file      test3_main.c
    @brief     Uart isr test(isr, blocking mode).
               This demo shows how to use UART driver for
               Lattice Mico32 device to send and receive characters. 
               The UART controller is configured in ISR mode and in 
               blocking mode for tx and rx.
               The demo is as shown in test1 but the led is turned on/off
               in the ISR callbacks. 
               The demo requires a RS232 serial connection with a 115200 bps,8N1 configuration.
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

volatile int rx_cbk_counter = 0;
volatile int tx_cbk_counter = 0;


TASK(myTask)
{
	EE_UINT8 myArray[5];

	/* Single byte test */
	myArray[0] = 'A';
	if( EE_uart_send_byte(myArray[0]) < 0 )
		while(1)
			;
	if( EE_uart_receive_byte(myArray) < 0 )
		while(1)
			;
	else
		if( EE_uart_send_byte(myArray[0]) < 0 )
			while(1)
				;

	/* Array test */
	myArray[0] = 'A';
	myArray[1] = 'B';
	myArray[2] = 'C';
	myArray[3] = 'D';
	myArray[4] = 'E';
	if( EE_uart_send_buffer(myArray, 5) < 0 )
		while(1)
			;
	if( EE_uart_receive_buffer(myArray, 5) < 0 )
		while(1)
			;
	else
		if( EE_uart_send_buffer(myArray, 5) < 0 )
			while(1)
				;
}

void rx_cbk(void)
{
	EE_led_off(EE_SERIO_SYSTEM_LED);
	rx_cbk_counter++; 
}

void tx_cbk(void)
{
	EE_led_on(EE_SERIO_SYSTEM_LED);
	tx_cbk_counter++; 
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
	EE_uart_set_rx_ISR_callback(rx_cbk);
	EE_uart_set_tx_ISR_callback(tx_cbk);
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_RXTX_ISR | EE_UART_RXTX_BLOCK); // polling, blocking mode  
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	EE_led_init();
	while(1)
		ActivateTask(myTask);

	return 0;
}

