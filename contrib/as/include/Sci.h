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

/** @file	Sci.h
 *  @brief	AUTOSAR-"like" SCI Driver Header File.
 *
 *  The SCI driver provides serial communications services.
 *
 *  The SCI driver is part of the microcontroller abstraction layer (MCAL),
 *  performs the hardware access and offers a hardware independent API to the
 *  upper layer.
 *
 *  A SCI driver can support more than one channel. This means that the SCI
 *  driver can handle one or more SCI channels as long as they are belonging to
 *  the same SCI hardware unit.
 *
 *  The hardware of the internal SCI hardware unit depends on the system clock,
 *  prescaler(s) and PLL. Hence, the length of the SCI bit timing depends on the
 *  clock settings made in module SCI.
 *
 *  The SCI driver module will not take care of setting the registers that
 *  configure the clock, prescaler(s) and PLL (e.g. switching on/off the PLL) in
 *  its init functions. The SCI module must do this.
 *
 *  The Port driver configures the port pins used for the SCI driver as input or
 *  output. Hence, the Port driver has to be initialized prior to the use of SCI
 *  functions. Otherwise, SCI driver functions will exhibit undefined behavior.
 *
 *  The SCI driver uses interrupts and therefore there is a dependency on the
 *  OS, which configures the interrupt sources.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */


#ifndef	SCI_H
#define	SCI_H

/** @brief	Vendor Id
 *
 *  Vendor Id from document:
 *  [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 *  http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	SCI_VENDOR_ID		0

/** @brief	Module Id
 *
 *  Module Id (101) from document:
 *  List of Basic Software Modules
 *  V1.5.0
 *  R4.0 Rev 2
 */
#define	SCI_MODULE_ID		0xFFFF	/**< (Not Specified in AUTOSAR)       */

#define	SCI_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	SCI_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	SCI_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	SCI_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	SCI_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	SCI_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

#include "Std_Types.h"

/** @brief	Channel
 *
 *  <tt>Sci_ChannelType</tt>
 *
 *  Parameters of type <tt>Sci_ChannelType</tt> contain the numeric ID of a SCI
 *  channel.
 *
 *  The mapping of the ID is implementation specific but not configurable.
 *
 *  For parameter values of type <tt>Sci_ChannelType</tt>, the Sci's user shall
 *  use the symbolic names provided by the configuration description.
 */
typedef	uint8_least	Sci_ChannelType;

/** @brief	Transmission Notifications Callback Function Pointer
 *
 *  The notification prototype <tt>Sci_TxNotification()</tt> is for the
 *  transmission notifications callback function and shall be implemented by the
 *  user.
 *
 *  The SCI module's environment shall declare a separate transmission
 *  notifications callback for each channel to avoid parameters in notification
 *  services and to improve run time efficiency.
 *
 *  The transmission notifications callback
 *  <tt>Sci_TxNotification_<channel>()</tt> shall be configurable as pointers to
 *  user defined functions within the configuration structure.
 *
 *  Each channel shall provide its own transmission notifications callback if
 *  configured.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
typedef void (*Sci_TxNotification)(
  void
);

/** @brief	Transmission Errors Notifications Callback Function Pointer
 *
 *  The notification prototype <tt>Sci_TxErrNotification()</tt> is for the
 *  transmission errors notifications callback function and shall be implemented
 *  by the user.
 *
 *  The SCI module's environment shall declare a separate transmission errors
 *  notifications callback for each channel to avoid parameters in notification
 *  services and to improve run time efficiency.
 *
 *  The transmission errors notifications callback
 *  <tt>Sci_TxErrNotification_<channel>()</tt> shall be configurable as pointers
 *  to user defined functions within the configuration structure.
 *
 *  Each channel shall provide its own transmission errors notifications
 *  callback if configured.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
typedef void (*Sci_TxErrNotification)(
  void
);

/** @brief	Reception Notifications Callback Function Pointer
 *
 *  The notification prototype <tt>Sci_RxNotification()</tt> is for the
 *  reception notifications callback function and shall be implemented by the
 *  user.
 *
 *  The SCI module's environment shall declare a separate reception
 *  notifications callback for each channel to avoid parameters in notification
 *  services and to improve run time efficiency.
 *
 *  The reception notifications callback <tt>Sci_RxNotification_<channel>()</tt>
 *  shall be configurable as pointers to user defined functions within the
 *  configuration structure.
 *
 *  Each channel shall provide its own reception notifications callback if
 *  configured.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
typedef void (*Sci_RxNotification)(
  void
);

/** @brief	Reception Errors Notifications Callback Function Pointer
 *
 *  The notification prototype <tt>Sci_RxErrNotification()</tt> is for the
 *  reception errors notifications callback function and shall be implemented
 *  by the user.
 *
 *  The SCI module's environment shall declare a separate reception errors
 *  notifications callback for each channel to avoid parameters in notification
 *  services and to improve run time efficiency.
 *
 *  The reception errors notifications callback
 *  <tt>Sci_RxErrNotification_<channel>()</tt> shall be configurable as pointers
 *  to user defined functions within the configuration structure.
 *
 *  Each channel shall provide its own reception errors notifications callback
 *  if configured.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
typedef void (*Sci_RxErrNotification)(
  void
);

/*
 * Sci.h shall include Sci_Cfg.h for the API pre-compiler switches.
 * ci.c has access to the Sci_Cfg.h via the implicitly included Sci.h file.
 */
