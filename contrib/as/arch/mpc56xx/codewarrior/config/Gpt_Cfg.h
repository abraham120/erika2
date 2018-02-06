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

/** @file	Gpt_Cfg.h
 *  @brief	fake-druid AUTOSAR-"like" GPT Driver Configuration Header File.
 *
 *  <b>GPT369</b>:	<tt>Gpt_Cfg.h</tt> Module configuration file, if
 *  			pre-compile defines are used (<tt>BSW00345</tt>,
 *  			<tt>BSW00381</tt>, <tt>BSW412</tt>)
 *
 *  Configured for (GPT): MPC5643L Leopard
 *
 *  @author	Francesco Esposito
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

//#include "Mcu.h"

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
#define	GPT_DEINIT_API				STD_OFF

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
 * Channel Hardware Macros
 */

/** @brief	Channel Reserved Hardware Configuration
 *
 *  Reserved Timer configuration.
 */
#define	GPT_CH_HW_CFG_RESERVED	0x00000000

/** @brief	Channel Joined Hardware Configuration
 *
 *  For a 16/32-bit timer, this value selects the 32-bit timer configuration.
 *
 *  For a 32/64-bit wide timer, this value selects the 64-bit timer
 *  configuration.
 */
#define	GPT_CH_HW_CFG_JOIN	0x00000000

/** @brief	Channel RTC Hardware Configuration
 *
 *  For a 16/32-bit timer, this value selects the 32-bit real-time clock (RTC)
 *  counter configuration.
 *
 *  For a 32/64-bit wide timer, this value selects the 64-bit real-time clock
 * (RTC) counter configuration.
 */
#define	GPT_CH_HW_CFG_RTC	0x00000001

/** @brief	Channel Splitted Hardware Configuration
 *
 *  For a 16/32-bit timer, this value selects the 16-bit timer configuration.
 *
 *  For a 32/64-bit wide timer, this value selects the 32-bit timer
 *  configuration.
 *
 *  @note	The function is controlled by Channel Hardware Mode.
 */
#define	GPT_CH_HW_CFG_SPLIT	0x00000004

/** @brief	Channel Reserved Hardware Mode
 *
 *  Reserved Timer mode
 */
#define	GPT_CH_HW_MODE_RESERVED		0x00000000

/** @brief	Channel One-Shot Hardware Mode
 *
 *  One-Shot Timer mode
 */
#define	GPT_CH_HW_MODE_ONE_SHOT		0x00000001

/** @brief	Channel Periodic Hardware Mode
 *
 *  Periodic Timer mode
 */
#define	GPT_CH_HW_MODE_PERIODIC		0x00000002

/** @brief	Channel Capture Hardware Mode
 *
 *  Capture mode
 */
#define	GPT_CH_HW_MODE_CAPTURE		0x00000003

/** @brief	Channel Hardware Mode Mask
 *
 *  Timer Mode Mask
 */
#define	GPT_CH_HW_MODE_M		0x00000003

/** @brief	Channel Capture Edge-Time Hardware Mode
 *
 *  - <tt>1</tt>:	Edge-Time mode
 *  - <tt>0</tt>:	Edge-Count mode
 */
#define	GPT_CH_HW_MODE_TIME		0x00000004

/** @brief	Channel Alternate Hardware Mode
 *
 *  - <tt>1</tt>:	PWM mode is enabled.
 *  - <tt>0</tt>:	Capture mode is enabled.
 *
 *  @note	To enable PWM mode, you must also clear the
 *  		<tt>GPT_CH_HW_MODE_TIME</tt> bit and configure
 *  		<tt>GPT_CH_HW_MODE_ONE_SHOT</tt> or
 *  		<tt>GPT_CH_HW_MODE_PERIODIC</tt> mode.
 */
#define	GPT_CH_HW_MODE_ALTERNATE	0x00000008

/** @brief	Channel Up Hardware Mode
 *
 *  - <tt>0</tt>:	The timer counts down.
 *  - <tt>1</tt>:	The timer counts up.
 *
 *  @note	When counting up, the timer starts from a value of 0x0.
 *
 *  @note	When in PWM or RTC mode, the status of this bit is ignored.
 *  		PWM mode always counts down and RTC mode always counts up.
 */
#define	GPT_CH_HW_MODE_UP		0x00000010

/** @brief	Channel Match Interrupt Enable Hardware Mode
 *
 *  - <tt>1</tt>:	An interrupt is generated when the match value in the
 *  			GPTMTnMATCHR register is reached in the one-shot and
 *  			periodic modes.
 *  - <tt>0</tt>:	The match interrupt is disabled.
 */
#define	GPT_CH_HW_MODE_MATCH_IE		0x00000020

