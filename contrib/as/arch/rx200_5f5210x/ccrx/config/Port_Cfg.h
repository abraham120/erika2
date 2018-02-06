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

/** @file	Port_Cfg.h
 *  @brief	fake-druid AUTOSAR PORT Driver Configuration Header File.
 *
 *  Configured for (MCU): Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2012
 */


#if !(\
 ((PORT_SW_MAJOR_VERSION == 1) && \
  (PORT_SW_MINOR_VERSION == 0) && \
  (PORT_SW_PATCH_VERSION == 0))\
)
#error Port: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	PORT_CFG_H
#define	PORT_CFG_H

/*
 * PORT117_Conf:	Module wide configuration parameters of the PORT driver.
 */
/* PortGeneral */

/** @brief	Development Error Detection
 *
 *  <b>PORT123_Conf:</b> Switches the Development Error Detection and 
 *  Notification on or off.<br>
 *  - <tt>TRUE</tt>: Enabled.
 *  - <tt>FALSE</tt>: Disabled.
 */
#define	PORT_DEV_ERROR_DETECT		STD_OFF

/** @brief	Pin Direction Setting API
 *
 *  <b>PORT131_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Port_SetPinDirection()</tt>.<br>
 *  - <tt>TRUE</tt>: Enabled, Function <tt>Port_SetPinDirection()</tt> is
 *  available.
 *  - <tt>FALSE</tt>: Disabled, Function <tt>Port_SetPinDirection()</tt> is not
 *  available.
 */
#define	PORT_SET_PIN_DIRECTION_API	STD_OFF

/** @brief	Pin Mode Setting API
 *
 *  <b>PORT132_Conf:</b> Pre-processor switch to enable / disable the use of the
 *  function <tt>Port_SetPinMode()</tt>.<br>
 *  - <tt>TRUE</tt>: Enabled, Function <tt>Port_SetPinMode()</tt> is available.
 *  - <tt>FALSE</tt>: Disabled, Function <tt>Port_SetPinMode()</tt> is not
 *  available.
 */
#define	PORT_SET_PIN_MODE_API		STD_OFF

/** @brief	Version Informations Retrieval API
 *
 *  <b>PORT133_Conf:</b> Pre-processor switch to enable / disable the API to
 *  read out the modules version information.
 *  - <tt>TRUE</tt>: Version info API enabled.
 *  - <tt>FALSE</tt>: Version info API disabled.
 */
#define	PORT_VERSION_INFO_API		STD_ON

/* PORT006:	The user of the PORT Driver module shall configure the symbolic
 * 		names of the port pins of the MCU.
 *
 * PORT207:	These symbolic names for the individual port pins (e.g.
 * 		PORT_A_PIN_0) shall be defined in the configuration tool.
 *
 * PORT076:	The PORT Driver module’s implementer shall define symbolic names
 * 		in the file Port_Cfg.h
 *
 * PORT208:	The PORT Driver module’s implementer shall publish the symbolic
 * 		names through the file Port.h
 */

#define	PORT_0			0x00000000	/**< Port 0		*/
#define	PORT_0_PIN_3	0x00000003	/**< Port 0 - Pin 3	*/
#define	PORT_0_PIN_4	0x00000004	/**< Port 0 - Pin 4	*/
#define	PORT_0_PIN_5	0x00000005	/**< Port 0 - Pin 5	*/
#define	PORT_0_PIN_6	0x00000006	/**< Port 0 - Pin 6	*/
#define	PORT_0_PIN_7	0x00000007	/**< Port 0 - Pin 7	*/
#define	PORT_1			0x00000008	/**< Port 1		*/
#define	PORT_1_PIN_2	0x0000000A	/**< Port 1 - Pin 2	*/
#define	PORT_1_PIN_3	0x0000000B	/**< Port 1 - Pin 3	*/
#define	PORT_1_PIN_4	0x0000000C	/**< Port 1 - Pin 4	*/
#define	PORT_1_PIN_5	0x0000000D	/**< Port 1 - Pin 5	*/
#define	PORT_1_PIN_6	0x0000000E	/**< Port 1 - Pin 6	*/
#define	PORT_1_PIN_7	0x0000000F	/**< Port 1 - Pin 7	*/
#define	PORT_2			0x00000010	/**< Port 2		*/
#define	PORT_2_PIN_0	PORT_2		/**< Port 2 - Pin 0	*/
#define	PORT_2_PIN_1	0x00000011	/**< Port 2 - Pin 1	*/
#define	PORT_2_PIN_2	0x00000012	/**< Port 2 - Pin 2	*/
#define	PORT_2_PIN_3	0x00000013	/**< Port 2 - Pin 3	*/
#define	PORT_2_PIN_4	0x00000014	/**< Port 2 - Pin 4	*/
#define	PORT_2_PIN_5	0x00000015	/**< Port 2 - Pin 5	*/
#define	PORT_2_PIN_6	0x00000016	/**< Port 2 - Pin 6	*/
#define	PORT_2_PIN_7	0x00000017	/**< Port 2 - Pin 7	*/
#define	PORT_3			0x00000018	/**< Port D		*/
#define	PORT_3_PIN_0	PORT_3		/**< Port 3 - Pin 0	*/
#define	PORT_3_PIN_1	0x00000019	/**< Port 3 - Pin 1	*/
#define	PORT_3_PIN_2	0x0000001A	/**< Port 3 - Pin 2	*/
#define	PORT_3_PIN_3	0x0000001B	/**< Port 3 - Pin 3	*/
#define	PORT_3_PIN_4	0x0000001C	/**< Port 3 - Pin 4	*/
#define	PORT_3_PIN_5	0x0000001D	/**< Port 3 - Pin 5	*/
#define	PORT_3_PIN_6	0x0000001E	/**< Port 3 - Pin 6	*/
#define	PORT_3_PIN_7	0x0000001F	/**< Port 3 - Pin 7	*/
#define	PORT_4			0x00000020	/**< Port 4		*/
#define	PORT_4_PIN_0	PORT_4		/**< Port 4 - Pin 0	*/
#define	PORT_4_PIN_1	0x00000021	/**< Port 4 - Pin 1	*/
#define	PORT_4_PIN_2	0x00000022	/**< Port 4 - Pin 2	*/
#define	PORT_4_PIN_3	0x00000023	/**< Port 4 - Pin 3	*/
#define	PORT_4_PIN_4	0x00000024	/**< Port 4 - Pin 4	*/
#define	PORT_4_PIN_5	0x00000025	/**< Port 4 - Pin 5	*/
#define	PORT_4_PIN_6	0x00000026	/**< Port 4 - Pin 6	*/
#define	PORT_4_PIN_7	0x00000027	/**< Port 4 - Pin 7	*/
#define	PORT_5			0x00000028	/**< Port 5		*/
#define	PORT_5_PIN_0	PORT_5		/**< Port 5 - Pin 0	*/
#define	PORT_5_PIN_1	0x00000029	/**< Port 5 - Pin 1	*/
#define	PORT_5_PIN_2	0x0000002A	/**< Port 5 - Pin 2	*/
#define	PORT_5_PIN_3	0x0000002B	/**< Port 5 - Pin 3	*/
#define	PORT_5_PIN_4	0x0000002C	/**< Port 5 - Pin 4	*/
#define	PORT_5_PIN_5	0x0000002D	/**< Port  - Pin 5	*/
#define	PORT_A			0x00000050	/**< Port A		*/
#define	PORT_A_PIN_0	PORT_A		/**< Port A - Pin 0	*/
#define	PORT_A_PIN_1	0x00000051	/**< Port A - Pin 1	*/
#define	PORT_A_PIN_2	0x00000052	/**< Port A - Pin 2	*/
#define	PORT_A_PIN_3	0x00000053	/**< Port A - Pin 3	*/
#define	PORT_A_PIN_4	0x00000054	/**< Port A - Pin 4	*/
#define	PORT_A_PIN_5	0x00000055	/**< Port A - Pin 5	*/
#define	PORT_A_PIN_6	0x00000056	/**< Port A - Pin 6	*/
#define	PORT_A_PIN_7	0x00000057	/**< Port A - Pin 7	*/
#define	PORT_B			0x00000058	/**< Port B		*/
#define	PORT_B_PIN_0	PORT_B		/**< PORT B - Pin 0	*/
#define	PORT_B_PIN_1	0x00000059	/**< PORT B - Pin 1	*/
#define	PORT_B_PIN_2	0x0000005A	/**< PORT B - Pin 2	*/
#define	PORT_B_PIN_3	0x0000005B	/**< PORT B - Pin 3	*/
#define	PORT_B_PIN_4	0x0000005C	/**< PORT B - Pin 4	*/
#define	PORT_B_PIN_5	0x0000005D	/**< PORT B - Pin 5	*/
#define	PORT_B_PIN_6	0x0000005E	/**< PORT B - Pin 6	*/
#define	PORT_B_PIN_7	0x0000005F	/**< PORT B - Pin 7	*/
#define	PORT_C			0x00000060	/**< PORT C		*/
#define	PORT_C_PIN_0	PORT_C		/**< PORT C - Pin 0	*/
#define	PORT_C_PIN_1	0x00000061	/**< PORT C - Pin 1	*/
#define	PORT_C_PIN_2	0x00000062	/**< PORT C - Pin 2	*/
#define	PORT_C_PIN_3	0x00000063	/**< PORT C - Pin 3	*/
#define	PORT_C_PIN_4	0x00000064	/**< PORT C - Pin 4	*/
#define	PORT_C_PIN_5	0x00000065	/**< PORT C - Pin 5	*/
#define	PORT_C_PIN_6	0x00000066	/**< PORT C - Pin 6	*/
#define	PORT_C_PIN_7	0x00000067	/**< PORT C - Pin 7	*/
#define	PORT_D			0x00000068	/**< PORT D		*/
#define	PORT_D_PIN_0	PORT_D		/**< PORT D - Pin 0	*/
#define	PORT_D_PIN_1	0x00000069	/**< PORT D - Pin 1	*/
#define	PORT_D_PIN_2	0x0000006A	/**< PORT D - Pin 2	*/
#define	PORT_D_PIN_3	0x0000006B	/**< PORT D - Pin 3	*/
#define	PORT_D_PIN_4	0x0000006C	/**< PORT D - Pin 4	*/
#define	PORT_D_PIN_5	0x0000006D	/**< PORT D - Pin 5	*/
#define	PORT_D_PIN_6	0x0000006E	/**< PORT D - Pin 6	*/
#define	PORT_D_PIN_7	0x0000006F	/**< PORT D - Pin 7	*/
#define	PORT_E			0x00000070	/**< Port E		*/
#define	PORT_E_PIN_0	PORT_E		/**< Port E - Pin 0	*/
#define	PORT_E_PIN_1	0x00000071	/**< Port E - Pin 1	*/
#define	PORT_E_PIN_2	0x00000072	/**< Port E - Pin 2	*/
#define	PORT_E_PIN_3	0x00000073	/**< Port E - Pin 3	*/
#define	PORT_E_PIN_4	0x00000074	/**< Port E - Pin 4	*/
#define	PORT_E_PIN_5	0x00000075	/**< Port E - Pin 5	*/
#define	PORT_E_PIN_6	0x00000076	/**< Port E - Pin 6	*/
#define	PORT_E_PIN_7	0x00000077	/**< Port E - Pin 7	*/
#define	PORT_H			0x00000088	/**< Port H		*/
#define	PORT_H_PIN_0	PORT_H		/**< Port H - Pin 0	*/
#define	PORT_H_PIN_1	0x00000089	/**< Port H - Pin 1	*/
#define	PORT_H_PIN_2	0x0000008A	/**< Port H - Pin 2	*/
#define	PORT_H_PIN_3	0x0000008B	/**< Port H - Pin 3	*/

