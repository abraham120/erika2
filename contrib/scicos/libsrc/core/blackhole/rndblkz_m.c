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
#include "machine.h"
#include <math.h>
extern double C2F(urand)();
void rndblkz_m(scicos_block *block,int flag)
{
  double *y_r;
  double *y_i;
  double *rpar;
  double *z;
  int *ipar;
  int ny,my,i,iy_r,iy_i;
  double sr,si,tl;

  my=GetOutPortRows(block,1);
  ny=GetOutPortCols(block,1);
  ipar=GetIparPtrs(block);
  rpar=GetRparPtrs(block);
  y_r=GetRealOutPortPtrs(block,1);
  y_i=GetImagOutPortPtrs(block,1);
  z=GetDstate(block);

  if (flag==2||flag==4) {
    iy_r=(int)z[0];
    iy_i=(int)z[1];
    if (ipar[0]==0) {
      for (i=0;i<my*ny;i++) {
         *(z+i+2)=C2F(urand)(&iy_r);
         *(z+i+2+my*ny)=C2F(urand)(&iy_i);
      }
    }
    else {
      for (i=0;i<my*ny;i++) {
        do {
         sr=2.0*C2F(urand)(&iy_r)-1.0;
         si=2.0*C2F(urand)(&iy_r)-1.0;
         tl=sr*sr+si*si;
        } while(tl>1.0);
        z[i+2]= sr*(sqrt(-2.0*log(tl)/tl));
        do {
         sr=2.0*C2F(urand)(&iy_i)-1.0;
         si=2.0*C2F(urand)(&iy_i)-1.0;
         tl=sr*sr+si*si;
        } while(tl>1.0);
        z[i+2+my*ny]= sr*(sqrt(-2.0*log(tl)/tl));
      }
    }
    *(z)=iy_r;
    *(z+1)=iy_i;
  }

  if (flag==1||flag==6) {
    for (i=0;i<my*ny;i++) {
      *(y_r+i)=*(rpar+i)+(*(rpar+i+2*my*ny))*(*(z+i+2));
      *(y_i+i)=*(rpar+i+my*ny)+(*(rpar+i+3*my*ny))*(*(z+i+2+my*ny));
    }
  }
}

