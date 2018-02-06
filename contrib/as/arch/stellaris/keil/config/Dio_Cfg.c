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

/*
 * fake-druid AUTOSAR DIO Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
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
const Dio_ChannelType	DioPortGChannels[] = {
  DIO_CHANNEL_USER_LED
};

const Dio_ChannelType	DioPortMChannels[] = {
  DIO_CHANNEL_USER_SWITCH_1,
  DIO_CHANNEL_USER_SWITCH_2,
  DIO_CHANNEL_USER_SWITCH_3,
  DIO_CHANNEL_USER_SWITCH_4,
  DIO_CHANNEL_USER_SWITCH_5
};

const Dio_ChannelType	DioPortDChannels[] = {
  DIO_CHANNEL_USER_OUTPUT
};

const Dio_ChannelType	DioPortFChannels[] = {
  DIO_CHANNEL_ENC28J60_CS,
  DIO_CHANNEL_ENC28J60_RESET,
  DIO_CHANNEL_ENC28J60_INT,
  DIO_CHANNEL_ENC28J60_WOL,
  DIO_CHANNEL_ENC28J60_CLK,
};

#ifdef	__AS_CFG_DIO_ICU__
const Dio_ChannelType	DioPortDICUChannels[] = {
  DIO_CHANNEL_ICU_DUTY_CYCLE,
  DIO_CHANNEL_ICU_PERIOD_TIME
};
#endif	/* __AS_CFG_DIO_ICU__ */

#ifdef	__AS_CFG_DIO_ICU_ARISTON_TESTS__
const Dio_ChannelType	DioPortAristonTestsICUChannels[] = {
  DIO_CHANNEL_ARISTON_TESTS_ICU_LOW_TIME,
  DIO_CHANNEL_ARISTON_TESTS_ICU_HIGH_TIME,
  DIO_CHANNEL_ARISTON_TESTS_ICU_PERIOD_TIME,
  DIO_CHANNEL_ARISTON_TESTS_ICU_DUTY_CYCLE,
};
#endif	/* __AS_CFG_DIO_ICU_ARISTON_TESTS__ */
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

const Dio_ChannelGroupType DioPortGChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_USER_LED */
    0x00000004,			/* mask				 */
    0x00000002,			/* offest			 */
    DIO_PORT_USER_LED		/* port				 */
  }
};

const Dio_ChannelGroupType DioPortMChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_USER_SWITCHES */
    0x0000001F,			/* mask				 */
    0x00000000,			/* offest			 */
    DIO_PORT_USER_SWITCHES	/* port				 */
  }
};

const Dio_ChannelGroupType DioPortDChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_USER_OUTPUT */
    0x00000040,			/* mask				 */
    0x00000006,			/* offest			 */
    DIO_PORT_USER_OUTPUT	/* port				 */
  }
};

const Dio_ChannelGroupType DioPortFChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_ENC28J60 */
    0x000000F8,			/* mask				 */
    0x00000003,			/* offest			 */
    DIO_PORT_ENC28J60		/* port				 */
  }
};

#ifdef	__AS_CFG_DIO_ICU__
const Dio_ChannelGroupType DioPortDICUChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_ICU */
    0x000000C0,			/* mask				 */
    0x00000006,			/* offest			 */
    DIO_PORT_ICU		/* port				 */
  }
};
#endif	/* __AS_CFG_DIO_ICU__ */

#ifdef	__AS_CFG_DIO_ICU_ARISTON_TESTS__
const Dio_ChannelGroupType DioPortAristonTestsICUChannelsGroups[] = {
  { /* DIO_CHANNEL_GROUP_ARISTON_TESTS_ICU */
    0x000000F0,			/* mask				 */
    0x00000004,			/* offest			 */
    DIO_PORT_ARISTON_TESTS_ICU	/* port				 */
  }
};
#endif	/* __AS_CFG_DIO_ICU__ */

/*
 * DIO144_Conf:	Configuration of individual DIO ports, consisting of channels
 * 		and possible channel groups. Note that this container definition
 * 		does not explicitly define a symbolic name parameter. Instead,
 * 		the container's short name will be used in the Ecu Configuration
 * 		Description to specify the symbolic name of the port.
 */
const Dio_PortConfType Dio_Ports[] = {
  { /* PORT G */
    DIO_PORT_USER_LED,		/* DioPortId			 */
    0x00000001,			/* DioNumberOfChannels		 */
    &DioPortGChannels[0],	/* Dio_Channels			 */
    0x00000001,			/* DioNumberOfChannelsGroups	 */
    &DioPortGChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  },
  { /* PORT_M */
    DIO_PORT_USER_SWITCHES,	/* DioPortId			 */
    0x00000005,			/* DioNumberOfChannels		 */
    &DioPortMChannels[0],	/* Dio_Channels			 */
    0x00000001,			/* DioNumberOfChannelsGroups	 */
    &DioPortMChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  }
};

const Dio_PortConfType Dio_OutputPorts[] = {
  { /* PORT_D */
    DIO_PORT_USER_OUTPUT,	/* DioPortId			 */
    0x00000001,			/* DioNumberOfChannels		 */
    &DioPortDChannels[0],	/* Dio_Channels			 */
    0x00000001,			/* DioNumberOfChannelsGroups	 */
    &DioPortDChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  },
  { /* PORT G */
    DIO_PORT_USER_LED,		/* DioPortId			 */
    0x00000001,			/* DioNumberOfChannels		 */
    &DioPortGChannels[0],	/* Dio_Channels			 */
    0x00000001,			/* DioNumberOfChannelsGroups	 */
    &DioPortGChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  }
};

