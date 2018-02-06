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

/** @file	Port_Cfg.h
 *  @brief	fake-druid AUTOSAR PORT Driver Configuration Header File.
 *
 *  Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 *  @author	Giuseppe Serano
 *  @date	2011
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
#define	PORT_VERSION_INFO_API		STD_OFF

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

#define	PORT_A		0x00000000	/**< Port A		*/
#define	PORT_A_PIN_0	PORT_A		/**< Port A - Pin 0	*/
#define	PORT_A_PIN_1	0x00000001	/**< Port A - Pin 1	*/
#define	PORT_A_PIN_2	0x00000002	/**< Port A - Pin 2	*/
#define	PORT_A_PIN_3	0x00000003	/**< Port A - Pin 3	*/
#define	PORT_A_PIN_4	0x00000004	/**< Port A - Pin 4	*/
#define	PORT_A_PIN_5	0x00000005	/**< Port A - Pin 5	*/
#define	PORT_A_PIN_6	0x00000006	/**< Port A - Pin 6	*/
#define	PORT_A_PIN_7	0x00000007	/**< Port A - Pin 7	*/
#define	PORT_B		0x00000008	/**< Port B		*/
#define	PORT_B_PIN_0	PORT_B		/**< Port B - Pin 0	*/
#define	PORT_B_PIN_1	0x00000009	/**< Port B - Pin 1	*/
#define	PORT_B_PIN_2	0x0000000A	/**< Port B - Pin 2	*/
#define	PORT_B_PIN_3	0x0000000B	/**< Port B - Pin 3	*/
#define	PORT_B_PIN_4	0x0000000C	/**< Port B - Pin 4	*/
#define	PORT_B_PIN_5	0x0000000D	/**< Port B - Pin 5	*/
#define	PORT_B_PIN_6	0x0000000E	/**< Port B - Pin 6	*/
#define	PORT_B_PIN_7	0x0000000F	/**< Port B - Pin 7	*/
#define	PORT_C		0x00000010	/**< Port C		*/
#define	PORT_C_PIN_0	PORT_C		/**< Port C - Pin 0	*/
#define	PORT_C_PIN_1	0x00000011	/**< Port C - Pin 1	*/
#define	PORT_C_PIN_2	0x00000012	/**< Port C - Pin 2	*/
#define	PORT_C_PIN_3	0x00000013	/**< Port C - Pin 3	*/
#define	PORT_C_PIN_4	0x00000014	/**< Port C - Pin 4	*/
#define	PORT_C_PIN_5	0x00000015	/**< Port C - Pin 5	*/
#define	PORT_C_PIN_6	0x00000016	/**< Port C - Pin 6	*/
#define	PORT_C_PIN_7	0x00000017	/**< Port C - Pin 7	*/
#define	PORT_D		0x00000018	/**< Port D		*/
#define	PORT_D_PIN_0	PORT_D		/**< Port D - Pin 0	*/
#define	PORT_D_PIN_1	0x00000019	/**< Port D - Pin 1	*/
#define	PORT_D_PIN_2	0x0000001A	/**< Port D - Pin 2	*/
#define	PORT_D_PIN_3	0x0000001B	/**< Port D - Pin 3	*/
#define	PORT_D_PIN_4	0x0000001C	/**< Port D - Pin 4	*/
#define	PORT_D_PIN_5	0x0000001D	/**< Port D - Pin 5	*/
#define	PORT_D_PIN_6	0x0000001E	/**< Port D - Pin 6	*/
#define	PORT_D_PIN_7	0x0000001F	/**< Port D - Pin 7	*/
#define	PORT_E		0x00000020	/**< Port E		*/
#define	PORT_E_PIN_0	PORT_E		/**< Port E - Pin 0	*/
#define	PORT_E_PIN_1	0x00000021	/**< Port E - Pin 1	*/
#define	PORT_E_PIN_2	0x00000022	/**< Port E - Pin 2	*/
#define	PORT_E_PIN_3	0x00000023	/**< Port E - Pin 3	*/
#define	PORT_E_PIN_4	0x00000024	/**< Port E - Pin 4	*/
#define	PORT_E_PIN_5	0x00000025	/**< Port E - Pin 5	*/
#define	PORT_E_PIN_6	0x00000026	/**< Port E - Pin 6	*/
#define	PORT_E_PIN_7	0x00000027	/**< Port E - Pin 7	*/
#define	PORT_F		0x00000028	/**< Port F		*/
#define	PORT_F_PIN_0	PORT_F		/**< Port F - Pin 0	*/
#define	PORT_F_PIN_1	0x00000029	/**< Port F - Pin 1	*/
#define	PORT_F_PIN_2	0x0000002A	/**< Port F - Pin 2	*/
#define	PORT_F_PIN_3	0x0000002B	/**< Port F - Pin 3	*/
#define	PORT_F_PIN_4	0x0000002C	/**< Port F - Pin 4	*/
#define	PORT_F_PIN_5	0x0000002D	/**< Port F - Pin 5	*/
#define	PORT_F_PIN_6	0x0000002E	/**< Port F - Pin 6	*/
#define	PORT_F_PIN_7	0x0000002F	/**< Port F - Pin 7	*/
#define	PORT_G		0x00000030	/**< Port G		*/
#define	PORT_G_PIN_0	PORT_G		/**< Port G - Pin 0	*/
#define	PORT_G_PIN_1	0x00000031	/**< Port G - Pin 1	*/
#define	PORT_G_PIN_2	0x00000032	/**< Port G - Pin 2	*/
#define	PORT_G_PIN_3	0x00000033	/**< Port G - Pin 3	*/
#define	PORT_G_PIN_4	0x00000034	/**< Port G - Pin 4	*/
#define	PORT_G_PIN_5	0x00000035	/**< Port G - Pin 5	*/
#define	PORT_G_PIN_6	0x00000036	/**< Port G - Pin 6	*/
#define	PORT_G_PIN_7	0x00000037	/**< Port G - Pin 7	*/
#define	PORT_H		0x00000038	/**< Port H		*/
#define	PORT_H_PIN_0	PORT_H		/**< Port H - Pin 0	*/
#define	PORT_H_PIN_1	0x00000039	/**< Port H - Pin 1	*/
#define	PORT_H_PIN_2	0x0000003A	/**< Port H - Pin 2	*/
#define	PORT_H_PIN_3	0x0000003B	/**< Port H - Pin 3	*/
#define	PORT_H_PIN_4	0x0000003C	/**< Port H - Pin 4	*/
#define	PORT_H_PIN_5	0x0000003D	/**< Port H - Pin 5	*/
#define	PORT_H_PIN_6	0x0000003E	/**< Port H - Pin 6	*/
#define	PORT_H_PIN_7	0x0000003F	/**< Port H - Pin 7	*/
#define	PORT_J		0x00000040	/**< Port J		*/
#define	PORT_J_PIN_0	PORT_J		/**< Port J - Pin 0	*/
#define	PORT_J_PIN_1	0x00000041	/**< Port J - Pin 1	*/
#define	PORT_J_PIN_2	0x00000042	/**< Port J - Pin 2	*/
#define	PORT_J_PIN_3	0x00000043	/**< Port J - Pin 3	*/
#define	PORT_J_PIN_4	0x00000044	/**< Port J - Pin 4	*/
#define	PORT_J_PIN_5	0x00000045	/**< Port J - Pin 5	*/
#define	PORT_J_PIN_6	0x00000046	/**< Port J - Pin 6	*/
#define	PORT_J_PIN_7	0x00000047	/**< Port J - Pin 7	*/
#define	PORT_K		0x00000048	/**< Port K		*/
#define	PORT_K_PIN_0	PORT_K		/**< Port K - Pin 0	*/
#define	PORT_K_PIN_1	0x00000049	/**< Port K - Pin 1	*/
#define	PORT_K_PIN_2	0x0000004A	/**< Port K - Pin 2	*/
#define	PORT_K_PIN_3	0x0000004B	/**< Port K - Pin 3	*/
#define	PORT_K_PIN_4	0x0000004C	/**< Port K - Pin 4	*/
#define	PORT_K_PIN_5	0x0000004D	/**< Port K - Pin 5	*/
#define	PORT_K_PIN_6	0x0000004E	/**< Port K - Pin 6	*/
#define	PORT_K_PIN_7	0x0000004F	/**< Port K - Pin 7	*/
#define	PORT_L		0x00000050	/**< Port L		*/
#define	PORT_L_PIN_0	PORT_L		/**< Port L - Pin 0	*/
#define	PORT_L_PIN_1	0x00000051	/**< Port L - Pin 1	*/
#define	PORT_L_PIN_2	0x00000052	/**< Port L - Pin 2	*/
#define	PORT_L_PIN_3	0x00000053	/**< Port L - Pin 3	*/
#define	PORT_L_PIN_4	0x00000054	/**< Port L - Pin 4	*/
#define	PORT_L_PIN_5	0x00000055	/**< Port L - Pin 5	*/
#define	PORT_L_PIN_6	0x00000056	/**< Port L - Pin 6	*/
#define	PORT_L_PIN_7	0x00000057	/**< Port L - Pin 7	*/
#define	PORT_M		0x00000058	/**< Port M		*/
#define	PORT_M_PIN_0	PORT_M		/**< Port M - Pin 0	*/
#define	PORT_M_PIN_1	0x00000059	/**< Port M - Pin 1	*/
#define	PORT_M_PIN_2	0x0000005A	/**< Port M - Pin 2	*/
#define	PORT_M_PIN_3	0x0000005B	/**< Port M - Pin 3	*/
#define	PORT_M_PIN_4	0x0000005C	/**< Port M - Pin 4	*/
#define	PORT_M_PIN_5	0x0000005D	/**< Port M - Pin 5	*/
#define	PORT_M_PIN_6	0x0000005E	/**< Port M - Pin 6	*/
#define	PORT_M_PIN_7	0x0000005F	/**< Port M - Pin 7	*/
#define	PORT_P		0x00000060	/**< Port P		*/
#define	PORT_P_PIN_0	PORT_P		/**< Port P - Pin 0	*/
#define	PORT_P_PIN_1	0x00000061	/**< Port P - Pin 1	*/
#define	PORT_P_PIN_2	0x00000062	/**< Port P - Pin 2	*/
#define	PORT_P_PIN_3	0x00000063	/**< Port P - Pin 3	*/
#define	PORT_P_PIN_4	0x00000064	/**< Port P - Pin 4	*/
#define	PORT_P_PIN_5	0x00000065	/**< Port P - Pin 5	*/
#define	PORT_P_PIN_6	0x00000066	/**< Port P - Pin 6	*/
#define	PORT_P_PIN_7	0x00000067	/**< Port P - Pin 7	*/
#define	PORT_Q		0x00000068	/**< Port Q		*/
#define	PORT_Q_PIN_0	PORT_Q		/**< Port Q - Pin 0	*/
#define	PORT_Q_PIN_1	0x00000069	/**< Port Q - Pin 1	*/
#define	PORT_Q_PIN_2	0x0000006A	/**< Port Q - Pin 2	*/
#define	PORT_Q_PIN_3	0x0000006B	/**< Port Q - Pin 3	*/
#define	PORT_Q_PIN_4	0x0000006C	/**< Port Q - Pin 4	*/
#define	PORT_Q_PIN_5	0x0000006D	/**< Port Q - Pin 5	*/
#define	PORT_Q_PIN_6	0x0000006E	/**< Port Q - Pin 6	*/
#define	PORT_Q_PIN_7	0x0000006F	/**< Port Q - Pin 7	*/