/** @brief	Channel Wait-on-Trigger Hardware Mode
 *
 *  - <tt>1</tt>:	If Timer is enabled, Timer does not begin counting until
 *  			it receives a trigger from the timer in the previous
 *  			position in the daisy chain. This function is valid for
 *  			one-shot, periodic, and PWM modes.
 *  - <tt>0</tt>:	Timer A begins counting as soon as it is enabled.
 *
 *  @note	This bit must be clear for GP Timer Module 0, Timer A.
 */
#define	GPT_CH_HW_MODE_WOT		0x00000040

/** @brief	Channel Snap-Shot Hardware Mode
 *
 *  - <tt>1</tt>:	If Timer is configured in the periodic mode, the actual
 *  			free-running value of Timer is loaded at the time-out
 *  			event into the Timer register. If the timer prescaler is
 *  			used, the Prescaler Snapshot is loaded into the
 *  			Prescaler register.
 *  - <tt>0</tt>:	Snap-shot mode is disabled.
 */
#define	GPT_CH_HW_MODE_SNAP_SHOT	0x00000080

/** @brief	Channel Interval Load Write Hardware Mode
 *
 *  - <tt>1</tt>:	Update the Timer register with the value in the Interval
 *  			Load register on the next timeout. If the prescaler is
 *  			used, update the Prescaler Snapshot register with the
 *  			value in the Prescaler register on the next timeout.
 *  - <tt>0</tt>:	Update the Timer register with the value in the Interval
 *  			Load register on the next cycle. If the prescaler is
 *  			used, update the Prescaler Snapshot register with the
 *  			value in the Prescaler register on the next cycle.
 */
#define	GPT_CH_HW_MODE_ILD		0x00000100

/** @brief	Channel PWM Interrupt Enable Hardware Mode
 *
 *  This bit enables interrupts in PWM mode on rising, falling, or both edges
 *  of the CCP output, as defined by the Event field in the Control register.
 *
 *  - <tt>1</tt>:	Interrupt is enabled.
 *  - <tt>0</tt>:	Interrupt is disabled.
 *
 *  @note	This bit is only valid in PWM mode.
 */
#define	GPT_CH_HW_MODE_PWM_IE		0x00000200

/** @brief	Channel Match Register Update Hardware Mode
 *
 *  - <tt>1</tt>:	Update the Match register and the Prescaler register,
 *  			if used, on the next timeout.
 *  - <tt>0</tt>:	Update the Match register and the Prescaler register,
 *  			if used, on the next cycle.
 *
 *  @note	If the timer is disabled when this bit is set, Match and
 *  		Prescaler registers are updated when the timer is enabled.
 *
 * @note	If the timer is stalled, Match and Prescaler registers are
 *  		updated according to the configuration of this bit.
 */
#define	GPT_CH_HW_MODE_MATCH_REG_UPDATE	0x00000400

/** @brief	Channel PWM Legacy Operation Hardware Mode
 *
 *  - <tt>1</tt>:	CCP is set to 1 on timeout.
 *  - <tt>0</tt>:	Legacy operation with CCP pin cleared to 0 on timeout.
 *
 *  @note	This bit is only valid in PWM mode.
 */
#define	GPT_CH_HW_MODE_PWM_LEGACY	0x00000800

/** @brief	Channel Reserved Hardware Control
 *
 *  Reserved Hardware control
 */
#define	GPT_CH_HW_CTL_RESERVED		0x00000000

/** @brief	Channel Timer Enable Hardware Control
 *
 *  - <tt>1</tt>:	Timer is enabled and begins counting or the capture
 *  			logic is enabled based on the Configuration register.
 *  - <tt>0</tt>:	Timer is disabled.
 */
#define	GPT_CH_HW_CTL_ENABLE		0x00000001

/** @brief	Channel Timer Stall Enable Hardware Control
 *
 *  - <tt>1</tt>:	Timer freezes counting while the processor is halted by
 *  			the debugger.
 *  - <tt>0</tt>:	Timer continues counting while the processor is halted
 *  			by the debugger.
 *
 *  @note	If the processor is executing normally, the bit is ignored.
 */
#define	GPT_CH_HW_CTL_STALL		0x00000002

/** @brief	Channel Timer Event Positive Edge Hardware Control.
 */
#define	GPT_CH_HW_CTL_EVENT_POS		0x00000000

/** @brief	Channel Timer Event Negative Edge Hardware Control.
 */
#define	GPT_CH_HW_CTL_EVENT_NEG		0x00000004

/** @brief	Channel Timer Event Both Edges Hardware Control.
 */
#define	GPT_CH_HW_CTL_EVENT_BOTH	0x0000000C

/** @brief	Channel Timer Event Mask Hardware Control.
 */
#define	GPT_CH_HW_CTL_EVENT_M		0x0000000C

/** @brief	Channel RTC Stall Enable Hardware Control
 *
 *  - <tt>1</tt>:	RTC counting continues while the processor is halted by
 *  			the debugger.
 *  - <tt>0</tt>:	RTC counting freezes while the processor is halted by
 *  			the debugger.
 *
 *  @note	If this bit is set, it prevents the timer from stalling in
 *  		all operating modes, even if other stall bits are set
 */
