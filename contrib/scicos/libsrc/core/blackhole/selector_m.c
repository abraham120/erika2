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
 
 
#include "scicos_block4.h"
#include "machine.h"
#include <memory.h>

void selector_m(scicos_block *block,int flag)
 {
  void *u;
  void *y;
  double *z;
  int nu,mu,ic,nev,nin,so;

  z=GetDstate(block);
  nin=GetNin(block);
  ic=(int)z[0];
  if (flag<3)
     {ic=0;
      nev=GetNevIn(block);
      while (nev>=1) 
           {
     	    ic=ic+1;
     	    nev=nev/2;
    	   }
     }
  if (nin>1)
     {
      mu=GetInPortRows(block,ic);
      nu=GetInPortCols(block,ic);
      u=GetInPortPtrs(block,ic);
      so=GetSizeOfOut(block,1);
      y=GetOutPortPtrs(block,1);
      memcpy(y,u,mu*nu*so);
      }
   else
      {
       mu=GetInPortRows(block,1);
       nu=GetInPortCols(block,1);
       u=GetRealInPortPtrs(block,1);
       y=GetRealOutPortPtrs(block,ic);
       so=GetSizeOfIn(block,1);
       memcpy(y,u,mu*nu*so);
       }
}
