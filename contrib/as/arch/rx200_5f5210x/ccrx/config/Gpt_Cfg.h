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

/** @file	Gpt_Cfg.h
 *  @brief	fake-druid AUTOSAR-"like" GPT Driver Configuration Header File.
 *
 *  <b>GPT369</b>:	<tt>Gpt_Cfg.h</tt> Module configuration file, if
 *  			pre-compile defines are used (<tt>BSW00345</tt>,
 *  			<tt>BSW00381</tt>, <tt>BSW412</tt>)
 *
 *  Configured for (GPT): Renesas RX210R5F5210x
 *
 *  @author	Giuanluca Franchino
 *  @date	2012
 */


#if !(\
 ((GPT_SW_MAJOR_VERSION == 1) && \
  (GPT_SW_MINOR_VERSION == 0) && \
  (GPT_SW_PATCH_VERSION == 0))\
)
#error Gpt: Configuration file expected BSW module version to be 1.0.0.*
#endif


#ifndef	GPT_CFG_H
#define	GPT_CFG_H

#include "Mcu.h"

/*
 * GptDriverConfiguration
 *
 * GPT183_Conf:	This container contains the module-wide configuration
 * 		(parameters) of the GPT Driver
 */

/** @brief	Development Error Detection
 *
 *  <b>GPT321_Conf</b>:	<tt>GptDevErrorDetect</tt>.
 *  			Enables/Disables development error detection.
 *
 *  <b>GPT175</b>:	The detection of development errors is configurable
 *  			(<tt>STD_ON</tt>/<tt>STD_OFF</tt>) at pre-compile time.
 *  			The switch <tt>GptDevErrorDetect</tt> shall activate or
 *  			deactivate the detection of all development errors.
 *
 *  <b>GPT176</b>:	If the <tt>GptDevErrorDetect</tt> switch is enabled, API
 *  			parameter checking and call sequence checking is
 *  			enabled.
 *
 *  <b>GPT332</b>:	If the <tt>GptDevErrorDetect</tt> switch is enabled:
 *  			When a development error occurs the corresponding GPT
 *  			function shall skip the desired functionality (leave
 *  			service without any action). (<tt>BSW12448</tt>)
 *
 *  <b>GPT177</b>:	If production errors are specified for GPT module:
 *  			The detection of production code errors cannot be
 *  			switched off.
 *
 *  <b>GPT178</b>:	Detected development errors shall be reported to the
 *  			<tt>Det_ReportError()</tt> service of the Development
 *  			Error Tracer if the preprocessor switch
 *  			<tt>GptDevErrorDetect</tt> is set. (<tt>BSW00338</tt>,
 *  			<tt>BSW00369</tt>, <tt>BSW12448</tt>)
 *
 *  <b>GPT179</b>:	If production errors are specified for GPT module:
 *  			Production errors shall be reported to Diagnostic Event
 *  			Manager. (<tt>BSW00369</tt>, <tt>BSW00339</tt>)
 */
#define	GPT_DEV_ERROR_DETECT			STD_OFF

/** @brief	Wakeup Source Reporting
 *
 *  <b>GPT322_Conf</b>:	<tt>GptReportWakeupSource</tt>
 *  			Enables/Disables wakeup source reporting.
 *
 *  <b>GPT255</b>:	The function <tt>Gpt_SetMode()</tt> is only available
 *  			if the configuration parameter
 *  			<tt>GptReportWakeupSource</tt> is enabled.
 *
 *  <b>GPT157</b>:	The function <tt>Gpt_DisableWakeup()</tt> is only
 *  			feasible, if <tt>GptReportWakeupSource</tt> is
 *  			statically configured available.
 *
 *  <b>GPT158</b>:	The function <tt>Gpt_EnableWakeup()</tt> is only
 *  			feasible, if <tt>GptReportWakeupSource</tt> is
 *  			statically configured available.
 *
 *  <b>GPT322</b>:	The function <tt>Gpt_CheckWakeup()</tt> is only
 *  			feasible, if <tt>GptReportWakeupSource</tt> is
 *  			statically configured available.
 */
