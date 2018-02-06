/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
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

/** 
	@file flex_buzzer.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
#include <machine.h>
#include <scicos_block.h>

#include <ee.h>

static void init(scicos_block *block)
{
// Initialize Output Compare Module
OC1CONbits.OCM = 0b000; // Disable Output Compare Module
OC1R = 300; // Write the duty cycle for the first PWM pulse
OC1RS = 1250; // Write the duty cycle for the second PWM pulse
OC1CONbits.OCTSEL = 1; // Select Timer 3 as output compare time base
OC1R = 1250; // Load the Compare Register Value
OC1CONbits.OCM = 0b110; // Select the Output Compare mode
// Initialize and enable Timer2
T3CONbits.TON = 0; // Disable Timer
T3CONbits.TCS = 0; // Select internal instruction cycle clock
T3CONbits.TGATE = 0; // Disable Gated Timer mode
//T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
	T3CONbits.TCKPS = 1;
TMR3 = 0x00; // Clear timer register
PR3 = 2500; // Load the period value
IPC2bits.T3IP = 0x01; // Set Timer 2 Interrupt Priority Level
IFS0bits.T3IF = 0; // Clear Timer 2 Interrupt Flag
//IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
T3CONbits.TON = 0; // Start Timer
}

EE_UINT16 buzzer_freq = 0;

static void inout(scicos_block *block)
{
	if (block->inptr[0][0] <= 10) {
		// Stop PWM
		OC1CONbits.OCM = 0;
	
		// Stop Timer3 
		T3CONbits.TON = 0;
		
		// Store frequency value 
		buzzer_freq = 0;
	} else {
		if ( ((block->inptr[0][0] - buzzer_freq) > 10) || ((block->inptr[0][0] - buzzer_freq) < -10) ) {
			// Stop PWM
			OC1CONbits.OCM = 0;

			// Stop Timer3
			T3CONbits.TON = 0;

			// Load the Period register wit the computed value 
			PR3 = 5000000ul / block->inptr[0][0];
		
			// Set the initial duty cycle 
			OC1R = PR3 >> 1;

			// Set the duty cycle 
			OC1RS = OC1R;

			// Start Timer3
			T3CONbits.TON = 1;

			// Start PWM
			OC1CONbits.OCM = 6;

			// Store frequency value 
			buzzer_freq = block->inptr[0][0];
		}
	}
}

static void end(scicos_block *block)
{
	/* Stop PWM*/
	OC1CONbits.OCM = 0;
	
	/* Stop Timer3 */
	T3CONbits.TON = 0;
}

void flex_buzzer(scicos_block *block,int flag)
{
	switch (flag) {
    case OutputUpdate:  /* set output */
      inout(block);
      break;

    case StateUpdate: /* get input */
      break;

    case Initialization:  /* initialisation */
      init(block);
      break;

    case Ending:  /* ending */
      end(block);
      break;
  }
}
