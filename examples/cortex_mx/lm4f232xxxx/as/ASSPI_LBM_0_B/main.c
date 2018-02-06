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
 * Simple project to test the AUTOSAR SPI Handler/Driver:
 * - 1 Sequence
 *   - 1 Job
 *     - 1 Channel
 *       - Max 3 bytes
 * - All 4 SSI Hardware Unit
 *   - Loop-back Mode
 *   - 2 Units Asynchronous
 *   - 2 Units Synchronous
 * - Write/AsyncTransmit/Read (IB)
 *   - Interrupt Mode
 *   - Polling Mode
 * - Setup/AsyncTransmit (EB)
 *   - Interrupt Mode
 *   - Polling Mode
 * - SyncTransmit/Read (IB)
 * - Setup/SyncTransmit (EB)
 *   - No Source Buffer.
 *
 * Author: 2012,  Giuseppe Serano
 */

#include "Dio.h"
#include "Dma.h"
#include "Mcu.h"
#include "Port.h"
#include "Spi.h"
#include "test/assert/inc/ee_assert.h"

#include <string.h>

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,			/*  0 */
  EE_ASSERT_INIT,			/*  1 */
  EE_ASSERT_VERSION,			/*  2 */
  EE_ASSERT_CLOCK_INIT,			/*  3 */
  EE_ASSERT_PLL_LOCKED,			/*  4 */
  EE_ASSERT_DMA_INIT,			/*  5 */
  EE_ASSERT_SPI_UNINIT,			/*  6 */
  EE_ASSERT_SPI_INIT,			/*  7 */
  EE_ASSERT_SPI_INTERRUPT_MODE,		/*  8 */
  EE_ASSERT_SPI_INT_WRITE_IB,		/*  9 */
  EE_ASSERT_SPI_INT_ASYNC_TX,		/* 10 */
  EE_ASSERT_SPI_INT_JOB_END,		/* 11 */
  EE_ASSERT_SPI_INT_JOB_OK,		/* 12 */
  EE_ASSERT_SPI_INT_SEQ_END,		/* 13 */
  EE_ASSERT_SPI_INT_SEQ_OK,		/* 14 */
  EE_ASSERT_SPI_INT_READ_IB,		/* 15 */
  EE_ASSERT_SPI_INT_READ_VALIDATE,	/* 16 */
  EE_ASSERT_SPI_POLLING_MODE,		/* 17 */
  EE_ASSERT_SPI_POLL_WRITE_IB,		/* 18 */
  EE_ASSERT_SPI_POLL_ASYNC_TX,		/* 19 */
  EE_ASSERT_SPI_POLL_JOB_END,		/* 20 */
  EE_ASSERT_SPI_POLL_JOB_OK,		/* 21 */
  EE_ASSERT_SPI_POLL_SEQ_END,		/* 22 */
  EE_ASSERT_SPI_POLL_SEQ_OK,		/* 23 */
  EE_ASSERT_SPI_POLL_READ_IB,		/* 24 */
  EE_ASSERT_SPI_POLL_READ_VALIDATE,	/* 25 */
  EE_ASSERT_SPI_EB_INT_MODE,		/* 26 */
  EE_ASSERT_SPI_EB_INT_SETUP,		/* 27 */
  EE_ASSERT_SPI_EB_INT_ASYNC_TX,	/* 28 */
  EE_ASSERT_SPI_EB_INT_JOB_END,		/* 29 */
  EE_ASSERT_SPI_EB_INT_JOB_OK,		/* 30 */
  EE_ASSERT_SPI_EB_INT_SEQ_END,		/* 31 */
  EE_ASSERT_SPI_EB_INT_SEQ_OK,		/* 32 */
  EE_ASSERT_SPI_EB_INT_VALIDATE,	/* 33 */
  EE_ASSERT_SPI_EB_POLL_MODE,		/* 34 */
  EE_ASSERT_SPI_EB_POLL_SETUP,		/* 35 */
  EE_ASSERT_SPI_EB_POLL_ASYNC_TX,	/* 36 */
  EE_ASSERT_SPI_EB_POLL_JOB_END,	/* 37 */
  EE_ASSERT_SPI_EB_POLL_JOB_OK,		/* 38 */
  EE_ASSERT_SPI_EB_POLL_SEQ_END,	/* 39 */
  EE_ASSERT_SPI_EB_POLL_SEQ_OK,		/* 40 */
  EE_ASSERT_SPI_EB_POLL_VALIDATE,	/* 41 */
  EE_ASSERT_SPI_SYNC_WRITE_IB,		/* 42 */
  EE_ASSERT_SPI_SYNC_TX,		/* 43 */
  EE_ASSERT_SPI_SYNC_JOB_OK,		/* 44 */
  EE_ASSERT_SPI_SYNC_SEQ_OK,		/* 45 */
  EE_ASSERT_SPI_SYNC_READ_IB,		/* 46 */
  EE_ASSERT_SPI_SYNC_READ_VALIDATE,	/* 47 */
  EE_ASSERT_SPI_EB_SYNC_SETUP,		/* 48 */
  EE_ASSERT_SPI_EB_SYNC_TX,		/* 49 */
  EE_ASSERT_SPI_EB_SYNC_JOB_OK,		/* 50 */
  EE_ASSERT_SPI_EB_SYNC_SEQ_OK,		/* 51 */
  EE_ASSERT_SPI_EB_SYNC_VALIDATE,	/* 52 */
  EE_ASSERT_SPI_DEINIT,			/* 53 */
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

  switch ( test ) {

    case 0:
      EE_assert( EE_ASSERT_SPI_INT_JOB_OK, TRUE, EE_ASSERT_SPI_INT_JOB_END );
      break;

    case 1:
      EE_assert( EE_ASSERT_SPI_POLL_JOB_OK, TRUE, EE_ASSERT_SPI_POLL_JOB_END );
      break;

    case 2:
      EE_assert(
	EE_ASSERT_SPI_EB_INT_JOB_OK, TRUE, EE_ASSERT_SPI_EB_INT_JOB_END
      );
      break;

    case 3:
      EE_assert(
	EE_ASSERT_SPI_EB_POLL_JOB_OK, TRUE, EE_ASSERT_SPI_EB_POLL_JOB_END
      );
      break;

  }

}

