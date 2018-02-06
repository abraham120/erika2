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
 * Auhtor: Antonio Fiaschi
 * CVS: $Id: ee_cpu.h,v 1.10 2006/04/08 21:07:53 pj Exp $
 */


#include "eecfg.h"
#include "cpu/mpc5xx/inc/ee_compiler.h"

#ifndef __INCLUDE_MPC5XX_ARCH_H__
#define __INCLUDE_MPC5XX_ARCH_H__



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
typedef unsigned int EE_UINT32;
typedef signed char EE_INT8;
typedef signed short EE_INT16;
typedef signed int EE_INT32;

typedef EE_UINT32 EE_UREG;
typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_FREG;

/* USIU Types */
typedef volatile signed char EE_VINT8;
typedef volatile unsigned char EE_VUINT8;

typedef volatile signed short EE_VINT16;
typedef volatile unsigned short EE_VUINT16;

typedef volatile signed int EE_VINT32;
typedef volatile unsigned int EE_VUINT32;

/* Thread IDs */
typedef EE_UINT32 EE_TID;

/* Addresses (that have the same size of a pointer) */
typedef EE_UINT32 *EE_ADDR;

/* IRQs */
typedef EE_UINT32 EE_TYPEIRQ;

/*
 * This structure is used by the Multistack HAL to contain the
 * information about a "stack", that is composed by a user stack
 * (SYS-mode). This type is used internally by the HAL and is 
 * not used by the Kernels.
 */
#ifdef __MULTI__
struct EE_TOS {
    EE_ADDR SYS_tos;
};
#endif

/*************************************************************************
 Application dependent data types
 *************************************************************************/

#ifdef __HAS_TYPES_H__
#include "types.h"
#endif


/*************************************************************************
 HAL Variables
 *************************************************************************/

/* Thread function body pointer */
extern const EE_ADDR EE_hal_thread_body[];

/* IRQ table pointer */
extern const EE_ADDR EE_mpc5_irq_table[];

#ifdef __ALLOW_NESTED_IRQ__
#ifndef __ENHANCED_IRQ__
extern const EE_UINT32 EE_mpc5_irq_mask[];
#endif
#endif



#ifdef __MULTI__

/* stack used only by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern struct EE_TOS EE_mpc5_IRQ_tos;
#endif

/* each task use a user (SYS) stack */
extern struct EE_TOS EE_mpc5_system_tos[];

/* mpc5_system_tos[] index that point to the thread tos (one for each thread) */
extern EE_UREG EE_mpc5_thread_tos[];

/* mpc5_system_tos[] index that point to the active thread tos */
extern EE_UREG EE_mpc5_active_tos;

#endif /* __MULTI__ */



#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern EE_UINT32 EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern void EE_oo_thread_stub(void);

#endif

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

#endif /* __INCLUDE_MPC5XX_ARCH_H__ */
