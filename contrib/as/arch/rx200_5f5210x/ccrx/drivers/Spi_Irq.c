/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * SPI372:	Spi_Irq.c File for implementation of interrupt service routine
 * 		(BSW00314)
 *
 * AUTOSAR SPI Handler/Driver Channels ISRs Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

/*
 * SPI276:	Spi_Irq.c file could exist depending upon implementation and
 * 		also it could or not include Spi.h.
 */
#include "Spi.h"
#include "Spi_Internal.h"


/* 
 * SPI069:	Spi_Irq.c shall check if the correct version of Spi.h is included.
 * 		This shall be done by a pre-processor check.
 *
 * SPI369:	The SPI module shall avoid the integration of incompatible files
 * 		by the following pre-processor checks:
 * 		for included (external) header files,
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		shall be verified.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	SPI_AR_RELEASE_MAJOR_VERSION	4
#define	SPI_AR_RELEASE_MINOR_VERSION	0

#if !defined( SPI_AR_MAJOR_VERSION ) || \
    ( SPI_AR_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION )
#error	Spi_Irq: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"


/* Transmission and receiving buffers associated with channels and jobs*/
extern Spi_DataType *SpiTxTable[SPI_JOBS_CHANNELS_MAX_NUMBER];
extern Spi_DataType *SpiRxTable[SPI_JOBS_CHANNELS_MAX_NUMBER];
extern Spi_NumberOfDataType TableLen[SPI_JOBS_CHANNELS_MAX_NUMBER];

/* Indexex uses to track the positon in transmission and receiving buffers.
 * Note: these indexes are "touched" by Spi_JobStart(), Spi_TxISR() and 
 * Spi_trx(). 
 * */
extern Spi_ChannelType TxChIdx, RxChIdx;
extern Spi_NumberOfDataType TxPosIdx, RxPosIdx;
extern Spi_ChannelType  NumAssChIdx;
extern boolean SpiTxNoInc;


#if ( defined(EE_RX200_SCI0_ERI0_ISR) || defined(EE_RX200_SCI1_ERI1_ISR) || \
		defined(EE_RX200_SCI5_ERI5_ISR) || defined(EE_RX200_SCI6_ERI6_ISR) || \
		defined(EE_RX200_SCI8_ERI8_ISR) || defined(EE_RX200_SCI9_ERI9_ISR) || \
		defined(EE_RX200_SCI9_ERI12_ISR) || defined(EE_RX200_RSPI0_SPEI0_ISR) )
/*
 * @brief 	SPI Receiveng Error ISR.
 * @param	HWUint	SPI Hardware Unit who fired Interrupt.
 */
void Spi_RxErrISR(Spi_HWUnitType HWUnit)
{
	register EE_FREG flags;
	register Spi_HWUnitType	HWUnitIdx;
	register boolean rx_err;

	flags = EE_hal_suspendIRQ();

	if (HWUnit != SPI_HW_UNIT_13) {
		rx_err = SCI_GET_RX_ERR_FLAGS(HWUnit);
		SCI_RX_ERR_CLR(HWUnit);
	} else {
		rx_err = RSPI_GET_RX_ERR_FLAGS();
		RSPI_CLR_RX_ERR_FLAGS();
	}

	/* External Device Look-up. */
	for (HWUnitIdx = 0; 
			( Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx].SpiHwUnit != 
					HWUnit ); HWUnitIdx++) { ; }

	EE_hal_resumeIRQ(flags);

	if (rx_err) {
		Spi_JobEnd(HWUnit, SPI_JOB_FAILED);
	}
	
}


#endif


#if ( defined(EE_RX200_SCI0_RXI0_ISR) || defined(EE_RX200_SCI1_RXI1_ISR) || \
		defined(EE_RX200_SCI5_RXI5_ISR) || defined(EE_RX200_SCI6_RXI6_ISR) || \
		defined(EE_RX200_SCI8_RXI8_ISR) || defined(EE_RX200_SCI9_RXI9_ISR) || \
		defined(EE_RX200_SCI12_RXI12_ISR) || defined(EE_RX200_RSPI0_SPRI0_ISR))

/*
 * @brief 	SPI RX buffer full ISR.
 * @param	HWUint	SPI Hardware Unit who fired Interrupt.
 */
