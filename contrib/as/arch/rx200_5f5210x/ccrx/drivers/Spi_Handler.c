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
 * Spi_Internal.c Module source file.
 *
 * AUTOSAR SPI Handler/Driver Internal Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

/*
 * Spi_Internal.c has implicit access to the Spi_Cfg.h through the Spi.h file.
 */
#include "Spi.h"
#include "Spi_Internal.h"

/* 
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
#error	Spi: version mismatch.
#endif

#include "ee.h"

/*
 * Global config
 */
Spi_GlobalType Spi_Global = {
		SPI_UNINIT,		/* DriverState		*/
		NULL_PTR,		/* ConfigPtr		*/
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
		SPI_POLLING_MODE,	/* AsyncMode		*/
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
		SPI_SYNC_ASYNC_NONE,	/* SyncTransmit		*/

		SPI_JOB_END_LIST,	/* CurrAsyncSpiJobIdx	*/
		SPI_JOB_END_LIST	/* CurrSyncSpiJobIdx	*/
#else	/* ( SPI_LEVEL_DELIVERED == 2 ) */
		SPI_JOB_END_LIST	/* CurrSpiJobIdx	*/
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */

};


/*
 * Sequence Status Array.
 */
Spi_SeqStateType	SpiSeqStatus[SPI_SEQUENCES_MAX_NUMBER];

/*
 * Hardware Unit Status Array.
 */
Spi_HwUnitStateType	SpiHwUnitStatus[SPI_MAX_HW_UNIT];

/*
 * Job Status Array.
 */
Spi_JobStateType	SpiJobStatus[SPI_JOBS_MAX_NUMBER];

/*
 * Channel Status Array.
 */
Spi_ChannelStateType	SpiChannelStatus[SPI_CHANNELS_MAX_NUMBER];


/* Transmission and receiving buffers associated with channels and jobs*/
Spi_DataType *SpiTxTable[SPI_JOBS_CHANNELS_MAX_NUMBER];
Spi_DataType *SpiRxTable[SPI_JOBS_CHANNELS_MAX_NUMBER];
Spi_NumberOfDataType TableLen[SPI_JOBS_CHANNELS_MAX_NUMBER];

/* Indexex uses to track the positon in transmission and receiving buffers.
 * Note: these indexes are "touched" by Spi_JobStart(), Spi_TxISR() and 
 * Spi_trx(). 
 * */
Spi_ChannelType TxChIdx, RxChIdx;
Spi_NumberOfDataType TxPosIdx, RxPosIdx;
Spi_ChannelType  NumAssChIdx;

/*Used to transmit the data without incrementing TxPosIdx. This is used when 
the pointer to external buffer is null. 
Ex: SpiChannelStatus[ChIdx].SpiSrcEbPtr == NULL_PTR; 
*/
boolean SpiTxNoInc = FALSE; 

/*
 * @brief SPI JOB Buffers Setup.
 *
 * @param	JobIdx		Job Index.
 * @param	AssChIdx	Channel Pointer.
 *
 * NOTES:
 * - Interrupts Disabled.
 */

static void Spi_Job_buffer_setup(Spi_JobType JobIdx, Spi_ChannelType AssChIdx)
{

	register Spi_ChannelType		ChIdx;
#if	( \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
	)
	register Spi_NumberOfDataType		IbBuffIdx;
