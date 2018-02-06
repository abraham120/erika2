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
 * GPT372:	Gpt_Irq.c File for implementation of interrupt service routine
 * 		(BSW00314)
 *
 * AUTOSAR-"like" GPT Driver Channels ISRs Source File.
 *
 * Author:  2012,  Gianluca Franchino
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

#include "Gpt.h"
#include "Gpt_Internal.h"

/*
 * Channel expired flags. 
 */
extern uint32 exp_flag;

/*
 * TMR module TCNT values.
 */
extern uint8* Gpt_tmr_tcnt_val;
                       
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
	defined(GPT_CHANNEL_TMR0) && \
	(defined(EE_RX200_CMIA0_ISR) || defined(EE_RX200_CMIB0_ISR)) \
  ) || \
  ( \
	defined(GPT_CHANNEL_TMR1) && \
	(defined(EE_RX200_CMIA1_ISR) || defined(EE_RX200_CMIB1_ISR)) \
  ) || \
  ( \
	defined(GPT_CHANNEL_TMR2) && \
	(defined(EE_RX200_CMIA2_ISR) || defined(EE_RX200_CMIB2_ISR)) \
  ) || \
  ( \
	defined(GPT_CHANNEL_TMR3) && \
	(defined(EE_RX200_CMIA3_ISR) || defined(EE_RX200_CMIB3_ISR)) \
  ) || \
  ( \
	defined(GPT_CHANNEL_TMR01) && \
	(defined(EE_RX200_CMIA0_ISR) || defined(EE_RX200_CMIB0_ISR)) \
  ) || \
  ( \
	defined(GPT_CHANNEL_TMR12) && \
	(defined(EE_RX200_CMIA1_ISR) || defined(EE_RX200_CMIB1_ISR)) \
  ) || \
  ( \
	defined(GPT_CHANNEL_CMT0) && defined(EE_RX200_CMI0_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_CMT1) && defined(EE_RX200_CMI1_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_CMT2) && defined(EE_RX200_CMI2_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_CMT3) && defined(EE_RX200_CMI3_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGIA0_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGIB0_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGIC0_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGID0_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU1) && defined(EE_RX200_TGIA1_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU1) && defined(EE_RX200_TGIB1_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU2) && defined(EE_RX200_TGIA2_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU2) && defined(EE_RX200_TGIB2_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGIA3_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGIB3_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGIC3_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGID3_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGIA4_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGIB4_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGIC4_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGID4_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU5U) && defined(EE_RX200_TGIU5_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU5V) && defined(EE_RX200_TGIV5_ISR) \
  ) || \
  ( \
	defined(GPT_CHANNEL_MTU5W) && defined(EE_RX200_TGIW5_ISR) \
  )\
)
		
static void Gpt_Isr(Gpt_ChannelType	Channel)
{

	register EE_FREG		flags;
	register Gpt_ChannelType	ch;
	register uint16				tcnt;

	flags = EE_hal_suspendIRQ();

	if ( Gpt_Global.Init == TRUE ) {

		/* Channel Look-up */
		for (ch = 0; ( ( ch < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
    		( Gpt_Global.ConfigPtr->GptChannels[ch].GptChannelId != Channel )); 
		ch++) { ; }

		/*
		 * Stop the timer if one-shot mode is selected.
		 */
		if (Gpt_Global.ConfigPtr->GptChannels[ch].GptChannelMode == 
				GPT_CH_MODE_ONESHOT) {
			/*if (Channel < GPT_CHANNEL_CMT0) {
				Gpt_DisableChannel(Channel);
			} else {
				Gpt_tmr_stop(Channel);
			}*/
			tcnt = Gpt_get_tmr_tcnt(Channel);
			GPT_CLEAR_TMR_CMIEA(Channel);
			GPT_CLEAR_TMR_CMIEB(Channel);
			//Gpt_tmr_dis_icu_int(Channel);
			if (Channel < GPT_CHANNEL_CMT0) {
				if (Channel < GPT_INTERNAL_CHANNEL_TMR01) {
					Gpt_tmr_tcnt_val[Channel] = (uint8) (tcnt);
				} else if (Channel == GPT_INTERNAL_CHANNEL_TMR01) {
					Gpt_tmr_tcnt_val[0] = (uint8) (tcnt >> 8);
					Gpt_tmr_tcnt_val[1] = (uint8) (tcnt);
				} else {
					Gpt_tmr_tcnt_val[2] = (uint8) (tcnt >> 8);
					Gpt_tmr_tcnt_val[3] = (uint8) (tcnt);
				}
			} else {
				Gpt_tmr_stop(Channel);
			}
			GPT_CLEAR_FLAG(start_flag, Channel);
			GPT_SET_FLAG(exp_flag, Channel);
		}
		
		/* Notification Callback Call. */
		if ( ( ch < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
				( Gpt_Global.ConfigPtr->GptChannels[ch].GptNotificationPtr 
						!= NULL_PTR ) ) {

			EE_hal_resumeIRQ(flags);

			(*(Gpt_Global.ConfigPtr->GptChannels[ch].GptNotificationPtr))();

			flags = EE_hal_suspendIRQ();

		}

	}

	EE_hal_resumeIRQ(flags);

}

#endif

#if	(defined(GPT_CHANNEL_TMR0) && defined(EE_RX200_CMIA0_ISR))
#pragma interrupt (EE_RX200_CMIA0_ISR)
ISR2(EE_RX200_CMIA0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_TMR0);
}
#endif

#if	(defined(GPT_CHANNEL_TMR0) && defined(EE_RX200_CMIB0_ISR))
#pragma interrupt (EE_RX200_CMIB0_ISR)
ISR2(EE_RX200_CMIB0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_TMR0);
}
#endif

