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
 * CVS: $Id: ee_irqvect.S,v 1.16 2006/01/24 10:44:26 pj Exp $
 */

#include "cpu/mpc5protected/inc/ee_macro.h"

	.extern _start
	.extern EE_IRQ_end_instance

	.extern EE_mpc5_system_tos
	.extern EE_mpc5_handler_tos

	.extern EE_hal_endcycle_next_appl
	.extern EE_hal_endcycle_next_thread
	.extern EE_hal_endcycle_next_stack
	.extern EE_hal_endcycle_next_body
	.extern EE_hal_endcycle_protection

	.extern EE_hal_stub_end_instance
	.extern	EE_hal_stub_IRQ_epilogue

	.extern EE_mpc5_active_thread
	.extern EE_mpc5_active_application
	.extern EE_mpc5_active_tos

	.extern EE_mpc5_system_stack
	.extern EE_mpc5_IRQ_tos

	.extern EE_hal_system_call
	.extern EE_hal_IRQ_handler

	.extern EE_IRQ_nesting_level
	.extern EE_IRQ_handler_active

	.global	EE_IRQ_epilogue

	.text

	.equ	SIVEC,	0x2fc01c
	.equ	SIMASK,	0x2fc014

//	0x0100 System Reset Exception
	EXCEPTION_ENTRY(0x0100,SystemReset)
#ifdef DEBUG
	STND_HANDLER(SystemReset)
#else
	STND_HANDLER
#endif

//	0x0200 Machine Check Exception
	EXCEPTION_ENTRY(0x0200,MachineCheck)
#ifdef DEBUG
	STND_HANDLER(MachineCheck)
#else
	STND_HANDLER
#endif

//	0x0300 Data Storage Exception
	EXCEPTION_ENTRY(0x0300,DataStorage)
#ifdef DEBUG
        STND_HANDLER(DataStorage)
#else
        STND_HANDLER
#endif

//      0x0400 Instruction Storage Exception
//	This exception is reserved

//      0x0500 External Interrupt Exception
        EXCEPTION_ENTRY(0x0500,ExternalInterrupt)
	// Salvo il contesto del thread interrotto
        stwu    sp, -160(sp)
        stw     r0, 32(sp)        // r0
        mflr    r0
        stw     r0, 16(sp)        // lr
        mfsrr0  r0
        stw     r0, 8(sp)         // srr0
        mfsrr1  r0
        stw     r0, 12(sp)        // srr1
        mfxer   r0
        stw     r0, 20(sp)        // xer
        mfctr   r0
        stw     r0, 24(sp)        // ctr
        mfcr    r0
        stw     r0, 28(sp)        // cr
#ifndef	DEBUG
        stmw    r2, 36(sp)
#else
	stw    r2, 36(sp)
	stw    r3, 40(sp)
	stw    r4, 44(sp)
	stw    r5, 48(sp)
	stw    r6, 52(sp)
	stw    r7, 56(sp)
	stw    r8, 60(sp)
	stw    r9, 64(sp)
	stw    r10, 68(sp)
	stw    r11, 72(sp)
	stw    r12, 76(sp)
	stw    r13, 80(sp)
	stw    r14, 84(sp)
	stw    r15, 88(sp)
	stw    r16, 92(sp)
	stw    r17, 96(sp)
	stw    r18, 100(sp)
	stw    r19, 104(sp)
	stw    r20, 108(sp)
	stw    r21, 112(sp)
	stw    r22, 116(sp)
	stw    r23, 120(sp)
	stw    r24, 124(sp)
	stw    r25, 128(sp)
	stw    r26, 132(sp)
	stw    r27, 136(sp)
	stw    r28, 140(sp)
	stw    r29, 144(sp)
	stw    r30, 148(sp)
	stw    r31, 152(sp)
