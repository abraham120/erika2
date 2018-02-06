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
    @file ee_uart.h
    @brief UART driver header file.
 **/
 
#ifndef __INCLUDE_MICROCHIP_DSPIC_UART_H__
#define __INCLUDE_MICROCHIP_DSPIC_UART_H__

#include "ee.h"

/* Include a file with the registers from Microchip C30 distribution */
#ifdef __PIC30_INCLUDE_REGS__
#include "ee_pic30regs.h"
#endif

#define EE_UART_BIT9        0x06
#define EE_UART_BIT8_ODD    0x04
#define EE_UART_BIT8_EVEN   0x02
#define EE_UART_BIT8_NO     0x00

#define EE_UART_BIT_STOP_1  0x00
#define EE_UART_BIT_STOP_2  0x01

#define EE_UART_CTRL_SIMPLE 0x00
#define EE_UART_CTRL_FLOW   0x01

#define EE_UART_TX_INT_EMPTY    0x8000
#define EE_UART_TX_INT_LAST     0x2000
#define EE_UART_TX_INT_SINGLE   0x0000

#define EE_UART_RX_INT_FULL     0x00C0
#define EE_UART_RX_INT_3OF4     0x0080
#define EE_UART_RX_INT_SINGLE   0x0040

#define EE_UART_PORT_1    0
#define EE_UART_PORT_2    1

#define EE_UART_OK                  0
#define EE_UART_ERR_BAD_PORT        -1
#define EE_UART_ERR_NO_DATA         -2
#define EE_UART_ERR_OVERFLOW        -3
#define EE_UART_ERR_INT_MODE        -4
#define EE_UART_ERR_INT_DISABLED    -5

EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format,
             EE_UINT16 mode);
EE_INT8 EE_uart_close(EE_UINT8 port);
EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data);
EE_INT8 EE_uart_write_byte_async(EE_UINT8 port, EE_UINT8 data);
EE_INT8 EE_uart_write_string(EE_UINT8 port, const char* str);
EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data);
EE_INT8 EE_uart_read_byte_async(EE_UINT8 port, EE_UINT8 *data);
EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data), EE_UINT16 rxmode);
EE_INT8 EE_uart_set_tx_callback(EE_UINT8 port, void (*TxFunc)(void), EE_UINT16 txmode);

__INLINE__ EE_BIT EE_uart_byte_available(EE_UINT8 port)
{
    EE_BIT available = 0;
    if (port == EE_UART_PORT_1) {
        available = U1STAbits.URXDA;
    } else if (port == EE_UART_PORT_2) {
        available = U2STAbits.URXDA;
    } 
    return available;
}

/**
    @brief Critical Section macros
    @ {
**/
#ifdef USE_UART_CRITICAL_SECTIONS
#if defined(__dsPIC33F__)
#   define CRITICAL_SECTION_UART1_RXSTART()  do{ IEC0bits.U1RXIE = 0; }while(0)
#   define CRITICAL_SECTION_UART1_RXEND()    do{ IEC0bits.U1RXIE = 1; }while(0)
#   define CRITICAL_SECTION_UART1_TXSTART()  do{ IEC0bits.U1TXIE = 0; }while(0)
#   define CRITICAL_SECTION_UART1_TXEND()    do{ IEC0bits.U1TXIE = 1; }while(0)
#else 
#   error "Unsupported Architecture"
#endif
#endif /* USE_UART_CRITICAL_SECTIONS */
/** @} **/

#endif /*__INCLUDE_MICROCHIP_DSPIC_UART_H__ */