const Dio_PortConfType Dio_Enc28j60tPorts[] = {
  { /* PORT G */
    DIO_PORT_USER_LED,		/* DioPortId			 */
    0x00000001,			/* DioNumberOfChannels		 */
    &DioPortGChannels[0],	/* Dio_Channels			 */
    0x00000001,			/* DioNumberOfChannelsGroups	 */
    &DioPortGChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  },
  { /* PORT F */
    DIO_PORT_ENC28J60,		/* DioPortId			 */
    0x00000005,			/* DioNumberOfChannels		 */
    &DioPortFChannels[0],	/* Dio_Channels			 */
    0x00000001,			/* DioNumberOfChannelsGroups	 */
    &DioPortFChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  }

};

#ifdef	__AS_CFG_DIO_ICU__
const Dio_PortConfType Dio_ICUPorts[] = {
  { /* PORT D */
    DIO_PORT_ICU,			/* DioPortId			 */
    0x00000002,				/* DioNumberOfChannels		 */
    &DioPortDICUChannels[0],		/* Dio_Channels			 */
    0x00000001,				/* DioNumberOfChannelsGroups	 */
    &DioPortDICUChannelsGroups[0]	/* Dio_ChannelsGroups		 */
  },
  { /* PORT G */
    DIO_PORT_USER_LED,			/* DioPortId			 */
    0x00000001,				/* DioNumberOfChannels		 */
    &DioPortGChannels[0],		/* Dio_Channels			 */
    0x00000001,				/* DioNumberOfChannelsGroups	 */
    &DioPortGChannelsGroups[0]		/* Dio_ChannelsGroups		 */
  },
  { /* PORT_M */
    DIO_PORT_USER_SWITCHES,		/* DioPortId			 */
    0x00000005,				/* DioNumberOfChannels		 */
    &DioPortMChannels[0],		/* Dio_Channels			 */
    0x00000001,				/* DioNumberOfChannelsGroups	 */
    &DioPortMChannelsGroups[0]		/* Dio_ChannelsGroups		 */
  },
};
#endif	/* __AS_CFG_DIO_ICU__ */

#ifdef	__AS_CFG_DIO_ICU_ARISTON_TESTS__
const Dio_PortConfType Dio_AristonTestsICUPorts[] = {
  { /* PORT F */
    DIO_PORT_ARISTON_TESTS_ICU,			/* DioPortId		      */
    0x00000004,					/* DioNumberOfChannels	      */
    &DioPortAristonTestsICUChannels[0],		/* Dio_Channels		      */
    0x00000001,					/* DioNumberOfChannelsGroups  */
    &DioPortAristonTestsICUChannelsGroups[0]	/* Dio_ChannelsGroups	      */
  },
  { /* PORT G */
    DIO_PORT_USER_LED,			/* DioPortId			 */
    0x00000001,				/* DioNumberOfChannels		 */
    &DioPortGChannels[0],		/* Dio_Channels			 */
    0x00000001,				/* DioNumberOfChannelsGroups	 */
    &DioPortGChannelsGroups[0]		/* Dio_ChannelsGroups		 */
  },
  { /* PORT_M */
    DIO_PORT_USER_SWITCHES,		/* DioPortId			 */
    0x00000005,				/* DioNumberOfChannels		 */
    &DioPortMChannels[0],		/* Dio_Channels			 */
    0x00000001,				/* DioNumberOfChannelsGroups	 */
    &DioPortMChannelsGroups[0]		/* Dio_ChannelsGroups		 */
  },
};
#endif	/* __AS_CFG_DIO_ICU_ARISTON_TESTS__ */

/*
 * DIO152_Conf:	This container contains the configuration parameters and sub
 * 		containers of the AUTOSAR DIO module. This container is a
 * 		MultipleConfigurationContainer, i.e. this container and its
 * 		sub-containers exist once per configuration set.
 */
const Dio_ConfigType Dio_Config[] = {
  { /* DIO_CONFIG_DIO */
    0x00000002,		/* DioNumberOfPorts	*/
    &Dio_Ports[0]	/* DioPorts		*/
  },
  { /* DIO_CONFIG_USER_LED */
    0x00000001,		/* DioNumberOfPorts	*/
    &Dio_Ports[0]	/* DioPorts		*/
  },
  { /* DIO_CONFIG_USER_OUTPUT */
    0x00000002,		/* DioNumberOfPorts	*/
    &Dio_OutputPorts[0]	/* DioPorts		*/
  },
  { /* DIO_CONFIG_ENC28J60 */
    0x00000002,		/* DioNumberOfPorts	*/
    &Dio_Enc28j60tPorts[0]	/* DioPorts		*/
  },
#ifdef	__AS_CFG_DIO_ICU__
  { /* DIO_CONFIG_ICU */
    0x00000003,		/* DioNumberOfPorts	*/
    &Dio_ICUPorts[0]	/* DioPorts		*/
  },
#endif	/* __AS_CFG_DIO_ICU__ */
#ifdef	__AS_CFG_DIO_ICU_ARISTON_TESTS__
  { /* DIO_CONFIG_ARISTION_TESTS_ICU */
    0x00000003,				/* DioNumberOfPorts	*/
    &Dio_AristonTestsICUPorts[0]	/* DioPorts		*/
  },
#endif	/* __AS_CFG_DIO_ICU_ARISTON_TESTS__ */
};
