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
 * Author:  Antonio Romano 	
 * CVS: $Id: ee_cpu.h,v 1.2 2006/08/02 11:46:58 romano Exp $
 */



#include "eecfg.h"
#include "cpu/avr5/inc/ee_compiler.h"

#ifndef __INCLUDE_AVR5_ARCH_H__
#define __INCLUDE_AVR5_ARCH_H__




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

typedef unsigned char EE_BIT;
typedef unsigned char EE_UINT8;
typedef unsigned int EE_UINT16;

typedef unsigned long EE_UINT32;
typedef unsigned char EE_UREG;
typedef int EE_ADDR;
typedef void (*EE_VOID_CALLBACK)(void);
/* Code addresses (same size of function pointers) */
/* For an easy upgrade path, we use a define instead of the typedef:
   typedef void (*EE_FADDR)(void); */
#define EE_FADDR EE_ADDR

/* Thread body pointer (same size of function pointers) */
#define EE_THREAD_PTR EE_ADDR

typedef signed char EE_INT8;
typedef int EE_INT16;
typedef long EE_INT32;


typedef long EE_SREG;
typedef unsigned long EE_FREG;

/* Thread IDs */
typedef unsigned long EE_TID;
typedef unsigned long EE_UTID;




/* EE_TYPEIRQ is defined inside the MCU */






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

#ifdef __MULTI__
struct EE_TOS {
    EE_ADDR SYS_tos;
};
#endif




extern const EE_ADDR EE_hal_thread_body[];


#ifdef __MULTI__

/* each task use a stack */

extern const struct EE_TOS EE_avr5_system_tos[];

/* avr5_system_tos[] index that point to the thread tos (one for each thread) */
extern EE_UREG EE_avr5_thread_tos[];

/* avr5_system_tos[] index that point to the active thread tos */
extern EE_UREG EE_avr5_active_tos;

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern EE_ADDR EE_avr5_IRQ_tos;
#endif

#endif /* __MULTI__ */

#if defined(__OSEKOS_BCC1__) || defined(__OSEKOS_BCC2__) || defined(__OSEKOS_ECC1__) || defined(__OSEKOS_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_osek_thread_stub */
extern EE_UINT32 EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern void EE_osek_thread_stub(void);

#endif



/*********************************************************************
 AVR5 interrupt disabling/enabling
 *********************************************************************/

/*
 * Enable interrupts
 */



__INLINE__ void EE_avr5_enableIRQ(void)
{
	
    asm volatile("sei"::); 
}





/*
 * Disable interrupts
 */



__INLINE__ void EE_avr5_disableIRQ(void)
{	

    asm volatile("cli"::); 
}




/*************************************************************************
 Functions
 *************************************************************************/

/* 
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void EE_hal_enableIRQ(void)
{
    EE_avr5_enableIRQ();
}

__INLINE__ void EE_hal_disableIRQ(void)
{
    EE_avr5_disableIRQ();
}

/* Disable/Enable interrupts when into an IRQ Routine */
/* NOTE: if there are no nested interrupt requests, IRQ handlers runs
   with interrupts disabled, and these functions are void!!! */
__INLINE__ void EE_hal_IRQ_enableIRQ(void)
{
#ifdef __ALLOW_NESTED_IRQ__
    EE_hal_enableIRQ();
#endif
}

/* Disable interrupts when into an IRQ Routine */
__INLINE__ void EE_hal_IRQ_disableIRQ(void)
{
#ifdef __ALLOW_NESTED_IRQ__
    EE_hal_disableIRQ();
#endif
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

#endif /* __INCLUDE_AVR5_ARCH_H__ */
