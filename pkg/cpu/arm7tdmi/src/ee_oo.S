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
 * CVS: $Id: ee_oo.S,v 1.1 2005/07/16 12:46:16 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_arm7defs.h"
#include "cpu/arm7tdmi/inc/ee_compiler.h"

	.global	EE_arm7_terminate_task
	.global EE_arm7_terminate_savestk
	
	.text

	//  kernel code is in ARM-mode
	.arm
	
	// r0 = &terminate_data[t]
	// r1 = terminate_real_th_body[t]()
	.type	EE_arm7_terminate_savestk, #function
EE_arm7_terminate_savestk:
	// save some registers:	
	// - r0-r3 do not need to be saved 9they are already dirty
	//   with the call to this function;
	// - r4-r11 have to be saved because they maybe contain some
	//   data of the preempted threads
	// - r12 has to be saved because it is not guaranteed that the value
	//   will remain the same after we return from the TerminateTask
	// - lr has to be saved to be able to jump back to the thread final }
	//   in the thread stub into tstub.h
	// - only the data from the System level have to be saved, the others
	//   will be restored when needed directly by the prempter 
	//   threads/irqs
	//
	// Please note that the interrupt are ENABLED
	STMFD	sp!, {r4-r12,lr}
	
	// save sp_sys in terminate_data[t]
	STR sp, [r0]
	
	// jmp terminate_real_th_body[t]
	BX r1
	
	.size	EE_arm7_terminate_savestk, . - EE_arm7_terminate_savestk

	// r0 = &terminate_data[t]
	.type	EE_arm7_terminate_task, #function
EE_arm7_terminate_task:
	// reload sp_sys from terminate_data[t]	
	LDR sp, [r0]
	// reload the registers saved before
	LDMFD	sp!, {r4-r12,lr}
	// return back to the caller (in tstub.c!!!)
	BX lr
	.size	EE_arm7_terminate_task, . - EE_arm7_terminate_task
	
	.end
