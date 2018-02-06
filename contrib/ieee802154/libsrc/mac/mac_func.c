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
* $Id: mac_func.c,v 1.2 2008/07/04 09:47:25 chris Exp $
* $Log: mac_func.c,v $
* Revision 1.2  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


#include "mac/mac_func.h"

#include "mac/mac_enumerations.h"
#include "mac/mac_const.h"
/*******************************************************************************************************************/ 

EE_UINT8 set_capability_information(EE_UINT8 alternate_PAN_coordinator, EE_UINT8 device_type, EE_UINT8 power_source, EE_UINT8 receiver_on_when_idle, EE_UINT8 security, EE_UINT8 allocate_address)
{
	
	return ((allocate_address << 7 ) | (security << 6 ) | (receiver_on_when_idle << 3 ) | (power_source << 2 ) | ( device_type << 1 ) | (alternate_PAN_coordinator << 0) );
}

EE_UINT8 get_alternate_PAN_coordinator(EE_UINT8 capability_information)
{

if ( (capability_information & 0x01) == 0x01)
	return 1;
else
	return 0;

}

  
/*******************************************************************************************************************/  
/********************************FRAME CONTROL FUNCTIONS************************************************************/
/*******************************************************************************************************************/
  
 //build MPDU frame control field
EE_UINT16 set_frame_control(EE_UINT8 frame_type,EE_UINT8 security,EE_UINT8 frame_pending,EE_UINT8 ack_request,EE_UINT8 intra_pan,EE_UINT8 dest_addr_mode,EE_UINT8 source_addr_mode) 
{
	  EE_UINT8 fc_b1=0;
	  EE_UINT8 fc_b2=0;
  	  fc_b1 = ( (intra_pan << 6) | (ack_request << 5) | (frame_pending << 4) |
 	   		  (security << 3) | (frame_type << 0) );				  
	  fc_b2 = ( (source_addr_mode << 6) | (dest_addr_mode << 2));
	  return ( (fc_b2 << 8 ) | (fc_b1 << 0) );

} 


//return the type of destination address specified in the frame control 

EE_UINT8 get_fc2_dest_addr(EE_UINT8 frame_control)
{
	switch( frame_control & 0xC )
	{
	case 0x4:	return RESERVED_ADDRESS; 
							break;
	case 0x8: return SHORT_ADDRESS;
						 break;
	case 0xC: return LONG_ADDRESS;
						break;
	default:
			return 0; 
			break;
	}
}

//return the type of source address specified in the frame control 

EE_UINT8 get_fc2_source_addr(EE_UINT8 frame_control)
{
	switch(frame_control & 0xC0 )
	{
	case 0x40:	return RESERVED_ADDRESS; 
							break;
	case 0x80: return SHORT_ADDRESS;
						 break;
	case 0xC0: return LONG_ADDRESS;
						break;
	default:
			return 0; 
			break;
	}
}

EE_UINT8 get_fc1_security(EE_UINT8 frame_control)
{

if ( (frame_control & 0x8) == 0x8)
	return 1;
else
	return 0;

}

EE_UINT8 get_fc1_frame_pending(EE_UINT8 frame_control)
{

if ( (frame_control & 0x10) == 0x10)
	return 1;
else
	return 0;
	
}

EE_UINT8 get_fc1_ack_request(EE_UINT8 frame_control)
{

if ( (frame_control & 0x20) == 0x20)
	return 1;
else
	return 0;
	
}

EE_UINT8 get_fc1_intra_pan(EE_UINT8 frame_control)
{

if ( (frame_control & 0x40) == 0x40)
	return 1;
else
	return 0;
	
} 
 
  
/*******************************************************************************************************************/  
/********************************SUPERFRAME SPECIFICATION FUNCTIONS*************************************************/
/*******************************************************************************************************************/

//build beacon superframe specification
EE_UINT16 set_superframe_specification(EE_UINT8 beacon_order,EE_UINT8 superframe_order,EE_UINT8 final_cap_slot,EE_UINT8 battery_life_extension,EE_UINT8 pan_coordinator,EE_UINT8 association_permit)
{
	  EE_UINT8 sf_b1=0;
	  EE_UINT8 sf_b2=0;
	  sf_b1 = ( (superframe_order << 4) | (beacon_order <<0));
	  sf_b2 = ( (association_permit << 7) | (pan_coordinator << 6) |
	  		    (battery_life_extension << 4) | (final_cap_slot << 0) );
	   return  ( (sf_b2 <<8 ) | (sf_b1 << 0) );  
   
}

EE_UINT8 get_beacon_order(EE_UINT16 superframe)
{
	return ((EE_UINT8)superframe &  0xF);
}

EE_UINT8 get_superframe_order(EE_UINT16 superframe)
{
	return (((EE_UINT8)superframe >> 4) &  0xF);
}



EE_UINT8 get_pan_coordinator(EE_UINT16 superframe)
{
if ( ((EE_UINT8)superframe & 0x40) == 0x40)
	return 1;
else
	return 0;
	
}

