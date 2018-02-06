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

/** @file	Dio.h
 *  @brief	AUTOSAR DIO Driver Header File.
 *
 *  The DIO Driver abstracts the access to the microcontroller's hardware pins.
 *  Furthermore, it allows the grouping of those pins.
 *
 *  The Dio SWS shall define synchronous read/write services.
 *
 *  <b>DIO005:</b> The Dio module's read and write services shall ensure for all
 *  services, that the data is consistent (Interruptible read-modify-write
 *  sequences are not allowed).
 *
 *  <b>DIO089:</b> Values used by the DIO Driver for the software level of
 *  Channels are either <tt>STD_HIGH</tt> or <tt>STD_LOW</tt>.
 *
 *  <b>DIO128:</b> A general-purpose digital IO pin represents a DIO channel.
 *
 *  <b>DIO061:</b> The Dio module shall not provide APIs for overall
 *  configuration and initialization of the port structure which is used in the
 *  Dio module. These actions are done by the PORT Driver Module.
 *
 *  <b>DIO063:</b> The Dio module shall adapt its configuration and usage to the
 *  microcontroller and ECU.
 *
 *  <b>DIO001:</b> The Dio module shall not provide an interface for
 *  initialization of the hardware. The Port Driver performs this.
 *
 *  <b>DIO002:</b> The PORT driver shall provide the reconfiguration of the port
 *  pin direction during runtime.
 *
 *  <b>DIO102:</b> The Dio module's user shall only use the Dio functions after
 *  the Port Driver has been initialized. Otherwise the Dio module will exhibit
 *  undefined behavior.
 *
 *  <b>DIO127:</b> The Port module shall configure a DIO channel as input or
 *  output.
 *
 *  <b>DIO053:</b> In the DIO Driver, it shall be possible to group several DIO
 *  channels by hardware (typically controlled by one hardware register) to
 *  represent a DIO port.
 *
 *  @note The single DIO channel levels inside a DIO port represent a bit in the
 *  DIO port value, depending on their position inside the port.
 *
 *  <b>DIO056:</b> A channel group is a formal logical combination of several
 *  adjoining DIO channels within a DIO port.
 *
 *  <b>DIO051:</b> The Dio module shall not buffer data when providing read and
 *  write services.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */


#ifndef	DIO_H
#define	DIO_H

/** @brief	Vendor Id
 *
 * Vendor Id form document:
 * [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 * http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	DIO_VENDOR_ID		0

/** @brief	Module Id
 *
 * Module Id (101) from document:
 * List of Basic Software Modules
 * V1.5.0
 * R4.0 Rev 2
 */
#define	DIO_MODULE_ID		120

#define	DIO_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	DIO_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	DIO_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	DIO_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	DIO_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	DIO_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

/*
 * DIO170:	Dio.h shall include Std_Types.h.
 */
#include "Std_Types.h"

/** @brief	Channel
 *
 *  <b>DIO182:</b> <tt>Dio_ChannelType</tt>
 *
 *  <b>DIO015:</b> Parameters of type <tt>Dio_ChannelType</tt> contain the
 *  numeric ID of a DIO channel.
 *
 *  <b>DIO180:</b> The mapping of the ID is implementation specific but not
 *  configurable.
 *
 *  <b>DIO017:</b> For parameter values of type <tt>Dio_ChannelType</tt>, the
 *  Dio's user shall use the symbolic names provided by the configuration
 *  description.
 *
 *  Furthermore, <b>DIO103</b> applies to the type <tt>Dio_ChannelType</tt>.
 */
typedef	uint32	Dio_ChannelType;

/** @brief	Port
 *
 *  <b>DIO183:</b> <tt>Dio_PortType</tt>
 *
 *  <b>DIO018:</b> Parameters of type <tt>Dio_PortType</tt> contain the numeric
 *  ID of a DIO port.
 *
 *  <b>DIO181:</b> The mapping of ID is implementation specific but not
 *  configurable.
 *
 *  <b>DIO020:</b> For parameter values of type <tt>Dio_PortType</tt>, the user
 *  shall use the symbolic names provided by the configuration description.
 *
 *  Furthermore, <b>DIO103</b> applies to the type <tt>Dio_PortType</tt>.
 */
