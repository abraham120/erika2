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
 * GPT368:	Gpt_Cfg.c Module configuration file, if pre-compile const are
 * 		used (BSW00345, BSW00419)
 *
 * fake-druid AUTOSAR GPT Driver Configuration Source File.
 *
 *  Configured for (GPT): Renesas RX210R5F5210x
 *
 *  @author	Giuanluca Franchino
 *  @date	2012
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

#define	GPT_CHANNELS_NUMBER	6	/* Configured GTP Channels */

//#define GPT_EN_ALL_NOTIF

#ifdef GPT_EN_ALL_NOTIF

#define GPT_TMR0_EN_NOTIFICATION STD_ON
#define GPT_CMT0_EN_NOTIFICATION STD_ON
#define GPT_MTU0_EN_NOTIFICATION STD_ON
#define GPT_TMR1_EN_NOTIFICATION STD_ON
#define GPT_CMT1_EN_NOTIFICATION STD_ON
#define GPT_MTU1_EN_NOTIFICATION STD_ON

#else

#define GPT_TMR0_EN_NOTIFICATION STD_OFF
#define GPT_CMT0_EN_NOTIFICATION STD_OFF
#define GPT_MTU0_EN_NOTIFICATION STD_OFF
#define GPT_TMR1_EN_NOTIFICATION STD_OFF
#define GPT_CMT1_EN_NOTIFICATION STD_OFF
#define GPT_MTU1_EN_NOTIFICATION STD_OFF

#endif

/*
 * Gpt Channels Configuration.
 */
const Gpt_ChannelConfigType GptChannels[] = {
		{ /* TIMER TMR0 */
			GPT_CHANNEL_TMR0,			/* GptChannelId			      */
			GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		      */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#if	 (defined(EE_RX200_CMIA0_ISR) && GPT_TMR0_EN_NOTIFICATION)
			&Gpt_Notification_Channel_TMR0,	/* GptNotificationPtr	*/
#else	/* EE_RX200_CMIA0_ISR	*/
			NULL_PTR,				/* GptNotificationPtr		      */
#endif	/* !EE_RX200_CMIA0_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON	*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
			TRUE,				/* GptChannelWakeupSupport	      */
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON	*/
			/* GptChannelHWConfig: */
			/* Timer Clock = Peripheral clock (PCLKB) / 8,
			 * Timer cleared cleared by compare match A. */
			GPT_HW_TMR_PCLK8 | GPT_HW_TMR_CLRA,		
    
	},
	{ /* TIMER TMR1 */
		GPT_CHANNEL_TMR1,			/* GptChannelId			      */
		GPT_CH_MODE_ONESHOT,		/* GptChannelMode		      */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#if	 (defined(EE_RX200_CMIB1_ISR) && GPT_TMR1_EN_NOTIFICATION)
		&Gpt_Notification_Channel_TMR1,	/* GptNotificationPtr	*/
#else	/* EE_RX200_CMIB1_ISR	*/
		NULL_PTR,				/* GptNotificationPtr		      */
#endif	/* !EE_RX200_CMIB1_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON	*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
		TRUE,				/* GptChannelWakeupSupport	      */
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON	*/
		/* GptChannelHWConfig: */
		/* Timer Clock = Peripheral clock (PCLKB) / 8,
		 * Timer cleared cleared by compare match A. */
		GPT_HW_TMR_PCLK8 | GPT_HW_TMR_CLRB,		
		
	},	
	{ /* TIMER CMT0 */
		GPT_CHANNEL_CMT0,			/* GptChannelId			      */
		GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		      */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#if	 (defined(EE_RX200_CMI0_ISR) && GPT_CMT0_EN_NOTIFICATION)	
		&Gpt_Notification_Channel_CMT0,	/* GptNotificationPtr	*/
#else	/* EE_RX200_CMI0_ISR	*/
		NULL_PTR,				/* GptNotificationPtr		      */
#endif	/* !EE_RX200_CMI0_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON	*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
		TRUE,				/* GptChannelWakeupSupport	      */
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON	*/
		/* GptChannelHWConfig: */
		/* Timer Clock = Peripheral clock (PCLKB) / 8,
		*/
		GPT_HW_CMT_PCLK8,		

	},
	{ /* TIMER CMT1 */
		GPT_CHANNEL_CMT1,			/* GptChannelId			      */
		GPT_CH_MODE_ONESHOT,		/* GptChannelMode		      */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#if (defined(EE_RX200_CMI1_ISR ) && GPT_CMT1_EN_NOTIFICATION)
		&Gpt_Notification_Channel_CMT1,	/* GptNotificationPtr	*/
#else	/* EE_RX200_CMI1_ISR	*/
		NULL_PTR,				/* GptNotificationPtr		      */
#endif	/* !EE_RX200_CMI1_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON	*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
		TRUE,				/* GptChannelWakeupSupport	      */
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON	*/
		/* GptChannelHWConfig: */
		/* Timer Clock = Peripheral clock (PCLKB) / 8,
		 */
		GPT_HW_CMT_PCLK8,		
		
	},
	{ /* TIMER MTU0 */
		GPT_CHANNEL_MTU0,			/* GptChannelId			      */
		GPT_CH_MODE_CONTINUOUS,		/* GptChannelMode		      */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#if	 (defined(EE_RX200_TGIA0_ISR) && GPT_MTU0_EN_NOTIFICATION)		
		&Gpt_Notification_Channel_MTU0,	/* GptNotificationPtr	*/
#else	/* EE_RX200_TGIA0_ISR	*/
		NULL_PTR,				/* GptNotificationPtr		      */
#endif	/* !EE_RX200_TGIA0_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON	*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
		TRUE,				/* GptChannelWakeupSupport	      */
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON	*/
		/* GptChannelHWConfig: */
		/* Timer Clock = Peripheral clock (PCLKB) / 16,
		*/
		GPT_HW_MTU_PCLK16  | GPT_HW_MTU_CLRA,
	},
	{ /* TIMER MTU1 */
		GPT_CHANNEL_MTU1,			/* GptChannelId			      */
		GPT_CH_MODE_ONESHOT,		/* GptChannelMode		      */
#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
#if	 (defined(EE_RX200_TGIB1_ISR) && GPT_MTU1_EN_NOTIFICATION)	
		&Gpt_Notification_Channel_MTU1,	/* GptNotificationPtr	*/
#else	/* EE_RX200_TGIB1_ISR	*/
		NULL_PTR,				/* GptNotificationPtr		      */
#endif	/* !EE_RX200_TGIB1_ISR	*/
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON	*/
#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
		TRUE,				/* GptChannelWakeupSupport	      */
#endif	/* GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON	*/
		/* GptChannelHWConfig: */
		/* Timer Clock = Peripheral clock (PCLKB) / 16,
		 */
		GPT_HW_MTU_PCLK16 | GPT_HW_MTU_CLRB,
	},
};

/*
 * This container is the base of a multiple configuration set.
 */
const Gpt_ConfigType Gpt_Config[] = {
  {
    GPT_CHANNELS_NUMBER,	/* GptNumberOfGptChannels	*/
    &GptChannels[0]		/* GptChannels			*/
  }
};
