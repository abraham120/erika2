/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: Antonio Fiaschi
 * CVS: $Id: ee_hal.S,v 1.7 2006/01/24 10:44:02 pj Exp $
 */

#include "cpu/mpc5xx/inc/ee_compiler.h"
#include "cpu/mpc5xx/inc/ee_macro.h"

	.global	EE_mpc5_hal_ready2stacked
	.global	EE_mpc5_enableIRQ
	.global	EE_mpc5_disableIRQ
	.global EE_hal_endcycle_next_thread

	.global	EE_IRQ_nesting_level

#ifdef __MULTI__
	.global EE_mpc5_hal_stkchange
	.global EE_hal_endcycle_next_tos

#ifdef __IRQ_STACK_NEEDED__
        .global EE_mpc5_change_to_irq_tos
        .global EE_mpc5_change_from_irq_tos
#endif

#endif

	.global EE_mpc5_end_nested_primitive
	.global EE_mpc5_begin_nested_primitive

	
	// system TOS
#ifdef __MULTI__
	.extern	EE_mpc5_system_tos
	.extern	EE_mpc5_active_tos
#endif
	
	// kernel scheduler addresses 
	.extern	EE_thread_end_instance

	.data
	
// This variable contains the address of the new preempter thread,
// when the preemption check is done at the end of a thread.
//
// NOTE: This variable is modified when a thread ends (before
//       EE_thread_end_instance()) and its content is read when
//       EE_thread_end_instance() ends; during this period it is
//       important to disable interrupts in order to avoid nested
//       EE_thread_end_instance() calls.


	.type	EE_hal_endcycle_next_thread, @object
EE_hal_endcycle_next_thread:
	.long	0x00000000
	.size	EE_hal_endcycle_next_thread, . - EE_hal_endcycle_next_thread

//
// This variable contains the index of the new preempter thread TOS.
//

#ifdef __MULTI__
	.type	EE_hal_endcycle_next_tos, @object
EE_hal_endcycle_next_tos:
	.long	0x00000000
	.size	EE_hal_endcycle_next_tos, . - EE_hal_endcycle_next_tos

#ifdef __IRQ_STACK_NEEDED__
EE_mpc5_temp_tos:
	.word	0x00000000	// sys
#endif
#endif

// interrupt handler nesting
	.type	EE_IRQ_nesting_level, @object
EE_IRQ_nesting_level:
	.word	0x00000000	// it must be 0!!!
		
	.text
// 
// This code is called when we have to change the thread stack
// NOTE: r4 *MUST* contain tos_index, while r3 (the thread address)
// will be unchanged!!!
//
#ifdef __MULTI__
EE_mpc5_change_tos:	
	// if tos_index == EE_mpc5_active_tos then we do not have to
	// switch stack
	lis	r9, EE_mpc5_active_tos@ha
	lwz	r0, EE_mpc5_active_tos@l(r9)

	cmpw	r4, r0
	beqlr

	// r0 contains _EE_mpc5_active_tos_
	
	// Before changing the stack, we have to save the registers
	// that could be modified (i.e. all the registers that should
	// be preserved through function calls). Note that if there is
	// not the stack change, the system will behave like the
	// monostack version of the kernel
	addi	sp, sp, -72
#ifndef	DEBUG
	stmw	r14, 0(sp)	
#else
	stw	r14, 0(sp)
	stw	r15, 4(sp)
	stw	r16, 8(sp)
	stw	r17, 12(sp)
	stw	r18, 16(sp)
	stw	r19, 20(sp)
	stw	r20, 24(sp)
	stw	r21, 28(sp)
	stw	r22, 32(sp)
	stw	r23, 36(sp)
	stw	r24, 40(sp)
	stw	r25, 44(sp)
	stw	r26, 48(sp)
	stw	r27, 52(sp)
	stw	r28, 56(sp)
	stw	r29, 60(sp)
	stw	r30, 64(sp)
	stw	r31, 68(sp)
#endif
	
	//
	// Save current TOS
	//
	// r11 = &EE_mpc5_system_tos
	lis	r9, EE_mpc5_system_tos@ha
	la	r11, EE_mpc5_system_tos@l(r9)
	
	// r9 = & EE_mpc5_system_tos[EE_mpc5_active_tos].SYS_tos
	slwi 	r0, r0, 2
	add	r9, r11, r0

	// EE_mpc5_system_tos[EE_mpc5_active_tos].SYS_tos = sp_SYS
	stw	sp, 0(r9)
	
	//
	// New current TOS
	//
	// r11 = &EE_mpc5_system_tos
	// r9 = &EE_mpc5_system_tos[tos_index].SYS_tos
        slwi    r0, r4, 2
        add     r9, r11, r0

	// sp_SYS = EE_mpc5_system_tos[tos_index].SYS_tos
	lwz	sp, 0(r9)	
	
	// Update mpc5_active_tos (= tos_index)
	//
        lis     r9, EE_mpc5_active_tos@ha
	stw	r4, EE_mpc5_active_tos@l(9)

	// Here we have to restore the registers saved before the
	// stack previous change. If this is the first time we use the
	// current stack, restoring is useless... (see also inithal.c
	// into the directories erika/tests/mpc5xxxx)
#ifndef	DEBUG
 	lmw	r14, 0(sp)
