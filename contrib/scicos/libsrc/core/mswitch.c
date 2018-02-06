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
 

#include <machine.h>
#include <scicos_block4.h>

#include <math.h>
#include <string.h>

#define GetRealInPortElem(blk,x,y) ((GetRealInPortPtrs(blk, x))[y-1])
#define GetIparElem(blk,x) (GetIparPtrs(blk)[x-1])

void  mswitch(scicos_block *block,int flag)
{
  int i,j=0; // j=0 to remove compiler warning
  
  i = GetIparElem(block,2);
  if (i==0) {
    if (GetRealInPortElem(block,1,1)>0) {
      j=(int)floor( GetRealInPortElem(block,1,1) );
    }else{
      j=(int)ceil( GetRealInPortElem(block,1,1) );
    }
  }else if (i==1) {
    if (GetRealInPortElem(block,1,1)>0) {
      j=(int)floor( GetRealInPortElem(block,1,1) +.5);
    }else{
      j=(int)ceil( GetRealInPortElem(block,1,1) -.5);
    }
  }else if (i==2) {
    j=(int)ceil(  GetRealInPortElem(block,1,1) );
  }else if (i==3) {
    j=(int)floor( GetRealInPortElem(block,1,1) );
  }
  
  j=j + 1 - GetIparElem(block,1);
  j=max(j,1);
  j=min(j,GetNin(block)-1);
  int num = GetInPortCols(block, j+1) * GetInPortRows(block, j+1) * GetSizeOfIn(block, j+1);
  void *dst = GetOutPortPtrs(block, 1);
  void *src = GetInPortPtrs(block, j+1);
  memcpy( dst, src, num);
}
