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
 * Author:2004 Paolo Gai
 * CVS: $Id: ee_hal.S,v 1.11 2008/10/06 21:25:05 pj Exp $
 */

#include "cpu/nios2/inc/ee_compiler.h"

/* the define is needed for binary distributions */
#define __EECFG_THIS_IS_ASSEMBLER__
#include "eecfg.h"
	
	/*
	 * Explicitly allow the use of r1 (the assembler temporary register)
	 */
	.set noat
	
	.global	EE_nios2_hal_ready2stacked
	.global EE_hal_endcycle_next_thread

#ifdef __MULTI__
	.global EE_nios2_hal_stkchange
	.global EE_hal_endcycle_next_tos
	
#ifdef __IRQ_STACK_NEEDED__
	.global	EE_nios2_change_to_irq_tos
	.global	EE_nios2_change_from_irq_tos
#endif
	
#endif


	
	// system TOS
#ifdef __MULTI__
	.extern	EE_hal_system_tos
	.extern	EE_hal_active_tos
#endif
	
	// kernel scheduler addresses 
	.extern	EE_thread_end_instance


	.section	.sbss
	.align	2
	
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
	.zero 4
	.size	EE_hal_endcycle_next_thread, . - EE_hal_endcycle_next_thread

//
// This variable contains the index of the new preempter thread TOS.
//
#ifdef __MULTI__
	.type	EE_hal_endcycle_next_tos, @object
EE_hal_endcycle_next_tos:
	.zero 4
	.size	EE_hal_endcycle_next_tos, . - EE_hal_endcycle_next_tos
#endif


// this variable is used by EE_nios2_change_to_irq_tos and
// EE_nios2_change_from_irq_tos to store the current thread TOS
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	.global EE_nios2_temp_tos
	.type	EE_nios2_temp_tos, @object
EE_nios2_temp_tos:	
	.zero 4
#endif
#endif

// interrupt handlers nesting
#ifdef __ALLOW_NESTED_IRQ__
	.global	EE_IRQ_nesting_level
	.type	EE_IRQ_nesting_level, @object
EE_IRQ_nesting_level:	
	.zero 4	// it must be 0!!!
#endif
	
	
		
	.text

	
// 
// This code is called when we have to change the thread stack
// subsumes that the new thread TOS is passed in the second parameter r5
//
#ifdef __MULTI__
	.type	EE_nios2_change_tos, @function
EE_nios2_change_tos:	
	// if tos_index == EE_hal_active_tos then we do not have to
	// switch stack
	ldw	r1, %gprel(EE_hal_active_tos)(gp)
	bne	r1, r5, change_tos_continue
	ret
	
change_tos_continue:
	// now r1 = EE_hal_active_tos, r5 = new tos

	// Before changing the stack, we have to save the registers
	// that could be modified (i.e. all the registers that should
	// be preserved through function calls). Note that if there is
	// not the stack change, the system will behave like the
	// monostack version of the kernel
	//
	// r0 (always 0, no need to be saved)
	// r1 (scratch register, no need to be saved)
	// r2-r3 (return values), r4-r7 (arguments) must be preserved
	// when changing the stack
	// r8-r15 (caller-saved registers) already saved by the callers
	// r16-r23 (callee-saved register) must be saved and restored
	// when changing stack
	// r24-r25 (exception and breackpoint temporary) no need to be saved
	// r26 (global pointer) --> MUST NOT be saved
	// r27 (stack pointer) saved inside HAL data structures
	// r28 (frame pointer) saved on the stack
	// r29, r30 (return addr for bpoints/exceptions) no need to be saved
	// r31 (return address) --> we are not changing context, only the stack
	
	addi	sp, sp, -36
	stw	fp, 32(sp)
	stw	r16, 28(sp)
	stw	r17, 24(sp)
	stw	r18, 20(sp)
	stw	r19, 16(sp)
	stw	r20, 12(sp)
	stw	r21, 8(sp)
	stw	r22, 4(sp)
	stw	r23, 0(sp)
	
	//
	// Save current TOS
	//
	// r16 = &EE_nios2_system_tos[0]
	movhi	r16, %hiadj(EE_nios2_system_tos)
	addi	r16, r16, %lo(EE_nios2_system_tos)

	// r17 = EE_hal_active_tos * 4
	slli r17,r1,2
	
	// r18 = & EE_nios2_system_tos[EE_hal_active_tos]
	add	r18, r16, r17

	// EE_nios2_system_tos[EE_hal_active_tos] = sp
	stw	sp, 0(r18)

	
	//
	// New current TOS
	//

	// r17 = tos_index * 4
	slli r17,r5,2
	
	// r18 = &EE_nios2_system_tos[tos_index]
	add	r18, r16, r17

	// sp = EE_nios2_system_tos[tos_index]
	ldw	sp, 0(r18)
	
	//
	// Update EE_hal_active_tos (= tos_index)
	//
	movhi	r16, %hiadj(EE_hal_active_tos)
	addi	r16, r16, %lo(EE_hal_active_tos)
	stw	r5, 0(r16)

	// Here we have to restore the registers saved before the 
	// stack previous change. If this is the first time we use the 
	// current stack, restoring is useless... (stack values are
	// initialized to the top-32

	ldw	fp, 32(sp)
	ldw	r16, 28(sp)
	ldw	r17, 24(sp)
	ldw	r18, 20(sp)
	ldw	r19, 16(sp)
	ldw	r20, 12(sp)
	ldw	r21, 8(sp)
	ldw	r22, 4(sp)
	ldw	r23, 0(sp)
	addi	sp, sp, 36
	
	ret
	.size	EE_nios2_change_tos, . - EE_nios2_change_tos
