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

/** @file	Spi.h
 *  @brief	AUTOSAR SPI Handler/Driver Header File.
 *
 *  The SPI handler/driver is part of the microcontroller abstraction layer
 *  (MCAL). It provides services for reading from and writing to devices
 *  connected via SPI busses. It also provides the required mechanism to
 *  configure the onchip SPI peripheral.
 *
 *  <b>SPI239</b>:	SPI peripherals may depend on the system clock,
 *  			prescaler(s) and PLL. Thus, changes of the system clock
 *  			(e.g. PLL on -> PLL off) may also affect the clock
 *  			settings of the SPI hardware.
 *
 *  <b>SPI244</b>:	The SPI Handler/Driver module does not take care of
 *  			setting the registers which configure the clock,
 *  			prescaler(s) and PLL in its init function. This has to
 *  			be done by the MCU module 0.
 *
 *  <b>SPI342</b>:	Depending on microcontrollers, the SPI peripheral could
 *  			share registers with other peripherals. In this typical
 *  			case, the SPI Handler/Driver has a relationship with MCU
 *  			module 0 for initialising and de-initialising those
 *  			registers.
 *
 *  <b>SPI343</b>:	If Chip Selects are done using microcontroller pins the
 *  			SPI Handler/Driver has a relationship with PORT module.
 *  			In this case, this specification assumes that these
 *  			microcontroller pins are directly accessed by the SPI
 *  			Handler/Driver module without using APIs of DIO module.
 *  			Anyhow, the SPI depends on ECU hardware design and for
 *  			that reason it may depend on other modules.
 *
 *  <b>SPI363</b>:	Each variable that shall be accessible by AUTOSAR
 *  			Debugging, shall be defined as global variable.
 *
 *  <b>SPI364</b>:	All type definitions of variables which shall be
 *  			debugged, shall be accessible by the header file
 *  			<tt>Spi.h</tt>.
 *
 *  <b>SPI365</b>:	The declaration of variables in the header file shall be
 *  			such, that it is possible to calculate the size of the
 *  			variables by C-"sizeof".
 *
 *  <b>SPI366</b>:	Variables available for debugging shall be described in
 *  			the respective Basic Software Module Description
 *
 *  <b>SPI367</b>:	The states <tt>SPI_UNINIT</tt>, <tt>SPI_IDLE</tt>,
 *  			<tt>SPI_BUSY</tt> shall be available for debugging.
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#ifndef	SPI_H
#define	SPI_H

/** @brief	Vendor Id
 *
 *  Vendor Id from document:
 *  [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 *  http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	SPI_VENDOR_ID		0

/** @brief	Module Id
 *
 *  Module Id (083) from document:
 *  List of Basic Software Modules
 *  V1.5.0
 *  R4.0 Rev 2
 */
#define	SPI_MODULE_ID		83

#define	SPI_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	SPI_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	SPI_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	SPI_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	SPI_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	SPI_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

/*
 * SPI272:	Spi.h shall include Std_Types.h.
 */
#include "Std_Types.h"

/* 
 * SPI370:	It shall be possible to define if the Chip Select handling is
 * 		managed autonomously by the HW peripheral, without explicit chip
 * 		select control by the driver, or the SPI driver shall drive the
 * 		chip select lines explicitly as DIO (see SPI212_Conf).
 */
#include "Dio.h"

/** @brief	SPI Handler/Driver Channel Type.
 *
 *  <b>SPI356</b>:	The type <tt>Spi_ChannelType</tt> specifies the
 *  			identification (ID) for a Channel.
 *
 *  <b>SPI166</b>:	The type <tt>Spi_ChannelType</tt> is used for
 *  			specifying the identification (ID) for a Channel.
 */
typedef	uint8		Spi_ChannelType;

/** @brief	SPI Handler/Driver Job Type.
 *
 *  <b>SPI357</b>:	The type <tt>Spi_JobType</tt> specifies the
 *  			identification (ID) for a Job.
 *
 *  <b>SPI167</b>:	The type <tt>Spi_JobType</tt> is used for specifying the
 * 			identification (ID) for a Job.
 */
typedef	uint16		Spi_JobType;

/** @brief	SPI Handler/Driver Sequence Type.
 *
 *  <b>SPI358</b>:	The type <tt>Spi_SequenceType</tt> specifies the
 *  			identification (ID) for a Sequence.
 *
 *  <b>SPI168</b>:	The type <tt>Spi_SequenceType</tt> is used for
 *  			specifying the identification (ID) for a Sequence.
 */
typedef	uint8		Spi_SequenceType;

/** @brief	SPI Handler/Driver Hardware Unit Type.
 *
 *  <b>SPI359</b>:	The type <tt>Spi_HWUnitType</tt> specifies the
 *  			identification (ID) for a SPI Hardware microcontroller
 *  			peripheral (unit).
 *
 *  <b>SPI169</b>:	The type <tt>Spi_HWUnitType</tt> is used for specifying
 *  			the identification (ID) for a SPI Hardware
 *  			microcontroller peripheral (unit).
 */
typedef	uint8		Spi_HWUnitType;

/** @brief	SPI Handler/Driver Number of Data Type
 *
 *  <b>SPI165</b>:	The type <tt>Spi_NumberOfDataType</tt> is used for
 *  			defining the number of data elements of the type
 *  			<tt>Spi_DataType</tt> to send and/or receive by
 *  			<tt>Channel</tt>.
 */
typedef uint16		Spi_NumberOfDataType;

/** @brief	Job End Notification Callback Function Pointer
 *
 *  <b>SPI192</b>:	Callback routine provided by the user for each Job to
 *  			notify the caller that a job has been finished.
 *
 *  <b>SPI340</b>:	The operation <tt>Spi_JobEndNotification()</tt> is
 *  			Re-entrant.
 *
 *  <b>SPI075</b>:	The SPI Handler/Driver shall use the callback routines
 *  			<tt>Spi_JobEndNotification()</tt> to inform other
 *  			software modules about certain states or state changes.
 *
 *  <b>SPI265</b>:	For implement the call back function other modules are
 *  			required to provide the routines in the expected manner,
 *  			as function pointers defined within the initialization
 *  			data structure (<tt>Spi_ConfigType</tt>).
 *
 *  The callback notification <tt>Spi_JobEndNotification()</tt> shall have no
 *  parameters and no return value.
 *
 *  <b>SPI054</b>:	If a callback notification is configured as null
 *  			pointer, no callback shall be executed.
 *
 *  <b>SPI071</b>:	If the <tt>Spi_JobEndNotification()</tt> is configured
 *  			(i.e. not a null pointer), the SPI Handler/Driver shall
 *  			call the configured callback notification at the end of
 *  			a Job transmission.
 *
 *  @note	This routine might be called on interrupt level, depending on
 *  		the calling function.
 *
 *  <b>SPI085</b>:	It is allowed to use the following API calls within the
 *  			SPI callback notifications:
 *  			- <tt>Spi_ReadIB()</tt>
 *  			- <tt>Spi_WriteIB()</tt>
 *  			- <tt>Spi_SetupEB()</tt>
 *  			- <tt>Spi_GetJobResult()</tt>
 *  			- <tt>Spi_GetSequenceResult()</tt>
 *  			- <tt>Spi_GetHWUnitStatus()</tt>
 *  			- <tt>Spi_Cancel()</tt>
 *  			All other SPI Handler/Driver API calls are not allowed.
 */
typedef void (*Spi_JobEndNotification)(
  void
);