#include "Sci_Cfg.h"

/** @brief	SCI Driver Configuration Parameters
 *
 *  The structure <tt>Sci_ConfigType</tt> is an external data structure (i.e.
 *  implementation specific) and shall contain the initialization data for the
 *  SCI module. It shall contain:
 *  - SCI dependent properties
 *  - SCI harware unit initialization parameters
 *  - SFR's settings affecting the SCI channels
 */
extern const Sci_ConfigType Sci_Config[];

/** @brief	SCI Status Type
 *
 *  The type <tt>Sci_StatusType</tt> is the type of the return value of the
 *  function <tt>Sci_GetStatus()</tt>.
 *
 *  The type of <tt>Sci_StatusType</tt> is an enumeration describing the
 *  operation states for a SCI channel or transmission.
 */
typedef enum {
  SCI_NOT_OK,		/**< Development or production error occurred.	      */
  SCI_TX_OK,		/**< Successful transmission.			      */
  SCI_TX_BUSY,		/**< Ongoing transmission.			      */
  SCI_TX_ERROR,		/**< Erroneous transmission such as:
  			 *   - Transmission disabled.
  			 *   - Physical bus error.			      */
  SCI_RX_OK,		/**< Successful reception.			      */
  SCI_RX_BUSY,		/**< Ongoing reception.				      */
  SCI_RX_ERROR,		/**< Erroneous reception such as:
  			 *   - Reception disabled.
			 *   - Parity error.
  			 *   - Framing error.
  			 *   - Overrun error.				      */
  SCI_OPERATIONAL,	/**< Normal operation; the related SCI channel is ready
  			 *   to transmit or receive. No data from previous
  			 *   reception available (e.g. after initialization)  */
  SCI_CH_SLEEP		/**< Sleep state operation; in this state wake-up
  			 *   detection is enabled.			      */
} Sci_StatusType;

/*
 * The following errors and exceptions shall be detectable by the SCI module
 * depending on its build version (development/production mode)
 */
#if ( SCI_DEV_ERROR_DETECT == STD_ON )
#define	SCI_E_UNINIT			0x00	/**< SCI Module Not
						 *   Initialized.	      */
#define	SCI_E_ALREADY_INITIALIZED	0x01	/**< SCI Module Already
						 *   Initialized	      */
#define	SCI_E_INVALID_CHANNEL		0x02	/**< Invalid or inactive
						 *   channel.     */
#define	SCI_E_INVALID_POINTER		0x03	/**< Invalid pointer.	      */
#define	SCI_E_STATE_TRANSITION		0x04	/**< Invalid state transition
						 *   from the current state.  */
#define	SCI_E_PARAM_POINTER		0x05	/**< Pointer is NULL_PTR.     */
#endif

/*
 * Service ID's
 */
#if ( SCI_DEV_ERROR_DETECT == STD_ON )
#define	SCI_INIT_SERVICE_ID			0x00
#define	SCI_GETVERSIONINFO_SERVICE_ID		0x01
#define	SCI_WRITETXDATA_SERVICE_ID		0x02
#define	SCI_READRXDATA_SERVICE_ID		0x03
#define	SCI_ENABLE_NOTIFICATIONS_SERVICE_ID	0x04
#define	SCI_DISABLE_NOTIFICATIONS_SERVICE_ID	0x05
#define	SCI_GOTOSLEEP_SERVICE_ID		0x06
#define	SCI_WAKEUP_SERVICE_ID			0x07
#define	SCI_GETSTATUS_SERVICE_ID		0x08
#define	SCI_DEINIT_SERVICE_ID			0x09
#define	SCI_CHECKWAKEUP_SERVICE_ID		0x0A
#define	SCI_DISABLETX_SERVICE_ID		0x0B
#define	SCI_ENABLETX_SERVICE_ID			0x0C
#define	SCI_DISABLERX_SERVICE_ID		0x0D
#define	SCI_ENABLERX_SERVICE_ID			0x0E
#endif

