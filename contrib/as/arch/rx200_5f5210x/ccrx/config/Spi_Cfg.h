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

/** @file	Spi_Cfg.h
 *  @brief	fake-druid AUTOSAR SPI Handler/Driver Configuration Header File.
 *
 *  <b>SPI103_Conf</b>:	Configuration of the Spi (Serial Peripheral Interface)
 *  			module.
 *
 *  Configured for Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2013
 */


#if !(\
 ((SPI_SW_MAJOR_VERSION == 1) && \
  (SPI_SW_MINOR_VERSION == 0) && \
  (SPI_SW_PATCH_VERSION == 0))\
)
#error Spi: Configuration file expected BSW module version to be 1.0.0.*
#endif

#ifndef	SPI_CFG_H
#define	SPI_CFG_H

/*
 * Spi
 *
 * SPI103_Conf: Configuration of the Spi (Serial Peripheral Interface) module.
 */

/*
 * SpiGeneral
 *
 * SPI225_Conf:	General configuration settings for SPI-Handler
 */

/** @brief	<tt>SpiCancelApi</tt>
 *
 *  <b>SPI226_Conf</b>:	Switches the <tt>Spi_Cancel()</tt> function ON or OFF.
 *
 *  <b>SPI146</b>:	The function <tt>Spi_Cancel()</tt> is pre-compile time
 *  			configurable On / Off by the configuration parameter
 *  			<tt>SpiCancelApi</tt>.
 */
#ifdef	__AS_CFG_SPI_CANCEL_API__
#define	SPI_CANCEL_API			STD_ON
#else
#define	SPI_CANCEL_API			STD_OFF
#endif

/** @brief	<tt>SpiChannelBuffersAllowed</tt>
 *
 *  <b>SPI227_Conf</b>:	Selects the SPI Handler/Driver Channel Buffers usage
 *  			allowed and delivered.
 *
 *  <b>SPI111</b>:	The <tt>SpiChannelBuffersAllowed</tt> parameter shall be
 *  			configured with one of the 3 authorized values (0, 1 or
 *  			2) according to the described usage.
 *
 *  Channel buffering methods may be used depending on the 3 use cases described
 *  below:
 *   - Usage 0:	the SPI Handler/Driver manages only Internal Buffers.
 *   - Usage 1:	the SPI Handler/Driver manages only External Buffers.
 *   - Usage 2:	the SPI Handler/Driver manages both buffers types.
 *
 *  <b>SPI279</b>:	The <tt>SpiChannelBuffersAllowed</tt> parameter shall be
 *  			configured to select which Channel Buffers the SPI
 *  			Handler/Driver manages.
 *
 *  <b>SPI137</b>:	The function <tt>Spi_WriteIB()</tt> shall be pre-compile
 *  			time configurable by the parameter
 *  			<tt>SpiChannelBuffersAllowed</tt>.
 *  			This function is only relevant for Channels with IB.
 *
 *  <b>SPI138</b>:	The function <tt>Spi_ReadIB()</tt> is pre-compile time
 *  			configurable by the parameter
 *  			<tt>SpiChannelBuffersAllowed</tt>.
 *  			This function is only relevant for Channels with IB.
 *
 *  <b>SPI139</b>:	The function <tt>Spi_SetupEB()</tt> is pre-compile time
 *  			configurable by the parameter
 *  			<tt>SpiChannelBuffersAllowed</tt>.
 *  			This function is only relevant for Channels with EB.
 */
#if	( \
		defined(__AS_CFG_SPI_INTERNAL_BUFFERS__) && \
		defined(__AS_CFG_SPI_EXTERNAL_BUFFERS__) \
	)

#define	SPI_CHANNEL_BUFFERS_ALLOWED	2

#else	/*
	 * ( \
	 * 	defined(__AS_CFG_SPI_INTERNAL_BUFFERS__) && \
	 * 	defined(__AS_CFG_SPI_EXTERNAL_BUFFERS__) \
	 * )
	 */

#ifdef	__AS_CFG_SPI_INTERNAL_BUFFERS__

#define	SPI_CHANNEL_BUFFERS_ALLOWED	0

#else	/* __AS_CFG_SPI_INTERNAL_BUFFERS__ */

#ifdef	__AS_CFG_SPI_EXTERNAL_BUFFERS__
#define	SPI_CHANNEL_BUFFERS_ALLOWED	1
#else	/* __AS_CFG_SPI_EXTERNAL_BUFFERS__ */
#define	SPI_CHANNEL_BUFFERS_ALLOWED	2

#endif	/* !__AS_CFG_SPI_EXTERNAL_BUFFERS__ */

#endif	/* !__AS_CFG_SPI_INTERNAL_BUFFERS__ */

#endif	/* 
	 * !(
	 * 	defined(__AS_CFG_SPI_INTERNAL_BUFFERS__) &&
	 * 	defined(__AS_CFG_SPI_EXTERNAL_BUFFERS__)
	 * )
	 */

/** @brief	<tt>SpiDevErrorDetect</tt>
 *
 *  <b>SPI228_Conf</b>:	Switches the Development Error Detection and
 *  			Notification ON or OFF.
 *
 *  <b>SPI005</b>:	The detection of all development errors is configurable
 *  			at pre-compile time.
 *
 *  <b>SPI249</b>:	The detection of all development errors is configurable
 *  			as (ON/OFF) by the switch <tt>SpiDevErrorDetect</tt>.
 *
 *  <b>SPI250</b>:	The switch <tt>SpiDevErrorDetect</tt> shall activate or
 *  			deactivate the detection of all development errors.
 *
 *  <b>SPI029</b>:	If the switch <tt>SpiDevErrorDetect</tt> is enabled API
 *  			parameter checking is also enabled.
 *
 *  <b>SPI099</b>:	The detection of production code errors cannot be
 *  			switched off.
 *
 *  <b>SPI100</b>:	Detected development errors shall be reported to the
 *  			error hook of the Development Error Tracer (DET) if the
 *  			pre-processor switch <tt>SpiDevErrorDetect</tt> is set.
 */
#ifdef	__AS_CFG_SPI_DEV_ERROR_DETECT__
#define	SPI_DEV_ERROR_DETECT		STD_ON
#else
#define	SPI_DEV_ERROR_DETECT		STD_OFF
#endif

/** @brief	<tt>SpiHwStatusApi</tt>
 *
 *  <b>SPI230_Conf</b>:	Switches the <tt>Spi_GetHWUnitStatus()</tt> function ON
 *  			or OFF.
 *
 *  <b>SPI142</b>:	The function <tt>Spi_GetHWUnitStatus()</tt> is
 *  			pre-compile time configurable On/Off by the
 *  			configuration parameter <tt>SpiHwStatusApi</tt>.
 */
#ifdef	__AS_CFG_SPI_HW_STATUS_API__
#define	SPI_HW_STATUS_API		STD_OFF
#else
#define	SPI_HW_STATUS_API		STD_ON
#endif

/** @brief	<tt>SpiInterruptibleSeqAllowed</tt>
 *
 *  <b>SPI230_Conf</b>:	Switches the Interruptible Sequences handling
 *  			functionality ON or OFF.
 *
 *  This parameter depends on <tt>SpiLevelDelivered</tt> value.
 *  It is only used for <tt>SpiLevelDelivered</tt> configured to 1 or 2.
 *
 *  <b>SPI121</b>:	The SPI Handler/Driver’s environment shall configure the
 *  			<tt>SpiInterruptibleSeqAllowed</tt> parameter (ON / OFF)
 *  			in order to select which kind of Sequences the SPI
 *  			Handler/Driver manages.
 *
 *  - Non-Interruptible Sequences:	every Sequence transmission started is
 *  					not suspended by the Handler/Driver
 *  					until the end of transmission.
 *  - Mixed Sequences:			according to its configuration, a
 *  					Sequence transmission started may be
 *  					suspended by the Handler/Driver between
 *  					two of their consecutives Jobs.
 *
 *  <b>SPI122</b>:	Interruptible Sequences are not allowed within levels 1
 *  			and 2 of the SPI Handler/Driver when the
 *  			<tt>SpiInterruptibleSeqAllowed</tt> parameter is
 *  			switched off (i.e. configured with value “OFF”).
 *
 *  <b>SPI125</b>:	Interruptible Sequences are allowed within levels 1 and
 *  			2 of SPI Handler/Driver when the
 *  			<tt>SpiInterruptibleSeqAllowed</tt> parameter is
 *  			switched on (i.e. configured with value “ON”).
 */
#ifdef	__AS_CFG_SPI_INTERRUPTIBLE_SEQUENCES__
#define	SPI_INTERRUPTIBLE_SEQ_ALLOWED	STD_ON
#else
#define	SPI_INTERRUPTIBLE_SEQ_ALLOWED	STD_OFF
#endif

/** @brief	<tt>SpiLevelDelivered</tt>
 *
 *  <b>SPI231_Conf</b>:	Selects the SPI Handler/Driver level of scalable
 *  			functionality that is available and delivered.
 *
 *  <b>SPI109</b>:	The SPI Handler/Driver’s level of scalable
 *  			functionality shall always be statically configurable,
 *  			i.e. configured at pre-compile time to allow the best
 *  			source code optimisation.
 *
 *  <b>SPI110</b>:	The <tt>SpiLevelDelivered</tt> parameter shall be
 *  			configured with one of the 3 authorized values according
 *  			to the described levels (0, 1 or 2) to allow the
 *  			selection of the SPI Handler/Driver’s level of scalable
 *  			functionality.
 *
 *  - LEVEL 0, Simple Synchronous SPI Handler/Driver: the communication is
 *    based on synchronous handling with a FIFO policy to handle multiple
 *    accesses. Buffer usage is configurable to optimize and/or to take
 *    advantage of HW capabilities.
 *  - LEVEL 1, Basic Asynchronous SPI Handler/Driver: the communication is
 *    based on asynchronous behavior and with a Priority policy to handle
 *    multiple accesses. Buffer usage is configurable as for
 *    "Simple Synchronous" level.
 *  - LEVEL 2, Enhanced (Synchronous/Asynchronous) SPI Handler/Driver: the
 *    communication is based on asynchronous behavior or synchronous handling,
 *    using either interrupts or polling mechanism selectable during execution
 *    time and with a Priority policy to handle multiple accesses. Buffer usage
 *    is configurable as for other levels.
 *
 *  <b>SPI150</b>:	The type <tt>Spi_AsyncModeType</tt> is made available
 *  			or not depending on the pre-compile time parameter:
 *  			<tt>SpiLevelDelivered</tt>. This is only relevant for
 *  			LEVEL 2.
 *
 *  <b>SPI133</b>:	The function <tt>Spi_AsyncTransmit</tt> is pre-compile
 *  			time selectable by the configuration parameter
 *  			<tt>SpiLevelDelivered</tt>. This function is only
 *  			relevant for LEVEL 1 and LEVEL 2.
 *
 *  <b>SPI136</b>:	The function <tt>Spi_SyncTransmit</tt> is pre-compile
 *  			time selectable by the configuration parameter
 *  			<tt>SpiLevelDelivered</tt>. This function is only
 *  			relevant for LEVEL 0 and LEVEL 2.
 *
 *  <b>SPI154</b>:	The function <tt>Spi_SetAsyncMode</tt> is pre-compile
 *  			time selectable by the configuration parameter
 *  			<tt>SpiLevelDelivered</tt>. This function is only
 *  			relevant for LEVEL 2.
 */
