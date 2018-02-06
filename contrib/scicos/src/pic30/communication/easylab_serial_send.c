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
    @file easylab_serial_send.c
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri, SUPSI- Lugano
    @date 2006-2011
*/
#include <ee.h>
#include <string.h> 
#include <machine.h>
#include <scicos_block4.h>

#include "pic30/communication/easylab_serial.h"

static void init(scicos_block *block)
{
    EE_UINT32 baudrate = block->rpar[0];
    if((baudrate != 9600) && (baudrate != 19200) && (baudrate != 57600) && (baudrate != 115200))
        return;
    /* initialize UART C-Buffer with default values */
    EE_easylab_serial_init(baudrate);
}

static void inout(scicos_block *block)
{
    int i;
    unsigned char serial_packet[EASYLAB_PACKET_SIZE];
    unsigned char crc = 0;
    serial_packet[0] = 0xAA;
    
    /* Data copy (I start from serial_packet + 1 address) */
    for(i = 0; i < EASYLAB_SERIAL_CHANNELS; ++i)
        memcpy(serial_packet + 1 + (i * EASYLAB_CHANNEL_DATA_SIZE), block->inptr[i], EASYLAB_CHANNEL_DATA_SIZE);
    
    /* CRC evaluation */
    for(i = 1; i < EASYLAB_PACKET_SIZE - 1; ++i)
        crc ^= serial_packet[i];

    serial_packet[EASYLAB_PACKET_SIZE - 1] = crc;
    
    /* Send through CBuffer Uart */
    EE_easylab_serial_tx(serial_packet);
}

static void end(scicos_block *block)
{
    EE_easylab_serial_close();
}

void easylab_serial_send(scicos_block *block,int flag)
{
 switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialisation */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
 
