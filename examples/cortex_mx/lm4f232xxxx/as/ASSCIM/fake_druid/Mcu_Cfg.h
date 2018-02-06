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
 *  Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 *  @author	Giuseppe Serano
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
#define	MCU_INIT_CLOCK		STD_OFF

/** @brief	Hardware PLL
 *
 *  <b>MCU180_Conf:</b>	This parameter shall be set True, if the H/W does not
 *  have a PLL or the PLL circuitry is enabled after the power on without S/W
 *  intervention. In this case <tt>MCU_DistributePllClock()</tt> has to be
 *  disabled and <tt>MCU_GetPllStatus()</tt> has to return
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt>. Otherwise this parameters has to be set
 *  False.
 */
#define	MCU_NO_PLL		STD_ON

/** @brief	Microcontroller Reset API
 *
 *  <b>MCU167_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Mcu_PerformReset()</tt>.
 */
#define	MCU_PERFORM_RESET_API	STD_OFF

/** @brief	Version Informations Retrieval API
 *
 *  <b>MCU168_Conf:</b> Pre-processor switch to enable / disable the API to read
 *  out the modules version information.
 */
#define	MCU_VERSION_INFO_API	STD_OFF

/** @brief	MCU PIOSC Calibrartion Maximum Attempts
 *
 *  Maximum attempts for TI Stellaris LM4F232XXX Precision Internal OSCillator
 *  calibration.
 */
#define	MCU_PIOSC_CAL_MAX_ATTEMPTS	0x00000010U
/*
 * MCU183_Conf:	The Id of this McuClockSettingConfig to be used as argument for
 * 		the API call "Mcu_InitClock".
 */

/* The following are defines for the bit fields in the RCC. */
#define MCU_RCC_ACG		0x08000000U	/**< Auto Clock Gating	      */
#define MCU_RCC_SYSDIV_M	0x07800000U	/**< System Clock Divisor     */
#define MCU_RCC_SYSDIV_1	0x00000000U	/**< System clock /2	      */
#define MCU_RCC_SYSDIV_2	0x00800000U	/**< System clock /2	      */
#define MCU_RCC_SYSDIV_3	0x01000000U	/**< System clock /3	      */
#define MCU_RCC_SYSDIV_4	0x01800000U	/**< System clock /4	      */
#define MCU_RCC_SYSDIV_5	0x02000000U	/**< System clock /5	      */
#define MCU_RCC_SYSDIV_6	0x02800000U	/**< System clock /6	      */
#define MCU_RCC_SYSDIV_7	0x03000000U	/**< System clock /7	      */
#define MCU_RCC_SYSDIV_8	0x03800000U	/**< System clock /8	      */
#define MCU_RCC_SYSDIV_9	0x04000000U	/**< System clock /9	      */
#define MCU_RCC_SYSDIV_10	0x04800000U	/**< System clock /10	      */
#define MCU_RCC_SYSDIV_11	0x05000000U	/**< System clock /11	      */
#define MCU_RCC_SYSDIV_12	0x05800000U	/**< System clock /12	      */
#define MCU_RCC_SYSDIV_13	0x06000000U	/**< System clock /13	      */
#define MCU_RCC_SYSDIV_14	0x06800000U	/**< System clock /14	      */
#define MCU_RCC_SYSDIV_15	0x07000000U	/**< System clock /15	      */
#define MCU_RCC_SYSDIV_16	0x07800000U	/**< System clock /16	      */
#define MCU_RCC_USESYSDIV	0x00400000U	/**< Enable System Clock
						 *   Divisor		      */