#if	( \
		defined(__AS_CFG_SPI_SYNCHRONOUS__) && \
		defined(__AS_CFG_SPI_ASYNCHRONOUS__) \
	)

#define	SPI_LEVEL_DELIVERED		2

#else	/*
	 * ( \
	 * 	defined(__AS_CFG_SPI_SYNCHRONOUS__) && \
	 * 	defined(__AS_CFG_SPI_ASYNCHRONOUS__) \
	 * )
	 */

#ifdef	__AS_CFG_SPI_SYNCHRONOUS__

#define	SPI_LEVEL_DELIVERED		0

#else	/* __AS_CFG_SPI_SYNCHRONOUS__ */

#ifdef	__AS_CFG_SPI_ASYNCHRONOUS__
#define	SPI_LEVEL_DELIVERED		1
#else	/* __AS_CFG_SPI_ASYNCHRONOUS__ */
#define	SPI_LEVEL_DELIVERED		2
#endif	/* !__AS_CFG_SPI_ASYNCHRONOUS__ */

#endif	/* !__AS_CFG_SPI_SYNCHRONOUS__ */

#endif	/*
	 * !(
	 * 	defined(__AS_CFG_SPI_SYNCHRONOUS__) &&
	 * 	defined(__AS_CFG_SPI_ASYNCHRONOUS__)
	 * )
	 */

/** @brief	<tt>SpiVersionInfoApi</tt>
 *
 *  <b>SPI232_Conf</b>:	Switches the <tt>Spi_GetVersionInfo()</tt> function ON
 *  			or OFF.
 *
 *  <b>SPI102</b>:	The function <tt>Spi_GetVersionInfo()</tt> is pre
 *  			compile time configurable by the configuration parameter
 *  			<tt>SpiVersionInfoApi</tt>.
 *
 *  <b>SPI278</b>:	The function <tt>Spi_GetVersionInfo()</tt> is pre
 *  			compile time configurable On/Off by the configuration
 *  			parameter <tt>SpiVersionInfoApi</tt>.
 */
#ifdef	__AS_CFG_SPI_VERSION_INFO_API__
#define	SPI_VERSION_INFO_API		STD_ON
#else
#define	SPI_VERSION_INFO_API		STD_OFF
#endif


#define	SPI_END_LIST	0xFFFFFFFFU	/**< End List Marker.	*/

/** @brief	SPI Channel End List Marker.	*/
#define	SPI_CHANNEL_END_LIST	(Spi_ChannelType)SPI_END_LIST
/** @brief	SPI Job End List Marker.	*/
#define	SPI_JOB_END_LIST	(Spi_JobType)SPI_END_LIST
/** @brief	SPI Sequence End List Marker.	*/
#define	SPI_SEQ_END_LIST	(Spi_SequenceType)SPI_END_LIST

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )

/** @brief	SPI Channel Buffer Type.
 *
 *  In order to allow taking advantages of all microcontroller capabilities but
 *  also to allow sending/receiving of data to/from a dedicated memory location,
 *  all levels have an optional feature with respect to the location of Channel
 *  Buffers.
 *
 *  Hence, two main kinds of channel buffering can be used by configuration:
 *  - Internally buffered Channels (IB): The buffer to transmit/receive data is
 *    provided by the Handler/Driver.
 *  - Externally buffered Channels (EB): The buffer to transmit/receive is
 *    provided by the user (statically and/or dynamically).
 *
 *  Behaviour of IB channels
 *
 *  The intention of Internal Buffer channels is to take advantage of
 *  microcontrollers including this feature by hardware. Otherwise, this feature
 *  should be simulated by software.
 *
 *  <b>SPI052</b>:	For the IB Channels, the Handler/Driver shall provide
 *  			the buffering but it is not able to take care of the
 *  			consistency of the data in the buffer during
 *  			transmission. The size of the Channel buffer is fixed.
 *
 *  <b>SPI049</b>:	The channel data received shall be stored in 1 entry
 *  			deep internal buffers by channel. The SPI Handler/Driver
 *  			shall not take care of the overwriting of these
 *  			"receive" buffers by another transmission on the same
 *  			channel.
 *
 *  <b>SPI051</b>:	The channel data to be transmitted shall be copied in 1
 *  			entry deep internal buffers by channel.
 *
 *  <b>SPI257</b>:	The SPI Handler/Driver is not able to prevent the
 *  			overwriting of these "transmit" buffers by users during
 *  			transmissions.
 *
 *  Behaviour of EB channels
 *
 *  The intention of External Buffer channels is to reuse existing buffers that
 *  are located outside. That means the SPI Handler/Driver does not monitor
 *  them.
 *
 *  <b>SPI053</b>:	For EB Channels the application shall provide the
 *  			buffering and shall take care of the consistency of the
 *  			data in the buffer during transmission.
 *
 *  <b>SPI112</b>:	The size of the Channel buffer is either fixed or
 *  			variable. A maximum size for the Channel buffer shall be
 *  			defined by the configuration.
 *
 *  <b>SPI280</b>:	The buffer provided by the application for the SPI
 *  			Handler Driver may have a different size.
 */
typedef enum {
	SPI_EB = 0,	/**< Externally Buffered Channel. */
	SPI_IB	/**< Internally Buffered Channel. */
}	Spi_ChannelBufferType;

#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	SPI Handler/Driver Data Type
 *
 *  <b>SPI355</b>:	<tt>Spi_DataType</tt> This defines the type of
 *  			application data buffer elements.
 *  			Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *  			it shall be provided for external use.
 *
 *  <b>SPI164</b>:	The type <tt>Spi_DataType</tt> refers to application
 *  			data buffer elements.
 *
 *  This is implementation specific but not all values may be valid within the
 *  type.
 *
 *  This type shall be chosen in order to have the most efficient implementation
 *  on a specific microcontroller platform.
 */
typedef uint8	Spi_DataType;

#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	SPI Synchronous Type.
 *
 *  If <tt>Spi_SynchronousType</tt> is <tt>SPI_SYNCHRONOUS</tt>, the SPI
 *  Handler/Driver is in a synchronous manner. If it is
 *  <tt>SPI_ASYNCHRONOUS</tt>, the SPI Handler/Driver is in asynchronous way. If
 *  it is <tt>DPI_SYNC_ASYNC</tt>, the SPI Handler/Driver can be either in
 *  synchronous and asynchronous way.
 */
typedef enum {
	SPI_SYNC_ASYNC_NONE = 0,	/**< No Synchronous and No Asynchronous way.*/
	SPI_SYNCHRONOUS		= 1,	/**< Synchronous way.			      		*/
	SPI_ASYNCHRONOUS	= 2,	/**< Asynchronous way.			      		*/
	SPI_SYNC_ASYNC		= 3		/**< Synchronous and Asynchronous way.		*/
}	Spi_SynchronousType;
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	SPI Transfer Start Type.
 *
 *  First starting bit for transfer.
 */
typedef enum
{
  SPI_LSB = 0,	/**< Transfer starts with the Least Significant Bit first. */
  SPI_MSB	/**< Transfer starts with the Most  Significant Bit first. */
}	Spi_TransferType;


/*
 * Configured Spi Channels IDs.
 */


/*
 * The configuration process for Spi module shall provide symbolic names for
 * each configured channel.
 */ 
#define	SPI_CHANNEL_0	0x00U	/**< Channel 0 	*/
#define	SPI_CHANNEL_1	0x01U	/**< Channel 1 	*/
#define	SPI_CHANNEL_2	0x02U	/**< Channel 2 	*/
#define	SPI_CHANNEL_3	0x03U	/**< Channel 3	*/
#define	SPI_CHANNEL_4	0x04U	/**< Channel 4 	*/
#define	SPI_CHANNEL_5	0x05U	/**< Channel 5  */
#define	SPI_CHANNEL_6	0x06U	/**< Channel 6 */


/*
 * TEST Chennels.
 */
#define	SPI_TEST_CHANNEL_0	SPI_CHANNEL_0	/**< Test Channel 0. */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#define	SPI_TEST_CHANNEL_0_EB	SPI_CHANNEL_1	/**< Test Channel 0 External Buffer. */
#endif

/** @brief	Test Channel 0 Default Data. */
#define	SPI_TEST_CHANNEL_0_DEFAULT_DATA	0xA5U

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/** @brief	Test Channel 0 EB Max Length */
#define	SPI_TEST_CHANNEL_0_EB_MAX_LENGTH	0x0001U
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/** @brief	Test Channel 0 IB N Buffers */
#define	SPI_TEST_CHANNEL_0_IB_N_BUFFERS	0x0001U
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	Configured SPI TEST Channels. */
#define	SPI_TEST_CHANNELS_NUMBER	SPI_TEST_CHANNEL_0_EB + 1
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
/** @brief	Configured SPI TEST Channels. */
#define	SPI_TEST_CHANNELS_NUMBER	SPI_TEST_CHANNEL_0 + 1
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/* NOTE: 8-bit SPI Channel Data Width. */
#if	0
/** @brief	Test Channels Data Width. */
#define	SPI_TEST_CHANNELS_DATA_WIDTH	0x08U
#endif

#ifdef	__AS_CFG_SPI_LBM__

/*
 * Loop-Back Mode Channels.
 */
