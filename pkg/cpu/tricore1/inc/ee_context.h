/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, TU Dortmund University, Faculty of Computer Science 12
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

/* Author: Jan C. Kleinsorge, TU Dortmund University, 2010-
 *
 */
#ifndef __INCLUDE_TRICORE1_EE_CONTEXT_H__
#define __INCLUDE_TRICORE1_EE_CONTEXT_H__

// #undef DEBUG

#include "cpu/tricore1/inc/ee_debug.h"
#include "cpu/tricore1/inc/ee_compiler.h"
#include "cpu/tricore1/inc/ee_hal.h"
#include "cpu/tricore1/inc/ee_cpu.h"

/* Required to break a cyclic dependency. */
void EE_tc1_hal_stkchange(EE_TID tid);


/* Starts a given thread, reschedules and starts another one when it
 * is finished.  
 *
 * If there is nothing scheduled, return to the preempted thread.  We
 * specifically use TriCore's mechanism to implicitly restore contexts
 * (interrupts on/off, stack pointer, return addressed, etc). */


#ifdef __MONO__
/* Multistack variant to be found in ee_hal.c */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_hal_ready2stacked(EE_THREAD_PTR thread)
{
    do {
        EE_hal_enableIRQ();
        ((EE_THREAD_PTR)thread)();
        EE_hal_disableIRQ();
        EE_thread_end_instance();  
        thread = EE_hal_endcycle_next_thread;
    } while (thread != 0);
}
#endif


/* Typically called from within a generic primitive to implement
 * preemption.
 * NOTE: tc1_thread_tos[0]=main, tc1_thread_tos[1]=thread0, ... */
#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID tid)
{
    EE_tc1_hal_ready2stacked(EE_hal_thread_body[tid]);
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID tid)
{
    EE_tc1_hal_ready2stacked(tid, EE_hal_thread_body[tid]);
}
#endif


/* typically called at the end of a thread instance */
#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID tid)
{
    EE_hal_endcycle_next_thread = 0;
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID tid)
{
    EE_hal_endcycle_next_tid = tid;
    EE_hal_endcycle_next_thread = 0;
}
#endif


#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID tid)
{
    EE_hal_endcycle_next_thread = EE_hal_thread_body[tid];
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID tid)
{
    EE_hal_endcycle_next_tid = tid;
    EE_hal_endcycle_next_thread = EE_hal_thread_body[tid];
}
#endif


#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID tid)
{
    EE_hal_endcycle_stacked(tid);
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_stacked(EE_TID tid)
{
    EE_hal_endcycle_stacked(tid);
}
#endif


#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID tid)
{
    EE_hal_endcycle_ready(tid);
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_ready(EE_TID tid)
{
    EE_hal_endcycle_ready(tid);
}
#endif


#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID tid)
{
    EE_tc1_hal_stkchange(tid);
}
#endif


/*
 * OO TerminateTask related functions
 */
#if defined(__OO_BCC1__)    \
    || defined(__OO_BCC2__) \
    || defined(__OO_ECC1__) \
    || defined(__OO_ECC2__)

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID tid)
{
    EE_tc1_hal_terminate_savestk(&EE_terminate_data[tid],
                                 EE_terminate_real_th_body[tid]);
}



__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID tid)
{
    EE_tc1_hal_terminate_task(&EE_terminate_data[tid]);
}

#endif

#endif