#endif
                                                                                
        // Devo salvare il _tos_ : non modifico r1
	// Ho interrotto un thread o un handler?
	lis	r9, EE_IRQ_nesting_level@ha
	la	r16, EE_IRQ_nesting_level@l(r9)
	lwz	r0, 0(r16)

	cmpwi	r0, 0
	bne	1f

	// Ho interrotto un thread
        lis     r9, EE_mpc5_active_tos@ha
        lwz     r7, EE_mpc5_active_tos@l(r9)
        slwi    r8, r7, 3
        lis     r9, EE_mpc5_system_tos@ha
        la      r10, EE_mpc5_system_tos@l(r9)
        add     r10, r10, r8
	b	2f

1:	// Ho interrotto un handler
	lis	r9, EE_IRQ_handler_active@ha
	la	r15, EE_IRQ_handler_active@l(r9)
	lwz	r7, 0(r15)
	lis	r9, EE_mpc5_handler_tos@ha
	la	r10, EE_mpc5_handler_tos@l(r9)

	slwi	r8, r7, 1		// <---------------------------------
	add	r10, r8, r10
2:	stw	sp, 0(r10)

	b	switch_on_stack


//      0x0600 Alignment Exception
        EXCEPTION_ENTRY(0x0600,Alignment)
#ifdef DEBUG
        STND_HANDLER(Alignment)
#else
        STND_HANDLER
#endif


//      0x0700 Program Exception
        EXCEPTION_ENTRY(0x0700,ProgramCheck)
#ifdef DEBUG
        STND_HANDLER(ProgramCheck)
#else
        STND_HANDLER
#endif


//      0x0800 Floating-point Unavailable Exception
        EXCEPTION_ENTRY(0x0800,FPUnavailable)
#ifdef DEBUG
        STND_HANDLER(FPUnavailable)
#else
        STND_HANDLER
#endif


//      0x0900 Decrementer Exception
        EXCEPTION_ENTRY(0x0900,Decrementer)
#ifdef DEBUG
        STND_HANDLER(Decrementer)
#else
        STND_HANDLER
#endif

//      0x0A00 Reserved
//	Reserved exception

//	0x0B00 Reserved
//	Reserved exception

//      0x0C00 System Call Exception
        EXCEPTION_ENTRY(0x0C00,SystemCall)

	stwu	sp, -160(sp)
	stw	r0, 32(sp)	// r0
	mflr	r0
	stw	r0, 16(sp)	// lr
	mfsrr0	r0
	stw	r0, 8(sp)	// srr0
	mfsrr1	r0
	stw	r0, 12(sp)	// srr1
	mfxer	r0
	stw	r0, 20(sp)	// xer
	mfctr	r0
	stw	r0, 24(sp)	// ctr
	mfcr	r0
	stw	r0, 28(sp)	// cr
#ifndef	DEBUG
        stmw    r2, 36(sp)
#else
	stw    r2, 36(sp)
	stw    r3, 40(sp)
	stw    r4, 44(sp)
	stw    r5, 48(sp)
	stw    r6, 52(sp)
	stw    r7, 56(sp)
	stw    r8, 60(sp)
	stw    r9, 64(sp)
	stw    r10, 68(sp)
	stw    r11, 72(sp)
	stw    r12, 76(sp)
	stw    r13, 80(sp)
	stw    r14, 84(sp)
	stw    r15, 88(sp)
	stw    r16, 92(sp)
	stw    r17, 96(sp)
	stw    r18, 100(sp)
	stw    r19, 104(sp)
	stw    r20, 108(sp)
	stw    r21, 112(sp)
	stw    r22, 116(sp)
	stw    r23, 120(sp)
	stw    r24, 124(sp)
	stw    r25, 128(sp)
	stw    r26, 132(sp)
	stw    r27, 136(sp)
	stw    r28, 140(sp)
	stw    r29, 144(sp)
	stw    r30, 148(sp)
	stw    r31, 152(sp)
