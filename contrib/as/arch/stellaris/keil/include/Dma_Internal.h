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

/** @file	Dma_Internal.h
 *  @brief	AUTOSAR-"like" DMA Driver Internal Header File.
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#ifndef	DMA_INTERNAL_H
#define	DMA_INTERNAL_H

#include "Hardware.h"

/*
 * MACRO Definitions
 */

#define	DMA_CH_MASK		0x0000001FU	/**< Channel Mask.	      */

#define	DMA_CH_BASE_FLAG_MASK	0x00000001U	/**< Channel Base Flag Mask.  */

/** @brief	DMA Channel Mapping Base Mask.	*/
#define	DMA_CH_BASE_MAP_MASK	0x0000000FU

/** @brief	DMA Channel Mapping Mask Shift Bits Shift Bits.	*/
#define	DMA_CH_MAP_S_S		0x00000002U

/** @brief	DMA Channel Mapping Register Base Address.	*/
#define	DMA_CH_MAP_REG_BAS_ADDR	0x400FF510U

/** @brief	DMA Channel Mapping Register Base Mask.		*/
#define	DMA_CH_MAP_REG_MASK	0x00000007U

/** @brief	DMA Channel Mapping Register Shift Bits.	*/
#define	DMA_CH_MAP_REG_S	0x00000003U

/** @brief	uDMA Channel Control Destination Increment Filed Shift Bits.  */
#define	UDMA_CHCTL_DSTINC_S	0x0000001EU

/** @brief	uDMA Channel Control Destination Size Field Shift Bits.	      */
#define	UDMA_CHCTL_DSTSIZE_S	0x0000001CU

/** @brief	uDMA Channel Control Source Increment Filed Shift Bits.	      */
#define	UDMA_CHCTL_SRCINC_S	0x0000001AU

/** @brief	uDMA Channel Control Source Size Field Shift Bits.	      */
#define	UDMA_CHCTL_SRCSIZE_S	0x00000018U

/** @brief	DMA Channel Canceled Control Word Value.		      */
#define	DMA_CH_CTRL_CANC	0xFFFFFFFFU

/** @brief	DMA Max Size of Transfer Elements.			      */
#define	DMA_MAX_TRANSFER_SIZE	0x00000400U

/** @brief	DMA Max Number of Supported Channels.			      */
#define	DMA_CHANNELS_MAX_NUMBER	0x00000020U

#if	( DMA_SCATTER_GATHER_API == STD_ON )

/** @brief	DMA Channel Alternate Scatter-Gather Mode Mask.		      */
#define	DMA_CH_SG_ALT_MASK	0x00000001U

/** @brief	DMA Channel Scatter-Gather Size Shift Buts.		      */
#define	DMA_CH_SG_SIZE_S	0x00000002U

#endif	/* ( DMA_SCATTER_GATHER_API == STD_ON ) */

/*
 * MACRO Utils
 */

/*
 * DMA Channel Base Flag Mask Shift Bits Number Retrieval.
 *
 * param	_ch	DMA Channel to address.
 * return	Number of Bits to shift in a DMA Channel Base Flag Mask.
 */
#define	DMA_CH_S(_ch)	(uint32) ( \
	(uint32)(_ch) & (uint32)DMA_CH_MASK \
)

/*
 * DMA Channel Flag Mask Retrieval.
 *
 * param	_ch	DMA Channel to address.
 * return	DMA Channel Flag Mask.
 */
#define	DMA_CH_2_FLAG(_ch)	(uint32)( \
	(uint32)DMA_CH_BASE_FLAG_MASK << DMA_CH_S(_ch) \
)

/*
 * DMA Register Channel Flag Clear.
 *
 * param	_reg	DMA Register Address.
 * param	_ch	DMA Channel to address.
 */
#define	DMA_REG_FLAG_CLR(_reg, _ch)	(_reg) &= ~DMA_CH_2_FLAG(_ch)

/*
 * DMA Register Channel Flag Set.
 *
 * param	_reg	DMA Register Address.
 * param	_ch	DMA Channel to address.
 */
#define	DMA_REG_FLAG_SET(_reg, _ch)	(_reg) |= DMA_CH_2_FLAG(_ch)

/*
 * DMA Register Channel Flag Write.
 *
 * param	_reg	DMA Register Address.
 * param	_ch	DMA Channel to address.
 */
#define	DMA_REG_FLAG_WRITE(_reg, _ch)	(_reg) = DMA_CH_2_FLAG(_ch)

/*
 * DMA Register Channel Flag Status Retrieval.
 *
 * param	_reg	DMA Register Address.
 * param	_ch	DMA Channel to address.
 * return	DMA Register Channel Flag Status.
 */
#define	DMA_REG_FLAG_STAT(_reg, _ch)	(uint32)( \
	((_reg) & DMA_CH_2_FLAG(_ch)) >> DMA_CH_S(_ch) \
)

/*
 * DMA Channel Mapping Mask Retrieval.
 *
 * param	_ch	DMA Channel to addess.
 * param	_map	DMA Channel Mapping.
 * return	DMA Channel Mapping Mask.
 */
