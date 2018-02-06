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
* $Id: Mac.c,v 1.47 2008/07/30 16:49:30 chris Exp $
* $Log: Mac.c,v $
* Revision 1.47  2008/07/30 16:49:30  chris
* Use sync-to-beacon mechanism (callback function called on beacon - received or sent - )
*
* Revision 1.46  2008/07/17 17:37:51  francesco
* Scicos update
*
* Revision 1.45  2008/07/16 09:04:03  chris
* BUG-FIX: use sd_fired_alarms in a non-periodic way, set it as timeout at the beginning of the beacon interval; Change GTS allocation
*
* Revision 1.44  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.43  2008/07/11 15:10:27  chris
* In case of coordiantor current_time_slot initialized to 0 every beacon firing.
* In case of coordiantor do not cancel time_slot_firing alarm (should be cheched in future).
* In case of CSMA_CA check I_AM_IN_CAP in perform_csma_ca_slotted function before sending message packet.
* In case of CSMA_CA FAIL we commented the removeq function (should be cheched in future).
*
* Revision 1.42  2008/07/08 18:20:05  chris
* BUG-FIX: checking return value for queue functions which was 0 ad put into a pointer (insertq, getq, removeq)
*
* Revision 1.41  2008/07/08 13:46:16  chris
* Check if the sender is in the CAP (variable I_AM_IN_CAP) while sending in slotted CSMA-CA
*
* Revision 1.40  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


/*
 * 
 * MAC Layer Main Implementation file
 * 
 * 
 */

#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "string.h"

//#include "hal/hal_defines.h"
#include "phy/phy.h"
#include "mac/Mac.h"
#include "nwl/Nwl.h" /* TODO: used for notify sync at upper layer, in future the use a  common .h ? */

#include "mac/mac_const.h"
#include "mac/mac_enumerations.h"

#include "frame_format.h"
#include "mac/mac_func.h"
#include "mac/gts_mechanism.h"
#include "common/console.h"
#include "common/queue.h"


#include "common/cc2420.h"
#include "hal/hal_cc2420.h"

#include "ieee802154alarms/ieee802154alarms.h"



#ifndef FLEX_DEVICE_ADDRESS_1 
#define FLEX_DEVICE_ADDRESS_1 0x0002
#endif
#ifndef FLEX_DEVICE_ADDRESS_2 
#define FLEX_DEVICE_ADDRESS_2 0x0003
#endif
#ifndef FLEX_DEVICE_ADDRESS_3 
#define FLEX_DEVICE_ADDRESS_3 0x0004
#endif
#ifndef FLEX_DEVICE_ADDRESS_4 
#define FLEX_DEVICE_ADDRESS_4 0x0005
#endif
#ifndef FLEX_DEVICE_ADDRESS 
#define FLEX_DEVICE_ADDRESS FLEX_DEVICE_ADDRESS_1
#endif

#ifdef DEVICE_TYPE_COORDINATOR
unsigned int openzb_device_addresses[4] = {
	FLEX_DEVICE_ADDRESS_1, 
	FLEX_DEVICE_ADDRESS_2, 
	FLEX_DEVICE_ADDRESS_3, 
	FLEX_DEVICE_ADDRESS_4
};
unsigned int openzb_device_address = 0x00FF;
#else
unsigned int openzb_device_address = FLEX_DEVICE_ADDRESS;
#endif



EE_UINT8 GTS_TRANSMITING=0;

/*****************************************************/
/*				GENERAL DECLARATIONS     			 */
/*****************************************************/  

//metrics


//total bytes effectivelly sent by MAC on a successfull CSMA/CA attemp
extern EE_UINT32 total_bytes_send_mac;
//total packets effectivelly sent by MAC
extern EE_UINT16 packet_count_mac;
//number of failed CSMA CA attemps - in packet count
extern EE_UINT16 packet_csmaca_fail;


extern EE_UINT32 sd_ticks; //chris TODO: check, maybe we must use the set alarm in the other file!

//local extended address
EE_UINT32 aExtendedAddress0;
EE_UINT32 aExtendedAddress1;

EE_UINT16 beaconnumber = 0;

macPIB mac_PIB;

//If the the MLME receives a start request the node becomes a pan coordinator and starts transmiting beacons 
EE_UINT8 PANCoordinator = 0;

//(0 NO beacon transmission; 1 beacon transmission);
EE_UINT8 Beacon_enabled_PAN = 0;

//(RESET) when the reset command arrives it checks whether or not to reset the PIB
EE_UINT8 SetDefaultPIB=0;
	
//use security
EE_UINT8 SecurityEnable=0;

EE_UINT8 backoff_count=0;
EE_UINT16 timer2_count=0;

//give the current time slot number
volatile EE_UINT8 current_time_slot=0;

/*****************************************************/
/*				General Buffers          			 */
/*****************************************************/ 

c_queue sendBuffer __attribute__((far)), receiveBuffer __attribute__((far));

c_queue *sendBuffer_ptr, *receiveBuffer_ptr;

void init_MacPIB(); 

//Internal MAC functions
/*****************************************************/
/*				BEACON MANAGEMENT  		             */
/*****************************************************/ 

	//beacon transmission memory position
	MPDU mac_beacon_txmpdu;
	MPDU *mac_beacon_txmpdu_ptr;
	
	//beacon reception memory position
	MPDU mac_beacon_rxmpdu;
	MPDU *mac_beacon_rxmpdu_ptr;







/*****************************************************/
/*				TIMER VARIABLES					 */
/*****************************************************/  
	/***************Variables*************************/
	EE_UINT32 response_wait_time;
	
	//Beacon Interval
	EE_UINT32 BI;
	//Superframe duration
	EE_UINT32 SD;
	
	//timer variables
	EE_UINT32 time_slot; //backoff boundary timer
	EE_UINT32 backoff;  //backoff timer


	void set_alarm_intervals();


/*****************************************************/
/*				RECEPTION AND TRANSMISSION		     */
/*****************************************************/  

	EE_UINT8 ackwait_period;
	
	
	EE_UINT8 I_AM_IN_CAP=0;
	EE_UINT8 I_AM_IN_CFP=0;
	EE_UINT8 I_AM_IN_IP=0;

	ACK mac_ack;
	ACK *mac_ack_ptr;
	
	void build_ack(EE_UINT8 sequence,EE_UINT8 frame_pending);

/*****************************************************/
/*				SYNCHRONIZATION		     */
/*****************************************************/  
	/***************Variables*************************/
	//(SYNC)the device will try to track the beacon ie enable its receiver just before the espected time of each beacon
	EE_UINT8 TrackBeacon=0;
	EE_UINT8 beacon_processed=0;
	//beacon loss indication
	//EE_UINT8 beacon_loss_reason;
	
	//(SYNC)the device will try to locate one beacon
	EE_UINT8 findabeacon=0;
	//(SYNC)number of beacons lost before sending a Beacon-Lost indication comparing to aMaxLostBeacons
	EE_UINT8 missed_beacons=0;
	//boolean variable stating if the device is synchonized with the beacon or not
	EE_UINT8 on_sync=0;





/*****************************************************/
/*				GTS Variables	//RARS				     */
/*****************************************************/  
	//GTS descriptor variables, coordinator usage only
	EE_UINT8 final_CAP_slot=15;
	EE_UINT8 GTS_descriptor_count=0;
	GTSinfoEntryType GTS_db[7] __attribute__((far));
	EE_UINT8 GTS_startslot=16;
	EE_UINT8 GTS_id=0x01;
	//null gts descriptors
	GTSinfoEntryType_null GTS_null_db[7] __attribute__((far));
	EE_UINT8 GTS_null_descriptor_count=0;

	//COORDINATOR GTS BUFFER 	
	gts_slot_element gts_slot_list[7] __attribute__((far));
	EE_UINT8 available_gts_index[GTS_SEND_BUFFER_SIZE] __attribute__((far));
	EE_UINT8 available_gts_index_count;
	EE_UINT8 coordinator_gts_send_pending_data=0;
	EE_UINT8 coordinator_gts_send_time_slot=0;
	

	EE_UINT8 gts_schedule[16] __attribute__((far)); //for translation between timeslots and gtss

	EE_UINT8 gts_confirm; //confirms that the GTS slot is present in the beacon
	
	EE_UINT8 GTS_specification;
	EE_UINT8 gts_expiration;
	
	//node GTS variables
	// 1 GTS for transmit
	EE_UINT8 s_GTSss=0;           //send gts start slot
	EE_UINT8 s_GTS_length=0;		 //send gts length
	
	//1 GTS for receive
	EE_UINT8 r_GTSss=0;			 //receive gts start slot
	EE_UINT8 r_GTS_length=0;		 //receive gts lenght
	
	//used to state that the device is on its transmit slot
	EE_UINT8 on_s_GTS=0;
	//used to state that the device is on its receive slot
	EE_UINT8 on_r_GTS=0;
	
	//used to determine if the next time slot is used for transmission
	EE_UINT8 next_on_s_GTS=0;
	//used to determine if the next time slot is used for reception
	EE_UINT8 next_on_r_GTS=0;
	
	//variable stating if the coordinator allow GTS allocations
	EE_UINT8 allow_gts=1;
	
	//gts buffer used to store the gts messages both in COORDINATOR and NON COORDINATOR
	MPDU gts_send_buffer[GTS_SEND_BUFFER_SIZE] __attribute__((far));
	
	//NON PAN COORDINATOR BUFFER management
	//buffering for sending
	EE_UINT8 gts_send_buffer_count=0;
	EE_UINT8 gts_send_buffer_msg_in=0;
	EE_UINT8 gts_send_buffer_msg_out=0;
	EE_UINT8 gts_send_pending_data=0;
	





/*****************************************************/
/*				CSMA VARIABLES					 */
/*****************************************************/  	
	/***************Variables*************************/	

	EE_UINT8 csma_slotted=1;

	//DEFERENCE CHANGE
	EE_UINT8 cca_deference = 0;
	EE_UINT8 backoff_deference = 0;
	
	//STEP 2
	EE_UINT8 delay_backoff_period;
	EE_UINT8 csma_delay=0;
	EE_UINT8 csma_locate_backoff_boundary=0;
	EE_UINT8 csma_cca_backoff_boundary=0;
	
	//Although the receiver of the device is enabled during the channel assessment portion of this algorithm, the
	//device shall discard any frames received during this time.
	EE_UINT8 performing_csma_ca=0;
	
	//CSMA-CA variables
	EE_UINT8 BE; //backoff exponent
	EE_UINT8 CW; //contention window (number of backoffs to clear the channel)
	EE_UINT8 NB; //number of backoffs

	/***************Functions Definition***************/	
	
	void init_csma_ca(EE_UINT8 slotted);
	
	void perform_csma_ca();
	
	void perform_csma_ca_unslotted();
	
	void perform_csma_ca_slotted();
	
	//task void start_csma_ca_slotted();
	
	void perform_csma_ca_unslotted();
	
	void backoff_fired_check_csma_ca();

	EE_UINT8 check_csma_ca_backoff_send_conditions(EE_UINT32 delay_backoffs);
	EE_UINT8 check_csma_ca_send_conditions(EE_UINT8 frame_length,EE_UINT8 frame_control1);
	
	//other functions declaration
	EE_UINT8 calculate_ifs(EE_UINT8 pk_length);
	
	#ifndef max
	#define max(a,b) ((a) >= (b) ? (a) : (b))
	#endif
	#ifndef min
	#define min(a,b) ((a) <= (b) ? (a) : (b))
	#endif

