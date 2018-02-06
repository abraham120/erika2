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
 * Edited to support HR kernel by Alessandro Biondi (2013)
 * CVS: $Id: ee_mcu.h,v 1.2 2008/07/24 14:26:55 francesco Exp $
 */

#include "altera_avalon_timer_regs.h"
#include "system.h"
#include "ee_internal.h"

#if defined(__FRSH__) || defined(__HR__)

#if defined(__FRSH__)
	#define EE__IRQ_budget EE_frsh_IRQ_budget
	#define EE__IRQ_timer_multiplexer EE_frsh_IRQ_timer_multiplexer
	#define EE__IRQ_recharging EE_frsh_IRQ_recharging
	#define EE__IRQ_dlcheck EE_frsh_IRQ_dlcheck
	#define EE__set_dline_timer EE_frsh_set_dline_timer
#endif

#if defined(__HR__)
	#define EE__IRQ_budget EE_hr_IRQ_budget
	#define EE__IRQ_timer_multiplexer EE_hr_IRQ_timer_multiplexer
	#define EE__IRQ_recharging EE_hr_IRQ_recharging
	#define EE__IRQ_dlcheck EE_hr_IRQ_dlcheck
	#define EE__set_dline_timer EE_hr_set_dline_timer
#endif



#ifndef __PRIVATE_IRQ_SYNCHOBJ_TIMEOUT__
void EE_frsh_IRQ_synchobj_timeout(void);
#endif


#ifndef __PRIVATE_TIME_INIT__
void EE_time_init(void)
{
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_SYSTEM_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_SYSTEM_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_SYSTEM_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);
}

#endif

#ifndef __PRIVATE_HAL_GETTIME__
EE_TIME EE_hal_gettime(void)
{
  union {
    struct { EE_UINT16 low, hi; } lowhi;
    EE_TIME time;
  } retvalue;
  IOWR(TIMER_SYSTEM_BASE, ALTERA_AVALON_TIMER_SNAPH_REG, 0xFFFF);

  retvalue.lowhi.low = IORD_ALTERA_AVALON_TIMER_SNAPL(TIMER_SYSTEM_BASE);
  retvalue.lowhi.hi = IORD_ALTERA_AVALON_TIMER_SNAPH(TIMER_SYSTEM_BASE);
  retvalue.time = 0xFFFFFFFF - retvalue.time;
  
  return retvalue.time;
}
#endif

#ifndef __PRIVATE_NIOS2_IRQ_BUDGET__
void EE_nios2_IRQ_budget(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_CAPACITY_BASE, 0);

#if !defined(__FRSH_SINGLEIRQ__) || !defined(__HR_SINGLEIRQ__)
  EE__IRQ_budget();
#else
  EE__IRQ_timer_multiplexer();
#endif
}
#endif


#if !defined(__FRSH_SINGLEIRQ__) || !defined(__HR_SINGLEIRQ__)
// the other three IRQ sources are available only when 4 timers are available

#ifndef __PRIVATE_NIOS2_IRQ_RECHARGING__
void EE_nios2_IRQ_recharging(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_RECHARGING_BASE, 0);

  EE__IRQ_recharging();
}
#endif


#ifndef __PRIVATE_NIOS2_IRQ_RECHARGING__
void EE_nios2_IRQ_dlcheck(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_DLCHECK_BASE, 0);

  EE__IRQ_dlcheck();
}
#endif

#ifdef __FRSH_SYNCHOBJ__
#ifndef __PRIVATE_NIOS2_IRQ_SYNCHOBJ__
void EE_nios2_IRQ_synchobj_timeout(void* context, alt_u32 id)
{
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (TIMER_SYNCHOBJ_BASE, 0);

  EE_frsh_IRQ_synchobj_timeout();
}
#endif
#endif


#endif

/* This function is used to initialize the two timers used for 
 * budget exaustion and for the recharging queue
 */
 
#if !defined(__PRIVATE_HR_TIME_INIT__) || !defined(__PRIVATE_HR_TIME_INIT__)
 
#if defined(__FRSH__)
void EE_frsh_time_init(void)
#endif

#if defined(__HR__) 
void EE_hr_time_init(void)
#endif
{
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_CAPACITY_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_CAPACITY_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_CAPACITY_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  alt_irq_register (TIMER_CAPACITY_IRQ, NULL, EE_nios2_IRQ_budget);    

#if !defined(__FRSH_SINGLEIRQ__) || !defined(__HR_SINGLEIRQ__)
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_RECHARGING_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_RECHARGING_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_RECHARGING_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  alt_irq_register (TIMER_RECHARGING_IRQ, NULL, EE_nios2_IRQ_recharging);    

  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_DLCHECK_BASE, 0x3FFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_DLCHECK_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_DLCHECK_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);

  alt_irq_register (TIMER_DLCHECK_IRQ, NULL, EE_nios2_IRQ_dlcheck);  

#ifdef __FRSH_SYNCHOBJ__
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_SYNCHOBJ_BASE, 0x3FFF);
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_SYNCHOBJ_BASE, 0xFFFF);
  IOWR_ALTERA_AVALON_TIMER_CONTROL (TIMER_SYNCHOBJ_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  alt_irq_register (TIMER_SYNCHOBJ_IRQ, NULL, EE_nios2_IRQ_synchobj_timeout);  
#endif

  EE_hal_set_nios2_timer(TIMER_DLCHECK_BASE, 0xffff);  
#else
  // only a single timer available. Program the deadline timer...
  EE__set_dline_timer(0xffff);
#endif
}
#endif


/* note: if the timing is negative, the timer is stopped */
#ifndef __PRIVATE_SET_NIOS2_TIMER__
void EE_hal_set_nios2_timer(EE_UINT32 base, EE_STIME t) 
{
  union {
    struct { EE_UINT16 low, hi; } lowhi;
    EE_TIME time;
  } retvalue;


  /* stop the timer */
  IOWR_ALTERA_AVALON_TIMER_CONTROL (base, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);

  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (base, 0); 

  if (t>0) {
    /* set the next period */
    retvalue.time = t;
    IOWR_ALTERA_AVALON_TIMER_PERIODH(base, (retvalue.lowhi.hi));
    IOWR_ALTERA_AVALON_TIMER_PERIODL(base, (retvalue.lowhi.low));
    
    /* restart the timer */
    IOWR_ALTERA_AVALON_TIMER_CONTROL (base, 
				      ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
				      ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
				      ALTERA_AVALON_TIMER_CONTROL_START_MSK);
  }
} 
#endif

#ifndef __PRIVATE_STOP_NIOS2_TIMER__
void EE_hal_stop_nios2_timer(EE_UINT32 base)
{
  IOWR_ALTERA_AVALON_TIMER_CONTROL (base, 
            ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (base, 0); 
}
#endif

#endif
