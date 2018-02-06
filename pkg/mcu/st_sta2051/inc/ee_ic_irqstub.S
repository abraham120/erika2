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
 * Author: 2001-2002 Paolo Gai, Alessandro Colantonio, 2003- Paolo Gai
 * CVS: $Id: ee_ic_irqstub.S,v 1.2 2006/10/25 13:59:02 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"
	
/*
 * Imported symbols
 */ 

	.extern	EE_IRQ_end_instance
	.extern EE_IRQ_nesting_level
	.extern EE_arm7_hal_ready2stacked 
	.extern EE_hal_endcycle_next_thread

	

#ifdef __MULTI__
	.extern EE_arm7_hal_stkchange
	.extern EE_hal_endcycle_next_tos
#ifdef __IRQ_STACK_NEEDED__
	.extern EE_arm7_temp_tos
	.extern EE_arm7_IRQ_tos
#endif
#endif



/* ------------------------------------------------------------------------
 * ISR Level 1 Macro
 * ------------------------------------------------------------------------
 *
 * ISR Level 1 contains all the code for a typical ISR1 routine.
 * Features of ISR1 include:
 * - Support for Nested interrupt
 * - The ISR C routine runs in System mode
 * - In multi stack systems if needed the stack can be switched 
 *   to the separate Interrupt stack
 * - No EE Functions can be called from this handler
 * - It is supposed that ISR 1 have priority higher than ISR 2
 */


.macro EE_ISR1_HANDLER_STUB C_FUNCTION_NAME, STUB_FUNCTION_NAME, PHERIPERAL_CHANNEL

	.extern \C_FUNCTION_NAME
	.global \STUB_FUNCTION_NAME
	
	.type \STUB_FUNCTION_NAME, #function
\STUB_FUNCTION_NAME:
	// NOTE: interrupts are disabled

	// ---------------------------------------------------------------
	// save the context inside SYS mode

	SUB	lr, lr, #4
	
	// save LR_IRQ, SPSR inside the IRQ stack
	STMFD	sp!,{r0-r1, lr}
	MRS	r0, spsr
	STMFD	sp!, {r0}
	MOV	r1, sp
	ADD	sp, sp, #16

	// r0 is free, r1=SP_IRQ, sp_IRQ is clean

	// switch to SYS mode
 	MOV	r0, #Mode_SYS | I_bit
 	MSR	cpsr_c, r0

	// save registers inside the user stack
	STMFD	sp!, {r2-r3, r12, lr}
	LDMFD	r1, {r0,r2,r3,r12}
	STMFD	sp!, {r0,r2,r3,r12}

	// On the user stack there are the following registers:	r2,r3, r12, lr_usr, r0, r1, lr_irq, spsr

	// R0, R1, R2, R3 are free

	// ---------------------------------------------------------------
	// handle nesting and IRQ priority levels
		
#ifdef __ALLOW_NESTED_IRQ__

	// increase the nesting level
	LDR	r1, =EE_IRQ_nesting_level
	LDR	r3, [r1]
	ADD	r3, r3, #1
	STR	r3, [r1]
	
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	// if this is the first handler instance then we have to
	// change stack
	CMP	r3, #1
	LDREQ	r0, =EE_arm7_temp_tos
	STREQ	sp, [r0]
	LDREQ	r0, =EE_arm7_IRQ_tos
	LDREQ	sp, [r0]
#endif
#endif
	
	// now we can re-enable interrupts and switch to SYS mode
 	MOV	r1, #Mode_SYS
 	MSR	cpsr_c, r1
	
#else // not __ALLOW_NESTED_IRQ__
	
	// nesting level = 1
	LDR	r1, =EE_IRQ_nesting_level
	MOV	r3, #1
	STR	r3, [r1]

	// now we can switch to SYS mode
 	MOV	r1, #Mode_SYS | I_bit
 	MSR	cpsr_c, r1
	
#endif // __ALLOW_NESTED_IRQ__


	// ---------------------------------------------------------------
	// jump to the handler

	BL	\C_FUNCTION_NAME

	// ---------------------------------------------------------------
	// handle nesting and IRQ priority levels

