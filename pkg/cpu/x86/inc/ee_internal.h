/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Derived from pkg/cpu/e200zx/inc/ee_internal.h
 * Author: 2014,  Martin Hoffmann, FAU Erlangen
 */


#ifndef __INCLUDE_X86_INTERNAL_H__
#define __INCLUDE_X86_INTERNAL_H__

#include "cpu/x86/inc/ee_cpu.h"

#include "mcu/x86/inc/ee_lapic.h"

/*
 * Generic Primitives
 */

#include "cpu/common/inc/ee_primitives.h"
void EE_IRQ_end_instance(void);

/*************************************************************************
                            System stack
 *************************************************************************/
extern EE_STACK_T EE_x86_sys_stack[1024];

/*************************************************************************
                              HAL Functions
 *************************************************************************/


/* called as _first_ function of a primitive that can be called in
   an IRQ and in a task */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
	return EE_hal_suspendIRQ();
}


/* Called as _last_ function of a primitive that can be called in
   an IRQ and in a task.  Enable IRQs if they were enabled before entering. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
	EE_hal_resumeIRQ(f);
}


/* Used to get internal CPU priority. */
__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_hal_get_int_prio(void)
{
	return EE_lapic_get_int_prio();
}

/*
	Used to set internal CPU priority.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_int_prio(EE_TYPEISR2PRIO prio)
{
    EE_lapic_set_int_prio(prio);
}

/*
	Used to change internal CPU priority and return a status flag mask.
	N.B
	EE_FREG param flag and return value needed only for according to HAL
	interface.
*/
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_change_int_prio(
		EE_TYPEISR2PRIO prio, EE_FREG flag)
{
	EE_hal_set_int_prio(prio);
	return flag;
}

/*
	Used to raise internal CPU interrupt priority if param new_prio is greater
	than actual priority.
	N.B
	EE_FREG param flag and return value needed only for according to HAL
	interface.
*/
__INLINE__ EE_FREG __ALWAYS_INLINE__
		EE_hal_raise_int_prio_if_less(EE_TYPEISR2PRIO new_prio, EE_FREG flag)
{
	EE_TYPEISR2PRIO prev_prio = EE_hal_get_int_prio();
	if(prev_prio < new_prio) {
		EE_hal_set_int_prio(new_prio);
	}
	return flag;
}

/*
	Used to check if interrupt priority is less tha new priority to
	set.
*/
__INLINE__ EE_BIT __ALWAYS_INLINE__ EE_hal_check_int_prio_if_higher(
		EE_TYPEISR2PRIO new_prio){
    EE_TYPEISR2PRIO actual_prio = EE_lapic_get_int_prio();
	return (actual_prio > new_prio)?1U:0U;
}

/* Common Context Handling implementation */
#include "cpu/common/inc/ee_context.h"
/* typically called at the end of an interrupt by kernel */
#define EE_hal_IRQ_stacked	EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready	EE_hal_endcycle_ready


//#include "cpu/common/inc/ee_irqstub.h"

/*
 * OO TerminateTask related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || \
  defined(__OO_ECC2__)

void EE_hal_terminate_savestk(EE_TID tid);
#ifdef USE_PRAGMAS
/* The use of __attribute__ in NORETURN macro is deprected for MISRA
compliance, if necessary (and if the MISRA deviation is allowed)
use #pragma no_return ... or similar (e.g: see Diab compiler
documentation for details) */
void EE_hal_terminate_task(EE_TID tid);
#else
void EE_hal_terminate_task(EE_TID tid) NORETURN;
#endif

#endif /* __OO_BCCx */



#endif


