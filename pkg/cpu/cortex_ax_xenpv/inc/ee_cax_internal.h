/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013 Bruno Morelli
 */

#ifndef EE_CAX_INTERNAL_H__
#define EE_CAX_INTERNAL_H__

/* Public API must be seen by Kernel internals */
#include "cpu/cortex_ax_xenpv/inc/ee_cax_cpu.h"

/*******************************************************************************
                              Generic Primitives
 ******************************************************************************/

#include "cpu/common/inc/ee_primitives.h"

/*******************************************************************************
      System startup Handling is Moved in MCU folder, because TriCore
      architecture doesn't define any standard core timer to be used as
      system timer. So the system timer must be a MCU Timer.
 ******************************************************************************/
/* Inform StartOS kernel primitive that have to call EE_cpu_startos
   start-up routine */
//#define OO_CPU_HAS_STARTOS_ROUTINE

/*******************************************************************************
                      HAL For Primitives Syncronization
 ******************************************************************************/

/* Called as _first_ function of a primitive that can be called from within
 * an IRQ and from within a task. */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive( void )
{
  return EE_hal_suspendIRQ();
}

/* Called as _last_ function of a primitive that can be called from
 * within an IRQ or a task. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive( EE_FREG flags )
{
  EE_hal_resumeIRQ(flags);
}

/* Used to get internal CPU priority. */
__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_hal_get_int_prio( void )
{
  /* TODO:
  return EE_tc_get_int_prio();
  */
  return 0;
}

/* Used to set internal CPU priority. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_int_prio( EE_TYPEISR2PRIO prio )
{
  /* TODO
  EE_tc_set_int_prio(prio);
  */
}

/*
 * Used to change internal CPU priority and return a status flags mask.
 *
 * Note:    EE_FREG param flags and return value needed only for according to
 *          HAL interface.
 */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_change_int_prio(
  EE_TYPEISR2PRIO prio, EE_FREG flags )
{
  /* TODO
  EE_tc_set_int_prio(prio);
  return EE_TC_ADJUST_FLAGS_WITH_NEW_PRIO(flags, prio);
  */
  return 0;
}

/*
 * Used to raise internal CPU interrupt priority if param new_prio is greater
 * than actual priority.
 *
 * Note:    EE_FREG param flags and return value needed only for according to
 *          HAL interface.
 */

__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_raise_int_prio_if_less(
  EE_TYPEISR2PRIO new_prio, EE_FREG flags )
{
#if 0
 TODO:
  register EE_TYPEISR2PRIO prev_prio = EE_tc_get_int_prio();
  if ( prev_prio < new_prio )
  {
    EE_tc_set_int_prio(new_prio);
    /* Mask CCPN in flags and set the new one */
    flags = EE_TC_ADJUST_FLAGS_WITH_NEW_PRIO(flags, new_prio);
  }
  return flags;
#endif
  return 0;
}

/*
    Used to check if interrupt priority is less than new priority to be
    set.
*/
__INLINE__ EE_BIT __ALWAYS_INLINE__ EE_hal_check_int_prio_if_higher(
    EE_TYPEISR2PRIO new_prio )
{
  /* TODO
  register EE_TYPEISR2PRIO actual_prio = EE_tc_get_int_prio();
  return (actual_prio > new_prio)? 1U: 0U;
  */
  return 0;
}

/*******************************************************************************
                Multistack Data Structures for Context Handling
 ******************************************************************************/
/*
 * These structures are used by the Multistack HAL to contain the
 * information about a "stack", that is composed by a user stack
 * (SYS-mode) and a system stack (IRQ-mode). This type is used
 * internally by the HAL and is not used by the kernel.
 */

#ifdef __MULTI__

#if 0

/* Index of the current stack. */
extern EE_UREG EE_tc_active_tos;

/* Used in common context */
#define EE_hal_active_tos EE_tc_active_tos

/* Top of each private stack. */
extern struct EE_TC_TOS EE_tc_system_tos[];

/* Used to hold the Tasks return addresses (that ccan be lost in context
   switches) */
extern EE_ADDR EE_tc_tasks_RA[];

/* Stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
/* This could be declared 'const', but to keep RT-Druid behave as usual
   is NOT declared as const */
extern struct EE_TOS EE_tc_IRQ_tos;
#endif /* __IRQ_STACK_NEEDED__ */

#endif

#endif /* __MULTI__ */

/*******************************************************************************
                            Standard Context Handling
 ******************************************************************************/

/* Flag (OR'ed to an EE_TID) to mark a task as stacked. */
#define TID_IS_STACKED_MARK 0x80000000U

#include "cpu/common/inc/ee_context.h"

/* typically called at the end of an interrupt */
#define EE_hal_IRQ_stacked  EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready    EE_hal_endcycle_ready

/*******************************************************************************
                        OO TerminateTask related stuffs
 ******************************************************************************/
#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || \
    defined(__OO_ECC2__)


void EE_cax_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
void EE_cax_terminate_task(EE_ADDR sp) NORETURN;
/** Save the context and call the body of the task `tid'. */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{
  EE_cax_terminate_savestk(&EE_terminate_data[t],
                            (EE_ADDR)EE_terminate_real_th_body[t]);
}

/** Restore the context saved by EE_hal_terminate_savestk() for the task `tid'
    and return from EE_hal_terminate_savestk(). */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
  EE_cax_terminate_task(&EE_terminate_data[t]);
}


#endif /* __OO_BCCx__  || __OO_ECCx__ */

#endif /* EE_CAX_INTERNAL_H__ */