#define	SPI_LBM_CHANNEL_0	0x00U	/**< Loop-back Mode Channel 0. */
#define	SPI_LBM_CHANNEL_1	0x01U	/**< Loop-back Mode Channel 1. */
#define	SPI_LBM_CHANNEL_2	0x02U	/**< Loop-back Mode Channel 2. */
#define	SPI_LBM_CHANNEL_3	0x03U	/**< Loop-back Mode Channel 3. */
#define	SPI_LBM_CHANNEL_4	0x04U	/**< Loop-back Mode Channel 4. */
#define	SPI_LBM_CHANNEL_5	0x05U	/**< Loop-back Mode Channel 5. */
#define	SPI_LBM_CHANNEL_6	0x06U	/**< Loop-back Mode Channel 6. */
#define	SPI_LBM_CHANNEL_7	0x07U	/**< Loop-back Mode Channel 7. */
#define	SPI_LBM_CHANNEL_8	0x08U	/**< Loop-back Mode Channel 8. */
#define	SPI_LBM_CHANNEL_9	0x09U	/**< Loop-back Mode Channel 9. */
#define	SPI_LBM_CHANNEL_10	0x0AU	/**< Loop-back Mode Channel 10. */
#define	SPI_LBM_CHANNEL_11	0x0BU	/**< Loop-back Mode Channel 11. */
#define	SPI_LBM_CHANNEL_12	0x0CU	/**< Loop-back Mode Channel 12. */
#define	SPI_LBM_CHANNEL_13	0x0DU	/**< Loop-back Mode Channel 13. */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#define	SPI_LBM_CHANNEL_0_EB	0x0EU	/**< Loop-back Mode Channel 0 EB. */
#define	SPI_LBM_CHANNEL_1_EB	0x0FU	/**< Loop-back Mode Channel 1 EB. */
#define	SPI_LBM_CHANNEL_2_EB	0x10U	/**< Loop-back Mode Channel 2 EB. */
#define	SPI_LBM_CHANNEL_3_EB	0x11U	/**< Loop-back Mode Channel 3 EB. */
#define	SPI_LBM_CHANNEL_4_EB	0x12U	/**< Loop-back Mode Channel 4 EB. */
#define	SPI_LBM_CHANNEL_5_EB	0x13U	/**< Loop-back Mode Channel 5 EB. */
#define	SPI_LBM_CHANNEL_6_EB	0x14U	/**< Loop-back Mode Channel 6 EB. */
#define	SPI_LBM_CHANNEL_7_EB	0x15U	/**< Loop-back Mode Channel 7 EB. */
#define	SPI_LBM_CHANNEL_8_EB	0x16U	/**< Loop-back Mode Channel 8 EB. */
#define	SPI_LBM_CHANNEL_9_EB	0x17U	/**< Loop-back Mode Channel 9 EB. */
#define	SPI_LBM_CHANNEL_10_EB	0x18U	/**< Loop-back Mode Channel 10 EB. */
#define	SPI_LBM_CHANNEL_11_EB	0x19U	/**< Loop-back Mode Channel 11 EB. */
#define	SPI_LBM_CHANNEL_12_EB	0x1AU	/**< Loop-back Mode Channel 12 EB. */
#define	SPI_LBM_CHANNEL_13_EB	0x1BU	/**< Loop-back Mode Channel 13 EB. */
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	Loop-back Mode Channel 0 Default Data. */
#define	SPI_LBM_CHANNEL_0_DEFAULT_DATA	SPI_LBM_CHANNEL_0
/** @brief	Loop-back Mode Channel 1 Default Data. */
#define	SPI_LBM_CHANNEL_1_DEFAULT_DATA	SPI_LBM_CHANNEL_1
/** @brief	Loop-back Mode Channel 2 Default Data. */
#define	SPI_LBM_CHANNEL_2_DEFAULT_DATA	SPI_LBM_CHANNEL_2
/** @brief	Loop-back Mode Channel 3 Default Data. */
#define	SPI_LBM_CHANNEL_3_DEFAULT_DATA	SPI_LBM_CHANNEL_3
/** @brief	Loop-back Mode Channel 4 Default Data. */
#define	SPI_LBM_CHANNEL_4_DEFAULT_DATA	SPI_LBM_CHANNEL_4
/** @brief	Loop-back Mode Channel 5 Default Data. */
#define	SPI_LBM_CHANNEL_5_DEFAULT_DATA	SPI_LBM_CHANNEL_5
/** @brief	Loop-back Mode Channel 6 Default Data. */
#define	SPI_LBM_CHANNEL_6_DEFAULT_DATA	SPI_LBM_CHANNEL_6
/** @brief	Loop-back Mode Channel 7 Default Data. */
#define	SPI_LBM_CHANNEL_7_DEFAULT_DATA	SPI_LBM_CHANNEL_7
/** @brief	Loop-back Mode Channel 8 Default Data. */
#define	SPI_LBM_CHANNEL_8_DEFAULT_DATA	SPI_LBM_CHANNEL_8
/** @brief	Loop-back Mode Channel 9 Default Data. */
#define	SPI_LBM_CHANNEL_9_DEFAULT_DATA	SPI_LBM_CHANNEL_9
/** @brief	Loop-back Mode Channel 10 Default Data. */
#define	SPI_LBM_CHANNEL_10_DEFAULT_DATA	SPI_LBM_CHANNEL_10
/** @brief	Loop-back Mode Channel 11 Default Data. */
#define	SPI_LBM_CHANNEL_11_DEFAULT_DATA	SPI_LBM_CHANNEL_11
/** @brief	Loop-back Mode Channel 12 Default Data. */
#define	SPI_LBM_CHANNEL_12_DEFAULT_DATA	SPI_LBM_CHANNEL_12
/** @brief	Loop-back Mode Channel 13 Default Data. */
#define	SPI_LBM_CHANNEL_13_DEFAULT_DATA	SPI_LBM_CHANNEL_13

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/** @brief	Loop-back Mode Channel 0 EB Max Length */
#define	SPI_LBM_CHANNEL_0_EB_MAX_LENGTH		SPI_LBM_CHANNEL_0 + 1
/** @brief	Loop-back Mode Channel 1 EB Max Length */
#define	SPI_LBM_CHANNEL_1_EB_MAX_LENGTH		SPI_LBM_CHANNEL_1 + 1
/** @brief	Loop-back Mode Channel 2 EB Max Length */
#define	SPI_LBM_CHANNEL_2_EB_MAX_LENGTH		SPI_LBM_CHANNEL_2 + 1
/** @brief	Loop-back Mode Channel 3 EB Max Length */
#define	SPI_LBM_CHANNEL_3_EB_MAX_LENGTH		SPI_LBM_CHANNEL_3 + 1
/** @brief	Loop-back Mode Channel 4 EB Max Length */
#define	SPI_LBM_CHANNEL_4_EB_MAX_LENGTH		SPI_LBM_CHANNEL_4 + 1
/** @brief	Loop-back Mode Channel 5 EB Max Length */
#define	SPI_LBM_CHANNEL_5_EB_MAX_LENGTH		SPI_LBM_CHANNEL_5 + 1
/** @brief	Loop-back Mode Channel 6 EB Max Length */
#define	SPI_LBM_CHANNEL_6_EB_MAX_LENGTH		SPI_LBM_CHANNEL_6 + 1
/** @brief	Loop-back Mode Channel 7 EB Max Length */
#define	SPI_LBM_CHANNEL_7_EB_MAX_LENGTH		SPI_LBM_CHANNEL_7 + 1
/** @brief	Loop-back Mode Channel 8 EB Max Length */
#define	SPI_LBM_CHANNEL_8_EB_MAX_LENGTH		SPI_LBM_CHANNEL_8 + 1
/** @brief	Loop-back Mode Channel 9 EB Max Length */
#define	SPI_LBM_CHANNEL_9_EB_MAX_LENGTH		SPI_LBM_CHANNEL_9 + 1
/** @brief	Loop-back Mode Channel 10 EB Max Length */
#define	SPI_LBM_CHANNEL_10_EB_MAX_LENGTH	SPI_LBM_CHANNEL_10 + 1
/** @brief	Loop-back Mode Channel 11 EB Max Length */
#define	SPI_LBM_CHANNEL_11_EB_MAX_LENGTH	SPI_LBM_CHANNEL_11 + 1
/** @brief	Loop-back Mode Channel 12 EB Max Length */
#define	SPI_LBM_CHANNEL_12_EB_MAX_LENGTH	SPI_LBM_CHANNEL_12 + 1
/** @brief	Loop-back Mode Channel 13 EB Max Length */
#define	SPI_LBM_CHANNEL_13_EB_MAX_LENGTH	SPI_LBM_CHANNEL_13 + 1
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/** @brief	Loop-back Mode Channel 0 IB N Buffers */
#define	SPI_LBM_CHANNEL_0_IB_N_BUFFERS	SPI_LBM_CHANNEL_0 + 1
/** @brief	Loop-back Mode Channel 1 IB N Buffers */
#define	SPI_LBM_CHANNEL_1_IB_N_BUFFERS	SPI_LBM_CHANNEL_1 + 1
/** @brief	Loop-back Mode Channel 2 IB N Buffers */
#define	SPI_LBM_CHANNEL_2_IB_N_BUFFERS	SPI_LBM_CHANNEL_2 + 1
/** @brief	Loop-back Mode Channel 3 IB N Buffers */
#define	SPI_LBM_CHANNEL_3_IB_N_BUFFERS	SPI_LBM_CHANNEL_3 + 1
/** @brief	Loop-back Mode Channel 4 IB N Buffers */
#define	SPI_LBM_CHANNEL_4_IB_N_BUFFERS	SPI_LBM_CHANNEL_4 + 1
/** @brief	Loop-back Mode Channel 5 IB N Buffers */
#define	SPI_LBM_CHANNEL_5_IB_N_BUFFERS	SPI_LBM_CHANNEL_5 + 1
/** @brief	Loop-back Mode Channel 6 IB N Buffers */
#define	SPI_LBM_CHANNEL_6_IB_N_BUFFERS	SPI_LBM_CHANNEL_6 + 1
/** @brief	Loop-back Mode Channel 7 IB N Buffers */
#define	SPI_LBM_CHANNEL_7_IB_N_BUFFERS	SPI_LBM_CHANNEL_7 + 1
/** @brief	Loop-back Mode Channel 8 IB N Buffers */
#define	SPI_LBM_CHANNEL_8_IB_N_BUFFERS	SPI_LBM_CHANNEL_8 + 1
/** @brief	Loop-back Mode Channel 9 IB N Buffers */
#define	SPI_LBM_CHANNEL_9_IB_N_BUFFERS	SPI_LBM_CHANNEL_9 + 1
/** @brief	Loop-back Mode Channel 10 IB N Buffers */
#define	SPI_LBM_CHANNEL_10_IB_N_BUFFERS	SPI_LBM_CHANNEL_10 + 1
/** @brief	Loop-back Mode Channel 11 IB N Buffers */
#define	SPI_LBM_CHANNEL_11_IB_N_BUFFERS	SPI_LBM_CHANNEL_11 + 1
/** @brief	Loop-back Mode Channel 12 IB N Buffers */
#define	SPI_LBM_CHANNEL_12_IB_N_BUFFERS	SPI_LBM_CHANNEL_12 + 1
/** @brief	Loop-back Mode Channel 13 IB N Buffers */
#define	SPI_LBM_CHANNEL_13_IB_N_BUFFERS	SPI_LBM_CHANNEL_13 + 1
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	Configured SPI LBM Channels. */
#define	SPI_LBM_CHANNELS_NUMBER	SPI_LBM_CHANNEL_13_EB + 1
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
/** @brief	Configured SPI LBM Channels. */
#define	SPI_LBM_CHANNELS_NUMBER	SPI_LBM_CHANNEL_13 + 1
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/* NOTE: 8-bit SPI Channel Data Width. */
#if	0
/** @brief	Loop-Back Mode Channels Data Width. */
#define	SPI_LBM_CHANNELS_DATA_WIDTH	0x08U
#endif

