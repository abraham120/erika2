/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 *
 * Author: 2010,  Christian Grioli
 * Uart header file.
*/

#ifndef __INCLUDE_MSP430_UART_H__
#define __INCLUDE_MSP430_UART_H__

#include "ee.h"


#ifdef __MSP430_1611__


/*Setting info*/

/*Port Information */
#define EE_UART_PORT_1	0
#define EE_UART_PORT_2	1

/*Byte format information*/
#define EE_UART_BIT7 (0x00)
#define EE_UART_BIT8 (0x10)
#define EE_UART_ODD  (0x00)
#define EE_UART_EVEN (0x40)
#define EE_UART_PARITY_ENABLE (0x80)
#define EE_UART_2STOP_BIT (0X20)
#define EE_UART_1STOP_BIT (0X00)


/*Mode information*/

#define EE_UART_POLLING     (0x00)  // polling mode
#define EE_UART_RX_ISR      (0x01)  // Reception IRQ enabled 
#define EE_UART_TX_ISR      (0x02)  // Transmission IRQ enabled 
#define EE_UART_RXTX_ISR    (0x03)  // Transmission/Reception IRQ enabled 
/*Only polling mode*/
#define EE_UART_RX_BLOCK    (0x10)  // Blocking mode in reception
#define EE_UART_TX_BLOCK    (0x20)  // Blocking mode in transmission
#define EE_UART_RXTX_BLOCK  (0x30)  // Blocking mode in transmission/reception

#define EE_UART_UCLK 	    (0x0000)
#define EE_UART_UCLK_INVERTED (0x4000)
#define EE_UART_UCLK_SOURCE  (0x0000)
#define EE_UART_ACLK_SOURCE  (0x1000)
#define EE_UART_SMCLK_SOURCE  (0x2000)
#define EE_UART_CTRL_ERROR (0x0040)

#define EE_UART_START_EDGE  (0x08) /*Only with interrupt and only on callback rxmode*/


/*Macro for testing mode information*/

#define EE_UART_IS_POLLING(mode) (mode & EE_UART_POLLING)
#define EE_UART_IS_RX_ISR(mode) (mode & EE_UART_RX_ISR)
#define EE_UART_IS_TX_ISR(mode) (mode & EE_UART_TX_ISR)
#define EE_UART_IS_RXTX_ISR(mode) (mode & EE_UART_RXTX_ISR)
#define EE_UART_IS_RX_BLOCK(mode)    (mode & EE_UART_RX_BLOCK)
#define EE_UART_IS_TX_BLOCK(mode)   (mode & EE_UART_TX_BLOCK)
#define EE_UART_IS_RXTX_BLOCK(mode)  (mode & EE_UART_RXTX_BLOCK)

/*Uart error*/
#define EE_UART_NO_ERROR		( 1)	//Used as positive
#define EE_UART_ERR_BAD_PORT		(-1)
#define EE_UART_ERR_BAD_BAUD_VALUE      (-2)
#define EE_UART_ERR_TX_NOT_READY    	(-3)
#define EE_UART_ERR_RX_NOT_READY    	(-4)
#define EE_UART_ERR_INT_MODE    	(-5)
#define EE_UART_ERR_FRAME		(-6)
#define EE_UART_ERR_PARITY		(-7)
#define EE_UART_ERR_OVERRUN		(-8)
#define EE_UART_ERR_BREAK_CONDITION	(-9)
#define EE_UART_ERR_FUNCTION_NULL	(-10)
#define EE_UART_ERR_INT_DISABLED	(-11)

/*Function*/
EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format, 
		     EE_UINT16 mode);
EE_INT8 EE_uart_close(EE_UINT8 port);
EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data);
EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data);
EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), EE_UINT8 rxmode);
EE_INT8 EE_uart_set_tx_callback(EE_UINT8 port, void (*TxFunc)(volatile EE_UINT8* regs), EE_UINT8 txmode);


EE_INT8 EE_uart_set_baud(EE_UINT32* baud, EE_UINT16 baud_value);
EE_INT8 EE_uart_set_modulation(EE_UINT32* baud, EE_UINT8 modulation_value);
EE_INT8 EE_uart_print_error(EE_UINT8 port);



#endif

#endif
