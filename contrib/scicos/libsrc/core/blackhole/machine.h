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
 
 
/* routines/machine.h.  Generated from machine.h.in by configure.  */
/* Copyright INRIA/ENPC */
#ifndef MACHINE_H 
#define MACHINE_H 

/* Define for using dld for sunos */
/* #undef SUNOSDLD */

/* Define if leading underscores */
/* #undef WLU */

/* Define if trailing underscores */
#define WTU 1

/* Define if use sharpsigns */
#define USE_SHARP_SIGN 1

/* Define if have exp10 */
#define HAVE_EXP10 1

/* Define if have getwd */
#define HAVE_GETWD 1

/* Define if have sleep: used in graphics/periX11.c */
#define HAVE_SLEEP 1

/* Define if have strerror: used in fileio/misc.c */
#define HAVE_STRERROR 1

/* Define if have termcap library: used in os_specific/zzledt.c */
#define HAVE_TERMCAP 1

/* Define if have usleep: used in graphics/periX11.c */
#define HAVE_USLEEP 1

/* Define if have limits.h header:  used in routines/default/scimem.c */
#define HAVE_LIMITS_H 1

/* Define if have values.h header:  used in routines/default/scimem.c */
#define HAVE_VALUES_H 1

/* Define if have finite */
#define HAVE_FINITE 1

/* Define if have and use TCL/TK */
#define WITH_TK 1

/* Define if have and use PVM */
#define WITH_PVM 1

/* Define if have and use ocaml */
#define WITH_OCAML 1

/* Define if have and use GTK */
/* #undef WITH_GTK */

/* Define if have and use READLINE */
/* #undef WITH_READLINE */

/* Define if we use f95 GNUFORTRAN */
/* #undef G95_FORTRAN */

/* CNAME(x,y) ==> xy **/

#if defined(USE_SHARP_SIGN)
#define CNAME(name1,name2) name1##name2
#else 
#define CNAME(name1,name2) name1/**/name2
#endif

/* Define  C2F and F2C entry point conversion */
#if defined(WTU)
#if defined(USE_SHARP_SIGN)
#define C2F(name) name##_
#define F2C(name) name##_
#else 
#define C2F(name) name/**/_
#define F2C(name) name/**/_
#endif
#else
#define C2F(name) name
#define F2C(name) name
#endif

/* Define some functions */

#if !defined(HAVE_EXP10)
#define exp10(x) pow((double) 10.0,x)
#endif

#if !defined(HAVE_GETWD)
#define getwd(x) getcwd(x,1024) /* you must define char x[1024] */
#endif

/* 
   Define integer C type which must fit Fortran integer
   For Scilab to work, the rule is: 
          size of Fortran double precision = 2 * size of Fortran integer

   At the present time, we suppose:
       size of Fortran integer = 4 bytes
       size of Fortran double precision = 8 bytes
       size of C int = 4 bytes
*/

typedef int integer;


/*  params.h */
#ifdef __STDC__
#ifndef  __PARAMS
#define  __PARAMS(paramlist)		paramlist
#endif
#ifndef  _PARAMS
#define  _PARAMS(paramlist)		paramlist
#endif
#else	
#ifndef  __PARAMS
#define  __PARAMS(paramlist)		()
#endif
#ifndef  _PARAMS
#define  _PARAMS(paramlist)		()
#endif
#endif

/** Intel Blas library on win32 */

#ifdef MKL 
#include "MKL.h" 
#endif 

#endif /* MACHINE_H  */
