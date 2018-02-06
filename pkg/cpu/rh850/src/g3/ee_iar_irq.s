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
 * Based on ee_ccrx_irq_stack.src
 */


	PUBLIC	_EE_rh850_change_IRQ_stack
	PUBLIC _EE_rh850_change_IRQ_stack_back
	EXTERN _EE_rh850_IRQ_tos
	
  SECTION     DATA_FLASH:DATA 
	_EE_rh850_tmp_tos: DS 4


  SECTION     CODE_FLASH:CODE


/* void EE_rh850_change_irq_stack(void) */
 
_EE_rh850_change_IRQ_stack:
	
	MOV _EE_rh850_tmp_tos, R15 	/* R15 = &_EE_rh850_tmp_tos */
	ST.W R3, 0[R15]							/* _EE_rh850_tmp_tos = SP */
	MOV _EE_rh850_IRQ_tos, R15  /* R15 = &_EE_rh850_IRQ_tos */
	LD.W 0[R15], R3							/* SP = _EE_rh850_IRQ_tos */
	STSR 0,R15,0
	STSR 1,R16,0
	PUSHSP R15-R16
	
	JMP [LP] /* Return */
	
_EE_rh850_change_IRQ_stack_back:
	
	POPSP R15-R16	
	LDSR R15,0,0
	LDSR R16,1,0
	MOV _EE_rh850_tmp_tos, R15 	/* R15 = &_EE_rh850_tmp_tos */
	LD.W 0[R15], R3							/* SP = _EE_rh850_tmp_tos */
	
	JMP [LP]
	
	END