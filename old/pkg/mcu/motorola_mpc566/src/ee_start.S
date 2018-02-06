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
 * CVS: $Id: ee_start.S,v 1.4 2006/01/05 14:37:22 pj Exp $
 */

#include "cpu/mpc5xx/inc/ee_compiler.h"

	// initial values for stack pointers
	.extern __SYS_STACK_ADDRESS	@ Initial Stack Pointer for SYS mode

	// initial C variable values
	.extern __DATA_RAM		@ Start of initialized data (RAM)
	.extern __DATA_END		@ End of initialized data (RAM)
	.extern __DATA_ROM		@ Start of initialized data (ROM)
	.extern __BSS_END		@ End of uninitialized data (RAM)
	.extern __SP_INIT		@ Start of stack memory bank
	.extern __SP_END		@ End of stack memory bank


//
// System "bootstrap"
//
	.extern main			// main thread
	.extern EE_install_handlers	// SWI and IRQ handler installer

	.text

//
// ENTRY POINT
//

	// bootstrap
	.global _start
	.type	_start,@function
_start:


#ifndef __DEFAULT_LD_SCRIPT__

	// Signaling that exception vector is at 0xFFFn_nnnn
	li	9, 1
	slwi	9, 9, 6
	mfmsr	0
	or	0, 0, 9
	mtmsr	0

	// Setting CPU to use external SRAM
	
	//
	// BSS and default C variable values (copy from ROM to RAM)
	//
	// r5 = __DATA_ROM  (r0)
	lis	9,__DATA_ROM@ha
	la	5,__DATA_ROM@l(9)
	// r3 = __DATA_RAM  (r1)
	lis	9,__DATA_RAM@ha
	la	3,__DATA_RAM@l(9)
	// r4 = __DATA_END  (r2)
	lis	9,__DATA_END@ha
	la	4,__DATA_END@l(9)

	// CMP	__DATA_ROM, __DATA_RAM  // If RW base equals RO limit, then the
	cmpw	0,5,3			// RW execution address...
	// BEQ   	_zeroinit   	// ... equals the load address => go to
	beq	0, _zeroinit		// not initialized data copy

_init_ram:
    	// Copy initialized RW data
    	//CMP   r3, r4       	// The initialized RW data ends at the
	cmpw	0, 3, 4		// beginning of the ZI data
	blt	0, 1f
	b	_zeroinit

1:    	//LDRCC r9, [r5], #4 	// If r1 < r2, read data from intialized
	lwz	9, 0(5)		// data section in ROM
	addi	5, 5, 4
    	
	//STRCC r9, [r3], #4 	// If r1 < r2, store data to intialized
	stw	9, 0(3)		// data section in RAM
	addi	3, 3, 4

    	b	_init_ram

_zeroinit:
    	//LDR   r3, =__bss_end__
	lis	9, __BSS_END@ha
	la	3, __BSS_END@l(9)
	
    	//MOV   r3, #0
	li	9, 0
	
_zero_loop:
    	// Build ZI data
    	//CMP   __DATA_END, __BSS_END - Loop until the end of the ZI data
	cmpw	0,4,3
	blt	0, 1f		// beginning of the ZI data
	b	_end_zero
	
1:    	//STRCC r3, [r2], #4
	stw	9, 0(4)
	addi	4, 4, 4
	
    	//BCC   _zero_loop
	b	_zero_loop
	
_end_zero:

#endif // __DEFAULT_LD_SCRIPTS__

#ifdef __OO_ORTI_STACK__
	// Manage the stack fillpattern
	//LDR  	r0, =__SP_END
	lis	9, __SP_END@ha
	la	1, __SP_END@l(9)
	//LDR  	r1, =__SP_INIT
	lis	9, __SP_INIT@ha
	la	2, __SP_INIT@l(9)
	//LDR	r2, =0xA5A5A5A5
	li	0, 0xA5A5A5A5

_init_stack_fillpattern:
    	// Set up Stack Fill Pattern
    	//STR	r2, [r1], #4
	stw	0, 0(2)
	addi	2, 2, -4
    	//CMP	r1, r0
	cmpw	1, 2
    	//BCC	_init_stack_fillpattern
	blt	_init_stack_fillpattern
#endif // __OO_ORTI_STACK__

	//
	// Stack pointer "set up"
	//

	lis	9, __SYS_STACK_ADDRESS@ha
	la	1, __SYS_STACK_ADDRESS@l(9)
	
	//

	// main() thread "activation".
#ifndef __MPC5PROTECTED__
  	b	main
#else
	mfmsr	0
	li	3, 2
	slwi	4, 3, 13
	or	0, 0, 3
	not	4, 4
	and	0, 0, 4
	mtmsr	0
	b	main
#endif
	.size	_start, . - _start

