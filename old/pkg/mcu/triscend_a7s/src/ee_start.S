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
 * CVS: $Id: ee_start.S,v 1.4 2006/05/14 17:50:30 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"
	
// initial values for stack pointers
	.extern __SVC_STACK_ADDRESS 			// initial stack pointer for SVC mode
	.extern __IRQ_STACK_ADDRESS 			// initial stack pointer for IRQ mode
	.extern __SYS_STACK_ADDRESS 			// initial stack pointer for SYS mode
	.extern __TMP_STACK_ADDRESS 			// temporary stack pointer

//
// System "bootstrap"
//
	.extern main		// main thread in 						tests/triscend/fp/code.c
	.extern EE_sdram_init	// inizializza sdram, definito in	tests/triscend/fp/initdrvs.c
	.extern EE_SWI_Handler	// handlers definiti in 				src/triscend/inthand.S
	.extern EE_IRQ_Handler
	.extern EE_FIQ_Handler	

.equ     REMAP_ALIAS_ENABLE_REG,   0xd1010440

		.section	".vectors","ax"
	        .align 4

		.globl	__begin
		.globl	_main
		.globl	__vectorend

__begin:
_main:
	LDR	PC,Start_Addr
Udef:
	B	Udef
SWI:
	LDR   PC,  SWI_handler_Addr
Prefetch:
	B	Prefetch
Abort:
	B  Abort
Res:
	NOP
IRQ:
	LDR	PC, IRQ_handler_Addr
FIQ:
	LDR	PC, FIQ_handler_Addr

SWI_handler_Addr:
   .long EE_SWI_handler       // Definito in inthand.S
IRQ_handler_Addr:
	.long	EE_IRQ_handler			// Definito in inthand.S
FIQ_handler_Addr:
	.long	EE_FIQ_handler			// Definito in inthand.S
Start_Addr:
	.long	Start
	
	

__vectorend:

	.text
// 
// ENTRY POINT
//
	// initialization code is in ARM-mode
	.arm
	
	
	
Start:
	/*
	 * Enter SVC mode and set up the SVC stack pointer
	 */
	MOV     R0, #Mode_SVC | I_bit | F_bit /* No interrupts */
	MSR     cpsr, R0
	LDR     SP, =__TMP_STACK_ADDRESS		// defined in tests/triscend/fp/cfg_triscend.h

	/*
	 * We setup a tempory stack above
	 * so we can now call the SDRAM
	 * init function which is written 
	 * in 'C'
	 */    

//#if A7HAL_USE_SDRAM
	BL	EE_sdram_init			// definito in initdrvs.c
//#endif


/*
 * Copy the executable image into SDRAM or
 * scratchpad from FLASH if the target is flash or flash_internal.
 */
#ifdef __FLASH__
	MOV	R0,#0x00000000
	LDR	R1,=__PSEUDO_EXEC_ADDRESS
	LDR	R2,=__BSS_START
l:
	LDR	R3,[R0],#4
	STR	R3,[R1],#4
	CMP	R0,R2
	BLT	l
#endif


	/*
	 * Make sure we are running from the physical
	 * address, so that we can map the correct
	 * memory type to address 0x00000000.
	 */
	LDR	R0,=__PSEUDO_EXEC_ADDRESS
	LDR	R1,=HiAddress
	ADD	R0,R0,R1
	MOV     PC,R0 
HiAddress:
	/*
	 * Alias the the RW memory to 0x00000000
	 */
	LDR	R0,=REMAP_ALIAS_ENABLE_REG
        LDR	R1,=__ALIAS_SETTING
	STR	R1,[r0,#0]

	LDR     PC, =LoAddress
LoAddress:
	/* Now running from the alias address */

	/*
	 * Initialise memory required by C code
	 */    
//	LDR	r0, =__DATA_ROM
//	LDR	r1, =__DATA_RAM
	LDR	r3, =__BSS_START
//	CMP	r0, r1		nei casi di flash_exec o flash_exec_internal
//	BEQ	NoCopy		copia solo i dati (e non testo) da flash a RAM
//Copy:
//	CMP     r1, r3
//	LDRCC   r2, [r0], #4
//	STRCC   r2, [r1], #4
//	BCC     Copy
//NoCopy:
	LDR     r1, =__BSS_END
	MOV     r2, #0
ZeroBSS:
	CMP	r3, r1
	STRCC	r2, [r3], #4
	BCC	ZeroBSS


#ifdef __OO_ORTI_STACK__
	// Manage the stack fillpattern
	LDR   	r0, =EE_ORTI_STACK_TOP
	LDR   	r1, =EE_ORTI_STACK_BOTTOM
	LDR	r2, =EE_ORTI_STACK_FILLPATTERN

_init_stack_fillpattern:
    	// Set up Stack Fill Pattern
    	STR	r2, [r1], #4 	
    	CMP	r1, r0
    	BCC	_init_stack_fillpattern
#endif


	//
	// Stack pointer "set up" 
	//
	
	// Supervisor mode (SWI) stack pointer
 	MOV	r0, #Mode_SVC | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__SVC_STACK_ADDRESS
   	
 	// IRQ mode stack pointer
 	MOV	r0, #Mode_IRQ | I_bit | F_bit
 	MSR	cpsr_c, r0
   	LDR	sp, =__IRQ_STACK_ADDRESS


	// System mode stack pointer
	// note: now we can enable the interrupts
 	MOV	r0, #Mode_SYS
 	MSR	cpsr_c, r0
 	LDR	sp, =__SYS_STACK_ADDRESS
	
	//
	// NOTE: now we are in SYS-mode! 
	//

	// main() thread "activation".
	// We are in System-mode and ARM-mode.
  	B	main

	
	.end
	
