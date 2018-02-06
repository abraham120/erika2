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

        .equ __30F2010, 1   
        .include "p30f2010.inc"

.global _T1_program
.global _T1_clear
.text
	; The following code example will enable Timer1 interrupts,
	; load the Timer1 Period register and start Timer1.
	; When a Timer1 period match interrupt occurs, the interrupt
	; service routine must clear the Timer1 interrupt status flag
	; in software.
_T1_program:	
	CLR T1CON		; Stops the Timer1 and reset control reg.
	CLR TMR1		; Clear contents of the timer register
	MOV #0xFFFF, w0		; Load the Period register
	MOV w0, PR1		; with the value 0xFFFF
	BSET IPC0, #T1IP0	; Setup Timer1 interrupt for
	BCLR IPC0, #T1IP1	; desired priority level
	BCLR IPC0, #T1IP2	; (this example assigns level 1 priority)
	BCLR IFS0, #T1IF	; Clear the Timer1 interrupt status flag
	BSET IEC0, #T1IE	; Enable Timer1 interrupts
	BSET T1CON, #TON	; Start Timer1 with prescaler settings
				; at 1:1 and clock source set to
				; the internal instruction cycle
	return

_T1_clear:	
	BCLR IFS0, #T1IF
	return
