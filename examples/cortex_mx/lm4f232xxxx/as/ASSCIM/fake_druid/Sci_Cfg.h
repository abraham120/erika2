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

/** @file	Sci_Cfg.h
 *  @brief	fake-druid AUTOSAR-"like" SCI Driver Configuration Header File.
 *
 *  Configured for (SCI): TI Stellaris LM4F232H5QD
 *
 *  @author	Giuseppe Serano
 *  @date	2012
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
#define	SCI_VERSION_INFO_API		STD_OFF

/** @brief	Wake-up Functionality
 *
 *  Adds / removes the services <tt>Sci_GoToSleep()</tt>, <tt>Sci_Wakeup()</tt>,
 *  <tt>Sci_GoToSleepInternal()</tt> and <tt>Sci_CheckWakeup()</tt> from the
 *  code.
 */
#define	SCI_WAKEUP_FUNCTIONALITY_API	STD_OFF

/** @brief	De-Init Functionality
 *
 *  Adds / removes the service <tt>Sci_DeInit()</tt> from the code.
 */
#define	SCI_DEINIT_API			STD_OFF

/** @brief	Notifications Functionality
 *
 *  Adds / removes the services <tt>Sci_EnableNotifications()</tt> and
 *  <tt>Sci_DisableNotifications()</tt> from the code.
 */
#define	SCI_NOTIFICATIONS_API		STD_OFF

/** @brief	Enable Clear To Send
 *
 *  - <tt>1</tt>:	CTS hardware flow control is enabled. Data is only
 *  			transmitted when the U1CTS signal is asserted.
 *  - <tt>0</tt>:	CTS hardware flow control is disabled.
 *
 *  This bit is implemented only on Channel 1 (UART1) and is reserved for
 *  Channel 0 (UART0) and Channel 2 (UART2).
 */
#define	SCI_CH_HW_CTS_ENABLE	0x00008000

/** @brief	Enable Request to Send
 *
 *  - <tt>1</tt>:	RTS hardware flow control is enabled. Data is only
 *  			requested (by asserting U1RTS) when the receive FIFO has
 *  			available entries.
 *  - <tt>0</tt>:	RTS hardware flow control is disabled.
 *
 *  This bit is implemented only on Channel 1 (UART1) and is reserved for
 *  Channel 0 (UART0) and Channel 2 (UART2).
 */
#define	SCI_CH_HW_RTS_ENABLE	0x00004000

/** @brief	Request to Send
 *
 *  When Request to Send is disabled, the status of this bit is reflected on the
 *  U1RTS signal. If Request to Send is enabled, this bit is ignored on a write
 *  and should be ignored on read.
 *
 *  This bit is implemented only on Channel 1 (UART1) and is reserved for
 *  Channel 0 (UART0) and Channel 2 (UART2).
 */
#define	SCI_CH_HW_RTS		0x00000800

/** @brief	Data Terminal Ready
 *
 *  This bit sets the state of the U1DTR output.
 *
 *  This bit is implemented only on Channel 1 (UART1) and is reserved for
 *  Channel 0 (UART0) and Channel 2 (UART2).
 */
#define	SCI_CH_HW_DTR		0x00000400

/** @brief	UART Receive Enable
 *
 *  - <tt>1</tt>:	The receive section of the UART is enabled.
 *  - <tt>0</tt>:	The receive section of the UART is disabled.
 *
 *  If the Channel (UART) is disabled in the middle of a receive, it completes
 *  the current character before stopping.
 *
 *  @note To enable reception, the UART Enable bit must also be set.
 */
#define	SCI_CH_HW_RX		0x000000200

/** @brief	UART Transmit Enable
 *
 *  - <tt>1</tt>:	The transmit section of the UART is enabled.
 *  - <tt>0</tt>:	The transmit section of the UART is disabled.
 *
 *  If the Channel (UART) is disabled in the middle of a transmission, it
 *  completes the current character before stopping.
 *
 *  @note To enable transmission, the UART Enable bit must also be set.
 */
#define	SCI_CH_HW_TX		0x00000100

/** @brief	UART Loop Back Enable
 *
 *  - <tt>1</tt>:	The Tx path is fed through the Rx path.
 *  - <tt>0</tt>:	Normal operation.
 */
#define	SCI_CH_HW_LOOP_BACK	0x00000080

/** @brief	LIN Mode Enable
 *
 *  - <tt>1</tt>:	The Channel (UART) operates in LIN mode.
 *  - <tt>0</tt>:	Normal operation.
 */
#define	SCI_CH_HW_LIN		0x00000040

