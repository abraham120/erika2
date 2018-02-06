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
	@file flex_gpin.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* GPIO bit allocation 

   WARNING : the GPIO Pin are allocated on CN5 AND CN6 
             look closely at the "Flex Connectors" allocation 

Scicos   Function   dsPIC   Flex Connectors
Pin=1    GPIO0	    RD8	    CON5.P7	
Pin=2    GPIO1      RD9	    CON5.P10	
Pin=3    GPIO2	    RD10	CON5.P9
Pin=4    GPIO3      RD11	CON5.P12
Pin=5    GPIO4      RD12	CON5.P15
Pin=6    GPIO5      RD13	CON5.P18
Pin=7    GPIO6      RD14	CON6.P35 : 
Pin=8    GPIO7      RD15	CON6.P38 : 
*/
static void init(scicos_block *block)
{
	unsigned int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 8))
	  return;
    //** TRISx(x=A,B,C,D,...) is the hree state out enable bit, one bit for each output
	//
	// ---------------------> WARNING: <-------------------------------------
	//**  TRISx works AS OPPOSITE AS standard I/O bit control register because
	//** "0" => is an OUTPUT
	//** "1" => is an INPUT 
    //
	//** The bit position is offset because
	//** the first Scicos Pin is the first I/O bit (zero)
	//** the first I/O bit is in postion "8" in the 16 bit I/O register 
	//** To define an OUTPUT, but te corresponding bit to ZERO	
	TRISD |= 0x01 << (pin-1+8); //** 
}

static void inout(scicos_block *block)
{
  float * y = block->outptr[0];

	unsigned int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 8))
		return;

	if ( PORTD & (0x01 << (pin-1+8)) )
		y[0] = 1.0; //** the output of a input bit is "1.0"  
	else                           //** or 
		y[0] = 0.0; //** "0.0" (float)
}

static void end(scicos_block *block)
{
}

void flex_gpin(scicos_block *block,int flag)
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
