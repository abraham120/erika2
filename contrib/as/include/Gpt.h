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

/** @file	Gpt.h
 *  @brief	AUTOSAR-"like" GPT Driver Header File.
 *
 *  <b>GPT365</b>:	<tt>Gpt.h</tt> Module header file (interface file)
 *  			(<b>BSW00370</b>)
 *
 *  The GPT driver provides General Porpose Times(s) services.
 *
 *  The GPT driver is part of the microcontroller abstraction layer (MCAL). It
 *  initializes and controls the internal General Purpose Timer(s) (GPT) of the
 *  microcontroller.
 *
 *  The GPT driver provides services and configuration parameters for
 *  - Starting and stopping hardware timers
 *  - Getting timer values
 *  - Controlling time triggered interrupt notifications
 *  - Controlling time triggered wakeup interrupts, if supported by hardware
 *
 *  The tick duration of a timer channel depends on channel specific settings
 *  (part of GPT driver) as well as on system clock and settings of the clock
 *  tree controlled by the MCU module. The tick duration is not limited by this
 *  specification.
 *
 *  Not all hardware timers must be controlled by the GPT module. Some timers
 *  may be controlled by AUTOSAR Operating System (OS) or Complex Device
 *  Drivers (CDD) directly. The number of timer channels controlled by the GPT
 *  driver depends on hardware, implementation and system configuration.
 *
 *  Beside the GPT there are other possibilities for time measurements:
 *  Software Free Running Timer (SWFRT) functionality, implemented in the
 *  AUTOSAR OS. The SWFRT especially is designed for reuse of timers with
 *  "short" tick durations, only realizable on base of hardware timers
 *  (typically 100ns ... 1ms). An other possibility for reusing timers is to
 *  create software timers based on cyclic OS tasks or cyclic interrupts.
 *  The tick duration of such a timer is equal to the respective cycle time
 *  (typically >= 1ms).
 *
 *  The GPT driver only generates time bases, and does not serve as an event
 *  counter. This functionality is provided by another driver module
 *  (ICU driver).
 *
 *  <b>GPT333</b>:	Each variable that shall be accessible by AUTOSAR
 *  			Debugging, shall be defined as global variable.
 *
 *  <b>GPT334</b>:	All type definitions of variables which shall be
 *  			debugged, shall be accessible by the header file
 *  			<tt>Gpt.h</tt>.
 *
 *  <b>GPT335</b>:	The declaration of variables in the header file shall
 *  			allow to calculate the size of the variables by
 *  			C-"sizeof".
 *
 *  <b>GPT336</b>:	Variables available for debugging shall be described in
 *  			the respective Basic Software Module Description.
 *
 *  <b>GPT337</b>:	The operation mode of the GPT driver and the state of
 *  			each timer channel shall be available for debugging.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */

#ifndef	GPT_H
#define	GPT_H

/** @brief	Vendor Id
 *
 *  Vendor Id from document:
 *  [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 *  http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	GPT_VENDOR_ID		0

/** @brief	Module Id
 *
 *  Module Id (100) from document:
 *  List of Basic Software Modules
 *  V1.5.0
 *  R4.0 Rev 2
 */
#define	GPT_MODULE_ID		100

#define	GPT_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	GPT_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	GPT_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	GPT_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	GPT_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	GPT_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

#include "Std_Types.h"

/** @brief	Numeric ID of a GPT channel.
 *
 *  <b>GPT358</b>:	Numeric ID of a GPT channel. (<tt>BSW00305</tt>)
 *  			Implementation specific. But not all values may be valid
 *  			within this type. This type shall be chosen in order to
 *  			have the most efficient implementation on a specific
 *  			micro controller platform.
 *
 *  Parameters of type <tt>Gpt_ChannelType</tt> contain the numeric ID of a GPT
 *  channel.
 *
 *  The mapping of the ID is implementation specific but not configurable and
 *  not all values may be valid within this type.
 *
 *  For parameter values of type <tt>Gpt_ChannelType</tt>, the Gpt's user shall
 *  use the symbolic names provided by the configuration description.
 *
 *  The type shall be uint8, uint16 or uint32, depending on uC platform.
 */
typedef	uint8_least	Gpt_ChannelType;

/** @brief	Notifications Callback Function Pointer
 *
 *  The notification prototype <tt>Gpt_Notification_<channel>()</tt> is for the
 *  notifications callback function and shall be implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notifications callback
 *  for each channel to avoid parameters in notification services and to improve
 *  run time efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The notifications callback
 *  			<tt>Gpt_Notification_<channel>()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notifications
 *  			callback if configured.
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting the interrupt flags (if needed
 *  			by hardware) and calling the according notification
 *  			function. (<tt>BSW12129</tt>)
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
typedef void (*Gpt_Notification)(
  void
);

/*
 * GPT259:	Gpt.h shall include Gpt_Cfg.h for the API pre-compiler switches.
 */
#include "Gpt_Cfg.h"

/*
 * GPT174:	Development error values are of type uint8. (BSW00304)
 *
 * The following errors shall be detectable by the GPT driver depending on its
 * build version (development / production).

 *
 * GPT345:	GPT_E_UNINIT (0x0A)
 * 		API service called without module initialization
 *
 * GPT346:	GPT_E_BUSY (0x0B)
 * 		API service when timer channel is still busy (running)
 *
 * GPT347:	GPT_E_ALREADY_INITIALIZED (0x0D) 
 * 		API parameter checking: called when already initialized
 *
 * GPT348:	GPT_E_PARAM_CHANNEL (0x14)
 * 		API parameter checking: invalid channel
 *
 * GPT349:	GPT_E_PARAM_VALUE (0x15)
 * 		API parameter checking: invalid value
 *
 * GPT350:	GPT_E_PARAM_POINTER (0x16)
 * 		API parameter checking: invalid pointer
 *
 * GPT351:	GPT_E_PARAM_MODE (0x1F)
 * 		API parameter checking: invalid mode
 *
 * GPT004:	Additional errors that are detected because of specific
 * 		implementation and/or specific hardware properties shall be
 * 		added in the GPT device specific implementation specification.
 * 		The classification and enumeration shall be compatible to the
 * 		errors listed above. (BSW00337)
 */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )
