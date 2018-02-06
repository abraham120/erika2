/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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

/** @file	Wdg_PCLK.h
 *  @brief	Peripheral Clock AUTOSAR WDG (Watchdog) Driver Header File.
 *
 *  This module provides services for initialization, changing the operation
 *  mode and setting the trigger condition (timeout) of a Watchdog Timer.
 *
 *  The functional requirements and the functional scope are the same for both
 *  internal and external watchdog drivers. Hence the API is semantically
 *  identical.
 *
 *  An internal watchdog driver belongs to the Microcontroller Abstraction Layer
 *  (MCAL), whereas an external watchdog driver belongs to the Onboard Device
 *  Abstraction Layer. Therefore, an external watchdog driver needs other
 *  drivers (in MCAL) in order to access the microcontroller hardware.
 *
 *  A Wdg module for an internal (on-chip) watchdog accesses the microcontroller
 *  hardware directly and is located in the Microcontroller Abstraction layer.
 *
 *  A Wdg module for an external watchdog uses other modules (e.g. SPI) to
 *  access the external watchdog device. Such a Wdg module is located in the
 *  Onboard Device Abstraction Layer.
 *
 *  <b>WDG055</b>:	The Wdg module for an external watchdog driver shall
 *  			have source code that is independent of the
 *  			microcontroller platform.
 *
 *  If the hardware of the internal watchdog depends on the system clock,
 *  changes to the system clock (e.g. PLL on -> PLL off) may also affect the
 *  clock settings of the watchdog hardware.
 *
 *  A Wdg module for an external watchdog device depends on the API and
 *  capabilities of the used onboard communication handlers or drivers (e.g. SPI
 *  handler).
 *
 *  Internal watchdog driver:
 *
 *  <b>WDG161</b>:	To access the internal watchdog hardware, the
 *  			corresponding Wdg module instance shall access the
 *  			hardware for watchdog servicing directly.
 *
 *  Hint:	An internal watchdog driver is part of the Microcontroller
 *  		Abstraction Layer, which allows direct hardware access.
 *
 *  <b>WDG166</b>:	The routine servicing an internal watchdog shall be
 *  			implemented either as an interrupt routine driven by a
 *  			hardware timer or as a GPT driver callback.
 *  			(<tt>BSW00427</tt>, <tt>BSW164</tt>, <tt>BSW00325</tt>,
 *  			<tt>BSW00326</tt>, <tt>BSW00439</tt>, <tt>BSW12129</tt>,
 *  			<tt>BSW12019</tt>)
 *
 *  @note	In both cases, the watchdog servicing routine runs in interrupt
 *  		context.
 *
 *  @note	If the watchdog servicing routine is implemented as an interrupt
 *  		routine (i.e. as a cat1 or cat2 interrupt routine and not via
 *  		the GPT), it shall be described in the Basic Software Module
 *  		Description and the implementation shall follow the requirements
 *  		for interrupt handling. (<tt>BSW00427</tt>, <tt>BSW00325</tt>,
 *  		<tt>BSW00326</tt>, <tt>BSW00439</tt>, <tt>BSW00314</tt>,
 *  		<tt>BSW00429</tt>, <tt>BSW12129</tt>).
 *
 *  External watchdog driver:
 *
 *  <b>WDG076</b>:	To access the external watchdog hardware, the
 *  			corresponding Wdg module instance shall use the
 *  			functionality and API of the corresponding handler or
 *  			driver, e.g. the SPI handler or DIO driver.
 *  			(<tt>BSW12092</tt>)
 *
 *  <b>WDG162</b>:	The routine servicing an external watchdog shall be
 *  			implemented as a GPT driver callback.
 *  			(<tt>BSW12019</tt>)
 *
 *  Hint:	An external watchdog driver is part of the Onboard Device
 *  		Abstraction Layer, which excludes direct hardware access.
 *
 *  <b>WDG077</b>:	A Wdg module for an external watchdog shall satisfy the
 *  			same functional requirements and offer the same
 *  			functional scope as a Wdg module for an internal
 *  			watchdog. Hence their respective APIs are semantically
 *  			identical. (<tt>BSW12165</tt>)
 *
 *  <b>WDG078</b>:	The Wdg module shall add all parameters required for
 *  			accessing the external watchdog hardware, e.g. the used
 *  			SPI channel or DIO port, to the module's published
 *  			parameters and to the module's configuration parameters.
 *  			(<tt>BSW12166</tt>)
 *
 *  <b>WDG169</b>:	If more than one watchdog driver instance exists on an
 *  			ECU (namely an external and an internal one) the
 *  			implementer shall provide unique code file names by
 *  			expanding the names according to <tt>BSW00347</tt>.
 *
 *  <b>WDG086</b>:	The Wdg module shall statically check the configuration
 *  			parameters (at the latest during compile time) for
 *  			correctness. (<tt>BSW167</tt>, <tt>BSW004</tt>)
 *
 *  <b>WDG031</b>:	The Wdg module shall not implement an interface for
 *  			deinitialization/shutdown. If the watchdog supports a
 *  			de-initialization/shutdown and the environment allows
 *  			the usage of this feature, the
 *  			de-initialization/shutdown shall be achieved by calling
 *  			the <tt>Wdg_SetMode()</tt> routine with <tt>OFF</tt>
 *  			mode parameter. (<tt>BSW00336</tt>, <tt>BSW12163</tt>)
 *
 *  Rationale:	Some watchdogs do not support the de-initialization/shutdown
 *  		functionality and in some environments this feature must not be
 *  		used (e.g. in safety critical systems).
 *
 *  <b>WDG034</b>:	The start address of the watchdog trigger routine shall
 *  			be statically configurable to a fixed memory location by
 *  			the user. The user needs to take care that Configured
 *  			memory location is valid for the platform on which
 *  			driver is being implemented on. This configuration
 *  			parameter shall only be given if supported/needed by the
 *  			hardware.
 *
 *  Rationale:	This allows the watchdog device to identify the correct trigger
 *  		input if supported by the hardware.
 *
 *  <b>WDG040</b>:	If interrupts have to be disabled in order to ensure
 *  			data consistency or correct functionality of this module
 *  			(e.g. while switching the watchdog mode or during the
 *  			watchdog trigger routine), this shall be done by using
 *  			the corresponding BSW Scheduler functionality if
 *  			possible (this means definition of an exclusive area).
 *  			The internal watchdog driver (because it belongs to
 *  			MCAL) may also directly disable interrupts – see
 *  			<tt>BSW00429</tt>. (<tt>BSW00426</tt>,
 *  			<tt>BSW00429</tt>)
 *
 *  <b>WDG168</b>:	Depending on a static configuration (see
 *  			<tt>WDG147_Conf</tt>), the code of the Wdg module is
 *  			executed either from ROM or from RAM.
 *
 *  Motivation:	For certain use cases, e.g. for flash programming in bootloader
 *  		mode, the watchdog module has to be part of an executable which
 *  		runs in RAM.
 *
 *  Hint:	This is more a requirement for the build environment than for
 *  		the watchdog module itself. However, since it might also
 *  		influence the implementation of the code, it is stated here and
 *  		a corresponding configuration parameter is given.
 *
 *  @author	Gianluca Franchino
 *  @date	2013
 */

