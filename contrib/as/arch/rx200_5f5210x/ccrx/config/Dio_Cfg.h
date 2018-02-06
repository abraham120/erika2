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

/** @file	Dio_Cfg.h
 *  @brief	fake-druid AUTOSAR DIO Driver Configuration Header File.
 *
 *  Configured for (MCU): Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2012
 */


#if !(\
 ((DIO_SW_MAJOR_VERSION == 1) && \
  (DIO_SW_MINOR_VERSION == 0) && \
  (DIO_SW_PATCH_VERSION == 0))\
)
#error Dio: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	DIO_CFG_H
#define	DIO_CFG_H

/*
 * DIO141_Conf:	General DIO Module configuration parameters.
 */
/* DioGeneral */

/** @brief	Development Error Detection
 *
 *  <b>DIO142_Conf:</b> Switches the Development Error Detection and
 *  Notification <tt>ON</tt> or <tt>OFF</tt>.
 */
#define	DIO_DEV_ERROR_DETECT	STD_OFF

/** @brief	Flip Channel API
 *
 *  <b>DIO153_Conf:</b> Adds / removes the service <tt>Dio_FlipChannel()</tt>
 *  from the code.
 */
#define	DIO_FLIP_CHANNEL_API	STD_ON

/** @brief	Version Informations Retrieval API
 *
 *  <b>DIO143_Conf:</b> Adds / removes the service
 *  <tt>Dio_ GetVersionInfo()</tt> from the code.
 */
#define	DIO_VERSION_INFO_API	STD_ON

/*
 * DIO026:	The configuration process for Dio module shall provide symbolic
 * 		names for each configured DIO channel, port and group.
 */ 
#define DIO_PORT0_RBITS_MASK	0b10101000	/**< PORT0 reserved bits mask */
#define	DIO_CHANNEL_0_3	0x00000003	/**< Channel 0 3 */
#define	DIO_CHANNEL_0_5	0x00000005	/**< Channel 0 5 */
#define	DIO_CHANNEL_0_7	0x00000007	/**< Channel 0 7 */

#define DIO_PORT1_RBITS_MASK	0b11111100	/**< PORT1 reserved bits mask */
#define	DIO_CHANNEL_1_2	0x0000000A	/**< Channel 1 2 */
#define	DIO_CHANNEL_1_3	0x0000000B	/**< Channel 1 3 */
#define	DIO_CHANNEL_1_4	0x0000000C	/**< Channel 1 4 */
/** Channel User Led 0*/
#define	DIO_CHANNEL_USER_LED_0	DIO_CHANNEL_1_4
#define	DIO_CHANNEL_1_5	0x0000000D	/**< Channel 1 5 */
/** Channel User Led 1*/
#define	DIO_CHANNEL_USER_LED_1	DIO_CHANNEL_1_5
#define	DIO_CHANNEL_1_6	0x0000000E	/**< Channel 1 6 */
/** Channel User Led 2*/
#define	DIO_CHANNEL_USER_LED_2	DIO_CHANNEL_1_6
#define	DIO_CHANNEL_1_7	0x0000000F	/**< Channel 1 7 */
/** Channel User Led 3*/
#define	DIO_CHANNEL_USER_LED_3	DIO_CHANNEL_1_7

#define DIO_PORT2_RBITS_MASK	0b11111111 /**< PORT2 reserved bits mask */
#define	DIO_CHANNEL_2_0	0x00000010	/**< Channel 2 0 */
#define	DIO_CHANNEL_2_1	0x00000011	/**< Channel 2 1 */
#define	DIO_CHANNEL_2_2	0x00000012	/**< Channel 2 2 */
#define	DIO_CHANNEL_2_3	0x00000013	/**< Channel 2 3 */
#define	DIO_CHANNEL_2_4	0x00000014	/**< Channel 2 4 */
#define	DIO_CHANNEL_2_5	0x00000015	/**< Channel 2 5 */
#define	DIO_CHANNEL_2_6	0x00000016	/**< Channel 2 6 */
#define	DIO_CHANNEL_2_7	0x00000017	/**< Channel 2 7 */

