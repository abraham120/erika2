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
	@file flex_blocks.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "pic30/flex_daughter.h"


#define FLEX_BLOCKS_TYPE_BUTTONS 0
#define FLEX_BLOCKS_TYPE_LEDSLCD 1
#define FLEX_BLOCKS_TYPE_LEDSLCDBUZ 2

static void init(scicos_block *block)
{
	int type = block->ipar[0];
	
	if(type == FLEX_BLOCKS_TYPE_BUTTONS) {
		flex_daughter_button_init();
	}
	else {
		flex_daughter_leds_init();
		#if defined(__USE_DEMOBOARD__)
		flex_daughter_lcd_init();
		if(type == FLEX_BLOCKS_TYPE_LEDSLCDBUZ)
			flex_daughter_buzzer_init();
		#endif
	}
}

static void inout(scicos_block *block)
{
	int type = block->ipar[0];
	
	if(type == FLEX_BLOCKS_TYPE_BUTTONS) {
		/* Buttons */
		flex_daughter_button_inout(1, block->outptr[0], SCITYPE_INT8);
		flex_daughter_button_inout(2, block->outptr[1], SCITYPE_INT8);
		#if defined(__USE_DEMOBOARD__)
		flex_daughter_button_inout(3, block->outptr[2], SCITYPE_INT8);
		flex_daughter_button_inout(4, block->outptr[3], SCITYPE_INT8);
		#endif
	}
	else {
		/* LEDs */
		int i;
		unsigned char ledv = 0;
		for(i=0; i<FLEX_DAUGHTER_NUM_LEDS; i++) {
			ledv |= (*(unsigned char *)block->inptr[i])? 0x01<<i : 0;
		}
		flex_daughter_leds_inout_uint8(ledv);

		/* LCD and buzzer */
		#if defined(__USE_DEMOBOARD__)
		int line1_type = block->ipar[2];
		int line2_type = block->ipar[3];
		if(type == FLEX_BLOCKS_TYPE_LEDSLCD){
			flex_daughter_lcd_inout_line (1, line1_type, (void*)block->inptr[8], block->insz[2*block->nin - 2]);
			flex_daughter_lcd_inout_line (2, line2_type, (void*)block->inptr[9], block->insz[2*block->nin - 1]);
		}
		else if(type == FLEX_BLOCKS_TYPE_LEDSLCDBUZ){
			flex_daughter_lcd_inout_line (1, line1_type, (void*)block->inptr[8], block->insz[2*block->nin - 3]);
			flex_daughter_lcd_inout_line (2, line2_type, (void*)block->inptr[9], block->insz[2*block->nin - 2]);
			float new_freq_f = ((float *)block->inptr[10])[0];
			flex_daughter_buzzer_update(new_freq_f);
		}
		#endif
	}
}

static void end(scicos_block *block)
{
	#if defined(__USE_DEMOBOARD__)
	int type = block->ipar[0];
	if(type == FLEX_BLOCKS_TYPE_LEDSLCDBUZ){
		flex_daughter_buzzer_stop();
	}
	#endif
}

void flex_blocks(scicos_block *block,int flag)
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
