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

/** @file	Port.h
 *  @brief	AUTOSAR PORT Driver Header File.
 *
 *  <b>PORT001:</b> The PORT Driver module shall initialize the whole port 
 *  structure of the microcontroller.
 *
 *  @note Defining the order in which the ports and port pins are configured is
 *  the task of the configuration tool.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */


#ifndef	AR_PORT_H
#define	AR_PORT_H

/** @brief	Vendor Id
 *
 * Vendor Id form document:
 * [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 * http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	PORT_VENDOR_ID		0

/** @brief	Module Id
 *
 * Module Id (101) from document:
 * List of Basic Software Modules
 * V1.5.0
 * R4.0 Rev 2
 */
#define	PORT_MODULE_ID		124

#define	PORT_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	PORT_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	PORT_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	PORT_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	PORT_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	PORT_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

/*
 * PORT130:	Port.h shall include Port_Cfg.h for the API pre-compiler
 * 		switches, Std_Types.h and EcuM.h
 */
#include "Std_Types.h"

/** @brief	Pin
 *
 *  <b>PORT013:</b> The type <tt>Port_PinType</tt> shall be used for the
 *  symbolic name of a Port Pin.
 *
 *  <b>PORT219:</b> The type <tt>Port_PinType</tt> shall be <tt>uint8</tt>,
 *  <tt>uint16</tt> or <tt>uint32</tt> based on the specific MCU platform.
 *
 *  @note The user shall use the symbolic names provided by the configuration
 *  tool.
 */
typedef	uint8_least	Port_PinType;

/** @brief	Pin Direction
 *
 *  <b>PORT046:</b> The type <tt>Port_PinDirectionType</tt> is a type for
 *  defining the direction of a Port Pin.
 *
 *  <b>PORT220:</b> The type <tt>Port_PinDirectionType</tt> shall be of
 *  enumeration type having range as <tt>PORT_PIN_IN</tt> and
 *  <tt>PORT_PIN_OUT</tt>.
 */
typedef enum
{
  PORT_PIN_IN	=	STD_OFF,	/**< Sets port pin as input.	      */
  PORT_PIN_OUT	=	STD_ON		/**< Sets port pin as output.	      */
} Port_PinDirectionType;

/** @brief	Pin Level */
typedef enum {
  PORT_PIN_LEVEL_HIGH	=	STD_HIGH,	/**< Port Pin level is High.  */
  PORT_PIN_LEVEL_LOW	=	STD_LOW		/**< Port Pin level is Low.   */
} Port_PinLevelType;

/** @brief	Pin Mode
 *
 *  <b>PORT124:</b> A port pin shall be configurable with a number of port pin
 *  modes (type <tt>Port_PinModeType</tt>).
 *
 *  <b>PORT212:</b> The type <tt>Port_PinModeType</tt> shall be used with the
 *  function call <tt>Port_SetPinMode()</tt>.
 *
 *  <b>PORT221:</b> The type <tt>Port_PinModeType</tt> shall be <tt>uint8</tt>,
 *  <tt>uint16</tt> or <tt>uint32</tt>.
 */
typedef	uint8_least	Port_PinModeType;

/*
 * PORT130:	Port.h shall include Port_Cfg.h for the API pre-compiler
 * 		switches, Std_Types.h and EcuM.h
 */
#include "Port_Cfg.h"

