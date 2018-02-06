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

void logicalop_ui16(scicos_block *block,int flag)
{
  int i,m,n,nin,k,j,l;
  int *ipar;
  unsigned short *y,*u;
  m=GetInPortRows(block,1);
  n=GetInPortCols(block,1);
  y=Getuint16OutPortPtrs(block,1);
  ipar=GetIparPtrs(block);
  nin=GetNin(block);
  k=ipar[0];
  switch (k)
	{
	case 0:
	     if (nin==1)
  		 {u=Getuint16InPortPtrs(block,1);
		  if (ipar[1]==0)
		      {*y=1;
                       for(i=0;i<m*n;i++)
     		       	  {if (u[i]<=0)
		       	       {*y=0;
			        break;}
     		      	  }
		      }
		  else
		      {*y=u[0];
		       for (i=1;i<m*n;i++)
			    {*y=(*y)&(u[i]);}
		      }
		 }
	     else
		 {if (ipar[1]==0)
		     {for (i=0;i<m*n;i++)
			   {y[i]=1;
			    for (j=1;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  if (u[i]<=0) 
				      {y[i]=0;
				       break;}
				 } 
			   }
		     }
		 else
		     {for (i=0;i<m*n;i++)
			   {u=Getuint16InPortPtrs(block,1);
			    y[i]=u[i];
			    for (j=2;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  y[i]=(y[i])&(u[i]);
				 }
			   }
		     }
		 }
	break;
	case 1:
	     if (nin==1)
  		 {u=Getuint16InPortPtrs(block,1);
		  *y=0;
		  if (ipar[1]==0)
		      {for(i=0;i<m*n;i++)
     		       	  {if (u[i]>0)
		       	       {*y=1;
			        break;}
     		      	  }
		      }
		  else
		      {for (i=0;i<m*n;i++)
			    {*y=(*y)|(u[i]);}
		      }
		 }
	     else
		 {if (ipar[1]==0)
		     {for (i=0;i<m*n;i++)
			   {y[i]=0;
			    for (j=1;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  if (u[i]>0) 
				      {y[i]=1;
				       break;}
				 }
			   }
		     }
		 else
		     {for (i=0;i<m*n;i++)
			   {y[i]=0;
			    for (j=1;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  y[i]=(y[i])|(u[i]);
				 }
			   }
		     }
		 }
	break;
	case 2:
	     if (nin==1)
  		 {u=Getuint16InPortPtrs(block,1);
		  if (ipar[1]==0)
		      {*y=0;
		       for(i=0;i<m*n;i++)
     		       	  {if (u[i]<=0)
		       	       {*y=1;
			        break;}
     		      	  }
		      }
		  else
		      {*y=u[0];
		       for (i=1;i<m*n;i++)
			    {*y=((*y)&(u[i]));}
		       *y=~*y;
		      }
		 }
	     else
		 {if (ipar[1]==0)
		     {for (i=0;i<m*n;i++)
			   {y[i]=0;
			    for (j=1;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  if (u[i]<=0) 
				      {y[i]=1;
				       break;}
				 } 
			   }
		     }
		 else
		     {for (i=0;i<m*n;i++)
			   {u=Getuint16InPortPtrs(block,1);
			    y[i]=u[i];
			    for (j=2;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  y[i]=((y[i])&(u[i]));
				 }
			    y[i]=~y[i];
			   }
		     }
		 }
	break;
	case 3:
	     if (nin==1)
  		 {u=Getuint16InPortPtrs(block,1);
		  if (ipar[1]==0)
		      {*y=1;
		       for(i=0;i<m*n;i++)
     		       	  {if (u[i]>0)
		       	       {*y=0;
			        break;}
     		      	  }
		      }
		  else
		      {*y=0;
		       for (i=0;i<m*n;i++)
			    {*y=((*y)|(u[i]));}
		       *y=~*y;
		      }
		 }
	     else
		 {if (ipar[1]==0)
		     {for (i=0;i<m*n;i++)
			   {y[i]=1;
			    for (j=1;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  if (u[i]>0) 
				      {y[i]=0;
				       break;}
				 }
			   }
		     }
		 else
		     {for (i=0;i<m*n;i++)
			   {u=Getuint16InPortPtrs(block,1);
			    y[i]=u[i];
			    for (j=2;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  y[i]=((y[i])|(u[i]));
				 }
			    y[i]=~y[i];
			   }
		     }
		 }
	break;
	case 4:
	     if (nin==1)
  		 {u=Getuint16InPortPtrs(block,1);
		  if (ipar[1]==0)
		      {l=0;
		       for(i=0;i<m*n;i++)
     		       	  {if (u[i]>0)
		       	       {l=(l+1)%2;
			       }
     		      	  }
		       *y=(unsigned short)l;
		      }
		  else
		      {*y=u[0];
		       for (i=1;i<m*n;i++)
			    {*y=((*y)^(u[i]));}
		      }
		 }
	     else
		 {if (ipar[1]==0)
		     {for (i=0;i<m*n;i++)
			   {l=0;
			    for (j=1;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  if (u[i]>0) 
				      {l=(l+1)%2;}
				 }
			    y[i]=(unsigned short)l;
			   }
		     }
		 else
		     {for (i=0;i<m*n;i++)
		           {u=Getuint16InPortPtrs(block,1);
		           y[i]=u[i];
			   for (j=2;j<nin+1;j++)
				 {u=Getuint16InPortPtrs(block,j);
				  y[i]=((y[i])^(u[i]));
				 }
			   }
		     }
		 }
	     break;
	case 5:
	     u=Getuint16InPortPtrs(block,1);
	     if (ipar[1]==0)
		 {for (i=0;i<m*n;i++)
		       {if (u[i]>0) y[i]=0;
			else y[i]=1;}
		 }
	     else
		 {for (i=0;i<m*n;i++)
		       {y[i]=~(u[i]);}
		 }
	     break;
	}
}
