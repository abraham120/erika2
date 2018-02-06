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


#include "mcu/microchip_dspic/inc/ee_uart_cbuffer.h"


/* Callback functions for UART */
static EE_UART_CBuffer_callback_Rx  uart_rx_callback  = NULL;
static EE_UART_CBuffer_callback_EOT uart_eot_callback = NULL;

/* UART status */
#define UART_STATUS_TX_OFF 0
#define UART_STATUS_TX_ON  1
static volatile EE_BIT uart_status;

/* UART receive and transmit buffers */
static EE_CBuffer rx_buffer;
static EE_CBuffer tx_buffer;

/* Internal ram space allocation for RX and TX buffers */
static EE_UINT8 __attribute__((far)) uart_rx_data[ UART_CBUFFER_RX_BUFFER_SIZE ] = {};
static EE_UINT8 __attribute__((far)) uart_tx_data[ UART_CBUFFER_TX_BUFFER_SIZE ] = {};

/*
    Utility to push a byte in RX buffer
    If needed I'll discard the oldest byte
 */
static void push_rx_buffer(EE_UINT8 data_in)
{
    if(!EE_cbuffer_available(&rx_buffer, sizeof(EE_UINT8))){
        EE_UINT8 pop_temp;
        EE_cbuffer_pop(&rx_buffer, &pop_temp, sizeof(EE_UINT8));
    }
    EE_cbuffer_push(&rx_buffer, &data_in, sizeof(EE_UINT8));
}

/*
    UART1 Reception interrupt handler.
    Whithin it we don't need critical sections as the concurrent task accessing
    uart1's buffer cannot interrupt an ISR.

    This wrapper is needed as work around of _U1RXInterrupt implementation in
    uart driver
*/
static void uart_rx_callback_wrapper (EE_UINT8 data_in)
{
    do {
        /* push received byte in buffer */
        push_rx_buffer(data_in);

        /* If needed: asynchronous notification */
        if(uart_rx_callback != NULL)
            uart_rx_callback(data_in);
            
        /* Read data from hardware's uart buffer until data are available */
        if(EE_uart_byte_available(EE_CBUF_UART_PORT))
            EE_uart_read_byte_async(EE_CBUF_UART_PORT, &data_in);
        else
            break;
    } while(1);
}

/*
    UART1 Transmition completion interrupt handler.
    Whithin it we don't need critical sections as the concurrent task accessing
    uart1's buffer cannot interrupt an ISR.

    This wrapper is needed as work around of _U1TXInterrupt implementation in
    uart driver
*/
static void uart_eot_callback_wrapper(void)
{
    EE_UINT8 data_out;
    if(uart_status == UART_STATUS_TX_ON){
        if(EE_cbuffer_contains(&tx_buffer, sizeof(EE_UINT8))){
            /* Transmit buffer still has data available, send frontmost byte */
            EE_cbuffer_pop(&tx_buffer, &data_out, sizeof(EE_UINT8));
            EE_uart_write_byte_async(EE_CBUF_UART_PORT, data_out);
        } else {
            /* Transmit buffer is empty, end transmission */
            uart_status = UART_STATUS_TX_OFF;

            /* Activate callback */
            if(uart_eot_callback != NULL)
                uart_eot_callback();
        }
    }
}

/**
    @brief initialize UART C-Buffer withj default values
 **/
EE_INT8 EE_uart_cbuffer_init(EE_UART_CBuffer_callback_Rx uart_rx, EE_UART_CBuffer_callback_EOT uart_eot)
{
    return EE_uart_cbuffer_complete_init(uart_rx, uart_eot, 115200, EE_UART_BIT_STOP_1 | EE_UART_BIT8_NO, EE_UART_CTRL_SIMPLE);
}

EE_INT8 EE_uart_cbuffer_complete_init(EE_UART_CBuffer_callback_Rx uart_rx, EE_UART_CBuffer_callback_EOT uart_eot, EE_UINT32 baud, EE_UINT16 byte_format,
    EE_UINT16 mode)
{
    /* save the callbacks */
    uart_rx_callback  = uart_rx;
    uart_eot_callback = uart_eot;

    /* Init state */
    uart_status = UART_STATUS_TX_OFF;

    /* Initialize the Uart RX and TX Buffers */
    EE_cbuffer_init(&rx_buffer, UART_CBUFFER_RX_BUFFER_SIZE, uart_rx_data);
    EE_cbuffer_init(&tx_buffer, UART_CBUFFER_TX_BUFFER_SIZE, uart_tx_data);

    /* UART initialization */
    EE_uart_init(EE_CBUF_UART_PORT, baud, byte_format, mode);
    EE_uart_set_rx_callback(EE_CBUF_UART_PORT, uart_rx_callback_wrapper, EE_UART_RX_INT_SINGLE);
    EE_uart_set_tx_callback(EE_CBUF_UART_PORT, uart_eot_callback_wrapper, EE_UART_TX_INT_SINGLE);

    return 0;
}

void EE_uart_cbuffer_reset_rx(void)
{
    /* This is enough to reset a C-Buffer */
    rx_buffer.counter = 0;
}

EE_CBuffer * EE_uart_cbuffer_get_rx_buffer(void)
{
    return &rx_buffer;
}


EE_CBuffer * EE_uart_cbuffer_get_tx_buffer(void)
{
    return &tx_buffer;
}


EE_CBufferError EE_uart_cbuffer_push_tx(const void * tx_data, EE_UINT16 data_length)
{
    EE_CBufferError error = EE_CBUFF_OK;

    CRITICAL_SECTION_UART1_TXSTART();
    error = EE_cbuffer_push(&tx_buffer, tx_data, data_length);
    CRITICAL_SECTION_UART1_TXEND();

    return error;
}


void EE_uart_cbuffer_trigger_tx( void ){
    EE_UINT8 data_out;

    CRITICAL_SECTION_UART1_TXSTART();
    if(uart_status != UART_STATUS_TX_ON){
        if(tx_buffer.counter){
            /* Enable and start transmition */
            uart_status = UART_STATUS_TX_ON;
            EE_cbuffer_pop(&tx_buffer, &data_out, sizeof(EE_UINT8));
            EE_uart_write_byte_async(EE_CBUF_UART_PORT, data_out);
        }
    }
    CRITICAL_SECTION_UART1_TXEND();
}


EE_CBufferError EE_uart_cbuffer_receive(void * rx_data, EE_UINT16 data_length)
{
    EE_CBufferError error;

    CRITICAL_SECTION_UART1_RXSTART();
    error = EE_cbuffer_pop(&rx_buffer, rx_data, data_length);
    CRITICAL_SECTION_UART1_RXEND();

    return error;
}

#ifdef CONFIG_UART_CBUFFER_PRINTF
#include <stdio.h>
#include <stdarg.h>
char __attribute__((far)) printf_buffer[UART1_PRINTF_BUFFER_SIZE];

EE_UINT16 EE_uart_cbuffer_printf(char *fmt, ...){
    va_list args;
    EE_UINT16 tmp, i;

    /* Format String. */
    va_start(args, fmt);
    tmp = vsprintf(printf_buffer, fmt, args);
    va_end(args);

    /* Push data */
    EE_uart_cbuffer_push_tx(printf_buffer, UART1_PRINTF_BUFFER_SIZE);

    /* Start Sending */
    EE_uart_cbuffer_trigger_tx();

    return tmp;
}
#endif /* CONFIG_UART_CBUFFER_PRINTF */