typedef	uint32	Dio_PortType;

/** @brief	Channel Group
 *
 *  <b>DIO184:</b> <tt>Dio_ChannelGroupType</tt>
 *
 *  <b>DIO021:</b> <tt>Dio_ChannelGroupType</tt> is the type for the definition
 *  of a channel group, which consists of several adjoining channels within a
 *  port.
 *
 *  <b>DIO022:</b> For parameter values of type <tt>Dio_ChannelGroupType</tt>,
 *  the user shall use the symbolic names provided by the configuration
 *  description.
 *
 *  Furthermore, <b>DIO056</b> applies to the type <tt>Dio_ChannelGroupType</tt>.
 */
typedef struct
{

  /** @brief	Mask
   *
   *  This element mask which defines the positions of the channel group.
   */
  uint32	mask;

  /** @brief	Offset
   *
   *  This element shall be the position of the Channel Group on the port,
   *  counted from the LSB.
   */
  uint8		offset;

  /** @brief	Port
   *
   *  This shall be the port on which the Channel group is defined.
   */
  Dio_PortType	port;

} Dio_ChannelGroupType;

/** @brief	Level
 *
 *  <b>DIO185:</b> <tt>Dio_LevelType</tt>
 *
 *  <b>DIO023:</b> <tt>Dio_LevelType</tt> is the type for the possible levels
 *  that a DIO channel can have (input or output).
 */
typedef	uint8	Dio_LevelType;

/** @brief	Port Level
 *
 *  <b>DIO186:</b> <tt>Dio_PortLevelType</tt>
 *
 *  <b>DIO024:</b> <tt>Dio_PortLevelType</tt> is the type for the value of a
 *  DIO port.
 *
 *  Furthermore, <b>DIO103</b> applies to the type <tt>Dio_PortLevelType</tt>.
 *
 *  @note If the uC owns ports of different port widths (e.g. 4, 8,16...Bit)
 *  <tt>Dio_PortLevelType</tt> inherits the size of the largest port.
 */
typedef	uint32	Dio_PortLevelType;

/*
 * DIO168:	Dio.h shall include Dio_Cfg.h for the API pre-compiler switches.
 *
 * DIO169:	Dio.c has access to the Dio_Cfg.h via the implicitly include
 * 		through the Dio.h file.
 */
#include "Dio_Cfg.h"

/** @brief	DIO Driver Configuration Parameters
 *
 *  <b>DIO187:</b> <tt>Dio_ConfigType</tt>
 *
 *  <b>DIO164:</b> <tt>Dio_ConfigType</tt> is the type for all post-build
 *  configurable parameters of the DIO driver.
 */
extern const Dio_ConfigType Dio_Config[];

/*
 * DIO065:	The Dio module shall detect the following errors and exceptions
 * 		depending on its build version (development/production mode).
 */
#if ( DIO_DEV_ERROR_DETECT == STD_ON )
/**
 * <b>DIO175:</b> Invalid channel name requested
 */
#define	DIO_E_PARAM_INVALID_CHANNEL_ID	0x0A

/**
 * <b>DIO176:</b> API service called with "<tt>NULL</tt> pointer" parameter
 */
#define	DIO_E_PARAM_CONFIG		0x10

/**
 * <b>DIO177:</b> Invalid port name requested
 */
#define	DIO_E_PARAM_INVALID_PORT_ID	0x14

/**
 * <b>DIO178:</b> Invalid ChannelGroup passed
 */
#define	DIO_E_PARAM_INVALID_GROUP	0x1F

/**
 * <b>DIO188:</b> API service called with a <tt>NULL</tt> pointer. In case of
 * this error, the API service shall return immediately without any further
 * action, beside reporting this development error.
 */
