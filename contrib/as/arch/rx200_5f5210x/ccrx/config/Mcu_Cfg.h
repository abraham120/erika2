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

/** @file	Mcu_Cfg.h
 *  @brief	fake-druid AUTOSAR MCU Driver Configuration Header File.
 *
 *  Configured for (MCU): Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2012
 */


#if !(\
 ((MCU_SW_MAJOR_VERSION == 1) && \
  (MCU_SW_MINOR_VERSION == 0) && \
  (MCU_SW_PATCH_VERSION == 0))\
)
#error Mcu: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	MCU_CFG_H
#define	MCU_CFG_H

/*
 * MCU118_Conf:	This container contains the configuration (parameters) of the
 * 		MCU driver.
 */
/* McuGeneralConfiguration */

/** @brief	Development Error Detection
 *
 *  <b>MCU166_Conf:</b> Pre-processor switch for enabling the development error
 *  detection and reporting.
 */
#define	MCU_DEV_ERROR_DETECT	STD_OFF

/** @brief	Ram State Retrieval API
 *
 *  <b>MCU181_Conf:</b> Pre-processor switch to enable/disable the API
 *  <tt>Mcu_GetRamState()</tt>. (e.g. If the H/W does not support the
 *  functionality, this parameter can be used to disable the Api).
 */
#define	MCU_GET_RAM_STATE_API	STD_OFF

/** @brief	Clock Initialization API
 *
 *  <b>MCU182_Conf:</b> If this parameter is set to FALSE, the clock
 *  initialization has to be disabled from the MCU driver. This concept applies
 *  when there are some write once clock registers and a bootloader is present.
 *  If this parameter is set to TRUE, the MCU driver is responsible of the clock
 +  initialization.
 */
#define	MCU_INIT_CLOCK		STD_ON

/** @brief	Hardware PLL
 *
 *  <b>MCU180_Conf:</b>	This parameter shall be set True, if the H/W does not
 *  have a PLL or the PLL circuitry is enabled after the power on without S/W
 *  intervention. In this case <tt>MCU_DistributePllClock()</tt> has to be
 *  disabled and <tt>MCU_GetPllStatus()</tt> has to return
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt>. Otherwise this parameters has to be set
 *  False.
 */
#define	MCU_NO_PLL		STD_OFF

/** @brief	Microcontroller Reset API
 *
 *  <b>MCU167_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Mcu_PerformReset()</tt>.
 */
#define	MCU_PERFORM_RESET_API	STD_ON

/** @brief	Version Informations Retrieval API
 *
 *  <b>MCU168_Conf:</b> Pre-processor switch to enable / disable the API to read
 *  out the modules version information.
 */
#define	MCU_VERSION_INFO_API	STD_ON


/*
 *The following are defines for the bit fields in the System Clock Control 
 * Register (SCKCR).
 */
