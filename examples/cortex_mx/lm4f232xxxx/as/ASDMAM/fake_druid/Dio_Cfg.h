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
 *  Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 *  @author	Giuseppe Serano
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
#define	DIO_FLIP_CHANNEL_API	STD_OFF

/** @brief	Version Informations Retrieval API
 *
 *  <b>DIO143_Conf:</b> Adds / removes the service
 *  <tt>Dio_ GetVersionInfo()</tt> from the code.
 */
#define	DIO_VERSION_INFO_API	STD_OFF

/*
 * DIO026:	The configuration process for Dio module shall provide symbolic
 * 		names for each configured DIO channel, port and group.
 */ 
#define	DIO_CHANNEL_A_0	0x00000000	/**< Channel A 0 */
#define	DIO_CHANNEL_A_1	0x00000001	/**< Channel A 1 */
#define	DIO_CHANNEL_A_2	0x00000002	/**< Channel A 2 */
#define	DIO_CHANNEL_A_3	0x00000003	/**< Channel A 3 */
#define	DIO_CHANNEL_A_4	0x00000004	/**< Channel A 4 */
#define	DIO_CHANNEL_A_5	0x00000005	/**< Channel A 5 */
#define	DIO_CHANNEL_A_6	0x00000006	/**< Channel A 6 */
#define	DIO_CHANNEL_A_7	0x00000007	/**< Channel A 7 */

#define	DIO_CHANNEL_B_0	0x00000008	/**< Channel B 0 */
#define	DIO_CHANNEL_B_1	0x00000009	/**< Channel B 1 */
#define	DIO_CHANNEL_B_2	0x0000000A	/**< Channel B 2 */
#define	DIO_CHANNEL_B_3	0x0000000B	/**< Channel B 3 */
#define	DIO_CHANNEL_B_4	0x0000000C	/**< Channel B 4 */
#define	DIO_CHANNEL_B_5	0x0000000D	/**< Channel B 5 */
#define	DIO_CHANNEL_B_6	0x0000000E	/**< Channel B 6 */
#define	DIO_CHANNEL_B_7	0x0000000F	/**< Channel B 7 */

#define	DIO_CHANNEL_C_0	0x00000010	/**< Channel C 0 */
#define	DIO_CHANNEL_C_1	0x00000011	/**< Channel C 1 */
#define	DIO_CHANNEL_C_2	0x00000012	/**< Channel C 2 */
#define	DIO_CHANNEL_C_3	0x00000013	/**< Channel C 3 */
#define	DIO_CHANNEL_C_4	0x00000014	/**< Channel C 4 */
#define	DIO_CHANNEL_C_5	0x00000015	/**< Channel C 5 */
#define	DIO_CHANNEL_C_6	0x00000016	/**< Channel C 6 */
#define	DIO_CHANNEL_C_7	0x00000017	/**< Channel C 7 */

#define	DIO_CHANNEL_D_0	0x00000018	/**< Channel D 0 */
#define	DIO_CHANNEL_D_1	0x00000019	/**< Channel D 1 */
#define	DIO_CHANNEL_D_2	0x0000001A	/**< Channel D 2 */
#define	DIO_CHANNEL_D_3	0x0000001B	/**< Channel D 3 */
#define	DIO_CHANNEL_D_4	0x0000001C	/**< Channel D 4 */
#define	DIO_CHANNEL_D_5	0x0000001D	/**< Channel D 5 */
#define	DIO_CHANNEL_D_6	0x0000001E	/**< Channel D 6 */
#define	DIO_CHANNEL_D_7	0x0000001F	/**< Channel D 7 */

#define	DIO_CHANNEL_E_0	0x00000020	/**< Channel E 0 */
#define	DIO_CHANNEL_E_1	0x00000021	/**< Channel E 1 */
#define	DIO_CHANNEL_E_2	0x00000022	/**< Channel E 2 */
#define	DIO_CHANNEL_E_3	0x00000023	/**< Channel E 3 */
#define	DIO_CHANNEL_E_4	0x00000024	/**< Channel E 4 */
#define	DIO_CHANNEL_E_5	0x00000025	/**< Channel E 5 */
#define	DIO_CHANNEL_E_6	0x00000026	/**< Channel E 6 */
#define	DIO_CHANNEL_E_7	0x00000027	/**< Channel E 7 */

