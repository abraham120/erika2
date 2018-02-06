/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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

#include <ee_irq.h>

#include "nrf.h"
#include "nrf_gpio.h"
#include "mcu/nordic_nrf51x22/inc/ee_uart.h"
#include "mcu/nordic_nrf51x22/inc/ee_ring_buffer.h"

//------------------------------------------------------------------

EE_RING_BUFFER_ALLOC(mem_area_txd,EE_UART_RING_BUFFER_SIZE_TXD);
EE_RING_BUFFER_ALLOC(mem_area_rxd,EE_UART_RING_BUFFER_SIZE_RXD);

EE_type_ring_buffer ring_buff_txd;
EE_type_ring_buffer ring_buff_rxd;

//------------------------------------------------------------------

#ifndef EE_BOARD_UART_TXD_PIN
#error Board not defined
#endif

#ifndef EE_BOARD_UART_RXD_PIN
#error Board not defined
#endif

#ifndef EE_BOARD_UART_CTS_PIN
#error Board not defined
#endif

#ifndef EE_BOARD_UART_RTS_PIN
#error Board not defined
#endif

//------------------------------------------------------------------


EE_UINT8 EE_uart_get(void)
{

  EE_UINT8 data;
  
  /* Polling on ring buffer */
  while (1)
  {
	NVIC_DisableIRQ(UART0_IRQn);
	if(!EE_ring_buffer_isempty(ring_buff_rxd)) {
		data = EE_ring_buffer_get(&ring_buff_rxd);
		NVIC_EnableIRQ(UART0_IRQn);
		break;
	}
	NVIC_EnableIRQ(UART0_IRQn);
  }
  
  return data;
}


ISR1(EE_UART0_IRQHandler)
{
	
	// Handle reception
    if (NRF_UART0->EVENTS_RXDRDY != 0)
    {
		NRF_UART0->EVENTS_RXDRDY=0; 		/* Clear UART RX event flag */
		EE_ring_buffer_put(&ring_buff_rxd, (EE_UINT8)NRF_UART0->RXD);
	}
	
	// Handle transmission
    if (NRF_UART0->EVENTS_TXDRDY != 0)
    {
		NRF_UART0->EVENTS_TXDRDY=0; 		/* Clear UART TX event flag */
		EE_ring_buffer_get(&ring_buff_txd);
		if(!EE_ring_buffer_isempty(ring_buff_txd))
			NRF_UART0->TXD = EE_ring_buffer_head(ring_buff_txd);
			
	}
}


//------------------------------------------------------------------

void EE_uart_send(EE_UINT8 c)
{
	NVIC_DisableIRQ(UART0_IRQn);
	if(EE_ring_buffer_isempty(ring_buff_txd))
		NRF_UART0->TXD = c;
		
	EE_ring_buffer_put(&ring_buff_txd, c);
	NVIC_EnableIRQ(UART0_IRQn);
}

//AB - FIXME: check on string size?
EE_INT8 EE_uart_send_str(char *str)
{
	EE_INT8 error = EE_UART_NO_ERRORS;
	EE_UINT8 i=0;
	
	if(str[0]=='\0') 
		error = EE_UART_EMPTY_STR;
	
	if(!error) 
	{
		NVIC_DisableIRQ(UART0_IRQn);
		if(EE_ring_buffer_isempty(ring_buff_txd))
			NRF_UART0->TXD = (EE_UINT8)str[0];
			
		do {
			EE_ring_buffer_put(&ring_buff_txd, str[i]);
		} while(str[++i]!='\0');
		
		NVIC_EnableIRQ(UART0_IRQn);
	}
	
	return error;
}

//------------------------------------------------------------------

EE_INT8 EE_uart_init(EE_UartBaudrate baudrate, EE_UINT8 use_parity, EE_UINT8 use_cf)
{
	EE_INT8 error = EE_UART_NO_ERRORS;
	
	if(use_cf)
		error = EE_UART_ERR_UNIMPLEMENTED;
	
	if(!error)
	{
		/* Ring buffers initialization */
		EE_ring_buffer_init(&ring_buff_txd, mem_area_txd, EE_UART_RING_BUFFER_SIZE_TXD);
		EE_ring_buffer_init(&ring_buff_rxd, mem_area_rxd, EE_UART_RING_BUFFER_SIZE_RXD);
		
		
		/* Configure UART GPIO */
		nrf_gpio_cfg_output(EE_BOARD_UART_TXD_PIN);
		nrf_gpio_cfg_input (EE_BOARD_UART_RXD_PIN, NRF_GPIO_PIN_NOPULL);  
		nrf_gpio_cfg_output(EE_BOARD_UART_RTS_PIN);
		nrf_gpio_cfg_input (EE_BOARD_UART_CTS_PIN, NRF_GPIO_PIN_NOPULL);
		
		/*NRF_UART0->PSELRTS = EE_UART_PIN_DISCONNECTED;
		NRF_UART0->PSELCTS = EE_UART_PIN_DISCONNECTED;*/
		/* Bugfix to fix crash with pin disconnected - AB: FIXME */
		NRF_UART0->PSELCTS = EE_BOARD_UART_CTS_PIN;
		NRF_UART0->PSELRTS = EE_BOARD_UART_RTS_PIN;
		
		NRF_UART0->PSELTXD = EE_BOARD_UART_TXD_PIN;
		NRF_UART0->PSELRXD = EE_BOARD_UART_RXD_PIN;
		
		
		/* Configure Baudrate */
		NRF_UART0->BAUDRATE = (baudrate << UART_BAUDRATE_BAUDRATE_Pos);
		
		/* Parity bit configuration */
		if(use_parity)
			NRF_UART0->CONFIG = (UART_CONFIG_PARITY_Included << UART_CONFIG_PARITY_Pos);
		else
			NRF_UART0->CONFIG = (UART_CONFIG_PARITY_Excluded << UART_CONFIG_PARITY_Pos);
			
		NRF_UART0->ENABLE        = (UART_ENABLE_ENABLE_Enabled << UART_ENABLE_ENABLE_Pos);
		NRF_UART0->EVENTS_RXDRDY = 0;
		NRF_UART0->EVENTS_TXDRDY = 0;

		//NRF_UART0->CONFIG       &= ~(UART_CONFIG_HWFC_Enabled << UART_CONFIG_HWFC_Pos);	
		NRF_UART0->CONFIG  = (UART_CONFIG_HWFC_Disabled << UART_CONFIG_HWFC_Pos); 

		NRF_UART0->TASKS_STARTTX = 1;
		NRF_UART0->TASKS_STARTRX = 1;	
		
		/* Enable UART interrupt */
		NRF_UART0->INTENCLR = 0xffffffffUL;
		NRF_UART0->INTENSET = (UART_INTENSET_TXDRDY_Set << UART_INTENSET_TXDRDY_Pos) | 
							  (UART_INTENSET_RXDRDY_Set << UART_INTENSET_RXDRDY_Pos);
		/*NRF_UART0->INTENSET = (UART_INTENSET_RXDRDY_Set << UART_INTENSET_RXDRDY_Pos) |
							  (UART_INTENSET_TXDRDY_Set << UART_INTENSET_TXDRDY_Pos) |
							  (UART_INTENSET_ERROR_Set << UART_INTENSET_ERROR_Pos);*/

		NVIC_ClearPendingIRQ(UART0_IRQn);
		NVIC_EnableIRQ(UART0_IRQn);
	}
	
	return error;

}

