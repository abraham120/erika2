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
 * fake-druid AUTOSAR SCI Driver Configuration Source File.
 *
 * Configured for (MCU): Renesas RX210R5F5210x
 *
 * Author: 2013, Gianluca Franchino
 */

#define	SCI_AR_RELEASE_MAJOR_VERSION	4
#define	SCI_AR_RELEASE_MINOR_VERSION	0

#include "Sci.h"
#include "eecfg.h"

/*
 * For included (external) header files:
 * - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * shall be verified.
 */
#if !defined( SCI_AR_MAJOR_VERSION ) || \
    ( SCI_AR_MAJOR_VERSION != SCI_AR_RELEASE_MAJOR_VERSION )
#error	Sci: version mismatch.
#endif

/*
 * Sci Channels Configuration.
 */
const Sci_ChannelConfigType SciChannels[] = {
  { /* UART0 */
    SCI_CHANNEL_0,			/* SciChannelId			      */
    //38400,				/* SciChannelBaudRate		      */
	600,
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */					
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */		
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_0,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_0,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_0	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif
#endif
  },
  { /* UART1 */
    SCI_CHANNEL_1,			/* SciChannelId			      */
    38400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */		
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_1,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_1,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_1	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif
#endif
  },
  { /* UART5 */
    SCI_CHANNEL_5,			/* SciChannelId			      */
    38400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1 |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */		
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_5,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_5,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_5	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif
#endif
  },
  { /* UART6 */
    SCI_CHANNEL_6,			/* SciChannelId			      */
     38400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */	
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_6,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_6,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_6	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif	
#endif
  },
  { /* UART8 */
    SCI_CHANNEL_8,			/* SciChannelId			      */
    38400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */		
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_8,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_8,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_8	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif
#endif
  },
  { /* UART9 */
    SCI_CHANNEL_9,			/* SciChannelId			      */
    38400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */		
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_9,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_9,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_9	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif	
#endif
  },
  { /* UART12 */
    SCI_CHANNEL_12,			/* SciChannelId			      */
    38400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
	SCI_CH_HW_HIGH_SPEED | /*UART Enable High Speed Mode */
    SCI_CH_HW_DNF_EN |	/* - UART Digital Filter Enable	      */
    SCI_CH_HW_TX_EN |	/* - UART Transmit Enable	      */
    SCI_CH_HW_RX_EN,	/* - UART Receive Enable	      */
    					/* SciModeCtrl:			      */
    SCI_CH_HW_UART_MODE_EN |
    SCI_CH_HW_DATA_8_BITS |
    SCI_CH_HW_ONE_BITS_STOP |
	SCI_CH_HW_CLOCK_PCLK_1, /* - 8 bits, 1 stop bit, No parity, Clock = PCLK /1 */	
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#if 0
    &Sci_TxNotifications_Channel_12,		/* SciTxNotificationPtr		      */
    NULL_PTR,							/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_12,		/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_12	/* SciRxErrNotificationPtr	      */
#else
	NULL_PTR,
	NULL_PTR,
	NULL_PTR,
	NULL_PTR
#endif
#endif
  },
  
};


/*
 * This container is the base of a multiple configuration set.
 */
const Sci_ConfigType Sci_Config[] = {
  {
    SCI_CHANNELS_NUMBER,	/* SciNumberOfSciChannels	*/
    &SciChannels[0]		/* SciChannels			*/
  },
};
