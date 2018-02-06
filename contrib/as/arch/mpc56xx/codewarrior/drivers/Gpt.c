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
 * GPT367:	Gpt.c Module source file.
 *
 * AUTOSAR-"like" GPT Driver Source File.
 *
 * Author:  2012,  Francesco Esposito
 */

/*
 * GPT293:	Gpt.c shall include Gpt.h.
 *
 * Comment: Gpt.c has implicit access to the Gpt_Cfg.h through the Gpt.h file.
 */
#include "Gpt.h"

/* 
 * GPT256:	The GPT module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files. The imported included files
 * 		shall be checked by preprocessing directives. (BSW004)
 *
 * The following version numbers shall be verified:
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * Where <MODULENAME> is the module abbreviation of the other (external) modules
 * which provide header files included by the GPT module.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	GPT_AR_RELEASE_MAJOR_VERSION	4
#define	GPT_AR_RELEASE_MINOR_VERSION	0

#if !defined( GPT_AR_MAJOR_VERSION ) || \
    ( GPT_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION )
#error	Gpt: version mismatch.
#endif

#include "ee.h"
#include "Gpt_Internal.h"

/*
 * Type that holds all global data for Gpt Driver
 */
typedef struct
{

  boolean			Init;		/* GPT Driver Initialized?    */

  const Gpt_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

  uint32			Status;		/* Channel Status	      */

  uint32			Notifications;	/* Channel Notifications      */

} Gpt_GlobalType;


/*
 * Global config
 */
Gpt_GlobalType Gpt_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
  0x00000000		/* Status	*/
};

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/* List of Notification GPT Flag */
int Gpt_NotificationList[8] = {	
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED, \
					NOTIFICATION_ENABLED
				     };
#endif

/*
 * Local function managing STM module
 */
void mpc5643l_stm_freeze_on(void)
{
        STM.CR.B.FRZ = 1;
}

void mpc5643l_stm_freeze_off(void)
{
        STM.CR.B.FRZ = 0;
}

void mpc5643l_stm_set_prescaler(unsigned int val)
{
        STM.CR.B.CPS = val-1;
}

void mpc5643l_stm_select_channel(unsigned int ch)
{
        if (ch == 0) {
                STM.CCR0.B.CEN = 1;
        }
        else if (ch == 1) {
                STM.CCR1.B.CEN = 1;
        }
        else if (ch == 2) {
                STM.CCR2.B.CEN = 1;
        }
        else if (ch == 3) {
                STM.CCR3.B.CEN = 1;
        }
}

void mpc5643l_stm_unselect_channel(unsigned int ch)
{
        if (ch == 0) {
                STM.CCR0.B.CEN = 0;
        }
        else if (ch == 1) {
                STM.CCR1.B.CEN = 0;
        }
        else if (ch == 2) {
                STM.CCR2.B.CEN = 0;
        }
        else if (ch == 3) {
                STM.CCR3.B.CEN = 0;
        }
}

void mpc5643l_stm_channel_cmp(unsigned int ch, unsigned int val)
{
        if (ch == 0) {
                STM.CMP0.R = val;
        }
        else if (ch == 1) {
                STM.CMP1.R = val;
        }
        else if (ch == 2) {
                STM.CMP2.R = val;
        }
        else if (ch == 3) {
                STM.CMP3.R = val;
        }
}

void mpc5643l_stm_clear_int(unsigned int ch)
{
        if (ch == 0) {
                STM.CIR0.B.CIF = 1;
        }
        else if (ch == 1) {
                STM.CIR1.B.CIF = 1;
        }
        else if (ch == 2) {
                STM.CIR2.B.CIF = 1;
        }
        else if (ch == 3) {
                STM.CIR3.B.CIF = 1;
        }
}

void mpc5643l_stm_set_counter(unsigned int val)
{
        STM.CNT.R = val;
}

void mpc5643l_stm_enable(void)
{
        STM.CR.B.TEN = 1;
}

void mpc5643l_stm_disable(void)
{
        STM.CR.B.TEN = 0;
}

/*
 * Gpt_Init implementation.
 */
