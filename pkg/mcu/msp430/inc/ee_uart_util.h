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
 * Author: 2010,  Christian Grioli
 * Uart implementation utility.
 */


#include "mcu/msp430/inc/ee_uart.h"
#include "cpu/msp430/inc/ee_irqstub.h"
#include <msp430/usart.h>

/*Select the byte information*/
#define EE_BYTE_FORMAT_INFO 0xF0
/*Select the baud and modulation information*/
#define EE_UxMCTL_value(v) (EE_UINT8)(v>>16)
#define EE_UxBR0_value(v) (EE_UINT8)(v)
#define EE_UxBR1_value(v) (EE_UINT8)(v>>8)

/*Enable Tx/Rx module*/
#define EE_UART_TX_RX_ENABLE_1 0xC0
#define EE_UART_TX_RX_ENABLE_2 0x30
/*Enable control error*/
#define EE_UART_SET_CTRL_ERROR 0x08

/*Control if the feature is enable*/
#define EE_UART_IS_ERROR 0x01
#define EE_UART_IS_FRAME_ERROR 0x80
#define EE_UART_IS_PARITY_ERROR 0x40
#define EE_UART_IS_OVERRUN_ERROR 0x20
#define EE_UART_IS_BREAK_DETECT 0x10
#define EE_UART_IS_START_EDGE_1 0x40
#define EE_UART_IS_START_EDGE_2 0x10

/*Set the UART pin direction and selection*/ 
#define EE_UART_SEL_TXD_RXD_1 0x18
#define EE_UART_SEL_TXD_RXD_2 0xC0
#define EE_UART_DIR_TXD_RXD_1 0x08
#define EE_UART_DIR_TXD_RXD_2 0x40

/*Enable Tx/Rx ISR*/
#define EE_UART_SET_TX_ISR_1 0x80
#define EE_UART_SET_RX_ISR_1 0x40
#define EE_UART_SET_TX_ISR_2 0x20
#define EE_UART_SET_RX_ISR_2 0x10