/* Peripheral Module Clock D (PCKD) */
#define MCU_SCKCR_PCKD_DIV_1  0x00000000U /* PCLKD = System Clock / 1  */
#define MCU_SCKCR_PCKD_DIV_2  0x00000001U /* PCLKD = System Clock / 2  */
#define MCU_SCKCR_PCKD_DIV_4  0x00000002U /* PCLKD = System Clock / 4  */
#define MCU_SCKCR_PCKD_DIV_8  0x00000003U /* PCLKD = System Clock / 8  */
#define MCU_SCKCR_PCKD_DIV_16 0x00000004U /* PCLKD = System Clock / 16 */
#define MCU_SCKCR_PCKD_DIV_32 0x00000005U /* PCLKD = System Clock / 32 */
#define MCU_SCKCR_PCKD_DIV_64 0x00000006U /* PCLKD = System Clock / 64 */
/* Peripheral Module Clock B (PCKB) */
#define MCU_SCKCR_PCKB_DIV_1  0x00001010U /* PCKB = System Clock / 1  */
#define MCU_SCKCR_PCKB_DIV_2  0x00001110U /* PCKB = System Clock / 2  */
#define MCU_SCKCR_PCKB_DIV_4  0x00001210U /* PCKB = System Clock / 4  */
#define MCU_SCKCR_PCKB_DIV_8  0x00001310U /* PCKB = System Clock / 8  */
#define MCU_SCKCR_PCKB_DIV_16 0x00001410U /* PCKB = System Clock / 16 */
#define MCU_SCKCR_PCKB_DIV_32 0x00001510U /* PCKB = System Clock / 32 */
#define MCU_SCKCR_PCKB_DIV_64 0x00001610U /* PCKB = System Clock / 64 */
/* External Bus Clock (BCLK) */
#define MCU_SCKCR_BCK_DIV_1  0x00001010U /* BCLK = System Clock / 1  */
#define MCU_SCKCR_BCK_DIV_2  0x00011010U /* BCLK = System Clock / 2  */
#define MCU_SCKCR_BCK_DIV_4  0x00021010U /* BCLK = System Clock / 4  */
#define MCU_SCKCR_BCK_DIV_8  0x00031010U /* BCLK = System Clock / 8  */
#define MCU_SCKCR_BCK_DIV_16 0x00041010U /* BCLK = System Clock / 16 */
#define MCU_SCKCR_BCK_DIV_32 0x00051010U /* BCLK = System Clock / 32 */
#define MCU_SCKCR_BCK_DIV_64 0x00061010U /* BCLK = System Clock / 64 */
/* BCLK Pin Output Control */
#define MCU_SCKCR_PSTOP1_EN  0x00801010U /* BCLK pin output is enabled */
#define MCU_SCKCR_PSTOP1_DIS 0xFF7FFFFFU /* BCLK pin output is disabled */
/* System Clock Select (ICLK)*/
#define MCU_SCKCR_ICK_DIV_1  0x00001010U /* ICLK = System Clock / 1  */
#define MCU_SCKCR_ICK_DIV_2  0x01001010U /* ICLK = System Clock / 2  */
#define MCU_SCKCR_ICK_DIV_4  0x02001010U /* ICLK = System Clock / 4  */
#define MCU_SCKCR_ICK_DIV_8  0x03001010U /* ICLK = System Clock / 8  */
#define MCU_SCKCR_ICK_DIV_16 0x04001010U /* ICLK = System Clock / 16 */
#define MCU_SCKCR_ICK_DIV_32 0x05001010U /* ICLK = System Clock / 32 */
#define MCU_SCKCR_ICK_DIV_64 0x06001010U /* ICLK = System Clock / 64 */
/* FlashIF Clock (FCLK)*/
#define MCU_SCKCR_FCK_DIV_1  0x00001010U /* FCLK = System Clock / 1  */
#define MCU_SCKCR_FCK_DIV_2  0x10001010U /* FCLK = System Clock / 2  */
#define MCU_SCKCR_FCK_DIV_4  0x20001010U /* FCLK = System Clock / 4  */
#define MCU_SCKCR_FCK_DIV_8  0x30001010U /* FCLK = System Clock / 8  */
#define MCU_SCKCR_FCK_DIV_16 0x40001010U /* FCLK = System Clock / 16 */
#define MCU_SCKCR_FCK_DIV_32 0x50001010U /* FCLK = System Clock / 32 */
#define MCU_SCKCR_FCK_DIV_64 0x60001010U /* FCLK = System Clock / 64 */

/*
 * The following are defines for the bit fields in the System Clock Control 
 * Register 3 (SCKCR3).
 */
#define MCU_SCKCR3_CKSEL_LOCO 0x0000U /* Clock source is LOCO */
#define MCU_SCKCR3_CKSEL_HOCO 0x0100U /* Clock source is HOCO */
#define MCU_SCKCR3_CKSEL_MAIN 0x0200U /* Clock source is Main clock osc.*/
#define MCU_SCKCR3_CKSEL_SUB  0x0300U /* Clock source is Sub-clock osc.*/
#define MCU_SCKCR3_CKSEL_PLL  0x0400U /* Clock source is PLL circuit*/

