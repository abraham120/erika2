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
	@file flex_daughter_encoder.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/


//** 9 Feb 2008 : Revision notes by Simone Mannori 
//** 26 July 2010 : SW encoder added by Dario Di Stefano 


#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>

/* Encoder bit allocation 
	HW encoder pins (motion demoII board, demo board):
	QEA/RB4 pin
	QEB/RB5 pin
	SW encoder pins (motion demoII board):
	IC1/RD8 pin (channel A) -> irq
	RB11 pin	(channel B)
	SW encoder pins (demo board):
	CN16/RD7 pin (channel A) -> irq
	RC4 pin		 (channel B)
*/

/* Macros to write on output ports */
#define y(i,j) ((double *)block->outptr[i])[j]

#define EE_scicos_encoder_get_enc_id() block->ipar[0]
//#define EE_scicos_encoder_get_gain() block->rpar[0]
//#define Deg_2_Rad			1.745329251994330e-002F
//#define EE_ENCODER_HW_GAIN	Deg_2_Rad
//#define EE_ENCODER_SW_GAIN	Deg_2_Rad*2.0                           // 2.0 

static void init(scicos_block *block)
{
	int id = EE_scicos_encoder_get_enc_id();
	
	if(id == EE_ENCODER_HW)
	{
		/**
		* The first encoder uses the Quadrature Encoder Interface
		* (QEI) module and associated operational modes.
		* The QEI module provides the interface to incremental
		* encoders for obtaining mechanical position data.
		* Max Resolution: 4x.
		*/
		EE_encoder_init(1, 1); 
	}
	else // sw encoder
	{
		/**
		* The second encoder uses the SW encoder driver library
		* and associated operational modes.
		* The driver functioning is based on interrupts on every edge 
		* of channel A so we haven't the max resolution, but only 2x.
		*/
		EE_encoder_SW_init(1, 1);
	}
}

static void inout(scicos_block *block)
{
	int id = EE_scicos_encoder_get_enc_id();
	
	if(id == EE_ENCODER_HW)
	{
		/** 
		* The encoder return a float value coded in signed pulse units
		* this means that the dspic register MUST be read as "int" 
		* in order to keep the signed comp. 2' bynary rapresentation.
		* the scaling to degree/radian/centesimal/mm must be done 
		* in the scicos diagram.
		*/
		y(0,0) = (float)EE_encoder_get_ticks();
		y(1,0) = EE_encoder_get_flag();
	}
	else // sw encoder
	{
		/** 
		* Because of 2x resolution, we have to double the number of counter ticks
		* to have the same behaviour of hw encoder (see the encoder driver). 
		* TODO: 4x resolution in the next releases...
		*/
		y(0,0) = (float)EE_encoder_SW_get_ticks();
		y(1,0) = EE_encoder_SW_get_flag();
	}
}

static void end(scicos_block *block)
{
}

void flex_daughter_encoder(scicos_block *block,int flag)
{
	switch (flag) {
	case OutputUpdate:  /* set output */
		inout(block);
		break;

	case StateUpdate:  /* get input */
		break;

	case Initialization:  /* initialisation */
		init(block);
		break;

	case Ending:  /* ending */
		end(block);
		break;
	}
}