void Spi_RxISR(Spi_HWUnitType HWUnit)
{
	if (RxChIdx < NumAssChIdx) {
		Spi_store(HWUnit); 
	}
	/* If the end of the channel rx buffer has been reached, go to the next
	 * channel in the list
	 * */
	if (RxPosIdx >= TableLen[RxChIdx]) {
		RxPosIdx = 0;
		RxChIdx++;
	}

	/*	If the received character has been got by Spi_RxISR() then transmit the 
		next one, if any.
	*/
	if ((TxPosIdx == RxPosIdx) && (TxChIdx == RxChIdx)) {
		/* If the end of the channel list has not been reached, transmit the
		* next character of current channel, else call the end job funciton if also the
		* transmission buffer is full.
		* */
		if (TxChIdx < NumAssChIdx) {
				Spi_trx(HWUnit); 
		} else {
			Spi_JobEnd(HWUnit, SPI_JOB_OK);
		}
	}

}


#endif

#if ( defined(EE_RX200_SCI0_TXI0_ISR) || defined(EE_RX200_SCI1_TXI1_ISR) || \
		defined(EE_RX200_SCI5_TXI5_ISR) || defined(EE_RX200_SCI6_TXI6_ISR) || \
		defined(EE_RX200_SCI8_TXI8_ISR) || defined(EE_RX200_SCI9_TXI9_ISR) || \
		defined(EE_RX200_SCI12_TXI12_ISR) || defined(EE_RX200_RSPI0_SPTI0_ISR) )
/*
 * @brief 	SPI TX buffer empty ISR.
 * @param	HWUint	SPI Hardware Unit who fired Interrupt.
 */
void Spi_TxISR(Spi_HWUnitType HWUnit)
{
	/* If the end of the channel tx buffer has been reached, go to the next
	 * channel in the list
	 * */
	if (TxPosIdx >= TableLen[TxChIdx]) {
		TxPosIdx = 0;
		TxChIdx++;
		if (HWUnit == SPI_HW_UNIT_13 && 
				Spi_Global.ConfigPtr->SpiChannel[TxChIdx].SpiTransferStart == 
						SPI_LSB) {
			RSPI_SET_LSB_SCPMD0();
		}
	}
	
	/*	If the received character has been got by Spi_RxISR() then transmit the 
		next one, if any.
	*/
	if ((TxPosIdx == RxPosIdx) && (TxChIdx == RxChIdx)) {
		/* If the end of the channel list has not been reached, transmit the
		* next datum of current channel, else call the end job routine if also the
		* receiving buffer is full.
		* */
		if (TxChIdx < NumAssChIdx) {
			Spi_trx(HWUnit); 
		} else {
			Spi_JobEnd(HWUnit, SPI_JOB_OK);
		}
	}
	
}


/*
 * @brief Job End.
 *
 * @param	HWUnit		SPI Hardware Unit on which Error Occurred.
 * @param	JobResult	SPI Job Result.
 */
void Spi_JobEnd(Spi_HWUnitType	HWUnit, Spi_JobResultType	JobResult)
{

	register EE_UREG flags;
	register Spi_HWUnitType HWUnitIdx;
	register Spi_JobType JobIdx;
	register Spi_ChannelType AssChNum, ChIdx;
	register const Spi_ExternalDeviceConfigType *ExtDevCfgPtr;

	flags = EE_hal_suspendIRQ();
	
	Spi_HwDisable(HWUnit);
	SpiTxNoInc = FALSE;

	/* External Device Look-up. */
	for (HWUnitIdx = 0;
			( Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx].SpiHwUnit != 
					HWUnit ); HWUnitIdx++) { ; }

	ExtDevCfgPtr = &Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx];

	if (ExtDevCfgPtr->SpiEnableCs) {
		Dio_WriteChannel(
				ExtDevCfgPtr->SpiCsChannelId, !ExtDevCfgPtr->SpiCsPolarity);
	}

	JobIdx = SpiHwUnitStatus[HWUnitIdx].SpiOwnerIdx;

	/* This prevents possible problems if Spi_JobEnd() is called when a job is 
	 * already ended.
	 */
	if (SpiHwUnitStatus[HWUnitIdx].SpiOwnerIdx == SPI_JOB_END_LIST) {
		
		EE_hal_resumeIRQ(flags);
		
		return;
	}

	
	SpiHwUnitStatus[HWUnitIdx].SpiOwnerIdx = SPI_JOB_END_LIST;

	SpiJobStatus[JobIdx].SpiJobResult = JobResult;
	

	
	for (AssChNum = 0; 
			Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiChannelList[AssChNum] != 
					SPI_CHANNEL_END_LIST; AssChNum++) {
		for (ChIdx = 0; (Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelId !=
				Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiChannelList[AssChNum]); 
		ChIdx++) { ; }
		

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
		if ( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelType == SPI_EB ){
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#if	( \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
	)
			SpiChannelStatus[ChIdx].SpiEbLen = 0x0000U;
			SpiChannelStatus[ChIdx].SpiSrcEbPtr = NULL_PTR;
			SpiChannelStatus[ChIdx].SpiDstEbPtr = NULL_PTR;
#endif	/*
	 * (
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 *    ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 *  )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
		} else {
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || \
		( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ))
			SpiChannelStatus[ChIdx].SpiSrcIbEmpty = TRUE;

			if (JobResult == SPI_JOB_OK) {
				SpiChannelStatus[ChIdx].SpiDstIbEmpty = FALSE;
			}
