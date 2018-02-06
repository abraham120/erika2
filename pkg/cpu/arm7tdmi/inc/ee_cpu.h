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
 *         2001-2003 Paolo Gai
 * CVS: $Id: ee_cpu.h,v 1.9 2006/10/25 13:59:42 pj Exp $
 */


#include "eecfg.h"
#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"

#ifndef __INCLUDE_ARM7GNU_EE_CPU_H__
#define __INCLUDE_ARM7GNU_EE_CPU_H__



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

/* Addresses (that have the same size of a pointer) */
typedef void *EE_ADDR;

/* EE_TYPEIRQ is defined inside the MCU */

/* Note: EE_TIME is defined for ARM7 into the drivers.h file,
   because arm7 do not have a common specification of the timer
   values, because they basically depend on the particular
   microcontroller implementation. */


/*
 * This structure is used by the Multistack HAL to contain the
 * information about a "stack". This type is
 * used internally by the HAL and is not used by the Kernels.
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
 ARM7TDMI interrupt disabling/enabling
 *********************************************************************/

/*
 * Enable interrupts
 */

#ifdef __THUMB__

/* if we are in thumb_mode, we have to switch to ARM-mode to use MSR
 * and MRS instructions */
void EE_arm7_enableIRQ(void);

#else

/*
 * DCC
 */
#ifdef __DCC__
asm EE_arm7_enableIRQ(void)
{
! "r0"				/* scratch registers */
    /*
     * NOTE:
     * 1) only flag field of CPSR can be set with immediate value, so
     *    we have to use two asm instruction (GCC will insert an
     *    instruction to copy "0x1f" into the register "%0")
     * 2) preserving flag field is useless
     */
//    asm("MSR cpsr_c, %0" :: "r" (0x1f)); /* Mode_SYS */

// MORE GENERIC CODE:
	MRS	r0, cpsr
	BIC 	r0, r0, #I_bit
	MSR	cpsr, r0
}

/*
 * ARM ADS
 */
#elif defined(__arm)
__INLINE__ void __ALWAYS_INLINE__ EE_arm7_enableIRQ(void)
{
    register int temp;
    __asm{MRS temp, CPSR};
    __asm{BIC temp, temp, #0x80};
    __asm{MSR CPSR_cxsf, temp};
}


/*
 * GCC
 */
#else
__INLINE__ void __ALWAYS_INLINE__ EE_arm7_enableIRQ(void)
{
    register int temp;
    asm("MRS %0, cpsr" : "=r" (temp));
    asm("BIC %0, %1, #0x80" : "=r" (temp) : "r" (temp));
    asm("MSR cpsr, %0" :: "r" (temp));
}
#endif

#endif /* __THUMB__ */




/*
 * Disable interrupts
 */


#ifdef __THUMB__

void EE_arm7_disableIRQ(void);

#else

/*
 * DCC
 */
#ifdef __DCC__
asm EE_arm7_disableIRQ(void)
{
! "r0"				/* scratch registers */
    /* ditto */
//    asm("MSR cpsr_c, %0" :: "r" (0x9f)); /* Mode_SYS | I_bit */

// MORE GENERIC CODE:
	MRS	r0, cpsr
	ORR	r0, r0, #I_bit
	MSR	cpsr, r0
}


/*
 * ARM ADS
 */
#elif defined(__arm)
__INLINE__ void __ALWAYS_INLINE__ EE_arm7_disableIRQ(void)
{
    register int temp;
    __asm{MRS temp, CPSR};
    __asm{ORR temp, temp, #0x80};
    __asm{MSR CPSR_cxsf, temp};
}





/*
 * GCC
 */
#else
__INLINE__ void __ALWAYS_INLINE__ EE_arm7_disableIRQ(void)
{
    register int temp;
    asm("MRS %0, cpsr" : "=r" (temp));
    asm("ORR %0, %1, #0x80" : "=r" (temp) : "r" (temp));
    asm("MSR cpsr, %0" :: "r" (temp));
}
#endif

#endif /* __THUMB__ */




/*************************************************************************
 Functions
 *************************************************************************/

/* 
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_arm7_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_arm7_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

#endif /* __INCLUDE_ARM7GNU_ARCH_H__ */