#define	DIO_CHANNEL_F_0	0x00000028	/**< Channel F 0 */
#define	DIO_CHANNEL_F_1	0x00000029	/**< Channel F 1 */
#define	DIO_CHANNEL_F_2	0x0000002A	/**< Channel F 2 */
#define	DIO_CHANNEL_F_3	0x0000002B	/**< Channel F 3 */
#define	DIO_CHANNEL_F_4	0x0000002C	/**< Channel F 4 */
#define	DIO_CHANNEL_F_5	0x0000002D	/**< Channel F 5 */
#define	DIO_CHANNEL_F_6	0x0000002E	/**< Channel F 6 */
#define	DIO_CHANNEL_F_7	0x0000002F	/**< Channel F 7 */

#define	DIO_CHANNEL_G_0	0x00000030	/**< Channel G 0 */
#define	DIO_CHANNEL_G_1	0x00000031	/**< Channel G 1 */
#define	DIO_CHANNEL_G_2	0x00000032	/**< Channel G 2 */
/** Channel User Led */
#define	DIO_CHANNEL_USER_LED	DIO_CHANNEL_G_2
#define	DIO_CHANNEL_G_3	0x00000033	/**< Channel G 3 */
#define	DIO_CHANNEL_G_4	0x00000034	/**< Channel G 4 */
#define	DIO_CHANNEL_G_5	0x00000035	/**< Channel G 5 */
#define	DIO_CHANNEL_G_6	0x00000036	/**< Channel G 6 */
#define	DIO_CHANNEL_G_7	0x00000037	/**< Channel G 7 */

#define	DIO_CHANNEL_H_0	0x00000038	/**< Channel H 0 */
#define	DIO_CHANNEL_H_1	0x00000039	/**< Channel H 1 */
#define	DIO_CHANNEL_H_2	0x0000003A	/**< Channel H 2 */
#define	DIO_CHANNEL_H_3	0x0000003B	/**< Channel H 3 */
#define	DIO_CHANNEL_H_4	0x0000003C	/**< Channel H 4 */
#define	DIO_CHANNEL_H_5	0x0000003D	/**< Channel H 5 */
#define	DIO_CHANNEL_H_6	0x0000003E	/**< Channel H 6 */
#define	DIO_CHANNEL_H_7	0x0000003F	/**< Channel H 7 */

#define	DIO_CHANNEL_J_0	0x00000040	/**< Channel J 0 */
#define	DIO_CHANNEL_J_1	0x00000041	/**< Channel J 1 */
#define	DIO_CHANNEL_J_2	0x00000042	/**< Channel J 2 */
#define	DIO_CHANNEL_J_3	0x00000043	/**< Channel J 3 */
#define	DIO_CHANNEL_J_4	0x00000044	/**< Channel J 4 */
#define	DIO_CHANNEL_J_5	0x00000045	/**< Channel J 5 */
#define	DIO_CHANNEL_J_6	0x00000046	/**< Channel J 6 */
#define	DIO_CHANNEL_J_7	0x00000047	/**< Channel J 7 */

#define	DIO_CHANNEL_K_0	0x00000048	/**< Channel K 0 */
#define	DIO_CHANNEL_K_1	0x00000049	/**< Channel K 1 */
#define	DIO_CHANNEL_K_2	0x0000004A	/**< Channel K 2 */
#define	DIO_CHANNEL_K_3	0x0000004B	/**< Channel K 3 */
#define	DIO_CHANNEL_K_4	0x0000004C	/**< Channel K 4 */
#define	DIO_CHANNEL_K_5	0x0000004D	/**< Channel K 5 */
#define	DIO_CHANNEL_K_6	0x0000004E	/**< Channel K 6 */
#define	DIO_CHANNEL_K_7	0x0000004F	/**< Channel K 7 */

#define	DIO_CHANNEL_L_0	0x00000050	/**< Channel L 0 */
#define	DIO_CHANNEL_L_1	0x00000051	/**< Channel L 1 */
#define	DIO_CHANNEL_L_2	0x00000052	/**< Channel L 2 */
#define	DIO_CHANNEL_L_3	0x00000053	/**< Channel L 3 */
#define	DIO_CHANNEL_L_4	0x00000054	/**< Channel L 4 */
#define	DIO_CHANNEL_L_5	0x00000055	/**< Channel L 5 */
#define	DIO_CHANNEL_L_6	0x00000056	/**< Channel L 6 */
#define	DIO_CHANNEL_L_7	0x00000057	/**< Channel L 7 */

