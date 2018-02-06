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
* $Id: PLME_SET.c,v 1.4 2008/07/14 10:48:34 chris Exp $
* $Log: PLME_SET.c,v $
* Revision 1.4  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.3  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
* Physical Layer Management Entity-Service Access Point
* PLME-SAP - PLME-SET
*
*/

#include "ee.h"
#include "phy/PLME_SET.h"

#include "phy/phy_const.h"
#include "phy/phy_enumerations.h"

#include "common/hal.h"

#include "hal/hal_interrupts.h"

extern phyPIB phy_PIB;

EE_UINT8 PLME_SET_request(EE_UINT8 PIBAttribute, EE_UINT8 PIBAttributeValue)
{
	//MAC is demanding for PHY to write the indicated PIB value
	  switch(PIBAttribute)
			{
				case PHYCURRENTCHANNEL:
					
					phy_PIB.phyCurrentChannel = PIBAttributeValue;
										
					//TODO
					//Implement the channel change
					//cc2420_set_channel();
					hal_set_channel(phy_PIB.phyCurrentChannel);	
					hal_set_rx();
					PLME_SET_confirm(PHY_SUCCESS, PIBAttribute);
					break;
	
				case PHYCHANNELSSUPPORTED:
					phy_PIB.phyChannelsSupported = PIBAttributeValue;
					PLME_SET_confirm(PHY_SUCCESS, PIBAttribute);
					break;
	
				case PHYTRANSMITPOWER:
					phy_PIB.phyTransmitPower= PIBAttributeValue;
										
					//TODO
					//Implement the transmit power change
					
					PLME_SET_confirm(PHY_SUCCESS, PIBAttribute);
					break;
				case PHYCCAMODE:
					phy_PIB.phyCcaMode= PIBAttributeValue;
					
					//TODO
					//Implement the CCAmode change
					
					PLME_SET_confirm(PHY_SUCCESS, PIBAttribute);
					break;
				default:
					PLME_SET_confirm(PHY_UNSUPPORTED_ATTRIBUTE, PIBAttribute);
					break;
			}
	
	return 1;
}
