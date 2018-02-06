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
    @file flex_udp_config.c
    @brief www.scicos.org, www.scicoslab.org
    @author Dario Di Stefano, Evidence Srl
    @date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>
#include "string.h"
#include "pic30/communication/flex_udp.h"

static volatile unsigned char UDP_is_initialized = 0;

BYTE scicosUDP_rx_buffer[UDP_SIZE_OF_ELEMENT];    /* buffer for UDP reception */
BYTE scicosUDP_tx_buffer[UDP_SIZE_OF_ELEMENT];    /* buffer for UDP transmission */

static void init(scicos_block *block)
{
    if(!UDP_is_initialized)
    {
        int i, ipar_index=0;
        
        UDP_flex_port                = block->ipar[ipar_index++];
        
        MY_DEFAULT_IP_ADDR_BYTE1     = block->ipar[ipar_index++];
        MY_DEFAULT_IP_ADDR_BYTE2     = block->ipar[ipar_index++];
        MY_DEFAULT_IP_ADDR_BYTE3     = block->ipar[ipar_index++];
        MY_DEFAULT_IP_ADDR_BYTE4     = block->ipar[ipar_index++];

        MY_DEFAULT_MASK_BYTE1        = block->ipar[ipar_index++];
        MY_DEFAULT_MASK_BYTE2        = block->ipar[ipar_index++];
        MY_DEFAULT_MASK_BYTE3        = block->ipar[ipar_index++];
        MY_DEFAULT_MASK_BYTE4        = block->ipar[ipar_index++];

        MY_DEFAULT_GATE_BYTE1        = block->ipar[ipar_index++];
        MY_DEFAULT_GATE_BYTE2        = block->ipar[ipar_index++];
        MY_DEFAULT_GATE_BYTE3        = block->ipar[ipar_index++];
        MY_DEFAULT_GATE_BYTE4        = block->ipar[ipar_index++];

        MY_DEFAULT_PRIMARY_DNS_BYTE1    = block->ipar[ipar_index++];
        MY_DEFAULT_PRIMARY_DNS_BYTE2    = block->ipar[ipar_index++];
        MY_DEFAULT_PRIMARY_DNS_BYTE3    = block->ipar[ipar_index++];
        MY_DEFAULT_PRIMARY_DNS_BYTE4    = block->ipar[ipar_index++];

        MY_DEFAULT_SECONDARY_DNS_BYTE1    = block->ipar[ipar_index++];
        MY_DEFAULT_SECONDARY_DNS_BYTE2    = block->ipar[ipar_index++];
        MY_DEFAULT_SECONDARY_DNS_BYTE3    = block->ipar[ipar_index++];
        MY_DEFAULT_SECONDARY_DNS_BYTE4    = block->ipar[ipar_index++];
        
        UDP_pc_port                       = block->ipar[ipar_index++];
        
        UDP_remote.IPAddr.v[0]            = block->ipar[ipar_index++];
        UDP_remote.IPAddr.v[1]            = block->ipar[ipar_index++];
        UDP_remote.IPAddr.v[2]            = block->ipar[ipar_index++];
        UDP_remote.IPAddr.v[3]            = block->ipar[ipar_index++];
        
        UDP_remote.MACAddr.v[0] = 0;
        UDP_remote.MACAddr.v[1] = 0;
        UDP_remote.MACAddr.v[2] = 0;
        UDP_remote.MACAddr.v[3] = 0;
        UDP_remote.MACAddr.v[4] = 0;
        UDP_remote.MACAddr.v[5] = 0;
        
        for(i=0; i < sizeof(scicosUDP_tx_buffer); i++)
            scicosUDP_tx_buffer[i] = 0;
        for(i=0; i < sizeof(scicosUDP_rx_buffer); i++)
            scicosUDP_rx_buffer[i] = 0;
            
        UDP_is_initialized = 1;
    }
}

static void inout(scicos_block *block)
{
}

static void end(scicos_block *block)
{
}

void flex_udp_config(scicos_block *block,int flag)
{
 switch (flag) {
    case OutputUpdate:    /* set output */
      inout(block);
      break;

    case StateUpdate:     /* get input */
      break;

    case Initialization:  /* initialisation */
      init(block);
      break;

    case Ending:          /* ending */
      end(block);
      break;
  }
}
