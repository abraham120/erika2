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

void  integralz_func(scicos_block *block,int flag)
{int i;
 double *ur,*ui;
 double *yr,*yi;
 ur=GetRealInPortPtrs(block,1);
 ui=GetImagInPortPtrs(block,1);
 yr=GetRealOutPortPtrs(block,1);
 yi=GetImagOutPortPtrs(block,1);
 if (flag==0){
    if(block->ng>0){
      for(i=0;i<(block->nx)/2;++i) {
	if(block->mode[i]==3){
	  block->xd[i]=ur[i];
	  block->xd[i+(block->nx)/2]=ui[i];
	}else{
	  block->xd[i]=0.0;
	  block->xd[i+(block->nx)/2]=0.0;
	}
      }
    }else{
      for(i=0;i<(block->nx)/2;++i) {
	block->xd[i]=ur[i];
	block->xd[i+(block->nx)/2]=ui[i];
      }
    }
  }else if (flag==1||flag==6){
    for(i=0;i<(block->nx)/2;++i) {
      yr[i]=block->x[i];
      yi[i]=block->x[i+(block->nx)/2];
    }
  }else if (flag==2&&block->nevprt==1){
    for(i=0;i<(block->nx)/2;++i) {
      block->x[i]=ur[i];
      block->x[i+(block->nx)/2]=ui[i];
    }
  } else if (flag==9){
    for(i=0;i<(block->nx)/2;++i) {
      if (block->mode[i]==3){
	block->g[i]=(block->x[i]-(block->rpar[i]))*(block->x[i]-(block->rpar[(block->nx)/2+i]));
	block->g[i+(block->nx)/2]=(block->x[i+(block->nx)/2]-(block->rpar[i+(block->nx)]))*(block->x[i+(block->nx)/2]-(block->rpar[3*(block->nx)/2+i]));
      } else {
	block->g[i]=ur[i];
	block->g[i+(block->nx)/2]=ui[i];
      } 
      if (get_phase_simulation()==1) {
	if (ur[i]>=0&&block->x[i]>=block->rpar[i]&&ui[i>=0]&&block->x[i+(block->nx)/2]>=block->rpar[i+(block->nx)]){
	  block->mode[i]=1;
	}else if (ur[i]<=0&&block->x[i]<=block->rpar[(block->nx)/2+i]&&ui[i]<=0&&block->x[i+(block->nx)/2]<=block->rpar[3*(block->nx)/2+i]){
	  block->mode[i]=2;
	}else {
	  block->mode[i]=3;
	}
      }
    }
  }
}