#define MCU_RCC_USEPWMDIV	0x00100000U	/**< Enable PWM Clock Divisor */
#define MCU_RCC_PWMDIV_M	0x000E0000U	/**< PWM Unit Clock Divisor   */
#define MCU_RCC_PWMDIV_2	0x00000000U	/**< PWM clock /2	      */
#define MCU_RCC_PWMDIV_4	0x00020000U	/**< PWM clock /4	      */
#define MCU_RCC_PWMDIV_8	0x00040000U	/**< PWM clock /8	      */
#define MCU_RCC_PWMDIV_16	0x00060000U	/**< PWM clock /16	      */
#define MCU_RCC_PWMDIV_32	0x00080000U	/**< PWM clock /32	      */
#define MCU_RCC_PWMDIV_64	0x000A0000U	/**< PWM clock /64	      */
#define MCU_RCC_PWRDN		0x00002000U	/**< PLL Power Down	      */
#define MCU_RCC_BYPASS		0x00000800U	/**< PLL Bypass		      */
#define MCU_RCC_XTAL_M		0x000007C0U	/**< Crystal Value	      */
#define MCU_RCC_XTAL_4MHZ	0x00000180U	/**< 4 MHz		      */
#define MCU_RCC_XTAL_4_09MHZ	0x000001C0U	/**< 4.096 MHz		      */
#define MCU_RCC_XTAL_4_91MHZ	0x00000200U	/**< 4.9152 MHz		      */
#define MCU_RCC_XTAL_5MHZ	0x00000240U	/**< 5 MHz		      */
#define MCU_RCC_XTAL_5_12MHZ	0x00000280U	/**< 5.12 MHz		      */
#define MCU_RCC_XTAL_6MHZ	0x000002C0U	/**< 6 MHz		      */
#define MCU_RCC_XTAL_6_14MHZ	0x00000300U	/**< 6.144 MHz		      */
#define MCU_RCC_XTAL_7_37MHZ	0x00000340U	/**< 7.3728 MHz		      */
#define MCU_RCC_XTAL_8MHZ	0x00000380U	/**< 8 MHz		      */
#define MCU_RCC_XTAL_8_19MHZ	0x000003C0U	/**< 8.192 MHz		      */
#define MCU_RCC_XTAL_10MHZ	0x00000400U	/**< 10 MHz		      */
#define MCU_RCC_XTAL_12MHZ	0x00000440U	/**< 12 MHz		      */
#define MCU_RCC_XTAL_12_2MHZ	0x00000480U	/**< 12.288 MHz		      */
#define MCU_RCC_XTAL_13_5MHZ	0x000004C0U	/**< 13.56 MHz		      */
#define MCU_RCC_XTAL_14_3MHZ	0x00000500U	/**< 14.31818 MHz	      */
#define MCU_RCC_XTAL_16MHZ	0x00000540U	/**< 16 MHz		      */
#define MCU_RCC_XTAL_16_3MHZ	0x00000580U	/**< 16.384 MHz		      */
#define MCU_RCC_XTAL_18MHZ	0x000005C0U	/**< 18.0 MHz		      */
#define MCU_RCC_XTAL_20MHZ	0x00000600U	/**< 20.0 MHz		      */
#define MCU_RCC_XTAL_24MHZ	0x00000640U	/**< 24.0 MHz		      */
#define MCU_RCC_XTAL_25MHZ	0x00000680U	/**< 25.0 MHz		      */
#define MCU_RCC_OSCSRC_M	0x00000030U	/**< Oscillator Source	      */
#define MCU_RCC_OSCSRC_MAIN	0x00000000U	/**< MOSC		      */
#define MCU_RCC_OSCSRC_INT	0x00000010U	/**< IOSC		      */
#define MCU_RCC_OSCSRC_INT4	0x00000020U	/**< IOSC/4		      */
#define MCU_RCC_OSCSRC_30	0x00000030U	/**< 30 kHz		      */
#define MCU_RCC_IOSCDIS		0x00000002U	/**< Internal Oscillator
						 *   Disable		      */
#define MCU_RCC_MOSCDIS		0x00000001U	/**< Main Oscillator Disable  */
#define MCU_RCC_SYSDIV_S	23U

/* The following are defines for the bit fields in the MCU_RCC2 register. */
#define MCU_RCC2_USERCC2	0x80000000U	/**< Use RCC2	      */
#define MCU_RCC2_DIV400		0x40000000U	/**< Divide PLL as 400 MHz vs.
						 *   200 MHz		      */