#endif

	// Devo salvare il _tos_ : non modifico r1

	lis	r9, EE_IRQ_nesting_level@ha
	lwz	r2, EE_IRQ_nesting_level@l(r9)

	cmpwi	r2, 0
	beq	1f
	// La primitiva e` stata invocata da un handler
        lis     r9, EE_IRQ_handler_active@ha
        lwz	r7, EE_IRQ_handler_active@l(r9)
        lis     r9, EE_mpc5_handler_tos@ha
        la      r10, EE_mpc5_handler_tos@l(r9)
                                                                                
        slwi    r8, r7, 1		// <---------------------------
        add     r10, r8, r10
	b	2f

1:	// La primitiva e` stata invocata da un thread
	lis	r9, EE_mpc5_active_tos@ha
	lwz	r0, EE_mpc5_active_tos@l(r9)
	slwi	r0, r0, 3
	lis	r9, EE_mpc5_system_tos@ha
	la	r10, EE_mpc5_system_tos@l(r9)
	add	r10, r10, r0
2:	
	stw	sp, 0(r10)
	// Now context are saved. I restore SP and before I can
	// switch stack
	// *********************************************************
	
	lis	r9, EE_mpc5_system_stack@ha
	lwz	sp, EE_mpc5_system_stack@l(r9)

	slwi	r11, r11, 2
	add	r11, r11, r0
	lwz	r0, 0(r11)
	mtlr	r0
	blrl
	b	continue


//      0x0D00 Trace Exception
        EXCEPTION_ENTRY(0x0D00,Trace)
#ifdef DEBUG
        STND_HANDLER(Trace)
#else
        STND_HANDLER
#endif


//      0x0E00 Floating-point Assist Exception
        EXCEPTION_ENTRY(0x0E00,FPAssist)
#ifdef DEBUG
        STND_HANDLER(FPAssist)
#else
        STND_HANDLER
#endif


//      0x1000 Software Emulation Exception
        EXCEPTION_ENTRY(0x1000,SoftwareEmulation)
#ifdef DEBUG
        STND_HANDLER(SoftwareEmulation)
#else
        STND_HANDLER
#endif


//      0x1100 Reserved
//	Reserved exception


//      0x1200 Reserved
//	Reserved exception


//      0x1300 Instruction Protection Exception
        EXCEPTION_ENTRY(0x1300,Protection)
#ifdef DEBUG
        STND_HANDLER(InstructionProtection)
#else
        STND_HANDLER
#endif


//      0x1400 Data Protection Exception
        EXCEPTION_ENTRY(0x1400,DataProtection)
#ifdef DEBUG
        STND_HANDLER(DataProtection)
#else
        STND_HANDLER
#endif


//	1500 to 1B00 Reserved


//      0x1C00 Data Breakpoint Exception
        EXCEPTION_ENTRY(0x1C00,DataBreakpoint)
#ifdef DEBUG
        STND_HANDLER(DataBreakpoint)
#else
        STND_HANDLER
#endif


//      0x1D00 Instruction Breakpoint Exception
        EXCEPTION_ENTRY(0x1D00,InstructionBreakpoint)
#ifdef DEBUG
        STND_HANDLER(InstructionBreakpoint)
#else
        STND_HANDLER
#endif


//      0x1E00 Maskable External Breakpoint Exception
        EXCEPTION_ENTRY(0x1E00,MaskExtBreakpoint)
#ifdef DEBUG
        STND_HANDLER(MaskExtBreakpoint)
#else
        STND_HANDLER
#endif


//      0x1F00 Non-maskable External Breakpoint Exception
        EXCEPTION_ENTRY(0x1F00,NonMaskExtBreakpoint)
#ifdef DEBUG
        STND_HANDLER(NonMaskExtBreakpoint)
#else
        STND_HANDLER
#endif

	END_EXCEPTION_TABLE(0x2000)

//****************************************************************

continue:
	// Return here from primitive
	// Storing return values in the calle_thread context
	lis	r9, EE_IRQ_nesting_level@ha
	lwz	r0, EE_IRQ_nesting_level@l(r9)
	cmpwi	r0, 0
	beq	1f
	// handler
	lis	r9, EE_IRQ_handler_active@ha
	lwz	r10, EE_IRQ_handler_active@l(r9)
	slwi	r10, r10, 1	// <--------------------------
	lis	r9, EE_mpc5_handler_tos@ha
	la	r11, EE_mpc5_handler_tos@l(r9)
	add	r11, r10, r11
	lwz	sp, 0(r11)
	// Saving return value of primitive
	stw	r3, 40(sp)
	b	restore // Primi di questa dobbiamo inserire le info di protezione
	
