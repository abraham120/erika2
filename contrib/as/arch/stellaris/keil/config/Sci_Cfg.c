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
 * fake-druid AUTOSAR PORT Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
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
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
  { /* UART1 */
    SCI_CHANNEL_1,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
  { /* UART2 */
    SCI_CHANNEL_2,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
  { /* UART3 */
    SCI_CHANNEL_3,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
  { /* UART4 */
    SCI_CHANNEL_4,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_HIGH_SPEED |		/* - UART High-Speed Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    /*SCI_CH_HW_FIFO |*/		/* - UART Enable FIFOs		      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
#ifdef	EE_CORTEX_MX_UART_4_ISR
    &Sci_TxNotifications_Channel_4,	/* SciTxNotificationPtr		      */
    &Sci_TxErrNotifications_Channel_4,	/* SciTxErrNotificationPtr	      */
    &Sci_RxNotifications_Channel_4,	/* SciRxNotificationPtr		      */
    &Sci_RxErrNotifications_Channel_4	/* SciRxErrNotificationPtr	      */
#else	/* EE_CORTEX_MX_UART_4_ISR	*/
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif	/* !EE_CORTEX_MX_UART_4_ISR	*/
#endif	/* SCI_NOTIFICATIONS_API == STD_ON */
  },
  { /* UART5 */
    SCI_CHANNEL_5,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
  { /* UART6 */
    SCI_CHANNEL_6,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
  { /* UART7 */
    SCI_CHANNEL_7,			/* SciChannelId			      */
    2400,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_LOOP_BACK |		/* - UART Loop Back Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
};

#ifdef	__AS_CFG_SCI_ARISTON_TESTS__
/*
 * Ariston Tests Sci Channels Configuration.
 */
const Sci_ChannelConfigType AristonTestsSciChannels[] = {
  { /* UART4 */
    SCI_CHANNEL_ARISTON_TESTS_DEBUG,	/* SciChannelId			      */
    115200,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    TRUE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_HIGH_SPEED |		/* - UART High-Speed Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
};
#endif	/* __AS_CFG_SCI_ARISTON_TESTS__ */

#ifdef	__AS_CFG_SCI_WDG_PIOSC_TESTS__
/*
 * WdgPIOsc Tests Sci Channels Configuration.
 */
const Sci_ChannelConfigType WdgPIOscTestsSciChannels[] = {
  { /* UART4 */
    SCI_CHANNEL_WDG_PIOSC_TESTS_DEBUG,	/* SciChannelId			      */
    115200,				/* SciChannelBaudRate		      */
#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
    TRUE,				/* SciChannelWakeupSupport	      */
#endif
    FALSE,				/* SciSysClock			      */
    					/* SciSysCtrl:			      */
    SCI_CH_HW_HIGH_SPEED |		/* - UART High-Speed Enable	      */
    SCI_CH_HW_RX |			/* - UART Receive Enable	      */
    SCI_CH_HW_TX |			/* - UART Transmit Enable	      */
    SCI_CH_HW_ENABLE,			/* - UART Enable		      */
    					/* SciLineCtrl:			      */
    SCI_CH_HW_8_BITS,			/* - 8 bits, 1 stop bit, No parity    */
#if ( SCI_NOTIFICATIONS_API == STD_ON )
    NULL_PTR,				/* SciTxNotificationPtr		      */
    NULL_PTR,				/* SciTxErrNotificationPtr	      */
    NULL_PTR,				/* SciRxNotificationPtr		      */
    NULL_PTR				/* SciRxErrNotificationPtr	      */
#endif
  },
};
#endif	/* __AS_CFG_SCI_WDG_PIOSC_TESTS__ */

/*
 * This container is the base of a multiple configuration set.
 */
const Sci_ConfigType Sci_Config[] = {
  {
    SCI_CHANNELS_NUMBER,	/* SciNumberOfSciChannels	*/
    &SciChannels[0]		/* SciChannels			*/
  },
#ifdef	__AS_CFG_SCI_ARISTON_TESTS__
  {
    ARISTON_TESTS_SCI_CHANNELS_NUMBER,	/* SciNumberOfSciChannels	*/
    &AristonTestsSciChannels[0]		/* SciChannels			*/
  },
#endif	/* __AS_CFG_SCI_ARISTON_TESTS__ */
#ifdef	__AS_CFG_SCI_WDG_PIOSC_TESTS__
  {
    WDG_PIOSC_TESTS_SCI_CHANNELS_NUMBER,	/* SciNumberOfSciChannels     */
    &WdgPIOscTestsSciChannels[0]		/* SciChannels		      */
  },
#endif	/* __AS_CFG_SCI_WDG_PIOSC_TESTS__ */
};
