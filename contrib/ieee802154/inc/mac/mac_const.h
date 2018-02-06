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
* $Id: mac_const.h,v 1.4 2008/07/04 09:47:25 chris Exp $
* $Log: mac_const.h,v $
* Revision 1.4  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


// The MAC constants are defined in here.
// Notice that these makes use of the PHY constants.
//pag 134

#ifndef __MAC_CONST__
#define __MAC_CONST__

#include "phy/phy_const.h"

#define aBaseSlotDuration          60
#define aBaseSuperframeDuration    960 //aBaseSlotDuration*aNumSuperframeSlots

//#define aExtendedAddress         // This should be defined by the device!

#define aMaxBE                     5 //CSMA-CA

#define aMaxBeaconOverhead         75
#define aMaxBeaconPayloadLength    aMaxPHYPacketSize-aMaxBeaconOverhead
#define aGTSDescPersistenceTime    4
#define aMaxFrameOverhead          25
#define aMaxFrameResponseTime      1220
#define aMaxFrameRetries           1

//(SYNC)number of beacons lost before sending a Beacon-Lost indication
#define aMaxLostBeacons            4
#define aMaxMACFrameSize           aMaxPHYPacketSize-aMaxFrameOverhead
#define aMaxSIFSFrameSize          18
#define aMinCAPLength              440
#define aMinLIFSPeriod             40
#define aMinSIFSPeriod             12
#define aNumSuperframeSlots        16
#define aResponseWaitTime          32*aBaseSuperframeDuration
#define aUnitBackoffPeriod         20


#define TYPE_BEACON 0
#define TYPE_DATA 1
#define TYPE_ACK 2
#define TYPE_CMD 3

#define SHORT_ADDRESS 2
#define LONG_ADDRESS 3
#define RESERVED_ADDRESS 1

#define NUMBER_TIME_SLOTS 16

#define ACK_LENGTH 5

//buffer sizes
#define MAX_GTS_BUFFER 7

//#define MAX_GTS_PEND 2
//#define MAX_GTS_IN_SLOT 1

#define INDIRECT_BUFFER_SIZE 2
#define RECEIVE_BUFFER_SIZE 4
#define SEND_BUFFER_SIZE 3

#define UPSTREAM_BUFFER_SIZE 3

#define GTS_SEND_BUFFER_SIZE 15

#define BACKOFF_PERIOD_MS 0.34724
#define BACKOFF_PERIOD_US 347.24

//value of each symbol in us
#define EFFECTIVE_SYMBOL_VALUE 17.362

// MAC PIB attribute
typedef struct
{
	//pag 135
	EE_UINT8 macAckWaitDuration;
	EE_UINT8 macAssociationPermit;//FDD
	EE_UINT8 macAutoRequest;
	EE_UINT8 macBattLifeExt;
	EE_UINT8 macBattLifeExtPeriods;
	
	EE_UINT8 macBeaconPayload[aMaxBeaconPayloadLength];//FDD
	
	EE_UINT8 macBeaconPayloadLenght;//FDD
	EE_UINT8 macBeaconOrder;//FDD
	
	EE_UINT32 macBeaconTxTime;//FDD
	EE_UINT8 macBSN;//FDD
	EE_UINT32 macCoordExtendedAddress0;
	EE_UINT32 macCoordExtendedAddress1;
	EE_UINT16 macCoordShortAddress;
	EE_UINT8 macDSN;
	EE_UINT8 macGTSPermit;//FDD
	EE_UINT8 macMaxCSMABackoffs;
	EE_UINT8 macMinBE;
	EE_UINT16 macPANId;
	EE_UINT8 macPromiscuousMode;//FDD
	EE_UINT8 macRxOnWhenIdle;
	EE_UINT32 macShortAddress;
	EE_UINT8 macSuperframeOrder;//FDD
	EE_UINT32 macTransactionPersistenceTime;//FDD
	
} macPIB;

/*
// MAC PIB security ACL entry descriptor
typedef struct
{
	uint32_t ACLExtendedAddress[2];
	uint16_t ACLShortAddress;
	uint16_t ACLPANId;
	uint8_t ACLSecurityMaterialLength;
	//variable string
	uint8_t ACLSecurityMaterial;
	uint8_t ACLSecuritySuite;
	
}ACLDescriptor;

// MAC PIB security attribute
typedef struct
{
	//pag 138
	ACLDescriptor macACLEntryDescriptorSet;
	uint8_t macACLEntryDescriptorSetSize;
	bool macDefaultSecurity;
	uint8_t macDefaultSecurityMaterialLength;
	//variable string
	uint8_t macDefaultSecurityMaterial;
	uint8_t macDefaultSecuritySuite;
	uint8_t macSecurityMode;
	
}macPIBsec;
*/
//MAC PANDescriptor
typedef struct
{
	//pag76
	EE_UINT8 CoordAddrMode;
	EE_UINT16 CoordPANId;
	EE_UINT32 CoordAddress0;
	EE_UINT32 CoordAddress1;
	EE_UINT8 LogicalChannel;
	//superframe specification field
	EE_UINT16 SuperframeSpec;
	EE_UINT8 GTSPermit;
	EE_UINT8 LinkQuality;
	EE_UINT32 TimeStamp;
	EE_UINT8 SecurityUse;
	EE_UINT8 ACLEntry;
	EE_UINT8 SecurityFailure;

}PANDescriptor;


//GTS entry (used in the PAN coordinator)
typedef struct
{
	EE_UINT8 gts_id;
	EE_UINT8 starting_slot;
	EE_UINT8 length;
	EE_UINT8 direction;
	EE_UINT16 DevAddressType;
	EE_UINT8 expiration;

}GTSinfoEntryType;

//GTS entry (used in the PAN coordinator)
typedef struct
{
	EE_UINT8 gts_id;
	EE_UINT8 starting_slot;
	EE_UINT8 length;
	EE_UINT16 DevAddressType;
	EE_UINT8 persistencetime;

}GTSinfoEntryType_null;
/*
typedef struct
{
	uint8_t handler;
	uint16_t transaction_persistent_time;
	
	//MPDU frame;
	uint8_t frame[127];

}indirect_transmission_element;
*/

typedef struct gts_slot_element
{
	EE_UINT8 element_count;
	EE_UINT8 element_in;
	EE_UINT8 element_out;
	EE_UINT8 gts_send_frame_index[GTS_SEND_BUFFER_SIZE];

}gts_slot_element;

/*
typedef struct time_stamp32
{

EE_UINT32 time_stamp;

}time_stamp32;
*/
/*
typedef struct time_stamp16
{

EE_UINT16 time_stamp;

}time_stamp16;

//MAC ACTIVE CHANNEL SCAN REDUCED PAN DESCRIPTOR (SHOR ADDRESS ONLY)
typedef struct SCAN_PANDescriptor
{
	//pag76
	uint16_t CoordPANId;
	uint16_t CoordAddress;
	uint8_t LogicalChannel;
	//superframe specification field
	uint16_t SuperframeSpec;
	uint8_t lqi;
}SCAN_PANDescriptor;
*/

#endif
