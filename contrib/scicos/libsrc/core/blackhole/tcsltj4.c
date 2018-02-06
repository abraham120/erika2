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
#include <memory.h>
#include "machine.h"
#include "scicos_block.h"
#include "sci_mem_alloc.h"  /* malloc */

void tcsltj4(scicos_block *block,int flag)
{
  /* Copyright INRIA

     Scicos block simulator
     continuous state space linear system simulator
     rpar(1:nx*nx)=A
     rpar(nx*nx+1:nx*nx+nx*nu)=B
     rpar(nx*nx+nx*nu+1:nx*nx+nx*nu+nx*ny)=C
     rpar(nx*nx+nx*nu+nx*ny+1:nx*nx+nx*nu+nx*ny+ny*nu)=D */

  int un=1,lb,lc;
  int nx=block->nx;
  double* x=block->x;
  double* xd=block->xd;
  double* rpar=block->rpar;
  double* y=block->outptr[0];
  double* u1=block->inptr[0];
  double* u2=block->inptr[1];
  int* outsz=block->outsz;
  int* insz=block->insz;
    
  lb=nx*nx;
  lc=lb+nx*insz[0];
  
  if (flag ==1 || flag ==6){
    /* y=c*x*/
    dmmul(&rpar[lc],outsz,x,&nx,y,outsz,outsz,&nx,&un);
  }else if (flag == 2 && block->nevprt == 1){
    /* x+=u2 */
    memcpy(x,u2 ,nx*sizeof(double));
  }else if (flag ==0 && block->nevprt == 0){
    /* xd=a*x+b*u1*/
    dmmul(&rpar[0],&nx,x,&nx,xd,&nx,&nx,&nx,&un);
    dmmul1(&rpar[lb],&nx,u1,&insz[0],xd,&nx,&nx,&insz[0],&un);
  }
}