#endif	/*
	 * (
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 * )
	 */
	for (ChIdx = 0;
	      Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelId !=
	      Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiChannelList[AssChIdx]; 
	      ChIdx++) { ; }
    
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	if ( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelType == SPI_EB ) {
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#if	( \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
	  )
	if ( SpiChannelStatus[ChIdx].SpiEbLen == 0x0000 ) {
		TableLen[AssChIdx] = Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiEbMaxLength;
		SpiChannelStatus[ChIdx].SpiSrcEb =
				Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiDefaultData;
		SpiTxTable[AssChIdx] = &SpiChannelStatus[ChIdx].SpiSrcEb;
		SpiRxTable[AssChIdx] = &SpiChannelStatus[ChIdx].SpiDstEb;
	} else {
		TableLen[AssChIdx] = SpiChannelStatus[ChIdx].SpiEbLen;
    	if ( SpiChannelStatus[ChIdx].SpiSrcEbPtr == NULL_PTR ) {
    		SpiChannelStatus[ChIdx].SpiSrcEb = 
    				Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiDefaultData;
    		SpiTxTable[AssChIdx] = &SpiChannelStatus[ChIdx].SpiSrcEb;
			SpiTxNoInc = TRUE;
    	} else {
			SpiTxNoInc = FALSE;
    		SpiTxTable[AssChIdx] = (Spi_DataType *) SpiChannelStatus[ChIdx].SpiSrcEbPtr;
    	}

    	if ( SpiChannelStatus[ChIdx].SpiDstEbPtr == NULL_PTR ) {
    		SpiRxTable[AssChIdx] = &SpiChannelStatus[ChIdx].SpiDstEb;
    	} else {
    		SpiRxTable[AssChIdx] = SpiChannelStatus[ChIdx].SpiDstEbPtr;
    	}
	}
#endif	/*
	 * (
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 *  )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	} else {
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#if	( \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || \
	  ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
	)
		TableLen[AssChIdx] = Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiIbNBuffers;
		SpiTxTable[AssChIdx] =  SpiChSrcIb[ChIdx];
		SpiRxTable[AssChIdx] =  SpiChDstIb[ChIdx];
		if ( SpiChannelStatus[ChIdx].SpiSrcIbEmpty == TRUE ) {

			for (IbBuffIdx = 0; IbBuffIdx < TableLen[AssChIdx]; IbBuffIdx++) {

				SpiChSrcIb[ChIdx][IbBuffIdx] =
						Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiDefaultData;
			}
		}
#endif	/*
	 * (
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 *   ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 * )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    }
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

}

/*
 * @brief 	Spi transmit a frame.
 * @param 	HWUnit	 Spi device
 * 
 */
void Spi_trx(Spi_HWUnitType HWUnit) 
{
	uint8 n_of_fr;
	
	if (HWUnit != SPI_HW_UNIT_13) {
		if (!SpiTxNoInc) { 
			SCI_SPI_SET_TDR(HWUnit, SpiTxTable[TxChIdx][TxPosIdx++]);
		} else {
			TxPosIdx++;
			SCI_SPI_SET_TDR(HWUnit, SpiTxTable[TxChIdx][0]);
		}
	} else {
		n_of_fr =  (RSPI_GET_SPDCR() & 0x03) + 1;
		if (!SpiTxNoInc) {
			while (n_of_fr--) 
				RSPI_SET_SPDR(SpiTxTable[TxChIdx][TxPosIdx++]);
		} else {
			while (n_of_fr--) {
				RSPI_SET_SPDR(SpiTxTable[TxChIdx][0]);
				TxPosIdx++;
			}
		}
				
	}	                  
}


/*
 * @brief 	Store a spi frame into SpiRxTable.
 * @param 	HWUnit	Spi device
 */
void Spi_store(Spi_HWUnitType HWUnit) 
{
	uint8 n_of_fr;
	
	if (HWUnit != SPI_HW_UNIT_13) {
		SpiRxTable[RxChIdx][RxPosIdx++] = SCI_SPI_GET_RDR(HWUnit);
	} else {
		n_of_fr = (RSPI_GET_SPDCR() & 0x03) + 1;
		while (n_of_fr--)
			SpiRxTable[RxChIdx][RxPosIdx++] = RSPI_GET_SPDR();
	}	                  
}

/*
 * @brief 	Spi start hw unit.
 * @param 	HWUnit	Spi device
 */
void Spi_HwEnable(Spi_HWUnitType HWUnit) 
{
	
	if (HWUnit != SPI_HW_UNIT_13) {
		SCI_SPI_EN(HWUnit);
	} else {
		RSPI_ENABLE();
	}	                  
}

/*
 * @brief 	Spi stop hw unit.
 * @param 	HWUnit	Spi device
 */