#define	DMA_CH_2_MAP(_ch,_map)	(uint32)( \
	(uint32)((uint32)(_map) & (uint32)DMA_CH_BASE_MAP_MASK) << \
	(uint32)( \
		((uint32)(_ch) & (uint32)DMA_CH_MAP_REG_MASK) << \
		(uint32)DMA_CH_MAP_S_S \
	) \
)

/*
 * DMA Channel Mapping Register Retrieval.
 *
 * param	_ch	DMA Channel to addess.
 * return	DMA Channel Mapping Register.
 */
#define	DMA_CH_MAP_REG(_ch)	EE_HWREG( \
	(uint32)DMA_CH_MAP_REG_BAS_ADDR + \
	( \
	  (uint32)((uint32)(_ch) >> (uint32)DMA_CH_MAP_REG_S) << \
	  (uint32)DMA_CH_MAP_S_S \
	) \
)

/*
 * DMA Error Clear.
 */
#define	DMA_ERR_CLR()			( UDMA_ERRCLR_R = UDMA_ERRCLR_ERRCLR )

/*
 * DMA Error Get.
 */
#define	DMA_ERR_GET()			( UDMA_ERRCLR_R & UDMA_ERRCLR_ERRCLR )

/*
 * DMA Channel Interrupt Clear.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_INT_CLR(_ch)		DMA_REG_FLAG_SET(UDMA_CHIS_R, _ch)

/*
 * DMA Channel Interrupt Status Retieval.
 *
 * param	_ch	DMA Channel to addess.
 * return	DMA Channel Interrupt Status.
 */
#define	DMA_INT_STAT(_ch)		DMA_REG_FLAG_STAT(UDMA_CHIS_R, _ch)

/*
 * DMA Channel Enable.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_ENABLE(_ch)		DMA_REG_FLAG_SET(UDMA_ENASET_R, _ch)

/*
 * DMA Channel Enable Status Retieval.
 *
 * param	_ch	DMA Channel to addess.
 * return	DMA Channel Enable Status.
 */
#define	DMA_CHANNEL_STAT(_ch)		DMA_REG_FLAG_STAT(UDMA_ENASET_R, _ch)

/*
 * DMA Channel Disable.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_DISABLE(_ch)	DMA_REG_FLAG_SET(UDMA_ENACLR_R, _ch)

/*
 * DMA Channel Transfer Request.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_REQUEST(_ch)	DMA_REG_FLAG_WRITE(UDMA_SWREQ_R, _ch)

/*
 * DMA Channel Mapping Clear.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_MAP_CLR(_ch)	( \
	DMA_CH_MAP_REG(_ch) &= ~DMA_CH_2_MAP(_ch, DMA_CH_BASE_MAP_MASK) \
)

/*
 * DMA Channel Mapping Set.
 *
 * param	_ch	DMA Channel to addess.
 * param	_map	DMA Channel Mapping.
 */
#define	DMA_CHANNEL_MAP_SET(_ch,_map)	( \
	DMA_CH_MAP_REG(_ch) |= DMA_CH_2_MAP(_ch, _map) \
)

/*
 * DMA Channel Priority Attribute Clear.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_PRIO_CLR(_ch)	DMA_REG_FLAG_SET(UDMA_PRIOCLR_R, _ch)

/*
 * DMA Channel Priority Attribute Set.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_PRIO_SET(_ch)	DMA_REG_FLAG_SET(UDMA_PRIOSET_R, _ch)

/*
 * DMA Channel Burst-Only Attribute Clear.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_BURST_ONLY_CLR(_ch)	\
	DMA_REG_FLAG_SET(UDMA_USEBURSTCLR_R, _ch)

/*
 * DMA Channel Burst-Only Attribute Set.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_BURST_ONLY_SET(_ch)	\
	DMA_REG_FLAG_SET(UDMA_USEBURSTSET_R, _ch)

/*
 * DMA Channel Software Attribute Clear.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_SOFTWARE_CLR(_ch)	\
	DMA_REG_FLAG_SET(UDMA_REQMASKCLR_R, _ch)

/*
 * DMA Channel Software Attribute Set.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_SOFTWARE_SET(_ch)	\
	DMA_REG_FLAG_SET(UDMA_REQMASKSET_R, _ch)

/*
 * DMA Channel Primary Alternate Clear.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_PRIALT_CLR(_ch)	\
	DMA_REG_FLAG_SET(UDMA_ALTCLR_R, _ch)

/*
 * DMA Channel Primary Alternate Set.
 *
 * param	_ch	DMA Channel to addess.
 */
#define	DMA_CHANNEL_PRIALT_SET(_ch)	\
	DMA_REG_FLAG_SET(UDMA_ALTSET_R, _ch)

/*
 * Type that holds all global data for Dma Driver
 */
typedef struct
{
  boolean			Init;		/* DMA Driver Initialized     */
  const Dma_ConfigType *	ConfigPtr;	/* Actual Configuration	      */
} Dma_GlobalType;

/*
 * Global config
 */
extern Dma_GlobalType	Dma_Global;

/*
 * The control table used by the uDMA controller.
 *
 * NOTE:	This table must be aligned to a 1024 byte boundary.
 */
extern	Dma_EntryType	DmaControlTable[DMA_CHANNELS_MAX_NUMBER << 1]
			__attribute__ ((aligned(1024)));

#endif	/* DMA_INTERNAL_H */
