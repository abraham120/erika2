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
 * Spi.c Module source file.
 *
 * AUTOSAR SPI Handler/Driver Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

/*
 * SPI092:	The SPI module shall adhere to the following include file
 * 		structure: Spi.c shall include Spi.h, MemMap.h, Det.h and
 * 		SchM_Spi.h.
 *
 * Comment: Spi.c has implicit access to the Spi_Cfg.h through the Spi.h file.
 */
#include "Spi.h"

/* 
 * SPI069:	Spi.c shall check if the correct version of Spi.h is included.
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
#error	Spi: version mismatch.
#endif

#include "ee.h"

#include "Spi_Internal.h"


/*
 * SCI Harware Unit Baudrate Parameters Computing.
 *
 * param	baudrate	Desired Baudrate.
 * param	clock		Source Clock.
 * param	SpiHwUnit	SCI hardware unit.
 */
static void Sci_SetHWUnitBRParms(float32 baudrate, float32 clock, 
		Spi_HWUnitType	SpiHwUnit)
{
	uint8 i; 
	uint16 N;
	
	
	clock = clock / SCR_GET_PCKB_DIV(
			Mcu_Global.ConfigPtr->McuClockSettingConfig[
			        Mcu_Global.ClockSetting].McuRunModeClockConfiguration2);
	

	/*We could use the assert(exp) macros.*/
	VALIDATE( ( ( baudrate >= clock / 8192.0) && ( baudrate <= clock / 4.0)   ), 
			SPI_INIT_SERVICE_ID, SPI_E_WRONG_BAUDRATE );	
	
	for (i = 4; i > 0; i--) {
		
		N = (uint8) ( clock / (baudrate * (1 << (2 * (i-1) + 2))) );
	
		if (N > 0 && N < 256) {
			SCI_SET_CLOCK_DIV(SpiHwUnit, i-1);
			SCI_SET_BAUDRATE(SpiHwUnit, N - 1);
			break; 
		}		
	}
		
}

/*
 * RSPI Harware Unit Baudrate Parameters Computing.
 *
 * param	baudrate	Desired Baudrate.
 * param	clock		Source Clock.
 */
static void Rspi_SetHWUnitBRParms(float32 baudrate, float32 clock)
{
	uint8 N; 
	uint16 n;
	
	clock = clock / SCR_GET_PCKB_DIV(
			Mcu_Global.ConfigPtr->McuClockSettingConfig[
			        Mcu_Global.ClockSetting].McuRunModeClockConfiguration2);

	/*We could use the assert(exp) macros.*/
	VALIDATE( ( ( baudrate >= clock / 4096.0) && ( baudrate <= clock / 2.0)   ), 
			SPI_INIT_SERVICE_ID, SPI_E_WRONG_BAUDRATE );	
	
	for (N = 4; N > 0; N--) {
		
		n = (uint8) ( clock / (baudrate * (1 << (N+1))) );
	
		if (n > 0 && n < 256) {
			RSPI_SET_CLOCK_DIV(N);
			RSPI_SET_SPBR(n - 1);
			break; 
		}		
	}
}


/*
 * Spi Hardware Unit Initialization.
 *
 * param	ConfigPtr	SPI External Device Configuration Pointer.
 *
 */
static void Spi_InitSpiHWUnit(const Spi_ExternalDeviceConfigType *ConfigPtr)
{
	/* Enables Sci Module in Run-Mode. */
	Spi_EnableChannel(ConfigPtr->SpiHwUnit);
	
	/*Which module is selected? SCI or RSPI?*/
	if (ConfigPtr->SpiHwUnit != SPI_HW_UNIT_13) {
		/* Unit reset. */
		SCI_RESET(ConfigPtr->SpiHwUnit);
		/*Set SCI module in simple SPI mode.*/
		SCI_SET_SIMPLE_SPI(ConfigPtr->SpiHwUnit);
		/*Set Baudrate */
		Sci_SetHWUnitBRParms(ConfigPtr->SpiBaudrate,
				Mcu_Global.ConfigPtr->McuClockSettingConfig[
		               Mcu_Global.ClockSetting].McuClockReferencePointFrequency,
		               ConfigPtr->SpiHwUnit);

		/* Configure the working settings: Master/Slave, Chip Select etc.*/
		SCI_SET_SPMR(ConfigPtr->SpiHwUnit, ConfigPtr->SpiHwUnitMode, 
				ConfigPtr->SpiEnableCs, ConfigPtr->SpiCsPolarity);
		
		/* Set CLK out if Master, CLK input otherwise. Select peripheral clock 
		 * as internal or external.
		 */
		SCI_SET_SCR(ConfigPtr->SpiHwUnit, (ConfigPtr->SpiHwUnitMode & 
										SPI_MASTER_SLAVE_MODE_MASK & 
										SPI_CLOCK_SEL_MODE_MASK) );

	} else {

		/* NOTES:
		 * - The RSPI Sequence Control Register (SPSCR) is left to its default
		 * configuration. Control Sequence 0->0->0-> ... 
		 * 
		 */
		
		RSPI_RESET();
		
		/* Configure the RSPI module */
		RSPI_SET_SSLP(ConfigPtr->SpiCsPolarity, ConfigPtr->SpiCsIdentifier);
		RSPI_SET_SPPCR(ConfigPtr->SpiHwUnitMode);
		RSPI_SET_SPDCR(ConfigPtr->SpiHwUnitMode);
		RSPI_SET_SPCKD(ConfigPtr->SpiHwUnitMode);
		RSPI_SET_SSLND(ConfigPtr->SpiTimeClk2Cs);
		RSPI_SET_SPND(ConfigPtr->SpiHwUnitMode);
		RSPI_SET_SPCR2(ConfigPtr->SpiHwUnitMode);
		RSPI_SET_SPCMD0(
				ConfigPtr->SpiShiftClockIdleLevel, 
				ConfigPtr->SpiCsIdentifier,
				ConfigPtr->SpiHwUnitMode);
		
		/* Set Baudrate */
		Rspi_SetHWUnitBRParms(ConfigPtr->SpiBaudrate, 
				Mcu_Global.ConfigPtr->McuClockSettingConfig[
				      Mcu_Global.ClockSetting].McuClockReferencePointFrequency);
		RSPI_SET_SPCR(RSPI_SET_MODE_BITS(ConfigPtr->SpiHwUnitMode, 
						ConfigPtr->SpiEnableCs));
	}
	
}