#ifndef	WDG_PCLK_H
#define	WDG_PCLK_H

/** @brief	Vendor Id
 *
 *  Vendor Id from document:
 *  [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 *  http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	WDG_PCLK_VENDOR_ID	0

/** @brief	Module Id
 *
 *  Module Id (083) from document:
 *  List of Basic Software Modules
 *  V1.5.0
 *  R4.0 Rev 2
 */
#define	WDG_PCLK_MODULE_ID	102

#define	WDG_PCLK_SW_MAJOR_VERSION	1 /**< Software Version Major Number  */
#define	WDG_PCLK_SW_MINOR_VERSION	0 /**< Software Version Minor Number  */
#define	WDG_PCLK_SW_PATCH_VERSION	0 /**< Software Version Patch Number  */

#define	WDG_PCLK_AR_MAJOR_VERSION	4 /**< AUTOSAR Version Major Number   */
#define	WDG_PCLK_AR_MINOR_VERSION	0 /**< AUTOSAR Version Minor Number   */
#define	WDG_PCLK_AR_PATCH_VERSION	2 /**< AUTOSAR Version Patch Number   */

/*
 *  WDGIF049:	The Watchdog Interface shall comprise a header file
 *  		WdgIf_Types.h providing type declarations for the watchdog
 *  		interface and common type declarations to be imported by
 *  		watchdog drivers.
 */
