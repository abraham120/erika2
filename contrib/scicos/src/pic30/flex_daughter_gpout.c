/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
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
	@file flex_daughter_gpout.c
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

/* GPIO bit allocation 

Scicos	Function	dsPIC	Flex Connectors
Pin=1	 GPIO1	RE0	CON8.P2	
Pin=2	 GPIO2	RE1	CON8.P4	
Pin=3	 GPIO3	RE2	CON8.P6	
Pin=4	 GPIO4	RE3	CON8.P8	
Pin=5	 GPIO5	RE4	CON8.P10
Pin=6	 GPIO6	RE5	CON8.P12
Pin=7	 GPIO7	RE6	CON8.P14
Pin=8	 GPIO8	RE7	CON8.P16
*/

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;

	TRISE &= 0xFFFF - ( 0x01 << (pin-1) );
	LATE  &= 0xFFFF - ( 0x01 << (pin-1) ); //** preset the same output to zero 
}

static void inout(scicos_block *block)
{
	float *u = block->inptr[0];
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return; //** return if outside the allowed range

	if (u[0] > 0.5)      //** threshold is fixed to 0.5 STATIC 
		LATE |= ( 0x01 << (pin-1) ); //** set the bit to one 
	else
		LATE &= 0xFFFF - ( 0x01 << (pin-1) ); //** set the bit to zero
}

static void end(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ( (pin < 1) || (pin > 8) )
		return;

	LATE  &= 0xFFFF - ( 0x01 << (pin-1) ); //** set the bit to zero at the ending 
}

void flex_daughter_gpout(scicos_block *block,int flag)
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
