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
 * Simple project to to estimate the SPI Handler/Driver MINIMAL services:
 * - 1 Sequence
 *   - 1 Job
 *     - 1 Channel
 *       - One Byte Only.
 * - 1 SSI Hardware Modules
 *   - Synchronous
 *   - Loop-back Mode
 * - Setup/SyncTransmit (EB)
 *
 * Author: 2012,  Giuseppe Serano
 */

#include "Dio.h"
#include "Dma.h"
#include "Mcu.h"
#include "Port.h"
#include "Spi.h"
#include "test/assert/inc/ee_assert.h"

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,			/*  0 */
  EE_ASSERT_INIT,			/*  1 */
  EE_ASSERT_SPI_INIT,			/*  2 */
  EE_ASSERT_SPI_EB_SYNC_SETUP,		/*  3 */
  EE_ASSERT_SPI_EB_SYNC_TX,		/*  4 */
  EE_ASSERT_SPI_EB_SYNC_JOB_OK,		/*  5 */
  EE_ASSERT_SPI_EB_SYNC_SEQ_OK,		/*  6 */
  EE_ASSERT_SPI_EB_SYNC_VALIDATE,	/*  7 */
  EE_ASSERT_SPI_DEINIT,			/*  8 */
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/*
 * TASK 1
 */
TASK(Task1)
{

  /* Nothing To Do... */

}

#define	SPI_TX_RX_DATA		0xA5U
#define	SPI_TX_RX_DATA_NULL	0x00U
#define	SPI_EB_LENGTH		0x01U

Spi_DataType	rx;
Spi_DataType	tx;

/*
 * MAIN TASK
 */
int main(void)
{

  Dio_PortLevelType	lvl;

  counter = 0;

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  Port_Init(PORT_CONFIG_DEFAULT_PTR);

  Dio_Init(DIO_CONFIG_DEFAULT_PTR);

  Dma_Init(DMA_CONFIG_SPI_PTR);

  Spi_Init(SPI_CONFIG_DEFAULT_PTR);

  EE_assert(
    EE_ASSERT_SPI_INIT, ( Spi_GetStatus() == SPI_IDLE ), EE_ASSERT_INIT
  );

  tx = SPI_TX_RX_DATA;
  rx = SPI_TX_RX_DATA_NULL;

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_SETUP,
    ( Spi_SetupEB(SPI_TEST_CHANNEL_0, &tx, &rx, SPI_EB_LENGTH) == E_OK ),
    EE_ASSERT_SPI_INIT
  );

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_TX,
    ( Spi_SyncTransmit(SPI_TEST_SEQ_0) == E_OK ),
    EE_ASSERT_SPI_EB_SYNC_SETUP
  );

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_JOB_OK,
    ( Spi_GetJobResult(SPI_TEST_JOB_0) == SPI_JOB_OK ),
    EE_ASSERT_SPI_EB_SYNC_TX
  );

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_SEQ_OK,
    ( Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_OK ),
    EE_ASSERT_SPI_EB_SYNC_JOB_OK
  );

  if ( Spi_GetSequenceResult(SPI_TEST_SEQ_0) == SPI_SEQ_OK ) {

    EE_assert(
      EE_ASSERT_SPI_EB_SYNC_VALIDATE,
      ( rx == SPI_TX_RX_DATA ),
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

    lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED);

    if (lvl == STD_HIGH)
      Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_LOW);
    else
      Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_HIGH);

    counter++;
  }

}
