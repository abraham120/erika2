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
	@file rt_randm.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
#include <stdlib.h> /* for rand()*/

#include "machine.h"
#include "scicos_block4.h"

static void init(scicos_block *block)
{
  double * y = block->outptr[0]   ;
  double   seed = block->rpar[1]  ; // Seed

  srand ( (int)seed ); // randomize the generator   

  y[0]=0.0;
}

static void inout(scicos_block *block)
{
  double * y = block->outptr[0]; //Output 
  double   A = block->rpar[0]  ; //Amplitute 

  //** one random integer [0 RAND_MAX]
  y[0] = A * ( (double)rand() / (double)RAND_MAX  ) ; 
}

static void end(scicos_block *block)
{
  double * y = block->outptr[0];
  y[0]=0.0;
}




//** This block produce a pseudo random output 

void rt_randm(scicos_block *block,int flag)
{
  if (flag==OutputUpdate){          /* set output */
    inout(block);
  }
  else if (flag==Ending){      /* termination */ 
    end(block);
  }
  else if (flag ==Initialization){    /* initialisation */
    init(block);
  }
}


