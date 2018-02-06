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
 * Wdg_PIOscIrq.c File for implementation of interrupt service routine
 *
 * Precision Internal Oscillator (PIOsc) AUTOSAR WDG (Watchdog) Driver
 * ISRs Source File.
 *
 * Author:  2012,  Giuseppe Serano
 */

/*
 * Wdg_PIOscIrq.c has implicit access to the Wdg_PIOscCfg.h through the
 * WdgPIOsc.hfile.
 */
#include "WdgPIOsc.h"

/* 
 * WDG087:	The Wdg module shall avoid the integration of incompatible files
 * 		by the following pre-processor checks:
 * 		For included (external) header files:
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		shall be verified.
 * 		If the values are not identical to the values expected by the
 * 		Wdg module, an error shall be reported. (BSW167, BSW004)
 */
#define	WDG_PIOSC_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_PIOSC_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_PIOSC_AR_MAJOR_VERSION ) || \
    ( WDG_PIOSC_AR_MAJOR_VERSION != WDG_PIOSC_AR_RELEASE_MAJOR_VERSION )
#error	WdgPIOsc: version mismatch.
#endif

#include "ee.h"
#include "ee_irq.h"

#if	( \
		( \
			defined(__AS_CFG_WDG_PIOSC_NMI_ISR__) && \
			defined(EE_CORTEX_MX_NMI_ISR) \
		) || ( \
			defined(__AS_CFG_WDG_PIOSC_WATCHDOG_TIMER_ISR__) && \
			defined(EE_CORTEX_MX_WATCHDOG_TIMER_ISR) \
		) \
)

#include "Wdg_PIOscInternal.h"

static void Wdg_PIOsc_Isr(
  void
) {

  register EE_UREG	flags;

  flags = EE_hal_suspendIRQ();

  if ( Wdg_PIOsc_Global.State == WDG_IDLE ) {

    if ( Wdg_PIOsc_Global.Mode != WDGIF_OFF_MODE ) {

      if ( Wdg_PIOsc_Global.Expired == FALSE ) {

	Wdg_PIOsc_Global.Expired = TRUE;

	if ( Wdg_PIOsc_Global.Mode == WDGIF_FAST_MODE ) {

	  if ( 
	    ( Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast != NULL_PTR ) &&
	    (
	    Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgNotificationPtr !=
	      NULL_PTR 
	    )
	  ) {

	    EE_hal_resumeIRQ(flags);

	(*(Wdg_PIOsc_Global.ConfigPtr->WdgSettingsFast->WdgNotificationPtr))();

	    flags = EE_hal_suspendIRQ();

	  }

	}
	else {

	  if (
	    ( Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow != NULL_PTR ) &&
	    (
	    Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgNotificationPtr !=
	      NULL_PTR
	    )
	  ) {

	    EE_hal_resumeIRQ(flags);

	(*(Wdg_PIOsc_Global.ConfigPtr->WdgSettingsSlow->WdgNotificationPtr))();

	    flags = EE_hal_suspendIRQ();

	  }

	}

      }	/* if ( Wdg_PIOsc_Global.Expired == FALSE ) */

    }	/* if ( Wdg_PIOsc_Global.Mode != WDGIF_OFF_MODE ) */

  }	/* if ( Wdg_PIOsc_Global.State == WDG_IDLE ) */

  EE_hal_resumeIRQ(flags);

}

#endif	/*
	 * ( __AS_CFG_WDG_PIOSC_NMI_ISR__ && EE_CORTEX_MX_NMI_ISR ) ||
	 * (
	 *    __AS_CFG_WDG_PIOSC_WATCHDOG_TIMER_ISR__ &&
	 *    EE_CORTEX_MX_WATCHDOG_TIMER_ISR)
	 * )
	 */


#if	( \
	defined(__AS_CFG_WDG_PIOSC_NMI_ISR__) && \
	defined(EE_CORTEX_MX_NMI_ISR) \
)
/*
 * WDG Interrupt Service Routine.
 */
ISR2(EE_CORTEX_MX_NMI_ISR) { Wdg_PIOsc_Isr(); }

#endif	/*
	 * __AS_CFG_WDG_PIOSC_WATCHDOG_TIMER_ISR__ &&
	 * EE_CORTEX_MX_WATCHDOG_TIMER_ISR
	 */

#if	( \
	defined(__AS_CFG_WDG_PIOSC_WATCHDOG_TIMER_ISR__) && \
	defined(EE_CORTEX_MX_WATCHDOG_TIMER_ISR) \
)
/*
 * WDG Interrupt Service Routine.
 */
ISR2(EE_CORTEX_MX_WATCHDOG_TIMER_ISR) { Wdg_PIOsc_Isr(); }

#endif	/*
	 * __AS_CFG_WDG_PIOSC_WATCHDOG_TIMER_ISR__ &&
	 * EE_CORTEX_MX_WATCHDOG_TIMER_ISR
	 */