void Spi_HwDisable(Spi_HWUnitType HWUnit) 
{
	
	if (HWUnit != SPI_HW_UNIT_13) {
		SCI_SPI_DIS(HWUnit);
	} else {
		RSPI_DISABLE();
	}	                  
}

/*
 * Job Transmission Start.
 *
 * param	CallType	(A)Synchronous Call Type.
 * param	JobIdx		Job Index.
 * param	Owner		Job Owner Sequence Index.
 *
 * NOTES:
 * - Interrupts Disabled.
 * - Hardware Unit Disabled.
 */
static void Spi_JobStart(

#if	( SPI_LEVEL_DELIVERED == 2 )
  Spi_SynchronousType	CallType,
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
  Spi_JobType		JobIdx,
  Spi_SequenceType	OwnerIdx
)
{

	register const Spi_ExternalDeviceConfigType	*ExtDevCfgPtr;
	register Spi_HWUnitType	HWUnitIdx, HWUnit;
	register Spi_ChannelType AssChIdx;

	/* External Device Lookup. */
	for (HWUnitIdx = 0; (
		   Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx].SpiCsIdentifier != 
				   Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiDeviceAssignment); 
	HWUnitIdx++) { ; }
  
	ExtDevCfgPtr	= &Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx];

	/* Hardware Unit Retrieval. */
	HWUnit = ExtDevCfgPtr->SpiHwUnit;

	SpiHwUnitStatus[HWUnitIdx].SpiOwnerIdx = JobIdx;

	SpiJobStatus[JobIdx].SpiJobResult = SPI_JOB_PENDING;
	SpiJobStatus[JobIdx].SpiOwnerIdx = OwnerIdx;

#if	( SPI_LEVEL_DELIVERED == 2 )

	if ( CallType & SPI_ASYNCHRONOUS ) {

		Spi_Global.CurrAsyncJobIdx = JobIdx;  
	} else { 
		Spi_Global.CurrSyncJobIdx = JobIdx;
	}

#else	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	Spi_Global.CurrJobIdx = JobIdx;

#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
    
	
	for ( AssChIdx = 0; 
			Spi_Global.ConfigPtr->SpiJob[JobIdx].SpiChannelList[AssChIdx] != 
					SPI_CHANNEL_END_LIST; AssChIdx++) {
		Spi_Job_buffer_setup(JobIdx, AssChIdx);
	}

	if ( ExtDevCfgPtr->SpiEnableCs ) {
		Dio_WriteChannel(ExtDevCfgPtr->SpiCsChannelId, 
				ExtDevCfgPtr->SpiCsPolarity);
	}
	
	/*Reset the indexes of buffers.*/ 
	TxChIdx = RxChIdx = 0;
	TxPosIdx = RxChIdx = 0;
	/*Set the number of associated channel for current job .*/
	NumAssChIdx = AssChIdx;  
	
	ExtDevCfgPtr	= &Spi_Global.ConfigPtr->SpiExternalDevice[HWUnitIdx];

	if (HWUnit == SPI_HW_UNIT_13 && 
			Spi_Global.ConfigPtr->SpiChannel[0].SpiTransferStart == SPI_LSB) {
		RSPI_SET_LSB_SCPMD0();
	}

	Spi_HwEnable(HWUnit);
	
	Spi_trx(HWUnit);

}	/* Spi_JobStart() */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
/*
 * SPI093:	Priority order of jobs shall be from the lower to the higher
 * 		value defined, higher value higher priority (from 0, the lower
 * 		to 3, the higher, limited to 4 priority levels see [SPI009]).
 */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

/*
 * SPI Sequence Scheduling.
 *
 * param	CallType	(A)Synchronous Call Type.
 * return	Scheduled Sequence Index otherwise Configured SpiMaxSequence.
 */
