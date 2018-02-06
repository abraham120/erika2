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

/** @file	Dma_Cfg.h
 *  @brief	fake-druid AUTOSAR-"like" DMA Driver Configuration Header File.
 *
 *  Configuration of the Dma (Direct Memory Access) module.
 *
 *  Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */


#if !(\
 ((DMA_SW_MAJOR_VERSION == 1) && \
  (DMA_SW_MINOR_VERSION == 0) && \
  (DMA_SW_PATCH_VERSION == 0))\
)
#error Dma: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	DMA_CFG_H
#define	DMA_CFG_H

/*
 * Dma
 *
 * Configuration of the Dma (Direct Memory Access) module.
 */

/*
 * DmaGeneral
 *
 * General configuration settings for DMA Driver
 */

/** @brief	<tt>DmaDevErrorDetect</tt>
 *
 *  Switches the Development Error Detection and Notification ON or OFF.
 *
 *  The detection of all development errors is configurable at pre-compile time.
 *
 *  The detection of all development errors is configurable as (ON/OFF) by the
 *  switch <tt>DmaDevErrorDetect</tt>.
 *
 *  The switch <tt>DmaDevErrorDetect</tt> shall activate or deactivate the
 *  detection of all development errors.
 *
 *  If the switch <tt>DmaDevErrorDetect</tt> is enabled API parameter checking
 *  is also enabled.
 *
 *  The detection of production code errors cannot be switched off.
 *
 *  Detected development errors shall be reported to the error hook of the
 *  Development Error Tracer (DET) if the pre-processor switch
 *  <tt>DmaDevErrorDetect</tt> is set.
 */
#ifdef	__AS_CFG_DMA_DEV_ERROR_DETECT__
#define	DMA_DEV_ERROR_DETECT		STD_ON
#else
#define	DMA_DEV_ERROR_DETECT		STD_OFF
#endif

/** @brief	<tt>DmaVersionInfoApi</tt>
 *
 *  Switches the <tt>Dma_GetVersionInfo()</tt> function ON or OFF.
 *
 *  The function <tt>Dma_GetVersionInfo()</tt> is pre-compile time configurable
 *  by the configuration parameter <tt>DmaVersionInfoApi</tt>.
 *
 *  The function <tt>Dma_GetVersionInfo()</tt> is pre-compile time configurable
 *  On/Off by the configuration parameter <tt>DmaVersionInfoApi</tt>.
 */
#ifdef	__AS_CFG_DMA_VERSION_INFO_API__
#define	DMA_VERSION_INFO_API		STD_ON
#else
#define	DMA_VERSION_INFO_API		STD_OFF
#endif

/** @brief	De-Init Functionality
 *
 *  Adds / removes the service <tt>Dma_DeInit()</tt> from the code.
 */
#ifdef	__AS_CFG_DMA_DE_INIT_API__
#define	DMA_DE_INIT_API			STD_ON
#else
#define	DMA_DE_INIT_API			STD_OFF
#endif

/** @brief	Diable Channel Functionality
 *
 *  Adds / removes the service <tt>Dma_DisableChannel()</tt> from the code.
 */
#ifdef	__AS_CFG_DMA_DISABLE_CHANNEL_API__
#define	DMA_DISABLE_CHANNEL_API			STD_ON
#else
#define	DMA_DISABLE_CHANNEL_API			STD_OFF
#endif

/** @brief	Driver Status Functionality
 *
 *  Adds / removes the service <tt>Dma_GetStatus()</tt> from the code.
 */
#ifdef	__AS_CFG_DMA_STATUS_API__
#define	DMA_STATUS_API			STD_ON
#else
#define	DMA_STATUS_API			STD_OFF
#endif

/** @brief	Channel Result Functionality
 *
 *  Adds / removes the service <tt>Dma_GetChannelResult()</tt> from the code.
 */
#ifdef	__AS_CFG_DMA_CHANNEL_RESULT_API__
#define	DMA_CHANNEL_RESULT_API		STD_ON
#else
#define	DMA_CHANNEL_RESULT_API		STD_OFF
#endif

/** @brief	Transfer Request Functionality
 *
 *  Adds / removes the service <tt>Dma_TransferRequest()</tt> from the code.
 */
#ifdef	__AS_CFG_DMA_TRANSFER_REQUEST_API__
#define	DMA_TRANSFER_REQUEST_API	STD_ON
#else
#define	DMA_TRANSFER_REQUEST_API	STD_OFF
#endif

/** @brief	Ping-Pong Transfer Functionality
 *
 *  Adds / removes <tt>Dma_PingPongTransferSetup()</tt>,
 *  <tt>Dma_PingTransferUpdate()</tt> and <tt>Dma_PongTransferUpdate()</tt>
 *  services from the code.
 */
#ifdef	__AS_CFG_DMA_PING_PONG_API__
#define	DMA_PING_PONG_API		STD_ON
#else
#define	DMA_PING_PONG_API		STD_OFF
#endif

/** @brief	Scatter-Gather Transfer Functionality
 *
 *  Adds / removes <tt>Dma_ScatterGatherTransferSetup()</tt> and
 *  <tt>Dma_ScatterGatherEntrySetup()</tt> services from the code.
 */
#ifdef	__AS_CFG_DMA_SCATTER_GATHER_API__
#define	DMA_SCATTER_GATHER_API		STD_ON
#else
#define	DMA_SCATTER_GATHER_API		STD_OFF
#endif

/** @brief	Notifications Functionality
 *
 *  Adds / removes the services <tt>Dma_EnableNotifications()</tt> and
 *  <tt>Dma_DisableNotifications()</tt> from the code.
 */
#ifdef	__AS_CFG_DMA_NOTIFICATIONS_API__
#define	DMA_NOTIFICATIONS_API		STD_ON
#else
#define	DMA_NOTIFICATIONS_API		STD_OFF
#endif

/** @brief	DMA Data Type
 *
 *  <tt>Dma_DataType</tt>

 *  This defines the type of application data buffer elements.
 *
 *  Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *
 *  It shall be provided for external use.
 *
 *  This is implementation specific but not all values may be valid within the
 *  type.
 *
 *  This type shall be chosen in order to have the most efficient implementation
 *  on a specific microcontroller platform.
 */
typedef uint8	Dma_DataType;

/** @brief	DMA Entry Type
 *
 *  The type <tt>Dma_EntryType</tt> defines the type for a specific DMA Channel
 *  transfer entry when the Channel is configurable for multiple transfers.
 *
 *  Type is struct.
 *
 *  It shall be provided for external use.
 *
 *  This is implementation specific.
 *
 *  This type shall be chosen in order to have the most efficient implementation
 *  on a specific microcontroller platform.
 */
typedef struct
{

  /** @brief	Source End Address.
   *
   *  The ending source address of the data transfer.
   */
  uint32	DmaSrcEndAddress;

  /** @brief	Destination End Address.
   *
   *  The ending destination address of the data transfer.
   */
  uint32	DmaDstEndAddress;

  /** @brief	Control Mode
   *
   *  The channel control mode. */
  uint32	DmaControl;

  /** @brief	Unused Location.
   *
   *  An unused location needed by Harware DMA Controller.
   */
  uint32	DmaUnused;

}		Dma_EntryType;

