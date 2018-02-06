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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: arch.h,v 1.5 2006/04/08 21:05:47 pj Exp $
 */

#ifndef __INCLUDE_ARM7ADS_ARCH_H__
#define __INCLUDE_ARM7ADS_ARCH_H__


#include "eecfg.h"


/*
 * Compiler dependent interface
 */

/* inline definitions */
#define __INLINE__ __inline
#define __ALWAYS_INLINE__ 


/*************************************************************************
 HAL Constants
 *************************************************************************/


/* invalid pointer */
#define NULL 0

/*************************************************************************
 HAL Types
 *************************************************************************/


/* Primitive data types */
/* TODO: it is worth for THUMB?!? */

typedef unsigned char EE_BIT;
typedef unsigned char EE_UINT8;
typedef unsigned short EE_UINT16;
typedef unsigned int EE_UINT32;
typedef signed char EE_INT8;
typedef signed short EE_INT16;
typedef signed int EE_INT32;

typedef EE_INT32 EE_UREG;


/* Thread IDs */
/* TID is application dependent! */

/* Addresses (that have the same size of a pointer) */
typedef EE_UINT32 *EE_ADDR;

/* IRQs */
typedef EE_UINT32 EE_TYPEIRQ;


#ifdef __TIME_SUPPORT__
/* Timer size */
typedef EE_UINT32 EE_TIME;
#endif



/*
 * This structure is used by the Multistack HAL to contain the
 * information about a "stack", that is composed by a user stack
 * (SYS-mode) and a system stack (IRQ-mode). This type is
 * used internally by the HAL and is not used by the Kernels.
 */
#ifdef __MULTI__
struct EE_TOS {
    EE_ADDR SYS_tos;
    EE_ADDR IRQ_tos;
};
#endif



/*************************************************************************
 Application dependent data types
 *************************************************************************/

#include "types.h"



/*************************************************************************
 HAL Variables
 *************************************************************************/

/* Thread function body pointer */
extern const EE_ADDR EE_hal_thread_body[];


#ifdef __MULTI__

/* each task use a system (IRQ) stack and a user (SYS) stack */
extern struct EE_TOS EE_arm7_system_tos[];

/* arm7_system_tos[] index that point to the thread tos (one for each thread) */
extern EE_UREG EE_arm7_thread_tos[];

/* arm7_system_tos[] index that point to the active thread tos */
extern EE_UREG EE_arm7_active_tos;

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern struct EE_TOS EE_arm7_IRQ_tos;
#endif

#endif /* __MULTI__ */



/*************************************************************************
 Functions
 *************************************************************************/

/*
 * Generic Primitives
 */


/* 
 * Context Handling  
 */

/* WARNING: All these functions are non-reentrant */

/* typically called at the end of a thread instance */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread);

/* typically called into a generic primitive to implement preemption */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread);

/* typically called at the end of an interrupt */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID thread);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID thread);

/* called to change the active stack, typically used with locking semaphores */
#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread);
#endif


/* 
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void);



/*
 * Time Handling
 */

#ifdef __TIME_SUPPORT__
/* read current time (used by EDF scheduler) */
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void);
#endif

#endif /* __INCLUDE_ARM7ADS_ARCH_H__ */
