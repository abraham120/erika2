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
#ifndef __EE_TC1_INT_STUB_S__
#define __EE_TC1_INT_STUB_S__

#define __EECFG_THIS_IS_ASSEMBLER__

#include "cpu/tricore1/inc/ee_int.h"

#ifdef __GNUC__

        .extern     EE_int_default_isr, STT_FUNC, 0
        .extern     EE_IRQ_nesting_level, STT_FUNC, 0

/* Interrupt vector table:
 *
 * The table consists of N 8 word wide entries with 0 < N < 255.
 * Each entry corresponds to an interrupt priority with 0 being the
 * top priority handler. The alignment must be 4096 byte. */


/* Defines the prologue for a vector table
 *
 */
.macro      BEGIN_VECTOR_TABLE

        .section    .inttab, "awx", @progbits
        .globl      EE_int_vector
        .align      13
        .set        EE_int_vector, .

.endm


/* Defines the epilogue for a vector table
 *
 */
.macro      END_VECTOR_TABLE

        .set        EE_int_vector_size, . - EE_int_vector
        .size       EE_int_vector, . - EE_int_vector
        .previous

.endm


/* Provide default stubs for undefined vectors
 *
 * All vectors between vector 'num' and the previously defined one
 * is filled with default entries. These invoke some default handler.
 */
.macro      EE_INT_DEFAULT_FILL num

        .ifndef     EE_previous_vector
        .set        EE_previous_vector, 0
        .endif

        .rept       \num - EE_previous_vector

        svlcx
        movh.a      %a15, HI:EE_int_default_isr
        lea         %a15, [%a15] LO:EE_int_default_isr
        ji          %a15

        .align      5
        .endr
        .set        EE_previous_vector, \num + 1

.endm


/* Interrupt vector stub (ISR1)
 *
 * As opposed to ISR2 stubs, we do not counter the nesting level, nor
 * do we explicitly enable interrrupts before executing the user ISR.
 * Note that CCPN is not reset, which means enabling interrupts
 * potentially leads to uncontrolled results. Alternatively, use BISR
 * instead of just SVLCX.
 */
.macro      EE_ISR1_STUB num fun=EE_int_default_isr

        EE_INT_DEFAULT_FILL \num

        .globl      EE_int_\num
EE_int_\num:

        svlcx
        movh.a      %a15, HI:EE_isr1_\fun
        lea         %a15, [%a15] LO:EE_isr1_\fun
        ji          %a15

        .if         . - EE_int_\num > 32
        .err /* 32 byte limit exceeded */
        .endif

/* ISR return directly */
        .size       EE_int_\num, . - EE_int_\num
        .align      5
.endm


/* Interrupt vector stub (ISR2)
 *
 *
 */
.macro      EE_ISR2_STUB num fun=EE_int_default_isr

        EE_INT_DEFAULT_FILL \num

        .globl      EE_int_\num
EE_int_\num:

        movh.a      %a12, HI:EE_IRQ_nesting_level
        ld.w        %d8, [%a12] LO:EE_IRQ_nesting_level
#ifdef __ALLOW_NESTED_IRQ__

        add         %d8, 1 /* increase nesting_level */

/* We make use of PSW.IS to switch to the IRQ stack
         * (see initialization routine below) */

        st.w        [%a12] LO:EE_IRQ_nesting_level, %d8 /* Store nesting_level */
        bisr        \num /* Save LCTX, A11, sets ICR.CCPN to N, sets ICR.IE */

#else /* __ALLOW_NESTED_IRQ__ */

        mov         %d8, 1 /* nesting_level = 1 */
        st.w        [%a12] LO:EE_IRQ_nesting_level, %d8 /* Store nesting_level */

/* Enables interrupts. We set this quite high to prevent nesting. */
        bisr        EE_int_vector_size/32

#endif /* __ALLOW_NESTED_IRQ__ */

        movh.a      %a15, HI:EE_isr2_stub_\fun
        lea         %a15, [%a15] LO:EE_isr2_stub_\fun
        ji          %a15
/* ISR return directly */

        .if         . - EE_int_\num > 32
        .err /* 32 byte limit exceeded */
        .endif

        .size EE_int_\num, . - EE_int_\num
        .align 5
.endm


#else /* __GNUC__  */

#error Compiler not supported.

#endif /* __GNUC__ */

#endif
