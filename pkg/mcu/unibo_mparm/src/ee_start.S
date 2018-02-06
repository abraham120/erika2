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
 * Author: 2001-2002 Alessandro Colantonio, 2003- Paolo Gai
 * CVS: $Id: ee_start.S,v 1.5 2006/01/05 14:37:22 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"

	// initial values for stack pointers, defined in the
	// application file cfg_e7t.h
	.extern __IRQ_STACK_ADDRESS	// Initial Stack Pointer for IRQ mode
	.extern __SVC_STACK_ADDRESS	// Initial Stack Pointer for SVC mode
	.extern __SYS_STACK_ADDRESS	// Initial Stack Pointer for SYS mode
	.extern __FIQ_STACK_ADDRESS	// Initial Stack Pointer for FIQ mode
	.extern __ABT_STACK_ADDRESS	// Initial Stack Pointer for ABT mode
	.extern __UND_STACK_ADDRESS	// Initial Stack Pointer for UND mode
	.extern __SP_INIT		// Start of stack memory bank
	.extern __SP_END		// End of stack memory bank

	// initial C variable values
//	.extern __data_start		// Start of initialized data (RAM)
//	.extern _edata			// End of initialized data   (RAM)
//	.extern _data_copy__		// Start of initialized data (ROM)
//	.extern __bss_end__		// End of uninitialized data (RAM)
	
		
//
// System "bootstrap"
//
	.extern main			// main thread

	.text

// 
// ENTRY POINT
//
	// initialization code is in ARM-mode
	.arm


	// bootstrap
	.global _start
	.type	_start,#function
_start:	

	//	
	// Stack pointer "set up" 
	//
	
	// Supervisor mode (SWI) stack pointer
 	MOV	r0, #Mode_SVC | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__SVC_STACK_ADDRESS

	// Abort (ABT) stack pointer
 	MOV	r0, #Mode_ABT | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__ABT_STACK_ADDRESS

	// Undefined (UND) stack pointer
 	MOV	r0, #Mode_UND | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__UND_STACK_ADDRESS

 	// IRQ mode stack pointer
 	MOV	r0, #Mode_IRQ | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__IRQ_STACK_ADDRESS

 	// FIQ mode stack pointer
 	MOV	r0, #Mode_FIQ | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__FIQ_STACK_ADDRESS

		// System mode stack pointer
	// note: now we can enable the interrupts
 	MOV	r0, #Mode_SYS
 	MSR	cpsr_c, r0
 	LDR	sp, =__SYS_STACK_ADDRESS
	

	//
	// NOTE: now we are in SYS-mode! 
	//

		
	//
	// BSS and default C variable values (copy from ROM to RAM)
	//	
	/*LDR   	r0, =_data_copy__
	LDR   	r1, =__data_start
	LDR   	r2, =_edata

	CMP   	r0, r1          // If RW base equals RO limit, then the
				// RW execution address...
	BEQ   	_zeroinit   	// ... equals the load address => go to 
				// not initialized data copy

_init_ram:
    	// Copy initialized RW data
    	CMP   r1, r2       	// The initialized RW data ends at the 
				// beginning of the ZI data
    	LDRCC r3, [r0], #4 	// If r1 < r2, read data from intialized 
				// data section in ROM
    	STRCC r3, [r1], #4 	// If r1 < r2, store data to intialized 
				// data section in RAM
    	BCC   _init_ram

_zeroinit:
    	LDR   r1, =__bss_end__
    	MOV   r3, #0
_zero_loop:
    	// Build ZI data
    	CMP   r2, r1       	// Loop until the end of the ZI data
    	STRCC r3, [r2], #4      
    	BCC   _zero_loop

#ifdef __OO_ORTI_STACK__
	// Manage the stack fillpattern
	LDR   	r0, =__SP_END
	LDR   	r1, =__SP_INIT
	LDR	r2, =0xA5A5A5A5

_init_stack_fillpattern:
    	// Set up Stack Fill Pattern
    	STR	r2, [r1], #4 	
    	CMP	r1, r0
    	BCC	_init_stack_fillpattern
#endif*/

  	B	main

	.size	_start, . - _start
	
	.end
	
