/*
 * Dynastream Innovations Inc.
 * Cochrane, AB, CANADA
 *
 * Copyright (c) 2012 Dynastream Innovations Inc.
 * THIS SOFTWARE IS AN EXAMPLE USAGE OF THE ANT PROTOCOL MODULE.
 * IT MAY BE USED, MODIFIED and DISTRIBUTED ONLY WITH THE
 * APPROPRIATE LICENSE AGREEMENT.
 */
/* Header guard */
#ifndef ANT_INTERFACE_H__
#define ANT_INTERFACE_H__

#include <stdint.h>
#include <stdbool.h>

/**
  @addtogroup stack_ant_module ANT STACK
  @{
  @defgroup ant_interface ANT Application Interface
  @{
* @brief ANT Stack Application Programming Interface (API).
*/

#ifndef SVCALL
#if defined(__arm__)
#define SVCALL(x) __svc(x)
#else
#define SVCALL(x)
#endif
#endif  // SVCALL

#define STK_SVC_BASE 0x50

/* Common constants */
#define PROTOCOL_EVENT_IRQn       SWI3_IRQn           ///< The Protocol event SW IRQ number (used for passing protocol-> application events)
#define PROTOCOL_EVENT_IRQHandler (SWI3_IRQHandler)   ///< The name of the application's IRQ handler (where protocol -> application events are handled)

/** @brief ANT Stack API SVC numbers */
enum {
  ////////////////////////////////////
  // INITIAL SVC COMMANDS - AXX0.03B00
  ////////////////////////////////////
  /*ant re/initialization*/
  SVC_ANT_STACK_INIT = STK_SVC_BASE,
  /*event api*/
  SVC_ANT_EVENT_GET ,
  /*channel control*/
  SVC_ANT_CHANNEL_ASSIGN,
  SVC_ANT_CHANNEL_UNASSIGN,
  SVC_ANT_CHANNEL_OPEN,
  SVC_ANT_CHANNEL_CLOSE,
  SVC_ANT_RX_SCAN_MODE_START, // api modified AXX1.02B01
  /*data api*/
  SVC_ANT_TX_BROADCAST_MESSAGE,
  SVC_ANT_TX_ACKNOWLEDGED_MESSAGE,
  SVC_ANT_BURST_HANDLER_REQUEST,
  SVC_ANT_PENDING_TRANSMIT_CLEAR,
  SVC_ANT_TRANSFER_STOP,
  /*radio configuration api*/
  SVC_ANT_NETWORK_KEY_SET,
  SVC_ANT_CHANNEL_RADIO_FREQ_SET,
  SVC_ANT_CHANNEL_RADIO_FREQ_GET,
  SVC_ANT_CHANNEL_RADIO_TX_POWER_SET,
  SVC_ANT_PROX_SEARCH_SET,
  /*configuration api*/
  SVC_ANT_CHANNEL_PERIOD_SET,
  SVC_ANT_CHANNEL_PERIOD_GET,
  SVC_ANT_CHANNEL_ID_SET,
  SVC_ANT_CHANNEL_ID_GET,
  SVC_ANT_SEARCH_WAVEFORM_SET,
  SVC_ANT_CHANNEL_RX_SEARCH_TIMEOUT_SET,
  SVC_ANT_SEARCH_CHANNEL_PRIORITY_SET,
  SVC_ANT_ACTIVE_SEARCH_SHARING_CYCLES_SET, // api modified AXX1.02B09
  SVC_ANT_ACTIVE_SEARCH_SHARING_CYCLES_GET, // api modified AXX1.02B09
  SVC_ANT_CHANNEL_LOW_PRIO_RX_SEARCH_TIMEOUT_SET,
  SVC_ANT_ADV_BURST_CONFIG_SET,
  SVC_ANT_ADV_BURST_CONFIG_GET,
  SVC_ANT_LIB_CONFIG_SET,
  SVC_ANT_LIB_CONFIG_CLEAR,
  SVC_ANT_LIB_CONFIG_GET,
  SVC_ANT_ID_LIST_ADD,
  SVC_ANT_ID_LIST_CONFIG,
  SVC_ANT_AUTO_FREQ_HOP_TABLE_SET,
  SVC_ANT_EVENT_FILTERING_SET,
  SVC_ANT_EVENT_FILTERING_GET,
  /*status api*/
  SVC_ANT_ACTIVE,
  SVC_ANT_CHANNEL_IN_PROGRESS,
  SVC_ANT_CHANNEL_STATUS_GET,
  SVC_ANT_PENDING_TRANSMIT,
  /*radio test api*/
  SVC_ANT_INIT_CW_TEST_MODE,
  SVC_ANT_CW_TEST_MODE,
  /*antstack version*/
  SVC_ANT_VERSION,
  /*antstack capabilities*/
  SVC_ANT_CAPABILITIES,
  ////////////////////////////////////
  // ADDED SVC COMMANDS - AXX0.04B00
  ////////////////////////////////////
  /*data api*/
  SVC_ANT_BURST_HANDLER_WAIT_FLAG_ENABLE,
  SVC_ANT_BURST_HANDLER_WAIT_FLAG_DISABLE,
  ////////////////////////////////////
  // ADDED SVC COMMANDS - AXX0.04B01
  ////////////////////////////////////
  /*configuration api*/
  SVC_ANT_SDU_MASK_SET,
  SVC_ANT_SDU_MASK_GET,
  SVC_ANT_SDU_MASK_CONFIG,
  SVC_ANT_CRYPTO_CHANNEL_ENABLE, // api modified AXX1.02B00
  SVC_ANT_CRYPTO_KEY_SET,
  SVC_ANT_CRYPTO_INFO_SET,
  SVC_ANT_CRYPTO_INFO_GET,
  ////////////////////////////////////
  // ADDED SVC COMMANDS - AXX0.04B03
  ////////////////////////////////////
  /*configuration api*/
  SVC_ANT_RFACTIVE_NOTIFICATION_CONFIG_SET,
  SVC_ANT_RFACTIVE_NOTIFICATION_CONFIG_GET,
  ////////////////////////////////////
  // ADDED SVC COMMANDS - AXX1.02B01
  ////////////////////////////////////
  /*configuration api*/
  SVC_ANT_COEX_CONFIG_SET,
  SVC_ANT_COEX_CONFIG_GET,
};