/*
 * Spi_Init implementation. (Non Re-entrant)
 */
void Spi_Init(const Spi_ConfigType *ConfigPtr)
{

	register EE_FREG	flags;
	register uint32	idx;

	VALIDATE( ( ConfigPtr != NULL ), SPI_INIT_SERVICE_ID, SPI_E_PARAM_POINTER );
	
	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(( Spi_Global.DriverState == SPI_UNINIT ), 
					SPI_INIT_SERVICE_ID,
					SPI_E_ALREADY_INITIALIZED,
					flags);

	Spi_Global.DriverState = SPI_IDLE;
	Spi_Global.ConfigPtr = ConfigPtr;

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
	Spi_Global.AsyncMode = SPI_POLLING_MODE;
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
	Spi_Global.TransmitMode = SPI_SYNC_ASYNC_NONE;
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
	Spi_Global.CurrAsyncJobIdx = SPI_JOB_END_LIST;
	Spi_Global.CurrSyncJobIdx = SPI_JOB_END_LIST;
#else
	Spi_Global.CurrJobIdx = SPI_JOB_END_LIST;
#endif

	for ( idx = 0; idx < ConfigPtr->SpiMaxExternalDevice; idx++ ) {
		Spi_InitSpiHWUnit(&ConfigPtr->SpiExternalDevice[idx]);
	}

	/*
	 * Hardware Units Status Initialization.
	 */
	for ( idx = 0; idx < SPI_MAX_HW_UNIT; idx++ ) {
		SpiHwUnitStatus[idx].SpiOwnerIdx = SPI_JOB_END_LIST;
	}

	/*
	 * Sequences Status Initialization.
	 */
	for ( idx = 0; idx < ConfigPtr->SpiMaxSequence; idx++ ) {
		SpiSeqStatus[idx].SpiCurrJobIdx = SPI_JOB_END_LIST;
		SpiSeqStatus[idx].SpiSeqResult = SPI_SEQ_OK;
	}

	/*
	 * Jobs Status Intialization.
	 */
	for ( idx = 0; idx < ConfigPtr->SpiMaxJob; idx++ ) {
		SpiJobStatus[idx].SpiOwnerIdx = SPI_SEQ_END_LIST;
		SpiJobStatus[idx].SpiJobResult = SPI_JOB_OK;
	}

	/*
	 * Channels Status Intialization.
	 */
	for ( idx = 0; idx < ConfigPtr->SpiMaxChannel; idx++ ) {

#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||\
		( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) )
		
		SpiChannelStatus[idx].SpiEbLen = 0x0000U;
		SpiChannelStatus[idx].SpiSrcEbPtr = NULL_PTR;
		SpiChannelStatus[idx].SpiDstEbPtr = NULL_PTR;

		/* Dummy Buffers to be used when User don't call Spi_SetupEB(). */
		SpiChannelStatus[idx].SpiSrcEb = 0x00000000U;
		SpiChannelStatus[idx].SpiDstEb = 0x00000000U;
	
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||\
		( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) )
		
		SpiChannelStatus[idx].SpiSrcIbEmpty = TRUE;
		SpiChannelStatus[idx].SpiDstIbEmpty = TRUE;

#endif	/* 
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
 	 */
	}

	EE_hal_resumeIRQ(flags);

}

/*
 * Spi Hardware Unit De-Initialization.
 *
 * param	SpiHwUnit	SPI Harware Unit Identifier.
 */
