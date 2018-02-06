/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2002 Paolo Gai
 * CVS: $Id: initkern.c,v 1.1 2005/07/17 13:10:52 pj Exp $
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

EE_TYPEAPPMODE EE_ApplicationMode;

/* thread status */
EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = 
  {SUSPENDED, SUSPENDED, SUSPENDED, SUSPENDED};

/* next: is used for the stacked queue and for WaitEvent */
EE_TID   EE_th_next[EE_MAX_TASK] =
  {EE_NIL, EE_NIL, EE_NIL, EE_NIL};     /* remaining nact */

/* priorities */
const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] =
  {0x01, 0x02, 0x04, 0x08};
const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] =
  {0x01, 0x02, 0x04, 0x08};

#ifndef __OO_NO_CHAINTASK__
/* The next task to be activated after a ChainTask */
EE_TID EE_th_terminate_nextask[EE_MAX_TASK] = 
  {EE_NIL,EE_NIL,EE_NIL,EE_NIL};
#endif


/* The first stacked task */
EE_TID EE_stkfirst = EE_NIL;

/* System ceiling */
EE_TYPEPRIO EE_sys_ceiling = 0;


#if defined(__OO_BCC1__) || defined(__OO_ECC1__)

EE_TID EE_rq_first = EE_NIL;

/* remaining nact: init= maximum pending activations of a Task */
/* MUST BE 1 for BCC1 and ECC1 */
EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] = {1, 1, 1, 1};

#endif




#if defined(__OO_BCC2__) || defined(__OO_ECC2__)

#if defined(__OO_BCC2__)
EE_UINT8  EE_rq_bitmask = 0;
#else
EE_UINT16 EE_rq_bitmask = 0;
#endif

/* remaining nact: init= maximum pending activations of a Task */
EE_TYPENACT   EE_th_rnact[EE_MAX_TASK] =
  {1, 3, 1, 1};

EE_TYPEPRIO EE_rq_link[EE_MAX_TASK] = {0, 1, 2, 3};

/* The priority queues */
#if defined(__OO_BCC2__)
/* BCC2: 8 priorities */
EE_TYPEPAIR EE_rq_queues_head[] =
 {-1, -1, -1, -1, -1, -1, -1, -1};
EE_TYPEPAIR EE_rq_queues_tail[] =
 {-1, -1, -1, -1, -1, -1, -1, -1};
#else
/* ECC2: 16 priorities */
EE_TYPEPAIR EE_rq_queues_head[] =
 {-1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1};
EE_TYPEPAIR EE_rq_queues_tail[] =
 {-1, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, -1, -1, -1};
#endif

/* The pairs that are enqueued into the priority queues (5 is the
   total number of task activations) */
EE_TYPEPAIR EE_rq_pairs_next[] =
  {1, 2, 3, 4, 5, -1};

/* no need to be initialized */
EE_TID EE_rq_pairs_tid[6];

/* a list of unused pairs */
EE_TYPEPAIR EE_rq_free = 0; /* pointer to a free pair */

#endif



/* Event handling */
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
EE_TYPEEVENTMASK EE_th_event_active[EE_MAX_TASK] =
  {0,0,0,0};      /* thread event already active */
EE_TYPEEVENTMASK EE_th_event_waitmask[EE_MAX_TASK] =
  {0,0,0,0};    /* thread wait mask */

EE_TYPEBOOL EE_th_waswaiting[EE_MAX_TASK] =
  {0,0,0,0};

EE_TYPEBOOL EE_th_is_extended[EE_MAX_TASK] =
  {0,0,1,0};

#endif




/* No Resource data structures !!! */

/* Alarms */
const EE_oo_counter_ROM_type EE_counter_ROM[] = 
  {/* counter 1 */ {0xFFFFFFFF, 1, 1},
   /* counter 2 */ {0xFFFFFFFF, 1, 1} };

EE_oo_counter_RAM_type       EE_counter_RAM[] = 
  {/* counter 1 */ {0, -1},
   /* counter 2 */ {0, -1}};

void mycallback(void);
void mycallback2(void);

/* Note: the number of fields of this structure changes and depends on the kernel configuration! */
#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
const EE_oo_alarm_ROM_type   EE_alarm_ROM[] = 
{
  {0, EE_ALARM_ACTION_TASK    , 1, 0, NULL },
  {0, EE_ALARM_ACTION_CALLBACK, 0, 0, (EE_ADDR)mycallback},
  {1, EE_ALARM_ACTION_EVENT   , 2, myevent, NULL} 
};
#else
const EE_oo_alarm_ROM_type   EE_alarm_ROM[] = 
{
  {0, EE_ALARM_ACTION_TASK    , 1, NULL },
  {0, EE_ALARM_ACTION_CALLBACK, 0, (EE_ADDR)mycallback},
  {1, EE_ALARM_ACTION_CALLBACK, 0, (EE_ADDR)mycallback2}
};
#endif

EE_oo_alarm_RAM_type         EE_alarm_RAM[3];
