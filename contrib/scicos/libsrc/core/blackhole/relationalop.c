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


void relationalop(scicos_block *block,int flag)
{
  int i;
  i=block->ipar[0];
  if(flag==1){
    if ((block->ng!=0)&(get_phase_simulation()==2))
      {
	block->outptr[0][0]=block->mode[0]-1.0;
      }
    else {
      switch (i)
	{
	case 0:
	  if(block->inptr[0][0]==block->inptr[1][0]) {
	    block->outptr[0][0]=1.0;
	  }else{
	    block->outptr[0][0]=0.0;
	  }
	  break;
	  
	case 1:
	  if(block->inptr[0][0]!=block->inptr[1][0]) {
	    block->outptr[0][0]=1.0;
	  }else{
	    block->outptr[0][0]=0.0;
	  }
	  break;
	case 2:
	  if(block->inptr[0][0]<block->inptr[1][0]) {
	    block->outptr[0][0]=1.0;
	  }else{
	    block->outptr[0][0]=0.0;
	  }
	  break;    
	case 3:
	  if(block->inptr[0][0]<=block->inptr[1][0]) {
	    block->outptr[0][0]=1.0;
	  }else{
	    block->outptr[0][0]=0.0;
	  }
	  break;   
	case 4:
	  if(block->inptr[0][0]>=block->inptr[1][0]) {
	    block->outptr[0][0]=1.0;
	  }else{
	    block->outptr[0][0]=0.0;
	  }
	  break;   
	case 5:
	  if(block->inptr[0][0]>block->inptr[1][0]) {
	    block->outptr[0][0]=1.0;
	  }else{
	    block->outptr[0][0]=0.0;
	  }
	  break;
	}
    }

  }else if(flag==9){
    block->g[0]=block->inptr[0][0]-block->inptr[1][0];
    if (get_phase_simulation()==1) {
      switch (i)
	{
	case 0:
	  if(block->inptr[0][0]==block->inptr[1][0]) {
	    block->mode[0]=(int)2.0;
	  }else{
	    block->mode[0]=(int)1.0;
	  }
	  break;
	  
	case 1:
	  if(block->inptr[0][0]!=block->inptr[1][0]) {
	    block->mode[0]=(int)2.0;
	  }else{
	    block->mode[0]=(int)1.0;
	  }
	  break;
	case 2:
	  if(block->inptr[0][0]<block->inptr[1][0]) {
	    block->mode[0]=(int)2.0;
	  }else{
	    block->mode[0]=(int)1.0;
	  }
	  break;    
	case 3:
	  if(block->inptr[0][0]<=block->inptr[1][0]) {
	    block->mode[0]=(int)2.0;
	  }else{
	    block->mode[0]=(int)1.0;
	  }
	  break;   
	case 4:
	  if(block->inptr[0][0]>=block->inptr[1][0]) {
	    block->mode[0]=(int)2.0;
	  }else{
	    block->mode[0]=(int)1.0;
	  }
	  break;   
	case 5:
	  if(block->inptr[0][0]>block->inptr[1][0]) {
	    block->mode[0]=(int)2.0;
	  }else{
	    block->mode[0]=(int)1.0;
	  }
	  break;
	}
    }
  }
}