/** @brief	Sequence End Notification Callback Function Pointer
 *
 *  <b>SPI193</b>:	Callback routine provided by the user for each Sequence
 *  			to notify the caller that a sequence has been finished.
 *
 *  <b>SPI341</b>:	The operation <tt>Spi_SeqEndNotification()</tt> is
 *  			Re-entrant.
 *
 *  <b>SPI264</b>:	The SPI Handler/Driver shall use the callback routines
 *  			<tt>Spi_SeqEndNotification()</tt> to inform other
 *  			software modules about certain states or state changes.
 *
 *  <b>SPI265</b>:	For implement the call back function other modules are
 *  			required to provide the routines in the expected manner,
 *  			as function pointers defined within the initialization
 *  			data structure (<tt>Spi_ConfigType</tt>).
 *
 *  The callback notification <tt>Spi_SeqEndNotification()</tt> shall have no
 *  parameters and no return value.
 *
 *  <b>SPI054</b>:	If a callback notification is configured as null
 *  			pointer, no callback shall be executed.
 *
 *  <b>SPI073</b>:	If the <tt>Spi_SeqEndNotification()</tt> is configured
 *  			(i.e. not a null pointer), the SPI Handler/Driver shall
 *  			call the configured callback notification at the end of
 *  			a Sequence transmission.
 *
 *  @note	This routine might be called on interrupt level, depending on
 *  		the calling function.
 *
 *  <b>SPI085</b>:	It is allowed to use the following API calls within the
 *  			SPI callback notifications:
 *  			- <tt>Spi_ReadIB()</tt>
 *  			- <tt>Spi_WriteIB()</tt>
 *  			- <tt>Spi_SetupEB()</tt>
 *  			- <tt>Spi_GetJobResult()</tt>
 *  			- <tt>Spi_GetSequenceResult()</tt>
 *  			- <tt>Spi_GetHWUnitStatus()</tt>
 *  			- <tt>Spi_Cancel()</tt>
 *  			All other SPI Handler/Driver API calls are not allowed.
 */
typedef void (*Spi_SeqEndNotification)(
  void
);

/*
 * SPI273:	Spi.h shall include Spi_Cfg.h.
 */
#include "Spi_Cfg.h"

/*
 * SPI098:	Development error values are of type uint8.
 *
 * The following errors shall be detectable by the SPI driver depending on its
 * build version (development / production).
 *
 * SPI004:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_PARAM_CHANNEL(0x0A) when API service called with wrong
 * 		parameter.
 *
 * SPI237:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_PARAM_JOB(0x0B) when API service called with wrong
 * 		parameter.
 *
 * SPI238:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_PARAM_SEQ(0x0C) when API service called with wrong
 * 		parameter.
 *
 * SPI240:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_PARAM_LENGTH(0x0D) when API service called with wrong
 * 		parameter.
 *
 * SPI241:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_PARAM_UNIT(0x0E) when API service called with wrong
 *  		parameter.
 *
 * SPI242:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_UNINIT(0x1A) when API service used without module
 * 		initialization.
 *
 * SPI243:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_SEQ_PENDING(0x2A) when services called in a wrong
 * 		sequence.
 *
 * SPI245:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_SEQ_IN_PROCESS(0x3A) when synchronous transmission service
 * 		called at wrong time.
 *
 * SPI246:	SPI Handler/driver shall be able to detect the error
 * 		SPI_E_ALREADY_INITIALIZED(0x4A) when API SPI_Init service called
 * 		while the SPI driver has already been initialized time.
 *
 * SPI007:	Additional errors that are detected because of specific
 * 		implementation and/or specific hardware properties shall be
 * 		added to the SPI device specific implementation description.
 */
#if ( SPI_DEV_ERROR_DETECT == STD_ON )

/** Invalid Channel */
#define	SPI_E_PARAM_CHANNEL		0x0A
/** Invalid Job */
#define	SPI_E_PARAM_JOB			0x0B
/** Invalid Sequence */
#define	SPI_E_PARAM_SEQ			0x0C
/** Invalid Lenght */
#define	SPI_E_PARAM_LENGTH		0x0D
/** Invalid Unit */
#define	SPI_E_PARAM_UNIT		0x0E

/** Pointer is NULL_PTR. */
#define	SPI_E_PARAM_POINTER		0x10

/** SPI Module Not Initialized */
#define	SPI_E_UNINIT			0x1A

/** SPI Service called in a wrong Sequence */
#define	SPI_E_SEQ_PENDING		0x2A

/** SPI Service called at wrong time in a synchronous transmission */
#define	SPI_E_SEQ_IN_PROCESS		0x3A

/** SPI Module Already Initialized */
#define	SPI_E_ALREADY_INITIALIZED	0x4D

#endif

/** @brief	SPI Handler/Driver Configuration Parameters
 *
 *  <b>SPI344</b>:	The description of the type <tt>Spi_ConfigType</tt> is
 *  			implementation specific and it shall be provided for
 *  			external use.
 *
 *  <b>SPI008</b>:	The type <tt>Spi_ConfigType</tt> is an external data
 *  			structure and shall contain the initialization data for
 *  			the SPI Handler/Driver. It shall contain:
 *  			 - MCU dependent properties for SPI HW units
 *  			 - Definition of Channels
 *  			 - Definition of Jobs
 *  			 - Definition of Sequences
 *
 *  <b>SPI063</b>:	For the type <tt>Spi_ConfigType</tt>, the definition for
 *  			each Channel shall contain:
 *  			 - Buffer usage with EB/IB Channel
 *  			 - Transmit data width (1 up to 32 bits)
 *  			 - Number of data buffers for IB Channels (at least 1)
 *  			   or it is the maximum of data for EB Channels (a value
 *  			   of 0 makes no sense)
 *  			 - Transfer start LSB or MSB
 *  			 - Default transmit value
 *
 *  <b>SPI009</b>:	For the type <tt>Spi_ConfigType</tt>, the definition for
 *  			each Job shall contain:
 *  			 - Assigned SPI HW Unit
 *  			 - Assigned Chip Select pin (it is possible to assign no
 *  			   pin)
 *  			 - Chip select functionality on/off
 *  			 - Chip select pin polarity high or low
 *  			 - Baud rate
 *  			 - Timing between clock and chip select
 *  			 - Shift clock idle low or idle high
 *  			 - Data shift with leading or trailing edge
 *  			 - Priority (4 levels are available from 0, the lower to
 *  			   3, the higher)
 *  			 - Job finish end notification function
 *  			 - MCU dependent properties for the Job (only if needed)
 *  			 - Fixed link of Channels (at least one)
 *
 *  <b>SPI064</b>:	For the type <tt>Spi_ConfigType</tt>, the definition for
 *  			each Sequence shall contain:
 *  			 - Collection of Jobs (at least one)
 *  			 - Interruptible or not interruptible after each Job
 *  			 - Sequence finish end notification function
 *
 *  <b>SPI010</b>:	For the type <tt>Spi_ConfigType</tt>, the configuration
 *  			will map the Jobs to the different SPI hardware units
 *  			and the devices.
 */
extern const Spi_ConfigType	Spi_Config[];

/** @brief	SPI Handler/Driver Status Type
 *
 *  <b>SPI061</b>:	The type <tt>Spi_StatusType</tt> defines a range of
 *  			specific status for SPI Handler/Driver. It informs about
 *  			the SPI Handler/Driver status or specified SPI Hardware
 *  			microcontroller peripheral.
 *
 *  <b>SPI259</b>:	The type <tt>Spi_StatusType</tt> can be obtained calling
 *  			the API service <tt>Spi_GetStatus()</tt>.
 *
 *  <b>SPI260</b>:	The type <tt>Spi_StatusType</tt> can be obtained calling
 *  			the API service <tt>Spi_GetHWUnitStatus()</tt>.
 *
 *  <b>SPI011</b>:	After reset, the type <tt>Spi_StatusType</tt> shall have
 *  			the default value <tt>SPI_UNINIT</tt> with the numeric
 *  			value 0.
 *
 *  <b>SPI345</b>:	API service <tt>Spi_GetStatus()</tt> shall return
 *  			<tt>SPI_UNINIT</tt> when the SPI Handler/Driver is not
 *  			initialized or not usable.
 *
 *  <b>SPI346</b>:	API service <tt>Spi_GetStatus()</tt> shall return
 *  			<tt>SPI_IDLE</tt> when The SPI Handler/Driver is not
 *  			currently transmitting any Job.
 *
 *  <b>SPI347</b>:	API service <tt>Spi_GetStatus()</tt> shall return
 *  			<tt>SPI_BUSY</tt> when The SPI Handler/Driver is
 *  			performing a SPI Job transmit.
 *
 *  <b>SPI348</b>:	<tt>Spi_GetHWUnitStatus()</tt> function shall return
 *  			<tt>SPI_IDLE</tt> when The SPI Hardware microcontroller
 *  			peripheral is not currently transmitting any Job.
 *
 *  <b>SPI349</b>:	<tt>Spi_GetHWUnitStatus()</tt> function shall return
 *  			<tt>SPI_BUSY</tt> when The SPI Hardware microcontroller
 *  			peripheral is performing a SPI Job transmit.
 */
