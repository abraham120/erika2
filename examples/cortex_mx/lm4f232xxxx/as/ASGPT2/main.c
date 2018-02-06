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
 * Simple project to test all timers in polling mode.
 *
 * Author: 2011,  Giuseppe Serano
 */

#include "Dio.h"
#include "Mcu.h"
#include "Port.h"
#include "Gpt.h"
#include "test/assert/inc/ee_assert.h"

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,				/*  0 */
  EE_ASSERT_INIT,				/*  1 */
  EE_ASSERT_VERSION,				/*  2 */
  EE_ASSERT_CLOCK_INIT,				/*  3 */
  EE_ASSERT_PLL_LOCKED,				/*  4 */
  EE_ASSERT_GPT_INIT,				/*  5 */
  EE_ASSERT_GPT_0_A_INIT,			/*  6 */
  EE_ASSERT_GPT_0_A_NO_PRESC_RUNNING,		/*  7 */
  EE_ASSERT_GPT_0_A_NO_PRESC_FIRED,		/*  8 */
  EE_ASSERT_GPT_0_A_NO_PRESC_FIRED_LAST,	/*  9 */
  EE_ASSERT_GPT_0_A_NO_PRESC_STOPPED,		/* 10 */
  EE_ASSERT_GPT_0_A_PRESC_RUNNING,		/* 11 */
  EE_ASSERT_GPT_0_A_PRESC_FIRED,		/* 12 */
  EE_ASSERT_GPT_0_A_PRESC_FIRED_LAST,		/* 13 */
  EE_ASSERT_GPT_0_A_PRESC_STOPPED,		/* 14 */
  EE_ASSERT_GPT_0_B_INIT,			/* 15 */
  EE_ASSERT_GPT_0_B_NO_PRESC_RUNNING,		/* 16 */
  EE_ASSERT_GPT_0_B_NO_PRESC_EXPIRED,		/* 17 */
  EE_ASSERT_GPT_0_B_PRESC_RUNNING,		/* 18 */
  EE_ASSERT_GPT_0_B_PRESC_EXPIRED,		/* 19 */
  EE_ASSERT_GPT_W_3_A_INIT,			/* 20 */
  EE_ASSERT_GPT_W_3_A_NO_PRESC_RUNNING,		/* 21 */
  EE_ASSERT_GPT_W_3_A_NO_PRESC_FIRED,		/* 22 */
  EE_ASSERT_GPT_W_3_A_NO_PRESC_FIRED_LAST,	/* 23 */
  EE_ASSERT_GPT_W_3_A_NO_PRESC_STOPPED,		/* 24 */
  EE_ASSERT_GPT_W_3_A_PRESC_RUNNING,		/* 25 */
  EE_ASSERT_GPT_W_3_A_PRESC_FIRED,		/* 26 */
  EE_ASSERT_GPT_W_3_A_PRESC_FIRED_LAST,		/* 27 */
  EE_ASSERT_GPT_W_3_A_PRESC_STOPPED,		/* 28 */
  EE_ASSERT_GPT_W_3_B_INIT,			/* 29 */
  EE_ASSERT_GPT_W_3_B_NO_PRESC_RUNNING,		/* 30 */
  EE_ASSERT_GPT_W_3_B_NO_PRESC_EXPIRED,		/* 31 */
  EE_ASSERT_GPT_W_3_B_PRESC_RUNNING,		/* 32 */
  EE_ASSERT_GPT_W_3_B_PRESC_EXPIRED,		/* 33 */
  EE_ASSERT_GPT_J_1_INIT,			/* 34 */
  EE_ASSERT_GPT_J_1_RUNNING,			/* 35 */
  EE_ASSERT_GPT_J_1_FIRED,			/* 36 */
  EE_ASSERT_GPT_J_1_FIRED_LAST,			/* 37 */
  EE_ASSERT_GPT_J_1_STOPPED,			/* 38 */
  EE_ASSERT_GPT_J_2_INIT,			/* 39 */
  EE_ASSERT_GPT_J_2_RUNNING,			/* 40 */
  EE_ASSERT_GPT_J_2_EXPIRED,			/* 41 */
  EE_ASSERT_GPT_J_W_1_INIT,			/* 42 */
  EE_ASSERT_GPT_J_W_1_RUNNING,			/* 43 */
  EE_ASSERT_GPT_J_W_1_FIRED,			/* 44 */
  EE_ASSERT_GPT_J_W_1_FIRED_LAST,		/* 45 */
  EE_ASSERT_GPT_J_W_1_STOPPED,			/* 46 */
  EE_ASSERT_GPT_J_W_2_INIT,			/* 47 */
  EE_ASSERT_GPT_J_W_2_RUNNING,			/* 48 */
  EE_ASSERT_GPT_J_W_2_EXPIRED,			/* 49 */
  EE_ASSERT_GPT_DEINIT,				/* 50 */
  EE_ASSERT_DIM					/* 51 */
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

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

  lvl = Dio_ReadChannelGroup(DIO_CHANNEL_GROUP_USER_LED);

  if (lvl == STD_HIGH)
    Dio_WriteChannelGroup(DIO_CHANNEL_GROUP_USER_LED, STD_LOW);
  else
    Dio_WriteChannelGroup(DIO_CHANNEL_GROUP_USER_LED, STD_HIGH);
}