/** @brief	High-Speed Enable
 *
 *  - <tt>0</tt>:	The Channel (UART) is clocked using the system clock
 *  			divided by 16.
 *  - <tt>1</tt>:	The Channel (UART) is clocked using the system clock
 *  			divided by 8.
 *
 *  @note	System clock used is also dependent on the baud-rate divisor
 *  		configuration.
 */
#define	SCI_CH_HW_HIGH_SPEED	0x00000020

/** @brief	End of Transmission
 *
 *  This bit determines the behavior of the TXRIS bit in the UARTRIS register.
 *
 *  - <tt>1</tt>:	The TXRIS bit is set only after all transmitted data,
 *  			including stop bits, have cleared the serializer.
 *  - <tt>0</tt>:	The TXRIS bit is set when the transmit FIFO condition
 *  			specified in UARTIFLS is met.
 */
#define	SCI_CH_HW_EOT		0x00000010

/** @brief	ISO 7816 Smart Card Support
 *
 *  - <tt>1</tt>:	The Channel (UART) operates in Smart Card mode.
 *  - <tt>0</tt>:	Normal operation.
 *
 *  The application must ensure that it sets 8-bit word length (WLEN set to 0x3)
 *  and even parity (PEN set to 1, EPS set to 1, SPS set to 0) in UARTLCRH when
 *  using ISO 7816 mode.
 *
 *  In this mode, the value of the STP2 bit in UARTLCRH is ignored and the
 *  number of stop bits is forced to 2. Note that the UART does not support
 *  automatic retransmission on parity errors. If a parity error is detected on
 *  transmission, all further transmit operations are aborted and software must
 *  handle retransmission of the affected byte or message.
 */
#define	SCI_CH_HW_SMART_CARD	0x00000008

/** @brief	UART SIR Low-Power Mode
 *
 *  This bit selects the IrDA encoding mode.
 *
 *  - <tt>1</tt>:	The Channel (UART) operates in SIR Low-Power mode.
 *  			Low-level bits are transmitted with a pulse width which
 *  			is 3 times the period of the IrLPBaud16 input signal,
 *  			regardless of the selected bit rate.
 *  - <tt>0</tt>:	Low-level bits are transmitted as an active High pulse
 *  			with a width of 3/16th of the bit period.
 *
 *  Setting this bit uses less power, but might reduce transmission distances.
 */
#define	SCI_CH_HW_SIR_LOW_PWR	0x00000004

/** @brief	UART SIR Enable
 *
 *  - <tt>1</tt>:	The IrDA SIR block is enabled, and the Channel (UART)
 *  			will transmit and receive data using SIR protocol.
 *  - <tt>0</tt>:	 Normal operation.
 */
#define	SCI_CH_HW_SIR_ENABLE	0x00000002

/** @brief	UART Enable
 *
 *  - <tt>1</tt>:	The Channel (UART) is enabled.
 *  - <tt>0</tt>:	The Channel (UART) is disabled.
 *
 *  If the Channel (UART) is disabled in the middle of transmission or
 *  reception, it completes the current character before stopping.
 */
#define	SCI_CH_HW_ENABLE	0x00000001


/** @brief	UART Stick Parity Select
 *
 *  - When parity is enabled, parity even is selected and stick parity is
 *    selected, the parity bit is transmitted and checked as a 0.
 *  - When parity is enabled, parity odd is selected and stick parity is
 *    selected, the parity bit is transmitted and checked as a 1.
 */
#define	SCI_CH_HW_STICK_PARITY	0x00000080

/** @brief	UART Word Length (5 bits)
 *
 *  5 bits transmitted or received in a frame.
 */
#define	SCI_CH_HW_5_BITS	0x00000000

/** @brief	UART Word Length (6 bits)
 *
 *  6 bits transmitted or received in a frame.
 */
#define	SCI_CH_HW_6_BITS	0x00000020

/** @brief	UART Word Length (7 bits)
 *
 *  7 bits transmitted or received in a frame.
 */
#define	SCI_CH_HW_7_BITS	0x00000040

/** @brief	UART Word Length (8 bits)
 *
 *  8 bits transmitted or received in a frame.
 */
#define	SCI_CH_HW_8_BITS	0x00000060

/** @brief	UART Enable FIFOs
 *
 *  - <tt>1</tt>:	The transmit and receive FIFObuffers are enabled
 *  			(FIFOmode).
 *  - <tt>0</tt>:	The FIFOs are disabled (Character mode). The FIFOs
 *  			become 1-byte-deep holding registers.
 */
#define	SCI_CH_HW_FIFO		0x00000010

