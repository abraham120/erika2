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
* @file 	pcf8583_hal.h
* @brief 	PCF8583 Real time clock Driver - HAL header file.
* @author 	Dario Di Stefano
* @date 	2010
*/

#ifndef __pcf8583_hal_h__
#define __pcf8583_hal_h__

#include <pcf8583_compiler.h>


/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>

#if defined	__MICROCHIP_PIC32__
#include <pcf8583_hal_ee_pic32.h>
#else
	#if defined __LM32__
	#include <pcf8583_hal_ee_mico32.h>
	#else /* NO Architecture */		
	#error "PCF8583_HAL: Architecture not supported"
	#endif
#endif

#else			/* No OS */

#error "PCF8583_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