/** Number of Port Pins */
#define	PORT_PINS_NUMBER	PORT_Q_PIN_7

/** DIO Pin Mode. */
#define	PORT_PIN_MODE_DIO	0x00000000

/** SCI Pin Mode. */
#define	PORT_PIN_MODE_SCI	0x00000001

/** SPI Pin Mode. */
#define	PORT_PIN_MODE_SPI	0x00000002

/** Number of Port Pin Modes */
#define	PORT_PIN_MODES_NUMBER	PORT_PIN_MODE_SPI + 1

/*
 * Port Pin Mode Hardware Configuration Data Values.
 */
#define	PORT_PIN_HW_CFG_PMC_M	0x0000000F	/**< Port Mux Control Mask    */
#define	PORT_PIN_HW_CFG_DEN	0x00000010	/**< Digital Enable	      */
#define	PORT_PIN_HW_CFG_AMSEL	0x00000020	/**< Analog Mode Select	      */
#define	PORT_PIN_HW_CFG_AFSEL	0x00000040	/**< Alternate Function Select*/
#define	PORT_PIN_HW_CFG_ODR	0x00000080	/**< Open Drain Select	      */
#define	PORT_PIN_HW_CFG_PUR	0x00000100	/**< Pull-Up Select	      */
#define	PORT_PIN_HW_CFG_PDR	0x00000200	/**< Pull-Down Select	      */
#define	PORT_PIN_HW_CFG_DR2R	0x00000400	/**< 2-mA Drive Select	      */
#define	PORT_PIN_HW_CFG_DR4R	0x00000800	/**< 4-mA Drive Select	      */
#define	PORT_PIN_HW_CFG_DR8R	0x00001000	/**< 8-mA Drive Select	      */
#define	PORT_PIN_HW_CFG_SLR	0x00002000	/**< Slew-Rate Control Select */
#define	PORT_PIN_HW_CFG_ADCCTL	0x00004000	/**< ADC Control	      */
#define	PORT_PIN_HW_CFG_DMACTL	0x00008000	/**< DMA Control	      */