/** @brief	UART Two Stop Bits Select
 *
 *  - <tt>1</tt>:	Two stop bits are transmitted at the end of a frame. The
 *  			receive logic does not check for two stop bits being
 *  			received.
 *  - <tt>0</tt>:	One stop bit is transmitted at the end of a frame.
 */
#define	SCI_CH_HW_2_STOP_BITS	0x00000008

/** @brief	UART Even Parity Select
 *
 *  - <tt>1</tt>:	Even parity generation and checking is performed during
 *  			transmission and reception, which checks for an even
 *  			number of 1s in data and parity bits.
 *  - <tt>0</tt>:	Odd parity is performed, which checks for an odd number
 *  			of 1s.
 *
 *  @note This bit has no effect when parity is disabled.
 */
#define	SCI_CH_HW_PARITY_EVEN	0x00000004

/** @brief	UART Parity Enable
 *
 *  - <tt>1</tt>:	Parity checking and generation is enabled.
 *  - <tt>0</tt>:	Parity is disabled and no parity bit is added to the
 *  			data frame.
 */
#define	SCI_CH_HW_PARITY_ENABLE	0x00000002

/** @brief	UART Send Break
 *
 *  - <tt>1</tt>:	A Low level is continually output on the UnTx signal,
 *  			after completing transmission of the current character.
 *  			For the proper execution of the break command, software
 *  			must set this bit for at least two frames (character
 *  			periods).
 *  - <tt>0</tt>:	Normal use.
 */
#define	SCI_CH_HW_SEND_BREAK	0x00000001

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
   *  - <tt>FALSE</tt>:	Precision Internal Oscillator.
   *  - <tt>TRUE</tt>:	System Clock.
   */
  boolean		SciSysClock;

  /** @brief	UART System Control
   *
   *  UARTCTL Register:
   *  Bit/Field	Description
   *   15	Enable Clear To Send
   *   14	Enable Request to Send
   *   13:13	Reserved
   *   11	Request to Send
   *   10	Data Terminal Ready
   *    9	UART Receive Enable
   *    8	UART Transmit Enable
   *    7	UART Loop Back Enable
   *    6	LIN Mode Enable
   *    5	High-Speed Enable
   *    4	End of Transmission
   *    3	ISO 7816 Smart Card Support
   *    2	UART SIR Low-Power Mode
   *    1	UART SIR Enable
   *    0	UART Enable
   */
  uint32		SciSysCtrl;

  /** @brief	UART Line Control
   *
   *  UARTLCRH Register:
   *  Bit/Field	Description
   *   31:8	Reserved
   *    7	UART Stick Parity Select
   *    6:5	UART Word Length
   *    4	UART Enable FIFOs
   *    3	UART Two Stop Bits Select
   *    2	UART Even Parity Select
   *    1	UART Parity Enable
   *    0	UART Send Break
   */
  uint32		SciLineCtrl;

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
 */ 
#define	SCI_CHANNEL_0	0x00	/**< Channel 0 */
#define	SCI_CHANNEL_1	0x01	/**< Channel 1 */
#define	SCI_CHANNEL_2	0x02	/**< Channel 2 */
#define	SCI_CHANNEL_3	0x03	/**< Channel 3 */
#define	SCI_CHANNEL_4	0x04	/**< Channel 4 */
#define	SCI_CHANNEL_5	0x05	/**< Channel 5 */
#define	SCI_CHANNEL_6	0x06	/**< Channel 6 */
#define	SCI_CHANNEL_7	0x07	/**< Channel 7 */

/** Number of Channels */
#define	SCI_CHANNELS_NUMBER	SCI_CHANNEL_7 + 1

/** @brief	Channel 4 Transmission Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxNotification_Channel_4()</tt> is for
 *  the transmission notifications callback function for SCI Channel 4 and shall
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
void Sci_TxNotifications_Channel_4(
  void
);

/** @brief	Channel 4 Transmission Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_TxErrNotification_Channel_4()</tt> is for
 *  the transmission errors notifications callback function for SCI Channel 4
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
void Sci_TxErrNotifications_Channel_4(
  void
);

/** @brief	Channel 4 Reception Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxNotification_Channel_4()</tt> is for
 *  the reception notifications callback function for SCI Channel 4 and shall be
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
void Sci_RxNotifications_Channel_4(
  void
);

/** @brief	Channel 4 Reception Errors Notifications Callback
 *
 *  The notification prototype <tt>Sci_RxErrNotification_Channel_4()</tt> is for
 *  the reception errors notifications callback function for SCI Channel 4 and
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
void Sci_RxErrNotifications_Channel_4(
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
