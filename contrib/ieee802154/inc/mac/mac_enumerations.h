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
* $Id: mac_enumerations.h,v 1.2 2008/07/04 09:47:25 chris Exp $
* $Log: mac_enumerations.h,v $
* Revision 1.2  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

 
#ifndef __MAC_ENUMERATIONS__
#define __MAC_ENUMERATIONS__
 
//Mac enumerations standard pag 110

enum { 
		MAC_SUCCESS = 0x00,
        MAC_BEACON_LOSS = 0xE0,
        MAC_CHANNEL_ACCESS_FAILURE = 0xE1,
        MAC_DENIED = 0xE2,
		//MLME-RESET
        MAC_DISABLE_TRX_FAILURE = 0xE3,
        MAC_FAILED_SECURITY_CHECK = 0xE4,
        MAC_FRAME_TOO_LONG = 0xE5,
        MAC_INVALID_GTS = 0xE6,
        MAC_INVALID_HANDLE = 0xE7,
        MAC_INVALID_PARAMETER = 0xE8,
        MAC_NO_ACK = 0xE9,
        MAC_NO_BEACON = 0xEA,
        MAC_NO_DATA = 0xEB,
        MAC_NO_SHORT_ADDRESS = 0xEC,
        MAC_OUT_OF_CAP = 0xED,
        MAC_PAN_ID_CONFLICT = 0xEE,
        MAC_REALIGNMENT = 0xEF,
        MAC_TRANSACTION_EXPIRED = 0xF0,
        MAC_TRANSACTION_OVERFLOW = 0xF1,
        MAC_TX_ACTIVE = 0xF2,
        MAC_UNAVAILABLE_KEY = 0xF3,
        MAC_UNSUPPORTED_ATTRIBUTE = 0xF4
        };



//mac dissassociation enums
enum{
		MAC_PAN_COORD_LEAVE = 0x01,
        MAC_PAN_DEVICE_LEAVE = 0x02,

};



//mac commands enums
enum {

	CMD_ASSOCIATION_REQUEST = 0x01,
	CMD_ASSOCIATION_RESPONSE = 0x02,
	CMD_DISASSOCIATION_NOTIFICATION = 0x03,
	CMD_DATA_REQUEST = 0x04,
	CMD_PANID_CONFLICT = 0x05,
	CMD_ORPHAN_NOTIFICATION = 0x06,
	CMD_BEACON_REQUEST = 0x07,
	CMD_COORDINATOR_REALIGNMENT = 0x08,
	CMD_GTS_REQUEST = 0x09
};


//mac association responses
enum {

	CMD_RESP_ASSOCIATION_SUCCESSFUL = 0x00,
	CMD_RESP_PAN_CAPACITY =0x01,
	CMD_RESP_ACCESS_DENIED =0x02
	
};

//MAC PIB Enumeration
enum {

	MACACKWAITDURATION = 0x40,
	MACASSOCIATIONPERMIT=0x41,
	MACAUTOREQUEST = 0x42,
	MACBATTLIFEEXT=0x43,
	MACBATTLIFEEXTPERIODS=0x44,
	MACBEACONPAYLOAD=0x45,
	MACMAXBEACONPAYLOADLENGTH=0x46,
	MACBEACONORDER=0x47,
	MACBEACONTXTIME=0x48,
	MACBSN=0x49,
	MACCOORDEXTENDEDADDRESS=0x4a,
	MACCOORDSHORTADDRESS=0x4b,
	MACDSN=0x4c,
	MACGTSPERMIT=0x4d,
	MACMAXCSMABACKOFFS=0x4e,
	MACMINBE=0x4f,
	MACPANID=0x50,
	MACPROMISCUOUSMODE=0x51,
	MACRXONWHENIDLE=0x52,
	MACSHORTADDRESS=0x53,
	MACSUPERFRAMEORDER=0x54,
	MACTRANSACTIONPERSISTENCETIME=0x55

};

//gts enumerations
enum{
	GTS_TX_ONLY = 0x00,
	GTS_RX_ONLY = 0x01
};

//channel scan enumerations
enum{
	ED_SCAN = 0x00,
	ACTIVE_SCAN = 0x01,
	PASSIVE_SCAN = 0x02,
	ORPHAN_SCAN = 0x03
};


#endif

