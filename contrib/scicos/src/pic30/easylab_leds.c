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
    @file flex_daughter_leds.c
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri
    @date 2006-2010
*/ 


#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

static void init(scicos_block *block)
{
    EE_INT16 pin = block->ipar[0];
    
    if ( pin < 1 || pin > 8) {
        /* return if outside the allowed range */
        return; 
    }

    switch (pin) {
        case 1:
            EE_led1_init();
        break;
        case 2:
            EE_led2_init();
        break;
        case 3:
            EE_led3_init();
        break;
        case 4:
            EE_led4_init();
        break;
        case 5:
            EE_led5_init();
        break;
        case 6:
            EE_led6_init();
        break;
        case 7:
            EE_led7_init();
        break;
        case 8:
            EE_led8_init();
        break;
    }
}

static void inout(scicos_block *block)
{
    EE_INT16 pin = block->ipar[0];

    if ( pin < 1 || pin > 8) {
        /* return if outside the allowed range */
        return;
    }

    float u = *(float *)block->inptr[0];
    float led_threshold = block->rpar[0];

    if( led_threshold < 0.01 || led_threshold > 0.99 )
        led_threshold = 0.5;

    switch (pin) {
        case 1:
            if (u > led_threshold)
                EE_led1_on();
            else
                EE_led1_off();
            break;
        case 2:
            if (u > led_threshold)
                EE_led2_on();
            else
                EE_led2_off();
            break;
        case 3:
            if (u > led_threshold)
                EE_led3_on();
            else
                EE_led3_off();
            break;
        case 4:
            if (u > led_threshold)
                EE_led4_on();
            else
                EE_led4_off();
            break;
        case 5:
            if (u > led_threshold)
                EE_led5_on();
            else
                EE_led5_off();
            break;
        case 6:
            if (u > led_threshold)
                EE_led6_on();
            else
                EE_led6_off();
            break;
        case 7:
            if (u > led_threshold)
                EE_led7_on();
            else
                EE_led7_off();
            break;
        case 8:
            if (u > led_threshold)
                EE_led8_on();
            else
                EE_led8_off();
            break;
    }
}

static void end(scicos_block *block)
{
    EE_INT16 pin = block->ipar[0];
    switch (pin) {
        case 1:
            EE_led1_off();
        break;
        case 2:
            EE_led2_off();
        break;
        case 3:
            EE_led3_off();
        break;
        case 4:
            EE_led4_off();
        break;
        case 5:
            EE_led5_off();
        break;
        case 6:
            EE_led6_off();
        break;
        case 7:
            EE_led7_off();
        break;
        case 8:
            EE_led8_off();
        break;
    }
}

void easylab_leds(scicos_block *block,int flag)
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
