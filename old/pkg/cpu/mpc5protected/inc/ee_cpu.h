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
 * Author: Antonio Fiaschi
 * CVS: $Id: ee_cpu.h,v 1.15 2006/04/08 21:08:54 pj Exp $
 */


#include "eecfg.h"
#include "cpu/mpc5protected/inc/ee_compiler.h"
#include "cpu/mpc5xx/inc/ee_macro.h"

#ifndef __INCLUDE_MPC5PROTECTED_CPU_H__
#define __INCLUDE_MPC5PROTECTED_CPU_H__



/*************************************************************************
 HAL Constants
 *************************************************************************/


/* invalid pointer */
#ifndef NULL
#define NULL 0
#endif

/*************************************************************************
 HAL Types
 *************************************************************************/


/* Primitive data types */

typedef unsigned char EE_BIT;
typedef unsigned char EE_UINT8;
typedef unsigned short EE_UINT16;
typedef unsigned long EE_UINT32;
typedef signed char EE_INT8;
typedef signed short EE_INT16;
typedef signed long EE_INT32;

typedef EE_UINT32 EE_UREG;
typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_FREG;

/* USIU Types */
typedef volatile signed char EE_VINT8;
typedef volatile unsigned char EE_VUINT8;

typedef volatile signed short EE_VINT16;
typedef volatile unsigned short EE_VUINT16;

typedef volatile signed long EE_VINT32;
typedef volatile unsigned long EE_VUINT32;

/* Thread IDs */
typedef EE_UINT32 EE_TID;

/* Application IDs */
typedef EE_UINT32 EE_AID;

/* Addresses (that have the same size of a pointer) */
typedef EE_UINT32 *EE_ADDR;

/* IRQs */
typedef EE_UINT32 EE_TYPEIRQ;

/* Primitve IDs */
typedef EE_UREG EE_PID;

/* This structure is used to keep information about thread context, as 
   application id, the stack_id within the application and where is his body */

struct EE_THREAD_TOC {
	EE_AID application_id;
	EE_ADDR body;
	EE_UREG stack_id;
	EE_UREG appl_segment;
	EE_BIT appl_protection;
};

struct EE_HANDLER_TOC {
	EE_ADDR handler_body;
	EE_BIT handler_type;
};

/* This structure is used to have information about the application
  segment in memory */

struct EE_TOS {
	EE_ADDR SYS_tos;
	EE_UREG segment;
};

/*************************************************************************
 Application dependent data types
 *************************************************************************/

#ifdef __HAS_TYPES_H__
#include "types.h"
#endif


/*************************************************************************
 HAL Variables
 *************************************************************************/

/* IRQ table pointer */
//extern const EE_ADDR EE_mpc5_irq_table[];
extern const struct EE_HANDLER_TOC EE_hal_IRQ_handler[];
/* Vector Mask for each IRQ level */
extern const EE_UINT32 EE_mpc5_irq_mask[];

/* here we have all information about thread */
extern const struct EE_THREAD_TOC EE_mpc5_thread_toc[];

/* here we have all information about stacks */
/* this is the top of stack, one for each thread stack */
extern struct EE_TOS EE_mpc5_system_tos[];
/* this is the top of stack, one for each handler */
/* NOTE: handler can't shared stack with other handlers */
extern struct EE_TOS EE_mpc5_handler_tos[];
/* top of IRQ stack */
extern EE_ADDR EE_mpc5_IRQ_tos;
/* address of kernel stack */
extern const EE_ADDR EE_mpc5_system_stack;

/* this is the thread_id of active thread */
extern EE_TID EE_mpc5_active_thread;
extern EE_AID EE_mpc5_active_application;
extern EE_UREG EE_mpc5_active_tos;

extern EE_ADDR EE_mpc5_thread_epilogue[];

/*********************************************************************
 MPC5XX interrupt disabling/enabling
 *********************************************************************/

/*
 * Enable interrupts
 */

// The following code is for GCC
__INLINE__ void __ALWAYS_INLINE__ EE_mpc5_enableIRQ(void)
{
	register int temp=0;
	asm("mtspr\t80, %0" :: "r" (temp));
}


/*
 * Disable interrupts
 */
// The following code is for GCC
__INLINE__ void __ALWAYS_INLINE__ EE_mpc5_disableIRQ(void)
{
	register int temp=0;
	asm("mtspr\t81, %0" :: "r" (temp));
}


/*************************************************************************
 Functions
 *************************************************************************/

/* 
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_mpc5_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_mpc5_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

/**************************************************************
 * Stubs for protected calls
 **************************************************************/

// Stub for primitve call without params and return value
void EE_hal_protected_stub(EE_UREG primitve); /* in ASM */

// Stub for primitive call with return value and no params
EE_UREG EE_hal_protected_stub_r(EE_UREG primitive); /* in ASM */

// Stub for primitive call with one param and no return value
void EE_hal_protected_stub_1p(EE_UREG par1, EE_UREG primitive); /* in ASM */

// Stub for primitve call with two params and no return value
void EE_hal_protected_stub_2p(EE_UREG par1, EE_UREG par2, EE_UREG primitve); /*in AMS */

EE_UREG EE_hal_protected_stub_r_1p(EE_UREG par1, EE_UREG primitive);

// new features
EE_UREG EE_hal_protected_stub_r_2p(EE_UREG par1, EE_UREG par2, EE_UREG primitve);

EE_UREG EE_hal_protected_stub_r_3p(EE_UREG par1, EE_UREG par2, EE_UREG par3, EE_UREG primitive);

#endif /* __INCLUDE_MPC5PROTECTED_CPU_H__ */
