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
 * Wdg_IWDT_Irq.c File for implementation of interrupt service routine
 *
 * Peripheral Clock AUTOSAR WDG (Watchdog) Driver ISRs Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

/*
 * Wdg_IWDT_Irq.c has implicit access to the Wdg_IWDT_Cfg.h through the
 * Wdg_IWDT.h file.
 */
#include "Wdg_IWDT.h"

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
#define	WDG_IWDT_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_IWDT_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_IWDT_AR_MAJOR_VERSION ) || \
    ( WDG_IWDT_AR_MAJOR_VERSION != WDG_IWDT_AR_RELEASE_MAJOR_VERSION )
#error	Wdg_IWDT: version mismatch.
#endif

#include "ee.h"

#if	( defined(EE_RX200_NON_MASKABLE_INT_ISR) )

#include "Wdg_IWDT_Internal.h"

static void Wdg_IWDT_Isr(void) {

	register EE_UREG	flags;

	flags = EE_hal_suspendIRQ();

	/*Check if the interrupt was raised because of underflow or refresh error,
	 * then clear the corresponding flag.
	 */
	if (WDG_IWDT_GET_IWDTSR() & WDG_IWDTSR_UNDFF_FLAG_MASK) {
		while(WDG_IWDT_GET_IWDTSR() & WDG_IWDTSR_UNDFF_FLAG_MASK)
			WDG_IWDT_RESET_IWDTSR_UNDFF(); 
	} else {
		
		WDG_IWDT_RESET_IWDTSR_REFEF();
	}
	
	if ( Wdg_IWDT_Global.State == WDG_IDLE &&  
			(Wdg_IWDT_Global.Mode != WDGIF_OFF_MODE )) {
		if ( Wdg_IWDT_Global.Expired == FALSE ) {

			Wdg_IWDT_Global.Expired = TRUE;

			if ( Wdg_IWDT_Global.Mode == WDGIF_FAST_MODE ) {

				if (( Wdg_IWDT_Global.ConfigPtr->WdgSettingsFast != NULL_PTR ) 
						&& ( Wdg_IWDT_Global.ConfigPtr->WdgSettingsFast->WdgNotificationPtr != NULL_PTR)) {

					EE_hal_resumeIRQ(flags);

					(*(Wdg_IWDT_Global.ConfigPtr->WdgSettingsFast->WdgNotificationPtr))();

					flags = EE_hal_suspendIRQ();

				}

			} else {
				if (( Wdg_IWDT_Global.ConfigPtr->WdgSettingsSlow != NULL_PTR ) &&
						( Wdg_IWDT_Global.ConfigPtr->WdgSettingsSlow->WdgNotificationPtr != NULL_PTR)) {
					
					EE_hal_resumeIRQ(flags);
					(*(Wdg_IWDT_Global.ConfigPtr->WdgSettingsSlow->WdgNotificationPtr))();

					flags = EE_hal_suspendIRQ();
				}
			} /* if ( Wdg_IWDT_Global.Mode == WDGIF_FAST_MODE )	*/
		}/* if ( Wdg_IWDT_Global.Expired == FALSE ) */

	}	/* if ( Wdg_IWDT_Global.State == WDG_IDLE ) && ( Wdg_IWDT_Global.Mode != WDGIF_OFF_MODE ) */

	EE_hal_resumeIRQ(flags);

}

#endif	/* (EE_RX200_NON_MASKABLE_INT_ISR ) */



#if	( defined(EE_RX200_NON_MASKABLE_INT_ISR) )
/*
 * WDG Interrupt Service Routine.
 */
ISR2(EE_rx200_non_maskable_int) {

	if (EE_HWREG8(HW_ICU_NMISR) & HW_ICU_NMISR_IWDTST_MASK) {

		do {

			EE_HWREG8(HW_ICU_NMICLR) = HW_ICU_NMICLR_IWDTCLR_MASK;

		} while (EE_HWREG8(HW_ICU_NMISR) & HW_ICU_NMISR_IWDTST_MASK);

		Wdg_IWDT_Isr();
	}
}

#endif	/* EE_RX200_NON_MASKABLE_INT_ISR */