#endif	/*
	 * (
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 *    ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 *  )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
		}
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

	}

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
	if ( 
#if	( SPI_LEVEL_DELIVERED == 2 )
			( ExtDevCfgPtr->SpiHwUnitSynchronous & SPI_ASYNCHRONOUS ) &&
#endif
			( Spi_Global.AsyncMode == SPI_INTERRUPT_MODE )
	) {

		EE_hal_resumeIRQ(flags);

		Spi_MainFunction_Internal_Handling(
#if	( SPI_LEVEL_DELIVERED == 2 )
				SPI_ASYNCHRONOUS
#endif
		);

		flags = EE_hal_suspendIRQ();

	}
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

	EE_hal_resumeIRQ(flags);

}
#endif	/*
	 * EE_RX200_SCI0_ERI0_ISR || EE_RX200_SCI1_ERI1_ISR || EE_RX200_SCI5_ERI5_ISR || 
	 * EE_RX200_SCI6_ERI6_ISR) || EE_RX200_SCI8_ERI8_ISR || EE_RX200_SCI9_ERI9_ISR || 
	 * EE_RX200_SCI12_ERI12_ISR || EE_RX200_SCI0_TXI0_ISR || EE_RX200_SCI1_TXI1_ISR || 
	 * EE_RX200_SCI5_TXI5_ISR || EE_RX200_SCI6_TXI6_ISR || EE_RX200_SCI8_TXI8_ISR || 
	 * EE_RX200_SCI9_TXI9_ISR || EE_RX200_SCI12_TXI12_ISR || EE_RX200_RSPI0_SPTI0_ISR
	 */



#ifdef	EE_RX200_SCI0_ERI0_ISR
#pragma interrupt (EE_RX200_SCI0_ERI0_ISR)
ISR2(EE_RX200_SCI0_ERI0_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_0); 
	while (EE_HWREG8(HW_ICU_IR_SCI0_ERX) == 1);
}
#endif

#ifdef	EE_RX200_SCI0_RXI0_ISR
#pragma interrupt (EE_RX200_SCI0_RXI0_ISR)
ISR2(EE_RX200_SCI0_RXI0_ISR) { Spi_RxISR(SPI_HW_UNIT_0); }
#endif

#ifdef	EE_RX200_SCI0_TXI0_ISR
#pragma interrupt (EE_RX200_SCI0_TXI0_ISR)
ISR2(EE_RX200_SCI0_TXI0_ISR) { Spi_TxISR(SPI_HW_UNIT_0); }
#endif


#ifdef	EE_RX200_SCI1_ERI1_ISR
#pragma interrupt (EE_RX200_SCI1_ERI1_ISR)
ISR2(EE_RX200_SCI1_ERI1_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_1); 
	while (EE_HWREG8(HW_ICU_IR_SCI1_ERX));
}
#endif

#ifdef	EE_RX200_SCI1_RXI1_ISR
#pragma interrupt (EE_RX200_SCI1_RXI1_ISR)
ISR2(EE_RX200_SCI1_RXI1_ISR) { Spi_RxISR(SPI_HW_UNIT_1); }
#endif

#ifdef	EE_RX200_SCI1_TXI1_ISR
#pragma interrupt (EE_RX200_SCI1_TXI1_ISR)
ISR2(EE_RX200_SCI1_TXI1_ISR) { Spi_TxISR(SPI_HW_UNIT_1); }
#endif

#ifdef	EE_RX200_SCI5_ERI5_ISR
#pragma interrupt (EE_RX200_SCI5_ERI5_ISR)
ISR2(EE_RX200_SCI5_ERI5_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_5); 
	while (EE_HWREG8(HW_ICU_IR_SCI5_ERX));
}
#endif

#ifdef	EE_RX200_SCI5_RXI5_ISR
#pragma interrupt (EE_RX200_SCI5_RXI5_ISR)
ISR2(EE_RX200_SCI5_RXI5_ISR) { Spi_RxISR(SPI_HW_UNIT_5); }
#endif

#ifdef	EE_RX200_SCI5_TXI5_ISR
#pragma interrupt (EE_RX200_SCI5_TXI5_ISR)
ISR2(EE_RX200_SCI5_TXI5_ISR) { Spi_TxISR(SPI_HW_UNIT_5); }
#endif

