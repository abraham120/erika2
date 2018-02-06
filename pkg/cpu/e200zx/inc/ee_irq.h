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

/*
 * Author: 2010 Fabio Checconi
 */

#ifndef PKG_CPU_E200ZX_INC_EE_IRQ_H
#define PKG_CPU_E200ZX_INC_EE_IRQ_H

/* CPU-dependent part of HAL that have to be seen by user code */
#include "ee_cpu_os.h"


/* ISR priority level defines */
#define EE_ISR_UNMASKED 0U
#define EE_ISR_PRI_1  1U
#define EE_ISR_PRI_2  2U
#define EE_ISR_PRI_3  3U
#define EE_ISR_PRI_4  4U
#define EE_ISR_PRI_5  5U
#define EE_ISR_PRI_6  6U
#define EE_ISR_PRI_7  7U
#define EE_ISR_PRI_8  8U
#define EE_ISR_PRI_9  9U
#define EE_ISR_PRI_10 10U
#define EE_ISR_PRI_11 11U
#define EE_ISR_PRI_12 12U
#define EE_ISR_PRI_13 13U
#define EE_ISR_PRI_14 14U
#define EE_ISR_PRI_15 15U

#if (defined(__RN__)) && (defined (EE_ISR_DYNAMIC_TABLE))

#if defined(EE_PPCE200ZX_7_ISR) || defined(EE_PPCE200ZX_7_ISR_PRI)
#error In multicore environment IRQ priority 7 is already used by ERIKA\
 for Inter Cores Communication.
#endif /* EE_PPCE200ZX_7_ISR || EE_PPCE200ZX_7_ISR_PRI */

#define EE_PPCE200ZX_7_ISR     EE_e200zx_iirq_handler
#define EE_PPCE200ZX_7_ISR_PRI EE_E200ZX_INTC_CURRPROC | EE_ISR_PRI_1

#endif /* __RN__ && EE_ISR_DYNAMIC_TABLE */


/* I include context because is needed by common ee_irqstub.h */
#include "cpu/common/inc/ee_context.h"
#include "cpu/common/inc/ee_irqstub.h"

#if (defined(__ALLOW_NESTED_IRQ__)) && (!defined(__EE_MEMORY_PROTECTION__))
#define EE_std_enableIRQ_nested()   EE_e200z7_enableIRQ()
#define EE_std_disableIRQ_nested()  EE_e200z7_disableIRQ()
#endif  /* defined(__ALLOW_NESTED_IRQ__) &&
  (!defined(__EE_MEMORY_PROTECTION__)) */


/*
  For memory protection the stack is changed within the prestub and the postub
 */
#if (defined(__IRQ_STACK_NEEDED__)) && (!defined(__EE_MEMORY_PROTECTION__))
/*
 * Call an ISR. If the ISR is to be called on a new stack we need to
 * resort to the black magic of assembly programming, and here we're
 * left with just a declaration.  If the ISR doesn't need a new stack
 * we only need to enable the external interrupts and call it.
 *
 * The pseudocode for the full-fledged ISR call is the following:
 *
 * void EE_e200z7_call_ISR_new_stack(EE_e200z7_ISR_handler fun)
 * {
 *    if (EE_IRQ_nesting_level == 1) {
 *      change_to_IRQ_stacks();
 *      EE_std_enableIRQ_nested();    // Enable IRQs if nesting is allowed.
 *      fun();
 *      EE_std_disableIRQ_nested();   // Disable IRQs if nesting is allowed.
 *      change_back_from_IRQ_stacks();
 *    } else {
 *      EE_std_enableIRQ_nested();    // Enable IRQs if nesting is allowed.
 *      fun();
 *      EE_std_disableIRQ_nested();   // Disable IRQs if nesting is allowed.
 *    }
 * }
 */
void EE_e200zx_call_ISR(EE_e200z7_ISR_handler fun, EE_UREG nesting);

#else /* if defined(__IRQ_STACK_NEEDED__) &&
  (!defined(__EE_MEMORY_PROTECTION__)) */