#define DIO_PORT3_RBITS_MASK	0b11111111 /**< PORT3 reserved bits mask */
#define	DIO_CHANNEL_3_0	0x00000018	/**< Channel 3 0 */
#define	DIO_CHANNEL_3_1	0x00000019	/**< Channel 3 1 */
/** Channel User Switch 1*/
#define DIO_CHANNEL_USER_SWITCH_1	DIO_CHANNEL_3_1
#define	DIO_CHANNEL_3_2	0x0000001A	/**< Channel 3 2 */
#define	DIO_CHANNEL_3_3	0x0000001B	/**< Channel 3 3 */
/** Channel User Switch 2*/
#define DIO_CHANNEL_USER_SWITCH_2	DIO_CHANNEL_3_3
#define	DIO_CHANNEL_3_4	0x0000001C	/**< Channel 3 4 */
/** Channel User Switch 3*/
#define DIO_CHANNEL_USER_SWITCH_3	DIO_CHANNEL_3_4
#define	DIO_CHANNEL_3_5	0x0000001D	/**< Channel 3 5 */
#define	DIO_CHANNEL_3_6	0x0000001E	/**< Channel 3 6 */
#define	DIO_CHANNEL_3_7	0x0000001F	/**< Channel 3 7 */

#define DIO_PORT4_RBITS_MASK	0b11111111 /**< PORT4 reserved bits mask */
#define	DIO_CHANNEL_4_0	0x00000020	/**< Channel 4 0 */
#define	DIO_CHANNEL_4_1	0x00000021	/**< Channel 4 1 */
#define	DIO_CHANNEL_4_2	0x00000022	/**< Channel 4 2 */
#define	DIO_CHANNEL_4_3	0x00000023	/**< Channel 4 3 */
#define	DIO_CHANNEL_4_4	0x00000024	/**< Channel 4 4 */
#define	DIO_CHANNEL_4_5	0x00000025	/**< Channel 4 5 */
#define	DIO_CHANNEL_4_6	0x00000026	/**< Channel 4 6 */
#define	DIO_CHANNEL_4_7	0x00000027	/**< Channel 4 7 */

#define DIO_PORT5_RBITS_MASK	0b00111111 /**< PORT5 reserved bits mask */
#define	DIO_CHANNEL_5_0	0x00000028	/**< Channel 5 0 */
#define	DIO_CHANNEL_5_1	0x00000029	/**< Channel 5 1 */
#define	DIO_CHANNEL_5_2	0x0000002A	/**< Channel 5 2 */
#define	DIO_CHANNEL_5_3	0x0000002B	/**< Channel 5 3 */
#define	DIO_CHANNEL_5_4	0x0000002C	/**< Channel 5 4 */
#define	DIO_CHANNEL_5_5	0x0000002D	/**< Channel 5 5 */

#define DIO_PORTA_RBITS_MASK	0b11111111 /**< PORTA reserved bits mask */
#define	DIO_CHANNEL_A_0	0x00000050	/**< Channel A 0 */
#define	DIO_CHANNEL_A_1	0x00000051	/**< Channel A 1 */
#define	DIO_CHANNEL_A_2	0x00000052	/**< Channel A 2 */
#define	DIO_CHANNEL_A_3	0x00000053	/**< Channel A 3 */
#define	DIO_CHANNEL_A_4	0x00000054	/**< Channel A 4 */
#define	DIO_CHANNEL_A_5	0x00000055	/**< Channel A 5 */
#define	DIO_CHANNEL_A_6	0x00000056	/**< Channel A 6 */
#define	DIO_CHANNEL_A_7	0x00000057	/**< Channel A 7 */

#define DIO_PORTB_RBITS_MASK	0b11111111 /**< PORTB reserved bits mask */
#define	DIO_CHANNEL_B_0	0x00000058	/**< Channel B 0 */
#define	DIO_CHANNEL_B_1	0x00000059	/**< Channel B 1 */
#define	DIO_CHANNEL_B_2	0x0000005A	/**< Channel B 2 */
#define	DIO_CHANNEL_B_3	0x0000005B	/**< Channel B 3 */
#define	DIO_CHANNEL_B_4	0x0000005C	/**< Channel B 4 */
#define	DIO_CHANNEL_B_5	0x0000005D	/**< Channel B 5 */
#define	DIO_CHANNEL_B_6	0x0000005E	/**< Channel B 6 */
#define	DIO_CHANNEL_B_7	0x0000005F	/**< Channel B 7 */

