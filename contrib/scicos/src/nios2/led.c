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
	@file led.c
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


static int led_status=0;
static int leds[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

static void init(scicos_block *block)
{
}

static void inout(scicos_block *block)
{
	int i = block->ipar[0];
	
	if ( (i<0) || (i>7) )
		return;

	alt_irq_context c;
	c = alt_irq_disable_all();

	if(block->inptr[0][0]>0.5)
		led_status |= leds[i];
	else
		led_status &= ~leds[i];

	IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_status);
	alt_irq_enable_all(c);
}

static void end(scicos_block *block)
{
}

void rt_led(scicos_block *block,int flag)
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