////////////////////////////////////
// INITIAL SVC COMMANDS - AXX0.03B00
////////////////////////////////////
/******************************************************************************/
/** @name ANT API functions
  * @{ */
/******************************************************************************/

/** @brief Function for initializing or re-initializing ANT Stack.
 *
 * @param void
 *
 * @return ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_STACK_INIT) sd_ant_stack_reset (void);

/******************************* EVENT API *******************************/

/** @brief This function returns ANT channel events and data messages.
 *
 * @param[out] pucChannel is the pointer to an unsigned char (1 octet) where the channel number will be copied.
 * @param[out] pucEvent is the pointer to an unsigned char (1 octet) where the event code will be copied. See Channel Events and Command Response Codes in ant_parameters.h.
 * @param[out] aucANTMesg is the buffer where event's message will be copied. The array size must be at least MESG_BUFFER_SIZE to accommadate the entire ANT_MESSAGE structure size. See ANT Message Structure in ant_parameters.h.
 *
 * @return ::NRF_SUCCESS
 * @return ::NRF_ERROR_INVALID_PARAM
 * @return ::NRF_ERROR_NOT_FOUND
 */
uint32_t SVCALL(SVC_ANT_EVENT_GET) sd_ant_event_get (uint8_t *pucChannel, uint8_t *pucEvent, uint8_t *aucANTMesg);

/********************** CHANNEL CONTROL API ******************************/

/** @brief This function assigns and initializes a new channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to assign.
 * @param[in] ucChannelType is an unsigned char (1 octet) denoting the channel type. See Assign Channel Parameters/Assign Channel Types in ant_parameters.h.
 * @param[in] ucNetwork is an unsigned char (1 octet) denoting the network key to associate with the channel.
 * @param[in] ucExtAssign is a bit field (1 octet) for an extended assign. See Ext. Assign Channel Parameters in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 *          ::NRF_ANT_ERROR_INVALID_NETWORK_NUMBER
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_ASSIGN) sd_ant_channel_assign (uint8_t ucChannel, uint8_t ucChannelType, uint8_t ucNetwork, uint8_t ucExtAssign);

/** @brief This function unassigns a channel. The channel to unassign must be in an assigned state.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to unassign.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_UNASSIGN) sd_ant_channel_unassign (uint8_t ucChannel);

/** @brief This function opens and activates a channel. The channel to open must be in an assigned state.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to open.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_OPEN) sd_ant_channel_open(uint8_t ucChannel);

/** @brief This function closes a channel. The channel must be in an open state (SEARCHING or TRACKING).
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to close.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 *
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_CLOSE) sd_ant_channel_close (uint8_t ucChannel);

/** @brief This function starts receive scanning mode feature. Channel 0 must be assigned.  All other channels must be closed.
 *
 * @param[in] ucSyncChannelPacketsOnly is an unsigned char (1 octet) denoting synchronous channel only scanning mode. 0 = disable, 1 = enable.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 *          ::NRF_ANT_ERROR_CLOSE_ALL_CHANNELS
 */
uint32_t SVCALL(SVC_ANT_RX_SCAN_MODE_START) sd_ant_rx_scan_mode_start (uint8_t ucSyncChannelPacketsOnly);

/*********************** DATA API ****************************************/

