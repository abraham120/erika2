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

/** @file	Dma.h
 *  @brief	AUTOSAR-"like" DMA Driver Header File.
 *
 *  The DMA driver is part of the microcontroller abstraction layer (MCAL).
 *  It provides services to offload data transfer tasks from the uC, allowing
 *  for more efficient use of the uC and the available bus bandwidth.
 *  The DMA driver can perform transfers between memory and peripherals. It has
 *  dedicated channels for each supported on-chip module and can be programmed
 *  to automatically perform transfers between peripherals and memory as the
 *  peripheral is ready to transfer more data.
 *  It also provides the required mechanism to configure the onchip DMA
 *  peripheral.
 *
 *  Each variable that shall be accessible by AUTOSAR Debugging, shall be
 *  defined as global variable.
 *
 *  All type definitions of variables which shall be debugged, shall be
 *  accessible by the header file <tt>Dma.h</tt>.
 *
 *  The declaration of variables in the header file shall be such, that it is
 *  possible to calculate the size of the variables by C-"sizeof".
 *
 *  Variables available for debugging shall be described in the respective Basic
 *  Software Module Description
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#ifndef	DMA_H
#define	DMA_H

/** @brief	Vendor Id
 *
 *  Vendor Id from document:
 *  [STD_HIS_SUPPLIER_IDS] HIS Software Supplier Identifications
 *  http://www.automotive--his.de/his--ergebnisse.htm (broken link)
 */
#define	DMA_VENDOR_ID		0

/** @brief	Module Id
 *
 *  Module Id (083) from document:
 *  List of Basic Software Modules
 *  V1.5.0
 *  R4.0 Rev 2
 */
#define	DMA_MODULE_ID		0xFFFF	/**< (Not Specified in AUTOSAR)       */

#define	DMA_SW_MAJOR_VERSION	1	/**< Software Version Major Number    */
#define	DMA_SW_MINOR_VERSION	0	/**< Software Version Minor Number    */
#define	DMA_SW_PATCH_VERSION	0	/**< Software Version Patch Number    */

#define	DMA_AR_MAJOR_VERSION	4	/**< AUTOSAR Version Major Number     */
#define	DMA_AR_MINOR_VERSION	0	/**< AUTOSAR Version Minor Number     */
#define	DMA_AR_PATCH_VERSION	2	/**< AUTOSAR Version Patch Number     */

/*
 * Dma.h shall include Std_Types.h.
 */
#include "Std_Types.h"

/* DMA Driver Data Type
 *
 * Dma_DataType defines the type of application data buffer elements.
 *
 * Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *
 * It shall be provided for external use.
 *
 * This is implementation specific but not all values may be valid within the
 * type.
 *
 * This type shall be chosen in order to have the most efficient implementation
 * on a specific microcontroller platform.
 *
 * typedef uint<8,16,32> Dma_DataType; <- To be defined in Dma_Cfg.h
 */

/* DMA Driver Channel Type.
 *
 * The type Dma_ChannelType specifies the identification (ID) for a DMA Channel.
 *
 * Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *
 * It shall be provided for external use.
 *
 * This is implementation specific but not all values may be valid within the
 * type.
 *
 * This type shall be chosen in order to have the most efficient implementation
 * on a specific microcontroller platform.
 *
 * typedef uint<8,16,32> Dma_ChannelType; <- To be defined in Dma_Cfg.h
 */

/* DMA Driver Number of Elements Type
 *
 * The type Dma_NumberOfElementsType is used for defining the number of elements
 * to transfer on a DMA Channel.
 *
 * Type is uint8,uint16,uint32 and Range is 8 to 32 bit.
 *
 * It shall be provided for external use.
 *
 * This is implementation specific but not all values may be valid within the
 * type.
 *
 * This type shall be chosen in order to have the most efficient implementation
 * on a specific microcontroller platform.
 *
 * typedef uint<8,16,32> Dma_NumberOfElementsType; <- To be defined in Dma_Cfg.h
 */

/* DMA Entry Type
 *
 * The type Dma_EntryType defines the type for a specific DMA Channel transfer
 * entry when the Channel is configurable for multiple transfers.
 *
 * Type is struct.
 *
 * It shall be provided for external use.
 *
 * This is implementation specific.
 *
 * This type shall be chosen in order to have the most efficient implementation
 * on a specific microcontroller platform.
 *
 * typedef struct Dma_EntryType; <- To be defined in Dma_Cfg.h
 */

/** @brief	DMA Channel Software Transfer End Notification Callback Function
 *  		Pointer
 *
 *  Callback routine provided by the user to notify the caller that a transfer
 *  on a DMA Channel Software has been finished.
 *
 *  The operation <tt>Dma_SoftwareTransferEndNotification_<Channel>()</tt> is
 *  Re-entrant.
 *
 *  For implement the call back function other modules are required to provide
 *  the routines in the expected manner, as function pointers defined within the
 *  initialization data structure (<tt>Dma_ConfigType</tt>).
 *
 *  The callback notification
 *  <tt>Dma_SoftwareTransferEndNotification_<Channel>()</tt> shall have no
 *  parameters and no return value.
 *
 *  If a callback notification is configured as null pointer, no callback shall
 *  be executed.
 *
 *  If the <tt>Dma_SoftwareTransferEndNotification_<Channel>()</tt> is
 *  configured (i.e. not a null pointer), the DMA Driver shall call the
 *  configured callback notification at the end of a DMA Channel Software
 *  transfer.
 *
 *  @note	This routine might be called on interrupt level, depending on
 *  		the calling function.
 */
typedef void (*Dma_SoftwareTransferEndNotification)(
  void
);

/** @brief	DMA Channel Transfer Error Notification Callback Function
 *  		Pointer
 *
 *  Callback routine provided by the user to notify the caller that a transfer
 *  on a DMA Channel has not been finished due to a transfer error.
 *
 *  The operation <tt>Dma_TransferErrorNotification_<Channel>()</tt> is
 *  Re-entrant.
 *
 *  For implement the call back function other modules are required to provide
 *  the routines in the expected manner, as function pointers defined within the
 *  initialization data structure (<tt>Dma_ConfigType</tt>).
 *
 *  The callback notification <tt>Dma_TransferErrorNotification_<Channel>()</tt>
 *  shall have no parameters and no return value.
 *
 *  If a callback notification is configured as null pointer, no callback shall
 *  be executed.
 *
 *  If the <tt>Dma_TransferErrorNotification_<Channel>()</tt> is configured
 *  (i.e. not a null pointer), the DMA Driver shall call the configured callback
 *  notification when an error occurs during a transfer on DMA Channel.
 *
 *  @note	This routine might be called on interrupt level, depending on
 *  		the calling function.
 */