/** @brief	DMA Driver Channel Type.
 *
 *  The type <tt>Dma_ChannelType</tt> specifies the identification (ID) for a
 *  Channel.
 *
 *  Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *
 *  It shall be provided for external use.
 *
 *  This is implementation specific but not all values may be valid within the
 *  type.
 *
 *  This type shall be chosen in order to have the most efficient implementation
 *  on a specific microcontroller platform.
 */
typedef	uint8	Dma_ChannelType;

/** @brief	DMA Driver Number of Elements Type
 *
 *  The type <tt>Dma_NumberOfElementsType</tt> is used for defining the number
 *  of elements to transfer on a DMA Channel.
 *
 *  Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *
 *  It shall be provided for external use.
 *
 *  This is implementation specific but not all values may be valid within the
 *  type.
 *
 *  This type shall be chosen in order to have the most efficient implementation
 *  on a specific microcontroller platform.
 */
typedef uint16	Dma_NumberOfElementsType;

/*
 * DMA Channels IDs.
 */
#define	DMA_CHANNEL_0	0x00U	/**< DMA Channel 0.  */
#define	DMA_CHANNEL_1	0x01U	/**< DMA Channel 1.  */
#define	DMA_CHANNEL_2	0x02U	/**< DMA Channel 2.  */
#define	DMA_CHANNEL_3	0x03U	/**< DMA Channel 3.  */
#define	DMA_CHANNEL_4	0x04U	/**< DMA Channel 4.  */
#define	DMA_CHANNEL_5	0x05U	/**< DMA Channel 5.  */
#define	DMA_CHANNEL_6	0x06U	/**< DMA Channel 6.  */
#define	DMA_CHANNEL_7	0x07U	/**< DMA Channel 7.  */
#define	DMA_CHANNEL_8	0x08U	/**< DMA Channel 8.  */
#define	DMA_CHANNEL_9	0x09U	/**< DMA Channel 9.  */
#define	DMA_CHANNEL_10	0x0AU	/**< DMA Channel 10. */
#define	DMA_CHANNEL_11	0x0BU	/**< DMA Channel 11. */
#define	DMA_CHANNEL_12	0x0CU	/**< DMA Channel 12. */
#define	DMA_CHANNEL_13	0x0DU	/**< DMA Channel 13. */
#define	DMA_CHANNEL_14	0x0EU	/**< DMA Channel 14. */
#define	DMA_CHANNEL_15	0x0FU	/**< DMA Channel 15. */
#define	DMA_CHANNEL_16	0x10U	/**< DMA Channel 16. */
#define	DMA_CHANNEL_17	0x11U	/**< DMA Channel 17. */
#define	DMA_CHANNEL_18	0x12U	/**< DMA Channel 18. */
#define	DMA_CHANNEL_19	0x13U	/**< DMA Channel 19. */
#define	DMA_CHANNEL_20	0x14U	/**< DMA Channel 20. */
#define	DMA_CHANNEL_21	0x15U	/**< DMA Channel 21. */
#define	DMA_CHANNEL_22	0x16U	/**< DMA Channel 22. */
#define	DMA_CHANNEL_23	0x17U	/**< DMA Channel 23. */
#define	DMA_CHANNEL_24	0x18U	/**< DMA Channel 24. */
#define	DMA_CHANNEL_25	0x19U	/**< DMA Channel 25. */
#define	DMA_CHANNEL_26	0x1AU	/**< DMA Channel 26. */
#define	DMA_CHANNEL_27	0x1BU	/**< DMA Channel 27. */
#define	DMA_CHANNEL_28	0x1CU	/**< DMA Channel 28. */
#define	DMA_CHANNEL_29	0x1DU	/**< DMA Channel 29. */
#define	DMA_CHANNEL_30	0x1EU	/**< DMA Channel 30. */
#define	DMA_CHANNEL_31	0x1FU	/**< DMA Channel 31. */

/*
 * DMA Channels Assigments Encodings.
 *
 * NOTE:	Channels Assignments Encodingd noted as "_SW_" may be assigned
 * 		to peripherals in the future. However, they are currently
 * 		available for software use. Channel 30 is dedicated for software
 * 		use.
 */

/** @brief	DMA Channel 0 - USB0 - EP1 - RX	*/
#define	DMA_CHANNEL_0_USB_0_EP_1_RX	0x00U
/** @brief	DMA Channel 0 - UART2 - RX	*/
#define	DMA_CHANNEL_0_UART_2_RX		0x01U
/** @brief	DMA Channel 0 - Software	*/
#define	DMA_CHANNEL_0_SW_2		0x02U
/** @brief	DMA Channel 0 - GPT4 - A	*/
#define	DMA_CHANNEL_0_GPT_4_A		0x03U
/** @brief	DMA Channel 0 - Software	*/
#define	DMA_CHANNEL_0_SW_4		0x04U

/** @brief	DMA Channel 1 - USB0 - EP1 - TX	*/
#define	DMA_CHANNEL_1_USB_0_EP_1_TX	0x00U
/** @brief	DMA Channel 1 - UART2 - TX	*/
#define	DMA_CHANNEL_1_UART_2_TX		0x01U
/** @brief	DMA Channel 1 - Software	*/
#define	DMA_CHANNEL_1_SW_2		0x02U
/** @brief	DMA Channel 1 - GPT4 - B	*/
#define	DMA_CHANNEL_1_GPT_4_B		0x03U
/** @brief	DMA Channel 1 - Software	*/
#define	DMA_CHANNEL_1_SW_4		0x04U

/** @brief	DMA Channel 2 - USB0 - EP2 - RX	*/
#define	DMA_CHANNEL_2_USB_0_EP_2_RX	0x00U
/** @brief	DMA Channel 2 - GPT3 - A	*/
#define	DMA_CHANNEL_2_GPT_3_A		0x01U
/** @brief	DMA Channel 2 - Software	*/
#define	DMA_CHANNEL_2_SW_2		0x02U
/** @brief	DMA Channel 2 - Software	*/
#define	DMA_CHANNEL_2_SW_3		0x03U
/** @brief	DMA Channel 2 - Software	*/
#define	DMA_CHANNEL_2_SW_4		0x04U

/** @brief	DMA Channel 3 - USB0 - EP2 - TX	*/
#define	DMA_CHANNEL_3_USB_0_EP_2_TX	0x00U
/** @brief	DMA Channel 3 - GPT3 - B	*/
#define	DMA_CHANNEL_3_GPT_3_B		0x01U
/** @brief	DMA Channel 3 - Software	*/
#define	DMA_CHANNEL_3_SW_2		0x02U
/** @brief	DMA Channel 3 - Software	*/
#define	DMA_CHANNEL_3_SW_3		0x03U
/** @brief	DMA Channel 3 - Software	*/
#define	DMA_CHANNEL_3_SW_4		0x04U