/*********************************************************************************/

void set_alarm_intervals()
{
	ackwait_period = ((mac_PIB.macAckWaitDuration * 4.0 ) / 250.0) * 3;

	response_wait_time = ((aResponseWaitTime * 4.0) / 250.0) * 2;
		
	BI = aBaseSuperframeDuration * powf(2,mac_PIB.macBeaconOrder);
	SD = aBaseSuperframeDuration * powf(2,mac_PIB.macSuperframeOrder);
	
	//backoff_period
	backoff = aUnitBackoffPeriod;
	//backoff_period_boundary		
	time_slot = SD / NUMBER_TIME_SLOTS;
	
	ieee802145alarms_set_bi_sd(BI,SD);

return;
}

void init_mac()
{
	
	//beacon transmission
	mac_beacon_txmpdu_ptr = &mac_beacon_txmpdu;
	
	//beacon reception
	mac_beacon_rxmpdu_ptr = &mac_beacon_rxmpdu;
	
	//ack frame
	mac_ack_ptr= &mac_ack;

	//initialize buffer pointers
	sendBuffer_ptr = &sendBuffer;
	receiveBuffer_ptr = &receiveBuffer;
	
	initq(sendBuffer_ptr);
	initq(receiveBuffer_ptr);
	
	
	//initialize the MAC PAN Information BASE
	init_MacPIB();
	
	//RARS
	#ifdef DEVICE_TYPE_COORDINATOR
		init_GTS_db();
		init_GTS_null_db();
		init_gts_slot_list();
		init_available_gts_index();
		
		//add_gts_entry(4,1,0x1234,7);		
		//add_gts_entry(4,0,0x0002,7);
		add_gts_entry(1,1,0x1234,10);		
		add_gts_entry(1,1,0x1234,11);		
		add_gts_entry(1,1,0x1234,12);		
		add_gts_entry(1,1,0x1234,13);		
		add_gts_entry(1,0,openzb_device_addresses[0],10);
		add_gts_entry(1,0,openzb_device_addresses[1],11);
		add_gts_entry(1,0,openzb_device_addresses[2],12);
		add_gts_entry(1,0,openzb_device_addresses[3],13);
	#endif
	

	init_phy();
	
	
	#ifdef DEVICE_TYPE_END_DEVICE
		//ee_console_out_str("End Device");
		set_alarm_intervals();
		ieee802145alarms_start();
	#endif
	return;
}




/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/************************		BUILD FRAMES FUNCTIONS   			**********************************/
/*****************************************************************************************************/ 
/*****************************************************************************************************/
/*****************************************************************************************************/
void build_ack(EE_UINT8 sequence,EE_UINT8 frame_pending)
{
	EE_UINT16 frame_control;
	
	mac_ack_ptr->length = ACK_LENGTH;
	//mac_ack_ptr->frame_control = set_frame_control(TYPE_ACK,0,frame_pending,0,0,0,0);
	
	frame_control = set_frame_control(TYPE_ACK,0,frame_pending,0,0,0,0);
	mac_ack_ptr->frame_control1 =(EE_UINT8)( frame_control);
	mac_ack_ptr->frame_control2 =(EE_UINT8)( frame_control >> 8);
	
	mac_ack_ptr->seq_num = sequence;
	
	PD_DATA_request(mac_ack_ptr->length,(EE_UINT8*)mac_ack_ptr);
	
}


void create_beacon()
{
	
	EE_UINT8 i;
	EE_UINT8 packet_length = 25;
	int data_count=0;
	//int pending_data_index=0;
	//MPDU* pkt_ptr=0;
	//pending frames
	EE_UINT8 short_addr_pending=0;
	EE_UINT8 long_addr_pending=0;
		
	EE_UINT8 gts_directions=0x00;
	
	EE_UINT16 frame_control;

	//beacon addressing structure, only for the intra pan beaconing		
	beacon_addr_short *mac_beacon_addr_short_ptr;

	mac_beacon_addr_short_ptr = (beacon_addr_short*) &mac_beacon_txmpdu.data;
		
	mac_beacon_txmpdu_ptr->length = 15;
	
	//creating the 16 bit frame control
	frame_control = set_frame_control(TYPE_BEACON,0,0,0,1,SHORT_ADDRESS,SHORT_ADDRESS);
		
	mac_beacon_txmpdu_ptr->frame_control1 = (EE_UINT8)( frame_control);
	mac_beacon_txmpdu_ptr->frame_control2 = (EE_UINT8)( frame_control >> 8);
	
	//assign the sequence number
	mac_beacon_txmpdu_ptr->seq_num = mac_PIB.macBSN;
	mac_PIB.macBSN++;
	
	//short address assignment
	mac_beacon_addr_short_ptr->destination_PAN_identifier= mac_PIB.macPANId;
	mac_beacon_addr_short_ptr->destination_address = 0xffff;
	mac_beacon_addr_short_ptr->source_address = mac_PIB.macShortAddress;
	if (mac_PIB.macShortAddress == 0x0000)
	{	//the device is the PAN Coordinator
		mac_beacon_addr_short_ptr->superframe_specification = set_superframe_specification(mac_PIB.macBeaconOrder,(EE_UINT8)mac_PIB.macSuperframeOrder,final_CAP_slot,0,1,mac_PIB.macAssociationPermit);
	}
	else
	{
		mac_beacon_addr_short_ptr->superframe_specification = set_superframe_specification(mac_PIB.macBeaconOrder,(EE_UINT8)mac_PIB.macSuperframeOrder,final_CAP_slot,0,1,mac_PIB.macAssociationPermit);
	}
	
	//assign the gts specification field
	mac_beacon_txmpdu_ptr->data[8] = set_gts_specification(GTS_descriptor_count,mac_PIB.macGTSPermit);
	
	//assign the pending address specification field
	mac_beacon_txmpdu_ptr->data[9] = set_pending_address_specification(short_addr_pending,long_addr_pending);
	
	//moving in the position of the beacon data payload	
	data_count = 9;
	//after the addressing the the beacon fields the beacon has the size of 15 bytes
	packet_length = 15;
		
	//BUILDING the GTS DESCRIPTORS
	//RARS todo
	
	if( (GTS_descriptor_count + GTS_null_descriptor_count) > 0 )
	{
		data_count++;
				
		for(i=0; i< 7 ; i++)
		{
		
			if( GTS_db[i].gts_id != 0x00 && GTS_db[i].DevAddressType != 0x0000) 
			{
				
			mac_beacon_txmpdu_ptr->data[data_count] = (EE_UINT8) (GTS_db[i].DevAddressType );
		
		//ee_console_out16_radix(mac_beacon_txmpdu_ptr->data[data_count], 16);
				data_count++;
			
				mac_beacon_txmpdu_ptr->data[data_count] = (EE_UINT8) (GTS_db[i].DevAddressType >> 8 );;
				//////////////printfUART("B gts %i\n",  GTS_db[i].DevAddressType ); 
				
		//ee_console_out16_radix(mac_beacon_txmpdu_ptr->data[data_count], 16);
				
				data_count++;
				
			mac_beacon_txmpdu_ptr->data[data_count] = (EE_UINT8) set_gts_descriptor(GTS_db[i].starting_slot,GTS_db[i].length);
				data_count++;
			 
			 
				
				packet_length = packet_length + 3;
				
				if ( GTS_db[i].direction == 1 )
				{
					gts_directions = gts_directions | (1 << i); 
				}
				else
				{
					gts_directions = gts_directions | (0 << i); 
				}
				//////printfUART("dir %i\n", gts_directions); 
			}
		}
		mac_beacon_txmpdu_ptr->data[9] = gts_directions;
		//CHECK
		packet_length++;
		//BUILDING the NULL GTS DESCRIPTORS
		/*
		if ( GTS_null_descriptor_count > 0 )
		{
			for(i=0; i< 7 ; i++)
			{
				if( GTS_null_db[i].DevAddressType != 0x0000) 
				{
					mac_beacon_txmpdu_ptr->data[data_count] = GTS_null_db[i].DevAddressType;
					//////////////printfUART("B gts %i\n", (GTS_db[i].DevAddressType >> 8 ) ); 
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count] = (GTS_null_db[i].DevAddressType >> 8 );
					//////////////printfUART("B gts %i\n",  GTS_db[i].DevAddressType ); 
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count] = 0x00;
					data_count++;
					//////////////printfUART("B gts %i\n", set_gts_descriptor(GTS_db[i].starting_slot,GTS_db[i].length) ); 
					packet_length = packet_length +3;
				}
			}
		}
		*/
		//resetting the GTS specification field
		mac_beacon_txmpdu_ptr->data[8] = set_gts_specification(GTS_descriptor_count + GTS_null_descriptor_count,mac_PIB.macGTSPermit);
		

	}
	
	/*
	pending_data_index = data_count;
	data_count++;
	//IMPLEMENT PENDING ADDRESSES
	//temporary
	//indirect_trans_count =0;
		
	if (indirect_trans_count > 0 )
{
			//IMPLEMENT THE PENDING ADDRESSES CONSTRUCTION

		for(i=0;i<INDIRECT_BUFFER_SIZE;i++)
		{
			if (indirect_trans_queue[i].handler > 0x00)
			{
				pkt_ptr = (MPDU *)&indirect_trans_queue[i].frame;
				//ADD INDIRECT TRANSMISSION DESCRIPTOR
				if(get_fc2_dest_addr(pkt_ptr->frame_control2) == SHORT_ADDRESS)
				{
					short_addr_pending++;
					packet_length = packet_length + 2;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[2];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[3];
					data_count++;
				}
			}
		}
		for(i=0;i<INDIRECT_BUFFER_SIZE;i++)
		{
			if (indirect_trans_queue[i].handler > 0x00)
			{
				if(get_fc2_dest_addr(pkt_ptr->frame_control2) == LONG_ADDRESS)
				{
					long_addr_pending++;
					packet_length = packet_length + 8;

					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[0];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[1];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[2];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[3];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[4];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[5];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[6];
					data_count++;
					mac_beacon_txmpdu_ptr->data[data_count]=pkt_ptr->data[7];
					data_count++;
					
				}
			}
		}
			
	}
	mac_beacon_txmpdu_ptr->data[pending_data_index] = set_pending_address_specification(short_addr_pending,long_addr_pending);
	*/	
	/*
	//adding the beacon payload
	if (mac_PIB.macBeaconPayloadLenght > 0 )
	{
		for (i=0;i < mac_PIB.macBeaconPayloadLenght;i++)
		{
			mac_beacon_txmpdu_ptr->data[data_count] = mac_PIB.macBeaconPayload[i];
			data_count++;
			packet_length++;
		}
	
	
	}
	*/
		
	//short_addr_pending=0;
	//long_addr_pending=0;
		
	mac_beacon_txmpdu_ptr->length = packet_length;
		
return;
}