#define	GPT_REPORT_WAKEUP_SOURCE		STD_OFF

/*
 * GptConfigurationOfOptApiServices
 *
 * GPT193_Conf:	This container contains all configuration switches for
 * 		configuring optional API services of the GPT driver.
 */

/** @brief	De-Init API
 *
 *  <b>GPT314_Conf</b>:	<tt>GptDeinitApi</tt>.
 *  			Adds / removes the service <tt>Gpt_DeInit()</tt> from
 *  			the code.
 *
 *  <b>GPT194</b>:	The function <tt>Gpt_DeInit()</tt> shall be pre compile
 *  			time configurable On/Off by the configuration parameter:
 *  			<tt>GptDeInitApi</tt>. (<tt>BSW171</tt>)
 */
#define	GPT_DEINIT_API				STD_ON

/** @brief	Notification API 
 *
 *  <b>GPT315_Conf</b>:	<tt>GptEnableDisableNotificationApi</tt>.
 *  			Adds / removes the services
 *  			<tt>Gpt_EnableNotifications()</tt> and
 *  			<tt>Gpt_DisableNotifications()</tt> from the code.
 *
 *  <b>GPT199</b>:	The function <tt>Gpt_EnableNotification()</tt> shall be
 *  			pre compile time configurable On/Off by the
 *  			configuration parameter:
 *  			<tt>GptEnableDisableNotificationApi</tt>
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT200</b>:	The function <tt>Gpt_DisableNotification()</tt> shall be
 *  			pre compile time configurable On/Off by the
 *  			configuration parameter:
 *  			<tt>GptEnableDisableNotificationApi</tt>.
 *  			(<tt>BSW171</tt>)
 */
#define	GPT_ENABLE_DISABLE_NOTIFICATION_API	STD_ON

/** @brief	Elapsed Time Retrieval API
 *
 *  <b>GPT317_Conf</b>:	<tt>GptTimeElapsedApi</tt>.
 *  			Adds / removes the service <tt>Gpt_GetTimeElapsed()</tt>
 *  			from the code.
 *
 *  <b>GPT195</b>:	The function <tt>Gpt_GetTimeElapsed()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptTimeElapsedApi</tt>. (<tt>BSW171</tt>)
 */
#define	GPT_TIME_ELAPSED_API			STD_ON

/** @brief	Remaining Time Retrieval API
 *
 *  <b>GPT318_Conf</b>:	<tt>GptTimeRemainingApi</tt>.
 *  			Adds / removes the service
 *  			<tt>Gpt_GetTimeRemaining()</tt> from the code.
 *
 *  <b>GPT196</b>:	?The function <tt>Gpt_GetTimeRemaining()</tt> shall be
 *  			pre compile time configurable On/Off by the
 *  			configuration parameter: <tt>GptTimeRemainingApi</tt>.
 *  			(<tt>BSW171</tt>)
 */
#define	GPT_TIME_REMAINING_API			STD_ON

/** @brief	Version Informations Retrieval API
 *
 *  <b>GPT319_Conf</b>:	<tt>GptVersionInfoApi</tt>
 *  			Adds / removes the service <tt>Gpt_GetVersionInfo()</tt>
 *  			from the code.
 *
 *  <b>GPT182</b>:	The function <tt>Gpt_GetVersionInfo()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptVersionInfoApi</tt> (<tt>BSW171</tt>)
 *
 */
#define	GPT_VERSION_INFO_API			STD_ON