/** @brief	SCI Driver Initialization
 *  @param	ConfigPtr	Pointer to SCI driver configuration set.
 *  @return	None
 *
 *  This service initializes the SCI driver.
 *
 *  Service 0x00
 *
 *  The function <tt>Sci_Init()</tt> shall initialize the SCI modulemodule (i.e.
 *  static variables, including flags and SCI HW Unit global hardware settings),
 *  as well as the SCI channels.
 *
 *  Different sets of static configuration may have been configured.
 *
 *  The function <tt>Sci_Init()</tt> shall initialize the module according to
 *  the configuration set pointed to by the parameter Config.
 *
 *  The function <tt>Sci_Init()</tt> shall invoke initializations for relevant
 *  hardware register settings common to all channels available on the SCI
 *  hardware unit.
 *
 *  The function <tt>Sci_Init()</tt> shall also invoke initializations for SCI
 *  channel specific settings.
 *
 *  The SCI module's environment shall not call any function of the SCI module
 *  before having called <tt>Sci_Init()</tt> except
 *  <tt>Sci_GetVersionInfo()</tt>.
 *
 *  If wake-up is supported by hardware (i.e. SciChannelWakeUpSupport == true),
 *  during SCI channel initialization it shall be checked if there was a wake-up
 *  event on the specific SCI channel, (if supported by hardware). If a wake-up
 *  event has been detected, the wake-up shall directly be reported to the EcuM
 *  via <tt>EcuM_SetWakeupEvent()</tt> call-back function. (NOT IMPLEMENTED)
 *
 *  Symbolic names of the available configuration sets are provided by the
 *  configuration description of the SCI driver.
 *
 *  If development error detection for the SCI module is enabled: the function
 *  <tt>Sci_Init()</tt> shall check the parameter <tt>Config</tt> for being
 *  within the allowed range. If <tt>Config</tt> is not in the allowed range,
 *  the function <tt>Sci_Init()</tt> shall raise the development error
 *  <tt>SCI_E_INVALID_POINTER</tt>.
 *
 *  If development error detection for the SCI module is enabled: the function
 *  <tt>Sci_Init()</tt> shall check the SCI driver for being in the state
 *  <tt>SCI_UNINIT</tt>. If the SCI driver is not in the state
 *  <tt>SCI_UNINIT</tt>, the function <tt>Sci_Init()</tt> shall raise the
 *  development error <tt>SCI_E_STATE_TRANSITION</tt>.
 */
void Sci_Init(
  const Sci_ConfigType * ConfigPtr
);

#if ( SCI_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval.
 *  @param	_vi	Pointer to where to store the version
 *  			information of this module.
 *
 *  This service returns the version information of this module.
 *
 *  Service 0x01
 *
 *  The function <tt>SCI_GetVersionInfo()</tt> shall return the version
 *  information of the SCI module. The version information includes:
 *  - Module Id
 *  - Vendor Id
 *  - Vendor specific version numbers
 *
 *  The function <tt>SCI_GetVersionInfo()</tt> shall be pre-compile time
 *  configurable On/Off by the configuration parameter
 *  <tt>SciVersionInfoApi</tt>.
 *
 *  If source code for caller and callee of the function
 *  <tt>SCI_GetVersionInfo()</tt> is available, the SCI module should realize
 *  this function as a macro. The SCI module should define this macro in the
 *  module's header file.
 *
 *  if development error detection is enabled, the parameter
 *  <tt>versioninfo</tt> shall be checked for being <tt>NULL</tt>. The error
 *  <tt>SCI_E_PARAM_POINTER</tt> shall be reported in case the value is a
 *  <tt>NULL</tt> pointer. (TODO)
 */