#if	( (defined(GPT_CHANNEL_TMR1) || defined(GPT_CHANNEL_TMR12) ) \
		&& defined(EE_RX200_CMIA1_ISR))
#pragma interrupt (EE_RX200_CMIA1_ISR)
ISR2(EE_RX200_CMIA1_ISR)
{
#if (defined(GPT_CHANNEL_TMR1)
	Gpt_Isr(GPT_CHANNEL_TMR1);
#else 
	Gpt_Isr(GPT_CHANNEL_TMR12);
#endif
}
#endif

#if	(defined(GPT_CHANNEL_TMR1) && defined(EE_RX200_CMIB1_ISR))
#pragma interrupt (EE_RX200_CMIB1_ISR)
ISR2(EE_RX200_CMIB1_ISR)
{
#if (defined(GPT_CHANNEL_TMR1))
	Gpt_Isr(GPT_CHANNEL_TMR1);
#else 
	Gpt_Isr(GPT_CHANNEL_TMR12);
#endif
}
#endif

#if	(defined(GPT_CHANNEL_TMR2) && defined(EE_RX200_CMIA2_ISR))
#pragma interrupt (EE_RX200_CMIA2_ISR)
ISR2(EE_RX200_CMIA2_ISR)
{
	Gpt_Isr(GPT_CHANNEL_TMR2);
}
#endif

#if	(defined(GPT_CHANNEL_TMR2) && defined(EE_RX200_CMIB2_ISR))
#pragma interrupt (GPT_CHANNEL_TMR2)
ISR2(EE_RX200_CMIB2_ISR)
{
	Gpt_Isr(GPT_CHANNEL_TMR2);
}
#endif

#if	(defined(GPT_CHANNEL_TMR3) && defined(EE_RX200_CMIA3_ISR))
#pragma interrupt (EE_RX200_CMIA3_ISR)
ISR2(EE_RX200_CMIA3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_TMR3);
}
#endif

#if	(defined(GPT_CHANNEL_TMR3) && defined(EE_RX200_CMIB3_ISR))
#pragma interrupt (EE_RX200_CMIB3_ISR)
ISR2(EE_RX200_CMIB3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_TMR3);
}
#endif

#if (defined(GPT_CHANNEL_CMT0) && defined(EE_RX200_CMI0_ISR))
#pragma interrupt (EE_RX200_CMI0_ISR)
ISR2(EE_RX200_CMI0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_CMT0);
}
#endif

#if (defined(GPT_CHANNEL_CMT1) && defined(EE_RX200_CMI1_ISR))
#pragma interrupt (EE_RX200_CMI1_ISR)
ISR2(EE_RX200_CMI1_ISR)
{
	Gpt_Isr(GPT_CHANNEL_CMT1);
}
#endif

#if (defined(GPT_CHANNEL_CMT2) && defined(EE_RX200_CMI2_ISR))
#pragma interrupt (EE_RX200_CMI2_ISR)
ISR2(EE_RX200_CMI2_ISR)
{
	Gpt_Isr(GPT_CHANNEL_CMT2);
}
#endif