#endif // __MULTI__

	

	
//
// MONO:  void EE_nios2_hal_ready2stacked(ADDR thread_addr)
// MULTI: void EE_nios2_hal_ready2stacked(ADDR thread_addr, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement preemption.
// r4 contains the parameter
//
	.type	EE_nios2_hal_ready2stacked, @function
EE_nios2_hal_ready2stacked:
	addi	sp, sp, -4

	// save the return address
	stw	ra, 0(sp)
	// no need (I hope) to save the frame pointer
	//stw	fp, XXX(sp)
	
1:	
#ifdef __MULTI__
	// (eventually) switch to the TOS of the new thread
	call	EE_nios2_change_tos
#endif
	
	//
	// Before calling the new thread we have to enable interrupts. 
	//
	movi	r1, 1
	wrctl	status, r1

	// jump to the preempter thread (r4 = first parameter)
	callr	r4

	// NOTE: we have to disable interrupts here before calling
	// EE_thread_end_instance() because it is a primitive
	wrctl	status, zero
	
	// call the scheduler 
	call	EE_thread_end_instance

	// note that interrupts are disabled here
	
	//
	// if EE_hal_endcycle_next_thread == 0
	//   then wake up the preempted thread
	//   (EE_nios2_hal_endcycle_stacked executed)
	//
	// if EE_hal_endcycle_next_thread != 0
	//   then activate a new thread
	//   (EE_nios2_hal_endcycle_ready executed)
	//
	// note that r4 is also the first parameter that was passed to
	// the function
	
#ifdef __MULTI__
	ldw	r5, %gprel(EE_hal_endcycle_next_tos)(gp) 
#endif

	ldw r4,	%gprel(EE_hal_endcycle_next_thread)(gp) 
	bne r4, zero, 1b

	// (eventually) switch to the TOS of the preempted thread
#ifdef __MULTI__
	call	EE_nios2_change_tos
#endif
	
	// Keep interrupts disabled !!!
	// we always return into a primitive or into an IRQ handler...
	
	//
	// return to the interrupted thread
	//
	ldw	ra, 0(sp)
	addi	sp, sp, 4
	ret
		
	.size	EE_nios2_hal_ready2stacked, . - EE_nios2_hal_ready2stacked


#ifdef __MULTI__

//
// MONO:  not defined
// MULTI: void EE_nios2_hal_stkchange(EE_UREG 0, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement a blocking
// synchronization primitive.
//
	.type	EE_nios2_hal_stkchange, @function
EE_nios2_hal_stkchange:	
	
	// Mk: saving lr here and restoring it after EE_nios2_change_tos is mandatory, in order to
	// save lr of the preempted thread and to restore lr of the preempter thread
	//	from their respective stacks!
 	addi	sp, sp, -4
	stw	ra, 0(sp)

	// switch to the TOS of the new thread
	call	EE_nios2_change_tos

	// now the stack is changed, and we need to return to the interrupted thread!
	ldw	ra, 0(sp)
	addi	sp, sp, 4
	ret
	.size	EE_nios2_hal_stkchange, . - EE_nios2_hal_stkchange

#endif		
	
	
#ifdef __NIOSII_INITSTACKS__
// if you are using the Nios II instruction simulator, 
// you should call this function to avoid the warning issued by the
// simulator signaling the read of a data location that has not been
// previously written
	
