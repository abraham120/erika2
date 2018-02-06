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
 
 
#include <stdio.h>
#include "machine.h"

#ifndef WIN32
#include <sys/time.h>
#include <unistd.h>

#ifndef __GNUC__
#define inline
#endif


static inline unsigned long long TIME2ULL(t)
     struct timeval t;
{
  unsigned long long result;
  result = (unsigned long long)t.tv_sec * 1000000 + t.tv_usec;
  return result;
}

static inline struct timeval ULL2TIME(t)
     unsigned long long t;
{
  struct timeval result;
  result.tv_sec = t / 1000000;
  result.tv_usec = t % 1000000;
  return result;
}

static double simulation_start = 0;
static double simulation_scale = 0;
static unsigned long long realtime_start = 0;
static int simulation_doinit = 1;


int C2F(realtimeinit)(t,scale)
     double *t; 
     double *scale; 
{
  struct timeval now;
  
  gettimeofday(&now, 0); 
  /*  printf("Realtime init %f %f\n", *t, *scale);*/
  realtime_start = TIME2ULL(now);
  simulation_doinit = 1;
  simulation_scale = *scale;
  return 0;
}

int C2F(realtime)(t) 
     double *t;
{
  struct timeval now;
  unsigned long long realtime_diff;
  double simulation_diff;
  long long delay;

  if (simulation_doinit) {
    simulation_doinit = 0;
    simulation_start = *t;
  }
  gettimeofday(&now, 0); 
  realtime_diff = TIME2ULL(now) - realtime_start;
  simulation_diff = (*t - simulation_start) * simulation_scale;
  delay = (long long)(simulation_diff * 1000000) - realtime_diff;
/*  printf("Realtime diff %Ld %f -> %Ld (t=%f)\n", 
    realtime_diff, simulation_diff, delay, *t);
*/

  if (delay > 0) {
    struct timeval d ;
    d = ULL2TIME(delay);
    select(0, 0, 0, 0, &d);
  }
  return 0;
}

#else
#include <windows.h>

static double simulation_start = 0;
static double simulation_scale = 0;
static __int64 realtime_start = 0;
static int simulation_doinit = 1;
  union {FILETIME ftFileTime;
    __int64  ftInt64;
  } ftRealTime; 

int C2F(realtimeinit)(double *t, double *scale) {
  SYSTEMTIME st;
  GetSystemTime(&st);
  SystemTimeToFileTime(&st,&ftRealTime.ftFileTime); 

  realtime_start = ftRealTime.ftInt64;
  simulation_doinit = 1;
  simulation_scale = *scale;
  return 0;
}

int C2F(realtime)(double *t) {
  __int64 realtime_diff;
  double simulation_diff;
  __int64 delay;
  SYSTEMTIME st;

  if (simulation_doinit) {
    simulation_doinit = 0;
    simulation_start = *t;
  }
  GetSystemTime(&st);
  SystemTimeToFileTime(&st,&ftRealTime.ftFileTime);

  realtime_diff = ftRealTime.ftInt64  - realtime_start;
  simulation_diff = (*t - simulation_start) * simulation_scale;
  delay = (__int64)(simulation_diff * 10000000) - realtime_diff;
/*  printf("Realtime diff %Ld %f -> %Ld (t=%f)\n", 
    realtime_diff, simulation_diff, delay, *t);
*/

  if (delay > 0) {
    Sleep((DWORD)(delay/10000));
  }
  return 0;
}
#endif
