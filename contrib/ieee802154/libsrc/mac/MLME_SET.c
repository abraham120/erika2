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
* $Id: MLME_SET.c,v 1.2 2008/07/04 09:47:25 chris Exp $
* $Log: MLME_SET.c,v $
* Revision 1.2  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * MLME-SET-Service Access Point
 * pag 98
 */
 
#include "ee.h"
#include "mac/MLME_SET.h"

#include "mac/mac_const.h"
#include "mac/mac_enumerations.h"

extern macPIB mac_PIB;


EE_UINT8 MLME_SET_request(EE_UINT8 PIBAttribute,EE_UINT8 PIBAttributeValue[])
{
switch(PIBAttribute)
	{
	
	
		case MACACKWAITDURATION :		mac_PIB.macAckWaitDuration = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
									
		case MACASSOCIATIONPERMIT:  	if ((EE_UINT8)PIBAttributeValue[1] == 0x00)
										{
											mac_PIB.macAssociationPermit = 0x00;
										}
										else
										{
											mac_PIB.macAssociationPermit = 0x01;
										}
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
		case MACAUTOREQUEST : 			mac_PIB.macAutoRequest = PIBAttributeValue[0];
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
		case MACBATTLIFEEXT:			mac_PIB.macBattLifeExt = PIBAttributeValue[0];
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACBATTLIFEEXTPERIODS:		mac_PIB.macBattLifeExtPeriods = PIBAttributeValue[0];
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
		case MACBEACONPAYLOAD:			
										//memcpy(&PIBAttributeValue[0],&mac_PIB.macBeaconPayload[0],mac_PIB.macBeaconPayloadLenght * sizeof(EE_UINT8));
										//TODO
										//Copy data to the macBeaconPayload
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
				
		case MACMAXBEACONPAYLOADLENGTH:	mac_PIB.macBeaconPayloadLenght = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
		case MACBEACONORDER:			mac_PIB.macBeaconOrder = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACBEACONTXTIME:			mac_PIB.macBeaconTxTime =PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACBSN:					mac_PIB.macBSN = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;

		case MACCOORDEXTENDEDADDRESS:	//mac_PIB.macCoordExtendedAddress0 = ((PIBAttributeValue[0] >> 24) | (PIBAttributeValue[1] >> 16) | (PIBAttributeValue[2] >> 8) | (PIBAttributeValue[3])) ;
										//mac_PIB.macCoordExtendedAddress1 = ((PIBAttributeValue[4] >> 24) | (PIBAttributeValue[5] >> 16) | (PIBAttributeValue[6] >> 8) | (PIBAttributeValue[7]));

										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
									
		case MACCOORDSHORTADDRESS:		mac_PIB.macCoordShortAddress= ((PIBAttributeValue[0] << 8) |PIBAttributeValue[1]);

										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		
		case MACDSN:					mac_PIB.macDSN = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACGTSPERMIT:				mac_PIB.macGTSPermit = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACMAXCSMABACKOFFS:		mac_PIB.macMaxCSMABackoffs = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACMINBE:					mac_PIB.macMinBE = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		
		case MACPANID:					mac_PIB.macPANId = ((PIBAttributeValue[0] << 8)| PIBAttributeValue[1]);
										//TODO
										//Implement the hardware address decode
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		
		case MACPROMISCUOUSMODE:		mac_PIB.macPromiscuousMode = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
		case MACRXONWHENIDLE:			mac_PIB.macRxOnWhenIdle = PIBAttributeValue[0];
										
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
										
		case MACSHORTADDRESS:			mac_PIB.macShortAddress = ((PIBAttributeValue[0] << 8) |PIBAttributeValue[1]);
										//TODO
										//Implement the hardware address decode
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
		case MACSUPERFRAMEORDER:		mac_PIB.macSuperframeOrder = PIBAttributeValue[0];
										MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
										break;
										
		case MACTRANSACTIONPERSISTENCETIME:	 mac_PIB.macTransactionPersistenceTime = PIBAttributeValue[0];
											 MLME_SET_confirm(MAC_SUCCESS,PIBAttribute);
											 break;
											
		default:						MLME_SET_confirm(MAC_UNSUPPORTED_ATTRIBUTE,PIBAttribute);
										break;
										
		
	}

return 1;
}