/** GPT Module Not Initialized. */
#define	GPT_E_UNINIT			0x0A
/** Timer Channel Busy */
#define	GPT_E_BUSY			0x0B
/** GPT Module Already Initialized */
#define	GPT_E_ALREADY_INITIALIZED	0x0D
/** Invalid Channel. */
#define	GPT_E_PARAM_CHANNEL		0x14
/** Invalid Value. */
#define	GPT_E_PARAM_VALUE		0x15
/** Pointer is NULL_PTR. */
#define	GPT_E_PARAM_POINTER		0x16
/** Invalid Mode. */
#define	GPT_E_PARAM_MODE		0x1F
/** Invalid state transition from the current state. */
#define	GPT_E_STATE_TRANSITION		0x20
#endif

/** @brief	GPT Driver Configuration Parameters
 *
 *  <b>GPT357</b>:	This is the type of the data structure including the
 *  			configuration set required for initializing the GPT
 *  			timer unit. (<tt>BSW00404</tt>, <tt>BSW00405</tt>,
 *  			<tt>BSW00438</tt>, <tt>BSW00305</tt>, <tt>BSW00414</tt>,
 *  			<tt>BSW12263</tt>)
 *
 *  The structure <tt>Gpt_ConfigType</tt> is an external data structure (i.e.
 *  implementation specific) and shall contain the initialization data for the
 *  GPT module. It shall contain:
 *  - GPT dependent properties
 *  - GPT harware unit initialization parameters
 *  - SFR's settings affecting the GPT channels
 */
extern const Gpt_ConfigType	Gpt_Config[];

/** @brief	GPT Value Type
 *
 *  <b>GPT359</b>:	Type for reading and setting the timer values (in number
 *  			of ticks). (<tt>BSW00305</tt>, <tt>BSW12063</tt>,
 *  			<tt>BSW12328</tt>) The range of this type is uC
 *  			dependent (width of the timer register) and has to be
 *  			described by the supplier.
 */
typedef uint64		Gpt_ValueType;

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )
/** @brief	GPT Mode Type
 *
 *  <b>GPT360</b>:	Allows the selection of different power modes.
 *  			(<tt>BSW00441</tt>, <tt>BSW00305</tt>)
 */
typedef enum {
  GPT_MODE_NORMAL,	/**< Normal operation mode of the GPT.		      */
  GPT_MODE_SLEEP	/**< Operation for reduced power operation mode.
  			 *   In sleep mode only wakeup capable channels are
  			 *   available.					      */
} Gpt_ModeType;
#endif

/** @brief	GPT Status Type
 *
 *  The type <tt>Gpt_StatusType</tt> is the type of the return value of the
 *  function <tt>Gpt_GetStatus()</tt>.
 *
 *  The type of <tt>Gpt_StatusType</tt> is an enumeration describing the
 *  operation states for a GPT channel.
 */
typedef enum {
  GPT_NOT_OK,		/**< Development or production error occurred.	      */
  GPT_CH_EXPIRED,	/**< "Expired" State.				      */
  GPT_CH_STOPPED,	/**< "Stopped" State.				      */
  GPT_CH_RUNNING,	/**< "Running" State.				      */
  GPT_OPERATIONAL,	/**< Normal operation. "Initialized" State. */
  GPT_CH_SLEEP		/**< Sleep state operation.			      */
} Gpt_StatusType;

/*
 * Service ID's
 */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )

#define	GPT_GETVERSIONINFO_SERVICE_ID		0x00
#define	GPT_INIT_SERVICE_ID			0x01
#define	GPT_DEINIT_SERVICE_ID			0x02
#define	GPT_GETTIMEELAPSED_SERVICE_ID		0x03
#define	GPT_GETTIMEREMINING_SERVICE_ID		0x04
#define	GPT_STARTTIMER_SERVICE_ID		0x05
#define	GPT_STOPTIMER_SERVICE_ID		0x06
#define	GPT_ENABLENOTIFICATION_SERVICE_ID	0x07
#define	GPT_DISABLENOTIFICATION_SERVICE_ID	0x08
#define	GPT_SETMODE_SERVICE_ID			0x09
#define	GPT_DISABLEWAKEUP_SERVICE_ID		0x0A
#define	GPT_ENABLEWAKEUP_SERVICE_ID		0x0B
#define	GPT_CHECKWAKEUP_SERVICE_ID		0x0C
#define	GPT_GOTOSLEEP_SERVICE_ID		0x0D
#define	GPT_WAKEUP_SERVICE_ID			0x0E
#define	GPT_GETSTATUS_SERVICE_ID		0x0F

#endif

#if ( GPT_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval.
 *  @param	_vi	Pointer to where to store the version
 *  			information of this module.
 *
 *  This service returns the version information of this module.
 *
 *  <b>GPT279</b>:	Service 0x00 (<tt>BSW00407</tt>)
 *
 *  <b>GPT181</b>:	The function <tt>Gpt_GetVersionInfo()</tt> shall return
 *  			the version information this module according to the
 *  			definition of <tt>Std_VersionInfoType</tt>.
 *  			(<tt>BSW00407</tt>)
 *
 *  <b>GPT273</b>:	If source code for caller and callee of
 *  			<tt>Gpt_GetVersionInfo()</tt> is available, the GPT
 *  			module should realize <tt>Gpt_GetVersionInfo()</tt> as a
 *  			macro, defined in the module's header file.
 *
 *  <b>GPT182</b>:	The function <tt>Gpt_GetVersionInfo()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptVersionInfoApi</tt> (<tt>BSW171</tt>)
 *
 *  <b>GPT338</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter <tt>_vi</tt> is a null
 *  			pointer, the function <tt>Gpt_GetVersionInfo()</tt>
 *  			shall raise the error <tt>GPT_E_PARAM_POINTER</tt>.
 */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )
