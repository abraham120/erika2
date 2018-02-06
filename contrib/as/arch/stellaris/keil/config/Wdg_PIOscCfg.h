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

/** @file	Wdg_PIOscCfg.h
 *  @brief	fake-druid PIOsc AUTOSAR WDG Driver Configuration Header File.
 *
 *  Configuration of the Wdg (Watchdog) module.
 *
 *  Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 *  The Watchdog Timer module generates the first time-out signal when the
 *  32-bit counter reaches the zero state after being enabled; enabling the
 *  counter also enables the watchdog timer interrupt.
 *
 *  The watchdog interrupt can be programmed to be a standard watchdog interrupt
 *  or a non-maskable interrupt (NMI) using <tt>WDG_PIOSC_CTL_STD_INT</tt> or
 *  <tt>WDG_PIOSC_CTL_NMI_INT</tt> or-macros in the <tt>WdgCtl</tt> field of
 *  Mode Settings structure.
 *
 *  After the first time-out event, the 32-bit counter is re-loaded with the
 *  last value triggered by <tt>Wdg_PIOsc_SetTriggerCondition()</tt>, and the
 *  timer resumes counting down from that value.
 *
 *  If the timer counts down to its zero state again before
 *  <tt>Wdg_PIOsc_SetTriggerCondition()</tt> is called, and the reset signal has
 *  been enabled by setting the <tt>WDG_PIOSC_CTL_RST_EN</tt> or-macro in the
 *  <tt>WdgCtl</tt> field of Mode Settings structure, the Watchdog timer asserts
 *  its reset signal to the system.
 *
 *  If <tt>Wdg_PIOsc_SetTriggerCondition()</tt> is called before the 32-bit
 *  counter reaches its second time-out, the 32-bit counter is loaded with the
 *  value triggered by <tt>Wdg_PIOsc_SetTriggerCondition()</tt>, and counting
 *  resumes from that value.
 *
 *  If <tt>Wdg_PIOsc_SetTriggerCondition()</tt> is called while the Watchdog
 *  Timer counter is counting, then the counter is loaded with the new value and
 *  continues counting.
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */


#if !(\
 ((WDG_PIOSC_SW_MAJOR_VERSION == 1) && \
  (WDG_PIOSC_SW_MINOR_VERSION == 0) && \
  (WDG_PIOSC_SW_PATCH_VERSION == 0))\
)
#error WdgPIOsc: Configuration file expected BSW module version to be 1.0.0.*
#endif

#ifndef	WDG_PIOSC_CFG_H
#define	WDG_PIOSC_CFG_H

/*
 * Wdg
 *
 * WDG073_Conf:	Configuration of the Wdg (Watchdog driver) module.
 */


/*
 * WdgDemEventParameterRefs
 *
 * WDG148_Conf:	Container for the references to DemEventParameter elements which
 * 		shall be invoked using the API Dem_ReportErrorStatus in case the
 * 		corresponding error occurs. The EventId is taken from the
 * 		referenced DemEventParameter's DemEventId value. The
 * 		standardized errors are provided in the container and can be
 * 		extended by vendor-specific error references.
 */

/*
 * WDG_E_DISABLE_REJECTED
 *
 * WDG150_Conf:	Reference to the DemEventParameter which shall be issued when
 * 		the error "Initialization or mode switch failed because it
 * 		would disable the watchdog" has occurred.
 */

/*
 * WDG_E_MODE_FAILED
 *
 * WDG149_Conf:	Reference to the DemEventParameter which shall be issued when
 * 		the error "Setting a watchdog mode failed (during initialization
 *  		or mode switch)" has occurred.
 */

/*
 * WdgGeneral
 *
 * WDG114_Conf:	All general parameters of the watchdog driver are collected
 * 		here.
 */

/** @brief	<tt>WdgDevErrorDetect</tt>
 *
 *  <b>WDG115_Conf</b>:	Compile switch to enable / disable development error
 *  			detection for this module.
 *  			- True:		Development error detection enabled
 *  			- False:	Development error detection disabled
 */
