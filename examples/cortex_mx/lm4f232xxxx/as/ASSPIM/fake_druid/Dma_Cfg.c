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
 * fake-druid AUTOSAR-"like" DMA Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2012, Giuseppe Serano
 */

/*
 * Dma_Cfg.c shall include Dma.h.
 */
#include "Dma.h"

/* 
 * Dma.c shall check if the correct version of Dma.h is included.
 * This shall be done by a pre-processor check.
 *
 * The DMA module shall avoid the integration of incompatible files by the
 * following pre-processor checks:
 * for included (external) header files,
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * shall be verified.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	DMA_AR_RELEASE_MAJOR_VERSION	4
#define	DMA_AR_RELEASE_MINOR_VERSION	0

#if !defined( DMA_AR_MAJOR_VERSION ) || \
    ( DMA_AR_MAJOR_VERSION != DMA_AR_RELEASE_MAJOR_VERSION )
#error	Dma_Cfg: version mismatch.
#endif

/*
 * Dma Channels Configurations.
 */

/*
 * Software DMA Channels Configuration.
 */
#define	DMA_SW_CHANNELS_NUMBER	0x01U

const Dma_ChannelConfigType		Dma_SwChannelConfig[] = {
  {
    DMA_CHANNEL_30,			/* DmaChannelId.		      */
    DMA_CHANNEL_30_SW_1,		/* DmaChannelAssignment.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_WORD	|	/* - Dest. Addr. Inc. Word: 32-bit.   */
    DMA_CHANNEL_DST_SZ_WORD	|	/* - Dest Data Size Word:   32-bit.   */
    DMA_CHANNEL_SRC_INC_WORD	|	/* - Src. Addr. Inc. Word:  32-bit.   */
    DMA_CHANNEL_SRC_SZ_WORD	|	/* - Src. Data Size Word:   32-bit.   */
    DMA_CHANNEL_ARB_SZ_16  	|	/* - No Arbitration.		      */
    DMA_CHANNEL_XFER_AUTO	|	/* - Auto Transfer Mode.	      */
    DMA_CHANNEL_SOFTWARE,		/* - Software Channel.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */

#if	( DMA_NOTIFICATIONS_API == STD_ON )

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__
    /* DmaSoftwareTransferEndNotificationPtr	*/
    Dma_SoftwareTransferEndNotification_Channel_30,
#else	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__ */
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#endif	/* !__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__
    /* DmaTransferErrorNotificationPtr		*/
    Dma_TransferErrorNotification_Channel_30,
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__ */

#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */

  },
};

#ifdef	__AS_CFG_DMA_SPI__
/*
 * SPI Handler/Driver DMA Channels Configuration.
 */
#if	( DMA_SCATTER_GATHER_API == STD_ON )
#define	DMA_SPI_CHANNELS_NUMBER	0x0AU
#else	/* ( DMA_SCATTER_GATHER_API == STD_ON ) */
#define	DMA_SPI_CHANNELS_NUMBER	0x01U
#endif	/* ( DMA_SCATTER_GATHER_API != STD_ON ) */