#define	Gpt_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,GPT) \
	else \
	{\
		Det_ReportError(\
			GPT_MODULE_ID,\
			0,\
			GPT_GETVERSIONINFO_SERVICE_ID,\
			GPT_E_PARAM_POINTER\
		);\
	}
#else
#define	Gpt_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,GPT)
#endif	/* GPT_DEV_ERROR_DETECT */
#endif	/* GPT_VERSION_INFO_API */

/** @brief	GPT Driver Initialization
 *  @param	ConfigPtr	Pointer to GPT driver configuration set.
 *  @return	None
 *
 *  This service initializes the GPT driver.
 *
 *  <b>GPT280</b>:	Service 0x01 (<tt>BSW00404</tt>, <tt>BSW00405</tt>,
 *  			<tt>BSW00438</tt>, <tt>BSW101</tt>, <tt>BSW00358</tt>,
 *  			<tt>BSW00414</tt>, <tt>BSW12057</tt>)
 *
 *  <b>GPT006</b>:	The function <tt>Gpt_Init()</tt> shall initialize the
 *  			hardware timer module according to a configuration set
 *  			referenced by <tt>ConfigPtr</tt>.
 *  			(<tt>BSW101</tt>, <tt>BSW12057</tt>)
 *
 *  <b>GPT107</b>:	The function <tt>Gpt_Init()</tt> shall disable all
 *  			interrupt notifications, controlled by the GPT driver.
 *
 *  <b>GPT068</b>:	The function <tt>Gpt_Init()</tt> shall only initialize
 *  			the configured resources. Resources that are not
 *  			configured in the configuration file shall not be
 *  			touched. (<tt>BSW12125</tt>)
 *
 *  The following rules regarding initialization of controller registers shall
 *  apply to this driver implementation:
 *  - <b>GPT352</b>:	If the hardware allows for only one usage of the
 *  			register, the driver module implementing that
 *  			functionality is responsible for initializing the
 *  			register. (<tt>BSW12461</tt>)
 *  - <b>GPT353</b>:	If the register can affect several hardware modules and
 *  			if it is an I/O register it shall be initialized by the
 *  			PORT driver. (<tt>BSW12461</tt>)
 *  - <b>GPT354</b>:	If the register can affect several hardware modules and
 *  			if it is not an I/O register it shall be initialized by
 *  			the MCU driver. (<tt>BSW12461</tt>)
 *  - <b>GPT355</b>:	One-time writable registers that require initialization
 *  			directly after reset shall be initialized by the startup
 *  			code. (<tt>BSW12461</tt>)
 *  - <b>GPT356</b>:	All other registers shall be initialized by the startup
 *  			code (<tt>BSW12461</tt>)
 *
 *  <b>GPT307</b>:	If development error detection for the GPT module is
 *  			enabled: If the GPT driver is not in operation mode
 *  			"uninitialized", the function Gpt_Init shall raise the
 *  			error <tt>GPT_E_ALREADY_INITIALIZED</tt>.
 *
 *  <b>GPT258</b>:	The function <tt>Gpt_Init()</tt> shall disable all
 *  			wakeup interrupts, controlled by the GPT driver.
 *
 *  <b>GPT339</b>:	The function <tt>Gpt_Init()</tt> shall set the operation
 *  			mode of the GPT driver to "normal mode". This leads to a
 *  			behavior like <tt>Gpt_SetMode()</tt> is called with
 *  			parameter <tt>GPT_MODE_NORMAL</tt>.
 *
 *  <b>GPT294</b>:	If development error detection for the GPT module is
 *  			enabled: If <tt>VARIANT-POST-BUILD</tt> is supported by
 *  			implementation and the parameter <tt>ConfigPtr</tt> is a
 *  			null pointer, the function <tt>Gpt_Init()</tt> shall
 *  			raise the error <tt>GPT_E_PARAM_POINTER</tt>.
 *
 *  <b>GPT340</b>:	If development error detection for the GPT module is
 *  			enabled: If <tt>VARIANT-POST-BUILD</tt> is not supported
 *  			by implementation and the parameter <tt>ConfigPtr</tt>
 *  			is not a null pointer, the function <tt>Gpt_Init()</tt>
 *  			shall raise the error <tt>GPT_E_PARAM_POINTER</tt>.
 *
 *  <b>GPT309</b>:	A re-initialization of the GPT driver by executing the
 *  			<tt>Gpt_Init()</tt> function requires a
 *  			de-initialization before by executing a
 *  			<tt>Gpt_DeInit</tt>.
 */
void Gpt_Init(
  const Gpt_ConfigType * ConfigPtr
);