#ifdef	__AS_CFG_WDG_PIOSC_DEV_ERROR_DETECT__
#define	WDG_PIOSC_DEV_ERROR_DETECT	STD_ON
#else
#define	WDG_PIOSC_DEV_ERROR_DETECT	STD_OFF
#endif

/** @brief	<tt>WdgDisableAllowed</tt>
 *
 *  <b>WDG116_Conf</b>:	Compile switch to allow / forbid disabling the watchdog
 *  			driver during runtime.
 *  			- True:		Disabling the watchdog driver at runtime
 *  					is allowed.
 *  			- False:	Disabling the watchdog driver at runtime
 *  					is not allowed.
 */
#ifdef	__AS_CFG_WDG_PIOSC_DISABLE_ALLOWED__
#define	WDG_PIOSC_DISABLE_ALLOWED	STD_ON
#else
#define	WDG_PIOSC_DISABLE_ALLOWED	STD_OFF
#endif

/** @brief	<tt>WdgIndex</tt>
 *
 *  <b>WDG117_Conf</b>:	Represents the watchdog driver's ID so that it can be
 *  			referenced by the watchdog interface.
 */
#define	WDG_PIOSC_INDEX			0x01U

/** @brief	PIOsc Clock Frequency (Hz) */
#define	WDG_PIOSC_CLK_FREQ		16000000

/** @brief	<tt>WdgInitialTimeout</tt>
 *
 *  <b>WDG130_Conf</b>:	The initial timeout (sec) for the trigger condition to
 *  			be initialized during Init function. It shall be not
 *  			larger than <tt>WdgMaxTimeout</tt>.
 */
#define	WDG_PIOSC_INITIAL_TIMEOUT	10.0

/** @brief	<tt>WdgMaxTimeout</tt>
 *
 *  <b>WDG131_Conf</b>:	The maximum timeout (sec) to which the watchdog
 *  			trigger condition can be initialized.
 *
 *  @note	<tt>WdgMaxTimeout</tt> =
 *  		Watchdog Counter Max Value / PIOsc Frequency (Hz)
 */
#define	WDG_PIOSC_MAX_TIMEOUT		268.4354559375

/** @brief	Watchdog driver to be executed out of RAM area. */
#define	WDG_PIOSC_RUN_AREA_RAM		STD_OFF

/** @brief	Watchdog driver to be executed out of ROM area. */
#define	WDG_PIOSC_RUN_AREA_ROM		STD_ON

/** @brief	<tt>WdgRunArea</tt>
 *
 *  <b>WDG147_Conf</b>:	Represents the watchdog driver execution area is either
 *  			from ROM(Flash) or RAM as required with the particular
 *  			microcontroller.
 */
#define	WDG_PIOSC_RUN_AREA		WDG_RUN_AREA_RAM

/** @brief	<tt>WdgTriggerLocation</tt>
 *
 *  <b>WDG118_Conf</b>:	Location (memory address) of the watchdog trigger
 *  			routine.
 *
 *  dependency: Only relevant if provided by hardware and needed by the system.
 */
#define	WDG_PIOSC_TRIGGER_LOCATION	0x00000000U

/** @brief	<tt>WdgVersionInfoApi</tt>
 *
 *  <b>WDG119_Conf</b>:	Compile switch to enable / disable the version
 *  			information API.
 *  			- True:		API enabled
 *  			- False:	API disabled
 */
#ifdef	__AS_CFG_WDG_PIOSC_VERSION_INFO_API__
#define	WDG_PIOSC_VERSION_INFO_API	STD_ON
#else
#define	WDG_PIOSC_VERSION_INFO_API	STD_OFF
#endif