/*
 * LBM Job 3 End Notification.
 */
void Spi_LBMJob3EndNotification()
{

  switch ( test ) {

    case 0:
      EE_assert( EE_ASSERT_SPI_INT_JOB_END, TRUE, EE_ASSERT_SPI_INT_WRITE_IB );
      if ( Spi_GetJobResult(SPI_LBM_JOB_3) == SPI_JOB_OK ) {
	ActivateTask(TaskJobOk);
      }
      else {
	ActivateTask(TaskJobError);
      }
      break;

    case 1:
      EE_assert(
	EE_ASSERT_SPI_POLL_JOB_END, TRUE, EE_ASSERT_SPI_POLL_ASYNC_TX
      );
      if ( Spi_GetJobResult(SPI_LBM_JOB_3) == SPI_JOB_OK ) {
	ActivateTask(TaskJobOk);
      }
      else {
	ActivateTask(TaskJobError);
      }
      break;

    case 2:
      EE_assert(
	EE_ASSERT_SPI_EB_INT_JOB_END, TRUE, EE_ASSERT_SPI_EB_INT_SETUP
      );
      if ( Spi_GetJobResult(SPI_LBM_JOB_3_EB) == SPI_JOB_OK ) {
	ActivateTask(TaskJobOk);
      }
      else {
	ActivateTask(TaskJobError);
      }
      break;

    case 3:
      EE_assert(
	EE_ASSERT_SPI_EB_POLL_JOB_END, TRUE, EE_ASSERT_SPI_EB_POLL_ASYNC_TX
      );
      if ( Spi_GetJobResult(SPI_LBM_JOB_3_EB) == SPI_JOB_OK ) {
	ActivateTask(TaskJobOk);
      }
      else {
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

  switch ( test ) {

    case 0:
      EE_assert( EE_ASSERT_SPI_INT_SEQ_OK, TRUE, EE_ASSERT_SPI_INT_SEQ_END );
      break;

    case 1:
      EE_assert( EE_ASSERT_SPI_POLL_SEQ_OK, TRUE, EE_ASSERT_SPI_POLL_SEQ_END );
      break;

    case 2:
      EE_assert(
	EE_ASSERT_SPI_EB_INT_SEQ_OK, TRUE, EE_ASSERT_SPI_EB_INT_SEQ_END
      );
      break;

    case 3:
      EE_assert(
	EE_ASSERT_SPI_EB_POLL_SEQ_OK, TRUE, EE_ASSERT_SPI_EB_POLL_SEQ_END
      );
      break;

  }

}

/*
 * LBM Sequence 3 End Notification.
 */
void Spi_LBMSeq3EndNotification()
{

  switch ( test ) {

    case 0:
      EE_assert( EE_ASSERT_SPI_INT_SEQ_END, TRUE, EE_ASSERT_SPI_INT_JOB_END );
      if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3) == SPI_SEQ_OK ) {
	ActivateTask(TaskSeqOk);
      }
      else {
	ActivateTask(TaskSeqError);
      }
      break;

    case 1:
      EE_assert( EE_ASSERT_SPI_POLL_SEQ_END, TRUE, EE_ASSERT_SPI_POLL_JOB_END );
      if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3) == SPI_SEQ_OK ) {
	ActivateTask(TaskSeqOk);
      }
      else {
	ActivateTask(TaskSeqError);
      }
      break;

    case 2:
      EE_assert(
	EE_ASSERT_SPI_EB_INT_SEQ_END, TRUE, EE_ASSERT_SPI_EB_INT_JOB_END
      );
      if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB) == SPI_SEQ_OK ) {
	ActivateTask(TaskSeqOk);
      }
      else {
	ActivateTask(TaskSeqError);
      }
      break;

    case 3:
      EE_assert(
	EE_ASSERT_SPI_EB_POLL_SEQ_END, TRUE, EE_ASSERT_SPI_EB_POLL_JOB_END
      );
      if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB) == SPI_SEQ_OK ) {
	ActivateTask(TaskSeqOk);
      }
      else {
	ActivateTask(TaskSeqError);
      }
      break;

  }

}