#define	DIO_E_PARAM_POINTER		0x20
#endif

/*
 * Service ID's
 */
#if ( DIO_DEV_ERROR_DETECT == STD_ON )
#define	DIO_READCHANNEL_ID		0x00
#define	DIO_WRITECHANNEL_ID		0x01
#define	DIO_READPORT_ID			0x02
#define	DIO_WRITEPORT_ID		0x03
#define	DIO_READCHANNELGROUP_ID		0x04
#define	DIO_WRITECHANNELGROUP_ID	0x05
#define	DIO_INIT_ID			0x10
#define	DIO_FLIPCHANNEL_ID		0x11
#define	DIO_GETVERSIONINFO_ID		0x12
#endif

/** @brief	Channel Read
 *  @param	ChannelId	ID of DIO channel
 *  @return	
 *  	- <tt>STD_HIGH</tt>: The physical level of the corresponding Pin is
 *  <tt>STD_HIGH</tt>
 *  	- <tt>STD_LOW</tt>: The physical level of the corresponding Pin is
 *  <tt>STD_LOW</tt>
 *
 *  Returns the value of the specified DIO channel.
 *
 *  <b>DIO133:</b> Service 0x00
 *
 *  <b>DIO027:</b> The <tt>Dio_ReadChannel()</tt> function shall return the
 *  value of the specified DIO channel.
 *
 *  Regarding the return value of the <tt>Dio_ReadChannel</tt> function, the
 *  requirements <b>DIO083</b> and <b>DIO084</b> are applicable.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO118</b> and <b>DIO026</b>
 *  are applicable to the <tt>Dio_ReadChannel()</tt> function.
 */
Dio_LevelType Dio_ReadChannel(
  Dio_ChannelType	ChannelId
);

/** @brief	Channel Write
 *  @param	ChannelId	ID of DIO channel
 *  @param	Level		Value to be written
 *  @return	Nono
 *
 *  Service to set a level of a channel.
 *
 *  <b>DIO134:</b> Service	0x01
 *
 *  <b>DIO028:</b> If the specified channel is configured as an output channel,
 *  the <tt>Dio_WriteChannel()</tt> function shall set the specified Level for
 *  the specified channel.
 *
 *  <b>DIO029:</b> If the specified channel is configured as an input channel,
 *  the <tt>Dio_WriteChannel()</tt> function shall have no influence on the
 *  physical output.
 *
 *  <b>DIO079:</b> If the specified channel is configured as an input channel,
 *  the <tt>Dio_WriteChannel()</tt> function shall have no influence on the
 *  result of the next Read-Service.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO119</b> and <b>DIO026</b>
 *  are applicable to the <tt>Dio_WriteChannel()</tt> function.
 */
void Dio_WriteChannel(
  Dio_ChannelType	ChannelId,
  Dio_LevelType		Level
);

/** @brief	Port Read
 *  @param	PortId	ID of DIO Port
 *  @return	Level of all channels of that port
 *
 *  Returns the level of all channels of that port.
 *
 *  <b>DIO135:</b> Service 0x02
 *
 *  <b>DIO031:</b> The <tt>Dio_ReadPort()</tt> function shall return the level
 *  of all channels of that port.
 *
 *  <b>DIO104:</b> When reading a port which is smaller than the
 *  <tt>Dio_PortType</tt> using the <tt>Dio_ReadPort()</tt> function (see
 *  <b>DIO103</b>), the function shall set the bits corresponding to undefined
 *  port pins to <tt>0</tt>.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO118</b> and <b>DIO026</b>
 *  are applicable to the <tt>Dio_ReadPort()</tt> function.
 */
Dio_PortLevelType Dio_ReadPort(
  Dio_PortType		PortId
);

