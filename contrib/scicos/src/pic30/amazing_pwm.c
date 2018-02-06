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
	@file amazing_pwm.c
	@brief www.scicos.org, www.scicoslab.org
	@author Francesco Prosperi, RetisLab, Pisa
	@date 2006-2010
*/
 
#include <ee.h>
#include <machine.h>
#include <scicos_block4.h>

static void init(scicos_block *block)
{
#ifndef __AMAZING_TUNER__
	EE_ocpwm_init( EE_PWM_PORT1 , 20000 , 0 );
	EE_ocpwm_init( EE_PWM_PORT2 , 20000 , 0 );
#endif // __AMAZING_TUNER__
}
 
static void inout(scicos_block *block)
{
	/* Get angle(degree) from Scicos block */
	float *x_angle = block->inptr[0];
	float *y_angle = block->inptr[1];
	unsigned int pwm_step = 10; // us
	unsigned int pwm_bias = 1500; // us
	
	EE_ocpwm_set_duty( EE_PWM_PORT1 , (*x_angle)*pwm_step+pwm_bias );
	EE_ocpwm_set_duty( EE_PWM_PORT2 , (*y_angle)*pwm_step+pwm_bias );
}

static void end(scicos_block *block)
{
	EE_ocpwm_close(EE_PWM_PORT1);
	EE_ocpwm_close(EE_PWM_PORT2);
}

void amazing_pwm(scicos_block *block,int flag)
{
	switch (flag) {
		case OutputUpdate:
			inout(block);
			break;
    		case StateUpdate:
			break;
		case Initialization:
			init(block);
			break;
		case Ending:
			end(block);
			break;
	}
}

