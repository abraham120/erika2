// /* ###*B*###
// * ERIKA Enterprise - a tiny RTOS for small microcontrollers
// *
// * Copyright (C) 2002-2008  Evidence Srl
// *
// * This file is part of ERIKA Enterprise.
// *
// * ERIKA Enterprise is free software; you can redistribute it
// * and/or modify it under the terms of the GNU General Public License
// * version 2 as published by the Free Software Foundation, 
// * (with a special exception described below).
// *
// * Linking this code statically or dynamically with other modules is
// * making a combined work based on this code.  Thus, the terms and
// * conditions of the GNU General Public License cover the whole
// * combination.
// *
// * As a special exception, the copyright holders of this library give you
// * permission to link this code with independent modules to produce an
// * executable, regardless of the license terms of these independent
// * modules, and to copy and distribute the resulting executable under
// * terms of your choice, provided that you also meet, for each linked
// * independent module, the terms and conditions of the license of that
// * module.  An independent module is a module which is not derived from
// * or based on this library.  If you modify this code, you may extend
// * this exception to your version of the code, but you are not
// * obligated to do so.  If you do not wish to do so, delete this
// * exception statement from your version.
// *
// * ERIKA Enterprise is distributed in the hope that it will be
// * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// * GNU General Public License version 2 for more details.
// *
// * You should have received a copy of the GNU General Public License
// * version 2 along with ERIKA Enterprise; if not, write to the
// * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// * Boston, MA 02110-1301 USA.
// * ###*E*### */

//! 
//! \file ee_context.S
//! \brief EE_std_change_context (context change) implementation.\n
//! \author Dario Di Stefano
//! \version 0.1
//! \date 2011-01-12
//!

//!  \fn void EE_std_change_context(void)
//!  \brief Context change implementation.
//!  Pseudo code for EE_std_change_context():\n
//!  begin:\n
//!     tos_index = EE_std_thread_tos[tid+1];\n
//!     if is_not_the_current_stack(tos_index) {\n
//!         EE_CHANGE_TOS_MACRO(EE_S12_ACTIVE_TOS, EE_S12_SYSTEM_TOS);\n
//!     }\n
//!     if (is_not_marked_stacked(tid)) {\n
//!         tid = EE_std_run_task_code(tid);\n
//!         goto begin;\n
//!     }\n

// the define is needed for binary distributions
#define	__EECFG_THIS_IS_ASSEMBLER__

#ifdef __CODEWARRIOR__
  #include	"cpu/hs12xs/inc/ee_cpu_cw_utils.h"
#else
  #include	"cpu/hs12xs/inc/ee_cpu_cosmic_utils.h"
#endif

#ifdef __CODEWARRIOR__
.text: SECTION
#else // COSMIC
.ftext:	section	.text
#endif

	xref	EE_S12_SYSTEM_TOS
	xref	EE_S12_ACTIVE_TOS
	xref	EE_S12_THREAD_TOS
	xref	EE_STD_RUN_TASK_CODE

// ---------------------------------------------------------------------------------------------

//	Pseudo code for EE_CHANGE_TOS_MACRO(EE_S12_ACTIVE_TOS, EE_S12_SYSTEM_TOS, tos_index):
//	begin:
//		EE_s12xs_system_tos[EE_s12xs_active_tos] = stack_pointer;
//		EE_s12xs_active_tos = tos_index 
//		stack_pointer = EE_s12xs_system_tos[tos_index]

	EE_CHANGE_TOS_MACRO: macro // this macro needs tos_index in y register
		// EE_s12xs_system_tos[EE_s12xs_active_tos] = stack pointer;
		pshy								// save tos_index on the stack
		tfr STACK_POINTER,d					// I must use d to change the value d-=2 
		addd #2								// d+=2
		tfr d,y								// I can use y because tos_index is saved in the stack...
		ldd \1								// load d with _EE_s12_active_tos
		lsld								// logical shift left (1 bit) on d -> d*=2 (to 16 bit) 
		tfr d,x								// I can't use d in the next operation so d -> x 
		sty \2,x							// store y in _EE_s12_system_tos,x 
OFST:	set	0
		// EE_s12xs_active_tos = tos_index (tos_index is now in w0 and w1)
		puld								// put tos_index in d
		std \1								// change _EE_s12xs_active_tos

		// stack pointer = EE_s12xs_system_tos[tos_index]
		//ldd \1							// load d with _EE_s12xs_active_tos==tos_index
											// but d has been already loaded... (see before: std \1)
		lsld								// logical shift left (1 bit) on d -> d*=2 
		tfr d,x								// I can't use d in the next operation so d -> x 
		ldy \2,x							// ldy	_EE_s12xs_system_tos,x
		tfr y,STACK_POINTER					// change the stack pointer

		endm								// end of macro

// ---------------------------------------------------------------------------------------------

//	Pseudo code for EE_std_change_context():
//	begin:
//		tos_index = EE_std_thread_tos[tid+1];
//		if is_not_the_current_stack(tos_index) {
//			EE_CHANGE_TOS_MACRO(EE_S12_ACTIVE_TOS, EE_S12_SYSTEM_TOS);
//		}
//		if (is_not_marked_stacked(tid)) {
//			tid = EE_std_run_task_code(tid);
//			goto begin;
//		}

// Auxiliary variable to save tid
	xref	EE_CHANGE_CONTEXT_TID_PAR

#ifdef __CODEWARRIOR__
	xdef EE_std_change_context
EE_std_change_context:
#else
	xdef f_EE_std_change_context
f_EE_std_change_context:
#endif
_EE_std_change_context_begin:
	// tos_index = EE_std_thread_tos[tid+1]; (tid is in d)
		std EE_CHANGE_CONTEXT_TID_PAR		// save tid using an auxiliary variable (irq are disabled...)
		addd #1								// tid+1
		lsld								// logical shift left (1 bit) on d -> d*=2 (to 16 bit) 
		tfr d,x								// I can't use d in the next operation so d -> x 
		ldy EE_S12_THREAD_TOS,x				// load y with _EE_s12_system_tos,x (y is tos_index)
	// if is_not_the_current_stack(tos_index)
		cpy EE_S12_ACTIVE_TOS				// compare y with EE_S12_ACTIVE_TOS
		beq _after_stack_change				// if equal goto lab2
	// {
		EE_CHANGE_TOS_MACRO EE_S12_ACTIVE_TOS, EE_S12_SYSTEM_TOS
	// }
_after_stack_change:
		ldd EE_CHANGE_CONTEXT_TID_PAR		// load d with EE_CHANGE_CONTEXT_TID_PAR (it cant'be changed!)
	// if (is_not_marked_stacked(tid))
		cpd #0								// compare d with 0
		blt _EE_std_change_context_end		// if d<0 branch to the end
	// {
	// tid = EE_std_run_task_code(tid)
		call	EE_STD_RUN_TASK_CODE		// at the end: tid is in d
	// goto begin;
		bra	_EE_std_change_context_begin
	// }
_EE_std_change_context_end:
		rtc
		end
