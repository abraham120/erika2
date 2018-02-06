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
 * AUTOSAR-"like" SCI Driver Channels ISRs Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

#define	SCI_AR_RELEASE_MAJOR_VERSION	4
#define	SCI_AR_RELEASE_MINOR_VERSION	0

#include "Sci.h"

/*
 * For included (external) header files:
 * - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * shall be verified.
 */
#if !defined( SCI_AR_MAJOR_VERSION ) || \
    ( SCI_AR_MAJOR_VERSION != SCI_AR_RELEASE_MAJOR_VERSION )
#error	Sci_Irq: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"

#include "Sci_Internal.h"

/*
 * SCI Global Configuration Reference.
 */
typedef struct
{
  boolean			Init;		/* SCI Driver Initialized? */

  const Sci_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Sci_GlobalType;
extern Sci_GlobalType Sci_Global;

#if ( SCI_NOTIFICATIONS_API == STD_ON )

#if ( \
  defined(EE_CORTEX_MX_UART_0_ISR) || \
  defined(EE_CORTEX_MX_UART_1_ISR) || \
  defined(EE_CORTEX_MX_UART_2_ISR) || \
  defined(EE_CORTEX_MX_UART_3_ISR) || \
  defined(EE_CORTEX_MX_UART_4_ISR) || \
  defined(EE_CORTEX_MX_UART_5_ISR) || \
  defined(EE_CORTEX_MX_UART_6_ISR) || \
  defined(EE_CORTEX_MX_UART_7_ISR) \
)
void Sci_Isr(
  Sci_ChannelType Channel
)
{

  register EE_FREG	flags;
  register uint32	is;
  register uint32	ch;

  flags = EE_hal_suspendIRQ();

  /* Driver Initialization Check. */
  if ( Sci_Global.Init == TRUE ) {

    /* Channel Look-up */
    for (
      ch = 0;
      (
	(ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
	(Sci_Global.ConfigPtr->SciChannels[ch].SciChannelId != Channel)
      );
      ch++
    ) {
      ;
    }

    /* Channel Configured Check. */
    if ( ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) {

	is = ( UART_RIS(Channel) | UART_MIS(Channel) );
	UART_INT_CLEAR(Channel, UART_INT_ALL);

      /* Receception Errors */
      if (
	(
	  is & (
	    UART_MIS_OEMIS | /* UART Overrun Error Masked Interrupt Status    */
	    UART_MIS_BEMIS | /* UART Break Error Masked Interrupt Status      */
	    UART_MIS_PEMIS | /* UART Parity Error Masked Interrupt Status     */
	    UART_MIS_FEMIS | /* UART Framing Error Masked Interrupt Status    */
	    UART_MIS_RTMIS   /* UART Receive Time-Out Masked Interrupt Status */
	  )
	) 
      ) {

	/* Dummy read preventing RX Lock. */
	while ( !UART_RX_FIFO_EMPTY(Channel) ) {
	  UART_RX_DATA(Channel);
	}

	if (
	  Sci_Global.ConfigPtr->SciChannels[ch].SciRxErrNotificationPtr !=
	  NULL_PTR
	) {

	  EE_hal_resumeIRQ(flags);

	  /* Call Reception Errors Notifications Callback. */
	  (*(Sci_Global.ConfigPtr->SciChannels[ch].SciRxErrNotificationPtr))();

	  flags = EE_hal_suspendIRQ();

	}

      }

      /* Trasnmission Successful */
      else if ( ( is & UART_MIS_TXMIS ) ) {

	if (
	  Sci_Global.ConfigPtr->SciChannels[ch].SciTxNotificationPtr !=
	  NULL_PTR
	) {

	  EE_hal_resumeIRQ(flags);

	  /* Call Transmission Notifications Callback. */
	  (*(Sci_Global.ConfigPtr->SciChannels[ch].SciTxNotificationPtr))();

	  flags = EE_hal_suspendIRQ();

	}

      }

      /* Reception Successful */
      else /* if ( (mis & UART_MIS_RXMIS) || (ris & UART_RIS_RXRIS) ) */ {

	if (
	  Sci_Global.ConfigPtr->SciChannels[ch].SciRxNotificationPtr !=
	  NULL_PTR
	) {

	  EE_hal_resumeIRQ(flags);

	  /* Call Reception Notifications Callback. */
	  (*(Sci_Global.ConfigPtr->SciChannels[ch].SciRxNotificationPtr))();

	  flags = EE_hal_suspendIRQ();

	}

      }

    }	/* ch < cfg->SciNumberOfSciChannels */

  }	/* init == TRUE */

  EE_hal_resumeIRQ(flags);

}
#endif	/*
	 * EE_CORTEX_MX_UART_0_ISR || EE_CORTEX_MX_UART_1_ISR ||
	 * EE_CORTEX_MX_UART_2_ISR || EE_CORTEX_MX_UART_3_ISR ||
	 * EE_CORTEX_MX_UART_4_ISR || EE_CORTEX_MX_UART_5_ISR ||
	 * EE_CORTEX_MX_UART_6_ISR || EE_CORTEX_MX_UART_7_ISR
	 */

#ifdef	EE_CORTEX_MX_UART_0_ISR
ISR2(EE_CORTEX_MX_UART_0_ISR) { Sci_Isr(SCI_CHANNEL_0); }
#endif

#ifdef	EE_CORTEX_MX_UART_1_ISR
ISR2(EE_CORTEX_MX_UART_1_ISR) { Sci_Isr(SCI_CHANNEL_1); }
#endif

#ifdef	EE_CORTEX_MX_UART_2_ISR
ISR2(EE_CORTEX_MX_UART_2_ISR) { Sci_Isr(SCI_CHANNEL_2); }
#endif

#ifdef	EE_CORTEX_MX_UART_3_ISR
ISR2(EE_CORTEX_MX_UART_3_ISR) { Sci_Isr(SCI_CHANNEL_3); }
#endif

#ifdef	EE_CORTEX_MX_UART_4_ISR
ISR2(EE_CORTEX_MX_UART_4_ISR) { Sci_Isr(SCI_CHANNEL_4); }
#endif

#ifdef	EE_CORTEX_MX_UART_5_ISR
ISR2(EE_CORTEX_MX_UART_5_ISR) { Sci_Isr(SCI_CHANNEL_5); }
#endif

#ifdef	EE_CORTEX_MX_UART_6_ISR
ISR2(EE_CORTEX_MX_UART_6_ISR) { Sci_Isr(SCI_CHANNEL_6); }
#endif

#ifdef	EE_CORTEX_MX_UART_7_ISR
ISR2(EE_CORTEX_MX_UART_7_ISR) { Sci_Isr(SCI_CHANNEL_7); }
#endif

#endif	/* SCI_NOTIFICATIONS_API */

