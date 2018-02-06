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
 * Author: 2004 Antonio Fiaschi
 *
 */

#ifndef __MPC5PROTECTED_MACRO_H__
#define __MPC5PROTECTED_MACRO_H__


#define	EXCEPTION_ENTRY(address,label)	\
	. = address;			\
label:

#ifdef DEBUG

#define STND_HANDLER(label)		\
	b	label

#else

#define STND_HANDLER			\
	rfi

#endif

#define END_EXCEPTION_TABLE(address)	\
	. = address
	
/***************************************

#define STND_HANDLER(handler)		\
	<codice specifico>;		\
	lis	9, handler@ha;		\
	la	10, handler@l(9);	\
	mtlr	10;			\
	blrl;				\
	<codice specifico>

***************************************/

/* Condition Register Bit Fields */

#define cr0     0
#define cr1     1
#define cr2     2
#define cr3     3
#define cr4     4
#define cr5     5
#define cr6     6
#define cr7     7


/* General Purpose Registers (GPRs) */
 
#define r0      0
#define r1      1

#define sp	r1

#define r2      2
#define r3      3
#define r4      4
#define r5      5
#define r6      6
#define r7      7
#define r8      8
#define r9      9
#define r10     10
#define r11     11
#define r12     12
#define r13     13
#define r14     14
#define r15     15
#define r16     16
#define r17     17
#define r18     18
#define r19     19
#define r20     20
#define r21     21
#define r22     22
#define r23     23
#define r24     24
#define r25     25
#define r26     26
#define r27     27
#define r28     28
#define r29     29
#define r30     30
#define r31     31

/* Interrupt Enabling / Disabling Register */

#define	EIE	80	// Write to this reg to enabling external interrupt
#define	EID	81	// Write to this reg to disabling external interrupt
#define	NRI	82	// Write here to signaling that exception is revorable

#endif // __MPC5PROTECTED_MACRO_H__