#define MCU_RCC2_SYSDIV2_M	0x1F800000U	/**< System Clock Divisor 2   */
#define MCU_RCC2_SYSDIV2_2	0x00800000U	/**< System clock /2	      */
#define MCU_RCC2_SYSDIV2_3	0x01000000U	/**< System clock /3	      */
#define MCU_RCC2_SYSDIV2_4	0x01800000U	/**< System clock /4	      */
#define MCU_RCC2_SYSDIV2_5	0x02000000U	/**< System clock /5	      */
#define MCU_RCC2_SYSDIV2_6	0x02800000U	/**< System clock /6	      */
#define MCU_RCC2_SYSDIV2_7	0x03000000U	/**< System clock /7	      */
#define MCU_RCC2_SYSDIV2_8	0x03800000U	/**< System clock /8	      */
#define MCU_RCC2_SYSDIV2_9	0x04000000U	/**< System clock /9	      */
#define MCU_RCC2_SYSDIV2_10	0x04800000U	/**< System clock /10	      */
#define MCU_RCC2_SYSDIV2_11	0x05000000U	/**< System clock /11	      */
#define MCU_RCC2_SYSDIV2_12	0x05800000U	/**< System clock /12	      */
#define MCU_RCC2_SYSDIV2_13	0x06000000U	/**< System clock /13	      */
#define MCU_RCC2_SYSDIV2_14	0x06800000U	/**< System clock /14	      */
#define MCU_RCC2_SYSDIV2_15	0x07000000U	/**< System clock /15	      */
#define MCU_RCC2_SYSDIV2_16	0x07800000U	/**< System clock /16	      */
#define MCU_RCC2_SYSDIV2_17	0x08000000U	/**< System clock /17	      */
#define MCU_RCC2_SYSDIV2_18	0x08800000U	/**< System clock /18	      */
#define MCU_RCC2_SYSDIV2_19	0x09000000U	/**< System clock /19	      */
#define MCU_RCC2_SYSDIV2_20	0x09800000U	/**< System clock /20	      */
#define MCU_RCC2_SYSDIV2_21	0x0A000000U	/**< System clock /21	      */
#define MCU_RCC2_SYSDIV2_22	0x0A800000U	/**< System clock /22	      */
#define MCU_RCC2_SYSDIV2_23	0x0B000000U	/**< System clock /23	      */
#define MCU_RCC2_SYSDIV2_24	0x0B800000U	/**< System clock /24	      */
#define MCU_RCC2_SYSDIV2_25	0x0C000000U	/**< System clock /25	      */
#define MCU_RCC2_SYSDIV2_26	0x0C800000U	/**< System clock /26	      */
#define MCU_RCC2_SYSDIV2_27	0x0D000000U	/**< System clock /27	      */
#define MCU_RCC2_SYSDIV2_28	0x0D800000U	/**< System clock /28	      */
#define MCU_RCC2_SYSDIV2_29	0x0E000000U	/**< System clock /29	      */
#define MCU_RCC2_SYSDIV2_30	0x0E800000U	/**< System clock /30	      */
#define MCU_RCC2_SYSDIV2_31	0x0F000000U	/**< System clock /31	      */
#define MCU_RCC2_SYSDIV2_32	0x0F800000U	/**< System clock /32	      */
#define MCU_RCC2_SYSDIV2_33	0x10000000U	/**< System clock /33	      */
#define MCU_RCC2_SYSDIV2_34	0x10800000U	/**< System clock /34	      */
#define MCU_RCC2_SYSDIV2_35	0x11000000U	/**< System clock /35	      */
#define MCU_RCC2_SYSDIV2_36	0x11800000U	/**< System clock /36	      */
#define MCU_RCC2_SYSDIV2_37	0x12000000U	/**< System clock /37	      */
#define MCU_RCC2_SYSDIV2_38	0x12800000U	/**< System clock /38	      */
#define MCU_RCC2_SYSDIV2_39	0x13000000U	/**< System clock /39	      */
#define MCU_RCC2_SYSDIV2_40	0x13800000U	/**< System clock /40	      */
#define MCU_RCC2_SYSDIV2_41	0x14000000U	/**< System clock /41	      */
#define MCU_RCC2_SYSDIV2_42	0x14800000U	/**< System clock /42	      */
#define MCU_RCC2_SYSDIV2_43	0x15000000U	/**< System clock /43	      */
#define MCU_RCC2_SYSDIV2_44	0x15800000U	/**< System clock /44	      */
#define MCU_RCC2_SYSDIV2_45	0x16000000U	/**< System clock /45	      */
#define MCU_RCC2_SYSDIV2_46	0x16800000U	/**< System clock /46	      */
#define MCU_RCC2_SYSDIV2_47	0x17000000U	/**< System clock /47	      */
#define MCU_RCC2_SYSDIV2_48	0x17800000U	/**< System clock /48	      */
#define MCU_RCC2_SYSDIV2_49	0x18000000U	/**< System clock /49	      */
#define MCU_RCC2_SYSDIV2_50	0x18800000U	/**< System clock /50	      */
#define MCU_RCC2_SYSDIV2_51	0x19000000U	/**< System clock /51	      */
#define MCU_RCC2_SYSDIV2_52	0x19800000U	/**< System clock /52	      */
#define MCU_RCC2_SYSDIV2_53	0x1A000000U	/**< System clock /53	      */
#define MCU_RCC2_SYSDIV2_54	0x1A800000U	/**< System clock /54	      */
#define MCU_RCC2_SYSDIV2_55	0x1B000000U	/**< System clock /55	      */
#define MCU_RCC2_SYSDIV2_56	0x1B800000U	/**< System clock /56	      */
#define MCU_RCC2_SYSDIV2_57	0x1C000000U	/**< System clock /57	      */
#define MCU_RCC2_SYSDIV2_58	0x1C800000U	/**< System clock /58	      */
#define MCU_RCC2_SYSDIV2_59	0x1D000000U	/**< System clock /59	      */
#define MCU_RCC2_SYSDIV2_60	0x1D800000U	/**< System clock /60	      */
#define MCU_RCC2_SYSDIV2_61	0x1E000000U	/**< System clock /61	      */
#define MCU_RCC2_SYSDIV2_62	0x1E800000U	/**< System clock /62	      */
#define MCU_RCC2_SYSDIV2_63	0x1F000000U	/**< System clock /63	      */
#define MCU_RCC2_SYSDIV2_64	0x1F800000U	/**< System clock /64	      */
#define MCU_RCC2_SYSDIV2LSB	0x00400000U	/**< Additional LSB for
						 *   SYSDIV2		      */
