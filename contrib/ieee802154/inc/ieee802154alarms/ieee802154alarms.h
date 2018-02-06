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
* $Id: ieee802154alarms.h,v 1.6 2008/07/04 09:47:25 chris Exp $
* $Log: ieee802154alarms.h,v $
* Revision 1.6  2008/07/04 09:47:25  chris
* INFO: Add commented header (project description, licence, people) to files.
*
*
*************************************************************************/


/*
 * 
 * IEEE 802.15.4 Timer Events (Beacon Intervals + Before Beacon Interval, Superframe Duration, Time Slots + Before Time Slot and Backoff)
 * 
 */

#include "ee.h"

//reset the alarms to 0
void ieee802145alarms_reset(void);

//configure the alarms BI and SD
void ieee802145alarms_set_bi_sd(EE_UINT32 bi_symbols,EE_UINT32 sd_symbols);

//enable the alarms to call the MAC functions on every interrupt
void ieee802145alarms_set_timers_enable(EE_UINT8 timer);

//start the alarms interrupts
void ieee802145alarms_start();

//stop the alarms interrupts
void ieee802145alarms_stop();

//reset the timers at a specified time (used for the synchronization of the end devices
void ieee802145alarms_reset_start(EE_UINT32 start_ticks);

//enable the backoff fired (only during the CAP, there are no backoff in the GTS)
void ieee802145alarms_set_enable_backoffs(EE_UINT8 enable);

EE_UINT32 ieee802145alarms_get_sd_ticks();

EE_UINT32 ieee802145alarms_get_bi_ticks();

EE_UINT32 ieee802145alarms_get_time_slot_ticks();

EE_UINT32 ieee802145alarms_get_backoff_ticks();


