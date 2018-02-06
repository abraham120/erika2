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
* $Id: MCPS_DATA.c,v 1.14 2008/07/14 10:48:34 chris Exp $
* $Log: MCPS_DATA.c,v $
* Revision 1.14  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.13  2008/07/11 15:01:46  chris
* Comment address assignement for frame_pkt which is NULL in case of GTS (should be fixed)
*
* Revision 1.12  2008/07/08 18:20:05  chris
* BUG-FIX: checking return value for queue functions which was 0 ad put into a pointer (insertq, getq, removeq)
*
* Revision 1.11  2008/07/08 13:47:35  chris
* BUG-FIX: Use -1 instead of 0 to force the crate_data_frame to use CAP for sending
*
* Revision 1.10  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


/**
 * MCPS-DATA-Service Access Point
 *
 *pag 56
 */

#include "string.h"
#include "mac/Mac.h"
#include "mac/MCPS_DATA.h"
#include "mac/mac_func.h"
#include "frame_format.h"
#include "mac/mac_enumerations.h"
#include "common/queue.h"
#include "common/console.h"

extern macPIB mac_PIB;

extern EE_UINT8 PANCoordinator;

extern c_queue *sendBuffer_ptr;

extern EE_UINT8 on_sync;
extern GTSinfoEntryType GTS_db[7];
extern EE_UINT8 s_GTSss;
extern MPDU gts_send_buffer[GTS_SEND_BUFFER_SIZE];
extern gts_slot_element gts_slot_list[7];
extern EE_UINT8 available_gts_index[GTS_SEND_BUFFER_SIZE];
extern EE_UINT8 available_gts_index_count;
extern EE_UINT8 gts_send_buffer_count;
extern EE_UINT8 gts_send_buffer_msg_in;

EE_UINT8 MCPS_DATA_request(EE_UINT8 SrcAddrMode, EE_UINT16 SrcPANId, EE_UINT32 SrcAddr[], EE_UINT8 DstAddrMode, EE_UINT16 DestPANId, EE_UINT32 DstAddr[], EE_UINT8 msduLength, EE_UINT8 msdu[],EE_UINT8 msduHandle, EE_UINT8 TxOptions)
{
	EE_UINT8 i;
	//check conditions on page 58
	if (mac_PIB.macShortAddress == 0xffff)
		return 0;
			
	#ifdef DEVICE_TYPE_COORDINATOR 
		
		if (get_txoptions_gts(TxOptions) == 1)
		{
		//GTS TRANSMISSION
			for (i=0 ; i < 7 ; i++)
			{
				//SEARCH FOR A VALID GTS
				if ( GTS_db[i].DevAddressType == (EE_UINT16)DstAddr[1] && GTS_db[i].direction == 1 && GTS_db[i].gts_id != 0)
				{
						///printfUART("BUFFER UNTIL GTS SLOT n: %i ss: %i\n",number_time_slot,GTS_db[valid_gts].starting_slot);
						create_data_frame(SrcAddrMode, SrcPANId, SrcAddr, DstAddrMode, DestPANId, DstAddr, msduLength, msdu, msduHandle, TxOptions,i,1); //pass the GTS_db position of the slot
					//RARS SIGNAL MCPSDATA CONFIRM??
					return 1;
					
				}
			}
		}
	
		else
		{
		//PAN COORDINATOR OPERATION
		//NORMAL TRANSMISSION	
			create_data_frame(SrcAddrMode, SrcPANId, SrcAddr, DstAddrMode, DestPANId, DstAddr, msduLength, msdu, msduHandle, TxOptions,-1,0);
		}
	#endif	
	
	#ifdef DEVICE_TYPE_END_DEVICE 
		//NON PAN COORDINATOR OPERATION
		//check if it a gts transmission
		if (get_txoptions_gts(TxOptions) == 1)
		{
			
			
		//GTS TRANSMISSIONs_GTSss
		////ee_console_out_str("\ngtssssss:\n");
		////ee_console_out16_radix(s_GTSss,16);
			if (s_GTSss == 0x00)
				{
					
					////ee_console_out_str("\nNO VALID GTS");
				//	signal MCPS_DATA.confirm(msduHandle, MAC_INVALID_GTS);
				}
			else
				{
					if (on_sync == 1 && s_GTSss > 0)
						create_data_frame(SrcAddrMode, SrcPANId, SrcAddr, DstAddrMode, DestPANId, DstAddr, msduLength, msdu, msduHandle, TxOptions,s_GTSss,0);
				////ee_console_out_str("\ncreate dataframe gts");
				}
		}
		else
		{	
			//NORMAL TRANSMISSION	
			create_data_frame(SrcAddrMode, SrcPANId, SrcAddr, DstAddrMode, DestPANId, DstAddr, msduLength, msdu, msduHandle, TxOptions,-1,0);
		}
	#endif

return 1;
}  