static void Spi_DeInitSpiHWUnit(Spi_HWUnitType	SpiHwUnit)
{
	
	  /* Enable Sci Module in Run-Mode */
	if ( !Spi_IsChannelEnabled(SpiHwUnit) ) {
		/* Enable Spi Module in Run-Mode */
		Spi_EnableChannel(SpiHwUnit);
	}

	/*Which module is selected? SCI or RSPI?*/
	if (SpiHwUnit != SPI_HW_UNIT_13) {
		/* Unit reset. */
		SCI_RESET(SpiHwUnit);
	} else {
		RSPI_RESET();	
	}
	
	/* Stop Spi Module */
	Spi_DisableChannel(SpiHwUnit);
}

/*
 * Spi_DeInit implementation. (Non Re-entrant)
 */
Std_ReturnType Spi_DeInit(void)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;
	register Spi_HWUnitType	HwUnit;


	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV( ( Spi_Global.DriverState != SPI_UNINIT ),
						SPI_DEINIT_SERVICE_ID, 
						SPI_E_UNINIT,
						E_NOT_OK,
						flags);

	/* SPI Handler/Driver Idle Check */
	if ( Spi_Global.DriverState == SPI_BUSY ) {

		rv = E_NOT_OK;

	} else {

		/* De-Initialization Command Accepted. */
		for (HwUnit = 0; 
				HwUnit < Spi_Global.ConfigPtr->SpiMaxExternalDevice; HwUnit++) {

			Spi_DeInitSpiHWUnit(
					Spi_Global.ConfigPtr->SpiExternalDevice[HwUnit].SpiHwUnit);
		}

		Spi_Global.DriverState = SPI_UNINIT;
		Spi_Global.ConfigPtr = NULL_PTR;

		rv = E_OK;

	}

	EE_hal_resumeIRQ(flags);

	return rv;

}

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == 0) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2))
/*
 * Spi_WriteIB implementation. (Reentrant)
 */
Std_ReturnType Spi_WriteIB(Spi_ChannelType	Channel, 
							const Spi_DataType *DataBufferPtr)
{

	register EE_FREG flags;
	register Spi_ChannelType ChIdx;
	register Spi_NumberOfDataType IbBuffIdx;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Spi_Global.DriverState != SPI_UNINIT ),
						SPI_WRITEIB_SERVICE_ID, 
						SPI_E_UNINIT, 
						E_NOT_OK, 
						flags);

	for (ChIdx = 0;
		( (ChIdx < Spi_Global.ConfigPtr->SpiMaxChannel) &&
		(Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelId != Channel) );
		ChIdx++) { ; }

	VALIDATE_IRQ_W_RV( (ChIdx < Spi_Global.ConfigPtr->SpiMaxChannel), 
						SPI_WRITEIB_SERVICE_ID, 
						SPI_E_PARAM_CHANNEL, 
						E_NOT_OK, 
						flags);

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	
	VALIDATE_IRQ_W_RV(
			( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelType == SPI_IB ),
			SPI_WRITEIB_SERVICE_ID,
			SPI_E_PARAM_CHANNEL,
			E_NOT_OK,
			flags);
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

	if (DataBufferPtr != NULL_PTR) {
		for (IbBuffIdx = 0; 
			IbBuffIdx < Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiIbNBuffers; 
			IbBuffIdx++) {
			SpiChSrcIb[ChIdx][IbBuffIdx] = DataBufferPtr[IbBuffIdx];
		}
		
		SpiChannelStatus[ChIdx].SpiSrcIbEmpty = FALSE;
	}

	EE_hal_resumeIRQ(flags);

	return E_OK;
}

#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	( SPI_LEVEL_DELIVERED == 2 )
/*
 * Validate Sequence according to Synchronous or Asynchronous trasmission mode.
 *
 * param	SeqIdx		Spi Sequence Index to Check.
 * param	CallType	(A)Synchronous Call Type.
 * return	TRUE		Sequence Valid.
 * 		FALSE		Sequence Not Valid.
 */
static boolean Spi_SeqSyncAsyncValidate(Spi_SequenceType	SeqIdx, 
										Spi_SynchronousType	CallType)
{

	register const Spi_SequenceConfigType *SpiSeqCfgPtr;
	register Spi_JobType job, SpiJobIdx;
	register const Spi_JobConfigType *SpiJobCfgPtr;
	register Spi_ChannelType ch, SpiChIdx; 
	register boolean rv = TRUE;

	/* Sequence Check. */
	SpiSeqCfgPtr = &Spi_Global.ConfigPtr->SpiSequence[SeqIdx];

	for (SpiJobIdx = 0, job = SpiSeqCfgPtr->SpiJobAssignment[SpiJobIdx];
			( ( job != SPI_JOB_END_LIST ) && rv ); 
			SpiJobIdx++, job = SpiSeqCfgPtr->SpiJobAssignment[SpiJobIdx]) {

		/* Job Check. */
		SpiJobCfgPtr = &Spi_Global.ConfigPtr->SpiJob[job];

		/* External Device Check. */
		if (Spi_Global.ConfigPtr->SpiExternalDevice[
		    SpiJobCfgPtr->SpiDeviceAssignment].SpiHwUnitSynchronous != 
		    		CallType) {
			rv = FALSE;
		} else {
    
			for (SpiChIdx = 0, ch = SpiJobCfgPtr->SpiChannelList[SpiChIdx];
					(( ch != SPI_CHANNEL_END_LIST ) && rv );
					SpiChIdx++, ch = SpiJobCfgPtr->SpiChannelList[SpiChIdx]) {

				/* Channel Check. */
				if (!(Spi_Global.ConfigPtr->SpiChannel[ch].SpiHwUnitSynchronous 
						& CallType)) {
					rv = FALSE;
				}
			}

		}	/* for ( ch ) */
	}	/* for ( job ) */

	return rv;
}
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

