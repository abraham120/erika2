/** 
* @file uwl_simple154.h
* @brief Simple IEEE 802.15.4 Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_simple154_h__
#define __uwl_simple154_h__

#include <mac/uwl_mac.h>
/** 
* @name Error Codes
* @{ */
#define UWL_SIMPLE154_ERR_NONE 			1 /* Returned as positive! */
#define UWL_SIMPLE154_ERR_INITMAC 			1 
#define UWL_SIMPLE154_ERR_SETADDR 			2 
#define UWL_SIMPLE154_ERR_STARTMAC 			3 
#define UWL_SIMPLE154_ERR_ASSOCIATE 			4 
#define UWL_SIMPLE154_ERR_ALREADYINIT			5 
#define UWL_SIMPLE154_ERR_NOTINIT			6 
#define UWL_SIMPLE154_ERR_NOTSUPPORTED			7 
#define UWL_SIMPLE154_ERR_DATAREQ			8 
#define UWL_SIMPLE154_ERR_DATACONFIRM			9 
#define UWL_SIMPLE154_ERR_GTS_MANIPULATION		10 
#define UWL_SIMPLE154_ERR_GTS_NOTCOORDINATOR		11
#define UWL_SIMPLE154_ERR_INVALID_LENGTH		12
#define UWL_SIMPLE154_ERR_SUPERFRAME_CALLBACKS_DISABLED 13
#define UWL_SIMPLE154_ERR_INVALID_JAMMER		14
/**  @} */


/** 
* @brief Set RX Callback
*
* Set the reception callback to be called by the MAC sublayer.
* \note This callback exectutes in the context of the 
* \b MAC_PROCESS_RX_DATA task.
*
* The callback parameters are:
* - The MAC error code
* - A pointer to the received data
* - The length of the received data
* - The short address of the sender, if the addressing mode was extended then
*   0xFFFE is returned.
* 
* @param[in] func The RX callback pointer, if NULL nothing is done on reception.
*/
void uwl_simple154_set_rx_callback(void (*func) (int8_t, uint8_t*, uint8_t, 
						 uint16_t));

/** 
* @brief PAN Coordinator Initialization
* 
* This function initializes the device stack as PAN Coordinator of a 
* simple star topology. 
* The network will operate in an IEEE 802.15.4 compliant beacon-enabled mode.
* 
* @param[in] coordinator_id PAN Coordinator 16-bits Address
* @param[in] pan_id PAN Identifier
* @param[in] channel A valid channel ID
* @param[in] bo The Beacon Order
* @param[in] so The Superframe Order
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_init_coordinator(uint16_t coordinator_id, uint16_t pan_id,
				      uint8_t channel, uint8_t bo, uint8_t so);

/** 
* @brief End-Device Initialization
* 
* This function initializes the device stack as the End-Devic of a
* simple star topology. 
* The network will operate in an IEEE 802.15.4 compliant beacon-enabled mode.
* 
* @param[in] device_id End-Device 16-bits Address
* @param[in] coordinator_id PAN Coordinator Address to which associate to.
* @param[in] pan_id PAN Identifier
* @param[in] channel A valid channel ID
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_init_device(uint16_t device_id, uint16_t coordinator_id, 
				 uint16_t pan_id, uint8_t channel);

/** 
* @brief Send Data
* 
* The function attempt to send data using the underlying initialized MAC layer.
* If the node is an End-Device, i.e. has been initialized by the 
* \ref uwl_simple154_init_device, the data frame can only be sent towards 
* the coordinator.   
* If the node is PAN Coordinator, i.e. has been initialized by the 
* \ref uwl_simple154_init_coordinator, the data frame can be sent towards 
* to any associated End-Devices.   
* 
* @param[in] data A pointer to the buffer of data to be sent. 
* @param[in] len The length of the data.
* @param[in] dst_device_id The destination address, by now is ignored in case
*			   of End-Device (forced send to PAN Coordinator).	
* @param[in] use_gts Specify whether the data has to be sent using the 
*                    Guaranteed Time Slot (GTS) mechanism of the standard.
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_send(uint8_t *data, uint8_t len, uint16_t dst_device_id, 
			  uint8_t use_gts);

/** 
* @name GTS Manipulation
*
* To enable GTS Manipulation the \b UWL_GTS_MANIPULATION symbol must be defined.
* 
* @{ */