void create_data_frame(EE_UINT8 SrcAddrMode, EE_UINT16 SrcPANId, EE_UINT32 SrcAddr[], EE_UINT8 DstAddrMode, EE_UINT16 DestPANId, EE_UINT32 DstAddr[], EE_UINT8 msduLength, EE_UINT8 msdu[],EE_UINT8 msduHandle, EE_UINT8 TxOptions,EE_INT8 on_gts_slot,EE_UINT8 pan)
{
	
	dest_short *dest_short_ptr;
	dest_long *dest_long_ptr;
	
	source_short *source_short_ptr;
	source_long *source_long_ptr;

	//intra_pan_source_short *intra_pan_source_short_ptr;
	//intra_pan_source_long *intra_pan_source_long_ptr;
	
	EE_UINT8 current_gts_element_count=0;
	
	//CHECK
	EE_UINT8 intra_pan=0;
	EE_UINT8 data_len=0;
		
	MPDU *frame_pkt=NULL;
	
	
	EE_UINT16 frame_control;
	

	
	//RARS todo
	
	//decision of the buffer where to store de packet creation
	if (on_gts_slot >= 0 )
	{
	
		#ifdef DEVICE_TYPE_COORDINATOR
		//setting the coordinator gts frame pointer
			
			//get the number of frames in the gts_slot_list
			current_gts_element_count = gts_slot_list[on_gts_slot].element_count;
			
			if (current_gts_element_count  == GTS_SEND_BUFFER_SIZE || available_gts_index_count == 0)
			{
				//////////printfUART("FULL\n","");
				MCPS_DATA_confirm(0x00, MAC_TRANSACTION_OVERFLOW);
				return;
			}
			else
			{
				//frame_pkt = (MPDU *) &gts_send_buffer[available_gts_index[available_gts_index_count]];
			}
			
		#endif
		
		#ifdef DEVICE_TYPE_END_DEVICE
		 //NON PAN COORDINATOR
		//setting the device gts frame pointer
		
			if(gts_send_buffer_count == GTS_SEND_BUFFER_SIZE)
			{
				MCPS_DATA_confirm(0x00, MAC_TRANSACTION_OVERFLOW);
				return;
			}
			if (gts_send_buffer_msg_in == GTS_SEND_BUFFER_SIZE)
				gts_send_buffer_msg_in=0;
			////ee_console_out_str("\ndevenddevice");
				//frame_pkt = (MPDU *) &gts_send_buffer[gts_send_buffer_msg_in];
		
		#endif
		
	}//END IF GTS
	
	else
	{
		//CREATE NORMAL TRANSMISSION PACKET POINTER //returns 0 is full
		frame_pkt = (MPDU *)insertq(sendBuffer_ptr);
	
		if (frame_pkt == 0)
			{
		MCPS_DATA_confirm(0x00, MAC_TRANSACTION_OVERFLOW);
		return;
		}
	
	}
	
	//creation of addressing fields
	if (intra_pan == 0 )
	{
	
		if ( DstAddrMode > 1 && SrcAddrMode > 1 )
		{
			// Destination LONG - Source LONG		NOTE: NOT TESTED YET!
			if (DstAddrMode == LONG_ADDRESS && SrcAddrMode == LONG_ADDRESS)
			{
				dest_long_ptr = (dest_long *) &frame_pkt->data[0];
				source_long_ptr = (source_long *) &frame_pkt->data[DEST_LONG_LEN];
				
				dest_long_ptr->destination_PAN_identifier=DestPANId;
				dest_long_ptr->destination_address0=DstAddr[1];
				dest_long_ptr->destination_address1=DstAddr[0];
				
				source_long_ptr->source_PAN_identifier=SrcPANId;
				source_long_ptr->source_address0=SrcAddr[1];
				source_long_ptr->source_address1=SrcAddr[0];
				
				data_len = 20;
			}
			
			// Destination SHORT - Source LONG		NOTE: NOT TESTED YET!
			if ( DstAddrMode == SHORT_ADDRESS && SrcAddrMode == LONG_ADDRESS )
			{
				dest_short_ptr = (dest_short *) &frame_pkt->data[0];
				source_long_ptr = (source_long *) &frame_pkt->data[DEST_SHORT_LEN];
				
				dest_short_ptr->destination_PAN_identifier=DestPANId;
				dest_short_ptr->destination_address=(EE_UINT16)DstAddr[1];
				
				source_long_ptr->source_PAN_identifier=SrcPANId;
				source_long_ptr->source_address0=SrcAddr[1];
				source_long_ptr->source_address1=SrcAddr[0];
				
				data_len = 14;
			}
			// Destination LONG - Source SHORT		NOTE: NOT TESTED YET!
			if ( DstAddrMode == LONG_ADDRESS && SrcAddrMode == SHORT_ADDRESS )
			{
				dest_long_ptr = (dest_long *) &frame_pkt->data[0];
				source_short_ptr = (source_short *) &frame_pkt->data[DEST_LONG_LEN];
				
				dest_long_ptr->destination_PAN_identifier=DestPANId;
				dest_long_ptr->destination_address0=DstAddr[1];
				dest_long_ptr->destination_address1=DstAddr[0];
				
				source_short_ptr->source_PAN_identifier=SrcPANId;
				source_short_ptr->source_address=(EE_UINT16)SrcAddr[1];
				
				data_len = 14;
			}
			
			
			//Destination SHORT - Source SHORT
			if ( DstAddrMode == SHORT_ADDRESS && SrcAddrMode == SHORT_ADDRESS )	
			{
				/* chris TODO: to uncomment this lines we need to fix the frame_pkt* in case of GTS at the beginning of this function

				dest_short_ptr = (dest_short *) &frame_pkt->data[0];
				source_short_ptr = (source_short *) &frame_pkt->data[DEST_SHORT_LEN];
				
				dest_short_ptr->destination_PAN_identifier=DestPANId;
				dest_short_ptr->destination_address=(EE_UINT16)DstAddr[1];
				
				source_short_ptr->source_PAN_identifier=SrcPANId;
				source_short_ptr->source_address=(EE_UINT16)SrcAddr[1];
				*/
				
				data_len = 8;
			}
		}
		
		if ( DstAddrMode == 0 && SrcAddrMode > 1 )
		{
				
			if (SrcAddrMode == LONG_ADDRESS)
			{//Source LONG
				source_long_ptr = (source_long *) &frame_pkt->data[0];
				
				source_long_ptr->source_PAN_identifier=SrcPANId;
				source_long_ptr->source_address0=SrcAddr[1];
				source_long_ptr->source_address1=SrcAddr[0];
				
				data_len = 10;
			}
			else
			{//Source SHORT

				source_short_ptr = (source_short *) &frame_pkt->data[0];
				
				source_short_ptr->source_PAN_identifier=SrcPANId;
				source_short_ptr->source_address=(EE_UINT16)SrcAddr[1];
				
				data_len = 4;
			}
		}
		
		if ( DstAddrMode > 1 && SrcAddrMode == 0 )
		{
			if (DstAddrMode == LONG_ADDRESS)
			{//Destination LONG
				dest_long_ptr = (dest_long *) &frame_pkt->data[0];
		
				dest_long_ptr->destination_PAN_identifier=DestPANId;
				dest_long_ptr->destination_address0=DstAddr[1];
				dest_long_ptr->destination_address1=DstAddr[0];

				data_len = 10;
			}
			else
			{//Destination SHORT
				dest_short_ptr = (dest_short *) &frame_pkt->data[0];

				dest_short_ptr->destination_PAN_identifier=DestPANId;
				dest_short_ptr->destination_address=(EE_UINT16)DstAddr[1];
				
				data_len = 4;
			}
		}

		/*TODO: check (DstAddrMode==0 && SrcAddrMode==0) and raise an error if is not valid! */
	}
	else
	{
	//intra_pan == 1

	}
	
	
	//copy the packet payload
	if(on_gts_slot >= 0)
		memcpy(&gts_send_buffer[gts_send_buffer_msg_in].data[data_len],&msdu[0],msduLength*sizeof(EE_UINT8));
	else
		memcpy(&frame_pkt->data[data_len],&msdu[0],msduLength*sizeof(EE_UINT8));
		
		//ee_console_out_str("\nmemcpy");
	//ee_console_out16_radix(data_len,16);
	//ee_console_out16_radix(msduLength,16);
	//ee_console_out16_radix(msdu[6],16);
	//ee_console_out16_radix(gts_send_buffer[gts_send_buffer_msg_in].data[16],16);
		
	if(on_gts_slot >= 0)
		{
			//preparing a GTS transmission
			
			
			//gts_send_buffer[gts_send_buffer_msg_in].data[5+data_len]=1;
			////////////printfUART("GTS send slt: %i count %i %u\n",on_gts_slot,gts_slot_list[15-on_gts_slot].element_count,mac_PIB.macDSN);
			gts_send_buffer[gts_send_buffer_msg_in].length = data_len + msduLength + MPDU_HEADER_LEN;
			frame_control = set_frame_control(TYPE_DATA,0,0,1,intra_pan,DstAddrMode,SrcAddrMode);
			gts_send_buffer[gts_send_buffer_msg_in].frame_control1 =(EE_UINT8)( frame_control);
			gts_send_buffer[gts_send_buffer_msg_in].frame_control2 =(EE_UINT8)( frame_control >> 8);
			
			gts_send_buffer[gts_send_buffer_msg_in].seq_num = mac_PIB.macDSN;
			mac_PIB.macDSN++;
						
			//ADDING DATA TO THE GTS BUFFER
			
					#ifdef DEVICE_TYPE_COORDINATOR
					
						gts_slot_list[on_gts_slot].element_count ++;
						gts_slot_list[on_gts_slot].gts_send_frame_index[gts_slot_list[on_gts_slot].element_in] = available_gts_index[available_gts_index_count];
						//gts_slot_list[i].length = frame_pkt->length;
						
						gts_slot_list[on_gts_slot].element_in ++;
						
						if (gts_slot_list[on_gts_slot].element_in == GTS_SEND_BUFFER_SIZE)
							gts_slot_list[on_gts_slot].element_in=0;
						
						available_gts_index_count --;
						
						//RARS todo if i am at the slot i should transmit immediatly...
						
						//current_gts_pending_frame++;
					#endif
					#ifdef DEVICE_TYPE_END_DEVICE
					
//						gts_send_buffer[gts_send_buffer_msg_in].data[6+data_len]=1;
//						gts_send_buffer[gts_send_buffer_msg_in].data[7+data_len]=gts_send_buffer_count;
//						gts_send_buffer[gts_send_buffer_msg_in].data[8+data_len]=gts_send_buffer_msg_in;
//						gts_send_buffer[gts_send_buffer_msg_in].data[9+data_len]=2;		
//						gts_send_buffer[gts_send_buffer_msg_in].data[10+data_len]=data_len;				
						gts_send_buffer_count++;
						gts_send_buffer_msg_in++;
						
						////////////printfUART("end c %i %i %i \n",gts_send_buffer_count,gts_send_buffer_msg_in,gts_send_buffer_msg_out);
					#endif
		}		
		
		else 
		{
		frame_pkt->length = data_len + msduLength + MPDU_HEADER_LEN;
				
		frame_control = set_frame_control(TYPE_DATA,0,0,get_txoptions_ack(TxOptions),intra_pan,DstAddrMode,SrcAddrMode);
		frame_pkt->frame_control1 =(EE_UINT8)( frame_control);
		frame_pkt->frame_control2 =(EE_UINT8)( frame_control >> 8);
				
		frame_pkt->seq_num = mac_PIB.macDSN;
				
		mac_PIB.macDSN++;
	
		send_frame_csma();
		}	
		
return;
}