const Dma_ChannelConfigType		Dma_SpiChannelConfig[] = {
  {
    DMA_CHANNEL_30,			/* DmaChannelId.		      */
    DMA_CHANNEL_30_SW_1,		/* DmaChannelAssignment.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_WORD	|	/* - Dest. Addr. Inc. Word: 32-bit.   */
    DMA_CHANNEL_DST_SZ_WORD	|	/* - Dest Data Size Word:   32-bit.   */
    DMA_CHANNEL_SRC_INC_WORD	|	/* - Src. Addr. Inc. Word:  32-bit.   */
    DMA_CHANNEL_SRC_SZ_WORD	|	/* - Src. Data Size Word:   32-bit.   */
    DMA_CHANNEL_ARB_SZ_16  	|	/* - No Arbitration.		      */
    DMA_CHANNEL_XFER_AUTO	|	/* - Auto Transfer Mode.	      */
    DMA_CHANNEL_SOFTWARE,		/* - Software Channel.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */

#if	( DMA_NOTIFICATIONS_API == STD_ON )

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__
    /* DmaSoftwareTransferEndNotificationPtr	*/
    Dma_SoftwareTransferEndNotification_Channel_30,
#else	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__ */
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#endif	/* !__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_30__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__
    /* DmaTransferErrorNotificationPtr		*/
    Dma_TransferErrorNotification_Channel_30,
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_CH_30__ */

#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */

  },
#if	( DMA_SCATTER_GATHER_API == STD_ON )
  {
    DMA_CHANNEL_29,			/* DmaChannelId.		      */
    DMA_CHANNEL_29_SW_4,		/* DmaChannelAssignment.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_WORD	|	/* - Dest. Addr. Inc. Word: 32-bit.   */
    DMA_CHANNEL_DST_SZ_WORD	|	/* - Dest Data Size Word:   32-bit.   */
    DMA_CHANNEL_SRC_INC_WORD	|	/* - Src. Addr. Inc. Word:  32-bit.   */
    DMA_CHANNEL_SRC_SZ_WORD	|	/* - Src. Data Size Word:   32-bit.   */
    DMA_CHANNEL_ARB_SZ_4  	|	/* - No Arbitration.		      */
    DMA_CHANNEL_XFER_MSG	|	/* - Memory Scatter-Gather.	      */
    DMA_CHANNEL_SOFTWARE,		/* - Software Channel.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */

#if	( DMA_NOTIFICATIONS_API == STD_ON )

#ifdef	__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_29__
    /* DmaSoftwareTransferEndNotificationPtr	*/
    Dma_SoftwareTransferEndNotification_Channel_29,
#else	/* __AS_CFG_DMA_SW_XFER_END_NOTIF_CH_29__ */
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#endif	/* !__AS_CFG_DMA_SW_XFER_END_NOTIF_CH_29__ */

#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_CH_29__
    /* DmaTransferErroeNotificationPtr	*/
    Dma_TransferErrorNotification_Channel_29,
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_CH_29__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_CH_29__ */

#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */

  },
  {
    DMA_CHANNEL_SPI_0_RX,		/* DmaChannelId.		      */
    DMA_SSI_0_RX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_BYTE	|	/* - Dest. Addr. Inc. Byte: 8-bit     */
    DMA_CHANNEL_DST_SZ_BYTE 	|	/* - Dest. Data Size Byte:  8-bit.    */
    DMA_CHANNEL_SRC_INC_NONE	|	/* - Src. Addr. Inc. None.	      */
    DMA_CHANNEL_SRC_SZ_BYTE 	|	/* - Src. Data Size Byte:   8-bit.    */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_PRIO_HIGH,		/* - High Priority.		      */
    DMA_SSI_0_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_SSI_0_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_0_RX__
    SPI_0_RX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_0_RX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_0_RX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
  {
    DMA_CHANNEL_SPI_0_TX,		/* DmaChannelId.		      */
    DMA_SSI_0_TX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_NONE	|	/* - Dest. Addr. Inc. None.	      */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte: 8-bit.     */
    DMA_CHANNEL_SRC_INC_BYTE	|	/* - Src. Addr. Inc. Byte: 8-bit.     */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:  8-bit.     */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_BURST_ONLY,		/* - Burst Only.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_SSI_0_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_SSI_0_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_0_TX__
    SPI_0_TX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_0_TX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_0_TX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
{
    DMA_CHANNEL_SPI_1_RX,		/* DmaChannelId.		      */
    DMA_SSI_1_RX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_BYTE	|	/* - Dest. Addr. Inc. Byte: 8-bit     */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte:  8-bit.    */
    DMA_CHANNEL_SRC_INC_NONE	|	/* - Src. Addr. Inc. None.	      */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:   8-bit.    */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_PRIO_HIGH,		/* - High Priority.		      */
    DMA_SSI_1_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_SSI_2_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_1_RX__
    SPI_1_RX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_1_RX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_1_RX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
  {
    DMA_CHANNEL_SPI_1_TX,		/* DmaChannelId.		      */
    DMA_SSI_1_TX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_NONE	|	/* - Dest. Addr. Inc. None.	      */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte: 8-bit.     */
    DMA_CHANNEL_SRC_INC_BYTE	|	/* - Src. Addr. Inc. Byte: 8-bit.     */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:  8-bit.     */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_BURST_ONLY,		/* - Burst Only.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_SSI_1_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_SSI_1_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_1_TX__
    SPI_1_TX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_1_TX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_1_TX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
  {
    DMA_CHANNEL_SPI_2_RX,		/* DmaChannelId.		      */
    DMA_SSI_2_RX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_BYTE	|	/* - Dest. Addr. Inc. Byte: 8-bit     */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte:  8-bit.    */
    DMA_CHANNEL_SRC_INC_NONE	|	/* - Src. Addr. Inc. None.	      */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:   8-bit.    */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_PRIO_HIGH,		/* - High Priority.		      */
    DMA_SSI_2_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_SSI_2_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_2_RX__
    SPI_2_RX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_2_RX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_2_RX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
  {
    DMA_CHANNEL_SPI_2_TX,		/* DmaChannelId.		      */
    DMA_SSI_2_TX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_NONE	|	/* - Dest. Addr. Inc. None.	      */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte: 8-bit.     */
    DMA_CHANNEL_SRC_INC_BYTE	|	/* - Src. Addr. Inc. Byte: 8-bit.     */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:  8-bit.     */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_BURST_ONLY,		/* - Burst Only.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_SSI_2_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_SSI_2_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_2_TX__
    SPI_2_TX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_2_TX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_2_TX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
  {
    DMA_CHANNEL_SPI_3_RX,		/* DmaChannelId.		      */
    DMA_SSI_3_RX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_BYTE	|	/* - Dest. Addr. Inc. Byte: 8-bit     */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte:  8-bit.    */
    DMA_CHANNEL_SRC_INC_NONE	|	/* - Src. Addr. Inc. None.	      */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:   8-bit.    */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_PRIO_HIGH,		/* - High Priority.		      */
    DMA_SSI_3_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_SSI_3_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_3_RX__
    SPI_3_RX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_3_RX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_3_RX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
  {
    DMA_CHANNEL_SPI_3_TX,		/* DmaChannelId.		      */
    DMA_SSI_3_TX,			/* DmaChannelAssignemnt.	      */
    					/* DmaChannelControl:		      */
    DMA_CHANNEL_DST_INC_NONE	|	/* - Dest. Addr. Inc. None.	      */
    DMA_CHANNEL_DST_SZ_BYTE	|	/* - Dest. Data Size Byte: 8-bit.     */
    DMA_CHANNEL_SRC_INC_BYTE	|	/* - Src. Addr. Inc. Byte: 8-bit.     */
    DMA_CHANNEL_SRC_SZ_BYTE	|	/* - Src. Data Size Byte:  8-bit.     */
#if	0
    DMA_CHANNEL_ARB_SZ_4	|	/* - Arbitration Size: FIFO HALF-FULL.*/
#endif
    DMA_CHANNEL_ARB_SZ_1	|	/* - Arbitration Size: Every Transfer.*/
    DMA_CHANNEL_XFER_PSG	|	/* - Peripheral Scatter-Gather.	      */
    DMA_CHANNEL_BURST_ONLY,		/* - Burst Only.		      */
    DMA_MEMORY_ADDRESS_LOW,		/* DmaSrcAddrLow.		      */
    DMA_MEMORY_ADDRESS_HIGH,		/* DmaSrcAddrHigh.		      */
    DMA_SSI_3_ADDRESS_LOW,		/* DmaDstAddrLow.		      */
    DMA_SSI_3_ADDRESS_HIGH,		/* DmaDstAddrHigh.		      */
#if	( DMA_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,			/* DmaSoftwareTransferEndNotificationPtr      */
#ifdef	__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_3_TX__
    SPI_3_TX_DMA_XFER_ERR_NOTIF_SYM,	/* DmaTransferErrorNotificationPtr    */
#else	/* __AS_CFG_DMA_XFER_ERR_NOTIF_SPI_3_TX__ */
    NULL_PTR,				/* DmaTransferErrorNotificationPtr    */
#endif	/* !__AS_CFG_DMA_XFER_ERR_NOTIF_SPI_3_TX__ */
#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */
  },
#endif	/* ( DMA_SCATTER_GATHER_API == STD_ON ) */
};
#endif	/* __AS_CFG_DMA_SPI__ */

/*
 * This container is the base of a multiple configuration set.
 */
const Dma_ConfigType			Dma_Config[] = {
  { /* DMA_CONFIG_SW */
    DMA_SW_CHANNELS_NUMBER,		/* DmaMaxChannel.		      */
    &Dma_SwChannelConfig[0],		/* DmaChannel.			      */
  },
#ifdef	__AS_CFG_DMA_SPI__
  { /* DMA_CONFIG_SPI */
    DMA_SPI_CHANNELS_NUMBER,		/* DmaMaxChannel.		      */
    &Dma_SpiChannelConfig[0],		/* DmaChannel.			      */
  },
#endif	/* __AS_CFG_DMA_SPI__ */
};
