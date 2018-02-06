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
 * Author: 2001-2002 Paolo Gai
 * CVS: $Id: kernopt.h,v 1.6 2007/06/01 09:00:21 pj Exp $
 */

#ifndef __INCLUDE_ARM7ADS_KERNOPT_H__
#define __INCLUDE_ARM7ADS_KERNOPT_H__


#ifdef __FP__
#include "fp/ee_kernel.h"
#endif

#ifdef __EDF__
#include "edf/ee_kernel.h"
#endif



/*************************************************************************
 ARM7ADS Optimization defines
 *************************************************************************/

/* #define __PRIVATE_SYS_SCHEDULER__ */
/* #define __PRIVATE_THREAD_ACTIVATE__ */
/* #define __PRIVATE_THREAD_END_INSTANCE__ */
/* #define __PRIVATE_MUTEX_LOCK__ */
/* #define __PRIVATE_MUTEX_UNLOCK__ */
/* #define __PRIVATE_IRQ_END_INSTANCE__ */
/* #define __PRIVATE_SYS_GETTIME__ */


/*************************************************************************
 ARM7ADS Declarations
 *************************************************************************/

#ifdef __FP__

#define EE_sys_scheduler()		EE_fp_sys_scheduler()
#define EE_thread_activate(t)	EE_fp_thread_activate(t)
#define EE_mutex_lock(s) 		EE_fp_mutex_lock(s)
#define EE_mutex_unlock(s) 	        EE_fp_mutex_unlock(s)

#ifdef __TIME_SUPPORT__
#define EE_sys_gettime()		EE_fp_sys_gettime(t)
#endif

#endif /* __FP__ */



#ifdef __EDF__

#define EE_sys_scheduler()		EE_edf_sys_scheduler()
#define EE_thread_activate(t)	EE_edf_thread_activate(t)
#define EE_mutex_lock(s) 		EE_edf_mutex_lock(s)
#define EE_mutex_unlock(s)		EE_edf_mutex_unlock(s)

#ifdef __TIME_SUPPORT__
#define EE_sys_gettime(t)		EE_edf_sys_gettime(t)
#endif

#endif /* __EDF__ */



/*************************************************************************
 Kernel-layer ARM7ADS optimized functions
 *************************************************************************/



#endif /* __INCLUDE_ARM7ADS_KERNOPT_H__ */