#define	PORT_J			0x00000090	/**< Port J		*/

#define	PORT_J_PIN_1	0x00000091	/**< Port J - Pin 1	*/
#define	PORT_P_PIN_3	0x00000093	/**< Port J - Pin 3	*/


/** Number of Port Pins */
#define	PORT_PINS_NUMBER	PORT_J_PIN_3 + 1

/*
 * Port Pins Function Selection masks 
 */
 
/** High Impedence Pin Mode. */
#define	PORT_PIN_PFS_HI_Z		0x00
/** Multi Timer Unit I/O Pin Mode. */
#define	PORT_PIN_PFS_MTIOC		0x01
/** Multi Timer Unit module 5 Input Capture Pin Mode. */
#define PORT_PIN_PFS_MTIC5		0x01
/** Multi Timer Unit Channel 3 Clock D I/O Pin Mode. */
#define	PORT_PIN_PFS_MTIOC3D	0x02
/** Multi Timer Unit Channel 3 Clock B I/O Pin Mode. */
#define	PORT_PIN_PFS_MTIOC3B	0x02
/** Multi Timer Unit Channel 4 Clock A I/O Pin Mode. Setting for PORTB */
#define	PORT_PIN_PFS_PORTB_MTIOC4A	0x02
/** Multi Timer Unit Channel 4 Clock C I/O Pin Mode. */
#define	PORT_PIN_PFS_PORTB_MTIOC4C	0x02
/** Multi Timer Unit Channel 1 Clock B I/O Pin Mode.  */
#define	PORT_PIN_PFS_PORTB_MTIOC1B	0x02
/** Multi Timer Unit Channel 1 Clock A I/O Pin Mode.  */
#define	PORT_PIN_PFS_PORTE_MTIOC1A	0x02
/** Multi Timer Unit Channel 2 Clock B I/O Pin Mode.  */
#define PORT_PIN_PFS_PORTE_MTIOC2B
/** Multi Timer Unit Input for Ext. Clk Pin Mode. */
#define	PORT_PIN_PFS_MTCLK		0x02
/** TMR External Clock Input Pin Mode. */
#define	PORT_PIN_PFS_TMCI		0x05
/** TMR Compare Match Output Pin Mode. */
#define	PORT_PIN_PFS_TMO		0x05
/** TMR Counter Reset Input Pin Mode. */
#define	PORT_PIN_PFS_TMRI		0x05
/** MTU Port Output Enable 2 Input Pin Mode. */
#define	PORT_PIN_PFS_POE		0x07
/** RTC Output pin for 1-Hz clock. Pin Mode. */
#define	PORT_PIN_PFS_RTCOUT		0x07
/** CAC Port input clock freq. measur. Input Pin Mode. */
#define	PORT_PIN_PFS_CACREF		0x07
/** 12-bit ADC Port input external trigger Input Pin Mode. */
#define	PORT_PIN_PFS_ADTRG		0x09
/** SCIc (USART and SPI) Input/Output Clock I/O Pin Mode. */
#define	PORT_PIN_PFS_SCK		0x0A
/** SCIc (USART) Received data Input Pin Mode. */
#define	PORT_PIN_PFS_RXD		0x0A
/** SCIc (USART) Transmitted data Output Pin Mode. */
#define	PORT_PIN_PFS_TXD		0x0A
/** SCIc (I2C) i2c clock pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SSCL		0x0A
/** SCIc (I2C) i2c data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SSDA		0x0A
/** SCIc (SPI) slave transmission data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SMISO		0x0A
/** SCIc (SPI) master transmission data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SMOSI		0x0A
/** SCIc (USART and SPI (SCI6)) Input/Output Clock I/O Pin Mode. */
#define	PORT_PIN_PFS_SCK6		0x0B
/** SCIc (USART (SCI6)) Received data Input Pin Mode. */
#define	PORT_PIN_PFS_RXD6		0x0B
/** SCIc (USART (SCI6)) Transmitted data Output Pin Mode. */
#define	PORT_PIN_PFS_TXD6		0x0B
/** SCIc (I2C (SCI6)) i2c clock pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SSCL6		0x0B
/** SCIc (I2C (SCI6)) i2c data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SSDA6		0x0B
/** SCIc (SPI (SCI6)) slave transmission data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SMISO6		0x0B
/** SCIc (SPI (SCI6)) master transmission data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SMOSI6		0x0B
/** SCIc (SPI) chip select Input Pin Mode. */
#define	PORT_PIN_PFS_SS			0x0B
/** SCIc (USART) CTS Input Pin Mode. */
#define	PORT_PIN_PFS_CTS		0x0B
/** SCIc (USART)CTS Output Pin Mode. */
#define	PORT_PIN_PFS_RTS		0x0B
/** SCIc (SPI (SCI6)) chip select Input Pin Mode. */
#define	PORT_PIN_PFS_SS6		0x0B
/** SCIc (USART (SCI6)) CTS Input Pin Mode. */
#define	PORT_PIN_PFS_CTS6		0x0B
/** SCIc (USART (SCI6))CTS Output Pin Mode. */
#define	PORT_PIN_PFS_RTS6		0x0B
/** SCId (USART and SPI (SCI12)) Input/Output Clock I/O Pin Mode. */
#define	PORT_PIN_PFS_SCK12		0x0C
/** SCId (USART (SCI12)) Received data Input Pin Mode. */
#define	PORT_PIN_PFS_RXD12		0x0C
/** SCId (USART (SCI12)) Extended Received data Input Pin Mode. */
#define	PORT_PIN_PFS_RXDX12		0x0C
/** SCId (USART (SCI12)) Transmitted data Output Pin Mode. */
#define	PORT_PIN_PFS_TXD12		0x0C
/** SCId (USART (SCI12)) Extended Transmitted data Output Pin Mode. */
#define	PORT_PIN_PFS_TXDX12		0x0C
/** SCId (I2C (SCI12)) i2c clock pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SSCL12		0x0C
/** SCId (I2C (SCI12)) i2c data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SSDA12		0x0C
/** SCId (SPI (SCI12)) slave transmission data I/O Pin Mode. */
#define	PORT_PIN_PFS_SMISO12	0x0C
/** SCId (SPI (SCI12)) master transmission data pin I/O Pin Mode. */
#define	PORT_PIN_PFS_SMOSI12	0x0C
/** SCId (SPI (SCI12)) chip select Input Pin Mode. */
#define	PORT_PIN_PFS_SS12		0x0C
/** SCId (USART (SCI12)) CTS Input Pin Mode. */
#define	PORT_PIN_PFS_CTS12		0x0C
/** SCId (USART (SCI12))CTS Output Pin Mode. */
#define	PORT_PIN_PFS_RTS12		0x0C
/** SCId (USART (SCI12)) SCId (USART (SCI12))data reception/transmission I/O 
 * Pin Mode. 
 */
