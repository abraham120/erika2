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
 * Author:   Antonio Romano
 * CVS: $Id: stackManage.S,v 1.2 2006/08/02 11:46:58 romano Exp $
 */

#ifndef __INCLUDE_STACKMANAGE__
#define __INCLUDE_STACKMANAGE__

#ifdef __MULTI__
.macro changestack

	//save working registers of preempted thread

    	push r2		
	push r3		
	push r4		
	push r5		
   	push r6 	
	push r7		
	push r8		
	push r9	
	push r10	
	push r11		
	push r12	
	push r13	
   	push r14	
	push r15		
	push r16	
	push r17		
	push r28	
	push r29
	

	// from now i can use r2-r17 as scratch!
	// r31:r30 = &EE_avr5_active_tos
	
	
	//save SREG	
	
	in r2, 0x3F  //SREG address
	push r2

		
	// Save current TOS
	//
	// r28:r29 = &EE_avr5_system_tos/*/


	in r16, 0x3D	//SPL address
	in r17, 0x3E	//SPH address

	ldi r28, lo8(EE_avr5_system_tos)
	ldi r29, hi8(EE_avr5_system_tos) 

	

	//multiply r18 by 2

	clr r5
	lsl r18
	add r28, r18
	adc r29, r5
	st Y+, r16
	st Y,  r17 		//now Y point to active_tos index
		
	/*/
	// 
	//New current TOS
	//
	/*/
	
	ldi r28,  lo8(EE_avr5_system_tos)
	ldi r29,  hi8(EE_avr5_system_tos) 
	mov r20, r22
	lsl r20
	add r28, r20
	adc r29, r5
	ld  r16, Y+    // Y = r29:r28
	ld  r17, Y	
	out 0x3D, r16  
	out 0x3E, r17		//now SP point to the stack of preempter thread
	

	st Z, r22
	
	/*/
	// Here we have to restore the registers saved before the
	// stack previous change. If this is the first time we use the
	// current stack, restoring is useless...
	/*/
     
	pop r1
	out 0x3F, r1  //restore SREG
	
	//restore working registers
	pop r29
	pop r28
	pop r17
	pop r16
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
.endm	


#ifdef __IRQ_STACK_NEEDED__



.macro EE_avr5_change_from_irq_tos

	// load EE_avr5_temp_tos address memory within r31:r30 (Z)
	ldi r30, lo8(EE_avr5_temp_tos)
	ldi r31, hi8(EE_avr5_temp_tos) 

	//load in r20:r21 the content of EE_avr5_temp_tos location

	ld r20, Z+
	ld r21, Z
	
	// store in SP the content of r20:r21 

	out 0x3D, r20  
	out 0x3E, r21	

	// now SP point to the stack of interrupted thread
		
.endm		
	
.macro EE_avr5_change_to_irq_tos
	
	// load EE_avr5_temp_tos address memory within r31:r30 (Z)
	ldi r30, lo8(EE_avr5_temp_tos)
	ldi r31, hi8(EE_avr5_temp_tos) 

	//load the stack pointer state within r21:r20	

	in r20, 0x3D	//SPL address
	in r21, 0x3E	//SPH address
	
	// store within data memory the tos of interrupted thread 

	st Z+, r20
	st Z, r21

	// load 	

	ldi r30, lo8(EE_avr5_IRQ_tos)
	ldi r31, hi8(EE_avr5_IRQ_tos) 
	
	ld  r20, Z+    
	ld  r21, Z	

	out 0x3D, r20  
	out 0x3E, r21		//now SP point to the stack of IRQ

	.endm

#endif  //irq_stack_needed
#endif  //multi
#endif 
