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
 * Author: 2005 Michele Cirinei
 *         2006- Paolo Gai
 *         2008- Paolo & Francesco: change interrupt disabling/enabling
 *         procedure, now with DISI instruction
 *         2011- Giuseppe Serano: pkg/cpu/common integration
 *                                interrupt disable/enable via IPL
 *                                adds interrupt suspend/resume hal APIs
 * CVS: $Id: ee_cpu.h,v 1.7 2008/07/16 15:01:38 francesco Exp $
 */

#ifndef	__INCLUDE_PIC30_EE_CPU_H__
#define	__INCLUDE_PIC30_EE_CPU_H__

#include	"eecfg.h"
#include	"cpu/pic30/inc/ee_compiler.h"
#include	"ee_pic30regs.h"

#define	USER_INT_MAX_IPL	6
#define	USER_INT_MIN_IPL	0

/******************************************************************************
 HAL Types and Structures
 ******************************************************************************/

/* Primitive data types */
#include	"cpu/common/inc/ee_types.h"

typedef	EE_UINT16 EE_UREG;
typedef	EE_INT16  EE_SREG;
typedef	EE_UINT16 EE_FREG;

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
typedef	EE_SREG EE_TID;
typedef	EE_UREG EE_UTID;
#define	TID_IS_STACKED_MARK	0x8000

/* EE_TYPEIRQ is currently unused */

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

extern	EE_UREG EE_pic30_active_tos;
#define	EE_hal_active_tos EE_pic30_active_tos
extern	struct EE_TOS EE_pic30_system_tos[];
#define	EE_std_system_tos EE_pic30_system_tos
extern	EE_UREG EE_pic30_thread_tos[];
#define	EE_std_thread_tos EE_pic30_thread_tos

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern	struct EE_TOS EE_pic30_IRQ_tos;
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
 PIC30 interrupt disabling/enabling
 *********************************************************************/

/*
 * Enable interrupts
 */

__INLINE__ void __ALWAYS_INLINE__ EE_pic30_enableIRQ(void)
{
  SRbits.IPL = USER_INT_MIN_IPL;
}

/*
 * Disable interrupts
 */

__INLINE__ void __ALWAYS_INLINE__ EE_pic30_disableIRQ(void)
{
  SRbits.IPL = USER_INT_MAX_IPL;
}

/*
 * Supend interrupts
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_pic30_suspendIRQ()
{
  register EE_FREG sr;
  sr = SR;
  SRbits.IPL = USER_INT_MAX_IPL;
  return sr;
}

/*
 * Resume interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_pic30_resumeIRQ(EE_FREG sr)
{
  SR = sr;
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
    EE_pic30_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_pic30_disableIRQ();
}

/* Suspend/Resume Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
    return EE_pic30_suspendIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG flags)
{
    EE_pic30_resumeIRQ(flags);
}

/*************************************************************************
 Include the Utils
 *************************************************************************/

#include	"cpu/pic30/inc/ee_utils.h"

#endif /* __INCLUDE_PIC30_ARCH_H__ */