#if ( SCI_DEV_ERROR_DETECT == STD_ON )
#define	Sci_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,SCI) \
	else \
	{\
		Det_ReportError(\
			SCI_MODULE_ID,\
			0,\
			SCI_GETVERSIONINFO_SERVICE_ID,\
			SCI_E_PARAM_POINTER\
		);\
	}
#else
#define	Sci_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,SCI)
#endif	/* SCI_DEV_ERROR_DETECT */
#endif	/* SCI_VERSION_INFO_API */

/** @brief	Tx Write.
 *  @param	Channel	SCI channel to be addressed
 *  @param	Data	Data byte to be write
 *  @return	
 *  	- <tt>E_OK</tt>:	Write command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Write command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service writes a Data byte into the Tx data register of the SCI HW Unit
 *  for the addressed Channel.
 *
 *  Service 0x02
 *
 *  The SCI module's environment shall only call <tt>Sci_WriteTxData()</tt> on a
 *  channel which is in state <tt>SCI_OPERATIONAL</tt> or in one of the
 *  sub-states of <tt>SCI_OPERATIONAL</tt>.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_WriteTxData()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_WriteTxData()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt> and return with <tt>E_NOT_OK</tt>.
 *  - if the channel parameter is invalid, the function
 *    <tt>Sci_WriteTxData()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> and return with <tt>E_NOT_OK</tt>.
 *  - if the SCI channel state-machine is in the state SCI_CH_SLEEP, the
 *    function <tt>Sci_WriteTxData()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> and return with <tt>E_NOT_OK</tt>.
 */
Std_ReturnType Sci_WriteTxData(
  Sci_ChannelType	Channel,
  uint8			Data
);

/** @brief	Rx Read.
 *  @param	Channel	SCI channel to be addressed
 *  @param	DataPtr	Data byte buffer pointer for Data byte to be read
 *  @return	
 *  	- <tt>E_OK</tt>:	Read command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Read command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service reads a Data byte from the Rx data register of the SCI HW Unit
 *  for the addressed Channel.
 *
 *  Service 0x03
 *
 *  The SCI module's environment shall only call <tt>Sci_ReadRxData()</tt> on a
 *  channel which is in state <tt>SCI_OPERATIONAL</tt> or in one of the
 *  sub-states of <tt>SCI_OPERATIONAL</tt>.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_ReadRxData()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_ReadRxData()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt> and return with <tt>E_NOT_OK</tt>.
 *  - if the channel parameter is invalid, the function
 *    <tt>Sci_ReadRxData()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> and return with <tt>E_NOT_OK</tt>.
 *  - the function <tt>Sci_ReadRxData()</tt> shall check the parameter
 *    <tt>DataPtr</tt> for not being a <tt>NULL</tt> pointer.
 *    If <tt>DataPtr</tt> is a <tt>NULL</tt> pointer, the function
 *    <tt>Sci_ReadRxData()</tt> shall raise the development error
 *    <tt>SCI_E_PARAM_POINTER</tt> and return with <tt>E_NOT_OK</tt>.
 *  - if the SCI channel state-machine is in the state SCI_CH_SLEEP, the
 *    function <tt>Sci_ReadRxData()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> and return with <tt>E_NOT_OK</tt>.
 */
Std_ReturnType Sci_ReadRxData(
  Sci_ChannelType	Channel,
  uint8 *		DataPtr
);

#if ( SCI_NOTIFICATIONS_API == STD_ON )
/** @brief	Channel Notifications Enable
 *  @param	Channel	SCI channel to be addressed
 *  @return	None
 *
 *  Enables the interrupt notifications for a channel.
 *
 *  Service 0x04
 *
 *  The function <tt>Sci_EnableNotifications()</tt> shall enable the interrupt
 *  notifications of the referenced channel configured for notifications.
 *
 *  The function shall save an attribute like "notifications enabled" of the
 *  channel.
 *
 *  @note: This attribute affects the interrupt notifications always when the
 *  channel is in <tt>SCI_OPERATIONAL</tt> state or substates.
 *  In <tt>SCI_CH_SLEEP</tt> state the attribute has no influence.
 *
 *  The function <tt>Sci_EnableNotifications()</tt> shall be reentrant, if the
 *  SCI channels used in concurrent calls are different.
 *
 *  The function <tt>Sci_EnableNotifications()</tt> shall be pre compile time
 *  configurable On/Off by the configuration parameter:
 *  <tt>SciEnableDisableNotificationsApi</tt>
 *
 *  If development error detection for the SCI module is enabled:
 *  - If the driver is not initialized, the function Sci_EnableNotifications()
 *    shall raise the error <tt>SCI_E_UNINIT.</tt>
 *  - If the parameter Channel is invalid (not within the range specified by
 *    configuration), the function <tt>Sci_EnableNotifications()</tt> shall
 *    raise the error <tt>SCI_E_PARAM_CHANNEL</tt>.
 *  - If no valid notification function is configured, the function
 *    <tt>Sci_EnableNotifications()</tt> shall raise the error
 *    <tt>SCI_E_PARAM_CHANNEL</tt>.
 */