/** @brief	Watchdog Standard Interrupt.*/
#define	WDG_PIOSC_CTL_STD_INT	0x00000000U
/** @brief	Watchdog Non-Maskable Interrupt.*/
#define	WDG_PIOSC_CTL_NMI_INT	0x00000004U
/** @brief	Watchdog Reset Enable.*/
#define	WDG_PIOSC_CTL_RST_EN	0x00000002U
/** @brief	Watchdog Debug Stall.*/
#define	WDG_PIOSC_CTL_DBG_STALL	0x00000100U

#ifdef	__AS_CFG_WDG_PIOSC_FAST_MODE_NOTIFICATION__
/** @brief	Watchdog Mode Fast Notification Callback
 *
 *  The notification prototype <tt>Wdg_PIOsc_Notification_Fast()</tt> is for
 *  the notification callback function for watchdog mode "fast" and shall be
 *  implemented by the user.
 *
 *  The notifications callback <tt>Wdg_PIOsc_Notification_Fast()</tt> shall be
 *  configurable as pointers to user defined functions within the configuration
 *  structure.
 *
 *  Each watchdog mode shall provide its own notifications callback if
 *  configured.
 *
 *  When disabled, the PIOSC WDG Driver will send no notifications.
 *
 *  The PIOSC WDG Driver shall invoke a notification callback whenever the
 *  defined target time of the watchdog is reached.
 *
 *  For all available watchdog modes, callback functions have to be declared by
 *  the configuration tool.
 */
void Wdg_PIOsc_Notification_Fast(
  void
);
#endif	/* __AS_CFG_WDG_PIOSC_FAST_MODE_NOTIFICATION__ */

/** @brief	WDG Fast Settings Type.
 *
 *  <b>WDG121_Conf</b>:	<tt>WdgSettingsFast</tt>
 *
 *  Hardware dependent settings for the watchdog driver's "fast" mode.
 */
typedef	struct {

  /** @brief	Watchdog Control
   *
   *  This field is the watchdog control.
   */
  uint32	WdgCtl;

  /** @brief	<tt>WdgTimeout</tt>
   *
   *  The initial timeout (msec) for the trigger condition to be initialized
   *  in "fast" mode. It shall be not larger than <tt>WdgMaxTimeout</tt>.
   */
  uint16	WdgTimeout;

  /** @brief	Notification Callback Function Pointer
   *
   *  Function pointer to callback function.
   *
   *  The notification prototype <tt>Wdg_PIOsc_Notification_<mode>()</tt> is for
   *  the notifications callback function and shall be implemented by the user.
   *
   *  The PIOSC WDG module's environment shall declare a separate notifications
   *  callback for each watchdog mode to avoid parameters in notification
   *  services and to improve run time efficiency.
   *
   *  The notifications callback <tt>Wdg_Notification_<mode>()</tt> shall be
   *  configurable as pointers to user defined functions within the
   *  configuration structure.
   *
   *  Each watchdog mode shall provide its own notifications callback if
   *  configured.
   *
   *  The PIOSC WDG Driver shall invoke a notification callback whenever the
   *  defined target time of the watchdog is reached.
   *
   *  For all available watchdog modes, callback functions have to be declared
   *  by the configuration tool.
   */
  Wdg_PIOsc_Notification	WdgNotificationPtr;

}	Wdg_PIOsc_SettingsFastType;

#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_ON )
/** @brief	WDG Off Settings Type.
 *
 *  <b>WDG122_Conf</b>:	<tt>WdgSettingsOff</tt>
 *
 *  Hardware dependent settings for the watchdog driver's "off" mode.
 */
typedef	struct {

  /** @brief	Watchdog Dummy
   *
   *  This field is a Dummy field.
   */
  uint32	WdgDummy;

}	Wdg_PIOsc_SettingsOffType;
#endif	/* ( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */

#ifdef	__AS_CFG_WDG_PIOSC_SLOW_MODE_NOTIFICATION__
/** @brief	Watchdog Mode Slow Notification Callback
 *
 *  The notification prototype <tt>Wdg_PIOsc_Notification_Slow()</tt> is for
 *  the notification callback function for watchdog mode "slow" and shall be
 *  implemented by the user.
 *
 *  The notifications callback <tt>Wdg_PIOsc_Notification_Slow()</tt> shall be
 *  configurable as pointers to user defined functions within the configuration
 *  structure.
 *
 *  Each watchdog mode shall provide its own notifications callback if
 *  configured.
 *
 *  When disabled, the PIOSC WDG Driver will send no notifications.
 *
 *  The PIOSC WDG Driver shall invoke a notification callback whenever the
 *  defined target time of the watchdog is reached.
 *
 *  For all available watchdog modes, callback functions have to be declared by
 *  the configuration tool.
 */
void Wdg_PIOsc_Notification_Slow(
  void
);
#endif	/* __AS_CFG_WDG_PIOSC_SLOW_MODE_NOTIFICATION__ */

/** @brief	WDG Slow Settings Type.
 *
 *  <b>WDG123_Conf</b>:	<tt>WdgSettingsSlow</tt>
 *
 *  Hardware dependent settings for the watchdog driver's "slow" mode..
 */
typedef	struct {

  /** @brief	Watchdog Control
   *
   *  This field is the watchdog control.
   */
  uint32	WdgCtl;

  /** @brief	<tt>WdgTimeout</tt>
   *
   *  The initial timeout (msec) for the trigger condition to be initialized
   *  in "slow" mode. It shall be not larger than <tt>WdgMaxTimeout</tt>.
   */
  uint16	WdgTimeout;

  /** @brief	Notification Callback Function Pointer
   *
   *  Function pointer to callback function.
   *
   *  The notification prototype <tt>Wdg_PIOsc_Notification_<mode>()</tt> is for
   *  the notifications callback function and shall be implemented by the user.
   *
   *  The PIOSC WDG module's environment shall declare a separate notifications
   *  callback for each watchdog mode to avoid parameters in notification
   *  services and to improve run time efficiency.
   *
   *  The notifications callback <tt>Wdg_Notification_<mode>()</tt> shall be
   *  configurable as pointers to user defined functions within the
   *  configuration structure.
   *
   *  Each watchdog mode shall provide its own notifications callback if
   *  configured.
   *
   *  The PIOSC WDG Driver shall invoke a notification callback whenever the
   *  defined target time of the watchdog is reached.
   *
   *  For all available watchdog modes, callback functions have to be declared
   *  by the configuration tool.
   */
  Wdg_PIOsc_Notification	WdgNotificationPtr;

}	Wdg_PIOsc_SettingsSlowType;

#if	0
/** @brief	WDG External Configuration Type.
 *
 *  <b>WDG112_Conf</b>:	<tt>WdgExternalConfiguration</tt>
 *
 *  Configuration items for an external watchdog hardware.
 */
typedef struct {

  /** @brief	WDG External Container Reference.
   *
   *  <b>WDG113_Conf</b>:	<tt>WdgExternalContainerRef</tt>
   *
   *  Reference to either - a DioChannelGroup container in case the hardware
   *  watchdog is connected via DIO pins - an SpiSequenceConfiguration container
   *  in case the watchdog hardware is accessed via SPI.
   */
  void					WdgExternalContainerRef;

}	Wdg_PIOsc_ExternalConfigType;
#endif

/** @brief	WDG Configuration Settings.
 *
 *  <b>WDG082_Conf</b>:		<tt>WdgSettingsConfig</tt>
 *
 *  Configuration items for the different watchdog settings, including those for
 *  external watchdog hardware.
 *
 *  @note	All postbuild parameters are handled via this container.
 */
