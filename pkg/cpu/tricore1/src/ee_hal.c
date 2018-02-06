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

// #undef DEBUG

#include "ee_internal.h"
#include "cpu/tricore1/inc/ee_debug.h"
#include "cpu/tricore1/inc/ee_compiler.h"
#include "cpu/tricore1/inc/ee_hal.h"

/*
 * This variable contains the address of the new preempter thread,
 * when the preemption check is done at the end of a thread.
 *
 * NOTE: This variable is modified when a thread ends (before
 * EE_thread_end_instance()) and its content is read when
 * EE_thread_end_instance() ends; during this period it is
 * important to disable interrupts in order to avoid nested
 * EE_thread_end_instance() calls. */
EE_THREAD_PTR EE_hal_endcycle_next_thread = 0;

/* Counts nesting of interrupts
 * (PSW.CDC is reset upon each interrupt so we need to keep track
 * of it manually) */
EE_UREG EE_IRQ_nesting_level = 0;

#ifdef __MULTI__

/* Holds the preempter thread's id */
EE_TID EE_hal_endcycle_next_tid;

/* The id of the currently active stack. */
EE_TID EE_tc1_active_tid = -1;

#endif


#ifdef __MULTI__
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_tos_of(EE_TID tid)
{
    return EE_tc1_system_ctx[tid + 1].SYS_tos;
}


/* Saves necessary context information to resume a thread later */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_thread_save(EE_TID tid, EE_UREG tos)
{
    /* For shared stacks, we need to update the stack base address. */
    EE_tc1_system_tos[tos].SYS_tos_addr = EE_tc1_get_SP();
    EE_tc1_system_ctx[tid + 1].SYS_pcx = EE_tc1_csa_get_pcxi().reg;
    EE_tc1_system_ctx[tid + 1].SYS_ra = EE_tc1_get_RA();
    EE_tc1_dsync();
}


/* Restores previously saved context information of a thread */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_thread_restore(EE_TID tid)
{
    const EE_PCXI pcx = (EE_PCXI)EE_tc1_system_ctx[tid +  1].SYS_pcx;
    const EE_ADDR ra = EE_tc1_system_ctx[tid + 1].SYS_ra;

    EE_tc1_csa_set_pcxi(pcx);
    EE_tc1_set_RA(ra);
    EE_tc1_active_tid = tid;
    EE_tc1_isync();
}


/* This function must be invoked by call and may not be inlined  
 * so we have direct access to the caller's CSA. 
 * The mono-stack variant is inlined (ee_context.h).
 */
void EE_tc1_hal_ready2stacked(EE_TID tid, EE_THREAD_PTR thread)
{
    EE_UREG tid_from = EE_tc1_active_tid;
    EE_UREG tos_from = EE_tos_of(tid_from);
    EE_UREG tos = EE_tos_of(tid);

    EE_tc1_thread_save(EE_tc1_active_tid, tos_from);
    do {
        if (tos_from != tos)
            EE_tc1_set_SP(EE_tc1_system_tos[tos].SYS_tos_addr);    
        EE_tc1_active_tid = tid;

        EE_hal_enableIRQ();
        ((EE_THREAD_PTR)thread)();
        EE_hal_disableIRQ();  
        EE_thread_end_instance(); 

        tid = EE_hal_endcycle_next_tid;
        tos = EE_tos_of(tid);
        thread = EE_hal_endcycle_next_thread;
        tos_from = EE_tos_of(EE_tc1_active_tid);
    } while (thread != 0);

    if (tos_from != tos)
        EE_tc1_set_SP(EE_tc1_system_tos[tos].SYS_tos_addr);    
    EE_tc1_thread_restore(EE_hal_endcycle_next_tid);
}



/* Resumes a preempted thread. 
 * 
 * Similar to ready2stacked, we rely on TriCore's implicit context
 * handling to recover state when resuming a thread.
 */
void EE_tc1_hal_stkchange(EE_TID tid)
{
    const EE_TID tid_from = EE_tc1_active_tid;
    const EE_UREG tos_from = EE_tc1_system_ctx[tid_from + 1].SYS_tos;

    EE_tc1_thread_save(tid_from, tos_from);
    EE_tc1_thread_restore(tid);
}

#endif  /* __MULTI__ */
