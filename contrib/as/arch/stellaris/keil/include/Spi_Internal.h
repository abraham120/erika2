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

/** @file	Spi_Internal.h
 *  @brief	AUTOSAR SPI Handler/Driver Internal Header File.
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#ifndef	SPI_INTERNAL_H
#define	SPI_INTERNAL_H

/* Development error macros. */
#if ( SPI_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* SPI_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#endif	/* !SPI_DEV_ERROR_DETECT */

/* SPI Hardware Module Mask */
#define	HW_CH_MOD_MASK		0x00000003U

/* SSI Hardware Base Address */
#define	HW_BASE_ADDR		&SSI0_CR0_R

/* Hardware Abstraction */
#include "Hardware.h"

/*
 * SSI Harware Register Offsets
 */
#define	SSI_CR0_R_OFFSET	0x00000000U	/* Control 0		      */
#define	SSI_CR1_R_OFFSET	0x00000004U	/* Control 1		      */
#define	SSI_DR_R_OFFSET		0x00000008U	/* Data			      */
#define	SSI_SR_R_OFFSET		0x0000000CU	/* Status		      */
#define	SSI_CPSR_R_OFFSET	0x00000010U	/* Clock Prescale	      */
#define	SSI_IM_R_OFFSET		0x00000014U	/* Interrupt Mask	      */
#define	SSI_RIS_R_OFFSET	0x00000018U	/* Raw Interrupt Status	      */
#define	SSI_MIS_R_OFFSET	0x0000001CU	/* Masked Interrupt Status    */
#define	SSI_IC_R_OFFSET		0x00000020U	/* Interrupt Clear	      */
#define	SSI_DMACTL_R_OFFSET	0x00000024U	/* DMA Control		      */
#define	SSI_CC_R_OFFSET		0x00000028U	/* Clock Configuration	      */

/*
 * SSI Hardware Interrupt Sources
 */
#define	SSI_INT_TX	0x00000008U	/* Trasmit FIFO.	*/
#define	SSI_INT_RX	0x00000004U	/* Receive FIFO.	*/
#define	SSI_INT_RT	0x00000002U	/* Receive Time-Out.	*/
#define	SSI_INT_ROR	0x00000001U	/* Receive Overrun.	*/
#define	SSI_INT_RX_ERR	( SSI_INT_RT | SSI_INT_ROR )
#define	SSI_INT_ALL	( SSI_INT_TX | SSI_INT_RX | SSI_INT_RX_ERR )

/*
 * SSI Hardware Unit Status.
 */
#define	SSI_STAT_BSY	0x00000010	/* Busy.		*/
#define	SSI_STAT_RFF	0x00000008	/* Rx FIFO Full.	*/
#define	SSI_STAT_RNE	0x00000004	/* Rx FIFO Not Empty.	*/
#define	SSI_STAT_TNF	0x00000002	/* Tx FIFO Not Full.	*/
#define	SSI_STAT_TFE	0x00000001	/* Tx FIFO Empty.	*/

/*
 * SSI Hardware DMA Enable.
 */
#define SSI_DMA_TX	0x00000002	/* Transmit DMA Enable	*/
#define SSI_DMA_RX	0x00000001	/* Receive DMA Enable	*/

/*
 * MACRO Utils
 */

/* Hardware Unit Registers Read/Write */
#define	SSI_REG(_ch,_ofs)	HW_CH_2_MOD_REG(_ch,_ofs)

#define	SSI_REG_SET(_ch,_ofs,_val)	(SSI_REG(_ch,_ofs) = (uint32)_val)

#define	SSI_REG_AND(_ch,_ofs,_val)	(SSI_REG(_ch,_ofs) & (uint32)_val)

#define	SSI_REG_OR(_ch,_ofs,_val)	(SSI_REG(_ch,_ofs) | (uint32)_val)

#define	SSI_REG_AND_SET(_ch,_ofs,_val)	(SSI_REG(_ch,_ofs) &= (uint32)_val)

#define	SSI_REG_OR_SET(_ch,_ofs,_val)	(SSI_REG(_ch,_ofs) |= (uint32)_val)

