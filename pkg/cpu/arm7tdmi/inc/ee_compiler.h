/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/*
 * Author: Paolo Gai
 * CVS: $Id: ee_compiler.h,v 1.3 2006/10/25 13:59:42 pj Exp $
 */

/* This file MUST contain only #defines, because it is also included
   by the .S files */

/*
 * Compiler dependent interface
 */

/*
 * Diab C compiler
 */
#ifdef __DCC__

/* inline definitions */
#define __INLINE__ __inline__
#define NORETURN
#define __ALWAYS_INLINE__ 



/*
 * ARM ADS
 */
#elif defined(__arm)

#define __INLINE__ __inline

#define __ALWAYS_INLINE__ 

#ifdef __thumb
#define __THUMB__
#endif

// CODE32 is a keyword of ADS

// probably does not exist on ADS
#define NORETURN  



/*
 * GCC
 */
#else 


#ifdef __NO_INLINE__
#define __INLINE__ static
#else
#define __INLINE__ static inline
#endif

#define __ALWAYS_INLINE__ 

#ifdef __thumb__
#define __THUMB__
#endif

#define CODE32 .arm

#define NORETURN  __attribute__ ((noreturn))

#endif
