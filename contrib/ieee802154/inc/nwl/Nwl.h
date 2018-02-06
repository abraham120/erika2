/*************************************************************************
*
* Project: ERIKA Enterprise and Open-ZB 
*          ZigBee compliant network stack for ERIKA Enterprise
*
* Coordinators:
*   Giuseppe Lipari     <lipari@sssup.it>
*   Eduardo Tovar       <emt@dei.isep.ipp.pt>
*   Mario Alves         <mjs@isep.ipp.pt>
*
* Authors:
*   Andre Cunha            <andreribeirocunha@gmail.com>
*   Mangesh Chitnis        <m.chitnis@sssup.it>
*   Antonio Romano         <a.romano@sssup.it>
*   Ricardo Severino       <rars@isep.ipp.pt>
*   Paolo Pagano           <p.pagano@sssup.it>
*   Christian Nastasi      <nastasichr@gmail.com>
*
* ReTiS Lab (CEIIC, Scuola Superiore S.Anna - Pisa - Italy)
* IPP-Hurray (Polytechnique Institute of Porto - Portugal)
*
* http://retis.sssup.it
* http://www.hurray.isep.ipp.pt
*
*************************************************************************
*
* Copyright (C) 2008 Andre Cunha, Mangesh Chitnis 
*                    Antonio Romano, Ricardo Severino
*                    Paolo Pagano, Christian Nastasi
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*************************************************************************
*
* CVS: 
*
* $Id: Nwl.h,v 1.5 2008/07/30 16:49:30 chris Exp $
* $Log: Nwl.h,v $
* Revision 1.5  2008/07/30 16:49:30  chris
* Use sync-to-beacon mechanism (callback function called on beacon - received or sent - )
*
* Revision 1.4  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.3  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


/*
 * Network Layer HEADER FILE
 * 
 */
#include "ee.h"

#include "mac/Mac.h"
#include "mac/mac_enumerations.h"
#include "mac/mac_func.h"

#include "common/console.h"


/** 
* @brief Open-ZB exit status codes
*/
typedef enum {
	OPENZB_SUCCESS,				/**< Sucess status */
	OPENZB_ERR_INVALID_PACKET,		/**< Invalid packet received, unknown for the protocol */
} OpenZB_ExitStatus;

/** 
* @brief Open-ZB debug information
*/
typedef struct {
	EE_UINT32 received_beacon_packets; 		/**< Number of beacons received  */
	EE_UINT32 received_data_packets; 		/**< Number of data packet received */
	EE_UINT32 received_ack_packets; 		/**< Number of ack packet received */
	EE_UINT32 received_command_packets; 		/**< Number of command packet received */
	EE_UINT32 received_invalid_packets; 		/**< Number of invalid packet received */
} OpenZB_DebugInfo;


/*TODO: in future we MUST have a internal file */
#ifndef _Nwl_c_
extern volatile void (*_openZB_err_callback) (OpenZB_ExitStatus);
extern volatile void (*_openZB_sync_callback) (OpenZB_ExitStatus);
extern volatile OpenZB_DebugInfo _openZB_debug_stats;

/* TODO: remove this mechanism, used just to set address in the PERCOM09 demo 
	 see also those variable in Mac.c
*/
extern unsigned int openzb_device_addresses[4];
extern unsigned int openzb_device_address;

/** 
* @brief Set the time synchronization callback
*
* \todo Write more comment
* 
* @param sync_callback 	Pointer to a callback function to call on the receving of the beacon. 
*			If \c NULL the synchronization notification is skipped.
* 
* @return 		Returns \ref OPENZB_SUCCESS if no error occurs, otherwise a specific \ref OpenZB_ExitStatus code.
*/
__INLINE__ OpenZB_ExitStatus  openZB_set_sync_callback(void (*sync_callback) (OpenZB_ExitStatus)) 
{ 
	_openZB_sync_callback = sync_callback; 
	return OPENZB_SUCCESS;
}

#endif

/** 
* @brief Initializes the Open-ZB stack 
*
* \todo Write more comment
* \todo Check if and how disable RX
* 
* @param rx_callback 	Pointer to a callback function to call when a data packet is received. 
*			If \c NULL the receive is disabled.
*
* @param err_callback 	Pointer to a callback function to call if error occurs. 
*			If \c NULL the error notification is skipped.
* 
* @return 		Returns \ref OPENZB_SUCCESS if no error occurs, otherwise a specific \ref OpenZB_ExitStatus code.
*/
OpenZB_ExitStatus openZB_init(void (*rx_callback) (OpenZB_ExitStatus, EE_UINT8*, EE_UINT16), void (*err_callback) (OpenZB_ExitStatus));


/** 
* @brief Retrieve Open-ZB stack debug information
* 
* \todo make this inline
* \todo lock on sempahore before memcpy
* 
* @param stats 		A pointer to a structure that will store the debug information.
* 
* @return 		Returns \ref OPENZB_SUCCESS if no error occurs, otherwise a specific \ref OpenZB_ExitStatus code.
*/
OpenZB_ExitStatus openZB_get_debug_info(OpenZB_DebugInfo* stats);


/** 
* @brief Send Bytes
* 
* \todo write more
* 
* @param data 		The buffer with the data to send.	
* @param size 		The number of bytes to send.
* @param use_gts 	Specify if the use of GTS is required.
* 
* @return 		Returns \ref OPENZB_SUCCESS if no error occurs, otherwise a specific \ref OpenZB_ExitStatus code.
*/
OpenZB_ExitStatus openZB_send_bytes(const EE_UINT8 *data, EE_UINT16 size, EE_UINT8 use_gts);

/** 
* 
* @brief Send string of chars. 
* 
* \todo write more
* 
* @param str 		A valid string of chars (terminated with \\0);
* @param use_gts 	Specify if the use of GTS is required.
* 
* @return 		Returns \ref OPENZB_SUCCESS if no error occurs, otherwise a specific \ref OpenZB_ExitStatus code.
*/
OpenZB_ExitStatus openZB_send_string(const char *str, EE_UINT8 use_gts);


/** 
* @brief Raise error to the application layer
*
* \todo Move this macro to a internals include file.
* 
* @param e 	A valid \ref OpenZB_ExitStatus code.
*/
#define _openZB_raise_error(e)		\
if(_openZB_err_callback)		\
	_openZB_err_callback((e));	\

/** 
* @brief Notify synchronization for the upper layers
*
* \todo Move this macro to a internals include file.
* 
* @param e 	A valid \ref OpenZB_ExitStatus code.
*/
#define _openZB_sync_notify(e)		\
if(_openZB_sync_callback)		\
	_openZB_sync_callback((e));	\