typedef enum {
  SPI_UNINIT = 0,	/**< The SPI Handler/Driver is not initialized or
  			 *   not usable.				      */
  SPI_IDLE,		/**< The SPI Handler/Driver is not currently
  			 *   transmitting any Job.			      */
  SPI_BUSY		/**< The SPI Handler/Driver is performing a SPI Job
  			 *   (transmit).				      */
} Spi_StatusType;

/** @brief	SPI Handler/Driver Job Result Type
 *
 *  <b>SPI062</b>:	The type <tt>Spi_JobResultType</tt> defines a range of
 *  			specific Jobs status for SPI Handler/Driver.
 *
 *  <b>SPI261</b>:	The type <tt>Spi_JobResultType</tt> it informs about a
 *  			SPI Handler/Driver Job status and can be obtained
 *  			calling the API service <tt>Spi_GetJobResult</tt> with
 *  			the Job ID.
 *
 *  <b>SPI012</b>:	After reset, the type <tt>Spi_JobResultType</tt> shall
 *  			have the default value <tt>SPI_JOB_OK</tt> with the
 *  			numeric value 0.
 *
 *  <b>SPI350</b>:	The function <tt>Spi_GetJobResult</tt> shall return
 *  			<tt>SPI_JOB_OK</tt> when the last transmission of the
 *  			Job has been finished successfully.
 */
typedef enum {
  SPI_JOB_OK = 0,	/**< The last transmission of the Job has been finished
  			 *   successfully.				      */
  SPI_JOB_PENDING,	/**< The SPI Handler/Driver is performing a SPI Job.
  			 *   The meaning of this status is equal to SPI_BUSY. */
  SPI_JOB_FAILED	/**< The last transmission of the Job has failed.     */
} Spi_JobResultType;

/** @brief	SPI Handler/Driver Sequence Result Type
 *
 *  <b>SPI351</b>:	The type <tt>Spi_SeqResultType</tt> defines a range of
 *  			specific Sequences status for SPI Handler/Driver and can
 *  			be obtained calling the API service
 *  			<tt>Spi_GetSequenceResult()</tt>, it shall be provided
 *  			for external use.
 *
 *  <b>SPI019</b>:	The type <tt>Spi_SeqResultType</tt> defines the range of
 *  			specific Sequences status for SPI Handler/Driver.
 *
 *  <b>SPI251</b>:	The type <tt>Spi_SeqResultType</tt> defines about SPI
 *  			Handler/Driver Sequence status and can be obtained
 *  			calling the API service <tt>Spi_GetSequenceResult()</tt>
 *  			with the Sequence ID.
 *
 *  <b>SPI017</b>:	After reset, the type <tt>Spi_SeqResultType</tt> shall
 *  			have the default value <tt>SPI_SEQ_OK</tt> with the
 *  			numeric value 0.
 *
 *  <b>SPI352</b>:	<tt>Spi_GetSequenceResult()</tt> function shall return
 *  			<tt>SPI_SEQ_OK</tt> when the last transmission of the
 *  			Sequence has been finished successfully.
 *
 *  <b>SPI353</b>:	<tt>Spi_GetSequenceResult()</tt> function shall return
 *  			<tt>SPI_SEQ_PENDING</tt> when the SPI Handler/Driver is
 *  			performing a SPI Sequence. The meaning of this status is
 *  			equal to <tt>SPI_BUSY</tt>.
 *
 *  <b>SPI354</b>:	<tt>Spi_GetSequenceResult()</tt> function shall return
 *  			<tt>SPI_SEQ_FAILED</tt> when the last transmission of
 *  			the Sequence has failed.
 */
typedef enum {
  SPI_SEQ_OK,		/**< The last transmission of the Sequence has been
  			 *   finished successfully.			      */
  SPI_SEQ_PENDING,	/**< The SPI Handler/Driver is performing a SPI
  			 *   Sequence. The meaning of this status is equal to
  			 *   <tt>SPI_BUSY</tt>.				      */
  SPI_SEQ_FAILED,	/**< The last transmission of the Sequence has
  			 *   failed.					      */
#if	( SPI_CANCEL_API == STD_ON )
  SPI_SEQ_CANCELED	/**< The last transmission of the Sequence has been
  			 *   canceled by user.				      */
#endif	/* ( SPI_CANCEL_API == STD_ON ) */
} Spi_SeqResultType;

/* SPI Handler/Driver Data Type
 *
 * SPI355</b>:	Spi_DataType defines the type of application data buffer
 *  		elements. Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 * 		it shall be provided for external use.
 *
 * SPI164</b>:	The type Spi_DataType refers to application data buffer
 * 		elements.
 *
 * This is implementation specific but not all values may be valid within the
 * type.
 *
 * This type shall be chosen in order to have the most efficient implementation
 * on a specific microcontroller platform.
 *
 * typedef uint<8,16,32> Spi_DataType; <- To be defined in Spi_Cfg.h
 */

#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
/** @brief	SPI Handler/Driver Asynchronous Mode Type
 *
 *  <b>SPI360</b>:	The type <tt>Spi_AsyncModeType</tt> specifies the
 *  			asynchronous mechanism mode for SPI buses handled
 *  			asynchronously in LEVEL 2 and obtained by the API
 *  			<tt>Spi_SetAsyncMode()</tt>.
 *
 *  @note	<b>SPI360</b> extended to LEVEL 1 too.
 *
 *  <b>SPI170</b>:	The type <tt>Spi_AsyncModeType</tt> is used for
 *  			specifying the asynchronous mechanism mode for SPI
 *  			busses handled asynchronously in LEVEL 2.
 *
 *  <b>SPI150</b>:	The type <tt>Spi_AsyncModeType</tt> is made available or
 *  			not depending on the pre-compile time parameter:
 *  			<tt>SpiLevelDelivered</tt>. This is only relevant for
 *  			LEVEL 2.
 *
 *  <b>SPI361</b>:	If API <tt>Spi_SetAsyncMode()</tt> function is called by
 *  			the parameter value <tt>SPI_POLLING_MODE</tt> then
 *  			asynchronous mechanism is ensured by polling. So
 *  			interrupts related to SPI buses handled asynchronously
 *  			are disabled.
 *
 *  <b>SPI362</b>:	If API <tt>Spi_SetAsyncMode()</tt> function is called by
 *  			the parameter value <tt>SPI_INTERRUPT_MODE</tt>
 *  			asynchronous mechanism is ensured by interrupt, so
 *  			interrupts related to SPI buses handled asynchronously
 *  			are enabled.
 */
typedef enum {
  SPI_POLLING_MODE,	/**< The asynchronous mechanism is ensured by polling,
			 *   so interrupts related to SPI busses handled
			 *   asynchronously are disabled.		      */
  SPI_INTERRUPT_MODE	/**< The asynchronous mechanism is ensured by interrupt,
			 *   so interrupts related to SPI busses handled
			 *   asynchronously are enabled.		      */
} Spi_AsyncModeType;
#endif

/*
 * Service ID's
 */
#if ( SPI_DEV_ERROR_DETECT == STD_ON )

