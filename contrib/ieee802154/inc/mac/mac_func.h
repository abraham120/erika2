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
* $Id: mac_func.h,v 1.2 2008/07/04 09:47:25 chris Exp $
* $Log: mac_func.h,v $
* Revision 1.2  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

#include "ee.h"

#include "mac/mac_enumerations.h"
#include "mac/mac_const.h"
/*******************************************************************************************************************/ 

EE_UINT8 set_capability_information(EE_UINT8 alternate_PAN_coordinator, EE_UINT8 device_type, EE_UINT8 power_source, EE_UINT8 receiver_on_when_idle, EE_UINT8 security, EE_UINT8 allocate_address);

EE_UINT8 get_alternate_PAN_coordinator(EE_UINT8 capability_information);


  
/*******************************************************************************************************************/  
/********************************FRAME CONTROL FUNCTIONS************************************************************/
/*******************************************************************************************************************/
  
 //build MPDU frame control field
EE_UINT16 set_frame_control(EE_UINT8 frame_type,EE_UINT8 security,EE_UINT8 frame_pending,EE_UINT8 ack_request,EE_UINT8 intra_pan,EE_UINT8 dest_addr_mode,EE_UINT8 source_addr_mode); 

//return the type of destination address specified in the frame control 
EE_UINT8 get_fc2_dest_addr(EE_UINT8 frame_control);

//return the type of source address specified in the frame control 
EE_UINT8 get_fc2_source_addr(EE_UINT8 frame_control);

EE_UINT8 get_fc1_security(EE_UINT8 frame_control);

EE_UINT8 get_fc1_frame_pending(EE_UINT8 frame_control);

EE_UINT8 get_fc1_ack_request(EE_UINT8 frame_control);

EE_UINT8 get_fc1_intra_pan(EE_UINT8 frame_control);
 
/*******************************************************************************************************************/  
/********************************SUPERFRAME SPECIFICATION FUNCTIONS*************************************************/
/*******************************************************************************************************************/

//build beacon superframe specification
EE_UINT16 set_superframe_specification(EE_UINT8 beacon_order,EE_UINT8 superframe_order,EE_UINT8 final_cap_slot,EE_UINT8 battery_life_extension,EE_UINT8 pan_coordinator,EE_UINT8 association_permit);

EE_UINT8 get_beacon_order(EE_UINT16 superframe);

EE_UINT8 get_superframe_order(EE_UINT16 superframe);

EE_UINT8 get_pan_coordinator(EE_UINT16 superframe);

EE_UINT8 get_association_permit(EE_UINT16 superframe);

EE_UINT8 get_battery_life_extention(EE_UINT16 superframe);

EE_UINT8 get_final_cap_slot(EE_UINT16 superframe);

/*******************************************************************************************************************/  
/********************************      DATA TX OPTIONS   ************************************************************/
/*******************************************************************************************************************/

EE_UINT8 set_txoptions(EE_UINT8 ack, EE_UINT8 gts, EE_UINT8 indirect_transmission,EE_UINT8 security);

EE_UINT8 get_txoptions_ack(EE_UINT8 txoptions);
  
EE_UINT8 get_txoptions_gts(EE_UINT8 txoptions); 

EE_UINT8 get_txoptions_indirect_transmission(EE_UINT8 txoptions);

EE_UINT8 get_txoptions_security(EE_UINT8 txoptions);

//BEACON SCHEDULING IMPLEMENTATION
EE_UINT8 get_txoptions_upstream_buffer(EE_UINT8 txoptions);

EE_UINT8 set_txoptions_upstream(EE_UINT8 ack, EE_UINT8 gts, EE_UINT8 indirect_transmission,EE_UINT8 security,EE_UINT8 upstream);

/******************************************************************************************************************/  
/********************************PENDING ADDRESSES FUNCTIONS********************************************************/
/*******************************************************************************************************************/
EE_UINT8 set_pending_address_specification(EE_UINT8 number_short, EE_UINT8 number_extended);

EE_UINT8 get_number_short(EE_UINT8 pending_specification);

EE_UINT8 get_number_extended(EE_UINT8 pending_specification);

/*******************************************************************************************************************/  
/********************************GTS FIELDS FUNCTIONS***************************************************************/
/*******************************************************************************************************************/
EE_UINT8 set_gts_specification(EE_UINT8 gts_descriptor_count, EE_UINT8 gts_permit);

EE_UINT8 get_gts_permit(EE_UINT8 gts_specification);

///UNUSED
EE_UINT8 set_gts_directions(EE_UINT8 gts1,EE_UINT8 gts2,EE_UINT8 gts3,EE_UINT8 gts4,EE_UINT8 gts5,EE_UINT8 gts6,EE_UINT8 gts7);

EE_UINT8 set_gts_descriptor(EE_UINT8 GTS_starting_slot, EE_UINT8 GTS_length);

EE_UINT8 get_gts_descriptor_len(EE_UINT8 gts_des_part);

EE_UINT8 get_gts_descriptor_ss(EE_UINT8 gts_des_part);

/************************************************************************************************/  
/********************************GTS CHARACTERISTICS*************************************************/
/************************************************************************************************/
EE_UINT8 set_gts_characteristics(EE_UINT8 gts_length, EE_UINT8 gts_direction, EE_UINT8 characteristic_type);

EE_UINT8 get_gts_length(EE_UINT8 gts_characteristics);

EE_UINT8 get_gts_direction(EE_UINT8 gts_characteristics);

EE_UINT8 get_characteristic_type(EE_UINT8 gts_characteristics);