#ifdef __ALLOW_NESTED_IRQ__
	// we can disable interrupts (_only_ IRQ, _not_ FIQ)
 	MOV	r0, #Mode_SYS | I_bit
 	MSR	cpsr_c, r0
#endif

	//
	// Re-enable the interrupt source
	//
	
	// *((ADDR)IPR) = (1 << PHERIPERAL_CHANNEL)
	LDR	r0, =0xFFFFFC40 // IPR0
	MOV	r1, #1 << \PHERIPERAL_CHANNEL
	STR	r1, [r0]


#ifdef __ALLOW_NESTED_IRQ__
	// decrease the nesting level
	LDR	r0, =EE_IRQ_nesting_level
	LDR	r1, [r0]
	SUB	r1, r1, #1
	STR	r1, [r0]

	// is this the first handler instance?
	CMP	r1, #0
	
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	// if this is the first handler instance then we have to
	// change stack
	LDREQ	r0, =EE_arm7_temp_tos
	LDREQ	sp, [r0]
#endif
#endif

#else  // not __ALLOW_NESTED_IRQ__
	
	// nesting level = 0
	LDR	r0, =EE_IRQ_nesting_level
	MOV	r1, #0
	STR	r1, [r0]
	
#endif // __ALLOW_NESTED_IRQ__



	// ---------------------------------------------------------------
	// end of the interrupt

	MOV	r1, sp
	ADD	sp, sp, #16
	LDMFD	sp!, {r2-r3, r12, lr}

	// switch to IRQ mode
 	MOV	r0, #Mode_IRQ | I_bit
 	MSR	cpsr_c, r0

	LDMFD	r1!, {r0}
	MSR	spsr, r0
	LDMFD	r1, {r0-r1,pc}^

	.size	\STUB_FUNCTION_NAME, . - \STUB_FUNCTION_NAME
	
	.endm
	
	

/* ------------------------------------------------------------------------
 * ISR Level 2 Macro
 * ------------------------------------------------------------------------
	
 * ISR Level 1 contains all the code for a typical ISR2 routine.
 * Features of ISR2 include:
 * - Support for Nested interrupt
 * - The ISR C routine runs in System mode
 * - In multi stack systems if needed the stack can be switched 
 *   to the separate Interrupt stack
 * - EE Functions can be called from this handler
 * - It is supposed that ISR 2 have priority lower than ISR 1
 */

.macro EE_ISR2_HANDLER_STUB C_FUNCTION_NAME, STUB_FUNCTION_NAME, PHERIPERAL_CHANNEL

	.extern \C_FUNCTION_NAME
	.global \STUB_FUNCTION_NAME
	
	.type \STUB_FUNCTION_NAME, #function
\STUB_FUNCTION_NAME:
	// NOTE: interrupts are disabled

	// ---------------------------------------------------------------
	// save the context inside SYS mode

	SUB	lr, lr, #4
	
	// save LR_IRQ, SPSR inside the IRQ stack
	STMFD	sp!,{r0-r1, lr}
	MRS	r0, spsr
	STMFD	sp!, {r0}
	MOV	r1, sp
	ADD	sp, sp, #16

	// r0 is free, r1=SP_IRQ, sp_IRQ is clean

	// switch to SYS mode
 	MOV	r0, #Mode_SYS | I_bit
 	MSR	cpsr_c, r0

	// save registers inside the user stack
	STMFD	sp!, {r2-r3, r12, lr}
	LDMFD	r1, {r0,r2,r3,r12}
	STMFD	sp!, {r0,r2,r3,r12}

	// On the user stack there are the following registers:	r2,r3, r12, lr_usr, r0, r1, lr_irq, spsr

	// R0, R1, R2, R3 are free

	// ---------------------------------------------------------------
	// handle nesting and IRQ priority levels
		
#ifdef __ALLOW_NESTED_IRQ__

	// increase the nesting level
	LDR	r1, =EE_IRQ_nesting_level
	LDR	r3, [r1]
	ADD	r3, r3, #1
	STR	r3, [r1]
	
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	// if this is the first handler instance then we have to
	// change stack
	CMP	r3, #1
	LDREQ	r0, =EE_arm7_temp_tos
	STREQ	sp, [r0]
	LDREQ	r0, =EE_arm7_IRQ_tos
	LDREQ	sp, [r0]
