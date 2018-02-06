/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/** 
	@file ee_cpu.h
	@brief CPU-dependent part of HAL. Derived from pkg/cpu/pic30/inc/ee_cpu.h
	@author Gianluca Franchino
	@date 2012
*/ 

#ifndef __INCLUDE_RX200_EE_CPU_H__
#define __INCLUDE_RX200_EE_CPU_H__

#include "eecfg.h"

#ifdef __CCRX__
#include "cpu/common/inc/ee_compiler_ccrx.h"
#else	/* __CCRX__ */
#error ee_cpu.h --> Unsupported compiler
#endif	/* !__CCRX__ */

/* Initial stack offset (in words) */
#ifndef RX200_INIT_TOS_OFFSET
#define RX200_INIT_TOS_OFFSET 8
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

typedef EE_UINT16 EE_UREG16;
typedef EE_INT16  EE_SREG16;
typedef EE_UINT16 EE_FREG16;

typedef EE_UINT8 EE_UREG8;
typedef EE_INT8  EE_SREG8;
typedef EE_UINT8 EE_FREG8;

#define EE_UREG_SIZE 4
#define EE_UREG16_SIZE 2
#define EE_UREG8_SIZE 1

#ifdef __CCRX__
#define	EE_HWREG_PTR		volatile EE_UREG __evenaccess *

#define	EE_HWREG_ADDR(x)	((EE_HWREG_PTR)(x))
#define	EE_HWREG(x)		(*EE_HWREG_ADDR(x))

#define	EE_HWREG16_PTR		volatile EE_UREG16 __evenaccess *

#define	EE_HWREG16_ADDR(x)	((EE_HWREG16_PTR)(x))
#define	EE_HWREG16(x)		(*EE_HWREG16_ADDR(x))

#define	EE_HWREG8_PTR		volatile EE_UREG8 __evenaccess *

#define	EE_HWREG8_ADDR(x)	((EE_HWREG8_PTR)(x))
#define	EE_HWREG8(x)		(*EE_HWREG8_ADDR(x))
#else	/* __CCRX__ */
#error ee_cpu.h --> Unsupported compiler
#endif	/* !__CCRX__ */


/* Thread IDs */
typedef EE_INT32 EE_TID;
typedef	EE_UREG EE_UTID;
/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x80000000

/* EE_TYPEIRQ is currently unused */

/* XXX: define EE_TIME? */

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

#ifdef __MULTI__

/* Top-of-stack of each private stack */
extern struct EE_TOS EE_rx200_system_tos[];
#define	EE_std_system_tos EE_rx200_system_tos

/* Index of the current stack */
extern EE_UREG EE_rx200_active_tos;
#define	EE_hal_active_tos EE_rx200_active_tos

/*extern	EE_UREG EE_pic30_thread_tos[];
#define	EE_std_thread_tos EE_pic30_thread_tos */
#endif /* __MULTI__ */

/*********************************************************************
RX200 interrupt disabling/enabling
 *********************************************************************/

#pragma inline_asm (EE_rx200_enableIRQ, EE_rx200_disableIRQ, EE_rx200_suspendIRQ, EE_rx200_resumeIRQ, EE_rx200_get_IRQ_enabled)


/**
 * Enable interrupts
 */
static void EE_rx200_enableIRQ()
{
	SETPSW I;
}

/**
 * Disable interrupts
 */
static void EE_rx200_disableIRQ()
{
	CLRPSW I;
}

/*
 * Supend interrupts
 * Return value is in R1
 */
static EE_FREG EE_rx200_suspendIRQ()
{
	MVFC PSW, R1;
	CLRPSW I;
}

/*
 * Resume interrupts
 * Note: sr is stord in R1
 */
static void EE_rx200_resumeIRQ(EE_FREG sr)
{
/*
	if (sr & 0b10000000000000000)
			EE_rx200_enableIRQ();
	else
			EE_rx200_disableIRQ();
*/
	BTST #16, R1;
	BZ	EE_CLEAR_INT;
	SETPSW I;
	BRA	EE_RESUME_IRQ_END;
EE_CLEAR_INT:	
	CLRPSW I;
EE_RESUME_IRQ_END:
}

/**
 * Return true (not 0) if IRQs are enabled, 0 (false) if IRQ are disabled.
 */
static EE_UINT32 EE_rx200_get_IRQ_enabled(void)
{
	MVFC PSW, R1;
	BZ	EE_IRQ_DISABLED;
	MOV #1, R1;
	BRA	EE_RESUME_IRQ_END;
EE_IRQ_DISABLED:	
	MOV #0, R1;
EE_GET_IRQ_END:

}

/*************************************************************************
 Functions exported by the HAL to the kernel
 *************************************************************************/

/* 
 * Interrupt Handling
 */

/** Hal Enable Interrupts */
 __INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_rx200_enableIRQ();
}

/** Hal Disable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_rx200_disableIRQ();
}

/** Hal Resume Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG f)
{
    EE_rx200_resumeIRQ(f);
}

/** Hal Suspend Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
    return EE_rx200_suspendIRQ();
}


#if 0
/**************************************************************************
 System Initialization
***************************************************************************/

void EE_system_init(void);

/*************************************************************************
 CPU-dependent ORT support (mainly OTM)
 *************************************************************************/

/* Probably, some parts of the OTM code below does not depend on the
 * architecture.  They should be moved somewhere into pkg/cpu/common if this
 * turns out to be the case. */

#define EE_ORTI_OTM_ID_RUNNINGISR2 1
#define EE_ORTI_OTM_ID_SERVICETRACE 2

#ifdef __OO_ORTI_USE_OTM__
void EE_rx200_send_otm8(EE_UINT8 id, EE_UINT8 data);
void EE_rx200_send_otm32(EE_UINT8 id, EE_UINT32 data);

#else /* if __OO_ORTI_USE_OTM__ */
__INLINE__ void EE_rx200_send_otm8(EE_UINT8 id, EE_UINT8 data)
{
	/* OTM disabled */
}

__INLINE__ void EE_rx200_send_otm32(EE_UINT8 id, EE_UINT32 data)
{
	/* OTM disabled */
}
#endif /* else __OO_ORTI_USE_OTM__ */

#ifdef __OO_ORTI_RUNNINGISR2__
__INLINE__ void EE_ORTI_send_otm_runningisr2(EE_ORTI_runningisr2_type isr2)
{
	EE_rx200_send_otm32(EE_ORTI_OTM_ID_RUNNINGISR2, (EE_UINT32)isr2);
}
#endif /* __OO_ORTI_RUNNINGISR2__ */

#ifdef __OO_ORTI_SERVICETRACE__
__INLINE__ void EE_ORTI_send_otm_servicetrace(EE_UINT8 srv)
{
	EE_rx200_send_otm8(EE_ORTI_OTM_ID_SERVICETRACE, srv);
}

#endif /* __OO_ORTI_SERVICETRACE__ */

#endif /* #if 0*/

#endif /* __INCLUDE_RX200_EE_CPU_H__ */
