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
 
 
/* Copyright INRIA */
#include "machine.h"

void 
zcross2(flag,nevprt,t,xd,x,nx,z,nz,tvec,ntvec,rpar,nrpar,
	ipar,nipar,u,nu,g,ng)
     int *flag,*nevprt,*nx,*nz,*ntvec,*nrpar,ipar[],*nipar,*nu,*ng;
     double x[],xd[],z[],tvec[],rpar[];
     double u[],g[],*t;
     
{
  
  int i,j;
  int surface_matched,exist_enabled_surface;

  exist_enabled_surface=0;
  if ((*flag==3) &&(*nevprt<0)){
    for(i=0;i<*ntvec;i++){
      surface_matched=1;
      exist_enabled_surface=0;
      
      for (j=0;j<*ng;j++){
	if (rpar[(*ng+1)*i+j]!=0){
	  exist_enabled_surface=1;
	  if((rpar[(*ng+1)*i+j]*g[j])<=0){
	    surface_matched=0;
	  }
	}
      }
      
      if(( surface_matched==1)&&(exist_enabled_surface ==1))
	tvec[i]=*t+rpar[(*ng+1)*i+*ng];
      else
	tvec[i]=-1;
      
    }
  }
  else{
    if(*flag==9){
      for(i=0;i<*ng;i++)
	g[i]=u[i];
    }
  }
}