#endif	/* __AS_CFG_SPI_LBM__ */


#ifdef	__AS_CFG_SPI_LBM__

/** @brief	Maximum Number of Configured SPI Channels. */
#define	SPI_CHANNELS_MAX_NUMBER	SPI_LBM_CHANNELS_NUMBER

#else	/* __AS_CFG_SPI_LBM__ */

/** @brief	Maximum Number of Configured SPI Channels. */
#define	SPI_CHANNELS_MAX_NUMBER	SPI_TEST_CHANNELS_NUMBER

#endif	/* !__AS_CFG_SPI_LBM__ */

/*
 * Channel Internal Buffers.
 */
#ifdef	__AS_CFG_SPI_LBM__
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/** @brief	SPI Channel 0 Max IB N Buffers */
#define	SPI_CHANNEL_0_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_0_IB_N_BUFFERS
/** @brief	SPI Channel 1 Max IB N Buffers */
#define	SPI_CHANNEL_1_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_1_IB_N_BUFFERS
/** @brief	SPI Channel 2 Max IB N Buffers */
#define	SPI_CHANNEL_2_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_2_IB_N_BUFFERS
/** @brief	SPI Channel 3 Max IB N Buffers */
#define	SPI_CHANNEL_3_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_3_IB_N_BUFFERS
/** @brief	SPI Channel 4 Max IB N Buffers */
#define	SPI_CHANNEL_4_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_4_IB_N_BUFFERS
/** @brief	SPI Channel 5 Max IB N Buffers */
#define	SPI_CHANNEL_5_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_5_IB_N_BUFFERS
/** @brief	SPI Channel 6 Max IB N Buffers */
#define	SPI_CHANNEL_6_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_6_IB_N_BUFFERS
/** @brief	SPI Channel 7 Max IB N Buffers */
#define	SPI_CHANNEL_7_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_7_IB_N_BUFFERS
/** @brief	SPI Channel 8 Max IB N Buffers */
#define	SPI_CHANNEL_8_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_8_IB_N_BUFFERS
/** @brief	SPI Channel 9 Max IB N Buffers */
#define	SPI_CHANNEL_9_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_9_IB_N_BUFFERS
/** @brief	SPI Channel 10 Max IB N Buffers */
#define	SPI_CHANNEL_10_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_10_IB_N_BUFFERS
/** @brief	SPI Channel 11 Max IB N Buffers */
#define	SPI_CHANNEL_11_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_11_IB_N_BUFFERS
/** @brief	SPI Channel 12 Max IB N Buffers */
#define	SPI_CHANNEL_12_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_12_IB_N_BUFFERS
/** @brief	SPI Channel 13 Max IB N Buffers */
#define	SPI_CHANNEL_13_MAX_IB_N_BUFFERS	SPI_LBM_CHANNEL_13_IB_N_BUFFERS
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	SPI Channel 14 Max IB N Buffers */
#define	SPI_CHANNEL_14_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 15 Max IB N Buffers */
#define	SPI_CHANNEL_15_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 16 Max IB N Buffers */
#define	SPI_CHANNEL_16_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 17 Max IB N Buffers */
#define	SPI_CHANNEL_17_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 18 Max IB N Buffers */
#define	SPI_CHANNEL_18_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 19 Max IB N Buffers */
#define	SPI_CHANNEL_19_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 20 Max IB N Buffers */
#define	SPI_CHANNEL_20_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 21 Max IB N Buffers */
#define	SPI_CHANNEL_21_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 22 Max IB N Buffers */
#define	SPI_CHANNEL_22_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 23 Max IB N Buffers */
#define	SPI_CHANNEL_23_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 24 Max IB N Buffers */
#define	SPI_CHANNEL_24_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 25 Max IB N Buffers */
#define	SPI_CHANNEL_25_MAX_IB_N_BUFFERS	0x0000U
/** @brief	SPI Channel 26 Max IB N Buffers */
#define	SPI_CHANNEL_26_MAX_IB_N_BUFFERS	0x0000U
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */
#else	/* __AS_CFG_SPI_LBM__ */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/** @brief	SPI Channel 0 Max IB N Buffers */
#define	SPI_CHANNEL_0_MAX_IB_N_BUFFERS	SPI_TEST_CHANNEL_0_IB_N_BUFFERS
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	SPI Channel 1 Max IB N Buffers */
#define	SPI_CHANNEL_1_MAX_IB_N_BUFFERS	0x0000U
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */
#endif	/* !__AS_CFG_SPI_LBM__ */

/** @brief	SPI Channel Configuration Type.
 *
 *  <b>SPI104_Conf</b>:	<tt>SpiChannel</tt>
 *
 *  All data needed to configure one SPI Channel.
 */
typedef struct {

	/** @brief	SPI Channel Identifier.
	 *
	 *  <b>SPI200_Conf</b>:	<tt>SpiChannelId</tt>
	 *
	 *  SPI Channel ID, used as parameter in SPI API functions.
	 */
	Spi_ChannelType		SpiChannelId;

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	/** @brief	SPI Channel Buffer Type
	 *
	 *  <b>SPI201_Conf</b>:	<tt>SpiChannelType</tt>
	 *
	 *  Buffer usage with EB/IB channel.
	 *
	 *  <tt>SPI_EB</tt>:	<b>E</b>xternal <b>B</b>uffer
	 *  <tt>SPI_IB</tt>:	<b>I</b>nternal <b>B</b>uffer
	 */
	Spi_ChannelBufferType	SpiChannelType;
#endif

  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
	/** @brief	SPI Channel Data Width
	 *
	 *  <b>SPI202_Conf</b>:	<tt>SpiDataWidth</tt>
	 *
	 *  This parameter is the width of a transmitted data unit.
	 *
	 */
	Spi_DataType	SpiDataWidth;
#endif

	/** @brief	SPI Channel Default Data
	*
	*  <b>SPI203_Conf</b>:	<tt>SpiDefaultData</tt>
	*
	*  The default data to be transmitted when (for internal buffer or external
	*  buffer) the pointer passed to <tt>Spi_WriteIB()</tt> (for internal buffer)
	*  or to <tt>Spi_SetupEB()</tt> (for external buffer) is <tt>NULL</tt>.
	*/
	Spi_DataType	SpiDefaultData;

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
	/** @brief	SPI Channel External Buffer Max Size.
	*
	*  <b>SPI204_Conf</b>:	<tt>SpiEbMaxLength</tt>
	*
	*  This parameter contains the maximum size (in bytes) of data buffers in
	*  case of EB Channels only.
	*/
	Spi_NumberOfDataType	SpiEbMaxLength;
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
	/** @brief	SPI Channel Hardware Unit Synchronous.
	*
	*  <b>SPI129_Conf</b>:	<tt>SpiHwUnitSynchronous</tt>
	*
	*  If <tt>SpiHwUnitSynchronous</tt> is set to <tt>SPI_SYNCHRONOUS</tt>, the
	*  <tt>SpiChannel</tt> uses its containing <tt>SpiDriver</tt> in a
	*  synchronous manner. If it is set to <tt>SPI_ASYNCHRONOUS</tt>, it uses the
	*  driver in an asynchronous way. If the parameter is not set, the
	*  <tt>SpiChannel</tt> uses the driver also in an asynchronous way.
	*/
	Spi_SynchronousType	SpiHwUnitSynchronous;
#endif

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
	/** @brief	SPI Channel IB Buffers Number.
	*
	*  <b>SPI205_Conf</b>:	<tt>SpiIbNBuffers</tt>
	*
	*  This parameter contains the maximum number of data buffers in case of IB
	*  Channels and only.
	*/
	Spi_NumberOfDataType		SpiIbNBuffers;
#endif

	/** @brief	SPI Channel Transfer First Starting Bit.
	*
	*  <b>SPI206_Conf</b>:	<tt>SpiTransferStart</tt>
	*
	*  This parameter defines the first starting bit for transmission.
	*/
	Spi_TransferType		SpiTransferStart;

} Spi_ChannelConfigType;


/** @brief	SPI Hardware Unit Slave.
 *
 *  This macro sets-up the SPI Hardware Unit (SCI unit) in Slave Mode: <b>SPI External
 *  Device is SLAVE.</b>
 */
#define	SPI_HW_UNIT_SCI_SLAVE			0x00000002U

/** @brief	SPI Hardware Unit Master.
 *
 *  This macro sets-up the SPI Hardware Unit (RSPI unit) in Master Mode: <b>SPI External
 *  Device is MASTER.</b>
 */
#define	SPI_HW_UNIT_RSPI_MASTER			0x00000002U