#endif
#endif
	
	// now we can re-enable interrupts and switch to SYS mode
 	MOV	r1, #Mode_SYS
 	MSR	cpsr_c, r1
	
#else // not __ALLOW_NESTED_IRQ__
	
	// nesting level = 1
	LDR	r1, =EE_IRQ_nesting_level
	MOV	r3, #1
	STR	r3, [r1]

	// now we can switch to SYS mode
 	MOV	r1, #Mode_SYS | I_bit
 	MSR	cpsr_c, r1
	
#endif // __ALLOW_NESTED_IRQ__


	// ---------------------------------------------------------------
	// jump to the handler

	BL	\C_FUNCTION_NAME

	// ---------------------------------------------------------------
	// handle nesting and IRQ priority levels

#ifdef __ALLOW_NESTED_IRQ__
	// we can disable interrupts (_only_ IRQ, _not_ FIQ)
 	MOV	r0, #Mode_SYS | I_bit
 	MSR	cpsr_c, r0
#endif

	//
	// Re-enable the interrupt source
	//
	
	// *((ADDR)IPR) = (1 << PHERIPERAL_CHANNEL)
	LDR	r0, =0xFFFFFC40 // IPR0
	MOV	r1, #1 << \PHERIPERAL_CHANNEL
	STR	r1, [r0]

	B EE_IRQ_footer
	.endm




/* ------------------------------------------------------------------------
 * IRQ Footer macro
 * ------------------------------------------------------------------------
 *
 * This macro is called once to complete the IRQ management, and it
 * covers the common ending part of all the irq handlers.
 *
 * NOTE: when this function is called INTERRUPTS ARE DISABLED!!!
 */

.macro EE_IRQ_FOOTER_STUB

.global EE_IRQ_footer
EE_IRQ_footer:
	
#ifdef __ALLOW_NESTED_IRQ__
	// decrease the nesting level
	LDR	r0, =EE_IRQ_nesting_level
	LDR	r1, [r0]
	SUB	r1, r1, #1
	STR	r1, [r0]

	// is this the first handler instance?
	CMP	r1, #0
	
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	// if this is the first handler instance then we have to
	// change stack
	LDREQ	r0, =EE_arm7_temp_tos
	LDREQ	sp, [r0]
#endif
#endif

	// call the scheduler only if this is the first instance
	BNE	theend

#else // not __ALLOW_NESTED_IRQ__
	// nesting level = 0
	LDR	r0, =EE_IRQ_nesting_level
	MOV	r1, #0
	STR	r1, [r0]
#endif // __ALLOW_NESTED_IRQ__

	// ---------------------------------------------------------------
	// call the scheduler
	
	// call the scheduler only if this is the first instance
	BL	EE_IRQ_end_instance


	// check if the scheduler has called IRQ_ready or IRQ_stacked
#ifdef __MULTI__
	LDR	r2, =EE_hal_endcycle_next_tos
	LDR	r1, [r2]
#endif
	
	LDR	r2, =EE_hal_endcycle_next_thread
	LDR	r0, [r2]

	CMP r0, #0 
	// now we have to call two different functions

#ifdef __MULTI__
	ADD lr, pc, #4                       // that is, theend
	BNE EE_arm7_hal_ready2stacked 
	BEQ EE_arm7_hal_stkchange
#else
	BLNE EE_arm7_hal_ready2stacked 
#endif
	
	// ---------------------------------------------------------------
	// end of the interrupt
theend:	
	MOV	r1, sp
	ADD	sp, sp, #16
	LDMFD	sp!, {r2-r3, r12, lr}

	// switch to IRQ mode
 	MOV	r0, #Mode_IRQ | I_bit
 	MSR	cpsr_c, r0

	LDMFD	r1!, {r0}
	MSR	spsr, r0
	LDMFD	r1, {r0-r1,pc}^

	.endm

		
	// there is no .end directive, this file is included!