#define	SPI_INIT_SERVICE_ID			0x00
#define	SPI_DEINIT_SERVICE_ID			0x01
#define	SPI_WRITEIB_SERVICE_ID			0x02
#define	SPI_ASYNCTRANSMIT_SERVICE_ID		0x03
#define	SPI_READIB_SERVICE_ID			0x04
#define	SPI_SETUPEB_SERVICE_ID			0x05
#define	SPI_GETSTATUS_SERVICE_ID		0x06
#define	SPI_GETJOBRESULT_SERVICE_ID		0x07
#define	SPI_GETSEQUENCERESULT_SERVICE_ID	0x08
#define	SPI_GETVERSIONINFO_SERVICE_ID		0x09
#define	SPI_SYNCTRANSMIT_SERVICE_ID		0x0A
#define	SPI_GETHWUNITSTATUS_SERVICE_ID		0x0B
#define	SPI_CANCEL_SERVICE_ID			0x0C
#define	SPI_SETASYNCMODE_SERVICE_ID		0x0D
#define	SPI_MAINFUNCTION_HANDLING_SERVICE_ID	0x10

#endif

/** @brief	SPI Handler/Driver Initialization
 *  @param	ConfigPtr	Pointer to configuration set.
 *  @return	None
 *
 *  This service initializes the SPI handler/driver.
 *
 *  <b>SPI175</b>:	Service 0x00
 *
 *  <b>SPI298</b>:	The operation <tt>Spi_Init()</tt> is Non Re-entrant.
 *
 *  <b>SPI299</b>:	The function <tt>Spi_Init()</tt> provides the service
 *  			for SPI initialization.
 *
 *  <b>SPI013</b>:	The function <tt>Spi_Init()</tt> shall initialize all
 *  			SPI relevant registers with the values of the structure
 *  			referenced by the parameter <tt>ConfigPtr</tt>.
 *
 *  <b>SPI082</b>:	The function <tt>Spi_Init()</tt> shall define default
 *  			values for required parameters of the structure
 *  			referenced by the ConfigPtr. For example: all buffer
 *  			pointers shall be initialized as a <tt>NULL</tt> value
 *  			pointer.
 *
 *  <b>SPI015</b>:	After the module initialization using the function
 *  			<tt>Spi_Init()</tt>, the SPI Handler/Driver shall set
 *  			its state to <tt>SPI_IDLE</tt>, the Sequences result to
 *  			<tt>SPI_SEQ_OK</tt> and the jobs result to
 *  			<tt>SPI_JOB_OK</tt>.
 *
 *  <b>SPI151</b>:	For LEVEL 2, the function <tt>Spi_Init()</tt> shall set
 *  			the SPI Handler/Driver asynchronous mechanism mode to
 *  			<tt>SPI_POLLING_MODE</tt> by default. Interrupts related
 *  			to SPI busses shall be disabled.
 *
 *  <b>SPI233</b>:	The calling of the routine <tt>SPI_Init()</tt> while the
 *  			SPI driver is already initialized will cause a
 *  			development error <tt>SPI_E_ALREADY_INITIALIZED</tt> and
 *  			the desired functionality shall be left without any
 *  			action.
 *
 *  If development error detection for the SPI module is enabled:
 *   - If <tt>VARIANT-POST-BUILD</tt> is supported by implementation and the
 *     parameter <tt>ConfigPtr</tt> is a <tt>NULL_PTR</tt> pointer, the function
 *     <tt>Spi_Init()</tt> shall raise the error <tt>SPI_E_PARAM_POINTER</tt>.
 *   - If <tt>VARIANT-POST-BUILD</tt> is not supported by implementation and the
 *     parameter <tt>ConfigPtr</tt> is not a <tt>NULL_PTR</tt> pointer, the
 *     function <tt>Spi_Init()</tt> shall raise the error
 *     <tt>SPI_E_PARAM_POINTER</tt>.
 *
 *  A re-initialization of a SPI Handler/Driver by executing the
 *  <tt>Spi_Init()</tt> function requires a de-initialization before by
 *  executing a <tt>Spi_DeInit()</tt>.
 */
void Spi_Init(
  const Spi_ConfigType * ConfigPtr
);

/** @brief	SPI Handler/Driver De-Initialization.
 *  @return	
 *  	- <tt>E_OK</tt>:	De-initialisation command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	De-initialisation command has not been accepted.
 *
 *  This service de-initializes the SPI handler/driver.
 *
 *  <b>SPI176</b>:	Service 0x01
 *
 *  <b>SPI300</b>:	The operation <tt>Std_ReturnType Spi_DeInit()</tt> is
 *  			Non Re-entrant.
 *
 *  <b>SPI302</b>:	When the API <tt>Spi_DeInit()</tt> has not been accepted
 *  			the return value of this function shall be
 *  			<tt>E_NOT_OK</tt>.
 *
 *  <b>SPI303</b>:	The function <tt>Spi_DeInit()</tt> provides the service
 *  			for SPI de-initialization.
 *
 *  <b>SPI021</b>:	The function <tt>Spi_DeInit()</tt> shall de-initialize
 *  			SPI Handler/Driver.
 *
 *  <b>SPI252</b>:	In case of the SPI Handler/Driver state is not
 *  			<tt>SPI_BUSY</tt>, the deInitialization function shall
 *  			put all already initialized microcontroller SPI
 *  			peripherals into the same state such as Power On Reset.
 *
 *  <b>SPI253</b>:	The function call <tt>Spi_DeInit()</tt> shall be
 *  			rejected if the status of SPI Handler/Driver is
 *  			<tt>SPI_BUSY</tt>.
 *
 *  <b>SPI022</b>:	After the module de-initialization using the function
 *  			<tt>Spi_DeInit()</tt>, the SPI Handler/Driver shall set
 *  			its state to <tt>SPI_UNINIT</tt>.
 *
 *  The SPI Handler/Driver shall have been initialized before the function
 *  <tt>Spi_DeInit()</tt> is called.
 */
Std_ReturnType Spi_DeInit(
  void
);

#if ( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
/** @brief	Internal Buffer Writing.
 *  @param	Channel		Channel ID.
 *  @param	DataBufferPtr	Pointer to source data buffer.
 *  @return	
 *  	- <tt>E_OK</tt>:	Write command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Write command has not been accepted
 *
 *  Service for writing one or more data to an IB SPI Handler/Driver Channel
 *  specified by parameter.
 *
 *  <b>SPI177</b>:	Service 0x02
 *
 *  <b>SPI304</b>:	The operation <tt>Spi_WriteIB()</tt> is Re-entrant.
 *
 *  <b>SPI305</b>:	When the API <tt>Spi_WriteIB()</tt> command has been
 *  			accepted the function returns the value <tt>E_OK</tt>.
 *
 *  <b>SPI306</b>:	When the API <tt>Spi_WriteIB()</tt> command has not been
 *  			accepted the function returns the value
 *  			<tt>E_NOT_OK</tt>.
 *
 *  <b>SPI307</b>:	The function <tt>Spi_WriteIB()</tt> provides the service
 *  			for writing one or more data to an IB SPI Handler/Driver
 *  			Channel by the respective parameter.
 *
 *  <b>SPI018</b>:	The function <tt>Spi_WriteIB()</tt> shall write one or
 *  			more data to an IB SPI Handler/Driver Channel specified
 *  			by the respective parameter.
 *
 *  <b>SPI024</b>:	The function <tt>Spi_WriteIB()</tt> shall take over the
 *  			given parameters, and save the pointed data to the
 *  			internal buffer defined with the function
 *  			<tt>Spi_Init()</tt>.
 *
 *  <b>SPI023</b>:	If the given parameter <tt>DataBufferPtr</tt> is
 *  			<tt>NULL</tt>, the function <tt>Spi_WriteIB()</tt> shall
 *  			assume that the data to be transmitted is not relevant
 *  			and the default transmit value of the given channel
 *  			shall be used instead.
 *
 *  <b>SPI137</b>:	The function <tt>Spi_WriteIB()</tt> shall be pre-compile
 *  			time configurable by the parameter
 *  			<tt>SpiChannelBuffersAllowed</tt>. This function is only
 *  			relevant for Channels with IB.
 *
 *  <b>SPI031</b>:	The API parameter Channel shall have a value within the
 *  			defined channels in the initialization data structure,
 *  			and the correct type of channel (IB or EB) has to be
 *  			used with services. Related error value:
 *  			<tt>SPI_E_PARAM_CHANNEL</tt>. Otherwise, the service is
 *  			not done and the return value shall be
 *  			<tt>E_NOT_OK</tt>.
 *
 *  <b>SPI060</b>:	The API parameter Length of data shall have a value
 *  			within the specified buffer maximum value. Related error
 *  			value: <tt>SPI_E_PARAM_LENGTH</tt>.
 *
 *  <b>SPI258</b>:	If the API parameter Length related service is not done
 *  			and the return value shall be <tt>E_NOT_OK</tt>.
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 */
Std_ReturnType Spi_WriteIB(
  Spi_ChannelType	Channel,
  const Spi_DataType *	DataBufferPtr
);
#endif