#define	PORT_PIN_PFS_SIOX12		0x0C
/** RSPI Clock I/O Pin Mode. */
#define	PORT_PIN_PFS_RSPCKA		0x0D
/** RSPI Input/output from the master I/O Pin Mode. */
#define	PORT_PIN_PFS_MOSIA		0x0D
/** RSPI Input/output from the slave I/O Pin Mode. */
#define	PORT_PIN_PFS_MISOA		0x0D
/** RSPI slave select I/O Pin Mode. */
#define	PORT_PIN_PFS_SSLA		0x0D
/** RIIC Input/output clock pin for i2c bus interface I/O Pin Mode. */
#define	PORT_PIN_PFS_SCL		0x0C
/** RIIC Input/output data pin for i2c bus interface I/O Pin Mode. */
#define	PORT_PIN_PFS_SDA		0x0C
/** RIIC clock pin used for Deep Standby cancel signal Input Pin Mode.*/
#define	PORT_PIN_PFS_SCL_DS		0x0C
/** RIIC  data pin used for Deep Standby cancel signal Input Pin Mode.*/
#define	PORT_PIN_PFS_SDA_DS		0x0C

/** DIO Pin Mode. */
#define	PORT_PIN_MODE_DIO	0x00000000
/**Set Port Pin for IRQ input  */
#define PORT_PIN_MODE_ISEL	0x00000001
/**Set Port Pin as Analog Input/Output  */
#define PORT_PIN_MODE_ASEL	0x00000002
/** SCI Pin Mode. */
#define	PORT_PIN_MODE_SCI	0x00000003
/** SPI Pin Mode. */
#define	PORT_PIN_MODE_SPI	0x00000004

/** Number of Port Pin Modes. */
#define	PORT_PIN_MODES_NUMBER	(PORT_PIN_MODE_SPI + 1)
/*
 * Port Pin Mode Hardware Configuration Data Values.
 */
 /**< Port Function Selection Mask  */
#define	PORT_PIN_HW_CFG_PFS_M			0x0000000F
/**< Port DIO Selection  */	
#define	PORT_PIN_HW_CFG_DIO				0x00000010
/**< Port IRQ Selection  */	
#define	PORT_PIN_HW_CFG_ISEL			0x00000020
/**< Port Analog Selection */
#define	PORT_PIN_HW_CFG_ASEL			0x00000040
/**< Pull-Up Select	      */	
#define PORT_PIN_HW_CFG_PULL_UP			0x00000080
/**< Opend Drain Select	  */
#define PORT_PIN_HW_CFG_OPEN_DRAIN		0x00000100
/**< 4-mA Drive Select	  */
#define PORT_PIN_HW_CFG_DRVCAP_LOW		0x00000200
/**< 8-mA Drive Select	  */
#define PORT_PIN_HW_CFG_DRVCAP_HIGH		0x00000400	
 
/*
 * Port Pins MPCs
 */
