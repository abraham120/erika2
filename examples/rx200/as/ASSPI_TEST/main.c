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
 * Simple project to test the AUTOSAR SPI Handler/Driver:
 * - 1 Sequence
 *   - 1 Job
 *     - 1 Channel
 *       - One Byte Only.
 * - 2 SSI Hardware Modules
 *   - Loop-back Mode
 *   - 1 Unit Asynchronous
 *   - 1 Unit Synchronous
 * - Write/AsyncTransmit/Read (IB)
 *   - Interrupt Mode
 *   - Polling Mode
 * - Setup/AsyncTransmit (EB)
 *   - Interrupt Mode
 *   - Polling Mode
 * - Write/SyncTransmit/Read (IB)
 * - Setup/SyncTransmit (EB)
 *
 * 
 * Author: 2013  Gianluca Franchino
 */

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Spi.h"
#include "test/assert/inc/ee_assert.h"

/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,					/*  0 */
	EE_ASSERT_INIT,						/*  1 */
	EE_ASSERT_VERSION,					/*  2 */
	EE_ASSERT_CLOCK_INIT,				/*  3 */
	EE_ASSERT_SPI_UNINIT,				/*  4 */
	EE_ASSERT_SPI_INIT,					/*  5 */
	EE_ASSERT_SPI_INTERRUPT_MODE,		/*  6 */
	EE_ASSERT_SPI_INT_WRITE_IB,			/*  7 */
	EE_ASSERT_SPI_INT_ASYNC_TX,			/* 	8 */
	EE_ASSERT_SPI_INT_JOB_END,			/* 	9 */
	EE_ASSERT_SPI_INT_JOB_OK,			/* 10 */
	EE_ASSERT_SPI_INT_SEQ_END,			/* 11 */
	EE_ASSERT_SPI_INT_SEQ_OK,			/* 12 */
	EE_ASSERT_SPI_INT_READ_IB,			/* 13 */
	EE_ASSERT_SPI_INT_READ_VALIDATE,	/* 14 */
	EE_ASSERT_SPI_POLLING_MODE,			/* 15 */
	EE_ASSERT_SPI_POLL_WRITE_IB,		/* 16 */
	EE_ASSERT_SPI_POLL_ASYNC_TX,		/* 17 */
	EE_ASSERT_SPI_POLL_JOB_END,			/* 18 */
	EE_ASSERT_SPI_POLL_JOB_OK,			/* 19 */
	EE_ASSERT_SPI_POLL_SEQ_END,			/* 20 */
	EE_ASSERT_SPI_POLL_SEQ_OK,			/* 21 */
	EE_ASSERT_SPI_POLL_READ_IB,			/* 22 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE,	/* 23 */
	EE_ASSERT_SPI_EB_INT_MODE,			/* 24 */
	EE_ASSERT_SPI_EB_INT_SETUP,			/* 25 */
	EE_ASSERT_SPI_EB_INT_ASYNC_TX,		/* 26 */
	EE_ASSERT_SPI_EB_INT_JOB_END,		/* 27 */
	EE_ASSERT_SPI_EB_INT_JOB_OK,		/* 28 */
	EE_ASSERT_SPI_EB_INT_SEQ_END,		/* 29 */
	EE_ASSERT_SPI_EB_INT_SEQ_OK,		/* 30 */
	EE_ASSERT_SPI_EB_INT_VALIDATE,		/* 31 */
	EE_ASSERT_SPI_EB_POLL_MODE,			/* 32 */
	EE_ASSERT_SPI_EB_POLL_SETUP,		/* 33 */
	EE_ASSERT_SPI_EB_POLL_ASYNC_TX,		/* 34 */
	EE_ASSERT_SPI_EB_POLL_JOB_END,		/* 35 */
	EE_ASSERT_SPI_EB_POLL_JOB_OK,		/* 36 */
	EE_ASSERT_SPI_EB_POLL_SEQ_END,		/* 37 */
	EE_ASSERT_SPI_EB_POLL_SEQ_OK,		/* 38 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE,		/* 39 */
	EE_ASSERT_SPI_SYNC_WRITE_IB,		/* 40 */
	EE_ASSERT_SPI_SYNC_TX,				/* 41 */
	EE_ASSERT_SPI_SYNC_JOB_OK,			/* 42 */
	EE_ASSERT_SPI_SYNC_SEQ_OK,			/* 43 */
	EE_ASSERT_SPI_SYNC_READ_IB,			/* 44 */
	EE_ASSERT_SPI_SYNC_READ_VALIDATE,	/* 45 */
	EE_ASSERT_SPI_EB_SYNC_SETUP,		/* 46 */
	EE_ASSERT_SPI_EB_SYNC_TX,			/* 47 */
	EE_ASSERT_SPI_EB_SYNC_JOB_OK,		/* 48 */
	EE_ASSERT_SPI_EB_SYNC_SEQ_OK,		/* 49 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE,		/* 50 */
	EE_ASSERT_SPI_DEINIT,				/* 51 */
	EE_ASSERT_DIM
};

EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/* counter */
volatile int test = 0;

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
		EE_assert(EE_ASSERT_SPI_INT_JOB_OK, TRUE, EE_ASSERT_SPI_INT_JOB_END);
		break;
    case 1:
    	EE_assert(EE_ASSERT_SPI_POLL_JOB_OK, TRUE, EE_ASSERT_SPI_POLL_JOB_END);
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
 * TEST Job 0 End Notification.
 */
void Spi_TestJob0EndNotification()
{

	switch ( test ) {
	case 0:
		EE_assert( EE_ASSERT_SPI_INT_JOB_END, TRUE, EE_ASSERT_SPI_INT_WRITE_IB);
		if (Spi_GetJobResult(SPI_TEST_JOB_0) == SPI_JOB_OK) { 
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_JOB_END, TRUE, EE_ASSERT_SPI_POLL_ASYNC_TX);
		if (Spi_GetJobResult(SPI_TEST_JOB_0) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_JOB_END, TRUE, EE_ASSERT_SPI_EB_INT_SETUP);
		if ( Spi_GetJobResult(SPI_TEST_JOB_0_EB) == SPI_JOB_OK ) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_JOB_END, TRUE, 
				EE_ASSERT_SPI_EB_POLL_ASYNC_TX);
		if (Spi_GetJobResult(SPI_TEST_JOB_0_EB) == SPI_JOB_OK) {
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
		EE_assert( EE_ASSERT_SPI_INT_SEQ_OK, TRUE, EE_ASSERT_SPI_INT_JOB_END );
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_SEQ_OK, TRUE, EE_ASSERT_SPI_POLL_JOB_END);
      break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_SEQ_OK, TRUE, 
				EE_ASSERT_SPI_EB_INT_JOB_END);
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_SEQ_OK, TRUE, 
				EE_ASSERT_SPI_EB_POLL_JOB_END);
		break;
	}
}

/*
 * TEST Sequence 0 End Notification.
 */
