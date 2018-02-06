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
 * Derived from pkg/cpu/pic30/inc/ee_cpu.h
 * Derived from pkg/cpu/msp430/inc/ee_cpu.h
 * Author: 2010,  Christian Grioli
 */


#ifndef __INCLUDE_MSP430_EE_CPU_H__
#define __INCLUDE_MSP430_EE_CPU_H__

#include "eecfg.h"
#include<io.h>
#include <signal.h>
#ifdef __GNUC__
#include "cpu/common/inc/ee_compiler_gcc.h"
#else
#error Unsupported compiler
#endif



#define MSP430_INIT_TOS_OFFSET 9


/*************************************************************************
 HAL Types and structures
 *************************************************************************/


/* Primitive data types */
#include "cpu/common/inc/ee_types.h"

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

/* Thread IDs */
typedef EE_INT16 EE_TID;
/* Used by the common layer to decide whether to start a new thread */
#define TID_IS_STACKED_MARK 0x8000

/* EE_TYPEIRQ is currently unused */


/* Use the "standard" implementation */
#include "cpu/common/inc/ee_hal_structs.h"

#ifdef __MULTI__

/* Top-of-stack of each private stack */
extern struct EE_TOS EE_msp430_system_tos[];

/* Index of the current stack */
extern EE_UREG EE_msp430_active_tos;

#endif /* __MULTI__ */





/*********************************************************************
 MSP430 interrupt disabling/enabling
 *********************************************************************/


/* Used to check the value returned by EE_msp430_disableIRQ */
#define EE_msp430_are_IRQs_enabled(ie) (ie & 0x0008)


/*
 * Enable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_msp430_enableIRQ(void)
{
  	/*Enable interrupt*/
	eint();

}


/*
 * Disable interrupts
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_msp430_disableIRQ(void)
{
    	/*Save SR register*/
	EE_FREG status=READ_SR;
	/*Disable interrupt*/
  	dint();
/*From the manual:If any code sequence needs to be protected from interruption, the DINT should be executed at least one instruction before the beginning of the uninterruptible sequence, or should be followed by a NOP instruction.*/
	nop();
	return status;
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
    EE_msp430_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_msp430_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

#include "cpu/msp430/inc/ee_utils.h"
#include "cpu/msp430/inc/ee_context.h"
#include "cpu/msp430/inc/ee_irqstub.h"

#endif /* __INCLUDE_MSP430_EE_CPU_H__ */
