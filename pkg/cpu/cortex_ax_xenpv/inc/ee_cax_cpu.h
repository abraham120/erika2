/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013 Bruno Morelli
 */

#ifndef EE_INCLUDE_CPU_CAX_H__
#define EE_INCLUDE_CPU_CAX_H__

#include "eecfg.h"
#include "cpu/common/inc/ee_compiler_gcc.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_defs.h"

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
#include "cpu/common/inc/ee_types.h"

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

/* EE_TYPEIRQ is defined inside the MCU */


/* ISR Priority representation type */
typedef EE_UREG EE_TYPEISR2PRIO;

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

#if 0
/* Thread function body pointer */
extern const EE_ADDR EE_hal_thread_body[];
#endif

#include "cpu/common/inc/ee_hal_structs.h"

/*
 * Multicore
 */

#include "cpu/cortex_ax_xenpv/inc/ee_cax_multicore.h"
/* Remote TID, to be used with Remote notifications */
#define EE_REMOTE_TID   0x80000000U

#ifdef __MULTI__

/* each task use a system (IRQ) stack and a user (SYS) stack */
extern struct EE_TOS EE_cortex_ax_xenpv_system_tos[];

/* arm7_system_tos[] index that point to the thread tos (one for each thread) */
extern EE_UREG EE_cortex_ax_thread_tos[];

/* arm7_system_tos[] index that point to the active thread tos */
extern EE_UREG EE_cortex_ax_active_tos;

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern struct EE_TOS EE_cortex_ax_xenpv_IRQ_tos;
#endif

#endif /* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern EE_UINT32 EE_terminate_data[];

#if 0
/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];
#endif

/* this is the stub that have to be put into the EE_th_body array */
extern void EE_oo_thread_stub(void);

#endif


/*********************************************************************
 cortex-ax interrupt disabling/enabling
 *********************************************************************/

#define get_cpsr()              \
({                              \
        unsigned int rval;      \
        asm volatile(   \
        "mrs        %0, cpsr\n" \
        : "=r" (rval)           \
        );                      \
        rval;                   \
})

#define set_cpsr(v)  asm volatile("msr  cpsr,%0\n" : : "r" (v))
#define _exceptionEnableMask(mask)                   \
         set_cpsr(get_cpsr() & ~ (mask & EXCEPTION_MASK))

#define _exceptionDisableMask(mask)                  \
         set_cpsr(get_cpsr() | (mask & EXCEPTION_MASK))

/*
 * Enable interrupts
 */

#ifdef __THUMB__

/* if we are in thumb_mode, we have to switch to ARM-mode to use MSR
 * and MRS instructions */
void EE_cortex_ax_enableIRQ(void);

#else

/*
 * GCC
 */
__INLINE__ void __ALWAYS_INLINE__ EE_cortex_ax_enableIRQ(void)
{
	_exceptionEnableMask(I_bit);
}

#endif /* __THUMB__ */

/*
 * Disable interrupts
 */


#ifdef __THUMB__

void EE_cortex_ax_disableIRQ(void);

#else

/*
 * GCC
 */
__INLINE__ void __ALWAYS_INLINE__ EE_cortex_ax_disableIRQ(void)
{
	_exceptionDisableMask(I_bit);
}

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
    EE_cortex_ax_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_cortex_ax_disableIRQ();
}


/* Suspend/Resume Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ( EE_FREG flags )
{
  set_cpsr(flags);
}

__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ( void )
{
  EE_FREG reg = get_cpsr();
  set_cpsr(reg | (I_bit & EXCEPTION_MASK));

  return reg;
}

#endif /* EE_INCLUDE_CPU_CAX_H__ */
