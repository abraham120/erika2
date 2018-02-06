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
	@file flex_daughter_touch.c
	@brief www.scicos.org, www.scicoslab.org
	@author Francesco Prosperi, RetisLab, Pisa
	@date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>

#define ADC_TO_USE 2

#include <ee.h>
#include "touch.h"

#define touch_set_dimension(a, b)       touch_1_set_dimension(a, b) 
#define touch_raw_init()                touch_1_raw_init()
#define touch_start()                   touch_1_start()
#define touch_wait_raw_position(a, b)   touch_1_wait_raw_position(a, b)
#define touch_tune(a)                   touch_1_tune(a)
#define touch_poll_s_position(a, b)     touch_1_poll_s_position(a, b)

#define ASCII_X	88
#define ASCII_Y	89

static EE_UINT8 x_already_initialized = 0;
static EE_UINT8 y_already_initialized = 0;
static EE_UINT8 touch_initialized = 0;

static void init(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];
	EE_UINT16 range = block->ipar[1];

	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
	if(axis == ASCII_X && x_already_initialized)
		return;
	if(axis == ASCII_Y && y_already_initialized)
		return;

	touch_set_dimension(axis-ASCII_X,range);

	if(axis == ASCII_X)
		x_already_initialized = 1;
	else if(axis == ASCII_Y)
		y_already_initialized = 1;
	
	if(x_already_initialized && y_already_initialized)
	{
		touch_initialized = 1;
		touch_raw_init();
		
		#if (defined __USE_LEDS__) && (defined __USE_MOTIONBOARD__)
		EE_daughter_leds_init();
		#endif
	}
}

static void inout(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];
	EE_INT16 aux;
	float *y = block->outptr[0];

	if(!touch_initialized)
		return;
	
	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
		
	//y[0] = (float)touch_get_position_s(axis-ASCII_X,);
	touch_poll_s_position(axis-ASCII_X,&aux);
	y[0] = (float)aux;

}

static void end(scicos_block *block)
{
}

void flex_daughter_touch(scicos_block *block,int flag)
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
