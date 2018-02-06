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

#define __EECFG_THIS_IS_ASSEMBLER__

#include "cpu/tricore1/inc/ee_int.h"

/* Could be defined in eecfg.h to reduce arbitration cycles */
#ifndef EE_MAX_ISR
#define EE_MAX_ISR 255
#endif

        
#ifdef __GNUC__

        .extern EE_wdt_lock, STT_FUNC, 0
        .extern EE_wdt_unlock, STT_FUNC, 0
        .extern EE_int_vector, STT_FUNC, 0

/* Default interupt handler for both ISR1 and ISR2
 *
 */
        .section .text
        .type   EE_int_default_isr, @function
        .globl EE_int_default_isr
EE_int_default_isr:

        rslcx /* Restore lower context and A11 */
        nop   /* Workaround for CPU_TC.069 */
        rfe   /* Return From Exception */

        .size EE_int_default_isr, . - EE_int_default_isr
        .previous

        
/* Sets this table as the interrupt vector
 *
 * NOTE: On GCC this is invoked automatically.
 *
 */
        .section .text
        .globl EE_init_int_vector
        .type EE_init_int_vector, @function
EE_init_int_vector:

        disable
        call EE_wdt_unlock
#if defined (__INT__)
        movh %d8, HI:EE_int_vector
        addi %d8, %d8, LO:EE_int_vector
        mtcr $biv, %d8 /* Table must be properly aligned */
        isync
#endif

#if defined (__MULTI__) && defined(__IRQ_STACK_NEEDED__)
        /* Define an ISR stack location. */
        movh.a %a12, HI:EE_tc1_IRQ_tos
        ld.w   %d8, [%a12] LO:EE_tc1_IRQ_tos
        mtcr   $isp, %d8
        isync        
#endif

        /* Set PSW.IS in all preceeding CSAs. */
        mfcr %d14, $psw
#if defined (__MULTI__) && defined(__IRQ_STACK_NEEDED__)
        jz.t %d14, 9, 3f   /* Skip next steps if PSW.IS = 0 */
#else
        jnz.t %d14, 9, 3f  /* Skip next steps if PSW.IS = 1 */
#endif
        /* Otherwise, traverse CSA list resetting PSW.IS: */
        mfcr    %d15,$pcxi          /* Obtain previous context */
        jz      %d15, 1f            /* Give up when there is no previous CSA */
        movh.a  %a3, HI:__CSA_BEGIN /* CSA space base address */
        lea     %a3, [%a3] LO:__CSA_BEGIN
2:      extr.u  %d0,%d15,16,4     /* Extract PCXS (segment) from link */
        mov     %d1,0             /* Base value for insert operation */
        sha     %d0,%d0,28        /* Move PCXS in place to form valid address */
        insert  %d1,%d1,%d15,6,16 /* Extract PCXO */
        addsc.a %a15,%a3,%d1,0    /* &__CSA_BEGIN[PCXS] (2^6 byte per CSA) */
        or      %d0,%d1           /* PCXS | <in-segment address>  */
        mov.a   %a2,%d0           /* Make address accessible */
        ld.w    %d15,[%a2]4       /* Load PSW from CSA */
#if defined (__MULTI__) && defined(__IRQ_STACK_NEEDED__)
        insert      %d15,%d15,0,9,1 /* Clear PSW.IS */
#else
        insert      %d15,%d15,1,9,1 /* Set PSW.IS */
#endif
        st.w [%a2]4,%d15          /* Store back */
        ld.w %d15,[%a15]0         /* Load PCX from CSA */
        jnz %d15, 2b              /* Repeat or exit */
1:      dsync                     /* Make sure changes apply */
3:      nop

        /* Minimize the number of arbitration cycles */
        /* (Sets CONECYC to 0, which should be already the case) */
       .if EE_MAX_ISR > 63
        mov %d8, 0b00
       .elseif EE_MAX_ISR > 15
        mov %d8, 0b01
       .elseif EE_MAX_ISR > 3
        mov %d8, 0b10
       .else
        mov %d8, 0b11
       .endif
        sh %d8, %d8, 24
        mtcr $icr, %d8
        isync

        call EE_wdt_lock
        enable
        ret

        .size EE_init_int_vector, . - EE_init_int_vector
        .previous

#else /* __GNUC__  */

#error Compiler not supported.

#endif /* __GNUC__ */