/*
 * TASK 0 A
 */
TASK(Task_0_A)
{

  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    if ( presc ) {
      EE_assert(
	EE_ASSERT_GPT_0_A_PRESC_FIRED,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_A_PRESC_RUNNING
      );
    }
    else {
      EE_assert(
	EE_ASSERT_GPT_0_A_NO_PRESC_FIRED,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_A_NO_PRESC_RUNNING
      );
    }
  }
  else if ( counter == GPT_TMR_CNTR_MAX ) {
    if ( presc ) {
      EE_assert(
	EE_ASSERT_GPT_0_A_PRESC_FIRED_LAST,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_A_PRESC_FIRED
      );
    }
    else {
      EE_assert(
	EE_ASSERT_GPT_0_A_NO_PRESC_FIRED_LAST,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_A_NO_PRESC_FIRED
      );
    }
  }

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
  if ( counter == 1 ) {
    if ( presc ) {
      EE_assert(
	EE_ASSERT_GPT_0_B_PRESC_EXPIRED,
	( Gpt_GetStatus(GPT_CHANNEL_0_B) == GPT_CH_STOPPED ),
	EE_ASSERT_GPT_0_B_PRESC_RUNNING
      );
    }
    else {
      EE_assert(
	EE_ASSERT_GPT_0_B_NO_PRESC_EXPIRED,
	( Gpt_GetStatus(GPT_CHANNEL_0_B) == GPT_CH_STOPPED ),
	EE_ASSERT_GPT_0_B_NO_PRESC_RUNNING
      );
    }
  }
}

/*
 * Channel 0 B Notification Callback.
 */
void Gpt_Notification_Channel_0_B(void)
{
  ActivateTask(Task_0_B);
}


/*
 * TASK W 0 A
 */
TASK(Task_W_3_A)
{
  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    if ( presc ) {
      EE_assert(
	EE_ASSERT_GPT_W_3_A_PRESC_FIRED,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_A_PRESC_RUNNING
      );
    }
    else {
      EE_assert(
	EE_ASSERT_GPT_W_3_A_NO_PRESC_FIRED,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_A_NO_PRESC_RUNNING
      );
    }
  }
  else if ( counter == GPT_TMR_CNTR_MAX ) {
    if ( presc ) {
      EE_assert(
	EE_ASSERT_GPT_W_3_A_PRESC_FIRED_LAST,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_A_PRESC_FIRED
      );
    }
    else {
      EE_assert(
	EE_ASSERT_GPT_W_3_A_NO_PRESC_FIRED_LAST,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_A_NO_PRESC_FIRED
      );
    }
  }
}

/*
 * Channel W 0 A Notification Callback.
 */
void Gpt_Notification_Channel_W_3_A(void)
{
  ActivateTask(Task_W_3_A);
}

/*
 * TASK W 0 B
 */
TASK(Task_W_3_B)
{
  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    if ( presc ) {
      EE_assert(
	EE_ASSERT_GPT_W_3_B_PRESC_EXPIRED,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_B) == GPT_CH_STOPPED ),
	EE_ASSERT_GPT_W_3_B_PRESC_RUNNING
      );
    }
    else {
      EE_assert(
	EE_ASSERT_GPT_W_3_B_NO_PRESC_EXPIRED,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_B) == GPT_CH_STOPPED ),
	EE_ASSERT_GPT_W_3_B_NO_PRESC_RUNNING
      );
    }
  }
}

/*
 * Channel W 0 B Notification Callback.
 */
void Gpt_Notification_Channel_W_3_B(void)
{
  ActivateTask(Task_W_3_B);
}

/*
 * TASK J 1
 */