#if ( GPT_DEINIT_API == STD_ON )
/** @brief	GPT Driver De-Initialization.
 *  @return	None
 *
 *  Deinitializes all hardware timer channels.
 *
 *  <b>GPT281</b>:	Service 0x02 (<tt>BSW00336</tt>, <tt>BSW12163</tt>,
 *  			<tt>BSW12116</tt>)
 *
 *  <b>GPT008</b>:	The function <tt>Gpt_DeInit()</tt> shall deinitialize
 *  			the hardware used by the GPT driver (depending on
 *  			configuration) to the power on reset state. Values of
 *  			registers which are not writeable are excluded. It's
 *  			the responsibility of the hardware design that the state
 *  			does not lead to undefined activities in the uC.
 *  			(<tt>BSW00336</tt>, <tt>BSW12163</tt>,
 *  			<tt>BSW12116</tt>)
 *
 *  <b>GPT105</b>:	The function <tt>Gpt_DeInit()</tt> shall disable all
 *  			interrupt notifications and wakeup interrupts,
 *  			controlled by the GPT driver.
 *
 *  <b>GPT162</b>:	The function <tt>Gpt_DeInit()</tt> shall influence only
 *  			the peripherals, which are allocated by the static
 *  			configuration. (<tt>BSW12116</tt>)
 *
 *  <b>GPT308</b>:	If a postbuild multiple selectable configuration variant
 *  			was used, the function <tt>Gpt_DeInit()</tt> shall
 *  			further influence only the peripherals, which are
 *  			allocated by the runtime configuration set passed by the
 *  			previous call of the function <tt>Gpt_Init()</tt>.
 *  			(<tt>BSW12116</tt>)
 *
 *  <b>GPT194</b>:	The function <tt>Gpt_DeInit()</tt> shall be pre compile
 *  			time configurable On/Off by the configuration parameter:
 *  			<tt>GptDeInitApi</tt>. (<tt>BSW171</tt>)
 *
 *  <b>GPT363</b>:	The function <tt>Gpt_DeInit()</tt> shall set the
 *  			operation mode of the GPT driver to "uninitialized".
 *
 *  <b>GPT234</b>:	If development error detection for the GPT module is
 *  			enabled: If any timer channel is in state "running", the
 *  			function <tt>Gpt_DeInit()</tt> shall raise the error
 *  			<tt>GPT_E_BUSY</tt>.
 *
 *  <b>GPT220</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_DeInit()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 */
void Gpt_DeInit(
  void
);
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
/** @brief	Elapsed Time Retrieval.
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	Elapsed timer value (in number of ticks)
 *
 *  The service returns the time already elapsed.
 *
 *  <b>GPT282</b>:	Service 0x03 (<tt>BSW12117</tt>)
 *
 *  <b>GPT010</b>:	The function <tt>Gpt_GetTimeElapsed()</tt> shall return
 *  			the time already elapsed. When the channel is in mode
 *  			"one-shot mode", this is the value relative to the point
 *  			in time, the channel has been started.
 *  			(<tt>BSW12117</tt>)
 *
 *  <b>GPT361</b>:	When the channel is in mode "continuous mode", the
 *  			return value of <tt>Gpt_GetTimeElapsed()</tt> is the
 *  			value relative to the last recurrence (target time
 *  			reached) or to the start of the channel before the first
 *  			recurrence occurs.
 *
 *  <b>GPT295</b>:	If the function <tt>Gpt_GetTimeElapsed()</tt> is called
 *  			on a timer channel in state "initialized" (channel
 *  			started never before), the function shall return the
 *  			value "0".
 *
 *  <b>GPT297</b>:	If the function <tt>Gpt_GetTimeElapsed()</tt> is called
 *  			on a timer channel in state "stopped", the function
 *  			shall return the time value at the moment of stopping.
 *
 *  <b>GPT299</b>:	If the function <tt>Gpt_GetTimeElapsed()</tt> is called
 *  			on a channel configured for "one-shot mode" in state
 *  			"expired" (timer has reached the target time), the
 *  			function shall return the target time.
 *
 *  <b>GPT113</b>:	The function <tt>Gpt_GetTimeElapsed()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT195</b>:	The function <tt>Gpt_GetTimeElapsed()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptTimeElapsedApi</tt>. (<tt>BSW171</tt>)
 *
 *  <b>GPT222</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_GetTimeElapsed()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt> and shall return the value "0".
 *  			(<tt>BSW00406</tt>)
 *
 *  <b>GPT210</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration), the function
 *  			<tt>Gpt_GetTimeElapsed()</tt> shall raise the
 *  			development error <tt>GPT_E_PARAM_CHANNEL</tt> and shall
 *  			return the value "0".
 *
 *  if the GPT channel state-machine is in the state <tt>GPT_CH_SLEEP</tt>, the
 *  function <tt>Gpt_GetTimeElapsed()</tt> shall raise the development error
 *  <tt>GPT_E_STATE_TRANSITION</tt> and shall return the value "0".
 */
Gpt_ValueType Gpt_GetTimeElapsed(
  Gpt_ChannelType	Channel
);
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
/** @brief	Time Remaining Retrieval.
 *  @param	Channel	Numeric identifier of the GPT channel
 *  @return	Remaining timer value (in number of ticks)
 *
 *  The service returns the time remaining until the target time is reached.
 *
 *  <b>GPT283</b>:	Service 0x04 (<tt>BSW12117</tt>)
 *
 *  <b>GPT083</b>:	The function <tt>Gpt_GetTimeRemaining()</tt> shall
 *  			return the timer value remaining until the target time
 *  			will be reached next time. The remaining time is the
 *  			"target time" minus the time already elapsed.
 *  			(<tt>BSW12117</tt>)
 *
 *  <b>GPT301</b>:	If the function <tt>Gpt_GetTimeRemaining()</tt> is
 *  			called on a timer channel in state "initialized"
 *  			(channel started never before), the function shall
 *  			return the value "0".
 *
 *  <b>GPT303</b>:	If the function <tt>Gpt_GetTimeRemaining()</tt> is
 *  			called on a timer channel in state "stopped", the
 *  			function shall return the remaining time value at the
 *  			moment of stopping.
 *
 *  <b>GPT305</b>:	If the function <tt>Gpt_GetTimeRemaining()</tt> is
 *  			called on a channel configured for "one-shot mode" in
 *  			state "expired" (timer has reached the target time), the
 *  			function shall return the value "0".
 *
 *  <b>GPT114</b>:	The function <tt>Gpt_GetTimeRemaining()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT196</b>:	?The function <tt>Gpt_GetTimeRemaining()</tt> shall be
 *  			pre compile time configurable On/Off by the
 *  			configuration parameter: <tt>GptTimeRemainingApi</tt>.
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT223</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_GetTimeRemaining()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt> and shall return the value "0".
 *  			(<tt>BSW00406</tt>)
 *
 *  <b>GPT211</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration), the function
 *  			<tt>Gpt_GetTimeRemaining()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt> and shall return the value
 *  			"0".
 *
 *  if the GPT channel state-machine is in the state <tt>GPT_CH_SLEEP</tt>, the
 *  function <tt>Gpt_GetTimeRemaining()</tt> shall raise the development error
 *  <tt>GPT_E_STATE_TRANSITION</tt> and shall return the value "0".
 */