typedef void (*Dma_TransferErrorNotification)(
  void
);

/*
 * Dma.h shall include Dma_Cfg.h.
 */
#include "Dma_Cfg.h"

#if	( DMA_DEV_ERROR_DETECT == STD_ON )
/*
 * Development error values are of type uint8.
 *
 * The following errors shall be detectable by the DMA driver depending on its
 * build version (development / production).
 *
 * Additional errors that are detected because of specific implementation and/or
 * specific hardware properties shall be added to the DMA device specific
 * implementation description.
 */

/** @brief	Pointer is <tt>NULL_PTR</tt>.
 *
 *   *
 *  DMA driver shall be able to detect the error <tt>DMA_E_PARAM_POINTER</tt>
 *  (0x0A) when API service called with a pointer parameter whose value is
 *  <tt>NULL_PTR</tt>.
 */
#define	DMA_E_PARAM_POINTER		0x0A

/** @brief	Invalid Channel
 *
 *  DMA driver shall be able to detect the error <tt>DMA_E_PARAM_CHANNEL</tt>
 *  (0x0B) when API service called with wrong parameter.
 */
#define	DMA_E_PARAM_CHANNEL		0x0B

/** @brief	Invalid Address
 *
 *  DMA driver shall be able to detect the error <tt>DMA_E_PARAM_ADDRESS</tt>
 *  (0x0C) when API service called with wrong parameter.
 */
#define	DMA_E_PARAM_ADDRESS		0x0C

/** @brief	Invalid Lenght
 *
 *  DMA driver shall be able to detect the error <tt>DMA_E_PARAM_SIZE</tt>
 *  (0x0D) when API service called with wrong parameter.
 */
#define	DMA_E_PARAM_SIZE		0x0D

/** @brief	DMA Module Not Initialized
 *
 *  DMA driver shall be able to detect the error <tt>DMA_E_UNINIT</tt> (0x0E)
 *  when API service used without module initialization.
 */
#define	DMA_E_UNINIT			0x0E

/** @brief	DMA Module Already Initialized
 *
 *  DMA driver shall be able to detect the error
 *  <tt>DMA_E_ALREADY_INITIALIZED</tt> (0x0F) when API <tt>Dma_Init()</tt>
 *  service called while the DMA driver has already been initialized time.
 */
#define	DMA_E_ALREADY_INITIALIZED	0x0F

/** @brief	DMA Channel State
 *
 * DMA Driver shall be able to detect the error <tt>DMA_E_CHANNEL_STATE</tt>
 * (0x10) when services called DMA Channel in a wrong state.
 */
#define	DMA_E_CHANNEL_STATE		0x10

/** @brief	DMA Channel Transfer Pending
 *
 * DMA Driver shall be able to detect the error <tt>DMA_E_CHANNEL_PENDING</tt>
 * (0x10) when services called DMA Channel on which a tranfer is pending.
 */
#define	DMA_E_CHANNEL_PENDING		0x11

#endif	/* ( DMA_DEV_ERROR_DETECT == STD_ON ) */

/** @brief	DMA Driver Configuration Parameters
 *
 *  The description of the type <tt>Dma_ConfigType</tt> is implementation
 *  specific and it shall be provided for external use.
 *
 *  The type <tt>Dma_ConfigType</tt> is an external data structure and shall
 *  contain the initialization data for the DMA Driver.
 *  It shall contain:
 *  - MCU dependent properties for DMA HW units
 *  - Definition of Channels
 *
 *  For the type <tt>Dma_ConfigType</tt>, the definition for each Channel shall
 *  contain:
 *  - Channel Identifier.
 *  - Channel Peripheral Assignment.
 *  - Channel Source Address Boudaries.
 *  - Channel Destination Address Boudaries.
 *  - Channel Notifications Call-Backs.
 *  - Channel Harware Specific Configuration.
 *
 *  For the type <tt>Dma_ConfigType</tt>, the configuration will map the
 *  Channels to the different hardware units and the devices.
 */
extern const Dma_ConfigType	Dma_Config[];

#if	( DMA_STATUS_API == STD_ON )
/** @brief	DMA Driver Status Type
 *
 *  The type <tt>Dma_StatusType</tt> defines a range of specific status for DMA
 *  Driver. It informs about the DMA Driver status or specified DMA Hardware
 *  microcontroller peripheral.
 *
 *  The type <tt>Dma_StatusType</tt> can be obtained calling the API service
 *  <tt>Dma_GetStatus()</tt>.
 *
 *  After reset, the type <tt>Dma_StatusType</tt> shall have the default value
 *  <tt>DMA_UNINIT</tt> with the numeric value 0.
 *
 *  API service <tt>Dma_GetStatus()</tt> shall return <tt>DMA_UNINIT</tt> when
 *  the DMA Driver is not initialized or not usable.
 *
 *  API service <tt>Dma_GetStatus()</tt> shall return <tt>DMA_IDLE</tt> when the
 *  DMA Driver is not currently performing any transfer.
 *
 *  API service <tt>Dma_GetStatus()</tt> shall return <tt>DMA_BUSY</tt> when the
 *  DMA Driver is performing a DMA transfer.
 */
typedef enum {
  DMA_UNINIT = 0,	/**< The DMA Driver is not initialized or not usabe.  */
  DMA_IDLE,		/**< The DMA Driver is not currently performing any
  			 *   transfer.					      */
  DMA_BUSY		/**< The DMA Driver is performing a DMA transfer.     */
}	Dma_StatusType;
#endif	/* ( DMA_STATUS_API == STD_ON ) */