/** @brief	SPI Harware Unit Slave Output Disable.
 *
 *  This macro is relevant only in the Slave Mode for the SPI Hardware Unit. In
 *  multiple-slave systems, it is possible for the SPI Master to broadcast a
 *  message to all slaves in the system while ensuring that only one slave
 *  drives data onto the serial output line. In such systems, the TXD lines from
 *  multiple slaves could be tied together. To operate in such a system, the SPI
 *  Hardware Unit can be configured so that it does not drive the TXD pin.
 */
#define	SPI_HW_UNIT_SLAVE_OUTPUT_DISABLE	0x00000008U


/** @brief	SPI Harware Unit (SCI module) peripheral clock type
 *
 *  Select external clock for the module: the SCKn pin functions as the 
 *	clock input pin.
 */
#define SPI_HW_UNIT_EXT_CLK			0x00000001U

/** @brief	SPI Harware Unit (RSPI module) reverse loopback mode
 *
 *  RSPI module: enable reverse loopback mode.
 */
#define SPI_HW_UNIT_LOOPBACK_REV	0x00000008U

/** @brief	SPI Harware Unit (RSPI module) loopback mode
 *
 *  RSPI module: enable loopback mode.
 */
#define SPI_HW_UNIT_LOOPBACK		0x00000010U

/** @brief	SPI Harware Unit (RSPI module) open drain
 *
 *  RSPI module: set ouput pins as open-drain.
 */
#define SPI_HW_UNIT_OPEN_DRAIN		0x00000020U

/** @brief	SPI Harware Unit (RSPI module) MOSI idle value
 *
 *  RSPI module: set MOSI pin idle value equals to 1.
 */
#define SPI_HW_UNIT_MOSI_IDLE_1		0x00000040U

/** @brief	SPI Harware Unit (RSPI module) MOSI idle value enable
 *
 *  RSPI module: MOSI output value equals the value set in the MOIFV bit.
 */
#define SPI_HW_UNIT_MOSI_EN_IDLE	0x00000080U

/** @brief	SPI Harware Unit (RSPI module) 2 SPDR frames.
 *
 *  RSPI module: 2 frames are stored in SPDR (per transfer activation).
 */
#define SPI_HW_UNIT_SPDR_2FRAMES		0x00000100U

/** @brief	SPI Harware Unit (RSPI module) 3 SPDR frames.
 *
 *  RSPI module: 3 frames are stored in SPDR (per transfer activation).
 */
#define SPI_HW_UNIT_SPDR_3FRAMES		0x00000200U

/** @brief	SPI Harware Unit (RSPI module) 4 SPDR frames.
 *
 *  RSPI module: 4 frames are stored in SPDR (per transfer activation).
 */
#define SPI_HW_UNIT_SPDR_4FRAMES		0x00000300U

/** @brief	SPI Harware Unit (RSPI module) 4 SPDR frames.
 *
 *  RSPI module: 4 frames are stored in SPDR (per transfer activation).
 */
#define SPI_HW_UNIT_SPDR_4FRAMES		0x00000300U

/** @brief	SPI Harware Unit (RSPI module) set SSLA0 pin as ouput.
 *
 *  RSPI module: SSLA0 pin output. SSLA1, SSLA2, SSLA3 I/O.
 */
#define SPI_HW_UNIT_SSLA0_OUTPUT		0x00000400U

/** @brief	SPI Harware Unit (RSPI module) set SSLA0 and SSLA0 pins as ouput.
 *
 *  RSPI module: SSLA0, SSLA1 pins output. SSLA2, SSLA3 I/O.
 */
#define SPI_HW_UNIT_SSLA01_OUTPUT		0x00000800U

/** @brief	SPI Harware Unit (RSPI module) set SPDR values read from tx buffer.
 *
 *  RSPI module:  SPDR values are read from the transmit buffer 
 *  (but only if the transmit buffer is empty. 
 */
#define SPI_HW_UNIT_SPDR_FROM_TX		0x00001000U

/** @brief	SPI Harware Unit (RSPI module) set SPDR access in longwords.
 *
 */
#define SPI_HW_UNIT_SPDR_ACCESS_LONG		0x00002000U

/** @brief	SPI Harware Unit (RSPI module) set 2 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL2		0x00004000U

/** @brief	SPI Harware Unit (RSPI module) set 3 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL3		0x00008000U

/** @brief	SPI Harware Unit (RSPI module) set 4 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL4		0x0000C000U

/** @brief	SPI Harware Unit (RSPI module) set 5 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL5		0x00010000U

/** @brief	SPI Harware Unit (RSPI module) set 6 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL6		0x00014000U

/** @brief	SPI Harware Unit (RSPI module) set 7 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL7		0x00018000U

/** @brief	SPI Harware Unit (RSPI module) set 8 RSPCK oscillation delay.
 *
 */
#define SPI_HW_UNIT_RSPCK_DEL8		0x0001C000U

/** @brief	SPI Harware Unit (RSPI module). Keeps the SSL signal level from the 
 * end of transfer until the beginning of the next access.
 */
#define SPI_HW_UNIT_KEEP_SSL		0x00020000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 8 bits data length.
 */
#define SPI_HW_UNIT_8B_DATA_LEN		0x001C0000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 9 bits data length.
 */
#define SPI_HW_UNIT_9B_DATA_LEN		0x00200000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 10 bits data length.
 */
#define SPI_HW_UNIT_10B_DATA_LEN		0x00240000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 11 bits data length.
 */
#define SPI_HW_UNIT_11B_DATA_LEN		0x00280000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 12 bits data length.
 */
#define SPI_HW_UNIT_12B_DATA_LEN		0x002C0000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 13 bits data length.
 */
#define SPI_HW_UNIT_13B_DATA_LEN		0x00300000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 14 bits data length.
 */
#define SPI_HW_UNIT_14B_DATA_LEN		0x00340000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 15 bits data length.
 */
#define SPI_HW_UNIT_15B_DATA_LEN		0x00380000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 16 bits data length.
 */
#define SPI_HW_UNIT_16B_DATA_LEN		0x003C0000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 24 bits data length.
 */
#define SPI_HW_UNIT_24B_DATA_LEN		0x00040000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI with 32 bits data length.
 */
#define SPI_HW_UNIT_32B_DATA_LEN		0x000C0000U

/** @brief	SPI Harware Unit (RSPI module). Set RSPI LSB transmitted first.
 */
#define SPI_HW_UNIT_LSB_FIRST			0x00400000U

/** @brief	SPI Harware Unit (RSPI module). Enable next access delay.
 */
#define SPI_HW_UNIT_EN_NEXT_ACC_DEL			0x00800000U

/** @brief	SPI Harware Unit (RSPI module). Enable SSL negation delay.
 */
#define SPI_HW_UNIT_EN_SSL_DEL				0x01000000U

/** @brief	SPI Harware Unit (RSPI module). Enable RSPCK setting delay.
 */
#define SPI_HW_UNIT_EN_RSPCK_SET_DEL		0x02000000U

/** @brief	SPI Harware Unit (RSPI module). Enable RSPCK phase setting delay.
 */
#define SPI_HW_UNIT_EN_RSPCK_PHASE_DEL		0x04000000U


/** @brief	SPI Harware Unit (RSPI module). Enable parity bit check.
 */
#define SPI_HW_UNIT_EN_PARITY				0x08000000U

/** @brief	SPI Harware Unit (RSPI module). Selects odd parity for use in 
 *  transmission and reception
 */
#define SPI_HW_UNIT_ODD_PARITY				0x10000000U

/** @brief	SPI Harware Unit (RSPI module). Enable the self-diagnosis function 
 *  of the parity circuit
 */
#define SPI_HW_UNIT_EN_PARITY_TEST			0x40000000U


/** @brief	SPI Harware Unit (RSPI module). Enable all delays
 */
#define SPI_HW_ENABLE_ALL_DELAYS			0x07800000U


/*
 * Available SPI Hardware Units.
 */
#define	SPI_HW_UNIT_0	0x00	/**< Renesas RX200  SCI0 module. */
#define	SPI_HW_UNIT_1	0x01	/**< Renesas RX200  SCI1 module. */
#define	SPI_HW_UNIT_5	0x05	/**< Renesas RX200  SCI2 module. */
#define	SPI_HW_UNIT_6	0x06	/**< Renesas RX200  SCI3 module. */
#define	SPI_HW_UNIT_8	0x08	/**< Renesas RX200  SCI4 module. */
#define	SPI_HW_UNIT_9	0x09	/**< Renesas RX200  SCI5 module. */
#define	SPI_HW_UNIT_12	0x0C	/**< Renesas RX200  SCI6 module. */
#define	SPI_HW_UNIT_13	0x0D	/**< Renesas RX200  RSPI module. */


/* SPI Published Information.
 *
 * SPI235_Conf:		SpiPublishedInformation
 *
 * Container holding all SPI specific published information parameters
 */

/** @brief	SPI Max Hardware Unit.
 *
 *  <b>SPI236_Conf</b>:		<tt>SpiMaxHwUnit</tt>
 *
 *  Number of different SPI hardware microcontroller peripherals (units/busses)
 *  available and handled by this SPI Handler/Driver module.
 */
#define	SPI_MAX_HW_UNIT		SPI_HW_UNIT_13 + 1


/*
 * Configured SPI Chip Selects.
 */
/*
 * TEST Chip-Selects.
 */
#define	SPI_TEST_CS_0	0x00U	/**< Test Chip-Select 0.	*/
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_CS_1	0x01U	/**< Test Chip-Select 1 (Synchronous).  */
#endif

/** @brief	Number of Configured Test External Devices.	*/
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_EXTERNAL_DEVICES_NUMBER	SPI_TEST_CS_1 + 1
#else
#define	SPI_TEST_EXTERNAL_DEVICES_NUMBER	SPI_TEST_CS_0 + 1
#endif

#ifdef	__AS_CFG_SPI_LBM__

/*
 * Loop-back Mode Chip-Selects.
 */
