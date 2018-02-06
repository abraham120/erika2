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
//#include <memory.h>
#include <string.h>

void  switch2_m(scicos_block *block,int flag)
{
  int i=0,phase,ipar,mu,nu,so; // =0 to avoid compiler warning
  int *iparptrs;
  double *rpar;
  double *u2;
  void *y,*u;
  iparptrs=GetIparPtrs(block);
  ipar=*iparptrs;
  rpar=GetRparPtrs(block);
  mu=GetInPortRows(block,1);
  nu=GetInPortCols(block,1);
  u2=GetRealInPortPtrs(block,2);
  y=GetOutPortPtrs(block,1);
  if (flag == 1) {
    phase=get_phase_simulation();
    if (phase==1||block->ng==0){
      i=3;
      if (ipar==0){
	if (*u2>=*rpar) i=1;
      }else if (ipar==1){
	if (*u2>*rpar) i=1;
      }else {
	if (*u2!=*rpar) i=1;			     
      }
    }else{
      if(block->mode[0]==1){
	i=1;
      }else if(block->mode[0]==2){
	i=3;
      }
    }
       u=GetInPortPtrs(block,i);
       so=GetSizeOfOut(block,1);
       memcpy(y,u,mu*nu*so);
  }else if(flag == 9){
    phase=get_phase_simulation();
    block->g[0]=*u2-*rpar;
    if (phase==1){
      i=3;
      if (ipar==0){
	if (block->g[0]>=0.0) i=1;
      }else if (ipar==1){
	if (block->g[0]>0.0) i=1;
      }else {
	if (block->g[0]!=0.0) i=1;			     
      }
      if(i==1) {
	block->mode[0]=1;
      }else{
	block->mode[0]=2;
      }
    }
  }
}
