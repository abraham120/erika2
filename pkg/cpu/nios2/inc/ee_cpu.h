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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_cpu.h,v 1.17 2006/04/08 21:08:54 pj Exp $
 */

#include "eecfg.h"
#include "cpu/nios2/inc/ee_compiler.h"



#ifndef __INCLUDE_NIOS2_CPU_H__
#define __INCLUDE_NIOS2_CPU_H__

/*************************************************************************
 From Altera
 *************************************************************************/

/* Note that we DO NOT include system.h. That is, the objects that we generate
 * are NOT dependent on the particular configuration of the Hardware.
 */
 
#include "sys/alt_irq.h"
#include "alt_types.h"
#include "nios2.h"

/*************************************************************************
 HAL Constants
 *************************************************************************/


/* invalid pointer */
#ifndef NULL
#define NULL 0
#endif




#ifdef __NIOS2_MULTICPU__

/* Disabling GP-relative addressing 
 * 
 * This macro has to be used everytime you DECLARE a variable that is meant 
 * to be:
 * - shared among different processors
 * - allocated in a particular memory region
 * 
 * The definition of the variable have then to contain the specification of the
 * real section where it have to go to (e.g., another gcc attribute that 
 * specifies the real section where the data have to go. 
 * 
 * Note: specifying a section attribute when
 * - DECLARING a variable -> disables GP-addressing
 * - DEFINING a variable -> really allocates the variable on a given section
 * 
 * This macro is only used for DECLARING a variable! when defining a variable 
 * please use the normal section attributes...
 */
#define EE_DISABLE_GP_ADDRESSING __attribute__ ((section (".data")))

/* Sharing of data structures and code */
#define EE_SHARED_DATA(x) EE_SHARED_DATA_##x
#define EE_SHARED_CODE(x) EE_SHARED_CODE_##x
#define EE_SHARED_RES(name,var) EE_SHARED_RES_##name(var)

#ifndef EE_GLOBAL_MUTEX
/* the MSB of MUTEX type indicates if a resource is global (1) or
   local (0) to a processor */
#define EE_GLOBAL_MUTEX 0x80000000 
#endif

/* Then, the configuration in eecfg.h should generate the variable
   EE_CURRENTCPU equal to the current CPUID register */

#endif


/*************************************************************************
 HAL Types
 *************************************************************************/

/* Primitive data types */

typedef alt_8   EE_BIT;
typedef alt_u8  EE_UINT8;
typedef alt_u16 EE_UINT16;
typedef alt_u32 EE_UINT32;
typedef alt_8   EE_INT8;
typedef alt_16  EE_INT16;
typedef alt_32  EE_INT32;

typedef EE_UINT32 EE_UREG;
typedef EE_INT32  EE_SREG;

// was alt_irq_context from altera_nios2/HAL/inc/sys/alt_irq.h
typedef int EE_FREG;

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

/* Callbacks with no parameters nor return value */
typedef void (*EE_VOID_CALLBACK)(void);

/* Code addresses (same size of function pointers) */
/* For an easy upgrade path, we use a define instead of the typedef:
   typedef void (*EE_FADDR)(void); */
#define EE_FADDR EE_ADDR

/* Thread body pointer (same size of function pointers) */
#define EE_THREAD_PTR EE_ADDR

/* IRQs */
typedef EE_UINT32 EE_TYPEIRQ;

#ifdef __NIOS2_MULTICPU__
/* SPIN Locks */
typedef EE_UINT32 EE_TYPESPIN;
#endif

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

extern struct EE_TOS EE_nios2_system_tos[];

extern EE_UREG EE_hal_thread_tos[];

/* hal_active_tos[] index that point to the active thread tos */
extern EE_UREG EE_hal_active_tos;

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern struct EE_TOS EE_nios2_IRQ_tos;
#endif

#endif /* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern EE_UREG EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern void EE_oo_thread_stub(void);

#endif


/*********************************************************************
 NIOSII interrupt disabling/enabling
 *********************************************************************/

/*
 * Enable/Disable interrupts
 */

/* Note: This way may not work in future NIOSII versions */ 

__INLINE__ void __ALWAYS_INLINE__ EE_nios2_enableIRQ(void)
{
  NIOS2_WRITE_STATUS (NIOS2_STATUS_PIE_MSK);
}

__INLINE__ void __ALWAYS_INLINE__ EE_nios2_disableIRQ(void)
{
  NIOS2_WRITE_STATUS (0);
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
    EE_nios2_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_nios2_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

/*
 * Lauterbach Trace32 Stack initialization
 *
 * This function fills up all the stack space from the current stack
 * pointer to the stack limit with a 0xa5 pattern.
 *
 * This function should be used in conjunction with Lauterbach
 * Trace32, and together with the ORTI stack support enabled.
 * 
 * WARNING: The function should be called inside alt_main or main, in
 * any case -before- any memory allocation with malloc and free!!!
 */


__INLINE__ void __ALWAYS_INLINE__ EE_trace32_stack_init(void)
{
  extern unsigned int *__alt_stack_limit;
  unsigned int *p;
  asm("mov %0, sp" : "=r"(p));
  while((unsigned int)p > (unsigned int)&__alt_stack_limit) {
    p--;
    *(unsigned int *)p = 0xa5a5a5a5;
  }
}


#endif