// r4 contains the number of stacks
	.global	EE_nios2_initstacks
EE_nios2_initstacks:

	movhi	r5, %hiadj(end)
	addi	r5, r5, %lo(end)
	
EE_nios2_initstacks_loop:
	stw		r0, 0(r5)
	addi	r5,r5,4
	bne		r5,sp,EE_nios2_initstacks_loop

// I have to setup all the global pointers in the right places
	movhi	r5, %hiadj(EE_nios2_system_tos)
	addi	r5, r5, %lo(EE_nios2_system_tos)

EE_nios2_initstacks_gploop:
	ldw		r6, 4(r5) // I always skip the main thread!!!
	stw		gp, 36(r6)
	addi	r4, r4, -1
	addi 	r5, r5, 4
	bne		r4, zero, EE_nios2_initstacks_gploop

	ret
#endif


/* 
 * Interrupt handler code.
 * I wish I could have put this code on another file, but unfortunately this piece of
 * code do not have any global symbol. Placin this code in a separated object file in a library
 * makes it impossible to be included in the final image.
 */
	

/* kernel scheduler addresses */
.extern EE_IRQ_end_instance

	
/* stack used by IRQ handlers */
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
.extern EE_nios2_IRQ_tos
.extern EE_nios2_temp_tos
#endif
#endif

/* interrupt handlers nesting */
#ifdef __ALLOW_NESTED_IRQ__
.extern EE_IRQ_nesting_level
#endif	


	
.section .exceptions.irqhandler.user, "xa"

#ifdef __ALLOW_NESTED_IRQ__

	/* increase the nesting level */
	ldw	r2, %gprel(EE_IRQ_nesting_level)(gp)
	addi	r3, r2, 1
	stw	r3, %gprel(EE_IRQ_nesting_level)(gp)

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	/* if this is the first handler instance then we have to 
	   change stack to the IRQ stack */
	bne  r2, zero, after_change_to_irq_tos
        /* change the stack */
	stw  sp, %gprel(EE_nios2_temp_tos)(gp)
	ldw  sp, %gprel(EE_nios2_IRQ_tos)(gp)
	after_change_to_irq_tos:
#endif
#endif

	/* Interrupts will be reenabled using alt_irq_interruptible() */
	
#else // __ALLOW_NESTED_IRQ__
#error "The ALTERA NIOS II HAL works only with NESTED IRQ enabled. Please enable nested IRQ in the OIL file."
#endif // __ALLOW_NESTED_IRQ__

    /* after this code, there should be a "call alt_irq_handler" instruction */



	

.section .exceptions.irqreturn.user, "xa"

	/* here in ARM7 if __ALLOW_NESTED_IRQ__ we were disabling interrupts;
           here in NIOS there is no need since interrupts are
	       enabled/disabled by the handlers called inside alt_irq_handler
	*/

#ifdef __ALLOW_NESTED_IRQ__
	/* decrease the nesting level */
	ldw	r2, %gprel(EE_IRQ_nesting_level)(gp)
	addi	r2, r2, -1
	stw	r2, %gprel(EE_IRQ_nesting_level)(gp)

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	/* if this is the first handler instance then we have to
	   change stack
	   This code is called when we have to change from the IRQ stack to
	   the thread stack. Note that we don't have to save the IRQ TOS 
	   because the IRQ stack is empty. */
	bne	r2, zero, after_change_from_irq_tos
	ldw	sp, %gprel(EE_nios2_temp_tos)(gp)
	after_change_from_irq_tos:
#endif
#endif

	/* call the scheduler only if this is the first instance */
	bne	r2, zero, theend

#endif // __ALLOW_NESTED_IRQ__

	
	/* call the scheduler only if this is the first instance */
	call	EE_IRQ_end_instance

	/* check if the scheduler has called IRQ_ready or IRQ_stacked
           I use r5 because it is the same register received by
           ready2stacked */
#ifdef __MULTI__
	ldw	r5, %gprel(EE_hal_endcycle_next_tos)(gp)
#endif
	
	ldw r4,	%gprel(EE_hal_endcycle_next_thread)(gp)

	/* now we have to call two different functions */

#ifdef __MULTI__
	beq r4, zero, callstkchange
	call EE_nios2_hal_ready2stacked
	br theend

	callstkchange:
	call EE_nios2_hal_stkchange
#else
	beq r4, zero, theend
	call EE_nios2_hal_ready2stacked
#endif
	
        theend:
        

	.end