/** Port 0 - Pin 5 12-bit ADC input external trigger */
#define PORT_0_PIN7_ADTRG0	PORT_PIN_PFS_ADTRG
/** Port 1 - Pin 2 TMR1 External Clock Input Pin */
#define PORT_1_PIN2_TMCI1	PORT_PIN_PFS_TMCI
/** Port 1 - Pin 2  RIIC I/O clock pin for i2c bus interface */
#define PORT_1_PIN2_SCL	PORT_PIN_PFS_SCL
/** Port 1 - Pin 3  MTU 2 channel 0 Input Capture / Output Compare Pin. */
#define PORT_1_PIN3_MTIOC0B	PORT_PIN_PFS_MTIOC
/** Port 1 - Pin 3  TMR3 Compare Match Output Pin. */
#define PORT_1_PIN3_TMO3	PORT_PIN_PFS_TMO
/** Port 1 - Pin 3  I/O data pin for i2c bus interface */
#define PORT_1_PIN3_SDA	PORT_PIN_PFS_SDA
/** Port 1 - Pin 4   MTU 2 channel 3 Input Capture/Output Compare Pin.*/
#define PORT_1_PIN4_MTIOC3A	PORT_PIN_PFS_MTIOC
/** Port 1 - Pin 4   MTU Input A for External Clock Pin.*/
#define PORT_1_PIN4_MTCLKA	PORT_PIN_PFS_MTCLK
/** Port 1 - Pin 4   TMR2 Counter Reset Input Pin.*/
#define PORT_1_PIN4_TMRI2	PORT_PIN_PFS_TMRI
/** Port 1 - Pin 4   SCIc (USART) CTS1 Input Pin.*/
#define PORT_1_PIN4_CTS1	PORT_PIN_PFS_CTS
/** Port 1 - Pin 4   SCIc (USART) RTS1 Output Pin.*/
#define PORT_1_PIN4_RTS1	PORT_PIN_PFS_RTS
/** Port 1 - Pin 4   SCIc (USART) SS1 Input Pin.*/
#define PORT_1_PIN4_SS1	PORT_PIN_PFS_SS
/** Port 1 - Pin 5   MTU 2 channel 0 CLK B Input Capture / Output Compare Pin.*/
#define PORT_1_PIN5_MTIOC0B	PORT_PIN_PFS_MTIOC
/** Port 1 - Pin 5   MTU Input B for External Clock Pin.*/
#define PORT_1_PIN5_MTCLKB	PORT_PIN_PFS_MTCLK
/** Port 1 - Pin 5 TMR2 External Clock Input Pin */
#define PORT_1_PIN5_TMCI2	PORT_PIN_PFS_TMCI
/** Port 1 - Pin 5 SCIc (USART) channel 1 Received data Input Pin. */
#define PORT_1_PIN5_RXD1	PORT_PIN_PFS_RXD
/** Port 1 - Pin 5 SCIc (SPI) channel 1 slave transmission data I/O Pin. */
#define PORT_1_PIN5_SMISO1	PORT_PIN_PFS_SMISO
/** Port 1 - Pin 5 SCIc (I2C) channel 1 clock pin. */
#define PORT_1_PIN5_SSCL1	PORT_PIN_PFS_SSCL
/** Port 1 - Pin 6   MTU 2 channel 3 CLK C Input Capture / Output Compare Pin.*/
#define PORT_1_PIN6_MTIOC3C	PORT_PIN_PFS_MTIOC
/** Port 1 - Pin 6   MTU 2 channel 3 CLK D Input Capture / Output Compare Pin.*/
#define PORT_1_PIN6_MTIOC3D	PORT_PIN_PFS_MTIOC3D
/** Port 1 - Pin 6   TMR2 Compare Match Output Pin. */
#define PORT_1_PIN6_TMO2	PORT_PIN_PFS_TMO
/** Port 1 - Pin 6   RTC Output pin for 1-Hz clock. */
#define PORT_1_PIN6_RTCOUT	PORT_PIN_PFS_RTCOUT
/** Port 1 - Pin 6 12-bit ADC input external trigger Pin. */
#define PORT_1_PIN6_ADTRG0	PORT_PIN_PFS_ADTRG
/** Port 1 - Pin 6 SCIc (USART) channel 1 Transmitted data Output Pin. */
#define PORT_1_PIN6_TXD1	PORT_PIN_PFS_TXD
/** Port 1 - Pin 6 SCIc (SPI1) master transmission data pin I/O Pin. */
#define PORT_1_PIN6_SMOSI1	PORT_PIN_PFS_SMOSI
/** Port 1 - Pin 6 SCIc (I2C1) i2c data pin I/O Pin. */
#define PORT_1_PIN6_SSDA1	PORT_PIN_PFS_SSDA
/** Port 1 - Pin 6 RSPI Input/output from the master I/O Pin. */
#define PORT_1_PIN6_MOSIA	PORT_PIN_PFS_MOSIA
/** Port 1 - RIIC clock pin used for Deep Standby cancel signal Input Pin. */
#define PORT_1_PIN6_SCL_DS	PORT_PIN_PFS_SCL_DS
/** Port 1 - Pin 7   MTU 2 channel 3 CLK A Input Capture / Output Compare Pin.*/
#define PORT_1_PIN6_MTIOC3A	PORT_PIN_PFS_MTIOC
/** Port 1 - Pin 7   MTU 2 channel 3 CLK B Input Capture / Output Compare Pin.*/
#define PORT_1_PIN6_MTIOC3B	PORT_PIN_PFS_MTIOC3B
/** Port 1 - Pin 7  TMR1 Compare Match Output Pin. */
#define PORT_1_PIN7_TMO1	PORT_PIN_PFS_TMO
/** Port 1 - Pin 7  MTU Port Output Enable 2 Input Pin.  POE8# */
#define PORT_1_PIN7_POE8	PORT_PIN_PFS_POE
/** Port 1 - Pin 7  SCIc channel 1 Input/Output Clock I/O Pin.*/
#define PORT_1_PIN7_SCK1	PORT_PIN_PFS_SCK
/** Port 1 - RSPI Input/output from the slave I/O Pin. */
#define PORT_1_PIN6_MISOA	PORT_PIN_PFS_MISOA
/** Port 1 - RIIC  data pin used for Deep Standby cancel signal Input Pin. */
#define PORT_1_PIN6_SDA_DS	PORT_PIN_PFS_SDA_DS
/** Port 2 - MTU 2 channel 1 CLK A Input Capture / Output Compare Pin. */
#define PORT_2_PIN0_MTIOC1A	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 0 TMRO Counter Reset Input Pin. */
#define PORT_2_PIN0_TMRI0	PORT_PIN_PFS_TMRI
/** Port 2 - Pin 0 SCIc (USART) channel 0 Transmitted data Output Pin. */
#define PORT_2_PIN0_TXD0	PORT_PIN_PFS_TXD
/** Port 2 - Pin 0 SCIc (SPI0) master transmission data pin I/O Pin. */
#define PORT_2_PIN0_SMOSI0	PORT_PIN_PFS_SMOSI
/** Port 2 - Pin 0 SCIc (I2C0) i2c data pin I/O Pin. */
#define PORT_2_PIN0_SSDA0	PORT_PIN_PFS_SSDA
/** Port 2 - Pin 1  MTU 2 channel 1 CLK B Input Capture / Output Compare Pin. */
#define PORT_2_PIN1_MTIOC1B	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 1  TMR0 External Clock Input Pin. */
#define PORT_2_PIN1_TMCI0	PORT_PIN_PFS_TMCI
/** Port 2 - Pin 1  SCIc (USART) channel 0 Received data Input Pin. */
#define PORT_2_PIN1_RXD0	PORT_PIN_PFS_RXD
/** Port 2 - Pin 1  SCIc (SPI) channel 0 slave transmission data I/O Pin. */
#define PORT_2_PIN1_SMISO0	PORT_PIN_PFS_SMISO
/** Port 2 - Pin 1  SCIc (I2C) channel 0 clock pin. */
#define PORT_2_PIN1_SSCL0	PORT_PIN_PFS_SSCL
/** Port 2 - Pin 2 MTU 2 channel 3 CLK B Input Capture / Output Compare Pin. */
#define PORT_2_PIN2_MTIOC3B	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 2 MTU Input C for External Clock Pin. */
#define PORT_2_PIN2_MTCLKC	PORT_PIN_PFS_MTCLK
/** Port 2 - Pin 2 TMR0 Compare Match Output Pin. */
#define PORT_2_PIN2_TMO0	PORT_PIN_PFS_TMO
/** Port 2 - Pin 2 SCIc (USART and SPI)channel 0 Input/Output Clock I/O Pin. */
#define PORT_2_PIN2_SCK0	PORT_PIN_PFS_SCK
/** Port 2 - Pin 3 MTU 2 channel 3 CLK D Input Capture / Output Compare Pin. */
#define PORT_2_PIN3_MTIOC3D	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 3 MTU Input D for External Clock Pin. */
#define PORT_2_PIN3_MTCLKD	PORT_PIN_PFS_MTCLK
/** Port 2 - Pin 3  SCIc (USART) CTS channel 0 Input Pin. */
#define PORT_2_PIN3_CTS0	PORT_PIN_PFS_CTS
/** Port 2 - Pin 3  SCIc (USART) RTS channel 0 Input Pin. */
#define PORT_2_PIN3_RTS0	PORT_PIN_PFS_RTS
/** Port 2 - Pin 3 SCIc (USART) SS channel 0 Input Pin. */
#define PORT_2_PIN3_SS0		PORT_PIN_PFS_SS
/** Port 2 - Pin 4 MTU 2 channel 4 CLK A Input Capture / Output Compare Pin. */
#define PORT_2_PIN4_MTIOC4A	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 4 MTU Input A for External Clock Pin. */
#define PORT_2_PIN4_MTCLKA	PORT_PIN_PFS_MTCLK
/** Port 2 - Pin 4 TMR1 Counter Reset Input Pin.*/
#define PORT_2_PIN4_TMRI1	PORT_PIN_PFS_TMRI
/** Port 2 - Pin 5  MTU 2 channel 4 CLK C Input Capture / Output Compare Pin. */
#define PORT_2_PIN5_MTIOC4C	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 5  MTU Input B for External Clock Pin. */
#define PORT_2_PIN5_MTCLKB	PORT_PIN_PFS_MTCLK
/** Port 2 - Pin 5  12-bit ADC input external trigger Pin. */
#define PORT_2_PIN5_ADTRG0	PORT_PIN_PFS_ADTRG
/** Port 2 - Pin 6 MTU 2 channel 2 CLK A Input Capture / Output Compare Pin. */
#define PORT_2_PIN6_MTIOC2A	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 6 TMR1 Compare Match Output Pin. */
#define PORT_2_PIN6_TMO1	PORT_PIN_PFS_TMO
/** Port 2 - Pin 6 SCIc (USART) channel 1 Transmitted data Output Pin. */
#define PORT_2_PIN6_TXD1	PORT_PIN_PFS_TXD
/** Port 2 - Pin 6 SCIc (SPI1) master transmission data pin I/O Pin. */
#define PORT_2_PIN6_SMOSI1	PORT_PIN_PFS_SMOSI
/** Port 2 - Pin 6 SCIc (I2C1) i2c data pin I/O Pin. */
#define PORT_2_PIN6_SSDA1	PORT_PIN_PFS_SSDA
/** Port 2 - Pin 7 MTU 2 channel 2 CLK B Input Capture / Output Compare Pin. */
#define PORT_2_PIN7_MTIOC2B	PORT_PIN_PFS_MTIOC
/** Port 2 - Pin 7 TMR3 External Clock Input Pin. */
#define PORT_2_PIN7_TMCI3	PORT_PIN_PFS_TMCI
/** Port 2 - Pin 7 SCIc (USART and SPI)channel 1 Input/Output Clock I/O Pin. */
#define PORT_2_PIN7_SCK1	PORT_PIN_PFS_SCK
/** Port 3 - Pin 0 MTU 2 channel 4 CLK B Input Capture / Output Compare Pin. */
#define PORT_3_PIN0_MTIOC4B	PORT_PIN_PFS_MTIOC
/** Port 3 - Pin 0 TMR3 Counter Reset Input Pin. */
#define PORT_3_PIN0_TMRI3	PORT_PIN_PFS_TMRI
/** Port 3 - Pin 0 MTU Port Output Enable 2 Input Pin.  POE8# */
#define PORT_3_PIN0_POE8	PORT_PIN_PFS_POE
/** Port 3 - Pin 0 SCIc (USART) channel 1 Received data Input Pin. */
#define PORT_3_PIN0_RXD1	PORT_PIN_PFS_RXD
/** Port 3 - Pin 0 SCIc (SPI) channel 1 slave transmission data I/O Pin. */
#define PORT_3_PIN0_SMISO1	PORT_PIN_PFS_SMISO
/** Port 3 - Pin 0 SCIc (I2C) channel 1 clock pin. */
#define PORT_3_PIN0_SSCL1	PORT_PIN_PFS_SSCL
/** Port 3 - Pin 1 MTU 2 channel 4 CLK D Input Capture / Output Compare Pin. */
#define PORT_3_PIN1_MTIOC4D	PORT_PIN_PFS_MTIOC
/** Port 3 - Pin 1 TMR2 External Clock Input Pin. */
#define PORT_3_PIN1_TMCI2	PORT_PIN_PFS_TMCI
/** Port 3 - Pin 1 SCIc (USART) CTS channel 1 Input Pin. */
#define PORT_3_PIN1_CTS1	PORT_PIN_PFS_CTS
/** Port 3 - Pin 1 SCIc (USART) RTS channel 1 Input Pin. */
#define PORT_3_PIN1_RTS1	PORT_PIN_PFS_RTS
/** Port 3 - Pin 1 SCIc (USART) SS channel 1 Input Pin. */
#define PORT_3_PIN1_SS1		PORT_PIN_PFS_SS
/** Port 3 - Pin 2  MTU 2 channel 0 CLK D Input Capture / Output Compare Pin.*/
#define PORT_3_PIN2_MTIOC0D	PORT_PIN_PFS_MTIOC
/** Port 3 - Pin 2  TMR3 Compare Match Output Pin. */
#define PORT_3_PIN2_TMO3	PORT_PIN_PFS_TMO
/** Port 3 - Pin 2  RTC Output pin for 1-Hz clock. Pin */
#define PORT_3_PIN2_RTCOUT	PORT_PIN_PFS_RTCOUT
/** Port 3 - Pin 2 SCIc (USART (SCI6)) Transmitted data Output Pin. */
#define PORT_3_PIN2_TXD6	PORT_PIN_PFS_TXD6
/** Port 3 - Pin 2 SCIc (SPI (SCI6)) master transmission data pin I/O Pin. */
#define PORT_3_PIN2_SMOSI6	PORT_PIN_PFS_SMOSI6
/** Port 3 - Pin 2 SCIc (I2C (SCI6)) i2c data pin I/O Pin. */
#define PORT_3_PIN2_SSDA6	PORT_PIN_PFS_SSDA6
/** PORT 3 - Pin 3 MTU 2 channel 0 CLK D Input Capture / Output Compare Pin.*/
#define PORT_3_PIN3_MTIOC0D	PORT_PIN_PFS_MTIOC
/** Port 3 - Pin 3  TMR3 Counter Reset Input Pin. */
#define PORT_3_PIN3_TMRI3	PORT_PIN_PFS_TMRI
/** Port 3 - Pin 3  MTU Port Output Enable 2 Input Pin.  POE3# */
#define PORT_3_PIN3_POE3	PORT_PIN_PFS_POE
/** Port 3 - Pin 3  (USART (SCI6)) Received data Input Pin Mode. */
#define PORT_3_PIN3_RXD6	PORT_PIN_PFS_RXD6
/** Port 3 - Pin 3  SCIc (SPI (SCI6)) slave transmission data I/O Pin. */
#define PORT_3_PIN3_SMISO6	PORT_PIN_PFS_SMISO6
/** Port 3 - Pin 3  SCIc (I2C (SCI6)) i2c clock pin I/O Pin. */
#define PORT_3_PIN3_SSCL6	PORT_PIN_PFS_SSCL6
/** Port 3 - Pin 4  MTU 2 channel 0 CLK A Input Capture / Output Compare Pin.*/
#define PORT_3_PIN3_MTIOC0A	PORT_PIN_PFS_MTIOC
/** Port 3 - Pin 4   TMR3 External Clock Input Pin. */
#define PORT_3_PIN3_TMCI3	PORT_PIN_PFS_TMCI
/** Port 3 - Pin 4   MTU Port Output Enable 2 Input Pin.  POE2# */
#define PORT_3_PIN3_POE2	PORT_PIN_PFS_POE
/** Port 3 - Pin 4  SCIc (USART and SPI (SCI6)) Input/Output Clock I/O Pin. */
#define PORT_3_PIN3_SCK6	PORT_PIN_PFS_SCK6
/** Port 5 - Pin 4 MTU 2 channel 4 CLK B Input Capture / Output Compare Pin.*/
#define PORT5_PIN4_MTIOC4B	PORT_PIN_PFS_MTIOC
/** Port 5 - Pin 4 TMR1 External Clock Input Pin. */
#define PORT5_PIN4_TMCI1	PORT_PIN_PFS_TMCI
/** Port 5 - Pin 4 MTU 2 channel 4 CLK D Input Capture / Output Compare Pin.*/
#define PORT5_PIN4_MTIOC4D	PORT_PIN_PFS_MTIOC
/** Port 5 - Pin 4 TMR3 Compare Match Output Pin. */
#define PORT5_PIN4_TMO3		PORT_PIN_PFS_TMO
/** Port A - Pin 0  MTU 2 channel 4 CLK A Input Capture / Output Compare Pin.*/
#define PORTA_PIN0_MTIOC4A	PORT_PIN_PFS_MTIOC
/** Port A - Pin 0  CAC Port input clock freq. measur. Input Pin. */
#define PORTA_PIN0_CACREF	PORT_PIN_PFS_CACREF
/** Port A - Pin 0  RSPI channel 1 slave select output Pin. */
#define PORTA_PIN0_SSLA1	PORT_PIN_PFS_SSLA
/** Port A - Pin 1  MTU 2 channel 0 CLK B Input Capture / Output Compare Pin.*/
#define PORTA_PIN1_MTIOC0B	PORT_PIN_PFS_MTIOC
/** Port A - Pin 1 MTU Input C for External Clock Pin.*/
#define PORTA_PIN1_MTCLKC	PORT_PIN_PFS_MTCLK
/** Port A - Pin 1 SCIc channel 5 Input/Output Clock I/O Pin.  */
#define PORTA_PIN1_SCK5		PORT_PIN_PFS_SCK
/** Port A - Pin 1 RSPI channel 2 slave select output Pin.*/
#define PORTA_PIN1_SSLA2	PORT_PIN_PFS_SSLA
/** Port A - Pin 2 SCIc (USART) channel 5 Received data Input Pin.*/
#define PORTA_PIN2_RXD5		PORT_PIN_PFS_RXD
/** Port A - Pin 2 SCIc channel 5 slave transmission data I/O Pin.*/
#define PORTA_PIN2_SMISO5	PORT_PIN_PFS_SMISO
/** Port A - Pin 2 SCIc (I2C) channel 5 clock pin. */
#define PORTA_PIN2_SSCL5	PORT_PIN_PFS_SSCL
/** Port A - Pin 2 RSPI channel 3 slave select output Pin.*/
#define PORTA_PIN2_SSLA3	PORT_PIN_PFS_SSLA
/** Port A - Pin 3  MTU 2 channel 0 CLK D Input Capture / Output Compare Pin.*/
#define PORTA_PIN3_MTIOC0D	PORT_PIN_PFS_MTIOC
/** Port A - Pin 3  MTU Input D for External Clock Pin.*/
#define PORTA_PIN3_MTCLKD	PORT_PIN_PFS_MTCLK
/** Port A - Pin 3  SCIc (USART) channel 5 Received data Input Pin.*/
#define PORTA_PIN3_RXD5		PORT_PIN_PFS_RXD
/** Port A - Pin 3  SCIc channel 5 slave transmission data I/O Pin.*/
#define PORTA_PIN3_SMISO5	PORT_PIN_PFS_SMISO
/** Port A - Pin 3  SCIc (I2C) channel 5 clock pin. */
#define PORTA_PIN3_SSCL5	PORT_PIN_PFS_SSCL5
/** Port A - Pin 4  MTU module 5U Input Capture Pin Mode.*/
#define PORTA_PIN4_MTIC5U	PORT_PIN_PFS_MTIC5
/** Port A - Pin 4  MTU Input A for External Clock Pin.*/
#define PORTA_PIN4_MTCLKA	PORT_PIN_PFS_MTCLK
/** Port A - Pin 4  TMRO Counter Reset Input Pin. */
#define PORTA_PIN4_TMRI0	PORT_PIN_PFS_TMRI
/** Port A - Pin 4  SCIc (USART) channel 5 Received data Input Pin.*/
#define PORTA_PIN4_RXD5		PORT_PIN_PFS_RXD
/** Port A - Pin 4  SCIc channel 5 slave transmission data I/O Pin.*/
#define PORTA_PIN4_SMISO5	PORT_PIN_PFS_SMISO
/** Port A - Pin 4  SCIc (I2C) channel 5 clock pin. */
#define PORTA_PIN4_SSCL5	PORT_PIN_PFS_SSCL5
/** Port A - Pin 4  RSPI channel 0 slave select output Pin.*/
#define PORTA_PIN4_SSLA0	PORT_PIN_PFS_SSLA	
/** Port A - Pin 5  RSPI Clock I/O Pin Mode. */
#define PORTA_PIN5_RSPCKA	PORT_PIN_PFS_RSPCKA
/** Port A - Pin 6 MTU module 5U Input Capture Pin Mode.*/
#define PORTA_PIN6_MTIC5V	PORT_PIN_PFS_MTIC5
/** Port A - Pin 6 MTU Input B for External Clock Pin.*/
#define PORTA_PIN6_MTCLKB	PORT_PIN_PFS_MTCLK
/** Port A - Pin 6 TMR3 External Clock Input Pin. */
#define PORTA_PIN6_TMCI3	PORT_PIN_PFS_TMCI
/** Port A - Pin 6 MTU Port Output Enable 2 Input Pin.  POE2# */
#define PORTA_PIN6_POE2		PORT_PIN_PFS_POE
/** Port A - Pin 6  SCIc (USART) CTS channel 5 Input Pin. */
#define PORTA_PIN6_CTS5		PORT_PIN_PFS_CTS
/** Port A - Pin 6  SCIc (USART) RTS channel 5 Input Pin. */
#define PORTA_PIN6_RTS5		PORT_PIN_PFS_RTS
/** Port A - Pin 6 SCIc (USART) channel 5 Input Pin. */
#define PORTA_PIN6_SS5		PORT_PIN_PFS_SS
/** Port A - Pin 6 RSPI Input/output from the master I/O Pin. */
#define PORTA_PIN6_MOSIA	PORT_PIN_PFS_MOSIA
/** Port A - Pin 7 RSPI Input/output from the slave I/O Pin. */
#define PORTA_PIN7_MISOA	PORT_PIN_PFS_MISOA
/** Port B - Pin 0 MTU module 5U Input Capture Pin Mode.*/
#define PORTB_PIN0_MTIC5W	PORT_PIN_PFS_MTIC5
/** Port B - Pin 0 (USART (SCI6)) Received data Input Pin Mode. */
#define PORTB_PIN0_RXD6		PORT_PIN_PFS_RXD6
/** Port B - Pin 0 SCIc (SPI (SCI6)) slave transmission data I/O Pin.*/
#define PORTB_PIN0_SMISO6	PORT_PIN_PFS_SMISO6
/** Port B - Pin 0 SCIc (I2C (SCI6)) i2c clock pin I/O Pin. */
#define PORTB_PIN0_SSCL6	PORT_PIN_PFS_SSCL6
/** Port B - Pin 0 RSPI Clock I/O Pin Mode.*/
#define PORTB_PIN0_RSPCKA	PORT_PIN_PFS_RSPCKA
/** Port B - Pin 1 MTU 2 channel 0 CLK C Input Capture / Output Compare Pin.*/
#define PORTB_PIN1_MTIOC0C	PORT_PIN_PFS_MTIOC
/** Port B - Pin 1 MTU 2 channel 4 CLK C Input Capture / Output Compare Pin.*/
#define PORTB_PIN1_MTIOC4C	PORT_PIN_PFS_PORTB_MTIOC4C
/** Port B - Pin 1 TMR0 External Clock Input Pin.*/
#define PORTB_PIN1_TMCI0	PORT_PIN_PFS_TMCI
/** Port B - Pin 1 SCIc (USART (SCI6)) Transmitted data Output Pin Mode.*/
#define PORTB_PIN1_TXD6		PORT_PIN_PFS_TXD6
/** Port B - Pin 1 SCIc (SPI (SCI6)) master transmission data pin I/O Pin.*/
#define PORTB_PIN1_SMOSI6	PORT_PIN_PFS_SMOSI6
/** Port B - Pin 1 SCIc (I2C (SCI6)) i2c data pin I/O Pin. */
#define PORTB_PIN1_SSDA6	PORT_PIN_PFS_SSDA6
/** Port B - Pin 2 SCIc (USART) CTS channel 6 Input Pin. */
#define PORTB_PIN2_CTS6		PORT_PIN_PFS_CTS6
/** Port B - Pin 2 SCIc (USART) RTS channel 6 Input Pin. */
#define PORTB_PIN2_RTS6		PORT_PIN_PFS_RTS6
/** Port B - Pin 2 SCIc (USART) SS channel 6 Input Pin. */
#define PORTB_PIN2_SS6		PORT_PIN_PFS_SS6
/** Port B - Pin 3 MTU 2 channel 0 CLK A Input Capture / Output Compare Pin.*/
#define PORTB_PIN3_MTIOC0A	PORT_PIN_PFS_MTIOC
/** Port B - Pin 3 MTU 2 channel 4 CLK A Input Capture / Output Compare Pin.*/
#define PORTB_PIN3_MTIOC4A	PORT_PIN_PFS_PORTB_MTIOC4A
/** Port B - Pin 3 TMR0 Compare Match Output Pin. */
#define PORTB_PIN3_TMO0		PORT_PIN_PFS_TMO
/** Port B - Pin 3 MTU Port Output Enable 2 Input Pin.  POE3# */
#define PORTB_PIN3_POE3		PORT_PIN_PFS_POE
/** Port B - Pin 3 SCIc (USART and SPI (SCI6)) Input/Output Clock I/O Pin.*/
#define PORTB_PIN3_SCK6		PORT_PIN_PFS_SCK6
/** Port B - Pin 4 SCIc (USART) CTS channel 9 Input Pin.*/
#define PORTB_PIN4_CTS9		PORT_PIN_PFS_CTS
/** Port B - Pin 4 SCIc (USART) RTS9 Output Pin. */
#define PORTB_PIN4_RTS9		PORT_PIN_PFS_RTS
/** Port B - Pin 4 SCIc (USART) SS channel 9 Input Pin.*/
#define PORTB_PIN4_SS9		PORT_PIN_PFS_SS
/** Port B - Pin 5 MTU 2 channel 2 CLK A Input Capture / Output Compare Pin.*/
#define PORTB_PIN5_MTIOC2A	PORT_PIN_PFS_MTIOC
/** Port B - Pin 5 MTU 2 channel 2 CLK A Input Capture / Output Compare Pin.*/
#define PORTB_PIN5_MTIOC1B	PORT_PIN_PFS_PORTB_MTIOC1B
/** Port B - Pin 5 TMR1 Counter Reset Input Pin.*/
#define PORTB_PIN5_TMRI1	PORT_PIN_PFS_TMRI
/** Port B - Pin 5 MTU Port Output Enable 2 Input Pin.  POE1# */
#define PORTB_PIN5_POE1		PORT_PIN_PFS_POE
/** Port B - Pin 5 SCIc channel 9 Input/Output Clock I/O Pin. */
#define PORTB_PIN5_SCK9		PORT_PIN_PFS_SCK
/** Port B - Pin 6 MTU 2 channel 3 CLK D Input Capture / Output Compare Pin.*/
#define PORTB_PIN6_MTIOC3D	PORT_PIN_PFS_MTIOC
/** Port B - Pin 6 SCIc (USART) channel 9 Received data Input Pin.*/
#define PORTB_PIN6_RXD9		PORT_PIN_PFS_RXD
/** Port B - Pin 6 SCIc (SPI (SCI9)) slave transmission data I/O Pin. */
#define PORTB_PIN6_SMISO9	PORT_PIN_PFS_SMISO
/** Port B - Pin 6 SCIc (I2C) channel 9 clock pin. */
#define PORTB_PIN6_SSCL9	PORT_PIN_PFS_SSCL
/** Port B - Pin 7  MTU 2 channel 3 CLK B Input Capture / Output Compare Pin.*/
#define PORTB_PIN7_MTIOC3B	PORT_PIN_PFS_MTIOC
/** Port B - Pin 7  SCIc (USART) channel 9 Transmitted data Output Pin.*/
#define PORTB_PIN7_TXD9		PORT_PIN_PFS_TXD
/** Port B - Pin 7  SCIc (SPI9) master transmission data pin I/O Pin.*/
#define PORTB_PIN7_SMOSI9	PORT_PIN_PFS_SMOSI
/** Port B - Pin 7  SCIc (I2C (SCI9)) i2c data pin I/O Pin. */
#define PORTB_PIN7_SSDA9	PORT_PIN_PFS_SSDA
/** Port C - Pin 0 MTU 2 channel 3 CLK C Input Capture / Output Compare Pin.*/ 
#define PORTC_PIN0_MTIOC3C	PORT_PIN_PFS_MTIOC
/** Port C - Pin 0 SCIc (USART) CTS5 Input Pin.*/
#define PORTC_PIN0_CTS5		PORT_PIN_PFS_CTS
/** Port C - Pin 0 SCIc (USART) RTS5 Output Pin.*/ 
#define PORTC_PIN0_RTS5		PORT_PIN_PFS_RTS
/** Port C - Pin 0 SCIc (USART) SS channel 5 Input Pin.*/ 
#define PORTC_PIN0_SS		PORT_PIN_PFS_SS
/** Port C - Pin 0 RSPI channel 1 slave select output Pin.*/
#define PORTC_PIN0_SSLA1	PORT_PIN_PFS_SSLA
/** Port C - Pin 1 MTU 2 channel 3 CLK C Input Capture / Output Compare Pin.*/ 
#define PORTC_PIN1_MTIOC3A	PORT_PIN_PFS_MTCIO
/** Port C - Pin 1 SCIc channel 5 Input/Output Clock I/O Pin. */ 
#define PORTC_PIN1_SCK5		PORT_PIN_PFS_SCK
/** Port C - Pin 1 RSPI channel 2 slave select output Pin.*/ 
#define PORTC_PIN1_SSLA2	PORT_PIN_PFS_SSLA
/** Port C - Pin 2 MTU 2 channel 4 CLK B Input Capture / Output Compare Pin.*/ 
#define PORTC_PIN2_MTIOC4B	PORT_PIN_PFS_MTIOC
/** Port C - Pin 2 SCIc (USART) channel 5 Received data Input Pin.*/ 
#define PORTC_PIN2_RXD5		PORT_PIN_PFS_RXD
/** Port C - Pin 2 SCIc (SPI (SCI5)) slave transmission data I/O Pin. */ 
#define PORTC_PIN2_SMISO5	PORT_PIN_PFS_SMISO
/** Port C - Pin 2 SCIc (I2C) channel 5 clock pin. */ 
#define PORTC_PIN2_SSCL5	PORT_PIN_PFS_SSCL
/** Port C - Pin 2 RSPI channel 3 slave select output Pin.*/
#define PORTC_PIN2_SSLA3	PORT_PIN_PFS_SSLA
/** Port C - Pin 3 MTU 2 channel 4 CLK D Input Capture / Output Compare Pin.*/  
#define PORTC_PIN3_MTIOC4D	PORT_PIN_PFS_MTIOC
/** Port C - Pin 3 SCIc (USART) channel 5 Transmitted data Output Pin.*/ 
#define PORTC_PIN3_TXD5		PORT_PIN_PFS_TXD
/** Port C - Pin 3 SCIc (SPI5) master transmission data pin I/O Pin.*/ 
#define PORTC_PIN3_SMOSI5	PORT_PIN_PFS_SMOSI
/** Port C - Pin 3 SCIc i2c channel 5 data pin I/O Pin. */ 
#define PORTC_PIN3_SSDA5	PORT_PIN_PFS_SSDA
/** Port C - Pin 4 MTU 2 channel 3 CLK D Input Capture / Output Compare Pin.*/ 
#define PORTC_PIN4_MTIOC3D	PORT_PIN_PFS_MTIOC
/** Port C - Pin 4 MTU Input C for External Clock Pin.*/ 
#define PORTC_PIN4_MTCLKC	PORT_PIN_PFS_MTCLK
/** Port C - Pin 4	TMR1 External Clock Input Pin.*/ 
#define PORTC_PIN4_TMCI1	PORT_PIN_PFS_TMCI1
/** Port C - Pin 4 MTU Port Output Enable 2 Input Pin.  POE0# */
#define PORTC_PIN4_POE0		PORT_PIN_PFS_POE
/** Port C - Pin 4 SCIc channel 5 Input/Output Clock I/O Pin. */ 
#define PORTC_PIN4_SCK5		PORT_PIN_PFS_SCK
/** Port C - Pin 4 SCIc (USART) CTS8 Input Pin.*/  
#define PORTC_PIN4_CTS8		PORT_PIN_PFS_CTS
/** Port C - Pin 4 SCIc (USART) RTS8 Output Pin.*/ 
#define PORTC_PIN4_RTS8		PORT_PIN_PFS_RTS
/** Port C - Pin 4 SCIc (USART) SS channel 8 Input Pin.*/  
#define PORTC_PIN4_SS8		PORT_PIN_PFS_SS
/** Port C - Pin 4 RSPI channel 0 slave select output Pin.*/ 
#define PORTC_PIN4_SSLA0	PORT_PIN_PFS_SSLA
/** Port C - Pin 5 MTU 2 channel 3 CLK B Input Capture / Output Compare Pin.*/ 
#define PORTC_PIN5_MTIOC3B	PORT_PIN_PFS_MTIOC
/** Port C - Pin 5 MTU Input D for External Clock Pin.*/ 
#define PORTC_PIN5_MTCLKD	PORT_PIN_PFS_MTCLK
/** Port C - Pin 5 TMR2 Counter Reset Input Pin.*/
#define PORTC_PIN5_TMRI2	PORT_PIN_PFS_TMRI
/** Port C - Pin 5 SCIc channel 8 Input/Output Clock I/O Pin. */ 
#define PORTC_PIN5_SCK8		PORT_PIN_PFS_SCK
/** Port C - Pin 5 RSPI Clock I/O Pin Mode. */ 
#define PORTC_PIN5_RSPCKA	PORT_PIN_PFS_RSPCKA
/** Port C - Pin 6 MTU 2 channel 3 CLK C Input Capture / Output Compare Pin.*/ 
#define PORTC_PIN6_MTIOC3C	PORT_PIN_PFS_MTIOC
/** Port C - Pin 6 MTU Input A for External Clock Pin.*/ 
#define PORTC_PIN6_MTCLKA	PORT_PIN_PFS_MTCLK
/** Port C - Pin 6 TMR2 External Clock Input Pin.*/ 
#define PORTC_PIN6_TMCI2	PORT_PIN_PFS_TMCI
/** Port C - Pin 6 SCIc (USART) channel 8 Received data Input Pin.*/ 
#define PORTC_PIN6_RXD8		PORT_PIN_PFS_RXD
/** Port C - Pin 6 SCIc (SPI (SCI8)) slave transmission data I/O Pin. */ 
#define PORTC_PIN6_SMISO8	PORT_PIN_PFS_SMISO
/** Port C - Pin 6 SCIc (I2C) channel 8 clock pin. */ 
#define PORTC_PIN6_SSCL8	PORT_PIN_PFS_SSCL
/** Port C - Pin 6 RSPI Input/output from the master I/O Pin. */ 
#define PORTC_PIN6_MOSIA	PORT_PIN_PFS_MOSIA
/** Port C - Pin 7 MTU 2 channel 3 CLK A Input Capture / Output Compare Pin.*/  
#define PORTC_PIN7_MTIOC3A	PORT_PIN_PFS_MTIOC
/** Port C - Pin 7 MTU Input B for External Clock Pin.*/ 
#define PORTC_PIN7_MTCLKB	PORT_PIN_PFS_MTCLK
/** Port C - Pin 7 TMR2 Compare Match Output Pin. */ 
#define PORTC_PIN7_TMO2		PORT_PIN_PFS_TMO
/** Port C - Pin 7 CAC Port input clock freq. measur. Input Pin. */ 
#define PORTC_PIN7_CACREF	PORT_PIN_PFS_CACREF
/** Port C - Pin 7 SCIc (USART) channel 8 Transmitted data Output Pin.*/  
#define PORTC_PIN7_TXD8		PORT_PIN_PFS_TXD
/** Port C - Pin 7 SCIc (SPI8) master transmission data pin I/O Pin.* 
#define PORTC_PIN7_SMOSI8	PORT_PIN_PFS_SMOSI
/** Port C - Pin 7 SCIc i2c channel 8 data pin I/O Pin. */ 
#define PORTC_PIN7_SSDA8	PORT_PIN_PFS_SSDA
/** Port C - Pin 7 RSPI Input/output from the slave I/O Pin. */ 
#define PORTC_PIN7_MISOA	PORT_PIN_PFS_MISOA
/** Port D - Pin 1 MTU 2 channel 4 CLK B Input Capture / Output Compare Pin.*/ 
#define PORTD_PIN1_MTIOC4B	PORT_PIN_PFS_MTIOC
/** Port D - Pin 2 MTU 2 channel 4 CLK D Input Capture / Output Compare Pin.*/
#define PORTD_PIN2_MTIOC4D	PORT_PIN_PFS_MTIOC
/** Port D - Pin 3 MTU Port Output Enable 2 Input Pin.  POE8# */
#define PORTD_PIN3_POE8		PORT_PIN_PFS_POE
/** Port D - Pin 4 MTU Port Output Enable 2 Input Pin.  POE3# */
#define PORTD_PIN4_POE3		PORT_PIN_PFS_POE
/** Port D - Pin 5 MTU module 5W Input Capture Pin Mode.*/
#define PORTD_PIN5_MTIC5W	PORT_PIN_PFS_MTIC5
/** Port D - Pin 5 MTU Port Output Enable 2 Input Pin.  POE2# */
#define PORTD_PIN5_POE2		PORT_PIN_PFS_POE
/** Port D - Pin 6 MTU module 5V Input Capture Pin Mode.*/
#define PORTD_PIN6_MTIC5V	PORT_PIN_PFS_MTIC5
/** Port D - Pin 6 MTU Port Output Enable 2 Input Pin.  POE1# */
#define PORTD_PIN6_POE1		PORT_PIN_PFS_POE
/** Port D - Pin 7 MTU module 5U Input Capture Pin Mode. */
#define PORTD_PIN7_MTIC5U	PORT_PIN_PFS_MTIC5
/** Port D - Pin 7 MTU Port Output Enable 2 Input Pin.  POE0# */
#define PORTD_PIN7_POE0		PORT_PIN_PFS_POE
/** Port E - Pin 0 SCId (USART and SPI (SCI12)) I/O Clock Pin. */
#define PORTE_PIN0_SCK12	PORT_PIN_PFS_SCK12
/** Port E - Pin 1 MTU 2 channel 4 CLK C Input Capture / Output Compare Pin.*/
#define PORTE_PIN1_MTIOC4C	PORT_PIN_PFS_MTIOC
/** Port E - Pin 1 SCId (USART (SCI12)) Transmitted data Output Pin.*/
#define PORTE_PIN1_TXD12	PORT_PIN_PFS_TXD12
/** Port E - Pin 1 SCId (USART (SCI12)) Extended Transmitted data Output Pin. */
#define PORTE_PIN1_TXDX12	PORT_PIN_PFS_TXDX12
/** Port E - Pin 1 SCId (USART (SCI12)) I/O data reception/transmission Pin.*/
#define PORTE_PIN1_SIOX12	PORT_PIN_PFS_SIOX12
/** Port E - Pin 1 SCId (SPI (SCI12)) master transmission data pin I/O Pin. */
#define PORTE_PIN1_SMOSI12	PORT_PIN_PFS_SMOSI12
/** Port E - Pin 1  SCId (I2C (SCI12)) i2c data pin I/O Pin. */
#define PORTE_PIN1_SSDA12	PORT_PIN_PFS_SSDA12
/** Port E - Pin 2 MTU 2 channel 4 CLK A Input Capture / Output Compare Pin.*/
#define PORTE_PIN2_MTIOC4A	PORT_PIN_PFS_MTIOC
/** Port E - Pin 2 SCId (USART (SCI12)) Received data Input Pin.*/
#define PORTE_PIN2_RXD12	PORT_PIN_PFS_RXD12
/** Port E - Pin 2 SCId (USART (SCI12)) Extended Received data Input Pin.*/
#define PORTE_PIN2_RXDX12	PORT_PIN_PFS_RXDX12
/** Port E - Pin 2 SCId (SPI (SCI12)) slave transmission data I/O Pin.*/
#define PORTE_PIN2_SMISO12	PORT_PIN_PFS_SMISO12
/** Port E - Pin 2 SCId (I2C (SCI12)) i2c clock pin I/O Pin. */
#define PORTE_PIN2_SSCL12	PORT_PIN_PFS_SSCL12
/** Port E - Pin 3 MTU 2 channel 4 CLK B Input Capture / Output Compare Pin.*/
#define PORTE_PIN3_MTIOC4B	PORT_PIN_PFS_MTIOC
/** Port E - Pin 3 MTU Port Output Enable 2 Input Pin.  POE8# */
#define PORTE_PIN3_POE8		PORT_PIN_PFS_POE
/** Port E - Pin 3 SCId (USART (SCI12)) CTS Input Pin.*/
#define PORTE_PIN3_CTS12	PORT_PIN_PFS_CTS12
/** Port E - Pin 3SCId (USART (SCI12))CTS Output Pin.*/
#define PORTE_PIN3_RTS12	PORT_PIN_PFS_RTS12
/** Port E - Pin 3 SCId (SPI (SCI12)) chip select Input Pin. */
#define PORTE_PIN3_SS12		PORT_PIN_PFS_SS12
/** Port E - Pin 4 MTU 2 channel 4 CLK D Input Capture / Output Compare Pin.*/
#define PORTE_PIN4_MTIOC4D	PORT_PIN_PFS_MTIOC
/** Port E - Pin 4 MTU Channel 1 Clock A I/O Pin. */
#define PORTE_PIN4_MTIOC1A	PORT_PIN_PFS_PORTE_MTIOC1A
/** Port E - Pin 5 MTU 2 channel 4 CLK C Input Capture / Output Compare Pin.*/
#define PORTE_PIN5_MTIOC4C	PORT_PIN_PFS_MTIOC
/** Port E - Pin 5 MTU Channel 2 Clock B I/O Pin. */
#define PORTE_PIN5_MTIOC2B	PORT_PIN_PFS_PORTE_MTIOC2B
/** Port H - Pin 0 CAC Port input clock freq. measur. Input Pin. */
#define PORTH_PIN0_CACREF	PORT_PIN_PFS_CACREF
/** Port H - Pin 1 TMR0 Compare Match Output Pin. */
#define PORTH_PIN1_TMO0		PORT_PIN_PFS_TMO
/** Port H - Pin 2 TMR0 Counter Reset Input Pin. */
#define PORTH_PIN2_TMRI0	PORT_PIN_PFS_TMRI
/** Port H - Pin 3 TMR0 External Clock Input Pin.*/
#define PORTH_PIN3_TMCI0	PORT_PIN_PFS_TMCI
/** Port J - Pin 1 MTU Channel 3 Clock A I/O Pin. */
#define PORTJ_PIN1_MTIOC3A	PORT_PIN_PFS_MTIOC
/** Port J - Pin 3  MTU Channel 3 Clock C I/O Pin. */
#define PORTJ_PIN1_MTIOC3C	PORT_PIN_PFS_MTIOC
/** Port J - Pin 3 SCIc (USART (SCI6)) CTS Input Pin. */
#define PORTJ_PIN1_CTS6		PORT_PIN_PFS_CTS6
/** Port J - Pin 3  SCIc (USART (SCI6)) RTS Output Pin. */
#define PORTJ_PIN1_RTS6		PORT_PIN_PFS_RTS6
/** Port J - Pin 3  SCIc (USART) SS channel 6 Input Pin.*/
#define PORTJ_PIN1_SS6		PORT_PIN_PFS_SS6





