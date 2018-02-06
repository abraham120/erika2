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
#include "scicos_block4.h"
#include <stdio.h>

void summation_ui32s(scicos_block *block,int flag)
{
 if((flag==1)|(flag==6)) {
    int j,k;
    int nu,mu,nin;
    unsigned long *y;
    int *ipar;
    double v,l;
    double *rpar;
    unsigned long *u;

    y=Getuint32OutPortPtrs(block,1);
    nu=GetInPortRows(block,1);
    mu=GetInPortCols(block,1);
    ipar=GetIparPtrs(block);
    rpar=GetRparPtrs(block);
    nin=GetNin(block);
    l=pow(2,32);
    if (nin==1){
      v=0;
      u=Getuint32InPortPtrs(block,1);
      for (j=0;j<nu*mu;j++) {
	v=v+(double)u[j];
      }
      if (v>=l)  v=l-1;
      else if (v<0) v=0;
      y[0]=(unsigned long)v; 
    }
    else {
      for (j=0;j<nu*mu;j++) {
        v=0;
	for (k=0;k<nin;k++) {
	  u=Getuint32InPortPtrs(block,k+1);
          if(ipar[k]>0){
	     v=v+(double)u[j];
	    }
	  else{
	     v=v-(double)u[j];}
      }
      if (v>=l)  v=l-1;
      else if (v<0) v=0;
      y[j]=(unsigned long)v;
    }
   }
  }
}
