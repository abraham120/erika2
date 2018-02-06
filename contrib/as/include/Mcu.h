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

/** @file	Mcu.h
 *  @brief	AUTOSAR MCU Driver Header File.
 *
 *  The MCU driver provides MCU services for Clock and RAM initialization.
 *  In the MCU configuration set, the MCU specific settings for the Clock
 *  (i.e. PLL setting) and RAM (i.e. section base address and size) shall be
 *  configured.
 *
 *  <b>MCU055:</b> The MCU module shall provide a service to provide software
 *  triggering of a hardware reset.
 *
 *  @note Only an authorized user shall be able to call this reset service
 *  function.
 *
 *  <b>MCU052:</b> The MCU module shall provide services to get the reset reason
 *  of the last reset if the hardware supports such a feature.
 *
 *  @note In an ECU, there are several sources which can cause a reset.
 *  Depending on the reset reason, several application scenarios might be
 *  necessary after reinitialization of the MCU.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */


#ifndef	MCU_H
#define	MCU_H

/** @brief	Vendor Id
 *
 *  Vendor Id from document:
 *  [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 *  http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	MCU_VENDOR_ID		0

/** @brief	Module Id
 *
 *  Module Id (101) from document:
 *  List of Basic Software Modules
 *  V1.5.0
 *  R4.0 Rev 2
 */
#define	MCU_MODULE_ID		101

#define	MCU_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	MCU_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	MCU_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	MCU_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	MCU_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	MCU_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

#include "Std_Types.h"

/** @brief	Clock Type
 *
 *  <b>MCU232:</b> The type Mcu_ClockType defines the identification (ID) for
 *  clock setting configured via the configuration structure.
 *
 *  <b>MCU233:</b> The type shall be uint8, uint16 or uint32, depending on uC
 *  platform.
 */
typedef	uint8_least	Mcu_ClockType;

/** @brief	PLL Status Type
 *
 *  <b>MCU230:</b> The type <tt>Mcu_PllStatusType</tt> is the type of the return
 *  value of the function <tt>Mcu_GetPllStatus()</tt>.
 *
 *  <b>MCU231:</b> The type of <tt>Mcu_PllStatusType</tt> is an enumeration with
 *  the following values: <tt>MCU_PLL_LOCKED</tt>, <tt>MCU_PLL_UNLOCKED</tt>,
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt>.
 */
typedef enum {
  MCU_PLL_LOCKED,		/**< PLL is locked.	    */
  MCU_PLL_UNLOCKED,		/**< PLL is unlocked.	    */
  MCU_PLL_STATUS_UNDEFINED,	/**< PLL Status is unknown. */
} Mcu_PllStatusType;

/** @brief	Reset Type
 *
 *  <b>MCU234:</b> This type represents the different reset that a specified MCU
 *  can have.
 *
 *  <b>MCU 134:</b> The MCU module shall provide at least the values
 *  <tt>MCU_POWER_ON_RESET</tt> and <tt>MCU_RESET_UNDEFINED</tt>.
 *
 *  @note	Additional reset types may be added depending on MCU.
 */
typedef enum {
  MCU_POWER_ON_RESET,	/**< Power On Reset (default)	   */
  MCU_WATCHDOG_RESET,	/**< Internal Watchdog Timer Reset */
  MCU_SW_RESET,		/**< Software Reset		   */
  MCU_RESET_UNDEFINED	/**< Reset is undefined		   */
} Mcu_ResetType;

/** @brief	Mode Type
 *
 *  <b>MCU237:</b> The <tt>Mcu_ModeType</tt> specifies the identification (ID)
 *  for a MCU mode, configured via configuration structure.
 *
 *  <b>MCU238:</b> The type shall be <tt>uint8</tt>, <tt>uint16</tt> or
 *  <tt>uint32</tt>.
 */
typedef	uint8_least	Mcu_ModeType;

/** @brief	Ram Section Type
 *
 *  <b>MCU239:</b> The <tt>Mcu_RamSectionType</tt> specifies the identification
 *  (ID) for a RAM section, configured via the configuration structure.
 *
 *  <b>MCU240:</b> The type shall be <tt>uint8</tt>, <tt>uint16</tt> or
 *  <tt>uint32</tt>, based on best performance.
 */
typedef uint8_least	Mcu_RamSectionType;

