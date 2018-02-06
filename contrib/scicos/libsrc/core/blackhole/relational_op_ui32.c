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
#include <math.h>

void relational_op_ui32(scicos_block *block,int flag)
{
  unsigned long *u1,*u2,*y;
  int *ipar;
  int k,i,m,n;
  m=GetInPortRows(block,1);
  n=GetInPortCols(block,1);
  u1=Getuint32InPortPtrs(block,1);
  u2=Getuint32InPortPtrs(block,2);
  y=Getuint32OutPortPtrs(block,1);
  ipar=GetIparPtrs(block);
  if (flag==1)
  {if ((block->ng!=0)&(get_phase_simulation()==2)) 
	{for(i=0;i<m*n;i++) *(y+i)=block->mode[i]-1;}
   else{
	for(i=0;i<m*n;i++) y[i]=0;
	k=ipar[0];
   	switch(k)
		{case 0:
			for(i=0;i<m*n;i++)
			     {if (u1[i]==u2[i]) y[i]=1;}
	 	break;
		case 1:
			for(i=0;i<m*n;i++)
			     {if (u1[i]!=u2[i]) y[i]=1;}
		break;
		case 2:
			for(i=0;i<m*n;i++)
			     {if (u1[i]<u2[i]) y[i]=1;}
		break;
		case 3:
			for(i=0;i<m*n;i++)
			     {if (u1[i]<=u2[i]) y[i]=1;}
		break;
		case 4:
			for(i=0;i<m*n;i++)
			     {if (u1[i]>u2[i]) y[i]=1;}
		break;
		case 5:
			for(i=0;i<m*n;i++)
			     {if (u1[i]>=u2[i]) y[i]=1;}
		break;
		}
	}
  }
  else if (flag==9)
  {for(i=0;i<m*n;i++) block->g[i]=*(u1+i)-*(u2+i);
   if (get_phase_simulation()==1)
	{for(i=0;i<m*n;i++) block->mode[i]=(int)1;
	k=ipar[0];
   	switch(k)
		{case 0:
			for(i=0;i<m*n;i++)
			    {if (u1[i]==u2[i]) block->mode[i]=(int)2;}
	 	break;
		case 1:
			for(i=0;i<m*n;i++)
			    {if (u1[i]!=u2[i]) block->mode[i]=(int)2;}
		break;
		case 2:
			for(i=0;i<m*n;i++)
			    {if (u1[i]<u2[i]) block->mode[i]=(int)2;}
		break;
		case 3:
			for(i=0;i<m*n;i++)
			    {if (u1[i]<=u2[i]) block->mode[i]=(int)2;}
		break;
		case 4:
			for(i=0;i<m*n;i++)
			    {if (u1[i]>u2[i]) block->mode[i]=(int)2;}
		break;
		case 5:
			for(i=0;i<m*n;i++)
			    {if (u1[i]>=u2[i]) block->mode[i]=(int)2;}
		break;
		}
	}
  }

}