Gpt_ValueType Gpt_GetTimeRemaining(
  Gpt_ChannelType	Channel
);
#endif

/** @brief	Timer Start.
 *  @param	Channel	Numeric identifier of the GPT channel
 *  @param	Value	Target time in number of ticks.
 *  @return	None
 *
 *  Starts a timer channel.
 *
 *  <b>GPT284</b>:	Service 0x05 (<tt>BSW12128</tt>)
 *
 *  <b>GPT274</b>:	The function <tt>Gpt_StartTimer()</tt> shall start the
 *  			selected timer channel with a defined target time.
 *  			(<tt>BSW12128</tt>)
 *
 *  <b>GPT275</b>:	If configured and enabled, an interrupt notification or
 *  			a wakeup interrupt occurs, when the target time is
 *  			reached. (<tt>BSW12128</tt>)
 *
 *  <b>GPT115</b>:	The function <tt>Gpt_StartTimer()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT364</b>:	The state of the selected timer channel shall be changed
 *  			to "running" if <tt>Gpt_StartTimer()</tt> is called.
 *
 *  <b>GPT212</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration), the function
 *  			<tt>Gpt_StartTimer()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 *
 *  <b>GPT218</b>:	If development error detection for the GPT module is
 *  			enabled: The function <tt>Gpt_StartTimer()</tt> shall
 *  			raise the error <tt>GPT_E_PARAM_VALUE</tt> if the
 *  			parameter Value is "0" or not within the allowed range
 *  			(exceeding the maximum timer resolution).
 *
 *  <b>GPT224</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_StartTimer()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  <b>GPT084</b>:	If development error detection for the GPT module is
 *  			enabled: If the function <tt>Gpt_StartTimer()</tt> is
 *  			called on a channel in state "running", the function
 *  			shall raise the error <tt>GPT_E_BUSY</tt>.
 *
 *  if the GPT channel state-machine is in the state <tt>GPT_CH_SLEEP</tt>, the
 *  function <tt>Gpt_StartTimer()</tt> shall raise the development error
 *  <tt>GPT_E_STATE_TRANSITION</tt>.
 */
void Gpt_StartTimer(
  Gpt_ChannelType	Channel,
  Gpt_ValueType		Value
);

/** @brief	Timer Stop.
 *  @param	Channel	Numeric identifier of the GPT channel
 *  @return	None
 *
 *  Stops a timer channel.
 *
 *  <b>GPT285</b>:	Service 0x06 (<tt>BSW12119</tt>)
 *
 *  <b>GPT013</b>:	The function <tt>Gpt_StopTimer()</tt> shall stop the
 *  			selected timer channel. (<tt>BSW12119</tt>)
 *
 *  <b>GPT343</b>:	The state of the selected timer channel shall be changed
 *  			to "stopped" if <tt>Gpt_StopTimer()</tt> is called.
 *
 *  <b>GPT099</b>:	If development error detection for the GPT module is
 *  			enabled: If the function <tt>Gpt_StopTimer()</tt> is
 *  			called on a channel in state "initialized", "stopped" or
 *  			"expired", the function shall not raise a development
 *  			error.
 *
 *  <b>GPT344</b>:	If the function <tt>Gpt_StopTimer()</tt> is called on a
 *  			channel in state "initialized", "stopped" or "expired",
 *  			the function shall leave without any action (no change
 *  			of the channel state).
 *
 *  <b>GPT116</b>:	The function <tt>Gpt_StopTimer()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT213</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration), the function
 *  			<tt>Gpt_StopTimer()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 *
 *  <b>GPT225</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_StopTimer()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  if the GPT channel state-machine is in the state <tt>GPT_CH_SLEEP</tt>, the
 *  function <tt>Gpt_StopTimer()</tt> shall raise the development error
 *  <tt>GPT_E_STATE_TRANSITION</tt>.
 */
void Gpt_StopTimer(
Gpt_ChannelType Channel
);

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/** @brief	Channel Notification Enable
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	None
 *
 *  Enables the interrupt notification for a channel (relevant in normal mode).
 *
 *  <b>GPT286</b>:	Service 0x07 (<tt>BSW12121</tt>)
 *
 *  <b>GPT014</b>:	The function <tt>Gpt_EnableNotification()</tt> shall
 *  			enable the interrupt notification of the referenced
 *  			channel configured for notification. (<tt>BSW157</tt>,
 *  			<tt>BSW12067</tt>, <tt>BSW12121</tt>)
 *
 *  @note	The function shall save an attribute like "notification enabled"
 *  		of the channel.
 *
 *  @note	This attribute affects the interrupt notification always when
 *  		the driver is in "normal mode". In "sleep mode" the attribute
 *  		has no influence.
 *
 *  <b>GPT117</b>:	The function <tt>Gpt_EnableNotification()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT199</b>:	The function <tt>Gpt_EnableNotification()</tt> shall be
 *  			pre compile time configurable On/Off by the
 *  			configuration parameter:
 *  			<tt>GptEnableDisableNotificationApi</tt>
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT226</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_EnableNotification()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  <b>GPT214</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration), the function
 *  			<tt>Gpt_EnableNotification()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 *
 *  <b>GPT377</b>:	If development error detection for the GPT module is
 *  			enabled: If no valid notification function is configured
 *  			(<tt>GptNotification_<channel>()</tt>), the function
 *  			<tt>Gpt_EnableNotification()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 */
