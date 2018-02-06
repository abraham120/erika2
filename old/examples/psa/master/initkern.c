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
 * Author: 2003 Francesco Bertozzi
 * CVS: $Id: initkern.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */
 
#include "ee.h"
#include "com/com.h"

// ROM kernel descriptors
const EE_TYPEPRIO EE_th_ready_prio[THREAD_MAX] = { 0x02, 0x02 };
const EE_TYPEPRIO EE_th_dispatch_prio[THREAD_MAX] = { 0x02, 0x02 };

// RAM kernel descriptors
EE_TYPENACT EE_th_nact[THREAD_MAX] = { 0, 0 };
EE_TID EE_th_next[THREAD_MAX] = { EE_NIL, EE_NIL };

EE_TYPEPRIO EE_sys_ceiling = 0; // the ceiling of the first task

EE_TID EE_rqfirst  = EE_NIL;
EE_TID EE_stkfirst = EE_NIL;

// ROM
const EE_TYPEPRIO EE_mutex_ceiling[2] = { 0x02, 0x02 };

// RAM
EE_TYPEPRIO EE_mutex_oldceiling[2];

/* Alarms related data structures */
#include "alarms/alarms.h"

EE_counter_RAM_type       EE_counter_RAM[] = 
{ 
  {0, -1}
};

const EE_alarm_ROM_type   EE_alarm_ROM[] = 
{
  {0, EE_ALARM_ACTION_CALLBACK, 0, EE_PSA_DISPATCHER},
};

EE_alarm_RAM_type         EE_alarm_RAM[1];