TASK(Task_J_1)
{
  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    EE_assert(
      EE_ASSERT_GPT_J_1_FIRED,
      ( Gpt_GetStatus(GPT_CHANNEL_J_1) == GPT_CH_RUNNING ),
      EE_ASSERT_GPT_J_1_RUNNING
    );
  }
  else if ( counter == GPT_TMR_JOINED_CNTR_MAX ) {
    EE_assert(
      EE_ASSERT_GPT_J_1_FIRED_LAST,
      ( Gpt_GetStatus(GPT_CHANNEL_J_1) == GPT_CH_RUNNING ),
      EE_ASSERT_GPT_J_1_FIRED
    );
  }
}

/*
 * Channel J 1 Notification Callback.
 */
void Gpt_Notification_Channel_J_1(void)
{
  ActivateTask(Task_J_1);
}

/*
 * TASK J 2
 */
TASK(Task_J_2)
{
  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    EE_assert(
      EE_ASSERT_GPT_J_2_EXPIRED,
      ( Gpt_GetStatus(GPT_CHANNEL_J_2) == GPT_CH_STOPPED ),
      EE_ASSERT_GPT_J_2_RUNNING
    );
  }
}

/*
 * Channel J 2 Notification Callback.
 */
void Gpt_Notification_Channel_J_2(void)
{
  ActivateTask(Task_J_2);
}

/*
 * TASK J W 1
 */
TASK(Task_J_W_1)
{
  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    EE_assert(
      EE_ASSERT_GPT_J_W_1_FIRED,
      ( Gpt_GetStatus(GPT_CHANNEL_J_W_1) == GPT_CH_RUNNING ),
      EE_ASSERT_GPT_J_W_1_RUNNING
    );
  }
  else if ( counter == GPT_TMR_JOINED_CNTR_MAX ) {
    EE_assert(
      EE_ASSERT_GPT_J_W_1_FIRED_LAST,
      ( Gpt_GetStatus(GPT_CHANNEL_J_W_1) == GPT_CH_RUNNING ),
      EE_ASSERT_GPT_J_W_1_FIRED
    );
  }
}

/*
 * Channel J W 1 Notification Callback.
 */
void Gpt_Notification_Channel_J_W_1(void)
{
  ActivateTask(Task_J_W_1);
}

/*
 * TASK J W 2
 */
TASK(Task_J_W_2)
{
  user_led_toggle();
  counter++;
  if ( counter == 1 ) {
    EE_assert(
      EE_ASSERT_GPT_J_W_2_EXPIRED,
      ( Gpt_GetStatus(GPT_CHANNEL_J_W_2) == GPT_CH_STOPPED ),
      EE_ASSERT_GPT_J_W_2_RUNNING
    );
  }
}

/*
 * Channel J W 2 Notification Callback.
 */
void Gpt_Notification_Channel_J_W_2(void)
{
  ActivateTask(Task_J_W_2);
}

/*
 * MAIN TASK
 */
