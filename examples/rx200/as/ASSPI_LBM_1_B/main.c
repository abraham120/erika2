/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013	Evidence Srl
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
 * module.	An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.	If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Simple project to test the AUTOSAR SPI Handler/Driver:
 * - 1 Sequence
 *	 - 1 Job
 *	   - 4 Channel
 * - 3 SCI Hardware Units
 *	 - Loop-back Mode (MOSI and MISO pins connected by a wire)
 *	 - 2 Units Asynchronous
 *	 - 1 Units Synchronous
 * - Write/AsyncTransmit/Read (IB)
 *	 - Interrupt Mode
 *	 - Polling Mode
 * - Setup/AsyncTransmit (EB)
 *	 - Interrupt Mode
 *	 - Polling Mode
 * - Write/SyncTransmit/Read (IB)
 * - Setup/SyncTransmit (EB)
 *
 * Author: 2013	 Gianluca Franchino
 */

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Spi.h"
#include "test/assert/inc/ee_assert.h"

#include <string.h>

/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,					/*	0 */
	EE_ASSERT_INIT,						/*	1 */
	EE_ASSERT_VERSION,					/*	2 */
	EE_ASSERT_CLOCK_INIT,				/*	3 */
	EE_ASSERT_SPI_INIT,					/*	4 */
	EE_ASSERT_SPI_UNINIT,				/*	5 */
	EE_ASSERT_SPI_INTERRUPT_MODE,		/*	6 */
	EE_ASSERT_SPI_INT_WRITE_IB_0,		/*	7 */
	EE_ASSERT_SPI_INT_WRITE_IB_1,		/*	8 */
	EE_ASSERT_SPI_INT_WRITE_IB_2,		/*	9 */
	EE_ASSERT_SPI_INT_WRITE_IB_3,		/* 10 */
	EE_ASSERT_SPI_INT_ASYNC_TX,			/* 11 */
	EE_ASSERT_SPI_INT_JOB_END,			/* 12 */
	EE_ASSERT_SPI_INT_JOB_OK,			/* 13 */
	EE_ASSERT_SPI_INT_SEQ_END,			/* 14 */
	EE_ASSERT_SPI_INT_SEQ_OK,			/* 15 */
	EE_ASSERT_SPI_INT_READ_IB_0,		/* 16 */
	EE_ASSERT_SPI_INT_READ_IB_1,		/* 17 */
	EE_ASSERT_SPI_INT_READ_IB_2,		/* 18 */
	EE_ASSERT_SPI_INT_READ_IB_3,		/* 19 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_0,	/* 20 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_1,	/* 21 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_2,	/* 22 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_3,	/* 23 */
	EE_ASSERT_SPI_POLLING_MODE,			/* 24 */
	EE_ASSERT_SPI_POLL_WRITE_IB_0,		/* 25 */
	EE_ASSERT_SPI_POLL_WRITE_IB_1,		/* 26 */
	EE_ASSERT_SPI_POLL_WRITE_IB_2,		/* 27 */
	EE_ASSERT_SPI_POLL_WRITE_IB_3,		/* 28 */
	EE_ASSERT_SPI_POLL_ASYNC_TX,		/* 29*/
	EE_ASSERT_SPI_POLL_JOB_END,			/* 30 */
	EE_ASSERT_SPI_POLL_JOB_OK,			/* 31 */
	EE_ASSERT_SPI_POLL_SEQ_END,			/* 32 */
	EE_ASSERT_SPI_POLL_SEQ_OK,			/* 33 */
	EE_ASSERT_SPI_POLL_READ_IB_0,		/* 34 */
	EE_ASSERT_SPI_POLL_READ_IB_1,		/* 35 */
	EE_ASSERT_SPI_POLL_READ_IB_2,		/* 36 */
	EE_ASSERT_SPI_POLL_READ_IB_3,		/* 37 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_0,	/* 38 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_1,	/* 39 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_2,	/* 40 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_3,	/* 41 */
	EE_ASSERT_SPI_EB_INT_MODE,			/* 42 */
	EE_ASSERT_SPI_EB_INT_SETUP_0,		/* 43 */
	EE_ASSERT_SPI_EB_INT_SETUP_1,		/* 44 */
	EE_ASSERT_SPI_EB_INT_SETUP_2,		/* 45 */
	EE_ASSERT_SPI_EB_INT_SETUP_3,		/* 46 */
	EE_ASSERT_SPI_EB_INT_ASYNC_TX,		/* 47 */
	EE_ASSERT_SPI_EB_INT_JOB_END,		/* 48 */
	EE_ASSERT_SPI_EB_INT_JOB_OK,		/* 49 */
	EE_ASSERT_SPI_EB_INT_SEQ_END,		/* 50 */
	EE_ASSERT_SPI_EB_INT_SEQ_OK,		/* 51 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_0,	/* 52 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_1,	/* 53 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_2,	/* 54 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_3,	/* 55 */
	EE_ASSERT_SPI_EB_POLL_MODE,			/* 56 */
	EE_ASSERT_SPI_EB_POLL_SETUP_0,		/* 57 */
	EE_ASSERT_SPI_EB_POLL_SETUP_1,		/* 58 */
	EE_ASSERT_SPI_EB_POLL_SETUP_2,		/* 59 */
	EE_ASSERT_SPI_EB_POLL_SETUP_3,		/* 60 */
	EE_ASSERT_SPI_EB_POLL_ASYNC_TX,		/* 61 */
	EE_ASSERT_SPI_EB_POLL_JOB_END,		/* 62 */
	EE_ASSERT_SPI_EB_POLL_JOB_OK,		/* 63 */
	EE_ASSERT_SPI_EB_POLL_SEQ_END,		/* 64 */
	EE_ASSERT_SPI_EB_POLL_SEQ_OK,		/* 65 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_0,	/* 66 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_1,	/* 67 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_2,	/* 68 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_3,	/* 69 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_0,		/* 70 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_1,		/* 71 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_2,		/* 72 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_3,		/* 73 */
	EE_ASSERT_SPI_SYNC_TX,				/* 74 */
	EE_ASSERT_SPI_SYNC_JOB_OK,			/* 75 */
	EE_ASSERT_SPI_SYNC_SEQ_OK,			/* 76 */
	EE_ASSERT_SPI_SYNC_READ_IB_0,		/* 77 */
	EE_ASSERT_SPI_SYNC_READ_IB_1,		/* 78 */
	EE_ASSERT_SPI_SYNC_READ_IB_2,		/* 79 */
	EE_ASSERT_SPI_SYNC_READ_IB_3,		/* 80 */
	EE_ASSERT_SPI_SYNC_VALIDATE_0,		/* 81 */
	EE_ASSERT_SPI_SYNC_VALIDATE_1,		/* 82 */
	EE_ASSERT_SPI_SYNC_VALIDATE_2,		/* 83 */
	EE_ASSERT_SPI_SYNC_VALIDATE_3,		/* 84 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_0,		/* 85 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_1,		/* 86 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_2,		/* 87 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_3,		/* 88 */
	EE_ASSERT_SPI_EB_SYNC_TX,			/* 89 */
	EE_ASSERT_SPI_EB_SYNC_JOB_OK,		/* 90 */
	EE_ASSERT_SPI_EB_SYNC_SEQ_OK,		/* 91 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_0,	/* 92 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_1,	/* 93 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_2,	/* 94 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_3,	/* 95 */
	EE_ASSERT_SPI_DEINIT,				/* 96 */
	EE_ASSERT_DIM
};


EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int test = 0;

/* counter */
volatile int counter = 0;

/*
 * TASK Job Error.
 */
TASK(TaskJobError)
{
	counter++;
}

/*
 * TASK Job Ok.
 */
TASK(TaskJobOk)
{

	switch (test) {
		case 0:
			EE_assert(EE_ASSERT_SPI_INT_JOB_OK, TRUE, 
					EE_ASSERT_SPI_INT_JOB_END);
			break;
		case 1:
			EE_assert(EE_ASSERT_SPI_POLL_JOB_OK, TRUE, 
					EE_ASSERT_SPI_POLL_JOB_END);
			break;
		case 2:
			EE_assert(EE_ASSERT_SPI_EB_INT_JOB_OK, TRUE, 
					EE_ASSERT_SPI_EB_INT_JOB_END);
			break;
		case 3:
			EE_assert(EE_ASSERT_SPI_EB_POLL_JOB_OK, TRUE, 
					EE_ASSERT_SPI_EB_POLL_JOB_END);
			break;
	}
}

/*
 * LBM Job 1 End Notification.
 */
void Spi_LBMJob1EndNotification()
{

	switch (test) {
	case 0: 
		EE_assert(EE_ASSERT_SPI_INT_JOB_END, TRUE, EE_ASSERT_SPI_INT_WRITE_IB_3);
		if (Spi_GetJobResult(SPI_LBM_JOB_1) == SPI_JOB_OK) { 
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_JOB_END, TRUE, EE_ASSERT_SPI_POLL_ASYNC_TX);
		if (Spi_GetJobResult(SPI_LBM_JOB_1) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		} 
		break;	
	case 2: 
		EE_assert(EE_ASSERT_SPI_EB_INT_JOB_END, TRUE, EE_ASSERT_SPI_EB_INT_SETUP_3);
		if (Spi_GetJobResult(SPI_LBM_JOB_1_EB) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_JOB_END, TRUE, 
				EE_ASSERT_SPI_EB_POLL_ASYNC_TX);
		if (Spi_GetJobResult(SPI_LBM_JOB_1_EB) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	}
}

/*
 * TASK Sequence Error
 */
TASK(TaskSeqError)
{

  counter++;

}

/*
 * TASK Sequence Ok
 */
TASK(TaskSeqOk)
{

	switch (test) {
	case 0:
		EE_assert(EE_ASSERT_SPI_INT_SEQ_OK, TRUE, EE_ASSERT_SPI_INT_SEQ_END);
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_SEQ_OK, TRUE, EE_ASSERT_SPI_POLL_SEQ_END);
		break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_SEQ_OK, TRUE, 
				EE_ASSERT_SPI_EB_INT_SEQ_END);
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_SEQ_OK, TRUE, 
				EE_ASSERT_SPI_EB_POLL_SEQ_END);
		break;
  }

}

