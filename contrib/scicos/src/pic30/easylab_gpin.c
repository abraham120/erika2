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
    @file easylab_gpin.c
    @brief www.scicos.org, www.scicoslab.org
    @author Errico Guidieri
    @date 2006-2011
*/

#include <ee.h>

#include <machine.h>
#include <scicos_block4.h>

/* GPIO bit allocation 

Scicos    Function    dsPIC     LED
Pin=1      GPIO1       RA3       7
Pin=2      GPIO2       RB4       8
Pin=3      GPIO3       RA4       9
Pin=4      GPIO4       RB5       10
Pin=5      GPIO5       RB12      1
Pin=6      GPIO6       RB13      2 
Pin=7      GPIO7       RB7       3
Pin=8      GPIO8       RB6       4
*/

static void init(scicos_block *block)
{
    EE_INT16 pin = block->ipar[0];
    
    if ( (pin < 1) || (pin > 8) )
        return;
    switch(pin){
        case 1:
            /* TRISAbits.TRISA3 = 1; */ 
            /* is an input */
            EE_dio1_configure(1);
        break;
        case 2:
            /* TRISBbits.TRISB4 = 1; */
            /* is an input */
            EE_dio2_configure(1);
        break;
        case 3:
            /* TRISAbits.TRISA4 = 1;  */
            /* is an input */
            EE_dio3_configure(1);
        break;
        case 4:
            /* TRISBbits.TRISB5 = 1; */
            /* is an input */
            EE_dio4_configure(1);
        break;
        case 5:
            /* TRISBbits.TRISB12 = 1; */
            /* is an input */
            EE_dio5_configure(1);
        break;
        case 6:
            /* TRISBbits.TRISB13 = 1; */
            /* is an input */
            EE_dio6_configure(1);
        break;
        case 7:
            /* TRISBbits.TRISB7 = 1; */ 
            /* is an input */
            EE_dio7_configure(1);
        break;
        case 8:
            /* TRISBbits.TRISB6 = 1; */
            /* is an input */
            EE_dio8_configure(1);
        break;
    }
}

static void inout(scicos_block *block)
{
    float* y = block->outptr[0];
    unsigned int pin = block->ipar[0];
    
    if ((pin < 1) || (pin > 8))
        return;

    switch(pin){
        case 1:
            /*PORTAbits.RA3*/
            *y = (EE_dio1_read())? 1.0f: 0.0f; 
        break;
        case 2:
            /*PORTBbits.RB4*/
            *y = (EE_dio2_read())? 1.0f: 0.0f;
        break;
        case 3:
            /*PORTAbits.RA4*/
            *y = (EE_dio3_read())? 1.0f: 0.0f;
        break;
        case 4:
            /*PORTBbits.RB5*/
            *y = (EE_dio4_read())? 1.0f: 0.0f;
        break;
        case 5:
            /*PORTBbits.RB12*/
            *y = (EE_dio5_read())? 1.0f: 0.0f;
        break;
        case 6:
            /*PORTBbits.RB13*/
            *y = (EE_dio6_read())? 1.0f: 0.0f;
        break;
        case 7:
            /*PORTBbits.RB7*/
            *y = (EE_dio7_read())? 1.0f: 0.0f;
        break;
        case 8:
            /*PORTBbits.RB6*/
            *y = (EE_dio8_read())? 1.0f: 0.0f;
        break;
    }
}

static void end(scicos_block *block)
{
}

void easylab_gpin(scicos_block *block,int flag)
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
