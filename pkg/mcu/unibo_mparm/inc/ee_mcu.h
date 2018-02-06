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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: ee_mcu.h,v 1.6 2006/08/13 17:20:24 pj Exp $
 */

#include "mcu/unibo_mparm/inc/ee_mcuregs.h"

#ifndef __INCLUDE_UNIBO_MPARM_MCU_H__
#define __INCLUDE_UNIBO_MPARM_MCU_H__

/*************************************************************************
 Timers
 *************************************************************************/

#ifdef __TIMER_0_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_start(void) 
//{ *TMOD |= (1<<0); }	// modified by Francesco Esposito
{*((volatile unsigned int *)SWARM_TIMER_INTEN) |= 0x1;}	// modified by Francesco Esposito
__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_stop(void)  
//{ *TMOD &= ~(1<<0); }	// modified by Francesco Esposito
{*((volatile unsigned int *)SWARM_TIMER_INTEN) &= ~(0x1);}	// modified by Francesco Esposito
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_0_get(void) { return *SWARM_TIMER_CNT; }
__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_set(EE_UREG count_down) 
//{ *TDATA0 = count_down; } // modified by Francesco Esposito
{*((volatile unsigned int *)SWARM_TIMER_MATCH0) = *((volatile unsigned int *)SWARM_TIMER_CNT) + count_down;}	// modified by Francesco Esposito

#endif /* __TIMER_0_USED__ */


#ifdef __TIMER_1_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_start(void) 
//{ *TMOD |= (1<<(0+3)); }	// modified by Francesco Esposito
{*((volatile unsigned int *)SWARM_TIMER_INTEN) |= 0x2;}	// modified by Francesco Esposito
__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_stop(void) 
//{*TMOD &= ~(1<<(0+3)); }	// modified by Francesco Esposito
{*((volatile unsigned int *)SWARM_TIMER_INTEN) &= ~(0x2);}	// modified by Francesco Esposito
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_1_get(void) { return *SWARM_TIMER_CNT; }
__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_set(EE_UREG count_down)
//{ *TDATA1 = count_down; }	// modified by Francesco Esposito
{*((volatile unsigned int *)SWARM_TIMER_MATCH1) = *((volatile unsigned int *)SWARM_TIMER_CNT) + count_down;}	// modified by Francesco Esposito

#endif /* __TIMER_1_USED__ */


#ifdef __TIMER_2_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

__INLINE__ void __ALWAYS_INLINE__ EE_timer_2_start(void) 
{*((volatile unsigned int *)SWARM_TIMER_INTEN) |= 0x4;}	// modified by Francesco Esposito
__INLINE__ void __ALWAYS_INLINE__ EE_timer_2_stop(void) 
{*((volatile unsigned int *)SWARM_TIMER_INTEN) &= ~(0x4);}	// modified by Francesco Esposito
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_2_get(void) { return *SWARM_TIMER_CNT; }
__INLINE__ void __ALWAYS_INLINE__ EE_timer_2_set(EE_UREG count_down)
{*((volatile unsigned int *)SWARM_TIMER_MATCH2) = *((volatile unsigned int *)SWARM_TIMER_CNT) + count_down;}	// modified by Francesco Esposito

#endif /* __TIMER_2_USED__ */


#ifdef __TIMER_3_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

__INLINE__ void __ALWAYS_INLINE__ EE_timer_3_start(void) 
{*((volatile unsigned int *)SWARM_TIMER_INTEN) |= 0x8;}	// modified by Francesco Esposito
__INLINE__ void __ALWAYS_INLINE__ EE_timer_3_stop(void) 
{*((volatile unsigned int *)SWARM_TIMER_INTEN) &= ~(0x8);}	// modified by Francesco Esposito
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_3_get(void) { return *SWARM_TIMER_CNT; }
__INLINE__ void __ALWAYS_INLINE__ EE_timer_3_set(EE_UREG count_down)
{*((volatile unsigned int *)SWARM_TIMER_MATCH3) = *((volatile unsigned int *)SWARM_TIMER_CNT) + count_down;}	// modified by Francesco Esposito

#endif /* __TIMER_3_USED__ */


#ifdef __TIMER_USED__
__INLINE__ void __ALWAYS_INLINE__ EE_timer_init(void)
{
    /* disable timer */
    //*TMOD = 0;
	*SWARM_TIMER_INTEN = 0x0;	// modified by Francesco Esposito
}
#endif /* __TIMER_USED__ */


/*
 * Timer
 */

#ifdef __TIME_SUPPORT__
/* Timer size */
typedef EE_UINT32 EE_TIME;

/* read current time (used by EDF scheduler) */
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
    return 0xffffffff - EE_timer_0_get();
}
#endif





#endif
