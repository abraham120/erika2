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
#include "cpu/cortex_ax_xenpv/inc/ee_gic_maps.h"

.extern	EE_IRQ_nesting_level

.global EE_IRQ_handler
.type	EE_IRQ_handler, #function
EE_IRQ_handler:
	sub 	lr, lr, #4
	/* saves old r0  r1 regs and irq lr inside irq stack */


	stmfd 	sp!, {r0-r1, lr}
	mrs 	r0, spsr
	/* saves previous status register (spsr) */
	stmfd 	sp!, {r0}
	mov 	r1, sp
	/* clean IRQ stack */
	add 	sp, sp, #16

	/* enter SYS mode */
	mov 	r0, #Mode_SYS | I_bit
	msr 	cpsr_c, r0

	/* copy IRQ stack to Mode_SYS stack */
	stmfd 	sp!, {r2-r3, r12, lr}
	ldmfd 	r1, {r0, r2, r3, r12}
	stmfd 	sp!, {r0, r2, r3, r12}

	/* gets the irq ID*/
	ldr 	r3, =(EE_IC_INTERFACES_BASE_ADDR + EE_GIC_CPU_INTACK)
	ldr 	r2, [r3]
	ldr 	r3, =(EE_GIC_INTID_MASK)
	/* r2=intID */
	and 	r2, r2, r3
/* intID must be preserved */
	stmfd 	sp!, {r2}

#if 0 //NEST

#ifdef __ALLOW_NESTED_IRQ__
	/* increase the nesting level */
	ldr 	r1, =EE_IRQ_nesting_level
	ldr 	r3, [r1]
	add 	r3, r3, #1
	str 	r3, [r1]

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	/* TODO */
#endif
#endif
	/* now we can re-enable interrupts */
	mov 	r1, #Mode_SYS
	msr 	cpsr_c, r1

#else /* ! __ALLOW_NESTED_IRQ__ */

	/* nesting level = 1 */
	ldr 	r1, =EE_IRQ_nesting_level
	mov 	r3, #1
	str 	r3, [r1]
#if 0
	/* now we can switch to SYS mode */
	mov 	r1, #Mode_SYS | I_bit
	msr 	cpsr_c, r1
#endif
#endif /* __ALLOW_NESTED_IRQ__ */
#endif  //NEST

	/* jump to the handler */
	ldr 	r0, =EE_IRQ_HANDLER_TABLE
	mov 	r3, r2, lsl #2
	ldr 	r0, [r0, r3]
	mov 	lr, pc
	mov 	pc, r0

#if 0 //NEST
#ifdef __ALLOW_NESTED_IRQ__
        /* we can disable interrupts (_only_ IRQ, _not_ FIQ) */
        mov 	r0, #Mode_SYS | I_bit
        msr 	cpsr_c, r0

        /* decrease the nesting level */
        ldr 	r0, =EE_IRQ_nesting_level
        ldr 	r1, [r0]
        sub 	r1, r1, #1
        str 	r1, [r0]

        /* is this the first handler instance? */
        cmp 	r1, #0

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	/*TODO based on arm7tdmi */
        /* if this is the first handler instance then we have to
         * change stack
	 */
        ldreq 	r0, =EE_arm7_temp_tos
        ldreq 	sp, [r0]
#endif
#endif

        /* call the scheduler only if this is the first instance */
        bne 	theend

#else  /* ! __ALLOW_NESTED_IRQ__ */

        /* nesting level = 0 */
        ldr 	r0, =EE_IRQ_nesting_level
        mov 	r1, #0
        str 	r1, [r0]

#endif /* __ALLOW_NESTED_IRQ__ */
#endif //NEST


#if 0 //next th
        /* ---------------------------------------------------------------
         * call the scheduler
	 */
	/* call the scheduler only if this is the first instance */
	/* same as EE_std_after_IRQ_schedule */
        bl 	EE_IRQ_end_instance

        /* check if the scheduler has called IRQ_ready or IRQ_stacked */
#ifdef __MULTI__
        ldr 	r3, =EE_hal_endcycle_next_tos
        ldr 	r1, [r3]
#endif

        ldr 	r3, =EE_std_endcycle_next_tid
        ldr 	r0, [r3]

/***********/
	ldr 	r3, =0x80000000
//	mov	r1, #0
_l1:
//	ldr 	r3, =0x80000000 //*

	tst 	r0, r3
//	ldr 	r3, =0x1080200C //*
//	add 	r1, r1, #1  //*
//	str 	r1, [r3]
	bne     _out
        bl 	EE_std_run_task_code
	b 	_l1
_out:
#endif //next th

/**********/


#if 0
        cmp 	r0, #0
        /* now we have to call two different functions */

#ifdef __MULTI__
	/*TODO:*/
        add 	lr, pc, #4                       // that is, theend
        bne 	EE_arm7_hal_ready2stacked
        beq 	EE_arm7_hal_stkchange
#else
	/* TODO */
        blne 	EE_cortex_ax_hal_ready2stacked
#endif

#endif

        /* ---------------------------------------------------------------
         * end of the interrupt */
theend:
	/* EOI r2 is the irq ID */
	/* EOI is a priority drop for IRQ in GIC */
        ldmfd 	sp!, {r2}
	ldr 	r3, =(EE_IC_INTERFACES_BASE_ADDR + EE_GIC_CPU_EOI)
	str 	r2, [r3]

        mov 	r1, sp
        add 	sp, sp, #16
        ldmfd 	sp!, {r2-r3, r12, lr}

        /* switch to IRQ mode */
        mov 	r0, #Mode_IRQ | I_bit
        msr 	cpsr_c, r0

        ldmfd 	r1!, {r0}
        msr 	spsr, r0
        ldmfd 	r1, {r0-r1, pc}^

        .size   EE_IRQ_handler, . - EE_IRQ_handler
.global	EE_FIQ_handler
.type	EE_FIQ_handler, #function
EE_FIQ_handler:
	bx 	lr

.global	EE_abortInterrupt
.type	EE_abortInterrupt, #function
EE_abortInterrupt:
	b	.

.global	EE_pabortInterrupt
.type	EE_pabortInterrupt, #function
EE_pabortInterrupt:
	b	.