/** @brief	Wake-up Functionality API
 *
 *  <b>GPT320_Conf</b>:	<tt>GptWakeupFunctionalityApi</tt>
 *  			Adds / removes the services <tt>Gpt_SetMode()</tt>,
 *  			<tt>Gpt_EnableWakeup()</tt>,
 *  			<tt>Gpt_DisableWakeup()</tt> and
 *  			<tt>Gpt_CheckWakeup()</tt> from the code.
 *
 *  <b>GPT201</b>:	The function <tt>Gpt_SetMode()</tt> shall be pre compile
 *  			time configurable On/Off by the configuration parameter:
 *  			<tt>GptWakeupFunctionalityApi</tt>. (<tt>BSW171</tt>)
 *
 *  <b>GPT202</b>:	The function <tt>Gpt_DisableWakeup()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptWakeupFunctionalityApi</tt>.
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT203</b>:	The function <tt>Gpt_EnableWakeup()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptWakeupFunctionalityApi</tt>.
 *  			(<tt>BSW171</tt>)
 *
 *  <b>GPT324</b>:	The function <tt>Gpt_CheckWakeup()</tt> shall be pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter: <tt>GptWakeupFunctionalityApi</tt>.
 */
#define	GPT_WAKEUP_FUNCTIONALITY_API		STD_OFF

/** @brief	Channel Wake-up Functionality API
 *
 *  <tt>GptChannelWakeupFunctionalityApi</tt>
 *  Adds / removes the services <tt>Gpt_GoToSleep()</tt>, <tt>Gpt_Wakeup()</tt>
 *  and <tt>Gpt_GetStatus()</tt> from the code.
 *
 *  The function <tt>Gpt_GoToSleep()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter:
 *  <tt>GptChannelWakeupFunctionalityApi</tt>.
 *
 *  The function <tt>Gpt_Wakeup()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter:
 *  <tt>GptChannelWakeupFunctionalityApi</tt>.
 *
 *  The function <tt>Gpt_GetStatus()</tt> shall be pre compile time configurable
 *  On/Off by the configuration parameter:
 *  <tt>GptChannelWakeupFunctionalityApi</tt>.
 */
#define	GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API	STD_ON

/*
 * The configuration process for Gpt module shall provide symbolic names for
 * each configured GPT channel.
 */ 
 
#define	GPT_CHANNEL_TMR0	0x00	/**< Channel TMR 0  */
#define	GPT_CHANNEL_TMR1	0x01	/**< Channel TMR 1  */
#define	GPT_CHANNEL_TMR2	0x02	/**< Channel TMR 2  */
#define	GPT_CHANNEL_TMR3	0x03	/**< Channel TMR 3  */
#define	GPT_CHANNEL_TMR01	0x04	/**< Channel TMR 01 */
#define	GPT_CHANNEL_TMR23	0x05	/**< Channel TMR 23 */
#define	GPT_CHANNEL_CMT0	0x06	/**< Channel CMT 0  */
#define	GPT_CHANNEL_CMT1	0x07	/**< Channel CMT 1  */
#define	GPT_CHANNEL_CMT2	0x08	/**< Channel CMT 2  */
#define	GPT_CHANNEL_CMT3	0x09	/**< Channel CMT 3  */
#define	GPT_CHANNEL_MTU0	0x0A	/**< Channel MTU2A MTU0 */
#define	GPT_CHANNEL_MTU1	0x0B	/**< Channel MTU2A MTU1 */
#define	GPT_CHANNEL_MTU2	0x0C	/**< Channel MTU2A MTU2 */
#define GPT_CHANNEL_MTU12	0x0D	/**< Channel MTU2A MTU12 */
#define	GPT_CHANNEL_MTU3	0x0E	/**< Channel MTU2A MTU3 */
#define	GPT_CHANNEL_MTU4	0x0F	/**< Channel MTU2A MTU4 */
#define	GPT_CHANNEL_MTU5U	0x10	/**< Channel MTU2A MTU5U */
#define	GPT_CHANNEL_MTU5V	0x11	/**< Channel MTU2A MTU5V */
#define	GPT_CHANNEL_MTU5W	0x12	/**< Channel MTU2A MTU5W */



