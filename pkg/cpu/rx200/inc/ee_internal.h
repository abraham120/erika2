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
	@file ee_internal.h
	@brief Derived from cpu/pic30/inc/ee_internal.h
	@author Gianluca Franchino
	@date 2012
*/  

#ifndef __INCLUDE_RX200_INTERNAL_H__
#define __INCLUDE_RX200_INTERNAL_H__


#include "cpu/rx200/inc/ee_cpu.h"


/*************************************************************************
 Functions
 *************************************************************************/

/*
 * Generic Primitives
 */

#include "cpu/common/inc/ee_primitives.h"


/** Called as _first_ function of a primitive that can be called in
   an IRQ and in a task */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
    return EE_rx200_suspendIRQ();
}


/** Called as _last_ function of a primitive that can be called in
   an IRQ and in a task.  Enable IRQs if they were enabled before entering. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
    EE_rx200_resumeIRQ(f);
}

/* 
 * Context Handling  
 */

#include "cpu/common/inc/ee_context.h"

/* typically called at the end of an interrupt */
#define	EE_hal_IRQ_stacked	EE_hal_endcycle_stacked
#define	EE_hal_IRQ_ready	EE_hal_endcycle_ready


/* 
 * OO TerminateTask related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

/** Save the context and call the body of the task `tid'.  Implemented in
 * assembly */
void EE_hal_terminate_savestk(EE_TID tid);

/** Restore the context saved by EE_hal_terminate_savestk() for the task `tid' and
 * return from EE_hal_terminate_savestk().  Implemented in assembly */
void EE_hal_terminate_task(EE_TID tid) NORETURN;

#endif /* __OO_BCCx */



#endif /* __INCLUDE_CORTEX_MX_INTERNAL_H__ */