#else
	lwz	r14, 0(sp)
	lwz	r15, 4(sp)
	lwz	r16, 8(sp)
	lwz	r17, 12(sp)
	lwz	r18, 16(sp)
	lwz	r19, 20(sp)
	lwz	r20, 24(sp)
	lwz	r21, 28(sp)
	lwz	r22, 32(sp)
	lwz	r23, 36(sp)
	lwz	r24, 40(sp)
	lwz	r25, 44(sp)
	lwz	r26, 48(sp)
	lwz	r27, 52(sp)
	lwz	r28, 56(sp)
	lwz	r29, 60(sp)
	lwz	r30, 64(sp)
	lwz	r31, 68(sp)
#endif
	addi	sp, sp, 72

	blr
#endif // __MULTI__

//
// MONO:  void EE_mpc5_hal_ready2stacked(ADDR thread_addr)
// MULTI: void EE_mpc5_hal_ready2stacked(ADDR thread_addr, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement preemption.
//
	.type	EE_mpc5_hal_ready2stacked, @function
EE_mpc5_hal_ready2stacked:
	// NOTE: in this function we not create the function stack frame!!
	
	// we have to save LR into the stack (EABI standard)
	stwu	sp, -8(sp)
	mflr	r0
	stw	r0, 12(sp)
1:	
#ifdef __MULTI__
	// (eventually) switch to the TOS of the new thread
	bl	EE_mpc5_change_tos
#endif
	
	//
	// Before calling the new thread we have to enable interrupts. 
	//
	mtspr	EIE, r0 //External Interrupt Enabling

	// jump to the preempter thread (r3 = first parameter)
	mtlr	r3
	
	blrl	

	// NOTE: we have to disable interrupts here before calling
	// EE_thread_end_instance() because it is a primitive
	mtspr	EID, r0 //External Interrupt Disabling
	
	// call the scheduler 
	bl	EE_thread_end_instance

	// note that interrupts are disabled here
	
	//
	// if EE_hal_endcycle_next_thread == 0
	//   then wake up the preempted thread
	//   (EE_mpc5_hal_endcycle_stacked executed)
	//
	// if EE_hal_endcycle_next_thread != 0
	//   then activate a new thread
	//   (EE_mpc5_hal_endcycle_ready executed)
	//
#ifdef __MULTI__
	lis	r9, EE_hal_endcycle_next_tos@ha
	lwz	r4, EE_hal_endcycle_next_tos@l(r9)
#endif
	
	lis	r9, EE_hal_endcycle_next_thread@ha
	lwz	r3, EE_hal_endcycle_next_thread@l(r9)
	
	cmpwi	r3, 0
	bne	1b

	// (eventually) switch to the TOS of the preempted thread
#ifdef __MULTI__
	bl	EE_mpc5_change_tos
#endif
	
	// Keep interrupts disabled !!!
	
	//
	// return to the interrupted thread
	//
	lwz	r0, 12(sp)
	mtlr	r0
	addi	sp, sp, 8
	blr
		
//	.size	EE_mpc5_hal_IRQ_ready, . - EE_mpc5_hal_IRQ_ready
	.size	EE_mpc5_hal_ready2stacked, . - EE_mpc5_hal_ready2stacked


#ifdef __MULTI__

//
// MONO:  not defined
// MULTI: void EE_mpc5_hal_stkchange(EE_UREG 0, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement a blocking
// synchronization primitive.
//
	.type	EE_mpc5_hal_stkchange, @function
EE_mpc5_hal_stkchange:	
	
	// Mk: saving lr here and restoring it after EE_mpc5_change_tos is mandatory, in order to
	// save lr of the preempted thread and to restore lr of the preempter thread
	//	from their respective stacks!
	// NOTE: a row (a word) of stack frame is blank!! This is because the EABI standard say that stack 
	//	address must be a multiple of 4 !!
	stwu	sp, -16(sp)
	stw	r0, 8(sp)
	mflr	r0
	stw	r0, 18(sp) //Under EABI standard

	// switch to the TOS of the new thread
	bl	EE_mpc5_change_tos

	// now the stack is changed, and we need to return to the interrupted thread!
	lwz	r0, 18(sp)
	mtlr	r0
	lwz	r0, 8(sp)
	addi	sp, sp, 16
	blr
	.size	EE_mpc5_hal_stkchange, . - EE_mpc5_hal_stkchange

#endif		

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
//
EE_mpc5_change_to_irq_tos:
	lis	r9, EE_mpc5_temp_tos@ha
	stw	sp, EE_mpc5_temp_tos@l(r9)

	lis	r9, EE_mpc5_IRQ_tos@ha
	lwz	sp, EE_mpc5_IRQ_tos@l(r9)

	blr
	.size	EE_mpc5_change_to_irq_tos, . - EE_mpc5_change_to_irq_tos

//
EE_mpc5_change_from_irq_tos:
	lis	r9, EE_mpc5_temp_tos@ha
	lwz	sp, EE_mpc5_temp_tos@l(r9)

	blr
	.size	EE_mpc5_change_from_irq_tos, . - EE_mpc5_change_from_irq_tos
#endif	//__IRQ_STACK_NEEDED__
#endif	//__MULTI__

	.end