/*
 * LBM Sequence 2 End Notification.
 */
void Spi_LBMSeq2EndNotification()
{

	switch (test) {
	case 0:
		EE_assert(EE_ASSERT_SPI_INT_SEQ_END, TRUE, EE_ASSERT_SPI_INT_JOB_END);
		if (Spi_GetSequenceResult(SPI_LBM_SEQ_2) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_SEQ_END, TRUE, EE_ASSERT_SPI_POLL_JOB_END);
		if (Spi_GetSequenceResult(SPI_LBM_SEQ_2) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_SEQ_END, TRUE, 
				EE_ASSERT_SPI_EB_INT_JOB_END);
		if (Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_SEQ_END, TRUE, 
				EE_ASSERT_SPI_EB_POLL_JOB_END);
	  if (Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB) == SPI_SEQ_OK) {
		  ActivateTask(TaskSeqOk);
	  } else {
		  ActivateTask(TaskSeqError);
	  }
	  break;
	}
}


#define	SPI_TX_RX_DATA_NULL	0x00U

#define	SPI_CHANNEL_NUMBER	0x04U

#if	0	/* Not-Optimized Code. */
Spi_DataType rx[SPI_CHANNEL_NUMBER][SPI_IB_MAX_N_BUFFERS],
		tx[SPI_CHANNEL_NUMBER][SPI_IB_MAX_N_BUFFERS];
#else	/* Optimized Code. */
Spi_DataType rx[SPI_CHANNEL_NUMBER][SPI_CHANNEL_13_MAX_IB_N_BUFFERS],
		tx[SPI_CHANNEL_NUMBER][SPI_CHANNEL_13_MAX_IB_N_BUFFERS];
#endif	/* Optimized Code. */