/** @brief This function is used to set broadcast data for transmission.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to send the data on.
 * @param[in] ucSize is an unsigned char (1 octet) denoting the size of the message, ucSize must be 8.
 * @param[in] aucMesg is the buffer where the message is located (array must be 8 octets).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_MESSAGE_SIZE_EXCEEDS_LIMIT
 *          ::NRF_ANT_ERROR_INVALID_SCAN_TX_CHANNEL
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 *          ::NRF_ANT_ERROR_TRANSFER_IN_PROGRESS
 *          ::NRF_ANT_ERROR_TRANSFER_IN_ERROR
 */
uint32_t SVCALL(SVC_ANT_TX_BROADCAST_MESSAGE) sd_ant_broadcast_message_tx (uint8_t ucChannel, uint8_t ucSize, uint8_t *aucMesg);

/** @brief This function is used to send an acknowledge message. This message requests an acknowledgement from the slave to validate reception.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to send the data on.
 * @param[in] ucSize is an unsigned char (1 octet) denoting the size of the message, ucSize must be 8.
 * @param[in] aucMesg is the buffer where the message is located (array must be 8 octets).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_MESSAGE_SIZE_EXCEEDS_LIMIT
 *          ::NRF_ANT_ERROR_INVALID_SCAN_TX_CHANNEL
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 *          ::NRF_ANT_ERROR_TRANSFER_IN_PROGRESS
 *          ::NRF_ANT_ERROR_TRANSFER_IN_ERROR
 */
uint32_t SVCALL(SVC_ANT_TX_ACKNOWLEDGED_MESSAGE) sd_ant_acknowledge_message_tx (uint8_t ucChannel, uint8_t ucSize, uint8_t *aucMesg);

/** @brief This function is used to queue data for burst transmission. After every successful call, the input buffer is held in use by the burst handler and must not be changed.
 *         When the burst handler releases the input buffer, it will either generate a EVENT_TRANSFER_NEXT_DATA_BLOCK event or clear a specified wait flag assigned to the
 *         burst handler. Transfer end events: EVENT_TRANSFER_TX_COMPLETED and EVENT_TRANSFER_TX_FAILED also releases the input buffer. Special care must be made to ensure that
 *         the input buffer does not change until it is released by the burst handler to avoid data corruption. Use of burst segment identifiers (BURST_SEGMENT_START, BURST_SEGMENT_CONTINUE,
 *         and BURST_SEGMENT_END) is required to indicate the sequence of the data block being sent as a burst transfer.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to do a burst transmission.
 * @param[in] usSize is an unsigned short (2 octets) denoting the size of the message block.  Size must be divisible by 8.
 * @param[in] aucData is the buffer where the message block is located.
 * @param[in] ucBurstSegment is an unsigned char (1 octet) containing a bitfield representing the message block type. See Burst Handler Request Segment Defines in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_TRANSFER_SEQUENCE_NUMBER_ERROR
 *          ::NRF_ANT_ERROR_TRANSFER_IN_PROGRESS
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 *          ::NRF_ANT_ERROR_TRANSFER_BUSY
 *          ::NRF_ANT_ERROR_TRANSFER_IN_ERROR
 *          ::NRF_ANT_ERROR_MESSAGE_SIZE_EXCEEDS_LIMIT
 *          ::NRF_ANT_ERROR_INVALID_SCAN_TX_CHANNEL
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 */
uint32_t SVCALL(SVC_ANT_BURST_HANDLER_REQUEST) sd_ant_burst_handler_request(uint8_t ucChannel, uint16_t usSize, uint8_t *aucData, uint8_t ucBurstSegment);

/** @brief This function clears a pending transmit. Primarily intended for shared slave channels (receive channel).
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to clear pending transmit.
 * @param[out] ucSuccess is the pointer to an unsigned char (1 octet) where the result will be stored.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_PENDING_TRANSMIT_CLEAR) sd_ant_pending_transmit_clear (uint8_t ucChannel, uint8_t *pucSuccess);

/** @brief This function kills a receive transfer that is in progress.
 *
 * @param void
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_TRANSFER_STOP) sd_ant_transfer_stop (void);

/********************** RADIO CONFIGURATION API **************************/

/** @brief This function sets the 64bit network address.
 *
 * @param[in] ucNetwork is an unsigned char (1 octet) denoting the network number to assign the network address to.
 * @param[in] aucNetworkKey is the pointer to location of the Network Key (8 octets in length)
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_NETWORK_KEY_SET) sd_ant_network_address_set (uint8_t ucNetwork, uint8_t *aucNetworkKey);

/** @brief This function sets the radio frequency of an ANT channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set to.
 * @param[in] ucFreq is an unsigned char (1 octet) denoting the radio frequency offset from 2400MHz (eg. 2466MHz, ucFreq = 66).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_RADIO_FREQ_SET) sd_ant_channel_radio_freq_set (uint8_t ucChannel, uint8_t ucFreq);

/** @brief This function returns the radio frequency of an ANT channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to query.
 * @param[out] pucRfreq is the pointer to an unsigned char (1 octet) where the frequency will be stored.
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_RADIO_FREQ_GET) sd_ant_channel_radio_freq_get (uint8_t ucChannel, uint8_t *pucRfreq);

/** @brief This function sets the radio tx power.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to assign the radio tx power.
 * @param[in] ucTxPower is an unsigned char (1 octet) denoting the transmit power number. See Radio TX Power Definitions in ant_parameters.h
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_RADIO_TX_POWER_SET) sd_ant_channel_radio_tx_power_set (uint8_t ucChannel, uint8_t ucTxPower);

/** @brief This function sets the sensitivity threshold for acquisition on a searching channel. One time set.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number.
 * @param[in] ucProxThreshold is an unsigned char (1 octet) denoting the minimum RSSI threshold required for acquisition during a search. See Radio Proximity Search Threshold in ant_parameters.h
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_PROX_SEARCH_SET) sd_ant_prox_search_set (uint8_t ucChannel, uint8_t ucProxThreshold);

/********************** CONFIGURATION API ********************************/

