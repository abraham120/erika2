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
 * Author: 2002- Paolo Gai
 *
 * CVS: $Id: ee_oo.S,v 1.3 2008/06/17 12:33:47 pj Exp $
 */

#include	"cpu/pic30/inc/ee_compiler.h"

	.global	_EE_pic30_terminate_task
	.global _EE_pic30_terminate_savestk

	.text

	// w0 = &terminate_data[t]
	// w1 = terminate_real_th_body[t]()
	// .type	EE_pic30_terminate_savestk, #function
_EE_pic30_terminate_savestk:
	// save some registers:
	// - w0-w7 do not need to be saved (caller saved)
	// - w8-w14 have to be saved (callee saved)
	// Please note that the interrupt are ENABLED
        mov.d   w8,[w15++]
        mov.d   w10,[w15++]
        mov.d   w12,[w15++]
        mov     w14,[w15++]

	// save sp in terminate_data[t]
	mov w15, [w0]

	// save ourselves in the case the user forgets a TerminateTask
	// at the end of the task body (first part)
	mov	w0, w8

	// jmp terminate_real_th_body[t]
	call w1

	// save ourselves in the case the user forgets a TerminateTask
	// at the end of the task body (second part)
	mov	w8, w0

	//.size	EE_pic30_terminate_savestk, . - EE_pic30_terminate_savestk

	// r0 = &terminate_data[t]
	//.type	EE_pic30_terminate_task, #function
_EE_pic30_terminate_task:
	// reload sp from terminate_data[t]
	mov [w0], w15
	// reload the registers saved before
        mov     [--w15],w14
        mov.d   [--w15],w12
        mov.d   [--w15],w10
        mov.d   [--w15],w8
	// return back to the caller
	return
	//.size	EE_pic30_terminate_task, . - EE_pic30_terminate_task

	.end