/** @brief	Port Write
 *  @param	PortId	ID of DIO Port
 *  @param	Level	Value to be written
 *  @return	None
 *
 *  Service to set a value of the port.
 *
 *  <b>DIO136:</b> Service 0x03
 *
 *  <b>DIO034:</b> The <tt>Dio_WritePort()</tt> function shall set the specified
 *  value for the specified port.
 *
 *  <b>DIO035:</b> When the <tt>Dio_WritePort()</tt> function is called, DIO
 *  Channels that are configured as input shall remain unchanged.
 *
 *  <b>DIO105:</b> When writing a port which is smaller than the
 *  <tt>Dio_PortType</tt> using the <tt>Dio_WritePort()</tt> function (see
 *  <b>DIO103</b>), the function shall ignore the MSB.
 *
 *  <b>DIO108:</b> The <tt>Dio_WritePort()</tt> function shall have no effect on
 *  channels within this port which are configured as input channels.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO119</b> and <b>DIO026</b>
 *  are applicable to the <tt>Dio_WritePort()</tt> function.
 */
void Dio_WritePort(
  Dio_PortType		PortId,
  Dio_PortLevelType	Level
);

/** @brief	Channel Group Read
 *  @param	ChannelGroupIdPtr	Pointer to ChannelGroup Parameters
 *  @return	Level of a subset of the adjoining bits of a port
 *
 *  This Service reads a subset of the adjoining bits of a port.
 *
 *  <b>DIO137:</b> Service 0x04
 *
 *  <b>DIO037:</b> The <tt>Dio_ReadChannelGroup()</tt> function shall read a
 *  subset of the adjoining bits of a port (channel group).
 *
 *  <b>DIO092:</b> The <tt>Dio_ReadChannelGroup()</tt> function shall do the
 *  masking of the channel group.
 *
 *  <b>DIO093:</b> The <tt>Dio_ReadChannelGroup()</tt> function shall do the
 *  shifting so that the values read by the function are aligned to the LSB.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO056</b>, <b>DIO083</b>,
 *  <b>DIO084</b>, <b>DIO118</b> and <b>DIO026</b> are applicable to the
 *  <tt>Dio_ReadChannelGroup()</tt> function.
 */
Dio_PortLevelType Dio_ReadChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr
);

/** @brief	Channel Group Write
 *  @param	ChannelGroupIdPtr	Pointer to ChannelGroup
 *  @param	Level			Value to be written
 *  @return	None
 *
 *  Service to set a subset of the adjoining bits of a port to a specified level.
 *
 *  <b>DIO138:</b> Service 0x05
 *
 *  <b>DIO039:</b> The <tt>Dio_WriteChannelGroup()</tt> function shall set a
 *  subset of the adjoining bits of a port (channel group) to a specified level.
 *
 *  <b>DIO040:</b> The <tt>Dio_WriteChannelGroup()</tt> shall not change the
 *  remaining channels of the port and channels which are configured as input.
 *
 *  <b>DIO090:</b> The <tt>Dio_WriteChannelGroup()</tt> function shall do the
 *  masking of the channel group.
 *
 *  <b>DIO091:</b> The function <tt>Dio_WriteChannelGroup()</tt> shall do the
 *  shifting so that the values written by the function are aligned to the LSB.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO056</b>, <b>DIO119</b>
 *  and <b>DIO026</b> are applicable for the <tt>Dio_WriteChannelGroup()</tt>
 * function.
 */
void Dio_WriteChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr,
  Dio_PortLevelType		Level
);

/** @brief	Dio Driver Initialization
 *  @param	ConfigPtr	Pointer to post-build configuration data
 *  				Parameters None
 *  @return	None
 *
 *  Initializes the module.
 *
 *  <b>DIO165:</b> Service 0x10
 *
 *  <b>DIO166:</b> The <tt>Dio_Init()</tt> function shall initialize all global
 *  variables of the DIO module.
 *
 *  <b>DIO167:</b> When development error detection is enabled for the DIO
 *  module: The function <tt>Dio_Init()</tt> shall check that the parameter
 *  <tt>ConfigPtr</tt> is not <tt>NULL</tt>. If this error is detected, the
 *  function <tt>Dio_Init()</tt> shall not execute the initialization but raise
 *  the development error <tt>DIO_E_PARAM_CONFIG</tt>.
 */