/** @brief	Ram State Type
 *
 *  This is the Ram State data type returned by the function
 *  <tt>Mcu_GetRamState()</tt> of the Mcu module. It is not required that all
 *  RAM state types are supported by the hardware.
 */
#if ( MCU_GET_RAM_STATE_API == STD_ON )
typedef enum {
  MCU_RAMSTATE_INVALID,	/**< Ram content is not valid or unknown (default) */
  MCU_RAMSTATE_VALID	/**< Ram content is valid.			   */
} Mcu_RamStateType;
#endif

/*
 * MCU211:	Mcu.h shall include Mcu_Cfg.h for the API pre-compiler switches.

 * 		Mcu.c has access to the Mcu_Cfg.h via the implicitly included
 * 		Mcu.h file.
 */
#include "Mcu_Cfg.h"

/** @brief	MCU Driver Configuration Parameters
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
extern const Mcu_ConfigType Mcu_Config[];

/*
 * MCU012:	The following errors and exceptions shall be detectable by the
 * 		MCU module depending on its build version
 * 		(development/production mode)
 */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define	MCU_E_PARAM_CONFIG	0x0A	/**< Parameter ConfigPtr is NULL_PTR. */
#define	MCU_E_PARAM_CLOCK	0x0B	/**< Parameter ClockSetting Invalid.  */
#define	MCU_E_PARAM_MODE	0x0C	/**< Parameter McuMode Invalid.	      */
#define	MCU_E_PARAM_RAMSECTION	0x0D	/**< Parameter RamSection Invalid.    */
#define	MCU_E_PLL_NOT_LOCKED	0x0E	/**< PLL Detected and Not Locked.     */
#define	MCU_E_UNINIT		0x0F	/**< MCU Module Not Initialized.      */
#define	MCU_E_PARAM_POINTER	0x10	/**< Parameter _vi is NULL_PTR.	      */
#endif

/*
 * Service ID's
 */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define	MCU_INIT_SERVICE_ID			0x00
#define	MCU_INITRAMSECTION_SERVICE_ID		0x01
#define	MCU_INITCLOCK_SERVICE_ID		0x02
#define	MCU_DISTRIBUTEPLLCLOCK_SERVICE_ID	0x03
#define	MCU_GETPLLSTATUS_SERVICE_ID		0x04
#define	MCU_GETRESETREASON_SERVICE_ID		0x05
#define	MCU_GETRESETRAWVALUE_SERVICE_ID		0x06
#define	MCU_PERFORMRESET_SERVICE_ID		0x07
#define	MCU_SETMODE_SERVICE_ID			0x08
#define	MCU_GETVERSIONINFO_SERVICE_ID		0x09
#define	MCU_GETRAMSTATE_SERVICE_ID		0x0A
#define	MCU_LAST_SERVICE_ID		MCU_GETRAMSTATE_SERVICE_ID
#endif

/** @brief	MCU Driver Initialization
 *  @param	ConfigPtr	Pointer to MCU driver configuration set.
 *  @return	None
 *
 *  This service initializes the MCU driver.
 *
 *  <b>MCU153:</b> Service 0x00
 *
 *  <b>MCU026:</b> The function Mcu_Init shall initialize the MCU module, i.e.
 *  make the configuration settings for power down, clock and RAM sections
 *  visible within the MCU module.
 *
 *  @note After the execution of the function <tt>Mcu_Init()</tt>, the
 *  configuration data are accessible and can be used by the MCU module
 *  functions as, e.g., <tt>Mcu_InitRamSection()</tt>.
 *
 *  The MCU module's implementer shall apply the following rules regarding
 *  initialization of controller registers within the function Mcu_Init:
 *  	- <b>MCU116:</b> If the hardware allows for only one usage of the
 *  			register, the driver module implementing that
 *  			functionality is responsible for initializing the
 *  			register.
 *  	- <b>MCU244:</b> If the register can affect several hardware modules and
 *  			if it is an I/O register, it shall be initialised by the
 *  			PORT driver.
 *  	- <b>MCU245:</b> If the register can affect several hardware modules and
 *  			if it is not an I/O register, it shall be initialised by
 *  			this MCU driver.
 *  	- <b>MCU246:</b> One-time writable registers that require initialisation
 *  			directly after reset shall be initialised by the
 *  			startup code.
 *  	- <b>MCU247:</b> All other registers not mentioned before shall be
 *  			initialised by the start-up code.
 *
 *  <b>MCU127:</b> If not applicable, the MCU module's environment shall pass a
 *  <tt>NULL</tt> pointer to the function Mcu_Init. In this case the check for
 *  this <tt>NULL</tt> pointer has to be omitted.
 *
 *  @note The term 'Hardware Module' refers to internal modules of the MCU and
 *  not to a BSW module.
 */
