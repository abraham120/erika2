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

.section .vectors,"ax"

.global pabortInterrupt
.global abortInterrupt
.global EE_IRQ_handler
.global fiqInterrupt

.global __reboot
.global __undefined_handler
.global __SVC_handler
.global __pabort_handler
.global __abort_handler
.global __addrexception_handler
/* .global __irq_handler */
.global __fiq_handler

.global _vector_table
_vector_table:
	ldr 	pc, =__reboot
	ldr 	pc, =__undefined_handler
	ldr 	pc, =__SVC_handler
	ldr 	pc, =__pabort_handler
	ldr 	pc, =__abort_handler
	ldr 	pc, =__addrexception_handler
	ldr 	pc, =EE_IRQ_handler
	ldr 	pc, =__fiq_handler

#if 0
__irq_handler:
	.word EE_IRQ_handler
/*	b 	EE_IRQ_handler */
	stmdb 	sp!, {r0-r3, r12, lr} 	/* save state from compiled code */
	bl 	EE_IRQ_handler
	ldmia 	sp!, {r0-r3, r12, lr} 	/* restore state from compiled code */
	subs 	pc, lr, #4 		/* adjust return */
#endif

__fiq_handler:
	stmdb 	sp!, {r0-r3, r12, lr} 	/* save state from compiled code */
	bl 	EE_FIQ_handler
	ldmia 	sp!, {r0-r3, r12, lr} 	/* restore state from compiled code */
	subs 	pc, lr, #4 		/* adjust return */

__abort_handler:
	stmdb 	sp!, {r0-r3, r12, lr} 	/* save state from compiled code */
	bl 	EE_abortInterrupt
	ldmia 	sp!, {r0-r3, r12, lr} 	/* restore state from compiled code */
	subs 	pc, lr, #4 		/* adjust return */


__pabort_handler:
	stmdb 	sp!, {r0-r3, r12, lr} 	/* save state from compiled code */
	bl 	EE_pabortInterrupt
	ldmia 	sp!, {r0-r3, r12, lr} 	/* restore state from compiled code */
	subs 	pc, lr, #4 		/* adjust return */


__SVC_handler:
	b 	__SVC_handler

__undefined_handler:
	b 	__reboot

__addrexception_handler:
	b 	__addrexception_handler

__reboot:
	b 	__reboot

.end