/** @brief	DMA Channel 4 - USB0 - EP3 - RX	*/
#define	DMA_CHANNEL_4_USB_0_EP_3_RX	0x00U
/** @brief	DMA Channel 4 - GPT2 - A	*/
#define	DMA_CHANNEL_4_GPT_2_A		0x01U
/** @brief	DMA Channel 4 - Software	*/
#define	DMA_CHANNEL_4_SW_2		0x02U
/** @brief	DMA Channel 4 - GPIO - A	*/
#define	DMA_CHANNEL_4_GPIO_A		0x03U
/** @brief	DMA Channel 4 - Software	*/
#define	DMA_CHANNEL_4_SW_4		0x04U

/** @brief	DMA Channel 5 - USB0 - EP3 - TX	*/
#define	DMA_CHANNEL_5_USB_0_EP_3_TX	0x00U
/** @brief	DMA Channel 5 - GPT2 - B	*/
#define	DMA_CHANNEL_5_GPT_2_B		0x01U
/** @brief	DMA Channel 5 - Software	*/
#define	DMA_CHANNEL_5_SW_2		0x02U
/** @brief	DMA Channel 5 - GPIO - B	*/
#define	DMA_CHANNEL_5_GPIO_B		0x03U
/** @brief	DMA Channel 5 - Software	*/
#define	DMA_CHANNEL_5_SW_4		0x04U

/** @brief	DMA Channel 6 - Software	*/
#define	DMA_CHANNEL_6_SW_0		0x00U
/** @brief	DMA Channel 6 - GPT2 - A	*/
#define	DMA_CHANNEL_6_GPT_2_A		0x01U
/** @brief	DMA Channel 6 - UART5 - RX	*/
#define	DMA_CHANNEL_6_UART_5_RX		0x02U
/** @brief	DMA Channel 6 - GPIO - C	*/
#define	DMA_CHANNEL_6_GPIO_C		0x03U
/** @brief	DMA Channel 6 - Software	*/
#define	DMA_CHANNEL_6_SW_4		0x04U

/** @brief	DMA Channel 7 - Software	*/
#define	DMA_CHANNEL_7_SW_0		0x00U
/** @brief	DMA Channel 7 - GPT2 - B	*/
#define	DMA_CHANNEL_7_GPT_2_B		0x01U
/** @brief	DMA Channel 7 - UART5 - TX	*/
#define	DMA_CHANNEL_7_UART_5_TX		0x02U
/** @brief	DMA Channel 7 - GPIO - C	*/
#define	DMA_CHANNEL_7_GPIO_D		0x03U
/** @brief	DMA Channel 7 - Software	*/
#define	DMA_CHANNEL_7_SW_4		0x04U

/** @brief	DMA Channel 8 - UART0 - RX	*/
#define	DMA_CHANNEL_8_UART_0_RX		0x00U
/** @brief	DMA Channel 8 - UART1 - RX	*/
#define	DMA_CHANNEL_8_UART_1_RX		0x01U
/** @brief	DMA Channel 8 - Software	*/
#define	DMA_CHANNEL_8_SW_2		0x02U
/** @brief	DMA Channel 8 - GPT5 - A	*/
#define	DMA_CHANNEL_8_GPT_5_A		0x03U
/** @brief	DMA Channel 8 - Software	*/
#define	DMA_CHANNEL_8_SW_4		0x04U

/** @brief	DMA Channel 9 - UART0 - TX	*/
#define	DMA_CHANNEL_9_UART_0_TX		0x00U
/** @brief	DMA Channel 9 - UART1 - TX	*/
#define	DMA_CHANNEL_9_UART_1_TX		0x01U
/** @brief	DMA Channel 9 - Software	*/
#define	DMA_CHANNEL_9_SW_2		0x02U
/** @brief	DMA Channel 9 - GPT5 - B	*/
#define	DMA_CHANNEL_9_GPT_5_B		0x03U
/** @brief	DMA Channel 9 - Software	*/
#define	DMA_CHANNEL_9_SW_4		0x04U

/** @brief	DMA Channel 10 - SSI0 - RX	*/
#define	DMA_CHANNEL_10_SSI_0_RX		0x00U
/** @brief	DMA Channel 10 - SSI1 - RX	*/
#define	DMA_CHANNEL_10_SSI_1_RX		0x01U
/** @brief	DMA Channel 10 - UART6 - RX	*/
#define	DMA_CHANNEL_10_UART_6_RX	0x02U
/** @brief	DMA Channel 10 - GPT6 - A	*/
#define	DMA_CHANNEL_10_GPT_6_A		0x03U
/** @brief	DMA Channel 10 - Software	*/
#define	DMA_CHANNEL_10_SW_4		0x04U

/** @brief	DMA Channel 11 - SSI0 - TX	*/
#define	DMA_CHANNEL_11_SSI_0_TX		0x00U
/** @brief	DMA Channel 11 - SSI1 - TX	*/
#define	DMA_CHANNEL_11_SSI_1_TX		0x01U
/** @brief	DMA Channel 11 - UART6 - TX	*/
#define	DMA_CHANNEL_11_UART_6_TX	0x02U
/** @brief	DMA Channel 11 - GPT6 - B	*/
#define	DMA_CHANNEL_11_GPT_6_B		0x03U
/** @brief	DMA Channel 11 - Software	*/
#define	DMA_CHANNEL_11_SW_4		0x04U

/** @brief	DMA Channel 12 - Software	*/
#define	DMA_CHANNEL_12_SW_0		0x00U
/** @brief	DMA Channel 12 - UART2 - RX	*/
#define	DMA_CHANNEL_12_UART_2_RX	0x01U
/** @brief	DMA Channel 12 - SSI2 - RX	*/
#define	DMA_CHANNEL_12_SSI_2_RX		0x02U
/** @brief	DMA Channel 12 - GPT7 - A	*/
#define	DMA_CHANNEL_12_GPT_7_A		0x03U
/** @brief	DMA Channel 12 - GPIO - K	*/
#define	DMA_CHANNEL_12_GPIO_K		0x04U

/** @brief	DMA Channel 13 - Software	*/
#define	DMA_CHANNEL_13_SW_0		0x00U
/** @brief	DMA Channel 13 - UART2 - TX	*/
#define	DMA_CHANNEL_13_UART_2_TX	0x01U
/** @brief	DMA Channel 13 - SSI2 - TX	*/
#define	DMA_CHANNEL_13_SSI_2_TX		0x02U
/** @brief	DMA Channel 13 - GPT7 - B	*/
#define	DMA_CHANNEL_13_GPT_7_A		0x03U
/** @brief	DMA Channel 13 - GPIO - L	*/
#define	DMA_CHANNEL_13_GPIO_L		0x04U

/** @brief	DMA Channel 14 - ADC - SS0	*/
#define	DMA_CHANNEL_14_ADC_SS_0		0x00U
/** @brief	DMA Channel 14 - GPT2 - A	*/
#define	DMA_CHANNEL_14_GPT_2_A		0x01U
/** @brief	DMA Channel 14 - SSI3 - RX	*/
#define	DMA_CHANNEL_14_SSI_3_RX		0x02U
/** @brief	DMA Channel 14 - GPIO - E	*/
#define	DMA_CHANNEL_14_GPIO_E		0x03U
/** @brief	DMA Channel 14 - GPIO - M	*/
#define	DMA_CHANNEL_14_GPIO_M		0x04U