#if (defined(GPT_CHANNEL_CMT3) && defined(EE_RX200_CMI3_ISR))
#pragma interrupt (EE_RX200_CMI3_ISR)
ISR2(EE_RX200_CMI3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_CMT3);
}
#endif

#if (defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGIA0_ISR))
#pragma interrupt (EE_RX200_TGIA0_ISR)
ISR2(EE_RX200_TGIA0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU0);
}
#endif

#if (defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGIB0_ISR))
#pragma interrupt (EE_RX200_TGIB0_ISR)
ISR2(EE_RX200_TGIB0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU0);
}
#endif

#if (defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGIC0_ISR))
#pragma interrupt (EE_RX200_TGIC0_ISR)
ISR2(EE_RX200_TGIC0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU0);
}
#endif

#if (defined(GPT_CHANNEL_MTU0) && defined(EE_RX200_TGID0_ISR))
#pragma interrupt (EE_RX200_TGID0_ISR)
ISR2(EE_RX200_TGID0_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU0);
}
#endif

#if (defined(GPT_CHANNEL_MTU1) && defined(EE_RX200_TGIA1_ISR))
#pragma interrupt (EE_RX200_TGIA1_ISR)
ISR2(EE_RX200_TGIA1_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU1);
}
#endif

#if (defined(GPT_CHANNEL_MTU1) && defined(EE_RX200_TGIB1_ISR))
#pragma interrupt (EE_RX200_TGIB1_ISR)
ISR2(EE_RX200_TGIB1_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU1);
}
#endif

#if (defined(GPT_CHANNEL_MTU2) && defined(EE_RX200_TGIA2_ISR))
#pragma interrupt (EE_RX200_TGIA2_ISR)
ISR2(EE_RX200_TGIA2_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU2);
}
#endif

#if (defined(GPT_CHANNEL_MTU2) && defined(EE_RX200_TGIB2_ISR))
#pragma interrupt (EE_RX200_TGIB2_ISR)
ISR2(EE_RX200_TGIB2_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU2);
}
#endif

#if (defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGIA3_ISR))
#pragma interrupt (EE_RX200_TGIA3_ISR)
ISR2(EE_RX200_TGIA3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU3);
}
#endif

#if (defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGIB3_ISR))
#pragma interrupt (EE_RX200_TGIB3_ISR)
ISR2(EE_RX200_TGIB3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU3);
}
#endif

#if (defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGIC3_ISR))
#pragma interrupt (EE_RX200_TGIC3_ISR)
ISR2(EE_RX200_TGIC3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU3);
}
#endif

#if (defined(GPT_CHANNEL_MTU3) && defined(EE_RX200_TGID3_ISR))
#pragma interrupt (EE_RX200_TGID3_ISR)
ISR2(EE_RX200_TGID3_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU3);
}
#endif

#if (defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGIA4_ISR))
#pragma interrupt (EE_RX200_TGIA4_ISR)
ISR2(EE_RX200_TGIA4_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU4);
}
#endif

#if (defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGIB4_ISR))
#pragma interrupt (EE_RX200_TGIB4_ISR)
ISR2(EE_RX200_TGIB4_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU4);
}
#endif

#if (defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGIC4_ISR))
#pragma interrupt (EE_RX200_TGIC4_ISR)
ISR2(EE_RX200_TGIC4_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU4);
}
#endif

#if (defined(GPT_CHANNEL_MTU4) && defined(EE_RX200_TGID4_ISR))
#pragma interrupt (EE_RX200_TGID4_ISR)
ISR2(EE_RX200_TGID4_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU4);
}
#endif

#if (defined(GPT_CHANNEL_MTU5U) && defined(EE_RX200_TGIU5_ISR))
#pragma interrupt (EE_RX200_TGIU5_ISR)
ISR2(EE_RX200_TGIU5_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU5U);
}
#endif

#if (defined(GPT_CHANNEL_MTU5V) && defined(EE_RX200_TGIV5_ISR))
#pragma interrupt (EE_RX200_TGIV5_ISR)
ISR2(EE_RX200_TGIV5_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU5)V;
}
#endif

#if (defined(GPT_CHANNEL_MTU5W) && defined(EE_RX200_TGIW5_ISR))
#pragma interrupt (EE_RX200_TGIW5_ISR)
ISR2(EE_RX200_TGIW5_ISR)
{
	Gpt_Isr(GPT_CHANNEL_MTU5W);
}
#endif

#endif	/* GPT_NOTIFICATIONS_API */
