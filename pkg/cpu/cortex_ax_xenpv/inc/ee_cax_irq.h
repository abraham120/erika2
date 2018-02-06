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

#ifndef EE_CAX_IRQ_H__
#define EE_CAX_IRQ_H__

//#define EE_std_change_context(x) ((void)0)

/* Use angled parenthesis to include the main "ee_internal.h" */
#include "ee_irq.h" /* for ee_irqstub.h ? */
#include "cpu/cortex_ax_xenpv/inc/ee_cax_cpu.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_context.h"
#include "cpu/common/inc/ee_irqstub.h"

/* TODO: EE_CAX_MAX_ARCH_ISR_ID should be defined in
 * MCU config */
#define EE_CAX_MAX_ARCH_ISR_ID 1019 /* 0 .. 1019 different IRQ ID */

#ifdef __MSRP__

#if defined(EE_CAX_10_ISR) || defined(EE_CAX_10_ISR_PRI) || defined(EE_CAX_10_ISR_CAT)
#error "Irq 10 is reserverd while rpc are enabled"
#endif /* EE_CAX_10_ISR || EE_CAX_10_ISR_PRI || EE_CAX_10_ISR_CAT */

#define EE_CAX_10_ISR EE_cax_iirq_handler
#define EE_CAX_10_ISR_PRI 1
#define EE_CAX_10_ISR_CAT 2

#endif /* __MSRP__ */



#ifdef __ALLOW_NESTED_IRQ__

extern struct EE_TOS EE_cortex_ax_xenpv_IRQ_tos;

#define EE_std_enableIRQ_nested() EE_cortex_ax_enableIRQ()
#define EE_std_disableIRQ_nested() EE_cortex_ax_disableIRQ()

#else	/* else __ALLOW_NESTED_IRQ__*/

#define EE_std_enableIRQ_nested() ((void)0)
#define EE_std_disableIRQ_nested() ((void)0)

#endif /* end __ALLOW_NESTED_IRQ__*/

#if defined(__MULTI__) && defined(__IRQ_STACK_NEEDED__)
/* TODO */

#else	/* else __MULTI__ && __IRQ_STACK_NEEDED__*/

#define EE_cortex_ax_change_stack() ((void)0)
#define EE_cortex_ax_stack_back() ((void)0)

#endif	/* end __MULTI__ && __IRQ_STACK_NEEDED__*/

/* Define an ISR (category 1). */
#define ISR1(f)                          \
void EE_PREPROC_JOIN(ISR1_,f) ( void );  \
void f ( void )                          \
{                                        \
  EE_std_enableIRQ_nested();             \
  EE_PREPROC_JOIN(ISR1_,f)();            \
  EE_std_disableIRQ_nested();            \
}                                        \
void EE_PREPROC_JOIN(ISR1_,f) ( void )

/* Define an ISR (category 2). */
#define ISR2(f)                          \
void EE_PREPROC_JOIN(ISR2_,f) ( void );  \
void f ( void )                          \
{                                        \
  EE_increment_IRQ_nesting_level();      \
  EE_std_enableIRQ_nested();             \
  EE_PREPROC_JOIN(ISR2_,f)();            \
  EE_std_disableIRQ_nested();            \
  EE_decrement_IRQ_nesting_level();      \
  EE_std_after_IRQ_schedule();           \
}                                        \
void EE_PREPROC_JOIN(ISR2_,f) ( void )



#endif /* EE_CAX_IRQ_H__ */