#define	SPI_LBM_CS_0	0x00U	/**< Loop-back Mode Chip-Select 0.	*/
#define	SPI_LBM_CS_1	0x01U	/**< Loop-back Mode Chip-Select 1.	*/
#define	SPI_LBM_CS_2	0x02U	/**< Loop-back Mode Chip-Select 2.	*/
#define	SPI_LBM_CS_3	0x03U	/**< Loop-back Mode Chip-Select 3.	*/
#define	SPI_LBM_CS_4	0x04U	/**< Loop-back Mode Chip-Select 4.	*/
#define	SPI_LBM_CS_5	0x05U	/**< Loop-back Mode Chip-Select 5.	*/
#define	SPI_LBM_CS_6	0x06U	/**< Loop-back Mode Chip-Select 6.	*/
#define	SPI_LBM_CS_7	0x07U	/**< Loop-back Mode Chip-Select 7.	*/
#define	SPI_LBM_CS_8	0x08U	/**< Loop-back Mode Chip-Select 8.	*/
#define	SPI_LBM_CS_9	0x09U	/**< Loop-back Mode Chip-Select 9.	*/
#define	SPI_LBM_CS_10	0x0AU	/**< Loop-back Mode Chip-Select 10.	*/
#define	SPI_LBM_CS_11	0x0BU	/**< Loop-back Mode Chip-Select 11.	*/
#define	SPI_LBM_CS_12	0x0CU	/**< Loop-back Mode Chip-Select 12.	*/
#define	SPI_LBM_CS_13	0x0DU	/**< Loop-back Mode Chip-Select 13.	*/

/** @brief	Number of Configured Loop-back Mode External Devices.	*/
#define	SPI_LBM_EXTERNAL_DEVICES_NUMBER		SPI_LBM_CS_13 + 1  /*SPI_LBM_CS_13 + 1*/

#endif	/* __AS_CFG_SPI_LBM__ */

/** @brief	SPI Polarity
 *
 *  This type defines polarity for SPI signals.
 */
typedef	enum {
	SPI_LOW		=	STD_LOW,	/**< Low Polarity.	*/
	SPI_HIGH	=	STD_HIGH,	/**< High Polarity.	*/
} Spi_PolarityType;

/*Renesas RX200: data sampling only on leading edge for SCI.
 * RSPI module can handle both leading and trailing but is configured through
 * Spi_ExternalDeviceConfigType->SpiHwUnitMode.
 */
#if 0
/** @brief	SPI Data Shift Edge Type.
 *
 *  SPI data shift edge type: data sampling on leading or trailing clock edge.
 */
typedef	enum {
	SPI_LEADING	=	0,	/**< Leading Clock Edge.	*/
	SPI_TRAILING		/**< Trailing Clock Edge.	*/
} Spi_DataShiftEdgeType;

#endif
/** @brief	SPI External Device Configuration Type.
 *
 *  <b>SPI207_Conf</b>:	<tt>SpiExternalDevice</tt>
 *
 *  The communication settings of an external device. Closely linked to Spi Job.
 */
typedef	struct {

	/** @brief	Communication Baudrate
	*
	*  <b>SPI208_Conf</b>:	<tt>SpiBaudrate</tt>
	*
	*  This parameter is the communication baudrate - This parameter allows using
	*  a range of values, from the point of view of configuration tools, from
	*  Hz up to MHz.
	*
	*/
	float32		SpiBaudrate;

	/** @brief	Chip Select Identifier.
	*
	*  <b>SPI209_Conf</b>:	<tt>SpiCsIdentifier</tt>
	*
	*  This parameter is the symbolic name to identify the Chip Select (CS)
	*  allocated to this Job.
	*/
	Spi_HWUnitType	SpiCsIdentifier;

	/** @brief	Chip Select Polarity.
	*
	*  <b>SPI210_Conf</b>:	<tt>SpiCsPolarity</tt>
	*
	*  This parameter defines the active polarity of Chip Select.
	*
	*  <tt>SPI_HIGH</tt> or <tt>SPI_LOW</tt>
	*/
	Spi_PolarityType	SpiCsPolarity;
	
	/*Renesas RX200 support only on leading edge for SCI module.
	 * RSPI module can handle leading and trailing edges, it is configured through
	 * SpiHwUnitMode.
	 **/
#if 0

	/** @brief	Data Shift Edge.
	*
	*  <b>SPI211_Conf</b>:	<tt>SpiDataShiftEdge</tt>
	*
	*  This parameter defines the SPI data shift edge.
	*/
	Spi_DataShiftEdgeType	SpiDataShiftEdge;
#endif
	
	/** @brief	Enable Chip-Select.
	*
	*  <b>SPI212_Conf</b>:	<tt>SpiEnableCs</tt>
	*
	*  This parameter defines whether the SPI master will handle the chip select
	*  for the device. <tt>SpiEnableCs = FALSE</tt> means that the SPI drives the
	*  chip select lines autonomously without explicit chip select control by the
	*  driver. <tt>SpiEnableCs = TRUE</tt> means that the SPI driver shall drive
	*  the chip select lines explicitly as DIO.
	*/
	boolean		SpiEnableCs;

	/** @brief	Chip-Select Dio Channel Identidfier.
	*
	*  This parameter defines, when the SPI master will handle the chip select
	*  for the device, the DIO Channel Identifier for the Cs.
	*/
	Dio_ChannelType	SpiCsChannelId;

	/** @brief	SPI Hardware Unit.
	*
	*  <b>SPI217_Conf</b>:	<tt>SpiHwUnit</tt>
	*
	*  This parameter is the symbolic name to identify the HW SPI Hardware
	*  microcontroller peripheral allocated to this Job.
	*/
	Spi_HWUnitType	SpiHwUnit;

	/** @brief	SPI Shift Clock Idle Level.
	*
	*  <b>SPI213_Conf</b>:	<tt>SpiShiftClockIdleLevel</tt>
	*
	*  This parameter defines the SPI shift clock idle level.
	*/
	Spi_PolarityType	SpiShiftClockIdleLevel;


	/** @brief	SPI Timing Between Clock and Chip-Select (in seconds).
	*
	*  <b>SPI214_Conf</b>:	<tt>SpiTimeClk2Cs</tt>
	*
	*  This parameter allows to use a range of values from 0 up to 0.0001
	*  seconds. The real configuration value used in software BSW-SPI is
	*  calculated out of this by the generator tools.
	*
	* @note	float value in configuration, uint32 value here.
	*/
	uint32		SpiTimeClk2Cs;


#if	( SPI_LEVEL_DELIVERED == 2 )
	/** @brief	SPI Hardware Unit Type.
	*
	*  If <tt>SpiHwUnitSynchronous</tt> is set to <tt>SPI_SYNCHRONOUS</tt>, the
	*  <tt>SpiExternalDevice</tt> uses its containing <tt>SpiDriver</tt> in a
	*  synchronous manner. If it is set to <tt>SPI_ASYNCHRONOUS</tt>, it uses the
	*  driver in an asynchronous way.
	*
	*  Handling asynchronous and synchronous transmissions means that the
	*  microcontroller for which this software module is dedicated has to provide
	*  more than one SPI bus. In fact, the goal is to support SPI buses using a
	*  so-called synchronous driver and to support other SPI buses using a
	*  so-called asynchronous driver.
	*/
	Spi_SynchronousType	SpiHwUnitSynchronous;
#endif

	/** @brief	SPI Hardware Unit Mode.
	*
	*  This parameter contains or-ed symbolic macros to setup HW SPI Hardware
	*  microcontroller peripheral allocated to this Job.
	*  
	*  Bit/Field	Description
	*  	31 	Reserved
	*  	30	Parity Self-Testing (only for RSPI)
	*  	29	Reserved
	*  	28	Parity Mode	(only for RSPI)
	*  	27	Parity Enable (only for RSPI)
	*  	26	RSPCK Phase Setting
	*  	25	RSPCK Delay Setting Enable
	*  	24	SSL Negation Delay Setting Enable
	*  	23	RSPI Next-Access Delay Enable
	*	22	RSPI LSB First
	*	21:18 RSPI Data Length Setting 
	*	17	SSL Signal Level Keeping (only for RSPI)
	*	16:14 RSPCK Delay Setting (only for RSPI)
	*  	13	Data buffer access mode (word or longword) (only for RSPI)
	*  	12	Data values are read either from the for receiving or from 
	*  		transmission buffer (only for RSPI).
	*	11:10	SSlx Pin Output Selection (only for RSPI)
	*  	9:8	Number of frames stored in the buffer (only for RSPI)
	*	7	MOSI Idle Value Fixing Enable (only for RSPI)
	*	6	MOSI Idle fixed value (only for RSPI)
	*	5	Set MOSI output pin as (CMOS or Open-Drain) (only for RSPI)
	*	4	Enable Loopback 2 (only for RSPI)
	*	3	Enable Loopback  (only for RSPI)
	*	2	Enable Multi-Master Error Detection.
	*	1	Master/Slave Select (0 Master, 1 Slave) 	
	*	0	RSPI: Enable Loopback (reverse)
	*	0	SCI: Clock Source (PCLKB or external)
	*/
	uint32		SpiHwUnitMode;

} Spi_ExternalDeviceConfigType;

/*
 * Configured SPI Jobs.
 */

/*
 * TEST Jobs.
 */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )

#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
#define	SPI_TEST_JOB_0_PRI	0x03U	/**< Test Job 0 Priority (Lowest).    */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */

#ifdef	__AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__
void Spi_TestJob0EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__ */

#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

/** @brief	Configured SPI TEST Jobs Channels Max Number.		      */
#define	SPI_TEST_JOBS_CHANNELS_MAX_NUMBER	1


#define	SPI_TEST_JOB_0		0x0000U		/**< Test Job 0.	      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#define	SPI_TEST_JOB_0_EB	0x0001U		/**< Test Job 0. (EB)	      */
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_JOB_0_SYNC	0x0002U		/**< Test Job 0. (Synch)      */
#define	SPI_TEST_JOB_0_EB_SYNC	0x0003U		/**< Test Job 0. (EB + Sync)  */
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		*/
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	*/
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_JOB_0_SYNC	0x0001U		/**< Test Job 0. (Synch)      */
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	TEST Jobs Number. */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_JOBS_NUMBER	SPI_TEST_JOB_0_EB_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_TEST_JOBS_NUMBER	SPI_TEST_JOB_0_EB + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	 */
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_JOBS_NUMBER	SPI_TEST_JOB_0_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_TEST_JOBS_NUMBER	SPI_TEST_JOB_0 + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 )	 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#ifdef	__AS_CFG_SPI_LBM__


/*
 * Loop-back Mode Jobs.
 */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )

#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
#define	SPI_LBM_JOB_0_PRI	0x02U	/**< Loop-back Mode Job 0 Priority.   */
#define	SPI_LBM_JOB_1_PRI	0x03U	/**< Loop-back Mode Job 1 Priority.   */
#define	SPI_LBM_JOB_2_PRI	0x01U	/**< Loop-back Mode Job 2 Priority.   */
#define	SPI_LBM_JOB_3_PRI	0x03U	/**< Loop-back Mode Job 3 Priority.   */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */

#ifdef	__AS_CFG_SPI_LBM_JOB_0_END_NOTIFICATION__
void Spi_LBMJob0EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_JOB_0_END_NOTIFICATION__ */

#ifdef	__AS_CFG_SPI_LBM_JOB_1_END_NOTIFICATION__
void Spi_LBMJob1EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_JOB_1_END_NOTIFICATION__ */

#ifdef	__AS_CFG_SPI_LBM_JOB_2_END_NOTIFICATION__
void Spi_LBMJob2EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_JOB_2_END_NOTIFICATION__ */

#ifdef	__AS_CFG_SPI_LBM_JOB_3_END_NOTIFICATION__
void Spi_LBMJob3EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_JOB_3_END_NOTIFICATION__ */

#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

#define	SPI_LBM_JOBS_CHANNELS_MAX_NUMBER	7

#define	SPI_LBM_JOB_0		0x0000U		/**< Loop-back Mode Job 0.    */
#define	SPI_LBM_JOB_1		0x0001U		/**< Loop-back Mode Job 1.    */
#define	SPI_LBM_JOB_2		0x0002U		/**< Loop-back Mode Job 2.    */
#define	SPI_LBM_JOB_3		0x0003U		/**< Loop-back Mode Job 3.    */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	Loop-back Mode Job 0. (EB) */
#define	SPI_LBM_JOB_0_EB	0x0004U
/** @brief	Loop-back Mode Job 1. (EB) */
#define	SPI_LBM_JOB_1_EB	0x0005U
/** @brief	Loop-back Mode Job 2. (EB) */
#define	SPI_LBM_JOB_2_EB	0x0006U
/** @brief	Loop-back Mode Job 3. (EB) */
#define	SPI_LBM_JOB_3_EB	0x0007U
#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	Loop-back Mode Job 0. (Synch) */
#define	SPI_LBM_JOB_0_SYNC	0x0008U
/** @brief	Loop-back Mode Job 1. (Synch) */
#define	SPI_LBM_JOB_1_SYNC	0x0009U
/** @brief	Loop-back Mode Job 2. (Synch) */
#define	SPI_LBM_JOB_2_SYNC	0x000AU
/** @brief	Loop-back Mode Job 3. (Synch) */
#define	SPI_LBM_JOB_3_SYNC	0x000BU
/** @brief	Loop-back Mode Job 0. (EB + Sync) */
#define	SPI_LBM_JOB_0_EB_SYNC	0x000CU
/** @brief	Loop-back Mode Job 1. (EB + Sync) */
#define	SPI_LBM_JOB_1_EB_SYNC	0x000DU
/** @brief	Loop-back Mode Job 2. (EB + Sync) */
#define	SPI_LBM_JOB_2_EB_SYNC	0x000EU
/** @brief	Loop-back Mode Job 3. (EB + Sync) */
#define	SPI_LBM_JOB_3_EB_SYNC	0x000FU
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		*/
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	*/
#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	Loop-back Mode Job 0. (Synch) */
#define	SPI_LBM_JOB_0_SYNC	0x0004U
/** @brief	Loop-back Mode Job 1. (Synch) */
#define	SPI_LBM_JOB_1_SYNC	0x0005U
/** @brief	Loop-back Mode Job 2. (Synch) */
#define	SPI_LBM_JOB_2_SYNC	0x0006U
/** @brief	Loop-back Mode Job 3. (Synch) */
#define	SPI_LBM_JOB_3_SYNC	0x0007U
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	LBM Jobs Number. */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_LBM_JOBS_NUMBER	SPI_LBM_JOB_3_EB_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_LBM_JOBS_NUMBER	SPI_LBM_JOB_3_EB + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	 */
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_LBM_JOBS_NUMBER	SPI_LBM_JOB_3_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_LBM_JOBS_NUMBER	SPI_LBM_JOB_3 + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 )	 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#endif	/* !__AS_CFG_SPI_LBM__ */

/** @brief	Maximum Number of Configured SPI Jobs. */
#ifdef	__AS_CFG_SPI_LBM__
#define	SPI_JOBS_MAX_NUMBER	SPI_LBM_JOBS_NUMBER
#else	/* __AS_CFG_SPI_LBM__ */
#ifdef	__AS_CFG_SPI_ENC28J60__
#define	SPI_JOBS_MAX_NUMBER	SPI_ENC28J60_JOBS_NUMBER
#else	/* __AS_CFG_SPI_ENC28J60__ */
#define	SPI_JOBS_MAX_NUMBER	SPI_TEST_JOBS_NUMBER
#endif	/* !__AS_CFG_SPI_ENC28J60__ */
#endif	/* !__AS_CFG_SPI_LBM__ */

#ifdef	__AS_CFG_SPI_LBM__

/** @brief	Configured SPI Jobs Channels Max Number.		      */
#define	SPI_JOBS_CHANNELS_MAX_NUMBER SPI_LBM_JOBS_CHANNELS_MAX_NUMBER

#else	/* __AS_CFG_SPI_LBM__ */

/** @brief	Configured SPI Jobs Channels Max Number.		      */
#define	SPI_JOBS_CHANNELS_MAX_NUMBER SPI_TEST_JOBS_CHANNELS_MAX_NUMBER

#endif	/* __AS_CFG_SPI_LBM__ */

/** @brief	SPI Job Configuration Type.
 *
 *  <b>SPI105_Conf</b>:	<tt>SpiJob</tt>
 *
 *  All data needed to configure one SPI Job, amongst others the connection
 *  between the internal SPI unit and the special settings for an external
 *  device is done.
 */
typedef	struct {

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
  /** @brief	SPI Job End Notification.
   *
   *  <b>SPI218_Conf</b>:	<tt>SpiJobEndNotification</tt>
   *
   *  This parameter is a reference to a notification function.
   */
  Spi_JobEndNotification	SpiJobEndNotification;
#endif

  /** @brief	SPI Job Identifier.
   *
   *  <b>SPI219_Conf</b>:	<tt>SpiJobId</tt>
   *
   *  SPI Job ID, used as parameter in SPI API functions.
   */
  Spi_JobType			SpiJobId;

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
  /** @brief	SPI Job Priority.
   *
   *  <b>SPI220_Conf</b>:	<tt>SpiJobPriority</tt>
   *
   *  Priority set accordingly to <b>SPI093</b>: 0, lowest, 3, highest priority.
   */
  uint8				SpiJobPriority;
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

  /** @brief	SPI Device Assignment.
   *
   *  <b>SPI216_Conf</b>:	<tt>SpiDeviceAssignment</tt>
   *
   *  Reference to the external device used by this job.
   */
  uint8				SpiDeviceAssignment;

  /** @brief	SPI Channel List
   *
   *  <tt>SpiChannelList</tt>
   *
   *  References to SPI channels and their order within the Job.
   */
  const Spi_ChannelType *	SpiChannelList;

} Spi_JobConfigType;

/*
 * Configured SPI Sequences.
 */

/*
 * TEST Sequences.
 */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__
void Spi_TestSeq0EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

/** @brief	Test Sequence 0. */
#define	SPI_TEST_SEQ_0		0x0000U
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	Test Sequence 0. (EB) */
#define	SPI_TEST_SEQ_0_EB	0x0001U
#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	Test Sequence 0. (Synch) */
#define	SPI_TEST_SEQ_0_SYNC	0x0002U
/** @brief	Test Sequence 0. (EB + Sync) */
#define	SPI_TEST_SEQ_0_EB_SYNC	0x0003U
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		*/
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	*/
#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	Test Sequence 0. (Synch) */
#define	SPI_TEST_SEQ_0_SYNC	0x0001U
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	TEST Sequences Number. */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_SEQUENCES_NUMBER	SPI_TEST_SEQ_0_EB_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_TEST_SEQUENCES_NUMBER	SPI_TEST_SEQ_0_EB + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	 */
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_TEST_SEQUENCES_NUMBER	SPI_TEST_SEQ_0_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_TEST_SEQUENCES_NUMBER	SPI_TEST_SEQ_0 + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 )	 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#ifdef	__AS_CFG_SPI_LBM__

/*
 * Loop-back Mode Sequences.
 */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )

#ifdef	__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__
void Spi_LBMSeq0EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */

#ifdef	__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__
void Spi_LBMSeq1EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */

#ifdef	__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__
void Spi_LBMSeq2EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */

#ifdef	__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__
void Spi_LBMSeq3EndNotification(
  void
);
#endif	/* __AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */

#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

