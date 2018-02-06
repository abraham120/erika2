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
 * AUTOSAR-"like" SCI Driver Channels ISRs Source File.
 *
 * Author:  2013,  Gianluca Franchino
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
//#include "ee_irq.h"

#include "Sci_Internal.h"

/*
 * SCI Global Configuration Reference.
 */
typedef struct {
  
	boolean			Init;		/* SCI Driver Initialized? */

	const Sci_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Sci_GlobalType;

extern Sci_GlobalType Sci_Global;


#if ( SCI_NOTIFICATIONS_API == STD_ON )

#if ( \
  defined(EE_RX200_ERI0_ISR) || \
  defined(EE_RX200_ERI1_ISR) || \
  defined(EE_RX200_ERI5_ISR) || \
  defined(EE_RX200_ERI6_ISR) || \
  defined(EE_RX200_ERI8_ISR) || \
  defined(EE_RX200_ERI9_ISR) || \
  defined(EE_RX200_ERI12_ISR) \
)

void Sci_RxErrIsr(Sci_ChannelType Channel)
{
	register EE_FREG	flags;
	register uint32	ch;
	
	flags = EE_hal_suspendIRQ();
	
	/* Driver Initialization Check. */
	if ( Sci_Global.Init == TRUE ) {
		/* Channel Look-up */
		for (ch = 0;
			(
			(ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
			(Sci_Global.ConfigPtr->SciChannels[ch].SciChannelId != Channel)
			); 
			ch++) { ; }

	    /* Channel Configured Check. */
		if ( ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) {
	    	/* Receception Errors */
	    		
				if (Sci_Global.ConfigPtr->SciChannels[ch].SciRxErrNotificationPtr !=
						NULL_PTR) {
					EE_hal_resumeIRQ(flags);
					/* Call Reception Errors Notifications Callback. */
					(*(Sci_Global.ConfigPtr->SciChannels[ch].SciRxErrNotificationPtr))();

					flags = EE_hal_suspendIRQ();
					}

				/* Clear Errors */
				UART_RX_ERR_CLR(Channel);
	    }/* ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels */

	}	/* init == TRUE */
	
	
	EE_hal_resumeIRQ(flags);
}

#endif	/*
	 * EE_RX200_ERI0_ISR ||EE_RX200_ERI1_ISR ||
	 * EE_RX200_ERI6_ISR ||EE_RX200_ERI6_ISR || etc.
	 */	 


#if ( \
  defined(EE_RX200_RXI0_ISR) || \
  defined(EE_RX200_RXI1_ISR) || \
  defined(EE_RX200_RXI5_ISR) || \
  defined(EE_RX200_RXI6_ISR) || \
  defined(EE_RX200_RXI8_ISR) || \
  defined(EE_RX200_RXI9_ISR) || \
  defined(EE_RX200_RXI12_ISR) \
)

void Sci_RxIsr(Sci_ChannelType Channel)
{
	register EE_FREG	flags;
	register uint32	ch;
	

	flags = EE_hal_suspendIRQ();
	
	/* Driver Initialization Check. */
	if ( Sci_Global.Init == TRUE ) {
		/* Channel Look-up */
		for (ch = 0;
			(
			(ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
			(Sci_Global.ConfigPtr->SciChannels[ch].SciChannelId != Channel)
			); 
			ch++) { ; }

	    /* Channel Configured Check. */
		if ( ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) {
	    		
	    	if ( Sci_Global.ConfigPtr->SciChannels[ch].SciRxNotificationPtr !=
					NULL_PTR) {

				EE_hal_resumeIRQ(flags);
			/* Call Reception Notifications Callback. */
				(*(Sci_Global.ConfigPtr->SciChannels[ch].SciRxNotificationPtr))();
				
				flags = EE_hal_suspendIRQ();

	    	}
	    }/* ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels */

	}	/* init == TRUE */
	EE_hal_resumeIRQ(flags);
}

#endif	/*
	 * EE_RX200_RXI0_ISR || EE_RX200_RXI1_ISR ||
	 * EE_RX200_RXI6_ISR ||EE_RX200_RXI6_ISR || etc.
	 */

#if ( \
  defined(EE_RX200_TXI0_ISR) || \
  defined(EE_RX200_TXI1_ISR) || \
  defined(EE_RX200_TXI6_ISR) || \
  defined(EE_RX200_TXI8_ISR) || \
  defined(EE_RX200_TXI9_ISR) || \
  defined(EE_RX200_TXI12_ISR) \
)

