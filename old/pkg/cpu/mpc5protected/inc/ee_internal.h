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
 * Author: Antonio Fiaschi
 * CVS: $Id: ee_internal.h,v 1.10 2006/04/08 21:08:54 pj Exp $
 */

#include "cpu/mpc5protected/inc/ee_cpu.h"

#ifndef __INCLUDE_MPC5PROTECTED_INTERNAL_H__
#define __INCLUDE_MPC5PROTECTED_INTERNAL_H__

/*************************************************************************
 Functions
 *************************************************************************/

/*
 * System utilities
 */

void EE_hal_stub_end_instance(void);

/*
 * Generic Primitives
 */

/* This primitive shall be atomic.
   This primitive shall be inserted as the last function in an IRQ handler.
   If the HAL allow IRQ nesting the end_instance should work as follows:
   - it must implement the preemption test only if it is the last IRQ on the stack
   - if there are other interrupts on the stack the IRQ end_instance should do nothing
*/

/*
 * Context Handling
 */

/* WARNING: All these functions may be non-reentrant */

extern EE_ADDR EE_hal_endcycle_next_body;
extern EE_TID EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_stack;
extern EE_AID EE_hal_endcycle_next_appl;
extern EE_BIT EE_hal_endcycle_protection;

/* typically called into a generic primitive to implement preemption */

__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread, EE_ADDR epilogue)
{
	EE_hal_endcycle_next_body = EE_mpc5_thread_toc[thread+1].body;
	EE_hal_endcycle_next_appl = EE_mpc5_thread_toc[thread+1].application_id;
	EE_hal_endcycle_next_thread = thread+1;
	EE_hal_endcycle_next_stack = EE_mpc5_thread_toc[thread+1].stack_id;
	EE_mpc5_thread_epilogue[EE_mpc5_active_thread] = epilogue;
	EE_mpc5_thread_epilogue[thread+1] = NULL;

	EE_hal_endcycle_protection = EE_mpc5_thread_toc[thread+1].appl_protection;
}

/* typically called at the end of a thread instance */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
	EE_hal_endcycle_next_stack = EE_mpc5_thread_toc[thread+1].stack_id;
	EE_hal_endcycle_next_thread = thread+1;
	EE_hal_endcycle_next_body = 0;
	EE_hal_endcycle_next_appl = EE_mpc5_thread_toc[thread+1].application_id;

	EE_hal_endcycle_protection = EE_mpc5_thread_toc[thread+1].appl_protection;
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
	EE_hal_endcycle_next_stack = EE_mpc5_thread_toc[thread+1].stack_id;
	EE_hal_endcycle_next_thread = thread+1;
	EE_hal_endcycle_next_body = EE_mpc5_thread_toc[thread+1].body;
	EE_hal_endcycle_next_appl = EE_mpc5_thread_toc[thread+1].application_id;
	EE_mpc5_thread_epilogue[thread+1] = NULL;

	EE_hal_endcycle_protection = EE_mpc5_thread_toc[thread+1].appl_protection;
}

/* typically called at the end of an interrupt */
#define EE_hal_IRQ_stacked EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready EE_hal_endcycle_ready

/* called to change the active stack, typically inside blocking primitives */
/* there is no mono version for this primitive...*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread, EE_ADDR epilogue)
{
	EE_hal_endcycle_next_stack = EE_mpc5_thread_toc[thread+1].stack_id;
	EE_hal_endcycle_next_thread = thread+1;
	EE_hal_endcycle_next_body = 0;
	EE_hal_endcycle_next_appl = EE_mpc5_thread_toc[thread+1].application_id;
	EE_mpc5_thread_epilogue[EE_mpc5_active_thread] = epilogue;

	EE_hal_endcycle_protection = EE_mpc5_thread_toc[thread+1].appl_protection;
}

extern EE_UREG EE_IRQ_nesting_level;

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
	return EE_IRQ_nesting_level;
}

__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
}


__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
}

/* ASM implemented by ee_irqvect.S */
void EE_IRQ_epilogue(void);

#endif

