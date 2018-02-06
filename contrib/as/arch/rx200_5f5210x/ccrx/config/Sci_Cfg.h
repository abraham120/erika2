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

/** @file	Sci_Cfg.h
 *  @brief	fake-druid AUTOSAR-"like" SCI Driver Configuration Header File.
 *
 *  Configured for (SCI): Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2013
 */


#if !(\
 ((SCI_SW_MAJOR_VERSION == 1) && \
  (SCI_SW_MINOR_VERSION == 0) && \
  (SCI_SW_PATCH_VERSION == 0))\
)
#error Sci: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	SCI_CFG_H
#define	SCI_CFG_H

#include "Mcu.h"

/*
 * This container contains the configuration (parameters) of the SCI driver.
 */
/* SciGeneralConfiguration */

/** @brief	Development Error Detection
 *
 *  Pre-processor switch for enabling the development error detection and
 *  reporting.
 */
#define	SCI_DEV_ERROR_DETECT		STD_OFF

/** @brief	Version Informations Retrieval API
 *
 *  Pre-processor switch to enable / disable the API to read out the modules
 *  version information.
 */
#define	SCI_VERSION_INFO_API		STD_ON

/** @brief	Wake-up Functionality
 *
 *  Adds / removes the services <tt>Sci_GoToSleep()</tt>, <tt>Sci_Wakeup()</tt>,
 *  <tt>Sci_GoToSleepInternal()</tt> and <tt>Sci_CheckWakeup()</tt> from the
 *  code.
 */
#define	SCI_WAKEUP_FUNCTIONALITY_API	STD_ON

/** @brief	De-Init Functionality
 *
 *  Adds / removes the service <tt>Sci_DeInit()</tt> from the code.
 */
#define	SCI_DEINIT_API			STD_ON

/** @brief	Notifications Functionality
 *
 *  Adds / removes the services <tt>Sci_EnableNotifications()</tt> and
 *  <tt>Sci_DisableNotifications()</tt> from the code.
 */
#define	SCI_NOTIFICATIONS_API		STD_ON

/** @brief	Enable Digital Noise Filter
 *
 */
#define SCI_CH_HW_DNF_EN			0x80

/** @brief	Enable Clock Output Pin
 *
 */
#define SCI_CH_HW_OUPUT_CLK			0x40

/** @brief	Enable UART TX
 *
 */
#define SCI_CH_HW_TX_EN				0x20

/** @brief	Enable UART RX
 *
 */
#define SCI_CH_HW_RX_EN				0x10

/** @brief	Enable RTS/CTS hardware flow control.
 *
 */
#define SCI_CH_HW_RTS_CTS_EN		0x08

/** @brief	Enable UART High Speed Clock.
 *  Select 8 base clock cycles.
 *
 */
#define SCI_CH_HW_HIGH_SPEED		0x04

/** @brief	Enable UART Extended Mode Support.
 *
 */
#define SCI_CH_HW_EXTENDED_MODE_EN	0x02

/** @brief	Enable UART Smart Card Support.
 *
 */
#define SCI_CH_HW_SMART_CARD_EN		0x01

/** @brief	Enable UART Mode (i.e. Asyncronous mode).
 *
 */
#define SCI_CH_HW_UART_MODE_EN		0x00

/** @brief	Enable UART 8 bits data length.
 *
 */
#define SCI_CH_HW_DATA_8_BITS		0x00

/** @brief	Enable UART 7 bits data length.
 *
 */
#define SCI_CH_HW_DATA_7_BITS		0x10

/** @brief	Enable UART parity bit check.
 *
 */
#define SCI_CH_HW_PARITY_EN			0x20

/** @brief	Enable UART odd parity.
 *
 */
#define SCI_CH_HW_ODD_PARITY		0x10

/** @brief	Enable UART even parity.
 *
 */
#define SCI_CH_HW_EVEN_PARITY		0x00

/** @brief	Enable UART two stop bits.
 *
 */
#define SCI_CH_HW_TWO_BITS_STOP		0x08

/** @brief	Enable UART one stop bit.
 *
 */
#define SCI_CH_HW_ONE_BITS_STOP		0x00

/** @brief	Enable UART multi-processor mode.
 *
 */
#define SCI_CH_HW_MULTI_PROC_EN		0x04

/** @brief	Set UART clock source -> PCLK/64
 *
 */
#define SCI_CH_HW_CLOCK_PCLK_64		0x03

/** @brief	Set UART clock source -> PCLK/16
 *
 */
#define SCI_CH_HW_CLOCK_PCLK_16		0x02