/** @brief This function sets the channel period.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set the period to.
 * @param[in] usPeriod is an unsigned short (2 octets) denoting the period in 32 kHz counts (usPeriod/32768 s).
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_PERIOD_SET) sd_ant_channel_period_set (uint8_t ucChannel, uint16_t usPeriod);

/** @brief This function returns the current channel period.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to query.
 * @param[out] pusPeriod is the pointer to an unsigned short (2 octets) where the channel period will be stored.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_PERIOD_GET) sd_ant_channel_period_get (uint8_t ucChannel, uint16_t *pusPeriod );

/** @brief This function sets the channel ID.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set.
 * @param[in] usDeviceNumber is an unsigned short (2 octets) denoting the device number.
 * @param[in] ucDeviceType is an unsigned char (1 octet) denoting the device type.
 * @param[in] ucTransmitType is an unsigned char (1 octet) denoting the transmission type.
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_ID_SET) sd_ant_channel_id_set (uint8_t ucChannel, uint16_t usDeviceNumber, uint8_t ucDeviceType, uint8_t ucTransmitType);

/** @brief This function returns the current Channel ID of a channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to query.
 * @param[out] pusDeviceNumber is the pointer to an unsigned short (2 octets) where the device number will be stored.
 * @param[out] pucDeviceType is the pointer to an unsigned char (1 octet) where the device type will be stored.
 * @param[out] pucTransmitType is the pointer to an unsigned char (1 octet) where the transmit type will be stored.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_ID_GET) sd_ant_channel_id_get (uint8_t ucChannel, uint16_t *pusDeviceNumber, uint8_t *pucDeviceType, uint8_t *pucTransmitType);

/** @brief This function sets the searching waveform value of an ANT Channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set.
 * @param[in] usWaveform is an unsigned short (2 octets) denoting the channel waveform period (usWaveform/32768 s). Default = 316.
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_SEARCH_WAVEFORM_SET) sd_ant_search_waveform_set (uint8_t ucChannel, uint16_t usWaveform);

/** @brief This function sets the receive channel search timeout.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set.
 * @param[in] ucTimeout is an unsigned char (1 octet) denoting the timeout value in 2.5 second increments. Default = 10 (25s).
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_RX_SEARCH_TIMEOUT_SET) sd_ant_channel_rx_search_timeout_set (uint8_t ucChannel, uint8_t ucTimeout);

/** @brief This function sets the channel's search priority.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set.
 * @param[in] ucSearchPriority is an unsigned char (1 octet) denoting the search priority value. 0 to 7 (Default = 0).
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_SEARCH_CHANNEL_PRIORITY_SET) sd_ant_search_channel_priority_set (uint8_t ucChannel, uint8_t ucSearchPriority);

/** @brief This function sets the search cycle number of separate searching channels for active search time sharing.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to configure.
 * @param[in] ucCycles is an unsigned char (1 octet) denoting the number of cycles to set.
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_ACTIVE_SEARCH_SHARING_CYCLES_SET) sd_ant_active_search_sharing_cycles_set (uint8_t ucChannel, uint8_t ucCycles);

/** @brief This function returns the search sharing cycles number of the specified searching channel for active search time sharing.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to query.
 * @param[out] pucCycles is the pointer to an unsigned char (1 octet) where the cycle value will be stored.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_ACTIVE_SEARCH_SHARING_CYCLES_GET) sd_ant_active_search_sharing_cycles_get (uint8_t ucChannel, uint8_t *pucCycles);

/** @brief This function sets the low priority search timeout value of a channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set.
 * @param[in] ucTimeout is an unsigned char (1 octet) denoting the timeout value in 2.5 seconds increments. Default = 2 (5s).
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_LOW_PRIO_RX_SEARCH_TIMEOUT_SET) sd_ant_channel_low_priority_rx_search_timeout_set (uint8_t ucChannel, uint8_t ucTimeout);

/** @brief This function sets the advanced burst configuration. Configuration structure is as follows:
 *         Required Byte0 = 0-Disable, 1-Enable. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Required Byte1 = RF payload size. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Required Byte2 = Required advanced burst modes. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Required Byte3 = 0, Reserved
 *         Required Byte4 = 0, Reserved
 *         Required Byte5 = Optional advanced burst modes. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Required Byte6 = 0, Reserved
 *         Required Byte7 = 0, Reserved
 *         Optional Byte8 = Advanced burst stalling count config LSB. Typical is 3210 (~10s of stalling) where each count represents ~3ms of stalling.
 *         Optional Byte9 = Advanced burst stalling count config MSB.
 *         Optional Byte10 = Advanced burst retry count cycle extension. Typical is 3 (15 retries) where each count cycles represents 5 retries.
 *
 * @param[in] aucConfig is a buffer containing the advanced burst configuration to be set (as stated above).
 * @param[in] ucSize is an unsigned char (1 octet) denoting the size of the configuration parameter buffer. Minimum config set is 8 octets, maximum is 11 octets.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_ADV_BURST_CONFIG_SET) sd_ant_adv_burst_config_set (uint8_t *aucConfig, uint8_t ucSize);

/** @brief This function gets the advance burst configuration and supported capabilities.
 *         Returned structure is as follows for configuration:
 *         Byte0 = RF payload size. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Byte1 = Required advanced burst modes. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Byte2 = 0, Reserved
 *         Byte3 = 0, Reserved
 *         Byte4 = Optional advanced burst modes. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Byte5 = 0, Reserved
 *         Byte6 = 0, Reserved
 *         Byte7 = Advanced burst stalling count config LSB. Each count represents ~3ms of stalling.
 *         Byte8 = Advanced burst stalling count config MSB
 *         Byte9 = Advanced burst retry count cycle extension. Each count cycle represents 5 retries.
 *
 *         Returned structure is as folows for capabilities:
 *         Byte0 = Supported RF payload size. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Byte1 = Supported burst configurations. See Advanced Burst Configuration Defines in ant_parameters.h.
 *         Byte2 = 0, Reserved
 *         Byte3 = 0, Reserved
 *
 * @param[in] ucRequestType is an unsigned char (1 octet) denoting the type of request. 1 = configuration, 0 = capability.
 * @param[out] aucConfig is the pointer to the buffer where the configuration/capabilities will be read to. The array should be at least 10 octets
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_ADV_BURST_CONFIG_GET) sd_ant_adv_burst_config_get (uint8_t ucRequestType, uint8_t *aucConfig);

/** @brief This function sets the ANT Messaging Library Configuration used by Extended messaging.
 *
 * @param[in] ucANTLibConfig is an unsigned char (1 octet) denoting the ANT lib config bit flags. See ANT Library Config in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_LIB_CONFIG_SET) sd_ant_lib_config_set (uint8_t ucANTLibConfig);

/** @brief This function clears the ANT Messaging Library Configuration.
 *
 * @param[in] ucANTLibConfig is an unsigned char (1 octet) denoting the ANT lib Config bit(s) to clear. See ANT Library Config in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_LIB_CONFIG_CLEAR) sd_ant_lib_config_clear (uint8_t ucANTLibConfig);

/** @brief This function returns current ANT Messaging Library Configuration.
 *
 * @param[out] pucANTLibConfig is the pointer to an unsigned char (1 octet) where the bit flags will be stored. See ANT Library Config in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_LIB_CONFIG_GET) sd_ant_lib_config_get (uint8_t *pucANTLibConfig);

/** @brief This function is used to add a Device ID to an include or exclude list.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to add the list entry to.
 * @param[in] aucDevId is the pointer to the buffer (4 octets) containing device ID information with the following format:
 *            Byte0 = DeviceNumber_LSB
 *            Byte1 = DeviceNumber_MSB
 *            Byte2 = DeviceType
 *            Byte3 = TransType
 * @param[in] ucListIndex is an unsigned char (1 octet) denoting the index where the specified Channel ID is to be placed in the list (0-3).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_LIST_ID
 */
