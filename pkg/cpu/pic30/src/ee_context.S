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

/**
	@file ee_context.S
	@brief Context switch function for multistack on dsPIC Implementation
	of EE_std_change_context() as described in
	pkg/cpu/common/inc/ee_context.h
	@author Giuseppe Serano
	@date 2011
*/

/* the define is needed for binary distributions */
#define	__EECFG_THIS_IS_ASSEMBLER__
#include	"eecfg.h"

/*

Pseudo code for EE_std_change_context():
  begin:
    tos_index = EE_std_thread_tos[tid+1];
    if is_not_the_current_stack(tos_index) {
      save_caller_saved_registers();
      switch_stacks(tos_index);
      restore_caller_saved_registers();
    }
    if (is_not_marked_stacked(tid)) {
      tid = EE_std_run_task_code(tid);
      goto begin;
    }

*/
	.text

	.extern	_EE_pic30_system_tos
	.extern	_EE_pic30_thread_tos
	.extern	_EE_pic30_active_tos
	.extern	_EE_std_run_task_code

	.extern	_EE_pic30_system_splim

	.global	_EE_std_change_context
//	.type	EE_std_change_context, @function
_EE_std_change_context:
	// w0 == tid

	/* tos_index = EE_pic30_thread_tos[tid+1] */
	sl	w0, w2
	add	#2, w2
	mov	w0, w1				// w1 == tid
	mov	#_EE_pic30_thread_tos, w3
	mov	[w2 + w3], w0			// w0 == tos_index

	/* if is_not_the_current_stack(tos_index) { */
	cp	_EE_pic30_active_tos
	bra	z, 1f

	/* save_caller_saved_registers() */
	mov.d	w8, [w15++]
	mov.d	w10, [w15++]
	mov.d	w12, [w15++]
	mov	w14, [w15++]

	/* switch_stacks(tos_index) */
	// EE_pic30_system_tos[EE_pic30_active_tos] = stack pointer;
	mov	#_EE_pic30_system_tos, w3
	mov	_EE_pic30_active_tos, w4
	sl	w4, w4
	mov	w15, [w4+w3]
	// EE_pic30_active_tos = tos_index (tos_index is in w0)
	mov	w0, _EE_pic30_active_tos
	// stack pointer = EE_pic30_system_tos[tos_index]
	sl	w0, w0
#ifdef __PIC30_SPLIM__
	mov	#_EE_pic30_system_splim, w4
	mov	[w0 + w4], w4
	mov	w4, _SPLIM
	// the next operation cannot do an access based on w15
#endif
	mov	[w0 + w3], w15

	/* restore_caller_saved_registers() */
	mov	[--w15], w14
	mov.d	[--w15], w12
	mov.d	[--w15], w10
	mov.d	[--w15], w8

	/* } */
1:	mov	w1, w0				// w0 == tid

	/* if (is_not_marked_stacked(tid)) { */
	cp0	w0
	bra	N, 2f

	/* tid = EE_std_run_task_code(tid) */
	call	_EE_std_run_task_code

	/* goto begin */
	bra	_EE_std_change_context

	/* } */
2:	return

	.end
