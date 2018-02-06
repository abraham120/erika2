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
	@file amazing_touch.c
	@brief www.scicos.org, www.scicoslab.org
	@author Francesco Prosperi, RetisLab, Pisa
	@date 2006-2010
*/

#include <ee.h>
#include "touch.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"
#include <machine.h>
#include <scicos_block4.h>

#define ASCII_X	88
#define ASCII_Y	89

static void out(scicos_block *block)
{
	EE_UINT8 axis = block->ipar[0];
	EE_INT16 data;

	float *y = block->outptr[0];

	if(axis != ASCII_X && axis != ASCII_Y) 
		return;
	if(axis == ASCII_X){
		touch_poll_s_position(TOUCH_X_AXIS,&data);
	} else {
		touch_poll_s_position(TOUCH_Y_AXIS,&data);
	}

	y[0] = (float)data; 
}

void amazing_touch(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			out(block);
			break;
		case StateUpdate:
			break;
		case Initialization:
			break;
		case Ending:
			break;
	}
}
