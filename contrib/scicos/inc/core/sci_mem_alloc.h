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
	@file sci_mem_alloc.h
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
/* Allan CORNET INRIA 2005 */

#ifndef __SCI_MEM_ALLOC__
#define __SCI_MEM_ALLOC__

#if _MSC_VER
	#include <stdlib.h>
#endif

#ifdef MALLOC
#undef MALLOC
#endif

#ifdef FREE
#undef FREE
#endif

#ifdef CALLOC
#undef CALLOC
#endif

#ifdef REALLOC
#undef REALLOC
#endif

#if _MSC_VER
	#ifdef EXPORT_MALLOC_DLL
		#define IMPORT_EXPORT_MALLOC_DLL __declspec(dllexport)
	#else
		#define IMPORT_EXPORT_MALLOC_DLL __declspec(dllimport)
	#endif
#else
	#define IMPORT_EXPORT_MALLOC_DLL extern 
#endif

IMPORT_EXPORT_MALLOC_DLL void * MyReAlloc(void * lpAddress,int dwSize,char *fichier,int ligne);
IMPORT_EXPORT_MALLOC_DLL void * MyAlloc(unsigned int dwSize,char *fichier,int ligne);
IMPORT_EXPORT_MALLOC_DLL void * MyCalloc(unsigned  int x, unsigned int y, char *fichier,int ligne);
IMPORT_EXPORT_MALLOC_DLL void  MyFree(void *x, char *fichier,int ligne);

#ifndef _MSC_VER
 
 #ifdef lint5
   #include <sys/stdtypes.h>
   #define MALLOC(x) MyAlloc((size_t)x,__FILE__,__LINE__)
   #define FREE(x) if (x  != NULL) MyFree((void *) x,__FILE__,__LINE__);
   #define REALLOC(x,y) MyReAlloc((void *)x, y,__FILE__,__LINE__)
   #define CALLOC(x,y) MyCalloc((size_t) x, (size_t) y,__FILE__,__LINE__)

   /* Only for Scilab Stacksize use VirtualAlloc on Window */
   #define SCISTACKMALLOC(x) MyAlloc((size_t)x,__FILE__,__LINE__)
   #define SCISTACKFREE(x) if (x  != NULL) MyFree((void *) x,__FILE__,__LINE__);

 #else
   #define MALLOC(x) MyAlloc((unsigned)x,__FILE__,__LINE__)
   #define FREE(x) if (x  != NULL) MyFree((char *) x,__FILE__,__LINE__);
   #define REALLOC(x,y) MyReAlloc((char *)x, y,__FILE__,__LINE__)
   #define CALLOC(x,y) MyCalloc((unsigned) x, (unsigned) y,__FILE__,__LINE__)

    /* Only for Scilab Stacksize use VirtualAlloc on Window */
   #define SCISTACKMALLOC(x) MyAlloc((unsigned)x,__FILE__,__LINE__)
   #define SCISTACKFREE(x) if (x  != NULL) MyFree((char *) x,__FILE__,__LINE__);


 #endif
#else
	#define MALLOC(x) MyAlloc((unsigned)x,__FILE__,__LINE__)
	#define FREE(x) if (x  != NULL) MyFree((char *) x,__FILE__,__LINE__);
	#define REALLOC(x,y) MyReAlloc((char *)x, y,__FILE__,__LINE__)
	#define CALLOC(x,y) MyCalloc((unsigned) x, (unsigned) y,__FILE__,__LINE__)

#endif	

#endif /* __SCI_MEM_ALLOC__ */