/*
 * The following are defines for the bit fields in the PLL Control register 
 * (PLLCR).
 */
#define MCU_PLLCR_PLIDIV_1  0x0000U /* PLL Division Rate 1 */
#define MCU_PLLCR_PLIDIV_2  0x0001U /* PLL Division Rate 2 */
#define MCU_PLLCR_PLIDIV_4  0x0002U /* PLL Division Rate 4 */

#define MCU_PLLCR_STC_MUL8  0x0700U /* PLL Multiplication Factor 8  */
#define MCU_PLLCR_STC_MUL10 0x0900U /* PLL Multiplication Factor 10 */
#define MCU_PLLCR_STC_MUL12 0x0B00U /* PLL Multiplication Factor 12 */
#define MCU_PLLCR_STC_MUL16 0x0F00U /* PLL Multiplication Factor 16 */
#define MCU_PLLCR_STC_MUL20 0x1300U /* PLL Multiplication Factor 20 */
#define MCU_PLLCR_STC_MUL24 0x1700U /* PLL Multiplication Factor 24 */
#define MCU_PLLCR_STC_MUL25 0x1800U /* PLL Multiplication Factor 25 */

/*
 * The following are defines for the bit fields in the PLL Control register 2
 * (PLLCR2).
 */
#define MCU_PLLCR2_START 0x01U /* Active the PLL circuit */
#define MCU_PLLCR2_STOP  0x00U /* Stop the PLL circuit   */

/*
 * The following are defines for the bit fields in the External Bus Clock 
 * Control Register (BCKCR).
 */
#define MCU_BCKCR_BCLK_DIV1 0x00U /* External Bus Clock defined by SCKCR.BCK*/
#define MCU_BCKCR_BCLK_DIV2 0x01U /* Ext. Bus Clock defined by SCKCR.BCK/2  */

/*
 * The following are defines for the bit fields in the Main Clock Oscillator 
 * Control Register (MOSCCR).
 */
#define MCU_MOSCCR_EN   0x00U /* Main Clocl Oscillator is operating */
#define MCU_MOSCCR_STOP 0x01U /* Main Clock Oscillator is stopped   */

/*
 * The following are defines for the bit fields in the Sub-Clock Oscillator 
 * Control Register (SOSCCR).
 */
#define MCU_SOSCCR_EN   0x00U /* Sub-Clocl Oscillator is operating */
#define MCU_SOSCCR_STOP 0x01U /* Sub-Clock Oscillator is stopped   */

/*
 * The following are defines for the bit fields in the Low-Speed Clock 
 * Oscillator Control Register (LOCCR).
 */
#define MCU_LOCO_EN   0x00U /* Low-Speed Clocl Oscillator is operating */
#define MCU_LOCO_STOP 0x01U /* Low-Speed Clock Oscillator is stopped   */

/*
 * The following are defines for the bit fields in the IWDT-Dedicated Low-Speed 
 * Clock Oscillator Control Register (ILOCOCR).
 */
#define MCU_IWDTLOCO_EN   0x00U /* ILOCO is operating */
#define MCU_IWDTLOCO_STOP 0x01U /* ILOCO is stopped   */

/*
 * The following are defines for the bit fields in the High-Speed Clock 
 * Oscillator Control Register (HOCCR).
 */
#define MCU_HOCO_EN   0x00U /* High-Speed Clocl Oscillator is operating */
#define MCU_HOCO_STOP 0x01U /* High-Speed Clock Oscillator is stopped */

/*
 * The following are defines for the bit fields in the High-Speed Clock 
 * Oscillator Control Register 2 (HOCCR2).
 */
#define MCU_HOCO_FR_32MHZ	  0x00U /* HOCO Freq. is 32 MHz     */
#define MCU_HOCO_FR_36_864MHZ 0x01U /* HOCO Freq. is 36.864 MHz */
#define MCU_HOCO_FR_40MHZ	  0x02U /* HOCO Freq. is 40 MHz     */
#define MCU_HOCO_FR_50MHZ	  0x03U /* HOCO Freq. is 50 MHz     */