EE_UINT8 get_association_permit(EE_UINT16 superframe)
{
if ( ((EE_UINT8)superframe & 0x80) == 0x80)
	return 1;
else
	return 0;	
}

EE_UINT8 get_battery_life_extention(EE_UINT16 superframe)
{
if ( ((EE_UINT8)superframe & 0x10) == 0x10)
	return 1;
else
	return 0;	
}

EE_UINT8 get_final_cap_slot(EE_UINT16 superframe)
{
return (((EE_UINT8)superframe >> 4) &  0xF);
}


/*******************************************************************************************************************/  
/********************************      DATA TX OPTIONS   ************************************************************/
/*******************************************************************************************************************/
  
  
EE_UINT8 set_txoptions(EE_UINT8 ack, EE_UINT8 gts, EE_UINT8 indirect_transmission,EE_UINT8 security)
{
return ( (ack << 0) | (gts << 1) | (indirect_transmission << 2) | (security << 3 ) );
}  
  
EE_UINT8 get_txoptions_ack(EE_UINT8 txoptions)
{

if ( (txoptions & 0x1) == 0x1)
	return 1;
else
	return 0;

}
  
EE_UINT8 get_txoptions_gts(EE_UINT8 txoptions)
{

if ( (txoptions & 0x2) == 0x2)
	return 1;
else
	return 0;

}  

EE_UINT8 get_txoptions_indirect_transmission(EE_UINT8 txoptions)
{

if ( (txoptions & 0x4) == 0x4)
	return 1;
else
	return 0;

}  

EE_UINT8 get_txoptions_security(EE_UINT8 txoptions)
{

if ( (txoptions & 0x8) == 0x8)
	return 1;
else
	return 0;
}


//BEACON SCHEDULING IMPLEMENTATION
EE_UINT8 get_txoptions_upstream_buffer(EE_UINT8 txoptions) 
{

if ( (txoptions & 0x10) == 0x10)
	return 1;
else
	return 0;
}

EE_UINT8 set_txoptions_upstream(EE_UINT8 ack, EE_UINT8 gts, EE_UINT8 indirect_transmission,EE_UINT8 security,EE_UINT8 upstream)
{
return ( (ack << 0) | (gts << 1) | (indirect_transmission << 2) | (security << 3 ) | (upstream << 4) );
} 


/*******************************************************************************************************************/  
/********************************PENDING ADDRESSES FUNCTIONS********************************************************/
/*******************************************************************************************************************/
EE_UINT8 set_pending_address_specification(EE_UINT8 number_short, EE_UINT8 number_extended)
{
	return ( (number_extended << 4) | (number_short << 0) );
}

EE_UINT8 get_number_short(EE_UINT8 pending_specification)
{
	return (pending_specification & 0x07);
}

EE_UINT8 get_number_extended(EE_UINT8 pending_specification)
{
	return ( (pending_specification >> 4) & 0x07);
}


/*******************************************************************************************************************/  
/********************************GTS FIELDS FUNCTIONS***************************************************************/
/*******************************************************************************************************************/
EE_UINT8 set_gts_specification(EE_UINT8 gts_descriptor_count, EE_UINT8 gts_permit)
{
	return ( ( gts_descriptor_count << 0) | (gts_permit << 7) );  
}

EE_UINT8 get_gts_permit(EE_UINT8 gts_specification)
{
return ( (gts_specification >> 7) & 0x01);
}


///UNUSED
EE_UINT8 set_gts_directions(EE_UINT8 gts1,EE_UINT8 gts2,EE_UINT8 gts3,EE_UINT8 gts4,EE_UINT8 gts5,EE_UINT8 gts6,EE_UINT8 gts7)
{
	return ((gts1 << 0) | (0 << 7));
}


EE_UINT8 set_gts_descriptor(EE_UINT8 GTS_starting_slot, EE_UINT8 GTS_length)
{
//part of the descriptor list
	return ( (GTS_starting_slot << 0) | (GTS_length << 4) );
}

EE_UINT8 get_gts_descriptor_len(EE_UINT8 gts_des_part)
{
	return ( (gts_des_part & 0xf0) >> 4);
}

EE_UINT8 get_gts_descriptor_ss(EE_UINT8 gts_des_part)
{
	return (gts_des_part & 0x0f);
}



/************************************************************************************************/  
/********************************GTS CHARACTERISTICS*************************************************/
/************************************************************************************************/
EE_UINT8 set_gts_characteristics(EE_UINT8 gts_length, EE_UINT8 gts_direction, EE_UINT8 characteristic_type)
{
	return ( (gts_length << 0) | (gts_direction << 4) | (characteristic_type << 5));
}  
 
 
EE_UINT8 get_gts_length(EE_UINT8 gts_characteristics)
{
	return (gts_characteristics &  0xF);
}

EE_UINT8 get_gts_direction(EE_UINT8 gts_characteristics)
{
	if ( (gts_characteristics & 0x10) == 0x10)
		return 1;
	else
		return 0;
}  

EE_UINT8 get_characteristic_type(EE_UINT8 gts_characteristics)
{
	if ( (gts_characteristics & 0x20) == 0x20)
		return 1;
	else
		return 0;
} 