1:	// thread
	lis	r9, EE_mpc5_active_tos@ha
	lwz	r0, EE_mpc5_active_tos@l(r9)
	slwi	r0, r0, r3  	// <--------------------------

	lis	r9, EE_mpc5_system_tos@ha
	la	r10, EE_mpc5_system_tos@l(r9)
	add	r10, r10, r0	// r10 = &EE_mpc5_system_tos[_active_tos]

	lwz	r11, 0(r10)
	stw	r3, 40(r11)

	// r7 = EE_hal_endcycle_next_thread
	lis	r9, EE_hal_endcycle_next_thread@ha
	lwz	r7, EE_hal_endcycle_next_thread@l(r9)
	stw	r7, 32(sp)

	// r0 = EE_mpc5_active_thread
	lis	r9, EE_mpc5_active_thread@ha
	lwz	r0, EE_mpc5_active_thread@l(r9)

	// if (active_thread != next_thread)
	//
	// else
	//	
	cmpw	r0, r7
	beq	no_change_thread

	// Update EE_mpc5_active_thread
	lis	r9, EE_mpc5_active_thread@ha
	la	r10, EE_mpc5_active_thread@l(r9)

	stw	r7, 0(r10)

	// r0 = &EE_mpc5_thread_epilogue
	lis	r9, EE_mpc5_thread_epilogue@ha
	la	r0, EE_mpc5_thread_epilogue@l(r9)
	slwi	r9, r7, 2
	add	r10, r0, r9

	lwz	r9, 0(r10)
	cmpwi	r9, 0
	beq	change_appl
	mtlr	r9
	blrl
	//b	change_appl

change_appl:
	// r8 = EE_hal_endcycle_next_appl
	lis	r9, EE_hal_endcycle_next_appl@ha
	lwz	r8, EE_hal_endcycle_next_appl@l(r9)

	// r10 = &EE_mpc5_active_application
	// r0 = EE_mpc5_active_application
	lis	r9, EE_mpc5_active_application@ha
	la	r10, EE_mpc5_active_application@l(r9)
	lwz	r0, 0(r10)

	cmpw	r0, r8
	beq	change_stack

	// Update EE_mpc5_active_application
	stw	r8, 0(r10)

#ifdef __MEMORY_PROTECTION__

#endif

change_stack:
	// r10 = EE_hal_endcycle_next_body
	lis	r9, EE_hal_endcycle_next_body@ha
	lwz	r10, EE_hal_endcycle_next_body@l(r9)

	cmpwi	r10, 0
	beq	stacked_thread

	// _READY THREAD_
	//  r0 = &EE_mpc5_system_tos
	lis	r9, EE_mpc5_system_tos@ha
	la	r0, EE_mpc5_system_tos@l(r9)

	// r7 = EE_hal_endcycle_next_stack
	lis	r9, EE_hal_endcycle_next_stack@ha
	lwz	r7, EE_hal_endcycle_next_stack@l(r9)

	slwi	r9, r7, 3
	add	r9, r0, r9
	
	lwz	sp, 0(r9)		// Now I'm on user stack

	// Updating EE_mpc5_active_tos
	lis	r9, EE_mpc5_active_tos@ha
	la	r11, EE_mpc5_active_tos@l(r9)

	stw	r7, 0(r11)

	// LR = EE_hal_endcycle_next_body
	mtlr	r10

	lis	r9, EE_hal_stub_end_instance@ha
	la	r10, EE_hal_stub_end_instance@l(r9)

	// SRR0 = &EE_hal_stub_end_instance
	mtsrr0	r10

	lis	r9, EE_hal_endcycle_protection@ha
	lbz	r10, EE_hal_endcycle_protection@l(r9)

	mfsrr1	r0
        li	r3, 2
	slwi	r4, r3, 13
	or	r0, r0, r3
	cmpwi	r10, 1
	beq	1f
	// No protection MSR[PR]=0
	nor	r4, r4, r4
	and	r0, r0, r4
	b	2f