uint32_t SVCALL(SVC_ANT_ID_LIST_ADD) sd_ant_id_list_add (uint8_t ucChannel, uint8_t *aucDevId, uint8_t ucListIndex);

/** @brief This function is used to configure the device ID list as include or exclude as well as the number of IDs to compare against.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number of the device ID list.
 * @param[in] ucIDListSize is an unsigned char (1 octet) denoting the size of the inclusion or exclusion list (0-4).
 * @param[in] ucIncExcFlag is an unsigned char (1 octet) denoting the type of list as Include(0) or Exclude(1)
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_INVALID_LIST_ID
 */
uint32_t SVCALL(SVC_ANT_ID_LIST_CONFIG) sd_ant_id_list_config (uint8_t ucChannel, uint8_t ucIDListSize, uint8_t ucIncExcFlag);

/** @brief This function populates the frequency hop table list. This table is used when frequency hopping is enabled on a channel via extended assignment bit.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to set the frequency hop table list.
 * @param[in] ucFreq0 is an unsigned char (1 octet) denoting the offset from 2400MHz of the 1st frequency hop value.
 * @param[in] ucFreq1 is an unsigned char (1 octet) denoting the offset from 2400MHz of the 2nd frequency hop value.
 * @param[in] ucFreq2 is an unsigned char (1 octet) denoting the offset from 2400MHz of the 3rd frequency hop value.
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_AUTO_FREQ_HOP_TABLE_SET) sd_ant_auto_freq_hop_table_set (uint8_t ucChannel, uint8_t ucFreq0, uint8_t ucFreq1, uint8_t ucFreq2);

/** @brief This function is used to specify filter configuration for channel event message generation.
 *
 * @param[in] usFilter is an unsigned short (2 octets) denoting the filter configuration bitfield. See Event Filtering in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_EVENT_FILTERING_SET) sd_ant_event_filtering_set (uint16_t usFilter);

/** @brief This function is used to retrieve the filter configuration for channel event message generation.
 *
 * @param[out] pusFilter is the pointer to an unsigned short (2 octets) where the filter configuration will be stored. See Event Filtering in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL (SVC_ANT_EVENT_FILTERING_GET) sd_ant_event_filtering_get (uint16_t *pusFilter);

/*************************** STATUS API **********************************/

