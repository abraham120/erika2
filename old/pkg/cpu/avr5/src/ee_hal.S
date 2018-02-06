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
 * Author: Antonio Romano
 * CVS: $Id: ee_hal.S,v 1.3 2007/06/01 09:00:21 pj Exp $
 */


/* the define is needed for binary distributions */

#define __EECFG_THIS_IS_ASSEMBLER__
#include "eecfg.h"
#include "cpu/avr5/inc/ee_compiler.h"
#include "stackManage.S"



	.global	EE_avr5_hal_ready2stacked
	.global EE_hal_endcycle_next_thread


#ifdef __MULTI__
	.global EE_avr5_hal_stkchange
	.global EE_hal_endcycle_next_tos
#endif

	
/* system TOS */


#ifdef __MULTI__
	.extern	EE_avr5_system_tos
	.extern	EE_avr5_active_tos
	.extern EE_avr5_IRQ_tos
#endif
	
/* kernel scheduler addresses */
#ifdef __FP__
	.extern	EE_thread_end_instance
#define __thread_end_instance EE_thread_end_instance
#endif

#ifdef __EDF__
	.extern	EE_edf_thread_end_instance
#define __thread_end_instance EE_edf_thread_end_instance
#endif

#if defined(__OSEKOS_BCC1__) || defined(__OSEKOS_BCC2__) || defined(__OSEKOS_ECC1__) || defined(__OSEKOS_ECC2__)
	.extern	EE_osek_thread_end_instance
#define __thread_end_instance EE_osek_thread_end_instance
#endif


.section .bss

/*	
// This variable contains the address of the new preempter thread,
// when the preemption check is done at the end of a thread.
//
// NOTE: This variable is modified when a thread ends (before
//       xxx_thread_end_instance()) and its content is read when
//       xxx_thread_end_instance() ends; during this period it is
//       important to disable interrupts in order to avoid nested
//       thread_end_instance() calls.
*/

	
EE_hal_endcycle_next_thread:
	.word 0x0000
/*   
//
// This variable contains the index of the new preempter thread TOS.
//
*/


#ifdef __MULTI__
	
EE_hal_endcycle_next_tos:
	.byte 0x00

#endif
/*
// this variable is used by EE_avr5_change_to_irq_tos and
// EE_avr5_change_from_irq_tos to store the current thread TOS
*/

#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__

.global EE_avr5_temp_tos
EE_avr5_temp_tos:	
	.word 0x0000

#endif
#endif

/* interrupt handlers nesting */


	.global	EE_IRQ_nesting_level
EE_IRQ_nesting_level:	
	.word 0x0000
	
	
		
	.text

/*
// This code is called when we have to change the thread stack
// NOTE: r22:r23 *MUST* contain tos_index, while r24:r25 (the thread address)
// will be unchanged!!!
*/

/*
	// Before changing the stack, we have to save the registers
	// that could be modified (i.e. all the registers that should
	// be preserved through function calls). Note that if there is
	// not the stack change, the system will behave like the
	// monostack version of the kernel
 */
						
	/*/
	//Update avr5_active_tos (= tos_index)
	
	// remember that r31:r30 = &EE_arm7_active_tos 
	*/
	


/*
// MONO:  void EE_arm7_hal_ready2stacked(ADDR thread_addr)
// MULTI: void EE_arm7_hal_ready2stacked(ADDR thread_addr, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement preemption.
*/
//	.type	EE_avr5_hal_ready2stacked, #function


EE_avr5_hal_ready2stacked:
		 	
rep:	
	#ifdef __MULTI__
	ldi r30, lo8(EE_avr5_active_tos)
	ldi r31, hi8(EE_avr5_active_tos) 
	ld r18, Z
    cp  r18, r22

	//if tos_index == active_tos **** no change stack

	breq nochangestack00
	changestack	
	nochangestack00:
#endif
	//enable global interrupt before call the preempter thread	

	sei
	movw r30, r24
	clr r0
	clr r1

	//call the thread

	icall

	//disable interrupt	

	cli
	clr r0
	clr r1
	
	call __thread_end_instance
	
	#ifdef __MULTI__
	ldi r30, lo8(EE_hal_endcycle_next_tos)
	ldi r31, hi8(EE_hal_endcycle_next_tos) 
	ld r22, Z
	#endif
	ldi r30, lo8(EE_hal_endcycle_next_thread)
	ldi r31, hi8(EE_hal_endcycle_next_thread) 
	ld r24, Z+
	ld r25, Z
	clr r0
	clr r1
	cp  r24, r0
	cpc r25, r1
	
	breq jump
    jmp rep
    jump:

	/*/
	// (eventually) switch to the TOS of the preempted thread
	/*/	
	#ifdef __MULTI__
	ldi r30, lo8(EE_avr5_active_tos)
	ldi r31, hi8(EE_avr5_active_tos) 
	ld r18, Z
    cp  r18, r22
	breq nochangestack01
	changestack
	#endif
    nochangestack01:
	ret


	#ifdef __MULTI__
EE_avr5_hal_stkchange:
	
	ldi r30, lo8(EE_avr5_active_tos)
	ldi r31, hi8(EE_avr5_active_tos) 
	ld r18, Z
    cp  r18, r22	
	breq exitstkchange
	changestack
	exitstkchange:
	ret
	#endif // __MULTI__
