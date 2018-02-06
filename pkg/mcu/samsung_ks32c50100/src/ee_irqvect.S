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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_irqvect.S,v 1.2 2004/11/18 11:18:39 pj Exp $
 */
	
/* handlers */	
.extern _start
.extern	EE_UNDEFINED_handler
.extern EE_SWI_handler
.extern EE_PREFETCH_handler
.extern EE_DATAABORT_handler
.extern EE_IRQ_handler
#include "mcu/samsung_ks32c50100/inc/ee_ic_fiqstub.S"
	
	.text
	CODE32
/* 
 *  Exception Vector
 */  
		
/*  0x00000000:	Reset  */
	.org 0x0
entry_point:
	B	_start

/*  0x00000004:	Undefined instructions */
	B	EE_UNDEFINED_handler

/*  0x00000008:	Software interrupts (SWI) */
	B	EE_SWI_handler

/*  0x0000000C:	Prefetch Abort (Instruction fetch memory abort) */
	B	EE_PREFETCH_handler

/*  0x00000010:	Data Abort (Data access memory abort) */
	B	EE_DATAABORT_handler

/*  0x00000014:	Reserved (26-bit architecture) */
	B	.

/*  0x00000018:	Interrupt (IRQ) */
	B	EE_IRQ_handler

/*  0x0000001C:	Fast Interrupt (FIQ) */
	EE_FIQ_HANDLER_STUB

	.end