#include "WdgIf_Types.h"
#include "Std_Types.h"

/** @brief	Notifications Callback Function Pointer
 *
 *  The notification prototype <tt>Wdg_PCLK_Notification()</tt> is for
 *  the notifications callback function and shall be implemented by the user.
 *
 *  Each watchdog mode shall provide its own notifications callback if
 *  configured.
 *
 *  The notifications callback <tt>Wdg_PCLK_Notification()</tt> shall be
 *  configurable as pointers to user defined functions within the configuration
 *  structure.
 *
 *  When disabled, the PCLK WDG Driver will send no notifications.
 *
 *  The PCLK WDG Driver shall invoke a notification callback whenever the
 *  defined target time of the watchdog is reached.
 *
 *  For all available watchdog modes, callback functions have to be declared by
 *  the configuration tool.
 */
typedef void (*Wdg_PCLK_Notification)(void);

/*
 * Wdg_PCLK.h shall include Wdg_PCLK_Cfg.h.
 */
#include "Wdg_PCLK_Cfg.h"

/** @brief	WDG Module Configuration Parameters
 *
 *  <b>WDG171</b>:	Structure to hold the watchdog driver configuration set.
 *  			Used for pointers to structures holding configuration
 *  			data provided to the Wdg module initialization routine
 *  			for configuration of the module and watchdog hardware.
 *  			(<tt>BSW00414</tt>)
 */
extern const Wdg_PCLK_ConfigType	Wdg_PCLK_Config[];

/** @brief	PCLK WDG Driver Initialization
 *  @param	ConfigPtr	Pointer to configuration set.
 *  @return	None
 *
 *  Initializes the module.
 *
 *  <b>WDG106</b>:	Service 0x00
 *
 *  <b>WDG001</b>:	The <tt>Wdg_PCLK_Init()</tt> function shall initialize
 *  			the WdgPCLK module and the watchdog hardware, i.e. it
 *  			shall set the default watchdog mode and timeout period
 *  			as provided in the configuration set.
 *  			(<tt>BSW00400</tt>, <tt>BSW101</tt>, <tt>BSW12105</tt>)
 *
 *  @note	Via post-build configuration, the user can choose the
 *  		configuration set to be used with the <tt>Wdg_PCLK_Init()</tt>
 *  		function from a limited number of statically configured sets
 *  		(see also <tt>BSW00314</tt>).
 *
 *  <b>WDG100</b>:	The <tt>Wdg_PCLK_Init()</tt> function shall initialize
 *  			all global variables of the Wdg_PCLK module and set the
 *  			default watchdog mode and initial timeout period.
 *  			(<tt>BSW12057</tt>, <tt>BSW12125</tt>,
 *  			<tt>BSW12461</tt>, <tt>BSW12105</tt>)
 *
 *  <b>WDG101</b>:	The <tt>Wdg_PCLK_Init()</tt> function shall initialize
 *  			those controller registers that are needed for
 *  			controlling the watchdog hardware and that do not
 *  			influence/depend on other (hardware) modules.
 *
 *  Registers that can influence or depend on other modules are initialized by a
 *  common system module. (<tt>BSW12057</tt>, <tt>BSW12125</tt>,
 *  <tt>BSW12461</tt>, <tt>BSW12105</tt>)
 *
 *  <b>WDG025</b>:	If disabling the watchdog is not allowed (because
 *  			pre-compile configuration parameter
 *  			<tt>WdgDisableAllowed</tt> == <tt>OFF</tt>) and if the
 *  			default mode given in the provided configuration set
 *  			disables the watchdog, the <tt>Wdg_PCLK_Init()</tt>
 *  			function shall not execute the initialization but raise
 *  			the production error <tt>WDG_E_DISABLE_REJECTED</tt>.
 *  			(<tt>BSW00338</tt>, <tt>BSW00323</tt>,
 *  			<tt>BSW12163</tt>, <tt>BSW12106</tt>)
 *
 *  <b>WDG173</b>:	If switching the Wdg_PCLK module and the watchdog
 *  			hardware into the default mode is not possible, e.g.
 *  			because of inconsistent mode settings or because some
 *  			timing constraints have not been met, the
 *  			<tt>Wdg_PCLK_Init()</tt> function shall raise the
 *  			production error <tt>WDG_E_MODE_FAILED</tt>.
 *
 *  <b>WDG089</b>:	When development error detection is enabled for the
 *  			Wdg_PCLK module: The function
 *  			<tt>Wdg_PCLK_Init()</tt> shall check that the
 *  			parameter <tt>ConfigPtr</tt> is not <tt>NULL</tt>
 *  			(except for the Pre-Compiled variant). If this error is
 *  			detected, the function <tt>Wdg_PCLK_Init()</tt> shall
 *  			not execute the initialization but raise the development
 *  			error <tt>WDG_E_PARAM_POINTER</tt>. (<tt>BSW00338</tt>,
 *  			<tt>BSW00323</tt>, <tt>BSW12448</tt>)
 *
 *  <b>WDG090</b>:	When development error detection is enabled for the
 *  			Wdg_PCLK module: The <tt>Wdg_PCLK_Init()</tt>
 *  			function shall check that the (hardware specific)
 *  			contents of the given configuration set is within the
 *  			allowed boundaries. If this error is detected, the
 *  			function <tt>Wdg_PCLK_Init()</tt> shall not execute
 *  			the initialization but raise the development error
 *  			<tt>WDG_E_PARAM_CONFIG</tt>. (<tt>BSW00338</tt>,
 *  			<tt>BSW00323</tt>, <tt>BSW12448</tt>)
 *
 *  <b>WDG019</b>:	When development error detection is enabled for the 
 *  			Wdg_PCLK module: The <tt>Wdg_PCLK_Init()</tt>
 *  			function shall set the Wdg_PCLK module's internal state
 *  			from <tt>WDG_UNINIT</tt> (the default state indicating a
 *  			non-initialized module) to <tt>WDG_IDLE</tt> if the
 *  			initialization was successful. (<tt>BSW00406</tt>,
 *  			<tt>BSW00335</tt>)
 *
 *  @note	This specification prescribes the symbols <tt>WDG_IDLE</tt> and
 *  		<tt>WDG_UNINIT</tt> only, if they are externally visible, e.g.
 *  		for debugging (see <tt>BSW00335</tt>). Choosing the data type
 *  		for the status variable is up to the implementation.
 */
