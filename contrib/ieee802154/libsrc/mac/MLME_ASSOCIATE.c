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
* $Id: MLME_ASSOCIATE.c,v 1.5 2008/07/14 10:48:34 chris Exp $
* $Log: MLME_ASSOCIATE.c,v $
* Revision 1.5  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.4  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * MLME-ASSOCIATE-Service Access Point
 *	std pag 65
 */

#include "mac/MLME_ASSOCIATE.h"
#include "common/hal.h"

extern macPIB mac_PIB;

extern EE_UINT8 PANCoordinator;

EE_UINT8 MLME_ASSOCIATE_request(EE_UINT8 LogicalChannel,EE_UINT8 CoordAddrMode,EE_UINT16 CoordPANId,EE_UINT32 CoordAddress[],EE_UINT8 CapabilityInformation,EE_UINT8 SecurityEnable)
{

	//updates the PAN ID 
	mac_PIB.macPANId = CoordPANId;
	mac_PIB.macCoordShortAddress = (EE_UINT16)(CoordAddress[1] & 0x000000ff);
	
	PANCoordinator =0;
	
	
	//associating=1; //boolean variable stating that the device is trying to associate
	
	//TODO
	//ENABLE_TIMERS
	
	//the channel selection is made during the SynC procedure
	//PLME_SET_request(PHYCURRENTCHANNEL, LogicalChannel);
	
	//hal_set_rx();
	//current_channel = LogicalChannel;
	
	//create_association_request_cmd(CoordAddrMode,CoordPANId,CoordAddress,CapabilityInformation);

return 1;
}
 
EE_UINT8 MLME_ASSOCIATE_response(EE_UINT32 DeviceAddress[], EE_UINT16 AssocShortAddress, EE_UINT8 status, EE_UINT8 SecurityEnable)
{


return 1;
}

  