void Sci_TxIsr(Sci_ChannelType Channel)
{
	register EE_FREG	flags;
	register uint32	ch;
	
		
	flags = EE_hal_suspendIRQ();

	/* Driver Initialization Check. */
	if ( Sci_Global.Init == TRUE ) {
		/* Channel Look-up */
		for (ch = 0;
			(
			(ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels) &&
			(Sci_Global.ConfigPtr->SciChannels[ch].SciChannelId != Channel)
			); 
			ch++) { ; }

	    /* Channel Configured Check. */
		if ( ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) {
			if (Sci_Global.ConfigPtr->SciChannels[ch].SciTxNotificationPtr !=
	    		  NULL_PTR) {

	    		EE_hal_resumeIRQ(flags);

	    		/* Call Transmission Notifications Callback. */
	    		(*(Sci_Global.ConfigPtr->SciChannels[ch].SciTxNotificationPtr))();

	    		flags = EE_hal_suspendIRQ();
	    		}
	    }/* ch < Sci_Global.ConfigPtr->SciNumberOfSciChannels */
	}	/* init == TRUE */
	
	EE_hal_resumeIRQ(flags);
}

#endif	/*
	 * EE_RX200_TXI0_ISR  || EE_RX200_TXI1_ISR  ||
	 * EE_RX200_TXI5_ISR  || EE_RX200_TXI6_ISR || etc.
	 */


	 
	 
#ifdef	EE_RX200_ERI0_ISR
#pragma interrupt (EE_RX200_ERI0_ISR)
ISR2(EE_RX200_ERI0_ISR) 
{ 
	Sci_RxErrIsr(SCI_CHANNEL_0); 
	while (EE_HWREG8(HW_ICU_IR_SCI0_ERX) == 1);
}
#endif

#ifdef	EE_RX200_RXI0_ISR
#pragma interrupt (EE_RX200_RXI0_ISR)
ISR2(EE_RX200_RXI0_ISR) { Sci_RxIsr(SCI_CHANNEL_0); }
#endif

#ifdef	EE_RX200_TXI0_ISR
#pragma interrupt (EE_RX200_TXI0_ISR)
ISR2(EE_RX200_TXI0_ISR) { Sci_TxIsr(SCI_CHANNEL_0); }
#endif


#ifdef	EE_RX200_ERI1_ISR
#pragma interrupt (EE_RX200_ERI1_ISR)
ISR2(EE_RX200_ERI1_ISR) 
{ 
	Sci_RxErrIsr(SCI_CHANNEL_1); 
	while (EE_HWREG8(HW_ICU_IR_SCI1_ERX));
}
#endif

#ifdef	EE_RX200_RXI1_ISR
#pragma interrupt (EE_RX200_RXI1_ISR)
ISR2(EE_RX200_RXI1_ISR) { Sci_RxIsr(SCI_CHANNEL_1); }
#endif

#ifdef	EE_RX200_TXI1_ISR
#pragma interrupt (EE_RX200_TXI1_ISR)
ISR2(EE_RX200_TXI1_ISR) { Sci_TxIsr(SCI_CHANNEL_1); }
#endif

#ifdef	EE_RX200_ERI5_ISR
#pragma interrupt (EE_RX200_ERI5_ISR)
ISR2(EE_RX200_ERI5_ISR) 
{ 
	Sci_RxErrIsr(SCI_CHANNEL_5); 
	while (EE_HWREG8(HW_ICU_IR_SCI5_ERX));
}
#endif

