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
 * Simple project to test all timers in polling mode.
 *
 * Author: 2013  Gianluca Franchino
 */

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Gpt.h"
#include "test/assert/inc/ee_assert.h"


/*Timers values */
#define GPT_TMR_START_VALUE	200 /*TMR0, TMR1 target time about 0,5 msec.*/
#define GPT_CMT_START_VALUE	50000 /*CMT0, CMT0 target time about 20 msec.*/
#define GPT_MTU_START_VALUE	50000 /*MTU0 target time about 20 msec.*/

#define	GPT_TMR_CNTR_MAX				0x3


/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,				/*  0 */
	EE_ASSERT_INIT,					/*  1 */
	EE_ASSERT_VERSION,				/*  2 */
	EE_ASSERT_CLOCK_INIT,			/*  3 */
	EE_ASSERT_GPT_INIT,				/*  4 */
	EE_ASSERT_GPT_TMR0_INIT,		/*  5 */
	EE_ASSERT_GPT_TMR0_RUNNING,		/*  6 */
	EE_ASSERT_GPT_TMR0_FIRED,		/*  7 */
	EE_ASSERT_GPT_TMR0_FIRED_LAST,	/*  8 */
	EE_ASSERT_GPT_TMR0_STOPPED,		/*  9 */
	EE_ASSERT_GPT_CMT0_INIT,		/*  10 */
	EE_ASSERT_GPT_CMT0_RUNNING,		/*  11 */
	EE_ASSERT_GPT_CMT0_FIRED,		/*  12 */
	EE_ASSERT_GPT_CMT0_FIRED_LAST,	/*  13 */
	EE_ASSERT_GPT_CMT0_STOPPED,		/*  14 */
	EE_ASSERT_GPT_MTU0_INIT,		/*  15 */
	EE_ASSERT_GPT_MTU0_RUNNING,		/*  16 */
	EE_ASSERT_GPT_MTU0_FIRED,		/*  17 */
	EE_ASSERT_GPT_MTU0_FIRED_LAST,	/*  18 */
	EE_ASSERT_GPT_MTU0_STOPPED,		/*  19 */
	EE_ASSERT_GPT_TMR1_INIT,		/*  20 */
	EE_ASSERT_GPT_TMR1_RUNNING,		/*  21 */
	EE_ASSERT_GPT_TMR1_EXPIRED,		/*  22 */
	EE_ASSERT_GPT_CMT1_INIT,		/*  23 */
	EE_ASSERT_GPT_CMT1_RUNNING,		/*  24 */
	EE_ASSERT_GPT_CMT1_EXPIRED,		/*  25 */
	EE_ASSERT_GPT_MTU1_INIT,		/*  26 */
	EE_ASSERT_GPT_MTU1_RUNNING,		/*  27 */
	EE_ASSERT_GPT_MTU1_EXPIRED,		/*  28 */
	EE_ASSERT_GPT_DEINIT,			/*  29 */
	EE_ASSERT_DIM					/*  30 */
};

EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/*
 * User Led Toggle
 */
void user_led_toggle()
{
	Dio_PortLevelType	lvl;

	lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED_1);

	if (lvl & 0x1)
		Dio_WriteChannel(DIO_CHANNEL_USER_LED_1, 0);
	else
		Dio_WriteChannel(DIO_CHANNEL_USER_LED_1, 1);
}


/*
 * TASK TMR0
 */
TASK(TaskTMR0)
{
	user_led_toggle();
	counter++;
	if ( counter == 1 ) {
		EE_assert(EE_ASSERT_GPT_TMR0_FIRED,
			( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_CH_RUNNING ), 
			EE_ASSERT_GPT_TMR0_RUNNING);
	} else if (counter == GPT_TMR_CNTR_MAX) {
		EE_assert(EE_ASSERT_GPT_TMR0_FIRED_LAST,
			( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_CH_RUNNING ), 
			EE_ASSERT_GPT_TMR0_RUNNING);
	}
}

/*
 * Channel TMR0 Notification Callback.
 */
void Gpt_Notification_Channel_TMR0(void)
{
  ActivateTask(TaskTMR0);
}

/*
 * TASK CMT0
 */
