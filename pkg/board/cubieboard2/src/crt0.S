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


#include "cpu/cortex_ax_xenpv/inc/ee_cax_defs.h"

.section .crt0
.global _crt_section
_crt_section:
@ load stack
	@ Interrupt stack (IRQ)
        mov     r1, #I_bit | F_bit | Mode_IRQ
        msr     cpsr_c, r1
        ldr	sp, =EE_irq_stack_end

	@ Abort stack (ABT)
        mov     r1, #I_bit | F_bit | Mode_ABT
        msr     cpsr_c, r1
        ldr     sp, =EE_abt_stack_end

	@ Fast interrupt stack (FIQ)
	mov     r1, #I_bit | F_bit | Mode_FIQ
	msr     cpsr_c, r1
	ldr     sp, =EE_fiq_stack_end

        @ Supervisor stack (SWI)
        mov     r1, #I_bit | F_bit | Mode_SVC
        msr     cpsr_c, r1
        ldr     sp, =EE_svc_stack_end

        @ System stack (default running mode)
	mov     r1, #I_bit | F_bit | Mode_SYS
        msr     cpsr_c, r1
        ldr     sp, =EE_stack_end

#ifdef __OO_ORTI_STACK__
        ldr     r0, =EE_stack_start
        ldr     r1, =EE_stack_end
        ldr     r2, =0xa5a5a5a5
_orti_stack_fill:
        str     r2, [r1], #4
        cmp     r1, r0;
        bcc     _orti_stack_fill
#endif

        ldr     r0, =__bss_start__
        ldr     r1, =__bss_end__
        mov     r2, #0
bss_loop:
        str     r2, [r0]
        cmp     r0, r1
        add     r0, r0, #4
        bne     bss_loop

#if 0
	mov     lr, pc
	ldr     pc, =EE_gic_dist_init
#endif
	ldr	pc, =main
.end