#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
/** @brief	Asynchronous Transmission.
 *  @param	Sequence	Sequence ID.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transmission command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transmission command has not been accepted
 *
 *  Service to transmit data on the SPI bus.
 *
 *  <b>SPI178</b>:	Service 0x03
 *
 *  <b>SPI308</b>:	The operation <tt>Std_ReturnType Spi_AsyncTransmit(
 *  			Spi_SequenceType Sequence()</tt> is Re-entrant.
 *
 *  <b>SPI309</b>:	When the API <tt>Spi_AsyncTransmit()</tt> command has
 *  			been accepted the function shall return the value
 *  			<tt>E_OK</tt>.
 *
 *  <b>SPI310</b>:	When the API <tt>Spi_AsyncTransmit()</tt> command has
 *  			not been accepted the function shall return the value
 *  			<tt>E_NOT_OK</tt>.
 *
 *  <b>SPI311</b>:	The function <tt>Spi_AsyncTransmit()</tt> provides
 *  			service to transmit data on the SPI bus.
 *
 *  <b>SPI020</b>:	The function <tt>Spi_AsyncTransmit()</tt> shall take
 *  			over the given parameter, initiate a transmission, set
 *  			the SPI Handler/Driver status to SPI_BUSY, set the
 *  			sequence result to <tt>SPI_SEQ_PENDING</tt> and return.
 *
 *  <b>SPI157</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is
 *  			called, the SPI Handler/Driver shall handle the Job
 *  			results. Result shall be <tt>SPI_JOB_PENDING</tt> when
 *  			the transmission of Jobs is started.
 *
 *  <b>SPI292</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is
 *  			called, the SPI Handler/Driver shall handle the Job
 *  			results. Result shall be SPI_JOB_OK when the
 *  			transmission of Jobs is success.
 *
 *  <b>SPI293</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is
 *  			called, the SPI Handler/Driver shall handle the Job
 *  			results. Result shall be SPI_JOB_FAILED when the
 *  			transmission of Jobs is failed.
 *
 *  <b>SPI081</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is called
 *  			and the requested Sequence is already in state
 *  			<tt>SPI_SEQ_PENDING</tt>, the SPI Handler/Driver shall
 *  			not take in account this new request and this function
 *  			shall return with value <tt>E_NOT_OK</tt>, in this case.
 *
 *  <b>SPI266</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is called
 *  			and the requested Sequence is already in state
 *  			<tt>SPI_SEQ_PENDING</tt> the SPI Handler/Driver shall
 *  			report the <tt>SPI_E_SEQ_PENDING</tt> error.
 *
 *  <b>SPI086</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is called
 *  			and the requested Sequence shares Jobs with another
 *  			sequence that is in the state <tt>SPI_SEQ_PENDING</tt>,
 *  			the SPI Handler/Driver shall not take into account this
 *  			new request and this function shall return the value
 *  			<tt>E_NOT_OK</tt>. In this case and according to
 *  			<b>SPI100</b>, the SPI Handler/Driver shall report the
 *  			<tt>SPI_E_SEQ_PENDING</tt> error.
 *
 *  <b>SPI035</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is used
 *  			with EB and the source data pointer has been provided as
 *  			<tt>NULL</tt> using the <tt>Spi_SetupEB()</tt> method,
 *  			the default transmit data configured for each channel
 *  			will be transmitted. (See also <b>SPI028</b>)
 *
 *  <b>SPI036</b>:	When the function <tt>Spi_AsyncTransmit()</b> is used
 *  			with EB and the destination data pointer has been
 *  			provided as <tt>NULL</tt> using the
 *  			<tt>Spi_SetupEB()</tt> method, the SPI Handler/Driver
 *  			shall ignore receiving data (See also <b>SPI030</b>)
 *
 *  <b>SPI055</b>:	When the function <tt>Spi_AsyncTransmit()</tt> is used
 *  			for a Sequence with linked Jobs, the function shall
 *  			transmit from the first Job up to the last Job in the
 *  			sequence.
 *
 *  <b>SPI057</b>:	At the end of a sequence transmission initiated by the
 *  			function <tt>Spi_AsyncTransmit()</tt> and if configured,
 *  			the SPI Handler/Driver shall invoke the sequence
 *  			notification call-back function after the last Job end
 *  			notification if this one is also configured.
 *
 *  <b>SPI133</b>:	The function <tt>Spi_AsyncTransmit()</tt> is pre-compile
 *  			time selectable by the configuration parameter
 *  			<tt>SpiLevelDelivered</tt>. This function is only
 *  			relevant for LEVEL 1 and LEVEL 2.
 *
 *  <b>SPI173</b>:	The SPI Handler/Driver’s environment shall call the
 *  			function <tt>Spi_AsyncTransmit()</tt> after a function
 *  			call of <tt>Spi_SetupEB()</tt> for EB Channels or a
 *  			function call of <tt>Spi_WriteIB()</tt> for IB Channels
 *  			but before the function call <tt>Spi_ReadIB()</tt>.
 *
 *  <b>SPI032</b>:	The API parameters Sequence and Job shall have values
 *  			within the specified range of values. Related errors
 *  			values: <tt>SPI_E_PARAM_SEQ</tt> or
 *  			<tt>SPI_E_PARAM_JOB</tt>.
 *
 *  <b>SPI254</b>:	If the Sequence and Job related service is not done and,
 *  			depending on services, either the return value shall be
 *  			<b>E_NOT_OK</b> or a failed result 
 *  			(<tt>SPI_JOB_FAILED</tt> or <tt>SPI_SEQ_FAILED</tt>).
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver’s environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 */
Std_ReturnType Spi_AsyncTransmit(
  Spi_SequenceType	Sequence
);
#endif

#if ( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
/** @brief	Internal Buffer Reading.
 *  @param	Channel		Channel ID.
 *  @param	DataBufferPtr	Pointer to destination data buffer in RAM.
 *  @return	
 *  	- <tt>E_OK</tt>:	Read command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Read command has not been accepted
 *
 *  Service for reading synchronously one or more data from an IB SPI
 *  Handler/Driver Channel specified by parameter.
 *
 *  <b>SPI179</b>:	Service 0x04
 *
 *  <b>SPI312</b>:	The operation <tt>Spi_ReadIB()</tt> is Re-entrant.
 *
 *  <b>SPI313</b>:	The function <tt>Spi_ReadIB()</tt> return values
 *  			<tt>E_OK</tt>: read command has been accepted.
 *
 *  <b>SPI314</b>:	The function <tt>Spi_ReadIB()</tt> return values
 *  			<tt>E_NOT_OK</tt>: read command has not been accepted.
 *
 *  <b>SPI315</b>:	The function <tt>Spi_ReadIB()</tt> provides the service
 *  			for reading synchronously one or more data from an IB
 *  			SPI Handler/Driver Channel specified by parameter.
 *
 *  <b>SPI016</b>:	The function <tt>Spi_ReadIB()</tt> shall read
 *  			synchronously one or more data from an IB SPI
 *  			Handler/Driver Channel specified by the respective
 *  			parameter.
 *
 *  <b>SPI027</b>:	The SPI Handler/Driver's environment shall call the
 *  			function <tt>Spi_ReadIB()</tt> after a Transmit method
 *  			call to have relevant data within IB Channel.
 *
 *  <b>SPI138</b>:	The function <tt>Spi_ReadIB()</tt> is pre-compile time
 *  			configurable by the parameter
 *  			<tt>SpiChannelBuffersAllowed</tt>. This function is only
 *  			relevant for Channels with IB.
 *
 *  <b>SPI031</b>:	The API parameter Channel shall have a value within the
 *  			defined channels in the initialization data structure,
 *  			and the correct type of channel (IB or EB) has to be
 *  			used with services. Related error value:
 *  			<tt>SPI_E_PARAM_CHANNEL</tt>. Otherwise, the service is
 *  			not done and the return value shall be
 *  			<tt>E_NOT_OK</tt>.
 *
 *  <b>SPI060</b>:	The API parameter Length of data shall have a value
 *  			within the specified buffer maximum value. Related error
 *  			value: <tt>SPI_E_PARAM_LENGTH</tt>.
 *
 *  <b>SPI258</b>:	If the API parameter Length related service is not done
 *  			and the return value shall be <tt>E_NOT_OK</tt>.
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 */
Std_ReturnType Spi_ReadIB(
  Spi_ChannelType	Channel,
  Spi_DataType *	DataBufferPtr
);
#endif

