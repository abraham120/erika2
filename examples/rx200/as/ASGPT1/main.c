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


/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,				/*  0 */
	EE_ASSERT_INIT,					/*  1 */
	EE_ASSERT_VERSION,				/*  2 */
	EE_ASSERT_CLOCK_INIT,			/*  3 */
	EE_ASSERT_GPT_INIT,				/*  4 */
	EE_ASSERT_GPT_TMR0_INIT,		/*  5 */
	EE_ASSERT_GPT_TMR0_RUNNING,		/*  6 */
	EE_ASSERT_GPT_TMR0_ELAPSED,		/*  7 */
	EE_ASSERT_GPT_TMR0_REMAINING,	/*  8 */
	EE_ASSERT_GPT_TMR0_STOPPED,		/*  9 */
	EE_ASSERT_GPT_CMT0_INIT,		/*  10 */
	EE_ASSERT_GPT_CMT0_RUNNING,		/*  11 */
	EE_ASSERT_GPT_CMT0_ELAPSED,		/*  12 */
	EE_ASSERT_GPT_CMT0_REMAINING,	/*  13 */
	EE_ASSERT_GPT_CMT0_STOPPED,		/*  14 */
	EE_ASSERT_GPT_MTU0_INIT,		/*  15 */
	EE_ASSERT_GPT_MTU0_RUNNING,		/*  16 */
	EE_ASSERT_GPT_MTU0_ELAPSED,		/*  17 */
	EE_ASSERT_GPT_MTU0_REMAINING,	/*  18 */
	EE_ASSERT_GPT_MTU0_STOPPED,		/*  20 */
	EE_ASSERT_GPT_TMR1_INIT,		/*  21 */
	EE_ASSERT_GPT_TMR1_RUNNING,		/*  22 */
	EE_ASSERT_GPT_TMR1_ELAPSED,		/*  23 */
	EE_ASSERT_GPT_TMR1_REMAINING,	/*  24 */
	EE_ASSERT_GPT_TMR1_EXPIRED,		/*  25 */
	EE_ASSERT_GPT_CMT1_INIT,		/*  26 */
	EE_ASSERT_GPT_CMT1_RUNNING,		/*  27 */
	EE_ASSERT_GPT_CMT1_ELAPSED,		/*  28 */
	EE_ASSERT_GPT_CMT1_REMAINING,	/*  29 */
	EE_ASSERT_GPT_CMT1_EXPIRED,		/*  30 */
	EE_ASSERT_GPT_MTU1_INIT,		/*  31 */
	EE_ASSERT_GPT_MTU1_RUNNING,		/*  32 */
	EE_ASSERT_GPT_MTU1_ELAPSED,		/*  33 */
	EE_ASSERT_GPT_MTU1_REMAINING,	/*  34 */
	EE_ASSERT_GPT_MTU1_EXPIRED,		/*  35 */
	EE_ASSERT_GPT_DEINIT,			/*  36 */
	EE_ASSERT_DIM					/*  37 */
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
 * TASK 1
 */
TASK(Task1)
{
  /* Nothing to do! */
}

volatile Gpt_ValueType	elapsed;
volatile Gpt_ValueType	remaining;

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
	 * Channel TMR0: 8 bit counter in continuous mode.
	 */
	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_TMR0_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_StartTimer(GPT_CHANNEL_TMR0, GPT_TMR_START_VALUE);

	EE_assert(EE_ASSERT_GPT_TMR0_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_TMR0_INIT);

	counter = 0;

	do {

		counter++;

		elapsed = Gpt_GetTimeElapsed(GPT_CHANNEL_TMR0);

		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_TMR0_ELAPSED, 
					( ( elapsed > 0 ) && (elapsed < GPT_TMR_START_VALUE ) ), 
					EE_ASSERT_GPT_TMR0_RUNNING);
		}
		remaining = Gpt_GetTimeRemaining(GPT_CHANNEL_TMR0); 
		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_TMR0_REMAINING, ( 
				( remaining > 0 ) && ( remaining < GPT_TMR_START_VALUE ) &&
				( elapsed < remaining ) && 
				( (elapsed + remaining ) < GPT_TMR_START_VALUE )),
				EE_ASSERT_GPT_TMR0_ELAPSED);
		}
	
	} while ( elapsed < remaining );

	Gpt_StopTimer(GPT_CHANNEL_TMR0);

	EE_assert( EE_ASSERT_GPT_TMR0_STOPPED, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR0) == GPT_CH_STOPPED ), 
		EE_ASSERT_GPT_TMR0_REMAINING);

