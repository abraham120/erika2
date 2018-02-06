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
 
 
# include "scicos_block4.h"
# include "machine.h"
#include <stdio.h>
extern int C2F(dgetrf)();
extern int C2F(dlaswp)();

#if WIN32
#define NULL    0
#endif

#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif

typedef struct
{         int *ipiv;
          double *dwork;
	  double *IL;
	  double *IU;
} mat_lu_struct ;
void mat_lu(scicos_block *block,int flag)
{
 double *u;
 double *y1;
 double *y2;
 int mu;
 int nu;
 int info;
 int i,j,l,ij,ik;
 mat_lu_struct *ptr;
 
 mu =GetInPortRows(block,1);
 nu =GetInPortCols(block,1);
 u=GetRealInPortPtrs(block,1);
 y1=GetRealOutPortPtrs(block,1);
 y2=GetRealOutPortPtrs(block,2);
 l=min(mu,nu);
             /*init : initialization*/
if (flag==4)
   {if((*(block->work)=(mat_lu_struct*) scicos_malloc(sizeof(mat_lu_struct)))==NULL)
	{set_block_error(-16);
	 return;}
    ptr=*(block->work);
    if((ptr->ipiv=(int*) scicos_malloc(sizeof(int)*nu))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr);
	 return;}
    if((ptr->dwork=(double*) scicos_malloc(sizeof(double)*(mu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->ipiv);
	 scicos_free(ptr);
	 return;}
    if((ptr->IL=(double*) scicos_malloc(sizeof(double)*(mu*l)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->dwork);
	 scicos_free(ptr->ipiv);
	 scicos_free(ptr);
	 return;}
    if((ptr->IU=(double*) scicos_malloc(sizeof(double)*(l*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->IL);
	 scicos_free(ptr->dwork);
	 scicos_free(ptr->ipiv);
	 scicos_free(ptr);
	 return;}
   }

       /* Terminaison */
else if (flag==5)
   {ptr=*(block->work);
    if((ptr->IU)!=NULL){
    	scicos_free(ptr->ipiv);
    	scicos_free(ptr->dwork);
    	scicos_free(ptr->IL);
    	scicos_free(ptr->IU);
    	scicos_free(ptr);
    	return;}
   }

else
   {
    ptr=*(block->work);
    for (i=0;i<(mu*nu);i++)   { ptr->dwork[i]=u[i];}
    C2F(dgetrf)(&mu,&nu,ptr->dwork,&mu,ptr->ipiv,&info);
    if (info !=0)
       {if (flag!=6)
   	{set_block_error(-7);
        return;}}
   for (j=0;j<l;j++)
	{for (i=0;i<mu;i++)
	     {ij=i+j*mu;
	      if (i==j)
		{*(y2+ij)=1;}
	      else if (i>j)
		{*(y2+ij)=*(ptr->dwork+ij);}
	      else 
		{*(y2+ij)=0;}
	      }
	}
	for (j=0;j<nu;j++)
	{for (i=0;i<l;i++)
	     {ij=i+j*l;
	      ik=i+j*mu;
	      if (i<=j)
		{*(y1+ij)=*(ptr->dwork+ik);}
	      else
		{*(y1+ij)=0;}
	      }
 	}
   }
}