static Spi_SequenceType Spi_Schedule(
#if	( SPI_LEVEL_DELIVERED == 2 )
		Spi_SynchronousType	CallType
#else
		void
#endif
)
{

	register Spi_SequenceType	SpiSeqIdx, SpiSchedSeqIdx;

#if	( SPI_LEVEL_DELIVERED == 2 )
	register Spi_HWUnitType	SpiHWUnitIdx;
#endif

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
	register uint8		SpiJobPri, SpiSchedJobPri;

	SpiSchedJobPri = 0;
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

	SpiSchedSeqIdx = Spi_Global.ConfigPtr->SpiMaxSequence;

	for (SpiSeqIdx = 0; SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence; 
		  SpiSeqIdx++) {

	  if ( SpiSeqStatus[SpiSeqIdx].SpiSeqResult == SPI_SEQ_PENDING ) {

#if	( SPI_LEVEL_DELIVERED == 2 )
      /* External Device Look-up. */
		  for (
			   SpiHWUnitIdx = 0; 
			  (Spi_Global.ConfigPtr->SpiExternalDevice[SpiHWUnitIdx].SpiCsIdentifier != 
					  Spi_Global.ConfigPtr->SpiJob[
		              SpiSeqStatus[SpiSeqIdx].SpiCurrJobIdx].SpiDeviceAssignment
		              ); SpiHWUnitIdx++) { ; }

		  if (Spi_Global.ConfigPtr->SpiExternalDevice[SpiHWUnitIdx
		                                    ].SpiHwUnitSynchronous & CallType) {
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
			  SpiJobPri =	Spi_Global.ConfigPtr->SpiJob[SpiSeqStatus[SpiSeqIdx
			             	                ].SpiCurrJobIdx].SpiJobPriority + 1;
			  if ( SpiJobPri > SpiSchedJobPri ) {
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

				  SpiSchedSeqIdx = SpiSeqIdx;

#if	( \
  ( SPI_LEVEL_DELIVERED == 0 ) || ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_OFF ) \
)

				  SpiSeqIdx = Spi_Global.ConfigPtr->SpiMaxSequence;

#else	/* 
	 * (
	 *    ( SPI_LEVEL_DELIVER == 0 ) ||
	 *    ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_OFF )
	 *  )
	 */

				  SpiSchedJobPri = SpiJobPri;

#endif	/* 
	 * !(
	 *    ( SPI_LEVEL_DELIVER == 0 ) ||
	 *    ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_OFF )
	 *  )
	 */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
			  }	/* if ( SpiJobPri < SchedJobPri ) */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
      
