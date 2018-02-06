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
* $Id: MLME_START.c,v 1.4 2008/07/04 09:47:25 chris Exp $
* $Log: MLME_START.c,v $
* Revision 1.4  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * MLME-START-Service Access Point
 *pag 100
 *
 */

#include "math.h"

#include "ee.h"
#include "mac/MLME_START.h"

#include "mac/Mac.h"
#include "mac/mac_const.h"
#include "mac/mac_enumerations.h"

#include "phy/phy.h"
#include "phy/phy_enumerations.h"

#include "ieee802154alarms/ieee802154alarms.h"


extern EE_UINT8 PANCoordinator;

extern EE_UINT8 Beacon_enabled_PAN;

//Beacon Interval
extern EE_UINT32 BI;
	//Superframe duration
extern EE_UINT32 SD;

extern EE_UINT32 time_slot;

extern macPIB mac_PIB;

//request for the device to start using new superframe configuration
EE_UINT8 MLME_START_request(EE_UINT16 PANId, EE_UINT8 LogicalChannel, EE_UINT8 beacon_order, EE_UINT8 superframe_order,EE_UINT8 pan_coodinator,EE_UINT8 BatteryLifeExtension,EE_UINT8 CoordRealignment,EE_UINT8 securityenable,EE_UINT32 StartTime)
{
//pag 102

	EE_UINT32 BO_EXPONENT;
	EE_UINT32 SO_EXPONENT;

	PANCoordinator=1;
	Beacon_enabled_PAN=1;
	
	//this is the PAN Coordinator
	mac_PIB.macShortAddress = 0x0000;

	if ( mac_PIB.macShortAddress == 0xffff)
	{
		MLME_START_confirm(MAC_NO_SHORT_ADDRESS);
		return 1;
	}
	else
	{
		mac_PIB.macBeaconOrder = beacon_order;
			
		if (beacon_order == 15)
		{
			mac_PIB.macSuperframeOrder = 15;
		}
		else
		{
			mac_PIB.macSuperframeOrder = superframe_order;
		}
		
		//PANCoordinator is set to TRUE
		if (pan_coodinator == 1)
		{
			mac_PIB.macPANId = PANId;
			
			PLME_SET_request(PHYCURRENTCHANNEL,LogicalChannel);
		}
		if (CoordRealignment == 1)
		{
			//generates and broadcasts a coordinator realignment command containing the new PANId and LogicalChannels
		}
		if (securityenable == 1)
		{
		//security parameters
		}
	}
		
	if (mac_PIB.macSuperframeOrder == 0)
		SO_EXPONENT = 1;
	else
	{
		SO_EXPONENT = powf(2,mac_PIB.macSuperframeOrder);	
	}
	
	if ( mac_PIB.macBeaconOrder == 0)
		BO_EXPONENT = 1;
	else
	{
		BO_EXPONENT = powf(2,mac_PIB.macBeaconOrder);
			
	}	
		
	BI = aBaseSuperframeDuration * BO_EXPONENT; 
			
	SD = aBaseSuperframeDuration * SO_EXPONENT; 

	time_slot = SD / NUMBER_TIME_SLOTS;
		
	ieee802145alarms_set_bi_sd(BI,SD);
	
	create_beacon();
	
	ieee802145alarms_start();

	MLME_START_confirm(MAC_SUCCESS);
		
return 1;
}
  

  