void Sci_EnableNotifications(
  Sci_ChannelType	Channel
);

/** @brief	Channel Notifications Disable
 *  @param	Channel	SCI channel to be addressed
 *  @return	None
 *
 *  Disables the interrupt notifications for a channel.
 *
 *  Service 0x05
 *
 *  The function <tt>Sci_DisableNotifications()</tt> shall disable the interrupt
 *  notifications of the referenced channel configured for notifications.
 *
 *  The function shall save an attribute like "notifications disabled" of the
 *  channel.
 *
 *  @note: This attribute affects the interrupt notifications always when the
 *  channel is in <tt>SCI_OPERATIONAL</tt> state or substates.
 *  In <tt>SCI_CH_SLEEP</tt> state the attribute has no influence.
 *
 *  The function <tt>Sci_DisableNotifications()</tt> shall be reentrant, if the
 *  SCI channels used in concurrent calls are different.
 *
 *  The function <tt>Sci_DisableNotifications()</tt> shall be pre compile time
 *  configurable On/Off by the configuration parameter:
 *  <tt>SciEnableDisableNotificationsApi</tt>
 *
 *  If development error detection for the SCI module is enabled:
 *  - If the driver is not initialized, the function Sci_DisableNotifications()
 *    shall raise the error <tt>SCI_E_UNINIT.</tt>
 *  - If the parameter Channel is invalid (not within the range specified by
 *    configuration), the function <tt>Sci_DisableNotifications()</tt> shall
 *    raise the error <tt>SCI_E_PARAM_CHANNEL</tt>.
 *  - If no valid notification function is configured, the function
 *    <tt>Sci_DisableNotifications()</tt> shall raise the error
 *    <tt>SCI_E_PARAM_CHANNEL</tt>.
 */
void Sci_DisableNotifications(
  Sci_ChannelType	Channel
);
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/** @brief	Channel Sleep
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	Sleep command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Sleep command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service instructs the driver to set the addressed SCI channel in the
 *  state <tt>SCI_CH_SLEEP</tt>.
 *
 *  Service 0x06
 *
 *  The function <tt>Sci_GoToSleep()</tt> shall set the channel state to
 *  <tt>SCI_CH_SLEEP</tt>.
 *
 *  The function <tt>Sci_GoToSleep()</tt> shall optionally set the SCI hardware
 *  unit to reduced power operation mode (if supported by HW).
 *
 *  The SCI channel shall enter SCI_CH_SLEEP state even in case of an erroneous
 *  transmission/reception.
 *
 *  The function <tt>Sci_GoToSleep()</tt> shall terminate ongoing frame
 *  transmission of prior transmission requests, even if the transmission is
 *  unsuccessfully completed.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_GoToSleep()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_GoToSleep()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_GoToSleep()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> if the channel parameter is invalid.
 *  - the function <tt>Sci_GoToSleep()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if the SCI channel state-machine is in the
 *    state <tt>SCI_CH_SLEEP</tt>.
 */
Std_ReturnType Sci_GoToSleep(
  Sci_ChannelType	Channel
);
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/** @brief	Channel Wake-up
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	Wake-up request has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Wake-up request has not been accepted,
 *  				development or production error occurred.
 *
 *  The service generates a wake-up pulse on the addressed SCI channel.
 *
 *  Service 0x07
 *
 *  The function <tt>Sci_Wakeup()</tt> shall generate a wake up pulse on the
 *  addressed SCI channel.
 *
 *  The SCI driver's environment shall only call <tt>Sci_Wakeup()</tt> when the
 *  SCI channel is in state SCI_CH_SLEEP.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_Wakeup()</tt> is called before the SCI module was
 *    initialized, the function <tt>Sci_Wakeup()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_Wakeup()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> if the channel parameter is invalid or the
 *    channel is inactive.
 *  - the function <tt>Sci_Wakeup()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if the SCI channel state-machine is not in
 *    the state <tt>SCI_CH_SLEEP</tt>.
 */
