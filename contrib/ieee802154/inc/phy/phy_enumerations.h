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
* $Id: phy_enumerations.h,v 1.3 2008/07/04 09:47:25 chris Exp $
* $Log: phy_enumerations.h,v $
* Revision 1.3  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/ 
#ifndef __PHY_ENUMERATIONS__
#define __PHY_ENUMERATIONS__
 
//phy status enumerations
enum{
	PHY_BUSY = 0x00,
	PHY_BUSY_RX = 0x01,
	PHY_BUSY_TX = 0x02,
	PHY_FORCE_TRX_OFF = 0x03,
	PHY_IDLE = 0x04,
	PHY_INVALID_PARAMETER = 0x05,
	PHY_RX_ON = 0x06,
	PHY_SUCCESS = 0x07,
	PHY_TRX_OFF = 0x08,
	PHY_TX_ON = 0x09,
	PHY_UNSUPPORTED_ATTRIBUTE = 0x0a
};

//phy PIB attributes enumerations
enum{
	PHYCURRENTCHANNEL = 0x00,
	PHYCHANNELSSUPPORTED = 0X01,
	PHYTRANSMITPOWER = 0X02,
	PHYCCAMODE=0X03
};

#endif