/** @brief	Pin Mode Configuration Parameters
 *
 * This container contains the configuration (parameters) of a Port Pin Mode.
 */
typedef struct {

  /** @brief	Pin Mode
   *
   *  <b>PORT130_Conf:</b> Port pin mode from mode list. Note that more than one
   *  mode is allowed by default. That way it is e.g. possible to combine DIO
   *  with another mode such as ICU. More HW specific literals may be added by
   *  module implementor. E.g. SPI may be further broken down into SpiCsHw,
   *  SpiCsSw, etc. if necessary.
   */
  Port_PinModeType	PortPinMode;

  /** @brief	Hardware Configuration Data.
   *
   * Port Pin Mode Hardware Configuration Data.
   */
  uint32		PortPinModeHWConfig;

} Port_PinModeConfType;

/** @brief	Pin Configuration Parameters
 *
 *  <b>PORT118_Conf:</b> Configuration of the individual port pins.
 */
typedef struct {

  /** @brief	Direction
   *
   *  <b>PORT125_Conf:</b> The initial direction of the pin (<tt>IN</tt> or
   *  <tt>OUT</tt>). If the direction is not changeable, the value configured
   *  here is fixed. The direction must match the pin mode. E.g. a pin used for
   *  an ADC must be configured to be an in port.
   */
  Port_PinDirectionType		PortPinDirection;

  /** @brief	Direction Changeable
   *
   *  <b>PORT126_Conf:</b> Parameter to indicate if the direction is changeable
   *  on a port pin during runtime.
   *  - <b>true</b>:	Port Pin direction changeable enabled.
   *  - <b>false</b>:	Port Pin direction changeable disabled.
   */
  boolean			PortPinDirectionChangeable;

  /** @brief	Identifier
   *
   *  <b>PORT127_Conf:</b> Pin Id of the port pin. This value will be assigned
   *  to the symbolic name derived from the port pin container short name.
   */
  Port_PinType			PortPinId;

  /** @brief	Initial Mode
   *
   *  <b>PORT128_Conf:</b> Port pin mode from mode list for use with
   *  <tt>Port_Init()</tt> function.
   */
  Port_PinModeType		PortPinInitialMode;

  /** @brief	Level Value
   *
   *  <b>PORT129_Conf:</b> Port Pin Level value from Port pin list.
   */
  Port_PinLevelType		PortPinLevelValue;

  /** @brief	Modes Number
   *
   *  Number of Supported Port Pin Modes ( > 0 ).
   */
  uint32			PortPinModeNumber;

  /** @brief	Supported Modes
   *
   *  Supported Port Pin Modes.
   */
  const Port_PinModeConfType *	PortPinSupportedModes;

  /** @brief	Pin Mode Changeable
   *
   *  <b>PORT134_Conf:</b> Parameter to indicate if the mode is changeable on a
   *  port pin during runtime.
   *  - <b>true</b>:	Port Pin mode changeable allowed.
   *  - <b>False:</b>	Port Pin mode changeable not permitted.
   */
  boolean			PortPinModeChangeable;

} Port_PinConfType;

