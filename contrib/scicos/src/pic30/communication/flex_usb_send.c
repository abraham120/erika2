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
	@file flex_usb_send.c
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
#include "scicos_USB.h"
#include "string.h"

static void init(scicos_block *block)
{
//  TRISAbits.TRISA14=0;
	EE_usb_init();	
}

//static unsigned char checksum(unsigned char *buf)
//{
//   unsigned char len=buf[1]+2, sum=0, *pt=buf+1;
//   while(len--){
//      sum+=*pt++;
//   }
//   return sum;
//}

static void inout(scicos_block *block)
{
	//float inputdata;
	//float * y = block->inptr[0];
	//unsigned char datasize;
 	//unsigned char buf[32];
	//int logical_channel = block->ipar[0];
	//buf[0] = 0xAA; // sync char
	//datasize=sizeof(float) + 1; //TODO: mettere la size del dato letto in input	
	//buf[1] = datasize; // len	
	//buf[2] = 21;       // id
	//buf[3] = *(unsigned char *)y;
	//buf[4] = *((unsigned char *)y+1);
	//buf[5] = *((unsigned char *)y+2);
	//buf[6] = *((unsigned char *)y+3);
	//buf[7] = (unsigned char)logical_channel; 	
	//buf[8] = checksum(buf);
	//buf[9] = 0;        // padding
	//
	//EE_usb_send( (unsigned int *)buf, (datasize + 5)>>1 );

// chris: simplified dummy version!
//	struct flex_bus_packet_t pkt;	
//
//	pkt.channel = (unsigned int) block->ipar[0];
//	pkt.payload.length = sizeof(float);
//	*((float *) pkt.payload.data) = *((float *) block->inptr[0]);
//	EE_usb_write((unsigned char *) &pkt, sizeof(struct flex_bus_packet_t));

	EE_INT16 data_id = (EE_INT16) block->ipar[0];

	if (data_id < 0 || data_id >= SCICOS_USB_CHANNELS)
		return;
	GetResource(scicosUSB_tx_buffer_mutex);
	memcpy(scicosUSB_tx_buffer + data_id,  block->inptr[0], sizeof(float));
	ReleaseResource(scicosUSB_tx_buffer_mutex);
}

static void end(scicos_block *block)
{
}

void flex_usb_send(scicos_block *block,int flag)
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
