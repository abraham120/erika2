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
* $Id: MLME_ASSOCIATE.h,v 1.4 2008/07/04 09:47:25 chris Exp $
* $Log: MLME_ASSOCIATE.h,v $
* Revision 1.4  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * MLME-ASSOCIATE-Service Access Point
 *	std pag 65
 */

#include "ee.h"

#include "phy/phy.h"

#include "mac/mac_const.h"
#include "mac/mac_enumerations.h"

#include "phy/phy_enumerations.h"

EE_UINT8 MLME_ASSOCIATE_request(EE_UINT8 LogicalChannel,EE_UINT8 CoordAddrMode,EE_UINT16 CoordPANId,EE_UINT32 CoordAddress[],EE_UINT8 CapabilityInformation,EE_UINT8 SecurityEnable);
  
EE_UINT8 MLME_ASSOCIATE_indication(EE_UINT32 DeviceAddress[], EE_UINT8 CapabilityInformation, EE_UINT8 SecurityUse, EE_UINT8 ACLEntry);
  
EE_UINT8 MLME_ASSOCIATE_response(EE_UINT32 DeviceAddress[], EE_UINT16 AssocShortAddress, EE_UINT8 status, EE_UINT8 SecurityEnable);
  
EE_UINT8 MLME_ASSOCIATE_confirm(EE_UINT16 AssocShortAddress, EE_UINT8 status);

//  
//	void create_association_request_cmd(uint8_t CoordAddrMode,uint16_t CoordPANId,uint32_t CoordAddress[],uint8_t CapabilityInformation);
//
//	error_t create_association_response_cmd(uint32_t DeviceAddress[],uint16_t shortaddress, uint8_t status);
//	
//	void create_disassociation_notification_cmd(uint32_t DeviceAddress[],uint8_t disassociation_reason);
//	
//	void process_dissassociation_notification(MPDU *pdu);
//	


