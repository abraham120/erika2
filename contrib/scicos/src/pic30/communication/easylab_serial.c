/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
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
    @file easylab_serial.c
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri, Evidence Srl
    @date 2006-2011
*/

#include "ee.h"
#include "pic30/communication/easylab_serial.h"
#include "ee_internal.h"

#include <string.h>

/* Shared initialization status */
static volatile EE_BIT ee_cbuffer_uart_driver_initialized = 0;


#ifdef __RECEIVING_FROM_UART__

/* Shared receiving task active status*/
static volatile EE_BIT receiving_task_active = 0;

/* Last valid parameter received */
volatile float received_param1 = 0.0f;
/* Last valid parameter received */
volatile float received_param2 = 0.0f;

void receiving_from_uart_callback( EE_UINT8 data )
{
    if((EE_uart_cbuffer_rx_buffer_contains() >= EASYLAB_PACKET_SIZE)
        && !receiving_task_active)
    {
        receiving_task_active = 1;
        ActivateTask(receiving_from_uart);
    }
}

TASK(receiving_from_uart)
{
    EE_UINT16 rx_bytes;
    /* Start critical section */
    EE_hal_disableIRQ();
    while((rx_bytes = EE_uart_cbuffer_rx_buffer_contains()) >= EASYLAB_PACKET_SIZE){
        /* I make the read buffer of same size of receiving buffer so 
           I can read all bytes in one step (less memory access) */
        unsigned char read_buffer[UART_CBUFFER_RX_BUFFER_SIZE];
        unsigned int i,j;
        /* I directly access rx_buffer because i don't want pop bytes yet,
           because i don't know how many of them I'm going to use.
        */
        EE_CBuffer * rx_buffer = EE_uart_cbuffer_get_rx_buffer();
        EE_cbuffer_first(rx_buffer, &read_buffer, rx_bytes);        

        /* End critical section */
        EE_hal_enableIRQ();
        
        /* Parsing condition is remaining bytes are more than packet length */
        for(i = 0; (rx_bytes - i) >= EASYLAB_PACKET_SIZE; ){
            unsigned char crc = 0, crc2;
            /* Start byte check. I need 'i' incremented after this point */
            if(read_buffer[i++] != 0xAA)
                continue;
            
            /* Parsing inner loop */
            for(j = i; j < (i + EASYLAB_PACKET_SIZE - 2); ++j){
                /* Loop to evaluate crc */
                crc ^= read_buffer[j];
            }
            /* Check end of crc condition (-2 because 'i' is already incremented)*/
			crc2 = read_buffer[i + EASYLAB_PACKET_SIZE - 2];
            if(crc2 == crc){
				/* Valid packet read: I populate received variables */
                memcpy((void *)&received_param1, read_buffer + i, sizeof(float));
                memcpy((void *)&received_param2, read_buffer + i + sizeof(float), sizeof(float));
                /* Valid packet I restart parsing after this one */
                i += EASYLAB_PACKET_SIZE - 1;
            }
        }
        
        /* Start critical section */
        EE_hal_disableIRQ();
        /* Skip used bytes(pop without reading, already done).
           N.B 'i' points to next byte to check, so  i - 1 is last used 
           byte 
        */
        EE_cbuffer_skip(rx_buffer, (i - 1));
    }
    /* End task flag to re-arm the ISR behaviour */
    receiving_task_active = 0;
    /* WARNING:
       I don't renable interrupt: I defer this to the kernel scheduler, 
       because I know his implementation.
       I do this to eliminate the needing of pending attivation handling
       for this task that could appen between status changing + ISR enabling 
       and task ending
     */
}
#else
#define receiving_from_uart_callback NULL
#endif /*__RECEIVING_FROM_UART__*/

EE_INT8 EE_easylab_serial_init(EE_UINT32 baudrate)
{
    EE_INT8 error = EE_CBUFFER_UART_ERR_ALREADY_INIT;
    if(!ee_cbuffer_uart_driver_initialized){
        error = EE_uart_cbuffer_complete_init(receiving_from_uart_callback, NULL, 
            baudrate, EE_UART_BIT_STOP_1 | EE_UART_BIT8_NO, EE_UART_CTRL_SIMPLE);
        /*UART driver doesn't have a good error handling so i don't check it */
        ee_cbuffer_uart_driver_initialized = 1;
    }
    return error;
}