#if	(( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ))
/*
 * Checks if a Sequence can be accepted according other on-going sequences.
 *
 * param	SeqIdx	Spi Sequence Index to Check.
 * return:
 * 	- SPI_SEQ_OK:		Sequence Accepted and no others pending.
 * 	- SPI_SEQ_PENDING:	Sequence Accepted and others pending.
 * 	- SPI_SEQ_FAILED:	Sequence Not Accepted.
 */
static Spi_SeqResultType Spi_SeqAccept(Spi_SequenceType	SeqIdx)
{
	register Spi_SequenceType	si;
	register Spi_SeqResultType	rv;
#if	( (SPI_LEVEL_DELIVERED == 2) || ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON) )
	register const Spi_JobType	*ja;
	register Spi_JobType		ji;
#endif	/*
	 * (
	 *    ( SPI_LEVEL_DELIVERED == 2 ) ||
	 *    ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
	 * )
	 */
#if	( SPI_LEVEL_DELIVERED == 2 )
	register Spi_HWUnitType	hwui;
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
	register Spi_JobType		JobIdx;
	register const Spi_JobType	*JobAssgmt;

	JobAssgmt = Spi_Global.ConfigPtr->SpiSequence[SeqIdx].SpiJobAssignment;
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */

	for (si = 0, rv = SPI_SEQ_OK; 
		(( si < Spi_Global.ConfigPtr->SpiMaxSequence ) &&
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
		( rv != SPI_SEQ_FAILED ) );
#else	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
		( rv != SPI_SEQ_PENDING ) );
#endif	/* !( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
		si++) {
#if	( (SPI_LEVEL_DELIVERED == 2) || (SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON) )
		ja = Spi_Global.ConfigPtr->SpiSequence[si].SpiJobAssignment;
#endif	/*
	 * (
	 *    ( SPI_LEVEL_DELIVERED == 2 ) ||
	 *    ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
	 * )
	 */

#if	( SPI_LEVEL_DELIVERED == 2 )
		/* First Job Look-up */
		for (ji = 0; 
				( Spi_Global.ConfigPtr->SpiJob[ji].SpiJobId != ja[0] ); ji++) {
			;
		}

		/* External Device Lookup */
		for (hwui = 0; ( 
			Spi_Global.ConfigPtr->SpiExternalDevice[hwui].SpiCsIdentifier !=
			Spi_Global.ConfigPtr->SpiJob[ji].SpiDeviceAssignment); hwui++) {
			;
		}
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

		if (
#if	( SPI_LEVEL_DELIVERED == 2 )
			(
			Spi_Global.ConfigPtr->SpiExternalDevice[hwui].SpiHwUnitSynchronous &
			SPI_ASYNCHRONOUS
			) &&
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
			( SpiSeqStatus[si].SpiSeqResult == SPI_SEQ_PENDING ) ) {

			rv = SPI_SEQ_PENDING;

#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
			for (JobIdx = 0; ( JobAssgmt[JobIdx] != SPI_JOB_END_LIST ) && 
			( rv == SPI_SEQ_PENDING ); JobIdx++) {

				for (ji = 0; ( ja[ji] != SPI_JOB_END_LIST ) && 
				( rv == SPI_SEQ_PENDING ); ji++) {

					if ( JobAssgmt[JobIdx] == ja[ji] ) {
						rv = SPI_SEQ_FAILED;
					}

				}	/* for ( j ) */

			}	/* for ( Job ) */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */

		}	/* SPI_SEQ_PENDING */

	}	/* for ( si ) */

	return rv;

}

/*
 * Spi_AsyncTransmit implementation.
 */