/** @brief	Loop-back Mode Sequence 0. */
#define	SPI_LBM_SEQ_0		0x0000U
/** @brief	Loop-back Mode Sequence 1. */
#define	SPI_LBM_SEQ_1		0x0001U
/** @brief	Loop-back Mode Sequence 2. */
#define	SPI_LBM_SEQ_2		0x0002U
/** @brief	Loop-back Mode Sequence 3. */
#define	SPI_LBM_SEQ_3		0x0003U
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
/** @brief	Loop-back Mode Sequence 0. (EB) */
#define	SPI_LBM_SEQ_0_EB	0x0004U
/** @brief	Loop-back Mode Sequence 1. (EB) */
#define	SPI_LBM_SEQ_1_EB	0x0005U
/** @brief	Loop-back Mode Sequence 2. (EB) */
#define	SPI_LBM_SEQ_2_EB	0x0006U
/** @brief	Loop-back Mode Sequence 3. (EB) */
#define	SPI_LBM_SEQ_3_EB	0x0007U
#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	Loop-back Mode Sequence 0. (Synch) */
#define	SPI_LBM_SEQ_0_SYNC	0x0008U
/** @brief	Loop-back Mode Sequence 1. (Synch) */
#define	SPI_LBM_SEQ_1_SYNC	0x0009U
/** @brief	Loop-back Mode Sequence 2. (Synch) */
#define	SPI_LBM_SEQ_2_SYNC	0x000AU
/** @brief	Loop-back Mode Sequence 3. (Synch) */
#define	SPI_LBM_SEQ_3_SYNC	0x000BU
/** @brief	Loop-back Mode Sequence 0. (EB + Sync) */
#define	SPI_LBM_SEQ_0_EB_SYNC	0x000CU
/** @brief	Loop-back Mode Sequence 1. (EB + Sync) */
#define	SPI_LBM_SEQ_1_EB_SYNC	0x000DU
/** @brief	Loop-back Mode Sequence 2. (EB + Sync) */
#define	SPI_LBM_SEQ_2_EB_SYNC	0x000EU
/** @brief	Loop-back Mode Sequence 3. (EB + Sync) */
#define	SPI_LBM_SEQ_3_EB_SYNC	0x000FU
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		*/
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	*/
#if	( SPI_LEVEL_DELIVERED == 2 )
/** @brief	Loop-back Mode Sequence 0. (Synch) */
#define	SPI_LBM_SEQ_0_SYNC	0x0004U
/** @brief	Loop-back Mode Sequence 1. (Synch) */
#define	SPI_LBM_SEQ_1_SYNC	0x0005U
/** @brief	Loop-back Mode Sequence 2. (Synch) */
#define	SPI_LBM_SEQ_2_SYNC	0x0006U
/** @brief	Loop-back Mode Sequence 3. (Synch) */
#define	SPI_LBM_SEQ_3_SYNC	0x0007U
#endif	/* ( SPI_LEVEL_DELIVERED == 2 )		 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/** @brief	Loop-back Mode Sequences Number. */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_LBM_SEQUENCES_NUMBER	SPI_LBM_SEQ_3_EB_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_LBM_SEQUENCES_NUMBER	SPI_LBM_SEQ_3_EB + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */
#else	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )	 */
#if	( SPI_LEVEL_DELIVERED == 2 )
#define	SPI_LBM_SEQUENCES_NUMBER	SPI_LBM_SEQ_3_SYNC + 1
#else	/* ( SPI_LEVEL_DELIVERED == 2 )	 */
#define	SPI_LBM_SEQUENCES_NUMBER	SPI_LBM_SEQ_3 + 1
#endif	/* !( SPI_LEVEL_DELIVERED == 2 )	 */
#endif	/* !( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#endif	/* __AS_CFG_SPI_LBM__ */

/** @brief	Maximum Number of Configured SPI Sequences. */
#if defined(__AS_CFG_SPI_LBM__)
#define	SPI_SEQUENCES_MAX_NUMBER	SPI_LBM_SEQUENCES_NUMBER
#elif defined(__AS_CFG_SPI_ENC28J60__)
#define	SPI_SEQUENCES_MAX_NUMBER	SPI_ENC28J60_SEQUENCES_NUMBER
#else
#define	SPI_SEQUENCES_MAX_NUMBER	SPI_TEST_SEQUENCES_NUMBER
#endif	/* !__AS_CFG_SPI_LBM__ */


/** @brief	SPI Sequence Configuration Type.
 *
 *  <b>SPI106_Conf</b>:	<tt>SpiSequence</tt>
 *
 *  All data needed to configure one SPI Sequence.
 */
typedef struct {

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )

#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
  /** @brief	SPI Interruptible Sequence.
   *
   *  <b>SPI222_Conf</b>:	<tt>SpiInterruptibleSequence</tt>
   *
   *  This parameter allows or not this Sequence to be suspended by another
   *  one.
   */
  boolean			SpiInterruptibleSequence;
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */

  /** @brief	SPI Sequence End Notification.
   *
   *  <b>SPI223_Conf</b>:	<tt>SpiSeqEndNotification</tt>
   *
   *  This parameter is a reference to a notification function.
   */
  Spi_SeqEndNotification	SpiSeqEndNotification;
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */

  /** @brief	SPI Sequence Identifier.
   *
   *  <b>SPI224_Conf</b>:	<tt>SpiSequenceId</tt>
   *
   *  SPI Sequence ID, used as parameter in SPI API functions.
   */
  Spi_SequenceType		SpiSequenceId;

  /** @brief	SPI Job Assignment
   *
   *  <b>SPI221_Conf</b>:	<tt>SpiJobAssignment</tt>
   *
   *  A sequence references several jobs, which are executed during a
   *  communication sequence.
   */
  const Spi_JobType *		SpiJobAssignment;

} Spi_SequenceConfigType;

/** @brief	SPI Driver.
 *
 *  <b>SPI091_Conf</b>:		<tt>SpiDriver</tt>
 *
 *  Configuration of one instance (if multiplicity is 1, it is the sole
 *  configuration) of an SPI driver.
 */
typedef struct {

  /** @brief	SPI Max Channel.
   *
   *  <b>SPI197_Conf</b>:	<tt>SpiMaxChannel</tt>
   *
   *  This parameter contains the number of Channels configured. It will be
   *  gathered by tools during the configuration stage.
   */
  Spi_ChannelType			SpiMaxChannel;

  /** @brief	SPI Max External Device.
   *
   *  Total number of Jobs configured.
   */
  Spi_HWUnitType			SpiMaxExternalDevice;

  /** @brief	SPI Max Job.
   *
   *  <b>SPI198_Conf</b>:	<tt>SpiMaxJob</tt>
   *
   *  Total number of Jobs configured.
   */
  Spi_JobType				SpiMaxJob;

  /** @brief	SPI Max Sequence.
   *
   *  <b>SPI199_Conf</b>:	<tt>SpiMaxSequence</tt>
   *
   *  Total number of Sequences configured.
   */
  Spi_SequenceType			SpiMaxSequence;

  /** @brief	SPI Channel Configuration.
   *
   *  All data needed to configure one SPI-channel.
   */
  const Spi_ChannelConfigType *		SpiChannel;

  /** @brief	SPI External Device Configuration.
   *
   *  The communication settings of an external device. Closely linked to
   *  SpiJob.
   */
  const Spi_ExternalDeviceConfigType *	SpiExternalDevice;

  /** @brief	SPI Job Configuration.
   *
   *  All data needed to configure one SPI-Job, amongst others the connection
   *  between the internal SPI unit and the special settings for an external
   *  device is done.
   */
  const Spi_JobConfigType *		SpiJob;

  /** @brief	SPI Sequence Configuration.
   *
   *  All data needed to configure one SPI-sequence.
   */
  const Spi_SequenceConfigType *	SpiSequence;

}	Spi_DriverConfigType;

/** @brief	SPI Handler/Driver Configuration Parameters
 *
 *  <b>SPI344</b>:	The description of the type <tt>Spi_ConfigType</tt> is
 *  			implementation specific and it shall be provided for
 *  			external use.
 *
 *  <b>SPI008</b>:	The type <tt>Spi_ConfigType</tt> is an external data
 *  			structure and shall contain the initialization data for
 *  			the SPI Handler/Driver. It shall contain:
 *  			 - MCU dependent properties for SPI HW units
 *  			 - Definition of Channels
 *  			 - Definition of Jobs
 *  			 - Definition of Sequences
 *
 *  <b>SPI063</b>:	For the type <tt>Spi_ConfigType</tt>, the definition for
 *  			each Channel shall contain:
 *  			 - Buffer usage with EB/IB Channel
 *  			 - Transmit data width (1 up to 32 bits)
 *  			 - Number of data buffers for IB Channels (at least 1)
 *  			   or it is the maximum of data for EB Channels (a value
 *  			   of 0 makes no sense)
 *  			 - Transfer start LSB or MSB
 *  			 - Default transmit value
 *
 *  <b>SPI009</b>:	For the type <tt>Spi_ConfigType</tt>, the definition for
 *  			each Job shall contain:
 *  			 - Assigned SPI HW Unit
 *  			 - Assigned Chip Select pin (it is possible to assign no
 *  			   pin)
 *  			 - Chip select functionality on/off
 *  			 - Chip select pin polarity high or low
 *  			 - Baud rate
 *  			 - Timing between clock and chip select
 *  			 - Shift clock idle low or idle high
 *  			 - Data shift with leading or trailing edge
 *  			 - Priority (4 levels are available from 0, the lower to
 *  			   3, the higher)
 *  			 - Job finish end notification function
 *  			 - MCU dependent properties for the Job (only if needed)
 *  			 - Fixed link of Channels (at least one)
 *
 *  <b>SPI064</b>:	For the type <tt>Spi_ConfigType</tt>, the definition for
 *  			each Sequence shall contain:
 *  			 - Collection of Jobs (at least one)
 *  			 - Interruptible or not interruptible after each Job
 *  			 - Sequence finish end notification function
 *
 *  <b>SPI010</b>:	For the type <tt>Spi_ConfigType</tt>, the configuration
 *  			will map the Jobs to the different SPI hardware units
 *  			and the devices.
 */
typedef	Spi_DriverConfigType	Spi_ConfigType;

/** @brief	Test Configuration
 *
 *  Identifier for Test SPI Handler/Driver Configuration.
 */
#define	SPI_CONFIG_TEST		0x00000000U

/** @brief	Test Configuration Pointer
 *
 *  Pointer of Test SPI Handler/Driver Configuration.
 */
#define	SPI_CONFIG_TEST_PTR	&Spi_Config[SPI_CONFIG_TEST]

#ifdef	__AS_CFG_SPI_LBM__

/** @brief	Loop-back Mode Configuration
 *
 *  Identifier for Loop-back Mode SPI Handler/Driver Configuration.
 */
#define	SPI_CONFIG_LBM		0x00000001U

/** @brief	Loop-back Mode Configuration Pointer
 *
 *  Pointer of Loop-back Mode SPI Handler/Driver Configuration.
 */
#define	SPI_CONFIG_LBM_PTR	&Spi_Config[SPI_CONFIG_LBM]

#endif	/* __AS_CFG_SPI_TEST__ */


/** @brief	Default Configuration
 *
 *  Identifier for Default SPI Handler/Driver Configuration.
 */
#define	SPI_CONFIG_DEFAULT	SPI_CONFIG_TEST

/** @brief	Default Configuration Pointer
 *
 *  Pointer of Default SPI Handler/Driver Configuration.
 */
#define	SPI_CONFIG_DEFAULT_PTR	&Spi_Config[SPI_CONFIG_DEFAULT]

#endif	/* SPI_CFG_H */