/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/
/****************************************PACKET PROCESSING FUNCTIONS************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/





void process_beacon(EE_UINT8 ppduLinkQuality)
{
	/*
	ORGANIZE THE PROCESS BEACON FUNCION AS FOLLOWS.
	1- GET THE BEACON ORDER
	2- GET THE SUPERFRAME ORDER
	3- GET THE FINAL CAP SLOT
	4 - COMPUTE SD, BI, TS, BACKOFF PERIOD IN MILLISECONDS
	
	4- SYNCHRONIZE THE NODE BY DOING THE FOLLOWING
		- SET A TIMER IN MS FOR THE FINAL TIME SLOT (SUPERFRAME DURATION) : IT EXPRIES AFTER SD - TX TIME - PROCESS TIME
		- SET A TIMER IN MS FOR THE GTS IF ANY EXIST IT EXPRIES AFTER GTS_NBR * TIME_SLOT - TX TIME - PROCESS TIME 
	*/
	EE_UINT32 SO_EXPONENT;
	EE_UINT32 BO_EXPONENT;
	
	EE_UINT8 i;
	EE_UINT16 gts_descriptor_addr;
	EE_UINT8 data_count;
	
	EE_UINT8 gts_directions;
	EE_UINT8 gts_des_count;
	
	EE_UINT8 gts_ss;
	EE_UINT8 gts_l;
	EE_UINT8 dir;
	EE_UINT8 dir_mask;
	
	//end gts variables

	//function that processes the received beacon
	beacon_addr_short *beacon_ptr;
	
	PANDescriptor pan_descriptor;

	//pending frames
	//EE_UINT8 short_addr_pending=0;
//	EE_UINT8 long_addr_pending=0;

	//sync functions
	EE_UINT16 timer2_count_end=0;
	EE_UINT32 sync_time=0;
	EE_UINT16 new_timer2_count=0;
	EE_UINT8 backoff_elapsed=0;



	beaconnumber++;
	//used in the track beacon
	beacon_processed = 1;
	missed_beacons=0;
	
	
	//ee_console_out_str("1\n");
	//initializing pointer to data structure
	beacon_ptr = (beacon_addr_short*) (mac_beacon_rxmpdu_ptr->data);
	
	
	if( beacon_ptr->source_address != mac_PIB.macCoordShortAddress)
	{
		//return;
	}
	
	//ee_console_out_str("2\n");
	/**********************************************************************************/
	/*					PROCESSING THE SUPERFRAME STRUCTURE							  */
	/**********************************************************************************/
	if (PANCoordinator == 0)
	{
		mac_PIB.macBeaconOrder = get_beacon_order(beacon_ptr->superframe_specification);
		mac_PIB.macSuperframeOrder = get_superframe_order(beacon_ptr->superframe_specification);
		
		
		//mac_PIB.macCoordShortAddress = beacon_ptr->source_address;
		
		////printfUART("BO,SO:%i %i\n",mac_PIB.macBeaconOrder,mac_PIB.macSuperframeOrder);
		
		//mac_PIB.macPANId = beacon_ptr->source_PAN_identifier;
		
		//beacon order check if it changed
		if (mac_PIB.macSuperframeOrder == 0)
		{
			SO_EXPONENT = 1;
		}
		else
		{
			SO_EXPONENT = powf(2,mac_PIB.macSuperframeOrder);
		}
		
		if ( mac_PIB.macBeaconOrder ==0)
		{
			BO_EXPONENT =1;
		}
		else
		{
				BO_EXPONENT = powf(2,mac_PIB.macBeaconOrder);
		}
		BI = aBaseSuperframeDuration * BO_EXPONENT; 
		SD = aBaseSuperframeDuration * SO_EXPONENT; 
		
		//backoff_period
		backoff = aUnitBackoffPeriod;
		time_slot = SD / NUMBER_TIME_SLOTS;
		
		//call TimerAsync.set_bi_sd(BI,SD);
	}	
		
	/**********************************************************************************/
	/*							PROCESS GTS CHARACTERISTICS							  */
	/**********************************************************************************/
		//ee_console_out_str("3\n");
		allow_gts =1;
	
		//initializing the gts variables
		//s_GTSss=0;
		s_GTS_length=0;
		
		//gts_send_buffer_count=0;
		//gts_send_buffer_msg_in=0;
		//gts_send_buffer_msg_out=0;
		//gts_send_pending_data=0;
		
		r_GTSss=0;
		r_GTS_length=0;
		
		final_CAP_slot = 15;


		gts_des_count = (mac_beacon_rxmpdu_ptr->data[8] & 0x0f);
		
		data_count = 9;
		
		final_CAP_slot = 15 - gts_des_count;
		
		if (gts_des_count > 0 )
		{
		data_count = 10; //position of the current data count
		//process descriptors
		
			gts_directions = mac_beacon_rxmpdu_ptr->data[9];
			
			////printfUART("gts_directions:%x\n",gts_directions);
			
			for(i=0; i< gts_des_count; i++)
			{	
				gts_descriptor_addr = (EE_UINT16) mac_beacon_rxmpdu_ptr->data[data_count];
					
				////printfUART("gts_des_addr:%x mac short:%x\n",gts_descriptor_addr,mac_PIB.macShortAddress);
				
				data_count = data_count+2;
				//check if it concerns me
				if (gts_descriptor_addr == mac_PIB.macShortAddress)
				{
					
				
					//confirm the gts request
					//////////////printfUART("packet->data[data_count]: %x\n",packet->data[data_count]);
					//gts_ss = 15 - get_gts_descriptor_ss(packet->data[data_count]);
					gts_ss = get_gts_descriptor_ss(mac_beacon_rxmpdu_ptr->data[data_count]);
					gts_l = get_gts_descriptor_len(mac_beacon_rxmpdu_ptr->data[data_count]);

					if ( i == 0 )
					{
						dir_mask=1;
					}
					else
					{
					
							dir_mask = powf(2,i);
					}
					//////////////printfUART("dir_mask: %x i: %x gts_directions: %x \n",dir_mask,i,gts_directions);
					dir = ( gts_directions & dir_mask);
					if (dir == 0)
					{
						s_GTSss=gts_ss;
						s_GTS_length=gts_l;
		//ee_console_out_str("\nTX SLOT");
		//ee_console_out16_radix(s_GTSss,16);
		
					}
					else
					{

						r_GTSss=gts_ss;
						r_GTS_length=gts_l;
	//ee_console_out_str("\nrx SLOT");
						
					}
				
					////printfUART("PB gts_ss: %i gts_l: %i dir: %i \n",gts_ss,gts_l,dir);
					//////////////printfUART("PB send_s_GTSss: %i send_s_GTS_len: %i\n",send_s_GTSss,send_s_GTS_len);
					
					if ( gts_l == 0 )
					{
						allow_gts=0;
					}

					if (gts_confirm == 1 && gts_l != 0)
					{
						//signal ok
						////printfUART("gts confirm \n","");
						gts_confirm =0;
						//RARS TODO
						//MLME_GTS.confirm(GTS_specification,MAC_SUCCESS);
					}
					else
					{
						//signal not ok
						//////////////printfUART("gts not confirm \n","");
						gts_confirm =0;
						//RARS TODO
						//MLME_GTS.confirm(GTS_specification,MAC_DENIED);
					}
					
				}
				data_count++;	
			}
		}
	
	
	/**********************************************************************************/
	/*							PROCESS PENDING ADDRESSES INFORMATION				  */
	/**********************************************************************************/	
		//this should pass to the network layer
		/*
		
		short_addr_pending=get_number_short(packet->data[data_count]);
		long_addr_pending=get_number_extended(packet->data[data_count]);
		
		////////////printfUART("ADD COUNT %i %i\n",short_addr_pending,long_addr_pending);
		
		data_count++;
		
		if(short_addr_pending > 0)
		{
			for(i=0;i < short_addr_pending;i++)
			{
				////////////printfUART("PB %i %i\n",(EE_UINT16)packet->data[data_count],short_addr_pending);
				
				//if(packet->data[data_count] == (EE_UINT8)mac_PIB.macShortAddress && packet->data[data_count+1] == (EE_UINT8)(mac_PIB.macShortAddress >> 8) )
				if((EE_UINT16)packet->data[data_count] == mac_PIB.macShortAddress)
				{
					
					create_data_request_cmd();
				}
				data_count = data_count + 2;
			}
		}
		if(long_addr_pending > 0)
		{
			for(i=0; i < long_addr_pending;i++)
			{
				if((EE_UINT32)packet->data[data_count] == aExtendedAddress0 && (EE_UINT32)packet->data[data_count + 4] == aExtendedAddress1)
				{
					
					data_count = data_count + 8;

				}
			
			}
		}
*/
	/**********************************************************************************/
	/*				BUILD the PAN descriptor of the COORDINATOR						  */
	/**********************************************************************************/
		
		
	   //Beacon NOTIFICATION
	   //BUILD the PAN descriptor of the COORDINATOR
		//assuming that the adress is short
		pan_descriptor.CoordAddrMode = SHORT_ADDRESS;
		pan_descriptor.CoordPANId = 0x0000;//beacon_ptr->source_PAN_identifier;
		pan_descriptor.CoordAddress0=0x00000000;
		pan_descriptor.CoordAddress1=mac_PIB.macCoordShortAddress;
		
		//TODO
		//pan_descriptor.LogicalChannel=current_channel;
		
		//superframe specification field
		pan_descriptor.SuperframeSpec = beacon_ptr->superframe_specification;
		
		pan_descriptor.GTSPermit=mac_PIB.macGTSPermit;
		pan_descriptor.LinkQuality=0x00;
		pan_descriptor.TimeStamp=0x000000;
		pan_descriptor.SecurityUse=0;
		pan_descriptor.ACLEntry=0x00;
		pan_descriptor.SecurityFailure=0x00;
	   
		//I_AM_IN_CAP = 1;
	   
	/**********************************************************************************/
	/*								SYNCHRONIZING									  */
	/**********************************************************************************/

	//processing time + beacon transmission delay
	
	
	if(PANCoordinator == 0)
	{
			if(findabeacon == 1)
			{
				////printfUART("findabeacon\n", "");
				//call TimerAsync.set_timers_enable(1);
				findabeacon =0;
			}
		
		//syncronization procedure
		
	
		/*backoff_elapsed = backoff_count;
		timer2_count_end=TMR2;*/
		#ifdef DEVICE_TYPE_END_DEVICE
			set_alarm_intervals();
		#endif
		/*if (backoff_elapsed == 0 )
		{
			new_timer2_count = (EE_UINT16)(timer2_count_end - timer2_count);
			TMR2 = new_timer2_count;
			ieee802145alarms_reset_start(0);
		}
		else
		{
			sync_time = (timer2_count_end + timer2_count) + ((backoff_elapsed - 1) * 0x3200);
			new_timer2_count = (EE_UINT16)(sync_time % 0x3200);
			TMR2 = new_timer2_count;
			ieee802145alarms_reset_start(backoff_elapsed - 1);
				
		}*/
		ieee802145alarms_reset_start(0);
		
		SetRelAlarm(sd_firedAlarm, sd_ticks, 0);	/* Set timeout on SD */
		
		I_AM_IN_CAP=1;
		I_AM_IN_CFP=0;
		I_AM_IN_IP=0;
		
		_openZB_sync_notify(OPENZB_SUCCESS); /* Notify, if required, the beacon time to the upper layer */

//		ee_console_out_str("\n");
//		ee_console_out_radix(mac_beacon_rxmpdu_ptr->seq_num, 16);
//		ee_console_out_str("\t");
//		ee_console_out16_radix(new_timer2_count, 16);
//		ee_console_out_str(" ");
//		ee_console_out_radix(backoff_elapsed, 16);	
		
		
			//#ifdef PLATFORM_MICAZ
			//number_time_slot = call TimerAsync.reset_start(start_reset_ct+process_tick_counter+52);// //SOBI=3 52 //SOBI=0 15
			//#else
			
			//call TimerAsync.reset();
			
			//number_time_slot = call TimerAsync.reset_start(75);   //95 old val sem print
					
			// +process_tick_counter+52 //SOBI=3 52 //SOBI=0 
			//#endif
			on_sync=1;
			
			////printfUART("sED\n", "");
	}
	
	MLME_BEACON_NOTIFY_indication((EE_UINT8)mac_beacon_rxmpdu_ptr->seq_num,pan_descriptor,0, 0, mac_PIB.macBeaconPayloadLenght, mac_beacon_rxmpdu_ptr->data);
				
