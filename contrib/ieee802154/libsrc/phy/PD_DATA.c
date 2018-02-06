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
* $Id: PD_DATA.c,v 1.6 2008/07/04 09:47:25 chris Exp $
* $Log: PD_DATA.c,v $
* Revision 1.6  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * PD-Service Access Point //interface PD_DATA
 *
 *
 */
#include "ee.h"
#include "phy/PD_DATA.h"

#include "hal/hal_cc2420.h"

extern EE_UINT8 csma_slotted;

EE_UINT8 PD_DATA_request(EE_UINT8 psduLenght, EE_UINT8* psdu)
{
	//TODO
	//Send data pointed by psdu
	/*if (csma_slotted)
	{
		store_msg(psduLenght, (EE_UINT8 *) psdu);
	}
	else
	{
		//store_msg(psduLenght, (EE_UINT8 *) psdu);
		store_msg_cca(psduLenght, (EE_UINT8 *) psdu);
	}*/
	store_msg(psduLenght, (EE_UINT8 *) psdu);
return 1;
}

