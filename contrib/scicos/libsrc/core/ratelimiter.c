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
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
#include "scicos_block.h"
#include <math.h>

#if WIN32
#define NULL    0
#endif

//* DerivativeState    0
//* OutputUpdate       1
//* StateUpdate        2
//* OutputEventTiming  3
//* Initialization     4
//* Ending             5
//* 
//* ReInitialization   6
//* ModeZeroCrossing   9

void ratelimiter(scicos_block *block,int flag)
{/*  rpar[0]=rising rate limit, rpar[1]=falling rate limit */
  double* pw,rate=0.0,t; // rate set to 0 to avoid compiler warning
  if (flag == 4){/* the workspace is used to store previous values */
    if ((*block->work=
	 scicos_malloc(sizeof(double)*4))== NULL ) {
      set_block_error(-16);
      return;
    }
    pw=*block->work; 
    pw[0]=0.0;
    pw[1]=0.0;
    pw[2]=0.0;
    pw[3]=0.0;
  }else  if (flag == 5){
    scicos_free(*block->work);
  } else if (flag==1) {
    if (get_phase_simulation()==1) do_cold_restart();
    pw=*block->work; 
    t=get_scicos_time();
    if(t>pw[2]){
      pw[0]=pw[2];
      pw[1]=pw[3];
      rate=(block->inptr[0][0]-pw[1])/(t-pw[0]);
    }
    else if(t<=pw[2]){
      if(t>pw[0]){
	rate=(block->inptr[0][0]-pw[1])/(t-pw[0]);
      }else{
	rate=0.0;
      }
    }
    if(rate>block->rpar[0]){
      block->outptr[0][0]=(t-pw[0])*block->rpar[0]+pw[1];
    } else if(rate<block->rpar[1]){
      block->outptr[0][0]=(t-pw[0])*block->rpar[1]+pw[1];
    }else{
      block->outptr[0][0]=block->inptr[0][0];
    }
    pw[2]=t;
    pw[3]=block->outptr[0][0];
  }
}
