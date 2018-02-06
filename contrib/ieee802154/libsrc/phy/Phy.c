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
* $Id: Phy.c,v 1.5 2008/07/04 09:47:25 chris Exp $
* $Log: Phy.c,v $
* Revision 1.5  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/*
 * 
 * Physical Layer Main Implementation file
 * 
 * 
 */

#include "ee.h"
#include "phy/phy.h"
#include "phy/phy_const.h"
#include "phy/phy_enumerations.h"

#include "hal/hal_interrupts.h"

phyPIB phy_PIB = {INIT_CURRENTCHANNEL,INIT_CHANNELSSUPPORTED,INIT_TRANSMITPOWER,INIT_CCA_MODE};

EE_UINT8 currentTxRxState = PHY_IDLE;


void init_phy()
{
	//initialization of the phy_PIB
	phy_PIB.phyCurrentChannel=INIT_CURRENTCHANNEL;
	phy_PIB.phyChannelsSupported=INIT_CHANNELSSUPPORTED;
	phy_PIB.phyTransmitPower=INIT_TRANSMITPOWER;
	phy_PIB.phyCcaMode=INIT_CCA_MODE;
	
	
	//initialization of the CC2420 registers and setting up the default values of the phy_PIB
	
	/* Program Timer 2 to raise interrupts */
	T2_program();
	
	
	hardware_init();
	
	
return;
}