void Mcu_Init(
  const Mcu_ConfigType * ConfigPtr
);

/** @brief	Ram Section Initialization.
 *  @param	RamSection	Selects RAM memory section provided in
 *  				configuration set
 *  @return	
 * 		- <tt>E_OK</tt>:	command has been accepted
 *  		- <tt>E_NOT_OK</tt>:	command has not been accepted e.g. due
 *  					to parameter error
 *
 *  This service initializes the RAM section wise.
 *
 *  <b>MCU154:</b> Service 0x01
 *
 *  <b>MCU011:</b> The function <tt>Mcu_InitRamSection()</tt> shall fill the
 *  memory from address <tt>McuRamSectionBaseAddress</tt> up to address
 *  <tt>McuRamSectionBaseAddress</tt> + <tt>McuRamSectionSize</tt> - 1 with the
 *  byte-value contained in <tt>McuRamDefaultValue</tt>, where
 *  <tt>McuRamSectionBaseAddress</tt>, <tt>McuRamSectionSize</tt> and
 *  <tt>McuRamDefaultValue</tt> are the values of the configuration parameters
 *  for each <tt>RamSection</tt>.
 *
 *  <b>MCU136:</b> The MCU module's environment shall call the function
 *  <tt>Mcu_InitRamSection()</tt> only after the MCU module has been initialized
 *  using the function <tt>Mcu_Init()</tt>.
 *
 *  @note NOT YET IMPLEMENTED, reason: no support for external RAM.
 */
Std_ReturnType Mcu_InitRamSection(
  Mcu_RamSectionType RamSection
);

#if ( MCU_INIT_CLOCK == STD_ON )
/** @brief	Clock Initialization
 *  @param	ClockSetting	Clock setting
 *  @return	
 *  		- <tt>E_OK</tt>:	Command has been accepted
 *  		- <tt>E_NOT_OK</tt>:	Command has not been accepted
 *
 *  This service initializes the PLL and other MCU specific clock options.
 *
 *  <b>MCU155:</b> Service 0x02
 *
 *  <b>MCU137:</b> The function <tt>Mcu_InitClock()</tt> shall initialize the
 *  PLL and other MCU specific clock options. The clock configuration parameters
 *  are provided via the configuration structure.
 *
 *  <b>MCU138:</b> The function <tt>Mcu_InitClock()</tt> shall start the PLL
 *  lock procedure (if PLL shall be initialized) and shall return without
 *  waiting until the PLL is locked.
 *
 *  <b>MCU139:</b> The MCU module's environment shall only call the function
 *  <tt>Mcu_InitClock()</tt> after the MCU module has been initialized using
 *  the function <tt>Mcu_Init()</tt>.
 *
 *  <b>MCU210:</b> The function <tt>Mcu_InitClock()</tt> shall be disabled if
 *  the parameter <tt>McuInitClock</tt> is set to <tt>FALSE</tt>. Instead this
 *  function is available if the former parameter is set to <tt>TRUE</tt>.
 */
Std_ReturnType Mcu_InitClock(
  Mcu_ClockType ClockSetting
);
#endif

#if ( MCU_NO_PLL == STD_OFF )
/** @brief	PLL Clock Distribution.
 *
 *  This service activates the PLL clock to the MCU clock distribution.
 *
 *  <b>MCU156:</b> Service 0x03
 *
 *  <b>MCU140:</b> The function <tt>Mcu_DistributePllClock()</tt> shall activate
 *  the PLL clock to the MCU clock distribution.
 *
 *  <b>MCU141:</b> The MCU module's environment shall execute the function
 *  <tt>Mcu_DistributePllClock()</tt> if the MCU module needs a separate
 *  request to activate the PLL clock after the PLL is locked. In this case, the
 *  function shall remove the current clock source (for example internal
 *  oscillator clock) from MCU clock distribution.
 *
 *  <b>MCU056:</b> The function <tt>Mcu_DistributePllClock()</tt> shall return
 *  without affecting the MCU hardware if the PLL clock has been automatically
 *  activated by the MCU hardware.
 *
 *  <b>MCU142:</b> The MCU module's environment shall only call the function
 *  <tt>Mcu_DistributePllClock()</tt> after the status of the PLL has been
 *  detected as locked by the function <tt>Mcu_GetPllStatus()</tt>.
 *
 *  <b>MCU205:</b> The function <tt>Mcu_DistributePllClock()</tt> shall be
 *  available if the pre-compile parameter <tt>McuNoPll</tt> is set to
 *  <tt>FALSE</tt>. Otherwise, this Api has to be disabled.
 */