/** @brief	PORT Driver Configuration Parameters
 *
 *  <b>PORT073:</b> The type <tt>Port_ConfigType</tt> is a type for the external
 *  data structure containing the initialization data for the PORT Driver.
 *
 *  @note The user shall use the symbolic names defined in the configuration
 *  tool.
 *
 *  @note The configuration of each port pin is MCU specific. Therefore, it is
 *  not possible to include a complete list of different configurations in this
 *  specification.
 *
 *  <b>PORT072:</b> A list of possible port configurations for the structure
 *  <tt>Port_ConfigType</tt> is given below:
 *  - Pin mode (e.g. DIO, ADC, SPI...): this port pin configuration is mandatory
 *  unless the port pin is configured for DIO.
 *  - Pin direction (input, output): this port pin configuration is mandatory
 *  when the port pin is to be used for DIO.
 *  - Pin level init value (see <b>PORT055</b>): this port pin configuration is
 *  mandatory when the port pin is used for DIO.
 *  - Pin direction changeable during runtime
 *  (<tt>STD_ON</tt>/<tt>STD_OFF</tt>): this port pin configuration is MCU
 *  dependent.
 *  - Pin mode changeable during runtime (<tt>STD_ON</tt>/<tt>STD_OFF</tt>):
 *  configuration is MCU dependent.
 *
 *  Optional parameters (if supported by hardware):
 *  - Slew rate control.
 *  - Activation of internal pull-ups.
 *  - Microcontroller specific port pin properties.
 */
extern	const Port_ConfigType	Port_Config[];

/** @brief  Default PORT Configuration Pointer
 *
 *  Pointer to Default PORT Driver Configuration.
 */
#define PORT_CONFIG_PTR &Port_Config[0]


/*
 * PORT051:	The following errors and exceptions shall be detectable by the
 * 		PORT driver depending on its build version
 * 		(development/production).
 */
#if ( PORT_DEV_ERROR_DETECT == STD_ON )
/** Invalid Port Pin ID requested					      */
#define	PORT_E_PARAM_PIN		0x0A
/** Port Pin not configured as changeable				      */
#define	PORT_E_DIRECTION_UNCHANGEABLE	0x0B
/** API <tt>Port_Init()</tt> service called with wrong parameter	      */
#define	PORT_E_PARAM_CONFIG		0x0C
/** Port Pin Mode passed Not Valid					      */
#define	PORT_E_PARAM_INVALID_MODE	0x0D
/** API <tt>Port_SetPinMode()</tt> service called when mode is unchangeable   */
#define	PORT_E_MODE_UNCHANGEABLE	0x0E
/** API service called without module initialization			      */
#define	PORT_E_UNINIT			0x0F
/** APIs called with a <tt>NULL</tt> Pointer				      */
#define	PORT_E_PARAM_POINTER		0x10
#endif

/*
 * Service ID's
 */
#if ( PORT_DEV_ERROR_DETECT == STD_ON )
#define	PORT_INIT_SERVICE_ID			0x00
#define	PORT_SET_PIN_DIRECTION_SERVICE_ID	0x01
#define	PORT_REFRESH_PORT_DIRECTION_SERVICE_ID	0x02
#define	PORT_GET_VERSION_INFO_SERVICE_ID	0x03
#define	PORT_SET_PIN_MODE_SERVICE_ID		0x04
#endif