void Dio_Init(
  const Dio_ConfigType*		ConfigPtr
);

#if ( DIO_FLIP_CHANNEL_API == STD_ON )
/** @brief	Channel Flip
 *  @param	ChannelId	ID of DIO channel
 *  @return	
 *  - <tt>STD_HIGH</tt>: The physical level of the corresponding Pin is
 *  <tt>STD_HIGH</tt>.
 *  - <tt>STD_LOW</tt>: The physical level of the corresponding Pin is
 *  <tt>STD_LOW</tt>.
 *
 *  Service to flip (change from <tt>1</tt> to <tt>0</tt> or from <tt>0</tt> to
 *  <tt>1</tt>) the level of a channel and return the level of the channel after
 *  flip.
 *
 *  <b>DIO190:</b> Service 0x11
 *
 *  <b>DIO191:</b> If the specified channel is configured as an output channel,
 *  the <tt>Dio_FlipChannel()</tt> function shall read level of the channel
 *  (requirements <b>DIO083</b> & <b>DIO084</b> are applicable) and invert it,
 *  then write the inverted level to the channel. The return value shall be the
 *  inverted level of the specified channel.
 *
 *  <b>DIO192:</b> If the specified channel is configured as an input channel,
 *  the <b>Dio_FlipChannel()</b> function shall have no influence on the
 *  physical output. The return value shall be the level of the specified
 *  channel.
 *
 *  <b>DIO193:</b> If the specified channel is configured as an input channel,
 *  the <tt>Dio_FlipChannel()</tt> function shall have no influence on the
 *  result of the next Read-Service.
 *
 *  Furthermore, the requirements <b>DIO005</b>, <b>DIO119</b> and <b>DIO026</b>
 *  are applicable to the <tt>Dio_FlipChannel()</tt> function.
 */
Dio_LevelType Dio_FlipChannel(
  Dio_ChannelType		ChannelId
);
#endif

#if ( DIO_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval
 *  @param	_vi	Pointer to where to store the version information of
 *  			this module.
 *  @return	None
 *
 *  Service to get the version information of this module.
 *
 *  <b>DIO139:</b> Service 0x12
 *
 *  <b>DIO123:</b> The <tt>Dio_GetVersionInfo()</tt> function shall return the
 *  version information of this module. The version information includes:
 *  - Module Id
 *  - Vendor Id
 *  - Vendor specific version numbers.
 *
 *  <b>DIO126:</b> If source code for caller and callee is available, the module
 *  Dio should realize the function <tt>Dio_GetVersionInfo()</tt> as a macro
 *  defined in the module's header file.
 *
 *  <b>DIO124:</b> The <tt>Dio_GetVersionInfo()</tt> function shall be
 *  pre-compile time configurable (On/Off) by the configuration parameter
 *  <tt>DioVersionInfoApi</tt>.
 *
 *  <b>DIO189:</b> If DET is enabled for the DIO Driver module, the function
 *  <tt>Dio_GetVersionInfo()</tt> shall raise <tt>DIO_E_PARAM_POINTER</tt>, if
 *  the argument is <tt>NULL</tt> pointer and return without any action.
 */
#if ( DIO_DEV_ERROR_DETECT == STD_ON )
#define	Dio_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,DIO) \
	else \
	{\
		Det_ReportError(\
			DIO_MODULE_ID,\
			0,\
			DIO_GETVERSIONINFO_ID,\
			DIO_E_PARAM_POINTER\
		);\
	}
#else
#define	Dio_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,DIO)
#endif	/* DIO_DEV_ERROR_DETECT */
#endif	/* DIO_VERSION_INFO_API */

#endif	/* DIO_H */
