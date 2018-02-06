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
	@file flex_simple802154_send.c
	@brief www.scicos.org, www.scicoslab.org
	@author Christian Nastasi, RetisLab, Pisa
	@date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>
#include "pic30/communication/flex_simple802154.h"

#if !( (defined __HAS_SIMPLE802154_C_CONFIG__) \
    || (defined __HAS_SIMPLE802154_D_CONFIG__))
#error FLEX 802.15.4 ERROR: Either a coordinator or a device configuration block is required.
#endif

//#define COORDINATOR_USE_GTS 0

static void tx_init(void) 
{
	/* TODO: do something? */
}

static void tx_end(void)
{
	/* TODO: do something? */
}

static void tx_inout(scicos_block *block)
{
	flex_simple802154_packet_t packet;
	EE_UINT8 use_gts;
	float *y = block->inptr[0];
	
	/* ipar[0] := data_id, ipar[1] := dst_addr, ipar[2] := use_gts */
	packet.data = *y;
	packet.data_id = block->ipar[0];	
	packet.dst_addr = block->ipar[1]; 
	packet.src_addr = flex_simple802154_local_address; 
	#ifdef COORDINATOR_USE_GTS	
	use_gts = (flex_simple802154_flags.is_coordinator) ? 
		  COORDINATOR_USE_GTS :  block->ipar[2];
	#else	
	use_gts = block->ipar[2];
	#endif
	uwl_simple154_send((EE_UINT8 *) &packet, 
			   sizeof(flex_simple802154_packet_t), 
			   block->ipar[1], use_gts);
}

void flex_simple802154_send(scicos_block *block, int flag)
{
	switch (flag) {
	case OutputUpdate:  	/* set output */
		tx_inout(block); 
		break;
	case StateUpdate: 	/* get input */
		break;
	case Initialization:  	/* initialisation */
		tx_init();
		break;
	case Ending:  		/* ending */
		tx_end();
		break;
	}
}


