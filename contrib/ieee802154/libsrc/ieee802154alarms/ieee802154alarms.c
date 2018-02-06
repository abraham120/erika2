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
* $Id: ieee802154alarms.c,v 1.20 2008/07/30 16:44:59 chris Exp $
* $Log: ieee802154alarms.c,v $
* Revision 1.20  2008/07/30 16:44:59  chris
* Clean comments and commented code
*
* Revision 1.19  2008/07/16 09:04:03  chris
* BUG-FIX: use sd_fired_alarms in a non-periodic way, set it as timeout at the beginning of the beacon interval; Change GTS allocation
*
* Revision 1.18  2008/07/14 10:48:34  chris
* Adapting to the new common files moved into the ieee802154 library tree
*
* Revision 1.17  2008/07/11 14:58:47  chris
* BUG-FIX: correct the sd_tick calculation for SO=BO
*
* Revision 1.16  2008/07/04 09:47:25  chris
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

#include "ieee802154alarms/ieee802154alarms.h"

#include "mac/Mac.h"

#include "common/console.h"

#define BACKOFF_SYMBOLS 20

//offset when the sd_fired fires at the same time as the bi_fired
//not to have the sd_fired before the bi_fired
#define SO_EQUAL_BO_DIFFERENCE 1

#define BEFORE_BI_INTERVAL 5
#define BEFORE_TS_INTERVAL 5

#define NUMBER_TIME_SLOTS 16

//BEACON INTERVAL VARIABLES
EE_UINT32 bi_ticks;
//EE_UINT32 bi_backoff_periods;
EE_UINT32 before_bi_ticks;

//SUPERFRAME DURATION
EE_UINT32 sd_ticks;

//number of elapsed backoffs in the superframe
EE_UINT32 backoff_ticks_count;

//number of ticks in the timeslot
EE_UINT32 time_slot_ticks;
EE_UINT32 before_time_slot_ticks;

//boolean variable enabling the backoff fired event during the CAP
EE_UINT8 backoff_enable=1;
//boolean variable enabling the timers calling the MAC functions
EE_UINT8 timers_enable=1;

extern EE_UINT8 current_time_slot;

//reset the alarms to 0
void ieee802145alarms_reset(void)
{
	
return;
}

//configure the alarms BI and SD
void ieee802145alarms_set_bi_sd(EE_UINT32 bi_symbols, EE_UINT32 sd_symbols)
{
	/* Calculate durations */	
	bi_ticks = bi_symbols / (EE_UINT32)BACKOFF_SYMBOLS;		/* Duration in CouterTicks of the Beacon Interval */ 
	sd_ticks = sd_symbols / (EE_UINT32)BACKOFF_SYMBOLS;		/* Duration in CouterTicks of the Superframe */ 

	time_slot_ticks = sd_ticks / (EE_UINT32)NUMBER_TIME_SLOTS; 	/* Duration in CouterTicks of 1 Time Slot */ 

	/* Set the 'before' timer ticks */
	before_bi_ticks = bi_ticks - (EE_UINT32)BEFORE_BI_INTERVAL;			
	before_time_slot_ticks = time_slot_ticks - (EE_UINT32)BEFORE_TS_INTERVAL;


	/* If full duty cycle (NO inactive period!) -> 'sd_ticks == bi_ticks' -> force 'sd_ticks < bi_ticks' */	
	if (bi_symbols == sd_symbols ) 
		sd_ticks = sd_ticks - (EE_UINT32)SO_EQUAL_BO_DIFFERENCE;
	return;
}

//enable the alarms to call the MAC functions on every interrupt
void ieee802145alarms_set_timers_enable(EE_UINT8 timer)
{
	timers_enable = timer;
return;
}
//start the alarms interrupts
void ieee802145alarms_start()
{
	//ee_console_out_str("alarms_start");
	SetRelAlarm(bi_firedAlarm, bi_ticks, bi_ticks);
	// SetRelAlarm(sd_firedAlarm, sd_ticks, sd_ticks);  // chris: TODO: check!!
	SetRelAlarm(time_slot_firedAlarm, time_slot_ticks, time_slot_ticks);
	SetRelAlarm(backoff_firedAlarm, 1, 1);
	
	backoff_ticks_count=0;

return;
}
//stop the alarms interrupts
void ieee802145alarms_stop()
{

return;
}
//reset the timers at a specified time (used for the synchronization of the end devices
void ieee802145alarms_reset_start(EE_UINT32 start_ticks)
{
	//ee_console_out_str("reset_start");
	CancelAlarm(bi_firedAlarm);
	CancelAlarm(sd_firedAlarm);
	CancelAlarm(time_slot_firedAlarm);
	CancelAlarm(backoff_firedAlarm);	
	
	backoff_ticks_count = start_ticks;
	current_time_slot=0;
	
	SetRelAlarm(bi_firedAlarm, bi_ticks - start_ticks, bi_ticks - start_ticks);
	//SetRelAlarm(sd_firedAlarm, sd_ticks - start_ticks, sd_ticks - start_ticks);	// chris: TODO: check!!
	SetRelAlarm(time_slot_firedAlarm, time_slot_ticks - start_ticks, time_slot_ticks - start_ticks);
	SetRelAlarm(backoff_firedAlarm, 1, 1);
	
	//SetRelAlarm(PacketsGeneratorAlarm, 1000,1000);

return;
}
//enable the backoff fired (only during the CAP, there are no backoff in the GTS)
void ieee802145alarms_set_enable_backoffs(EE_UINT8 enable)
{
	backoff_enable = enable;
return;
}


//get functions
EE_UINT32 ieee802145alarms_get_sd_ticks()
{
	return sd_ticks;
}

EE_UINT32 ieee802145alarms_get_bi_ticks()
{
	return bi_ticks;	
}

EE_UINT32 ieee802145alarms_get_time_slot_ticks()
{
	return time_slot_ticks;
}

EE_UINT32 ieee802145alarms_get_backoff_ticks()
{
	return backoff_ticks_count;
}





//TASK definitions

TASK(bi_firedTask)
{
	backoff_ticks_count=0;
	bi_fired();
}

TASK(before_bi_firedTask)
{
	before_bi_fired();
}

TASK(sd_firedTask)
{
	sd_fired();
}

TASK(time_slot_firedTask)
{
	time_slot_fired();
}

TASK(before_time_slot_firedTask)
{
	before_time_slot_fired();
}

TASK(backoff_firedTask)
{
	backoff_ticks_count ++;
	backoff_fired();
}