/** 
* @brief Clear the GTS database
* 
* Flush all the entry in the GTS database 
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_gts_clear(void); 

/** 
* @brief Add entry to GTS database 
* 
* Insert a new entry, if possible, in the current GTS database. 
* 
* @param[in] device_id The device address  to be added.
* @param[in] length The length of the GTS in timeslot.
* @param[in] dir The direction, can be either \ref UWL_MAC_GTS_DIRECTION_IN
* 		 for End-Device reception (PAN Coordinator transmits) or
* 		 \ref UWL_MAC_GTS_DIRECTION_OUT (viceversa).
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_gts_add(uint16_t device_id, uint8_t length, uint8_t dir);
/**  @} */

/** 
* @brief Set the Beacon Payload 
* 
* The function set the beacon payload that will be sent for all the future  
* beacon until this function is called once more. 
* This function has effects only if the device as been configure as PAN 
* Coordinator
* 
* @param[in] data Pointer to data for beacon payload, if NULL the beacon 
*		  payload will be omitted.
* @param[in] len Data length
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_set_beacon_payload(uint8_t *data, uint8_t len); 

/** 
* @brief Get the Beacon Payload 
* 
* @param[out] data Pointer to the destination buffer for the read beacon.
* @param[in] len Bytes to be read from the beacon payload into \c data.
* 
* @return 	The numbr of bytes read is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_get_beacon_payload(uint8_t *data, uint8_t len);

/** 
* @name Callback Installation
*
* To enable callback installation the \b UWL_SUPERFRAME_CALLBACKS 
* symbol must be defined.
* 
* @{ */

/** 
* @brief Set On-Beacon Callback
* 
* This function will be called every time a beacon interval starts and after the
* complention of all the internal activities (Beacon TX or parsing, etc.).
* \note This callback exectutes in the context of the 
* \b MAC_TIMESLOT task.
* 
* @param[in] func The function pointer to the callback, 
* 		  if NULL nothing is done on reception.
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_set_on_beacon_callback(void (* func)(void)); 

/** 
* @brief Set On-RxBeacon Callback
* 
* This function will be called every time a beacon is received by the device  
* and before any internal activities (Beacon parsing, etc.).
* \note This callback exectutes in the context of the 
* \b PHY_READ_DISPATCHER task.
* 
* @param[in] func The function pointer to the callback, 
* 		  if NULL nothing is done on reception.
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_set_on_rx_beacon_callback(void (* func)(void)); 

/** 
* @brief Set Before-Beacon Callback
* 
* This function will be called every time before the next beacon 
* interval starts and before any internal activities (Beacon creation, etc.).
* \note This callback exectutes in the context of the 
* \b MAC_BEFORE_TIMESLOT task.
* 
* @param[in] func The function pointer to the callback, 
* 		  if NULL nothing is done on reception.
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_set_before_beacon_callback(void (* func)(void));
/**  @} */

/** 
* @brief JAM the CAP with data
* 
* This function attempt to send data in the CAP irrespective of the CSMA-CA
* algorithm. The function should be used only for debugging purposes.
* The function will immediately send data if the current context of the 
* superframe is the Contention Access Period, otherwise the transmission is
* aborted.
* \note To enable callback installation the \b UWL_HAS_JAMMER 
* symbol must be defined.
* 
* @param[in] data Pointer to data to be sent
* @param[in] len Data length
* 
* @return 	\ref UWL_SIMPLE154_ERR_NONE is returned on success, otherwise a 
* 		specific negative error code is returned and the appropriate 
*		MAC error is retrieved.
*/
int8_t uwl_simple154_jam_cap(uint8_t *data, uint8_t len);

/** 
* @brief Last MAC error code
*
* @return * Return the last MAC layer error code
*/
int8_t uwl_simple154_get_mac_error(void);

/** 
* @brief Check if TX GTS is allocated
*
* @return Zero if no TX GTS is allocated
*/
__INLINE__ uint8_t uwl_simple154_is_tx_gts_allocated(void) {
	return uwl_mac_is_tx_gts_allocated();
}

#endif /* Header Protection */