/* Implemented as macro to remove the need of pointer null check for MISRA
   compliance. Fake do while construct to enforce ending semicolon */
#define EE_e200zx_call_ISR(fun, nesting)  \
  do {                                    \
    EE_std_enableIRQ_nested();            \
    fun();                                \
    EE_std_disableIRQ_nested();           \
  } while (0)
#endif /* else if defined(__IRQ_STACK_NEEDED__) &&
  (!defined(__EE_MEMORY_PROTECTION__)) */


#ifdef EE_ISR_DYNAMIC_TABLE
/*                        Dynamic ISR table implementation.                   */
/*
 * Register the handler `fun' for the IRQ `level', using priority `pri'.  If
 * `fun' is 0, disable the given interrupt.  Levels 0-15 are used for the
 * primary interrupt sources for the e200 core, while levels greater than 15 are
 * used for external interrupt sources connected to the interrupt controller.
 * This function is available only if the system is configured to use a dynamic
 * interrupt table (i.e., the EEOPT EE_ISR_DYNAMIC_TABLE is defined).
 */
void EE_e200z7_register_ISR(EE_UINT16 level, EE_e200z7_ISR_handler fun, EE_UINT8 pri);
#else
/*
  ISR2 pre-stub and post-stub shared between normal and memory protection
  behaviour
*/
__INLINE__ EE_ORTI_runningisr2_type __ALWAYS_INLINE__ EE_ISR2_prestub(
    EE_ORTI_runningisr2_type fun)
{
  /* keep the old ORTI */
  EE_ORTI_runningisr2_type ortiold;
  /* increment nesting level here, with isr disabled */
  EE_increment_IRQ_nesting_level();
  /* Save the old ORTI ID */
  ortiold = EE_ORTI_get_runningisr2();
  /* Set the new ID as an ISR2 ID */
  EE_ORTI_set_runningisr2(EE_ORTI_build_isr2id(fun));
  return ortiold;
}

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(
    EE_ORTI_runningisr2_type ortiold)
{
  /* Set old ORTI ID back */
  EE_ORTI_set_runningisr2(ortiold);
  /* ISR2 instance clean-up as requested by AR */
  EE_std_end_IRQ_post_stub();
  /*  Pop priority for external interrupts
      (the only that can be ISR2) Look at reference manual:
      9.4.3.1.2 End-of-Interrupt Exception Handler NOTE */
  EE_e200zx_mbar();
  EE_INTC_EOIR = 0U;
  /* decrement nesting level only from hereunder */
  EE_decrement_IRQ_nesting_level();
  /* check for scheduling point */
  if (!EE_is_inside_ISR_call()) {
    EE_std_after_IRQ_schedule();
  }
}

/* Poststub without INTC priority queue pop for internal exception */
__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_INT_poststub(
    EE_ORTI_runningisr2_type ortiold)
{
  /* Set old ORTI ID back */
  EE_ORTI_set_runningisr2(ortiold);
  /* ISR2 instance clean-up as requested by AR */
  EE_std_end_IRQ_post_stub();
  /* decrement nesting level only from hereunder */
  EE_decrement_IRQ_nesting_level();
  /* check for scheduling point */
  if (!EE_is_inside_ISR_call()) {
    EE_std_after_IRQ_schedule();
  }
}
#endif /* EE_ISR_DYNAMIC_TABLE */

/* ISRs with memory protection need special treatment */
#ifndef __EE_MEMORY_PROTECTION__

#ifdef EE_ISR_DYNAMIC_TABLE
/* Macro for ISR declaration. ISR1 macro doesn't exist because only ISR2 exists
   in Dynamic ISR table implementation */