void Spi_TestSeq0EndNotification()
{

	switch (test) {
	case 0:
		EE_assert(EE_ASSERT_SPI_INT_SEQ_END, TRUE, EE_ASSERT_SPI_INT_JOB_END);
		if (Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_SEQ_END, TRUE, EE_ASSERT_SPI_POLL_JOB_END);
		if (Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else { 
			ActivateTask(TaskSeqError);
		}
		break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_SEQ_END, TRUE, 
				EE_ASSERT_SPI_EB_INT_JOB_END);
		if (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_SEQ_END, TRUE, 
				EE_ASSERT_SPI_EB_POLL_JOB_END);
		if (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	}

}



#define	SPI_TX_RX_DATA		0xF0U
#define	SPI_TX_RX_DATA_NULL	0x00U
#define	SPI_EB_LENGTH		0x01U

Spi_DataType	rx;
Spi_DataType	tx;

/*
 * MAIN TASK
 */
int main(void)
{
	Std_VersionInfoType	version;
	Dio_PortLevelType	lvl;

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
	Spi_Init(SPI_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_SPI_INIT, ( Spi_GetStatus() == SPI_IDLE ), 
			EE_ASSERT_SPI_UNINIT);
	
	test = 0;
	
	EE_assert(EE_ASSERT_SPI_INTERRUPT_MODE, 
			( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ), 
			EE_ASSERT_SPI_INIT);

	tx = SPI_TX_RX_DATA + test;
	rx = SPI_TX_RX_DATA_NULL;

	EE_assert(EE_ASSERT_SPI_INT_WRITE_IB, 
			( Spi_WriteIB(SPI_TEST_CHANNEL_0, &tx) == E_OK ), 
			EE_ASSERT_SPI_INTERRUPT_MODE);

	EE_assert(EE_ASSERT_SPI_INT_ASYNC_TX, 
			( Spi_AsyncTransmit(SPI_TEST_SEQ_0) == E_OK ),
			EE_ASSERT_SPI_INT_WRITE_IB);

	while ( Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_PENDING ) { ; }

	if ( Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_OK ) {

		EE_assert(EE_ASSERT_SPI_INT_READ_IB, 
				( Spi_ReadIB(SPI_TEST_CHANNEL_0, &rx) == E_OK ), 
				EE_ASSERT_SPI_INT_SEQ_OK);

		EE_assert(EE_ASSERT_SPI_INT_READ_VALIDATE, 
				( rx == SPI_TX_RX_DATA + test ), EE_ASSERT_SPI_INT_READ_IB);
	}
	
	test++;

	EE_assert(EE_ASSERT_SPI_POLLING_MODE, 
			( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ), 
			EE_ASSERT_SPI_INT_READ_VALIDATE);

	tx = SPI_TX_RX_DATA + test;
	rx = SPI_TX_RX_DATA_NULL;

	EE_assert(EE_ASSERT_SPI_POLL_WRITE_IB, 
			( Spi_WriteIB(SPI_TEST_CHANNEL_0, &tx) == E_OK ), 
			EE_ASSERT_SPI_POLLING_MODE);

	EE_assert(EE_ASSERT_SPI_POLL_ASYNC_TX, 
			( Spi_AsyncTransmit(SPI_TEST_SEQ_0) == E_OK ), 
			EE_ASSERT_SPI_POLL_WRITE_IB);

	while (Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_PENDING) {

		Spi_MainFunction_Handling();
	}

	if (Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_OK) {

		EE_assert(EE_ASSERT_SPI_POLL_READ_IB, 
				( Spi_ReadIB(SPI_TEST_CHANNEL_0, &rx) == E_OK ), 
				EE_ASSERT_SPI_POLL_SEQ_OK);

	    EE_assert(EE_ASSERT_SPI_POLL_READ_VALIDATE, 
	    		( rx == SPI_TX_RX_DATA + test ), EE_ASSERT_SPI_POLL_READ_IB);
	}

	test++;

	EE_assert(EE_ASSERT_SPI_EB_INT_MODE, 
			( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ), 
			EE_ASSERT_SPI_POLL_READ_IB);

	tx = SPI_TX_RX_DATA + test;
	rx = SPI_TX_RX_DATA_NULL;

	EE_assert(EE_ASSERT_SPI_EB_INT_SETUP, 
			(Spi_SetupEB(SPI_TEST_CHANNEL_0_EB, &tx, &rx, SPI_EB_LENGTH) == E_OK),
			EE_ASSERT_SPI_EB_INT_MODE);

	EE_assert(EE_ASSERT_SPI_EB_INT_ASYNC_TX, 
			(Spi_AsyncTransmit(SPI_TEST_SEQ_0_EB) == E_OK), 
			EE_ASSERT_SPI_EB_INT_SETUP);

	while (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB) == SPI_SEQ_PENDING) { ; }

	if (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB) == SPI_SEQ_OK) {

		EE_assert(EE_ASSERT_SPI_EB_INT_VALIDATE, (rx == SPI_TX_RX_DATA + test), 
				EE_ASSERT_SPI_EB_INT_ASYNC_TX);
	}

	test++;

	EE_assert(EE_ASSERT_SPI_EB_POLL_MODE,
			(Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK), 
			EE_ASSERT_SPI_EB_INT_VALIDATE);

	tx = SPI_TX_RX_DATA + test;
	rx = SPI_TX_RX_DATA_NULL;

	EE_assert(EE_ASSERT_SPI_EB_POLL_SETUP, 
			(Spi_SetupEB(SPI_TEST_CHANNEL_0_EB, &tx, &rx, SPI_EB_LENGTH) == E_OK), 
			EE_ASSERT_SPI_EB_POLL_MODE);

	EE_assert(EE_ASSERT_SPI_EB_POLL_ASYNC_TX, 
			(Spi_AsyncTransmit(SPI_TEST_SEQ_0_EB) == E_OK), 
			EE_ASSERT_SPI_EB_POLL_SETUP);

	while (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB) == SPI_SEQ_PENDING) {
		
		Spi_MainFunction_Handling();
	}

	if (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB) == SPI_SEQ_OK) {

		EE_assert(EE_ASSERT_SPI_EB_POLL_VALIDATE, (rx == SPI_TX_RX_DATA + test), 
				EE_ASSERT_SPI_EB_POLL_ASYNC_TX);
	}

	test++;

	tx = SPI_TX_RX_DATA + test;
	rx = SPI_TX_RX_DATA_NULL;

	EE_assert(EE_ASSERT_SPI_SYNC_WRITE_IB, 
			( Spi_WriteIB(SPI_TEST_CHANNEL_0, &tx) == E_OK ), 
			EE_ASSERT_SPI_EB_POLL_VALIDATE);

	EE_assert(EE_ASSERT_SPI_SYNC_TX, 
			(Spi_SyncTransmit(SPI_TEST_SEQ_0_SYNC) == E_OK), 
			EE_ASSERT_SPI_SYNC_WRITE_IB);

	EE_assert(EE_ASSERT_SPI_SYNC_JOB_OK, 
			(Spi_GetJobResult(SPI_TEST_JOB_0_SYNC) == SPI_JOB_OK), 
			EE_ASSERT_SPI_SYNC_TX);

	EE_assert(EE_ASSERT_SPI_SYNC_SEQ_OK, 
			(Spi_GetSequenceResult(SPI_TEST_SEQ_0_SYNC) == SPI_SEQ_OK), 
			EE_ASSERT_SPI_SYNC_JOB_OK);

	if (Spi_GetSequenceResult(SPI_TEST_SEQ_0_SYNC) == SPI_SEQ_OK) {

		EE_assert(EE_ASSERT_SPI_SYNC_READ_IB, 
				(Spi_ReadIB(SPI_TEST_CHANNEL_0, &rx) == E_OK),
	      EE_ASSERT_SPI_SYNC_SEQ_OK);

	    EE_assert(EE_ASSERT_SPI_SYNC_READ_VALIDATE, 
	    		(rx == SPI_TX_RX_DATA + test), EE_ASSERT_SPI_SYNC_READ_IB);
	}

	test++;

	tx = SPI_TX_RX_DATA + test;
	rx = SPI_TX_RX_DATA_NULL;

	EE_assert(EE_ASSERT_SPI_EB_SYNC_SETUP, 
			(Spi_SetupEB(SPI_TEST_CHANNEL_0_EB, &tx, &rx, SPI_EB_LENGTH) == E_OK), 
			EE_ASSERT_SPI_SYNC_READ_VALIDATE);

	EE_assert(EE_ASSERT_SPI_EB_SYNC_TX, 
			(Spi_SyncTransmit(SPI_TEST_SEQ_0_EB_SYNC) == E_OK), 
			EE_ASSERT_SPI_EB_SYNC_SETUP);

	EE_assert(EE_ASSERT_SPI_EB_SYNC_JOB_OK, 
			(Spi_GetJobResult(SPI_TEST_JOB_0_EB_SYNC) == SPI_JOB_OK), 
			EE_ASSERT_SPI_EB_SYNC_TX);

	EE_assert(EE_ASSERT_SPI_EB_SYNC_SEQ_OK, 
			(Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB_SYNC) == SPI_SEQ_OK), 
			EE_ASSERT_SPI_EB_SYNC_JOB_OK);

	if (Spi_GetSequenceResult(SPI_TEST_SEQ_0_EB_SYNC) == SPI_SEQ_OK) {

		EE_assert(EE_ASSERT_SPI_EB_SYNC_VALIDATE, (rx == SPI_TX_RX_DATA + test), 
				EE_ASSERT_SPI_EB_SYNC_SEQ_OK);
	}

	EE_assert(EE_ASSERT_SPI_DEINIT, (Spi_DeInit() == E_OK), 
			EE_ASSERT_SPI_EB_SYNC_VALIDATE);

	EE_assert_range(EE_ASSERT_FIN, ( Spi_GetStatus() == SPI_UNINIT ), 
			EE_ASSERT_SPI_DEINIT);

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