TASK(TaskCMT0)
{
	user_led_toggle();
	counter++;
	if ( counter == 1 ) {
		EE_assert(EE_ASSERT_GPT_CMT0_FIRED,
			( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_CH_RUNNING ), 
			EE_ASSERT_GPT_CMT0_RUNNING);
	} else if (counter == GPT_TMR_CNTR_MAX) {
		EE_assert(EE_ASSERT_GPT_CMT0_FIRED_LAST,
			( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_CH_RUNNING ), 
			EE_ASSERT_GPT_CMT0_RUNNING);
	}
}

/*
 * Channel CMT0 Notification Callback.
 */
void Gpt_Notification_Channel_CMT0(void)
{
  ActivateTask(TaskCMT0);
}

/*
 * TASK MTU0
 */
TASK(TaskMTU0)
{
	user_led_toggle();
	counter++;
	if ( counter == 1 ) {
		EE_assert(EE_ASSERT_GPT_MTU0_FIRED,
			( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_CH_RUNNING ), 
			EE_ASSERT_GPT_MTU0_RUNNING);
	} else if (counter == GPT_TMR_CNTR_MAX) {
		EE_assert(EE_ASSERT_GPT_MTU0_FIRED_LAST,
			( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_CH_RUNNING ), 
			EE_ASSERT_GPT_MTU0_RUNNING);
	}
}

/*
 * Channel MTU0 Notification Callback.
 */
void Gpt_Notification_Channel_MTU0(void)
{
  ActivateTask(TaskMTU0);
}

/*
 * TASK TMR1
 */
TASK(TaskTMR1)
{
	user_led_toggle();
	counter++;
	if ( counter == 1 ) {
      EE_assert(EE_ASSERT_GPT_TMR1_EXPIRED, 
    		  ( Gpt_GetStatus(GPT_CHANNEL_TMR1) == GPT_CH_EXPIRED ), 
    		  EE_ASSERT_GPT_TMR1_RUNNING);
    } 
}

/*
 * Channel TMR1 Notification Callback.
 */
void Gpt_Notification_Channel_TMR1(void)
{
	ActivateTask(TaskTMR1);
}

/*
 * TASK CMT1
 */
TASK(TaskCMT1)
{
	user_led_toggle();
	counter++;
	if ( counter == 1 ) {
      EE_assert(EE_ASSERT_GPT_CMT1_EXPIRED, 
    		  ( Gpt_GetStatus(GPT_CHANNEL_CMT1) == GPT_CH_EXPIRED ), 
    		  EE_ASSERT_GPT_CMT1_RUNNING);
    } 
}

/*
 * Channel CMT1 Notification Callback.
 */
void Gpt_Notification_Channel_CMT1(void)
{
	ActivateTask(TaskCMT1);
}

/*
 * TASK MTU1
 */
TASK(TaskMTU1)
{
	user_led_toggle();
	counter++;
	if ( counter == 1 ) {
      EE_assert(EE_ASSERT_GPT_MTU1_EXPIRED, 
    		  ( Gpt_GetStatus(GPT_CHANNEL_MTU1) == GPT_CH_EXPIRED ), 
    		  EE_ASSERT_GPT_MTU1_RUNNING);
    } 
}

/*
 * Channel MTU1 Notification Callback.
 */
void Gpt_Notification_Channel_MTU1(void)
{
	ActivateTask(TaskMTU1);
}


/*
 * MAIN TASK
 */