return;
}


/*    ----- SHOULD BE USED IN FUTURE  -----
void process_data()
{
	
	MPDU *pdu=0;
	
	EE_UINT8 ppduLinkQuality=0;
	
	EE_UINT8 data_len=0;
	
	EE_UINT8 payload[120];
	EE_UINT8 msdu_length=0;
	
	EE_UINT32 SrcAddr[2];
	EE_UINT32 DstAddr[2];
	
	
	//frame control variables
	EE_UINT8 source_address=0;
	EE_UINT8 destination_address=0;


	dest_short *dest_short_ptr=0;
	dest_long *dest_long_ptr=0;
	
	source_short *source_short_ptr=0;
	source_long *source_long_ptr=0;

	//implement the intra PAN data messages
	//intra_pan_source_short *intra_pan_source_short_ptr;
	//intra_pan_source_long *intra_pan_source_long_ptr;
	
	pdu = removeq(receiveBuffer_ptr);
	if(pdu == 0)
		return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing

	
	source_address=get_fc2_source_addr(pdu->frame_control2);
	destination_address=get_fc2_dest_addr(pdu->frame_control2);
	
	SrcAddr[0]=0x00000000;
	SrcAddr[1]=0x00000000;
	DstAddr[0]=0x00000000;
	DstAddr[1]=0x00000000;

	if ( get_fc1_intra_pan(pdu->frame_control1)== 0 )
	{
	//INTRA PAN
		if (destination_address > 1 && source_address > 1)
		{
			// Destination LONG - Source LONG	
			if (destination_address == LONG_ADDRESS && source_address == LONG_ADDRESS)
			{
				dest_long_ptr = (dest_long *) &pdu->data[0];
				source_long_ptr = (source_long *) &pdu->data[DEST_LONG_LEN];
				
				//If a short destination address is included in the frame, it shall match either macShortAddress or the
				//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
				//shall match aExtendedAddress.
				if ( dest_long_ptr->destination_address0 !=aExtendedAddress0 && dest_long_ptr->destination_address1 !=aExtendedAddress1 )
				{
					////////////printfUART("data rejected, ext destination not for me\n", ""); 
					return;
				}
				//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
				//broadcast PAN identifier (0 x ffff).
				if(dest_long_ptr->destination_PAN_identifier != 0xffff && dest_long_ptr->destination_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, wrong destination PAN\n", ""); 
					return;
				}
				data_len = 20;
				
				
				DstAddr[1] = dest_long_ptr->destination_address0;
				DstAddr[0] =dest_long_ptr->destination_address1;
				
				SrcAddr[1] =source_long_ptr->source_address0;
				SrcAddr[0] =source_long_ptr->source_address1;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
				
				MCPS_DATA_indication((EE_UINT16)source_address, (EE_UINT16)source_long_ptr->source_PAN_identifier, SrcAddr,(EE_UINT16)destination_address, (EE_UINT16)dest_long_ptr->destination_PAN_identifier, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  
				
			}
			
			// Destination SHORT - Source LONG
			if ( destination_address == SHORT_ADDRESS && source_address == LONG_ADDRESS )
			{
				dest_short_ptr = (dest_short *) &pdu->data[0];
				source_long_ptr = (source_long *) &pdu->data[DEST_SHORT_LEN];
				
				//If a short destination address is included in the frame, it shall match either macShortAddress or the
				//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
				//shall match aExtendedAddress.
				if ( dest_short_ptr->destination_address != 0xffff && dest_short_ptr->destination_address != mac_PIB.macShortAddress)
				{
					////////////printfUART("data rejected, short destination not for me\n", ""); 
					return;
				}
				//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
				//broadcast PAN identifier (0 x ffff).
				if(dest_short_ptr->destination_PAN_identifier != 0xffff && dest_short_ptr->destination_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, wrong destination PAN\n", ""); 
					return;
				}
				
				data_len = 14;
				
				DstAddr[0] =dest_short_ptr->destination_address;
				
				SrcAddr[1] =source_long_ptr->source_address0;
				SrcAddr[0] =source_long_ptr->source_address1;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
				
				MCPS_DATA_indication((EE_UINT16)source_address, (EE_UINT16)source_long_ptr->source_PAN_identifier, SrcAddr,(EE_UINT16)destination_address, (EE_UINT16)dest_short_ptr->destination_PAN_identifier, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
			// Destination LONG - Source SHORT
			if ( destination_address == LONG_ADDRESS && source_address == SHORT_ADDRESS )
			{
				dest_long_ptr = (dest_long *) &pdu->data[0];
				source_short_ptr = (source_short *) &pdu->data[DEST_LONG_LEN];
				
				//If a short destination address is included in the frame, it shall match either macShortAddress or the
				//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
				//shall match aExtendedAddress.
				if ( dest_long_ptr->destination_address0 !=aExtendedAddress0 && dest_long_ptr->destination_address1 !=aExtendedAddress1 )
				{
					////////////printfUART("data rejected, ext destination not for me\n", ""); 
					return;
				}
				//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
				//broadcast PAN identifier (0 x ffff).
				if(dest_long_ptr->destination_PAN_identifier != 0xffff && dest_long_ptr->destination_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, wrong destination PAN\n", ""); 
					return;
				}
				
				data_len = 14;
				
				DstAddr[1] = dest_long_ptr->destination_address0;
				DstAddr[0] =dest_long_ptr->destination_address1;
				
				
				SrcAddr[0] =source_short_ptr->source_address;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
				
				MCPS_DATA_indication((EE_UINT16)source_address, (EE_UINT16)source_short_ptr->source_PAN_identifier, SrcAddr,(EE_UINT16)destination_address, (EE_UINT16)dest_long_ptr->destination_PAN_identifier, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
			
			
			//Destination SHORT - Source SHORT
			if ( destination_address == SHORT_ADDRESS && source_address == SHORT_ADDRESS )	
			{
				dest_short_ptr = (dest_short *) &pdu->data[0];
				source_short_ptr = (source_short *) &pdu->data[DEST_SHORT_LEN];
				
				//If a short destination address is included in the frame, it shall match either macShortAddress or the
				//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
				//shall match aExtendedAddress.
				if ( dest_short_ptr->destination_address != 0xffff && dest_short_ptr->destination_address != mac_PIB.macShortAddress)
				{
					////printfUART("data rejected, short destination not for me\n", ""); 
					return;
				}
				//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
				//broadcast PAN identifier (0 x ffff).
				if(dest_short_ptr->destination_PAN_identifier != 0xffff && dest_short_ptr->destination_PAN_identifier != mac_PIB.macPANId )
				{
					////printfUART("SH SH data rejected, wrong destination PAN %x\n",mac_PIB.macPANId ); 
					return;
				}
				
				data_len = 8;
				
				if ( get_fc1_ack_request(pdu->frame_control1) == 1 ) 
				{

					build_ack(pdu->seq_num,0);
				}
				
				DstAddr[0] =dest_short_ptr->destination_address;
				
				SrcAddr[0] =source_short_ptr->source_address;
				
				msdu_length = (pdu->length - 5) - data_len;
				
				
				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
			
				MCPS_DATA_indication((EE_UINT16)source_address, (EE_UINT16)source_short_ptr->source_PAN_identifier, SrcAddr,(EE_UINT16)destination_address, (EE_UINT16)dest_short_ptr->destination_PAN_identifier, DstAddr, (EE_UINT16)msdu_length,payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
		}
		
		
		if ( destination_address == 0 && source_address > 1 )
		{
				
			if (source_address == LONG_ADDRESS)
			{//Source LONG
				source_long_ptr = (source_long *) &pdu->data[0];
				
				//If only source addressing fields are included in a data or MAC command frame, the frame shall be
				//accepted only if the device is a PAN coordinator and the source PAN identifier matches macPANId.
				if ( PANCoordinator==0 || source_long_ptr->source_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, im not pan\n", ""); 
					return;
				}
				
				data_len = 10;
				
				SrcAddr[1] =source_long_ptr->source_address0;
				SrcAddr[0] =source_long_ptr->source_address1;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
				
				MCPS_DATA_indication((EE_UINT16)source_address,(EE_UINT16)source_long_ptr->source_PAN_identifier, SrcAddr,(EE_UINT16)destination_address, 0x0000, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
			else
			{//Source SHORT

				source_short_ptr = (source_short *) &pdu->data[0];
				//If only source addressing fields are included in a data or MAC command frame, the frame shall be
				//accepted only if the device is a PAN coordinator and the source PAN identifier matches macPANId.
				if ( PANCoordinator==0 || source_short_ptr->source_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, im not pan\n", ""); 
					return;
				}
				
				data_len = 4;

				
				SrcAddr[0] =source_short_ptr->source_address;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
				
				MCPS_DATA_indication((EE_UINT16)source_address, (EE_UINT16)source_short_ptr->source_PAN_identifier, SrcAddr,(EE_UINT16)destination_address, 0x0000, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
		}
		
		if ( destination_address > 1 && source_address == 0 )
		{
			if (destination_address == LONG_ADDRESS)
			{//Destination LONG
				dest_long_ptr = (dest_long *) &pdu->data[0];
				
				//If a short destination address is included in the frame, it shall match either macShortAddress or the
				//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
				//shall match aExtendedAddress.
				if ( dest_long_ptr->destination_address0 !=aExtendedAddress0 && dest_long_ptr->destination_address1 !=aExtendedAddress1 )
				{
					////////////printfUART("data rejected, ext destination not for me\n", ""); 
					return;
				}
				//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
				//broadcast PAN identifier (0 x ffff).
				if(dest_long_ptr->destination_PAN_identifier != 0xffff && dest_long_ptr->destination_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, wrong destination PAN\n", ""); 
					return;
				}
				
				data_len = 10;
				
				DstAddr[1] = dest_long_ptr->destination_address0;
				DstAddr[0] =dest_long_ptr->destination_address1;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
			
				MCPS_DATA_indication((EE_UINT16)source_address,0x0000, SrcAddr,(EE_UINT16)destination_address, (EE_UINT16)dest_long_ptr->destination_PAN_identifier, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
			else
			{//Destination SHORT
				dest_short_ptr = (dest_short *) &pdu->data[0];
				
				//If a short destination address is included in the frame, it shall match either macShortAddress or the
				//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
				//shall match aExtendedAddress.
				if ( dest_short_ptr->destination_address != 0xffff && dest_short_ptr->destination_address != mac_PIB.macShortAddress)
				{
					////////////printfUART("data rejected, short destination not for me\n", ""); 
					return;
				}
				//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
				//broadcast PAN identifier (0 x ffff).
				if(dest_short_ptr->destination_PAN_identifier != 0xffff && dest_short_ptr->destination_PAN_identifier != mac_PIB.macPANId )
				{
					////////////printfUART("data rejected, wrong destination PAN\n", ""); 
					return;
				}
				
				data_len = 4;
				
				DstAddr[0] =dest_short_ptr->destination_address;
				
				msdu_length = pdu->length - data_len;

				memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));
				
				MCPS_DATA_indication((EE_UINT16)source_address,0x0000, SrcAddr,(EE_UINT16)destination_address, (EE_UINT16)dest_short_ptr->destination_PAN_identifier, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  

			}
		}
		
	}
	else
	{
	//intra_pan == 1
	
	
	
	}
	
	
return;
}

*/
void process_data()
{
	
	MPDU *pdu=0;
	
	EE_UINT8 ppduLinkQuality=0;
	
	EE_UINT8 data_len=0;
	
	EE_UINT8 payload[120];
	EE_UINT8 msdu_length=0;
	
	EE_UINT32 SrcAddr[2];
	EE_UINT32 DstAddr[2];

	//frame control variables
	EE_UINT8 source_address=0;
	EE_UINT8 destination_address=0;


	dest_short *dest_short_ptr=0;
	dest_long *dest_long_ptr=0;
	
	source_short *source_short_ptr=0;
	source_long *source_long_ptr=0;

	//implement the intra PAN data messages
	//intra_pan_source_short *intra_pan_source_short_ptr;
	//intra_pan_source_long *intra_pan_source_long_ptr;
	
	pdu = removeq(receiveBuffer_ptr);
	if(pdu == 0)
		return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
	
	//source_address=get_fc2_source_addr(pdu->frame_control2);
	//destination_address=get_fc2_dest_addr(pdu->frame_control2);
	
	SrcAddr[0]=0x00000000;
	SrcAddr[1]=0x00000000;
	DstAddr[0]=0x00000000;
	DstAddr[1]=0x00000000;
		
		
		//Destination SHORT
		dest_short_ptr = (dest_short *) &pdu->data[0];
		
		//If a short destination address is included in the frame, it shall match either macShortAddress or the
		//broadcast address (0 x ffff). Otherwise, if an extended destination address is included in the frame, it
		//shall match aExtendedAddress.
		/*if ( dest_short_ptr->destination_address != 0xffff && dest_short_ptr->destination_address != mac_PIB.macShortAddress)
		{
			////////////printfUART("data rejected, short destination not for me\n", ""); 
			return;
		}*/
		//If a destination PAN identifier is included in the frame, it shall match macPANId or shall be the
		//broadcast PAN identifier (0 x ffff).
		/*if(dest_short_ptr->destination_PAN_identifier != 0xffff && dest_short_ptr->destination_PAN_identifier != mac_PIB.macPANId )
		{
			////////////printfUART("data rejected, wrong destination PAN\n", ""); 
			return;
		}*/
		
		data_len = 8;

		//DstAddr[0] =dest_short_ptr->destination_address;
		
		msdu_length = pdu->length - data_len - MPDU_HEADER_LEN;

		memcpy(&payload,&pdu->data[data_len],msdu_length * sizeof(EE_UINT8));		
		//MCPS_DATA_indication(0x0000,0x0000, 0x00000000, 0x0000, DstAddr, (EE_UINT16)msdu_length, payload, (EE_UINT16)ppduLinkQuality, 0x0000,0x0000);  
		MCPS_DATA_indication(0x0000, 0x0000, SrcAddr, 0x0000, 0x0000, DstAddr, (EE_UINT16)msdu_length, payload,(EE_UINT16)ppduLinkQuality, 0x0000,0x0000);
		
		//EE_lcd_putc(pdu->data[8]);
		//EE_lcd_putc(pdu->data[9]);
	
	
return;
}

