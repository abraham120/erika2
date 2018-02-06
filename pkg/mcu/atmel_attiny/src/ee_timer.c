/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2017  Evidence Srl
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
  * Author: 2012 Pasquale Buonocunto
  * 	    2017 Giuseppe Serano
  */

#include "ee_internal.h"

#ifdef __TIMER_0_USED__
void EE_attiny_init_timer0(EE_UINT8 max_tick);
void EE_attiny_timer0_start();
void EE_attiny_timer0_stop();
#endif	/* __TIMER_0_USED__ */

#ifdef __TIMER_1_USED__
void EE_attiny_init_timer1(EE_UINT16 max_tick);
void EE_attiny_timer1_start();
void EE_attiny_timer1_stop();
#endif	/* __TIMER_1_USED__ */

#ifdef __TIMER_0_USED__
void EE_attiny_init_timer0(EE_UINT8 max_tick)
{
  TCCR0B |= (1 << WGM02);	/* Configure timer 0 for CTC mode */
  TIMSK |= (1 << OCIE0A);	/* Enable CTC interrupt		  */

#if	0
  EE_hal_enableIRQ();		/*  Enable global interrupts	  */
#endif	/* 0 */

  TIFR |= (1 << OCF0A);
  OCR0A = max_tick;		/* Set CTC compare value max_tick */
}

void EE_attiny_timer0_start()
{
  TCNT0 = 0x00U;
#ifdef	__TIMER0_CLK_DIV1__
  TCCR0B |= (1 << CS00);			/* Fcpu/1 (prescaler)	 */
#endif
#ifdef	__TIMER0_CLK_DIV8__
  TCCR0B |= (1 << CS01);			/* Fcpu/8 (prescaler)	 */
#endif
#ifdef	__TIMER0_CLK_DIV64__
  TCCR0B |= ((1 << CS00) | (1 << CS01));	/* Fcpu/64 (prescaler)	 */
#endif
#ifdef	__TIMER0_CLK_DIV256__
  TCCR0B |= (1 << CS02);			/* Fcpu/256 (prescaler)	 */
#endif
#ifdef	__TIMER0_CLK_DIV1024__
  TCCR0B |= ((1 << CS01) | (1 << CS02));	/* Fcpu/1024 (prescaler) */
#endif
}

void EE_attiny_timer0_stop()
{
  TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));	/* Stop timer */
}
#endif	/* __TIMER_0_USED__ */

#ifdef __TIMER_1_USED__
void EE_attiny_init_timer1(EE_UINT16 max_tick)	/* 16 bit timer */
{
   TCCR1B |= (1 << WGM12); 	/* Configure timer 1 for CTC mode */
   TIMSK |= (1 << OCIE1A);	/* Enable CTC interrupt		  */

#if	0
  EE_hal_enableIRQ();		/* Enable global interrupts	  */
#endif	/* 0 */

   TIFR |= (1 << OCF1A);
   OCR1A = max_tick;		/* Set CTC compare value max_tick */
}

void EE_attiny_timer1_start()
{
  TCNT1 = 0x00U;
  TCCR1B |= ((1 << CS10) | (1 << CS11)); /* Start timer at Fcpu/64 (prescaler) */
}

void EE_attiny_timer1_stop()
{
  TCCR1B &= ~((1 << CS10) | (1 << CS11)); /* Stop timer */
}
#endif	/* __TIMER_1_USED__ */
