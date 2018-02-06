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
	@file flex_daughter_dac.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

//*** da rivedere 

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* Dac bit allocation:
SCL	RG2
SDA	RG3
*/

static void init(scicos_block *block)
{
	EE_dac_init();
}

static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2]     */
	int pin = block->ipar[0];

	/* Get duty cycle from Scicos block */
	float * duty = block->inptr[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	//** non ci siamo : questi sono dei veri dac che producono VOLT, quindi 
	//** l'ingresso DEVE essere interpretato in VOLT e i VOLT devono essere 
	//** VOLT VERI e non noccioline ......
	EE_dac_fast_write( (unsigned int)(duty[0]*4095), pin-1, 0 );
}

static void end(scicos_block *block)
{
	/* Get the PWM number [1,2]     */
	int pin = block->ipar[0];

	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM

	EE_dac_fast_write( 0, pin-1, 0 );
}

void flex_daughter_dac(scicos_block *block,int flag)
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
