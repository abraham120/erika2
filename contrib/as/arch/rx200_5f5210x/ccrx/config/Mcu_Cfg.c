/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * Configured for (MCU): Renesas RX210R5F5210x
 *
 * Author:  2012,  Gianluca Franchino
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
	{
		MCU_CLK_MODE_LOCO_I1_B1,		/* Clock Settings Identifier       */
		125E3,							/* McuClockReferencePointFrequency */
#if	0
		0x00000000,						/* Run-Mode Clock Configuration    */
#endif
		MCU_SCKCR3_CKSEL_LOCO,			/* Select LOCO as clock source     */

#if	0
		0x00000000,						/* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKB_DIV_1	|		/* BCLK  = LOCO / 1                */            
		MCU_SCKCR_ICK_DIV_1,			/* ICKL  = LOCO / 1                */
		
	},
	
	{
		MCU_CLK_MODE_HOCO32_I1_B1,		/* Clock Settings Identifier       */
		32E6,							/* McuClockReferencePointFrequency */
#if	0
		0x00000100,						/* Run-Mode Clock Configuration    */
#endif
		MCU_SCKCR3_CKSEL_HOCO	|		/* Select HOCO as clock source     */
		(MCU_HOCO_FR_32MHZ << 27),		/* HOCO freq. 32MHz     */

		
#if	0
		0x00000000,						/* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKB_DIV_1	|		/* BCLK  = HOCO / 1                */            
		MCU_SCKCR_ICK_DIV_1,			/* ICKL  = HOCO / 1                */
		
	},

	{
		MCU_CLK_MODE_HOCO36_I1_B1,		/* Clock Settings Identifier       */
		36.864E6,						/* McuClockReferencePointFrequency */
#if	0
		0x08000100,						/* Run-Mode Clock Configuration    */
#endif
		MCU_SCKCR3_CKSEL_HOCO	|		/* Select LOCO as clock source     */
		(MCU_HOCO_FR_36_864MHZ << 27),	/* HOCO freq. 36.864 MHz     */		
#if	0
		0x00000000,						 /* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKB_DIV_1	|		 /* BCLK  = HOCO / 1                */           
		MCU_SCKCR_ICK_DIV_1,			 /* ICKL  = HOCO / 1                */
		
	},
	
	{
		MCU_CLK_MODE_HOCO40_I1_B2,		/* Clock Settings Identifier       */
		40E6,							/* McuClockReferencePointFrequency */
#if	0
		0x10000100,						/* Run-Mode Clock Configuration    */
#endif
		MCU_SCKCR3_CKSEL_HOCO	|		/* Select LOCO as clock source     */
		(MCU_HOCO_FR_40MHZ << 27),		/* HOCO freq. 40MHz     */		
#if	0
		0x00000100,						 /* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKB_DIV_2	|		 /* BCLK  = HOCO / 2                */
		MCU_SCKCR_ICK_DIV_1,			 /* ICKL  = HOCO / 1                */
		
	},
	
	{
		MCU_CLK_MODE_HOCO50_I1_B2,		 /* Clock Settings Identifier       */
		50E6,							 /* McuClockReferencePointFrequency */
#if	0
		0x18000100,						 /* Run-Mode Clock Configuration    */
#endif
		MCU_SCKCR3_CKSEL_HOCO	|		 /* Select LOCO as clock source     */
		(MCU_HOCO_FR_50MHZ << 27),		 /* HOCO freq. 40MHz				*/
		
#if	0
		0x00000100,						 /* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKB_DIV_2	|		 /* BCLK  = HOCO / 2                */ 
		MCU_SCKCR_ICK_DIV_1,			 /* ICKL  = HOCO / 1                */
		
	},
	
	{
		MCU_CLK_MODE_MOSC20_PLL40_I2_B2, /* Clock Settings Identifier       */
		40E6,							 /* McuClockReferencePointFrequency */
#if	0
		0x00381430,						 /* Run-Mode Clock Configuration    */
#endif
		MCU_SCKCR3_CKSEL_PLL		|	 /* Select PLL as clock source      */
		(MCU_PLLCR_PLIDIV_4 << 11)	|	 /* PLLDIV = 4     */
		(MCU_PLLCR_STC_MUL8 << 11)	|	 /* PLLSTC = 8     */
		MCU_MOFCR_MOSEL_RES			|    /* Oscillator is a resonetor (20MHz) */
		MCU_MOFCR_MODRV2_SWT_16_20,		 /* The resonetor is between 16-20MHz */
#if	0
		0x11010101,						 /* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKD_DIV_2	|		 /* BCLKD  = PLL / 2                 */
		MCU_SCKCR_PCKB_DIV_2	|		 /* BCLKB  = PLL / 2                 */
		MCU_SCKCR_BCK_DIV_2		|		 /* BCLK  = PLL / 2                  */
		MCU_SCKCR_ICK_DIV_2		|		 /* ICKL  = PLL / 2                  */
		MCU_SCKCR_FCK_DIV_2,			 /* FCKL  = PLL / 2                  */
		
	},
	{
		MCU_CLK_MODE_MOSC20_PLL50_I2_B2,	/* Clock Settings Identifier      */
		50E6,								/* McuClockReferencePointFrequency*/
#if	0
		0x00481430,							/* Run-Mode Clock Configuration   */
#endif
		MCU_SCKCR3_CKSEL_PLL		|		/* Select PLL as clock source     */
		(MCU_PLLCR_PLIDIV_4 << 11)	|		/* PLLDIV = 4     */
		(MCU_PLLCR_STC_MUL10 << 11) |		/* PLLSTC = 10     */
		MCU_MOFCR_MOSEL_RES			|		/* Oscill. is a resonetor (20MHz) */
		MCU_MOFCR_MODRV2_SWT_16_20,			/* The reson. is between 16-20MHz */
#if	0
		0x11010101,						 /* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKD_DIV_2	|		 /* BCLKD  = PLL / 2                 */
		MCU_SCKCR_PCKB_DIV_2	|		 /* BCLKB  = PLL / 2                 */
		MCU_SCKCR_BCK_DIV_2		|		 /* BCLK  = PLL / 2                  */
		MCU_SCKCR_ICK_DIV_2		|		 /* ICKL  = PLL / 2                  */
		MCU_SCKCR_FCK_DIV_2,			 /* FCKL  = PLL / 2                  */
		
	},
	{
		MCU_CLK_MODE_MOSC20_PLL60_I2_B2,	/* Clock Settings Identifier */
		60E6,								/* McuClockReferencePointFrequency*/
#if	0
		0x00581430,							/* Run-Mode Clock Configuration   */
#endif
		MCU_SCKCR3_CKSEL_PLL		|		/* Select PLL as clock source     */
		(MCU_PLLCR_PLIDIV_4 << 11)  |		/* PLLDIV = 4     */
		(MCU_PLLCR_STC_MUL12 << 11) |		/* PLLSTC = 12     */
		MCU_MOFCR_MOSEL_RES			|		/* Oscill. is a resonetor (20MHz) */
		MCU_MOFCR_MODRV2_SWT_16_20,			/* The reson. is between 16-20MHz */
#if	0
		0x11010101,						 	/* Run-Mode Clock Configuration 2  */
#endif
		MCU_SCKCR_PCKD_DIV_2	|			/* BCLKD = PLL / 2                */
		MCU_SCKCR_PCKB_DIV_2	|		 	/* BCLKB = PLL / 2                */
		MCU_SCKCR_BCK_DIV_2		|		 	/* BCLK  = PLL / 2                 */
		MCU_SCKCR_ICK_DIV_2		|		 	/* ICKL  = PLL / 2                 */
		MCU_SCKCR_FCK_DIV_2,				/* FCKL  = PLL / 2                 */
		
	},
	{
		MCU_CLK_MODE_MOSC20_PLL80_I2_B4,	/* Clock Settings Identifier */
		80E6,								/* McuClockReferencePointFrequency*/
#if	0
		0x00781430,							/* Run-Mode Clock Configuration   */
#endif
		MCU_SCKCR3_CKSEL_PLL		|		/* Select PLL as clock source     */
		(MCU_PLLCR_PLIDIV_4 << 11)	|		/* PLLDIV = 4     */
		(MCU_PLLCR_STC_MUL16 << 11) |		/* PLLSTC = 16     */
		MCU_MOFCR_MOSEL_RES			|		/* Oscill. is a resonetor (20MHz) */
		MCU_MOFCR_MODRV2_SWT_16_20,			/* The reson. is between 16-20MHz */
#if	0
		0x01000200,							/* Run-Mode Clock Configuration 2 */
#endif
		MCU_SCKCR_PCKD_DIV_2	|		 	/* BCLKD = PLL / 2                */
		MCU_SCKCR_PCKB_DIV_4	|		 	/* BCLKB = PLL / 4                */
		MCU_SCKCR_BCK_DIV_4		|		 	/* BCLK  = PLL / 4                 */
		MCU_SCKCR_ICK_DIV_2		|		 	/* ICKL  = PLL / 2                 */
		MCU_SCKCR_FCK_DIV_4,			 	/* FCKL  = PLL / 4                 */
		
	},
	{
		MCU_CLK_MODE_MOSC20_PLL100_I2_B4,	/* Clock Settings Identifier */
		100E6,								/* McuClockReferencePointFrequency*/
#if	0
		0x00981430,							/* Run-Mode Clock Configuration   */
#endif
		MCU_SCKCR3_CKSEL_PLL		|		/* Select PLL as clock source     */
		(MCU_PLLCR_PLIDIV_4 << 11)	|		/* PLLDIV = 4     */
		(MCU_PLLCR_STC_MUL20 << 11) |		/* PLLSTC = 20     */
		MCU_MOFCR_MOSEL_RES			|		/* Oscill. is a resonetor (20MHz) */
		MCU_MOFCR_MODRV2_SWT_16_20,			/* The reson. is between 16-20MHz */
#if	0
		0x01000200,							/* Run-Mode Clock Configuration 2 */
#endif
		MCU_SCKCR_PCKD_DIV_2	|		 	/* BCLKD = PLL / 2                */
		MCU_SCKCR_PCKB_DIV_4	|		 	/* BCLKB = PLL / 4                */
		MCU_SCKCR_BCK_DIV_4		|		 	/* BCLK  = PLL / 2                 */
		MCU_SCKCR_ICK_DIV_2		|		 	/* ICKL  = PLL / 2                 */
		MCU_SCKCR_FCK_DIV_4,			 	/* FCKL  = PLL / 4                 */
	}
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
