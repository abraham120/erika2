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
	@file flex_zigbee_send.c
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


static void init(scicos_block *block)
{
	#ifdef DEVICE_TYPE_COORDINATOR
	unsigned int i;

	/* Configure SOURCE address for the ieee802154 stack */
	openzb_device_address = 0x00FF; /* FIXME: now address ignored!!! */
	//openzb_device_address = block->ipar[1]; // in future is src_addr 
	/* NOTE: no need to store the destination address! */
	#else
	/* Configure SOURCE address for the ieee802154 stack */
	openzb_device_address = block->ipar[1]; /* ipar[1] = src_addr */
	/* NOTE: no need to store the destination address! */
	#endif
}

static void inout(scicos_block *block)
{
	float *y = block->inptr[0];
	ScicosOpenZB_Payload packet;

	/* Build the openZB payload for scicos */
	packet.channel_id = block->ipar[0];	
	packet.src_addr = block->ipar[1]; /*ipar[1]=src_addr*/
	#ifdef DEVICE_TYPE_COORDINATOR
	packet.dst_addr = block->ipar[2]; /*ipar[1]=dst_addr*/
	#else
	packet.dst_addr = 0x00FF; /*TODO: force coordinator, ipar[1]=dst_addr*/
	#endif
	packet.data = *y;
	/* Send the packet using GTS */
	#ifdef DEVICE_TYPE_COORDINATOR
	openZB_send_bytes(&packet, sizeof(ScicosOpenZB_Payload), 0);
	#else
	openZB_send_bytes(&packet, sizeof(ScicosOpenZB_Payload), 1);
	#endif
}

static void end(scicos_block *block)
{
}

void flex_zigbee_send(scicos_block *block,int flag)
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