/** @brief This function gets the ANT activity status.
 *
 * @param[out] pbAntActive is the pointer to an unsigned char (1 octet) where the ANT activity value will be stored. 1 = active, 0 = otherwise.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_ACTIVE) sd_ant_active (uint8_t *pbAntActive );

/** @brief This function gets the status if the channel is in progress.
 *
 * @param[out] pbChannelInProgress is the pointer to an unsigned char (1 octet) where the result will be stored. 1 = in progress, 0 = otherwise.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_IN_PROGRESS) sd_ant_channel_in_progress (uint8_t *pbChannelInProgress);

/** @brief This function gets a specific channel's status.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to query.
 * @param[out] pucStatus is the pointer to an unsigned char (1 octet) where the channel status will be stored. See Channel Status in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CHANNEL_STATUS_GET) sd_ant_channel_status_get (uint8_t ucChannel, uint8_t *pucStatus);

/** @brief This function determines if there is a pending transmission on a specific channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel number to query.
 * @param[out] pucPending is the pointer to an unsigned char (1 octet) where the pending result will be stored. 1 = pending, 0 = otherwise.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_PENDING_TRANSMIT) sd_ant_pending_transmit (uint8_t ucChannel, uint8_t *pucPending);

/*************************** TEST API **********************************/

/** @brief This function initialize the stack to get ready for a continuous wave transmission test.
 *
 * @param void
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_INIT_CW_TEST_MODE) sd_ant_cw_test_mode_init (void);

/** @brief This function starts a continuous wave test mode transmission.
 *
 * @param[in] ucRadioFreq is an unsigned char (1 octet) denoting the radio frequency offset from 2400MHz for continuous wave mode. (eg. 2466MHz, ucRadioFreq = 66).
 * @param[in] ucTxPower is an unsigned char (1 octet) denoting the transmit power for continuous wave mode. See Radio TX Power Definitions in ant_parameters.h
 *
 * @return  ::NRF_SUCCESS
 */
uint32_t SVCALL(SVC_ANT_CW_TEST_MODE) sd_ant_cw_test_mode (uint8_t ucRadioFreq, uint8_t ucTxPower);

/** @brief This function gets the version string of the ANT stack.
 *
 * @param[out] aucVersion is the pointer to the buffer where the version string will be copied, the array should be at least 11 octets.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_VERSION) sd_ant_version_get (uint8_t* aucVersion);

/** @brief This function gets the capabilities of the stack.
 *
 * @param[out] aucCapabilities is the pointer to the buffer where the capabilities message will be copied, the array should be at least 8 octets.
 *             Byte0 = Maximum supported ANT channels
 *             Byte1 = Maximum supported ANT networks
 *             Byte2 = CAPABILITIES_STANDARD. See Standard capabilities defines in ant_parameters.h
 *             Byte3 = CAPABILITIES_ADVANCED. See Advanced capabilities defines in ant_parameters.h
 *             Byte4 = CAPABILITIES_ADVANCED_2. See Advanced capabilities 2 defines in ant_parameters.h
 *             Byte5 = Maximum support ANT data channels (only applicable for SensRcore support)
 *             Byte6 = CAPABILITIES_ADVANCED_3. See Advanced capabilities 3 defines in ant_parameters.h
 *             Byte7 = CAPABILITIES_ADVANCED_4. Advanced capabilities 4 defines in ant_parameters.h
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CAPABILITIES) sd_ant_capabilities_get (uint8_t* aucCapabilities);

////////////////////////////////////
// ADDED SVC COMMANDS - AXX0.04B00
////////////////////////////////////

/*********************** DATA API ****************************************/

