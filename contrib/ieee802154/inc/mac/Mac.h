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
* $Id: Mac.h,v 1.13 2008/07/04 09:47:25 chris Exp $
* $Log: Mac.h,v $
* Revision 1.13  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/

/*
 * MAC Layer HEADER FILE
 * 
 */

#include "ee.h"

#include "mac/MLME_GET.h"
#include "mac/MLME_SET.h"
#include "mac/MLME_START.h"
#include "mac/MLME_ASSOCIATE.h"
#include "mac/MLME_BEACON_NOTIFY.h"

#include "mac/MCPS_DATA.h"


void init_mac();

void create_beacon();
/*function to process the beacon information*/
void process_beacon(EE_UINT8 ppduLinkQuality);

void process_data();
void process_cmd();
void process_ack();


void send_frame_csma();

//timer functions declaration
void bi_fired();

void before_bi_fired();

void sd_fired();

void time_slot_fired();

void before_time_slot_fired();

void backoff_fired();

void send_gts_after_interframearrival();


