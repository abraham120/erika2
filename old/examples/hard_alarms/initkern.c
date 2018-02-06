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
 * Author: 2001-2002 Paolo Gai
 * CVS: $Id: initkern.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "ee.h"


/* ROM */
const EE_TYPEPRIO EE_th_ready_prio   [THREAD_MAX] = {0x01, 0x02};   /* task preemption level */
const EE_TYPEPRIO     EE_th_dispatch_prio[THREAD_MAX] = {0x01, 0x02};   /* task threshold */

/* RAM */
/* Note: there are no pending activations!!! */
#if defined(__MULTI__) || defined(__WITH_STATUS__)
EE_TYPESTATUS   EE_th_status       [THREAD_MAX] = {EE_READY, EE_READY};  /* status of the thread */
#endif

EE_TYPENACT     EE_th_nact       [THREAD_MAX] = {0, 0};      /* pending activations */
EE_TID          EE_th_next       [THREAD_MAX] = {EE_NIL, EE_NIL};    /* for task queues */
EE_TYPEPRIO     EE_sys_ceiling                  = 0x0000;                      /* always 0... */

/* The first task into the ready queue */
EE_TID EE_rqfirst  = EE_NIL;

/* The first stacked task */
EE_TID EE_stkfirst = EE_NIL;


/* alarms related data structures */

/* Alarms */

#include "hard_alarms/hard_alarms.h"

EE_counter_RAM_type       EE_counter_RAM[] = { -1, -1};

void mycallback(void);

const EE_alarm_ROM_type   EE_alarm_ROM[] = 
{
  {0, EE_ALARM_ACTION_TASK    , 1, NULL },
  {0, EE_ALARM_ACTION_CALLBACK, 0, (EE_ADDR)mycallback},
  {1, EE_ALARM_ACTION_CALLBACK, 0, (EE_ADDR)mycallback} //note: counter 1
};

EE_alarm_RAM_type         EE_alarm_RAM[3];