Std_ReturnType Spi_AsyncTransmit(Spi_SequenceType	Sequence)
{

	register EE_FREG		flags;
	register Spi_SequenceType	SpiSeqIdx;
	register Spi_JobType		SpiJobIdx, SpiJob;
	register Spi_SeqResultType	SpiSeqRes;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV( ( Spi_Global.DriverState != SPI_UNINIT ), 
			SPI_ASYNCTRANSMIT_SERVICE_ID,
			SPI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (SpiSeqIdx = 0; 
		(( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ) && 
		(Spi_Global.ConfigPtr->SpiSequence[SpiSeqIdx].SpiSequenceId != Sequence)
		); SpiSeqIdx++) { ; }

	VALIDATE_IRQ_W_RV( ( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ),
						SPI_ASYNCTRANSMIT_SERVICE_ID,
						SPI_E_PARAM_SEQ,
						E_NOT_OK,
						flags);

#if	( SPI_LEVEL_DELIVERED == 2 )
  /*
   * SPI108:	The LEVEL 2 SPI Handler/Driver is specified for microcontrollers
   * 		that have to provide, at least, two SPI busses using separated
   * 		hardware units. Otherwise, using this level of functionality
   * 		does not make sense.
   */
	VALIDATE_IRQ_W_RV(Spi_SeqSyncAsyncValidate(SpiSeqIdx, SPI_ASYNCHRONOUS),
						SPI_ASYNCTRANSMIT_SERVICE_ID,
						SPI_E_PARAM_SEQ, 
						E_NOT_OK, 
						flags);
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

  /* SPI081 and SPI266 Check. */
	VALIDATE_IRQ_W_RV( (SpiSeqStatus[SpiSeqIdx].SpiSeqResult != SPI_SEQ_PENDING),
						SPI_ASYNCTRANSMIT_SERVICE_ID,
						SPI_E_SEQ_PENDING,
						E_NOT_OK,
						flags);

  /* This monolithic SPI Handler/Driver is able to handle one to n SPI busses
   * according to the microcontroller used. But SPI busses are assigned to
   * Jobs and not to Sequences.
   * Consequently, Jobs on different SPI buses could belong to the same
   * Sequence. Therefore:
   *
   * SPI116:	The LEVEL 1 and LEVEL 2 SPI Handler/Driver may allow
   * 		transmitting more than one Sequence at the same time. That means
   * 		during a Sequence transmission, all requests to transmit another
   * 		Sequence shall be evaluated in order to accept to start a new
   * 		sequence or to reject it accordingly to the lead Job.
   */
	SpiSeqRes = Spi_SeqAccept(SpiSeqIdx);

	/* SPI086 Check. */
	VALIDATE_IRQ_W_RV(
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
					( SpiSeqRes != SPI_SEQ_FAILED ),
#else	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    /* NOTE:	No more then 1 Sequence at the time. */
					( SpiSeqRes != SPI_SEQ_PENDING ),
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
					SPI_ASYNCTRANSMIT_SERVICE_ID,
					SPI_E_SEQ_PENDING,
					E_NOT_OK,
					flags);

	Spi_Global.DriverState = SPI_BUSY;

#if	( SPI_LEVEL_DELIVERED == 2 )
	Spi_Global.TransmitMode |= SPI_ASYNCHRONOUS;
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	SpiSeqStatus[SpiSeqIdx].SpiSeqResult = SPI_SEQ_PENDING;

	SpiJob = Spi_Global.ConfigPtr->SpiSequence[SpiSeqIdx].SpiJobAssignment[0];

	for (SpiJobIdx = 0; 
		( Spi_Global.ConfigPtr->SpiJob[SpiJobIdx].SpiJobId != SpiJob ); 
		SpiJobIdx++) { ; }
  
	SpiSeqStatus[SpiSeqIdx].SpiCurrJobIdx = SpiJobIdx;

	EE_hal_resumeIRQ(flags);

	if ( ( SpiSeqRes == SPI_SEQ_OK ) && 
			( Spi_Global.AsyncMode == SPI_INTERRUPT_MODE )){
#if	( SPI_LEVEL_DELIVERED == 2 )
		Spi_MainFunction_Internal_Handling(SPI_ASYNCHRONOUS);
#else
		Spi_MainFunction_Internal_Handling();
#endif
	}

	return E_OK;

}
#endif	/* ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) */

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == 0) || (SPI_CHANNEL_BUFFERS_ALLOWED == 2))
/*
 * Spi_ReadIB implementation.
 */