/** @brief	Set UART clock source -> PCLK/4
 *
 */
#define SCI_CH_HW_CLOCK_PCLK_4		0x01

/** @brief	Set UART clock source -> PCLK
 *
 */
#define SCI_CH_HW_CLOCK_PCLK_1		0x00


/** @brief	Channel Settings Configuration Parameters
 *
 *  This container contains the configuration (parameters) for the a SCI
 *  Channel.
 */
typedef struct {

  /** @brief	Channel Identifier
   *
   *  The Id of the SCI channel to configure.
   */
	Sci_ChannelType	SciChannelId;

  /** @brief	Baud Rate
   *
   *  This container specifies the baud rate of the SCI Channel.
   */
	uint32		SciChannelBaudRate;

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
  /** @brief	Wake-up Support
   *
   *  Specifies if the SCI channel supports wake-up functionality.
   */
	boolean		SciChannelWakeupSupport;
#endif

  /** @brief	Clock Reference
   *
   *  Reference to the SCI clock source configuration, which is set in the
   *  MCU driver configuration.
   */
  /*Mcu_ClockType		SciClockRef;*/

  /** @brief	UART Baud Clock Source
   *
   *  - <tt>FALSE</tt>:	External Oscillator.
   *  - <tt>TRUE</tt>:	System Clock (PCLKB).
   */
  boolean		SciSysClock;

  /** @brief	UART System Control
   *
   *  UARTCTL Register:
   *  Bit/Field	Description
   *  	7	Enable Digital Noise Filter
   *    6	Enable Extern Clock
   *    5	Enable Transmit
   *    4	Enable Receive
   *    3	Enable RTS/CTS
   *    2	High-Speed Enable
   *    1	Enable Serial Extended Mode	
   *    0	ISO 7816 Smart Card Support
   */
  uint8		SciSysCtrl;
 
  /** @brief	UART Line Control
   *
   *  UARTLCRH Register:
   *  Bit/Field	Description
   *    7	UART Mode Enable	
   *    6	UART Character Length	
   *    5	UART Parity Enable
   *    4	UART Even Parity Select
   *    3	UART Two Stop Bits Select
   *    2	Enable Multi-Processor Mode
   *    1:0 UART Clock Select Bits
   *    
   */
  uint8			SciModeCtrl;
  
 
  

#if ( SCI_NOTIFICATIONS_API == STD_ON )
  /** @brief	Transmission Notifications Callback Function Pointer
   *
   *  The notification prototype <tt>Sci_TxNotification()</tt> is for the
   *  transmission notifications callback function and shall be implemented by
   *  the user.
   *
   *  The SCI module's environment shall declare a separate transmission
   *  notifications callback for each channel to avoid parameters in
   *  notification services and to improve run time efficiency.
   *
   *  The transmission notifications callback
   *  <tt>Sci_TxNotification_<channel>()</tt> shall be configurable as pointers
   *  to user defined functions within the configuration structure.
   *
   *  Each channel shall provide its own transmission notifications callback if
   *  configured.
   *
   *  When disabled, the SCI Driver will send no transmission notifications.
   *
   *  The SCI Driver shall invoke a notification callback whenever a transmission
   *  event occurred on channel.
   *
   *  The ISR's, providing the SCI events, shall be responsible for resetting
   *  the interrupt flags (if needed by hardware) and calling the according
   *  notification function.
   *
   *  For all available channels, callback functions have to be declared by the
   *  configuration tool.
   */
  Sci_TxNotification	SciTxNotificationPtr;

  /** @brief	Transmission Errors Notifications Callback Function Pointer
   *
   *  The notification prototype <tt>Sci_TxErrNotification()</tt> is for the
   *  transmission errors notifications callback function and shall be
   *  implemented by the user.
   *
   *  The SCI module's environment shall declare a separate transmission errors
   *  notifications callback for each channel to avoid parameters in
   *  notification services and to improve run time efficiency.
   *
   *  The transmission errors notifications callback
   *  <tt>Sci_TxErrNotification_<channel>()</tt> shall be configurable as
   *  pointers to user defined functions within the configuration structure.
   *
   *  Each channel shall provide its own transmission errors notifications
   *  callback if configured.
   *
   *  When disabled, the SCI Driver will send no transmission errors
   *  notifications.
   *
   *  The SCI Driver shall invoke a notification callback whenever a trasmission
   *  error occurred on channel.
   *
   *  The ISR's, providing the SCI events, shall be responsible for resetting
   *  the interrupt flags (if needed by hardware) and calling the according
   *  notification function.
   *
   *  For all available channels, callback functions have to be declared by the
   *  configuration tool.
   */
	Sci_TxErrNotification	SciTxErrNotificationPtr;

  /** @brief	Reception Notifications Callback Function Pointer
   *
   *  The notification prototype <tt>Sci_RxNotification()</tt> is for the
   *  reception notifications callback function and shall be implemented by the
   *  user.
   *
   *  The SCI module's environment shall declare a separate reception
   *  notifications callback for each channel to avoid parameters in
   *  notification services and to improve run time efficiency.
   *
   *  The reception notifications callback
   *  <tt>Sci_RxNotification_<channel>()</tt>
   *  shall be configurable as pointers to user defined functions within the
   *  configuration structure.
   *
   *  Each channel shall provide its own reception notifications callback if
   *  configured.
   *
   *  When disabled, the SCI Driver will send no reception notifications.
   *
   *  The SCI Driver shall invoke a notification callback whenever a reception
   *  event occurred on channel.
   *
   *  The ISR's, providing the SCI events, shall be responsible for resetting
   *  the interrupt flags (if needed by hardware) and calling the according
   *  notification function.
   *
   *  For all available channels, callback functions have to be declared by the
   *  configuration tool.
   */
  Sci_RxNotification	SciRxNotificationPtr;

  /** @brief	Reception Errors Notifications Callback Function Pointer
   *
   *  The notification prototype <tt>Sci_RxErrNotification()</tt> is for the
   *  reception errors notifications callback function and shall be implemented
   *  by the user.
   *
   *  The SCI module's environment shall declare a separate reception errors
   *  notifications callback for each channel to avoid parameters in
   *  notification  services and to improve run time efficiency.
   *
   *  The reception errors notifications callback
   *  <tt>Sci_RxErrNotification_<channel>()</tt> shall be configurable as
   *  pointers to user defined functions within the configuration structure.
   *
   *  Each channel shall provide its own reception errors notifications callback
   *  if configured.
   *
   *  When disabled, the SCI Driver will send no reception errors notifications.
   *
   *  The SCI Driver shall invoke a notification callback whenever a reception
   *  error occurred on channel.
   *
   *  The ISR's, providing the SCI events, shall be responsible for resetting
   *  the interrupt flags (if needed by hardware) and calling the according
   *  notification function.
   *
   *  For all available channels, callback functions have to be declared by the
   *  configuration tool.
   */
  Sci_RxErrNotification	SciRxErrNotificationPtr;
#endif

} Sci_ChannelConfigType;