#if ( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
/** @brief	External Buffer Setting-up.
 *  @param	Channel			Channel ID.
 *  @param	SrcDataBufferPtr	Pointer to source data buffer.
 *  @param	DesDataBufferPtr	Pointer to destination data buffer in
 *  					RAM.
 *  @param	Length			Length (in bytes) of the data to be
 *  					transmitted from
 *  					<tt>SrcDataBufferPtr</tt> and/or
 *  					received from <tt>DesDataBufferPtr</tt>
 *  					- Min.:	1
 *  					- Max.:	Max of data specified at
 *  						configuration for this channel.
 *  @return	
 *  	- <tt>E_OK</tt>:	Setup command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Setup command has not been accepted
 *
 *  Service to setup the buffers and the length of data for the EB SPI
 *  Handler/Driver Channel specified.
 *
 *  <b>SPI180</b>:	Service 0x05
 *
 *  <b>SPI316</b>:	The operation <tt>Spi_SetupEB()</tt> is Re-entrant.
 *
 *  <b>SPI317</b>:	Return values of the function <tt>Spi_SetupEB()</tt> are
 *  			<tt>E_OK</tt>: Setup command has been accepted and
 *  			<tt>E_NOT_OK</tt>: Setup command has not been accepted.
 *
 *  <b>SPI318</b>:	The function <tt>Spi_SetupEB()</tt> provides the service
 *  			to setup the buffers and the length of data for the EB
 *  			SPI Handler/Driver Channel specified.
 *
 *  <b>SPI058</b>:	The function <tt>Spi_SetupEB()</tt> shall set up the
 *  			buffers and the length of data for the specific EB SPI
 *  			Handler/Driver Channel.
 *
 *  <b>SPI067</b>:	The function <tt>Spi_SetupEB()</tt> shall update the
 *  			buffer pointers and length attributes of the specified
 *  			Channel with the provided values.
 *
 *  As these attributes are persistent, they will be used for all succeeding
 *  calls to a Transmit method (for the specified Channel).
 *
 *  <b>SPI028</b>:	When the SPI Handler/Driver's environment is calling the
 *  			function <tt>Spi_SetupEB</tt> with the parameter
 *  			<tt>SrcDataBufferPtr</tt> being a <tt>NULL</tt> pointer,
 *  			the function shall transmit the default transmit value
 *  			configured for the channel after a Transmit method is
 *  			requested. (See also <b>SPI035</b>)
 *
 *  <b>SPI030</b>:	When the function <tt>Spi_SetupEB()</tt> is called with
 *  			the parameter <tt>DesDataBufferPtr</tt> being a
 *  			<tt>NULL</tt> pointer, the SPI Handler/Driver shall
 *  			ignore the received data after a Transmit method is
 *  			requested.(See also <b>SPI036</b>)
 *
 *  <b>SPI037</b>:	The SPI Handler/Driver's environment shall call the
 *  			<tt>Spi_SetupEB()</tt> function once for each Channel
 *  			with EB declared before the SPI Handler/Driver's
 *  			environment calls a Transmit method on them.
 *
 *  <b>SPI031</b>:	The API parameter Channel shall have a value within the
 *  			defined channels in the initialization data structure,
 *  			and the correct type of channel (IB or EB) has to be
 *  			used with services. Related error value:
 *  			<tt>SPI_E_PARAM_CHANNEL</tt>. Otherwise, the service is
 *  			not done and the return value shall be
 *  			<tt>E_NOT_OK</tt>.
 *
 *  <b>SPI060</b>:	The API parameter Length of data shall have a value
 *  			within the specified buffer maximum value. Related error
 *  			value: <tt>SPI_E_PARAM_LENGTH</tt>.
 *
 *  <b>SPI258</b>:	If the API parameter Length related service is not done
 *  			and the return value shall be <tt>E_NOT_OK</tt>.
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 */
Std_ReturnType Spi_SetupEB(
  Spi_ChannelType	Channel,
  const Spi_DataType *	SrcDataBufferPtr,
  Spi_DataType *	DesDataBufferPtr,
  Spi_NumberOfDataType	Length
);
#endif

/** @brief	SPI Handler/Driver Status Retrieval
 *  @return	SPI Handler/Driver software module status.
 *
 *  This service returns the SPI Handler/Driver software module status.
 *
 *  <b>SPI181</b>:	Service 0x06
 *
 *  <b>SPI319</b>:	The operation <tt>Spi_GetStatus()</tt> is Re-entrant.
 *
 *  <b>SPI320</b>:	The function <tt>Spi_GetStatus()</tt> returns the SPI
 *  			Handler/Driver software module status.
 *
 *  <b>SPI025</b>:	The function <tt>Spi_GetStatus()</tt> shall return the
 *  			SPI Handler/Driver software module status.
 */
Spi_StatusType Spi_GetStatus(
  void
);

/** @brief	Job Result Retrieval
 *  @param	Job	Job ID.
 *  @return	Last transmission result of the specified Job.
 *
 *  This service returns the last transmission result of the specified Job.
 *
 *  <b>SPI182</b>:	Service 0x07
 *
 *  <b>SPI321</b>:	The operation <tt>Spi_GetJobResult()</tt> is Re-entrant.
 *
 *  <b>SPI322</b>:	The function <tt>Spi_GetJobResult()</tt> service returns
 *  			the last transmission result of the specified Job.
 *
 *  <b>SPI026</b>:	The function <tt>Spi_GetJobResult()</tt> shall return
 *  			the last transmission result of the specified Job.
 *
 *  <b>SPI038</b>:	The SPI Handler/Driver's environment shall call the
 *  			function <tt>Spi_GetJobResult()</tt> to inquire whether
 *  			the Job transmission has succeeded (<tt>SPI_JOB_OK</tt>)
 *  			or failed (<tt>SPI_JOB_FAILED</tt>).
 *
 *  @note	Every new transmit job that has been accepted by the SPI
 *  		Handler/Driver overwrites the previous job result with
 *  		<tt>SPI_JOB_PENDING</tt>.
 *
 *  <b>SPI032</b>:	The API parameters Sequence and Job shall have values
 *  			within the specified range of values. Related errors
 *  			values: <tt>SPI_E_PARAM_SEQ</tt> or
 *  			<tt>SPI_E_PARAM_JOB</tt>.
 *
 *  <b>SPI254</b>:	If the Sequence and Job related service is not done and,
 *  			depending on services, either the return value shall be
 *  			<b>E_NOT_OK</b> or a failed result 
 *  			(<tt>SPI_JOB_FAILED</tt> or <tt>SPI_SEQ_FAILED</tt>).
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 */
Spi_JobResultType Spi_GetJobResult(
  Spi_JobType	Job
);