#if	( DMA_CHANNEL_RESULT_API == STD_ON )
/** @brief	DMA Channel Result Type
 *
 *  The type <tt>Dma_ChannelResultType</tt> defines a range of specific Channels
 *  status for DMA Driver.
 *
 *  The type <tt>Dma_ChannelResultType</tt> it informs about a DMA Channel
 *  status and can be obtained calling the API service
 *  <tt>Dma_GetChannelResult()</tt> with the Channel ID.
 *
 *  After reset, the type <tt>Dma_ChannelResultType</tt> shall have the default
 *  value <tt>DMA_CHANNEL_OK</tt> with the numeric value 0.
 *
 *  The function <tt>Dma_GetChannelResult()</tt> shall return
 *  <tt>DMA_CHANNEL_OK</tt> when the last DMA transfer on the Channel has been
 *  finished.
 */
typedef enum {
  DMA_CHANNEL_OK,	/**< The last transfer on the DMA Channel has been
  			 *   finished successfully.			      */
  DMA_CHANNEL_PENDING,	/**< The DMA Driver is performing a transfer on the DMA
  			 *   Channel. The meaning of this status is equal to
  			 *   <tt>DMA_BUSY</tt>.				      */
  DMA_CHANNEL_FAILED,	/**< The last transfer on the DMA Channel has failed. */
  DMA_CHANNEL_CANCELED	/**< The last transfer on the DMA Channel has been
  			 *   canceled by user.				      */
}	Dma_ChannelResultType;
#endif	/* ( DMA_CHANNEL_RESULT_API == STD_ON ) */

/*
 * Service ID's
 */
#if	( DMA_DEV_ERROR_DETECT == STD_ON )

#define	DMA_INIT_SERVICE_ID				0x00
#define	DMA_DE_INIT_SERVICE_ID				0x01
#define	DMA_ENABLE_CHANNEL_SERVICE_ID			0x02
#define	DMA_DISABLECHANNEL_SERVICE_ID			0x03
#define	DMA_GET_STATUS_SERVICE_ID			0x04
#define	DMA_GET_CHANNEL_RESULT_SERVICE_ID		0x05
#define	DMA_TRANSFER_REQUEST_SERVICE_ID			0x06
#define	DMA_TRANSFER_SETUP_SERVICE_ID			0x07
#define	DMA_PING_PONG_TRANSFER_SETUP_SERVICE_ID		0x08
#define	DMA_PING_PONG_TRANSFER_UPDATE_SERVICE_ID	0x09
#define	DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID	0x0A
#define	DMA_SCATTER_GATHER_TRANSFER_SETUP_SERVICE_ID	0x0B
#define	DMA_GET_VERSION_INFO_SERVICE_ID			0x0C

#endif	/* ( DMA_DEV_ERROR_DETECT == STD_ON ) */

/** @brief	DMA Driver Initialization
 *  @param	ConfigPtr	Pointer to configuration set.
 *  @return	None
 *
 *  This service initializes the DMA driver.
 *
 *  Service 0x00
 *
 *  The operation <tt>Dma_Init()</tt> is Non Re-entrant.
 *
 *  The function <tt>Dma_Init()</tt> provides the service for DMA
 *  initialization.
 *
 *  The function <tt>Dma_Init()</tt> shall initialize all DMA relevant registers
 *  with the values of the structure referenced by the parameter
 *  <tt>ConfigPtr</tt>.
 *
 *  The function <tt>Dma_Init()</tt> shall define default values for required
 *  parameters of the structure referenced by the ConfigPtr.
 *
 *  After the module initialization using the function <tt>Dma_Init()</tt>, the
 *  DMA Driver shall set its state to <tt>DMA_IDLE</tt> and the Channels result
 *  to <tt>DMA_CHANNEL_OK</tt>.
 *
 *  A re-initialization of a DMA Driver by executing the
 *  <tt>Dma_Init()</tt> function requires a de-initialization before by
 *  executing a <tt>Dma_DeInit()</tt>.
  *
 *  If development error detection for the DMA module is enabled:
 *   - If <tt>VARIANT-POST-BUILD</tt> is supported by implementation and the
 *     parameter <tt>ConfigPtr</tt> is a <tt>NULL_PTR</tt> pointer, the function
 *     <tt>Dma_Init()</tt> shall raise the error <tt>DMA_E_PARAM_POINTER</tt>.
 *   - If <tt>VARIANT-POST-BUILD</tt> is not supported by implementation and the
 *     parameter <tt>ConfigPtr</tt> is not a <tt>NULL_PTR</tt> pointer, the
 *     function <tt>Dma_Init()</tt> shall raise the error
 *     <tt>DMA_E_PARAM_POINTER</tt>.
 *   - If the function <tt>Dma_Init()</tt> is called while the DMA driver is
 *     already initialized, the function <tt>Dma_Init()</tt> shall raise
 *     development error <tt>DMA_E_ALREADY_INITIALIZED</tt> and return without
 *     any action.
 */
void Dma_Init(
  const Dma_ConfigType * ConfigPtr
);

#if	( DMA_DE_INIT_API == STD_ON )
/** @brief	DMA Driver De-Initialization.
 *  @return	
 *  	- <tt>E_OK</tt>:	De-initialisation command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	De-initialisation command has not been accepted.
 *
 *  This service de-initializes the DMA driver.
 *
 *  Service 0x01
 *
 *  The operation <tt>Dma_DeInit()</tt> is Non Re-entrant.
 *
 *  When the API <tt>Dma_DeInit()</tt> has been accepted the return value of
 *  this function shall be <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_DeInit()</tt> has not been accepted the return value of
 *  this function shall be <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_DeInit()</tt> provides the service for DMA
 *  de-initialization.
 *
 *  The function <tt>Dma_DeInit()</tt> shall de-initialize DMA Driver.
 *
 *  In case of the DMA Driver state is not <tt>DMA_BUSY</tt>, the
 *  deInitialization function shall put already initialized microcontroller DMA
 *  into the same state such as Power On Reset.
 *
 *  The function call <tt>Dma_DeInit()</tt> shall be rejected if the status of
 *  DMA Driver is <tt>DMA_BUSY</tt>.
 *
 *  After the module de-initialization using the function <tt>Dma_DeInit()</tt>,
 *  the DMA Driver shall set its state to <tt>DMA_UNINIT</tt>.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_DeInit()</tt> is called, otherwise <tt>E_NOT_OK</tt> shall be
 *  returned.
 *
 *  If development error detection for the DMA module is enabled and the
 *  function <tt>Dma_DeInit()</tt> is called before the DMA module has been
 *  initialized, the function <tt>Dma_DeInit()</tt> shall raise development
 *  error <tt>DMA_E_UNINIT</tt> and return without any action.
 *
 *  The function <tt>Dma_DeInit()</tt> shall be configurable <tt>ON</tt> /
 *  <tt>OFF</tt> by configuration parameter <tt>DMA_DE_INIT_API</tt>.
 */
