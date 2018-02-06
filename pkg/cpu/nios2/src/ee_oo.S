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
 * Author:	 2004 Paolo Gai
 * CVS: $Id: ee_oo.S,v 1.2 2006/01/24 10:41:12 pj Exp $
 */

#include "cpu/nios2/inc/ee_compiler.h"

	.global	EE_nios2_terminate_task
	.global EE_nios2_terminate_savestk
	
	.text

	// r4 = &terminate_data[t]
	// r5 = terminate_real_th_body[t]()
	.type	EE_nios2_terminate_savestk, @function
EE_nios2_terminate_savestk:
	// save some registers:	
	// - r16-r23 that are the Callee-Saved General-Purpose Registers
	// - fp, ra --> because they were used in longjmp
	// - gp should not be saved, it is used by the compiler!
	// Please note that the interrupt are ENABLED

	addi	sp, sp, -40
        stw     r16, 36(sp)
        stw     r17, 32(sp)
        stw     r18, 28(sp)	
        stw     r19, 24(sp)
        stw     r20, 20(sp)
        stw     r21, 16(sp)
        stw     r22, 12(sp)
        stw     r23, 8(sp)
        stw     fp, 4(sp)
        stw     ra, 0(sp)
	
	
	// save sp in terminate_data[t]
	stw	sp, 0(r4)
	
	// jmp terminate_real_th_body[t]
	jmp	r5
	
	.size	EE_nios2_terminate_savestk, . - EE_nios2_terminate_savestk

	// r4 = &terminate_data[t]
	.type	EE_nios2_terminate_task, @function
EE_nios2_terminate_task:
	// reload sp from terminate_data[t]
	ldw	sp, 0(r4)

	// reload the registers saved before
        ldw     r16, 36(sp)
        ldw     r17, 32(sp)
        ldw     r18, 28(sp)
	ldw     r19, 24(sp)
        ldw     r20, 20(sp)
        ldw     r21, 16(sp)
        ldw     r22, 12(sp)
        ldw     r23, 8(sp)
        ldw     fp, 4(sp)
        ldw     ra, 0(sp)
	addi	sp, sp, 40

	// return back to the caller (in tstub.c!!!)
	ret
	.size	EE_nios2_terminate_task, . - EE_nios2_terminate_task
	
	.end
