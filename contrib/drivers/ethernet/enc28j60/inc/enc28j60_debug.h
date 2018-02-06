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
 
/** 
* @file 	enc28j60_debug.h
* @brief 	ENC28J60 driver - Debug library.
* @author 	Dario Di Stefano
* @date 	2010
*/ 

#ifndef __ENC28J60_DEBUG_H__
#define __ENC28J60_DEBUG_H__

#ifdef __ENC28J60_DEBUG__

#include <stdio.h>
#include <string.h>

#ifdef __ENC28J60_DEBUG_SERIAL__

#include "console_serial.h"

#ifndef ENC28J60_DEBUG_SERIAL_PORT
#define ENC28J60_DEBUG_SERIAL_PORT 1
#endif

#ifndef ENC28J60_DEBUG_SERIAL_PORT 
#define ENC28J60_DEBUG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_1		
#endif

#ifndef ENC28J60_DEBUG_SERIAL_BAUDRATE 
#define ENC28J60_DEBUG_SERIAL_BAUDRATE 	115200 
#endif

#ifndef ENC28J60_DEBUG_SERIAL_OPT
#define ENC28J60_DEBUG_SERIAL_OPT (CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1)
#endif

#endif	//ENC28J60_DEBUG_SERIAL

#ifndef ENC28J60_STRING_MAXSIZE
#define ENC28J60_STRING_MAXSIZE 64
#endif

extern uint8_t ee_enc28j60_db_msg[ENC28J60_STRING_MAXSIZE];

#ifndef ENC28J60_DEBUG_PORT
#define ENC28J60_DEBUG_PORT 0
#endif

#define enc28j60_dbg_print(msg) console_write(ENC28J60_DEBUG_PORT, (uint8_t*) msg, strlen((char*)msg))
#define enc28j60_dbg_set_msg(str,val) sprintf((char*)ee_enc28j60_db_msg, str, val)

#else	//ENC28J60_DEBUG

#define	enc28j60_dbg_print(msg)
#define enc28j60_dbg_set_msg(str,val)

#endif	//ENC28J60_DEBUG

#endif	//__ENC28J60_DEBUG_H__


