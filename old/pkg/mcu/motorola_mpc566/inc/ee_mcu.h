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
 * Author: Antonio Fiaschi
 * CVS: $Id: ee_mcu.h,v 1.2 2006/04/08 21:10:43 pj Exp $
 */

#include "mcu/motorola_mpc566/inc/ee_micro.h"

#ifndef __INCLUDE_MPC566EVB_DRIVERS_H__
#define __INCLUDE_MPC566EVB_DRIVERS_H__

#ifndef INTERNAL_MEMORY_BASE
#define INTERNAL_MEMORY_BASE 0x00000000
#endif

#define USIU     (*( struct USIU_tag *)    (INTERNAL_MEMORY_BASE + 0x2FC000))
#define UIMB     (*( struct UIMB_tag *)    (INTERNAL_MEMORY_BASE + 0x307F80))

#define UNLOCK_REG 0x55CCAA33
#define LOCK_REG 0xFFFFFFFF



/*************************************************************************
 Initializing System
 *************************************************************************/

__INLINE__ void __ALWAYS_INLINE__ EE_init_mpc5xx(){
#ifndef __LAUTERBACH_SIM__
	USIU.SYPCR.R = 0xFFFFFF03;	// Disable watchdog timer
	USIU.PLPRCR.B.MF = 0x00D;	// Run at 56 MHz
	while(USIU.PLPRCR.B.SPLS == 0);	// Wait for PLL to lock
	UIMB.UMCR.B.HSPEED = 0;		// Run IMB at full clock speed
#ifdef __ENHANCED_IRQ__
	USIU.SIUMCR.B.EICEN = 1;	// Enhanced Interrupt Controller enable
	USIU.SIUMCR.B.LPMASK_EN = 1;	// Low Pririty Masking enable
#endif
#endif
}

/*************************************************************************
 Interrupts handling
 *************************************************************************/

/* parameters are a bit mask obtained using IRQ_*_MASK */
__INLINE__ void __ALWAYS_INLINE__ EE_enable_external_IRQ(EE_TYPEIRQ i)
{ 
#ifndef __ENHANCED_IRQ__
	USIU.SIMASK.R |= (i);
#else
	if ( (i & DISCR) == 0 ) USIU.SIMASK2.R |= (i);
	else USIU.SIMASK3.R |= (i);
#endif
}

__INLINE__ void __ALWAYS_INLINE__ EE_disable_external_IRQ(EE_TYPEIRQ i)
{ 
#ifndef __ENHANCED_IRQ__
	USIU.SIMASK.R &= ~(i); 
#else
	if ( (i & DISCR) == 0 ) USIU.SIMASK2.R &= ~(i);
	else USIU.SIMASK3.R &= ~(i); 
#endif
}

__INLINE__ void __ALWAYS_INLINE__ EE_clear_pending_IRQ(void)
{ 
#ifndef __ENHANCED_IRQ__
	USIU.SIPEND.R = 0x00000000;
#else
	USIU.SIPEND2.R = 0x00000000;
	USIU.SIPEND3.R = 0x00000000;
#endif
}

/*************************************************************************
 Programmable Interrupt Timer
 *************************************************************************/

#ifdef __PIT_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

extern EE_ADDR EE_pit_handler_addr;
__INLINE__ void __ALWAYS_INLINE__ EE_pit_start(void) { USIU.PISCR.B.PTE = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_pit_stop(void)  { USIU.PISCR.B.PTE = 0; }
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_pit_get(void) { return USIU.PITR.B.PIT; }
__INLINE__ void __ALWAYS_INLINE__ EE_pit_set(EE_UREG count_down) { USIU.PITC.B.PITC = count_down; }

__INLINE__ void __ALWAYS_INLINE__ EE_pit_enable(void) { USIU.PISCR.B.PIE = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_pit_disable(void) { USIU.PISCR.B.PIE = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_pit_set_IRQlevel(EE_TYPEIRQ l) { USIU.PISCR.B.PIRQ = l;}

__INLINE__ void __ALWAYS_INLINE__ EE_pit_freeze(void) { USIU.PISCR.B.PITF = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_pit_resume(void) { USIU.PISCR.B.PITF = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_pit_exception_reset(void) { USIU.PISCR.B.PS = 0; }

#endif /* __PIT_USED__ */

/*************************************************************************
 Real Time Clock
 *************************************************************************/

#ifdef __RT_CLOCK_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

extern EE_ADDR EE_rt_clock_handler_addr;

__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_start(void) { USIU.RTCSC.B.RTE = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_stop(void)  { USIU.RTCSC.B.RTE = 0; }
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_rt_clock_get(void) { return USIU.RTC.R; }
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_alarm_set(EE_UREG alarm) { USIU.RTCAL.R = alarm; }
    
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_reset(void) { USIU.RTC.R = 0; }
                                                                            
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_alarm_enable(void) { USIU.RTCSC.B.ALE = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_alarm_disable(void) { USIU.RTCSC.B.ALE = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_sec_enable(void) { USIU.RTCSC.B.SIE = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_sec_disable(void) { USIU.RTCSC.B.SIE = 0; }
                                                                                
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_set_IRQlevel(EE_TYPEIRQ l) { USIU.RTCSC.B.RTCIRQ = l;}
                                                                                
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_freeze(void) { USIU.RTCSC.B.RTF = 1; }
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_resume(void) { USIU.RTCSC.B.RTF = 0; }

__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_set_source(EE_UINT32 clk) { /*clk==4 ? USIU.RTCSC.B.M=1 : USIU.RTCSC.B.M=0;*/ }

__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_alarm_exception_reset(void) { USIU.RTCSC.B.ALR = 0; }
         
#endif /* __RT_CLOCK_USED__ */


#ifdef __TIMER_USED__
#ifdef __PIT_USED__
__INLINE__ void __ALWAYS_INLINE__ EE_timer_init(EE_TYPEIRQ level)
{
    /* disable timer */
	USIU.PISCR.B.PIE = 0;
	USIU.PISCR.B.PIRQ = level;
}
#endif
#ifdef __RT_CLOCK_USED__
__INLINE__ void __ALWAYS_INLINE__ EE_rt_clock_init(EE_UINT32 clk, EE_TYPEIRQ level)
{
	//Unlocking registers
	USIU.RTCSCK.R = UNLOCK_REG;
	USIU.RTCK.R = UNLOCK_REG;
	USIU.RTCALK.R = UNLOCK_REG;

	USIU.RTCSC.B.RTE = 0;
	/*clk==4 ? USIU.RTCSC.B.M=1 : USIU.RTCSC.B.M=0;*/
	USIU.RTCSC.B.RTCIRQ = level;
}
#endif
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
    return EE_rt_clock_get();
}
#endif



#endif /* __INCLUDE_MPC566EVB_DRIVERS_H__ */