#define	MCU_PLL_LOCK_MAX_ATTEMPTS	0x0000000A

#define	SPI_TX_RX_DATA_NULL	0x00U

void flush_buff(Spi_DataType *buff)
{

  size_t	i;

  for (i = 0; i < SPI_LBM_CHANNEL_2_IB_N_BUFFERS; i++) {

    buff[i] = SPI_TX_RX_DATA_NULL;

  }

}

boolean cmp_buff(Spi_DataType *buff, Spi_NumberOfElementsType *len)
{

  size_t	i;
  boolean	rv = TRUE;

  if ( len > SPI_LBM_CHANNEL_2_IB_N_BUFFERS ) {

    rv = FALSE;

  }
  else {

    for (i = 0; (i < len) && rv; i++) {

      if ( buff1[i] != SPI_LBM_CHANNEL_2_DEFAULT_DATA ) {

	rv = FALSE;

      }

    }

    for (; (i < SPI_LBM_CHANNEL_2_IB_N_BUFFERS) && rv; i++) {

      if ( buff1[i] != SPI_TX_RX_DATA_NULL ) {

	rv = FALSE;

      }

    }

  }

  return rv;

}

Spi_DataType	rx[SPI_LBM_CHANNEL_2_IB_N_BUFFERS];

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

  EE_assert(
    EE_ASSERT_VERSION,
    (
      (version.vendorID == 0) &&
      (version.moduleID == 83) &&
      (version.sw_major_version == 1) &&
      (version.sw_minor_version == 0) &&
      (version.sw_patch_version == 0)
    ),
    EE_ASSERT_INIT
  );

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  if ( Mcu_InitClock(MCU_CLOCK_MODE_PRIOSC_4_PLL) != E_OK ) {

    /* Clock Initialization Error. */
    Mcu_PerformReset();

  }

  EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

  counter = 0;
  while (
    ( Mcu_GetPllStatus() != MCU_PLL_LOCKED ) &&
    ( counter < MCU_PLL_LOCK_MAX_ATTEMPTS )
  ) {
    counter++;
  }

  if ( counter >= MCU_PLL_LOCK_MAX_ATTEMPTS ) {

    /* PLL Lock Error. */
    Mcu_PerformReset();

  }

  EE_assert(
    EE_ASSERT_PLL_LOCKED,
    Mcu_GetPllStatus() == MCU_PLL_LOCKED,
    EE_ASSERT_CLOCK_INIT
  );

  Mcu_DistributePllClock();

  Port_Init(PORT_CONFIG_DEFAULT_PTR);

  Dio_Init(DIO_CONFIG_USER_LED_PTR);

  Dma_Init(DMA_CONFIG_SPI_PTR);

  EE_assert(
    EE_ASSERT_DMA_INIT,
    ( Dma_GetStatus() == SPI_IDLE ),
    EE_ASSERT_PLL_LOCKED
  );


  EE_assert(
    EE_ASSERT_SPI_UNINIT,
    ( Spi_GetStatus() == SPI_UNINIT ),
    EE_ASSERT_DMA_INIT
  );

  Spi_Init(SPI_CONFIG_LBM_PTR);

  EE_assert(
    EE_ASSERT_SPI_INIT, ( Spi_GetStatus() == SPI_IDLE ), EE_ASSERT_SPI_UNINIT
  );

  test = 0;

  EE_assert(
    EE_ASSERT_SPI_INTERRUPT_MODE,
    ( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ),
    EE_ASSERT_SPI_INIT
  );

  flush_buff(rx);

  EE_assert(
    EE_ASSERT_SPI_INT_WRITE_IB,
    TRUE,
    EE_ASSERT_SPI_INTERRUPT_MODE
  );

  EE_assert(
    EE_ASSERT_SPI_INT_ASYNC_TX,
    ( Spi_AsyncTransmit(SPI_LBM_SEQ_3) == E_OK ),
    EE_ASSERT_SPI_INT_WRITE_IB
  );

  while ( Spi_GetSequenceResult(SPI_LBM_SEQ_3) == SPI_SEQ_PENDING ) {
    ;
  }

  if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_INT_READ_IB,
      ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx) == E_OK ),
      EE_ASSERT_SPI_INT_SEQ_OK
    );

    EE_assert(
      EE_ASSERT_SPI_INT_READ_VALIDATE,
      cmp_buff(rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS),
      EE_ASSERT_SPI_INT_READ_IB
    );

  }

  test++;

  EE_assert(
    EE_ASSERT_SPI_POLLING_MODE,
    ( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ),
    EE_ASSERT_SPI_INT_READ_VALIDATE
  );

  flush_buff(rx);

  EE_assert(
    EE_ASSERT_SPI_POLL_WRITE_IB,
    TRUE,
    EE_ASSERT_SPI_POLLING_MODE
  );

  EE_assert(
    EE_ASSERT_SPI_POLL_ASYNC_TX,
    ( Spi_AsyncTransmit(SPI_LBM_SEQ_3) == E_OK ),
    EE_ASSERT_SPI_POLL_WRITE_IB
  );

  while ( Spi_GetSequenceResult(SPI_LBM_SEQ_3) == SPI_SEQ_PENDING ) {

    Spi_MainFunction_Handling();

  }

  if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_POLL_READ_IB,
      ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx) == E_OK ),
      EE_ASSERT_SPI_POLL_SEQ_OK
    );

    EE_assert(
      EE_ASSERT_SPI_POLL_READ_VALIDATE,
      cmp_buff(rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS),
      EE_ASSERT_SPI_POLL_READ_IB
    );

  }

  test++;

  EE_assert(
    EE_ASSERT_SPI_EB_INT_MODE,
    ( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ),
    EE_ASSERT_SPI_POLL_READ_IB
  );

  flush_buff(rx);

  EE_assert(
    EE_ASSERT_SPI_EB_INT_SETUP,
    (
      Spi_SetupEB(
	SPI_LBM_CHANNEL_2_EB, NULL_PTR, rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS
      ) == E_OK
    ),
    EE_ASSERT_SPI_EB_INT_MODE
  );

  EE_assert(
    EE_ASSERT_SPI_EB_INT_ASYNC_TX,
    ( Spi_AsyncTransmit(SPI_LBM_SEQ_3_EB) == E_OK ),
    EE_ASSERT_SPI_EB_INT_SETUP
  );

  while ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB) == SPI_SEQ_PENDING ) {
    ;
  }

  if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_EB_INT_VALIDATE,
      cmp_buff(rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS),
      EE_ASSERT_SPI_EB_INT_ASYNC_TX
    );

  }

  test++;

  EE_assert(
    EE_ASSERT_SPI_EB_POLL_MODE,
    ( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ),
    EE_ASSERT_SPI_EB_INT_VALIDATE
  );

  flush_buff(rx);

  EE_assert(
    EE_ASSERT_SPI_EB_POLL_SETUP,
    (
      Spi_SetupEB(
	SPI_LBM_CHANNEL_2_EB, NULL_PTR, rx,  SPI_LBM_CHANNEL_2_IB_N_BUFFERS - 1
      ) == E_OK
    ),
    EE_ASSERT_SPI_EB_POLL_MODE
  );

  EE_assert(
    EE_ASSERT_SPI_EB_POLL_ASYNC_TX,
    ( Spi_AsyncTransmit(SPI_LBM_SEQ_3_EB) == E_OK ),
    EE_ASSERT_SPI_EB_POLL_SETUP
  );

  while ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB) == SPI_SEQ_PENDING ) {

    Spi_MainFunction_Handling();

  }

  if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_EB_POLL_VALIDATE,
      cmp_buff(rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS - 1),
      EE_ASSERT_SPI_EB_POLL_ASYNC_TX
    );

  }

  test++;

  flush_buff(rx);

  EE_assert(
    EE_ASSERT_SPI_SYNC_WRITE_IB,
    TRUE,
    EE_ASSERT_SPI_EB_POLL_VALIDATE
  );

  EE_assert(
    EE_ASSERT_SPI_SYNC_TX,
    ( Spi_SyncTransmit(SPI_LBM_SEQ_3_SYNC) == E_OK ),
    EE_ASSERT_SPI_SYNC_WRITE_IB
  );

  EE_assert(
    EE_ASSERT_SPI_SYNC_JOB_OK,
    ( Spi_GetJobResult(SPI_LBM_JOB_3_SYNC) == SPI_JOB_OK ),
    EE_ASSERT_SPI_SYNC_TX
  );

  EE_assert(
    EE_ASSERT_SPI_SYNC_SEQ_OK,
    ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_SYNC) == SPI_SEQ_OK ),
    EE_ASSERT_SPI_SYNC_JOB_OK
  );

  if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_SYNC) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_SYNC_READ_IB,
      ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx) == E_OK ),
      EE_ASSERT_SPI_SYNC_SEQ_OK
    );

    EE_assert(
      EE_ASSERT_SPI_SYNC_READ_VALIDATE,
      cmp_buff(rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS),
      EE_ASSERT_SPI_SYNC_READ_IB
    );

  }

  test++;

  flush_buff(rx);

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_SETUP,
    ( 
      Spi_SetupEB(
	SPI_LBM_CHANNEL_2_EB, NULL_PTR, rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS - 2
      ) == E_OK
    ),
    EE_ASSERT_SPI_SYNC_READ_VALIDATE
  );

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_TX,
    ( Spi_SyncTransmit(SPI_LBM_SEQ_3_EB_SYNC) == E_OK ),
    EE_ASSERT_SPI_EB_SYNC_SETUP
  );

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_JOB_OK,
    ( Spi_GetJobResult(SPI_LBM_JOB_0_EB_SYNC) == SPI_JOB_OK ),
    EE_ASSERT_SPI_EB_SYNC_TX
  );

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_SEQ_OK,
    ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB_SYNC) == SPI_SEQ_OK ),
    EE_ASSERT_SPI_EB_SYNC_JOB_OK
  );

  if ( Spi_GetSequenceResult(SPI_LBM_SEQ_3_EB_SYNC) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_EB_SYNC_VALIDATE,
      cmp_buff(rx, SPI_LBM_CHANNEL_2_IB_N_BUFFERS - 2),
      EE_ASSERT_SPI_EB_SYNC_SEQ_OK
    );

  }

  EE_assert(
    EE_ASSERT_SPI_DEINIT,
    ( Spi_DeInit() == E_OK ),
    EE_ASSERT_SPI_EB_SYNC_VALIDATE
  );

  EE_assert_range(
    EE_ASSERT_FIN,
    ( Spi_GetStatus() == SPI_UNINIT ),
    EE_ASSERT_SPI_DEINIT
  );

  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {
    while (counter % 100000) counter++;

    lvl = Dio_ReadChannelGroup(DIO_CHANNEL_GROUP_USER_LED);

    if (lvl == STD_HIGH)
      Dio_WriteChannelGroup(DIO_CHANNEL_GROUP_USER_LED, STD_LOW);
    else
      Dio_WriteChannelGroup(DIO_CHANNEL_GROUP_USER_LED, STD_HIGH);

    counter++;
  }

}