/** @brief	DMA Channel 15 - ADC - SS1	*/
#define	DMA_CHANNEL_15_ADC_SS_0		0x00U
/** @brief	DMA Channel 15 - GPT2 - B	*/
#define	DMA_CHANNEL_15_GPT_2_B		0x01U
/** @brief	DMA Channel 15 - SSI3 - TX	*/
#define	DMA_CHANNEL_15_SSI_3_TX		0x02U
/** @brief	DMA Channel 15 - GPIO - F	*/
#define	DMA_CHANNEL_15_GPIO_F		0x03U
/** @brief	DMA Channel 15 - GPIO - N	*/
#define	DMA_CHANNEL_15_GPIO_N		0x04U

/** @brief	DMA Channel 16 - ADC - SS2	*/
#define	DMA_CHANNEL_16_ADC_SS_2		0x00U
/** @brief	DMA Channel 16 - Software	*/
#define	DMA_CHANNEL_16_SW_1		0x01U
/** @brief	DMA Channel 16 - UART3 - RX	*/
#define	DMA_CHANNEL_16_UART_3_RX	0x02U
/** @brief	DMA Channel 16 - GPT8 - A	*/
#define	DMA_CHANNEL_16_GPT_8_A		0x03U
/** @brief	DMA Channel 16 - GPIO - P	*/
#define	DMA_CHANNEL_16_GPIO_P		0x04U

/** @brief	DMA Channel 17 - ADC - SS3	*/
#define	DMA_CHANNEL_17_ADC_SS_3		0x00U
/** @brief	DMA Channel 17 - Software	*/
#define	DMA_CHANNEL_17_SW_1		0x01U
/** @brief	DMA Channel 17 - UART3 - TX	*/
#define	DMA_CHANNEL_17_UART_3_TX	0x02U
/** @brief	DMA Channel 17 - GPT8 - B	*/
#define	DMA_CHANNEL_17_GPT_8_V		0x03U
/** @brief	DMA Channel 17 - Software	*/
#define	DMA_CHANNEL_17_SW_4		0x04U

/** @brief	DMA Channel 18 - GPT0 - A	*/
#define	DMA_CHANNEL_18_GPT_0_A		0x00U
/** @brief	DMA Channel 18 - GPT1 - A	*/
#define	DMA_CHANNEL_18_GPT_1_A		0x01U
/** @brief	DMA Channel 18 - UART4 - RX	*/
#define	DMA_CHANNEL_18_UART_4_RX	0x02U
/** @brief	DMA Channel 18 - GPIO - B	*/
#define	DMA_CHANNEL_18_GPIO_B		0x03U
/** @brief	DMA Channel 18 - Software	*/
#define	DMA_CHANNEL_18_SW_4		0x04U

/** @brief	DMA Channel 19 - GPT0 - B	*/
#define	DMA_CHANNEL_19_GPT_0_B		0x00U
/** @brief	DMA Channel 19 - GPT1 - B	*/
#define	DMA_CHANNEL_19_GPT_1_B		0x01U
/** @brief	DMA Channel 19 - UART4 - TX	*/
#define	DMA_CHANNEL_19_UART_4_TX	0x02U
/** @brief	DMA Channel 19 - GPIO - G	*/
#define	DMA_CHANNEL_19_GPIO_G		0x03U
/** @brief	DMA Channel 19 - Software	*/
#define	DMA_CHANNEL_19_SW_4		0x04U

/** @brief	DMA Channel 20 - GPT1 - A	*/
#define	DMA_CHANNEL_20_GPT_1_A		0x00U
/** @brief	DMA Channel 20 - Software	*/
#define	DMA_CHANNEL_20_SW_1		0x01U
/** @brief	DMA Channel 20 - UART7 - RX	*/
#define	DMA_CHANNEL_20_UART_7_RX	0x02U
/** @brief	DMA Channel 20 - GPIO - H	*/
#define	DMA_CHANNEL_20_GPIO_H		0x03U
/** @brief	DMA Channel 20 - Software	*/
#define	DMA_CHANNEL_20_SW_4		0x04U

/** @brief	DMA Channel 21 - GPT1 - B	*/
#define	DMA_CHANNEL_21_GPT_1_B		0x00U
/** @brief	DMA Channel 21 - Software	*/
#define	DMA_CHANNEL_21_SW_1		0x01U
/** @brief	DMA Channel 21 - UART7 - TX	*/
#define	DMA_CHANNEL_21_UART_7_TX	0x02U
/** @brief	DMA Channel 21 - GPIO - J	*/
#define	DMA_CHANNEL_21_GPIO_J		0x03U
/** @brief	DMA Channel 21 - Software	*/
#define	DMA_CHANNEL_21_SW_4		0x04U

/** @brief	DMA Channel 22 - UART1 - RX	*/
#define	DMA_CHANNEL_22_UART_1_RX	0x00U
/** @brief	DMA Channel 22 - Software	*/
#define	DMA_CHANNEL_22_SW_1		0x01U
/** @brief	DMA Channel 22 - Software	*/
#define	DMA_CHANNEL_22_SW_2		0x02U
/** @brief	DMA Channel 22 - Software	*/
#define	DMA_CHANNEL_22_SW_3		0x03U
/** @brief	DMA Channel 22 - Software	*/
#define	DMA_CHANNEL_22_SW_4		0x04U

/** @brief	DMA Channel 23 - UART1 - TX	*/
#define	DMA_CHANNEL_23_UART_1_RX	0x00U
/** @brief	DMA Channel 23 - Software	*/
#define	DMA_CHANNEL_23_SW_1		0x01U
/** @brief	DMA Channel 23 - Software	*/
#define	DMA_CHANNEL_23_SW_2		0x02U
/** @brief	DMA Channel 23 - Software	*/
#define	DMA_CHANNEL_23_SW_3		0x03U
/** @brief	DMA Channel 23 - Software	*/
#define	DMA_CHANNEL_23_SW_4		0x04U

/** @brief	DMA Channel 24 - SSI1 - RX	*/
#define	DMA_CHANNEL_24_SSI_1_RX		0x00U
/** @brief	DMA Channel 24 - ADC - SS0	*/
#define	DMA_CHANNEL_24_ADC_SS_0		0x01U
/** @brief	DMA Channel 24 - Software	*/
#define	DMA_CHANNEL_24_SW_2		0x02U
/** @brief	DMA Channel 24 - GPT9 - A	*/
#define	DMA_CHANNEL_24_GPT_9_A		0x03U
/** @brief	DMA Channel 24 - Software	*/
#define	DMA_CHANNEL_24_SW_4		0x04U