/*
 * The following are defines for the bit fields in the Oscillation Stop 
 * Detection Control Register (OSTDCR).
 */
#define MCU_OSTDCR_OSTDI_EN  0x01U /* Enable Osc. Stop Detec. Interrupt  */
#define MCU_OSTDCR_OSTDI_DIS 0x00U /* Disable Osc. Stop Detec. Interrupt */

/*
 * The following are defines for the bit fields in the Main Clock Oscillator 
 * Forced Oscillation Control Register (MOFCR).
 */
#define MCU_MOFCR_MOFXIN_EN 0x01U /* The Main Clk Osc. is forcedly oscillated */
#define MCU_MOFCR_MOFXIN_EN 0x01U /* The Main Clk Osc. is not controlled by 
									MOFXIN */
#define MCU_MOFCR_MODRV_NON_LEAD    	0x00U     /* Drive capability is non-lead
													type ceramic resonetor */
#define MCU_MOFCR_MODRV_LEAD      		0x0EU     /* Drive capability is lead type 
													ceramic resonetor */
#define MCU_MOFCR_MODRV2_SWT_1_8    	0x00U     /* Drive capability switch: 
													1 MHz to 8 MHz */
#define MCU_MOFCR_MODRV2_SWT_8_1_15_9 	0x10U     /* Drive capability switch: 
													8.1 MHz to 15.9 MHz */
#define MCU_MOFCR_MODRV2_SWT_16_20    	0x30U     /* Drive capability switch: 
													16 MHz to 20 MHz */
#define MCU_MOFCR_MOSEL_RES	0x00U /* Oscillator Source: Resonator */
#define MCU_MOFCR_MOSEL_EXT	0x40U /* External Oscillator Input */

/*
 * The following are defines for the bit fields in the High-Speed Clock 
 * Oscillator Power Supply Control Register (HOCOPCR)
 */
#define MCU_HOCOPCR_PWR_ON 0x00 /* Turn the Power Supply of the HOCO on */
#define MCU_HOCOPCR_PWR_OFF 0x01 /* Turn the Power Supply of the HOCO off */

/** @brief	125KHz
 *
 *  Low-speed Internal Oscillator - System Clock Divisor 1, 
 *	Peripheral Clock B DIV 1.
 */
#define	MCU_CLK_MODE_LOCO_I1_B1		0x00

/** @brief	Clock Mode Normal
 *
 *  <b>125KHz:</b> Low-speed Internal Oscillator - System Clock Divisor 1,
 *	Peripheral Clock B DIV 1.
 */
#define	MCU_CLOCK_MODE_NORMAL		MCU_CLK_MODE_LOCO_I1_B1

/** @brief	32MHz
 *
 *  High-speed Internal Oscillator (HOCO) - HOCO freq. 32MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 1.
 */
#define	MCU_CLK_MODE_HOCO32_I1_B1	0x01

/** @brief	36.864 MHz
 *
 *  High-speed Internal Oscillator (HOCO) - HOCO freq. 36.864 MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 1.
 */
#define	MCU_CLK_MODE_HOCO36_I1_B1	0x02

/** @brief	40MHz
 *
 *  High-speed Internal Oscillator (HOCO) - HOCO freq. 40MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 2.
 */
#define	MCU_CLK_MODE_HOCO40_I1_B2	0x03

/** @brief	50MHz
 *
 *  High-speed Internal Oscillator (HOCO) - HOCO freq. 50MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 2.
 */
#define	MCU_CLK_MODE_HOCO50_I1_B2	0x04

/** @brief	40MHz
 *
 *  Main Clock Osc (Xtal 20MHz) with PLL - PLL out Freq. 40MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 2.
 */
#define	MCU_CLK_MODE_MOSC20_PLL40_I2_B2	0x05