/*
 * Tx DMA Enable.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_TX_DMA_ENABLE(_hu)	\
	SSI_REG_OR_SET(_hu, SSI_DMACTL_R_OFFSET, SSI_DMA_TX)

/*
 * Rx DMA Enable.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_RX_DMA_ENABLE(_hu)	\
	SSI_REG_OR_SET(_hu, SSI_DMACTL_R_OFFSET, SSI_DMA_RX)

/*
 * Hardware Unit Enable.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_ENABLE(_hu)	SSI_REG_OR_SET(_hu, SSI_CR1_R_OFFSET, SSI_CR1_SSE)

/*
 * Hardware Unit is Enabled.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_IS_ENABLED(_hu)	SSI_REG_AND(_hu, SSI_CR1_R_OFFSET, SSI_CR1_SSE)

/*
 * Hardware Unit Disable.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_DISABLE(_hu)	\
	SSI_REG_AND_SET(_hu, SSI_CR1_R_OFFSET, ~((uint32)SSI_CR1_SSE))

#define	SSI_SET_DS(_hu,_ds)	\
	SSI_REG_AND_SET(_hu, SSI_CR0_R_OFFSET, ~((uint32)SSI_CR0_DSS_M)); \
	SSI_REG_OR_SET( \
	  _hu, \
	  SSI_CR0_R_OFFSET, \
	  (uint32)((uint32)_ds & (uint32)SSI_CR0_DSS_M) \
	)

#define	SSI_SET_CR0(_hu, _cr0)	SSI_REG_SET(_hu, SSI_CR0_R_OFFSET, _cr0)

#define	SSI_GET_CR1(_hu)	SSI_REG(_hu, SSI_CR1_R_OFFSET)
#define	SSI_SET_CR1(_hu, _cr1)	SSI_REG_SET(_hu, SSI_CR1_R_OFFSET, _cr1)

#define	SSI_SET_PIOSC(_hu)	\
	SSI_REG_SET(_hu, SSI_CC_R_OFFSET, SSI_CC_CS_PIOSC)

#define	SSI_SET_CPSR(_hu, _cpsr)	\
	SSI_REG_SET(_hu, SSI_CPSR_R_OFFSET, _cpsr)

/*
 * Hardware Unit FIFO Address.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_FIFO_ADDR(_hu)	HW_CH_2_MOD_REG_ADDR(_hu, SSI_DR_R_OFFSET)

/*
 * Hardware Unit Tx FIFO push.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 * param	_data	Data to push.
 */
#define	SSI_FIFO_TX(_hu, _data)	\
	SSI_REG_SET(_hu, SSI_DR_R_OFFSET, _data)

/*
 * Hardware Unit Rx FIFO pop.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_FIFO_RX(_hu)	\
	SSI_REG(_hu, SSI_DR_R_OFFSET)

/*
 * Hardware Unit Status Retrieval.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_GET_SR(_hu)		SSI_REG(_hu, SSI_SR_R_OFFSET)

/*
 * Raw Interrupt Status Retrieval.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_GET_RIS(_hu)	SSI_REG(_hu, SSI_RIS_R_OFFSET)

/*
 * Masked Interrupt Status Retrieval.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_GET_MIS(_hu)	SSI_REG(_hu, SSI_MIS_R_OFFSET)

/*
 * Interrupt Clear
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 * param	_srcs	SSI Hardware Interrupt Sources.
 */
#define	SSI_INT_CLR(_hu, _srcs)	SSI_REG_OR_SET(_hu, SSI_IC_R_OFFSET, _srcs)

/*
 * Interrupt Enable
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 * param	_srcs	SSI Hardware Interrupt Sources.
 */
#define	SSI_INT_EN(_hu, _srcs)	SSI_REG_OR_SET(_hu, SSI_IM_R_OFFSET, _srcs)

/*
 * Interrupt Disable
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 * param	_srcs	SSI Hardware Interrupt Sources.
 */
#define	SSI_INT_DIS(_hu, _srcs)	\
	SSI_REG_AND_SET(_hu, SSI_IM_R_OFFSET, ~((uint32)_srcs))

/*
 * Interrupt Mask Retrieval.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 */
#define	SSI_GET_INT_MASK(_hu)	SSI_REG(_hu, SSI_IM_R_OFFSET)

/*
 * Interrupt Mask Set-up.
 *
 * param	_hu	Numeric ID of a SPI Hardware Unit. (Spi_HWUnitType)
 * param	_mask	Interrupt Mask to Set-up.
 */
#define	SSI_SET_INT_MASK(_hu,_mask)	SSI_REG_SET(_hu, SSI_IM_R_OFFSET, _mask)

#endif	/* SPI_INTERNAL_H */