/*
 * Channel CMT0: 16 bit counter in continuous mode.
 */
 	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_CMT0_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_StartTimer(GPT_CHANNEL_CMT0, GPT_CMT_START_VALUE);

	EE_assert(EE_ASSERT_GPT_CMT0_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_CMT0_INIT);

	counter = 0;
	do {

		counter++;

		elapsed = Gpt_GetTimeElapsed(GPT_CHANNEL_CMT0);

		if (counter == 1) {
		EE_assert(EE_ASSERT_GPT_CMT0_ELAPSED, 
			( ( elapsed > 0 ) && (elapsed < GPT_CMT_START_VALUE ) ), 
			EE_ASSERT_GPT_CMT0_RUNNING);
		}
		remaining = Gpt_GetTimeRemaining(GPT_CHANNEL_CMT0); 
		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_CMT0_REMAINING, ( 
				( remaining > 0 ) && ( remaining < GPT_CMT_START_VALUE ) &&
				( elapsed < remaining ) && 
				( (elapsed + remaining ) < GPT_CMT_START_VALUE )),
				EE_ASSERT_GPT_CMT0_ELAPSED);
		}
	
	} while ( elapsed < remaining );

	Gpt_StopTimer(GPT_CHANNEL_CMT0);

	EE_assert( EE_ASSERT_GPT_CMT0_STOPPED, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT0) == GPT_CH_STOPPED ), 
		EE_ASSERT_GPT_CMT0_REMAINING);

/*
 * Channel MTU0: 16 bit counter in continuous mode.
 */
 	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_MTU0_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_StartTimer(GPT_CHANNEL_MTU0, GPT_MTU_START_VALUE);

	EE_assert(EE_ASSERT_GPT_MTU0_RUNNING,
		( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_MTU0_INIT);

	counter = 0;
	do {

		counter++;

		elapsed = Gpt_GetTimeElapsed(GPT_CHANNEL_MTU0);

		if (counter == 1) {
		EE_assert(EE_ASSERT_GPT_MTU0_ELAPSED, 
			( ( elapsed > 0 ) && (elapsed < GPT_MTU_START_VALUE ) ), 
			EE_ASSERT_GPT_MTU0_RUNNING);
		}
		remaining = Gpt_GetTimeRemaining(GPT_CHANNEL_MTU0); 
		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_MTU0_REMAINING, ( 
				( remaining > 0 ) && ( remaining < GPT_MTU_START_VALUE ) &&
				( elapsed < remaining ) && 
				( (elapsed + remaining ) < GPT_MTU_START_VALUE )),
				EE_ASSERT_GPT_MTU0_ELAPSED);
		}
	
	} while ( elapsed < remaining );

	Gpt_StopTimer(GPT_CHANNEL_MTU0);

	EE_assert( EE_ASSERT_GPT_MTU0_STOPPED, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU0) == GPT_CH_STOPPED ), 
		EE_ASSERT_GPT_MTU0_REMAINING);

 /*
  * Channel TMR1: 8 bit counter in one-shot mode.
  */
	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_TMR1_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR1) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_StartTimer(GPT_CHANNEL_TMR1, GPT_TMR_START_VALUE);
	
	EE_assert(EE_ASSERT_GPT_TMR1_RUNNING, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR1) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_TMR1_INIT);

	counter = 0;

	do {
		counter++;
		elapsed = Gpt_GetTimeElapsed(GPT_CHANNEL_TMR1);
		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_TMR1_ELAPSED, ( ( elapsed > 0 ) && 
				(elapsed < GPT_TMR_START_VALUE ) ),
			EE_ASSERT_GPT_TMR1_RUNNING);
		}

		remaining = Gpt_GetTimeRemaining(GPT_CHANNEL_TMR1);

		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_TMR1_REMAINING, 
			( ( remaining > 0 ) && ( elapsed < remaining ) && 
			( (elapsed + remaining ) < GPT_TMR_START_VALUE ) ), 
			EE_ASSERT_GPT_TMR1_ELAPSED);
		}

	} while ( elapsed < remaining );

	while (Gpt_GetStatus(GPT_CHANNEL_TMR1) != GPT_CH_EXPIRED);

	EE_assert(EE_ASSERT_GPT_TMR1_EXPIRED, 
		( Gpt_GetStatus(GPT_CHANNEL_TMR1) == GPT_CH_EXPIRED ), 
		EE_ASSERT_GPT_TMR1_ELAPSED);

 /*
  * Channel CMT1: 16 bit counter in one-shot mode.
  */
	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_CMT1_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT1) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_StartTimer(GPT_CHANNEL_CMT1, GPT_CMT_START_VALUE);
	
	EE_assert(EE_ASSERT_GPT_CMT1_RUNNING, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT1) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_CMT1_INIT);

	counter = 0;

	do {
		counter++;
		elapsed = Gpt_GetTimeElapsed(GPT_CHANNEL_CMT1);
		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_CMT1_ELAPSED, ( ( elapsed > 0 ) && 
				(elapsed < GPT_CMT_START_VALUE ) ),
			EE_ASSERT_GPT_CMT1_RUNNING);
		}

		remaining = Gpt_GetTimeRemaining(GPT_CHANNEL_CMT1);

		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_CMT1_REMAINING, 
			( ( remaining > 0 ) && ( elapsed < remaining ) && 
			( (elapsed + remaining ) < GPT_CMT_START_VALUE ) ), 
			EE_ASSERT_GPT_CMT1_ELAPSED);
		}

	} while ( elapsed < remaining );

	while (Gpt_GetStatus(GPT_CHANNEL_CMT1) != GPT_CH_EXPIRED);

	EE_assert(EE_ASSERT_GPT_CMT1_EXPIRED, 
		( Gpt_GetStatus(GPT_CHANNEL_CMT1) == GPT_CH_EXPIRED ), 
		EE_ASSERT_GPT_CMT1_ELAPSED);

