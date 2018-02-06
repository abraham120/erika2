/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Simple project to test SCI Driver interrupt operational mode.
 *
 * Author: 2011,  Giuseppe Serano
 */

#include "Dio.h"
#include "Mcu.h"
#include "Port.h"
#include "Sci.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef	TRUE
#define	TRUE	1
#endif

#define	ASCII_NULL	0x00
#define	ASCII_BELL	0x07

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_VERSION,
  EE_ASSERT_CLOCK_INIT,
  EE_ASSERT_PLL_LOCKED,
  EE_ASSERT_SCI_INIT,
  EE_ASSERT_RX_NOTIF_FIRED,
  EE_ASSERT_RX_OK_TASK_FIRED,
  EE_ASSERT_TX_NOTIF_FIRED,
  EE_ASSERT_TX_OK_TASK_FIRED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile int TxNotifCntr = 0;
volatile int TxOkCntr = 0;
volatile int RxNotifCntr = 0;
volatile int RxOkCntr = 0;
volatile int TxErrNotifCntr = 0;
volatile int TxErrCntr = 0;
volatile int RxErrNotifCntr = 0;
volatile int RxErrCntr = 0;

/* Stack Pointers */
volatile EE_UREG main_sp = 0;
volatile EE_UREG bg_sp = 0;

volatile EE_UREG counter = 0;
/*
 * TASK BackGround
 */
TASK(BackGround)
{

  EE_UREG curr_sp;

  while(1) {

    curr_sp = __current_sp();
    if (curr_sp != bg_sp) {
      bg_sp = curr_sp;
    }

    while ( counter % 100000 ) {
      counter++;
    }

    Dio_FlipChannel(DIO_CHANNEL_USER_LED);

    counter++;

  }

}

#ifdef	__FP__
void TerminateTask(void)
{
}

#define	OSDEFAULTAPPMODE	0
void StartOS(int appmode)
{
  ActivateTask(BackGround);
}
#endif

/*
 * SCI Channel 4 Transmission Notifications Callback.
 */
void Sci_TxNotifications_Channel_4(void)
{

  TxNotifCntr++;
  if (TxNotifCntr == 1)
    EE_assert(
      EE_ASSERT_TX_NOTIF_FIRED, TxNotifCntr == 1, EE_ASSERT_RX_OK_TASK_FIRED
    );

  ActivateTask(TaskTxOk);
}

/*
 * TASK Trasmission OK
 */
TASK(TaskTxOk)
{

  TxOkCntr++;
  if(TxOkCntr == 1)
    EE_assert(
      EE_ASSERT_TX_OK_TASK_FIRED, TxNotifCntr == 1, EE_ASSERT_TX_NOTIF_FIRED
    );

  TerminateTask();

}

/*
 * SCI Channel 4 Reception Notifications Callback.
 */
void Sci_RxNotifications_Channel_4(void)
{

  RxNotifCntr++;
  if (RxNotifCntr == 1)
    EE_assert(EE_ASSERT_RX_NOTIF_FIRED, RxNotifCntr == 1, EE_ASSERT_SCI_INIT);

  ActivateTask(TaskRxOk);

}

/*
 * TASK Reception OK
 */
TASK(TaskRxOk)
{
  uint8	RxData = ASCII_NULL;
  uint8	TxData = ASCII_BELL;

  RxOkCntr++;
  if(RxOkCntr == 1)
    EE_assert(
      EE_ASSERT_RX_OK_TASK_FIRED, RxNotifCntr == 1, EE_ASSERT_RX_NOTIF_FIRED
    );

  if ( Sci_ReadRxData(SCI_CHANNEL_4, &RxData) == E_OK )
    TxData = RxData;

  Sci_WriteTxData(SCI_CHANNEL_4, TxData);

  TerminateTask();

}

/*
 * SCI Channel 4 Transmission Errors Notifications Callback.
 */
void Sci_TxErrNotifications_Channel_4(void)
{

  TxErrNotifCntr++;

  ActivateTask(TaskTxErr);

}

/*
 * TASK Transmission Errors
 */
TASK(TaskTxErr)
{

  uint8	TxData = ASCII_BELL;

  TxErrCntr++;

  Sci_WriteTxData(SCI_CHANNEL_4, TxData);

  TerminateTask();

}

/*
 * SCI Channel 4 Reception Errors Notifications Callback.
 */
void Sci_RxErrNotifications_Channel_4(void)
{

  RxErrNotifCntr++;

  ActivateTask(TaskRxErr);

}

/*
 * TASK Reception Errors
 */
TASK(TaskRxErr)
{

  uint8	TxData = ASCII_BELL;

  RxErrCntr++;

  Sci_WriteTxData(SCI_CHANNEL_4, TxData);

  TerminateTask();

}

volatile Mcu_RawResetType	RawReset;

/*
 * MAIN TASK
 */
int main(void)
{

  EE_UREG curr_sp;

  Std_VersionInfoType	version;

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  Sci_GetVersionInfo(&version);

  EE_assert(
    EE_ASSERT_VERSION,
    (
      (version.vendorID == 0) &&
      (version.moduleID == 0xFFFF) &&
      (version.sw_major_version == 1) &&
      (version.sw_minor_version == 0) &&
      (version.sw_patch_version == 0)
    ),
    EE_ASSERT_INIT
  );

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  RawReset = Mcu_GetResetRawValue();

  if ( Mcu_InitClock(MCU_CLOCK_MODE_MOSC_4_PLL) == E_NOT_OK ) {

    Mcu_PerformReset();

  }

  EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

  while ( Mcu_GetPllStatus() != MCU_PLL_LOCKED );

  EE_assert(
    EE_ASSERT_PLL_LOCKED,
    Mcu_GetPllStatus() == MCU_PLL_LOCKED,
    EE_ASSERT_CLOCK_INIT
  );

  Mcu_DistributePllClock();

  Port_Init(PORT_CONFIG_SCI_PTR);

  Dio_Init(DIO_CONFIG_DEFAULT_PTR);

  Sci_Init(SCI_CONFIG_DEFAULT_PTR);

  EE_assert(EE_ASSERT_SCI_INIT, TRUE, EE_ASSERT_PLL_LOCKED);

  Sci_EnableNotifications(SCI_CHANNEL_4);

  StartOS(OSDEFAULTAPPMODE);

  while(
    !(
      TxNotifCntr || TxOkCntr || RxNotifCntr || RxOkCntr ||
      TxErrNotifCntr || TxErrCntr || RxErrNotifCntr || RxErrCntr
    )
  );

  EE_assert_range(
    EE_ASSERT_FIN,
    (TxNotifCntr || TxOkCntr || RxNotifCntr || RxOkCntr) &&
    !(TxErrNotifCntr || TxErrCntr || RxErrNotifCntr || RxErrCntr),
    EE_ASSERT_TX_OK_TASK_FIRED
  );
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = __current_sp();
    if (curr_sp != main_sp) {
      main_sp = curr_sp;
    }

  }

}
