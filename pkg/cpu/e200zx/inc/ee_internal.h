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
 * Derived from cpu/mico32/inc/ee_internal.h
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#ifndef PKG_CPU_E200ZX_INC_EE_INTERNAL_H
#define PKG_CPU_E200ZX_INC_EE_INTERNAL_H

#include "cpu/e200zx/inc/ee_cpu.h"

/*
 * Generic Primitives
 */

#include "cpu/common/inc/ee_primitives.h"

/* Common Context Handling implementation */
#include "cpu/common/inc/ee_context.h"


/*************************************************************************
                            System stack
 *************************************************************************/
#ifdef USE_PRAGMAS
#pragma section PRAGMA_SECTION_BEGIN_SYS_STACK
extern EE_STACK_T EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];
#pragma section PRAGMA_SECTION_END_SYS_STACK
#else
extern EE_STACK_T EE_STACK_ATTRIB EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];
#endif


/*************************************************************************
                            System startup
 *************************************************************************/

#define OO_CPU_HAS_STARTOS_ROUTINE

/* If system timer is defined with a device. I have to initialize it */
#if (defined(ENABLE_SYSTEM_TIMER)) && (defined(EE_SYSTEM_TIMER_DEVICE))
void EE_initialize_system_timer(void);
#else /* ENABLE_SYSTEM_TIMER && EE_SYSTEM_TIMER_DEVICE */
__INLINE__ void __ALWAYS_INLINE__ EE_initialize_system_timer(void) {}
#endif /* ENABLE_SYSTEM_TIMER && EE_SYSTEM_TIMER_DEVICE */

#if (defined(__MSRP__)) \
  || ( (defined(__EE_MEMORY_PROTECTION__)) \
       && ( (defined(__OO_BCC1__)) || (defined(__OO_BCC2__))	\
	    || (defined(__OO_ECC1__)) || (defined(__OO_ECC2__)) ))
/* On multi-core this is used also as a synchronization point */
EE_TYPEBOOL EE_cpu_startos(void);

#else /* if __MSRP__ or __EE_MEMORY_PROTECTION__ ... */
/* Nothing to do but initializing system timer */
__INLINE__ EE_TYPEBOOL __ALWAYS_INLINE__ EE_cpu_startos(void);
__INLINE__ EE_TYPEBOOL __ALWAYS_INLINE__ EE_cpu_startos(void)
{
  EE_initialize_system_timer();
  return EE_FALSE;
}

#endif /* else if __MSRP__ || __EE_MEMORY_PROTECTION__ ... */

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
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG endflags)
{
	EE_hal_resumeIRQ(endflags);
}

/* Used to get internal CPU priority. */
__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_hal_get_int_prio(void)
{
	return EE_e200zx_get_int_prio();
}

	/*
		Used to set internal CPU priority.
	*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_int_prio(EE_TYPEISR2PRIO prio)
{
	EE_TYPEISR2PRIO prev_prio = EE_e200zx_get_int_prio();
	/* I check for equality because changing INTC_CPR require alot of
		 synchronization */
	if(prev_prio != prio) {
		EE_e200zx_set_int_prio(prio);
	}
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
	EE_TYPEISR2PRIO prev_prio = EE_e200zx_get_int_prio();
	if(prev_prio < new_prio) {
		EE_e200zx_set_int_prio(new_prio);
	}
	return flag;
}

	/*
		Used to check if interrupt priority is less tha new priority to
		set.
	*/
__INLINE__ EE_BIT __ALWAYS_INLINE__ EE_hal_check_int_prio_if_higher(
		EE_TYPEISR2PRIO new_prio){
	EE_TYPEISR2PRIO actual_prio = EE_e200zx_get_int_prio();
	return (actual_prio > new_prio)?1U:0U;
}

/*******************************************************************************
                      Special Stacks Data Structures
 ******************************************************************************/
#if (defined(__IRQ_STACK_NEEDED__))
extern struct EE_TOS EE_e200z7_IRQ_tos;
#endif /* __IRQ_STACK_NEEDED__ */

/* typically called at the end of an interrupt by kernel */
#define EE_hal_IRQ_stacked  EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready    EE_hal_endcycle_ready

/*
 * OO TerminateTask related stuffs
 */

#if (defined(__OO_BCC1__)) || (defined(__OO_BCC2__)) || (defined(__OO_ECC1__)) \
  || (defined(__OO_ECC2__))

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

#ifdef __ASM_CONVERTED_TO_C__
/* Prototypes are included only for Erika source files, but they could be useful
 * also for user C code.  In that case, a further condition should be added. */
/* Assembly functions */
void FlashConfig(void);
void init_regs();
void intc_setup(void);
void cpu_setup(void);
void sram_setup(void);
void save_registers(void);
void restore_all_return(void);
void ivor_setup(void);
void EE_e200zx_external_input_handler(void);
void EE_e200zx_decrementer_handler(void);
void EE_e200zx_fixed_intv_handler(void);
/* Symbols provided by the linker script */
extern int ee_load_ram;
extern int ee_sbss;
extern int ee_sdata;
extern int ee_ebss;
extern int _SDA_BASE_;
extern int _SDA2_BASE_;
extern int ee_sstack, ee_estack;
extern int isram_base;
extern int isram_len;
extern int ee_ssbss2;
extern int ee_esbss2;
#endif


#endif /* __INCLUDE_E200ZX_INTERNAL_H__ */