Std_ReturnType Spi_ReadIB(Spi_ChannelType Channel, Spi_DataType *DataBufferPtr)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;
	register Spi_ChannelType	ChIdx;
	register Spi_NumberOfDataType	IbBuffIdx;

	VALIDATE_W_RV( ( DataBufferPtr != NULL_PTR ), 
			SPI_READIB_SERVICE_ID,
			SPI_E_PARAM_POINTER,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV( ( Spi_Global.DriverState != SPI_UNINIT ), 
			SPI_READIB_SERVICE_ID, 
			SPI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0; ((ChIdx < Spi_Global.ConfigPtr->SpiMaxChannel ) &&
		(Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelId != Channel));
    	ChIdx++) { ; }

	VALIDATE_IRQ_W_RV(( ChIdx < Spi_Global.ConfigPtr->SpiMaxChannel ), 
			SPI_READIB_SERVICE_ID,
			SPI_E_PARAM_CHANNEL,
			E_NOT_OK,
			flags);

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	VALIDATE_IRQ_W_RV( 
			( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelType == SPI_IB ),
					SPI_READIB_SERVICE_ID,
					SPI_E_PARAM_CHANNEL,
					E_NOT_OK,
					flags);
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

	if ( SpiChannelStatus[ChIdx].SpiDstIbEmpty == TRUE ) {

		rv = E_NOT_OK;

	} else {

		for ( IbBuffIdx = 0; IbBuffIdx < 
				Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiIbNBuffers; 
			IbBuffIdx++) {

			DataBufferPtr[IbBuffIdx] = SpiChDstIb[ChIdx][IbBuffIdx];
		
		}

		SpiChannelStatus[ChIdx].SpiDstIbEmpty = TRUE;

		rv = E_OK;
	}

	EE_hal_resumeIRQ(flags);

	return rv;

}
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if ( (SPI_CHANNEL_BUFFERS_ALLOWED == 1) || (SPI_CHANNEL_BUFFERS_ALLOWED == 2) )
/*
 * Spi_SetupEB implementation.
 */
Std_ReturnType Spi_SetupEB(Spi_ChannelType	Channel, 
							const Spi_DataType *SrcDataBufferPtr, 
							Spi_DataType *DesDataBufferPtr, 
							Spi_NumberOfDataType Length)
{

	register EE_FREG		flags;
	register Spi_ChannelType	ChIdx;

	VALIDATE_W_RV(( Length > 0x0000U ), 
			SPI_SETUPEB_SERVICE_ID,
			SPI_E_PARAM_LENGTH,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Spi_Global.DriverState != SPI_UNINIT ),
			SPI_SETUPEB_SERVICE_ID,
			SPI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0; (( ChIdx < Spi_Global.ConfigPtr->SpiMaxChannel ) &&
			( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelId != Channel )); 
		ChIdx++) { ; }

	VALIDATE_IRQ_W_RV(( ChIdx < Spi_Global.ConfigPtr->SpiMaxChannel ), 
			SPI_SETUPEB_SERVICE_ID,
			SPI_E_PARAM_CHANNEL,
			E_NOT_OK,
			flags);

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	VALIDATE_IRQ_W_RV( 
			( Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiChannelType == SPI_EB ),
			SPI_SETUPEB_SERVICE_ID,
			SPI_E_PARAM_CHANNEL,
			E_NOT_OK,
			flags);
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

	VALIDATE_IRQ_W_RV(
		( Length <= Spi_Global.ConfigPtr->SpiChannel[ChIdx].SpiEbMaxLength ),
		SPI_SETUPEB_SERVICE_ID,
		SPI_E_PARAM_LENGTH,
		E_NOT_OK,
		flags);

	SpiChannelStatus[ChIdx].SpiEbLen = Length;

	if ( SrcDataBufferPtr != NULL_PTR ) {

		SpiChannelStatus[ChIdx].SpiSrcEbPtr = SrcDataBufferPtr;

	}

	if ( DesDataBufferPtr != NULL_PTR ) {

		SpiChannelStatus[ChIdx].SpiDstEbPtr = DesDataBufferPtr;

	}

	EE_hal_resumeIRQ(flags);

	return E_OK;

}
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

/*
 * Spi_GetStatus implementation.
 */
Spi_StatusType Spi_GetStatus(void)
{

	register EE_FREG		flags;
	register Spi_StatusType	state;

	flags = EE_hal_suspendIRQ();
	state = Spi_Global.DriverState;
	EE_hal_resumeIRQ(flags);

	VALIDATE_W_RV(( state != SPI_UNINIT ), 
			SPI_GETSTATUS_SERVICE_ID,
			SPI_E_UNINIT,
			SPI_UNINIT);

	return state;
}

/*
 * Spi_GetJobResult implementation.
 */
Spi_JobResultType Spi_GetJobResult(Spi_JobType	Job)
{

	register EE_FREG		flags;
	register uint32		SpiJobIdx;
	register Spi_JobResultType	rv;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV( ( Spi_Global.DriverState != SPI_UNINIT ),
			SPI_GETJOBRESULT_SERVICE_ID,
			SPI_E_UNINIT,
			SPI_JOB_FAILED,
			flags);

	for (SpiJobIdx = 0; (( SpiJobIdx < Spi_Global.ConfigPtr->SpiMaxJob ) && 
			( Spi_Global.ConfigPtr->SpiJob[SpiJobIdx].SpiJobId != Job )); 
		SpiJobIdx++) { ; }

	VALIDATE_IRQ_W_RV( ( SpiJobIdx < Spi_Global.ConfigPtr->SpiMaxJob ),
			SPI_GETJOBRESULT_SERVICE_ID,
			SPI_E_PARAM_JOB,
			SPI_JOB_FAILED,
			flags);

	rv = SpiJobStatus[SpiJobIdx].SpiJobResult;

	EE_hal_resumeIRQ(flags);

	return rv;
}