void Gpt_EnableNotification(
  Gpt_ChannelType	Channel
);

/** @brief	Channel Notification Disable
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	None
 *
 *  Disables the interrupt notification for a channel (relevant in normal mode).
 *
 *  <b>GPT287</b>:	Service 0x08 (<tt>BSW12122</tt>)
 *
 *  <b>GPT015</b>:	The function <tt>Gpt_DisableNotification()</tt> shall
 *  			disable the interrupt notification of the referenced
 *  			channel configured for notification. (<tt>BSW157</tt>,
 *  			<tt>BSW12122</tt>, <tt>BSW12067</tt>)
 *
 *  @note	The function shall save an attribute like
 *  		"notification disabled" of the channel.
 *
 *  @note	This attribute affects the interrupt notification always when
 *  		the driver is in "normal mode". In "sleep mode" the attribute
 *  		has no influence.
 *
 *  <b>GPT118</b>:	The function <tt>Gpt_DisableNotification()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT200</b>:	The function <tt>Gpt_DisableNotification()</tt> shall be
 *  			pre compile time configurable On/Off by the
 *  			configuration parameter:
 *  			<tt>GptEnableDisableNotificationApi</tt>.
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT227</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_DisableNotification()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  <b>GPT217</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration), the function
 *  			<tt>Gpt_DisableNotification()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 *
 *  <b>GPT379</b>:	If development error detection for the GPT module is
 *  			enabled: If no valid notification function is configured
 *  			(<tt>GptNotification_<channel>()</tt>), the function
 *  			<tt>Gpt_DisableNotification()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 */
void Gpt_DisableNotification(
  Gpt_ChannelType	Channel
);
#endif

#if ( \
  ( GPT_REPORT_WAKEUP_SOURCE == STD_ON ) && \
  ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) \
)
/** @brief	GPT Mode Setting.
 *  @param	Mode	GPT Operation Mode.
 *  @return	None.
 *
 *  Sets the operation mode of the GPT.
 *
 *  <b>GPT288</b>:	Service 0x09 (<tt>BSW12169</tt>, <tt>BSW13603</tt>)
 *
 *  <b>GPT151</b>:	The function <tt>Gpt_SetMode()</tt> shall set the
 *  			operation mode of the GPT driver to the given mode
 *  			parameter. (<tt>BSW12169</tt>, <tt>BSW13603</tt>)
 *
 *  <b>GPT255</b>:	The function <tt>Gpt_SetMode()</tt> is only available
 *  			if the configuration parameter
 *  			<tt>GptReportWakeupSource</tt> is enabled.
 *
 *  <b>GPT152</b>:	If the parameter Mode has the value
 *  			<tt>GPT_MODE_NORMAL</tt>: The function
 *  			<tt>Gpt_SetMode()</tt> shall enable the interrupt
 *  			notification for all channels which are configured for
 *  			notification and the notification is enabled (stored
 *  			attribute) via the function
 *  			<tt>Gpt_EnableNotification()</tt> prior. All other
 *  			interrupt notifications shall be disabled.
 *  			(<tt>BSW13603</tt>)
 *
 *  <b>GPT153</b>:	If the parameter Mode has the value
 *  			<tt>GPT_MODE_SLEEP</tt>: The function
 *  			</tt>Gpt_SetMode()</tt> shall enable the wakeup
 *  			interrupts for all channels which are configured for
 *  			wakeup and the wakeup is enabled (stored attribute) via
 *  			the function <tt>Gpt_EnableWakeup()</tt> prior. All
 *  			other wakeup interrupts shall be disabled.
 *  			(<tt>BSW13603</tt>)
 *
 *  <b>GPT164</b>:	If the function <tt>Gpt_SetMode()</tt> is called with
 *  			parameter Mode has the value <tt>GPT_MODE_SLEEP</tt>:
 *  			All timer channels in state "running" which are not
 *  			configured for wakeup or not enabled for wakeup
 *  			interruption (stored attribute) via
 *  			<tt>Gpt_EnableWakeup()</tt> shall be stopped and their
 *  			state shall be changed to "stopped".
 *
 *  <b>GPT165</b>:	If the parameter Mode has the value
 *  			<tt>GPT_MODE_NORMAL</tt>, the function
 *  			<tt>Gpt_SetMode()</tt> shall not restart automatically
 *  			the timer channels which have been stopped by entering
 *  			the sleep mode.
 *
 *  <b>GPT341</b>:	If the parameter has the value <tt>GPT_MODE_SLEEP</tt>
 *  			the function <tt>Gpt_SetMode()</tt> shall not start a
 *  			wakeup timer automatically. First, the application shall
 *  			call <tt>Gpt_StartTimer()</tt> to start a wakeup timer,
 *  			after this the application shall call
 *  			<tt>Gpt_SetMode()</tt> with parameter
 *  			<tt>GPT_MODE_SLEEP</tt>.
 *
 *  <b>GPT228</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_SetMode()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  <b>GPT231</b>:	If development error detection for the GPT module is
 *  			enabled: The function <tt>Gpt_SetMode()</tt> shall raise
 *  			the error <tt>GPT_E_PARAM_MODE</tt> if the parameter
 *  			Mode is invalid.
 *
 *  <b>GPT201</b>:	The function <tt>Gpt_SetMode()</tt> shall be pre compile
 *  			time configurable On/Off by the configuration parameter:
 *  			<tt>GptWakeupFunctionalityApi</tt>. (<tt>BSW171</tt>)
 *
 *  @note	NOT YET IMPLEMENTED: Needs AUTOSAR EcuM.
 */
