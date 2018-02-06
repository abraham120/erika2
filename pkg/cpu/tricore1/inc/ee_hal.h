/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, TU Dortmund University, Faculty of Computer Science 12
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

/* Author: Jan C. Kleinsorge, TU Dortmund University, 2010-
 *
 */
#ifndef __INCLUDE_TRICORE_EE_HAL_H__
#define __INCLUDE_TRICORE_EE_HAL_H__

#include "cpu/tricore1/inc/ee_compiler.h"

/*************************************************************************
 HAL Constants
*************************************************************************/

#ifndef NULL
#define NULL ((void*)0)
#endif


/*************************************************************************
 HAL Types
*************************************************************************/

/* Primitive data types (from ee_compiler.h) */
typedef uint8  EE_BIT;

typedef int8   EE_INT8; 
typedef int16  EE_INT16;
typedef int32  EE_INT32;  
typedef uint8  EE_UINT8; 
typedef uint16 EE_UINT16;
typedef uint32 EE_UINT32;  

typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_UREG;
typedef EE_UINT32 EE_FREG;

/* boolean type */
#ifndef EE_TYPEBOOL
typedef EE_UREG EE_TYPEBOOL;
#endif

/* boolean true define */
#ifndef EE_TRUE
#define EE_TRUE ((EE_TYPEBOOL)1U)
#endif

/* boolean false define */
#ifndef EE_FALSE
#define EE_FALSE ((EE_TYPEBOOL)0U)
#endif

/* Thread IDs */
typedef EE_INT32 EE_TID;
typedef EE_UINT32 EE_UTID;

/* Callbacks with no parameters nor return value */
typedef void (*EE_VOID_CALLBACK)(void);

/* Function addresses (that have the same size of a pointer) */
typedef void *EE_FADDR;

/* Addresses (that have the same size of a pointer) */
typedef void *EE_ADDR;

/* A thread function pointer */
typedef void (*EE_THREAD_PTR)(void);

/* Stacks must be properly aligned on Tricore */
typedef EE_INT32 EE_STACK __ALIGNED__(8);

/*
 * This structure is used by the Multistack HAL to contain the
 * information about a "stack", that is composed by a user stack
 * (SYS-mode) and a system stack (IRQ-mode). This type is used
 * internally by the HAL and is not used by the kernel.
 *
 * Note: Keep order and offsets as this is also accessed from
 *       assembly.
 */
#ifdef __MULTI__
struct EE_TOS {
    EE_ADDR SYS_tos_addr;
};

struct EE_CTX {
    EE_UREG SYS_pcx; /* Previous context pointer */
    EE_ADDR SYS_ra;  /* Resume point return address */
    EE_UREG SYS_tos; /* Top-of-Stack index */
};
#endif


/*************************************************************************
 HAL Variables
*************************************************************************/

/* Thread function body pointer */
extern const EE_THREAD_PTR EE_hal_thread_body[];

/* From ee_hal.c */
extern EE_UREG EE_IRQ_nesting_level;
extern EE_THREAD_PTR EE_hal_endcycle_next_thread;

#ifdef __MULTI__

/* From ee_hal.c */
extern EE_TID EE_hal_endcycle_next_tid;
extern EE_UREG EE_hal_endcycle_next_tos;
extern EE_TID EE_tc1_active_tid;
extern int EE_tc1_need_reschedule;

/* Each task might use a system (IRQ) stack and a user (SYS) stack */
extern struct EE_TOS EE_tc1_system_tos[];

/* tc1_system_tos[] index that point to the thread head CSA (one for each thread) */
extern struct EE_CTX EE_tc1_system_ctx[];

/* Stack used by IRQ handlers */
#if defined(__ALLOW_NESTED_IRQ__) && defined(__IRQ_STACK_NEEDED__)
extern struct EE_TOS EE_tc1_IRQ_tos;
#endif 

#endif /* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) \
    || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* This is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern EE_UINT32 EE_terminate_data[];

/* This is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_THREAD_PTR EE_terminate_real_th_body[];

/* This is the stub that have to be put into the EE_th_body array */
extern void EE_oo_thread_stub(void);

#endif

/*************************************************************************
 HAL Functions 
*************************************************************************/

void EE_IRQ_end_instance(void);
#ifdef __MONO__
void EE_tc1_hal_thread_start(EE_ADDR thread);
/* EE_tc1_hal_ready2stacked for monostack is inlined (ee_context.h) */
#endif
#ifdef __MULTI__
void EE_tc1_hal_ready2stacked(EE_TID tid, EE_ADDR thread);
void EE_tc1_hal_stkchange(EE_TID tid);
#endif

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) \
    || defined(__OO_ECC1__) || defined(__OO_ECC2__)
void EE_tc1_hal_terminate_savestk(EE_ADDR sp, EE_THREAD_PTR realbody);
void EE_tc1_hal_terminate_task(EE_ADDR sp);
#endif

/*************************************************************************
 Kernel Dependencies
*************************************************************************/

void EE_IRQ_end_instance(void);
void EE_thread_end_instance(void);


#endif