int main(void)
{

  Std_VersionInfoType	version;

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  Gpt_GetVersionInfo(&version);

  EE_assert(
    EE_ASSERT_VERSION,
    (
      (version.vendorID == 0) &&
      (version.moduleID == 100) &&
      (version.sw_major_version == 1) &&
      (version.sw_minor_version == 0) &&
      (version.sw_patch_version == 0)
    ),
    EE_ASSERT_INIT
  );

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  Mcu_InitClock(MCU_CLOCK_MODE_PRIOSC_3_PLL);
  
  EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

  while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);

  EE_assert(
    EE_ASSERT_PLL_LOCKED,
    Mcu_GetPllStatus() == MCU_PLL_LOCKED,
    EE_ASSERT_CLOCK_INIT
  );

  Mcu_DistributePllClock();

  Port_Init(PORT_CONFIG_SCI_PTR);

  Dio_Init(DIO_CONFIG_USER_LED_PTR);

  Gpt_Init(GPT_CONFIG_DEFAULT_PTR);

  EE_assert(EE_ASSERT_GPT_INIT, TRUE, EE_ASSERT_PLL_LOCKED);

  /*
   * Channel 0 A: 16bit counter with and without 8bit prescaler in continuous
   * mode.
   */
  EE_assert(
    EE_ASSERT_GPT_0_A_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );


  Gpt_EnableNotification(GPT_CHANNEL_0_A);

  do {

    if ( presc ) {

      Gpt_StartTimer(GPT_CHANNEL_0_A, GPT_TMR_START_VALUE_PRESC);

      EE_assert(
	EE_ASSERT_GPT_0_A_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_A_NO_PRESC_STOPPED
      );
  
    }
    else {
  
      Gpt_StartTimer(GPT_CHANNEL_0_A, GPT_TMR_START_VALUE_NO_PRESC);

      EE_assert(
	EE_ASSERT_GPT_0_A_NO_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_A_INIT
      );
    }

    while ( counter < GPT_TMR_CNTR_MAX );

    Gpt_StopTimer(GPT_CHANNEL_0_A);

    if ( presc ) {

        EE_assert(
	  EE_ASSERT_GPT_0_A_PRESC_STOPPED,
	  ( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_STOPPED ),
	  EE_ASSERT_GPT_0_A_PRESC_FIRED_LAST
	);

    }
    else {

      EE_assert(
	EE_ASSERT_GPT_0_A_NO_PRESC_STOPPED,
	( Gpt_GetStatus(GPT_CHANNEL_0_A) == GPT_CH_STOPPED ),
	EE_ASSERT_GPT_0_A_NO_PRESC_FIRED_LAST
      );

    }

    presc = !presc;
    counter = 0;

  }
  while ( presc );

  Gpt_DisableNotification(GPT_CHANNEL_0_A);

  /*
   * Channel 0 B: 16bit counter with and without 8bit prescaler in one-shot
   * mode.
   */
  EE_assert(
    EE_ASSERT_GPT_0_B_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_0_B) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_0_B);

  do {

    if ( presc ) {

      Gpt_StartTimer(GPT_CHANNEL_0_B, GPT_TMR_START_VALUE_PRESC);

      EE_assert(
	EE_ASSERT_GPT_0_B_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_0_B) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_B_NO_PRESC_EXPIRED
      );

    }

    else {

      Gpt_StartTimer(GPT_CHANNEL_0_B, GPT_TMR_START_VALUE_NO_PRESC);

      EE_assert(
	EE_ASSERT_GPT_0_B_NO_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_0_B) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_0_B_INIT
      );

    }

    while ( counter == 0 );

    presc = !presc;
    counter = 0;

  }
  while ( presc );

  Gpt_DisableNotification(GPT_CHANNEL_0_B);

