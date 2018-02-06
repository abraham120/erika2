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
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
/** 
* @file 	mac_extphy_debug.h
* @brief 	ETH_EXTPHY driver - Debug library.
* @author 	Dario Di Stefano
* @date 	2011
*/ 

#ifndef __ETHEXTPHY_DEBUG_H__
#define __ETHEXTPHY_DEBUG_H__

#define ETHEXTPHY_DEBUG_ERROR  (-1)
#define ETHEXTPHY_DEBUG_OK     (1)

#ifdef __ETHEXTPHY_DEBUG__

#include <stdio.h>
#include <string.h>

#ifdef __ETHEXTPHY_DEBUG_SERIAL__

#include "console_serial.h"

#ifndef ETHEXTPHY_DEBUG_SERIAL_PORT
#define ETHEXTPHY_DEBUG_SERIAL_PORT       1
#endif

#ifndef ETHEXTPHY_DEBUG_SERIAL_PORT 
#define ETHEXTPHY_DEBUG_SERIAL_PORT       CONSOLE_SERIAL_PORT_1
#endif

#ifndef ETHEXTPHY_DEBUG_SERIAL_BAUDRATE 
#define ETHEXTPHY_DEBUG_SERIAL_BAUDRATE   115200 
#endif

#ifndef ETHEXTPHY_DEBUG_SERIAL_OPT
#define ETHEXTPHY_DEBUG_SERIAL_OPT        (CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1)
#endif

#endif    /* __ETHEXTPHY_DEBUG_SERIAL__ */

#ifndef ETHEXTPHY_STRING_MAXSIZE
#define ETHEXTPHY_STRING_MAXSIZE 64
#endif

extern uint8_t ee_ethextphy_db_msg[ETHEXTPHY_STRING_MAXSIZE];
extern uint8_t ethextphy_debug_initialized;

#ifndef ETHEXTPHY_DEBUG_PORT
#define ETHEXTPHY_DEBUG_PORT 0
#endif

#define EE_extphy_dbg_print(msg)        console_write(ETHEXTPHY_DEBUG_PORT, (uint8_t*) msg, strlen((char*)msg))
#define EE_extphy_dbg_set_msg(str,val)  sprintf((char*)ee_ethextphy_db_msg, str, val)

/**
 * @brief MAC/PHY debug initialization function.
 * This function configures a console for PHY serial debug. 
 * @return Initialization result (1 ok, -1 failed).
 */
__INLINE__ int8_t __ALWAYS_INLINE__ EE_extphy_debug_init(void){
	if(ethextphy_debug_initialized==1)
		return ETHEXTPHY_DEBUG_OK;
		
	console_descriptor_t *des = NULL;
	
	#ifdef __PHY_DEBUG_SERIAL__ 
	des = console_serial_config(PHY_DEBUG_SERIAL_PORT, PHY_DEBUG_SERIAL_BAUDRATE, PHY_DEBUG_SERIAL_OPT);
	#endif
	
	if (des == NULL)
		return ETHEXTPHY_DEBUG_ERROR;
	if (console_init(ETHEXTPHY_DEBUG_PORT, des) < 0)
		return ETHEXTPHY_DEBUG_ERROR;
		
	ethextphy_debug_initialized = 1;
	return console_open(ETHEXTPHY_DEBUG_PORT);
}

#else     /* __ETHEXTPHY_DEBUG__ */


#define ETHEXTPHY_STRING_MAXSIZE 1
extern uint8_t ee_ethextphy_db_msg[ETHEXTPHY_STRING_MAXSIZE];

__INLINE__ int8_t __ALWAYS_INLINE__ EE_extphy_dbg_print(const char* msg) {
	return ETHEXTPHY_DEBUG_ERROR;
}

__INLINE__ int __ALWAYS_INLINE__ EE_extphy_dbg_set_msg(const char *format, ...) {
	return ETHEXTPHY_DEBUG_ERROR;
}

__INLINE__ int8_t __ALWAYS_INLINE__ EE_extphy_debug_init(void){
	return ETHEXTPHY_DEBUG_ERROR;
}

#endif    /* __ETHEXTPHY_DEBUG__ */

#endif    /* __ETHEXTPHY_DEBUG_H__ */


