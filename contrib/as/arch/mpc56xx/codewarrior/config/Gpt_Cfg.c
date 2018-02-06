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
 * GPT368:	Gpt_Cfg.c Module configuration file, if pre-compile const are
 * 		used (BSW00345, BSW00419)
 *
 * fake-druid AUTOSAR GPT Driver Configuration Source File.
 *
 * Configured for (GPT): MPC5643L Leopard
 *
 * Author: 2012, Francesco Esposito
 */

#include "Gpt.h"
#include "eecfg.h"

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
#error	Gpt_Cfg: version mismatch.
#endif

#define	GPT_CHANNELS_NUMBER	8	/* Configured GTP Channels */

/*
 * Gpt Channels Configuration.
 */
const Gpt_ChannelConfigType GptChannels[] = {
  { /* TIMER 0 STM */
    GPT_CHANNEL_0_STM,			/* GptChannelId			*/
    GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		*/
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#ifdef	EE_PPCE200ZX_30_ISR
    &Gpt_Notification_Channel_0_STM,	/* GptNotificationPtr		*/
#else	/* EE_MPC5643L_TIMER_0_A_ISR	*/
    NULL_PTR,				/* GptNotificationPtr		*/
#endif	/* !EE_MPC5643L_TIMER_0_A_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON		*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* GptChannelWakeupSupport	*/
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON		*/
    20000000				/* Timer Match Valuer		*/
  },
  { /* TIMER 1 STM */
    GPT_CHANNEL_1_STM,			/* GptChannelId			*/
    GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		*/
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#ifdef	EE_PPCE200ZX_31_ISR
    &Gpt_Notification_Channel_1_STM,	/* GptNotificationPtr		*/
#else	/* EE_MPC5643L_TIMER_1_A_ISR	*/
    NULL_PTR,				/* GptNotificationPtr		*/
#endif	/* !EE_MPC5643L_TIMER_1_A_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON		*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* GptChannelWakeupSupport	*/
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON		*/
    60000000				/* Timer Match Valuer		*/
  },
  { /* TIMER 2 STM */
    GPT_CHANNEL_2_STM,			/* GptChannelId			*/
    GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		*/
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#ifdef	EE_PPCE200ZX_32_ISR
    &Gpt_Notification_Channel_2_STM,	/* GptNotificationPtr		*/
#else	/* EE_MPC5643L_TIMER_2_A_ISR	*/
    NULL_PTR,				/* GptNotificationPtr		*/
#endif	/* !EE_MPC5643L_TIMER_2_A_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON		*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* GptChannelWakeupSupport	*/
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON		*/
    80000000				/* Timer Match Valuer		*/
  },
  { /* TIMER 3 STM */
    GPT_CHANNEL_3_STM,			/* GptChannelId			*/
    GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		*/
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#ifdef	EE_PPCE200ZX_33_ISR
    &Gpt_Notification_Channel_3_STM,	/* GptNotificationPtr		*/
#else	/* EE_MPC5643L_TIMER_3_A_ISR	*/
    NULL_PTR,				/* GptNotificationPtr		*/
#endif	/* !EE_MPC5643L_TIMER_3_A_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON		*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* GptChannelWakeupSupport	*/
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON		*/
    120000000				/* Timer Match Valuer		*/
  },{0U,0U,0U,0U},{0U,0U,0U,0U},{0U,0U,0U,0U},{0U,0U,0U,0U}
};

/*
 * This container is the base of a multiple configuration set.
 */
const Gpt_ConfigType Gpt_Config[] = {
  {
    GPT_CHANNELS_NUMBER,	/* GptNumberOfGptChannels	*/
    &GptChannels[0],		/* GptChannels			*/
    FREEZE_ON,			    /* Freeze Capability: ON/OFF	*/
    0U,				        /* Initial Counter Value	*/
    1U				        /* Prescale Value		*/
  }
};