void setup_buff(void)
{

	Spi_NumberOfDataType i, j;

	for (i = 0; i < SPI_CHANNEL_NUMBER; i++) {

#if	0	/* Not-Optimized Code. */
		for (j = 0; j < SPI_IB_MAX_N_BUFFERS; j++) {
#else	/* Optimized Code. */
		for (j = 0; j < SPI_CHANNEL_13_MAX_IB_N_BUFFERS; j++) {
#endif	/* Optimized Code. */
			rx[i][j] = SPI_TX_RX_DATA_NULL;
			tx[i][j] = counter + test + i + j;
		}
	}
}


boolean cmp_buff(Spi_NumberOfDataType idx)
{

	Spi_NumberOfDataType	i;
	boolean		rv = TRUE;

	for (i = 0; i < ( idx + 1 ); i++) {

		if ( rx[idx][i] != tx[idx][i] ) {

			rv = FALSE;
		}

	}

	return rv;
}


/*
 * MAIN TASK
 */
int main(void)
{
	Std_VersionInfoType	version;
	Dio_PortLevelType	lvl;

	counter = 0;

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	Spi_GetVersionInfo(&version);

	EE_assert(EE_ASSERT_VERSION, 
			((version.vendorID == 0) && 
					(version.moduleID == 83) && 
					(version.sw_major_version == 1) && 
					(version.sw_minor_version == 0) && 
					(version.sw_patch_version == 0)), 
					EE_ASSERT_INIT);

	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
	
	if (Mcu_InitClock(MCU_CLK_MODE_HOCO40_I1_B2) == E_NOT_OK) {
		/* Clock Initialization Error. */
		Mcu_PerformReset();
	}
	
	EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

	Port_Init(PORT_CONFIG_DEFAULT_PTR);

	Dio_Init(DIO_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_SPI_UNINIT, ( Spi_GetStatus() == SPI_UNINIT ), 
			EE_ASSERT_CLOCK_INIT);
	
	/*Configure the pins of SCI modules */
	Port_Init(PORT_CONFIG_SCI_PTR);

	Spi_Init(SPI_CONFIG_LBM_PTR);

	EE_assert(EE_ASSERT_SPI_INIT, ( Spi_GetStatus() == SPI_IDLE ), 
			EE_ASSERT_INIT);

	test = 0;

	EE_assert(EE_ASSERT_SPI_INTERRUPT_MODE, 
			( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ), 
			EE_ASSERT_SPI_INIT);

	setup_buff();

	EE_assert(EE_ASSERT_SPI_INT_WRITE_IB_0, 
			( Spi_WriteIB(SPI_LBM_CHANNEL_0, tx[0]) == E_OK ), 
			EE_ASSERT_SPI_INTERRUPT_MODE);


	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_1,
		( Spi_WriteIB(SPI_LBM_CHANNEL_1, tx[1]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_0
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_2,
		( Spi_WriteIB(SPI_LBM_CHANNEL_2, tx[2]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_1
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_3,
		( Spi_WriteIB(SPI_LBM_CHANNEL_3, tx[3]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_2
	);

	EE_assert(
		EE_ASSERT_SPI_INT_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_2) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_3
	);

	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_2) == SPI_SEQ_PENDING ) {
	;
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_2) == SPI_SEQ_OK ) {

		EE_assert(
			EE_ASSERT_SPI_INT_READ_IB_0,
			( Spi_ReadIB(SPI_LBM_CHANNEL_0, rx[0]) == E_OK ),
			EE_ASSERT_SPI_INT_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_1,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_1, rx[1]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_0
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_2,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx[2]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_1
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_3,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_3, rx[3]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_2
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_INT_READ_IB_3
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_2
		);

	}

	test++;

	EE_assert(
		EE_ASSERT_SPI_POLLING_MODE,
		( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ),
		EE_ASSERT_SPI_INT_READ_VALIDATE_3
	);

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_0,
		( Spi_WriteIB(SPI_LBM_CHANNEL_0, tx[0]) == E_OK ),
		EE_ASSERT_SPI_POLLING_MODE
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_1,
		( Spi_WriteIB(SPI_LBM_CHANNEL_1, tx[1]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_0
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_2,
		( Spi_WriteIB(SPI_LBM_CHANNEL_2, tx[2]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_1
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_3,
		( Spi_WriteIB(SPI_LBM_CHANNEL_3, tx[3]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_2
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_2) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_3
	);

	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_2) == SPI_SEQ_PENDING ) {

		Spi_MainFunction_Handling();
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_2) == SPI_SEQ_OK ) {

		EE_assert(
		EE_ASSERT_SPI_POLL_READ_IB_0,
		( Spi_ReadIB(SPI_LBM_CHANNEL_0, rx[0]) == E_OK ),
		EE_ASSERT_SPI_POLL_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_1,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_1, rx[1]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_0
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_2,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx[2]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_1
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_3,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_3, rx[3]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_2
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_POLL_READ_IB_3
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_2
		);

	}

	test++;

	EE_assert(
		EE_ASSERT_SPI_EB_INT_MODE,
		( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ),
		EE_ASSERT_SPI_POLL_READ_VALIDATE_3
	);

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_0,
		(
		Spi_SetupEB(SPI_LBM_CHANNEL_0_EB, tx[0], rx[0], 1)
		==
		E_OK
		),
		EE_ASSERT_SPI_EB_INT_MODE
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_1,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_1_EB, tx[1], rx[1], 2)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_0
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_2,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_2_EB, tx[2], rx[2], 3)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_1
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_3,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_3_EB, tx[3], rx[3], 4)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_2
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_2_EB) == E_OK ),
		EE_ASSERT_SPI_EB_INT_SETUP_3
	);

	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB) == SPI_SEQ_PENDING ) {
	;
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_EB_INT_ASYNC_TX
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_2
		);

	}

	test++;

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_MODE,
		( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ),
		EE_ASSERT_SPI_EB_INT_VALIDATE_3
	);

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_0,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_0_EB, tx[0], rx[0], 1)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_MODE
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_1,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_1_EB, tx[1], rx[1], 2)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_0
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_2,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_2_EB, tx[2], rx[2], 3)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_1
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_3,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_3_EB, tx[3], rx[3], 4)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_2
	);


	EE_assert(
		EE_ASSERT_SPI_EB_POLL_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_2_EB) == E_OK ),
		EE_ASSERT_SPI_EB_POLL_SETUP_3
	);

	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB) == SPI_SEQ_PENDING ) {

	Spi_MainFunction_Handling();
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_EB_POLL_ASYNC_TX
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_0
		);

		EE_assert(
		EE_ASSERT_SPI_EB_POLL_VALIDATE_2,
		cmp_buff(2),
		EE_ASSERT_SPI_EB_POLL_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_2
		);

	}

	test++;

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_0,
		( Spi_WriteIB(SPI_LBM_CHANNEL_0, tx[0]) == E_OK ),
		EE_ASSERT_SPI_EB_POLL_VALIDATE_3
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_1,
		( Spi_WriteIB(SPI_LBM_CHANNEL_1, tx[1]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_0
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_2,
		( Spi_WriteIB(SPI_LBM_CHANNEL_2, tx[2]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_1
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_3,
		( Spi_WriteIB(SPI_LBM_CHANNEL_3, tx[3]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_2
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_TX,
		( Spi_SyncTransmit(SPI_LBM_SEQ_2_SYNC) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_3
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_JOB_OK,
		( Spi_GetJobResult(SPI_LBM_JOB_1_SYNC) == SPI_JOB_OK ),
		EE_ASSERT_SPI_SYNC_TX
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_SEQ_OK,
		( Spi_GetSequenceResult(SPI_LBM_SEQ_2_SYNC) == SPI_SEQ_OK ),
		EE_ASSERT_SPI_SYNC_JOB_OK
	);

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_2_SYNC) == SPI_SEQ_OK ) {

		EE_assert(
			EE_ASSERT_SPI_SYNC_READ_IB_0,
			( Spi_ReadIB(SPI_LBM_CHANNEL_0, rx[0]) == E_OK ),
			EE_ASSERT_SPI_SYNC_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_1,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_1, rx[1]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_0
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_2,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx[2]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_1
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_3,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_3, rx[3]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_2
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_SYNC_READ_IB_3
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_SYNC_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_SYNC_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_SYNC_VALIDATE_2
		);

	}

	test++;

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_0,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_0_EB, tx[0], rx[0], 1)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_SYNC_VALIDATE_3
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_1,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_1_EB, tx[1], rx[1], 2)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_0
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_2,
		( 
		Spi_SetupEB(SPI_LBM_CHANNEL_2_EB, tx[2], rx[2], 3)
		==
		E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_1
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_3,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_3_EB, tx[3], rx[3], 4)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_2
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_TX,
		( Spi_SyncTransmit(SPI_LBM_SEQ_2_EB_SYNC) == E_OK ),
		EE_ASSERT_SPI_EB_SYNC_SETUP_3
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_JOB_OK,
		( Spi_GetJobResult(SPI_LBM_JOB_1_EB_SYNC) == SPI_JOB_OK ),
		EE_ASSERT_SPI_EB_SYNC_TX
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SEQ_OK,
		( Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB_SYNC) == SPI_SEQ_OK ),
		EE_ASSERT_SPI_EB_SYNC_JOB_OK
	);

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_2_EB_SYNC) == SPI_SEQ_OK ) {

		EE_assert(
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_0,
			cmp_buff(0),
			EE_ASSERT_SPI_EB_SYNC_SEQ_OK
		);

		EE_assert(
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_1,
			cmp_buff(1),
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_0
		);

		EE_assert(
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_2,
			cmp_buff(2),
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_1
		);

		EE_assert(
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_3,
			cmp_buff(3),
			EE_ASSERT_SPI_EB_SYNC_VALIDATE_2
		);

	}

	EE_assert(
		EE_ASSERT_SPI_DEINIT,
		( Spi_DeInit() == E_OK ),
		EE_ASSERT_SPI_EB_SYNC_VALIDATE_3
	);

	EE_assert_range(
		EE_ASSERT_FIN,
		( Spi_GetStatus() == SPI_UNINIT ),
		EE_ASSERT_SPI_DEINIT
	);

	result = EE_assert_last();
	
	/* Forever loop: background activities (if any) should go here */
	for (;result == 1;) {
		while (counter % 100000) counter++;
		
		lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED_0);
		
		if (lvl & 0x00000001)
			Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000000);
		else 
			Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000001);

		counter++;
	}

}