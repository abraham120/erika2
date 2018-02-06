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
	@file amazing_button.c
	@brief www.scicos.org, www.scicoslab.org
	@author Francesco Prosperi, RetisLab, Pisa
	@date 2006-2010
*/

//** 9 Feb 2008 : Revision notes by Simone Mannori 
//**

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

/* Buttons bit allocation 

Scicos	Function	dsPIC
Pin=1	Button1	RD4
Pin=2	Button2	RD5
Pin=3	Button3	RD6
Pin=4	Button4	RD15
*/

static void init(scicos_block *block)
{
	unsigned int pin = block->ipar[0];
#if defined(__USE_DEMOBOARD__)	
	if ((pin < 1) || (pin > 4))
#elif defined(__USE_MOTIONBOARD__)
	if ((pin < 1) || (pin > 2))
#endif
		return; //** return if outside the allowed range

	EE_button_S1_init(NULL);
	EE_button_S2_init(NULL);
}

static void inout(scicos_block *block)
{
	float * y = block->outptr[0];

	unsigned int pin = block->ipar[0];
	
#if defined(__USE_DEMOBOARD__)	
	if ((pin < 1) || (pin > 4))
#elif defined(__USE_MOTIONBOARD__)
	if ((pin < 1) || (pin > 2))
#endif
		return; //** return if outside the allowed range
	
	switch(pin) {
		case 1:
			if (EE_button_get_S1())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
		case 2:
			if (EE_button_get_S2())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
#if defined(__USE_DEMOBOARD__)	
		case 3:
			if (EE_button_get_S3())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
		case 4:
			if (EE_button_get_S4())
				y[0] = 1.0; //** the output of a input bit is "1.0"  
			else
				y[0] = 0.0; //** "0.0" (float)
			break;
#endif // USE_DEMOBOARD__	
	}
}

static void end(scicos_block *block)
{
}

void amazing_button(scicos_block *block, int flag)
{
 switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialization */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