/*
 * Type that holds all global data for Spi Driver
 */
typedef struct
{
  Spi_StatusType		DriverState;	/* SPI Handler/Driver State   */

  const Spi_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
  Spi_AsyncModeType		AsyncMode;	/* Asynchronous Mode.	      */
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
  Spi_SynchronousType		TransmitMode;	/* Transmission Mode.	      */
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
  /* Current Asynchronous Job Index. */
  Spi_JobType			CurrAsyncJobIdx;
  /* Current Synchronous Job Index.  */
  Spi_JobType			CurrSyncJobIdx;
#else	/* ( SPI_LEVEL_DELIVERED == 2 ) */
  Spi_JobType			CurrJobIdx;	/* Current Job Index.         */
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */

}	Spi_GlobalType;

/*
 * Global config
 */
extern	Spi_GlobalType Spi_Global;

#include "Mcu.h"

/*
 * MCU Global Configuration Reference
 */
typedef struct
{
  boolean			Init;		/* MCU Driver Initialized?    */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting	      */

}	Mcu_GlobalType;

/*
 * MCU Global Configuration External Reference
 */
extern Mcu_GlobalType Mcu_Global;

/*
 * Channel State.
 */
typedef struct {

#if	( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
  Spi_NumberOfDataType	SpiEbLen;	/* External Buffers Elements Number.  */
  const Spi_DataType *	SpiSrcEbPtr;	/* Source External Buffer Pointer.    */
  Spi_DataType *	SpiDstEbPtr;  /* Destination External Buffer Pointer. */

  /* Dummy Buffers to be used when User don't call Spi_SetupEB(). */
  Spi_DataType		SpiSrcEb;	/* Fake Source External Buffer.	      */
  Spi_DataType		SpiDstEb;	/* Fake Destination External Buffer.  */
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
  boolean	SpiSrcIbEmpty;	/* Source Internal Buffer Empty Flag.	      */
  boolean	SpiDstIbEmpty;	/* Destination Internal Buffer Empty Flag.    */
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

}	Spi_ChannelStateType;

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/* Internal Buffers moved in Spi_Cfg.c */
extern	Spi_DataType *	SpiChSrcIb[];	/* Source Internal Buffer.	      */
extern	Spi_DataType *	SpiChDstIb[];	/* Destination Internal Buffer.	      */
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

/*
 * Channel Status Array.
 */
extern Spi_ChannelStateType	SpiChannelStatus[SPI_CHANNELS_MAX_NUMBER];

/*
 * Hardware Unit State.
 */
typedef struct {

  Spi_JobType		SpiOwnerIdx;	/* Hardware Unit Owner Job Index.     */

}	Spi_HwUnitStateType;

/*
 * Hardware Unit Status Array.
 */
extern Spi_HwUnitStateType	SpiHwUnitStatus[SPI_MAX_HW_UNIT];

/*
 * Job State.
 */
typedef	struct {

  Spi_SequenceType	SpiOwnerIdx;	/* Job Owner Sequence Index.	      */
  Spi_JobResultType	SpiJobResult;	/* Job Result.			      */

}	Spi_JobStateType;

/*
 * Job Status Array.
 */
extern Spi_JobStateType		SpiJobStatus[SPI_JOBS_MAX_NUMBER];

/*
 * Sequence State.
 */
typedef	struct {
  Spi_JobType		SpiCurrJobIdx;	/* Current Job Index.		      */
  Spi_SeqResultType	SpiSeqResult;	/* Sequence Result.		      */
}	Spi_SeqStateType;

/*
 * Sequence Status Array.
 */
extern Spi_SeqStateType		SpiSeqStatus[SPI_SEQUENCES_MAX_NUMBER];

/*
 * Current Job Index Setup.
 *
 * param	CallType	(A)Synchronous Call Type.
 * return	SpiJobIdx		Job Index to Setup.
 */
void Spi_SetCurrSpiJobIdx(
#if	( SPI_LEVEL_DELIVERED == 2 )
  Spi_SynchronousType	CallType,
#endif
  Spi_JobType		SpiJobIdx
);

/*
 * Main Function Internal Handling.
 *
 * param	CallType	(A)Synchronous Call Type.
 */
void Spi_MainFunction_Internal_Handling(
#if	( SPI_LEVEL_DELIVERED == 2 )
  Spi_SynchronousType	CallType
#else
  void
#endif
);