/** @brief	50MHz
 *
 *  Main Clock Osc (Xtal 20MHz) with PLL - PLL out Freq. 50MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 2.
 */
#define	MCU_CLK_MODE_MOSC20_PLL50_I2_B2	0x06

/** @brief	60MHz
 *
 *  Main Clock Osc (Xtal 20MHz) with PLL - PLL out Freq. 60MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 2.
 */
#define	MCU_CLK_MODE_MOSC20_PLL60_I2_B2	0x07

/** @brief	80MHz
 *
 *  Main Clock Osc (Xtal 20MHz) with PLL - PLL out Freq. 80MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 4.
 */
#define	MCU_CLK_MODE_MOSC20_PLL80_I2_B4	0x08

/** @brief	80MHz
 *
 *  Main Clock Osc (Xtal 20MHz) with PLL - PLL out Freq. 100MHz,
 *	System Clock Divisor 1, Peripheral Clock B Divisor 4.
 */
#define	MCU_CLK_MODE_MOSC20_PLL100_I2_B4	0x09

/** @brief	Clock Modes Number
 *
 *  Number of supported clock modes.
 */
#define	MCU_CLOCK_MODES_NUMBER		MCU_CLK_MODE_MOSC20_PLL100_I2_B4 + 1

/** @brief	Raw Reset Type
 *
 *  <b>MCU235:</b> The type Mcu_RawResetType specifies the reset reason in raw
 *  register format, read from a reset status register.
 *
 *  <b>MCU236:</b> The type shall be <tt>uint8</tt>, <tt>uint16</tt> or
 *  <tt>uint32</tt> based on best performance.
 */
typedef	uint8_least	Mcu_RawResetType;

/** @brief	Clock Settings Configuration Parameters
 *
 *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
 *  for the Clock settings of the MCU.
 *
 *  @see <b>MCU031</b> for more information on the MCU clock settings.
 */
typedef struct {

	/** @brief	Clock Settings Identifier
	 *
	 *  <b>MCU183_Conf:</b>	The Id of this <tt>McuClockSettingConfig</tt> to
	 *  				be used as argument for the API call
	 *  				<tt>Mcu_InitClock()</tt>.
	 */
	Mcu_ClockType	McuClockSettingId;

	/** @brief	Clock Frequency
	 *
	 *  <b>MCU174_Conf:</b> This container defines a reference point in the Mcu
	 *  Clock tree. It defines the frequency which then can be used by other
	 *  modules as an input value. Lower multiplictiy is 1, as even in the
	 *  simpliest case (only one frequency is used), there is one frequency to be
	 *  defined.
	 *
	 *  <b>MCU175_Conf:</b> This is the frequency for the specific instance of the
	 *  <tt>McuClockReferencePoint</tt> container. It shall be given in Hz.
	 */
	float32	McuClockReferencePointFrequency;
	
	/** @brief	Run-Mode Clock Configuration 
	 *
	 *  <pre>
	 *  Bit/Field	Description
	 *  31:29	Reserved (Should be set to 000b)
	 *  28:27	HCFRQ HOCO Frequency Setting (Reg, HOCOCR2)
	 *  26:24	Reserved (Should be set to 000b)
	 *  23:19	STC PLL Frequency Multiplication Factor Select (Reg. PLLCR)
	 *  18:13	Reserved (Should be set to 000000b)
	 *  12:11	PLIDIV PLL Input Frequency Division Ratio Select (Reg. PLLCR)
	 *  10:8	Clock Source Select (This bits are placed in SCKCR3.CKSEL)
	 *	7		Reserved (Should be set to 0b)
	 *  6		MOSEL Main Clock Oscillator Switch (Reg. MOFCR)
	 *  5:4		MODRV2 Main Clock Oscillator Drive Capacity Sw. 2 (Reg. MOFCR)
	 *  3:1		MODRV Main Clock Oscillator Drive Capacity Switch (Reg. MOFCR)
	 *  0		MOFXIN Main Clock Oscillator Forced Oscillation (Reg. MOFCR)
	 *  </pre>
	 */
	uint32 McuRunModeClockConfiguration;
	
	/** @brief Run-Mode Clock Configuration 2
	*
	*  <pre>
	*  Bit/Field	Description
	*  31:28	FCK FlashIf Clock (This value has to be set by the Flash Driver)
	*  27:24	ICK System Clock (ICKL) Select
	*  23		PSTOP1 BCLK Pin Output Control (This value has to be set by
	*											Mcu_Init)
	*  22:20	Reserved (Should be set to 000b)
	*  19:16	BCK External Bus Clock (BCLK) Select. (This value has 
	*				to be set by the Ext. Bus module.
	*  15:12	Reserved (Should be set to 0001b)
	*  11:8		PCKB Peripheral Module Clock B (PCLKB) Select
	*  7:4		Reserved (Should be set to 0001b)
	*  3:0		PCKD Peripheral Module Clock D (PCLKD) Select. (This value has 
	*				to be set by the ADC module (S12AD module)
	*  </pre>
	*/
	uint32 McuRunModeClockConfiguration2;

} Mcu_ClockSettingConfigType;

