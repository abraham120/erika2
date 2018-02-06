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
 * Author: 2014,  Martin Hoffmann
 * Uart header file.
*/

#ifndef __INCLUDE_X86_UART_H__
#define __INCLUDE_X86_UART_H__

#include "ee.h"

#ifdef __X86__

#define COM1 (0x03f8)
#define COM2 (0x02f8)
#define COM3 (0x03e8)
#define COM4 (0x02f8)


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
EE_INT8 EE_uart_init(EE_UINT16 port);

//EE_INT8 EE_uart_init(EE_UINT16 port, EE_UINT32 baud, EE_UINT16 byte_format, 
		     //EE_UINT16 mode);
//EE_INT8 EE_uart_close(EE_UINT16 port);
EE_INT8 EE_uart_write_byte(EE_UINT16 port, EE_UINT8 data);
void EE_uart_puts(EE_UINT16 port, char * data);
//EE_INT8 EE_uart_read_byte(EE_UINT16 port, EE_UINT8 *data);
//EE_INT8 EE_uart_set_rx_callback(EE_UINT16 port, void (*RxFunc)(EE_UINT8 data), EE_UINT8 rxmode);
//EE_INT8 EE_uart_set_tx_callback(EE_UINT16 port, void (*TxFunc)(volatile EE_UINT8* regs), EE_UINT8 txmode);


//EE_INT8 EE_uart_set_baud(EE_UINT32* baud, EE_UINT16 baud_value);
//EE_INT8 EE_uart_set_modulation(EE_UINT32* baud, EE_UINT8 modulation_value);
//EE_INT8 EE_uart_print_error(EE_UINT16 port);



#endif

#endif