#ifdef	EE_RX200_RXI5_ISR
#pragma interrupt (EE_RX200_RXI5_ISR)
ISR2(EE_RX200_RXI5_ISR) { Sci_RxIsr(SCI_CHANNEL_5); }
#endif

#ifdef	EE_RX200_TXI5_ISR
#pragma interrupt (EE_RX200_TXI5_ISR)
ISR2(EE_RX200_TXI5_ISR) { Sci_TxIsr(SCI_CHANNEL_5); }
#endif

#ifdef	EE_RX200_ERI6_ISR
#pragma interrupt (EE_RX200_ERI6_ISR)
ISR2(EE_RX200_ERI6_ISR) 
{ 
	Sci_RxErrIsr(SCI_CHANNEL_6); 
	while (EE_HWREG8(HW_ICU_IR_SCI6_ERX));	
}
#endif

#ifdef	EE_RX200_RXI6_ISR
#pragma interrupt (EE_RX200_RXI6_ISR)
ISR2(EE_RX200_RXI6_ISR) { Sci_RxIsr(SCI_CHANNEL_6); }
#endif

#ifdef	EE_RX200_TXI6_ISR
#pragma interrupt (EE_RX200_TXI6_ISR)
ISR2(EE_RX200_TXI6_ISR) { Sci_TxIsr(SCI_CHANNEL_6); }
#endif

#ifdef	EE_RX200_ERI8_ISR
#pragma interrupt (EE_RX200_ERI8_ISR)
ISR2(EE_RX200_ERI8_ISR) 
{ 
	Sci_RxErrIsr(SCI_CHANNEL_8); 
	while (EE_HWREG8(HW_ICU_IR_SCI8_ERX));	
}
#endif

#ifdef	EE_RX200_RXI8_ISR
#pragma interrupt (EE_RX200_RXI8_ISR)
ISR2(EE_RX200_RXI8_ISR) { Sci_RxIsr(SCI_CHANNEL_8); }
#endif

#ifdef	EE_RX200_TXI_ISR
#pragma interrupt (EE_RX200_TXI8_ISR)
ISR2(EE_RX200_TXI8_ISR) { Sci_TxIsr(SCI_CHANNEL_8); }
#endif

#ifdef	EE_RX200_ERI9_ISR
#pragma interrupt (EE_RX200_ERI9_ISR)
ISR2(EE_RX200_ERI9_ISR) 
{ 
	Sci_RxErrIsr(SCI_CHANNEL_9); 
	while (EE_HWREG8(HW_ICU_IR_SCI9_ERX));	
}
#endif

#ifdef	EE_RX200_RXI9_ISR
#pragma interrupt (EE_RX200_RXI9_ISR)
ISR2(EE_RX200_RXI9_ISR) { Sci_RxIsr(SCI_CHANNEL_9); }
#endif

#ifdef	EE_RX200_TXI9_ISR
#pragma interrupt (EE_RX200_TXI9_ISR)
ISR2(EE_RX200_TXI9_ISR) { Sci_TxIsr(SCI_CHANNEL_9); }
#endif

#ifdef	EE_RX200_ERI12_ISR
#pragma interrupt (EE_RX200_ERI12_ISR)
ISR2(EE_RX200_ERI12_ISR)
{ 
	Sci_RxErrIsr(SCI_CHANNEL_12); 
	while (EE_HWREG8(HW_ICU_IR_SCI12_ERX));	
}
#endif

#ifdef	EE_RX200_RXI12_ISR
#pragma interrupt (EE_RX200_RXI12_ISR)
ISR2(EE_RX200_RXI12_ISR) { Sci_RxIsr(SCI_CHANNEL_12); }
#endif

#ifdef	EE_RX200_TXI12_ISR
#pragma interrupt (EE_RX200_TXI12_ISR)
ISR2(EE_RX200_TXI12_ISR) { Sci_TxIsr(SCI_CHANNEL_12); }
#endif

#endif	/* SCI_NOTIFICATIONS_API */