/** @brief	Channel Mode.
 *
 *  <b>GPT309_Conf</b>:	<tt>GPT_CHANNEL_MODE</tt>
 *
 *  Specifies the behaviour of the timer channel after the target time is
 *  reached.
 */
typedef enum {

  /** @brief	Channel Countinuous Mode
   *
   *  After reaching the target time, the timer continues running with the
   *  value "zero" again.
   */
  GPT_CH_MODE_CONTINUOUS,

  /** @brief	Channel One-Shot Mode
   *
   *  After reaching the target time, the timer stops automatically (timer
   *  expired).
   */
  GPT_CH_MODE_ONESHOT

} Gpt_ChannelMode;

/*
 * The following are defines for the bit fields in 
 * Gpt_ChannelConfigType->GptChannelHWConfig. (See below.)
 */

/*
 * TMR module
 */

/** @brief	TMRx module, Clock Prescaler PCLK/1
 *
 */
#define	GPT_HW_TMR_PCLK1	0x08

/** @brief	TMRx module, Clock Prescaler PCLK/2
 *
 */
#define	GPT_HW_TMR_PCLK2	0x09

/** @brief	TMRx module, Clock Prescaler PCLK/8
 *
 */
#define	GPT_HW_TMR_PCLK8	0x0A

/** @brief	TMRx module, Clock Prescaler PCLK/32
 *
 */
#define	GPT_HW_TMR_PCLK32	0x0B

/** @brief	TMRx module, Clock Prescaler PCLK/64
 *
 */
#define	GPT_HW_TMR_PCLK64	0x0C

/** @brief	TMRx module, Clock Prescaler PCLK/1024
 *
 */
#define	GPT_HW_TMR_PCLK1024	0x0D

/** @brief	TMRx module, Clock Prescaler PCLK/8192
 *
 */
#define	GPT_HW_TMR_PCLK8192	0x0E

/** @brief	TMRx module, Counts at TMR1.TCNT overflow
 *
 */
#define	GPT_HW_TMR_CLK_TMR1OV	0x18

/** @brief	TMRx module, Counts at TMR3.TCNT overflow
 *
 */
#define	GPT_HW_TMR_CLK_TMR3_OV	0x18

/** @brief	TMRx module cleared by compare match A 
 *
 */
#define GPT_HW_TMR_CLRA		0x20

/** @brief	TMRx module cleared by compare match B
 *
 */
#define GPT_HW_TMR_CLRB		0x40

/*
 * CMT module.
 */
/** @brief	CMT module, Clock Prescaler PCLK/8
 *
 */
#define	GPT_HW_CMT_PCLK8	0x00

/** @brief	CMT module, Clock Prescaler PCLK/32
 *
 */
#define	GPT_HW_CMT_PCLK32	0x01

/** @brief	CMT module, Clock Prescaler PCLK/128
 *
 */
#define	GPT_HW_CMT_PCLK128	0x02

/** @brief	CMT module, Clock Prescaler PCLK/512
 *
 */
#define	GPT_HW_CMT_PCLK512	0x03

/*
 * MTU2a module.
 */
/** @brief	MTU2A module, Clock Prescaler PCLK/1
 *
 */
#define	GPT_HW_MTU_PCLK1	0x00

/** @brief	MTU2A module, Clock Prescaler PCLK/4
 *
 */
#define	GPT_HW_MTU_PCLK4	0x01

/** @brief	MTU2A module, Clock Prescaler PCLK/16
 *
 */
#define	GPT_HW_MTU_PCLK16	0x02

/** @brief	MTU2A module, Clock Prescaler PCLK/64
 *
 */
#define	GPT_HW_MTU_PCLK64	0x03

/** @brief	MTU3 module, Clock Prescaler PCLK/256
 *
 */
#define	GPT_HW_MTU3_PCLK256	0x04

/** @brief	MTU4 module, Clock Prescaler PCLK/256
 *
 */
#define	GPT_HW_MTU4_PCLK256	0x04

