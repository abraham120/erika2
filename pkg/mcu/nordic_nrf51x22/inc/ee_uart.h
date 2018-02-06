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

/**
    @file   ee_uart.h
    @brief  UART library header file for Nordic NRF51x22.

    This UART driver uses a static ring buffer and interrupts 
	to provide a non-blocking wirte API.
	Read operation is implemented in the same manner but it has
	a blocking API.

    @author Alessandro Biondi
    @date   2013

**/

#ifndef __INCLUDE_NORDIC_NRF51X22_UART_H__
#define __INCLUDE_NORDIC_NRF51X22_UART_H__

#include "ee.h"

#include "mcu/nordic_nrf51x22/inc/ee_utils.h"

/** UART Badurates **/
typedef enum _EE_UartBaudrate {
	EE_UART_BAUDRATE_1200	=(0x0004F000UL), /* 1200 baud. */
	EE_UART_BAUDRATE_2400	=(0x0009D000UL), /* 2400 baud. */
	EE_UART_BAUDRATE_4800 	=(0x0013B000UL), /* 4800 baud. */
	EE_UART_BAUDRATE_9600 	=(0x00275000UL), /* 9600 baud. */
	EE_UART_BAUDRATE_14400 	=(0x003B0000UL), /* 14400 baud. */
	EE_UART_BAUDRATE_19200 	=(0x004EA000UL), /* 19200 baud. */
	EE_UART_BAUDRATE_28800 	=(0x0075F000UL), /* 28800 baud. */
	EE_UART_BAUDRATE_38400 	=(0x009D5000UL), /* 38400 baud. */
	EE_UART_BAUDRATE_57600 	=(0x00EBF000UL), /* 57600 baud. */
	EE_UART_BAUDRATE_76800 	=(0x013A9000UL), /* 76800 baud. */
	EE_UART_BAUDRATE_115200 =(0x01D7E000UL), /* 115200 baud. */
	EE_UART_BAUDRATE_230400 =(0x03AFB000UL), /* 230400 baud. */
	EE_UART_BAUDRATE_250000 =(0x04000000UL), /* 250000 baud. */
	EE_UART_BAUDRATE_460800 =(0x075F7000UL), /* 460800 baud. */
	EE_UART_BAUDRATE_921600 =(0x0EBEDFA4UL), /* 921600 baud. */
	EE_UART_BAUDRATE_1M 	=(0x10000000UL) /* 1M baud. */
} EE_UartBaudrate;


#define  EE_UART_PIN_DISCONNECTED  0xFFFFFFFFUL

/** error value. No errors happened **/
#define EE_UART_NO_ERRORS           0
#define EE_UART_ERR_BAD_ARGS       -1
#define EE_UART_EMPTY_STR	       -3
/** error value. Uart is supposed to exist but is not yet implemented **/
#define EE_UART_ERR_UNIMPLEMENTED  -10


#define EE_UART_DEFAULT_RING_BUFFER_SIZE  32

#ifndef EE_UART_RING_BUFFER_SIZE_TXD
#define EE_UART_RING_BUFFER_SIZE_TXD EE_UART_DEFAULT_RING_BUFFER_SIZE 
#endif

#ifndef EE_UART_RING_BUFFER_SIZE_RXD
#define EE_UART_RING_BUFFER_SIZE_RXD EE_UART_DEFAULT_RING_BUFFER_SIZE 
#endif

/**
    @brief Initialization UART procedure.

    @param baudrate (EE_UartBaudrate): UART baud rate
    @param use_parity (EE_UINT8): flag for enable parity bit
    @param use_cf (EE_UINT8): flag for enable flux control

    @return EE_UART_NO_ERRORS if no errors happend.
        Otherwise appropriate error value.
 */
EE_INT8 EE_uart_init(EE_UartBaudrate baudrate, EE_UINT8 use_parity, EE_UINT8 use_cf);

/**
    @brief Send a byte through UART.

    @param c (EE_UINT8): The byte that is sent

    @return none
 */
void EE_uart_send(EE_UINT8 c);

/**
    @brief Send a string through UART.

    @param str (*EE_UINT8): The string that is sent

    @return EE_UART_NO_ERRORS if no errors happend.
        Otherwise appropriate error value.
 */
EE_INT8 EE_uart_send_str(char *str);


EE_UINT8 EE_uart_get(void);

#endif /* __INCLUDE_NORDIC_NRF51X22_UART_H__ */

