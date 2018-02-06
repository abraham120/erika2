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
 * Author: 2004- Antonio Fiaschi
 *
 * CVS: $Id: ee_oo.S,v 1.1 2005/07/16 12:53:15 pj Exp $
 */

#include "cpu/mpc5xx/inc/ee_compiler.h"
#include "cpu/mpc5xx/inc/ee_macro.h"

	.global	EE_mpc5_terminate_task
	.global EE_mpc5_terminate_savestk
	
	.text

	// r3 = &terminate_data[t]
	// r4 = terminate_real_th_body[t]()
	.type	EE_mpc5_terminate_savestk, @function
EE_mpc5_terminate_savestk:
	// save some registers:	
	// - r0-r12 do not need to be saved 9they are already dirty
	//   with the call to this function;
	// - r13-r31 have to be saved because they maybe contain some
	//   data of the preempted threads
	// - lr has to be saved to be able to jump back to the thread final }
	//   in the thread stub into tstub.h
	// - only the data from the System level have to be saved, the others
	//   will be restored when needed directly by the prempter 
	//   threads/irqs
	//
	// Please note that the interrupt are ENABLED
	stwu	sp, -88(sp)
	mtlr	r0
	stw	r0, 4(sp)
	mtmsr	r0
	stw	r0, 8(sp)
#ifndef	DEBUG
	stmw	r13, 12(sp)
#else
	stw	r13, 12(sp)
	stw	r14, 16(sp)
	stw	r15, 20(sp)
	stw	r16, 24(sp)
	stw	r17, 28(sp)
	stw	r18, 32(sp)
	stw	r19, 36(sp)
	stw	r20, 40(sp)
	stw	r21, 44(sp)
	stw	r22, 48(sp)
	stw	r23, 52(sp)
	stw	r24, 56(sp)
	stw	r25, 60(sp)
	stw	r26, 64(sp)
	stw	r27, 68(sp)
	stw	r28, 72(sp)
	stw	r29, 76(sp)
	stw	r30, 80(sp)
	stw	r31, 84(sp)
#endif

	// save sp_sys in terminate_data[t]
	stw	sp, 0(r3)
	
	// jmp terminate_real_th_body[t]
	mtctr	r4
	bctr
	
	.size	EE_mpc5_terminate_savestk, . - EE_mpc5_terminate_savestk

	// r3 = &terminate_data[t]
	.type	EE_mpc5_terminate_task, @function
EE_mpc5_terminate_task:
	// reload sp_sys from terminate_data[t]	
	lwz	sp, 0(r3)

	// reload the registers saved before
	lwz	r0, 4(sp)
	mtlr	r0
	lwz	r0, 8(sp)
	mtmsr	r0
#ifndef	DEBUG
	lmw	r13, 12(sp)
#else
	lwz	r13, 12(sp)
	lwz	r14, 16(sp)
	lwz	r15, 20(sp)
	lwz	r16, 24(sp)
	lwz	r17, 28(sp)
	lwz	r18, 32(sp)
	lwz	r19, 36(sp)
	lwz	r20, 40(sp)
	lwz	r21, 44(sp)
	lwz	r22, 48(sp)
	lwz	r23, 52(sp)
	lwz	r24, 56(sp)
	lwz	r25, 60(sp)
	lwz	r26, 64(sp)
	lwz	r27, 68(sp)
	lwz	r28, 72(sp)
	lwz	r29, 76(sp)
	lwz	r30, 80(sp)
	lwz	r31, 84(sp)
#endif

	// return back to the caller (in tstub.c!!!)
	blr
	.size	EE_mpc5_terminate_task, . - EE_mpc5_terminate_task
	
	.end