Std_ReturnType Dma_DeInit(
  void
);
#endif	/* ( DMA_DE_INIT_API == STD_ON ) */

/** @brief	Channel Enabling
 *  @param	Channel	DMA channel to be addressed.
 *  @return	
 *  	- <tt>E_OK</tt>:	Enabling Command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Enabling Command has not been accepted.
 *
 *  The service instructs the driver to enable DMA transfers on the addressed
 *  DMA channel.
 *
 *  Service 0x02
 *
 *  The operation <tt>Dma_EnableChannel()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_EnableChannel()</tt> has been accepted the return value
 *  of this function shall be <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_EnableChannel()</tt> has not been accepted the return
 *  value of this function shall be <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_EnableChannel()</tt> provides the service to enable DMA
 *  transfers on the addressed DMA channel.
 *
 *  The function <tt>Dma_EnableChannel()</tt> shall enable DMA transfers on the
 *  addressed DMA channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_EnableChannel()</tt> is called, otherwise <tt>E_NOT_OK</tt> shall be
 *  returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_EnableChannel()</tt> is called before the DMA
 *    module was initialized, the function <tt>Dma_EnableChannel()</tt> shall
 *    raise the development error <tt>DMA_E_UNINIT</tt> and return without any
 *    action.
 *  - the function <tt>Dma_EnableChannel()</tt> shall raise the development
 *    error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is invalid or
 *    the channel is already enabled.
 */
Std_ReturnType Dma_EnableChannel(
  Dma_ChannelType	Channel
);

#if	( DMA_DISABLE_CHANNEL_API == STD_ON )
/** @brief	Channel Disabling
 *  @param	Channel	DMA channel to be addressed.
 *  @return	
 *  	- <tt>E_OK</tt>:	Disabling Command has been accepted.
 *  	- <tt>E_NOT_OK</tt>:	Disabling Command has not been accepted.
 *
 *  The service instructs the driver to disable DMA transfers on the addressed
 *  DMA channel.
 *
 *  Service 0x03
 *
 *  The operation <tt>Dma_DisableChannel()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_DisableChannel()</tt> has been accepted the return
 *  value of this function shall be <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_DisableChannel()</tt> has not been accepted the return
 *  value of this function shall be <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_DisableChannel()</tt> provides the service to disable
 *  DMA transfers on the addressed DMA channel.
 *
 *  The function <tt>Dma_DisableChannel()</tt> shall disable DMA transfers on
 *  the addressed DMA channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_DisableChannel()</tt> is called, otherwise <tt>E_NOT_OK</tt> shall
 *  be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_DisableChannel()</tt> shall terminate ongoing transfers
 *  of prior transfer requests, even if the transfer is unsuccessfully
 *  completed.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_DisableChannel()</tt> is called before the DMA
 *    module was initialized, the function <tt>Dma_DisableChannel()</tt> shall
 *    raise the development error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_DisableChannel()</tt> shall raise the development
 *    error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is invalid or
 *    the channel is already disabled.
 *
 *  The function <tt>Dma_DisableChannel()</tt> shall be configurable <tt>ON</tt>
 *  / <tt>OFF</tt> by configuration parameter <tt>DMA_DISABLE_CHANNEL_API</tt>.
 */
Std_ReturnType Dma_DisableChannel(
  Dma_ChannelType	Channel
);
#endif	/* ( DMA_DISABLE_CHANNEL_API == STD_ON ) */

#if	( DMA_STATUS_API == STD_ON )
/** @brief	DMA Driver Status Retrieval
 *  @return	DMA Driver software module status.
 *
 *  This service returns the DMA Driver software module status.
 *
 *  Service 0x04
 *
 *  The operation <tt>Dma_GetStatus()</tt> is Re-entrant.
 *
 *  The function <tt>Dma_GetStatus()</tt> shall return the DMA Driver software
 *  module status.
 *
 *  The function <tt>Dma_GetStatus()</tt> shall be configurable <tt>ON</tt> /
 *  <tt>OFF</tt> by configuration parameter <tt>DMA_STATUS_API</tt>.
 */
Dma_StatusType Dma_GetStatus(
  void
);
#endif	/* ( DMA_STATUS_API == STD_ON ) */

#if	( DMA_CHANNEL_RESULT_API == STD_ON )
/** @brief	Channel Result Retrieval
 *  @param	Channel	DMA channel to be addressed.
 *  @return	Last DMA transfer result on the specified Channel.
 *
 *  This service returns the last DMA transfer result on the addressed DMA
 *  Channel.
 *
 *  Service 0x05
 *
 *  The operation <tt>Dma_GetChannelResult()</tt> is Re-entrant.
 *
 *  The function <tt>Dma_GetChannelResult()</tt> service returns the last DMA
 *  transfer result on the addressed DMA Channel.
 *
 *  The DMA Driver's environment shall call the function
 *  <tt>Dma_GetChannelResult()</tt> to inquire whether the Channel transfer has
 *  succeeded (<tt>DMA_CHANNEL_OK</tt>) or failed (<tt>DMA_CHANNEL_FAILED</tt>).
 *
 *  Every new channel transfer that has been accepted by the DMA Driver
 *  overwrites the previous channel result with <tt>DMA_CHANNEL_PENDING</tt>.
 *
 *  If the DMA Driver has not been initialized before the function
 *  <tt>Dma_GetChannelResult()</tt> is called or the channel parameter is
 *  invalid or not configured, the return value MUST BE
 *  <tt>DMA_CHANNEL_FAILED</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_GetChannelResult()</tt> is called before the DMA
 *    module was initialized, the function <tt>Dma_GetChannelResult()</tt> shall
 *    raise the development error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_GetChannelResult()</tt> shall raise the development
 *    error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is invalid or
 *    not configured.
 *
 *  The function <tt>Dma_GetChannelResult()</tt> shall be configurable
 *  <tt>ON</tt> / <tt>OFF</tt> by configuration parameter
 *  <tt>DMA_CHANNEL_RESULT_API</tt>.
 */