#define	DIO_CHANNEL_M_0	0x00000058	/**< Channel M 0 */
/** Channel User Switch 1 */
#define	DIO_CHANNEL_USER_SWITCH_1	DIO_CHANNEL_M_0
#define	DIO_CHANNEL_M_1	0x00000059	/**< Channel M 1 */
/** Channel User Switch 2 */
#define	DIO_CHANNEL_USER_SWITCH_2	DIO_CHANNEL_M_1
#define	DIO_CHANNEL_M_2	0x0000005A	/**< Channel M 2 */
/** Channel User Switch 3 */
#define	DIO_CHANNEL_USER_SWITCH_3	DIO_CHANNEL_M_2
#define	DIO_CHANNEL_M_3	0x0000005B	/**< Channel M 3 */
/** Channel User Switch 4 */
#define	DIO_CHANNEL_USER_SWITCH_4	DIO_CHANNEL_M_3
#define	DIO_CHANNEL_M_4	0x0000005C	/**< Channel M 4 */
/** Channel User Switch 5 */
#define	DIO_CHANNEL_USER_SWITCH_5	DIO_CHANNEL_M_4
#define	DIO_CHANNEL_M_5	0x0000005D	/**< Channel M 5 */
#define	DIO_CHANNEL_M_6	0x0000005E	/**< Channel M 6 */
#define	DIO_CHANNEL_M_7	0x0000005F	/**< Channel M 7 */

#define	DIO_CHANNEL_P_0	0x00000060	/**< Channel P 0 */
#define	DIO_CHANNEL_P_1	0x00000061	/**< Channel P 1 */
#define	DIO_CHANNEL_P_2	0x00000062	/**< Channel P 2 */
#define	DIO_CHANNEL_P_3	0x00000063	/**< Channel P 3 */
#define	DIO_CHANNEL_P_4	0x00000064	/**< Channel P 4 */
#define	DIO_CHANNEL_P_5	0x00000065	/**< Channel P 5 */
#define	DIO_CHANNEL_P_6	0x00000066	/**< Channel P 6 */
#define	DIO_CHANNEL_P_7	0x00000067	/**< Channel P 7 */

#define	DIO_CHANNEL_Q_0	0x00000068	/**< Channel Q 0 */
#define	DIO_CHANNEL_Q_1	0x00000069	/**< Channel Q 1 */
#define	DIO_CHANNEL_Q_2	0x0000006A	/**< Channel Q 2 */
#define	DIO_CHANNEL_Q_3	0x0000006B	/**< Channel Q 3 */
#define	DIO_CHANNEL_Q_4	0x0000006C	/**< Channel Q 4 */
#define	DIO_CHANNEL_Q_5	0x0000006D	/**< Channel Q 5 */
#define	DIO_CHANNEL_Q_6	0x0000006E	/**< Channel Q 6 */
#define	DIO_CHANNEL_Q_7	0x0000006F	/**< Channel Q 7 */

/** Number of Channels */
#define	DIO_CHANNELS_NUMBER	DIO_CHANNEL_Q_7 + 1

#define	DIO_PORT_A	0x00000000	/**< Port A */
#define	DIO_PORT_B	0x00000001	/**< Port B */
#define	DIO_PORT_C	0x00000002	/**< Port C */
#define	DIO_PORT_D	0x00000003	/**< Port D */
#define	DIO_PORT_E	0x00000004	/**< Port E */
#define	DIO_PORT_F	0x00000005	/**< Port F */
#define	DIO_PORT_G	0x00000006	/**< Port G */
/** Port User Led */
#define	DIO_PORT_USER_LED	DIO_PORT_G
#define	DIO_PORT_H	0x00000007	/**< Port H */
#define	DIO_PORT_J	0x00000008	/**< Port J */
#define	DIO_PORT_K	0x00000009	/**< Port K */
#define	DIO_PORT_L	0x0000000A	/**< Port L */
#define	DIO_PORT_M	0x0000000B	/**< Port M */
/** Port User Switches */
#define	DIO_PORT_USER_SWITCHES	DIO_PORT_M
#define	DIO_PORT_P	0x0000000C	/**< Port P */
#define	DIO_PORT_Q	0x0000000D	/**< Port Q */

/** Number of Ports */
#define	DIO_PORTS_NUMBER	DIO_PORT_Q + 1

/** @brief	Port G Channel Groups Configuration Parameters */
extern const Dio_ChannelGroupType DioPortGChannelsGroups[];

/** User Led Channel Group */
#define	DIO_CHANNEL_GROUP_USER_LED	&DioPortGChannelsGroups[0]

/** @brief	Port M Channel Groups Configuration Parameters */
extern const Dio_ChannelGroupType DioPortMChannelsGroups[];

/** User Switches Channel Group */
#define	DIO_CHANNEL_GROUP_USER_SWITCHES	&DioPortMChannelsGroups[0]

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

#endif	/* DIO_CFG_H */
