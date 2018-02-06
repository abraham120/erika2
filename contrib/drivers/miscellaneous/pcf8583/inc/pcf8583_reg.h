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
* @file 	pcf8583_reg.h
* @brief 	PCF8583 real time clock Driver - RTC registers. 
* @author 	Dario Di Stefano 
* @date 	2010
*/

#ifndef __PCF8583_REG_H__
#define __PCF8583_REG_H__

/******************************************************************************/
/*				Registers Definition 			      */
/******************************************************************************/

/*	Slave device addresses		*/
#define RTC_DEVICE_ID      		(0xA0)

/* Driver Macros */
#define RTC_OFF                 (0x80)
#define RTC_ON                  (0x00)

/*	Register adresses		*/
#define RTC_CSR_ADD             (0x00)
#define RTC_HSECONDS_ADD        (0x01)
#define RTC_SECONDS_ADD         (0x02)
#define RTC_MINUTES_ADD         (0x03)
#define RTC_HOURS_ADD           (0x04)
#define RTC_DAYS_ADD            (0x05)
#define RTC_MONTHS_ADD          (0x06)
#define RTC_TIMER_ADD           (0x07)
#define RTC_YEAR_ADD            (0x10)
#define RTC_FREE_RAM_ADD        (0x11)

#endif // __PCF8583_REG_H___