/** @brief	DMA Channel 25 - SSI1 - TX	*/
#define	DMA_CHANNEL_25_SSI_1_TX		0x00U
/** @brief	DMA Channel 25 - ADC - SS1	*/
#define	DMA_CHANNEL_25_ADC_SS_1		0x01U
/** @brief	DMA Channel 25 - Software	*/
#define	DMA_CHANNEL_25_SW_2		0x02U
/** @brief	DMA Channel 25 - GPT9 - B	*/
#define	DMA_CHANNEL_25_GPT_9_B		0x03U
/** @brief	DMA Channel 25 - Software	*/
#define	DMA_CHANNEL_25_SW_4		0x04U

/** @brief	DMA Channel 26 - Software	*/
#define	DMA_CHANNEL_26_SW_0		0x00U
/** @brief	DMA Channel 26 - ADC - SS2	*/
#define	DMA_CHANNEL_26_ADC_SS_2		0x01U
/** @brief	DMA Channel 26 - Software	*/
#define	DMA_CHANNEL_26_SW_2		0x02U
/** @brief	DMA Channel 26 - GPT10 - A	*/
#define	DMA_CHANNEL_26_GPT_10_A		0x03U
/** @brief	DMA Channel 26 - Software	*/
#define	DMA_CHANNEL_26_SW_4		0x04U

/** @brief	DMA Channel 27 - Software	*/
#define	DMA_CHANNEL_27_SW_0		0x00U
/** @brief	DMA Channel 27 - ADC - SS3	*/
#define	DMA_CHANNEL_27_ADC_SS_3		0x01U
/** @brief	DMA Channel 27 - Software	*/
#define	DMA_CHANNEL_27_SW_2		0x02U
/** @brief	DMA Channel 27 - GPT10 - B	*/
#define	DMA_CHANNEL_27_GPT_10_B		0x03U
/** @brief	DMA Channel 27 - Software	*/
#define	DMA_CHANNEL_27_SW_4		0x04U

/** @brief	DMA Channel 28 - Software	*/
#define	DMA_CHANNEL_28_SW_0		0x00U
/** @brief	DMA Channel 28 - Software	*/
#define	DMA_CHANNEL_28_SW_1		0x01U
/** @brief	DMA Channel 28 - Software	*/
#define	DMA_CHANNEL_28_SW_2		0x02U
/** @brief	DMA Channel 28 - GPT11 - A	*/
#define	DMA_CHANNEL_28_GPT_11_A		0x03U
/** @brief	DMA Channel 28 - Software	*/
#define	DMA_CHANNEL_28_SW_4		0x04U

/** @brief	DMA Channel 29 - Software	*/
#define	DMA_CHANNEL_29_SW_0		0x00U
/** @brief	DMA Channel 29 - Software	*/
#define	DMA_CHANNEL_29_SW_1		0x01U
/** @brief	DMA Channel 29 - Software	*/
#define	DMA_CHANNEL_29_SW_2		0x02U
/** @brief	DMA Channel 29 - GPT11 - B	*/
#define	DMA_CHANNEL_29_GPT_11_B		0x03U
/** @brief	DMA Channel 29 - Software	*/
#define	DMA_CHANNEL_29_SW_4		0x04U

/** @brief	DMA Channel 30 - Software	*/
#define	DMA_CHANNEL_30_SW_0		0x00U
/** @brief	DMA Channel 30 - Software	*/
#define	DMA_CHANNEL_30_SW_1		0x01U
/** @brief	DMA Channel 30 - Software	*/
#define	DMA_CHANNEL_30_SW_2_		0x02U
/** @brief	DMA Channel 30 - Software	*/
#define	DMA_CHANNEL_30_SW_3		0x03U
/** @brief	DMA Channel 30 - Software	*/
#define	DMA_CHANNEL_30_SW_4		0x04U

/** @brief	DMA Channel 31 - Reserved	*/
#define	DMA_CHANNEL_31_RESERVED_0	0x00U
/** @brief	DMA Channel 31 - Reserved	*/
#define	DMA_CHANNEL_31_RESERVED_1	0x01U
/** @brief	DMA Channel 31 - Reserved	*/
#define	DMA_CHANNEL_31_RESERVED_2_	0x02U
/** @brief	DMA Channel 31 - Reserved	*/
#define	DMA_CHANNEL_31_RESERVED_3	0x03U
/** @brief	DMA Channel 31 - Reserved	*/
#define	DMA_CHANNEL_31_RESERVED_4	0x04U

#if	( DMA_NOTIFICATIONS_API == STD_ON )

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_0__
/** @brief	DMA Channel 0 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_0(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_0__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_0__
/** @brief	DMA Channel 0 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_0(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_0__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_1__
/** @brief	DMA Channel 1 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_1(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_1__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_1__
/** @brief	DMA Channel 1 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_1(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_1__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_2__
/** @brief	DMA Channel 2 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_2(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_2__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_2__
/** @brief	DMA Channel 2 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_2(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_2__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_3__
/** @brief	DMA Channel 3 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_3(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_3__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_3__
/** @brief	DMA Channel 3 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_3(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_3__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_4__
/** @brief	DMA Channel 4 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_4(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_4__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_4__
/** @brief	DMA Channel 4 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_4(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_4__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_5__
/** @brief	DMA Channel 5 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_5(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_5__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_5__
/** @brief	DMA Channel 5 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_5(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_5__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_6__
/** @brief	DMA Channel 6 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_6(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_6__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_6__
/** @brief	DMA Channel 6 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_6(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_6__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_7__
/** @brief	DMA Channel 7 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_7(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_7__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_7__
/** @brief	DMA Channel 7 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_7(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_7__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_8__
/** @brief	DMA Channel 8 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_8(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_8__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_8__
/** @brief	DMA Channel 8 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_8(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_8__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_9__
/** @brief	DMA Channel 9 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_9(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_9__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_9__
/** @brief	DMA Channel 9 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_9(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_9__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_10__
/** @brief	DMA Channel 10 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_10(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_10__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_10__
/** @brief	DMA Channel 10 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_10(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_10__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_11__
/** @brief	DMA Channel 11 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_11(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_11__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_11__
/** @brief	DMA Channel 11 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_11(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_11__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_12__
/** @brief	DMA Channel 12 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_12(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_12__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_12__
/** @brief	DMA Channel 12 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_12(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_12__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_13__
/** @brief	DMA Channel 13 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_13(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_13__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_13__
/** @brief	DMA Channel 13 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_13(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_13__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_14__
/** @brief	DMA Channel 14 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_14(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_14__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_14__
/** @brief	DMA Channel 14 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_14(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_14__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_15__
/** @brief	DMA Channel 15 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_15(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_15__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_15__
/** @brief	DMA Channel 15 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_15(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_15__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_16__
/** @brief	DMA Channel 16 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_16(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_16__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_16__
/** @brief	DMA Channel 16 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_16(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_16__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_17__
/** @brief	DMA Channel 17 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_17(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_17__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_17__
/** @brief	DMA Channel 17 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_17(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_17__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_18__
/** @brief	DMA Channel 18 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_18(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_18__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_18__
/** @brief	DMA Channel 18 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_18(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_18__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_19__
/** @brief	DMA Channel 19 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_19(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_19__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_19__
/** @brief	DMA Channel 19 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_19(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_19__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_20__
/** @brief	DMA Channel 20 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_20(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_20__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_20__
/** @brief	DMA Channel 20 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_20(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_20__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_21__
/** @brief	DMA Channel 21 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_21(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_21__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_21__
/** @brief	DMA Channel 21 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_21(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_21__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_22__
/** @brief	DMA Channel 22 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_22(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_22__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_22__
/** @brief	DMA Channel 22 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_22(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_22__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_23__
/** @brief	DMA Channel 23 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_23(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_23__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_23__
/** @brief	DMA Channel 23 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_23(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_23__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_24__
/** @brief	DMA Channel 24 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_24(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_24__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_24__
/** @brief	DMA Channel 24 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_24(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_24__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_25__
/** @brief	DMA Channel 25 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_25(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_25__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_25__
/** @brief	DMA Channel 25 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_25(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_25__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_26__
/** @brief	DMA Channel 26 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_26(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_26__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_26__
/** @brief	DMA Channel 26 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_26(
  void
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_26__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_27__
/** @brief	DMA Channel 27 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_27(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_27__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_27__
/** @brief	DMA Channel 27 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_27(
  void
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_27__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_28__
/** @brief	DMA Channel 28 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_28(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_28__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_28__
/** @brief	DMA Channel 28 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_28(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_28__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_29__
/** @brief	DMA Channel 29 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_29(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_29__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_29__
/** @brief	DMA Channel 29 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_29(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_29__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__
/** @brief	DMA Channel 30 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_30(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__
/** @brief	DMA Channel 30 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_30(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_31__ */

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_31__
/** @brief	DMA Channel 31 - Software Transfer End Notification Callback. */
void Dma_SoftwareTransferEndNotification_Channel_31(
  void
);
#endif	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_31__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_31__
/** @brief	DMA Channel 31 - Transfer Error Notification Callback. */
void Dma_TransferErrorNotification_Channel_31(
  void
);
#endif	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_31__ */