/** @brief This function assigns a wait variable to the the burst handler. When the input buffer is locked by the handler the wait flag is set to 1. When the
 *         input buffer is unlocked, the wait flag is set to 0. When a wait flag is assigned, EVENT_TRANSFER_NEXT_DATA_BLOCK events will not
 *         be generated until the wait flag unassigned. The wait flag should be declared as a static variable.
 *
 * @param[in] pucWaitFlag is the pointer to a static unsigned char (1 octet) where the status of the burst handler will be updated.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_TRANSFER_IN_PROGRESS
 */
uint32_t SVCALL(SVC_ANT_BURST_HANDLER_WAIT_FLAG_ENABLE) sd_ant_burst_handler_wait_flag_enable (uint8_t* pucWaitFlag);

/** @brief This function unassigns any previously assigned wait variable from the burst handler. The burst handler returns to the default method in generating
 *         EVENT_TRANSFER_NEXT_DATA_BLOCK to indicate input buffer unlock.
 *
 * @param void
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_TRANSFER_IN_PROGRESS
 */
 uint32_t SVCALL(SVC_ANT_BURST_HANDLER_WAIT_FLAG_DISABLE) sd_ant_burst_handler_wait_flag_disable (void);

////////////////////////////////////
// ADDED SVC COMMANDS - AXX0.04B01
////////////////////////////////////

/********************** CONFIGURATION API ********************************/

/** @brief This function is used to assign a selective data update (SDU) mask (8 octets) to an identifier, ucMask.
 *
 * @param[in] ucMask is an unsigned char (1 octet) denoting the index representing the SDU data mask.
 * @param[in] aucMask is a buffer (8 octets) containing the SDU mask to be assigned to ucMask.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_SDU_MASK_SET) sd_ant_sdu_mask_set (uint8_t ucMask, uint8_t *aucMask);

/** @brief This function returns the selective data update (SDU) mask (8 octets) from the specified identifier, ucMask.
 *
 * @param[in] ucMask is an unsigned char (1 octet) denoting the index representing the SDU data mask.
 * @param[out] aucMask is a pointer to the buffer where the SDU data mask will be copied, the array should be at least 8 octects.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_SDU_MASK_GET) sd_ant_sdu_mask_get (uint8_t ucMask, uint8_t *aucMask);

/** @brief This function assigns a SDU mask configuration to a particular channel. The configuration specifies the mask identifier and the type of rx data in which the mask should be applied to.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel in which the SDU mask configuration is to be applied to.
 * @param[in] ucMaskConfig is an unsigned char (1 octet) denoting SDU mask configuration. See Selective Data Update Mask Configuration Defines in ant_parameters.h.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_SDU_MASK_CONFIG) sd_ant_sdu_mask_config (uint8_t ucChannel, uint8_t ucMaskConfig);

/** @brief This function enables/disables 128-bit AES encryption mode to the specified channel. Advanced burst must be enabled beforehand to enable encrypted channel.
 *         Currently, encryption supports configured advanced burst RF payload size 1 or 2 and can only be enabled for 1 ANT channel.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel in which encrpytion mode is set.
 * @param[in] ucEnable is an unsigned char (1 octet) denoting the encryption mode. See Encrypted Channel Defines in ant_parameters.h.
 * @param[in] ucKeyNum is an unsigned char (1 octet) denoting the key index of the 128-bit key to be used for encryption. Currently, only key index 0 can be used.
 * @param[in] ucDecimationRate is an unsigned char (1 octet) denoting the decimate rate to apply for encrypted slave channel. Must be > 0.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 *          ::NRF_ANT_ERROR_INVALID_SCAN_TX_CHANNEL
 *          ::NRF_ANT_ERROR_CHANNEL_NOT_OPENED
 *          ::NRF_ANT_ERROR_MESSAGE_SIZE_EXCEEDS_LIMIT
 *          ::NRF_ANT_ERROR_TRANSFER_IN_PROGRESS
 *          ::NRF_ANT_ERROR_TRANSFER_SEQUENCE_NUMBER_ERROR
 *          ::NRF_ANT_ERROR_TRANSFER_IN_ERROR
 *          ::NRF_ANT_ERROR_TRANSFER_BUSY
 *          ::NRF_ANT_ERROR_CHANNEL_IN_WRONG_STATE
 */
uint32_t SVCALL(SVC_ANT_CRYPTO_CHANNEL_ENABLE) sd_ant_crypto_channel_enable (uint8_t ucChannel, uint8_t ucEnable, uint8_t ucKeyNum, uint8_t ucDecimationRate);