/** @brief	MTU2A module, Clock Prescaler PCLK/64
 *
 */
#define	GPT_HW_MTU1_PCLK256	0x06

/** @brief	MTU1 module, Counts on MTU2.TCNT
 *
 */
#define	GPT_HW_MTU1_MTU2_OV	0x07

/** @brief	MTU2 module, Clock Prescaler PCLK/1024
 *
 */
#define	GPT_HW_MTU2_PCLK1024	0x07

/** @brief	MTU3 module, Clock Prescaler PCLK/1024
 *
 */
#define	GPT_HW_MTU3_PCLK1024	0x05

/** @brief	MTU4 module, Clock Prescaler PCLK/1024
 *
 */
#define	GPT_HW_MTU4_PCLK1024	0x05

/** @brief	MTU2A module cleared by compare match A 
 *
 */
#define GPT_HW_MTU_CLRA		0x20

/** @brief	MTU2A module cleared by compare match B
 *
 */
#define GPT_HW_MTU_CLRB		0x40

/** @brief	MTU2A module cleared by compare match C 
 *
 */
#define GPT_HW_MTU_CLRC		0xA0

/** @brief	MTU2A module cleared by compare match D
 *
 */
#define GPT_HW_MTU_CLRD		0xC0



/** @brief	Channel Settings Configuration Parameters
 *
 *  <b>GPT184_Conf</b>:	<tt>GptChannelConfiguration</tt>
 *
 *  Configuration of an individual GPT channel.
 */
typedef struct {

  /** @brief	Channel Identifier
   *
   *  <b>GPT308_Conf</b>:	<tt>GPT_CHANNEL_ID</tt>
   *
   *  Channel Id of the GPT channel. This value will be assigned to the symbolic
   *  name derived of the <tt>GptChannelConfiguration</tt> container short name.
   */
  Gpt_ChannelType	GptChannelId;

  /** @brief	Channel Mode
   *
   *  <b>GPT309_Conf</b>:	<tt>GPT_CHANNEL_MODE</tt>
   *
   *  Specifies the behaviour of the timer channel after the target time is
   *  reached.
   */
  Gpt_ChannelMode	GptChannelMode;

  /** @brief	Channel Tick Frequency
   *
   *  <b>GPT331_Conf</b>:	Specifies the tick frequency of the timer
   *  				channel in Hz.
   */
  /* float64		GptChannelTickFrequency; */

  /** @brief	Channel Tick Max Value
   *
   *  <b>GPT332_Conf</b>:	Maximum value in ticks, the timer channel is
   *  				able to count. With the next tick, the timer
   *  				rolls over to zero.
   */
  /* uint64		GptChannelTickValueMax; */

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )
  /** @brief	Wake-up Support
   *
   *  <b>GPT311_Conf</b>:	<tt>GPT_ENABLE_WAKEUP</tt>
   *
   *  Enables wakeup capability of MCU for a channel.
   *
   */
  /* boolean		GptEnableWakeup; */
#endif

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
  /** @brief	Notification Callback Function Pointer
   *
   *  <b>GPT312_Conf</b>:	<tt>GPT_NOTIFICATION</tt>
   *
   *  Function pointer to callback function (for non-wakeup notification)
   *
   *  The notification prototype <tt>Gpt_Notification_<channel>()</tt> is for
   *  the notifications callback function and shall be implemented by the user.
   *
   *  The GPT module's environment shall declare a separate notifications
   *  callback for each channel to avoid parameters in notification services and
   *  to improve run time efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
   *
   *  <b>GPT086</b>:	The notifications callback
   *  			<tt>Gpt_Notification_<channel>()</tt> shall be
   *  			configurable as pointers to user defined functions
   *  			within the configuration structure.
   *
   *  <b>GPT209</b>:	Each channel shall provide its own notifications
   *  			callback if configured.
   *
   *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
   *  			notifications.
   *
   *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
   *  			whenever the defined target time of the channel is
   *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
   *
   *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
   *  			responsible for resetting the interrupt flags (if needed
   *  			by hardware) and calling the according notification
   *  			function. (<tt>BSW12129</tt>)
   *
   *  <b>GPT362</b>:	For all available channels, callback functions have to
   *  			be declared by the configuration tool.
   */
  Gpt_Notification	GptNotificationPtr;
