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
//! \file ee_oo.S
//! \brief EE_s12_terminate_savestk (read and save the stack pointer), EE_s12_terminate_task (write the stack pointer) implementation.
//! \author Dario Di Stefano
//! \version 0.1
//! \date 2011-01-12
//!

//! \fn void EE_s12_terminate_savestk(EE_DADD sp, EE_ADDR realbody)
//! \param sp			Pointer to a location used to save the stack pointer.
//! \param realbody		Body of the thread to be called.

//! \fn void EE_s12_terminate_task(EE_DADD sp)
//! \param sp			New value for the stack pointer.

// the define is needed for binary distributions 
#define __EECFG_THIS_IS_ASSEMBLER__

#ifdef __CODEWARRIOR__
	xdef EE_s12_terminate_savestk
EE_s12_terminate_savestk:
OFST:	set	0
	pshx
	pshd
	tfr SP,d			// transfer stack pointer in d register
	addd #$04			// add 2 (d+=2)
	std [OFST+7,SP]		// Save the stack pointer (from d to the terminate_data vector saved in the stack pointer)    
	call	[OFST+1,SP] // Call the thread
	//puld				// Remove two bytes (the address of terminate_data) from the stack and put them in d (like a call, if the user doesnt'call the TerminateTask() function...)
	//pulx
	leas	4,SP		// remove 4 bytes from the stack (d,x previously pushed...)
	pulx				// prendo l'indirizzo di ritorno
	pula				// prendo l'indirizzo di ritorno
	puly				// prendo l'indirizzo dal quale leggere lo stack pointer
	pshd
	psha
	pshx
	tfr y,d
#else // COSMIC COMPILER
	xdef f_EE_s12_terminate_savestk
f_EE_s12_terminate_savestk:
	pshd				// Push (d, the first argument) in the stack the address of the memory location of the return stack pointer... 
OFST:	set	0
	//tfr s,x			// transfer stack pointer in the register x
	//addx #$02			// add 2 (x+=2)
	//tfr x,d			// transfer x in d
	tfr s,d				// transfer stack pointer in d register
	addd #$02			// add 2 (d+=2)
	std [OFST+0,s]		// Save the stack pointer (from d to the terminate_data vector saved in the stack pointer)
	call	[OFST+5,s]	// Call the thread
	puld				// Remove two bytes (the address of terminate_data) from the stack and put them in d (like a call, if the user doesnt'call the TerminateTask() function...)
#endif

#ifdef __CODEWARRIOR__
	xdef EE_s12_terminate_task
EE_s12_terminate_task:
#else
	xdef f_EE_s12_terminate_task
f_EE_s12_terminate_task:
#endif
	tfr	d,y				// transfer d in y register
	//ldd	0,y			// transfer the content of y in d
	//tfr	d,STACK_POINTER // Change the stack pointer (transfer d in sp)
	lds 0,y				// Change the stack pointer (transfer the content of y in sp)
	rtc					// Return in the thread stub (with ppage change)
	end