void process_cmd()
{
		MPDU *pdu=0;
		
		EE_UINT8 ppduLinkQuality=0;
	
		EE_UINT8 cmd_type=0;
		//EE_UINT8 pk_ptr;
		EE_UINT8 addressing_fields_length=0;
		
		EE_UINT32 SrcAddr[2];
		//EE_UINT32 DstAddr[2];//NOT USED SO FAR
		
		//frame control variables
		EE_UINT8 source_address=0;
		EE_UINT8 destination_address=0;
	
		//NOT USED SO FAR
		//dest_short *dest_short_ptr;
		//dest_long *dest_long_ptr;
		//NOT USED SO FAR
		//source_short *source_short_ptr;
		source_long *source_long_ptr=0;
		
		dest_short *dest_short_ptr=0;
		dest_long *dest_long_ptr=0;
		
		pdu = removeq(receiveBuffer_ptr);
		if(pdu == 0)
			return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
		
		//CHECK IMPLEMENT
		//intra_pan_source_short *intra_pan_source_short_ptr; 
		//intra_pan_source_long *intra_pan_source_long_ptr;
		
		destination_address=get_fc2_dest_addr(pdu->frame_control2);
		source_address=get_fc2_source_addr(pdu->frame_control2);
		
		switch(destination_address)
		{
			case LONG_ADDRESS: addressing_fields_length = DEST_LONG_LEN;
								dest_long_ptr = (dest_long *) &pdu->data[0];
								if(dest_long_ptr->destination_address0 !=aExtendedAddress0 && dest_long_ptr->destination_address1 !=aExtendedAddress1)
								{
									//printfUART("NOT FOR ME","");
									return;
								}
								
								break;
			case SHORT_ADDRESS: addressing_fields_length = DEST_SHORT_LEN;
								dest_short_ptr= (dest_short *) &pdu->data[0];
								//destination command not for me
								if (dest_short_ptr->destination_address != mac_PIB.macShortAddress && dest_short_ptr->destination_address !=0xffff)
								{
									//printfUART("NOT FOR ME","");
									////////////printfUART("NOT FOR ME %x me %e\n", dest_short_ptr->destination_address,mac_PIB.macShortAddress); 
									return;
								}
								break;
		}
		switch(source_address)
		{
			case LONG_ADDRESS: addressing_fields_length = addressing_fields_length + SOURCE_LONG_LEN;
								break;
			case SHORT_ADDRESS: addressing_fields_length = addressing_fields_length + SOURCE_SHORT_LEN;
								break;
		}

		cmd_type = pdu->data[addressing_fields_length];
		
		switch(cmd_type)
		{
		
		case CMD_ASSOCIATION_REQUEST: 	
									break;
		
		case CMD_ASSOCIATION_RESPONSE: 
									break;

		case CMD_DISASSOCIATION_NOTIFICATION: 	
									break;
		case CMD_DATA_REQUEST: 
								break;
		case CMD_PANID_CONFLICT:
								break;
								
		case CMD_ORPHAN_NOTIFICATION:
								break;
		case CMD_BEACON_REQUEST:
								break;
		case CMD_COORDINATOR_REALIGNMENT:
								break;
		case CMD_GTS_REQUEST: 	
					//RARS todo
					
								break;
		default: break;

		}

return;
}


void process_ack()
{
	MPDU *pdu=0;
		
	EE_UINT8 ppduLinkQuality=0;
	//RARS todo
	pdu = removeq(receiveBuffer_ptr);
	if(pdu == 0)
		return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
	
return;
}


/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/
/****************************************ALARM EVENTS FUNCTION************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/
/*******************************************************************************************************/

volatile unsigned char test_pass = 0;
volatile unsigned long int PLUTO = 0;


void bi_fired()
{
	
	//ee_console_out_str("BI FIRED");
	#ifdef DEVICE_TYPE_COORDINATOR
	
		SetRelAlarm(sd_firedAlarm, sd_ticks, 0);	/* Set timeout on SD */
	
		store_msg((EE_UINT8 *) mac_beacon_txmpdu_ptr->length, (EE_UINT8 *) mac_beacon_txmpdu_ptr);

//		if(test_pass++ > 4)
//			for(;;);
		_openZB_sync_notify(OPENZB_SUCCESS); /* Notify, if required, the beacon time to the upper layer */

		
		create_beacon(); //FIXME: check: MUST be done in before_bi_fired() ???
		//RARS if lost sync dealocate gtss

		current_time_slot = 0; /* When the new frame starts we MUST reset the time slot index */
	
	#endif

	I_AM_IN_CAP=1;
	I_AM_IN_CFP=0;
	I_AM_IN_IP=0;
return;
}