#if	( SPI_LEVEL_DELIVERED == 2 )
		  }	/*
	 * (
	 *   Spi_Global.ConfigPtr->SpiExternalDevice[
	 *	SpiHWUnitIdx
	 *   ].SpiHwUnitSynchronous & CallType
	 *  )
	 */
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	  }	/* if ( SPI_SEQ_PENDING ) */
  
	}	/* for ( SpiSeqIdx ) */

  return SpiSchedSeqIdx;

}	/* Spi_Schedule() */


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
)
{

	register EE_FREG		flags;
	register Spi_JobType		SpiJob;
	register Spi_JobType		SpiOldJobIdx, SpiNewJobIdx;
	register Spi_SequenceType	SpiOldSeqIdx, SpiNewSeqIdx;

	flags = EE_hal_suspendIRQ();

#if	( SPI_LEVEL_DELIVERED == 2 )

	if (CallType & SPI_ASYNCHRONOUS) {

		SpiOldJobIdx = Spi_Global.CurrAsyncJobIdx;
  
	} else {

		SpiOldJobIdx = Spi_Global.CurrSyncJobIdx;
	}

#else	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	SpiOldJobIdx = Spi_Global.CurrJobIdx;

#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	if ( SpiOldJobIdx == SPI_JOB_END_LIST ) {

		SpiOldSeqIdx = SPI_SEQ_END_LIST;

		/* Scheduler */
		SpiNewSeqIdx = Spi_Schedule(
#if	( SPI_LEVEL_DELIVERED == 2 )
				CallType
#endif
		);

		SpiNewJobIdx = SpiSeqStatus[SpiNewSeqIdx].SpiCurrJobIdx;

	} else {

		SpiOldSeqIdx = SpiJobStatus[SpiOldJobIdx].SpiOwnerIdx;

		if ( SpiJobStatus[SpiOldJobIdx].SpiJobResult != SPI_JOB_PENDING ) {

			SpiJobStatus[SpiOldJobIdx].SpiOwnerIdx = SPI_SEQ_END_LIST;

#if	( SPI_LEVEL_DELIVERED == 2 )

			if ( CallType & SPI_ASYNCHRONOUS ) {

				Spi_Global.CurrAsyncJobIdx = SPI_JOB_END_LIST;
  
			} else {

				Spi_Global.CurrSyncJobIdx = SPI_JOB_END_LIST;
			}

#else	/* ( SPI_LEVEL_DELIVERED == 2 ) */

			Spi_Global.CurrJobIdx = SPI_JOB_END_LIST;

#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

			if ( SpiJobStatus[SpiOldJobIdx].SpiJobResult == SPI_JOB_FAILED ) {

				SpiSeqStatus[SpiOldSeqIdx].SpiCurrJobIdx = SPI_JOB_END_LIST;

#if	( SPI_CANCEL_API == STD_ON )
				if ( SpiSeqStatus[SpiOldSeqIdx].SpiSeqResult != 
						SPI_SEQ_CANCELED ) {
#endif	/* ( SPI_CANCEL_API == STD_ON ) */

					SpiSeqStatus[SpiOldSeqIdx].SpiSeqResult = SPI_SEQ_FAILED;

#if	( SPI_CANCEL_API == STD_ON )
				}
#endif	/* ( SPI_CANCEL_API == STD_ON ) */

				SpiJob = SPI_JOB_END_LIST;

			}	/* SPI_JOB_FAILED */ 
			else { /* SPI_JOB_OK */

				/* Job Assignemnt Look-up. */
				SpiJob = Spi_Global.ConfigPtr->SpiJob[SpiOldJobIdx].SpiJobId;

				for (SpiNewJobIdx = 0; ( Spi_Global.ConfigPtr->SpiSequence[
				                 SpiOldSeqIdx].SpiJobAssignment[SpiNewJobIdx] !=
				                		 SpiJob); SpiNewJobIdx++) { ; }

				/* Next Job in Job Assignment */
				SpiNewJobIdx++;

				SpiJob = Spi_Global.ConfigPtr->SpiSequence[
				                   SpiOldSeqIdx].SpiJobAssignment[SpiNewJobIdx];

				if ( SpiJob == SPI_JOB_END_LIST ) {	/* Sequence Ended. */

					SpiSeqStatus[SpiOldSeqIdx].SpiCurrJobIdx = SPI_JOB_END_LIST;

#if	( SPI_CANCEL_API == STD_ON )
					if ( SpiSeqStatus[SpiOldSeqIdx].SpiSeqResult != 
							SPI_SEQ_CANCELED ) {
#endif	/* ( SPI_CANCEL_API == STD_ON ) */

						SpiSeqStatus[SpiOldSeqIdx].SpiSeqResult = SPI_SEQ_OK;

#if	( SPI_CANCEL_API == STD_ON )
	  }
#endif	/* ( SPI_CANCEL_API == STD_ON ) */

				}

			}	/* SPI_JOB_OK */

			if ( SpiJob == SPI_JOB_END_LIST ) {	/* Sequence Ended. */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
				SpiNewSeqIdx = Spi_Schedule(
#if	( SPI_LEVEL_DELIVERED == 2 )
						CallType
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
				);

				if ( SpiNewSeqIdx != Spi_Global.ConfigPtr->SpiMaxSequence ) {

					SpiNewJobIdx = SpiSeqStatus[SpiNewSeqIdx].SpiCurrJobIdx;

				} else {
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

					SpiNewSeqIdx = SPI_SEQ_END_LIST;
					SpiNewJobIdx = SPI_JOB_END_LIST;

#if	( SPI_LEVEL_DELIVERED == 2 )
					if ( ( CallType | Spi_Global.TransmitMode ) & 
							SPI_SYNC_ASYNC ) {

						Spi_Global.TransmitMode &= ~CallType;
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
						Spi_Global.DriverState = SPI_IDLE;
#if	( SPI_LEVEL_DELIVERED == 2 )
					}/*( CallType | Spi_Global.TransmitMode ) & SPI_SYNC_ASYNC*/
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
					}
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

			}	/* Sequence Ended. */
			else {	/* Sequence Not End. */

				/* Job Look-up. */
				for (SpiNewJobIdx = 0;
						( Spi_Global.ConfigPtr->SpiJob[SpiNewJobIdx].SpiJobId != 
								SpiJob ); SpiNewJobIdx++) { ; }

				SpiSeqStatus[SpiOldSeqIdx].SpiCurrJobIdx = SpiNewJobIdx;

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
				if ( Spi_Global.ConfigPtr->SpiSequence[
				                       SpiOldSeqIdx].SpiInterruptibleSequence) {
					SpiNewSeqIdx = Spi_Schedule(
#if	( SPI_LEVEL_DELIVERED == 2 )
							CallType
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
					);
				} else {
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

					SpiNewSeqIdx = SpiOldSeqIdx;

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
				}
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

				SpiNewJobIdx = SpiSeqStatus[SpiNewSeqIdx].SpiCurrJobIdx;
			}	/* Sequence Not Ended. */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )

#if	( SPI_LEVEL_DELIVERED == 2 )
			if ( CallType & SPI_ASYNCHRONOUS ) {
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

				if ((SpiJobStatus[SpiOldJobIdx].SpiJobResult != 
						SPI_SEQ_PENDING ) && 
						( Spi_Global.ConfigPtr->SpiJob[
								         SpiOldJobIdx].SpiJobEndNotification !=
								        		 NULL_PTR)) {
					EE_hal_resumeIRQ(flags);

					(*Spi_Global.ConfigPtr->SpiJob[
					                     SpiOldJobIdx].SpiJobEndNotification)();

					flags = EE_hal_suspendIRQ();
				}

				if (( SpiSeqStatus[SpiOldSeqIdx].SpiSeqResult != 
						SPI_SEQ_PENDING ) && (Spi_Global.ConfigPtr->SpiSequence[
						                 SpiOldSeqIdx].SpiSeqEndNotification != 
						                		 NULL_PTR)) {

					EE_hal_resumeIRQ(flags);

					(*Spi_Global.ConfigPtr->SpiSequence[
					                     SpiOldSeqIdx].SpiSeqEndNotification)();

					flags = EE_hal_suspendIRQ();
				}
  
#if	( SPI_LEVEL_DELIVERED == 2 )
			}
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

		} else {	/* SPI_JOB_PENDING */
  
			SpiNewJobIdx = SPI_JOB_END_LIST;
			SpiNewSeqIdx = SPI_SEQ_END_LIST;
		}
	}	/* !SPI_JOB_END_LIST */

	if (( SpiNewJobIdx != SPI_JOB_END_LIST ) && 
			( SpiNewSeqIdx != SPI_SEQ_END_LIST )) {

		/* Job Start */
		Spi_JobStart(
#if	( SPI_LEVEL_DELIVERED == 2 )
				CallType,
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
				SpiNewJobIdx, 
				SpiNewSeqIdx);
	}

	EE_hal_resumeIRQ(flags);

}	/* Spi_MainFunction_Internal_Handling() */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
/*
 * Spi_MainFunction_Handling implementation.
 */
void Spi_MainFunction_Handling(void)
{

	register EE_UREG flags;
	register Spi_StatusType	state;
	register Spi_AsyncModeType	mode;

	flags = EE_hal_suspendIRQ();
	state = Spi_Global.DriverState;
	mode = Spi_Global.AsyncMode;
	
	EE_hal_resumeIRQ(flags);

	if ( ( state == SPI_BUSY ) && ( mode == SPI_POLLING_MODE ) ) {
		Spi_MainFunction_Internal_Handling(
#if	( SPI_LEVEL_DELIVERED == 2 )
				SPI_ASYNCHRONOUS
#endif
		);
	}

}
#endif


