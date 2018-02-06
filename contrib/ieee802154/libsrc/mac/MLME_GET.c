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
* $Id: MLME_GET.c,v 1.2 2008/07/04 09:47:25 chris Exp $
* $Log: MLME_GET.c,v $
* Revision 1.2  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * MLME-GET-Service Access Point
 *pag 78
 */

#include "ee.h"
#include "mac/MLME_GET.h"

#include "mac/mac_const.h"
#include "mac/mac_enumerations.h"

extern macPIB mac_PIB;


EE_UINT8 MLME_GET_request(EE_UINT8 PIBAttribute)
{

	switch(PIBAttribute)
	{
		case MACACKWAITDURATION :		MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macAckWaitDuration);
										break;
		case MACASSOCIATIONPERMIT:  	MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macAssociationPermit);
										break;
		case MACAUTOREQUEST : 			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macAutoRequest);
										break;
		case MACBATTLIFEEXT:			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macBattLifeExt);
										break;
		case MACBATTLIFEEXTPERIODS:		MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macBattLifeExtPeriods);
										break;
		case MACBEACONPAYLOAD:			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute, mac_PIB.macBeaconPayload);
										break;
		case MACMAXBEACONPAYLOADLENGTH:	MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macBeaconPayloadLenght);
										break;
		case MACBEACONORDER:			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macBeaconOrder);
										break;
		case MACBEACONTXTIME:			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,(EE_UINT8 *)&mac_PIB.macBeaconTxTime);
										break;
		case MACBSN:					MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macBSN);
										break;
		case MACCOORDEXTENDEDADDRESS:	MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,(EE_UINT8 *) &mac_PIB.macCoordExtendedAddress0);
										break;
		case MACCOORDSHORTADDRESS:		MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,(EE_UINT8 *) &mac_PIB.macCoordShortAddress);
										break;
		case MACDSN:					MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macDSN);
										break;
		case MACGTSPERMIT:				MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macGTSPermit);
										break;
		case MACMAXCSMABACKOFFS:		MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macMaxCSMABackoffs);
										break;
		case MACMINBE:					MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macMinBE);
										break;
		case MACPANID:					MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,(EE_UINT8 *) &mac_PIB.macPANId);
										break;
		case MACPROMISCUOUSMODE:		MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macPromiscuousMode);
										break;
		case MACRXONWHENIDLE:			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macRxOnWhenIdle);
										break;
		case MACSHORTADDRESS:			MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,(EE_UINT8 *) &mac_PIB.macShortAddress);
										break;
		case MACSUPERFRAMEORDER:		MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,&mac_PIB.macSuperframeOrder);
										break;
		case MACTRANSACTIONPERSISTENCETIME:	MLME_GET_confirm(MAC_SUCCESS,PIBAttribute,(EE_UINT8 *) &mac_PIB.macTransactionPersistenceTime);
											break;
											
		default:						MLME_GET_confirm(MAC_UNSUPPORTED_ATTRIBUTE,PIBAttribute,0x00);
										break;
	}

	return 1;
}