/*
 * MCU176_Conf:	The parameter represents the MCU Mode settings.
 */

/** @brief	MCU Mode Normal
 */
#define	MCU_MODE_NORMAL	0x00

/** @brief	MCU Modes Number
 *
 *  Number of supported MCU modes.
 */
#define	MCU_MODES_NUMBER	MCU_MODE_NORMAL + 1

/** @brief	Mode Setting Configuration Paramaters
 *
 *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
 *  for the Mode setting of the MCU.
 *
 *  @see <b>MCU035</b> for more information on the MCU mode settings.
 */
typedef struct {

  /** @brief	MCU Mode
   *
   *  <b>MCU176_Conf:</b> The parameter represents the MCU Mode settings.
   */
  uint8_least	mode;

} Mcu_ModeSettingConfigType;

/** @brief	Ram Sector Setting Configuration Parameters
 *
 *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
 *  for the RAM Sector setting.
 *
 *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
 */
typedef struct {

  /** @brief	Default Value
   *
   *  <b>MCU177_Conf:</b> This parameter shall represent the Data pre-setting to
   *  be initialized.
   */
  uint8		McuRamDefaultValue;
  
  /** @brief	Base Address
   *
   *  <b>MCU178_Conf:</b> This parameter shall represent the MCU RAM section
   *  base address.
   */
  uint32	McuRamSectionBaseAddress;

  /** @brief	Section Size
   *
   *  <b>MCU179_Conf:</b> This parameter shall represent the MCU RAM Section
   *  size.
   */
  uint32	McuRamSectionSize;

} Mcu_RamSectorSettingConfType;

/** @brief	MCU Configuration Parameters
 *
 *  <b>MCU131:</b> The structure <tt>Mcu_ConfigType</tt> is an external data
 *  structure (i.e. implementation specific) and shall contain the
 *  initialization data for the MCU module. It shall contain:
 *  - MCU dependent properties
 *  - Reset Configuration
 *  - Definition of MCU modes
 *  - Definition of Clock settings
 *  - Definition of RAM sections
 *
 *  <b>MCU054:</b> The structure <tt>Mcu_ConfigType</tt> shall provide a
 *  configurable (enable/disable) clock failure notification if the MCU provides
 *  an interrupt for such detection. If the clock failure is detected with other
 *  HW mechanisms e.g., the generation of a trap, this notification shall be
 *  disabled and the failure reporting shall be done outside the MCU driver.
 *
 *  <b>MCU035:</b> The definitions for each MCU mode within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain: (depending on MCU)
 *  - MCU specific properties
 *  - Change of CPU clock
 *  - Change of Peripheral clock
 *  - Change of PLL settings
 *  - Change of MCU power supply
 *
 *  <b>MCU031:</b> The definitions for each Clock setting within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain:
 *  - MCU specific properties as, e.g., clock safety features and special clock
 *  distribution settings
 *  - PLL settings /start lock options
 *  - Internal oscillator setting
 *
 *  <b>MCU030:</b> The definitions for each RAM section within the structure
 *  <tt>Mcu_ConfigType</tt> shall contain:
 *  - RAM section base address
 *  - Section size
 *  - Data pre-setting to be initialized
 * Usage of linker symbols instead of scalar values is allowed.
 */
