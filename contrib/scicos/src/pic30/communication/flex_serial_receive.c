/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
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
	@file flex_serial_receive.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/
 
#include <machine.h>
#include <scicos_block4.h>
#include <ee.h>
#include "mcu/microchip_dspic/inc/ee_uart.h"

extern volatile EE_UINT8  scicos_uart_port;
extern volatile EE_UINT32 scicos_uart_baudrate;

void flex_serial_receive(scicos_block *block,int flag)
{
	EE_UINT8 serial_data;
	EE_INT8 res;

    unsigned char *y = block->outptr[0];

	switch (flag) {

		case OutputUpdate:
			res = EE_uart_read_byte(scicos_uart_port-1, &serial_data);
			if (res == EE_UART_ERR_NO_DATA)
				y[0] = '\0';
			else
				y[0] = serial_data;
			break;

		case StateUpdate: 
			break;
		
		case Initialization:
			break;
		
		case Ending:	
			break;
	}
}
 