/** @brief	Port Driver Initialization
 *  @param	ConfigPtr	Pointer to configuration set
 *  @return	None
 *
 *  Initializes the Port Driver module.
 
 *  <b>PORT140:</b> Service 0x00
 *
 *  <b>PORT041:</b> The function <tt>Port_Init()</tt> shall initialize ALL ports
 *  and port pins with the configuration set pointed to by the parameter
 *  <tt>>ConfigPtr</tt>.
 *
 *  <b>PORT078:</b> The Port Driver module's environment shall call the function
 *  <tt>Port_Init()</tt> first in order to initialize the port for use.
 *
 *  <b>PORT213:</b> If <tt>Port_Init()</tt> function is not called first, then
 *  no operation can occur on the MCU ports and port pins.
 *
 *  <b>PORT042:</b> The function <tt>Port_Init()</tt> shall initialize all
 *  configured resources.
 *
 *  The function <tt>Port_Init()</tt> shall apply the following rules regarding
 *  initialisation of controller registers.
 *
 *  - <b>PORT113:</b> If the hardware allows for only one usage of the register,
 *  the driver module implementing that functionality is responsible for
 *  initializing the register.
 *
 *  - <b>PORT214:</b> If the register can affect several hardware modules and if
 *  it is an I/O register it shall be initialised by this PORT driver.
 *
 *  - <b>PORT215:</b> If the register can affect several hardware modules and if
 *  it is not an I/O register, it shall be initialised by the MCU driver.
 *
 *  - <b>PORT217:</b> One-time writable registers that require initialisation
 *  directly after reset shall be initialised by the startup code.
 *
 *  - <b>PORT218:</b> All the other registers not mentioned before, shall be
 *  initialised by the start-up code.
 *
 *  <b>PORT043:</b> The function <tt>Port_Init()</tt> shall avoid glitches and
 *  spikes on the affected port pins.
 *
 *  <b>PORT071:</b> The Port Driver module's environment shall call the function
 *  <tt>Port_Init()</tt> after a reset in order to reconfigure the ports and
 *  port pins of the MCU.
 *
 *  <b>PORT002:</b> The function <tt>Port_Init()</tt> shall initialize all
 *  variables used by the PORT driver module to an initial state.
 *
 *  <b>PORT003:</b> The Port Driver module's environment may also uses the
 *  function <tt>Port_Init()</tt> to initialize the driver software and
 *  reinitialize the ports and port pins to another configured state depending
 *  on the configuration set passed to this function.
 *
 *  @note In some cases, MCU port control hardware provides an output latch for
 *  setting the output level on a port pin that may be used as a DIO port pin.
 *
 *  <b>PORT055:</b> The function <tt>Port_Init()</tt> shall set the port pin
 *  output latch to a default level (defined during configuration) before
 *  setting the port pin direction to output.
 *
 *  Requirement <b>PORT055</b> ensures that the default level is immediately
 *  output on the port pin when it is set to an output port pin.
 *
 *  <b>Example:</b> On some MCU's, after a power-on-reset, a DIO configurable
 *  port pin will be configured as an input pin. If the required configuration
 *  of the port pin is an output pin, then the function Port_Init shall ensure
 *  that the default level is set before switching the functionality of the port
 *  pin from input to output.
 *
 *  <b>PORT105:</b> If development error detection for the Port Driver module is
 *  enabled: In case the function <tt>Port_Init()</tt> is called with a
 *  <tt>NULL</tt> <tt>ConfigPtr</tt> and if a variant containing postbuild
 *  multiple selectable configuration parameters is used
 *  (<tt>VARIANT-POSTBUILD</tt>), the function <tt>Port_Init()</tt> shall raise
 *  the development error <tt>PORT_E_PARAM_CONFIG</tt> and return without any
 *  action.
 *
 *  <b>PORT121:</b> The function <tt>Port_Init()</tt> shall always have a
 *  pointer as a parameter, even though for the configuration variant
 *  <tt>VARIANT-PRE-COMPILE</tt>, no configuration set shall be given. In this
 *  case, the Port Driver module's environment shall pass a <tt>NULL</tt>
 *  pointer to the function <tt>Port_Init()</tt>.
 *
 *  The Port Driver module's environment shall not call the function
 *  <tt>Port_Init()</tt> during a running operation. This shall only apply if
 *  there is more than one caller of the PORT module.
 *
 *  Configuration of <tt>Port_Init()</tt>: All port pins and their functions,
 +  and alternate functions shall be configured by the configuration tool.
 */
void Port_Init(
  const Port_ConfigType*	ConfigPtr
);

#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
/** @brief	Pin Direction Setting
 *  @param	Pin		Port Pin ID number
 *  @param	Direction	Port Pin Direction
 *  @return	None
 *
 *  Sets the port pin direction
 *
 *  <b>PORT141:</b> Service 0x01
 *
 *  <b>PORT063:</b> The function <tt>Port_SetPinDirection()</tt> shall set the
 *  port pin direction during runtime.
 *
 *  <b>PORT054:</b> The function <tt>Port_SetPinDirection()</tt> shall be
 *  re-entrant if accessing different pins independent of a port.
 *
 *  <b>PORT086:</b> The function <tt>Port_SetPinDirection()</tt> shall only be
 *  available to the user if the pre-compile parameter
 *  <tt>PortSetPinDirectionApi</tt> is set to <tt>TRUE</tt>. If set to
 *  <tt>FALSE</tt>, the function <tt>Port_SetPinDirection()</tt> is not
 *  available.
 *
 *  Configuration of <tt>Port_SetPinDirection()</tt>: All ports and port pins
 *  shall be configured by the configuration tool.
 */
