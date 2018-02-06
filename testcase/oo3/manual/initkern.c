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
 * Author 2002 Paolo Gai
 * CVS: $Id: initkern.c,v 1.2 2005/07/17 13:26:25 pj Exp $
 */

#include "ee.h"

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
  {1, 1, 1, 1};

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
  {1, 2, 3, -1};

/* no need to be initialized */
EE_TID EE_rq_pairs_tid[4];

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
  {0,0,0,0};

#endif




/* Resources data structures */
const EE_TYPEPRIO   EE_resource_ceiling[EE_MAX_RESOURCE] = { 0x08, 0x04 };
EE_TYPEPRIO   EE_resource_oldceiling[EE_MAX_RESOURCE];

#ifdef __OO_EXTENDED_STATUS__ 
/* This is the last resource that the task has locked. This array
   contains one entry for each task.  Initvalue= all -1. at runtime,
   it points to the first item in the EE_resource_stack data structure */
EE_UREG EE_th_resource_last[EE_MAX_TASK] = {-1, -1, -1, -1};
/* this array is used to store a list of resources locked by a
   task. there is one entry for each resource, initvalue = -1. the
   list of resources locked by a task is ended by -1. */
EE_UREG EE_resource_stack[EE_MAX_RESOURCE] = {-1, -1};

/* Only in extended status; for each resource, a flag is allocated to
   see if the resource is locked or not.  Note that this information
   cannot be easily knew from the previous two data structures. initvalue=0
*/
EE_TYPEBOOL EE_resource_locked[EE_MAX_RESOURCE] = {0, 0};
#endif