/*
 * The configuration process for Sci module shall provide symbolic names for
 * each configured SCI channel.
 * Note, Renesas RX210R5F5210x provides the following SCI modules: SCIc and SCId.
 */ 
#define	SCI_CHANNEL_0	0x00	/**< Channel 0, SCIc module  */
#define	SCI_CHANNEL_1	0x01	/**< Channel 1, SCIc module  */
#define	SCI_CHANNEL_5	0x05	/**< Channel 5, SCIc module  */
#define	SCI_CHANNEL_6	0x06	/**< Channel 6, SCIc module  */
#define	SCI_CHANNEL_8	0x08	/**< Channel 8, SCIc module  */
#define	SCI_CHANNEL_9	0x09	/**< Channel 9, SCIc module  */
#define	SCI_CHANNEL_12	0x0C	/**< Channel 12, SCId module */

/** Number of Channels */
#define	SCI_CHANNELS_NUMBER	6


/** @brief	Channel 0 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_0()</tt> is for
 *  the transmission notifications callback function for SCI Channel 0 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_0(
  void
);

/** @brief	Channel 0 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_0()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 0
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_0(
  void
);

/** @brief	Channel 0 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_0()</tt> is for
 *  the reception notifications callback function for SCI Channel 0 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_0(
  void
);

/** @brief	Channel 0 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_0()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 0 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_0(
  void
);

/** @brief	Channel 1 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_1()</tt> is for
 *  the transmission notifications callback function for SCI Channel 1 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_1(
  void
);

/** @brief	Channel 1 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_1()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 1
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_1(
  void
);

/** @brief	Channel 1 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_1()</tt> is for
 *  the reception notifications callback function for SCI Channel 1 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_1(
  void
);

/** @brief	Channel 1 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_1()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 1 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_1(
  void
);

/** @brief	Channel 5 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_5()</tt> is for
 *  the transmission notifications callback function for SCI Channel 5 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_5(
  void
);

/** @brief	Channel 5 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_5()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 5
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_5(
  void
);

/** @brief	Channel 5 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_5()</tt> is for
 *  the reception notifications callback function for SCI Channel 5 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_5(
  void
);

/** @brief	Channel 5 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_5()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 5 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_5(
  void
);


/** @brief	Channel 6 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_6()</tt> is for
 *  the transmission notifications callback function for SCI Channel 6 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_6(
  void
);

/** @brief	Channel 6 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_6()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 6
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_6(
  void
);

/** @brief	Channel 6 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_6()</tt> is for
 *  the reception notifications callback function for SCI Channel 6 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_6(
  void
);

/** @brief	Channel 6 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_6()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 6 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_6(
  void
);


/** @brief	Channel 8 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_8()</tt> is for
 *  the transmission notifications callback function for SCI Channel 8 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_8(
  void
);

/** @brief	Channel 8 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_8()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 8
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_8(
  void
);

/** @brief	Channel 8 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_8()</tt> is for
 *  the reception notifications callback function for SCI Channel 8 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_8(
  void
);

/** @brief	Channel 8 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_8()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 8 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_8(
  void
);

/** @brief	Channel 9 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_9()</tt> is for
 *  the transmission notifications callback function for SCI Channel 9 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_9(
  void
);

/** @brief	Channel 9 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_9()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 9
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_9(
  void
);

/** @brief	Channel 9 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_9()</tt> is for
 *  the reception notifications callback function for SCI Channel 9 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_9(
  void
);

/** @brief	Channel 9 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_9()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 9 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_9(
  void
);

/** @brief	Channel 12 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_12()</tt> is for
 *  the transmission notifications callback function for SCI Channel 12 and shall
 *  be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a transmission
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxNotifications_Channel_12(
  void
);

/** @brief	Channel 12 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_12()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 12
 *  and shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no transmission errors
 *  notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a trasmission
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_TxErrNotifications_Channel_12(
  void
);

/** @brief	Channel 12 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_12()</tt> is for
 *  the reception notifications callback function for SCI Channel 12 and shall be
 *  implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  event occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxNotifications_Channel_12(
  void
);

/** @brief	Channel 12 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_12()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 12 and
 *  shall be implemented by the user.
 *
 *  When disabled, the SCI Driver will send no reception errors notifications.
 *
 *  The SCI Driver shall invoke a notification callback whenever a reception
 *  error occurred on channel.
 *
 *  The ISR's, providing the SCI events, shall be responsible for resetting
 *  the interrupt flags (if needed by hardware) and calling the according
 *  notification function.
 *
 *  For all available channels, callback functions have to be declared by the
 *  configuration tool.
 */