1:      // Protection MSR[PR]=1
	or	r0, r0, r4
2:
	mtsrr1	r0

	b	theend

stacked_thread:
	lis	r9, EE_mpc5_active_tos@ha
	la	r10, EE_mpc5_active_tos@l(r9)

	lis	r9, EE_hal_endcycle_next_stack@ha
	lwz	r0, EE_hal_endcycle_next_stack@l(r9)

	stw	r0, 0(r10)
	
no_change_thread:
	// Non togliere la duplicazione su active_thread perche` ci
	// posso arrivare da piu` parti....
	lis	r9, EE_mpc5_active_tos@ha
	lwz	r0, EE_mpc5_active_tos@l(r9)
	slwi	r0, r0, 3
	lis	r9, EE_mpc5_system_tos@ha
	la	r10, EE_mpc5_system_tos@l(r9)
	add	r10, r10, r0

	lwz	sp, 0(r10)	
restore:
	lwz	r0, 8(sp)
	mtsrr0	r0
	lwz	r0, 12(sp)
	mtsrr1	r0
	lwz	r0, 16(sp)
	mtlr	r0
	lwz	r0, 20(sp)
	mtxer	r0
	lwz	r0, 24(sp)
	mtctr	r0
	lwz	r0, 28(sp)
	mtcr	r0
	lwz	r0, 32(sp)
#ifndef	DEBUG
	lmw	r2, 36(sp)
#else
	lwz	r2, 36(sp)
	lwz	r3, 40(sp)
	lwz	r4, 44(sp)
	lwz	r5, 48(sp)
	lwz	r6, 52(sp)
	lwz	r7, 56(sp)
	lwz	r8, 60(sp)
	lwz	r9, 64(sp)
	lwz	r10, 68(sp)
	lwz	r11, 72(sp)
	lwz	r12, 76(sp)
	lwz	r13, 80(sp)
	lwz	r14, 84(sp)
	lwz	r15, 88(sp)
	lwz	r16, 92(sp)
	lwz	r17, 96(sp)
	lwz	r18, 100(sp)
	lwz	r19, 104(sp)
	lwz	r20, 108(sp)
	lwz	r21, 112(sp)
	lwz	r22, 116(sp)
	lwz	r23, 120(sp)
	lwz	r24, 124(sp)
	lwz	r25, 128(sp)
	lwz	r26, 132(sp)
	lwz	r27, 136(sp)
	lwz	r28, 140(sp)
	lwz	r29, 144(sp)
	lwz	r30, 146(sp)
	lwz	r31, 152(sp)
#endif
	lwz	sp, 0(sp)
theend:
	rfi
	
//*************** IRQ **********************

switch_on_stack:
	// Ora devo switchare sullo stack IRQ
	lis	r9, EE_mpc5_IRQ_tos@ha
	la	r10, EE_mpc5_IRQ_tos@l(r9)
	lwz	sp, 0(r10)

	// Se ho interrotto un handler devo salvarmi il suo ID
	// r0 = EE_IRQ_nesting_level
	cmpwi	r0, 0
	beq	1f

	// Ho interrotto un handler
	// Salvo il suo numero d'ordine
	stw	r7, -4(sp)
	addi	sp, sp, -4
	// Aggiorno EE_mpc5_IRQ_tos
	stw	sp, 0(r10)

