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
	@file flex_can_in.c
	@brief www.scicos.org, www.scicoslab.org
	@author Dario Di Stefano, Evidence Srl
	@date 2006-2010
*/


#include <machine.h>
#include <scicos_block4.h>
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_ecan.h"
#include "pic30/communication/flex_can.h"
#include <string.h>

static void init(scicos_block *block)
{
    /* 
        to do: add eCAN2 support 
        ecan_rx_canid	=	block->ipar[2];
    */
	EESCI_can_debug_print_string("can_rx init start!\n");
	EESCI_can_debug_print_val("can_rx block->ipar[0]: %d\n", block->ipar[0]);
	EESCI_can_debug_print_val("can_rx block->ipar[1]: %d\n", block->ipar[1]);
	EESCI_can_debug_print_string("can_rx init end!\n");
}


extern volatile int eesci_can_debug_rx_service_flag;

static void inout(scicos_block *block)
{
	static int eesci_can_debug_counter=0;

	EE_UINT32 id  = block->ipar[0]; /* packet id */
	EE_UINT8 len = block->ipar[1]; /* number of floats */
	//EE_UINT8 div = (len & 0x01)? len/2 + 1: len/2; /* number of CAN packets for this id (max 1 packet is supported) */
	int ind = EESCI_eCAN1_get_rx_block(id);
	if(ind >= 0)
	{
		int i;
		CAN1_rx_block can1b = CAN1_rx_blocks[ind];
		
		EE_hal_disableIRQ();
		for(i=0; i<CAN_DATA_LEN; i++)
			scicosCAN1_rx_buffer[i] = can1b.rx_ecan1message.data[i];
		EE_hal_enableIRQ();
		
		/* Received data is saved for testing */
		if( (eesci_can_debug_counter < CAN_DEBUG_TEST_NUM) && (eesci_can_debug_rx_service_flag!=0) ) {
				EESCI_can_debug_insert_val(scicosCAN1_rx_buffer, eesci_can_debug_counter);
				eesci_can_debug_counter++;
				eesci_can_debug_rx_service_flag = 0;
		}
		else if(eesci_can_debug_counter >= CAN_DEBUG_TEST_NUM) {
			/* This function is blocking in TEST mode */
			EESCI_can_debug_print_results();
		}
		
		for(i=0; i<len; i++)
			memcpy(&y(i,0), scicosCAN1_rx_buffer + i*sizeof(float), sizeof(float)); /* move data to output */
	}
	else
		EESCI_can_debug_print_string("can_rx inout error: ind<0!\n");
}

static void end(scicos_block *block)
{
}

void flex_can_in(scicos_block *block,int flag)
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




