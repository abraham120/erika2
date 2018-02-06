/** @file	ee_atmel_atxmega_mcu.h
 *
 *  @brief	Erika Enterprise - BOARD Driver - Atmel STK600 Header File.
 *
 *  <!--
 *    ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 *    Copyright (C) 2002-2013  Evidence Srl
 *
 *    This file is part of ERIKA Enterprise.
 *
 *    ERIKA Enterprise is free software; you can redistribute it
 *    and/or modify it under the terms of the GNU General Public License
 *    version 2 as published by the Free Software Foundation, 
 *    (with a special exception described below).
 *
 *    Linking this code statically or dynamically with other modules is
 *    making a combined work based on this code.  Thus, the terms and
 *    conditions of the GNU General Public License cover the whole
 *    combination.
 *
 *    As a special exception, the copyright holders of this library give you
 *    permission to link this code with independent modules to produce an
 *    executable, regardless of the license terms of these independent
 *    modules, and to copy and distribute the resulting executable under
 *    terms of your choice, provided that you also meet, for each linked
 *    independent module, the terms and conditions of the license of that
 *    module.  An independent module is a module which is not derived from
 *    or based on this library.  If you modify this code, you may extend
 *    this exception to your version of the code, but you are not
 *    obligated to do so.  If you do not wish to do so, delete this
 *    exception statement from your version.
 *
 *    ERIKA Enterprise is distributed in the hope that it will be
 *    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License version 2 for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    version 2 along with ERIKA Enterprise; if not, write to the
 *    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *    Boston, MA 02110-1301 USA.
 *  -->
 *
 *  The MCU driver provides MCU services for Clock and RAM initialization.
 *  In the MCU configuration set, the MCU specific settings for the Clock
 *  (i.e. PLL setting) and RAM (i.e. section base address and size) shall be
 *  configured.
 *
 *  The MCU module shall provide a service to provide software triggering of a
 *  hardware reset.
 *
 *  @note	Only an authorized user shall be able to call this reset service
 *  		function.
 *
 *  The MCU module shall provide services to get the reset reason of the last
 *  reset if the hardware supports such a feature.
 *
 *  @note	In an ECU, there are several sources which can cause a reset.
 *  		Depending on the reset reason, several application scenarios
 *  		might be necessary after reinitialization of the MCU.
 * 
 *  @author	Giuseppe Serano
 *  @version	0.1
 *  @date	2013
 */

#ifndef	__INCLUDE_ATMEL_STK600_BOARD_H__
#define	__INCLUDE_ATMEL_STK600_BOARD_H__

#include "board/common/inc/ee_board_common_board.h"

#ifdef	__LED_DRIVER__
#include "board/atmel_stk600/inc/ee_atmel_stk600_led.h"
#endif

#endif	/* __INCLUDE_ATMEL_STK600_BOARD_H__ */
