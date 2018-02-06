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
    @file      test2_main.c
    @brief     Uart polling test(non-blocking mode).
               This demo shows how to use UART driver for
               Lattice Mico32 device to send and receive characters. 
               The UART controller is configured in polling mode and non-blocking mode. 
               When task calls EE_uart_receive_byte, the UART driver checks if 
               there are characters to be read. If yes the application sends 
               the received character, otherwise sends 'X'.    
               In case of error the application turns on the system led.
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

TASK(myTask)
{
	EE_UINT8 myArray[5];

	/* Single byte test */
	myArray[0] = 'A';
	if( EE_uart_send_byte(myArray[0]) < 0 )
	{
		EE_led_on(EE_SERIO_SYSTEM_LED);
		while(1)
			;
	}
	if( EE_uart_receive_byte(myArray) < 0 )
	{
		while( !(ee_uart_st.base->lsr & MICOUART_LSR_TX_RDY_MASK) )
			;
		if( EE_uart_send_byte('X') < 0 )
		{
			EE_led_on(EE_SERIO_SYSTEM_LED);
			while(1)
				;
		}
	}
	else
	{
		while( !(ee_uart_st.base->lsr & MICOUART_LSR_TX_RDY_MASK) )
			;
		if( EE_uart_send_byte(myArray[0]) < 0 )
		{
			EE_led_on(EE_SERIO_SYSTEM_LED);
			while(1)
				;
		}
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
	EE_uart_set_ISR_mode(EE_UART_POLLING); // polling, non-blocking mode  
	
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
	SetRelAlarm(myAlarm, 2500, 2500);
	EE_timer_on();
	while(1)
		;

	return 0;
}