#define	GPT_CH_HW_CTL_RTC_STALL		0x00000010

/** @brief	Channel Timer Output Trigger Enable Hardawre Control
 *
 *  - <tt>1</tt>:	The output Timer A ADC trigger is enabled.
 *  - <tt>0</tt>:	The output Timer A ADC trigger is disabled.
 *
 * In addition, the ADC must be enabled and the timer selected as a trigger
 * source.
 */
#define	GPT_CH_HW_CTL_OUTPUT_TRIGGER	0x00000020

/** @brief	Channel Timer PWM Output Level Hardware Control
 *
 *  - <tt>1</tt>:	Output is inverted.
 *  - <tt>0</tt>:	Output is unaffected.
 */
#define	GPT_CH_HW_CTL_PWM_OUTPUT_LEVEL	0x00000040

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
   *   31:3	Reserved
   *    2:0	Configuration
   */
  /* uint32		GptChannelHWConfig; */

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

  /** @brief	Channel Comparator
   *
   *  Specifies the timer match value
   */
  uint32		GptCompare;

} Gpt_ChannelConfigType;

/*
 * The configuration process for Gpt module shall provide symbolic names for
 * each configured GPT channel.
 */ 
#define	GPT_CHANNEL_0_STM		0x00	/**< Channel 0 STM */
#define	GPT_CHANNEL_0_PIT		0x00	/**< Channel 0 PIT */
#define	GPT_CHANNEL_1_STM		0x01	/**< Channel 1 STM */
#define	GPT_CHANNEL_1_PIT		0x01	/**< Channel 1 PIT */
#define	GPT_CHANNEL_2_STM		0x02	/**< Channel 2 STM */
#define	GPT_CHANNEL_2 PIT		0x02	/**< Channel 2 PIT */
#define	GPT_CHANNEL_3_STM		0x03	/**< Channel 3 STM */
#define	GPT_CHANNEL_3_PIT		0x03	/**< Channel 3 PIT */

/*
 * Other GPT capabilities
 */
#define FREEZE_ON			0x1U
#define FREEZE_OFF			0x0U

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )

#define NOTIFICATION_ENABLED		0x1U
#define NOTIFICATION_DISABLED		0x0U

/*
 * The configuration process for Gpt module shall provide function prototypes
 * for notification callback functions for each configured GPT channel.
 */

/** @brief	Channel 0 A Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_0_STM()</tt> is for
 *  the notification callback function for GPT Channel 0 A and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_0_STM()</tt> shall be
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
void Gpt_Notification_Channel_0_STM(
  void
);

/** @brief	Channel 0 B Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_0_B()</tt> is for
 *  the notification callback function for GPT Channel 0 B and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_0_B()</tt> shall be
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
void Gpt_Notification_Channel_0_PIT(
  void
);

/** @brief	Channel 1 A Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_1_A()</tt> is for
 *  the notification callback function for GPT Channel 1 A and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_1_A()</tt> shall be
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
void Gpt_Notification_Channel_1_STM(
  void
);

/** @brief	Channel 1 B Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_1_B()</tt> is for
 *  the notification callback function for GPT Channel 1 B and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_1_B()</tt> shall be
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
void Gpt_Notification_Channel_1_PIT(
  void
);

/** @brief	Channel 2 A Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_2_A()</tt> is for
 *  the notification callback function for GPT Channel 2 A and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_2_A()</tt> shall be
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
void Gpt_Notification_Channel_2_STM(
  void
);

/** @brief	Channel 2 B Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_2_B()</tt> is for
 *  the notification callback function for GPT Channel 2 B and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_2_B()</tt> shall be
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
void Gpt_Notification_Channel_2_PIT(
  void
);

/** @brief	Channel 3 A Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_3_A()</tt> is for
 *  the notification callback function for GPT Channel 3 A and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_3_A()</tt> shall be
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
void Gpt_Notification_Channel_3_STM(
  void
);

/** @brief	Channel 3 B Notification Callback
 *
 *  The notification prototype <tt>Gpt_Notification_Channel_3_B()</tt> is for
 *  the notification callback function for GPT Channel 3 B and shall be
 *  implemented by the user.
 *
 *  The GPT module's environment shall declare a separate notification for each
 *  channel to avoid parameters in notification services and to improve run time
 *  efficiency. (<tt>BSW00375</tt>, <tt>BSW12069</tt>)
 *
 *  <b>GPT086</b>:	The callback notifications
 *  			<tt>Gpt_Notification_Channel_3_B()</tt> shall be
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
void Gpt_Notification_Channel_3_PIT(
  void
);
#endif	/* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

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

  /** @brief	Timer freeze flag
   *
   */
  uint8			freeze;

  /** @brief	Timer Initial value
   *
   */
  uint32		InitVal;

   /** @brief	Prescaler Initial value
   *
   */
  uint32		Prsc;

} Gpt_ConfigType;

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