/** @brief	Sequence Result Retrieval.
 *  @param	Sequence	Sequence ID
 *  @return	Last transmission result of the specified Sequence.
 *
 *  This service returns the last transmission result of the specified Sequence.
 *
 *  <b>SPI183</b>:	Service 0x08
 *
 *  <b>SPI323</b>:	The operation <tt>Spi_GetSequenceResult()</tt> is
 *  			Re-entrant.
 *
 *  <b>SPI324</b>:	The function <tt>Spi_GetSequenceResult()</tt> shall
 *  			return the last transmission result of the specified
 *  			Sequence.
 *
 *  <b>SPI039</b>:	The function <tt>Spi_GetSequenceResult()</tt> shall
 *  			return the last transmission result of the specified
 *  			Sequence.
 *
 *  <b>SPI042</b>:	The SPI Handler/Driver's environment shall call the
 *  			function <tt>Spi_GetSequenceResult()</tt> to inquire
 *  			whether the full Sequence transmission has succeeded
 *  			(<tt>SPI_SEQ_OK</tt>) or failed
 *  			(<tt>SPI_SEQ_FAILED</tt>).
 *
 *  @note
 *   - Every new transmit sequence that has been accepted by the SPI
 *     Handler/Driver overwrites the previous sequence result with
 *     <tt>SPI_SEQ_PENDING</tt>.
 *   - If the SPI Handler/Driver has not been initialized before the function
 *     <tt>Spi_GetSequenceResult()</tt> is called, the return value is
 *     undefined.
 *
 *  <b>SPI032</b>:	The API parameters Sequence and Job shall have values
 *  			within the specified range of values. Related errors
 *  			values: <tt>SPI_E_PARAM_SEQ</tt> or
 *  			<tt>SPI_E_PARAM_JOB</tt>.
 *
 *  <b>SPI254</b>:	If the Sequence and Job related service is not done and,
 *  			depending on services, either the return value shall be
 *  			<b>E_NOT_OK</b> or a failed result 
 *  			(<tt>SPI_JOB_FAILED</tt> or <tt>SPI_SEQ_FAILED</tt>).
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 */
Spi_SeqResultType Spi_GetSequenceResult(
  Spi_SequenceType	Sequence
);

#if	( SPI_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval.
 *  @param	_vi	Pointer to where to store the version
 *  			information of this module.
 *
 *  This service returns the version information of this module.
 *
 *  <b>SPI325</b>:	Service 0x09
 *
 *  <b>SPI325</b>:	The operation <tt>Spi_GetVersionInfo()</tt> is Non
 *  			Re-entrant.
 *
 *  <b>SPI326</b>:	The function <tt>Spi_GetVersionInfo()</tt> service
 * 			returns the version information of this module.
 *
 *  <b>SPI101</b>:	The function <tt>Spi_GetVersionInfo()</tt> shall return
 *  			the version information of this module according to the
 *  			definition of <tt>Std_VersionInfoType</tt>.
 *
 *  <b>SPI196</b>:	If source code for caller and callee of
 *  			<tt>Spi_GetVersionInfo()</tt> is available, the SPI
 *  			Handler/Driver should realize Spi_GetVersionInfo as a
 *  			macro, defined in the module's header file.
 *
 *  <b>SPI102</b>:	The function <tt>Spi_GetVersionInfo()</tt> is pre
 * 			compile time configurable by the configuration parameter
 *  			<tt>SpiVersionInfoApi</tt>.
 *
 *  <b>SPI278</b>:	The function <tt>Spi_GetVersionInfo()</tt> is pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter <tt>SpiVersionInfoApi</tt>.
 *
 *  <b>SPI371</b>:	If Det is enabled, the parameter versioninfo shall be
 *  			checked for being <tt>NULL</tt>. The error
 *  			<tt>PORT_E_PARAM_POINTER</tt> shall be reported in case
 *  			the value is a <tt>NULL</tt> pointer.
 */
#if ( SPI_DEV_ERROR_DETECT == STD_ON )
#define	Spi_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,SPI) \
	else \
	{\
		Det_ReportError(\
			SPI_MODULE_ID,\
			0,\
			SPI_GETVERSIONINFO_SERVICE_ID,\
			SPI_E_PARAM_POINTER\
		);\
	}
#else
#define	Spi_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,SPI)
#endif	/* SPI_DEV_ERROR_DETECT */
#endif	/* SPI_VERSION_INFO_API */

#if ( ( SPI_LEVEL_DELIVERED == 0 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
/** @brief	Synchronous Transmission.
 *  @param	Sequence	Sequence ID.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transmission command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transmission command has not been accepted
 *
 *  Service to transmit data on the SPI bus.
 *
 *  <b>SPI185</b>:	Service 0x0A
 *
 *  <b>SPI327</b>:	The operation <tt>Spi_SyncTransmit()</tt> is Re-entrant.
 *
 *  <b>SPI328</b>:	Return value of the function <tt>Spi_SyncTransmit()</tt>
 *  			is <tt>E_OK</tt>: when Transmission command has been
 *  			accepted.
 *
 *  <b>SPI329</b>:	Return value of the function <tt>Spi_SyncTransmit()</tt>
 *  			is <tt>E_NOT_OK</tt>: When Transmission command has not
 *  			been accepted.
 *
 *  <b>SPI330</b>:	The function <tt>Spi_SyncTransmit()</tt> provides the
 *  			service to transmit data on the SPI bus.
 *
 *  <b>SPI134</b>:	When the function <tt>Spi_SyncTransmit()</tt> is called,
 *  			shall take over the given parameter and set the SPI
 *  			Handler/Driver status to <tt>SPI_BUSY</tt> can be
 *  			obtained calling the API service
 *  			<tt>SPI_GetStatus()</tt>.
 *
 *  <b>SPI285</b>:	When the function <tt>Spi_SyncTransmit()</tt> is called,
 *  			shall take over the given parameter and set the Sequence
 *  			status to <tt>SPI_SEQ_PENDING</tt> can be obtained
 *  			calling the API service
 *  			<tt>Spi_GetSequenceResult()</tt>.
 *
 *  <b>SPI286</b>:	When the function <tt>Spi_SyncTransmit()</tt> is called,
 *  			shall take over the given parameter and set the Job
 *  			status to <tt>SPI_JOB_PENDING</tt> can be obtained
 *  			calling the API service <tt>Spi_GetJobResult()</tt>.
 *
 *  <b>SPI135</b>:	When the function <tt>Spi_SyncTransmit()</tt> is called
 *  			while a Sequence is on transmission, the SPI
 *  			Handler/Driver shall not take into account this new
 *  			transmission request and the function shall return the
 *  			value <tt>E_NOT_OK</tt> (see <b>SPI114</b>). In this
 *  			case and according to <b>SPI100</b>, the SPI
 *  			Handler/Driver shall report the
 *  			<b>SPI_E_SEQ_IN_PROCESS</b> error.
 *
 *  <b>SPI136</b>:	The function <tt>Spi_SyncTransmit()</tt> is pre-compile
 *  			time selectable by the configuration parameter
 *  			<tt>SpiLevelDelivered</tt>. This function is only
 *  			relevant for LEVEL 0 and LEVEL 2.
 *
 *  <b>SPI173</b>:	The SPI Handler/Driver's environment shall call the
 *  			function <tt>Spi_AsyncTransmit()</tt> after a function
 *  			call of <tt>Spi_SetupEB()</tt> for EB Channels or a
 *  			function call of <tt>Spi_WriteIB()</tt> for IB Channels
 *  			but before the function call <tt>Spi_ReadIB()</tt>.
 *
 *  <b>SPI032</b>:	The API parameters Sequence and Job shall have values
 *  			within the specified range of values. Related errors
 *  			values: <tt>SPI_E_PARAM_SEQ</tt> or
 *  			<tt>SPI_E_PARAM_JOB</tt>.
 *
 *  <b>SPI254</b>:	If the Sequence and Job related service is not done and,
 *  			depending on services, either the return value shall be
 *  			<b>E_NOT_OK</b> or a failed result 
 *  			(<tt>SPI_JOB_FAILED</tt> or <tt>SPI_SEQ_FAILED</tt>).
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI256</b>:	The SPI Handler/Driver shall not process the invoked
 *  			function but, depending on the invoked function, shall
 *  			either return the value <tt>E_NOT_OK</tt> or a failed
 *  			result (<tt>SPI_JOB_FAILED</tt> or
 *  			<tt>SPI_SEQ_FAILED</tt>).
 
 */