void Mcu_DistributePllClock(
  void
);
#endif

/** @brief	PLL Status Retrieval.
 *  @return	PLL Status
 *
 *  This service provides the lock status of the PLL.
 *
 *  <b>MCU157:</b> Service 0x04
 *
 *  <b>MCU008:</b> The function <tt>Mcu_GetPllStatus()</tt> shall return the
 *  lock status of the PLL.
 *
 *  <b>MCU132:</b> The function <tt>Mcu_GetPllStatus()</tt> shall return
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt> if this function is called prior to
 *  calling of the function <tt>Mcu_Init()</tt>.
 *
 *  <b>MCU206:</b> The function <tt>Mcu_GetPllStatus()</tt> shall also return
 *  <tt>MCU_PLL_STATUS_UNDEFINED</tt> if the pre-compile parameter
 *  <tt>McuNoPll</tt> is set to <tt>TRUE</tt>.
 */
Mcu_PllStatusType Mcu_GetPllStatus(
  void
);

/** @brief	Reset Reason Retrieval.
 *  @return	Reset Reason.
 *
 *  The service reads the reset type from the hardware, if supported.
 *
 *  <b>MCU158:</b> Service 0x05
 *
 *  <b>MCU005:</b> The function <tt>Mcu_GetResetReason()</tt> shall read the
 *  reset reason from the hardware and return this reason if supported by the
 *  hardware. If the hardware does not support the hardware detection of the
 *  reset reason, the return value from the function
 *  <tt>Mcu_GetResetReason()</tt> shall always be <tt>MCU_POWER_ON_RESET</tt>.
 *
 *  <b>MCU133:</b> The function <tt>Mcu_GetResetReason()</tt> shall return
 *  <tt>MCU_RESET_UNDEFINED</tt> if this function is called prior to calling of
 *  the function <tt>Mcu_Init()</tt>, and if supported by the hardware.
 *
 *  @note The User should ensure that the reset reason is cleared once it has
 *  been read out to avoid multiple reset reasons.
 */
Mcu_ResetType Mcu_GetResetReason(
  void 
);

/** @brief	Reset Raw Value Retrieval.
 *  @return	Reset raw value
 *
 *  The service reads the reset type from the hardware register, if supported.
 *
 *  <b>MCU159:</b> Service 0x06
 *
 *  <b>MCU135:</b> The function <tt>Mcu_GetResetRawValue()</tt> shall return an
 *  implementation specific value which does not correspond to a valid value of
 *  the reset status register and is not equal to 0 if this function is called
 *  prior to calling of the function <tt>Mcu_Init()</tt>, and if supported by
 *  the hardware.
 *
 *  <b>MCU006:</b> The function <tt>Mcu_GetResetRawValue()</tt> shall read the
 *  reset raw value from the hardware register if the hardware supports this. If
 *  the hardware does not have a reset status register, the return value
 *  shall be <tt>0x0</tt>.
 *
 *  @note The User should ensure that the reset reason is cleared once it has
 *  been read out to avoid multiple reset reasons.
 */
Mcu_RawResetType Mcu_GetResetRawValue(
  void
);

#if ( MCU_PERFORM_RESET_API == STD_ON )
/** @brief	Microcontroller Reset.
 *  @return	None.
 *
 *  The service performs a microcontroller reset.
 *
 *  <b>MCU160:</b> Service 0x07
 *
 *  <b>MCU143:</b> The function <tt>Mcu_PerformReset()</tt> shall perform a
 *  microcontroller reset by using the hardware feature of the microcontroller.
 *
 *  <b>MCU144:</b> The function <tt>Mcu_PerformReset()</tt> shall perform the
 *  reset type which is configured in the configuration set.
 *
 *  <b>MCU145:</b> The MCU module's environment shall only call the function
 *  <tt>Mcu_PerformReset</tt> after the MCU module has been initialized by
 *  the function Mcu_Init.
 *
 *  <b>MCU146:</b> The function <tt>Mcu_PerformReset()</tt> is only available if
 *  the runtime parameter <tt>McuPerformResetApi</tt> is set to <tt>TRUE</tt>.
 *  If set to <tt>FALSE</tt>, the function <tt>Mcu_PerformReset()</tt> is not
 *  applicable.
 */