#define MCU_RCC2_USBPWRDN	0x00004000U	/**< Power-Down USB PLL	      */
#define MCU_RCC2_PWRDN2		0x00002000U	/**< Power-Down PLL 2	      */
#define MCU_RCC2_BYPASS2	0x00000800U	/**< PLL Bypass 2	      */
#define MCU_RCC2_OSCSRC2_M	0x00000070U	/**< Oscillator Source 2      */
#define MCU_RCC2_OSCSRC2_MO	0x00000000U	/**< MOSC		      */
#define MCU_RCC2_OSCSRC2_IO	0x00000010U	/**< PIOSC		      */
#define MCU_RCC2_OSCSRC2_IO4	0x00000020U	/**< PIOSC/4		      */
#define MCU_RCC2_OSCSRC2_30	0x00000030U	/**< 30 kHz		      */
#define MCU_RCC2_OSCSRC2_32	0x00000070U	/**< 32.768 kHz		      */
#define MCU_RCC2_SYSDIV2_S	23

/** @brief	16MHz
 *
 *  Precision Internal Oscillator - No PLL - No System Clock Divisor.
 */
#define	MCU_CLOCK_MODE_PRIOSC_NO_PLL	0x00
/** @brief	Clock Mode Normal
 *
 *  <b>16MHz:</b> Precision Internal Oscillator - No PLL - No System Clock
 *  Divisor.
 */
#define	MCU_CLOCK_MODE_NORMAL		MCU_CLOCK_MODE_PRIOSC_NO_PLL

/** @brief	Clock Modes Number
 *
 *  Number of supported clock modes.
 */
#define	MCU_CLOCK_MODES_NUMBER		MCU_CLOCK_MODE_PRIOSC_NO_PLL + 1

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

  /** @brief Run-Mode Clock Configuration
   *
   *  <pre>
   *  Bit/Field	Description
   *  31:28		Undefined
   *  27		Auto Clock Gating
   *  26:23		System Clock Divisor
   *  22		Enable System Clock Divisor
   *  21:14		Undefined
   *  13		PLL Power Down
   *  12		Undeifned
   *  11		PLL Bypass
   *  10:6		Crystal Value
   *  5:4		Oscillator Source
   *  3:2		Undefined
   *  1			Precision Internal Oscillator Disable
   *  0			Main Oscillator Disable
   *  </pre>
   */
  uint32 McuRunModeClockConfiguration;

  /** @brief	Run-Mode Clock Configuration 2
   *
   *  <pre>
   *  Bit/Field	Description
   *  31		Overrides Run-Mode Clock Configuration
   *  30		Divide PLL as 400 MHz vs. 200 MHz
   *  29		Undefined
   *  28:23		System Clock Divisor
   *  22		Additional LSB for System Clock Divisor
   *  21:14		Undefined
   *  13		PLL Power Down
   *  12		Undeifned
   *  11		PLL Bypass
   *  10:7		Undefined
   *  6:4		Oscillator Source
   *  3:0		Undefined
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
