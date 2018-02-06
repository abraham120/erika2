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
 * CVS: $Id: ee_mcu.h,v 1.2 2006/10/25 13:59:02 pj Exp $
 */

#include "mcu/st_sta2051/inc/ee_mcuregs.h"

#ifndef __INCLUDE_ST_STA2051_MCU_H__
#define __INCLUDE_ST_STA2051_MCU_H__

/*************************************************************************
 Interrupt handling
 *************************************************************************/

#define ISR2(x) extern void x(void); void IRQFunc##x(void)


/*************************************************************************
 Timers
 *************************************************************************/

#ifdef __TIMER_0_USED__

/* enables T0 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer0_start(void) 
{ *T0_CR1 |= CR1_EN; }

/* stops T0 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer0_stop(void)
{ *T0_CR1 &= ~(CR1_EN); }

/* clears the pending IRQ request for T0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer0_clear(void)
{ *T0_SR = ~(SR_TOF); }

/* get the T0 value */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_sta2051_timer0_get(void)
{ return *T0_CNTR; }

/* init the timer as stopped, without interrupt, flags, ... , 
   with internal clock and prescaler=0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer0_init(void) 
{
  *T0_CNTR = 0;                  /* reset the counter to 0xFFFC */
  *T0_CR1  = 0;                  /* everything stopped, internal clock */
  *T0_CR2  = 0;                  /* no interrupts, prescaler to 0 */
  *T0_SR   = 0;                  /* clear timer status flags */
}

/* Set the timer with max prescaler, with interrupts at each overflow */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer0_periodic(void) 
{
  *T0_CR2  |= CR2_TOE | 0xff;     /* set OCAIE output compare A int. enable,
				    prescaler to 0xFF */
}

/* Set the timer prescaler */
__INLINE__ void __ALWAYS_INLINE__ 
EE_sta2051_timer0_set_prescaler(EE_UINT8 prescaler) 
{
  *T0_CR2 = (*T0_CR2 & 0xFF00) | prescaler;
}

#endif /* __TIMER_0_USED__ */



#ifdef __TIMER_1_USED__

/* enables T1 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer1_start(void) 
{ *T1_CR1 |= CR1_EN; }

/* stops T0 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer1_stop(void)
{ *T1_CR1 &= ~(CR1_EN); }

/* clears the pending IRQ request for T0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer1_clear(void)
{ *T1_SR = ~(SR_TOF); }

/* get the T0 value */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_sta2051_timer1_get(void)
{ return *T1_CNTR; }

/* init the timer as stopped, without interrupt, flags, ... , 
   with internal clock and prescaler=0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer1_init(void) 
{
  *T1_CNTR = 0;                  /* reset the counter to 0xFFFC */
  *T1_CR1  = 0;                  /* everything stopped, internal clock */
  *T1_CR2  = 0;                  /* no interrupts, prescaler to 0 */
  *T1_SR   = 0;                  /* clear timer status flags */
}

/* Set the timer with max prescaler, with interrupts at each overflow */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer1_periodic(void) 
{
  *T1_CR2  |= CR2_TOE | 0xff;     /* set OCAIE output compare A int. enable,
				    prescaler to 0xFF */
}

/* Set the timer prescaler */
__INLINE__ void __ALWAYS_INLINE__ 
EE_sta2051_timer1_set_prescaler(EE_UINT8 prescaler) 
{
  *T1_CR2 = (*T1_CR2 & 0xFF00) | prescaler;
}


#endif /* __TIMER_1_USED__ */




#ifdef __TIMER_2_USED__

/* enables T2 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer2_start(void) 
{ *T2_CR1 |= CR1_EN; }

/* stops T0 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer2_stop(void)
{ *T2_CR1 &= ~(CR1_EN); }

/* clears the pending IRQ request for T0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer2_clear(void)
{ *T2_SR = ~(SR_TOF); }

/* get the T0 value */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_sta2051_timer2_get(void)
{ return *T2_CNTR; }

/* init the timer as stopped, without interrupt, flags, ... , 
   with internal clock and prescaler=0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer2_init(void) 
{
  *T2_CNTR = 0;                  /* reset the counter to 0xFFFC */
  *T2_CR1  = 0;                  /* everything stopped, internal clock */
  *T2_CR2  = 0;                  /* no interrupts, prescaler to 0 */
  *T2_SR   = 0;                  /* clear timer status flags */
}

/* Set the timer with max prescaler, with interrupts at each overflow */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer2_periodic(void) 
{
  *T2_CR2  |= CR2_TOE | 0xff;     /* set OCAIE output compare A int. enable,
				    prescaler to 0xFF */
}

/* Set the timer prescaler */
__INLINE__ void __ALWAYS_INLINE__ 
EE_sta2051_timer2_set_prescaler(EE_UINT8 prescaler) 
{
  *T2_CR2 = (*T2_CR2 & 0xFF00) | prescaler;
}

#endif /* __TIMER_2_USED__ */


#ifdef __TIMER_3_USED__

/* enables T3 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer3_start(void) 
{ *T3_CR1 |= CR1_EN; }

/* stops T0 to count */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer3_stop(void)
{ *T3_CR1 &= ~(CR1_EN); }

/* clears the pending IRQ request for T0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer3_clear(void)
{ *T3_SR = ~(SR_TOF); }

/* get the T0 value */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_sta2051_timer3_get(void)
{ return *T3_CNTR; }

/* init the timer as stopped, without interrupt, flags, ... , 
   with internal clock and prescaler=0 */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer3_init(void) 
{
  *T3_CNTR = 0;                  /* reset the counter to 0xFFFC */
  *T3_CR1  = 0;                  /* everything stopped, internal clock */
  *T3_CR2  = 0;                  /* no interrupts, prescaler to 0 */
  *T3_SR   = 0;                  /* clear timer status flags */
}

/* Set the timer with max prescaler, with interrupts at each overflow */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_timer3_periodic(void) 
{
  *T3_CR2  |= CR2_TOE | 0xff;     /* set OCAIE output compare A int. enable,
				    prescaler to 0xFF */
}

/* Set the timer prescaler */
__INLINE__ void __ALWAYS_INLINE__ 
EE_sta2051_timer3_set_prescaler(EE_UINT8 prescaler) 
{
  *T3_CR2 = (*T3_CR2 & 0xFF00) | prescaler;
}

#endif /* __TIMER_3_USED__ */






/*
 * Timer
 */

#ifdef __TIME_SUPPORT__
/* Timer size */
typedef EE_UINT16 EE_TIME;

/* read current time (used by EDF scheduler) */
__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
    return 0xffff - EE_sta2051_timer0_get();
}
#endif





#endif
