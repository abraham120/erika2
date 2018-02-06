/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file ee_board.h
	@brief Main header file in board.
	@author Dario Di Stefano, Bernardo  Dal Seno 
	@date 2010
*/

#ifndef __INCLUDE_FPGA_CAMERA_BOARD_H__
#define __INCLUDE_FPGA_CAMERA_BOARD_H__

#ifdef __FPG_EYE__

#ifdef __USE_ETHERNET_ENC28J60__
#include "board/fpg-eye/inc/ee_ethernet_enc28j60.h"
#endif 

#ifdef __USE_ZIGBEE_MRF24J40__
#include "board/fpg-eye/inc/ee_zigbee_mrf24j40.h"
#endif 

#ifdef __USE_LIGHTSENSOR_TSL2561T__
#include "board/fpg-eye/inc/ee_lightsensor_tsl2561t.h"
#endif 

#ifdef __USE_RTC_PCF8583__
#include "board/fpg-eye/inc/ee_rtc_pcf8583.h"
#endif 

#if defined(__USE_SST25VF016B__) || defined(__USE_SST25LF0X0A__)
#include "ee_spi_flash_boot.h"
#endif

#endif

#if defined(__USE_LEDS__) || defined(__USE_SWITCHES__) || defined(__USE_TRANSISTORS__)
#include "ee_serio.h"
#endif

#endif //__INCLUDE_FPGA_CAMERA_BOARD_H__