void Mcu_PerformReset(
  void
);
#endif

/** @brief	Mode Setting.
 *  @param	McuMode	Set different MCU power modes configured in the
 *  		configuration set
 *
 *  This service activates the MCU power modes.
 *
 *  <b>MCU161:</b> Service 0x08
 *
 *  <b>MCU147:</b> The function <tt>Mcu_SetMode()</tt> shall set the MCU power
 *  mode. In case of CPU power down mode, the function <tt>Mcu_SetMode()</tt>
 *  returns after it has performed a wake-up.
 *
 *  <b>MCU148:</b> The MCU module's environment shall only call the function
 *  <tt>Mcu_SetMode()</tt> after the MCU module has been initialized by the
 *  function <tt>Mcu_Init()</tt>.
 *
 *  @note NOT YET IMPLEMENTED, reason: operational mode only.
 */
void Mcu_SetMode(
  Mcu_ModeType McuMode
);

#if ( MCU_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval.
 *  @param	_vi	Pointer to where to store the version
 *  		information of this module.
 *
 *  This service returns the version information of this module.
 *
 *  <b>MCU162:</b> Service 0x09
 *
 *  <b>MCU103:</b> The function <tt>Mcu_GetVersionInfo()</tt> shall return the
 *  version information of the MCU module. The version information includes:
 *  - Module Id
 *  - Vendor Id
 *  - Vendor specific version numbers (BSW00407)
 *
 *  <b>MCU104:</b> The function <tt>Mcu_GetVersionInfo()</tt> shall be
 *  pre-compile time configurable On/Off by the configuration parameter
 *  <tt>McuVersionInfoApi</tt>.
 *
 *  <b>MCU149:</b> If source code for caller and callee of the function
 *  <tt>Mcu_GetVersionInfo()</tt> is available, the MCU module should realize
 *  this function as a macro. The MCU module should define this macro in the
 *  module's header file.
 *
 *  <b>MCU204:</b> if development error detection is enabled, the parameter
 *  versioninfo shall be checked for being <tt>NULL</tt>. The error
 *  <tt>MCU_E_PARAM_POINTER</tt> shall be reported in case the value is a
 *  <tt>NULL</tt> pointer. (TODO)
 */

#if ( MCU_DEV_ERROR_DETECT == STD_ON )
#define	Mcu_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,MCU) \
	else \
	{\
		Det_ReportError(\
			MCU_MODULE_ID,\
			0,\
			MCU_GETVERSIONINFO_SERVICE_ID,\
			MCU_E_PARAM_POINTER\
		);\
	}
#else
#define	Mcu_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,MCU)
#endif	/* MCU_DEV_ERROR_DETECT */
#endif	/* MCU_VERSION_INFO_API */

#if ( MCU_GET_RAM_STATE_API == STD_ON )
/** @brief	Ram State Retrieval.
 *  @return	Status of the Ram Content
 *
 *  This service provides the actual status of the microcontroller Ram.
 *  (if supported)
 *
 *  <b>MCU207:</b> Service 0x0A
 *
 *  @note Some microcontrollers offer the functionality to check if the Ram
 *  Status is valid after a reset. The function <tt>Mcu_GetRamState()</tt>
 *  can be used for this reason.
 *
 *  <b>MCU208:</b> The MCU module's environment shall call this function only if
 *  the MCU module has been already initialized using the function
 *  <tt>MCU_Init()</tt>.
 *
 *  <b>MCU209:</b> The function <tt>Mcu_GetRamState()</tt> shall be available
 *  to the user if the precompile parameter <tt>McuGetRamStateApi</tt> is set to
 *  <tt>TRUE</tt>. Instead, if the former parameter is set to <tt>FALSE</tt>,
 *  this function shall be disabled (e.g. the hardware does not support this
 *  functionality).
 *
 *  @note NOT YET IMPLEMENTED, reason: no support for external RAM.
 */
Mcu_RamStateType Mcu_GetRamState(
  void
);
#endif

#endif	/* MCU_H */
