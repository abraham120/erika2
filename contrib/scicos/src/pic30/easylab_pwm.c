/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2011
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
    @file easylab_pwm.c
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri
    @date 2006-2011
*/ 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

float CPU_load_get(void);
double get_scicos_period();

/*  from ee_board di easylab    */
/*  EE_EASYLAB_PWM1 : 1   */
/*  EE_EASYLAB_PWM2 : 2   */  
/*  EE_EASYLAB_PWM3 : 3   */
/*  EE_EASYLAB_PWM4 : 4   */
/*  if you want activate PWM over both pins 1 e 2 you should use these pin's ID */
/*  EE_EASYLAB_PWM12 : 5  */
/*  if you want activate PWM over both pins 3 e 4 you should use these pin's ID */
/*  EE_EASYLAB_PWM34 : 6  */

static void init(scicos_block *block)
{
    EE_UINT32 pwm_freq = block->rpar[0];
    EE_UINT16 pwm_ch   = block->ipar[0];
    
    if ((pwm_ch < 1) || (pwm_ch > 4))
        return;
    EE_easylab_pwm_init(pwm_ch, pwm_freq);
}
 
static void inout(scicos_block *block)
{
    /* Get the PWM number [1,2,3,4]     */
    EE_UINT16 pwm_ch = block->ipar[0];
    float duty;
    
    if ((pwm_ch < 1) || (pwm_ch > 4))
        return;
    
    if( GetNin(block) == 0 ) {
        /* Calculate duty form CPU load */
        duty = CPU_load_get() / get_scicos_period();
    }
    else {
        /* Get duty cycle from Scicos block */
        duty = *(float *)block->inptr[0];
    }
    
    /* Express duty relative to MAX VALUE */
    EE_easylab_pwm_set_duty(pwm_ch, (EE_UINT32)(duty * EE_PWM_DUTY_MAX));
}

static void end(scicos_block *block)
{
    EE_UINT16 pwm_ch = block->ipar[0];
    
    if ((pwm_ch < 1) || (pwm_ch > 4))
        return;

    EE_easylab_pwm_close(pwm_ch);
}

void easylab_pwm(scicos_block *block,int flag)
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
