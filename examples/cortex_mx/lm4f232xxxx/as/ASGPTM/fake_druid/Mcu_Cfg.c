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

/*
 * fake-druid AUTOSAR MCU Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
 */

#define	MCU_AR_RELEASE_MAJOR_VERSION	4
#define	MCU_AR_RELEASE_MINOR_VERSION	0

#include "Mcu.h"

/*
 * MCU110:	For included (external) header files:
 * 		- <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * 		shall be verified.
 */
#if !defined( MCU_AR_MAJOR_VERSION ) || \
    ( MCU_AR_MAJOR_VERSION != MCU_AR_RELEASE_MAJOR_VERSION )
#error	Mcu: version mismatch.
#endif

/*
 * MCU124_Conf:	This container contains the configuration (parameters) for the
 * 		Clock settings of the MCU.
 *
 * Please see MCU031 for more information on the MCU clock settings.
 */
const Mcu_ClockSettingConfigType Mcu_ClockSettingConfigData[] =
{
  { /* MCU_CLOCK_MODE_NORMAL */
    MCU_CLOCK_MODE_PRIOSC_NO_PLL,	/* Clock Settings Identifier	      */
    1.6E7,				/* McuClockReferencePointFrequency    */
#if	0
    0x07802D51,				/* Run-Mode Clock Configuration	      */
#endif
    MCU_RCC_PWRDN	|		/* PLL Power Down		      */
    MCU_RCC_BYPASS	|		/* PLL Bypass			      */
    MCU_RCC_XTAL_16MHZ	|		/* 16 MHz			      */
    MCU_RCC_OSCSRC_INT	|		/* PIOSC			      */
    MCU_RCC_MOSCDIS,			/* Main Oscillator Disable	      */
#if	0
    0x07C02810,				/* Run-Mode Clock Configuration 2     */
#endif
    MCU_RCC2_PWRDN2	|		/* Power-Down PLL 2		      */
    MCU_RCC2_BYPASS2	|		/* PLL Bypass 2			      */
    MCU_RCC2_OSCSRC2_IO			/* PIOSC			      */
  },
};

/*
 * MCU123_Conf:	This container contains the configuration (parameters) for the
 * 		Mode setting of the MCU.
 *
 * Please see MCU035 for more information on the MCU mode settings.
 */

const Mcu_ModeSettingConfigType Mcu_ModeSettingConfigData[] = 
{
  {
    MCU_MODE_NORMAL,
  }
};

/*
 * MCU129_Conf:	This container contains the configuration (parameters) for the
 * 		RAM Sector setting.
 *
 * Please see MCU030 for more information on RAM sec-tor settings.
 */
const Mcu_RamSectorSettingConfType Mcu_RamSectorSettingConfigData[] =
{
  {
    0,		/* McuRamDefaultValue		*/
    0x20000000,	/* McuRamSectionBaseAddress	*/
    0x00008000,	/* McuRamSectionSize		*/
  }
};

/*
 * MCU131:	The structure Mcu_ConfigType is an external data structure (i.e.
 * 		implementation specific) and shall contain the initialization
 * 		data for the MCU module.
 * 		It shall contain:
 * 		- MCU dependent properties
 * 		- Reset Configuration
 * 		- Definition of MCU modes
 * 		- Definition of Clock settings
 * 		- Definition of RAM sections
 *
 * MCU054:	The structure Mcu_ConfigType shall provide a configurable
 * 		(enable/disable) clock failure notification if the MCU provides
 * 		an interrupt for such detection.
 * 		If the clock failure is detected with other HW mechanisms e.g.,
 * 		the generation of a trap, this notification shall be disabled
 * 		and the failure reporting shall be done outside the MCU driver.
 *
 * MCU035:	The definitions for each MCU mode within the structure
 * 		Mcu_ConfigType shall contain: (depending on MCU)
 * 		- MCU specific properties
 * 		- Change of CPU clock
 * 		- Change of Peripheral clock
 * 		- Change of PLL settings
 * 		- Change of MCU power supply
 *
 * MCU031:	The definitions for each Clock setting within the structure
 * 		Mcu_ConfigType shall contain:
 * 		- MCU specific properties as, e.g., clock safety features and
 * 		  special clock distribution settings
 * 		- PLL settings /start lock options
 * 		- Internal oscillator setting
 *
 * MCU030:	The definitions for each RAM section within the structure
 * 		Mcu_ConfigType shall contain:
 * 		- RAM section base address
 * 		- Section size
 * 		- Data pre-setting to be initialized
 * 		Usage of linker symbols instead of scalar values is allowed.
 */
const Mcu_ConfigType Mcu_Config[] = 
{
  {
    FALSE,				/* McuClockSrcFailureNotification */
    1,					/* McuNumberOfMcuModes		  */
    1,					/* McuRamSectors		  */
    NULL_PTR,				/* McuResetSetting		  */
    &Mcu_ClockSettingConfigData[0],	/* McuClockSettingConfig	  */
    /*NULL_PTR,*/			/* McuDemEventParametersRefs	  */
    &Mcu_ModeSettingConfigData[0],	/* McuModeSettingConf		  */
    &Mcu_RamSectorSettingConfigData[0]	/* McuRamSectorSettingConf	  */
  }
};
