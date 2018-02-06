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
* $Id: frame_format.h,v 1.4 2008/07/04 09:47:25 chris Exp $
* $Log: frame_format.h,v $
* Revision 1.4  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

//MAC frame Superstructure

#ifndef __FRAME_FORMAT__
#define __FRAME_FORMAT__

#define MPDU_HEADER_LEN 5

typedef struct MPDU
{
	EE_UINT8 length;
	//info on frame type/ack/etc
	EE_UINT8 frame_control1;
	//info on addressing fields
	EE_UINT8 frame_control2;
	//EE_UINT16 frame_control;
	EE_UINT8 seq_num;
	EE_UINT8 data[120];
}MPDU;

typedef struct MPDUBuffer
{
	EE_UINT8 length;
	//EE_UINT16 frame_control;
	EE_UINT8 frame_control1;
	EE_UINT8 frame_control2;
	EE_UINT8 seq_num;
	EE_UINT8 data[120];
	EE_UINT8 retransmission;
	EE_UINT8 indirect;
}MPDUBuffer;

//PD_DATA validation structures



/*****************************************************/
/*				BEACON FRAME SCTRUCTURES			 */
/*****************************************************/

//#define beacon_addr_short_length 7
//#define beacon_addr_long_length 12


typedef struct beacon_addr_short
{
	EE_UINT16 destination_PAN_identifier;
	EE_UINT16 destination_address;
	EE_UINT16 source_address;
	EE_UINT16 superframe_specification;
}beacon_addr_short;
/*
typedef struct beacon_struct
{
	EE_UINT8 length;
	EE_UINT16 frame_control;
	EE_UINT8 seq_num;
	EE_UINT16 source_PAN_identifier;
	EE_UINT16 destination_address;
	EE_UINT16 source_address;
	EE_UINT16 superframe_specification;
}beacon_struct;
*/
/*
typedef struct beacon_addr_long
{
	EE_UINT16 source_PAN_identifier;
	EE_UINT32 source_address0;
	EE_UINT32 source_address1;
	EE_UINT16 superframe_specification;
}beacon_addr_long;
*/
/*****************************************************/
/*				ACK FRAME Structures 				 */
/*****************************************************/

typedef struct ACK
{
	EE_UINT8 length;
	EE_UINT8 frame_control1;
	EE_UINT8 frame_control2;
	//EE_UINT16 frame_control;
	EE_UINT8 seq_num;
}ACK;

/*****************************************************/
/*				COMMAND FRAME Structures 			 */
/*****************************************************/

typedef struct cmd_association_request
{
	EE_UINT8 command_frame_identifier;
	EE_UINT8 capability_information;
}cmd_association_request;

typedef struct cmd_association_response
{
	EE_UINT8 command_frame_identifier;
	EE_UINT8 short_address1;
	EE_UINT8 short_address2;
	//EE_UINT16 short_address;
	EE_UINT8 association_status;
}cmd_association_response;

//disassociacion notification command structure pag. 126
typedef struct cmd_disassociation_notification
{
	EE_UINT16 destination_PAN_identifier;
	EE_UINT32 destination_address0;
	EE_UINT32 destination_address1;
	EE_UINT16 source_PAN_identifier;
	EE_UINT32 source_address0;
	EE_UINT32 source_address1;
	EE_UINT8 command_frame_identifier;
	EE_UINT8 disassociation_reason;
}cmd_disassociation_notification;

//pag 130
typedef struct cmd_beacon_request
{
	EE_UINT16 destination_PAN_identifier;
	EE_UINT16 destination_address;
	EE_UINT8 command_frame_identifier;
}cmd_beacon_request;


//pag 132
typedef struct cmd_gts_request
{
	EE_UINT16 source_PAN_identifier;
	EE_UINT16 source_address;
	EE_UINT8 command_frame_identifier;
	EE_UINT8 gts_characteristics;
}cmd_gts_request;

typedef struct cmd_default
{
	EE_UINT8 command_frame_identifier;
}cmd_default;


//131
typedef struct cmd_coord_realignment
{
	EE_UINT8 command_frame_identifier;
	EE_UINT8 PAN_identifier0;
	EE_UINT8 PAN_identifier1;
	EE_UINT8 coordinator_short_address0;
	EE_UINT8 coordinator_short_address1;
	
	/*
	EE_UINT16 PAN_identifier;
	EE_UINT16 coordinator_short_address;
	*/
	EE_UINT8 logical_channel;
	EE_UINT16 short_address;
}cmd_coord_realignment;



/*******************************************************/
/*     			ADDRESSING FIELDS ONLY				   */
/*******************************************************/
#define DEST_SHORT_LEN 4
#define DEST_LONG_LEN 10
#define INTRA_PAN_SOURCE_SHORT_LEN 2
#define INTRA_PAN_SOURCE_LONG_LEN 8
#define SOURCE_SHORT_LEN 4
#define SOURCE_LONG_LEN 10


//DESTINATION
typedef struct dest_short
{
	EE_UINT16 destination_PAN_identifier;
	EE_UINT16 destination_address;
}dest_short;

typedef struct dest_long
{
	EE_UINT16 destination_PAN_identifier;
	EE_UINT32 destination_address0;
	EE_UINT32 destination_address1;
}dest_long;

//SOURCE
typedef struct intra_pan_source_short
{
	EE_UINT16 source_address;
}intra_pan_source_short;

typedef struct intra_pan_source_long
{
	EE_UINT32 source_address0;
	EE_UINT32 source_address1;
}intra_pan_source_long;


typedef struct source_short
{
	EE_UINT16 source_PAN_identifier;
	EE_UINT16 source_address;
}source_short;


typedef struct source_long
{
	EE_UINT16 source_PAN_identifier;
	EE_UINT32 source_address0;
	EE_UINT32 source_address1;
}source_long;

#endif