void Wdg_PCLK_Init(const Wdg_PCLK_ConfigType * ConfigPtr);

/** @brief	Watchdog Mode Switching.
 *  @param	Mode	One of the following statically configured modes:
 *  			- <tt>WDGIF_OFF_MODE</tt>
 *  			- <tt>WDGIF_SLOW_MODE</tt>
 *  			- <tt>WDGIF_FAST_MODE</tt>
 *  @return	
 *  	- <tt>E_OK</tt>:	Mode switching command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Mode switching command has not been accepted
 *
 *  Switches the watchdog into the mode <tt>Mode</tt>.
 *
 *  <b>WDG107</b>:	Service 0x01
 *
 *  <b>WDG160</b>:	The function <tt>Wdg_PCLK_SetMode()</tt> shall switch
 *  			the watchdog driver from the current watchdog mode into
 *  			the mode given by the argument <tt>Mode</tt>.
 *  			This means: By choosing one of a limited number of
 *  			statically configured settings (e.g. toggle or window
 *  			watchdog, different timeout periods) the Wdg_PCLK
 *  			module and the watchdog hardware are switched to one of
 *  			the following three different modes:
 *  			- <tt>WDGIF_OFF_MODE</tt>
 *  			- <tt>WDGIF_SLOW_MODE</tt>
 *  			- <tt>WDGIF_FAST_MODE</tt>
 *  			(<tt>BSW12015</tt>, <tt>BSW12018</tt>)
 *
 *  <b>WDG051</b>:	The configuration set provided to the Wdg_PCLK module's
 *  			initialization routine shall contain the hardware /
 *  			driver specific parameters to be used in the different
 *  			watchdog modes. (<tt>BSW12015</tt>)
 *
 *  Hint:	This may, for example, include mode-dependent settings for the
 *  		GPT timer, if GPT callbacks are used.
 *
 *  <b>WDG145</b>:	The <tt>Wdg_PCLK_SetMode()</tt> function shall reset
 *  			the watchdog timeout counter based on the new watchdog
 *  			mode i.e. the timeout frame remaining shall be
 *  			recalculated based on a changed trigger period.
 *
 *  <b>WDG103</b>:	The <tt>Wdg_PCLK_SetMode()</tt> function shall return
 *  			<tt>E_OK</tt> if the mode switch has been executed
 *  			completely and successfully, i.e. all parameters of the
 *  			Wdg_PCLK module and the watchdog hardware have been set
 *  			to the new values.
 *
 *  <b>WDG016</b>:	If switching the Wdg_PCLK module and the watchdog
 *  			hardware into the requested mode is not possible, e.g.
 *  			because of inconsistent mode settings or because some
 *  			timing constraints have not been met, the
 *  			<tt>Wdg_PCLK_SetMode()</tt> function shall return the
 *  			value <tt>E_NOT_OK</tt> and raise the production error
 *  			<tt>WDG_E_MODE_FAILED</tt>. (<tt>BSW12064</tt>)
 *
 *  <b>WDG026</b>	If disabling the watchdog is not allowed (e.g. in safety
 *  			relevant systems, see <tt>WDG115_Conf</tt>) the
 *  			<tt>Wdg_PCLK_SetMode()</tt> function shall check
 *  			whether the settings for the requested mode would
 *  			disable the watchdog. In this case, the function shall
 *  			not execute the mode switch but raise the production
 *  			error <tt>WDG_E_DISABLE_REJECTED</tt> and return with
 *  			the value <tt>E_NOT_OK</tt>. (<tt>BSW00338</tt>,
 *  			<tt>BSW00323</tt>, <tt>BSW12163</tt>, <tt>BSW12106</tt>)
 *
 *  <b>WDG091</b>:	When development error detection is enabled for the
 *  			Wdg_PCLK module: The <tt>Wdg_PCLK_SetMode()</tt>
 *  			function shall check that the parameter <tt>Mode</tt> is
 *  			within the allowed range. If this is not the case, the
 *  			function shall not execute the mode switch but raise
 *  			development error <tt>WDG_E_PARAM_MODE</tt> and return
 *  			with the value <tt>E_NOT_OK</tt>. (<tt>BSW00338</tt>,
 *  			<tt>BSW00323</tt>, <tt>BSW12448</tt>)
 *
 *  <b>WDG092</b>:	When development error detection is enabled for the
 *  			Wdg_PCLK module: The <tt>Wdg_PCLK_SetMode()</tt>
 *  			function shall check that the (hardware specific)
 *  			settings for the requested mode are within the allowed
 *  			boundaries. If this is not the case, the function shall
 *  			not execute the mode switch but raise the development
 *  			error <tt>WDG_E_PARAM_MODE</tt> and return with the
 *  			value <tt>E_NOT_OK</tt>. (<tt>BSW00338</tt>,
 *  			<tt>BSW00323</tt>, <tt>BSW12448</tt>)
 *
 *  <b>WDG017</b>:	When development error detection is enabled for the
 *  			Wdg_PCLK module: The <tt>Wdg_PCLK_SetMode()</tt>
 *  			function shall check that the Wdg_PCLK module's state
 *  			is <tt>WDG_IDLE</tt> (meaning the Wdg_PCLK module and
 *  			the watchdog hardware are initialized and the watchdog
 *  			is currently not being triggered or switched). If this
 *  			is not the case, the function shall not execute the mode
 *  			switch but raise the development error
 *  			<tt>WDG_E_DRIVER_STATE</tt> and return with the value
 *  			<tt>E_NOT_OK</tt>. (<tt>BSW00338</tt>,
 *  			<tt>BSW00335</tt>, <tt>BSW12064</tt>, <tt>BSW12448</tt>)
 *
 *  <b>WDG018</b>:	When development error detection is enabled for the
 *  			Wdg_PCLK module: The <tt>Wdg_PCLK_SetMode()</tt>
 *  			function shall set the Wdg_PCLK module's state to
 *  			<tt>WDG_BUSY</tt> during its execution (indicating, that
 *  			the module is busy) and shall reset the Wdg_PCLK
 *  			module's state to <tt>WDG_IDLE</tt> as last operation
 *  			before it returns to the caller. (<tt>BSW00338</tt>,
 *  			<tt>BSW00335</tt>)
 *
 *  @note	This specification prescribes the symbols <tt>WDG_IDLE</tt> and
 *  		<tt>WDG_BUSY</tt> only, if they are externally visible, e.g. for
 *  		debugging (see <tt>BSW00335</tt>). Choosing the data type for
 *  		the status variable is up to the implementation.
 */
