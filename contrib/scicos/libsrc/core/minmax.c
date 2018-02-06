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
 
 
#include <math.h>
#include "scicos_block.h"

#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif

void minmax(scicos_block *block,int flag)
{ /*ipar[0]=1 -> min,  ipar[0]=2 -> max */
  
  int i,phase;
  double maxmin;
  phase=get_phase_simulation();
  if (flag == 1) {
    if(block->nin==1){
      if((block->ng==0)||(phase==1)){
	maxmin=block->inptr[0][0];
	for (i=1;i<block->insz[0];++i){
	  if(block->ipar[0]==1){
	    if(block->inptr[0][i]<maxmin)  maxmin=block->inptr[0][i];
	  } else {
	    if(block->inptr[0][i]>maxmin)  maxmin=block->inptr[0][i];
	  }
	}
      }else{
	maxmin=block->inptr[0][block->mode[0]-1];
      }
      block->outptr[0][0]=maxmin;

    }else if (block->nin==2){
      for (i=0;i<block->insz[0];++i){
	if((block->ng==0)||(phase==1)){
	  if(block->ipar[0]==1){
	    block->outptr[0][i]=min(block->inptr[0][i],block->inptr[1][i]);
	  } else {
	    block->outptr[0][i]=max(block->inptr[0][i],block->inptr[1][i]);
	  }
	}else{
	  block->outptr[0][i]=block->inptr[block->mode[0]-1][i];
	}
      }
    }
  } else if(flag == 9){
    if(block->nin==1){
      if(block->nin==1){
	if (phase==2){
	  for (i=0;i<block->insz[0];++i){
	    if(i!=block->mode[0]-1){
	      block->g[i]=block->inptr[0][i]-block->inptr[0][block->mode[0]-1];
	    }else{
	      block->g[i]=1.0;
	    }
	  }
	} else if (phase==1){
	  maxmin=block->inptr[0][0];
	  for (i=1;i<block->insz[0];++i){
	    block->mode[0]=1;
	    if(block->ipar[0]==1){
	      if(block->inptr[0][i]<maxmin) {
		maxmin=block->inptr[0][i];
		block->mode[0]=i+1;
	      }
	    } else {
	      if(block->inptr[0][i]>maxmin) {
		maxmin=block->inptr[0][i];
		block->mode[0]=i+1;
	      }
	    }
	  }
	}
      }
    }else if(block->nin==2){
      for (i=0;i<block->insz[0];++i){
	block->g[i]=block->inptr[0][i]-block->inptr[1][i];
	if(phase==1){
	  if(block->ipar[0]==1){
	    if(block->g[i]>0) {
	      block->mode[i]=2;
	    }else{
	      block->mode[i]=1;
	    }
	  }else{
	    if(block->g[i]<0) {
	      block->mode[i]=2;
	    }else{
	      block->mode[i]=1;
	    }
	  }
	}
      }
    }
  }
}

