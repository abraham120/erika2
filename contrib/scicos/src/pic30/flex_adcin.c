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
	@file flex_adcin.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#define VREF	3.3

static void init(scicos_block *block)
{
	int pin = block->ipar[0];
	
	if (pin > 8)
		pin = 8;
	else if (pin < 1)
		pin = 1;
	//block->ipar[0]=pin;
	
	/* turn off ADC module */
	AD1CON1bits.ADON = 0;

	/* set configuration bit for ADC input */
	switch (pin) {
		case 1:	// ANin0 - RB8
			AD1PCFGL &= 0xFEFF;
			break;
		case 2:	// ANin1 - RB9
			AD1PCFGL &= 0xFDFF;
			break;
		case 3:	// ANin2 - RB10
			AD1PCFGL &= 0xFBFF;
			break;
		case 4:	// ANin3 - RB11
			AD1PCFGL &= 0xF7FF;
			break;
		case 5:	// ANin4 - RB12
			AD1PCFGL &= 0xEEFF;
			break;
		case 6:	// ANin5 - RB13
			AD1PCFGL &= 0xFDFF;
			break;
		case 7:	// ANin6 - RB15
			AD1PCFGL &= 0xF7FF;
			break;
		case 8:	// ANin7 - RC1
			AD1PCFGH &= 0xFFFE;
			break;
	}
	
	/* Set control register 1 */
	/* 12-bit, unsigned integer format, autosampling */
	AD1CON1 = 0x04E0;
	
	/* Set control register 2 */
	/* Vref = AVcc/AVdd, Scan Inputs */
	AD1CON2 = 0x0000;
	
	/* Set Samples and bit conversion time */
	/* AS = 31 Tad, Tad = 64 Tcy = 1.6us  */
	AD1CON3 = 0x1F3F; //** Last PATCH xxx
        	
	/* disable channel scanning here */
	AD1CSSL = 0x0000;
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* disable ADC interrupts */	  
	IEC0bits.AD1IE = 0;       

	/* turn on ADC module */
	AD1CON1bits.ADON = 1;
}

static void inout(scicos_block *block)
{
	unsigned int adcdata;
	float * y = block->outptr[0];
	
	int pin = block->ipar[0];
	if (pin > 8)
		pin = 8;
	else if (pin < 1)
		pin = 1;

	/* channel select */
	switch (pin) {
		case 1:	// ANin0 - RB8
			AD1CHS0 = 8;
			break;
		case 2:	// ANin1 - RB9
			AD1CHS0 = 9;
			break;
		case 3:	// ANin2 - RB10
			AD1CHS0 = 10;
			break;
		case 4:	// ANin3 - RB11
			AD1CHS0 = 11;
			break;
		case 5:	// ANin4 - RB12
			AD1CHS0 = 12;
			break;
		case 6:	// ANin5 - RB13
			AD1CHS0 = 13;
			break;
		case 7:	// ANin6 - RB15
			AD1CHS0 = 15;
			break;
		case 8:	// ANin7 - RC1
			AD1CHS0 = 16;
			break;
	}
	
	/* Start conversion */
	AD1CON1bits.SAMP = 1;
	
	/* Wait till the EOC */
	while(!IFS0bits.AD1IF);
	
	/* reset ADC interrupt flag */
	IFS0bits.AD1IF = 0;           

	/* Acquire data */
	adcdata = ADC1BUF0;
	y[0] = (adcdata * VREF) / 4096;
}

static void end(scicos_block *block)
{
}

void flex_adcin(scicos_block *block,int flag)
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