/*
 * Port Pins PMCs
 */
/** Port A Mux Control Sci 0 */
#define	PORT_A_PMC_SCI_0		0x00000001
/** Port A - Pin 0 Mux Control Sci 0 Rx */
#define	PORT_A_PIN_0_PMC_SCI_0_RX	PORT_A_PMC_SCI_0
/** Port A - Pin 1 Mux Control Sci 1 Tx */
#define	PORT_A_PIN_1_PMC_SCI_0_TX	PORT_A_PMC_SCI_0
/** Port B Mux Control Sci 1 */
#define	PORT_B_PMC_SCI_1		0x00000001
/** Port B - Pin 0 Mux Control Sci 1 Rx */
#define	PORT_B_PIN_0_PMC_SCI_1_RX	PORT_B_PMC_SCI_1
/** Port B - Pin 1 Mux Control Sci 1 Tx */
#define	PORT_B_PIN_1_PMC_SCI_1_TX	PORT_B_PMC_SCI_1
/** Port C Mux Control Sci 4 */
#define	PORT_C_PMC_SCI_4		0x00000001
/** Port C - Pin 4 Mux Control Sci 4 Rx */
#define	PORT_C_PIN_4_PMC_SCI_4_RX	PORT_C_PMC_SCI_4
/** Port C - Pin 5 Mux Control Sci 4 Tx */
#define	PORT_C_PIN_5_PMC_SCI_4_TX	PORT_C_PMC_SCI_4
/** Port C Mux Control Sci 1 */
#define	PORT_C_PMC_SCI_1		0x00000002
/** Port C - Pin 4 Mux Control Sci 1 Rx */
#define	PORT_C_PIN_4_PMC_SCI_1_RX	PORT_C_PMC_SCI_1
/** Port C - Pin 5 Mux Control Sci 1 Tx */
#define	PORT_C_PIN_5_PMC_SCI_1_TX	PORT_C_PMC_SCI_1
/** Port C Mux Control Sci 1 RTS/CTS */
#define	PORT_C_PMC_SCI_1_RTS_CTS	0x00000008
/** Port C - Pin 4 Mux Control Sci 1 RTS */
#define	PORT_C_PIN_4_PMC_SCI_1_RTS	PORT_C_PMC_SCI_1_RTS_CTS
/** Port C - Pin 5 Mux Control Sci 1 CTS */
#define	PORT_C_PIN_5_PMC_SCI_1_CTS	PORT_C_PMC_SCI_1_RTS_CTS
/** Port C Mux Control Sci 3 */
#define	PORT_C_PMC_SCI_3		PORT_C_PMC_SCI_4
/** Port C - Pin 6 Mux Control Sci 3 Rx */
#define	PORT_C_PIN_6_PMC_SCI_3_RX	PORT_C_PMC_SCI_3
/** Port C - Pin 7 Mux Control Sci 3 Tx */
#define	PORT_C_PIN_7_PMC_SCI_3_TX	PORT_C_PMC_SCI_3
/** Port D Mux Control Sci 6 */
#define	PORT_D_PMC_SCI_6		0x00000001
/** Port D - Pin 4 Mux Control Sci 6 Rx */
#define	PORT_D_PIN_4_PMC_SCI_6_RX	PORT_D_PMC_SCI_6
/** Port D - Pin 5 Mux Control Sci 6 Tx */
#define	PORT_D_PIN_5_PMC_SCI_6_TX	PORT_D_PMC_SCI_6
/** Port D Mux Control Sci 2 */
#define	PORT_D_PMC_SCI_2		PORT_D_PMC_SCI_6
/** Port D - Pin 6 Mux Control Sci 2 Rx */
#define	PORT_D_PIN_6_PMC_SCI_2_RX	PORT_D_PMC_SCI_2
/** Port D - Pin 6 Mux Control Sci 2 Tx */
#define	PORT_D_PIN_7_PMC_SCI_2_TX	PORT_D_PMC_SCI_2
/** Port E Mux Control Sci 7 */
#define	PORT_E_PMC_SCI_7		0x00000001
/** Port E - Pin 0 Mux Control Sci 7 Rx */
#define	PORT_E_PIN_0_PMC_SCI_7_RX	PORT_E_PMC_SCI_7
/** Port E - Pin 1 Mux Control Sci 7 Rx */
#define	PORT_E_PIN_1_PMC_SCI_7_TX	PORT_E_PMC_SCI_7
/** Port E Mux Control Sci 5 */
#define	PORT_E_PMC_SCI_5		PORT_E_PMC_SCI_7
/** Port E - Pin 4 Mux Control Sci 5 Rx */
#define	PORT_E_PIN_4_PMC_SCI_5_RX	PORT_E_PMC_SCI_5
/** Port E - Pin 5 Mux Control Sci 5 Tx */
#define	PORT_E_PIN_5_PMC_SCI_5_TX	PORT_E_PMC_SCI_5
/** Port E Mux Control Sci 1 */
#define	PORT_E_PMC_SCI_1		PORT_E_PMC_SCI_7
/** Port E - Pin 7 Mux Control Sci 1 RI */
#define	PORT_E_PIN_7_PMC_SCI_1_RI	PORT_E_PMC_SCI_1
/** Port F Mux Control Sci 1 */
#define	PORT_F_PMC_SCI_1		0x00000001
/** Port F - Pin 0 Mux Control Sci 1 RTS */
#define	PORT_F_PIN_0_PMC_SCI_1_RTS	PORT_F_PMC_SCI_1
/** Port F - Pin 1 Mux Control Sci 1 CTS */
#define	PORT_F_PIN_1_PMC_SCI_1_CTS	PORT_F_PMC_SCI_1
/** Port F - Pin 2 Mux Control Sci 1 DCD */
#define	PORT_F_PIN_2_PMC_SCI_1_DCD	PORT_F_PMC_SCI_1
/** Port F - Pin 3 Mux Control Sci 1 DSR */
#define	PORT_F_PIN_3_PMC_SCI_1_DSR	PORT_F_PMC_SCI_1
/** Port F - Pin 4 Mux Control Sci 1 DTR */
#define	PORT_F_PIN_4_PMC_SCI_1_DTR	PORT_F_PMC_SCI_1
/** Port G Mux Control Sci 2 */
#define	PORT_G_PMC_SCI_2		0x00000001
/** Port G - Pin 4 Mux Control Sci 2 Rx */
#define	PORT_G_PIN_4_PMC_SCI_2_RX	PORT_G_PMC_SCI_2
/** Port G - Pin 5 Mux Control Sci 2 Tx */
#define	PORT_G_PIN_5_PMC_SCI_2_TX	PORT_G_PMC_SCI_2
/** Port J Mux Control Sci 4 */
#define	PORT_J_PMC_SCI_4		0x00000001
/** Port J - Pin 0 Mux Control Sci 4 Rx */
#define	PORT_J_PIN_0_PMC_SCI_4_RX	PORT_J_PMC_SCI_4
/** Port J - Pin 1 Mux Control Sci 4 Rx */
#define	PORT_J_PIN_1_PMC_SCI_4_TX	PORT_J_PMC_SCI_4
/** Port J  Mux Control Sci 5 */
#define	PORT_J_PMC_SCI_5		PORT_J_PMC_SCI_4
/** Port J - Pin 2 Mux Control Sci 5 Rx */
#define	PORT_J_PIN_2_PMC_SCI_5_RX	PORT_J_PMC_SCI_5
/** Port J - Pin 3 Mux Control Sci 5 Tx */
#define	PORT_J_PIN_3_PMC_SCI_5_TX	PORT_J_PMC_SCI_5
/** Port J Mux Control Sci 6 */
#define	PORT_J_PMC_SCI_6		PORT_J_PMC_SCI_4
/** Port J - Pin 4 Mux Control Sci 6 Rx */
#define	PORT_J_PIN_4_PMC_SCI_6_RX	PORT_J_PMC_SCI_6
/** Port J - Pin 5 Mux Control Sci 6 Tx */
#define	PORT_J_PIN_5_PMC_SCI_6_TX	PORT_J_PMC_SCI_6
/** Port K Mux Control Sci 7 */
#define	PORT_K_PMC_SCI_7		0x00000001
/** Port K - Pin 4 Mux Control Sci 7 Rx */
#define	PORT_K_PIN_4_PMC_SCI_7_RX	PORT_K_PMC_SCI_7
/** Port K - Pin 5 Mux Control Sci 7 Tx */
#define	PORT_K_PIN_5_PMC_SCI_7_TX	PORT_K_PMC_SCI_7