#define DIO_PORTC_RBITS_MASK	0b11111111 /**< PORTC reserved bits mask */
#define	DIO_CHANNEL_C_0	0x00000060	/**< Channel C 0 */
#define	DIO_CHANNEL_C_1	0x00000061	/**< Channel C 1 */
#define	DIO_CHANNEL_C_2	0x00000062	/**< Channel C 2 */
#define	DIO_CHANNEL_C_3	0x00000063	/**< Channel C 3 */
#define	DIO_CHANNEL_C_4	0x00000064	/**< Channel C 4 */
#define	DIO_CHANNEL_C_5	0x00000065	/**< Channel C 5 */
#define	DIO_CHANNEL_C_6	0x00000066	/**< Channel C 6 */
#define	DIO_CHANNEL_C_7	0x00000067	/**< Channel C 7 */

#define DIO_PORTD_RBITS_MASK	0b11111111 /**< PORTD reserved bits mask */
#define	DIO_CHANNEL_D_0	0x00000068	/**< Channel D 0 */
#define	DIO_CHANNEL_D_1	0x00000069	/**< Channel D 1 */
#define	DIO_CHANNEL_D_2	0x0000006A	/**< Channel D 2 */
#define	DIO_CHANNEL_D_3	0x0000006B	/**< Channel D 3 */
#define	DIO_CHANNEL_D_4	0x0000006C	/**< Channel D 4 */
#define	DIO_CHANNEL_D_5	0x0000006D	/**< Channel D 5 */
#define	DIO_CHANNEL_D_6	0x0000006E	/**< Channel D 6 */
#define	DIO_CHANNEL_D_7	0x0000006F	/**< Channel D 7 */

#define DIO_PORTE_RBITS_MASK	0b11111111 /**< PORTE reserved bits mask */
#define	DIO_CHANNEL_E_0	0x00000070	/**< Channel E 0 */
/*Channel User Output*/
#define DIO_CHANNEL_USER_OUTPUT	DIO_CHANNEL_E_0
#define	DIO_CHANNEL_E_1	0x00000071	/**< Channel E 1 */
#define	DIO_CHANNEL_E_2	0x00000072	/**< Channel E 2 */
#define	DIO_CHANNEL_E_3	0x00000073	/**< Channel E 3 */
#define	DIO_CHANNEL_E_4	0x00000074	/**< Channel E 4 */
#define	DIO_CHANNEL_E_5	0x00000075	/**< Channel E 5 */
#define	DIO_CHANNEL_E_6	0x00000076	/**< Channel E 6 */
#define	DIO_CHANNEL_E_7	0x00000077	/**< Channel E 7 */

#define DIO_PORTH_RBITS_MASK	0b00001111 /**< PORTH reserved bits mask */
#define	DIO_CHANNEL_H_0	0x00000088	/**< Channel H 0 */
#define	DIO_CHANNEL_H_1	0x00000089	/**< Channel H 1 */
#define	DIO_CHANNEL_H_2	0x0000008A	/**< Channel H 2 */
#define	DIO_CHANNEL_H_3	0x0000008B	/**< Channel H 3 */

#define DIO_PORTJ_RBITS_MASK	0b00001010 /**< PORTJ reserved bits mask */
#define	DIO_CHANNEL_J_1	0x00000091	/**< Channel J 4 */
#define	DIO_CHANNEL_J_3	0x00000093	/**< Channel J 5 */

/** Number of Channels */
#define	DIO_CHANNELS_NUMBER	DIO_CHANNEL_J_3 + 1

#define	DIO_PORT_0	0x00000000	/**< Port 0 */
#define	DIO_PORT_1	0x00000001	/**< Port 1 */
#define DIO_PORT_USER_LEDS	DIO_PORT_1 /** Port User Leds */
#define	DIO_PORT_2	0x00000002	/**< Port 2 */
#define	DIO_PORT_3	0x00000003	/**< Port 3 */
#define DIO_PORT_USER_SWITCHES	DIO_PORT_3 /** Port User Switches */
#define	DIO_PORT_4	0x00000004	/**< Port 4 */
#define	DIO_PORT_5	0x00000005	/**< Port 5 */
#define	DIO_PORT_A	0x0000000A	/**< Port A */
#define	DIO_PORT_B	0x0000000B	/**< Port B */
#define	DIO_PORT_C	0x0000000C	/**< Port C */
#define	DIO_PORT_D	0x0000000D	/**< Port D */
#define	DIO_PORT_E	0x0000000E	/**< Port E */
#define DIO_PORT_USER_OUTPUT	DIO_PORT_E	/** Port User Output */
#define	DIO_PORT_H	0x00000011	/**< Port H */
#define	DIO_PORT_J	0x00000012	/**< Port J */

