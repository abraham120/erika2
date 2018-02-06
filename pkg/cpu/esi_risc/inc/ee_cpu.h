/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, Pebble Bay Consulting Ltd.
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

/* Author: Steve Langstaff, Pebble Bay Consulting Ltd, 2010
 *
 */

#ifndef __INCLUDE_ESI_RISC_EE_CPU_H__
#define __INCLUDE_ESI_RISC_EE_CPU_H__

#ifndef __bits__
#error  "__bits__ not defined"
#endif

#include "eecfg.h"
#ifdef __GNUC__
#include "cpu/common/inc/ee_compiler_gcc.h"
#else
#error Unsupported compiler
#endif

#include <esirisc/interrupt.h>

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
typedef signed char EE_INT8;

#if __bits__ == 16

typedef int EE_INT16;
typedef unsigned int EE_UINT16;
typedef long int EE_INT32;
typedef unsigned long int EE_UINT32;

typedef EE_UINT16 EE_UREG;
typedef EE_INT16  EE_SREG;
typedef EE_UINT16 EE_FREG;

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

/* Data addresses (that have the same size of a pointer) */
typedef void *EE_ADDR;

/* Callbacks with no parameters nor return value */
typedef void (*EE_VOID_CALLBACK)(void);

/* Code addresses (same size of function pointers) */
typedef void *EE_FADDR;
typedef void (*EE_THREAD_PTR)(void);

/* Thread IDs */
typedef EE_INT16 EE_TID;
typedef EE_UINT16 EE_UTID;

/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x8000

#elif __bits__ == 32

typedef short int EE_INT16;
typedef unsigned short int EE_UINT16;
typedef int EE_INT32;
typedef unsigned int EE_UINT32;

typedef EE_UINT32 EE_UREG;
typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_FREG;

/* Data addresses (that have the same size of a pointer) */
typedef void *EE_ADDR;

/* Callbacks with no parameters nor return value */
typedef void (*EE_VOID_CALLBACK)(void);

/* Code addresses (same size of function pointers) */
typedef void *EE_FADDR;
typedef void (*EE_THREAD_PTR)(void);

/* Thread IDs */
typedef EE_INT32 EE_TID;
typedef EE_UINT32 EE_UTID;

/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x80000000

#else
#error "Unsupported architecture"
#endif

/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"


/*************************************************************************
 Interrupt handling
 *************************************************************************/

/* Used to check the value returned by EE_esi_risc_disableIRQ */
#define EE_esi_risc_are_IRQs_enabled(ie) ((ie) & 1)

/*
 * Enable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_esi_risc_enableIRQ(void)
{
	esi_interrupt_enable();
}


/*
 * Disable interrupts
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_esi_risc_disableIRQ(void)
{
	return esi_interrupt_disable();
}


/*************************************************************************
 Functions exported by the HAL to the kernel
 *************************************************************************/


/*
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_esi_risc_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_esi_risc_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

/* Cache invalidation */
#define EE_hal_invalidate_dcache EE_esi_risc_invalidate_dcache
#define EE_hal_invalidate_icache EE_esi_risc_invalidate_icache


#endif /* __INCLUDE_ESI_RISC_EE_CPU_H__ */
