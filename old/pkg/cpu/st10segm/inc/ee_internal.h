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
 * Author: 2000-2004 Paolo Gai
 * CVS: $Id: ee_internal.h,v 1.5 2006/04/08 21:08:54 pj Exp $
 */


#include "st10segm/arch.h"

#ifndef __INCLUDE_ST10SEGM_INTERNAL_H__
#define __INCLUDE_ST10SEGM_INTERNAL_H__

/*
 * Generic Primitives
 */

/* critical section for generic primitive called into an ISR or into a task */
/* critical section for generic primitive called into an ISR or into a task */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
  register EE_FREG temp;

  #pragma asm
	MOV @w1, PSW
	BCLR IEN
  #pragma endasm(temp=@w1)

  return temp;
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
  #pragma asm (@w1=f)
	MOV PSW, @w1
  #pragma endasm
}


/* 
 * Context Handling  
 */

/* WARNING: Most of these functions are non-reentrant */

/* typically called at the end of a thread instance */
extern EE_UREG EE_aux1, EE_aux2;


__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  #pragma asm(@w1=t)
	; R12 contains the t value
	MOV R12, @w1
	EXTERN _EE_st10_endcycle_ready:FAR
	JMPS SEG _EE_st10_endcycle_ready, SOF _EE_st10_endcycle_ready
  #pragma endasm()
#else
  EE_aux1 = -1;
  EE_aux2 = t;
#endif
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  #pragma asm(@w1=t)
	; R12 contains the t value
	MOV R12, @w1
	EXTERN _EE_st10_endcycle_stacked:FAR
	JMPS SEG _EE_st10_endcycle_stacked, SOF _EE_st10_endcycle_stacked
  #pragma endasm()
#else
  EE_aux1 = 0;
  EE_aux2 = t;
#endif
} 

/* typically called into a generic primitive to implement preemption */
void EE_hal_ready2stacked     (EE_TID t);             /* implemented in ASM */

/* typically called at the end of an interrupt */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  #pragma asm(@w1=t)
	; R12 and MDL should contain the t value
	MOV R12, @w1
	MOV MDL, R12
	EXTERN _EE_st10_IRQ_ready:FAR
	JMPS SEG _EE_st10_IRQ_ready, SOF _EE_st10_IRQ_ready
  #pragma endasm()
#else
  EE_aux1 = -1;
  EE_aux2 = t;
#endif
} 

__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID t)
{
#ifdef __ST10_OPTIMIZED__
  #pragma asm(@w1=t)
	; R12 contains the t value
	MOV R12, @w1
	EXTERN _EE_st10_IRQ_stacked:FAR
	JMPS SEG _EE_st10_IRQ_stacked, SOF _EE_st10_IRQ_stacked
  #pragma endasm()
#else
  EE_aux1 = 0;
  EE_aux2 = t;
#endif
} 

/* called to change the active stack, typically used with locking semaphores */
void EE_hal_stkchange (EE_TID t);	 /* implemented in ASM */
/*
 * Nested Interrupts Handling
 */


#ifdef __ALLOW_NESTED_IRQ__
/* Note: EE_IRQ_nesting_level is defined into src/st10mono/main.c */
/* can be called with interrupt enabled */
extern EE_UREG EE_IRQ_nesting_level;

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
  return EE_IRQ_nesting_level;
}
#endif

/* 
 * OO related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* we have only to save R0, because
   - The other registers are no more used (see tstub.c)
   - we used a CP bank for each task that can preempt another one
   - DPP1 should not be saved (since it is called from the same task, 
     DPP1 should not change
   - DPPx (I hope) do not need to be saved
*/

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{
  register EE_UINT16 t1;

  #pragma asm
    MOV @w1, R0
  #pragma endasm(t1=@w1)

  /* -4 means 1 word for CSP, 1 word for IP */
  EE_terminate_data_usr[t]= t1-4;

  ((void (*)(void))EE_terminate_real_th_body[t])();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
  register EE_UINT16 t1;

  t1 = EE_terminate_data_usr[t];

  #pragma asm(@w1=t1)
	MOV R0, @w1
	MOV	R3,[R0+]
	MOV	R2,[R0+]
	ATOMIC	#03h
	PUSH	R3
	PUSH	R2
	RETS
  #pragma endasm()
}

#endif

#endif
