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

//* DerivativeState    0
//* OutputUpdate       1
//* StateUpdate        2
//* OutputEventTiming  3
//* Initialization     4
//* Ending             5
//* 
//* ReInitialization   6
//* ModeZeroCrossing   9

void  absolute_value(scicos_block *block,int flag)
{
  int i,j;
  if (flag==1){
    if( block->ng>0){
      for(i=0;i<block->insz[0];++i){
	if (get_phase_simulation()==1) {
	  if (block->inptr[0][i]<0){
	    j=2;
	  } else{
	    j=1;
	  }
	}else {
	  j=block->mode[i];
	}
	if (j==1){
	  block->outptr[0][i]=block->inptr[0][i];
	} else{
	  block->outptr[0][i]=-block->inptr[0][i];
	}
      }
    }else{
      for(i=0;i<block->insz[0];++i){
	if (block->inptr[0][i]<0){
	  block->outptr[0][i]=-block->inptr[0][i];
	}else{
	  block->outptr[0][i]=block->inptr[0][i];
	}
      }
    }
  }else if (flag==9){
    for(i=0;i<block->insz[0];++i){
      block->g[i]=block->inptr[0][i];
      if (get_phase_simulation()==1) {
	if(block->g[i]<0){
	  block->mode[i]=2;
	}else{
	  block->mode[i]=1;
	}
      }
    }
  }
}
