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
* $Id: gts_mechanism.h,v 1.3 2008/07/04 09:47:25 chris Exp $
* $Log: gts_mechanism.h,v $
* Revision 1.3  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


#include "ee.h"

	/*************** GTS Functions Definition***************/
	void init_available_gts_index();
	void start_coordinator_gts_send();
	void start_gts_send();
	
	//GTS FUNCTIONS
	EE_UINT8 remove_gts_entry(EE_UINT16 DevAddressType);
	EE_UINT8 add_gts_entry(EE_UINT8 gts_length,EE_UINT8 direction,EE_UINT16 DevAddressType,EE_UINT16 GTS_startslotindex);
	EE_UINT8 add_gts_null_entry(EE_UINT8 gts_length,EE_UINT8 direction,EE_UINT16 DevAddressType);
	
	EE_UINT32 calculate_gts_expiration();
	//task void check_gts_expiration();
	EE_UINT8 check_gts_send_conditions(EE_UINT8 frame_length);
	
	
	//initialization functions
	void init_gts_slot_list();
	void init_GTS_null_db();
	void init_GTS_db();

