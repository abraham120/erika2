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
	@file flex_zigbee_receive.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/

//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#include "scicos_openZB.h"

/*
*/

static void init(scicos_block *block)
{	unsigned int i;

	#ifdef DEVICE_TYPE_COORDINATOR	

	/* Configure DESTINATION address for the ieee802154 stack */
	openzb_device_address = 0x00FF; /* FIXME: now address ignored!!! */
	//openzb_device_address = block->ipar[2]; // in future is dst_addr 
	/* Configure SOURCE addresses for the ieee802154 stack 
	   - Set the GTS table (NOTE: GTS used onlu Device->Coordinator ONLY! 
	   - Set the reception address for the lookup table
	 */
	for (i = 0; i < 4; i++)  // NOTE: 4 is the number of devices for GTS 
		if (openzb_device_addresses[i] == block->ipar[1]) /*src_addr*/
			break;
	if (i == 4) { // The address is not in the GTS table, add it somewhere!
		openzb_device_addresses[scicosOpenZB_address_count] = 
							block->ipar[1];
		scicosOpenZB_address_count = (scicosOpenZB_address_count + 1)%4;
	}
	i = scicosOpenZB_address_lookup(block->ipar[1]);
	if (i < SCICOS_OPENZB_ADDRESSES) //Address in the lookup table, ok(stop)
		return;
	for (i = 0; i < SCICOS_OPENZB_ADDRESSES; i++) {
		// Find a free space (0xFFFF is free entry) in the lookup table
		if (scicosOpenZB_address_table[i] == 0xFFFF) {
			scicosOpenZB_address_table[i] = block->ipar[1];
			return;
		}
	}
	#else
	/* Configure DESTINATION address for the ieee802154 stack 
	   - it's the device address 

	*/
	openzb_device_address = block->ipar[2]; /*ipar[1]=dst_addr*/
	// TODO: demo percom: the coordinator address is always 0x00FF !!
	/* Configure SOURCE address for the ieee802154 stack 
	   - it's only the coordinator address, now is fixed = 0x00FF 
	*/
	for (i = 0; i < SCICOS_OPENZB_ADDRESSES; i++) {
		// Find a free space (0xFFFF is free entry) in the lookup table
		scicosOpenZB_address_table[i] = 0x00FF;
			
	}		
	#endif

}

static void inout(scicos_block *block)
{
	unsigned int idx;

	idx = scicosOpenZB_address_lookup(block->ipar[1]); /*ipar[1]=src_addr*/
	if (idx >= SCICOS_OPENZB_ADDRESSES)
		return;
	GetResource(scicosOpenZB_rx_buffer_mutex);
	*((float *) block->outptr[0]) = scicosOpenZB_rx_buffer[idx][block->ipar[0]];
	ReleaseResource(scicosOpenZB_rx_buffer_mutex);
}

static void end(scicos_block *block)
{
}

void flex_zigbee_receive(scicos_block *block,int flag)
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


