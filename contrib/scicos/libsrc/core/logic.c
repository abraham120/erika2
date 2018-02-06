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

//* DerivativeState    0
//* OutputUpdate       1
//* StateUpdate        2
//* OutputEventTiming  3
//* Initialization     4
//* Ending             5
//* 
//* ReInitialization   6
//* ModeZeroCrossing   9

void logic(scicos_block *block,int flag)
{
    char *u,*y;
    char inp,num;
    int i,nin,nout,mo;
    char *opar;
    nin=GetNin(block);
    nout=GetNout(block);
    opar=Getint8OparPtrs(block,1);
    mo=GetOparSize(block,1,1);
    
	if (flag==1) {
	num=0;
	for (i=0;i<nin;i++)
	{
	    u=Getint8InPortPtrs(block,i+1);
	    inp=*u;
	    if (inp>0) inp=1;
	    else inp=0;
	    inp=inp<<i;
	    num=num+inp;
	}
	for (i=0;i<nout;i++)
	{
	    y=Getint8OutPortPtrs(block,i+1);
	    *y=*(opar+num+i*mo);
	}
    }
    if (flag==6) {
	u=Getint8InPortPtrs(block,1);
       	for (i=0;i<nout;i++)
	{
	    y=Getint8OutPortPtrs(block,i+1);
	    *y=*u;
	}
    }
}
