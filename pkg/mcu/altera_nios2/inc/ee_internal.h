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
 * Author: 2006 Paolo Gai
 * CVS: $Id: ee_internal.h,v 1.2 2008/07/21 16:46:40 francesco Exp $
 */

#include "mcu/altera_nios2/inc/ee_mcu.h"

#ifndef __INCLUDE_NIOSII_INTERNAL_H__
#define __INCLUDE_NIOSII_INTERNAL_H__

#include "altera_avalon_timer_regs.h"
#include "system.h"

/*************************************************************************
 Timers
 *************************************************************************/

/* In case of single IRQ mode, we remap the budget timer over the COMMON IRQ */
#if defined(__FRSH_SINGLEIRQ__)  || defined(__HR_SINGLEIRQ__)
#define TIMER_CAPACITY_BASE TIMER_COMMON_BASE
#define TIMER_CAPACITY_IRQ  TIMER_COMMON_IRQ
#endif


#if defined(__FRSH__)  || defined(__HR__)

void EE_hal_set_nios2_timer(EE_UINT32 base, EE_STIME t);
void EE_hal_stop_nios2_timer(EE_UINT32 base);

/* 
   This function set the capacity timer to raise in t ticks.
   
   The capacity interrupt is then programmed simply setting
   the delay into the timer1 counter. That is, whenever the timer
   fires, it restart counting down from 0xffffffff, and it will take a
   few seconds to do that.

   if t < 0, the timer is stopped.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_budget_timer(EE_STIME t) 
{
  EE_hal_set_nios2_timer(TIMER_CAPACITY_BASE,t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_budget_timer(void)
{
  EE_hal_stop_nios2_timer(TIMER_CAPACITY_BASE);
}

#endif

#if ( defined(__FRSH__) || defined(__HR__) ) && (!defined(__FRSH_SINGLEIRQ__) || !defined(__HR_SINGLEIRQ__))

// these are available only when SINGLEIRQ is not defined.

__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_recharging_timer(EE_STIME t)
{
  EE_hal_set_nios2_timer(TIMER_RECHARGING_BASE,t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_recharging_timer(void)
{
  EE_hal_stop_nios2_timer(TIMER_RECHARGING_BASE);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_dline_timer(EE_STIME t)
{
  EE_hal_set_nios2_timer(TIMER_DLCHECK_BASE,t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_dline_timer(void)
{
  EE_hal_stop_nios2_timer(TIMER_DLCHECK_BASE);
}
#endif

#if defined(__FRSH__) && !defined(__FRSH_SINGLEIRQ__)

__INLINE__ void __ALWAYS_INLINE__ EE_hal_set_synchobj_timeout_timer(EE_STIME t)
{
  EE_hal_set_nios2_timer(TIMER_SYNCHOBJ_BASE,t);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_synchobj_timeout_timer(void)
{
  EE_hal_stop_nios2_timer(TIMER_SYNCHOBJ_BASE);
}

#endif

#endif