#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */

/*
 * DMA Channel Destination Address Increments Macros.
 *
 * This macros configures the destination address increment.
 *
 * The address increment value must be equal or greater than the value of the
 * destination size.
 */
/** @brief	DMA Channel Destination Address Increment - Byte
 *
 *  Increment by 8-bit locations.
 */
#define	DMA_CHANNEL_DST_INC_BYTE	0x00000000U
/** @brief	DMA Channel Destination Address Increment - Half-Word
 *
 *  Increment by 16-bit locations.
 */
#define	DMA_CHANNEL_DST_INC_HALF_WORD	0x40000000U
/** @brief	DMA Channel Destination Address Increment - Word
 *
 *  Increment by 32-bit locations.
 */
#define	DMA_CHANNEL_DST_INC_WORD	0x80000000U
/** @brief	DMA Channel Destination Address Increment - None
 *
 *  Address remains set to the value of the Destination Address End Pointer
 *  for the channel.
 */
#define	DMA_CHANNEL_DST_INC_NONE	0xC0000000U

/*
 * DMA Channel Destination Data Size Macros.
 *
 * This field configures the destination item data size.
 *
 * Note:	DMA Channel Destination Data Size must be the same as DMA
 * 		Channel Source Data Size.
 */
/** @brief	DMA Channel Destination Data Size - Byte
 *
 *  8-bit Data Size.
 */
#define	DMA_CHANNEL_DST_SZ_BYTE		0x00000000U
/** @brief	DMA Channel Destination Data Size - Half-Word
 *
 *  16-bit Data Size.
 */
#define	DMA_CHANNEL_DST_SZ_HALF_WORD	0x10000000U
/** @brief	DMA Channel Destination Data Size - Word
 *
 *  32-bit Data Size.
 */
#define	DMA_CHANNEL_DST_SZ_WORD		0x20000000U

/*
 * DMA Channel Source Address Increments Macros.
 *
 * This macros configures the source address increment.
 *
 * The address increment value must be equal or greater than the value of the
 * source size.
 */
/** @brief	DMA Channel Source Address Increment - Byte
 *
 *  Increment by 8-bit locations.
 */
#define	DMA_CHANNEL_SRC_INC_BYTE	0x00000000U
/** @brief	DMA Channel Source Address Increment - Half-Word
 *
 *  Increment by 16-bit locations.
 */
#define	DMA_CHANNEL_SRC_INC_HALF_WORD	0x04000000U
/** @brief	DMA Channel Source Address Increment - Word
 *
 *  Increment by 32-bit locations.
 */
#define	DMA_CHANNEL_SRC_INC_WORD	0x08000000U
/** @brief	DMA Channel Source Address Increment - No Increment
 *
 *  Address remains set to the value of the Source Address End Pointer
 *  for the channel.
 */
#define	DMA_CHANNEL_SRC_INC_NONE	0x0C000000U

/*
 * DMA Channel Source Data Size Macros.
 *
 * This field configures the destination item data size.
 *
 * Note:	DMA Channel Source Data Size must be the same as DMA Channel
 * 		Destination Data Size.
 */
/** @brief	DMA Channel Source Data Size - Byte
 *
 *  8-bit Data Size.
 */
#define	DMA_CHANNEL_SRC_SZ_BYTE		0x00000000U
/** @brief	DMA Channel Source Data Size - Half-Word
 *
 *  16-bit Data Size.
 */
#define	DMA_CHANNEL_SRC_SZ_HALF_WORD	0x01000000U
/** @brief	DMA Channel Source Data Size - Word
 *
 *  32-bit Data Size.
 */
#define	DMA_CHANNEL_SRC_SZ_WORD		0x02000000U

/*
 * DMA Channel Arbitration Size Macros.
 *
 * This macros configures the number of transfers that can occur before the
 * µDMA controller re-arbitrates. The possible arbitration rate configurations
 * represent powers of 2 and are shown below.
 */
/** @brief	DMA Channel Arbitration Size - 1 transfer
 *
 *  Arbitrates after each µDMA transfer.
 */
#define	DMA_CHANNEL_ARB_SZ_1		0x00000000U
/** @brief	DMA Channel Arbitration Size - 2 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_2		0x00004000U
/** @brief	DMA Channel Arbitration Size - 4 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_4		0x00008000U
/** @brief	DMA Channel Arbitration Size - 8 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_8		0x0000C000U
/** @brief	DMA Channel Arbitration Size - 16 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_16		0x00010000U
/** @brief	DMA Channel Arbitration Size - 32 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_32		0x00014000U
/** @brief	DMA Channel Arbitration Size - 64 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_64		0x00018000U
/** @brief	DMA Channel Arbitration Size - 128 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_128		0x0001C000U
/** @brief	DMA Channel Arbitration Size - 256 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_256		0x00020000U
/** @brief	DMA Channel Arbitration Size - 512 transfer	*/
#define	DMA_CHANNEL_ARB_SZ_512		0x00024000U
/** @brief	DMA Channel Arbitration Size - 1024 transfer
 *
 *  In this configuration, no arbitration occurs during the µDMA transfer
 *  because the maximum transfer size is 1024.
 */
#define	DMA_CHANNEL_ARB_SZ_1024		0x0003C000U

