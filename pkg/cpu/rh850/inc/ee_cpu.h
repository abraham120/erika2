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
 * Author: 2016 Nils Scharnke
 * Derived from cpu/rx200/inc/ee_cpu.h
 */

#ifndef	__INCLUDE_RH850_EE_CPU_H__
#define	__INCLUDE_RH850_EE_CPU_H__

#include	"eecfg.h"
#include	"cpu/rh850/inc/ee_compiler.h"


/******************************************************************************
 HAL Types and Structures
 ******************************************************************************/

/* Primitive data types */
//#include	"cpu/common/inc/ee_types.h"

typedef unsigned char EE_BIT;

typedef unsigned char EE_UINT8;
typedef signed char EE_INT8;

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

/* boolean type */
#ifndef EE_TYPEBOOL
#define EE_TYPEBOOL EE_UREG
#endif

/* boolean true define */
#ifndef EE_TRUE
#define EE_TRUE ((EE_TYPEBOOL)1)
#endif

/* boolean false define */
#ifndef EE_FALSE
#define EE_FALSE ((EE_TYPEBOOL)0)
#endif

/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"

/******************************************************************************
 Application dependent data types
 ******************************************************************************/

#ifdef	__HAS_TYPES_H__
#include	"types.h"
#endif

/******************************************************************************
 HAL Variables
 ******************************************************************************/

#ifdef	__MULTI__

/* Top-Of-Stacks (tos) structure defined by RT-Druid in eecfg.c */

extern	EE_UREG EE_rh850_active_tos;
#define	EE_hal_active_tos EE_rh850_active_tos
extern	struct EE_TOS EE_rh850_system_tos[];
#define	EE_std_system_tos EE_rh850_system_tos
extern	const EE_UREG EE_rh850_thread_tos[];
#define	EE_std_thread_tos EE_rh850_thread_tos

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern	struct EE_TOS EE_rh850_IRQ_tos;
#endif

#endif	/* __MULTI__ */

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
RH850 CPU functions
 *********************************************************************/
__INLINE__ EE_UINT32 GetPEID( void)
{
	EE_UINT32	__t;

	__t= (__STSR( 0, 2) >>16) & 0x7;

	return __t;
}

/*********************************************************************
RH850 interrupt disabling/enabling
 *********************************************************************/

/**
 * Enable interrupts
 */
__INLINE__ static void EE_rh850_enableIRQ()
{
        __EI();
}


static void EE_rh850_disableIRQ();
/**
 * Disable interrupts
 */
__INLINE__ static void EE_rh850_disableIRQ()
{
      __DI();
}

/*
 * Supend interrupts
 */
__INLINE__ static EE_FREG EE_rh850_suspendIRQ()
{
	EE_FREG r_PSW;
	r_PSW = __GETSR();
	__DI();
  return r_PSW;
}

/*
 * Resume interrupts
 */
__INLINE__ static void EE_rh850_resumeIRQ(EE_FREG sr)
{
	if (sr & 0x00000020)
			EE_rh850_disableIRQ();
	else
			EE_rh850_enableIRQ();
}

__INLINE__ static void EE_rh850_enableIRQ_nested(void)
{
	asm("MOV 1, R15"); /* Set R15 = 1 */
	asm("LDSR R15,13,2"); /* Set INTCFG = 1 -> No automatic update of ISPR (Priority of Interrupt being serviced) */
	
	asm("MOV 8, R15");
	asm("LDSR R15,10,2"); /* Nesting only allowed for interrupts with priority 2-0 (highest) */
}

__INLINE__ static void EE_rh850_disableIRQ_nested(void)
{
	asm("LDSR R0,10,2"); /* Set ISPR = 0 */
	asm("LDSR R0,13,2"); /* Set INTCFG = 0 -> Automatic update of ISPR */
}

/**
 * Return true (not 0) if IRQs are enabled, 0 (false) if IRQ are disabled.
 */
__INLINE__ static EE_UINT32 EE_rh850_get_IRQ_enabled(void)
{
	EE_FREG r_PSW;
	r_PSW = __GETSR();	
	
	if (r_PSW & 0x00000020)
			return 0;
	else
			return 1;
}

/*************************************************************************
 Functions exported by the HAL to the kernel
 *************************************************************************/

/* 
 * Interrupt Handling
 */

/** Hal Enable Interrupts */
 __INLINE__ void  EE_hal_enableIRQ(void)
{
    __EI();
}

/** Hal Disable Interrupts */
__INLINE__ void EE_hal_disableIRQ(void)
{
    __DI();
}

/** Hal Resume Interrupts */
__INLINE__ void EE_hal_resumeIRQ(EE_FREG f)
{
	if (f & 0x00000020)
			__DI();
	else
			__EI();
}

/** Hal Suspend Interrupts */
__INLINE__ EE_FREG EE_hal_suspendIRQ(void)
{
  EE_FREG r_PSW;
	r_PSW = __GETSR();
	__DI();
  return r_PSW;
}

#endif /* __INCLUDE_RH850_EE_CPU_H__ */