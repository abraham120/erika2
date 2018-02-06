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
 * Author: 2000-2002 Paolo Gai
 * CVS: $Id: ee_arch.h,v 1.4 2006/04/08 21:08:54 pj Exp $
 */


#include "eecfg.h"
#include "compiler.h"

#ifndef __INCLUDE_ST10MONO_ARCH_H__
#define __INCLUDE_ST10MONO_ARCH_H__

/* 
 * Monostack HAL interface
 * -----------------------
 * The Monostack HAL interface exports a set of context handling functions and 
 * the abstraction of thread as an instruction flow with its own CPU register 
 * set that may be shared among other threads.
 * Each thread is identified by an unique Thread ID of type TID
 */



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

typedef bit               EE_BIT;
typedef unsigned char     EE_UINT8;
typedef unsigned int      EE_UINT16;
typedef unsigned long int EE_UINT32;
typedef signed char       EE_INT8;
typedef signed int        EE_INT16;
typedef signed long int   EE_INT32;

typedef unsigned int      EE_UREG;
typedef signed int        EE_SREG;
typedef unsigned int      EE_FREG;

/* Thread IDs */
typedef EE_INT16       EE_TID;

/* Addresses (that have the same size of a pointer */
typedef EE_INT16       EE_ADDR;

/* IRQs */
typedef EE_UINT8       EE_TYPEIRQ;


#ifdef __TIME_SUPPORT__
/* Timer size */
typedef EE_UINT16      EE_TIME;
#endif

#ifdef __MULTI__
/* A Stack:
   This structure is used by the Multistack HAL to contain the information about 
   a "stack", that is composed by a user stack and a system stack.
   This type is used internally by the HAl and is not used by the Kernels.
*/
struct EE_TOS {
  EE_UREG system_tos;
  EE_UREG user_tos;
};
#endif

/* Application dependent data types */
#ifdef __HAS_TYPES_H__
#include "types.h"
#endif

/*************************************************************************
 HAL Variables
 *************************************************************************/

/* Register banks addresses for each thread */
extern const EE_UINT16 EE_st10_thread_cp[]; 

/* Thread function body pointer */
extern const EE_ADDR EE_hal_thread_body[];

/* User stack 
   Note that if __MULTI__ is selected, there are more than
   a single stack; This array contains at least the stack of the Dummy
   task.  Usually, it contains ALL the user stacks, whose starting
   points are in addresses located in the middle of the array..
   */
extern EE_UINT16 EE_st10_user_stack[];

#ifdef __MULTI__
/* Stack Informations.
   Each task use a system stack and a user stack.
   These stacks may be shared if the appropriate scheduling protocol is used.
*/
extern __IRAM__ struct EE_TOS EE_st10_system_tos[];

/* Pointers to the system and user tos (stored into st10_tos), one for
   each thread */
extern __IRAM__ EE_UINT16 EE_st10_thread_tos[];

/* the tos pointer of the active thread.
   from this pointer we can get the CP pointer...
   this variable must exist because when an interrupt is raised it
   have to know the location at whitch put the stack top
   informations. */
extern __IRAM__ EE_UREG EE_hal_active_tos;

/* All the interrupts handlers run in a separate stack, that starts from
   the adress specified in these 2 locations (one for the user stack, 
   one for the system stack ) */
extern __IRAM__ EE_UREG EE_st10_IRQ_user_tos;
extern __IRAM__ EE_UREG EE_st10_IRQ_sys_tos;

#endif

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put the usr and sys tos when 
   EE_hal_terminate_savestk is called into EE_oo_thread_stub */
extern EE_UINT16 EE_terminate_data_sys[];
extern EE_UINT16 EE_terminate_data_usr[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];

#endif


/*************************************************************************
 Functions
 *************************************************************************/

/*
 * System startup/shutdown
 */

void EE_st10_start(EE_ADDR userstack);




/* 
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
  #pragma asm()
  	BSET IEN
  #pragma endasm()
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
  #pragma asm()
  	BCLR IEN
	NOP
  #pragma endasm()
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL


/*
 * Time Handling
 */

#ifdef __TIME_SUPPORT__
/* init T8 to be used to implement the EDF reference time for capcom registers */
__INLINE__ void __ALWAYS_INLINE__ EE_st10_timer_support_init(void)
{
  #pragma asm (@w1)                                                                              
	; Init T8
	MOV @w1, #04700h	; T8R=1 T8M=0 (TIMER MODE) T8I=111 (x1024), TIMER 7 DISABLED
	MOV T78CON, @w1
	MOV @w1, #0007h		; T8IR=0 T8IE=0 ILVL=0001 GLVL=11
	MOV T8IC, @w1
	MOV T8, ZEROS
  #pragma endasm()
}

/* read current time */
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
  EE_TIME ax;
  #pragma asm(@w1)
    MOV @w1,T8
  #pragma endasm(ax=@w1)
  return (ax);
}
#endif


#endif
