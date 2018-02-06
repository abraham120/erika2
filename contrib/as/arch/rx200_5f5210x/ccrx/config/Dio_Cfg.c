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

/*
 * fake-druid AUTOSAR DIO Driver Configuration Source File.
 *
 *  Configured for (MCU): Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2012
 */


#define	DIO_AR_RELEASE_MAJOR_VERSION	4
#define	DIO_AR_RELEASE_MINOR_VERSION	0

#include "Dio.h"

/*
 * DIO106:	The DIO module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files.
 * 		The imported included files shall be checked by preprocessing
 * 		directives.
 * 		The following version numbers shall be verified:
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		Where <MODULENAME> is the module short name of the other
 * 		(external) modules which provide header files included by DIO
 * 		module.
 * 		If the values are not identical to the expected values, an
 * 		error shall be reported.
 */
#if !defined( DIO_AR_MAJOR_VERSION ) || \
    ( DIO_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION )
#error	Dio: version mismatch.
#endif

/*
 * DIO146_Conf:	Configuration of an individual DIO channel. Besides a HW
 * 		specific channel name which is typically fixed for a specific
 * 		micro controller, additional symbolic names can be defined per
 * 		channel. Note hat this container definition does not explicitly
 * 		define a symbolic name parameter. Instead, the container's
 * 		short name will be used in the Ecu Configuration Description to
 * 		specify the symbolic name of the channel.
 */
const Dio_ChannelType	DioPort1Channels[] = {
	DIO_CHANNEL_USER_LED_0,
	DIO_CHANNEL_USER_LED_1,
	DIO_CHANNEL_USER_LED_2,
	DIO_CHANNEL_USER_LED_3
  
};

const Dio_ChannelType	DioPort3Channels[] = {
	DIO_CHANNEL_USER_SWITCH_1,
	DIO_CHANNEL_USER_SWITCH_2,
	DIO_CHANNEL_USER_SWITCH_3
};

const Dio_ChannelType	DioPortEChannels[] = {
	DIO_CHANNEL_USER_OUTPUT
};



/*
 * DIO149_Conf:	The DIO channel group is identified in DIO API by a
 * 		pointer to a data structure (of type Dio_ChannelGroupType).
 * 		That data structure contains the channel group information.
 * 		This parameter contains the code fragment that has to be
 * 		inserted in the API call of the calling module to get the
 * 		address of the variable in memory which holds the channel group
 * 		information. Example values are "&MyDioGroup1" or
 * 		"&MyDioGroupArray[0]"
 */

const Dio_ChannelGroupType DioPort1ChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_USER_LEDS */
    0x000000F0,			/* mask				 */
    0x00000004,			/* offest			 */
    DIO_PORT_USER_LEDS	/* port				 */
  }
};

const Dio_ChannelGroupType DioPort3ChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_USER_SWITCHES */
    0x0000001A,			/* mask				 */
    0x00000001,			/* offest			 */
    DIO_PORT_USER_SWITCHES	/* port				 */
  }
};

const Dio_ChannelGroupType DioPortEChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_USER_OUTPUT */
    0x00000001,			/* mask				 */
    0x00000000,			/* offest			 */
    DIO_PORT_USER_OUTPUT /* port				 */
  }
};


/*
 * DIO144_Conf:	Configuration of individual DIO ports, consisting of channels
 * 		and possible channel groups. Note that this container definition
 * 		does not explicitly define a symbolic name parameter. Instead,
 * 		the container's short name will be used in the Ecu Configuration
 * 		Description to specify the symbolic name of the port.
 */
const Dio_PortConfType Dio_Ports[] = {
  { /* PORT 1 */
    DIO_PORT_USER_LEDS,		/* DioPortId					*/
    0x00000004,				/* DioNumberOfChannels			*/
    &DioPort1Channels[0],	/* Dio_Channels					*/
    0x00000001,				/* DioNumberOfChannelsGroups	*/
    &DioPort1ChannelsGroups[0]	/* Dio_ChannelsGroups		*/
  },
  { /* PORT_3 */
    DIO_PORT_USER_SWITCHES,	/* DioPortId			 		*/
    0x00000003,				/* DioNumberOfChannels			*/
    &DioPort3Channels[0],	/* Dio_Channels			 		*/
    0x00000001,				/* DioNumberOfChannelsGroups	*/
    &DioPort3ChannelsGroups[0]	/* Dio_ChannelsGroups		*/
  }
};

const Dio_PortConfType Dio_OutputPorts[] = {
  { /* PORT_E */
    DIO_PORT_USER_OUTPUT,	/* DioPortId					*/
    0x00000001,			/* DioNumberOfChannels				*/
    &DioPortEChannels[0],	/* Dio_Channels					*/
    0x00000001,			/* DioNumberOfChannelsGroups		*/
    &DioPortEChannelsGroups[0]	/* Dio_ChannelsGroups		*/
  },
  { /* PORT 1 */
    DIO_PORT_USER_LEDS,		/* DioPortId			 		*/
    0x00000004,			/* DioNumberOfChannels		 		*/
    &DioPort1Channels[0],	/* Dio_Channels			 		*/
    0x00000001,			/* DioNumberOfChannelsGroups	 	*/
    &DioPort1ChannelsGroups[0]	/* Dio_ChannelsGroups		*/
  }
};


/*
 * DIO152_Conf:	This container contains the configuration parameters and sub
 * 		containers of the AUTOSAR DIO module. This container is a
 * 		MultipleConfigurationContainer, i.e. this container and its
 * 		sub-containers exist once per configuration set.
 */
const Dio_ConfigType Dio_Config[] = {
  { /* DIO_CONFIG_DIO */
    0x00000002,		/* DioNumberOfPorts	*/
    &Dio_Ports[0]	/* DioPorts			*/
  },
  { /* DIO_CONFIG_USER_LEDS */
    0x00000001,		/* DioNumberOfPorts	*/
    &Dio_Ports[0]	/* DioPorts			*/
  },
  { /* DIO_CONFIG_USER_OUTPUT */
    0x00000002,		/* DioNumberOfPorts	*/
    &Dio_OutputPorts[0]	/* DioPorts		*/
  }
};