#endif

  /** @brief	Clock Reference
   *
   *  <b>GPT329_Conf</b>	<tt>GptClockReferencePoint</tt>
   *  				This container contains a parameter, which
   *  				represents a  reference to a container of the
   *  				type <tt>McuClockReferencePoint</tt> (defined
   *  				in module MCU). A container is needed to support
   *  				multiple clock references (hardware dependent).
   *
   *  <b>GPT330_Conf</b>:	<tt>GptClockReference</tt>
   *  				Reference to a container of the type
   *  				<tt>McuClockReferencePoint</tt>, to select an
   *  				input clock. The configuration editor for the
   *  				GPT module can support the integrator by only
   *  				allowing a selection of those clock reference
   *  				points that can be connected physically to the
   *  				GPT hardware peripheral. The desired frequency
   *  				(desired by GPT) has to be the same as the
   *  				selected and provided frequency of the MCU
   *  				configuration. This has to be checked
   *  				automatically.
   *
   *  <b>GPT333_Conf</b>:	<tt>GptChannelClkSrcRef</tt>
   *  				Reference to the <tt>GptClockReferencePoint</tt>
   *  				from which the channel clock is derived.
   */
  /* Mcu_ClockType		GptClockReference; */

#if ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON )
  /** @brief	Wake-up Configuration
   *
   *  <b>GPT235_Conf </b>:	<tt>GptWakeupConfiguration</tt>
   *  				Function pointer to callback function (for
   *  				non-wakeup notification).
   *
   *  <b>GPT313_Conf</b>:	<tt>GptWakeupSourceRef</tt>
   *  				In case the wakeup-capability is true this value
   *  				is transmitted to the Ecu State Manager.
   *  				Implementation Type: reference to
   *  				<tt>EcuM_WakeupSourceType</tt>
   */
  /* Gpt_WakeupConfigurationPtr	GptWakeupConfiguration; */
#endif

#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
  /** @brief	Channel Wake-up Support
   *
   *  Specifies if the GPT channel supports wake-up functionality.
   */
  boolean		GptChannelWakeupSupport;
#endif

  /** @brief	Channel Hardware Configuration
   *
   *  Bit/Field	Description
   *  	8	Timer reset detection condition (only for TMR module).   
   *	7:5 Configuration (Clear Condition)
   *	4:0	Prescaler/Clk Config	
   */
   uint16		GptChannelHWConfig;

  /** @brief	Channel Hardware Mode
   *
   *  Bit/Field	Description
   *   31:12	Reserved
   *   11	PWM Legacy Operation
   *   10	Match Register Update
   *    9	PWM Interrupt Enable
   *    8	Interval Load Write
   *    7	Snap-Shot Mode
   *    6	Wait-on-Trigger
   *    5	Match Interrupt Enable
   *    4	Count Direction
   *    3	Alternate Mode Select
   *    2	Capture Mode
   *    1:0	Timer Mode
   */
  /* uint32		GptChannelHWMode; */

  /** @brief	Channel Hardware Control
   *
   *  Bit/Field	Description
   *   31:7	Reserved
   *    6	PWM Output Level
   *    5	Output Trigger Enable
   *    4	RTC Stall Enable
   *    3:2	Event Mode
   *    1	Stall Enable
   *    0	Timer Enable
   */
  /* uint32		GptChannelHWCtrl; */

} Gpt_ChannelConfigType;

