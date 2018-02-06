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
* $Id: MCPS_DATA.h,v 1.5 2008/07/04 09:47:25 chris Exp $
* $Log: MCPS_DATA.h,v $
* Revision 1.5  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/**
 * MCPS-DATA-Service Access Point
 *
 *pag 56
 */

#include "ee.h"

EE_UINT8 MCPS_DATA_request(EE_UINT8 SrcAddrMode, EE_UINT16 SrcPANId, EE_UINT32 SrcAddr[], EE_UINT8 DstAddrMode, EE_UINT16 DestPANId, EE_UINT32 DstAddr[], EE_UINT8 msduLength, EE_UINT8 msdu[],EE_UINT8 msduHandle, EE_UINT8 TxOptions);
  
EE_UINT8 MCPS_DATA_confirm(EE_UINT8 msduHandle, EE_UINT8 status);
																																								
EE_UINT8 MCPS_DATA_indication(EE_UINT16 SrcAddrMode, EE_UINT16 SrcPANId, EE_UINT32 SrcAddr[2], EE_UINT16 DstAddrMode, EE_UINT16 DestPANId, EE_UINT32 DstAddr[2], EE_UINT16 msduLength,EE_UINT8 msdu[100],EE_UINT16 mpduLinkQuality, EE_UINT16 SecurityUse, EE_UINT16 ACLEntry);  



void create_data_frame(EE_UINT8 SrcAddrMode, EE_UINT16 SrcPANId, EE_UINT32 SrcAddr[], EE_UINT8 DstAddrMode, EE_UINT16 DestPANId, EE_UINT32 DstAddr[], EE_UINT8 msduLength, EE_UINT8 msdu[],EE_UINT8 msduHandle, EE_UINT8 TxOptions,EE_INT8 on_gts_slot,EE_UINT8 pan);
