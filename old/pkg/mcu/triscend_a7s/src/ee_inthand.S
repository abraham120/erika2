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
 * Author: 2001-2002 Paolo Gai
 * CVS: $Id: ee_inthand.S,v 1.5 2006/05/14 17:50:30 pj Exp $
 */
	
#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"
	
//
// Imported symbols
//

	// user's handlers addresses
#ifdef __TIMER_0_USED__
	.extern EE_timer0_handler_addr
#endif

#ifdef __TIMER_1_USED__
	.extern EE_timer1_handler_addr
#endif
	
#ifdef __WATCHDOG_USED__
	.extern EE_watchdog_handler_addr
#endif

	// kernel scheduler addresses 
	.extern	EE_IRQ_end_instance

	// stack used by IRQ handlers
#ifdef __MULTI__
	.extern EE_arm7_hal_stkchange
#ifdef __IRQ_STACK_NEEDED__
	.extern EE_arm7_change_to_irq_tos
	.extern EE_arm7_change_from_irq_tos
#endif
#endif

	
	.extern	EE_IRQ_nesting_level

	.extern EE_hal_endcycle_next_thread
#ifdef __MULTI__
	.extern EE_hal_endcycle_next_tos
#endif

//
// Exported symbols
//
	// hardware and software interrupts handlers
	.global	EE_IRQ_handler
	.global	EE_SWI_handler
	.global	EE_FIQ_handler

	
//
// Code area
//
	
	.text

	// kernel code is in ARM-mode
	.arm
	
	// Address of the IRQ status register for triscend
	// NOTE: it is in the text segment (ROM?) because it cannot
	//       be an immediate operand and it is constant
EE_IRQ_STATUS_REG:		.word	0xd1010200
EE_FIQ_STATUS_REG:		.word	0xd1010300
EE_TIMER_0_INTCLEAR:		.word 0xd101050c
EE_TIMER_1_INTCLEAR:		.word 0xd101052c
EE_WATCHDOG_INTCLEAR:	.word 0xd101060c


//
// Hardware interrupts handler
//
	.type	EE_IRQ_handler, #function
EE_IRQ_handler:		
	// NOTE: interrupts are disabled

	// save LR_irq, PSR of the preempted thread and work registers
	// that are not preserved across function calls -- that can be
	// overwritten if another interrupt occurs while the current
	// one is being processed
	STMFD	sp!, {r0-r3,r12,lr}
	MRS	r0, spsr
	STMFD	sp, {r0, lr}^	// thread return address and cpsr
	NOP
	SUB	sp, sp, #8	// ARM7 "bug"
	

	// R0 contains the IRQ number
	LDR	r1, EE_IRQ_STATUS_REG // get address of the IRQ status reg 
	LDR	r0, [r1]	// read the status reg byte


 	//
	// TIMER0 handler
	//
#ifdef __TIMER_0_USED__
	TST	r0, #0x08
	BEQ	1f
	
// clear interrupt source (*EE_TIMER_0_INTCLEAR = 0x01)
	LDR	r1, EE_TIMER_0_INTCLEAR
	MOV   r2, #1
	STR	r2, [r1]

#ifdef __TIME_SUPPORT__
 	ADD	sp, sp, #8	// do not restore spsr and lr_sys... 	
 	LDMFD	sp!, {r0-r3,r12,lr}
	SUBS	pc, lr, #4
#else
	LDR	r2, =EE_timer0_handler_addr
	B	2f
#endif // __TIME_SUPPORT__

1:	
#endif // __TIMER_0_USED__


	//	
	// TIMER1 handler
	//
#ifdef __TIMER_1_USED__
	TST	r0, #0x10
	BEQ	1f
	
	// clear interrupt source (*EE_TIMER_1_INTCLEAR = 0x01)
	LDR	r1, EE_TIMER_1_INTCLEAR
	MOV   r2, #1
	STR	r2, [r1]
		
	LDR	r2, =EE_timer1_handler_addr
	B	2f
1:	
#endif // __TIMER_1_USED__



	//
	// WATCHDOG handler
	//
#ifdef __WATCHDOG_USED__
	TST	r0, #0x40
	BEQ	1f

	// clear interrupt source (*EE_WATCHDOG_INTCLEAR = 0x01)
	LDR	r1, EE_WATCHDOG_INTCLEAR
	MOV   r2, #1
	STR	r2, [r1]
	
	LDR	r2, =EE_watchdog_handler_addr
	B	2f