/** @brief This function assigns a 128-bit AES encryption key to a key index.
 *
 * @param[in] ucKeyNum is an unsigned char (1 octet) denoting the key index for assignment. Currently, only key index 0 can be used.
 * @param[in] aucKey is a buffer (16 octets) containing the 128-bit AES key to be assigned to the key index.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_CRYPTO_KEY_SET) sd_ant_crypto_key_set (uint8_t ucKeyNum, uint8_t *aucKey);

 /** @brief This function sets specific information to be exchanged between the channel master and slave during encryption channel set-up/negotiation.
 *
 * @param[in] ucType is an unsigned char (1 octet) denoting the type of information being set. See Encrypted Channel Defines in ant_parameters.h.
 * @param[in] aucInfo is a buffer containing the information being set (4 octets for ID, 19 octets for custom user data).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_CRYPTO_INFO_SET) sd_ant_crypto_info_set (uint8_t ucType, uint8_t *aucInfo);

 /** @brief This function retrieves specific information to be exchanged between the channel master and slave during encryption channel set-up/negotiation.
 *
 * @param[in] ucType is an unsigned char (1 octet) denoting the type of information being requested. See Encrypted Channel Defines in ant_parameters.h.
 * @param[out] aucInfo is a pointer to a buffer in which the information retrieved will be copied to (1 octet for supported mode, 4 octets for ID, 19 octets for custom user data).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_CRYPTO_INFO_GET) sd_ant_crypto_info_get (uint8_t ucType, uint8_t *aucInfo);

////////////////////////////////////
// ADDED SVC COMMANDS - AXX0.04B03
////////////////////////////////////

/********************** CONFIGURATION API ********************************/

 /** @brief This function enables/disables event notifications to be generated to the application indicating the time to the next radio activity exceeds the configured time threshold.
 *          Latency (delay in event notification being received and processed by application) must be taken into account if attempting to use this generated event to perform
 *          operations prior to the radio activity.
 *
 * @param[in] ucMode is an unsigned char (1 octet) denoting the mode of event notification. See RFActive Notification Defines in ant_parameters.h.
 * @param[in] usTimeThreshold is an unsigned short (2 octets) denoting the minimum time threshold (32 kHz counts (usTimeThreshold/32768 s)) before the next radio activity that will trigger generation of the event notification.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ANT_ERROR_INVALID_PARAMETER_PROVIDED
 */
uint32_t SVCALL(SVC_ANT_RFACTIVE_NOTIFICATION_CONFIG_SET) sd_ant_rfactive_notification_config_set (uint8_t ucMode, uint16_t usTimeThreshold);

 /** @brief This function retrieves the rf active notification configuration
 *
 * @param[in] pucMode is a pointer to an unsigned char (1 octet) where the configured mode of event notification will be stored.
 * @param[out] pusTimeThreshold is a pointer to an unsigned short (2 octets) where the configured time threhold value will be stored. Time threshold is in 32 kHz counts (usTimeThreshold/32768 s).
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_RFACTIVE_NOTIFICATION_CONFIG_GET) sd_ant_rfactive_notification_config_get (uint8_t *pucMode, uint16_t *pusTimeThreshold);

////////////////////////////////////
// ADDED SVC COMMANDS - AXX1.02B01
////////////////////////////////////

/********************** CONFIGURATION API ********************************/

 /** @brief This function sets ANT radio coexistence behaviour. Supported only if ANT is sharing radio HW concurrently with another wireless protocol.
 *          Configuration structure is as follows:
 *          Byte0 = Configuration enable bitfield
 *                  bit0 - enable/disable tx/rx channel keep alive
 *                  bit1 - enable/disable tx/rx channel fixed interval priority
 *                  bit2 - enable/disable transfer keep alive
 *                  bit3 - enable/disable search channel fixed interval priority
 *                  else - reserved
 *          Byte1 = tx/rx channel fixed interval priority configuration
 *          Byte2 = transfer keep alive configuration
 *          Byte3 = search channel fixed interval priority configuration
 *          Byte4(LSB)/Byte5(MSB) = tx channel keep alive configuration
 *          Byte6(LSB)/Byte7(MSB) = rx channel keep alive configuration
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel for which the coexistence configuration is to be set.
 * @param[in] aucCoexConfig is a buffer containing the coex configuration to be set. Must be 8 octet in size.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_COEX_CONFIG_SET) sd_ant_coex_config_set (uint8_t ucChannel, uint8_t *aucCoexConfig);

 /** @brief This function retrieves the configured ANT radio coexistence behaviour as described in ant_coex_config_set.
 *
 * @param[in] ucChannel is an unsigned char (1 octet) denoting the channel to query.
 * @param[out] aucCoexConfig is the pointer to an unsigned char (1 octet) where the coexistence configuration will be stored. Must be at least 8 octet in size.
 *
 * @return  ::NRF_SUCCESS
 *          ::NRF_ERROR_INVALID_PARAM
 */
uint32_t SVCALL(SVC_ANT_COEX_CONFIG_GET) sd_ant_coex_config_get (uint8_t ucChannel, uint8_t *aucCoexConfig);

#endif // ANT_INTERFACE_H__

/**
  @}
  @}
  */