1:
	// Incremento il nesting_level
	//lis	r9, EE_IRQ_nesting_level@ha
	//la	r10, EE_IRQ_nesting_level@l(r9)
	addi	r0, r0, 1
	stw	r0, 0(r16)

        // Calling the appropriate handler
        // r0 = &EE_hal_IRQ_handler
        lis     r9, EE_hal_IRQ_handler@ha
        la      r0, EE_hal_IRQ_handler@l(r9)

	lis	r9, SIVEC@ha
	lbz	r11, SIVEC@l(r9)

	// Aggiorno handler_active
	lis	r9, EE_IRQ_handler_active@ha
	la	r10, EE_IRQ_handler_active@l(r9)
	stw	r11, 0(r10)

	slwi	r12, r11, 1

	add	r12, r0, r12
	lwz	r0, 0(r12)
        mtlr    r0

	// Ora devo discriminare tra handler di tipo 1 ed handler di
	// tipo 2: nel primo caso devo solo saltare all'handler
	// mentre nel secondo devo eseguire una RFI

	lbz	r0, 4(r12)
	cmpwi	r0, 1
	bne	no_protection

	lis	r9, EE_hal_stub_IRQ_epilogue@ha
	la	r10, EE_hal_stub_IRQ_epilogue@l(r9)
	mtsrr0	r10

	// Devo caricare le informazioni sullo _stack_ e sui _segmenti_
	// dell'handler selezionato da EE_mpc5_handler_tos
	lis	r9, EE_mpc5_handler_tos@ha
	la	r10, EE_mpc5_handler_tos@l(r9)
	slwi	r11, r11, 1	// <---------------------------------
	add	r10, r10, r11

	// Now I'm on handler stack
	lwz	sp, 0(r10)
	
	

        mfsrr1  r0
        li      r3, 2
        slwi    r4, r3, 13
        or      r0, r0, r3
        or      r0, r0, r4
        mtsrr1  r0

#ifdef __ALLOW_NESTED_IRQ__
	// I do masking the lowest IRQ
	// and enable IRQ
#endif

#ifdef DEBUG
break_here:
#endif
	rfi

no_protection:

#ifdef __ALLOW_NESTED_IRQ__
	// I do masking the lowest IRQ
	// and enable IRQ
#endif

	blrl

	lis	r9, EE_IRQ_nesting_level@ha
	la	r10, EE_IRQ_nesting_level@l(r9)
	lwz	r0, 0(r10)

	addi	r2, r0, -1
	stw	r2, 0(r10)

	cmpwi	r2, 1
	bne	1f

	lwz	r7, 0(sp)
	addi	sp, sp, 4
	
	lis	r9, EE_IRQ_handler_active@ha
	la	r11, EE_IRQ_handler_active@l(r9)
	stw	r7, 0(r11)

	b	continue

1:	b	no_change_thread

//***********************************************

	.type	EE_IRQ_epilogue, @function
EE_IRQ_epilogue:
	// r0 = EE_IRQ_nesting_level
	lis	r9, EE_IRQ_nesting_level@ha
	la	r10, EE_IRQ_nesting_level@l(r9)
	lwz	r0, 0(r10)

	// Aggiorno il valore di EE_IRQ_nesting_level
	subi	r0, r0, 1
	stw	r0, 0(r10)

	cmpwi	r0, 0
	bne	1f
	// Non ci sono handler interrotti
	// chiamo lo scheduler
	lis	r9, EE_IRQ_end_instance@ha
	la	r10, EE_IRQ_end_instance@l(r9)
	mtlr	r10
	blrl

	b	2f

1:
	// Ci sono handler a priorita` piu` bassa 
	// che sono stati interrotti
	lis	r9, EE_mpc5_IRQ_tos@ha
	la	r11, EE_mpc5_IRQ_tos@l(r9)
	// r2 lo uso come stack pointer per accedere 
	// allo stack IRQ
	lwz	r2, 0(r11)

	lwz	r7, 0(r2)

	addi	r2, r2, 4
	stw	r2, 0(r11)

	lis	r9, EE_IRQ_handler_active@ha
	la	r11, EE_IRQ_handler_active@l(r9)
	stw	r7, 0(r11)

2:	// Ritorno a sys_call
	b	continue

	.size	EE_IRQ_epilogue, . - EE_IRQ_epilogue