void Port_SetPinDirection(
  Port_PinType		Pin,
  Port_PinDirectionType	Direction
);
#endif

/** @brief	Port Directorion Refreshing
 *  @return	None
 *
 *  Refreshes port direction.
 *
 *  <b>PORT142:</b> Service 0x02
 *
 *  <b>PORT060:</b> The function <tt>Port_RefreshPortDirection()</tt> shall
 *  refresh the direction of all configured ports to the configured direction
 *  (<tt>PortPinDirection</tt>).
 *
 *  <b>PORT061:</b> The function <tt>Port_RefreshPortDirection()</tt> shall
 *  exclude those port pins from refreshing that are configured as 'pin
 *  direction changeable during runtime'.
 *
 *  The configuration tool shall provide names for each configured port pin.
 */
void Port_RefreshPortDirection(
  void
);

#if ( PORT_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval
 *  @param	_vi	Pointer to where to store the version information of
 *  			this module.
 *  @return	None
 *
 *  Returns the version information of this module.
 *
 *  <b>PORT143:</b> Service 0x03
 *
 *  <b>PORT102:</b> The function <tt>Port_GetVersionInfo()</tt> shall return the
 *  version information of this module. The version information includes:
 *  - Module Id
 *  - Vendor Id
 *  - Vendor specific version numbers.
 *
 *  <b>PORT103:</b> The function <tt>Port_GetVersionInfo()</tt> shall be pre
 *  compile time configurable On/Off by the configuration parameter
 *  <tt>PortVersionInfoApi</tt>.
 *
 *  <b>PORT144:</b> If source code for caller and callee of
 *  <tt>Port_GetVersionInfo()</tt> is available, the PORT Driver module should
 *  realize <tt>Port_GetVersionInfo()</tt> as a macro, defined in the module's
 *  header file.
 *
 *  <b>PORT225:</b> if Det is enabled, the parameter versioninfo shall be
 *  checked for being <tt>NULL</tt>. The error <tt>PORT_E_PARAM_POINTER</tt>
 *  shall be reported in case the value is a <tt>NULL</tt> pointer.
 */
#if ( PORT_DEV_ERROR_DETECT == STD_ON )
#define	Port_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,PORT) \
	else \
	{\
		Det_ReportError(\
			PORT_MODULE_ID,\
			0,\
			PORT_GET_VERSION_INFO_SERVICE_ID,\
			PORT_E_PARAM_POINTER\
		);\
	}
#else
#define	Port_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,PORT)
#endif	/* PORT_DEV_ERROR_DETECT */
#endif	/* PORT_VERSION_INFO_API */

#if ( PORT_SET_PIN_MODE_API == STD_ON )
/** @brief	Pin Mode Setting
 *  @param	Pin	Port Pin ID number
 *  @param	Mode	New Port Pin mode to be set on port pin.
 *  @return	None
 *
 *  Sets the port pin mode.
 *
 *  <b>PORT145:</b> Service 0x04
 *
 *  <b>PORT125:</b> The function <tt>Port_SetPinMode()</tt> shall set the port
 *  pin mode of the referenced pin during runtime.
 *
 *  <b>PORT128:</b> The function <tt>Port_SetPinMode()</tt> shall be re-entrant
 *  if accessing different pins, independent of a port.
 *
 *  <b>PORT223:</b> If Det is enabled, the function <tt>Port_SetPinMode()</tt>
 *  shall return <tt>PORT_E_MODE_UNCHANGEABLE</tt> and return without any
 *  action, if the parameter <tt>PortPinModeChangeable</tt> is set to
 *  <tt>FALSE</tt>.
 *
 *  Configuration of <tt>Port_SetPinMode()</tt>: All ports and port pins shall be
 *  configured by the configuration tool.
 */
void Port_SetPinMode(
  Port_PinType		Pin,
  Port_PinModeType	Mode
);
#endif

#endif	/* AR_PORT_H */