void before_bi_fired()
{

return;
}
void sd_fired()
{
	I_AM_IN_CAP=0;
	I_AM_IN_CFP=0;
	I_AM_IN_IP=1;
	//ee_console_out_str("SD FIRED");

	// chris: TODO: check!!!
	//#ifdef DEVICE_TYPE_END_DEVICE
	//CancelAlarm(sd_firedAlarm);
	//#endif
	
	
	//RARS todo //increment the gts_null descriptors
	
			
				//if (GTS_null_descriptor_count > 0) post increment_gts_null();
			
				//if (GTS_descriptor_count >0 ) post check_gts_expiration();
			
	
	return;
}

void time_slot_fired()
{
	//ee_console_out_str("Time Slot");
	//ee_console_out_radix(current_time_slot, 16);
	EE_UINT8 current_gts_slot;

	if(I_AM_IN_IP)
		return;
	
	//RARS todo		
	//reset the backoff counter?? and increment the slot boundary
	current_time_slot++;
	
	if ((current_time_slot  >= final_CAP_slot) && (current_time_slot  < 16))
	{
		I_AM_IN_CAP = 0;
		I_AM_IN_CFP = 1;
	}

	
	#ifdef DEVICE_TYPE_COORDINATOR
	//verify is there is data to send in the GTS, and try to send it
		current_gts_slot = gts_schedule[current_time_slot];
	
		if(current_gts_slot < 8 && GTS_db[current_gts_slot].direction == 1 && GTS_db[current_gts_slot].gts_id != 0)
		{
		//COORDINATOR SEND DATA
		//////////printfUART("bbck%i:%i:%i\n", (15-number_time_slot),GTS_db[15-number_time_slot].direction,gts_slot_list[15-number_time_slot].element_count);
		
		start_coordinator_gts_send();
				
		}
		next_on_r_GTS =0;
		next_on_s_GTS=0;
	
		//GTS FIELDS PROCESSING
	
		//verification of the next time slot
		if(current_time_slot < 15)
		{
		//COORDINATOR verification of the next time slot
			if(GTS_db[gts_schedule[current_time_slot+1]].gts_id != 0x00 && GTS_db[gts_schedule[current_time_slot+1]].DevAddressType != 0x0000)
			{	
				if(GTS_db[gts_schedule[current_time_slot+1]].direction == 1 ) // device wants to receive
				{
					next_on_s_GTS =1; //PAN coord mode
				}
				else
				{
					next_on_r_GTS=1; //PAN coord mode
				}
			}
			
		} 
	
	
	#endif //PAN_C
	
	#ifdef DEVICE_TYPE_END_DEVICE
		//DEVICE SEND DATA
		if (!GTS_TRANSMITING &&     current_time_slot >= s_GTSss && current_time_slot <= s_GTSss + s_GTS_length && gts_send_buffer_count > 0 && on_sync == 1)//(send_s_GTSss-send_s_GTS_len) 
		{
			 	//ee_console_out_str("GTSSEND in slot");
			 	//ee_console_out_radix(current_time_slot, 16);
			 	
			  	
			  start_gts_send();
			  
		}		

	#endif
	
		
	return;
}
void before_time_slot_fired()
{
//RARS todo





return;
}
void backoff_fired()
{	
	//backoff_count++;
	
	//TODO activate slotted CSMA/CA
	backoff_fired_check_csma_ca();
	
//	if (backoff_count == 100)
//	{
//		ee_console_out_str("BF :");
//		backoff_count = 0;
//	}
	//
return;
}

void backoff_fired_check_csma_ca()
{
	EE_UINT8 random_interval;
	//slotted CSMA/CA function

	//if(!I_AM_IN_CAP || current_time_slot < 3)
	if(!I_AM_IN_CAP)
		return;

	if( csma_locate_backoff_boundary == 1 )
	{
		csma_locate_backoff_boundary=0;
		//DEFERENCE CHANGE
		
		if (backoff_deference == 0)
		{
//			//normal situation
			//srand ( 100 );
			random_interval = (EE_UINT8)(powf(2,BE) - 1);
			
			delay_backoff_period = (EE_UINT8)(rand() & random_interval);
//			
//			ee_console_out_str("init delay:");
//			ee_console_out16_radix(random_interval, 16);
//			ee_console_out_str("\n\r");
//			ee_console_out16_radix(delay_backoff_period, 16);
//			ee_console_out_str("\n\r");
//			ee_console_out16_radix((EE_UINT16)rand(), 16);
//			ee_console_out_str("\n\r");


			if (check_csma_ca_backoff_send_conditions((EE_UINT32) delay_backoff_period) == 1)
			{
				backoff_deference = 1;
			}
		}
		else
		{
			backoff_deference = 0;
		}
		
		csma_delay=1;
	}
	if( csma_cca_backoff_boundary == 1 )
	{
		perform_csma_ca_slotted();
		
	}
	//CSMA/CA
	if(csma_delay == 1 )
	{
		if (delay_backoff_period == 0)
		{
			if(csma_slotted == 0)
			{
				perform_csma_ca_unslotted();
			}
			else
			{
				//CSMA/CA SLOTTED
				csma_delay=0;
				csma_cca_backoff_boundary=1;
			}
		}
		delay_backoff_period--;
	}

return;
}




/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/************************		CSMA/CA    			**********************************/
/*****************************************************************************************************/ 
/*****************************************************************************************************/
/*****************************************************************************************************/

void perform_csma_ca_unslotted()
{
	MPDU *frame_pkt=0;
	
	frame_pkt = (MPDU *)removeq(sendBuffer_ptr);
	if(frame_pkt == 0)
		return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing

	//unslotted send
	
	PD_DATA_request((EE_UINT8)frame_pkt->length,(EE_UINT8*)frame_pkt);
	
	if (!isempty(sendBuffer_ptr))
	{
		send_frame_csma();
	}

return;
}

//CSMA CA send function
void send_frame_csma()
{
	//RARS TODO shouldn't we make a verification of the CAP or CFP to avoid sending in gts
	
	csma_slotted=1;
	
	if (csma_slotted == 0)
	{
		//ee_console_out_str("sfun");
		//unslotted, done by hardware
		perform_csma_ca_unslotted();
	
	}
	else
	{
		//ee_console_out_str("1 send_frame_csma\n");
		//slotted send
		performing_csma_ca = 1;
		//perform_csma_ca_unslotted();

		perform_csma_ca();
	}
	

return;
}

void init_csma_ca(EE_UINT8 slotted)
{
	//initialization of the CSMA/CA protocol variables
	//ee_console_out_str("3 - init_csma_ca \n");
	csma_delay=0;
	if (slotted == 0 )
	{
		NB=0;
		BE=mac_PIB.macMinBE;
	}
	else
	{
		NB=0;
		CW=2;
		
		csma_cca_backoff_boundary=0;
		csma_locate_backoff_boundary=0;
	}

return;
}

void perform_csma_ca()
{
	EE_UINT8 random_interval;
	
	//temp var
	csma_slotted=1;
	//STEP 1
	if (csma_slotted == 0 )
	{
		//UNSLOTTED version
		init_csma_ca(csma_slotted);
		//STEP 2
		random_interval = powf(2,BE) - 1;
		delay_backoff_period = (EE_UINT8)(rand() & random_interval );
			
		csma_delay=1;
		
		return;
	}
	else
	{
		//ee_console_out_str("2 - perform_csma_ca \n");
		//SLOTTED version

		//DEFERENCE CHANGE
		if (cca_deference==0)
		{
			init_csma_ca(csma_slotted);
			if (mac_PIB.macBattLifeExt == 1 )
			{
				BE = min(2,	mac_PIB.macMinBE);
			}
			else
			{
				BE = mac_PIB.macMinBE;
			}
			
			//ee_console_out_str("BE:");
			//ee_console_out16_radix(BE, 16);
			
			csma_locate_backoff_boundary = 1;
		}
		else
		{
			cca_deference = 0;
			csma_delay=0;
			csma_locate_backoff_boundary=0;
			csma_cca_backoff_boundary = 1;
		}
		return;
	}
}

void perform_csma_ca_slotted()
{
	EE_UINT8 random_interval;
	MPDU *frame_pkt=0;

	frame_pkt = (MPDU *)getq(sendBuffer_ptr);

	if(frame_pkt == 0)
		return; //TODO: we have to chose: notifty error with _openZB_raise_error(OPENZB_ERR_INVALID_PACKET) , or do nothing
	
	//ee_console_out_str("4 - perform_csma_ca_slotted\n");
	
	//DEFERENCE CHANGE
	

	if (check_csma_ca_send_conditions(frame_pkt->length,frame_pkt->frame_control1) == 1 )
	{
		cca_deference = 0;
	}
	else
	{
		//nao e necessario
		cca_deference = 1;
		return;
	}
	
	//ee_console_out_str("CCA:");
	//ee_console_out16_radix(CCA, 16);
	//ee_console_out_str("\n\r");
	
	if(CCA==1)
	{   
		//ee_console_out_str("CW:");
		//ee_console_out16_radix(CW, 16);
		//ee_console_out_str("\n\r");
		//STEP 5
		CW--;
		if (CW == 0 )
		{
			//send functions
			csma_cca_backoff_boundary =0;
			
			//verify if the message must be ack
			if ( get_fc1_ack_request(frame_pkt->frame_control1) == 1 )
			{
				//SEND WITH ACK_REQUEST

				//TODO
				//ENABLE THE ACK RESPONSE WAIT TIME
				//ENABLE RETRANSMISSIONS OF THE MESSAGE
				
				//ee_console_out_str("csma success ack");
				
				PD_DATA_request((EE_UINT8)frame_pkt->length,(EE_UINT8*)frame_pkt);
				
				removeq(sendBuffer_ptr);
			}
			else
			{	
				//ee_console_out_str("csma success");
			
				// USED FOR TESTING	
				//insert_mac_payload_16(sendBuffer_ptr, 52, 0xAF);
				//insert_mac_payload_16(sendBuffer_ptr, 54, current_time_slot);
				//insert_mac_payload_16(sendBuffer_ptr, 56, I_AM_IN_CAP);
				//insert_mac_payload_16(sendBuffer_ptr, 58, 0xAF);
				
				PD_DATA_request((EE_UINT8)frame_pkt->length,(EE_UINT8*)frame_pkt);
				
				packet_count_mac++;
				
				total_bytes_send_mac=total_bytes_send_mac+113;
				
				removeq(sendBuffer_ptr); 
			}	
			
			//CSMA/CA SUCCESS
			
			performing_csma_ca = 0;
			
			if (!isempty(sendBuffer_ptr))
			{
				send_frame_csma();
			}
		}
	}
	else
	{	//CHECK NOT USED
		//csma_backoff_counter++;
		//csma_backoff_counter_inst++;
		
		//ee_console_out_str("CW");
		
		if (NB < mac_PIB.macMaxCSMABackoffs)
		{	//STEP 4
			CW = 2;
			NB++;
			BE = min(BE+1,aMaxBE);
				
			//STEP 2
			//verification of the backoff_deference
			//DEFERENCE CHANGE
			if (backoff_deference == 0)
			{
				random_interval = powf(2,BE) - 1;
				delay_backoff_period = (rand() & random_interval );
						
				if (check_csma_ca_backoff_send_conditions((EE_UINT32) delay_backoff_period) == 1)
				{
					backoff_deference = 1;
				}
			}
			else
			{
				backoff_deference = 0;
			}
				csma_delay=1;
		}
		else
		{
			//CSMA/CA FAIL
			csma_delay=0;
			csma_cca_backoff_boundary=0;
			
			//TODO 
			//transmission failed
			//remove from the queue the packet
			
			//ee_console_out_str("csma fail");
			
			packet_csmaca_fail ++;
			
			//removeq(sendBuffer_ptr);
			
			if (!isempty(sendBuffer_ptr))
			{
				send_frame_csma();
			}
					
			performing_csma_ca = 0;
				
		}
	}
return;
}

