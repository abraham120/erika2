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
	@file flex_simple802154_receive.c
	@brief www.scicos.org, www.scicoslab.org
	@author Christian Nastasi, RetisLab, Pisa
	@date 2006-2010
*/

#include <ee.h>
#include <machine.h>		// TODO: serve?
#include <scicos_block4.h>
#include "pic30/communication/flex_simple802154.h"

#if !( (defined __HAS_SIMPLE802154_C_CONFIG__) \
    || (defined __HAS_SIMPLE802154_D_CONFIG__))
#error FLEX 802.15.4 ERROR: Either a coordinator or a device configuration block is required.
#endif

static float rx_buffer[FLEX_SIMPLE802154_ADDRESSES][FLEX_SIMPLE802154_CHANNELS];

/* ---------------------------------------------------------------------------- 
|  Rx callback function:                                                       |
|                                                                              |
|  Called by the network stack when data have been received.                   |
 ---------------------------------------------------------------------------- */
static void rx_data(int8_t status, uint8_t *data, uint8_t len, uint16_t sender)
{
	EE_INT16 id, addr;

	flex_simple802154_packet_t *packet = (flex_simple802154_packet_t*) data;
	/* Check Packet */
	if (len != sizeof(flex_simple802154_packet_t)) 
	  	return;	/* Wrong size */
	if (packet->dst_addr != flex_simple802154_local_address)
		return;	/* Wrong destination */
	id = packet->data_id;
	if (id >= FLEX_SIMPLE802154_CHANNELS)
		return; /* Bad data identifier */
	addr = flex_simple802154_address_lookup(packet->src_addr);
	if (addr >= FLEX_SIMPLE802154_ADDRESSES) 
	  	return; /* Bad Address (unknown by the lookup table) */
	/* Put the float data into the data_id buffer */
	GetResource(flex_simple802154_rx_buffer_mutex);
	rx_buffer[addr][id] = packet->data;
	ReleaseResource(flex_simple802154_rx_buffer_mutex);
}

static void rx_init(scicos_block *block) 
{
	if (!flex_simple802154_flags.rx_initialized) {
		uwl_simple154_set_rx_callback(rx_data);
		flex_simple802154_flags.rx_initialized = 1;
	}
	flex_simple802154_add_lookup(block->ipar[1]); /* ipar[1] := src_addr */
}

static void rx_end(void)
{
	return;
	/* TODO: do something! : clen lookup table? */
	flex_simple802154_flags.rx_initialized = 0;
}

static void rx_inout(scicos_block *block)
{
	EE_UINT16 id, addr;

	/* ipar[0] := data_id, ipar[1] := src_addr */
	id = block->ipar[0];
	addr = flex_simple802154_address_lookup(block->ipar[1]); 
	if (addr >= FLEX_SIMPLE802154_ADDRESSES)
		return;
	GetResource(flex_simple802154_rx_buffer_mutex);
	*((float *) block->outptr[0]) = rx_buffer[addr][id];
	ReleaseResource(flex_simple802154_rx_buffer_mutex);
}



void flex_simple802154_receive(scicos_block *block, int flag)
{
	switch (flag) {
	case OutputUpdate:  /* set output */
		rx_inout(block);
		break;
	case StateUpdate: /* get input */
		break;
	case Initialization:  /* initialisation */
		rx_init(block);
		break;
	case Ending:  /* ending */
		rx_end();
		break;
	}
}


