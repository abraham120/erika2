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
* \file ee_mcu.h
* \brief Main header of Erika HCS12 mcu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/
 
/** 
* \mainpage Erika MCU for HCS12 
*
* \todo Other peripheral/controllers drivers for HCS12 micro-controllers.
*
* \section intro_sec This documentation describes the functions, the macros and the variables of the 
* Erika peripherals drivers for Freescale HCS12. Current supported peripherals: Timer, SCI, PIT.
* The Erika MCU for HCS12 contains also the default linker-scripts used if no linker-script is specified in
* the OIL file.
*/

#include "eecfg.h"
#include "cpu/hs12xs/inc/ee_cpu.h"

#ifndef __INCLUDE_FREESCALE_S12XS_MCU_H__
#define __INCLUDE_FREESCALE_S12XS_MCU_H__

/** Include a file with the registers of the s12 micro-controller */ 
#include "mcu/hs12xs/inc/ee_mcuregs.h"

/* Functions and Utilities */
/**
 * \brief			ee_s12_peripheral_frequency_mhz: This variables is used to save the peripheral frequency.
 */
extern volatile unsigned int ee_s12_peripheral_frequency_mhz;

/**
 * \brief			This macro is used to read the saved peripheral frequency.
 * \return			the value saved in ee_s12_peripheral_frequency_mhz
 */
#define EE_get_peripheral_frequency_mhz()    ee_s12_peripheral_frequency_mhz

/**
 * \brief			This macro is used to save the peripheral frequency in ee_s12_peripheral_frequency_mhz.
 * \param mhz		Frequency value in MHz.
 * \return			the new value saved in ee_s12_peripheral_frequency_mhz
 */
#define EE_set_peripheral_frequency_mhz(mhz) ee_s12_peripheral_frequency_mhz = mhz


/*************************************************************************
 System startup
 *************************************************************************/
#ifdef OO_CPU_HAS_STARTOS_ROUTINE

/**
 * \brief			This function is used to initialize the peripherals and start some activity inside the EE_cpu_startos.
 * \return			the result of the initialization (0 if there is no error, !=0 otherwise).
 */
int EE_s12_hal_cpu_startos(void);

/**
 * \brief			This function is used to start the OSEK kernel timer.
 * \return			Only in case of __OO_EXTENDED_STATUS__ the function returns the result of the timer initialization.
 */
#ifdef __OO_EXTENDED_STATUS__
EE_TYPEBOOL EE_cpu_startos(void);
#else
void EE_cpu_startos(void);
#endif	/* __OO_EXTENDED_STATUS__ */

#endif	/* OO_CPU_HAS_STARTOS_ROUTINE */

#endif	/* __INCLUDE_FREESCALE_S12XS_MCU_H__ */