EE_UINT8 calculate_ifs(EE_UINT8 pk_length)
{
	if (pk_length > aMaxSIFSFrameSize)
		return aMinLIFSPeriod; // + ( ((pk_length * 8) / 250.00) / 0.34 );
	else
		return aMinSIFSPeriod; // + ( ((pk_length * 8) / 250.00) / 0.34 );
}

//used to check if the CSMA/CA has enought backoffs until the end of the superframe
EE_UINT8 check_csma_ca_backoff_send_conditions(EE_UINT32 delay_backoffs)
{
	//DEFERENCE CHANGE
	EE_UINT32 number_of_sd_ticks=0;
	EE_UINT32 number_of_backoffs_remaining =0;
	
	number_of_sd_ticks = ieee802145alarms_get_sd_ticks();
	
	//Note:one tick equals one backoff
	number_of_backoffs_remaining = number_of_sd_ticks - ieee802145alarms_get_backoff_ticks();
	
	if (number_of_backoffs_remaining > delay_backoffs)
		return 0;
	else
		return 1;

}

EE_UINT8 check_csma_ca_send_conditions(EE_UINT8 frame_length,EE_UINT8 frame_control1)
{
	EE_UINT8 ifs_symbols;
	EE_UINT32 frame_tx_time_symbols;
	
	EE_UINT32 number_of_sd_ticks=0;
	
	EE_UINT32 remaining_sd_symbols=0;
	
	number_of_sd_ticks = ieee802145alarms_get_sd_ticks();
	
	ifs_symbols=calculate_ifs(frame_length);
	
	if (get_fc1_ack_request(frame_control1) == 1 )
		frame_tx_time_symbols =  (EE_UINT32)(((frame_length + ACK_LENGTH) * 2) + (EE_UINT32)aTurnaroundTime + (EE_UINT32)ifs_symbols);
	else
		frame_tx_time_symbols =  (EE_UINT32)((frame_length *2) + (EE_UINT32)ifs_symbols);
	
	remaining_sd_symbols = (EE_UINT32)((number_of_sd_ticks - ieee802145alarms_get_backoff_ticks()) * 20);
	
	if (frame_tx_time_symbols < remaining_sd_symbols)
		return 1;
	else
		return 0;

}
 
//RARS TODO ADD GTS CHECK SEND CONDITIONS

EE_UINT8 check_gts_send_conditions(EE_UINT8 frame_length)
{
	EE_UINT8 ifs_symbols;
	EE_UINT32 frame_tx_time;
	EE_UINT32 remaining_gts_duration;
	

	ifs_symbols=calculate_ifs(frame_length);
	//wait_ifs=1;
	//call TimerAsync.set_ifs_symbols(ifs_symbols);
	
	////////printfUART("ifs_symbols %i\n",ifs_symbols ) ;
	
	frame_tx_time =  frame_length + ACK_LENGTH + aTurnaroundTime + ifs_symbols;
	
	remaining_gts_duration = time_slot - ( ieee802145alarms_get_backoff_ticks() * aUnitBackoffPeriod);
	
	////////printfUART("frame_tx %d remaing %d\n",frame_tx_time,remaining_gts_duration ) ;
	
	if (frame_tx_time < remaining_gts_duration)
		return 1;
	else
		return 0;
}

/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/************************		Physical Layer EVENTS    			**********************************/
/*****************************************************************************************************/ 
/*****************************************************************************************************/
/*****************************************************************************************************/

/***************************************************************/
/*						PD_DATA EVENTS							*/
/*****************************************************************/
EE_UINT8 PD_DATA_confirm(EE_UINT8 status)
{
	
	
	
return 0;
}
  
EE_UINT8 PD_DATA_indication(EE_UINT8 psduLenght,EE_UINT8* psdu, EE_UINT8 ppduLinkQuality)
{
	//data indication
	
	
	
	

return 0;
}


/***************************************************************/
/*						PLME_SET_TRX_STATE EVENTS				*/
/*****************************************************************/

EE_UINT8 PLME_SET_TRX_STATE_confirm(EE_UINT8 status)
{
return 1;
}

/***************************************************************/
/*						PLME_GET EVENTS							*/
/*****************************************************************/
EE_UINT8 PLME_GET_confirm(EE_UINT8 status, EE_UINT8 PIBAttribute, EE_UINT8 PIBAttributeValue)
{
	
	
	
return 1;
}


/***************************************************************/
/*						PLME_SET EVENTS							*/
/*****************************************************************/
EE_UINT8 PLME_SET_confirm(EE_UINT8 status, EE_UINT8 PIBAttribute)
{
	
	
return 1;
}

/*****************************************************/
/*				Other MAC general functions			 */
/*****************************************************/ 

void init_MacPIB()
{
	//mac PIB default values

	mac_PIB.macAckWaitDuration = 54;
	
	mac_PIB.macAssociationPermit = 1; //1 - PAN allowing associations
	mac_PIB.macAutoRequest = 1; //indication if a device automatically sends a data request command if address is listed in the beacon frame
	
	mac_PIB.macBattLifeExt= 1; //batery life extension CSMA-CA
	
	mac_PIB.macBattLifeExtPeriods=6;
	//mac_PIB.macBeaconPayload; //payload of the beacon
	mac_PIB.macBeaconPayloadLenght=0; //beacon payload lenght
	
	mac_PIB.macBeaconTxTime=(0xffffff << 24); //*****
	
	//TODO
	//Implement random
	mac_PIB.macBSN=(EE_UINT16) (rand()%255);
	//mac_PIB.macBSN=call Random.rand16(); //sequence number of the beacon frame
	
	mac_PIB.macCoordExtendedAddress0 = 0x00000000; //64bits address of the coordinator with witch the device is associated
	mac_PIB.macCoordExtendedAddress1 = 0x00000000;
	
	mac_PIB.macCoordShortAddress = 0x0000; //16bits address of the coordinator with witch the device is associated
	
	//TODO
	//Implement random
	mac_PIB.macDSN=(EE_UINT16) (rand()%255);
	//mac_PIB.macDSN=call Random.rand16(); //sequence number of the transmited data or MAC command frame
	
	//alowing gts requests (used in beacon)
	mac_PIB.macGTSPermit=1; //
	
	//Number of maximum CSMA backoffs
	mac_PIB.macMaxCSMABackoffs=4;
	mac_PIB.macMinBE=3;
	
	mac_PIB.macPANId=0xffff; //16bits identifier of the PAN on witch this device is operating
	
	mac_PIB.macPromiscuousMode=0;
	mac_PIB.macRxOnWhenIdle=0;
 
	//mac_PIB.macShortAddress=TOS_LOCAL_ADDRESS; //16bits short address
	mac_PIB.macShortAddress = openzb_device_address;
	//mac_PIB.macShortAddress=0x0003;

	mac_PIB.macBeaconOrder=6;  //specification of how often the coordinator transmits a beacon
	mac_PIB.macSuperframeOrder=4;
	
	//default mac_PIB.macTransactionPersistenceTime=0x01f4;
	mac_PIB.macTransactionPersistenceTime=0x0010;

return;
} 


	
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/************************		GTS FUNCTIONS  		**********************************/
/*****************************************************************************************************/ 
/*****************************************************************************************************/
/*****************************************************************************************************/



	void start_coordinator_gts_send()
	{
/*
	coordinator_gts_send_pending_data =0;
	
	if(gts_slot_list[15-number_time_slot].element_count > 0)
	{
		if (check_gts_send_conditions(gts_send_buffer[gts_slot_list[15-number_time_slot].gts_send_frame_index[gts_slot_list[15-number_time_slot].element_out]].length) == 1 )
		{
			
			gts_send_buffer[gts_slot_list[15-number_time_slot].gts_send_frame_index[gts_slot_list[15-number_time_slot].element_out]].length = gts_send_buffer[gts_slot_list[15-number_time_slot].gts_send_frame_index[gts_slot_list[15-number_time_slot].element_out]].length -2;
			
			call PD_DATA.request(gts_send_buffer[gts_slot_list[15-number_time_slot].gts_send_frame_index[gts_slot_list[15-number_time_slot].element_out]].length,(uint8_t *)&gts_send_buffer[gts_slot_list[15-number_time_slot].gts_send_frame_index[gts_slot_list[15-number_time_slot].element_out]]);
	
			available_gts_index_count++;
			available_gts_index[available_gts_index_count] = gts_slot_list[15-number_time_slot].gts_send_frame_index[gts_slot_list[15-number_time_slot].element_out];
			
			gts_slot_list[15-number_time_slot].element_count--;
			gts_slot_list[15-number_time_slot].element_out++;
			
			if (gts_slot_list[15-number_time_slot].element_out == GTS_SEND_BUFFER_SIZE)
				gts_slot_list[15-number_time_slot].element_out=0;

			if(gts_slot_list[15-number_time_slot].element_count > 0 )
			{
				coordinator_gts_send_pending_data =1;
				coordinator_gts_send_time_slot = number_time_slot;
			}
		}
	}*/
	return;
	}


	void start_gts_send()
	{
		
		if(!GTS_TRANSMITING && current_time_slot >= s_GTSss && current_time_slot <= s_GTSss + s_GTS_length && gts_send_buffer_count > 0 && on_sync == 1){
			GTS_TRANSMITING=1;
			//send_gts_after_interframearrival();
			SetRelAlarm(interframespace_firedAlarm, 1, 15);			
		}	
		return;	
	}

	//void send_gts_after_interframearrival(){
	TASK(send_gts_after_interframearrivalTask){
		
		//if(current_time_slot >= s_GTSss && current_time_slot <= s_GTSss + s_GTS_length && gts_send_buffer_count > 0 && on_sync == 1)
			//if (gts_send_buffer_count && check_gts_send_conditions(gts_send_buffer[gts_send_buffer_msg_out].length) == 1 )			
			//while(gts_send_buffer_count)
			//if (gts_send_buffer_count)
			if(current_time_slot >= s_GTSss && current_time_slot < s_GTSss + s_GTS_length && gts_send_buffer_count > 0)
			{
				
				
				//ee_console_out_str("\nbuf\n");
				//ee_console_out16_radix(gts_send_buffer_count,16);
				//PD_DATA_request	
				//gts_send_buffer[gts_send_buffer_msg_out].data[11+8]=current_time_slot;
				//gts_send_buffer[gts_send_buffer_msg_out].data[12+8]=gts_send_buffer_count;
				//gts_send_buffer[gts_send_buffer_msg_out].data[13+8]=gts_send_buffer_msg_out;
				//gts_send_buffer[gts_send_buffer_msg_out].data[14+8]=mac_PIB.macShortAddress;
				//gts_send_buffer[gts_send_buffer_msg_out].data[15+8]=(EE_UINT8)beaconnumber>>8;
				//gts_send_buffer[gts_send_buffer_msg_out].data[16+8]=(EE_UINT8)beaconnumber;
				
				PD_DATA_request(gts_send_buffer[gts_send_buffer_msg_out].length,(EE_UINT8 *)&gts_send_buffer[gts_send_buffer_msg_out]);
			
				//ee_console_out16_radix(gts_send_buffer[gts_send_buffer_msg_out].length,16);
				//ee_console_out16_radix(gts_send_buffer[gts_send_buffer_msg_out].data[6],16);
				
				gts_send_buffer_count --;
				gts_send_buffer_msg_out++;
	
				if (gts_send_buffer_msg_out == GTS_SEND_BUFFER_SIZE)
					gts_send_buffer_msg_out=0;
	
				
				
//				if (gts_send_buffer_count > 0)
//					gts_send_pending_data = 1;	
//					
//				if(gts_send_buffer_count == 0){
//					GTS_TRANSMITING=0;
//					break;					
//				}else{
//						//SetRelAlarm(interframespace_firedAlarm, 15, 0);
//					EE_UINT16 k = 0;
//					for(k = 0; k < 60000; k++);
//					//gts_send_buffer_count --;
//					//gts_send_buffer_msg_out++;
//				}
			}
			
			if(gts_send_buffer_count <= 0){
				CancelAlarm(interframespace_firedAlarm);
				GTS_TRANSMITING=0;
			}/*else{
				SetRelAlarm(interframespace_firedAlarm, 300, 0);
				//gts_send_buffer_count --;
				//gts_send_buffer_msg_out++;
			}*/		
	}
