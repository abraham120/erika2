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
 * CVS: $Id: ee_irqvect.S,v 1.1 2006/10/19 09:51:44 pj Exp $
 */
	
/* handlers */	
.extern _start
#include "mcu/st_sta2051/inc/ee_ic_fiqstub.S"
#include "mcu/st_sta2051/inc/ee_ic_irqstub.S"
	
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
	/* Jumps to the content pointed by the IVR location
	   0x18+0x8+0xfffffbf8=0xfffffc18=IVR */
        LDR pc, [pc, #0xFFFFFBF8]

/*  0x0000001C:	Fast Interrupt (FIQ) */
	EE_FIQ_HANDLER_STUB

        EE_IRQ_FOOTER_STUB



/*
 *
 * Forever Loops
 * This is used to fill the interrupt table with a set of forever loops.
 * SWI, Prefetch, and Data Abort are linked to an infinite loop if the
 * corresponding PRIVATE define is not defined.
 *
 */

	
#ifndef __PRIVATE_UNDEFINED_HANDLER__
.global EE_UNDEFINED_handler
.type	EE_UNDEFINED_handler, #function
EE_UNDEFINED_handler:	
#ifndef YES_FOREVER_LOOP
#define YES_FOREVER_LOOP
#endif

#else
.extern	EE_UNDEFINED_handler
#endif


	
#ifndef __PRIVATE_SWI_HANDLER__
.global EE_SWI_handler
.type	EE_SWI_handler, #function
EE_SWI_handler:	
#ifndef YES_FOREVER_LOOP
#define YES_FOREVER_LOOP
#endif

#else
.extern EE_SWI_handler
#endif
	

	
#ifndef __PRIVATE_PREFETCH_HANDLER__
.global EE_PREFETCH_handler
.type	EE_PREFETCH_handler, #function
EE_PREFETCH_handler:	
#ifndef YES_FOREVER_LOOP
#define YES_FOREVER_LOOP
#endif

#else
.extern EE_PREFETCH_handler
#endif


#ifndef __PRIVATE_DATAABORT_HANDLER__
.global EE_DATAABORT_handler
.type	EE_DATAABORT_handler, #function
EE_DATAABORT_handler:	
#ifndef YES_FOREVER_LOOP
#define YES_FOREVER_LOOP
#endif

#else
.extern EE_DATAABORT_handler
#endif


#ifdef YES_FOREVER_LOOP
	B .
#endif

	
	.end