typedef struct {

  /** @brief	WDG Default Mode.
   *
   *  <b>WDG120_Conf</b>:	<tt>WdgDefaultMode</tt>
   *
   *  Default mode for watchdog driver initialization.
   *
   *  @note	"Off" mode only possible if disabling the watchdog driver is
   *  		allowed.
   */
  WdgIf_ModeType			WdgDefaultMode;

#if	0
  /** @brief	WDG External Configuration.
   *
   *  Configuration items for an external watchdog hardware.
   */
  const Wdg_PIOsc_ExternalConfigType *	WdgExternalConfiguration;
#endif

  /*
   * Note:
   *
   * The three modes are provided as containers for the reason that they might
   * be referred by other modules and hence no parameters are needed. However
   * those containers might be extended by the vendor (resp. hardware) specific
   * configuration parameters, but these could not be standardized.
   */

  /** @brief	WDG Fast Mode Settings Type.
   *
   *  Hardware dependent settings for the watchdog driver's "fast" mode.
   */
  const Wdg_PIOsc_SettingsFastType *	WdgSettingsFast;

#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_ON )
  /** @brief	WDG Off Mode Settings Type.
   *
   *  Hardware dependent settings for the watchdog driver's "off" mode.
   */
  const Wdg_PIOsc_SettingsOffType *	WdgSettingsOff;
#endif	/* ( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */

  /** @brief	WDG Slow Mode Settings Type.
   *
   *  Hardware dependent settings for the watchdog driver's "slow" mode.
   */
  const Wdg_PIOsc_SettingsSlowType *	WdgSettingsSlow;

}	Wdg_PIOsc_SettingsConfigType;

/** @brief	PIOSC WDG Module Configuration Parameters
 *
 *  <b>WDG171</b>:	Structure to hold the watchdog driver configuration set.
 *  			Used for pointers to structures holding configuration
 *  			data provided to the Wdg module initialization routine
 *  			for configuration of the module and watchdog hardware.
 *  			(<tt>BSW00414</tt>)
 */
typedef	Wdg_PIOsc_SettingsConfigType	Wdg_PIOsc_ConfigType;

#if	0
/*
 * WdgPublishedInformation
 *
 * WDG074_Conf:	Container holding all Wdg specific published information
 * 		parameters.
 *
 * WDG156:	The standardized common published parameters as required by
 * 		BSW00402 in the SRS General on Basic Software Modules shall be
 * 		published within the header file of this module and need to be
 * 		provided in the BSW Module Description.
 * 		(BSW00374, BSW00379, BSW003, BSW00318)
 */
#define	WDG_PIOSC_TOGGLE	0x00000000U
#define	WDG_PIOSC_WINDOW	0x00000001U
#define	WDG_PIOSC_BOTH		0x00000002U

/*
 * WdgTriggerMode
 *
 * WDG127_Conf:	Watchdog trigger mode
 *
 * Note:	WdgTriggerMode is only published for information purposes;
 * 		this parameter is not used to configure the Watchdog Driver or
 * 		the modules using the Watchdog Driver.
 */
#define	WDG_PIOSC_TRIGGER_MODE	WDG_PIOSC_WINDOW;
#endif	/* 0 */

/** @brief	Test Configuration
 *
 *  Identifier for Test PIOSC WDG Driver Configuration.
 */
#define	WDG_PIOSC_CONFIG_TEST		0x00000000U

/** @brief	Test Configuration Pointer
 *
 *  Pointer of Test WDG Driver Configuration.
 */
#define	WDG_PIOSC_CONFIG_TEST_PTR	&Wdg_PIOsc_Config[WDG_PIOSC_CONFIG_TEST]

/** @brief	Default Configuration
 *
 *  Identifier for Default PIOSC WDG Driver Configuration.
 */
#define	WDG_PIOSC_CONFIG_DEFAULT	WDG_PIOSC_CONFIG_TEST

/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default PIOSC WDG Driver Configuration.
 */
#define	WDG_PIOSC_CONFIG_DEFAULT_PTR	\
	&Wdg_PIOsc_Config[WDG_PIOSC_CONFIG_DEFAULT]

#endif	/* WDG_PIOSC_CFG_H */