void Sci_RxErrNotifications_Channel_12(
  void
);



/** @brief	SCI Configuration Parameters
 *
 *  The structure <tt>Sci_ConfigType</tt> is an external data structure (i.e.
 *  implementation specific) and shall contain the initialization data for the
 *  SCI module. It shall contain:
 *  - SCI dependent properties
 *  - SCI harware unit initialization parameters
 *  - SFR's settings affecting the SCI channels
 */
typedef struct {

  /** @brief	SCI Channels Number
   *
   *  This parameter shall represent the number of Channels available for the
   *  SCI. calculationFormula = Number of configured <tt>SciChannel</tt>.
   */
  uint8_least				SciNumberOfSciChannels;

  /** @brief	Channels Setting Configuration Parameters
   *
   *  This container contains the configuration (parameters) for the channel
   *  settings of the SCI.
   */
  const Sci_ChannelConfigType *		SciChannels;

#if ( SCI_DEV_ERROR_DETECT == STD_ON )
  /** @brief	DEM Event Configuration Parameters
   *
   *  Container for the references to <tt>DemEventParameter</tt> elements which
   *  shall be invoked using the API <tt>Dem_ReportErrorStatus()</tt> API in
   *  case the corresponding error occurs. The EventId is taken from the
   *  referenced DemEventParameter's DemEventId value. The standardized errors
   *  are provided in the container and can be extended by vendor specific error
   *  references. */
  Sci_DemEventParametersTypeRefs *	SciDemEventParametersRefs;
#endif

} Sci_ConfigType;

/** @brief	Default Configuration
 *
 *  Identifier for Default SCI Driver Configuration.
 */
#define	SCI_CONFIG_DEFAULT	0x00000000
/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default SCI Driver Configuration
 */
#define	SCI_CONFIG_DEFAULT_PTR	&Sci_Config[SCI_CONFIG_DEFAULT]


#endif	/* SCI_CFG_H */