/*
 * Spi_GetSequenceResult implementation.
 */
Spi_SeqResultType Spi_GetSequenceResult(Spi_SequenceType Sequence)
{

	register EE_FREG		flags;
	register Spi_SequenceType	SpiSeqIdx;
	register Spi_SeqResultType	rv;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Spi_Global.DriverState != SPI_UNINIT ), 
			SPI_GETSEQUENCERESULT_SERVICE_ID,
			SPI_E_UNINIT,
			SPI_SEQ_FAILED,
			flags);

	for (SpiSeqIdx = 0; (( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ) &&
			( Spi_Global.ConfigPtr->SpiSequence[SpiSeqIdx].SpiSequenceId != 
					Sequence )); SpiSeqIdx++) { ; }

	VALIDATE_IRQ_W_RV( ( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ), 
			SPI_GETSEQUENCERESULT_SERVICE_ID, 
			SPI_E_PARAM_SEQ, 
			SPI_SEQ_FAILED, 
			flags);

	rv = SpiSeqStatus[SpiSeqIdx].SpiSeqResult;

	EE_hal_resumeIRQ(flags);

	return rv;
}

#if ( ( SPI_LEVEL_DELIVERED == 0 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
/*
 * Spi_SyncTransmit implementation.
 */
Std_ReturnType Spi_SyncTransmit(Spi_SequenceType Sequence)
{

	register EE_FREG		flags;
	register Spi_JobType		SpiJobIdx, SpiJob;
	register Spi_SequenceType	SpiSeqIdx;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Spi_Global.DriverState != SPI_UNINIT ), 
			SPI_SYNCTRANSMIT_SERVICE_ID,
			SPI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (SpiSeqIdx = 0; (( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ) &&
			( Spi_Global.ConfigPtr->SpiSequence[SpiSeqIdx].SpiSequenceId != 
					Sequence )); SpiSeqIdx++) { ;}
	
	VALIDATE_IRQ_W_RV( ( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ),
			SPI_SYNCTRANSMIT_SERVICE_ID,
			SPI_E_PARAM_SEQ, 
			E_NOT_OK, 
			flags);

#if	( SPI_LEVEL_DELIVERED == 0 )
  /*
   * SPI114:	The LEVEL 0 SPI Handler/Driver shall not allow transmitting more
   * 		than one Sequence at the same time. That means during a Sequence
   * 		on-going transmission, all requests to transmit another Sequence
   * 		shall be rejected.
   */
	VALIDATE_IRQ_W_RV( ( Spi_Global.DriverState == SPI_IDLE ), 
			SPI_SYNCTRANSMIT_SERVICE_ID, 
			SPI_E_SEQ_IN_PROCESS, 
			E_NOT_OK, 
			flags);
#else	/* ( SPI_LEVEL_DELIVERED == 0 ) */
  /*
   * SPI108:	The LEVEL 2 SPI Handler/Driver is specified for microcontrollers
   * 		that have to provide, at least, two SPI busses using separated
   * 		hardware units. Otherwise, using this level of functionality
   * 		does not make sense.
   *
   * SPI129:	The SPI bus dedicated for synchronous transfers is prearranged.
   * 		This information shall be published by the supplier of this
   * 		software module.
   *
   * This functionality level, based on a mixed usage of synchronous
   * transmission on one prearranged SPI bus and asynchronous transmission on
   * others, generates restrictions on configuration and usage of Sequences and
   * Jobs.
   *
   * SPI130:	The so-called synchronous Sequences shall only be composed of
   * 		Jobs that are associated to the prearranged SPI bus. These
   * 		Sequences shall be used with synchronous services only.
   *
   * The second part of this requirement is aim at SPI Handler/Driver users.
   * But, it is up to the software module supplier to implement mechanisms in
   * order to prevent potential misuses by users.
   *
   * SPI131:	Jobs associated with the prearranged SPI bus shall not belong to
   * 		Sequences containing Jobs associated with another SPI bus. In
   * 		other words, mixed Sequences (synchronous with asynchronous
   * 		Jobs) shall not be allowed.
   */
	VALIDATE_W_RV( Spi_SeqSyncAsyncValidate(SpiSeqIdx, SPI_SYNCHRONOUS), 
			SPI_SYNCTRANSMIT_SERVICE_ID, 
			SPI_E_PARAM_SEQ, 
			E_NOT_OK);

  /*
   * SPI132:	The requirements for LEVEL 0 apply to synchronous behaviour.
   */

  /*
   * Checks if a previous same Sequence polling loop ended.
   */
	VALIDATE_IRQ_W_RV( !( Spi_Global.TransmitMode & SPI_SYNCHRONOUS ), 
			SPI_SYNCTRANSMIT_SERVICE_ID, 
			SPI_E_SEQ_IN_PROCESS, 
			E_NOT_OK, 
			flags);
	
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	Spi_Global.DriverState = SPI_BUSY;