Std_ReturnType Sci_Wakeup(
  Sci_ChannelType	Channel
);
#endif

/** @brief	Channel Status Retrieval.
 *  @param	Channel		SCI channel to be addressed
 *  @return	
 *  	- <tt>SCI_NOT_OK</tt>:		Development or production error occurred
 *  	- <tt>SCI_TX_OK</tt>:		Successful transmission
 *  	- <tt>SCI_TX_BUSY</tt>:		Ongoing transmission
 *  	- <tt>SCI_TX_ERROR</tt>:	Erroneous response transmission such as:
 *  		- Transmission disabled.
 *  		- Physical bus error.
 *  	- <tt>SCI_RX_OK</tt>:		Reception of correct response
 *  	- <tt>SCI_RX_BUSY</tt>:		Ongoing reception
 *  	- <tt>SCI_RX_ERROR</tt>:	Erroneous response reception such as:
 *  		- Reception disabled.
 *  		- Parity error.
 *  		- Framing error.
 *  		- Overrun error.
 *  	- <tt>SCI_OPERATIONAL</tt>:	Normal operation; the related SCI
 *  					channel is just initialized or waked up
 *  					from the SCI_CH_SLEEP and no data has
 *  					been sent.
 *  	- <tt>SCI_CH_SLEEP</tt>:	Sleep state operation; in this state
 *  					wake-up detection from slave nodes is
 *  					enabled.
 *
 *  The service gets the status of the specified SCI channel.
 *
 *  service 0x08
 *
 *  The function <tt>Sci_GetStatus()</tt> shall return the current transmission,
 *  reception or operational status of the SCI driver.
 *
 *  The return states <tt>SCI_TX_OK</tt>, <tt>SCI_TX_BUSY</tt>,
 *  <tt>SCI_TX_ERROR</tt>, <tt>SCI_RX_OK</tt>, <tt>SCI_RX_BUSY</tt> and
 *  <tt>SCI_RX_ERROR</tt> are substates of the channel state
 *  <tt>SCI_CH_OPERATIONAL</tt>.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_GetStatus()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_GetStatus()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt> and return <tt>SCI_NOT_OK</tt>.
 *  - if the channel parameter is invalid or the channel is inactive, the
 *    function <tt>Sci_GetStatus()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> and return <tt>SCI_NOT_OK</tt>.
 */
Sci_StatusType Sci_GetStatus(
  Sci_ChannelType	Channel
);

#if ( SCI_DEINIT_API == STD_ON )
/** @brief	SCI Driver De-Initialization.
 *  @return	None
 *
 *  Deinitializes all hardware SCI channels.
 *
 *  Service 0x09
 *
 *  The function <tt>Sci_DeInit()</tt> shall deinitialize the hardware used by
 *  the SCI driver (depending on configuration) to the power on reset state.
 *  Values of registers which are not writeable are excluded. It's the
 *  responsibility of the hardware design that the state does not lead to
 *  undefined activities in the uC.
 *
 *  The function <tt>Sci_DeInit()</tt> shall disable all interrupt notifications
 *  controlled by the SCI driver.
 *
 *  The function <tt>Sci_DeInit()</tt> shall influence only the peripherals,
 *  which are allocated by the static configuration.
 *
 *  If a postbuild multiple selectable configuration variant was used, the
 *  function <tt>Sci_DeInit()</tt> shall further influence only the peripherals,
 *  which are allocated by the runtime configuration set passed by the previous
 *  call of the function <tt>Sci_Init()</tt>.
 *
 *  The function <tt>Sci_DeInit()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter: <tt>SciDeInitApi</tt>.
 *
 *  The function <tt>Sci_DeInit()</tt> shall set the operation mode of the SCI
 *  driver to "uninitialized".
 *
 *  If development error detection for the GPT module is enabled:
 *  - If the driver is not initialized, the function <tt>Sci_DeInit()</tt> shall
 *    raise the error SCI_E_UNINIT.
 */