/*
 * Channel MTU1: 8 bit counter in one-shot mode.
 */
	user_led_toggle();

	EE_assert(EE_ASSERT_GPT_MTU1_INIT, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU1) == GPT_OPERATIONAL ), 
		EE_ASSERT_GPT_INIT);

	Gpt_StartTimer(GPT_CHANNEL_MTU1, GPT_MTU_START_VALUE);
	
	EE_assert(EE_ASSERT_GPT_MTU1_RUNNING, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU1) == GPT_CH_RUNNING ), 
		EE_ASSERT_GPT_MTU1_INIT);

	counter = 0;

	do {
		counter++;
		elapsed = Gpt_GetTimeElapsed(GPT_CHANNEL_MTU1);
		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_MTU1_ELAPSED, ( ( elapsed > 0 ) && 
				(elapsed < GPT_MTU_START_VALUE ) ),
			EE_ASSERT_GPT_MTU1_RUNNING);
		}

		remaining = Gpt_GetTimeRemaining(GPT_CHANNEL_MTU1);

		if (counter == 1) {
			EE_assert(EE_ASSERT_GPT_MTU1_REMAINING, 
			( ( remaining > 0 ) && ( elapsed < remaining ) && 
			( (elapsed + remaining ) < GPT_MTU_START_VALUE ) ), 
			EE_ASSERT_GPT_MTU1_ELAPSED);
		}

	} while ( elapsed < remaining );

	while (Gpt_GetStatus(GPT_CHANNEL_MTU1) != GPT_CH_EXPIRED);

	EE_assert(EE_ASSERT_GPT_MTU1_EXPIRED, 
		( Gpt_GetStatus(GPT_CHANNEL_MTU1) == GPT_CH_EXPIRED ), 
		EE_ASSERT_GPT_MTU1_ELAPSED);
		

	Gpt_DeInit();
	EE_assert(EE_ASSERT_GPT_DEINIT, TRUE, EE_ASSERT_GPT_INIT);
	
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