void Gpt_Init(
  const Gpt_ConfigType *	ConfigPtr
)
{
	register EE_FREG	flags;
	register uint32		channel, Comparator=0U;
	Gpt_ChannelMode		Mode;

	flags = EE_hal_suspendIRQ();

	// Set prescaler
	mpc5643l_stm_set_prescaler(ConfigPtr->Prsc);

	// Initializes STM freeze capability
	if (ConfigPtr->freeze == FREEZE_ON) {
		mpc5643l_stm_freeze_on();
	}
	else {
		mpc5643l_stm_freeze_off();
	}

	// initial counter value
	mpc5643l_stm_set_counter(ConfigPtr->InitVal);

	for (channel = 0U; channel < ConfigPtr->GptNumberOfGptChannels; channel++)
	{
		// enable channel
		mpc5643l_stm_select_channel(channel);

		if (ConfigPtr->GptChannels[channel].GptNotificationPtr != NULL) {
			Gpt_NotificationList[channel] = NOTIFICATION_ENABLED;
		}

		// Get GPT Mode (continuous/one-shot)
		Mode = ConfigPtr->GptChannels[channel].GptChannelMode;

		// For continuous mode set user predefined Match-Comparator
		if (Mode == GPT_CH_MODE_CONTINUOUS) {
			Comparator = ConfigPtr->GptChannels[channel].GptCompare;
			mpc5643l_stm_channel_cmp(channel, Comparator);
		}
	}

	Gpt_Global.ConfigPtr = ConfigPtr;
	Gpt_Global.Init = TRUE;

	EE_hal_resumeIRQ(flags);
}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt_DeInit implementation.
 */
void Gpt_DeInit(
  void
)
{


}
#endif

#if ( GPT_TIME_ELAPSED_API == STD_ON )
/*
 * Gpt_GetTimeElapsed implementation.
 */
Gpt_ValueType Gpt_GetTimeElapsed(
  Gpt_ChannelType	Channel
)
{
	uint32 target = Gpt_Global.ConfigPtr->GptChannels[Channel].GptCompare;
	uint32 ret_val = 0U;

	if (target < STM.CNT.R) {
		ret_val = STM.CNT.R - target;
	}
	else {
		ret_val = STM.CNT.R + (0xFFFFFFFF - target);
	}

	return ret_val;
}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
/*
 * Gpt_GetTimeRemainig implementation.
 */
Gpt_ValueType Gpt_GetTimeRemaining(
  Gpt_ChannelType	Channel
)
{
	uint32 target = Gpt_Global.ConfigPtr->GptChannels[Channel].GptCompare;
	uint32 ret_val = 0U;

	if (target > STM.CNT.R) {
		ret_val = target - STM.CNT.R;
	}
	else {
		ret_val = target + (0xFFFFFFFF - STM.CNT.R);
	}

	return ret_val;
}
#endif

/*
 * Gpt_StartTimer implementation.
 */
void Gpt_StartTimer(
  Gpt_ChannelType	Channel,
  Gpt_ValueType		Value
)
{
	mpc5643l_stm_channel_cmp(Channel, Value);
	mpc5643l_stm_select_channel(Channel);
	mpc5643l_stm_enable();
}

/*
 * Gpt_StopTimer implementation.
 */
void Gpt_StopTimer(
  Gpt_ChannelType	Channel
)
{
	mpc5643l_stm_unselect_channel(Channel);
}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/*
 * Gpt_EnableNotification implementation.
 */
void Gpt_EnableNotification(
  Gpt_ChannelType	Channel
)
{
  	Gpt_NotificationList[Channel] = NOTIFICATION_ENABLED;
}

/*
 * Gpt_DisableNotification implementation.
 */
void Gpt_DisableNotification(
  Gpt_ChannelType	Channel
)
{
	Gpt_NotificationList[Channel] = NOTIFICATION_DISABLED;
}
#endif

#if ( \
  ( GPT_REPORT_WAKEUP_SOURCE == STD_ON ) && \
  ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) \
)
/*
 * Gpt_SetMode implementation.
 */
void Gpt_SetMode(
  Gpt_ModeType	Mode
)
{

}

/*
 * Gpt_DisableWakeup implementation.
 */
void Gpt_DisableWakeup(
  Gpt_ChannelType	Channel
)
{


}

/*
 * Gpt_EnableWakeup implementation.
 */
void Gpt_EnableWakeup(
  Gpt_ChannelType	Channel
)
{

}

/*
 * Gpt_CheckWakeup implementation.
 */
void Gpt_CheckWakeup(
  EcuM_WakeupSourceType	WakeupSource
)
{


}
#endif