Dma_ChannelResultType Dma_GetChannelResult(
  Dma_ChannelType	Channel
);
#endif	/* ( DMA_CHANNEL_RESULT_API == STD_ON ) */

#if	( DMA_TRANSFER_REQUEST_API == STD_ON )
/** @brief	Transfer Request.
 *  @param	Channel	DMA channel to be addressed.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transfer Request command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transfer Request command has not been accepted
 *
 *  Service to "trigger" a Transfer Request on the addressed DMA Channel.
 *
 *  Service 0x06
 *
 *  The operation <tt>Dma_TransferRequest()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_TransferRequest()</tt> command has been accepted the
 *  function shall return the value <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_TransferRequest()</tt> command has not been accepted
 *  the function shall return the value <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_TransferRequest()</tt> provides service to "trigger" a
 *  Tranfer Request on the addressed DMA Channel.
 *
 *  The function <tt>Dma_TransferRequest()</tt> shall take over the given
 *  parameter, trigger a transfer request on a DMA Channel, set the DMA Driver
 *  status to <tt>DMA_BUSY</tt>, set the channel result to
 *  <tt>DMA_CHANNEL_PENDING</tt> and return.
 *
 *  When the function <tt>Dma_TransferRequest()</tt> is called, the DMA Driver
 *  shall handle the DMA Channel results. Result shall be
 *  <tt>DMA_CHANNEL_PENDING</tt> when the transfer on the DMA Channel is
 *  started.
 *
 *  When the function <tt>Dma_TransferRequest()</tt> is called, the DMA Driver
 *  shall handle the DMA Channel results. Result shall be
 *  <tt>DMA_CHANNEL_OK</tt> when the transfer on the DMA Channel is success.
 *
 *  When the function <tt>Dma_TransferRequest()</tt> is called, the DMA Driver
 *  shall handle the DMA Channel results. Result shall be
 *  <tt>DMA_CHANNEL_FAILED</tt> when the transfer on the DMA Channels is failed.
 *
 *  At the end of a transfer initiated by the function
 *  <tt>Dma_TransferRequest()</tt> and if configured, the DMA Driver shall
 *  invoke the transfer end notification call-back function after the transfer
 *  on DMA Channel ends if this one is also configured.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_TransferRequest()</tt> is called, otherwise <tt>E_NOT_OK</tt> shall
 *  be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  When the function <tt>Dma_TransferRequest()</tt> is called and the requested
 *  DMA Channel is not enabled, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_TransferRequest()</tt> is called and the requested
 *  DMA Channel is already in state <tt>DMA_CHANNEL_PENDING</tt>, the DMA Driver
 *  shall not take in account this new request and this function shall return
 *  with value <tt>E_NOT_OK</tt>, in this case.
 *
 *  The function <tt>Dma_TransferRequest()</tt> is pre-compile time selectable
 *  by the configuration parameter <tt>DMA_TRANSFER_REQUEST_API</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_TransferRequest()</tt> is called before the DMA
 *    module was initialized, the function <tt>Dma_TransferRequest()</tt> shall
 *    raise the development error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_TransferRequest()</tt> shall raise the development
 *    error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is invalid or
 *    not configured.
 *  - the function <tt>Dma_TransferRequest()</tt> shall raise the development
 *    error <tt>DMA_E_CHANNEL_STATE</tt> if the requested DMA Channel is
 *    not enabled.
 *  - if the function <tt>Dma_TransferRequest()</tt> is called and the requested
 *    DMA Channel is already in state <tt>DMA_CHANNEL_PENDING</tt> the DMA
 *    Driver shall raise the development error <tt>DMA_E_CHANNEL_PENDING</tt>.
 */
Std_ReturnType Dma_TransferRequest(
  Dma_ChannelType	Channel
);
#endif	/* ( DMA_TRANSFER_REQUEST_API == STD_ON ) */

/** @brief	Transfer Setup.
 *  @param	Channel		DMA channel to be addressed.
 *  @param	SrcAddrPtr	Source Address Pointer.
 *  @param	DstAddrPtr	Destination Address Pointer.
 *  @param	TransferSize	Number of Elements to transfer.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transfer Setup command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transfer Setup command has not been accepted
 *
 *  Service to Set-up Basic or Auto DMA Transfer on the addressed DMA Channel.
 *
 *  Service 0x07
 *
 *  The operation <tt>Dma_TransferSetup()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_TransferSetup()</tt> command has been accepted the
 *  function shall return the value <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_TransferSetup()</tt> command has not been accepted
 *  the function shall return the value <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_TransferSetup()</tt> provides service to Set-up Basic
 *  or Auto DMA transfer on addressed DMA Channel.
 *
 *  The function <tt>Dma_TransferSetup()</tt> shall set-up Basic or Auto DMA
 *  transfer on addressed DMA Channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_TransferRequest()</tt> is called, otherwise <tt>E_NOT_OK</tt> shall
 *  be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  When the function <tt>Dma_TransferSetup()</tt> is called and the addressed
 *  DMA Channel is enabled, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_TransferSetup()</tt> is called and the Number of
 *  Elements to transfer is equal to 0 or greater than the addressed channel
 *  transfer capability, the DMA Driver shall not take in account this request
 *  and this function shall return with value <tt>E_NOT_OK</tt>, in this case.
 *
 *  When the function <tt>Dma_TransferSetup()</tt> is called and the Address
 *  Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_TransferSetup()</tt> is called and the Address
 *  Pointers are out of DMA Channal address boundaries, the DMA Driver shall not
 *  take in account this request and this function shall return with value
 *  <tt>E_NOT_OK</tt>, in this case.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_TransferSetup()</tt> is called before the DMA
 *    module was initialized, the DMA Driver shall raise the development error
 *    <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_TransferSetup()</tt> shall raise the development
 *    error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is invalid or
 *    not configured, or the channel parameter is configured with wrong transfer
 *    mode.
 *  - if the function <tt>Dma_TransferSetup()</tt> is called and the addressed
 *    DMA Channel is enabled, the DMA Driver shall raise the development error
 *    <tt>DMA_E_CHANNEL_STATE</tt>.
 *  - if the function <tt>Dma_TransferSetup()</tt> is called and the Number of
 *    Elements to transfer is equal to 0 or greater than the addressed channel
 *    transfer capability, the DMA Driver shall raise the development error
 *    <tt>DMA_E_PARAM_SIZE</tt>.
 *  - if the function <tt>Dma_TransferSetup()</tt> is called and the Address
 *    Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall raise the development
 *    error <tt>DMA_E_PARAM_POINTER</tt>.
 *  - if the function <tt>Dma_TransferSetup()</tt> is called and the Address
 *    Pointers are out of DMA Channal address boundaries, the DMA Driver shall
 *    raise the development error <tt>DMA_E_PARAM_ADDRESS</tt>.
 */