/** @brief	DMA Channel Last Transfer Burst Macros.
 *
 *  This macro controls whether the Burst Transfer Request Type is automatically
 *  set for the last transfer of a peripheral scatter-gather operation.
 *  Normally, for the last transfer, if the number of remaining items to
 *  transfer is less than the arbitration size, the µDMA controller uses single
 *  transfers to complete the transaction.
 *  If this macro is set, then the controller uses a burst transfer to complete
 *  the last transfer.
 */
#define	DMA_CHANNEL_LAST_BURST		0x00000008U

/*
 * DMA Channel Transfer Mode Macros.
 *
 * This macros configures the operating mode of the µDMA channel cycle.
 */

/** @brief	DMA Channel Transfer Mode - Stop
 *
 *  While Stop is not actually a transfer mode, it is a valid value for the mode
 *  field of the control word.
 *
 *  When the mode field has this value, the µDMA controller does not perform any
 *  transfers and disables the channel if it is enabled.
 *
 *  At the end of a transfer, the µDMA controller updates the control word to
 *  set the mode to Stop.
 */
#define	DMA_CHANNEL_XFER_STOP	0x00000000U

/** @brief	DMA Channel Transfer Mode - Basic
 *
 *  In Basic mode, the µDMA controller performs transfers as long as there are
 *  more items to transfer, and a transfer request is present.
 *
 *  This mode is used with peripherals that assert a µDMA request signal
 *  whenever the peripheral is ready for a data transfer.
 *
 *  Basic mode should not be used in any situation where the request is
 *  momentary even though the entire transfer should be completed. For example,
 *  a softwar transfer creates a momentary request, and in Basic mode, only the
 *  number of transfers specified by the Arbitration Size of the DMA Channel is
 *  transferred on a software request, even if there is more data to transfer.
 *
 *  When all of the items have been transferred using Basic mode, the µDMA
 *  controller sets the mode for that channel to Stop.
 */
#define	DMA_CHANNEL_XFER_BASIC	0x00000001U

/** @brief	DMA Channel Transfer Mode - Auto
 *
 *  Auto mode is similar to Basic mode, except that once a transfer request is
 *  received, the transfer runs to completion, even if the µDMA request is
 *  removed.
 *
 *  This mode is suitable for software transfers.
 *
 *  Generally, Auto mode is not used with a peripheral.
 *
 *  When all the items have been transferred using Auto mode, the µDMA
 *  controller sets the mode for that channel to Stop.
 */
#define	DMA_CHANNEL_XFER_AUTO	0x00000002U

#if	( DMA_PING_PONG_API == STD_ON )

/** @brief	DMA Channel Transfer Mode - Ping-Pong
 *
 *  Ping-Pong mode is used to support a continuous data flow to or from a
 *  peripheral.
 *
 *  To use Ping-Pong mode, both the primary and alternate data structures must
 *  be implemented.
 *
 *  Both structures are set up by the processor for data transfer between memory
 *  and a peripheral.
 *
 *  The transfer is started using the primary control structure.
 *
 *  When the transfer using the primary control structure is complete, the µDMA
 *  controller reads the alternate control structure for that channel to
 *  continue the transfer.
 *
 *  Each time this happens, an interrupt is generated, and the processor can
 *  reload the control structure for the just-completed transfer.
 *
 *  Data flow can continue indefinitely this way, using the primary and
 *  alternate control structures to switch back and forth between buffers as the
 *  data flows to or from the peripheral.
 */
#define	DMA_CHANNEL_XFER_PING_PONG	0x00000003U

#endif	/* ( DMA_PING_PONG_API == STD_ON ) */

#if	( DMA_SCATTER_GATHER_API == STD_ON )

/** @brief	DMA Channel Transfer Mode - Memory Scatter-Gather
 *
 *  Memory Scatter-Gather mode is a complex mode used when data must be
 *  transferred to or from varied locations in memory instead of a set of
 *  contiguous locations in a memory buffer. For example, a gather µDMA
 *  operation could be used to selectively read the payload of several stored
 *  packets of a communication protocol and store them together in sequence in a
 *  memory buffer.
 *
 *  In Memory Scatter-Gather mode, the primary control structure is used to
 *  program the alternate control structure from a table in memory. The table is
 *  set up by the processor software and contains a list of control structures,
 *  each containing the source and destination end pointers, and the control
 *  word for a specific transfer. The mode of each control word must be set to
 *  Scatter-Gather mode. Each entry in the table is copied in turn to the
 *  alternate structure where it is then executed. The µDMA controller
 *  alternates between using the primary control structure to copy the next
 *  transfer instruction from the list and then executing the new transfer
 *  instruction. The end of the list is marked by programming the control word
 *  for the last entry to use Auto transfer mode. Once the last transfer is
 *  performed using Auto mode, the µDMA controller stops.
 *
 *  A completion interrupt is generated only after the last transfer.
 *
 *  It is possible to loop the list by having the last entry copy the primary
 *  control structure to point back to the beginning of the list (or to a new
 *  list).
 *
 *  It is also possible to trigger a set of other channels to perform a
 *  transfer, either directly, by programming a write to the software trigger
 *  for another channel, or indirectly, by causing a peripheral action that
 *  results in a µDMA request.
 *
 *  By programming the µDMA controller using this method, a set of arbitrary
 *  transfers can be performed based on a single µDMA request.
 */
#define	DMA_CHANNEL_XFER_MSG	0x00000004U

/** @brief	DMA Channel Transfer Mode - Peripheral Scatter-Gather
 *
 *  Peripheral Scatter-Gather mode is very similar to Memory Scatter-Gather,
 *  except that the transfers are controlled by a peripheral making a µDMA
 *  request.
 *
 *  Upon detecting a request from the peripheral, the µDMA controller uses the
 *  primary control structure to copy one entry from the list to the alternate
 *  control structure and then performs the transfer. At the end of this
 *  transfer, the next transfer is started only if the peripheral again asserts
 *  a µDMA request. The µDMA controller continues to perform transfers from the
 *  list only when the peripheral is making a request, until the last transfer
 *  is complete.
 *
 *  A completion interrupt is generated only after the last transfer.
 *
 *  By using this method, the µDMA controller can transfer data to or from a
 *  peripheral from a set of arbitrary locations whenever the peripheral is
 *  ready to transfer data.
 */
#define	DMA_CHANNEL_XFER_PSG	0x00000006U

#endif	/* DMA_SCATTER_GATHER_API */

/*
 * DMA Channel Priority Macros.
 *
 * The µDMA controller assigns priority to each channel based on the channel
 * number and the priority level macro for the channel. Channel number 0 has the
 * highest priority and as the channel number increases, the priority of a
 * channel decreases. Each channel has a priority level macro to provide two
 * levels of priority: default priority and high priority. If the priority level
 * macro is set, then that channel has higher priority than all other channels
 * at default priority. If multiple channels are set for high priority, then the
 * channel number is used to determine relative priority among all the high
 * priority channels.
 */
/** @brief	DMA Channel Priority - High	*/
#define	DMA_CHANNEL_PRIO_HIGH	0x00100000U

