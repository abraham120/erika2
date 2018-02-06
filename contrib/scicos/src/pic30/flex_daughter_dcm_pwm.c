/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
	@file flex_daughter_dcm_pwm.c
	@brief www.scicos.org, www.scicoslab.org
	@author Dario Di Stefano, Evidence Srl
	@date 2010
*/
 
#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>

#define Fpwm 		10e3F
#define Offset_p 	0.0F	
#define Offset_n 	0.0F
#define Vmax 		12.0F
#define Vsat		6.0F

static void DC_Motor_Set_Voltage(EE_UINT8 chan, const float v)
{
	float volt;

	if(v >= 0.0){
		EE_dcm_pwm_set_direction(chan, EE_DCM_DIR_POS);
		volt = v + Offset_p;
	}
	else{
		EE_dcm_pwm_set_direction(chan, EE_DCM_DIR_NEG);
		volt = -v + Offset_n;
	}
	if(volt > Vsat)				// saturation
		volt = Vsat;
	EE_dcm_pwm_set_duty(chan, volt/Vmax*100.0);
}

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if ((pin < 1) || (pin > 2))
		return;
	
	EE_dcm_pwm_init(pin, Fpwm, 0, EE_DCM_DIR_POS);
	EE_dcm_pwm_enable_chan(pin);
}
 
static void inout(scicos_block *block)
{
	/* Get the PWM number [1,2,3,4]     */
	int pin = block->ipar[0];
	/* Get duty cycle from Scicos block */
	float *voltage = block->inptr[0];
	
	if ((pin < 1) || (pin > 2))
		return; //** refuse not supported PWM
		
	DC_Motor_Set_Voltage(pin, *voltage);
}

static void end(scicos_block *block)
{
	EE_dcm_pwm_set_duty(EE_DCM_PORT1, 0);	
	EE_dcm_pwm_disable_chan(EE_DCM_PORT1);	
	EE_dcm_pwm_set_duty(EE_DCM_PORT2, 0);	
	EE_dcm_pwm_disable_chan(EE_DCM_PORT2);
	EE_dcm_pwm_close();
}

void flex_daughter_dcm_pwm(scicos_block *block,int flag)
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