/** Port A Mux Control Spi 0 */
#define	PORT_A_PMC_SPI_0		0x00000002
/** Port A - Pin 2 Mux Control Spi 0 Clk */
#define	PORT_A_PIN_2_PMC_SPI_0_CLK	PORT_A_PMC_SPI_0
/** Port A - Pin 3 Mux Control Spi 0 Cs */
#define	PORT_A_PIN_3_PMC_SPI_0_CS	PORT_A_PMC_SPI_0
/** Port A - Pin 4 Mux Control Spi 0 Rx */
#define	PORT_A_PIN_4_PMC_SPI_0_RX	PORT_A_PMC_SPI_0
/** Port A - Pin 5 Mux Control Spi 0 Tx */
#define	PORT_A_PIN_5_PMC_SPI_0_TX	PORT_A_PMC_SPI_0
/** Port B Mux Control Spi 2 */
#define	PORT_B_PMC_SPI_2		0x00000002
/** Port B - Pin 4 Mux Control Spi 2 Clk */
#define	PORT_B_PIN_4_PMC_SPI_2_CLK	PORT_A_PMC_SPI_2
/** Port B - Pin 5 Mux Control Spi 2 Cs */
#define	PORT_B_PIN_5_PMC_SPI_2_CS	PORT_A_PMC_SPI_2
/** Port D Mux Control Spi 1 */
#define	PORT_D_PMC_SPI_1		0x00000002
/** Port D - Pin 0 Mux Control Spi 1 Clk */
#define	PORT_D_PIN_0_PMC_SPI_1_CLK	PORT_D_PMC_SPI_1
/** Port D - Pin 1 Mux Control Spi 1 Cs */
#define	PORT_D_PIN_1_PMC_SPI_1_CS	PORT_D_PMC_SPI_1
/** Port D - Pin 2 Mux Control Spi 1 Rx */
#define	PORT_D_PIN_2_PMC_SPI_1_RX	PORT_D_PMC_SPI_1
/** Port D - Pin 3 Mux Control Spi 1 Tx */
#define	PORT_D_PIN_3_PMC_SPI_1_TX	PORT_D_PMC_SPI_1
/** Port D Mux Control Spi 3 */
#define	PORT_D_PMC_SPI_3		0x00000001
/** Port D - Pin 0 Mux Control Spi 3 Clk */
#define	PORT_D_PIN_0_PMC_SPI_3_CLK	PORT_D_PMC_SPI_3
/** Port D - Pin 1 Mux Control Spi 3 Cs */
#define	PORT_D_PIN_1_PMC_SPI_3_CS	PORT_D_PMC_SPI_3
/** Port D - Pin 2 Mux Control Spi 3 Rx */
#define	PORT_D_PIN_2_PMC_SPI_3_RX	PORT_D_PMC_SPI_3
/** Port D - Pin 3 Mux Control Spi 3 Tx */
#define	PORT_D_PIN_3_PMC_SPI_3_TX	PORT_D_PMC_SPI_3
/** Port F Mux Control Spi 1 */
#define	PORT_F_PMC_SPI_1		0x00000002
/** Port F - Pin 0 Mux Control Spi 1 Rx */
#define	PORT_F_PIN_0_PMC_SPI_1_RX	PORT_F_PMC_SPI_1
/** Port F - Pin 1 Mux Control Spi 1 Tx */
#define	PORT_F_PIN_1_PMC_SPI_1_TX	PORT_F_PMC_SPI_1
/** Port F - Pin 2 Mux Control Spi 1 Clk */
#define	PORT_F_PIN_2_PMC_SPI_1_CLK	PORT_F_PMC_SPI_1
/** Port F - Pin 3 Mux Control Spi 1 Cs */
#define	PORT_F_PIN_3_PMC_SPI_1_CS	PORT_F_PMC_SPI_1
/** Port H Mux Control Spi 3 */
#define	PORT_H_PMC_SPI_3		0x00000002
/** Port H - Pin 0 Mux Control Spi 3 Clk */
#define	PORT_H_PIN_0_PMC_SPI_3_CLK	PORT_H_PMC_SPI_3
/** Port H - Pin 1 Mux Control Spi 3 Cs */
#define	PORT_H_PIN_1_PMC_SPI_3_CS	PORT_H_PMC_SPI_3
/** Port H - Pin 2 Mux Control Spi 3 Rx */
#define	PORT_H_PIN_2_PMC_SPI_3_RX	PORT_H_PMC_SPI_3
/** Port H - Pin 3 Mux Control Spi 3 Tx */
#define	PORT_H_PIN_3_PMC_SPI_3_TX	PORT_H_PMC_SPI_3
/** Port H Mux Control Spi 2 */
#define	PORT_H_PMC_SPI_2		0x00000002
/** Port H - Pin 4 Mux Control Spi 2 Clk */
#define	PORT_H_PIN_4_PMC_SPI_2_CLK	PORT_H_PMC_SPI_2
/** Port H - Pin 5 Mux Control Spi 2 Cs */
#define	PORT_H_PIN_5_PMC_SPI_2_CS	PORT_H_PMC_SPI_2
/** Port H - Pin 6 Mux Control Spi 2 Rx */
#define	PORT_H_PIN_6_PMC_SPI_2_RX	PORT_H_PMC_SPI_2
/** Port H - Pin 7 Mux Control Spi 2 Tx */
#define	PORT_H_PIN_7_PMC_SPI_2_TX	PORT_H_PMC_SPI_2
/** Port K Mux Control Spi 3 */
#define	PORT_K_PMC_SPI_3		0x00000002
/** Port K - Pin 0 Mux Control Spi 3 Clk */
#define	PORT_K_PIN_0_PMC_SPI_3_CLK	PORT_K_PMC_SPI_3
/** Port K - Pin 1 Mux Control Spi 3 Cs */
#define	PORT_K_PIN_1_PMC_SPI_3_CS	PORT_K_PMC_SPI_3
/** Port K - Pin 2 Mux Control Spi 3 Rx */
#define	PORT_K_PIN_2_PMC_SPI_3_RX	PORT_K_PMC_SPI_3
/** Port K - Pin 3 Mux Control Spi 3 Tx */
#define	PORT_K_PIN_3_PMC_SPI_3_TX	PORT_K_PMC_SPI_3

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
 *  Identifier for Port Pins as SCI Configuration.
 */
#define	PORT_CONFIG_SCI		0x00000001
/** @brief	Port Pins SCI Configuration Pointer
 *
 *  Pointer of Port Pins as SCI Port Driver Configuration.
 */
#define	PORT_CONFIG_SCI_PTR	&Port_Config[PORT_CONFIG_SCI]
/** @brief	Port Pins SPI Microchip ENC28J60 Configuration
 *
 *  Identifier for Port Pins as SPI Microchip ENC28J60 Configuration.
 */
#define	PORT_CONFIG_SPI_ENC28J60	0x00000002
/** @brief	Port Pins SPI Microchip ENC28J60 Configuration Pointer
 *
 *  Pointer of Port Pins as SPI Microchip ENC28J60 Port Driver Configuration.
 */
#define	PORT_CONFIG_SPI_ENC28J60_PTR	&Port_Config[PORT_CONFIG_SPI_ENC28J60]
#endif	/* PORT_CFG_H */