1:	
#endif // __WATCHDOG_USED__



	// 
	// if it isn't a known request, simply return. NB: in triscend non azzero altri pending interrupt
	// 	
	ADD	sp, sp, #8	// do not restore spsr and lr_sys...
	LDMFD	sp!, {r0-r3,r12,lr}
	SUBS	pc, lr, #4




	//
	// Jump to the correct handler
	//
2:	
#ifdef __ALLOW_NESTED_IRQ__

	// increase the nesting level
	LDR	r0, =EE_IRQ_nesting_level
	LDR	r1, [r0]
	ADD	r1, r1, #1
	STR	r1, [r0]
	
#ifdef __MULTI__
#ifdef __IRQ_STACK_NEEDED__
	// if this is the first handler instance then we have to
	// change stack
	CMP	r1, #1
	BLEQ	EE_arm7_change_to_irq_tos
#endif
#endif
	
	// now we can re-enable interrupts and switch to SYS mode
 	MOV	r0, #Mode_SYS
 	MSR	cpsr_c, r0
	
#else // not __ALLOW_NESTED_IRQ__
	
	// nesting level = 1
	LDR	r0, =EE_IRQ_nesting_level
	MOV	r1, #1
	STR	r1, [r0]

		// now we can switch to SYS mode
 	MOV	r0, #Mode_SYS | I_bit
 	MSR	cpsr_c, r0
	
#endif // __ALLOW_NESTED_IRQ__

	
	// 
	// jump to the correct handler
	// 
	MOV	lr, pc
	LDR	pc, [r2]

	
#ifdef __ALLOW_NESTED_IRQ__
	// we can disable interrupts
 	MOV	r0, #Mode_SYS | I_bit
 	MSR	cpsr_c, r0

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
	BLEQ	EE_arm7_change_from_irq_tos
#endif
#endif
		
	// call the scheduler only if this is the first instance
	BNE	theend

#else  // not __ALLOW_NESTED_IRQ__
	
	// nesting level = 0
	LDR	r0, =EE_IRQ_nesting_level
	MOV	r1, #0
	STR	r1, [r0]

#endif // __ALLOW_NESTED_IRQ__

	
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
	
theend:
	// switch to IRQ mode and disable _only_ IRQ, _not_ FIQ
 	MOV	r0, #Mode_IRQ | I_bit
 	MSR	cpsr_c, r0
	
	// restore IRQ-handler working registers and return from IRQ
	LDMFD	sp, {r0, lr}^	// cpsr and lr of preempted thread
	MSR	spsr, r0
	ADD	sp, sp, #8	// ARM7 "bug"
	LDMFD	sp!, {r0-r3,r12,lr}
	SUBS	pc, lr, #4
	
	.size	EE_IRQ_handler, . - EE_IRQ_handler

	
	
		
//
// Software interrupts handler
//
	.type	EE_SWI_handler, #function
EE_SWI_handler:	

	// 
	// simply return 
	//
	
	MOVS	pc, lr
	
	.size	EE_SWI_handler, . - EE_SWI_handler



	
	
//
// Fast interrupts handler
//		

	.type	EE_FIQ_handler, #function
EE_FIQ_handler:	

//da Janus:
        // The FIQ handler works as follows:
	//
	// - The banked registers R8-R10 are used to save the registers R0-R3
	//   without accessing the memory.
	// - R11 is used to store
	// - R12 is not saved (it is banked automatically by the FIQ mode)
	// - SPSR is not saved (there is no interrupt nesting)

	// Save the contents of the R0-R2 registers
	MOV	r8, r0
	MOV	r9, r1
	MOV	r10, r2

	// Save r3 and lr_fiq on the stack
 	STMFD	sp!, {r3, lr}

	// control the interrupt source, clear the pending bit 
        // and branch to the right handler
        // NOTE: the C handler runs with interrupt disabled

	// read the FIP register
	LDR	r11, EE_FIQ_STATUS_REG
	LDR	r0, [r11]


	LDR	r2, =EE_fiq_handler_addr
	MOV	lr, pc
	LDR	pc, [r2]


	// and clear it!!!
	//STR	r0, [r11] --> can't do this in triscend

	// Restore r3 and lr_fiq on the stack 	
	LDMFD	sp!, {r3, lr}	

	// Restore the contents of the R0-R2 registers
	MOV   r2, r10
	MOV   r1, r9
	MOV	r0, r8

	SUBS	pc, lr, #4

	.size	EE_FIQ_handler, . - EE_FIQ_handler


	.end
