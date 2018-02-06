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
	@file ee_mcu.h
	@brief Header file to include drivers header files needed.
	@author Giuseppe Serano
	@date 2011
  @author Christoph Kreuzberger
  @date 2014
*/
 
#ifndef	__INCLUDE_TI_TMS570_MCU_H__
#define	__INCLUDE_TI_TMS570_MCU_H__

#include "board/ti_tms570/inc/ee_board.h"
#include "mcu/ti_tms570/inc/ee_mcu.h"

#include "../contrib/ti_tms570/include/system.h"
#include "../contrib/ti_tms570/include/adc.h"
#include "../contrib/ti_tms570/include/can.h"
#include "../contrib/ti_tms570/include/esm.h"
#include "../contrib/ti_tms570/include/gio.h"
#include "../contrib/ti_tms570/include/het.h"
#include "../contrib/ti_tms570/include/lin.h"
#include "../contrib/ti_tms570/include/rti.h"
#include "../contrib/ti_tms570/include/sci.h"
#include "../contrib/ti_tms570/include/spi.h"
#include "../contrib/ti_tms570/include/sys_mpu.h"

// Called in the Main to initialise needed modules
static void EE_mcu_init(void)
{
  /* Initialize Error Signaling Module */
  esmInit();
  _enable_interrupts();
  rtiInit();

#ifdef __USE_DISPLAY__
  EMIF_Init();
  DISPLAY_Init();
#endif /*__USE_GLCD__*/


#if defined(__USE_GIO__) || defined(__USE_LEDS__)
  gioInit();
#endif

#if defined(__USE_HET__) || defined(__USE_LEDS__)
  hetInit();
#endif

#ifdef __USE_ADC__
  adcInit();
#endif

#ifdef __USE_CAN__
  canInit();
#endif

#ifdef __USE_LIN__
  linInit();
#endif

#ifdef __USE_SCI__
  sciInit();
#endif

#ifdef __USE_SPI__
  spiInit();
#endif

}

#endif	/* __INCLUDE_TI_TMS570_MCU_H__ */