#ifdef	EE_RX200_SCI6_ERI6_ISR
#pragma interrupt (EE_RX200_SCI6_ERI6_ISR)
ISR2(EE_RX200_SCI6_ERI6_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_6); 
	while (EE_HWREG8(HW_ICU_IR_SCI6_ERX));	
}
#endif

#ifdef	EE_RX200_SCI6_RXI6_ISR
#pragma interrupt (EE_RX200_SCI6_RXI6_ISR)
ISR2(EE_RX200_SCI6_RXI6_ISR) { Spi_RxISR(SPI_HW_UNIT_6); }
#endif

#ifdef	EE_RX200_SCI6_TXI6_ISR
#pragma interrupt (EE_RX200_SCI6_TXI6_ISR)
ISR2(EE_RX200_SCI6_TXI6_ISR) { Spi_TxISR(SPI_HW_UNIT_6); }
#endif

#ifdef	EE_RX200_SCI8_ERI8_ISR
#pragma interrupt (EE_RX200_SCI8_ERI8_ISR)
ISR2(EE_RX200_SCI8_ERI8_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_8); 
	while (EE_HWREG8(HW_ICU_IR_SCI8_ERX));	
}
#endif

#ifdef	EE_RX200_SCI8_RXI8_ISR
#pragma interrupt (EE_RX200_SCI8_RXI8_ISR)
ISR2(EE_RX200_SCI8_RXI8_ISR) { Spi_RxISR(SPI_HW_UNIT_8); }
#endif

#ifdef	EE_RX200_SCI8_TXI8_ISR
#pragma interrupt (EE_RX200_SCI8_TXI8_ISR)
ISR2(EE_RX200_SCI8_TXI8_ISR) { Spi_TxISR(SPI_HW_UNIT_8); }
#endif

#ifdef	EE_RX200_SCI9_ERI9_ISR
#pragma interrupt (EE_RX200_SCI9_ERI9_ISR)
ISR2(EE_RX200_SCI9_ERI9_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_9); 
	while (EE_HWREG8(HW_ICU_IR_SCI9_ERX));	
}
#endif

#ifdef	EE_RX200_SCI9_RXI9_ISR
#pragma interrupt (EE_RX200_SCI9_RXI9_ISR)
ISR2(EE_RX200_SCI9_RXI9_ISR) { Spi_RxISR(SPI_HW_UNIT_9); }
#endif

#ifdef	EE_RX200_SCI9_TXI9_ISR
#pragma interrupt (EE_RX200_SCI9_TXI9_ISR)
ISR2(EE_RX200_SCI9_TXI9_ISR) { Spi_TxISR(SPI_HW_UNIT_9); }
#endif

#ifdef	EE_RX200_SCI12_ERI12_ISR
#pragma interrupt (EE_RX200_SCI12_ERI12_ISR)
ISR2(EE_RX200_SCI12_ERI12_ISR)
{ 
	Spi_RxErrISR(SPI_HW_UNIT_12); 
	while (EE_HWREG8(HW_ICU_IR_SCI12_ERX));	
}
#endif

#ifdef	EE_RX200_SCI12_RXI12_ISR
#pragma interrupt (EE_RX200_RXI12_ISR)
ISR2(EE_RX200_SCI12_RXI12_ISR) { Spi_RxISR(SPI_HW_UNIT_12); }
#endif

#ifdef	EE_RX200_SCI12_TXI12_ISR
#pragma interrupt (EE_RX200_SCI12_TXI12_ISR)
ISR2(EE_RX200_SCI12_TXI12_ISR) { Spi_TxISR(SPI_HW_UNIT_12); }
#endif

#ifdef	EE_RX200_RSPI0_SPEI0_ISR
#pragma interrupt (EE_RX200_RSPI0_SPEI0_ISR)
ISR2(EE_RX200_RSPI0_SPEI0_ISR) 
{ 
	Spi_RxErrISR(SPI_HW_UNIT_13); 
	while (EE_HWREG8(HW_ICU_IER_RSPI_SPEI) == 1);
}
#endif

#ifdef	EE_RX200_RSPI0_SPRI0_ISR
#pragma interrupt (EE_RX200_RSPI0_SPRI0_ISR)
ISR2(EE_RX200_RSPI0_SPRI0_ISR) { Spi_RxISR(SPI_HW_UNIT_13); }
#endif

#ifdef	EE_RX200_RSPI0_SPTI0_ISR
#pragma interrupt (EE_RX200_RSPI0_SPTI0_ISR)
ISR2(EE_RX200_RSPI0_SPTI0_ISR) { Spi_TxISR(SPI_HW_UNIT_13); }
#endif