void Sci_DeInit(
  void
);
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/** @brief	Wake-up Check.
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	No error has occurred during execution
 *  				of the API
 *  	- <tt>E_NOT_OK</tt>:	An error has occurred during execution
 *  				of the API
 *
 *  This service checks if a wakeup has occurred on the addressed SCI channel.
 *
 *  Service 0x0A
 *
 *  After a wake up caused by SCI bus transceiver the function
 *  <tt>Sci_CheckWakeup()</tt> will be called by the SCI interface module to
 *  identify the corresponding SCI channel (e.g. in case of multiple
 *  transceivers are physically connected to one MCU wake up pin).
 *
 *  The function <tt>Sci_CheckWakeup()</tt> shall evaluate the wakeup on the
 *  addressed SCI channel. When a wake-up event on the addressed SCI channel
 *  (e.g. RxD pin has constant low level) is detected, the function
 *  <tt>Sci_CheckWakeup()</tt> shall notify the ECU State Manager module
 *  immediately via the <tt>EcuM_SetWakeupEvent()</tt> callback function.
 *  (NOT IMPLELEMENTED)
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the channel parameter is invalid, the function
 *    <tt>Sci_CheckWakeup()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> and return with <tt>E_NOT_OK</tt>.
 *  - if the function <tt>Sci_CheckWakeup()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_CheckWakeup()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_CheckWakeup()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if no SCI channel of the driver is in the
 *    <tt>SCI_CH_SLEEP state</tt>.
 */
Std_ReturnType Sci_CheckWakeup(
  Sci_ChannelType	Channel
);
#endif

/** @brief	Channel Transmission Disable
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	Command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service instructs the driver to disable the transmission for the
 *  addressed SCI channel.
 *
 *  Service 0x0B
 *
 *  The function <tt>Sci_DisableTx()</tt> shall terminate ongoing transmission
 *  of prior transmission requests, even if the transmission is unsuccessfully
 *  completed.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_DisableTx()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_DisableTx()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_DisableTx()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> if the channel parameter is invalid.
 *  - the function <tt>Sci_DisableTx()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if the SCI channel state-machine is in the
 *    state <tt>SCI_CH_SLEEP</tt>.
 */
Std_ReturnType Sci_DisableTx(
  Sci_ChannelType	Channel
);

/** @brief	Channel Transmission Enable
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	Command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service instructs the driver to enable the transmission for the
 *  addressed SCI channel.
 *
 *  Service 0x0C
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_EnableTx()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_EnableTx()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_EnableTx()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> if the channel parameter is invalid or the
 *    channel is inactive.
 *  - the function <tt>Sci_EnableTx()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if the SCI channel state-machine is in the
 *    state <tt>SCI_CH_SLEEP</tt>.
 */
Std_ReturnType Sci_EnableTx(
  Sci_ChannelType	Channel
);

/** @brief	Channel Reception Disable
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	Command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service instructs the driver to disable the reception for the addressed
 *  SCI channel.
 *
 *  Service 0x0D
 *
 *  The function <tt>Sci_DisableRx()</tt> shall terminate ongoing reception of
 *  prior reception requests, even if the receprion is unsuccessfully completed.
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_DisableRx()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_DisableRx()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_DisableRx()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> if the channel parameter is invalid.
 *  - the function <tt>Sci_DisableRx()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if the SCI channel state-machine is in the
 *    state <tt>SCI_CH_SLEEP</tt>.
 */
Std_ReturnType Sci_DisableRx(
  Sci_ChannelType	Channel
);

/** @brief	Channel Reception Enable
 *  @param	Channel	SCI channel to be addressed
 *  @return	
 *  	- <tt>E_OK</tt>:	Command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Command has not been accepted, development
 *  				or production error occurred.
 *
 *  The service instructs the driver to enable the reception for the
 *  addressed SCI channel.
 *
 *  Service 0x0E
 *
 *  If development error detection for the SCI module is enabled:
 *  - if the function <tt>Sci_EnableRx()</tt> is called before the SCI module
 *    was initialized, the function <tt>Sci_EnableRx()</tt> shall raise the
 *    development error <tt>SCI_E_UNINIT</tt>.
 *  - the function <tt>Sci_EnableRx()</tt> shall raise the development error
 *    <tt>SCI_E_INVALID_CHANNEL</tt> if the channel parameter is invalid or the
 *    channel is inactive.
 *  - the function <tt>Sci_EnableRx()</tt> shall raise the development error
 *    <tt>SCI_E_STATE_TRANSITION</tt> if the SCI channel state-machine is in the
 *    state <tt>SCI_CH_SLEEP</tt>.
 */
Std_ReturnType Sci_EnableRx(
  Sci_ChannelType	Channel
);

#endif	/* SCI_H */
