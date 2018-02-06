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
    @file easylab_adc.c
    @brief www.scicos.org, www.scicoslab.org
    @author Roberto Bucher, SUPSI- Lugano
    @author Simone Mannori, ScicosLab developer
    @date 2006-2010
*/

#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "mcu/microchip_dspic/inc/ee_adc.h"

static EE_AdcChId getAdcChId(EE_UINT16 adc_ch){
    EE_AdcChId adc_ch_id;
    switch(adc_ch){
        case 1:
            adc_ch_id = EE_ADC_AN1;
        break;
        case 2:
            adc_ch_id = EE_ADC_AN2;
        break;
        case 3:
            adc_ch_id = EE_ADC_AN3;
        break;
        case 4:
            adc_ch_id = EE_ADC_AN4;
        break;
        default:
            adc_ch_id = EE_ADC_AN1;
    }
    return adc_ch_id;
}

static void init(scicos_block *block)
{
    EE_UINT16 adc_ch = block->ipar[0];
    if((adc_ch < 1) || (adc_ch > 4))
        return;

    EE_AdcChId adc_ch_id = getAdcChId(adc_ch);
    EE_easylab_adc_init_ch(adc_ch_id);
}

static void inout(scicos_block *block)
{
    EE_UINT16 adcdata;
    float * y = block->outptr[0];

    EE_UINT16 adc_ch = block->ipar[0];

    if((adc_ch < 1) || (adc_ch > 4)) {
        y[0] = -1.0f ;
        return;
    }
    EE_easylab_adc_start(EE_ADC_VDD_VSS, EE_ADC_12_BIT);
    EE_AdcChId adc_ch_id = getAdcChId(adc_ch);
    EE_easylab_adc_get_ch_uint(adc_ch_id, &adcdata);
    adcdata = (adcdata * EE_ADC_VDD_mV) / EE_ADC_RES_MAX;
    y[0] = adcdata * 0.001f;
}

static void end(scicos_block *block)
{
    EE_easylab_adc_stop( );
}

void easylab_adc(scicos_block *block,int flag)
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
