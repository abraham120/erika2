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
	@file button.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
#include <altera_avalon_pio_regs.h>
#include <system.h>

#include <machine.h>
#include <scicos_block.h>

#include <ee.h>

static void init(scicos_block *block)
{
}

static void inout(scicos_block *block)
{
	int button = block->ipar[0];

	if ( (button < 1) || (button > 4) )
		return;

	volatile int pressed = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_PIO_BASE);

	if(!(pressed & (0x01 << (button-1))))
		block->outptr[0][0] = 1;
	else
		block->outptr[0][0] = 0;
}

static void end(scicos_block *block)
{
}

void rt_button(scicos_block *block,int flag)
{
	switch (flag) {
		case 1:	/* set output */
			inout(block);
			break;
		case 2:	/* get input */
			inout(block);
			break;
		case 4:	/* initialisation */
			init(block);
			break;
		case 5:	/* ending */
			end(block);
			break;
	}
}
