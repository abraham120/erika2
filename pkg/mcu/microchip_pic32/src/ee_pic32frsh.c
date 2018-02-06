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


#include "ee_internal.h"

#include "mcu/microchip_pic32/inc/ee_internal.h"
#include "cpu/pic32/inc/ee_irqstub.h"

extern void EE_IRQ_end_budget(void);
extern void EE_IRQ_end_recharging(void);

/*
 * These two interrupts are used in the FRSH implementation to handle the
 * timer interrupts for budget exaustion and for the recharging.
 */

// TODO!!!

/* Budget exaustion */
/*ISR2(_T7Interrupt)
{
	// clear the interrupt source
	IFS3bits.T7IF = 0;
	T6CONbits.TON = 0;
	EE_frsh_IRQ_timer_multiplexer();
}*/



/* This function set the capacity timer to raise in t ticks. */
/*void EE_hal_set_budget_timer(EE_STIME t) 
{   
  if (t > 0) {
    PR6 = t & 0xFFFF;
    PR7 = t >> 16;
    TMR6 = 0;
    TMR7 = 0;
    IFS3bits.T7IF = 0;
    T6CONbits.TON = 1; // Start Timer 6/7;
  } else {
    // Stop the timer
    IFS3bits.T7IF = 0;
    T6CONbits.TON = 0;
  }
}*/