Std_ReturnType Dma_TransferSetup(
  Dma_ChannelType		Channel,
  const Dma_DataType *		SrcAddrPtr,
  const Dma_DataType *		DstAddrPtr,
  Dma_NumberOfElementsType	TransferSize
);

#if	( DMA_PING_PONG_API == STD_ON )
/** @brief	Ping-Pong Transfer Setup.
 *  @param	Channel			DMA channel to be addressed.
 *  @param	PingSrcAddrPtr		Ping Source Address Pointer.
 *  @param	PingDstAddrPtr		Ping Destination Address Pointer.
 *  @param	PingTransferSize	Ping Number of Elements to transfer.
 *  @param	PongSrcAddrPtr		Pong Source Address Pointer.
 *  @param	PongDstAddrPtr		Pong Destination Address Pointer.
 *  @param	PongTransferSize	Pong Number of Elements to transfer.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transfer Setup command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transfer Setup command has not been accepted
 *
 *  Service to set-up Ping-Pong DMA Transfer on the addressed DMA Channel.
 *
 *  Service 0x08
 *
 *  The operation <tt>Dma_PingPongTransferSetup()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_PingPongTransferSetup()</tt> command has been accepted
 *  the function shall return the value <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_PingPongTransferSetup()</tt> command has not been
 *  accepted the function shall return the value <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_PingPongTransferSetup()</tt> provides service to set-up
 *  Ping-Pong DMA Tranfer on the addressed DMA Channel.
 *
 *  The function <tt>Dma_PingPongTransferSetup()</tt> shall set-up Ping-Pong DMA
 *  transfer on addressed DMA Channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_PingPongTransferSetup()</tt> is called, otherwise <tt>E_NOT_OK</tt>
 *  shall be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  When the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *  addressed DMA Channel is enabled, the DMA Driver shall not take in account
 *  this request and this function shall return with value <tt>E_NOT_OK</tt>, in
 *  this case.
 *
 *  When the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *  Number of Elements to transfer is equal to 0 or greater than the addressed
 *  channel transfer capability, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *  Address Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall not take in
 *  account this request and this function shall return with value
 *  <tt>E_NOT_OK</tt>, in this case.
 *
 *  When the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *  Address Pointers are out of DMA Channal address boundaries the DMA Driver
 *  shall not take in account this request and this function shall return with
 *  value <tt>E_NOT_OK</tt>, in this case.
 *
 *  The function <tt>Dma_PingPongTransferSetup()</tt> is pre-compile time
 *  selectable by the configuration parameter <tt>DMA_PING_PONG_API</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_PingPongTransferSetup()</tt> is called before the
 *    DMA module was initialized, the DMA Driver shall raise the development
 *    error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_PingPongTransferSetup()</tt> shall raise the
 *    development error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is
 *    invalid or not configured, or the channel parameter is configured with
 *    wrong transfer mode.
 *  - if the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *    addressed DMA Channel is enabled, the DMA Driver shall raise the
 *    development error <tt>DMA_E_CHANNEL_STATE</tt>.
 *  - if the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *    Number of Elements to transfer is equal to 0 or greater than the addressed
 *    channel transfer capability, the DMA Driver shall raise the development
 *    error <tt>DMA_E_PARAM_SIZE</tt>.
 *  - if the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *    Address Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall raise the
 *    development error <tt>DMA_E_PARAM_POINTER</tt>.
 *  - if the function <tt>Dma_PingPongTransferSetup()</tt> is called and the
 *    Address Pointers are out of DMA Channal address boundaries, the DMA Driver
 *    shall raise the development error <tt>DMA_E_PARAM_ADDRESS</tt>.
 */
Std_ReturnType Dma_PingPongTransferSetup(
  Dma_ChannelType		Channel,
  const Dma_DataType *		PingSrcAddrPtr,
  const Dma_DataType *		PingDstAddrPtr,
  Dma_NumberOfElementsType	PingTransferSize,
  const Dma_DataType *		PongSrcAddrPtr,
  const Dma_DataType *		PongDstAddrPtr,
  Dma_NumberOfElementsType	PongTransferSize
);