//////////////////////////////////////////////////////////////
////////////////////////GTS functions////////////////////////
/////////////////////////////////////////////////////////////

void init_GTS_db()
{
	//initialization of the GTS database
	EE_UINT8 i;

	for (i=0 ; i < 7 ; i++)
		{
			GTS_db[i].gts_id=0x00;
			GTS_db[i].starting_slot=0x00;
			GTS_db[i].length=0x00;
			GTS_db[i].direction=0x00;
			GTS_db[i].DevAddressType=0x0000;
		
		}
		
		memset(gts_schedule,255,sizeof(gts_schedule));
	
return;
}
/*//RARS TODO REMOVE GTS FUNCTION
result_t remove_gts_entry(uint16_t DevAddressType)
{
	int r_lenght=0;
	//int r_start_slot=7;
	int i;
	atomic{
		for (i=0; i < 7 ; i++)
		{
			if( GTS_db[i].DevAddressType == DevAddressType )
			{
				
				r_lenght = GTS_db[i].length;
				//r_start_slot = i;
				//delete the values
				GTS_db[i].gts_id=0x00;
				GTS_db[i].starting_slot=0x00;
				GTS_db[i].length=0x00;
				GTS_db[i].direction=0x00;
				GTS_db[i].DevAddressType=0x0000;
				GTS_db[i].expiration=0x00;
				
				//////////////////printfUART("GTS Entry removed dev:%i len:%i pos %i\n", DevAddressType,r_lenght,i);
				GTS_startslot = GTS_startslot + r_lenght;
				GTS_descriptor_count--;
				final_CAP_slot = final_CAP_slot + r_lenght;
			}
			
			if ( r_lenght > 0)
			{
				if ( GTS_db[i].gts_id != 0x00 && GTS_db[i].DevAddressType !=0x0000)
				{				
					GTS_db[i-r_lenght].gts_id = GTS_db[i].gts_id;
					GTS_db[i-r_lenght].starting_slot = i-r_lenght;
					GTS_db[i-r_lenght].length = GTS_db[i].length;
					GTS_db[i-r_lenght].direction = GTS_db[i].direction;
					GTS_db[i-r_lenght].DevAddressType = GTS_db[i].DevAddressType;
					GTS_db[i-r_lenght].expiration = GTS_db[i].expiration;
					
					//delete the values
					GTS_db[i].gts_id=0x00;
					GTS_db[i].starting_slot=0x00;
					GTS_db[i].length=0x00;
					GTS_db[i].direction=0x00;
					GTS_db[i].DevAddressType=0x0000;
					GTS_db[i].expiration=0x00;
					
					//////////////////printfUART("UPDATED\n","" );
				}
			}
		}
	}
return SUCCESS;
}
*/

EE_UINT8 add_gts_entry(EE_UINT8 gts_length,EE_UINT8 direction,EE_UINT16 DevAddressType, EE_UINT16 GTS_startslotindex)
{
	EE_UINT8 i;

	//RARS TODO
	//check aMinCAPLength maybe use a global variable with the number of alocated gtss
	if (GTS_descriptor_count >= 7)
		{
			return 0;
		}
	
	//check if the address already exists in the GTS list
	for (i=0 ; i < 7 ; i++)
	{
		if ( GTS_db[i].DevAddressType == DevAddressType && GTS_db[i].direction == direction && GTS_db[i].gts_id > 0)
		{
			//////////////////printfUART("ALREADY ADDED\n", ""); 
			return 0;
		}
		if ( GTS_null_db[i].DevAddressType == DevAddressType && GTS_null_db[i].gts_id > 0)
		{
			//////////////////printfUART("REJECTED\n", ""); 
			return 0;
		}

	}

	////////printfUART("GTS_startslot: %i\n", GTS_startslot); 
	//GTS_startslot = GTS_startslot - gts_length;
	
	GTS_startslot = GTS_startslotindex;

	GTS_db[GTS_descriptor_count].gts_id=GTS_id;
	GTS_db[GTS_descriptor_count].starting_slot=GTS_startslot;
	GTS_db[GTS_descriptor_count].length=gts_length;
	GTS_db[GTS_descriptor_count].direction=direction;
	GTS_db[GTS_descriptor_count].DevAddressType=DevAddressType;
	GTS_db[GTS_descriptor_count].expiration=0x00;

	////////printfUART("GTS Entry added start:%i len:%i\n", GTS_startslot,gts_length); 
	
	//CHANGED FOR WC DIMENSIONING
	for(i=GTS_startslot; i < GTS_startslot+ gts_length ; i++)
		gts_schedule[i] = GTS_descriptor_count;
	
	GTS_id++;
	GTS_descriptor_count++;
	
	final_CAP_slot = final_CAP_slot - gts_length; //update final cap slot
	
	
	//for(i=0; i<16; i++)
		////printfUART("GTS schedule: %i len:%i\n",i, gts_schedule[i]); 
	return 1;
}


//GTS null functions
void init_GTS_null_db()
{
	//initialization of the GTS database
	EE_UINT8 i;
		for (i=0 ; i < 7 ; i++)
		{
			GTS_null_db[i].gts_id=0x00;
			GTS_null_db[i].starting_slot=0x00;
			GTS_null_db[i].length=0x00;
			//GTS_null_db[i].direction=0x00;
			GTS_null_db[i].DevAddressType=0x0000;
			GTS_null_db[i].persistencetime=0x00;
		}
	
return;
}

void init_available_gts_index()
{
	EE_UINT8 i;
		
	available_gts_index_count = GTS_SEND_BUFFER_SIZE;
	for(i=0;i < GTS_SEND_BUFFER_SIZE;i++)
		{
			available_gts_index[i]=i;
		}
	return;
}
	
/*****************************GTS BUFFER******************************/
void init_gts_slot_list()
{
	EE_UINT8 i;
	
	for(i=0;i<7;i++)
	{
		gts_slot_list[i].element_count = 0x00;
		gts_slot_list[i].element_in = 0x00;
		gts_slot_list[i].element_out = 0x00;
	}
}
//RARS todo 
	/*
	void create_gts_request_cmd(uint8_t gts_characteristics)
	{
	atomic{
		cmd_gts_request *mac_gts_request;
		
		MPDU *frame_pkt;
		
		uint16_t frame_control;
		////printfUART("create_gts_request_cmd\n", "");
		
		
		if (send_buffer_msg_in == SEND_BUFFER_SIZE)
			send_buffer_msg_in=0;

		frame_pkt = (MPDU *) &send_buffer[send_buffer_msg_in];
		
		mac_gts_request= (cmd_gts_request*) &send_buffer[send_buffer_msg_in].data;

		frame_pkt->length = 11;
	
		if ( get_characteristic_type(gts_characteristics) != 0 )
		{   
			//frame_pkt->frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS);   //dest | source
		
			frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS); 
			frame_pkt->frame_control1 =(uint8_t)( frame_control);
			frame_pkt->frame_control2 =(uint8_t)( frame_control >> 8);
		}
		else
		{	
			//frame_pkt->frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS);
			
			frame_control = set_frame_control(TYPE_CMD,0,0,1,1,0,SHORT_ADDRESS);
			frame_pkt->frame_control1 =(uint8_t)( frame_control);
			frame_pkt->frame_control2 =(uint8_t)( frame_control >> 8);
		}
		
		frame_pkt->seq_num = mac_PIB.macDSN;
		
		gts_request_seq_num = frame_pkt->seq_num;
		
		mac_PIB.macDSN++;
		
		//enable retransmissions
		send_buffer[send_buffer_msg_in].retransmission =1;
		send_buffer[send_buffer_msg_in].indirect = 0;
		
		//mac_gts_request->source_PAN_identifier = 0x0001;
		mac_gts_request->source_PAN_identifier = mac_PIB.macPANId;
		
		mac_gts_request->source_address = mac_PIB.macShortAddress;
	
		mac_gts_request->command_frame_identifier = CMD_GTS_REQUEST;
		
		//mac_gts_request->gts_characteristics = set_gts_characteristics(2,1,1);
		mac_gts_request->gts_characteristics =gts_characteristics;
		
		//increment the send buffer variables
		send_buffer_count++;
		send_buffer_msg_in++;
		
		post send_frame_csma();
		
		}

	return;
	}
*/