Std_ReturnType Wdg_PCLK_SetMode(WdgIf_ModeType	Mode);

/** @brief	Trigger Condition Setup.
 *  @param	Timeout	Timeout value (milliseconds) for setting the trigger
 *  		counter.
 *
 *  Sets the timeout value for the trigger counter.
 *
 *  <b>WDG155</b>:	Service 0x03
 *
 *  <b>WDG136</b>:	The function <tt>Wdg_PCLK_SetTriggerCondition()</tt>
 *  			shall reset the watchdog timeout counter according to
 *  			the <tt>Timeout</tt> value passed.
 *
 *  <b>WDG138</b>:	The <tt>Timeout</tt> value passed shall be interpreted
 *  			as 'milliseconds'. The conversion from milliseconds to
 *  			the corresponding counter value shall be done internally
 *  			by the Wdg_PCLK module.
 *
 *  <b>WDG139</b>:	The current watchdog mode shall be taken into account
 *  			when calculating the counter value from the
 *  			<tt>Timeout</tt> parameter.
 *
 *  <b>WDG140</b>:	This function shall also allow to set "<tt>0</tt>" as
 *  			the time frame for triggering which will result in an
 *  			(almost) immediate stop of the watchdog triggering and
 *  			an (almost) instantaneous watchdog reset of the ECU.
 *
 *  <b>WDG146</b>:	When development error detection is enabled for the
 *  			module: The function
 *  			<tt>Wdg_PCLK_SetTriggerCondition()</tt> shall check
 *  			that the <tt>Timeout</tt> parameter given is less or
 *  			equal to the maximum timeout value
 *  			(<tt>WdgMaxTimeout</tt>). If this is not the case the
 *  			function shall not reload the timeout counter but raise
 *  			the development error <tt>WDG_E_PARAM_TIMEOUT</tt> and
 *  			return to the caller.
 */