Std_ReturnType Spi_SyncTransmit(
  Spi_SequenceType	Sequence
);
#endif

#if	( SPI_HW_STATUS_API == STD_ON )
/** @brief	SPI Hardware Unit Status Retrieval
 *  @param	HWUnit	SPI Hardware microcontroller peripheral (unit) ID.
 *  @return	Status of the specified SPI Hardware microcontroller peripheral.
 *
 *  This service returns the status of the specified SPI Hardware
 *  microcontroller peripheral.
 *
 *  <b>SPI186</b>:	Service 0x0B
 *
 *  <b>SPI331</b>:	The operation <tt>Spi_GetHWUnitStatus()</tt> is
 *  			Re-entrant.
 *
 *  <b>SPI332</b>:	The function <tt>Spi_GetHWUnitStatus()</tt> service
 *  			returns the status of the specified SPI Hardware
 *  			microcontroller peripheral.
 *
 *  <b>SPI141</b>:	The function <tt>Spi_GetHWUnitStatus()</tt> shall return
 *  			the status of the specified SPI Hardware microcontroller
 *  			peripheral.
 *
 *  <b>SPI287</b>:	The SPI Handler/Driver's environment shall call this
 *  			function to inquire whether the specified SPI Hardware
 *  			microcontroller peripheral is <tt>SPI_IDLE</tt> or
 *  			<tt>SPI_BUSY</tt>.
 *
 *  <b>SPI142</b>:	The function <tt>Spi_GetHWUnitStatus()</tt> is
 *  			pre-compile time configurable On / Off by the
 *  			configuration parameter <tt>SpiHwStatusApi</tt>.
 *
 *  If SPI Handler/Driver has not been initialized before the function
 *  <tt>Spi_GetHWUnitStatus()</tt> is called, the return value is undefined.
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 *
 *  <b>SPI143</b>:	The API parameter <tt>HWUnit</tt> shall have a value
 *  			within the specified range of values. Related error
 *  			value: <tt>SPI_E_PARAM_UNIT</tt>.
 *
 *  <b>SPI288</b>:	If HWUnit related service is not done and the return
 *  			value shall be <tt>SPI_UNINIT</tt>.
 */
Spi_StatusType Spi_GetHWUnitStatus(
  Spi_HWUnitType	HWUnit
);
#endif

#if ( SPI_CANCEL_API == STD_ON )
/** @brief	Sequence Transmission Cancellation
 *  @param	Sequence	Sequence ID.
 *  @return	None
 *
 *  This service cancels the specified on-going sequence transmission.
 *
 *  <b>SPI187</b>:	Service 0x0C
 *
 *  <b>SPI333</b>:	The operation <tt>Spi_Cancel()</tt> is Re-entrant.
 *
 *  <b>SPI334</b>:	The function <tt>Spi_Cancel()</tt> service cancels the
 *  			specified on-going sequence transmission.
 *
 *  <b>SPI144</b>:	The function <tt>Spi_Cancel()</tt> shall cancel the
 *  			specified on-going sequence transmission without
 *  			cancelling any Job transmission and set the sequence
 *  			result to <tt>SPI_SEQ_CANCELLED</tt>.
 *
 *  With other words, the <tt>Spi_Cancel()</tt> function stops a Sequence
 *  transmission after a (possible) on transmission Job ended and before a
 *  (potential) next Job transmission starts.
 *
 *  <b>SPI145</b>:	When the sequence is cancelled by the function
 *  			<tt>Spi_Cancel()</tt> and if configured, the SPI
 *  			Handler/Driver shall call the sequence notification
 *  			call-back function instead of starting a potential next
 *  			job belonging to it.
 *
 *  <b>SPI146</b>:	The function <tt>Spi_Cancel()</tt> is pre-compile time
 *  			configurable On / Off by the configuration parameter
 *  			<tt>SpiCancelApi</tt>.
 *
 *  The SPI Handler/Driver is not responsible on external devices damages or
 *  undefined state due to cancelling a sequence transmission. It is up to the
 *  SPI Handler/Driver's environment to be aware to what it is doing!
 *
 *  <b>SPI032</b>:	The API parameters Sequence and Job shall have values
 *  			within the specified range of values. Related errors
 *  			values: <tt>SPI_E_PARAM_SEQ</tt> or
 *  			<tt>SPI_E_PARAM_JOB</tt>.
 *
 *  <b>SPI046</b>:	If the SPI Handler/Driver's environment calls any API
 *  			function before initialization, an error should be
 *  			reported to the DET with the error value
 *  			<tt>SPI_E_UNINIT</tt> according to the configuration.
 */
void Spi_Cancel(
  Spi_SequenceType	Sequence
);
#endif

#if	( ( SPI_LEVEL_DELIVERED == 1 ) ||(  SPI_LEVEL_DELIVERED == 2 ) )
/** @brief	Asyncronous Mode Setting
 *  @param	Mode	New mode required.
 *  @return	
 *  	- <tt>E_OK</tt>:	Setting command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Setting command has not been accepted
 *
 *  Service to set the asynchronous mechanism mode for SPI busses handled
 *  asynchronously.
 *
 *  <b>SPI188</b>:	Service 0x0D
 *
 *  <b>SPI335</b>:	The operation <tt>Spi_SetAsyncMode()</tt> is
 *  			Non Re-entrant.
 *
 *  <b>SPI336</b>:	Return value of the function <tt>Spi_SetAsyncMode()</tt>
 *  			is <tt>E_OK</tt>: Setting command has been done.
 *
 *  <b>SPI337</b>:	Return value of the function <tt>Spi_SetAsyncMode()</tt>
 *  			is <tt>E_NOT_OK</tt>: setting command has not been
 *  			accepted.
 *
 *  <b>SPI338</b>:	The function <tt>Spi_SetAsyncMode()</tt> service to set
 *  			the asynchronous mechanism mode for SPI buses handled
 *  			asynchronously.
 *
 *  <b>SPI152</b>:	The function <tt>Spi_SetAsyncMode()</tt> according to
 *  			the given parameter shall set the asynchronous mechanism
 *  			mode for SPI channels configured to behave
 *  			asynchronously.
 *
 *  <b>SPI171</b>:	When the function <tt>Spi_SetAsyncMode()</tt> is called
 *  			in asynchronous mode while the SPI Handler/Driver status
 *  			is not SPI_IDLE, the SPI Handler/Driver shall not take
 *  			into account the function call, the mode is kept as it
 *  			is and the function returns the value <tt>E_NOT_OK</tt>.
 *
 *  <b>SPI172</b>:	When the function <tt>Spi_SetAsyncMode()</tt> is called
 *  			in synchronous mode, the SPI Handler/Driver shall accept
 *  			the function call even if the SPI Handler/Driver status
 *  			is <tt>SPI_BUSY</tt>.
 *
 *  <b>SPI154</b>:	The function <tt>Spi_SetAsyncMode()</tt> is pre-compile
 *  			time selectable by the configuration parameter
 *  			<tt>SpiLevelDelivered</tt>. This function is only
 *  			relevant for LEVEL 2.
 *
 *  @note	<b>SPI154</b> extended to LEVEL 1 too.
 */
Std_ReturnType Spi_SetAsyncMode(
  Spi_AsyncModeType	Mode
);
#endif

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
/** @brief	SPI Handler/Driver Main Function Handling.
 *  @return	None
 *
 *  <b>SPI189</b>:	Service 0x10
 *
 *  The SPI Handler/Driver module requires a scheduled function for the
 *  management of the asynchronous mode managed with polling
 *  (see <b>SPI361</b>).
 *
 *  This function shall polls the SPI interrupts linked to HW Units allocated to
 *  the transmission of SPI sequences to enable the evolution of transmission
 *  state machine.
 */
void Spi_MainFunction_Handling(
  void
);
#endif

#endif	/* SPI_H */
