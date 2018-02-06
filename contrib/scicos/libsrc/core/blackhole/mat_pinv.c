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
extern int C2F(dgesvd)();
extern int C2F(dlaset)();
extern int C2F(dlacpy)();

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
{         double *l0;
	  double *LA;
 	  double *LC;
          double *LS;
          double *LSV;
          double *LSW;
          double *LU;
          double *LUT;
          double *LV;
          double *LVT;
          double *dwork;
} mat_pinv_struct ;
void mat_pinv(scicos_block *block,int flag)
{
 double *u;
 double *y;
 int nu,mu;
 int info;
 int i,j,ij,ji,ii,lwork;
 mat_pinv_struct *ptr;
 mu=GetInPortRows(block,1);
 nu=GetInPortCols(block,1);
 u=GetRealInPortPtrs(block,1);
 y=GetRealOutPortPtrs(block,1);
 lwork=max(3*min(mu,nu)+max(mu,nu),5*min(mu,nu)-4); 
             /*init : initialization*/
if (flag==4)
   {if((*(block->work)=(mat_pinv_struct*) scicos_malloc(sizeof(mat_pinv_struct)))==NULL)
	{set_block_error(-16);
	 return;}
    ptr=*(block->work);
    if((ptr->l0=(double*) scicos_malloc(sizeof(double)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr);
	 return;}
    if((ptr->LA=(double*) scicos_malloc(sizeof(double)*(mu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LC=(double*) scicos_malloc(sizeof(double)*(nu*mu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LS=(double*) scicos_malloc(sizeof(double)*(nu*mu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LSV=(double*) scicos_malloc(sizeof(double)*(min(mu,nu))))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LSW=(double*) scicos_malloc(sizeof(double)*(min(mu,nu))))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LU=(double*) scicos_malloc(sizeof(double)*(mu*mu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LSW);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LUT=(double*) scicos_malloc(sizeof(double)*(mu*mu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LU);
	 scicos_free(ptr->LSW);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LV=(double*) scicos_malloc(sizeof(double)*(nu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LUT);
	 scicos_free(ptr->LU);
	 scicos_free(ptr->LSW);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->LVT=(double*) scicos_malloc(sizeof(double)*(nu*nu)))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LV);
	 scicos_free(ptr->LUT);
	 scicos_free(ptr->LU);
	 scicos_free(ptr->LSW);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
    if((ptr->dwork=(double*) scicos_malloc(sizeof(double)*lwork))==NULL)
	{set_block_error(-16);
	 scicos_free(ptr->LVT);
	 scicos_free(ptr->LV);
	 scicos_free(ptr->LUT);
	 scicos_free(ptr->LU);
	 scicos_free(ptr->LSW);
	 scicos_free(ptr->LSV);
	 scicos_free(ptr->LS);
	 scicos_free(ptr->LC);
	 scicos_free(ptr->LA);
	 scicos_free(ptr->l0);
	 scicos_free(ptr);
	 return;}
   }

       /* Terminaison */
else if (flag==5)
   {ptr=*(block->work);
    if((ptr->dwork)!=0){
    	scicos_free(ptr->LC);
    	scicos_free(ptr->l0);
    	scicos_free(ptr->LA);
    	scicos_free(ptr->LSW);
    	scicos_free(ptr->LS);
    	scicos_free(ptr->LSV);
    	scicos_free(ptr->LU);
    	scicos_free(ptr->LUT);
    	scicos_free(ptr->LV);
    	scicos_free(ptr->LVT);
    	scicos_free(ptr->dwork);
    	scicos_free(ptr);
    	return;}
   }

else
   {
    ptr=*(block->work);
    for(i=0;i<mu*nu;i++) y[i]=0;
    C2F(dlacpy)("F",&mu,&nu,u,&mu,ptr->LA,&mu);
    C2F(dgesvd)("A","A",&mu,&nu,ptr->LA,&mu,ptr->LSV,ptr->LU,&mu,ptr->LVT,&nu,ptr->dwork,&lwork,&info);
     if (info !=0)
       {if (flag!=6)
   	{set_block_error(-7);
        return;}}
    for (i=0;i<min(mu,nu);i++)  
	 {if (*(ptr->LSV+i)!=0)
	      {*(ptr->LSW+i)=1/(*(ptr->LSV+i));}
	 else 
	      {*(ptr->LSW+i)=0;}}
    *(ptr->l0)=0;
     C2F(dlaset)("F",&nu,&mu,ptr->l0,ptr->l0,ptr->LS,&nu);
    for (i=0;i<min(mu,nu);i++)
	{ii=i+i*nu;
	 *(ptr->LS+ii)=*(ptr->LSW+i);}
    for (j=0;j<mu;j++)
	{for (i=j;i<mu;i++)
		{ij=i+j*mu;
	 	 ji=j+i*mu;
		 *(ptr->LUT+ij)=*(ptr->LU+ji);
		 *(ptr->LUT+ji)=*(ptr->LU+ij);}
	}
    for (j=0;j<nu;j++)
	{for (i=j;i<nu;i++)
		{ij=i+j*nu;
	 	 ji=j+i*nu;
		 *(ptr->LV+ij)=*(ptr->LVT+ji);
		 *(ptr->LV+ji)=*(ptr->LVT+ij);}
	}
      dmmul(ptr->LV,&nu,ptr->LS,&nu,ptr->LC,&nu,&nu,&nu,&mu);
      dmmul(ptr->LC,&nu,ptr->LUT,&mu,y,&nu,&nu,&mu,&mu);
   }
}
