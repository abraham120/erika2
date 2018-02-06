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
    @file ee_uart_cbuffer.h
    @brief UART driver with cicular buffer support in RX/TX.
    
    UART driver with cicular buffer for transmission and reception. it support asynchronus behaviour 
    with interrupts.
    
    == ATTENTION ==
    This driver stack up to Erika dsPIC UART driver (defined by ee_uart.h)
    
    @author Errico Guidieri
    @date 2011
**/ 
 
#ifndef __INCLUDE_MICROCHIP_DSPIC_UART_CBUFFER_H__
#define __INCLUDE_MICROCHIP_DSPIC_UART_CBUFFER_H__

#if defined(__EE_UART_PORT1_CBUFFER__)

#define EE_CBUF_UART_PORT EE_UART_PORT_1

#ifndef EE_UART_PORT_1_ISR_ENABLE
#error "You MUST define EE_UART_PORT_1_ISR_ENABLE as compilation define\
 to work with ee_uart_cbuffer driver in UART Port 1"
#endif

#elif defined(__EE_UART_PORT2_CBUFFER__)

#define EE_CBUF_UART_PORT EE_UART_PORT_2

#ifndef EE_UART_PORT_2_ISR_ENABLE
#error "You MUST define EE_UART_PORT_2_ISR_ENABLE as compilation define\
 to work with ee_uart_cbuffer driver in UART Port 2"
#endif

#else /* !__EE_UART_PORT1_CBUFFER__ && !__EE_UART_PORT2_CBUFFER__ */

#error "UART port not specified or not supported by CBUFFER!"

#endif /* __EE_UART_PORT1_CBUFFER__ || __EE_UART_PORT2_CBUFFER__ */

#ifndef UART_CBUFFER_RX_BUFFER_SIZE
#define UART_CBUFFER_RX_BUFFER_SIZE 64
#endif /* UART_CBUFFER_RX_BUFFER_SIZE */

#ifndef UART_CBUFFER_TX_BUFFER_SIZE
#define UART_CBUFFER_TX_BUFFER_SIZE 64
#endif /* UART_CBUFFER_RX_BUFFER_SIZE */

#ifndef USE_UART_CRITICAL_SECTIONS
#define USE_UART_CRITICAL_SECTIONS
#endif /* USE_UART_CRITICAL_SECTIONS */

#include "ee_uart.h"
#include "ee_cbuffer.h"

/** Types for pointers to functions @{ **/
typedef void ( *EE_UART_CBuffer_callback_Rx )( EE_UINT8 data ); /** link to the function called every byte received by uart **/
typedef void ( *EE_UART_CBuffer_callback_EOT )( void ); /** link to function called at end of packet trasmission **/
/** @} **/

/**
    @brief initialize UART C-Buffer driver with default values an start it
    
    Initialize UART with following values:
    baudrate:    115200, 
    byte_format: EE_UART_BIT_STOP_1 | EE_UART_BIT8_NO, 
    ctrl_mode:   EE_UART_CTRL_SIMPLE
    
    @param uart_rx: callback pointer to be notified for each received byte (can be NULL)
    @param uart_eot: callback pointer to be when a transmission is end (can be NULL)
 **/
EE_INT8 EE_uart_cbuffer_init(EE_UART_CBuffer_callback_Rx uart_rx, EE_UART_CBuffer_callback_EOT uart_eot);

/**
    @brief initialize and start UART C-Buffer driver

    @param uart_rx: callback pointer to be notified for each received byte (can be NULL)
    @param uart_eot: callback pointer to be when a transmission is end (can be NULL)
    @param baud: UART baudrate, 
    @param byte_format: UART byte format 
    @param ctrl_mode:  UART control mode
 **/
EE_INT8 EE_uart_cbuffer_complete_init(EE_UART_CBuffer_callback_Rx uart_rx, EE_UART_CBuffer_callback_EOT uart_eot, EE_UINT32 baud, EE_UINT16 byte_format,
    EE_UINT16 mode);

    /** @brief Stop UART C-Buffer driver **/    
__INLINE__ EE_INT8 EE_uart_cbuffer_close(){
    return EE_uart_close(EE_CBUF_UART_PORT);
}

/** @brief reset the receive buffer **/
void EE_uart_cbuffer_reset_rx(void);

/** @brief Returns the Receive Buffer Structure **/
EE_CBuffer * EE_uart_cbuffer_get_rx_buffer(void);

/** @brief Returns the Trasmit Buffer Structure **/
EE_CBuffer * EE_uart_cbuffer_get_tx_buffer(void);

/** @brief Add data to uart tx buffer. **/
EE_CBufferError EE_uart_cbuffer_push_tx(const void * tx_data, EE_UINT16 data_length);

/** @brief Triggers transmission.

    Triggers transmission. If the transmission is already on, 
    or if there is nothing to send, it does nothing
**/
void EE_uart_cbuffer_trigger_tx(void);

/** @brief Gets a Byte (If Available) from the Uart Receive Buffer **/
EE_CBufferError EE_uart_cbuffer_receive(void * rx_data, EE_UINT16 data_length);

/**
    @brief Check if the buffer is empty.

    Checks the counter of the rx buffer is equal to zero.
    
    @return 1 if buffer is empty
            0 if buffer is not empty    
**/
__INLINE__ EE_BIT EE_uart_cbuffer_rx_buffer_isempty(void)
{
    return !EE_cbuffer_contains(EE_uart_cbuffer_get_rx_buffer(), 1);
}

/**
    @brief return how many bytes has beereceived and nor read.

    @return number of pending reading bytes    
**/
__INLINE__ EE_UINT16 EE_uart_cbuffer_rx_buffer_contains(void)
{
    return EE_uart_cbuffer_get_rx_buffer()->counter;
}

#ifdef CONFIG_UART_CBUFFER_PRINTF
/** Simple printf function with buffer Tx buffer **/
EE_UINT16 EE_uart_cbuffer_printf(char *fmt, ...);
#endif

#endif /*__INCLUDE_MICROCHIP_DSPIC_UART_CBUFFER_H__ */


