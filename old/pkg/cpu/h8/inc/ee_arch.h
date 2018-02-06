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
 * Author: 2002 Davide Cantini
 * CVS: $Id: ee_arch.h,v 1.6 2006/04/08 21:07:06 pj Exp $
 */


#ifndef __INCLUDE_H8_ARCH_H__
#define __INCLUDE_H8_ARCH_H__


#include "eecfg.h"

/*
 * Compiler dependent interface
 */

/* inline definitions */

#ifdef __NO_INLINE__
#define __INLINE__ static
#else
#define __INLINE__ static inline
#endif

#define __ALWAYS_INLINE__ 

/***************************
 * 	HAL Constants
 ***************************/
 
/* invalid pointer */
#define NULL 0


/***************************
 * 	HAL Types
 ***************************/

/* Primitive data types */
typedef unsigned char   EE_BIT;
typedef unsigned char   EE_UINT8;
typedef unsigned short 	EE_UINT16;
typedef signed char     EE_INT8;
typedef signed short    EE_INT16;

typedef EE_UINT16    EE_UREG;
typedef EE_INT16     EE_SREG;
typedef EE_UINT16    EE_FREG;

/* Thread IDs */
typedef EE_INT16 EE_TID;

/* Addresses (that have the same size of a pointer) */
typedef EE_UINT16 	* EE_ADDR;

/* IRQs */
typedef EE_UINT16 	EE_TYPEIRQ;

#ifdef __TIME_SUPPORT__
    /* Timer size */
    typedef EE_UINT16 EE_TIME;
#endif

/***************************
 * 	LIBC Types
 ***************************/

#ifdef __LIBC__
typedef unsigned int size_t;
#endif


/***********************************************
 * 	Application dependent data types
 ***********************************************/

#ifdef __HAS_TYPES_H__
#include "types.h"
#endif

/***************************
 * 	HAL Variables
 ***************************/

/* Thread function body pointer */
extern const EE_ADDR EE_hal_thread_body[];

#ifdef __MULTI__

    /* Stack pointer of each stack */
    extern EE_ADDR EE_h8_sp[];

    /* Index of the stack used by the task (ROM)*/
    extern const EE_UINT8 EE_h8_thread_stack_id[];

    /* Index of the stack used by running task */
    extern EE_UINT8 EE_h8_active_stack_id;
    
#endif /* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern EE_UINT16 EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern void EE_oo_thread_stub(void);

#endif


/**************************** 
 * 	HAL Functions
 ****************************/

/*
 * Context handling
 */
/* typically called at the end of a thread instance */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID t);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID t);

/* typically called into a generic primitive to implement preemption */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID t);

/* typically called at the end of an interrupt */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID t);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID t);

#ifdef __MULTI__
/* called to change the active stack, typically used with locking semaphores */
    __INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID t);    
#endif /* __MULTI__ */


/*
 * Generic Primitives
 */

/* called as _first_ function of a primitive that can be called into
   an IRQ and into a task */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void);

/* called as _last_ function of a primitive that can be called into
   an IRQ and into a task */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f);

/*
 * Interrupt handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void);

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL


#ifdef __TIME_SUPPORT__
/* read current time (used by EDF scheduler) */
    __INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void);          
#endif

/*
 * Nested Interrupts Handling 
 */

/* can be called with interrupt enabled */
//#ifdef __ALLOW_NESTED_IRQ__
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void);
//#endif

/* 
 * OO related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t);
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t);

#endif

#endif 