/** @brief	Ping-Pong Transfer Update.
 *  @param	Channel		DMA channel to be addressed.
 *  @param	SrcAddrPtr	Source Address Pointer.
 *  @param	DstAddrPtr	Destination Address Pointer.
 *  @param	TransferSize	Number of Elements to transfer.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transfer Update command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transfer Update command has not been accepted
 *
 *  Service to Update Ping-Pong DMA Transfer on the addressed DMA Channel.
 *
 *  Service 0x09
 *
 *  The operation <tt>Dma_PingPongTransferUpdate()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_PingPongTransferUpdate()</tt> command has been accepted
 *  the function shall return the value <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_PingPongTransferUpdate()</tt> command has not been
 *  accepted the function shall return the value <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_PingPongTransferUpdate()</tt> provides service to
 *  Update Ping-Pong DMA Tranfer on the addressed DMA Channel.
 *
 *  The function <tt>Dma_PingPongTransferUpdate()</tt> shall update Ping-Pong
 *  DMA transfer on addressed DMA Channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_PingPongTransferUpdate()</tt> is called, otherwise <tt>E_NOT_OK</tt>
 *  shall be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  When the function <tt>Dma_TransferSetup()</tt> is called and the addressed
 *  DMA Channel is disabled, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *  Number of Elements to transfer is equal to 0 or greater than the addressed
 *  channel transfer capability, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *  Address Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall not take in
 *  account this request and this function shall return with value
 *  <tt>E_NOT_OK</tt>, in this case.
 *
 *  When the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *  Address Pointers are out of DMA Channal address boundaries the DMA Driver
 *  shall not take in account this request and this function shall return with
 *  value <tt>E_NOT_OK</tt>, in this case.
 *
 *  The function <tt>Dma_PingPongTransferUpdate()</tt> is pre-compile time
 *  selectable by the configuration parameter <tt>DMA_PING_PONG_API</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_PingPongTransferUpdate()</tt> is called before the
 *    DMA module was initialized, the DMA Driver shall raise the development
 *    error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_PingPongTransferUpdate()</tt> shall raise the
 *    development error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is
 *    invalid or not configured, or the channel parameter is configured with
 *    wrong transfer mode.
 *  - if the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *    addressed DMA Channel is disabled, the DMA Driver shall raise the
 *    development error <tt>DMA_E_CHANNEL_STATE</tt>.
 *  - if the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *    Number of Elements to transfer is equal to 0 or greater than the addressed
 *    channel transfer capability, the DMA Driver shall raise the development
 *    error <tt>DMA_E_PARAM_SIZE</tt>.
 *  - if the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *    Address Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall raise the
 *    development error <tt>DMA_E_PARAM_POINTER</tt>.
 *  - if the function <tt>Dma_PingPongTransferUpdate()</tt> is called and the
 *    Address Pointers are out of DMA Channal address boundaries, the DMA Driver
 *    shall raise the development error <tt>DMA_E_PARAM_ADDRESS</tt>.
 */
Std_ReturnType Dma_PingPongTransferUpdate(
  Dma_ChannelType		Channel,
  const Dma_DataType *		SrcAddrPtr,
  const Dma_DataType *		DstAddrPtr,
  Dma_NumberOfElementsType	TransferSize
);

#endif	/* ( DMA_PING_PONG_API == STD_ON ) */

#if	( DMA_SCATTER_GATHER_API == STD_ON )

/** @brief	Scatter-Gather Entry Setup.
 *  @param	Channel		DMA channel to be addressed.
 *  @param	EntryPtr	Pointer of Scatter-Gather Entry to be Setup.
 *  @param	SrcAddrPtr	Source Address Pointer.
 *  @param	DstAddrPtr	Destination Address Pointer.
 *  @param	TransferSize	Number of Elements to transfer.
 *  @param	LastEntry	
 *  	- <tt>TRUE</tt>:	Scatter-Gather Last Entry.
 *  	- <tt>FALSE</tt>:	Scatter-Gather Intermediate Entry.
 *  @return	
 *  	- <tt>E_OK</tt>:	Setup command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Setup command has not been accepted
 *
 *  Service to set-up a Scatter-Gather Transfer Entry on the addressed DMA
 *  Channel.
 *
 *  Service 0x0A
 *
 *  The operation <tt>Dma_ScatterGatherEntrySetup()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_ScatterGatherEntrySetup()</tt> command has been
 *  accepted the function shall return the value <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_ScatterGatherEntrySetup()</tt> command has not been
 *  accepted the function shall return the value <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_ScatterGatherEntrySetup()</tt> provides service to
 *  set-up a Scatter-Gather Transfer Entry on the addressed DMA Channel.
 *
 *  The function <tt>Dma_ScatterGatherEntrySetup()</tt> shall set-up a
 *  Scatter-Gather Transfer Entry on the addressed DMA Channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_ScatterGatherEntrySetup()</tt> is called, otherwise
 *  <tt>E_NOT_OK</tt> shall be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  When the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called and the
 *  Number of Elements to transfer is equal to 0 or greater than the addressed
 *  channel transfer capability, the DMA Driver shall not take in account this
 *  request and this function shall return with value <tt>E_NOT_OK</tt>, in this
 *  case.
 *
 *  When the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called and the
 *  Entry or Address Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall not
 *  take in account this request and this function shall return with value
 *  <tt>E_NOT_OK</tt>, in this case.
 *
 *  When the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called and the
 *  Address Pointers are out of DMA Channal address boundaries, the DMA Driver
 *  shall not take in account this request and this function shall return with
 *  value <tt>E_NOT_OK</tt>, in this case.
 *
 *  The function <tt>Dma_ScatterGatherEntrySetup()</tt> is pre-compile time
 *  selectable by the configuration parameter <tt>DMA_SCATTER_GATHER_API</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called before
 *    the DMA module was initialized, the DMA Driver shall raise the development
 *    error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_ScatterGatherEntrySetup()</tt> shall raise the
 *    development error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is
 *    invalid or not configured, or the channel parameter is configured with
 *    wrong transfer mode.
 *  - if the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called and the
 *    Number of Elements to transfer is equal to 0 or greater than the addressed
 *    channel transfer capability, the DMA Driver shall raise the development
 *    error <tt>DMA_E_PARAM_SIZE</tt>.
 *  - if the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called and the
 *    Entry or Address Pointers are <tt>NULL_PTR</tt>, the DMA Driver shall
 *    raise the development error <tt>DMA_E_PARAM_POINTER</tt>.
 *  - if the function <tt>Dma_ScatterGatherEntrySetup()</tt> is called and the
 *    Address Pointers are out of DMA Channal address boundaries, the DMA Driver
 *    shall raise the development error <tt>DMA_E_PARAM_ADDRESS</tt>.
 */
Std_ReturnType Dma_ScatterGatherEntrySetup(
  Dma_ChannelType		Channel,
  Dma_EntryType *		EntryPtr,
  const Dma_DataType *		SrcAddrPtr,
  const Dma_DataType *		DstAddrPtr,
  Dma_NumberOfElementsType	TransferSize,
  boolean			LastEntry
);

