/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file ee_debug.h
	@brief  Some debugging facilities.  The content of this file is strictly connected
	with the internals of the kernel and the HAL, so it is likely to change with
	new releases of the OS.  It is meant to debug the HAL, the kernel, and to
	help in finding some nasty bugs; it is not meant for generale use.
	@author Bernardo  Dal Seno
	@date 2010
*/  
 

#ifndef __INCLUDE_MICO32_DEBUG_H__
#define __INCLUDE_MICO32_DEBUG_H__

#include <cpu/mico32/inc/ee_internal.h>

/*
 * Stack debugging
 */
#ifdef DEBUG_STACK

/**
 * This value is used as a canary (guard memory location) for stack overflow
 * detection.  This value has three interesting properties, which tend to cause
 * an exception if it's read and used by the processor:
 * 1. It's an invalid instruction
 * 2. It's a misaligned address
 * 3. It's an address in the I/O region, not suitable for code, and likely
 * invalid anyway
 * The canary is written before and after the actual stack space.  If it is
 * overwritten, you know that that the stack has been exceeded.
 */
#define MICO32_STACK_CANARY     0xabadbeef
/*
 * Value to fill uninitialized memory.  It has the same properties of the
 * canary.
 */
#define MICO32_FILL_MEMORY      0xce11f00d

#define PRE_STACK_CANARY_LEN    22  /* Enough to invalidate all caller-saved
                                     * registers */
#define POST_STACK_CANARY_LEN    4

/* Used as the initaliaziation value of the private stacks in `eccgc.c'.  Write
 * the canary before and after the actual stack, and fill it with garbage.  C99
 * syntax and `...' GCC extension are used. */
#define MICO32_STACK_INIT(stack_len) {                                  \
    [0 ... POST_STACK_CANARY_LEN - 1] = MICO32_STACK_CANARY,            \
        [POST_STACK_CANARY_LEN ... stack_len + POST_STACK_CANARY_LEN - 1] \
        = MICO32_FILL_MEMORY,                                           \
        [stack_len + POST_STACK_CANARY_LEN ...                          \
            stack_len + PRE_STACK_CANARY_LEN + POST_STACK_CANARY_LEN - 1] \
        = MICO32_STACK_CANARY                                           \
        }
#define MICO32_INIT_TOS_OFFSET (1-POST_STACK_CANARY_LEN)
#define MICO32_STACK_DEBUG_LEN (PRE_STACK_CANARY_LEN+POST_STACK_CANARY_LEN)


/**
 * Check that the canary below the stack is intact.  `base_tos' is the initial
 * value of the top-of-stack.  Return 0 if the canary is ok, and the offset (as
 * a positive number, measured in bytes) of the first corrupted location
 * otherwise.
 */
__INLINE__ int __ALWAYS_INLINE__ check_pre_stack_canary(EE_ADDR base_tos)
{
    int i;
    int *addr = (int *)base_tos;
    for (i = 1; i <= PRE_STACK_CANARY_LEN; ++i)
        if (addr[i] != MICO32_STACK_CANARY)
            return i*4;
    return 0;
}


/**
 * Check that the canaries before all stacks are intact.  Return 0 if the check
 * is passed, or a the index of the stack that failed the test.  The first stack
 * (index 0) is the system stack and has no canary, so it's not checked.  An
 * underflow of the system stack should cause a bus error anyway.
 */
__INLINE__ int __ALWAYS_INLINE__ check_all_pre_stack_canaries(
    EE_ADDR base_toses[], int num_toses)
{
    int i;
    /* Skip the system stack */
    for (i = 1; i < num_toses; ++i) {
        if (0 != check_pre_stack_canary(base_toses[i]))
            return i;
    }
    return 0;
}


#endif /* DEBUG_STACK */

#ifdef __MULTI__

/**
 * Return the current stack index (according to the HAL).
 */
__INLINE__ EE_UREG __ALWAYS_INLINE__ get_current_tos_index()
{
    return EE_mico32_active_tos;
}


/**
 * Return the index of the stack used for the given task.
 */
__INLINE__ EE_UREG __ALWAYS_INLINE__ get_tos_index_for_task(EE_TID tid)
{
    return EE_std_thread_tos[tid+1];
}


/**
 * Return the index of the stack more likely to be the current one.  If the
 * current stack pointer is corrupted, the result is unreliable; it could be
 * `-1' or any stack index.
 */
__INLINE__ EE_UREG __ALWAYS_INLINE__ get_most_likely_tos_index(
    EE_ADDR base_toses[], int num_toses)
{
    EE_ADDR sp; /* Current stack pointer */
    EE_UREG tosind = (EE_UREG)-1;
    EE_ADDR tos = (EE_ADDR)-1;
    int i;
    asm ("mv %0,sp" : "=r" (sp) );
    /* SP is inside the stack whose base top-of-stack is the smallest among
     * those above SP */
    for (i = 0; i < num_toses; ++i)
        if (sp <= base_toses[i] && base_toses[i] < tos) {
            tosind = i;
            tos = base_toses[i];
        }
    return tosind;
}


/**
 * Check that all stacks are empty, by comparing the current top-of-stack values
 * with those given (which should have been obtained through get_base_toses()).
 * It must be called from main() (when no other task is running).  Return 0 if
 * the check is passed, or the index of the stack that failed the test.  The
 * first stack (index 0) should be the current one and it's not checked.
 */
__INLINE__ int __ALWAYS_INLINE__ check_toses(
    EE_ADDR base_toses[], int num_toses)
{
    int i;
    for (i = 1; i < num_toses; ++i)
        if (base_toses[i] != EE_mico32_system_tos[i].SYS_tos)
            return i;
    return 0;
}


/**
 * Retrieve the initial top-of-stack value.  Must be called from main() before
 * any task activation (or StartOS).
 */
__INLINE__ int __ALWAYS_INLINE__ get_base_toses(
    EE_ADDR base_toses[EE_MAX_TASK+1] )
{
    int i, max_stack = 0;
    extern int _fstack;     /* Address defined in the linker script */
    for (i = 0; i < EE_MAX_TASK+1; ++i)
        if (EE_std_thread_tos[i] > max_stack) {
            max_stack = EE_std_thread_tos[i];
            base_toses[max_stack] = EE_mico32_system_tos[max_stack].SYS_tos;
        }
    base_toses[0] = (EE_ADDR)&_fstack;
    return max_stack+1;
}

#endif /* __MULTI__ */


#endif /* __INCLUDE_MICO32_DEBUG_H__ */
