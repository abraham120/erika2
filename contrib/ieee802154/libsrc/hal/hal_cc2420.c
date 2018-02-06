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
* $Id: hal_cc2420.c,v 1.26 2008/07/17 17:37:51 francesco Exp $
* $Log: hal_cc2420.c,v $
* Revision 1.26  2008/07/17 17:37:51  francesco
* Scicos update
*
* Revision 1.25  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.24  2008/07/11 14:57:43  chris
* Check for lenght: should be at least 13+1 bytes (empty payload)
*
* Revision 1.23  2008/07/08 18:20:05  chris
* BUG-FIX: checking return value for queue functions which was 0 ad put into a pointer (insertq, getq, removeq)
*
* Revision 1.22  2008/07/07 11:34:24  chris
* Remove & in memcpy arg which was already the source pointer.
*
* Revision 1.21  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

#include "hal/hal_cc2420.h"
#include "string.h"
#include "common/queue.h"
#include "common/console.h"
#include "frame_format.h"

#include "nwl/Nwl.h"
#include "phy/phy.h"
#include "mac/mac_const.h"

#include "mac/Mac.h"

EE_UINT8 ieee802154_buff[BUFFER_SIZE] __attribute__((far));
extern c_queue *receiveBuffer_ptr;

//in Mac.c
extern MPDU *mac_beacon_rxmpdu_ptr;
extern MPDU mac_beacon_rxmpdu;

void store_msg(EE_UINT8 length, EE_UINT8 *mpdu){
	
	memcpy(ieee802154_buff, mpdu, length * sizeof(EE_UINT8));

	//GetResource(S2); 
	
	hal_store_msg(ieee802154_buff, length);
	
	hal_set_tx();
	
	//ReleaseResource(S2);
	
}

void store_msg_cca(EE_UINT8 length, EE_UINT8 *mpdu){
	
	memcpy(ieee802154_buff, mpdu, length * sizeof(EE_UINT8));
	//GetResource(S2); 
	
	hal_store_msg(ieee802154_buff, length);
	
	hal_set_tx_on_cca();
	
	//ReleaseResource(S2);	
}

void read_Data(void){
	
	//read 3 bytes (in the read dispatcher)
	


	//if beacon cpy to mac_beacon_rxmpdu_ptr
	EE_UINT8 rssi=0, lqi=0;
	int retv;
	EE_UINT8 length;
	//EE_UINT8 k = 0;
	char radio_msg[BUFFER_SIZE];
	MPDU *rx_data;

	retv = hal_get_msg(radio_msg);
	/* chris TODO: in ftuture we need to check if lenght for the minimum available packet*/
	if(retv < 13) 
		return; /* chris TODO: Make something: notify to upper layer (raise an error) or ignore (return immediately) */

	length = ((EE_UINT8) retv) + 1; /* Lenght doe's not consider the first byte (which is length itself) so add it! */

/*	if(length < 100){
		EE_leds_off();
		EE_led_3_on();
		for(;;);
	}
*/
	
	/* If CRC is correct go ahead: check the most significant bit of the last byte */
	if (radio_msg[length-1] & 0x80) {
		/*
		 * The last two bytes in the buffer are the RSSI value 
		 * and the CRC value respectively. They are not part 
		 * of the message (payload), then we can discard them.
		 * For further information see the CC2420 datasheet  
		 */
		lqi = radio_msg[length-1] & 0x7f;
		rssi= 255 - radio_msg[length-2]; //chris TODO: check with respect to the cc2420 reference man
		 
		length -= 2;
		//k++;
		/*for(; k <= length; k++){
			ee_console_out_radix((EE_UINT8)radio_msg[k], 16);
		}*/
		//insertArr(receiveBuffer_ptr, radio_msg, length);
		//ee_console_out_array(receiveBuffer_ptr->arr, length, 16);		
	} else {
		 /* CRC failed */
		/* chris TODO: Make something: notify to upper layer (raise an error) or ignore (return immediately) */
//EE_leds_off();
//EE_led_0_on();
//for(;;);
		return;
	}		
		
	//check the frame type of the received packet


	/* Parse the data type Field */
	switch( ((EE_UINT8)radio_msg[1] & 0x7) )
	{
	
		case TYPE_BEACON: 
			#ifdef OPENZB_DEBUG
			_openZB_debug_stats.received_beacon_packets++;
			#endif
			/* chris TODO: check lenght */
			memcpy(&mac_beacon_rxmpdu, radio_msg, length * sizeof(EE_UINT8));
			process_beacon(lqi);
			break;

		case TYPE_DATA: 	
//EE_leds_off(); EE_led_0_on(); for(;;);
			#ifdef OPENZB_DEBUG
			_openZB_debug_stats.received_data_packets++;
			#endif
			rx_data = insertq(receiveBuffer_ptr);
			if(rx_data == 0)
				return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
			memcpy(rx_data,radio_msg,length * sizeof(EE_UINT8));
			ActivateTask(DataFrameDispatcher);
			return;
						
		case TYPE_ACK:  
			#ifdef OPENZB_DEBUG
			_openZB_debug_stats.received_ack_packets++;
			#endif
			rx_data = insertq(receiveBuffer_ptr);
			if(rx_data == 0)
				return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
			memcpy(rx_data,radio_msg,length * sizeof(EE_UINT8));
			ActivateTask(AckFrameDispatcher);
			return;
						
		case TYPE_CMD: 	
			#ifdef OPENZB_DEBUG
			_openZB_debug_stats.received_command_packets++;
			#endif
			rx_data = insertq(receiveBuffer_ptr);
			if(rx_data == 0)
				return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
			memcpy(rx_data,radio_msg,length * sizeof(EE_UINT8));
			ActivateTask(CmdFrameDispatcher);
			return;

		default: 
			#ifdef OPENZB_DEBUG
			_openZB_debug_stats.received_invalid_packets++;
			#endif
			_openZB_raise_error(OPENZB_ERR_INVALID_PACKET);
			break;
	}

	
	//call the phy layer to send the data
	//EE_UINT8 PD_DATA_request(EE_UINT8 psduLenght, EE_UINT8* psdu)
		
}


TASK (ReadDispatcher){
	read_Data();
}

TASK (DataFrameDispatcher){
	process_data();
}

TASK(AckFrameDispatcher){
	process_ack();
}

TASK (CmdFrameDispatcher){
	process_cmd();
}