void Gpt_SetMode(
  Gpt_ModeType	Mode
);

/** @brief	Wakeup Disable.
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	None.
 *
 *  Disables the wakeup interrupt of a channel (relevant in sleep mode).
 *
 *  <b>GPT289</b>:	Service 0x0A (<tt>BSW13602</tt>)
 *
 *  <b>GPT159</b>:	The function <tt>Gpt_DisableWakeup()</tt> shall disable
 *  			the wakeup interrupt of the referenced channel
 *  			configured for wakeup. (<tt>BSW13602</tt>)
 *
 *  @note	The function shall save an attribute like "wakeup disabled" of
 *  		the channel.
 *
 *  @note	This attribute affects the wakeup interrupt always when the
 *  		driver is in "sleep mode". In "normal mode" the attribute has no
 *  		influence.
 *
 *  <b>GPT157</b>:	The function <tt>Gpt_DisableWakeup()</tt> is only
 *  			feasible, if <tt>GptReportWakeupSource</tt> is
 *  			statically configured available.
 *
 *  <b>GPT155</b>:	The function <tt>Gpt_DisableWakeup()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT202</b>:	The function <tt>Gpt_DisableWakeup()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptWakeupFunctionalityApi</tt>.
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT215</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration) or channel wakeup
 *  			is not enabled by configuration
 *  			(<tt>GptEnableWakeup</tt>), the function
 *  			<tt>Gpt_DisableWakeup()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 *
 *  <b>GPT229</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_DisableWakeup()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  @note	NOT YET IMPLEMENTED: Needs AUTOSAR EcuM.
 */
void Gpt_DisableWakeup(
  Gpt_ChannelType	Channel
);

/** @brief	Wakeup Enable.
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	None.
 *
 *  Enables the wakeup interrupt of a channel (relevant in sleep mode).
 *
 *  <b>GPT290</b>:	Service 0x0B (<tt>BSW13602</tt>)
 *
 *  <b>GPT160</b>:	The function <tt>Gpt_EnableWakeup()</tt> shall enable
 *  			the wakeup interrupt of the referenced channel
 *  			configured for wakeup. (<tt>BSW13602</tt>)
 *
 *  @note	The function shall save an attribute like "wakeup enabled" of
 *  		the channel.
 *
 *  @note	This attribute affects the wakeup interrupt always when the
 *  		driver is in "sleep mode". In "normal mode" the attribute has no
 *  		influence.
 *
 *  <b>GPT158</b>:	The function <tt>Gpt_EnableWakeup()</tt> is only
 *  			feasible, if <tt>GptReportWakeupSource</tt> is
 *  			statically configured available.
 *
 *  <b>GPT156</b>:	The function <tt>Gpt_EnableWakeup()</tt> shall be
 *  			reentrant, if the timer channels used in concurrent
 *  			calls are different.
 *
 *  <b>GPT203</b>:	The function <tt>Gpt_EnableWakeup()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptWakeupFunctionalityApi</tt>.
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT230</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_EnableWakeup()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  <b>GPT216</b>:	If development error detection for the GPT module is
 *  			enabled: If the parameter Channel is invalid (not within
 *  			the range specified by configuration) or channel wakeup
 *  			is not enabled by configuration
 *  			(<tt>GptEnableWakeup</tt>), the function
 *  			<tt>Gpt_EnableWakeup()</tt> shall raise the error
 *  			<tt>GPT_E_PARAM_CHANNEL</tt>.
 *
 *  @note	NOT YET IMPLEMENTED: Needs AUTOSAR EcuM.
 */
void Gpt_EnableWakeup(
  Gpt_ChannelType	Channel
);

/** @brief	Wake-up Check.
 *  @param	WakeupSource	Information on wakeup source to be checked.
 *  				The associated GPT channel can be determined
 *  				from configuration data.
 *  @return	None.
 *
 *  Checks if a wakeup capable GPT channel is the source for a wakeup event and
 *  calls the ECU state manager service EcuM_SetWakeupEvent in case of a valid
 *  GPT channel wakeup event.
 *
 *  <b>GPT328</b>:	Service 0x0C
 *
 *  <b>GPT321</b>:	The function <tt>Gpt_CheckWakeup()</tt> shall check if a
 *  			wakeup capable GPT channel is the source for a wakeup
 *  			event and call <tt>EcuM_SetWakeupEvent()</tt> to
 *  			indicate a valid timer wakeup event to the ECU State
 *  			Manager.
 *
 *  <b>GPT322</b>:	The function <tt>Gpt_CheckWakeup()</tt> is only
 *  			feasible, if <tt>GptReportWakeupSource</tt> is
 *  			statically configured available.
 *
 *  <b>GPT323</b>:	The function <tt>Gpt_CheckWakeup()</tt> shall be
 *  			reentrant, by reason of possible usage in concurrent
 *  			interrupt service routines.
 *
 *  <b>GPT324</b>:	The function <tt>Gpt_CheckWakeup()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptWakeupFunctionalityApi</tt>.
 *
 *  <b>GPT325</b>:	If development error detection for the GPT module is
 *  			enabled: If the driver is not initialized, the function
 *  			<tt>Gpt_CheckWakeup()</tt> shall raise the error
 *  			<tt>GPT_E_UNINIT</tt>. (<tt>BSW00406</tt>)
 *
 *  @note	NOT YET IMPLEMENTED: Needs AUTOSAR EcuM.
 */
