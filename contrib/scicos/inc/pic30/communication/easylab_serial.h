/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2011  Evidence Srl
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
    @file easylab_serial.h
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri, Evidence Srl, Pisa
    @date 2006-2011
*/

#ifndef __INCLUDE_SCICOS_EASYLAB_SERIAL_H__
#define __INCLUDE_SCICOS_EASYLAB_SERIAL_H__

#include "mcu/microchip_dspic/inc/ee_uart_cbuffer.h"

#define EASYLAB_SERIAL_CHANNELS    2
#define EASYLAB_CHANNEL_DATA_SIZE (sizeof(float))
#define EASYLAB_PACKET_SIZE       (EASYLAB_CHANNEL_DATA_SIZE * EASYLAB_SERIAL_CHANNELS + 2)

#define EE_CBUFFER_UART_ERR_ALREADY_INIT  -5

/** Initialize CBuffer-UART driver for easylab **/
EE_INT8 EE_easylab_serial_init(EE_UINT32 baudrate);
    
__INLINE__ EE_CBufferError EE_easylab_serial_tx(unsigned char serial_packet[])
{
    EE_CBufferError error = EE_uart_cbuffer_push_tx(serial_packet, EASYLAB_PACKET_SIZE);
    EE_uart_cbuffer_trigger_tx();
    return error;
}

__INLINE__ EE_INT8 EE_easylab_serial_close()
{
    return EE_uart_cbuffer_close();
}
#endif /* __INCLUDE_SCICOS_EASYLAB_SERIAL_H__ */