/** @brief	GPT Configuration Parameters
 *
 *  <b>GPT357</b>:	This is the type of the data structure including the
 *  			configuration set required for initializing the GPT
 *  			timer unit. (<tt>BSW00404</tt>, <tt>BSW00405</tt>,
 *  			<tt>BSW00438</tt>, <tt>BSW00305</tt>, <tt>BSW00414</tt>,
 *  			<tt>BSW12263</tt>)
 *
 *  The structure <tt>Gpt_ConfigType</tt> is an external data structure (i.e.
 *  implementation specific) and shall contain the initialization data for the
 *  GPT module. It shall contain:
 *  - GPT dependent properties
 *  - GPT harware unit initialization parameters
 *  - SFR's settings affecting the GPT channels
 */
typedef struct {

  /** @brief	GPT Channels Number
   *
   *  This parameter shall represent the number of Channels available for the
   *  GPT. calculationFormula = Number of configured <tt>GptChannel</tt>.
   */
  uint8_least			GptNumberOfGptChannels;

  /** @brief	Channels Setting Configuration Parameters
   *
   *  This container contains the configuration (parameters) for the channel
   *  settings of the GPT.
   */
  const Gpt_ChannelConfigType *	GptChannels;
  
} Gpt_ConfigType;



#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/*
 * The configuration process for Gpt module shall provide function prototypes
 * for notification callback functions for each configured GPT channel.
 */

#ifdef	GPT_CHANNEL_TMR0
/** @brief	Channel TMR0 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR0()</tt> is for
 *  the notification callback function for GPT Channel TMR0 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR0()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR0(void);

#endif	/* GPT_CHANNEL_TMR0 */

#ifdef	GPT_CHANNEL_TMR1
/** @brief	Channel TMR1 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR1()</tt> is for
 *  the notification callback function for GPT Channel TMR1 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR1()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR1(void);

#endif	/* GPT_CHANNEL_TMR1 */

#ifdef	GPT_CHANNEL_TMR2
/** @brief	Channel TMR2 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR2()</tt> is for
 *  the notification callback function for GPT Channel TMR2 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR2()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR2(void);

#endif	/* GPT_CHANNEL_TMR2 */

#ifdef	GPT_CHANNEL_TMR3
/** @brief	Channel TMR3 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR3()</tt> is for
 *  the notification callback function for GPT Channel TMR3 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR3()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR3(void);

#endif	/* GPT_CHANNEL_TMR3 */

#ifdef	GPT_CHANNEL_TMR4
/** @brief	Channel TMR4 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR4()</tt> is for
 *  the notification callback function for GPT Channel TMR4 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR4()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR4(void);

#endif	/* GPT_CHANNEL_TMR4 */

#ifdef	GPT_CHANNEL_TMR01
/** @brief	Channel TMR01 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR01()</tt> is for
 *  the notification callback function for GPT Channel TMR01 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR01()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR01(void);

#endif	/* GPT_CHANNEL_TMR01 */

#ifdef	GPT_CHANNEL_TMR23
/** @brief	Channel TMR23 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_TMR23()</tt> is for
 *  the notification callback function for GPT Channel TMR23 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_TMR23()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_TMR23(void);

#endif	/* GPT_CHANNEL_TMR23 */

#ifdef	GPT_CHANNEL_CMT0
/** @brief	Channel CMT0 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_CMT0()</tt> is for
 *  the notification callback function for GPT Channel CMT0 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_CMT0()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_CMT0(void);

#endif	/* GPT_CHANNEL_CMT0 */

#ifdef	GPT_CHANNEL_CMT1
/** @brief	Channel CMT1 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_CMT1()</tt> is for
 *  the notification callback function for GPT Channel CMT1 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_CMT1()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_CMT1(void);

#endif	/* GPT_CHANNEL_CMT1 */

#ifdef	GPT_CHANNEL_CMT2
/** @brief	Channel CMT2 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_CMT2()</tt> is for
 *  the notification callback function for GPT Channel CMT2 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_CMT2()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_CMT2(void);

#endif	/* GPT_CHANNEL_CMT2 */