/** @brief	Port Pins Configuration Parameters
 *
 *  <b>PORT122_Conf:</b> Container collecting the PortPins.
 */
typedef struct {

  /** @brief	Pins Number
   *
   *  <b>PORT124_Conf:</b>	The number of specified PortPins.
   */
  uint32			PortNumberOfPortPins;

  /** @brief	Pins Configuration Parameters
   *
   *  PortPins.
   */
  const Port_PinConfType *		PortPins;

} Port_ConfigType;

/** @brief	Port Pins DIO Configuration
 *
 *  Identifier for Port Pins as DIO Configuration.
 */
#define	PORT_CONFIG_DIO		0x00000000
/** @brief	Port Pins DIO Configuration Pointer
 *
 *  Pointer of Port Pins as DIO Port Driver Configuration
 */
#define	PORT_CONFIG_DIO_PTR	&Port_Config[PORT_CONFIG_DIO]
/** @brief	Default Configuration
 *
 *  Identifier for Default Port Driver Configuration.
 */
#define	PORT_CONFIG_DEFAULT	PORT_CONFIG_DIO
/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default Port Driver Configuration
 */
#define	PORT_CONFIG_DEFAULT_PTR	&Port_Config[PORT_CONFIG_DEFAULT]
/** @brief	Port Pins SCI Configuration
 *
 *  Identifier for Port Pins as IRQ Configuration.
 */
#define	PORT_CONFIG_IRQ		0x00000001
/** @brief	Port Pins IRQ Configuration Pointer
 *
 *  Pointer of Port Pins as IRQ Port Driver Configuration.
 */
#define	PORT_CONFIG_IRQ_PTR	&Port_Config[PORT_CONFIG_IRQ]
/** @brief	Port Pins SCI Configuration
 *
 *  Identifier for Port Pins as SCI Configuration.
 */
#define	PORT_CONFIG_SCI		0x00000002
/** @brief	Port Pins SCI Configuration Pointer
 *
 *  Pointer of Port Pins as SCI Port Driver Configuration.
 */
#define	PORT_CONFIG_SCI_PTR	&Port_Config[PORT_CONFIG_SCI]


#endif	/* PORT_CFG_H */
