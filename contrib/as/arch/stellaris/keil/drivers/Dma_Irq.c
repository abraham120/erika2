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
 * ma_Irq.c File for implementation of interrupt service routine (BSW00314)
 *
 * AUTOSAR-"like" DMA Driver Software Channels ISRs Source File.
 *
 * Author:  2012,  Giuseppe Serano
 */

/*
 * Dma_Irq.c file could exist depending upon implementation and also it could or
 * not include Dma.h.
 */
#include "Dma.h"

/* 
 * Dma_Irq.c shall check if the correct version of Dma.h is included.
 * This shall be done by a pre-processor check.
 *
 * The DMA module shall avoid the integration of incompatible files by the
 * following pre-processor checks:
 * for included (external) header files,
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * shall be verified.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	DMA_AR_RELEASE_MAJOR_VERSION	4
#define	DMA_AR_RELEASE_MINOR_VERSION	0

#if !defined( DMA_AR_MAJOR_VERSION ) || \
    ( DMA_AR_MAJOR_VERSION != DMA_AR_RELEASE_MAJOR_VERSION )
#error	Dma_Irq: version mismatch.
#endif

#if	( DMA_NOTIFICATIONS_API == STD_ON )

#include "ee.h"
#include "ee_irq.h"
#include "Dma_Internal.h"

#ifdef	EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR
ISR2(EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR)
{

  register EE_UREG				flags;
  register Dma_ChannelType			chidx;
  register const Dma_ChannelConfigType *	chcfgptr;

  flags = EE_hal_suspendIRQ();

  for ( chidx = 0; chidx < Dma_Global.ConfigPtr->DmaMaxChannel; chidx++ ) {

    chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

    if ( DMA_INT_STAT(chcfgptr->DmaChannelId) ) {

      DMA_INT_CLR(chcfgptr->DmaChannelId);

      if ( chcfgptr->DmaSoftwareTransferEndNotificationPtr != NULL_PTR) {

	EE_hal_resumeIRQ(flags);

	(*chcfgptr->DmaSoftwareTransferEndNotificationPtr)();

	flags = EE_hal_suspendIRQ();

      }

    }

  }

  EE_hal_resumeIRQ(flags);

  

}
#endif	/* EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR */

#ifdef	EE_CORTEX_MX_UDMA_ERR_ISR
ISR2(EE_CORTEX_MX_UDMA_ERR_ISR)
{

  register EE_UREG				flags;
  register Dma_ChannelType			chidx;
  register const Dma_ChannelConfigType *	chcfgptr;

  flags = EE_hal_suspendIRQ();

  for ( chidx = 0; chidx < Dma_Global.ConfigPtr->DmaMaxChannel; chidx++ ) {

    chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

    if ( 
      !DMA_CHANNEL_STAT(chcfgptr->DmaChannelId) &&
      ( 
	DmaControlTable[chcfgptr->DmaChannelId].DmaControl & ( 
	  UDMA_CHCTL_XFERSIZE_M  | UDMA_CHCTL_XFERMODE_M
	)
      ) &&
      ( chcfgptr->DmaTransferErrorNotificationPtr != NULL_PTR )
    ) {

      EE_hal_resumeIRQ(flags);

      (*chcfgptr->DmaTransferErrorNotificationPtr)();

      flags = EE_hal_suspendIRQ();

    }

  }

  /* DMA Error Check. */
  if ( DMA_ERR_GET() ) {

    /* DMA Error Clean. */
    DMA_ERR_CLR();

  }

  EE_hal_resumeIRQ(flags);

}
#endif	/* EE_CORTEX_MX_UDMA_SOFT_TRANSF_ISR */

#endif	/* ( DMA_NOTIFICATIONS_API == STD_ON ) */

