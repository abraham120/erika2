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
#ifndef __INCLUDE_TRICORE1_EE_INT_H__
#define __INCLUDE_TRICORE1_EE_INT_H__

#include "ee_compiler.h"

#ifndef  __EECFG_THIS_IS_ASSEMBLER__

// #undef DEBUG

#include "cpu/tricore1/inc/ee_debug.h"
#include "cpu/tricore1/inc/ee_hal.h"
#include "cpu/tricore1/inc/ee_context.h"

/* Initialization routine */
void EE_init_int_vector(void);

/* Define an ISR (category 1)  */
#define ISR1(fn)                             \
    void __attribute__((interrupt_handler))  \
      EE_isr1_ ## fn (void)


/* ISR2 Prologue (Lower context safe)
 * (Interrupts already enabled, upper/lower contexts saved)
 */
__INLINE__ void __ALWAYS_INLINE__ EE_isr2_prestub(void)
{   
    /* Nothing to do (see comment below) */
}

/* ISR2 Epilogue
 *
 */
__INLINE__ void __ALWAYS_INLINE__ EE_isr2_poststub(void)
{
#ifdef __ALLOW_NESTED_IRQ__
    EE_hal_disableIRQ();
    EE_IRQ_nesting_level--;         
    if (EE_IRQ_nesting_level != 0)  /* Nested, resume a preempted ISR. */
        return;    
#else
    EE_IRQ_nesting_level = 0;
#endif
    EE_IRQ_end_instance();
    if (EE_hal_endcycle_next_thread) {
        EE_ICR icr = EE_tc1_get_ICR();
        icr.bits.CCPN = 0;      /* Reset interrupt priority */
        EE_tc1_set_ICR(icr);
        EE_tc1_isync();
#ifdef __MONO__
        EE_tc1_hal_ready2stacked(EE_hal_endcycle_next_thread);
#endif
#ifdef __MULTI__       
        EE_tc1_hal_ready2stacked(EE_hal_endcycle_next_tid, 
                                 EE_hal_endcycle_next_thread);
    } else { 
        EE_UREG from = EE_tc1_system_ctx[EE_tc1_active_tid + 1].SYS_tos;
        EE_UREG to = EE_tc1_system_ctx[EE_hal_endcycle_next_tid + 1].SYS_tos;
        if (to != from) {
            EE_ICR icr  = EE_tc1_get_ICR();
            icr.bits.CCPN = 0;  /* Reset interrupt priority */
            EE_tc1_set_ICR(icr);
            EE_tc1_isync();            
            EE_tc1_hal_stkchange(EE_hal_endcycle_next_tid);
        }
#endif
    }
}


/* Define an ISR (category 2): 
 * For the actual user-ISR the following holds:
 * - Executes in supervisor mode
 * - Upper and lower context saved, A11 holds return address
 * - PCXI is updated to hold previous IE and CCPN
 * - PIPN is written to CCPN
 * - Interrupts enabled 
 *
 * A word of warning: Tricore GCC 3.4.6 happily ignores the barrier
 * below and possibly schedules instructions from the user-defined ISR
 * at the very start which usually clobbers registers of the lower
 * context.  This is deadly when the prestub would actually trigger
 * saving the lower context - which would be too late to save a task's
 * state.  Luckily we managed to squeeze the entire prestub code into
 * the vector table so we can live with it for now.
 */
#define ISR(fn)                              \
    __INLINE__ void __ALWAYS_INLINE__        \
    EE_isr2_ ## fn (void);                   \
    void __attribute__((interrupt_handler))  \
      EE_isr2_stub_ ## fn (void)             \
    {                                        \
        EE_isr2_prestub();                   \
        EE_barrier();                        \
        EE_isr2_ ## fn();                    \
        EE_barrier();                        \
        EE_isr2_poststub();                  \
    }                                        \
    static void EE_isr2_ ## fn (void)


#endif /* __EECFG_THIS_IS_ASSEMBLER__ */

#endif /* __INCLUDE_TRICORE1_EE_INT_H__ */
