/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * version 2 along with ERIKA Enerprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

#ifndef __INCLUDE_EEUART_H__
#define __INCLUDE_EEUART_H__

#include "ee.h"
#include "ee_irq.h"

#define CLOCK_FREQ	(40000000)      // Hz
#define INSTR_FREQ	(CLOCK_FREQ/2)	// Hz

#define BIT9		0x06
#define BIT8_ODD	0x04
#define BIT8_EVEN	0x02
#define BIT8_NO		0x00

#define BIT_STOP_1	0x00
#define BIT_STOP_2	0x01

#define CTRL_SIMPLE	0x00
#define CTRL_FLOW	0x01

#define TX_INT_SINGLE	0x8000
#define TX_INT_EMPTY	0x2000
#define TX_INT_LAST		0x0000			// use this

#define RX_INT_FULL		0x00C0
#define RX_INT_3OF4		0x0080
#define RX_INT_SINGLE	0x0040			// use this

#endif
