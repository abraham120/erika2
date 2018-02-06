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
	@file rt_sinus.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@author Dario Di Stefano, Evidence Srl
	@author Errico Guidieri, Evidence Srl
	@date 2006-2011
*/

#include "ee.h"

#include "machine.h"
#include "scicos_block4.h"

#include <math.h>

/* Declaration of externalad defined functions */
extern double       get_scicos_period(void);

/* block->rpar[x]         */
/* 0 : Amplitude      : A */
/* 1 : Frequency (Hz) : F */
/* 2 : phase (rad)    : P */
/* 3 : DC bias        : B */
/* 4 : act.delay(sec) : D */

# define A  (block->rpar[0])
# define F  (block->rpar[1])
# define P  (block->rpar[2])
# define B  (block->rpar[3])
# define D  (block->rpar[4])

/* Pseudocode 

   EE_UINT16    tick   : icremented by one each isr call
   double scicos_time  : isr period (sec)

   double phase        : (radian)

init 

   // counter initialization
   counter = (EE_UINT16) (delay/scicos_time) 
   
isr

   pt = (double) (counter * scicos_time)
   phase = fmod(2*pi*F*(pt - D) - P,(2*pi))
   y = A*sin(phase)+B

*/

static void init(scicos_block *block)
{
    /* N° ticks x delay */
    /* N.B trick to use roundig not truncation */
    EE_UINT32 delay_ticks = (EE_UINT32)((D / get_scicos_period()) + 0.5);
    D = -1.0 * delay_ticks; /* NOTE: now D is not the delay but is an internal variable used to count the occurred ticks */
    
    double * y = block->outptr[0];
    y[0]=0.0;
}

static void inout(scicos_block *block)
{
    /* Pi constant */
    static const double pi = 3.1415927;
    /* Block output pointer */
    double * y = block->outptr[0];
    
    /* incremente the counter */
    D += 1;
    /* phase increment for each tick (Frequency (Hz) * tick length) */
    double tick_phase_increment = F * get_scicos_period();
    /* N° ticks x multi_period => [(1 / F) -> period (sec.)] * [(1 / scicos_period) -> n° ticks per period] 
       => 1 / tick_phase_increment */
    /* For the multiperiod: scicos_period/(F*scicos_period) and to have an integer value we can use [ms] => 1000/F with F<=1000 Hz */
    /* N.B trick to use roundig not truncation */
    EE_UINT32 period_ticks = (EE_UINT32)(1000.0/F + 0.5);

    if (D < 0.0) {
        /* Activation delay time D */
        y[0] = 0.0;
    } else {
        /* sine phase */
        double phase = 2*pi*D*tick_phase_increment - P;
        y[0] = A*sin(phase) + B ;
        /* reset the counter at the counter end */
        if((EE_UINT32)D == period_ticks)
            D = 0;
    }
}

static void end(scicos_block *block)
{
    double * y = block->outptr[0];
    y[0]=0.0;
}

void rt_sinus(scicos_block *block,int flag)
{
    if (flag == 1){          /* set output */
        inout(block);
    } else if (flag == 5){     /* termination */ 
        end(block);
    } else if (flag == 4){    /* initialisation */
        init(block);
    }
}