/** Number of Ports */
#define	DIO_PORTS_NUMBER	DIO_PORT_J + 1

/** @brief	Port 1 Channel Groups Configuration Parameters */
extern const Dio_ChannelGroupType DioPort1ChannelsGroups[];

/** User Leds Channel Group */
#define	DIO_CHANNEL_GROUP_USER_LEDS	&DioPort1ChannelsGroups[0]

/** @brief	Port M Channel Groups Configuration Parameters */
extern const Dio_ChannelGroupType DioPort3ChannelsGroups[];

/** User Switches Channel Group */
#define	DIO_CHANNEL_GROUP_USER_SWITCHES	&DioPort3ChannelsGroups[0]

/** @brief	Port Configuration Parameters
 *
 *  <b>DIO144_Conf:</b> Configuration of individual DIO ports, consisting of
 *  channels and possible channel groups. Note that this container definition
 *  does not explicitly define a symbolic name parameter. Instead, the
 *  container's short name will be used in the Ecu Configuration Description to
 *  specify the symbolic name of the port.
 */
typedef struct {

  /** @brief	Port Identifier
   *
   *  <b>DIO145_Conf:</b> Numeric identifier of the DIO port. Not all MCU ports
   *  may be used for DIO, thus there may be "gaps" in the list of all IDs. This
   *  value will be assigned to the DIO port symbolic name (i.e. the SHORT-NAME
   *  of the DioPort container).
   */
  uint32			DioPortId;

  /** brief	Number of Channels
   *
   *  The number of specified Port Channels.
   */
  uint32			DioNumberOfChannels;

  /** @brief	Channels
   *
   *  Configuration of an individual DIO channel. Besides a HW specific channel
   *  name which is typically fixed for a specific micro controller, additional
   *  symbolic names can be defined per channel. Note hat this container
   *  definition does not explicitly define a symbolic name parameter. Instead,
   *  the container's short name will be used in the Ecu Configuration
   *  Description to specify the symbolic name of the channel.
   */
  const Dio_ChannelType *	DioChannels;

  /** @brief	Number of Channel Groups
   *
   *  The number of specified Port Channels Groups.
   */
  uint32			DioNumberOfChannelsGroups;

  /** @brief	Channel Groups
   *
   *  <b>DIO149_Conf:</b> The DIO channel group is identified in DIO API by a
   *  pointer to a data structure (of type <tt>Dio_ChannelGroupType</tt>). That
   *  data structure contains the channel group information. This parameter
   *  contains the code fragment that has to be inserted in the API call of the
   *  calling module to get the address of the variable in memory which holds
   *  the channel group information. Example values are "&MyDioGroup1" or
   *  "&MyDioGroupArray[0]"
   */
  const Dio_ChannelGroupType *	Dio_ChannelsGroups;

} Dio_PortConfType;

/** @brief	Dio Module Configuration Parameters
 *
 *  <b>DIO152_Conf</b>:	This container contains the configuration parameters
 *  and sub containers of the AUTOSAR DIO module. This container is a 
 *  MultipleConfigurationContainer, i.e. this container and its sub-containers
 *  exist once per configuration set.
 */
typedef struct {

  /** @brief	Number of Ports
   *
   *  The number of specified Ports.
   */
  uint32			DioNumberOfPorts;

  /** @brief	Ports Configuration Parameters
   *
   *  Ports Configuration Parameters for all specified Ports.
   */
  const Dio_PortConfType *	DioPorts;

} Dio_ConfigType;

/** @brief	DIO Configuration
 *
 *  Identifier for DIO Configuration.
 */
#define	DIO_CONFIG_DIO		0x00000000
/** @brief	DIO Configuration Pointer
 *
 *  Pointer of DIO Driver Configuration
 */
#define	DIO_CONFIG_DIO_PTR	&Dio_Config[DIO_CONFIG_DIO]
/** @brief	Default Configuration
 *
 *  Identifier for Default DIO Driver Configuration.
 */
#define	DIO_CONFIG_DEFAULT	DIO_CONFIG_DIO
/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default DIO Driver Configuration
 */
#define	DIO_CONFIG_DEFAULT_PTR	&Dio_Config[DIO_CONFIG_DEFAULT]
/** @brief	User Led Configuration
 *
 *  Identifier for User Led DIO Driver Configuration.
 */

#endif	/* DIO_CFG_H */