/*
 * DMA Channel Request Type Macros.
 *
 * The µDMA controller responds to two types of requests from a peripheral:
 * single or burst.
 * Each peripheral may support either or both types of requests.
 * A single request means that the peripheral is ready to transfer one item,
 * while a burst request means that the peripheral is ready to transfer multiple
 * items.
 */
/** @brief	DMA Channel Request Type - Burst Only		*/
#define	DMA_CHANNEL_BURST_ONLY	0x00200000U

/*
 * DMA Channel Peripheral or Software.
 */
/** @brief	DMA Channel Software.	*/
#define	DMA_CHANNEL_SOFTWARE	0x00400000U

/** @brief	Memory Address Boundaries.	*/
#define	DMA_MEMORY_ADDRESS_LOW		0x20000000U
#define	DMA_MEMORY_ADDRESS_HIGH		0x20008000U

/** @brief	DMA Channel Configuration Type.
 *
 *  <tt>DmaChannelConfigType</tt>
 *
 *  All data needed to configure one DMA Channel.
 */
typedef struct {

  /** @brief	DMA Channel Identifier.
   *
   *  <tt>DmaChannelId</tt>
   *
   *  DMA Channel ID, used as parameter in DMA API functions.
   */
  Dma_ChannelType	DmaChannelId;

  /** @brief	DMA Channel Assignment
   *
   *  <tt>DmaChannelAssignment</tt>
   *
   *  DMA Channel Assignment Encoding.
   */
  Dma_ChannelType	DmaChannelAssignment;

  /** @brief	DMA Channel Control
   *
   *  <tt>DmaChannelControl</tt>
   *
   *  DMA Channel Control.
   */
  uint32		DmaChannelControl;

  /** @brief	Source Address Low Boundary.
   *
   *  <tt>DmaSrcAddrLow</tt>
   *
   *  Dma Channel Source Address Low Boundary.
   */
  uint32		DmaSrcAddrLow;

  /** @brief	Source Address High Boundary.
   *
   *  <tt>DmaSrcAddrHigh</tt>
   *
   *  Dma Channel Source Address High Boundary.
   */
  uint32		DmaSrcAddrHigh;

  /** @brief	Destination Address Low Boundary.
   *
   *  <tt>DmaSrcAddrLow</tt>
   *
   *  Dma Channel Destination Address Low Boundary.
   */
  uint32		DmaDstAddrLow;

  /** @brief	Destination Address High Boundary.
   *
   *  <tt>DmaSrcAddrHigh</tt>
   *
   *  Dma Channel Destination Address High Boundary.
   */
  uint32		DmaDstAddrHigh;

#if	( DMA_NOTIFICATIONS_API == STD_ON )
  /** @brief	DMA Channel Software Transfer End Notification Callback Function
   *  		Pointer
   *
   *  Callback routine provided by the user to notify the caller that a transfer
   *  on a DMA Channel Software has been finished.
   *
   *  The operation <tt>Dma_SoftwareTransferEndNotification_<Channel>()</tt> is
   *  Re-entrant.
   *
   *  For implement the call back function other modules are required to provide
   *  the routines in the expected manner, as function pointers defined within
   *  the initialization data structure (<tt>Dma_ConfigType</tt>).
   *
   *  The callback notification
   *  <tt>Dma_SoftwareTransferEndNotification_<Channel>()</tt> shall have no
   *  parameters and no return value.
   *
   *  If a callback notification is configured as null pointer, no callback
   *  shall be executed.
   *
   *  If the <tt>Dma_SoftwareTransferEndNotification_<Channel>()</tt> is
   *  configured (i.e. not a null pointer), the DMA Driver shall call the
   *  configured callback notification at the end of a DMA Channel Software
   *  transfer.
   *
   *  @note	This routine might be called on interrupt level, depending on
   *  		the calling function.
   *
   *  It is allowed to use the following API calls within the DMA callback
   *  notifications:
   *  - <tt>Dma_GetChannelResult()</tt>
   *  All other DMA Driver API calls are not allowed.
   */
  Dma_SoftwareTransferEndNotification	DmaSoftwareTransferEndNotificationPtr;

  /** @brief	DMA Channel Transfer Error Notification Callback Function
   *  		Pointer
   *
   *  Callback routine provided by the user to notify the caller that a transfer
   *  on a DMA Channel has not been finished due to a transfer error.
   *
   *  The operation <tt>Dma_TransferErrorNotification_<Channel>()</tt> is
   *  Re-entrant.
   *
   *  For implement the call back function other modules are required to provide
   *  the routines in the expected manner, as function pointers defined within
   *  the initialization data structure (<tt>Dma_ConfigType</tt>).
   *
   *  The callback notification
   *  <tt>Dma_TransferErrorNotification_<Channel>()</tt> shall have no
   *  parameters and no return value.
   *
   *  If a callback notification is configured as null pointer, no callback
   *  shall be executed.
   *
   *  If the <tt>Dma_TransferErrorNotification_<Channel>()</tt> is configured
   *  (i.e. not a null pointer), the DMA Driver shall call the configured
   *  callback notification when an error occurs during a transfer on DMA
   *  Channel.
   *
   *  @note	This routine might be called on interrupt level, depending on
   *  		the calling function.
   *
   *  It is allowed to use the following API calls within the DMA callback
   *  notifications:
   *  - <tt>Dma_GetChannelResult()</tt>
   *  All other DMA Driver API calls are not allowed.
   */
  Dma_TransferErrorNotification		DmaTransferErrorNotificationPtr;

#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */

} Dma_ChannelConfigType;

/** @brief	DMA Driver.
 *
 *  <tt>DmaDriver</tt>
 *
 *  Configuration of one instance (if multiplicity is 1, it is the sole
 *  configuration) of an DMA driver.
 */
typedef struct {

  /** @brief	DMA Max Channel.
   *
   *  <tt>DmaMaxChannel</tt>
   *
   *  This parameter contains the number of Channels configured. It will be
   *  gathered by tools during the configuration stage.
   */
  Dma_ChannelType			DmaMaxChannel;

  /** @brief	DMA Channel Configuration.
   *
   *  All data needed to configure one DMA-channel.
   */
  const Dma_ChannelConfigType *		DmaChannel;

} Dma_DriverConfigType;

typedef	Dma_DriverConfigType	Dma_ConfigType;

/** @brief	Software Configuration
 *
 *  Identifier for DMA Driver Software Configuration.
 */
#define	DMA_CONFIG_SW		0x00000000U

/** @brief	Software Configuration Pointer
 *
 *  Pointer of DMA Driver Software Configuration.
 */
#define	DMA_CONFIG_SW_PTR	&Dma_Config[DMA_CONFIG_SW]

/** @brief	Default Configuration
 *
 *  Identifier for DMA Driver Default Configuration.
 */
#define	DMA_CONFIG_DEFAULT	DMA_CONFIG_SW

/** @brief	Default Configuration Pointer
 *
 *  Pointer of DMA Driver Default Configuration.
 */
#define	DMA_CONFIG_DEFAULT_PTR	&Dma_Config[DMA_CONFIG_DEFAULT]

#endif	/* DMA_CFG_H */