int main(void)
{
	Std_VersionInfoType	version;
	Dio_PortLevelType	lvl;

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	Gpt_GetVersionInfo(&version);

	EE_assert(EE_ASSERT_VERSION, ( (version.vendorID == 0) && 
		(version.moduleID == 100) && (version.sw_major_version == 1) && 
		(version.sw_minor_version == 0) && (version.sw_patch_version == 0)),
		EE_ASSERT_INIT);
	
	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
	Mcu_InitClock(MCU_CLK_MODE_HOCO40_I1_B2);
	
	EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);
	
	Port_Init(PORT_CONFIG_DEFAULT_PTR);
	
	Dio_Init(DIO_CONFIG_DEFAULT_PTR);
	
	Gpt_Init(GPT_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_GPT_INIT, TRUE, EE_ASSERT_CLOCK_INIT);

	/*
	 * Channel TMR0: 8 bits counter in continuous mode.
	 */
	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_TMR0_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_EnableNotification(GPT_CHANNEL_TMR0);
	
	Gpt_StartTimer(GPT_CHANNEL_TMR0, GPT_TMR_START_VALUE);

	EE_assert(EE_ASSERT_GPT_TMR0_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_TMR0_INIT);
	
    while ( counter < GPT_TMR_CNTR_MAX );

	Gpt_StopTimer(GPT_CHANNEL_TMR0);

	EE_assert( EE_ASSERT_GPT_TMR0_STOPPED, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_CH_STOPPED ), 
		EE_ASSERT_GPT_TMR0_FIRED_LAST);
	
	Gpt_DisableNotification(GPT_CHANNEL_TMR0);
	
	
	
	/*
	 * Channel CMT0: 16 bits counter in continuous mode.
	 */
	user_led_toggle();
	counter = 0;

	EE_assert(EE_ASSERT_GPT_CMT0_INIT, 
			( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_OPERATIONAL ), 
			EE_ASSERT_GPT_INIT);

	Gpt_EnableNotification(GPT_CHANNEL_CMT0);
	
	Gpt_StartTimer(GPT_CHANNEL_CMT0, GPT_CMT_START_VALUE);

	EE_assert(EE_ASSERT_GPT_CMT0_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_CMT0_INIT);
	
    while ( counter < GPT_TMR_CNTR_MAX );

	Gpt_StopTimer(GPT_CHANNEL_CMT0);

	EE_assert( EE_ASSERT_GPT_CMT0_STOPPED, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_CH_STOPPED ), 
		EE_ASSERT_GPT_CMT0_FIRED_LAST);
	
	Gpt_DisableNotification(GPT_CHANNEL_CMT0);
	
	/*
	 * Channel MTU0: 16 bits counter in continuous mode.
	 */
	user_led_toggle();
	counter = 0;

	EE_assert(EE_ASSERT_GPT_MTU0_INIT, 
			( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_OPERATIONAL ), 
			EE_ASSERT_GPT_INIT);

	Gpt_EnableNotification(GPT_CHANNEL_MTU0);
	
	Gpt_StartTimer(GPT_CHANNEL_MTU0, GPT_MTU_START_VALUE);

	EE_assert(EE_ASSERT_GPT_MTU0_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_MTU0_INIT);
	
    while ( counter < GPT_TMR_CNTR_MAX );

	Gpt_StopTimer(GPT_CHANNEL_MTU0);

	EE_assert( EE_ASSERT_GPT_MTU0_STOPPED, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_CH_STOPPED ), 
		EE_ASSERT_GPT_MTU0_FIRED_LAST);
	
	Gpt_DisableNotification(GPT_CHANNEL_MTU0);
	
	/*
	 * Channel TMR1: 8 bits counter in one-shot mode.
	 */
	user_led_toggle();
	counter = 0;
	
	EE_assert(EE_ASSERT_GPT_TMR1_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR1) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_EnableNotification(GPT_CHANNEL_TMR1);
	
	Gpt_StartTimer(GPT_CHANNEL_TMR1, GPT_TMR_START_VALUE);

	EE_assert(EE_ASSERT_GPT_TMR1_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_TMR1) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_TMR1_INIT);

	while ( counter == 0 );


	
	Gpt_DisableNotification(GPT_CHANNEL_TMR1);
		

	/*
	 * Channel CMT1: 16 bits counter in one-shot mode.
	 */
	user_led_toggle();
	counter = 0;
	
	EE_assert(EE_ASSERT_GPT_CMT1_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT1) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_EnableNotification(GPT_CHANNEL_CMT1);
	
	Gpt_StartTimer(GPT_CHANNEL_CMT1, GPT_CMT_START_VALUE);

	EE_assert(EE_ASSERT_GPT_CMT1_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_CMT1) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_CMT1_INIT);

	while ( counter == 0 );

	Gpt_DisableNotification(GPT_CHANNEL_CMT1);
	
	/*
	 * Channel MTU1: 16 bits counter in one-shot mode.
	 */
	user_led_toggle();
	counter = 0;
	
	EE_assert(EE_ASSERT_GPT_MTU1_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU1) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_EnableNotification(GPT_CHANNEL_MTU1);
	
	Gpt_StartTimer(GPT_CHANNEL_MTU1, GPT_CMT_START_VALUE);

	EE_assert(EE_ASSERT_GPT_MTU1_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_MTU1) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_MTU1_INIT);

	while ( counter == 0 );

	Gpt_DisableNotification(GPT_CHANNEL_MTU1);

	Gpt_DeInit();
	EE_assert(EE_ASSERT_GPT_DEINIT, TRUE, EE_ASSERT_GPT_MTU1_EXPIRED);
	
	EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_GPT_DEINIT);
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