/*
   * Channel W 0 A: 32bit counter with and without 16bit prescaler in continuous
   * mode.
   */
  EE_assert(
    EE_ASSERT_GPT_W_3_A_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_W_3_A);

  do {

    if ( presc ) {

      Gpt_StartTimer(GPT_CHANNEL_W_3_A, GPT_TMR_WIDE_START_VALUE_PRESC);

      EE_assert(
	EE_ASSERT_GPT_W_3_A_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_A_NO_PRESC_STOPPED
      );
  
    }
    else {
  
      Gpt_StartTimer(GPT_CHANNEL_W_3_A, GPT_TMR_WIDE_START_VALUE_NO_PRESC);

      EE_assert(
	EE_ASSERT_GPT_W_3_A_NO_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_A_INIT
      );
    }

    while ( counter < GPT_TMR_CNTR_MAX );

    Gpt_StopTimer(GPT_CHANNEL_W_3_A);

    if ( presc ) {

        EE_assert(
	  EE_ASSERT_GPT_W_3_A_PRESC_STOPPED,
	  ( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_STOPPED ),
	  EE_ASSERT_GPT_W_3_A_PRESC_FIRED_LAST
	);

    }
    else {

      EE_assert(
	EE_ASSERT_GPT_W_3_A_NO_PRESC_STOPPED,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_A) == GPT_CH_STOPPED ),
	EE_ASSERT_GPT_W_3_A_NO_PRESC_FIRED_LAST
      );

    }

    presc = !presc;
    counter = 0;

  }
  while ( presc );

  Gpt_DisableNotification(GPT_CHANNEL_W_3_A);

  /*
   * Channel W 0 B: 32bit counter without prescaler in one-shot mode.
   */
  EE_assert(
    EE_ASSERT_GPT_W_3_B_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_W_3_B) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_W_3_B);

  do {

    if ( presc ) {

      Gpt_StartTimer(GPT_CHANNEL_W_3_B, GPT_TMR_WIDE_START_VALUE_PRESC);

      EE_assert(
	EE_ASSERT_GPT_W_3_B_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_B) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_B_NO_PRESC_EXPIRED
      );

    }

    else {

      Gpt_StartTimer(GPT_CHANNEL_W_3_B, GPT_TMR_WIDE_START_VALUE_NO_PRESC);

      EE_assert(
	EE_ASSERT_GPT_W_3_B_NO_PRESC_RUNNING,
	( Gpt_GetStatus(GPT_CHANNEL_W_3_B) == GPT_CH_RUNNING ),
	EE_ASSERT_GPT_W_3_B_INIT
      );

    }

    while ( counter == 0 );

    presc = !presc;
    counter = 0;

  }
  while ( presc );

  Gpt_DisableNotification(GPT_CHANNEL_W_3_B);

  /*
   * Channel J 1: 32bit joined counter without prescaler in continuous mode.
   */
  EE_assert(
    EE_ASSERT_GPT_J_1_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_J_1) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_J_1);

  Gpt_StartTimer(GPT_CHANNEL_J_1, GPT_TMR_JOINED_START_VALUE);

  EE_assert(
    EE_ASSERT_GPT_J_1_RUNNING,
    ( Gpt_GetStatus(GPT_CHANNEL_J_1) == GPT_CH_RUNNING ),
    EE_ASSERT_GPT_J_1_INIT
  );

  while ( counter < GPT_TMR_JOINED_CNTR_MAX );

  counter = 0;

  Gpt_StopTimer(GPT_CHANNEL_J_1);

  EE_assert(
    EE_ASSERT_GPT_J_1_STOPPED,
    ( Gpt_GetStatus(GPT_CHANNEL_J_1) == GPT_CH_STOPPED ),
    EE_ASSERT_GPT_J_1_FIRED_LAST
  );

  Gpt_DisableNotification(GPT_CHANNEL_J_1);

  /*
   * Channel J 2: 32bit joined counter without prescaler in one-shot mode.
   */
  EE_assert(
    EE_ASSERT_GPT_J_2_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_J_2) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_J_2);

  Gpt_StartTimer(GPT_CHANNEL_J_2, GPT_TMR_JOINED_START_VALUE);

  EE_assert(
    EE_ASSERT_GPT_J_2_RUNNING,
    ( Gpt_GetStatus(GPT_CHANNEL_J_2) == GPT_CH_RUNNING ),
    EE_ASSERT_GPT_J_2_INIT
  );

  while ( counter == 0 );

  counter = 0;

  Gpt_DisableNotification(GPT_CHANNEL_J_2);

  /*
   * Channel J W 1: 64bit joined counter without prescaler in continuous mode.
   */
  EE_assert(
    EE_ASSERT_GPT_J_W_1_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_J_W_1) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_J_W_1);

  Gpt_StartTimer(GPT_CHANNEL_J_W_1, GPT_TMR_JOINED_WIDE_START_VALUE);

  EE_assert(
    EE_ASSERT_GPT_J_W_1_RUNNING,
    ( Gpt_GetStatus(GPT_CHANNEL_J_W_1) == GPT_CH_RUNNING ),
    EE_ASSERT_GPT_J_W_1_INIT
  );

  while ( counter < GPT_TMR_JOINED_CNTR_MAX );

  counter = 0;

  Gpt_StopTimer(GPT_CHANNEL_J_W_1);

  EE_assert(
    EE_ASSERT_GPT_J_W_1_STOPPED,
    ( Gpt_GetStatus(GPT_CHANNEL_J_W_1) == GPT_CH_STOPPED ),
    EE_ASSERT_GPT_J_W_1_FIRED_LAST
  );

  Gpt_DisableNotification(GPT_CHANNEL_J_W_1);

  /*
   * Channel J W 2: 64bit joined counter without prescaler in one-shot mode.
   */
  EE_assert(
    EE_ASSERT_GPT_J_W_2_INIT,
    ( Gpt_GetStatus(GPT_CHANNEL_J_W_2) == GPT_OPERATIONAL ),
    EE_ASSERT_GPT_INIT
  );

  Gpt_EnableNotification(GPT_CHANNEL_J_W_2);

  Gpt_StartTimer(GPT_CHANNEL_J_W_2, GPT_TMR_JOINED_WIDE_START_VALUE);

  EE_assert(
    EE_ASSERT_GPT_J_W_2_RUNNING,
    ( Gpt_GetStatus(GPT_CHANNEL_J_W_2) == GPT_CH_RUNNING ),
    EE_ASSERT_GPT_J_W_2_INIT
  );

  while ( counter == 0 );

  Gpt_DisableNotification(GPT_CHANNEL_J_W_2);

  counter = 0;

  Gpt_DeInit();

  EE_assert(EE_ASSERT_GPT_DEINIT, TRUE, EE_ASSERT_GPT_J_W_2_EXPIRED);

  EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_GPT_DEINIT);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {
    while (counter % 100000) counter++;

    user_led_toggle();

    counter++;
  }

}
