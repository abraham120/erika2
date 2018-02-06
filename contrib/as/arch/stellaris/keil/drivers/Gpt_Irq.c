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
 * GPT372:	Gpt_Irq.c File for implementation of interrupt service routine
 * 		(BSW00314)
 *
 * AUTOSAR-"like" GPT Driver Channels ISRs Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

/*
 * GPT261:	Gpt_Irq.c shall include Gpt.h for the prototype declaration of
 * 		the notification functions. (BSW164)
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
#error	Gpt_Irq: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"

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
 * GPT Driver Global Configuration Reference
 */
extern Gpt_GlobalType Gpt_Global;

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )

#if ( \
  ( \
    defined(EE_CORTEX_MX_TIMER_0_A_ISR) && ( \
      defined(GPT_CHANNEL_0_A) || defined(GPT_CHANNEL_J_0) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_0_B_ISR) && defined(GPT_CHANNEL_0_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_1_A_ISR) && ( \
      defined(GPT_CHANNEL_1_A) || defined(GPT_CHANNEL_J_1) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_1_B_ISR) && defined(GPT_CHANNEL_1_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_2_A_ISR) && ( \
      defined(GPT_CHANNEL_2_A) || defined(GPT_CHANNEL_J_2) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_2_B_ISR) && defined(GPT_CHANNEL_2_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_3_A_ISR) && ( \
      defined(GPT_CHANNEL_3_A) || defined(GPT_CHANNEL_J_3) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_3_B_ISR) && defined(GPT_CHANNEL_3_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_4_A_ISR) && ( \
      defined(GPT_CHANNEL_4_A) || defined(GPT_CHANNEL_J_4) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_4_B_ISR) && defined(GPT_CHANNEL_4_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_5_A_ISR) && ( \
      defined(GPT_CHANNEL_5_A) || defined(GPT_CHANNEL_J_5) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_TIMER_5_B_ISR) && defined(GPT_CHANNEL_5_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR) && ( \
      defined(GPT_CHANNEL_W_0_A) || defined (GPT_CHANNEL_J_W_0) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR) && defined(GPT_CHANNEL_W_0_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR) && ( \
      defined(GPT_CHANNEL_W_1_A) || defined (GPT_CHANNEL_J_W_1) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR) && defined(GPT_CHANNEL_W_1_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR) && ( \
      defined(GPT_CHANNEL_W_2_A) || defined (GPT_CHANNEL_J_W_2) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR) && defined(GPT_CHANNEL_W_2_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR) && ( \
      defined(GPT_CHANNEL_W_3_A) || defined (GPT_CHANNEL_J_W_3) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR) && defined(GPT_CHANNEL_W_3_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR) && ( \
      defined(GPT_CHANNEL_W_4_A) || defined (GPT_CHANNEL_J_W_4) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR) && defined(GPT_CHANNEL_W_4_B) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR) && ( \
      defined(GPT_CHANNEL_W_5_A) || defined (GPT_CHANNEL_J_W_5) \
    ) \
  ) || \
  ( \
    defined(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR) && defined(GPT_CHANNEL_W_5_B) \
  ) \
)
static void Gpt_Isr(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register uint32		is;
  register Gpt_ChannelType	ch;

  flags = EE_hal_suspendIRQ();
  is = GPT_GET_RIS(Channel) | GPT_GET_MIS(Channel);
  GPT_INT_CLR(
    Channel,
    GPT_TMR_INT_TAM | GPT_TMR_INT_CAE | GPT_TMR_INT_CAM |
    GPT_TMR_INT_TBM | GPT_TMR_INT_CBE | GPT_TMR_INT_CBM |
    GPT_TMR_INT_WUE | GPT_TMR_INT_RTC
  );

  GPT_TMR_TIMEOUT_INT_CLR(Channel);

  if (
    ( Gpt_Global.Init == TRUE ) &&
    ( is & ( GPT_TMR_INT_TATO | GPT_TMR_INT_TBTO ) )
  ) {

    /* Channel Look-up */
    for (
      ch = 0;
      (
	( ch < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
	( Gpt_Global.ConfigPtr->GptChannels[ch].GptChannelId != Channel ) 
      );
      ch++
    ) {
      ;
    }

    /* Notification Callback Call. */
    if (
      ( ch < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[ch].GptNotificationPtr != NULL_PTR )
    ) {

      EE_hal_resumeIRQ(flags);

      (*(Gpt_Global.ConfigPtr->GptChannels[ch].GptNotificationPtr))();

      flags = EE_hal_suspendIRQ();

    }

  }

  EE_hal_resumeIRQ(flags);

}
#endif

#if	( \
  defined(EE_CORTEX_MX_TIMER_0_A_ISR) && ( \
    defined(GPT_CHANNEL_0_A) || defined(GPT_CHANNEL_J_0) \
  ) \
)
ISR2(EE_CORTEX_MX_TIMER_0_A_ISR)
{
#ifdef	GPT_CHANNEL_0_A
  Gpt_Isr(GPT_CHANNEL_0_A);
#else	/* GPT_CHANNEL_0_A */
  Gpt_Isr(GPT_CHANNEL_J_0);
#endif	/* GPT_CHANNEL_J_0 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_0_A_ISR) && (
	 * 		defined(GPT_CHANNEL_0_A) || defined(GPT_CHANNEL_J_0)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_0_B_ISR) && defined(GPT_CHANNEL_0_B) \
)
ISR2(EE_CORTEX_MX_TIMER_0_B_ISR) { Gpt_Isr(GPT_CHANNEL_0_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_0_B_ISR) && defined(GPT_CHANNEL_0_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_1_A_ISR) && ( \
    defined(GPT_CHANNEL_1_A) || defined(GPT_CHANNEL_J_1) \
  ) \
)
ISR2(EE_CORTEX_MX_TIMER_1_A_ISR)
{
#ifdef	GPT_CHANNEL_1_A
  Gpt_Isr(GPT_CHANNEL_1_A);
#else	/* GPT_CHANNEL_1_A */
  Gpt_Isr(GPT_CHANNEL_J_1);
#endif	/* GPT_CHANNEL_J_1 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_1_A_ISR) && (
	 * 		defined(GPT_CHANNEL_1_A) || defined(GPT_CHANNEL_J_1)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_1_B_ISR) && defined(GPT_CHANNEL_1_B) \
)
ISR2(EE_CORTEX_MX_TIMER_1_B_ISR) { Gpt_Isr(GPT_CHANNEL_1_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_1_B_ISR) && defined(GPT_CHANNEL_1_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_2_A_ISR) && ( \
    defined(GPT_CHANNEL_2_A) || defined(GPT_CHANNEL_J_2) \
  ) \
)
ISR2(EE_CORTEX_MX_TIMER_2_A_ISR)
{
#ifdef	GPT_CHANNEL_2_A
  Gpt_Isr(GPT_CHANNEL_2_A);
#else	/* GPT_CHANNEL_2_A */
  Gpt_Isr(GPT_CHANNEL_J_2);
#endif	/* GPT_CHANNEL_J_2 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_2_A_ISR) && (
	 * 		defined(GPT_CHANNEL_2_A) || defined(GPT_CHANNEL_J_2)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_2_B_ISR) && defined(GPT_CHANNEL_2_B) \
)
ISR2(EE_CORTEX_MX_TIMER_2_B_ISR) { Gpt_Isr(GPT_CHANNEL_2_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_2_B_ISR) && defined(GPT_CHANNEL_2_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_3_A_ISR) && ( \
    defined(GPT_CHANNEL_3_A) || defined(GPT_CHANNEL_J_3) \
  ) \
)
ISR2(EE_CORTEX_MX_TIMER_3_A_ISR)
{
#ifdef	GPT_CHANNEL_3_A
  Gpt_Isr(GPT_CHANNEL_3_A);
#else	/* GPT_CHANNEL_3_A */
  Gpt_Isr(GPT_CHANNEL_J_3);
#endif	/* GPT_CHANNEL_J_3 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_3_A_ISR) && (
	 * 		defined(GPT_CHANNEL_3_A) || defined(GPT_CHANNEL_J_3)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_3_B_ISR) && defined(GPT_CHANNEL_3_B) \
)
ISR2(EE_CORTEX_MX_TIMER_3_B_ISR) { Gpt_Isr(GPT_CHANNEL_3_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_3_B_ISR) && defined(GPT_CHANNEL_3_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_4_A_ISR) && ( \
    defined(GPT_CHANNEL_4_A) || defined(GPT_CHANNEL_J_4) \
  ) \
)
ISR2(EE_CORTEX_MX_TIMER_4_A_ISR)
{
#ifdef	GPT_CHANNEL_4_A
  Gpt_Isr(GPT_CHANNEL_4_A);
#else	/* GPT_CHANNEL_4_A */
  Gpt_Isr(GPT_CHANNEL_J_4);
#endif	/* GPT_CHANNEL_J_4 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_4_A_ISR) && (
	 * 		defined(GPT_CHANNEL_4_A) || defined(GPT_CHANNEL_J_4)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_4_B_ISR) && defined(GPT_CHANNEL_4_B) \
)
ISR2(EE_CORTEX_MX_TIMER_4_B_ISR) { Gpt_Isr(GPT_CHANNEL_4_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_4_B_ISR) && defined(GPT_CHANNEL_4_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_5_A_ISR) && ( \
    defined(GPT_CHANNEL_5_A) || defined(GPT_CHANNEL_J_5) \
  ) \
)
ISR2(EE_CORTEX_MX_TIMER_5_A_ISR)
{
#ifdef	GPT_CHANNEL_5_A
  Gpt_Isr(GPT_CHANNEL_5_A);
#else	/* GPT_CHANNEL_5_A */
  Gpt_Isr(GPT_CHANNEL_J_5);
#endif	/* GPT_CHANNEL_J_5 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_5_A_ISR) && (
	 * 		defined(GPT_CHANNEL_5_A) || defined(GPT_CHANNEL_J_5)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_TIMER_5_B_ISR) && defined(GPT_CHANNEL_5_B) \
)
ISR2(EE_CORTEX_MX_TIMER_5_B_ISR) { Gpt_Isr(GPT_CHANNEL_5_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_TIMER_5_B_ISR) && defined(GPT_CHANNEL_5_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR) && ( \
    defined(GPT_CHANNEL_W_0_A) || defined(GPT_CHANNEL_J_W_0) \
  ) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR)
{
#ifdef	GPT_CHANNEL_W_0_A
  Gpt_Isr(GPT_CHANNEL_W_0_A);
#else	/* GPT_CHANNEL_W_0_A */
  Gpt_Isr(GPT_CHANNEL_J_W_0);
#endif	/* GPT_CHANNEL_J_W_0 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_0_A_ISR) && (
	 * 		defined(GPT_CHANNEL_W_0_A) || defined(GPT_CHANNEL_J_W_0)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR) && defined(GPT_CHANNEL_W_0_B) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR) { Gpt_Isr(GPT_CHANNEL_W_0_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_0_B_ISR) &&
	 * 	defined(GPT_CHANNEL_W_0_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR) && ( \
    defined(GPT_CHANNEL_W_1_A) || defined(GPT_CHANNEL_J_W_1) \
  ) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR)
{
#ifdef	GPT_CHANNEL_W_1_A
  Gpt_Isr(GPT_CHANNEL_W_1_A);
#else	/* GPT_CHANNEL_W_1_A */
  Gpt_Isr(GPT_CHANNEL_J_W_1);
#endif	/* GPT_CHANNEL_J_W_1 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_1_A_ISR) && (
	 * 		defined(GPT_CHANNEL_W_1_A) || defined(GPT_CHANNEL_J_W_1)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR) && defined(GPT_CHANNEL_W_1_B) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR) { Gpt_Isr(GPT_CHANNEL_W_1_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_1_B_ISR) &&
	 * 	defined(GPT_CHANNEL_W_1_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR) && ( \
    defined(GPT_CHANNEL_W_2_A) || defined(GPT_CHANNEL_J_W_2) \
  ) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR)
{
#ifdef	GPT_CHANNEL_W_2_A
  Gpt_Isr(GPT_CHANNEL_W_2_A);
#else	/* GPT_CHANNEL_W_2_A */
  Gpt_Isr(GPT_CHANNEL_J_W_2);
#endif	/* GPT_CHANNEL_J_W_2 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_2_A_ISR) && (
	 * 		defined(GPT_CHANNEL_W_2_A) || defined(GPT_CHANNEL_J_W_2)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR) && defined(GPT_CHANNEL_W_2_B) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR) { Gpt_Isr(GPT_CHANNEL_W_2_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_2_B_ISR) &&
	 * 	defined(GPT_CHANNEL_W_2_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR) && ( \
    defined(GPT_CHANNEL_W_3_A) || defined(GPT_CHANNEL_J_W_3) \
  ) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR)
{
#ifdef	GPT_CHANNEL_W_3_A
  Gpt_Isr(GPT_CHANNEL_W_3_A);
#else	/* GPT_CHANNEL_W_3_A */
  Gpt_Isr(GPT_CHANNEL_J_W_3);
#endif	/* GPT_CHANNEL_J_W_3 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_3_A_ISR) && (
	 * 		defined(GPT_CHANNEL_W_3_A) || defined(GPT_CHANNEL_J_W_3)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR) && defined(GPT_CHANNEL_W_3_B) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR) { Gpt_Isr(GPT_CHANNEL_W_3_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_3_B_ISR) &&
	 * 	defined(GPT_CHANNEL_W_3_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR) && ( \
    defined(GPT_CHANNEL_W_4_A) || defined(GPT_CHANNEL_J_W_4) \
  ) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR)
{
#ifdef	GPT_CHANNEL_W_4_A
  Gpt_Isr(GPT_CHANNEL_W_4_A);
#else	/* GPT_CHANNEL_W_4_A */
  Gpt_Isr(GPT_CHANNEL_J_W_4);
#endif	/* GPT_CHANNEL_J_W_4 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_4_A_ISR) && (
	 * 		defined(GPT_CHANNEL_W_4_A) || defined(GPT_CHANNEL_J_W_4)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR) && defined(GPT_CHANNEL_W_4_B) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR) { Gpt_Isr(GPT_CHANNEL_W_4_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_4_B_ISR) &&
	 * 	defined(GPT_CHANNEL_W_4_B)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR) && ( \
    defined(GPT_CHANNEL_W_5_A) || defined(GPT_CHANNEL_J_W_5) \
  ) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR)
{
#ifdef	GPT_CHANNEL_W_5_A
  Gpt_Isr(GPT_CHANNEL_W_5_A);
#else	/* GPT_CHANNEL_W_5_A */
  Gpt_Isr(GPT_CHANNEL_J_W_5);
#endif	/* GPT_CHANNEL_J_W_5 */
}
#endif	/* 
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_5_A_ISR) && (
	 * 		defined(GPT_CHANNEL_W_5_A) || defined(GPT_CHANNEL_J_W_5)
	 * 	)
	 * )
	 */

#if	( \
  defined(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR) && defined(GPT_CHANNEL_W_5_B) \
)
ISR2(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR) { Gpt_Isr(GPT_CHANNEL_W_5_B); }
#endif	/*
	 * (
	 * 	defined(EE_CORTEX_MX_WIDE_TIMER_5_B_ISR) &&
	 * 	defined(GPT_CHANNEL_W_5_B)
	 * )
	 */

#endif	/* GPT_NOTIFICATIONS_API */