void Gpt_CheckWakeup(
  EcuM_WakeupSourceType	WakeupSource
);
#endif	/*  ( GPT_REPORT_WAKEUP_SOURCE == STD_ON ) &&
	    ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) */

#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
/** @brief	Channel Sleep
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	
 *  	- <tt>E_OK</tt>:	Sleep command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Sleep command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service instructs the driver to set the addressed GPT channel in the
 *  state <tt>GPT_CH_SLEEP</tt>.
 *
 *  Service 0x0D
 *
 *  The function <tt>Gpt_GoToSleep()</tt> shall set the channel state to
 *  <tt>GPT_CH_SLEEP</tt>.
 *
 *  The function <tt>Gpt_GoToSleep()</tt> shall optionally set the GPT hardware
 *  unit to reduced power operation mode (if supported by HW).
 *
 *  If the timer channel is in state "running", it shall be stopped and his
 *  state shall be changed to "stopped".
 *
 *  The function <tt>Gpt_GoToSleep()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter:
 *  <tt>GptChannelWakeupFunctionalityApi</tt>.
 *
 *  If development error detection for the GPT module is enabled:
 *  - if the function <tt>Gpt_GoToSleep()</tt> is called before the GPT module
 *    was initialized, the function <tt>Gpt_GoToSleep()</tt> shall raise the
 *    development error <tt>GPT_E_UNINIT</tt>.
 *  - the function <tt>Gpt_GoToSleep()</tt> shall raise the development error
 *    <tt>GPT_E_PARAM_CHANNEL</tt> if the channel parameter is invalid.
 *  - the function <tt>Gpt_GoToSleep()</tt> shall raise the development error
 *    <tt>GPT_E_STATE_TRANSITION</tt> if the GPT channel state-machine is in the
 *    state <tt>GPT_CH_SLEEP</tt>.
 */
Std_ReturnType Gpt_GoToSleep(
  Gpt_ChannelType	Channel
);

/** @brief	Channel Wake-up
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	
 *  	- <tt>E_OK</tt>:	Wake-up request has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Wake-up request has not been accepted,
 *  				development or production error occurred.
 *
 *  The service generates a wake-up pulse on the addressed GPT channel.
 *
 *  Service 0x0E
 *
 *  The function <tt>Gpt_Wakeup()</tt> shall generate a wake up pulse on the
 *  addressed GPT channel.
 *
 *  The GPT driver's environment shall only call <tt>Gpt_Wakeup()</tt> when the
 *  GPT channel is in state GPT_CH_SLEEP.
 *
 *  The function <tt>Gpt_Wakeup()</tt> shall enable the interrupt notification
 *  for the channel if is configured for notification and the notification is
 *  enabled (stored attribute) via the function
 *  <tt>Gpt_EnableNotification()</tt> prior.
 *
 *  The function <tt>Gpt_Wakeup()</tt> shall not restart automatically the timer
 *  channel if it has been stopped by entering the sleep mode.
 *
 *  The function <tt>Gpt_Wakeup()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter:
 *  <tt>GptChannelWakeupFunctionalityApi</tt>.
 *
 *  If development error detection for the GPT module is enabled:
 *  - if the function <tt>Gpt_Wakeup()</tt> is called before the GPT module was
 *    initialized, the function <tt>Gpt_Wakeup()</tt> shall raise the
 *    development error <tt>GPT_E_UNINIT</tt>.
 *  - the function <tt>Gpt_Wakeup()</tt> shall raise the development error
 *    <tt>GPT_E_PARAM_CHANNEL</tt> if the channel parameter is invalid or the
 *    channel is inactive.
 *  - the function <tt>Gpt_Wakeup()</tt> shall raise the development error
 *    <tt>GPT_E_STATE_TRANSITION</tt> if the GPT channel state-machine is not in
 *    the state <tt>GPT_CH_SLEEP</tt>.
 */
Std_ReturnType Gpt_Wakeup(
  Gpt_ChannelType	Channel
);

/** @brief	Channel Status Retrieval.
 *  @param	Channel	Numeric identifier of the GPT channel.
 *  @return	
 *  	- <tt>GPT_NOT_OK</tt>:		Development or production error occurred
 *  	- <tt>GPT_OPERATIONAL</tt>:	Normal operation.
 *  	- <tt>GPT_CH_SLEEP</tt>:	Sleep state operation.
 *
 *  The service gets the status of the specified GPT channel.
 *
 *  service 0x0F
 *
 *  The function <tt>Gpt_GetStatus()</tt> shall return the current operational
 *  status of the GPT channel.
 *
 *  The function <tt>Gpt_GetStatus()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter:
 *  <tt>GptChannelWakeupFunctionalityApi</tt>.
 *
 *  If development error detection for the GPT module is enabled:
 *  - if the function <tt>Gpt_GetStatus()</tt> is called before the GPT module
 *    was initialized, the function <tt>Gpt_GetStatus()</tt> shall raise the
 *    development error <tt>GPT_E_UNINIT</tt> and return <tt>GPT_NOT_OK</tt>.
 *  - if the channel parameter is invalid or the channel is inactive, the
 *    function <tt>Gpt_GetStatus()</tt> shall raise the development error
 *    <tt>GPT_E_PARAM_CHANNEL</tt> and return <tt>GPT_NOT_OK</tt>.
 */
Gpt_StatusType Gpt_GetStatus(
  Gpt_ChannelType	Channel
);
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON */

#endif	/* GPT_H */
