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
 * Simple banchmark project for AUTOSAR "like" GPT Driver.
 *
 * Author: 2013,  Giuseppe Serano
 */

#include "ee.h"
#include "Dio.h"
#include "Mcu.h"
#include "Port.h"
#include "Gpt.h"

/* counter */
volatile int counter = 0;

/* reset reason */
volatile Mcu_RawResetType reset = 0;

/* presc flag */
volatile boolean presc = FALSE;

#define	GPT_TMR_CNTR_MAX				0x000000000000000F
#define	GPT_TMR_JOINED_CNTR_MAX				0x0000000000000002

#define	GPT_TMR_START_VALUE_NO_PRESC			0x000000000000FFFF
#define	GPT_TMR_START_VALUE_PRESC			0x00000000000FFF0F
#define	GPT_TMR_WIDE_START_VALUE_NO_PRESC		0x0000000000FF00FF
#define	GPT_TMR_WIDE_START_VALUE_PRESC			0x0000000100000000
#define	GPT_TMR_JOINED_START_VALUE			0x0000000001000000
#define	GPT_TMR_JOINED_WIDE_START_VALUE			0x0000000100000000

/*
 * User Led Toggle
 */
void user_led_toggle()
{
  Dio_PortLevelType	lvl;

  lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED);

  if (lvl == STD_HIGH)
    Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_LOW);
  else
    Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_HIGH);
}

/*
 * TASK 0 A
 */
TASK(Task_0_A)
{
  user_led_toggle();
  counter++;
}

/*
 * Channel 0 A Notification Callback.
 */
void Gpt_Notification_Channel_0_A(void)
{
  ActivateTask(Task_0_A);
}

/*
 * TASK 0 B
 */
TASK(Task_0_B)
{
  user_led_toggle();
  counter++;
}

/*
 * Channel 0 B Notification Callback.
 */
void Gpt_Notification_Channel_0_B(void)
{
  ActivateTask(Task_0_B);
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
    ){
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

  Dio_Init(DIO_CONFIG_USER_LED_PTR);

  /* Forever loop: background activities (if any) should go here */
  for (;;)
  {

    Gpt_Init(GPT_CONFIG_DEFAULT_PTR);

    /*
     * Channel 0 A: 16bit counter with and without 8bit prescaler in continuous
     * mode.
     */
    Gpt_EnableNotification(GPT_CHANNEL_0_A);

    do {

      if ( presc ) {

	Gpt_StartTimer(GPT_CHANNEL_0_A, GPT_TMR_START_VALUE_PRESC);

      }
      else {
  
	Gpt_StartTimer(GPT_CHANNEL_0_A, GPT_TMR_START_VALUE_NO_PRESC);

      }

      while ( counter < GPT_TMR_CNTR_MAX );

      Gpt_StopTimer(GPT_CHANNEL_0_A);

      presc = !presc;
      counter = 0;

    }
    while ( presc );

    Gpt_DisableNotification(GPT_CHANNEL_0_A);

    /*
     * Channel 0 B: 16bit counter with and without 8bit prescaler in one-shot
     * mode.
     */
    Gpt_EnableNotification(GPT_CHANNEL_0_B);

    do {

      if ( presc ) {

	Gpt_StartTimer(GPT_CHANNEL_0_B, GPT_TMR_START_VALUE_PRESC);

      }
      else {

	Gpt_StartTimer(GPT_CHANNEL_0_B, GPT_TMR_START_VALUE_NO_PRESC);

      }

      while ( counter == 0 );

      presc = !presc;
      counter = 0;

    }
    while ( presc );

    Gpt_DisableNotification(GPT_CHANNEL_0_B);

    counter = 0;

    Gpt_DeInit();

  }

}
