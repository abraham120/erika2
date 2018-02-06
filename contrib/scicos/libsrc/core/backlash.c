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


void backlash(scicos_block *block,int flag)
{ 
  double* rw,t;
  if (flag == 4){/* the workspace is used to store previous values */
    if ((*block->work=	 scicos_malloc(sizeof(double)* 4))== NULL ) {
      set_block_error(-16);
      return;
    }
    rw=*block->work; 
    t=get_scicos_time();
    rw[0]=t;
    rw[1]=t;
    rw[2]=block->rpar[0];
    rw[3]=block->rpar[0];
  }else  if (flag == 5){
    scicos_free(*block->work);
  }else  if (flag == 1) {
    rw=*block->work;
    t=get_scicos_time();
    if(t>rw[1]) {
      rw[0]=rw[1];
      rw[2]=rw[3];
    }
    rw[1]=t;
    if(block->inptr[0][0]>rw[2]+block->rpar[1]/2){
      rw[3]=block->inptr[0][0]-block->rpar[1]/2;
    } else if (block->inptr[0][0]<rw[2]-block->rpar[1]/2){
      rw[3]=block->inptr[0][0]+block->rpar[1]/2;
    } else {
      rw[3]=rw[2];
    }
    block->outptr[0][0]=rw[3];
  }  else if (flag == 9) {
    rw=*block->work;
    t=get_scicos_time();
    if(t>rw[1]){
      block->g[0] = block->inptr[0][0]-block->rpar[1]/2-rw[3];
      block->g[1] = block->inptr[0][0]+block->rpar[1]/2-rw[3];
    }else{
      block->g[0] = block->inptr[0][0]-block->rpar[1]/2-rw[2];
      block->g[1] = block->inptr[0][0]+block->rpar[1]/2-rw[2];
    }
  } 
}