#define ISR2(f)   void (f)(void)
#else /* EE_ISR_DYNAMIC_TABLE */
/*                        Static ISR Table implementation.                    */
/*                               !!! WARNING !!!
    Use ISRx macros only to registers hanlders for external interrupts,
    because the code that pop interrupt controller priority queue embedded
    in these macros.
    Dynamic ISR table handling make the check (level >= EE_E200ZX_MAX_CPU_EXC)
    to execute that code or not. That check is impossible in Static ISR table
    implementation.
    To obviate this problem two more macro are given: ISR1_INT and ISR2_INT to
    register handlers for internal exception.
*/

#define ISR1_PART1(f)						      \
  EE_increment_IRQ_nesting_level();                                   \
  /* This handle stack change and nesting */                          \
  EE_e200zx_call_ISR(EE_PREPROC_JOIN(ISR1_,f), EE_IRQ_nesting_level); \
  /* Pop priority for external interrupts */                          \
  /* 9.4.3.1.2 EOIE Handler NOTE */                                   \
  EE_e200zx_mbar();

#define ISR1_PART2 \
  EE_INTC_EOIR = 0U;                                                  \
  /* decrement nesting level */                                       \
  EE_decrement_IRQ_nesting_level();                                   \


#define ISR1(f)                     \
void EE_PREPROC_JOIN(ISR1_,f)(void);\
void f(void)                        \
{                                   \
ISR1_PART1(f)			    \
ISR1_PART2			    \
}                                   \
void EE_PREPROC_JOIN(ISR1_,f)(void)


#define ISR2_PART1(f) \
  /* keep the old ORTI */           \
  EE_ORTI_runningisr2_type ortiold; \
  /* handle ORTI ID */              \
  ortiold = EE_ISR2_prestub(f);

#define ISR2_PART2(f) \
  /* This handle stack change and nesting */                          \
  EE_e200zx_call_ISR(EE_PREPROC_JOIN(ISR2_,f), EE_IRQ_nesting_level); \
  /* poststub do clean-up and scheduling and INTC PRIO pop */         \
  EE_ISR2_poststub(ortiold);

#define ISR2(f)                      \
void EE_PREPROC_JOIN(ISR2_,f)(void); \
void f(void)                         \
{                                    \
ISR2_PART1(f)                        \
ISR2_PART2(f)			     \
}                                    \
void EE_PREPROC_JOIN(ISR2_,f)(void)

/*
  Following macros SHOULD BE used for internal interrupt handlers.
 */

#define ISR1_INT_PART1(f)                     \
  EE_increment_IRQ_nesting_level();           \
  /* This handle stack change and nesting */  \
  EE_e200zx_call_ISR(EE_PREPROC_JOIN(ISR1_INT_,f), EE_IRQ_nesting_level);

#define ISR1_INT(f)                      \
void EE_PREPROC_JOIN(ISR1_INT_,f)(void); \
void f(void)                             \
{                                        \
  ISR1_INT_PART1(f)			 \
  /* decrement nesting level */          \
  EE_decrement_IRQ_nesting_level();      \
}                                        \
void EE_PREPROC_JOIN(ISR1_INT_,f)(void)

#define ISR2_INT_PART1(f)                    \
  /* keep the old ORTI */                    \
  EE_ORTI_runningisr2_type ortiold;          \
  /* Save the old ORTI ID */                 \
  ortiold = EE_ISR2_prestub(f);              \
  /* This handle stack change and nesting */ \
  EE_e200zx_call_ISR(EE_PREPROC_JOIN(ISR2_INT_,f), EE_IRQ_nesting_level);


#define ISR2_INT(f)                                   \
void EE_PREPROC_JOIN(ISR2_INT_,f)(void);              \
void f(void)                                          \
{                                                     \
  ISR2_INT_PART1(f)                                   \
  /* post-stub internal do clean-up and scheduling */ \
  EE_ISR2_INT_poststub(ortiold);                      \
}                                                     \
void EE_PREPROC_JOIN(ISR2_INT_,f)(void)

#endif /*else EE_ISR_DYNAMIC_TABLE */

#else /* __EE_MEMORY_PROTECTION__ */
#include "ee_irq_mem_prot.h"
#endif /* else __EE_MEMORY_PROTECTION__ */

#endif