typedef struct {

  /** @brief	Clock Source Failure Notification
   *
   *  <b>MCU170_Conf:</b> Enables/Disables clock failure notification. In case
   *  this feature is not supported by HW the setting should be disabled.
   */
  boolean	McuClockSrcFailureNotification;

  /** @brief	MCU Modes Number
   *
   *  <b>MCU171_Conf:</b> This parameter shall represent the number of Modes
   *  available for the MCU. calculationFormula = Number of configured
   *  <tt>McuModeSettingConf</tt>.
   */
  uint8		McuNumberOfMcuModes;

  /** @brief	RAM Sectors Number
   *
   *  <b>MCU172_Conf:</b> This parameter shall represent the number of RAM
   *  sectors available for the MCU. calculationFormula = Number of configured
   *  <tt>McuRamSectorSettingConf</tt>
   */
  uint32	McuRamSectors;

  /** @brief	Reset Setting Configuration Parameters
   *
   *  <b>MCU173_Conf:</b> This parameter relates to the MCU specific reset
   *  configuration. This applies to the function <tt>Mcu_PerformReset()</tt>,
   *  which performs a microcontroller reset using the hardware feature of the
   *  microcontroller.
   */
  uint8		* McuResetSettingPtr;

  /** @brief	Clock Setting Configuration Parameters
   *
   *  <b>MCU124_Conf:</b> This container contains the configuration (parameters)
   *  for the Clock settings of the MCU.
   *
   *  @see <b>MCU031</b> for more information on the MCU clock settings.
   */
  const Mcu_ClockSettingConfigType * McuClockSettingConfig;

#if ( MCU_DEV_ERROR_DETECT == STD_ON )
  /** @brief	DEM Event Configuration Parameters
   *
   *  <b>MCU187_Conf:</b> Container for the references to
   *  <tt>DemEventParameter</tt> elements which shall be invoked using the API
   *  <tt>Dem_ReportErrorStatus()</tt> API in case the corresponding error
   *  occurs. The EventId is taken from the referenced DemEventParameter's
   *  DemEventId value. The standardized errors are provided in the container
   *  and can be extended by vendor specific error references. */
  Mcu_DemEventParametersTypeRefs * McuDemEventParametersRefs;
#endif

  /** @brief	Mode Setting Configuration Parameters
   *
   *  <b>MCU123_Conf:</b> This container contains the configuration (parameters)
   *  for the Mode setting of the MCU.
   *
   *  @see <b>MCU035</b> for more information on the MCU mode settings.
   */
  const Mcu_ModeSettingConfigType  * McuModeSettingConf;

  /** @brief	Ram Sector Setting  Configuration Parameters
   *
   *  <b>MCU129_Conf:</b> This container contains the configuration (parameters)
   *  for the RAM Sector setting.
   *
   *  @see <b>MCU030</b> for more information on RAM sec-tor settings.
   */
  const Mcu_RamSectorSettingConfType * McuRamSectorSettingConf;

} Mcu_ConfigType;

/** @brief	Default Configuration
 *
 *  Identifier for Default MCU Driver Configuration.
 */
#define	MCU_CONFIG_DEFAULT	0x00000000U

/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default MCU Driver Configuration.
 */
#define	MCU_CONFIG_DEFAULT_PTR	&Mcu_Config[MCU_CONFIG_DEFAULT]

/** @brief	MCU Configuration Pointer
 *
 *  Pointer to MCU Driver Configuration.
 */
#define	MCU_CONFIG_PTR		&Mcu_Config[MCU_CONFIG_DEFAULT]

#endif	/* MCU_CFG_H */
