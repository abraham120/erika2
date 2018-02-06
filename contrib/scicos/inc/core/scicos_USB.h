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
	@file scicos_USB.h
	@brief www.scicos.org, www.scicoslab.org
	@author Christian Nastasi, RetisLab, Pisa
	@date 2006-2010
*/

#ifndef _scicos_USB_h_
#define _scicos_USB_h_

#include <ee.h>

#define SCICOS_USB_CHANNELS 15

/// chris: simplified dummy version!
///#define FLEX_BUS_MESSAGE_SIZE 32
///
///struct flex_bus_message_t {
///	unsigned int length;
///	unsigned char data[FLEX_BUS_MESSAGE_SIZE];
///};
///struct flex_bus_packet_t {
///	unsigned int channel;
///	struct flex_bus_message_t payload;
///};


extern float scicosUSB_rx_buffer[SCICOS_USB_CHANNELS];
extern float scicosUSB_tx_buffer[SCICOS_USB_CHANNELS];

#endif
