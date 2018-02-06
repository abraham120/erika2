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
 * Simple banchmark project for AUTOSAR "like" SCI Driver.
 *
 * Author: 2013,  Giuseppe Serano
 */

#include "ee.h"
#include "Dio.h"
#include "Mcu.h"
#include "Port.h"
#include "Sci.h"

#define	ASCII_NULL	0x00
#define	ASCII_BELL	0x07

/* Counters */
volatile int counter = 0;
volatile int TxNotifCntr = 0;
volatile int TxOkCntr = 0;
volatile int RxNotifCntr = 0;
volatile int RxOkCntr = 0;
volatile int TxErrNotifCntr = 0;
volatile int TxErrCntr = 0;
volatile int RxErrNotifCntr = 0;
volatile int RxErrCntr = 0;

/* reset reason */
volatile Mcu_RawResetType reset = 0;

/*
 * SCI Channel 4 Transmission Notifications Callback.
 */
void Sci_TxNotifications_Channel_4(void)
{

  TxNotifCntr++;

  ActivateTask(TaskTxOk);

}

/*
 * TASK Trasmission OK
 */
TASK(TaskTxOk)
{

  Dio_PortLevelType	lvl;

  TxOkCntr++;

  lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED);

  if (lvl == STD_HIGH)
    Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_LOW);
  else
    Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_HIGH);

}

/*
 * SCI Channel 4 Reception Notifications Callback.
 */
void Sci_RxNotifications_Channel_4(void)
{

  RxNotifCntr++;

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

  if ( Sci_ReadRxData(SCI_CHANNEL_4, &RxData) == E_OK ) {

    TxData = RxData;

  }

  Sci_WriteTxData(SCI_CHANNEL_4, TxData);

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

}

#define	PLL_LOCK_ATTEMPTS	1000

/*
 * MAIN TASK
 */
int main(void)
{

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  reset = Mcu_GetResetRawValue();

  if ( reset & SYSCTL_RESC_EXT ) {

    Mcu_InitClock(MCU_CLOCK_MODE_MOSC_4_PLL);

    while (
      (Mcu_GetPllStatus() != MCU_PLL_LOCKED) && (counter < PLL_LOCK_ATTEMPTS)
    ) {
      counter++;
    }

    if ( Mcu_GetPllStatus() == MCU_PLL_LOCKED ) {
  
      Mcu_DistributePllClock();

    }
    else {

      /* Forever loop: PLL NOT LOCKED!!! */
      for (;;)
      {
	;
      }

    }

    counter = 0;

  }
  else {

    Mcu_InitClock(MCU_CLOCK_MODE_NORMAL);

  }

  Port_Init(PORT_CONFIG_SCI_PTR);

  Dio_Init(DIO_CONFIG_DEFAULT_PTR);

  Sci_Init(SCI_CONFIG_DEFAULT_PTR);

  Sci_EnableNotifications(SCI_CHANNEL_4);

  StartOS(OSDEFAULTAPPMODE);

}
