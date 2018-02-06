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
	@file scicos_block.h
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
#ifndef __SCICOS_BLOCK_H__
#define __SCICOS_BLOCK_H__

#ifdef __STDC__
#include <stdlib.h>
#else 
	#ifndef WIN32
		#include <malloc.h>
	#endif
#endif 

typedef void (*voidg)();

typedef struct {
  int nevprt;
  voidg funpt ;
  int type;
  int scsptr;
  int nz;
  double *z;
  int noz;
  int *ozsz;
  int *oztyp;
  void **ozptr;
  int nx;
  double *x;
  double *xd;
  double *res;
  int nin;
  int *insz;
  double **inptr;
  int nout;
  int *outsz;
  double **outptr;
  int nevout;
  double *evout;
  int nrpar;
  double *rpar;
  int nipar;
  int *ipar;
  int nopar;
  int *oparsz;
  int *opartyp;
  void **oparptr;
  int ng;
  double *g;
  int ztyp;
  int *jroot;
  char *label;
  void **work;
  int nmode;
  int *mode;
} scicos_block;


void do_cold_restart();
int get_phase_simulation();
double get_scicos_time();
int get_block_number();
void set_block_error(int);
void set_pointer_xproperty(int* pointer);
void * scicos_malloc(size_t );
void scicos_free(void *p);
double Get_Jacobian_parameter(void);
double Get_Scicos_SQUR(void);
void Set_Jacobian_flag(int flag);

#if WIN32
#undef min
#undef max
#endif

#ifndef WIN32
#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#endif
#endif

extern int s_copy();
extern int s_cmp();


#endif /* __SCICOS_BLOCK_H__ */
