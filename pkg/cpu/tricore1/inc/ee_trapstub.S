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
#ifndef __EE_TC1_TRAP_STUB_S__
#define __EE_TC1_TRAP_STUB_S__

#define __EECFG_THIS_IS_ASSEMBLER__

#include "cpu/tricore1/inc/ee_trap.h"

#ifdef __GNUC__

        .extern     EE_trap_default_tsr, STT_FUNC, 0

/* Trap vector table:
 *
 * Eight 4 word wide entries representing trap classes.
 * The TIN (D15) distinguishes the specific trap type.
 */


/* Defines the prologue of a trap table
 *
 */
.macro      BEGIN_TRAP_TABLE

        .section    .traptab, "awx", @progbits
        .globl      EE_trap_vector
        .align      8
        .set        EE_trap_vector, .

.endm


/* Defines the epilogue of a trap table
 *
 */
.macro      END_TRAP_TABLE

#ifdef DEBUG
        EE_TRAP_DEFAULT_FILL EE_MAX_TSR
#endif
        .size       EE_trap_vector, . - EE_trap_vector
        .previous

.endm


/* Provide default stubs for undefined traps up to but not
 * including trap 'num'
 */
.macro      EE_TRAP_DEFAULT_FILL num

        .ifndef     EE_previous_trap
        .set        EE_previous_trap, 0
        .endif

        .rept       \num - EE_previous_trap

        svlcx
        movh.a      %a15, HI:EE_trap_default_tsr
        lea         %a15, [%a15] LO:EE_trap_default_tsr
        ji          %a15

        .align      5
        .endr
        .set        EE_previous_trap, \num + 1

.endm


/* Trap vector stub
 *
 */
.macro      EE_TRAP_STUB num fun=EE_trap_default_tsr

        EE_TRAP_DEFAULT_FILL \num

        .globl      EE_trap_\num
EE_trap_\num:

        svlcx
        movh.a      %a15, HI:EE_tsr_\fun
        lea         %a15, [%a15] LO:EE_tsr_\fun
        mov         %d4, %d15 /* Set first function argument to TIN */
        jli         %a15 /* Invoke handler */
        rslcx /* Restore lower context and A11 */
        nop /* CPU_TC.069 */
        rfe /* Return From Exception */

        .if         . - EE_trap_\num > 32
        .err /* 32 byte limit exceeded */
        .endif

        .size       EE_trap_\num, . - EE_trap_\num
        .align      5
.endm


#else /* __GNUC__  */

#error Compiler not supported.

#endif /* __GNUC__ */

#endif
