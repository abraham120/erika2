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
 * Author: 2005 Paolo Gai
 * CVS: $Id: ee_board.c,v 1.11 2007/01/04 16:53:09 nino Exp $
 */

#include "ee_internal.h"
#include "board/microchip_explorer16/inc/ee_board.h"

#if defined __PIC30__
#include "cpu/pic30/inc/ee_irqstub.h"
#include "mcu/microchip_dspic/inc/ee_mcu.h"
#elif defined __PIC32__
#include "cpu/pic32/inc/ee_irqstub.h"
#include "mcu/microchip_pic32/inc/ee_mcu.h"
#else
#error "Unsupported pic on explorer16 board"
#endif


/* ************************************************************************* */
/* Buttons */
/* ************************************************************************* */

#ifdef __USE_BUTTONS__

void (*EE_button_callback)(void);
EE_UINT8 EE_button_mask;

ISR2(EE_EXPLORER16_IRQ_HANDLER_NAME)
{
	// Execute callback function
	if (EE_button_callback != NULL) {
		EE_button_callback();
	}
		
	/* reset CN interrupt flag */
	IFS1bits.CNIF = 0;           
}

#endif

/* ************************************************************************* */
/* Analog input */
/* ************************************************************************* */
#ifdef __USE_ANALOG__

EE_UINT16 EE_analog_channel = 0;
EE_UINT16 EE_analog_raw_temperature = 1000;
EE_UINT16 EE_analog_raw_potentiometer = 1000;

ISR2(EE_EXPLORER16_INT_VECT)
{
  /* reset ADC interrupt flag */
  EE_explorer16_int_reset();

  /* Store Temperature and Potentiometer data */
  if (EE_analog_channel == 0) {
    EE_analog_raw_temperature = ADC1BUF0;
    EE_explorer16_temp_conf();
    EE_analog_channel = 1;
  } 
  else {
    EE_analog_raw_potentiometer = ADC1BUF0;             
    EE_explorer16_pot_conf();
    EE_analog_channel = 0;
  }
}

#endif

/* ************************************************************************* */
