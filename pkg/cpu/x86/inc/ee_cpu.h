/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * CPU-dependent part of HAL
 * Derived from pkg/cpu/msp430/inc/ee_cpu.h
 * Author: 2014,  Martin Hoffmann, FAU Erlangen
 */


#ifndef __INCLUDE_X86_EE_CPU_H__
#define __INCLUDE_X86_EE_CPU_H__

#include "eecfg.h"
#ifdef __GNUC__
#include "cpu/common/inc/ee_compiler_gcc.h"
#else
#error Unsupported compiler
#endif


/*************************************************************************
 HAL Types and structures
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

/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x80000000U

typedef EE_UINT32 EE_STACK_T;
typedef EE_UINT8 EE_TYPEISR2PRIO;
typedef EE_UINT32 EE_UTID;

/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"


#ifdef __MULTI__
// Multistack variant
/* Top-Of-Stacks (tos) structure defined by RT-Druid in eecfg.c */
#define X86_INIT_TOS_OFFSET	 0x10U /* edi, esi, ebp, ebx  */

extern	EE_UREG EE_x86_active_tos;
#define	EE_hal_active_tos EE_x86_active_tos

extern	struct EE_TOS EE_x86_system_tos[];
#define	EE_std_system_tos EE_x86_system_tos

extern	EE_UREG EE_x86_thread_tos[];
#define	EE_std_thread_tos EE_x86_thread_tos

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern	struct EE_TOS EE_x86_IRQ_tos;
#endif

#endif /* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || \
    defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern	EE_UINT32 EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_THREAD_PTR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern	void EE_oo_thread_stub(void);

#endif



/*********************************************************************
 x86 interrupt disabling/enabling
 *********************************************************************/

__INLINE__ int __ALWAYS_INLINE__ EE_x86_IRQenabled(void) {
        EE_UINT32 flags;
		asm("pushf; pop %0" : "=r"(flags));
		return (flags & 0x0200);
}

/*
 * Enable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_x86_enableIRQ(void)
{
  	/*Enable interrupt*/
    asm volatile("sti\n\tnop");
}


/*
 * Disable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_x86_disableIRQ(void)
{
	/*Disable interrupt*/
    asm volatile("cli\n\tnop");
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
    EE_x86_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_x86_disableIRQ();
}

/* Suspend/Resume Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
    EE_UINT32 flags;
    asm volatile("pushfl ; popl %0":"=g" (flags): /* no input */ :"memory");
    EE_x86_disableIRQ(); // cli...
    return flags;
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG flags)
{
    asm volatile("pushl %0 ; popfl": /* no output */ :"g" (flags):"memory");
}

/*************************************************************************
 Utils
 *************************************************************************/

__INLINE__ void __ALWAYS_INLINE__ EE_hal_halt_cpu(void)
{
		asm volatile ("hlt");
}


/**
 * \brief Shutdown machine using ACPI
 * The static ACPI values work for QEMU and Bochs but probably not on real PCs!
 */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_shutdown_system(void)
{
	// write shutdown command to ACPI port
	asm volatile( "outw %0, %1" :: "a"((unsigned short) 0x2000), "Nd"((unsigned short) 0xB004));

	// stop in case ACPI shutdown failed
	while(1) asm volatile ("nop");
    __builtin_unreachable();
}


#endif