void Wdg_PCLK_SetTriggerCondition(uint16	Timeout);

#if	( WDG_PCLK_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval.
 *  @param	_vi	Pointer to where to store the version
 *  			information of this module.
 *
 *  This service returns the version information of this module.
 *
 *  <b>WDG109</b>:	Service 0x04
 *
 *  <b>WDG067</b>:	The <tt>Wdg_PCLK_GetVersionInfo()</tt> function shall
 *  			return the version information of this module. The
 *  			version information includes:
 *  			- Module Id
 *  			- Vendor Id
 *  			- Vendor specific version numbers (<tt>BSW00407</tt>).
 *
 *  <b>WDG068</b>:	The <tt>Wdg_PCLK_GetVersionInfo()</tt> function shall
 *  			be pre-compile time configurable On/Off by the
 *  			configuration parameter <tt>WdgVersionInfoApi</tt>.
 *
 *  <b>WDG099</b>:	If source code for caller and callee of the
 *  			<tt>Wdg_PCLK_GetVersionInfo()</tt> function is
 *  			available, the module Wdg_PCLK should realize this
 *  			function as a macro, defined in the module's header
 *  			file.
 *
 *  <b>WDG174</b>:	If DET is enabled for the Wdg_PCLK Driver module, the
 *  			function <tt>Wdg_PCLK_GetVersionInfo()</tt> shall
 *  			raise <tt>WDG_E_PARAM_POINTER</tt>, if the argument is a
 *  			<tt>NULL</tt> pointer and return without any action.
 */
#if ( WDG_PCLK_DEV_ERROR_DETECT == STD_ON )
#define	Wdg_PCLK_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,WDG_PCLK) \
	else \
	{\
		Det_ReportError(\
			WDG_MODULE_ID,\
			0,\
			WDG_GETVERSIONINFO_SERVICE_ID,\
			WDG_E_PARAM_POINTER\
		);\
	}
#else
#define	Wdg_PCLK_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,WDG_PCLK)
#endif	/* WDG_PCLK_DEV_ERROR_DETECT */
#endif	/* WDG_PCLK_VERSION_INFO_API */

#endif	/* WDG_PCLK_H */