#ifdef	GPT_CHANNEL_CMT3
/** @brief	Channel CMT3 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_CMT3()</tt> is for
 *  the notification callback function for GPT Channel CMT0 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_CMT3()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_CMT3(void);

#endif	/* GPT_CHANNEL_CMT3 */

#ifdef	GPT_CHANNEL_MTU0
/** @brief	Channel MTU0 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU0()</tt> is for
 *  the notification callback function for GPT Channel MTU0 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU0()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU0(void);

#endif	/* GPT_CHANNEL_MTU0 */

#ifdef	GPT_CHANNEL_MTU1
/** @brief	Channel MTU1 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU1()</tt> is for
 *  the notification callback function for GPT Channel MTU1 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU1()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU1(void);

#endif	/* GPT_CHANNEL_MTU1 */

#ifdef	GPT_CHANNEL_MTU2
/** @brief	Channel MTU2 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU2()</tt> is for
 *  the notification callback function for GPT Channel MTU2 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU2()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU2(void);

#endif	/* GPT_CHANNEL_MTU2 */

#ifdef	GPT_CHANNEL_MTU12
/** @brief	Channel MTU12 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU12()</tt> is for
 *  the notification callback function for GPT Channel MTU12 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU12()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU12(void);

#endif	/* GPT_CHANNEL_MTU12 */

#ifdef	GPT_CHANNEL_MTU3
/** @brief	Channel MTU3 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU3()</tt> is for
 *  the notification callback function for GPT Channel MTU3 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU3()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU3(void);

#endif	/* GPT_CHANNEL_MTU3 */

#ifdef	GPT_CHANNEL_MTU4
/** @brief	Channel MTU4 Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU4()</tt> is for
 *  the notification callback function for GPT Channel MTU4 and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU4()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU4(void);

#endif	/* GPT_CHANNEL_MTU4 */

#ifdef	GPT_CHANNEL_MTU5U
/** @brief	Channel MTU5U Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU5U()</tt> is for
 *  the notification callback function for GPT Channel MTU5U and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU5U()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU5U(void);

#endif	/* GPT_CHANNEL_MTU5U */

#ifdef	GPT_CHANNEL_MTU5V
/** @brief	Channel MTU5V Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU5V()</tt> is for
 *  the notification callback function for GPT Channel MTU5V and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU5V()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU5V(void);

#endif	/* GPT_CHANNEL_MTU5V */

#ifdef	GPT_CHANNEL_MTU5W
/** @brief	Channel MTU5W Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_MTU5W()</tt> is for
 *  the notification callback function for GPT Channel MTU5W and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_MTU5W()</tt> shall be
 *  			configurable as pointers to user defined functions
 *  			within the configuration structure.
 *
 *  <b>GPT209</b>:	Each channel shall provide its own notification if
 *  			configured. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT093</b>:	When disabled, the GPT Driver will send no
 *  			notifications.
 *
 *  <b>GPT233</b>:	The GPT Driver shall invoke a notification callback
 *  			whenever the defined target time of the channel is
 *  			reached. (<tt>BSW12067</tt>, <tt>BSW12120</tt>)
 *
 *  <b>GPT206</b>:	The ISR's, providing the GPT events, shall be
 *  			responsible for resetting  the interrupt flags (if
 *  			needed by hardware) and calling the according
 *  			notification function.
 *
 *  <b>GPT362</b>:	For all available channels, callback functions have to
 *  			be declared by the configuration tool.
 */
void Gpt_Notification_Channel_MTU5W(void);

#endif	/* GPT_CHANNEL_MTU5W */

#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON


/** @brief	Default Configuration
 *
 *  Identifier for Default GPT Driver Configuration.
 */
#define	GPT_CONFIG_DEFAULT	0x00000000

/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default GPT Driver Configuration
 */
#define	GPT_CONFIG_DEFAULT_PTR	&Gpt_Config[GPT_CONFIG_DEFAULT]



#endif	/* GPT_CFG_H */
