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

#if WIN32
#define NULL    0
#endif

void m_frequ(scicos_block *block,int flag)
{
  double *mat;
  double *Dt;
  double *off;
  long *icount;
  double t;
  long long *counter;
  int m;
  mat=GetRealOparPtrs(block,1);
  Dt=GetRealOparPtrs(block,2);
  off=GetRealOparPtrs(block,3);
  icount=Getint32OparPtrs(block,4);
  m=GetOparSize(block,1,1);
  
  switch(flag)
  {

   case 4 :  {/* the workspace is used to store discrete counter value */
              if ((*block->work=scicos_malloc(sizeof(long long int)*2))==NULL) {
                set_block_error(-16);
                return;
              }
              counter=*block->work;
              if (*icount!=0) (*counter)=(int)mat[0];
              else *counter=0;
              (*(counter+1))=*icount;
              break;
             }

   /* event date computation */
   case 3  : {
              counter=*block->work;
              t=get_scicos_time(); 
              *counter+=(int)mat[*(counter+1)]; /*increase counter*/
              block->evout[(int)mat[*(counter+1)+m]-1]=*off+((double)*counter/(*Dt))-t;
              (*(counter+1))++;
	      *(counter+1)=*(counter+1)%m;
              break;
             }

   /* finish */
   case 5  : {
              scicos_free(*block->work); /*free the workspace*/
              break;
             }

   default : break;
  }
}