#if	( SPI_LEVEL_DELIVERED == 2 )
	/* Polling Loop Lock. */
	Spi_Global.TransmitMode |= SPI_SYNCHRONOUS;
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

	SpiSeqStatus[SpiSeqIdx].SpiSeqResult = SPI_SEQ_PENDING;

	SpiJob = Spi_Global.ConfigPtr->SpiSequence[SpiSeqIdx].SpiJobAssignment[0];

	for (SpiJobIdx = 0; 
			( Spi_Global.ConfigPtr->SpiJob[SpiJobIdx].SpiJobId != SpiJob ); 
			SpiJobIdx++) { ; }

	SpiSeqStatus[SpiSeqIdx].SpiCurrJobIdx = SpiJobIdx;

	/* Polling Loop */
	do {
		EE_hal_resumeIRQ(flags);

#if	( SPI_LEVEL_DELIVERED == 2 )
		Spi_MainFunction_Internal_Handling(SPI_SYNCHRONOUS);
#else
		Spi_MainFunction_Internal_Handling();
#endif
		flags = EE_hal_suspendIRQ();
	} while ( SpiSeqStatus[Sequence].SpiSeqResult == SPI_SEQ_PENDING );

	EE_hal_resumeIRQ(flags);

	return E_OK;

}
#endif	/* ( SPI_LEVEL_DELIVERED == 0 ) || ( SPI_LEVEL_DELIVERED == 2 ) */

#if ( SPI_HW_STATUS_API == STD_ON )
/*
 * Spi_GetHWUnitStatus implementation
 */
Spi_StatusType Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit)
{

	register EE_FREG		flags;
	register Spi_StatusType	rv;

	VALIDATE_W_RV( ( HWUnit < SPI_MAX_HW_UNIT ), 
			SPI_GETHWUNITSTATUS_SERVICE_ID,
			SPI_E_UNINIT, 
			SPI_UNINIT);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV( 
			( Spi_Global.DriverState != SPI_UNINIT ),
			SPI_GETHWUNITSTATUS_SERVICE_ID,
			SPI_E_UNINIT,
			SPI_UNINIT,
			flags);
  /* EFFECTIVE HARDAWARE UNIT STATUS */
	VALIDATE_IRQ_W_RV(( Spi_IsChannelEnabled(HWUnit) ), 
			SPI_GETHWUNITSTATUS_SERVICE_ID, SPI_E_UNINIT, SPI_UNINIT, flags);
	

	/* SPI Handler/Driver Hardware Unit Status. */
	if ( SpiHwUnitStatus[HWUnit].SpiOwnerIdx == SPI_JOB_END_LIST ) {

		rv = SPI_IDLE;

	} else {

		rv = SPI_BUSY;
	}

	EE_hal_resumeIRQ(flags);

	return rv;

}
#endif

#if	( SPI_CANCEL_API == STD_ON )
/*
 * Spi_Cancel implementation
 */
void Spi_Cancel(Spi_SequenceType Sequence)
{

	register EE_FREG		flags;
	register Spi_SequenceType	SpiSeqIdx;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(( Spi_Global.DriverState != SPI_UNINIT ),
			SPI_CANCEL_SERVICE_ID, 
			SPI_E_UNINIT, 
			flags);

	for (SpiSeqIdx = 0; 
			(( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ) &&
					( Spi_Global.ConfigPtr->SpiSequence[
					                     SpiSeqIdx].SpiSequenceId != Sequence));
			SpiSeqIdx++) { ; }

	VALIDATE_IRQ( ( SpiSeqIdx < Spi_Global.ConfigPtr->SpiMaxSequence ),
			SPI_CANCEL_SERVICE_ID,
			SPI_E_PARAM_SEQ,
			flags);

	if ( SpiSeqStatus[SpiSeqIdx].SpiSeqResult == SPI_SEQ_PENDING ) {
		SpiSeqStatus[SpiSeqIdx].SpiSeqResult = SPI_SEQ_CANCELED;
	}

	EE_hal_resumeIRQ(flags);

}
#endif

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || (  SPI_LEVEL_DELIVERED == 2 ) )
/*
 * Spi_SetAsyncMode implementation. (Non Re-entrant)
 */
Std_ReturnType Spi_SetAsyncMode(Spi_AsyncModeType Mode)
{

	register EE_FREG		flags;
	register Std_ReturnType	rv;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(( Spi_Global.DriverState != SPI_UNINIT ),
			SPI_SETASYNCMODE_SERVICE_ID,
			SPI_E_UNINIT,
			E_NOT_OK,
			flags);

	rv = E_NOT_OK;

	/* Asychronous Mode Setup. */
	if (
#if (  SPI_LEVEL_DELIVERED == 2 )
		!( Spi_Global.TransmitMode & SPI_ASYNCHRONOUS ) ||
#endif
		( Spi_Global.DriverState == SPI_IDLE )) {

		Spi_Global.AsyncMode = Mode;

		rv = E_OK;

	}

	EE_hal_resumeIRQ(flags);

	return rv;

}
#endif
