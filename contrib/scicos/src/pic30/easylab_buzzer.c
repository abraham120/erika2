/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2011 Evidence Srl
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
    @file easylab_buzzer.c
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri
    @date 2006-2011
*/


#include <machine.h>
#include <scicos_block4.h>
#include <math.h>

#include <ee.h>

#include "mcu/microchip_dspic/inc/ee_utils.h"

static void init(scicos_block *block)
{

}

static void end(scicos_block *block)
{
    EE_buzzer_stop();
}

static void inout(scicos_block *block)
{
    static const EE_UINT16 frequency_span = EE_BUZZER_MAX_FREQ - EE_BUZZER_MIN_FREQ;

    /* Stop the buzzer as first thing */
    EE_buzzer_stop();

    /* Evaluate new frequency. If IN is equal to Zero don't start it */
    float new_freq_f = ((float *)block->inptr[0])[0];
    if(new_freq_f > 0.0F)
    {
        /* Saturate IN to 1.0 */
        if(new_freq_f > 1.0F)
            new_freq_f = 1.0F;
        /* Frequency in Hz */
        EE_UINT32 new_span = new_freq_f * frequency_span;
        EE_UINT32 new_freq = new_span + EE_BUZZER_MIN_FREQ;
        EE_buzzer_start(new_freq);
    }
}

void easylab_buzzer(scicos_block *block,int flag)
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
