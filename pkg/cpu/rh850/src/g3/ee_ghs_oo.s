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
 * Author: 2016 Nils Scharnke
 *
 * Based on ee_ccrx_oo.src
 */

	.globl _EE_rh850_terminate_task
	.globl _EE_rh850_terminate_savestk

	.text
/*
 * void EE_rh850_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
 *
 * r6 = &terminate_data[t]
 * r7 = terminate_real_th_body[t]()
 */
 
_EE_rh850_terminate_savestk:
	
	PUSHSP R31-R31  /* save LP */
	/* save working registers */
	PUSHSP R1-R2
	PUSHSP R6-R14
  PUSHSP R25-R29

	ST.W R3,0[R6]   /* store SP at &terminate_data[t] */
	
	JARL [R7], R31
	
	/* Restore registers, if thread was not terminated */
	POPSP R25-R29
	POPSP R6-R14
	POPSP R1-R2
	POPSP R31-R31   /* restore LP */
	
	JMP [R31]
	

_EE_rh850_terminate_task:
	LD.W 0[R6],R3   /* restore SP */
	/* restore working registers */
  POPSP R25-R29
	POPSP R6-R14
	POPSP R1-R2
	POPSP R31-R31   /* restore LP */
	
	JMP [LP]
	
	
	.end
