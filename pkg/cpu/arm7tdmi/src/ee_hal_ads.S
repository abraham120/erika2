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
 * Author: 2001-2002 Alessandro Colantonio
 *         2002- Paolo Gai
 *
 * CVS: $Id: ee_hal_ads.S,v 1.1 2006/10/25 14:01:21 pj Exp $
 */

/* the define is needed for binary distributions */
#define __EECFG_THIS_IS_ASSEMBLER__
#include "eecfg.h"
	
#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"


	EXPORT EE_arm7_hal_ready2stacked

#ifdef __MULTI__
	EXPORT EE_arm7_hal_stkchange

	IMPORT EE_arm7_system_tos
	IMPORT EE_arm7_active_tos
	
	IMPORT EE_hal_endcycle_next_tos
#endif
	IMPORT EE_thread_end_instance
	IMPORT EE_hal_endcycle_next_thread

			
	AREA    text, CODE, READONLY


#ifdef __MULTI__

	
// 
// This code is called when we have to change the thread stack
// NOTE: r1 *MUST* contain tos_index, while r0 (the thread address)
// will be unchanged!!!
//

// TOBEDONE: probably some of these instructions can be remixed to
//           make efficient use of the ARM pipelining!!!
EE_arm7_change_tos	
	// if tos_index == EE_arm7_active_tos then we do not have to
	// switch stack
	LDR	r2, =EE_arm7_active_tos
	LDR	r3, [r2]

	CMP	r3, r1
	MOVEQ	pc, lr

	// Before changing the stack, we have to save the registers
	// that could be modified (i.e. all the registers that should
	// be preserved through function calls). Note that if there is
	// not the stack change, the system will behave like the
	// monostack version of the kernel
 	STMFD	sp!, {r4-r11}

	// from now until the LDMFD I can use r0-r11 as scratch!
	// r2=&EE_arm7_active_tos
	// r4=&EE_arm7_system_tos
	
	//
	// Save current TOS
	//
	// r4 = &EE_arm7_system_tos
	LDR	r4, =EE_arm7_system_tos
	// r3 = & EE_arm7_system_tos[EE_arm7_active_tos].SYS_tos
	ADD	r3, r4, r3, LSL#2

	// EE_arm7_system_tos[EE_arm7_active_tos].SYS_tos = sp_SYS
	STR	sp, [r3]

	//
	// New current TOS
	//
	// remember that r4 = &EE_arm7_system_tos
	// r3 = & EE_arm7_system_tos[tos_index].SYS_tos
	ADD	r3, r4, r1, LSL#2

	// sp_SYS = EE_arm7_system_tos[tos_index].SYS_tos
	LDR	sp, [r3]
	
	//
	// Update arm7_active_tos (= tos_index)
	//
	// remember that r2=&EE_arm7_active_tos
	STR	r1, [r2]

	// Here we have to restore the registers saved before the
	// stack previous change. If this is the first time we use the
	// current stack, restoring is useless... (see also inithal.c
	// into the directories EE/tests/arm7xxxx)
 	LDMFD	sp!, {r4-r11}
	
	MOV	pc, lr

	
	
//
// MONO:  not defined
// MULTI: void EE_arm7_hal_stkchange(EE_UREG 0, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement a blocking
// synchronization primitive.
//

EE_arm7_hal_stkchange
        
        // Mk: saving lr here and restoring it after EE_arm7_change_tos is mandatory, in order to
        // save lr of the preempted thread and to restore lr of the preempter thread
        //      from their respective stacks!
        STMFD   sp!, {lr}

        // switch to the TOS of the new thread
        BL      EE_arm7_change_tos

        // now the stack is changed, and we need to return to the interrupted thread!
        LDMFD   sp!, {lr}
        BX      lr


#endif // __MULTI__

	
//
// MONO:  void EE_arm7_hal_ready2stacked(ADDR thread_addr)
// MULTI: void EE_arm7_hal_ready2stacked(ADDR thread_addr, EE_UREG tos_index)
//
// Typically called into a generic primitive to implement preemption.
//

EE_arm7_hal_ready2stacked
	// we have to save LR into the stack (APCS standard)
 	STMFD	sp!, {lr}
EE_arm7_hal_ready2stacked_start	
#ifdef __MULTI__
	// (eventually) switch to the TOS of the new thread
	BL	EE_arm7_change_tos
#endif
	
	//
	// Before calling the new thread we have to enable interrupts. 
	// Note that only arithmetic flag field of CPSR can be set
	// with immediate value (we use LR because we saved its content)
	//
	MOV	lr, #Mode_SYS
 	MSR	cpsr_c, lr

	// jump to the preempter thread (r0 = first parameter)
	MOV	lr, pc
	BX	r0

	// NOTE: we have to disable interrupts here before calling
	// EE_thread_end_instance() because it is a primitive
	MOV	lr, #Mode_SYS | I_bit
 	MSR	cpsr_c, lr
	
	// call the scheduler 
	BL	EE_thread_end_instance

	// note that interrupts are disabled here
	
	//
	// if EE_hal_endcycle_next_thread == 0
	//   then wake up the preempted thread
	//   (EE_arm7_hal_endcycle_stacked executed)
	//
	// if EE_hal_endcycle_next_thread != 0
	//   then activate a new thread
	//   (EE_arm7_hal_endcycle_ready executed)
	//
#ifdef __MULTI__
	LDR	r2, =EE_hal_endcycle_next_tos
	LDR	r1, [r2]
#endif
	
	LDR	r2, =EE_hal_endcycle_next_thread
	LDR	r0, [r2]

	CMP	r0, #0
	BNE	EE_arm7_hal_ready2stacked_start

	// (eventually) switch to the TOS of the preempted thread
#ifdef __MULTI__
	BL	EE_arm7_change_tos
#endif
	
	// Keep interrupts disabled !!!
	// we always return into a primitive or into an IRQ handler...
	
	//
	// return to the interrupted thread
	//
	LDMFD	sp!, {lr}
	BX	lr
		
		
	END