/** @brief	Scatter-Gather Transfer Setup.
 *  @param	Channel		DMA channel to be addressed.
 *  @param	TablePtr	Pointer of Scatter-Gather Transfer Entries
 *  				Table.
 *  @param	TableSize	Number of Entry Elements of Scatter-Gather
 *  				Transfer Table.
 *  @return	
 *  	- <tt>E_OK</tt>:	Transfer Setup command has been accepted
 *  	- <tt>E_NOT_OK</tt>:	Transfer Setup command has not been accepted
 *
 *  Service to set-up Scatter-Gather DMA Transfer on the addressed DMA
 *  Channel.
 *
 *  Service 0x0B
 *
 *  The operation <tt>Dma_ScatterGatherTransferSetup()</tt> is Re-entrant.
 *
 *  When the API <tt>Dma_ScatterGatherTransferSetup()</tt> command has been
 *  accepted the function shall return the value <tt>E_OK</tt>.
 *
 *  When the API <tt>Dma_ScatterGatherTransferSetup()</tt> command has not been
 *  accepted the function shall return the value <tt>E_NOT_OK</tt>.
 *
 *  The function <tt>Dma_ScatterGatherTransferSetup()</tt> provides service to
 *  set-up Scatter-Gather DMA Transfer on the addressed DMA Channel.
 *
 *  The function <tt>Dma_ScatterGatherTransferSetup()</tt> shall set-up
 *  Scatter-Gather DMA Transfer on the addressed DMA Channel.
 *
 *  The DMA Driver shall have been initialized before the function
 *  <tt>Dma_ScatterGatherTransferSetup()</tt> is called, otherwise
 *  <tt>E_NOT_OK</tt> shall be returned.
 *
 *  The API parameters <tt>Channel</tt> shall have values within the specified
 *  range of values of configured DMA Channels otherwise the return value shall
 *  be <tt>E_NOT_OK</tt>.
 *
 *  When the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called and
 *  the addressed DMA Channel is enabled, the DMA Driver shall not take in
 *  account this request and this function shall return with value
 *  <tt>E_NOT_OK</tt>, in this case.
 *
 *  When the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called and
 *  the Number of Entry Elements of Scatter-Gather Transfer Table is equal to 0
 *  or greater than the addressed channel capability the DMA Driver shall not
 *  take in account this request and this function shall return with value
 *  <tt>E_NOT_OK</tt>, in this case.
 *
 *  When the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called and
 *  the Pointer of Scatter-Gather Transfer Entries Table is <tt>NULL_PTR</tt>
 *  the DMA Driver shall not take in account this request and this function
 *  shall return with value <tt>E_NOT_OK</tt>, in this case.
 *
 *  The function <tt>Dma_ScatterGatherTransferSetup()</tt> is pre-compile time
 *  selectable by the configuration parameter <tt>DMA_SCATTER_GATHER_API</tt>.
 *
 *  If development error detection for the DMA module is enabled:
 *  - if the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called before
 *    the DMA module was initialized, the DMA Driver shall raise the development
 *    error <tt>DMA_E_UNINIT</tt>.
 *  - the function <tt>Dma_ScatterGatherTransferSetup()</tt> shall raise the
 *    development error <tt>DMA_E_PARAM_CHANNEL</tt> if the channel parameter is
 *    invalid or not configured, or the channel parameter is configured with
 *    wrong transfer mode.
 *  - if the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called and
 *    the addressed DMA Channel is enabled, the DMA Driver shall raise the
 *    development error <tt>DMA_E_CHANNEL_STATE</tt>.
 *  - if the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called and
 *    the Number of Entry Elements of Scatter-Gather Transfer Table is equal to
 *    0 or greater than the addressed channel capability, the DMA Driver shall
 *    raise the development error <tt>DMA_E_PARAM_SIZE</tt>.
 *  - if the function <tt>Dma_ScatterGatherTransferSetup()</tt> is called and
 *    the Pointer of Scatter-Gather Transfer Entries Table is <tt>NULL_PTR</tt>,
 *    the DMA Driver shall raise the development error
 *     <tt>DMA_E_PARAM_POINTER</tt>.
 */
Std_ReturnType Dma_ScatterGatherTransferSetup(
  Dma_ChannelType		Channel,
  const Dma_EntryType *		TablePtr,
  Dma_NumberOfElementsType	TableSize
);

#endif	/* ( DMA_SCATTER_GATHER_API == STD_ON ) */

#if	( DMA_VERSION_INFO_API == STD_ON )
/** @brief	Version Informations Retrieval.
 *  @param	_vi	Pointer to where to store the version
 *  			information of this module.
 *
 *  This service returns the version information of this module.
 *
 *  Service 0x0C
 *
 *  The operation <tt>Dma_GetVersionInfo()</tt> is Non Re-entrant.
 *
 *  The function <tt>Dma_GetVersionInfo()</tt> provides service to return the
 *  version information of this module.
 *
 *  The function <tt>Dma_GetVersionInfo()</tt> shall return the version
 *  information of this module according to the definition of
 *  <tt>Std_VersionInfoType</tt>.
 *
 *  If source code for caller and callee of <tt>Dma_GetVersionInfo()</tt> is
 *  available, the DMA Driver should realize <tt>Dma_GetVersionInfo()</tt> as a
 *  macro, defined in the module's header file.
 *
 *  The function <tt>Dma_GetVersionInfo()</tt> is pre-compile time configurable
 *  by the configuration parameter <tt>DMA_VERSION_INFO_API</tt>.
 *
 *  If development error detection for the DMA module is enabled, the parameter
 *  <tt>_vi</tt> shall be checked for being <tt>NULL_PTR</tt>. The error
 *  <tt>PORT_E_PARAM_POINTER</tt> shall be reported in case the value is a
 *  <tt>NULL_PTR</tt> pointer.
 */
#if	( DMA_DEV_ERROR_DETECT == STD_ON )
#define	Dma_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,DMA) \
	else \
	{\
		Det_ReportError(\
			DMA_MODULE_ID,\
			0,\
			DMA_GET_VERSION_INFO_SERVICE_ID,\
			DMA_E_PARAM_POINTER\
		);\
	}
#else
#define	Dma_GetVersionInfo(_vi)	STD_GET_VERSION_INFO(_vi,DMA)
#endif	/* DMA_DEV_ERROR_DETECT */
#endif	/* DMA_VERSION_INFO_API */

#endif	/* DMA_H */
